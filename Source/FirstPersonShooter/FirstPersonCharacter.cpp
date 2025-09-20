#include "FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values can always change in blueprint
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
	// FirstPersonMesh is the mesh visible to the player in first person, doesn't clip with environment on camera
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(PlayerCamera);
	FirstPersonMesh->SetOnlyOwnerSee(true); // Only visible to player
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson; // Render separate from environment, but visible to camera
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));
	// GetMesh() returns the default character mesh, not visible to player but visible to engine
	GetMesh()->SetOwnerNoSee(true); // Not visible to player
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation; // Render separate from environment, bit not visible to camera
	GetCharacterMovement()->BrakingDecelerationFalling = 750.0f;
	GetCharacterMovement()->AirControl = 0.25f;
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

// Are we even going to do aiming? Or are we going to do hip fire?
// TODO: Don't allow sprint while aiming (also if possible maybe immediately sprint as they release aim)
void AFirstPersonCharacter::DoSprintStart() { bIsPressingSprint = true; }

void AFirstPersonCharacter::DoSprintEnd() { bIsPressingSprint = false; }

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
	bool bIsFalling = GetCharacterMovement()->IsFalling();
	if (SqrForward < SqrMovementDeadzone && SqrRight > SqrMovementDeadzone) return StrafeWalkSpeed;
	if (SqrForward > SqrMovementDeadzone && SqrRight > SqrMovementDeadzone) return bIsPressingSprint && !bIsFalling ? DiagonalSprintSpeed : DiagonalWalkSpeed;
	return bIsPressingSprint && !bIsFalling ? BaseSprintSpeed : BaseWalkSpeed;
}
