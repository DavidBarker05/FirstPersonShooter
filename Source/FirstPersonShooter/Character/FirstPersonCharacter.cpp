#include "Character/FirstPersonCharacter.h"

#include "Camera/CameraComponent.h"
#include "Character/Components/CharacterHealthComponent.h"
#include "Character/Components/WeaponHolderComponent.h"
#include "Character/StateMachine/CharacterState.h"
#include "Character/StateMachine/IdleState.h"
#include "Character/StateMachine/MoveState.h"
#include "Character/StateMachine/SprintState.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "Events/EventBus.h"
#include "FirstPersonGameMode.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "InputActionValue.h"
#include "Kismet/GameplayStatics.h"
#include "MatchLeaderboard.h"
#include "NiagaraFunctionLibrary.h"
#include "NiagaraSystem.h"
#include "Perception/AISense_Damage.h"

AFirstPersonCharacter::AFirstPersonCharacter() :
    CurrentCharacterState(nullptr), IdleState(nullptr), MoveState(nullptr), SprintState(nullptr)
{
    PrimaryActorTick.bCanEverTick = true;
    GetCapsuleComponent()->InitCapsuleSize(34.0f, 90.0f);
    PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
    PlayerCamera->SetupAttachment(GetMesh());
    PlayerCamera->bUsePawnControlRotation = true;
    PlayerCamera->bEnableFirstPersonFieldOfView = true;
    PlayerCamera->bEnableFirstPersonScale = true;
    PlayerCamera->FirstPersonFieldOfView = 70.0f;
    PlayerCamera->FirstPersonScale = 0.6f;
    FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
    FirstPersonMesh->SetupAttachment(PlayerCamera);
    FirstPersonMesh->SetOnlyOwnerSee(true);
    FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson;
    FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));
    GetMesh()->SetOwnerNoSee(true);
    GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation;
    GetCharacterMovement()->BrakingDecelerationFalling = 750.0f;
    GetCharacterMovement()->AirControl = 0.25f;
    CharacterHealthComponent = CreateDefaultSubobject<UCharacterHealthComponent>(TEXT("Character Health Component"));
    WeaponHolderComponent = CreateDefaultSubobject<UWeaponHolderComponent>(TEXT("Weapon Holder Component"));
    BulletSpawnOffset = CreateDefaultSubobject<USpringArmComponent>(TEXT("Bullet Spawn Offset"));
    BulletSpawnOffset->SetupAttachment(PlayerCamera);
    BulletSpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Bullet Spawn Transform"));
    BulletSpawnTransform->SetupAttachment(BulletSpawnOffset, USpringArmComponent::SocketName);
}

void AFirstPersonCharacter::BeginPlay()
{
    Super::BeginPlay();
    SUBSCRIBE_TO_EVENTS();
    GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
    bIsPressingSprint = false;
    IdleState = NewObject<UIdleState>(this);
    MoveState = NewObject<UMoveState>(this);
    SprintState = NewObject<USprintState>(this);
    SetCurrentCharacterState(IdleState);
}

void AFirstPersonCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    UNSUBSCRIBE_FROM_EVENTS();
    Super::EndPlay(EndPlayReason);
}

void AFirstPersonCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    UpdateBulletSpawnPos();
}

void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);
        EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this,
                                           &AFirstPersonCharacter::Look);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this,
                                           &AFirstPersonCharacter::DoJumpStart);
        EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this,
                                           &AFirstPersonCharacter::DoJumpEnd);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this,
                                           &AFirstPersonCharacter::DoSprintStart);
        EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this,
                                           &AFirstPersonCharacter::DoSprintEnd);
        EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoShoot);
        EnhancedInputComponent->BindAction(WeaponOneSelectAction, ETriggerEvent::Started, this,
                                           &AFirstPersonCharacter::DoSelectWeaponOne);
        EnhancedInputComponent->BindAction(WeaponTwoSelectAction, ETriggerEvent::Started, this,
                                           &AFirstPersonCharacter::DoSelectWeaponTwo);
        EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoPause);

