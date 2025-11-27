#pragma once

#include "CoreMinimal.h"
#include "CharacterStateMachine/CharacterState.h"
#include "MoveState.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API UMoveState : public UCharacterState
{
	GENERATED_BODY()

public:
    virtual void SprintStart(class AFirstPersonCharacter* Character) override;
};
