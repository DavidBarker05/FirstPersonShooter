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
		do\
		{\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>())\
			{\
				for (const FString& EventName : EventNames)\
					EventBus->AddListener(FName(EventName), this);\
			}\
		} while (0)
#endif

#ifndef SUBSCRIBE_TO_EVENTS_RUNTIME
	// Subscribe to new events during runtime, write this in the cpp file inside a function
	#define SUBSCRIBE_TO_EVENTS_RUNTIME(...)\
		do\
		{\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>())\
			{\
				FString TempNames[] = { __VA_ARGS__ };\
				for (const FString& Name : TempNames)\
				{\
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
		do\
		{\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>())\
			{\
				for (const FString& EventName : EventNames)\
					EventBus->RemoveListener(FName(EventName), this);\
			}\
		} while (0)
#endif

#ifndef UNSUBSCRIBE_FROM_EVENTS_RUNTIME
	// Unsubscribe from events during runtime, write this in the cpp file inside a function
	#define UNSUBSCRIBE_FROM_EVENTS_RUNTIME(...)\
		do\
		{\
			if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>())\
			{\
				FString TempNames[] = { __VA_ARGS__ };\
				for (const FString& Name : TempNames) {\
					if (!EventNames.Contains(Name)) continue;\
					(void)EventNames.Remove(Name);\
					EventBus->RemoveListener(FName(Name), this);\
				}\
			}\
		} while (0)
#endif

#ifndef EVENT_MATCHES
	#define EVENT_MATCHES(Name, NumArgs) EventName.IsEqual(Name) && Params.Num() == NumArgs
#endif

namespace Internal
{
	static bool EventParamsAreValid(const TArray<FEventData>& params)
	{
		bool isValid = true;
		for (const FEventData& param : params)
			isValid &= param.IsValid();
		return isValid;
	}

	template<typename... Types>
	static bool EventParamsAreCorrectTypes(const TArray<FEventData>& params)
	{
		if (params.Num() != sizeof...(Types)) return false; // In this case 'sizeof...' give the number of template parameters as opposed to 'sizeof' which give the number of bytes
		bool isCorrect = true;
		int32 index = 0;
		((isCorrect &= (params[index++].Get<Types>() != nullptr)), ...);
		/*
		* I think I understand how the above works, but I'm not fully sure
		* 
		* So this uses a fold expression introduced in c++17 to simplify going through all the types
		* https://en.cppreference.com/w/cpp/language/fold.html
		* 
		* The ... is used to iterate through each argument and create an expression
		* 
		* The fold expression needs an operator between the argument (LHS) and the ... (RHS)
		* In most online cases this can be done with a simple + or whatever but that won't work for this because index++ won't be evaluated
		* 
		* The comma is used so that each expanded expression for each type will be evaluated left to right, making index++ work
		* 
		* This allows us to iterate through each type and check if it is a valid get
		*/
		return isCorrect;
	}
}

#ifndef PARAMS_ARE_VALID
	#define PARAMS_ARE_VALID Internal::EventParamsAreValid(Params)
#endif

#ifndef PARAMS_ARE_CORRECT_TYPES
	#define PARAMS_ARE_CORRECT_TYPES(...) Internal::EventParamsAreCorrectTypes<__VA_ARGS__>(Params)
#endif


UINTERFACE(MinimalAPI, BlueprintType)
class UEventListener : public UInterface
{
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API IEventListener
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnEventReceived(FName EventName, const TArray<FEventData>& Params);
};
