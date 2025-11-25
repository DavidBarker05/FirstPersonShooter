#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "PickupFactory.generated.h"

namespace Internal
{
    static UPickupFactory* GetPickupFactoryFromContext(const UObject* contextObject)
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
        if (UGameInstance* gameInstance = world->GetGameInstance()) return gameInstance->GetSubsystem<UPickupFactory>();
        return nullptr;
    }
}

#ifndef PICKUP_FACTORY_EXISTS
    #define PICKUP_FACTORY_EXISTS UPickupFactory* PickupFactory = Internal::GetPickupFactoryFromContext(this)
#endif

#ifndef CREATE_PICKUP
    #define CREATE_PICKUP(Owner, SpawnTransform, PickupBlueprint) PickupFactory->CreatePickup(Owner, SpawnTransform, PickupBlueprint)
#endif

#ifndef CREATE_PICKUP_AND_ATTACH_TO_COMPONENT
    #define CREATE_PICKUP_AND_ATTACH_TO_COMPONENT(Owner, SceneComponent, PickupBlueprint) PickupFactory->CreatePickupAndAttachToComponent(Owner, SceneComponent, PickupBlueprint)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UPickupFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	AActor* CreatePickup(AActor* Owner, const FTransform& SpawnTransform, TSubclassOf<AActor> PickupBlueprint);

	UFUNCTION(BlueprintCallable)
	AActor* CreatePickupAndAttachToComponent(AActor* Owner, USceneComponent* SceneComponent, TSubclassOf<AActor> PickupBlueprint);
};
