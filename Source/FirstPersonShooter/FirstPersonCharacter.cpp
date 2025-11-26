#include "FirstPersonCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "CharacterHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/WeaponHolderComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "Events/EventBus.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"
#include "MatchLeaderboard.h"
#include "FirstPersonGameMode.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

AFirstPersonCharacter::AFirstPersonCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 90.0f);
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(GetMesh());;
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
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::DoJumpEnd);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::DoSprintEnd);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoShoot);
		EnhancedInputComponent->BindAction(WeaponOneSelectAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSelectWeaponOne);
		EnhancedInputComponent->BindAction(WeaponTwoSelectAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSelectWeaponTwo);
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoPause);
	}
}

void AFirstPersonCharacter::Move(const FInputActionValue& Value)
{
	FVector2D MoveVector = Value.Get<FVector2D>();
	DoMove(MoveVector.X, MoveVector.Y);
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value)
{
	FVector2D LookVector = Value.Get<FVector2D>();
	DoLook(LookVector.X, LookVector.Y);
}

void AFirstPersonCharacter::DoMove(const float Right, const float Forward)
{
	if (!GetController()) return;
	GetCharacterMovement()->MaxWalkSpeed = GetMaxMovementSpeed(Right, Forward);
	bIsMovingLeft = Right < -MovementDeadzone;
	bIsMovingRight = Right > MovementDeadzone;
	AddMovementInput(GetActorRightVector(), Right);
	AddMovementInput(GetActorForwardVector(), Forward);
}

void AFirstPersonCharacter::DoLook(const float Yaw, const float Pitch)
{
	if (!GetController()) return;
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void AFirstPersonCharacter::DoJumpStart() { Jump(); }

void AFirstPersonCharacter::DoJumpEnd() { StopJumping(); }

void AFirstPersonCharacter::DoSprintStart() { bIsPressingSprint = true; }

void AFirstPersonCharacter::DoSprintEnd() { bIsPressingSprint = false; }

void AFirstPersonCharacter::DoShoot()
{
	if (GetCharacterMovement()->Velocity.SizeSquared2D() > BaseWalkSpeed * BaseWalkSpeed || GetCharacterMovement()->IsFalling()) return;
	bool bDoBulletSpread = GetCharacterMovement()->Velocity.SizeSquared2D() > 1.0f;
	bool bWasSuccessfulShot = WeaponHolderComponent->Shoot(BulletSpawnTransform->GetComponentTransform(), bDoBulletSpread);
	if (!bWasSuccessfulShot) return;
	float Loudness = 1.0f;
	APawn* NoiseInstigator = this;
	FVector NoiseLocation = GetActorLocation();
	float MaxRange = 2000.0f;
	Super::MakeNoise(Loudness, NoiseInstigator, NoiseLocation, MaxRange);
}

void AFirstPersonCharacter::DoSelectWeaponOne() { WeaponHolderComponent->EquipPistol(); }

void AFirstPersonCharacter::DoSelectWeaponTwo() { WeaponHolderComponent->EquipRifle(); }

void AFirstPersonCharacter::DoPause()
{
	if (!PauseWidgetBlueprint || !IsValid(PauseWidgetBlueprint) || !GetWorld()) return;
	if (AFirstPersonGameMode* FirstPersonGameMode = Cast<AFirstPersonGameMode>(UGameplayStatics::GetGameMode(GetWorld())))
	{
		if (FirstPersonGameMode->GetCurrentMatchState() != GameMatchState::MatchRoundPhase) return;
		bIsPaused = !bIsPaused;
		UGameplayStatics::SetGamePaused(GetWorld(), bIsPaused);
		if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
		{
			if (bIsPaused && !WidgetInstance)
			{
				if (PlayerScreenWidgetInstance && IsValid(PlayerScreenWidgetInstance)) PlayerScreenWidgetInstance->RemoveFromParent();
				WidgetInstance = CreateWidget<UUserWidget>(PlayerController, PauseWidgetBlueprint);
				if (WidgetInstance) WidgetInstance->AddToPlayerScreen();
			}
			else if (!bIsPaused && WidgetInstance)
			{
				WidgetInstance->RemoveFromParent();
				WidgetInstance = nullptr;
				if (PlayerScreenWidgetInstance && IsValid(PlayerScreenWidgetInstance)) PlayerScreenWidgetInstance->AddToPlayerScreen();
			}
			else
			{
				GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("WidgetInstance was manipulated outside of FirstPersonCharacter.cpp"));
				UE_LOG(LogTemp, Error, TEXT("WidgetInstance was manipulated outside of FirstPersonCharacter.cpp"));
				return;
			}
		}
	}
}

