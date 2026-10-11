#pragma once

#include "CoreMinimal.h"

#include "Character/StateMachine/CharacterState.h"

#include "SprintState.generated.h"

class AFirstPersonCharacter;

UCLASS()
class FIRSTPERSONSHOOTER_API USprintState : public UCharacterState
{
    GENERATED_BODY()

public:
    virtual void Enter(AFirstPersonCharacter* Character) override;
    virtual void Exit(AFirstPersonCharacter* Character) override;

    virtual void Move(AFirstPersonCharacter* Character, float Right, float Forward) override;

    virtual void SprintEnd(AFirstPersonCharacter* Character) override;
};
