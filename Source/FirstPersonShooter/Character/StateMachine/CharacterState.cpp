#include "Character/StateMachine/CharacterState.h"

#include "Character/FirstPersonCharacter.h"

void UCharacterState::JumpStart(AFirstPersonCharacter* Character)
{
    if (Character && IsValid(Character)) Character->Jump();
}

void UCharacterState::JumpEnd(AFirstPersonCharacter* Character)
{
    if (Character && IsValid(Character)) Character->StopJumping();
}
