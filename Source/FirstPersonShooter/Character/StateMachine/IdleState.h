#pragma once

#include "CoreMinimal.h"

#include "Character/StateMachine/CharacterState.h"

#include "IdleState.generated.h"

class AFirstPersonCharacter;

UCLASS()
class FIRSTPERSONSHOOTER_API UIdleState : public UCharacterState
{
    GENERATED_BODY()

public:
    virtual void Move(AFirstPersonCharacter* Character, float Right, float Forward) override;

    virtual void Shoot(AFirstPersonCharacter* Character) override;
};
