#include "FirstPersonCharacter.h"
#include "Animation/AnimInstance.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "GameFramework/CharacterMovementComponent.h"

// Sets default values can always change in blueprint
AFirstPersonCharacter::AFirstPersonCharacter() {
	GetCapsuleComponent()->InitCapsuleSize(34.0f, 90.0f);
	// FirstPersonMesh is the mesh visible to the player in first person, doesn't clip with environment on camera
	FirstPersonMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	FirstPersonMesh->SetupAttachment(GetMesh());
	FirstPersonMesh->SetOnlyOwnerSee(true); // Only visible to player
	FirstPersonMesh->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::FirstPerson; // Render separate from environment, but visible to camera
	FirstPersonMesh->SetCollisionProfileName(FName("NoCollision"));
	PlayerCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Player Camera"));
	PlayerCamera->SetupAttachment(FirstPersonMesh);
	// If attach to head then certain bones need to be fixed by control rig, see First Person Template
	//PlayerCamera->SetupAttachment(FirstPersonMesh, FName("head"));
	PlayerCamera->bUsePawnControlRotation = true;
	PlayerCamera->bEnableFirstPersonFieldOfView = true;
	PlayerCamera->bEnableFirstPersonScale = true;
	PlayerCamera->FirstPersonFieldOfView = 70.0f;
	PlayerCamera->FirstPersonScale = 0.6f;
	// GetMesh() returns the default character mesh, not visible to player but visible to engine
	GetMesh()->SetOwnerNoSee(true); // Not visible to player
	GetMesh()->FirstPersonPrimitiveType = EFirstPersonPrimitiveType::WorldSpaceRepresentation; // Render separate from environment, bit not visible to camera
	GetCharacterMovement()->BrakingDecelerationFalling = 1500.0f;
	GetCharacterMovement()->AirControl = 0.5f;
}

void AFirstPersonCharacter::BeginPlay() {
	Super::BeginPlay();
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
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

// TODO: Don't allow sprint while aiming (also if possible maybe immediately sprint as they release aim)
void AFirstPersonCharacter::DoSprintStart() { GetCharacterMovement()->MaxWalkSpeed = SprintSpeed; }

void AFirstPersonCharacter::DoSprintEnd() { GetCharacterMovement()->MaxWalkSpeed = WalkSpeed; }
