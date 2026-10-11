#pragma once

#include "CoreMinimal.h"

#include "CharacterState.generated.h"

class AFirstPersonCharacter;

UCLASS(Abstract, Blueprintable)
class FIRSTPERSONSHOOTER_API UCharacterState : public UObject
{
    GENERATED_BODY()

public:
    virtual void Enter(AFirstPersonCharacter* Character) { }
    virtual void Exit(AFirstPersonCharacter* Character) { }

    virtual void Move(AFirstPersonCharacter* Character, float Right, float Forward) { }

    virtual void JumpStart(AFirstPersonCharacter* Character);
    virtual void JumpEnd(AFirstPersonCharacter* Character);

    virtual void SprintStart(AFirstPersonCharacter* Character) { }
    virtual void SprintEnd(AFirstPersonCharacter* Character) { }

    virtual void Shoot(AFirstPersonCharacter* Character) { }
};
