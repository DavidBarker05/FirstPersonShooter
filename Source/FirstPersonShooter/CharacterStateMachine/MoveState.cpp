#include "CharacterStateMachine/MoveState.h"
#include "FirstPersonCharacter.h"
#include "CharacterStateMachine/SprintState.h"

void UMoveState::SprintStart(AFirstPersonCharacter* Character) { if (Character && IsValid(Character)) Character->SetCurrentCharacterState(Character->GetSprintState()); }