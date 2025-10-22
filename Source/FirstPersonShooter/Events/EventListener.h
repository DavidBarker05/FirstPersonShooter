#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Events/EventData.h"
#include "EventListener.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UEventListener : public UInterface {
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API IEventListener {
	GENERATED_BODY()

	public:
		UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void OnEventReceived(FName EventName, const TArray<FEventData>& Params);
};
