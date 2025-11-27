#include "CharacterStateMachine/CharacterState.h"
#include "FirstPersonCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Weapons/WeaponHolderComponent.h"
#include "CharacterStateMachine/IdleState.h"

void UCharacterState::Tick(AFirstPersonCharacter* Character, float DeltaSeconds)
{
	if (!Character || !IsValid(Character)) return;
	const float MovementDeadzone = Character->GetMovementDeadzone();
	if (Character->GetCharacterMovement()->Velocity.SquaredLength() < MovementDeadzone * MovementDeadzone && Character->GetCurrentCharacterState() != Character->GetIdleState())
		Character->SetCurrentCharacterState(Character->GetIdleState());
}

void UCharacterState::Move(AFirstPersonCharacter* Character, float Right, float Forward)
{
	if (!Character || !IsValid(Character)) return;
	const float Deadzone = Character->GetMovementDeadzone();
	Character->SetIsMovingLeft(Right < -Deadzone);
	Character->SetIsMovingRight(Right > Deadzone);
	Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxMovementSpeed(Right, Forward);
	Character->AddMovementInput(Character->GetActorRightVector(), Right);
	Character->AddMovementInput(Character->GetActorForwardVector(), Forward);
	if (Right * Right < Deadzone * Deadzone && Forward * Forward < Deadzone * Deadzone) Character->SetCurrentCharacterState(Character->GetIdleState());
}

void UCharacterState::JumpStart(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->Jump(); }

void UCharacterState::JumpEnd(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->StopJumping(); }

void UCharacterState::Shoot(AFirstPersonCharacter* Character)
{
	if (!Character || !IsValid(Character) || Character->GetCharacterMovement()->IsFalling()) return;
	bool bDoBulletSpread = Character->GetCharacterMovement()->Velocity.SizeSquared2D() > 1.0f;
	bool bWasSuccessfulShot = Character->GetWeaponHolderComponent()->Shoot(Character->GetBulletSpawnTransform()->GetComponentTransform(), bDoBulletSpread);
	if (!bWasSuccessfulShot) return;
	float Loudness = 1.0f;
	APawn* NoiseInstigator = Character;
	FVector NoiseLocation = Character->GetActorLocation();
	float MaxRange = 2000.0f;
	Character->Super::MakeNoise(Loudness, NoiseInstigator, NoiseLocation, MaxRange);
}