void AFirstPersonCharacter::UpdateBulletSpawnPos()
{
	float CamToWeaponSocketDistFP = FVector::Dist(PlayerCamera->GetComponentLocation(), FirstPersonMesh->GetSocketLocation(FName("WeaponSocket")));
	float CamToWeaponSocketDistTP = FVector::Dist(PlayerCamera->GetComponentLocation(), GetMesh()->GetSocketLocation(FName("WeaponSocket")));
	float CamToWeaponSocketAvgDist = (CamToWeaponSocketDistFP + CamToWeaponSocketDistTP) / 2.0f;
	BulletSpawnOffset->TargetArmLength = -CamToWeaponSocketAvgDist;
}

float AFirstPersonCharacter::GetMaxMovementSpeed(const float Right, const float Forward)
{
	if (Forward < -MovementDeadzone) return BackwardsWalkSpeed;
	float SqrRight = Right * Right;
	float SqrForward = Forward * Forward;
	float SqrMovementDeadzone = MovementDeadzone * MovementDeadzone;
	if (SqrForward < SqrMovementDeadzone && SqrRight > SqrMovementDeadzone) return StrafeWalkSpeed;
	bool bIsFalling = GetCharacterMovement()->IsFalling();
	if (SqrForward > SqrMovementDeadzone && SqrRight > SqrMovementDeadzone) return bIsPressingSprint && !bIsFalling ? DiagonalSprintSpeed : DiagonalWalkSpeed;
	return bIsPressingSprint && !bIsFalling ? BaseSprintSpeed : BaseWalkSpeed;
}

UCharacterHealthComponent* AFirstPersonCharacter::GetCharacterHealthComponent() { return CharacterHealthComponent; }

UWeaponHolderComponent* AFirstPersonCharacter::GetWeaponHolderComponent() { return WeaponHolderComponent; }

USkeletalMeshComponent* AFirstPersonCharacter::GetFirstPersonMesh() { return FirstPersonMesh; }

void AFirstPersonCharacter::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params)
{
	if (EVENT_MATCHES("RiflePickupEvent", 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct))
	{
		if (*Params[0].Get<FUObjectStruct>() == this) WeaponHolderComponent->PickUpRifle();
	}
	else if (EVENT_MATCHES("DeathEvent", 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct))
	{
		if (*Params[0].Get<FUObjectStruct>() == this)
		{
			ADD_KILL_TO_LEADERBOARD(CharacterThatLastShotThisCharacter, LeaderboardName);
			BROADCAST_EVENT("RespawnEvent", FUObjectStruct((UObject*) UGameplayStatics::GetGameMode(GetWorld())), FUObjectStruct(this), FFloatStruct(CharacterHealthComponent->GetRespawnDelay()));
		}
	}
	else if (EVENT_MATCHES("BulletHitEvent", 3) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct, FInt32Struct, FUObjectStruct))
	{
		if (*Params[0].Get<FUObjectStruct>() != this) return;
		if (const FInt32Struct* Damage = Params[1].Get<FInt32Struct>())
		{
			CharacterHealthComponent->TakeDamage(*Damage);
			if (AActor* DamageInstigator = Params[2].Get<FUObjectStruct>()->CastAs<AActor>())
			{
				UObject* WorldContextObject = GetWorld();
				AActor* DamagedActor = this;
				float DamageAmount = (float) Damage->Get();
				FVector EventLocation = DamageInstigator->GetActorLocation();
				FVector HitLocation = GetActorLocation();
				UAISense_Damage::ReportDamageEvent(WorldContextObject, DamagedActor, DamageInstigator, DamageAmount, EventLocation, HitLocation);
				if (AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(DamageInstigator)) CharacterThatLastShotThisCharacter = Character->GetLeaderboardName();
				else CharacterThatLastShotThisCharacter = "Unknown";
			}
		}
	}
	else if (EVENT_MATCHES("HealthPickupEvent", 2) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct, FInt32Struct))
	{
		if (*Params[0].Get<FUObjectStruct>() != this) return;
		if (const FInt32Struct* HealAmount = Params[1].Get<FInt32Struct>()) CharacterHealthComponent->ReceiveHealth(*HealAmount);
	}
}