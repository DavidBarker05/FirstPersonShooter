#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "CharacterState.generated.h"

UCLASS(Abstract, Blueprintable)
class FIRSTPERSONSHOOTER_API UCharacterState : public UObject
{
	GENERATED_BODY()

public:
    virtual void Enter(class AFirstPersonCharacter* Character) { }
    virtual void Exit(class AFirstPersonCharacter* Character) { }

    virtual void Tick(class AFirstPersonCharacter* Character, float DeltaSeconds);

    virtual void Move(class AFirstPersonCharacter* Character, float Right, float Forward);

    virtual void JumpStart(class AFirstPersonCharacter* Character);
    virtual void JumpEnd(class AFirstPersonCharacter* Character);

    virtual void SprintStart(class AFirstPersonCharacter* Character) { }
    virtual void SprintEnd(class AFirstPersonCharacter* Character) { }

    virtual void Shoot(class AFirstPersonCharacter* Character);
};
