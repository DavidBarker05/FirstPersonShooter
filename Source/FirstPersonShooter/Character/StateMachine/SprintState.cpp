#include "Character/StateMachine/SprintState.h"

#include "Character/FirstPersonCharacter.h"
#include "Character/StateMachine/IdleState.h"
#include "Character/StateMachine/MoveState.h"

void USprintState::Enter(AFirstPersonCharacter* Character)
{
    if (IsValid(Character)) Character->SetIsPressingSprint(true);
}

void USprintState::Exit(AFirstPersonCharacter* Character)
{
    if (IsValid(Character)) Character->SetIsPressingSprint(false);
}

void USprintState::Move(AFirstPersonCharacter* Character, float Right, float Forward)
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

void USprintState::SprintEnd(AFirstPersonCharacter* Character)
{
    if (IsValid(Character)) Character->SetCurrentCharacterState(Character->GetMoveState());
}