#if WITH_EDITOR
        EnhancedInputComponent->BindAction(EditorPauseAction, ETriggerEvent::Started, this,
                                           &AFirstPersonCharacter::DoPause);
#endif
    }
}

void AFirstPersonCharacter::OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params)
{
    if (EVENT_MATCHES(TEXT("RiflePickupEvent"), 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(UObject*))
    {
        if (*Params[0].Get<UObject*>() == this) WeaponHolderComponent->PickUpRifle();
    }
    else if (EVENT_MATCHES(TEXT("DeathEvent"), 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(UObject*))
    {
        if (*Params[0].Get<UObject*>() != this) return;
        ADD_KILL_TO_LEADERBOARD(CharacterThatLastShotThisCharacter, LeaderboardName);
        BROADCAST_EVENT(TEXT("RespawnEvent"), UGameplayStatics::GetGameMode(GetWorld()), this,
                        CharacterHealthComponent->GetRespawnDelay());
    }
    else if (EVENT_MATCHES(TEXT("BulletHitEvent"), 5) && PARAMS_ARE_VALID &&
             PARAMS_ARE_CORRECT_TYPES(AActor*, int32, AActor*, FVector, FVector))
    {
        AActor* DamagedActor = *Params[0].Get<AActor*>();
        if (!IsValid(DamagedActor)) return;
        const FVector HitLocation = *Params[3].Get<FVector>();
        const FVector HitNormal = *Params[4].Get<FVector>();
        if (!DamagedActor->IsA<ACharacter>())
        {
            if (SparkSystem)
            {
                UNiagaraFunctionLibrary::SpawnSystemAtLocation(
                    GetWorld(), SparkSystem, HitLocation, FRotationMatrix::MakeFromZ(HitNormal).Rotator(),
                    FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);
            }
            return;
        }
        AActor* DamageInstigator = *Params[2].Get<AActor*>();
        if (DamageInstigator == this)
        {
            HitMarkerDelegate.Broadcast();
            return;
        }
        if (DamagedActor != this) return;
        const int32 Damage = *Params[1].Get<int32>();
        CharacterHealthComponent->TakeDamage(Damage);
        UObject* WorldContextObject = GetWorld();
        const float DamageAmount = Damage;
        const FVector EventLocation = DamageInstigator->GetActorLocation();
        UAISense_Damage::ReportDamageEvent(WorldContextObject, DamagedActor, DamageInstigator, DamageAmount,
                                           EventLocation, HitLocation);
        if (const AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(DamageInstigator))
            CharacterThatLastShotThisCharacter = Character->GetLeaderboardName();
        else CharacterThatLastShotThisCharacter = "Unknown";
        if (IsPlayerControlled())
        {
            HitEffectDelegate.Broadcast();
            return;
        }
        if (BloodSystem)
        {
            UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), BloodSystem, HitLocation,
                                                           FRotationMatrix::MakeFromZ(HitNormal).Rotator(),
                                                           FVector::OneVector, true, true, ENCPoolMethod::AutoRelease);
        }
    }
    else if (EVENT_MATCHES(TEXT("HealthPickupEvent"), 2) && PARAMS_ARE_VALID &&
             PARAMS_ARE_CORRECT_TYPES(AFirstPersonCharacter*, int32))
    {
        if (*Params[0].Get<AFirstPersonCharacter*>() != this) return;
        if (const int32 HealAmount = *Params[1].Get<int32>()) CharacterHealthComponent->ReceiveHealth(HealAmount);
    }
}

void AFirstPersonCharacter::Move(const FInputActionValue& Value)
{
    const FVector2D MoveVector = Value.Get<FVector2D>();
    DoMove(MoveVector.X, MoveVector.Y);
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value)
{
    const FVector2D LookVector = Value.Get<FVector2D>();
    DoLook(LookVector.X, LookVector.Y);
}

