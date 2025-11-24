#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponFactory.generated.h"

namespace Internal
{
    static UWeaponFactory* GetWeaponFactoryFromContext(const UObject* ContextObject)
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
        if (UGameInstance* WeaponFactory = World->GetGameInstance()) return WeaponFactory->GetSubsystem<UWeaponFactory>();
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
	class ABaseWeapon* CreateWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson, bool bIsVisible);
};
