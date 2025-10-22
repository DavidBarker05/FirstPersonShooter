#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Events/EventData.h"
#include "Events/EventBus.h"
#include "EventListener.generated.h"

#ifndef EVENTS_TO_LISTEN_TO
	// Write this in the cpp file outside of any function at the top
	#define EVENTS_TO_LISTEN_TO(...)\
		static TArray<FName> EventNames;\
		static FString UnformattedNames(#__VA_ARGS__);
#endif

#ifndef SUBSCRIBE_TO_EVENTS
	// Write this in the cpp file in the BeginPlay function
	#define SUBSCRIBE_TO_EVENTS()\
		do {\
			EventNames.Empty();\
			TArray<FString> SplitNames;\
			(void)UnformattedNames.Replace(TEXT(" "), TEXT(""));\
			(void)UnformattedNames.ParseIntoArray(SplitNames, TEXT(","));\
			for (FString Name : SplitNames) {\
				(void)EventNames.Add(FName(Name));\
			}\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				for (const FName& EventName : EventNames) {\
					EventBus->AddListener(EventName, this);\
				}\
			}\
		} while (0)
#endif

#ifndef UNSUBSCRIBE_FROM_EVENTS
	// Write this in the cpp file in the EndPlay function
	#define UNSUBSCRIBE_FROM_EVENTS() \
		do {\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {\
				for (const FName& EventName : EventNames) {\
					EventBus->RemoveListener(EventName, this);\
				}\
			}\
			EventNames.Empty();\
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
