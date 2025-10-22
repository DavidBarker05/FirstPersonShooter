#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "EventBus.generated.h"

UCLASS(BlueprintType)
class FIRSTPERSONSHOOTER_API UEventBus : public UGameInstanceSubsystem	{
	GENERATED_BODY()

	TMap<FName, TArray<TScriptInterface<class IEventListener>>> EventListeners;

	public:
		virtual void Initialize(FSubsystemCollectionBase& Collection) override;
		virtual void Deinitialize() override;

	public:
		UFUNCTION(BlueprintCallable)
		void AddListener(FName EventName, TScriptInterface<class IEventListener> Listener);

		UFUNCTION(BlueprintCallable)
		void RemoveListener(FName EventName, TScriptInterface<class IEventListener> Listener);

		UFUNCTION(BlueprintCallable)
		void Broadcast(FName EventName, const TArray<struct FEventData>& Params);
};
