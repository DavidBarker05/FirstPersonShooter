#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Respawnable.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class URespawnable : public UInterface {
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API IRespawnable {
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void Respawn();
};
