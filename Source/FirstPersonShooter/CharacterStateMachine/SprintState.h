#pragma once

#include "CoreMinimal.h"
#include "CharacterStateMachine/CharacterState.h"
#include "SprintState.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API USprintState : public UCharacterState
{
	GENERATED_BODY()
	
public:
    virtual void Enter(class AFirstPersonCharacter* Character) override;
    virtual void Exit(class AFirstPersonCharacter* Character) override;

    virtual void SprintEnd(class AFirstPersonCharacter* Character) override;

    virtual void Shoot(class AFirstPersonCharacter* Character) override { }
};
