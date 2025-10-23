#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Events/EventData.h"
#include "Events/EventBus.h"
#include "EventListener.generated.h"

#ifndef EVENTS_TO_LISTEN_TO
	// Write this in the header file
	#define EVENTS_TO_LISTEN_TO(...) TArray<FString> EventNames = { __VA_ARGS__ };
#endif

#ifndef SUBSCRIBE_TO_EVENTS
	// Write this in the cpp file in the BeginPlay function
	#define SUBSCRIBE_TO_EVENTS()\
		do {\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				for (const FString& EventName : EventNames) {\
					EventBus->AddListener(FName(EventName), this);\
				}\
			}\
		} while (0)
#endif

#ifndef SUBSCRIBE_TO_EVENTS_RUNTIME
	// Subscribe to new events during runtime, write this in the cpp file inside a function
	#define SUBSCRIBE_TO_EVENTS_RUNTIME(...)\
		do {\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				FString TempNames[] = { __VA_ARGS__ };\
				for (const FString& Name : TempNames) {\
					if (EventNames.Contains(Name)) continue;\
					(void)EventNames.Add(Name);\
					EventBus->AddListener(FName(Name), this);\
				}\
			}\
		} while (0)
#endif


#ifndef UNSUBSCRIBE_FROM_EVENTS
	// Write this in the cpp file in the EndPlay function
	#define UNSUBSCRIBE_FROM_EVENTS() \
		do {\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				for (const FString& EventName : EventNames) {\
					EventBus->RemoveListener(FName(EventName), this);\
				}\
			}\
		} while (0)
#endif

#ifndef UNSUBSCRIBE_FROM_EVENTS_RUNTIME
	// Unsubscribe from events during runtime, write this in the cpp file inside a function
	#define UNSUBSCRIBE_FROM_EVENTS_RUNTIME(...)\
		do {\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				FString TempNames[] = { __VA_ARGS__ };\
				for (const FString& Name : TempNames) {\
					if (!EventNames.Contains(Name)) continue;\
					(void)EventNames.Remove(Name);\
					EventBus->RemoveListener(FName(Name), this);\
				}\
			}\
		} while (0)
#endif

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
