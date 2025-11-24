#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Events/EventData.h"
#include "EventBus.generated.h"

namespace Internal
{
    static UEventBus* GetEventBusFromContext(const UObject* ContextObject)
    {
        if (!ContextObject || !IsValid(ContextObject)) return nullptr;
        const UWorld* World = nullptr;
		if (const AActor* Actor = Cast<AActor>(ContextObject)) World = Actor->GetWorld();
		else if (const USceneComponent* SceneComponent = Cast<USceneComponent>(ContextObject)) World = SceneComponent->GetWorld();
        else if (const UActorComponent* Component = Cast<UActorComponent>(ContextObject))
        {
            if (AActor* Owner = Component->GetOwner()) World = Owner->GetWorld();
        }
        if (!World) return nullptr;
        if (UGameInstance* EventBus = World->GetGameInstance()) return EventBus->GetSubsystem<UEventBus>();
        return nullptr;
    }
}

#ifndef BROADCAST_EVENT
	#define BROADCAST_EVENT(EventName, ...)\
		do\
		{\
			if (UEventBus* EventBus = Internal::GetEventBusFromContext(this))\
				EventBus->Broadcast(FName(EventName), { __VA_ARGS__ });\
		} while (0)
#endif

UCLASS(BlueprintType)
class FIRSTPERSONSHOOTER_API UEventBus : public UGameInstanceSubsystem
{
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
	void Broadcast(FName EventName, const TArray<FEventData>& Params);
};
