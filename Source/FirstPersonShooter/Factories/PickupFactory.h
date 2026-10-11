#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"

#include "PickupFactory.generated.h"

#ifndef CREATE_PICKUP
#define CREATE_PICKUP(Owner, SpawnTransform, PickupBlueprint) \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UPickupFactory* PickupFactory = GameInstance->GetSubsystem<UPickupFactory>()) \
                PickupFactory->CreatePickup(Owner, SpawnTransform, PickupBlueprint); \
        } \
    } while (0)
#endif

#ifndef CREATE_PICKUP_AND_ATTACH_TO_COMPONENT
#define CREATE_PICKUP_AND_ATTACH_TO_COMPONENT(Owner, SceneComponent, PickupBlueprint) \
    do \
    { \
        if (const UWorld* World = GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull); \
            const UGameInstance* GameInstance = World->GetGameInstance()) \
        { \
            if (UPickupFactory* PickupFactory = GameInstance->GetSubsystem<UPickupFactory>()) \
                PickupFactory->CreatePickupAndAttachToComponent(Owner, SceneComponent, PickupBlueprint); \
        } \
    } while (0)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UPickupFactory : public UGameInstanceSubsystem
{
    GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
    AActor* CreatePickup(AActor* Owner, const FTransform& SpawnTransform, const TSubclassOf<AActor>& PickupBlueprint);

    UFUNCTION(BlueprintCallable)
    AActor* CreatePickupAndAttachToComponent(AActor* Owner, USceneComponent* SceneComponent,
                                             const TSubclassOf<AActor>& PickupBlueprint);
};