void AFirstPersonCharacter::DoMove(const float Right, const float Forward)
{
    if (GetController() && IsValid(GetController()) && IsValid(CurrentCharacterState))
        CurrentCharacterState->Move(this, Right, Forward);
}

void AFirstPersonCharacter::DoLook(const float Yaw, const float Pitch)
{
    if (!GetController()) return;
    AddControllerYawInput(Yaw);
    AddControllerPitchInput(Pitch);
}

void AFirstPersonCharacter::DoJumpStart()
{
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->JumpStart(this);
}

void AFirstPersonCharacter::DoJumpEnd()
{
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->JumpEnd(this);
}

void AFirstPersonCharacter::DoSprintStart()
{
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->SprintStart(this);
}

void AFirstPersonCharacter::DoSprintEnd()
{
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->SprintEnd(this);
}

void AFirstPersonCharacter::DoShoot()
{
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->Shoot(this);
}

void AFirstPersonCharacter::DoSelectWeaponOne() { WeaponHolderComponent->EquipPistol(); }

void AFirstPersonCharacter::DoSelectWeaponTwo() { WeaponHolderComponent->EquipRifle(); }

void AFirstPersonCharacter::DoPause()
{
    if (!GetWorld()) return;
    if (const AFirstPersonGameMode* FirstPersonGameMode =
            Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
    {
        if (FirstPersonGameMode->GetCurrentMatchState() != EGameMatchState::MatchRoundPhase) return;
        bIsPaused = !bIsPaused;
        if (bIsPaused)
        {
            // Delay until next tick to guarantee that pause screen will be added
            GetWorldTimerManager().SetTimerForNextTick([this]() { UGameplayStatics::SetGamePaused(GetWorld(), true); });
        }
        else UGameplayStatics::SetGamePaused(GetWorld(), false);
    }
}

float AFirstPersonCharacter::GetMaxMovementSpeed(const float Right, const float Forward) const
{
    if (Forward < -MovementDeadzone) return BackwardsWalkSpeed;
    const float SqrRight = Right * Right;
    const float SqrForward = Forward * Forward;
    const float SqrMovementDeadzone = MovementDeadzone * MovementDeadzone;
    if (SqrForward < SqrMovementDeadzone && SqrRight > SqrMovementDeadzone) return StrafeWalkSpeed;
    const bool bIsFalling = GetCharacterMovement()->IsFalling();
    if (SqrForward > SqrMovementDeadzone && SqrRight > SqrMovementDeadzone)
        return bIsPressingSprint && !bIsFalling ? DiagonalSprintSpeed : DiagonalWalkSpeed;
    return bIsPressingSprint && !bIsFalling ? BaseSprintSpeed : BaseWalkSpeed;
}

void AFirstPersonCharacter::SetCurrentCharacterState(UCharacterState* NewState)
{
    if (!IsValid(NewState)) return;
    if (IsValid(CurrentCharacterState)) CurrentCharacterState->Exit(this);
    CurrentCharacterState = NewState;
    CurrentCharacterState->Enter(this);
}

void AFirstPersonCharacter::UpdateBulletSpawnPos() const
{
    const float CamToWeaponSocketDistFP =
        FVector::Dist(PlayerCamera->GetComponentLocation(), FirstPersonMesh->GetSocketLocation(FName("WeaponSocket")));
    const float CamToWeaponSocketDistTP =
        FVector::Dist(PlayerCamera->GetComponentLocation(), GetMesh()->GetSocketLocation(FName("WeaponSocket")));
    const float CamToWeaponSocketAvgDist = (CamToWeaponSocketDistFP + CamToWeaponSocketDistTP) / 2.0f;
    BulletSpawnOffset->TargetArmLength = -CamToWeaponSocketAvgDist;
}
