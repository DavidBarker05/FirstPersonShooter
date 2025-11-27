#pragma once

#include "CoreMinimal.h"
#include "CharacterStateMachine/CharacterState.h"
#include "IdleState.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API UIdleState : public UCharacterState
{
	GENERATED_BODY()

public:
	virtual void Move(class AFirstPersonCharacter* Character, float Right, float Forward) override;
};
