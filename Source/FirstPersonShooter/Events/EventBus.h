#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Events/EventData.h"
#include "EventBus.generated.h"

namespace Internal
{
    static UEventBus* GetEventBusFromContext(const UObject* contextObject)
    {
        if (!contextObject || !IsValid(contextObject)) return nullptr;
        const UWorld* world = nullptr;
        if (const AActor* actor = Cast<AActor>(contextObject)) world = actor->GetWorld();
        else if (const USceneComponent* sceneComponent = Cast<USceneComponent>(contextObject)) world = sceneComponent->GetWorld();
        else if (const UActorComponent* component = Cast<UActorComponent>(contextObject))
        {
            if (AActor* owner = component->GetOwner()) world = owner->GetWorld();
        }
        if (!world) return nullptr;
        if (UGameInstance* gameInstance = world->GetGameInstance()) return gameInstance->GetSubsystem<UEventBus>();
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
