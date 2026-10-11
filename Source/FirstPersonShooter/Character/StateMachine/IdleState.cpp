#include "Character/StateMachine/IdleState.h"

#include "Character/Components/WeaponHolderComponent.h"
#include "Character/FirstPersonCharacter.h"

#include "Character/StateMachine/MoveState.h"

void UIdleState::Move(AFirstPersonCharacter* Character, float Right, float Forward)
{
    if (!IsValid(Character)) return;
    const float Deadzone = Character->GetMovementDeadzone();
    Character->SetIsMovingLeft(Right < -Deadzone);
    Character->SetIsMovingRight(Right > Deadzone);
    Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxMovementSpeed(Right, Forward);
    if (Right * Right < Deadzone * Deadzone && Forward * Forward < Deadzone * Deadzone) return;
    Character->AddMovementInput(Character->GetActorForwardVector(), Forward);
    Character->AddMovementInput(Character->GetActorRightVector(), Right);
    Character->SetCurrentCharacterState(Character->GetMoveState());
}

void UIdleState::Shoot(AFirstPersonCharacter* Character)
{
    if (!IsValid(Character) || Character->GetCharacterMovement()->IsFalling()) return;
    const bool bWasSuccessfulShot = Character->GetWeaponHolderComponent()->Shoot(
        Character->GetBulletSpawnTransform()->GetComponentTransform(), false);
    if (bWasSuccessfulShot) Character->MakeNoise(1.0f, Character, Character->GetActorLocation(), 2000.0f);
}
