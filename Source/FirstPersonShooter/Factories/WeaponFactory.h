#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponFactory.generated.h"

namespace Internal
{
    static UWeaponFactory* GetWeaponFactoryFromContext(const UObject* contextObject)
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
        if (UGameInstance* gameInstance = world->GetGameInstance()) return gameInstance->GetSubsystem<UWeaponFactory>();
        return nullptr;
    }
}

#ifndef WEAPON_FACTORY_EXISTS
	#define WEAPON_FACTORY_EXISTS UWeaponFactory* WeaponFactory = Internal::GetWeaponFactoryFromContext(this)
#endif

#ifndef CREATE_WEAPON
	#define CREATE_WEAPON(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson, bIsVisible) WeaponFactory->CreateWeapon(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson, bIsVisible)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UWeaponFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
	class ABaseWeapon* CreateWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson, bool bIsVisible);
};
