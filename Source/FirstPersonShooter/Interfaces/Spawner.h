#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interfaces/Respawnable.h"
#include "Spawner.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class USpawner : public UInterface {
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API ISpawner {
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Spawn(TSubclassOf<AActor> ActorToSpawn);
};
