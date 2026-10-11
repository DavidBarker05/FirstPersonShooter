#include "Character/StateMachine/MoveState.h"

#include "Character/Components/WeaponHolderComponent.h"
#include "Character/FirstPersonCharacter.h"
#include "Character/StateMachine/IdleState.h"
#include "Character/StateMachine/SprintState.h"

void UMoveState::Move(AFirstPersonCharacter* Character, float Right, float Forward)
{
    if (!IsValid(Character)) return;
    const float Deadzone = Character->GetMovementDeadzone();
    Character->SetIsMovingLeft(Right < -Deadzone);
    Character->SetIsMovingRight(Right > Deadzone);
    Character->GetCharacterMovement()->MaxWalkSpeed = Character->GetMaxMovementSpeed(Right, Forward);
    if (Right * Right < Deadzone * Deadzone && Forward * Forward < Deadzone * Deadzone)
        Character->SetCurrentCharacterState(Character->GetIdleState());
    else
    {
        if (Right * Right >= Deadzone * Deadzone) Character->AddMovementInput(Character->GetActorRightVector(), Right);
        if (Forward * Forward >= Deadzone * Deadzone)
            Character->AddMovementInput(Character->GetActorForwardVector(), Forward);
    }
}

void UMoveState::SprintStart(AFirstPersonCharacter* Character)
{
    if (IsValid(Character)) Character->SetCurrentCharacterState(Character->GetSprintState());
}

void UMoveState::Shoot(AFirstPersonCharacter* Character)
{
    if (!IsValid(Character) || Character->GetCharacterMovement()->IsFalling()) return;
    const bool bWasSuccessfulShot = Character->GetWeaponHolderComponent()->Shoot(
        Character->GetBulletSpawnTransform()->GetComponentTransform(), true);
    if (bWasSuccessfulShot) Character->MakeNoise(1.0f, Character, Character->GetActorLocation(), 2000.0f);
}
