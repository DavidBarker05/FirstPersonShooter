#include "FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "CharacterHealthComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Weapons/WeaponHolderComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

AFirstPersonCharacter::AFirstPersonCharacter() {
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

void AFirstPersonCharacter::BeginPlay() {
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = BaseWalkSpeed;
}

void AFirstPersonCharacter::Tick(float DeltaSeconds) {
	Super::Tick(DeltaSeconds);
	MoveCameraToSocket();
}

void AFirstPersonCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) {
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent)) {
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Move);
		EnhancedInputComponent->BindAction(MouseLookAction, ETriggerEvent::Triggered, this, &AFirstPersonCharacter::Look);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoJumpStart);
		EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::DoJumpEnd);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSprintStart);
		EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::DoSprintEnd);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoShootStart);
		EnhancedInputComponent->BindAction(ShootAction, ETriggerEvent::Completed, this, &AFirstPersonCharacter::DoShootEnd);
		EnhancedInputComponent->BindAction(WeaponOneSelectAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSelectWeaponOne);
		EnhancedInputComponent->BindAction(WeaponTwoSelectAction, ETriggerEvent::Started, this, &AFirstPersonCharacter::DoSelectWeaponTwo);
	}
}

void AFirstPersonCharacter::Move(const FInputActionValue& Value) {
	FVector2D MoveVector = Value.Get<FVector2D>();
	DoMove(MoveVector.X, MoveVector.Y);
}

void AFirstPersonCharacter::Look(const FInputActionValue& Value) {
	FVector2D LookVector = Value.Get<FVector2D>();
	DoLook(LookVector.X, LookVector.Y);
}

void AFirstPersonCharacter::DoMove(const float Right, const float Forward) {
	if (!GetController()) return;
	GetCharacterMovement()->MaxWalkSpeed = GetMaxMovementSpeed(Right, Forward);
	bIsMovingLeft = Right < -MovementDeadzone;
	bIsMovingRight = Right > MovementDeadzone;
	AddMovementInput(GetActorRightVector(), Right);
	AddMovementInput(GetActorForwardVector(), Forward);
}

void AFirstPersonCharacter::DoLook(const float Yaw, const float Pitch) {
	if (!GetController()) return;
	AddControllerYawInput(Yaw);
	AddControllerPitchInput(Pitch);
}

void AFirstPersonCharacter::DoJumpStart() { Jump(); }

void AFirstPersonCharacter::DoJumpEnd() { StopJumping(); }

void AFirstPersonCharacter::DoSprintStart() { bIsPressingSprint = true; }

void AFirstPersonCharacter::DoSprintEnd() { bIsPressingSprint = false; }

void AFirstPersonCharacter::DoShootStart() {
	if (bIsPressingShoot) return;
	bIsPressingShoot = true;
	if (GetCharacterMovement()->MaxWalkSpeed == BaseSprintSpeed || GetCharacterMovement()->MaxWalkSpeed == DiagonalSprintSpeed || GetCharacterMovement()->IsFalling()) return;
	float CamToWeaponSocketDistFP = FVector::DistXY(PlayerCamera->GetComponentLocation(), FirstPersonMesh->GetSocketLocation(FName("WeaponSocket")));
	float CamToWeaponSocketDistTP = FVector::DistXY(PlayerCamera->GetComponentLocation(), GetMesh()->GetSocketLocation(FName("WeaponSocket")));
	float CamToWeaponSocketDistAvg = (CamToWeaponSocketDistFP + CamToWeaponSocketDistTP) / 2.0f;
	BulletSpawnOffset->TargetArmLength = -CamToWeaponSocketDistAvg;
	FTransform SpawnTransform(BulletSpawnTransform->GetComponentTransform());
	if (GetCharacterMovement()->Velocity.SizeSquared2D() > 1.0f) {
		FVector ForwardVector = SpawnTransform.GetRotation().GetForwardVector();
		float SpreadRadians = FMath::DegreesToRadians(MovementBulletSpread);
		FVector ShootDirection = FMath::VRandCone(ForwardVector, SpreadRadians);
		FRotator ShootRotation = ShootDirection.Rotation();
		SpawnTransform.SetRotation(ShootRotation.Quaternion());
	}
	WeaponHolderComponent->Shoot(SpawnTransform);
}

void AFirstPersonCharacter::DoShootEnd() { bIsPressingShoot = false; }

void AFirstPersonCharacter::DoSelectWeaponOne() { WeaponHolderComponent->EquipPistol(); }

void AFirstPersonCharacter::DoSelectWeaponTwo() { WeaponHolderComponent->EquipRifle(); }

void AFirstPersonCharacter::MoveCameraToSocket() {
	FVector CamPos = PlayerCamera->GetComponentLocation();
	FVector CamSocketPos = GetMesh()->GetSocketLocation(FName("CameraSocket"));
	float SqrDist = FVector::DistSquared(CamPos, CamSocketPos);
	float SqrCamMoveThresh = CameraMoveThreshold * CameraMoveThreshold;
	if (SqrDist < SqrCamMoveThresh) return;
	float Alpha = FMath::Clamp(SqrDist / (9.0f * SqrCamMoveThresh), 0.0f, 1.0f);
	PlayerCamera->SetWorldLocation(UKismetMathLibrary::VLerp(CamPos, CamSocketPos, Alpha));
}

float AFirstPersonCharacter::GetMaxMovementSpeed(const float Right, const float Forward) {
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