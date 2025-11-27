#include "CharacterStateMachine/IdleState.h"
#include "FirstPersonCharacter.h"
#include "CharacterStateMachine/MoveState.h"

void UIdleState::Move(AFirstPersonCharacter* Character, float Right, float Forward)
{
	if (!Character || !IsValid(Character)) return;
	const float Deadzone = Character->GetMovementDeadzone();
	if (Right * Right < Deadzone * Deadzone && Forward * Forward < Deadzone * Deadzone) return;
	Character->SetCurrentCharacterState(Character->GetMoveState());
	Character->GetCurrentCharacterState()->Move(Character, Right, Forward);
}
