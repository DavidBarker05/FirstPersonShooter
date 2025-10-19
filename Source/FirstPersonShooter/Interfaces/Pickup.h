#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickup.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UPickup : public UInterface {
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API IPickup {
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnPickup(AActor* CollidedActor);
};
