#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "PickupFactory.generated.h"

#ifndef PICKUP_FACTORY_EXISTS
#define PICKUP_FACTORY_EXISTS \
    UPickupFactory* PickupFactory = [](const UWorld* World) -> UPickupFactory* \
    { \
        if (World; const UGameInstance* GameInstance = World->GetGameInstance()) \
            return GameInstance->GetSubsystem<UPickupFactory>(); \
        return nullptr; \
    }(GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
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
	AActor* CreatePickup(AActor* Owner, const FTransform& SpawnTransform, const TSubclassOf<AActor>& PickupBlueprint);

	UFUNCTION(BlueprintCallable)
	AActor* CreatePickupAndAttachToComponent(AActor* Owner, USceneComponent* SceneComponent, const TSubclassOf<AActor>& PickupBlueprint);
};
