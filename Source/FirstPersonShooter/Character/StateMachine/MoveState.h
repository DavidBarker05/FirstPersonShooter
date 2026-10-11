#pragma once

#include "CoreMinimal.h"

#include "Character/StateMachine/CharacterState.h"

#include "MoveState.generated.h"

class AFirstPersonCharacter;

UCLASS()
class FIRSTPERSONSHOOTER_API UMoveState : public UCharacterState
{
    GENERATED_BODY()

public:
    virtual void Move(AFirstPersonCharacter* Character, float Right, float Forward) override;

    virtual void SprintStart(AFirstPersonCharacter* Character) override;

    virtual void Shoot(AFirstPersonCharacter* Character) override;
};
