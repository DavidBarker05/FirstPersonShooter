#include "CharacterStateMachine/SprintState.h"
#include "FirstPersonCharacter.h"
#include "CharacterStateMachine/MoveState.h"

void USprintState::Enter(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->SetIsPressingSprint(true); }

void USprintState::Exit(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->SetIsPressingSprint(false); }

void USprintState::SprintEnd(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->SetCurrentCharacterState(Character->GetMoveState()); }
