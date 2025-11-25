#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "Weapons/BaseWeapon.h"
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

#ifndef CREATE_THIRD_PERSON_WEAPON
    #define CREATE_THIRD_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint, bIsVisible) WeaponFactory->CreateThirdPersonWeapon(Owner, AttachMesh, WeaponBlueprint, bIsVisible)
#endif

#ifndef CREATE_FIRST_PERSON_WEAPON
    #define CREATE_FIRST_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint, bIsVisible) WeaponFactory->CreateFirstPersonWeapon(Owner, AttachMesh, WeaponBlueprint, bIsVisible)
#endif

#ifndef CREATE_INVISIBLE_WEAPON
    #define CREATE_INVISIBLE_WEAPON(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson) WeaponFactory->CreateInvisibleWeapon(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson)
#endif

#ifndef CREATE_VISIBLE_WEAPON
    #define CREATE_VISIBLE_WEAPON(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson) WeaponFactory->CreateVisibleWeapon(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson)
#endif

#ifndef CREATE_INVISIBLE_THIRD_PERSON_WEAPON
    #define CREATE_INVISIBLE_THIRD_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint) WeaponFactory->CreateInvisibleThirdPersonWeapon(Owner, AttachMesh, WeaponBlueprint)
#endif

#ifndef CREATE_VISIBLE_THIRD_PERSON_WEAPON
    #define CREATE_VISIBLE_THIRD_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint) WeaponFactory->CreateVisibleThirdPersonWeapon(Owner, AttachMesh, WeaponBlueprint)
#endif

#ifndef CREATE_INVISIBLE_FIRST_PERSON_WEAPON
    #define CREATE_INVISIBLE_FIRST_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint) WeaponFactory->CreateInvisibleFirstPersonWeapon(Owner, AttachMesh, WeaponBlueprint)
#endif

#ifndef CREATE_VISIBLE_FIRST_PERSON_WEAPON
    #define CREATE_VISIBLE_FIRST_PERSON_WEAPON(Owner, AttachMesh, WeaponBlueprint) WeaponFactory->CreateVisibleFirstPersonWeapon(Owner, AttachMesh, WeaponBlueprint)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UWeaponFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    UFUNCTION(BlueprintCallable)
	ABaseWeapon* CreateWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson, bool bIsVisible);

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateThirdPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsVisible) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, false, bIsVisible); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateFirstPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsVisible) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, true, bIsVisible); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateInvisibleWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson, false); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateVisibleWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, bIsFirstPerson, true); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateInvisibleThirdPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, false, false); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateVisibleThirdPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, false, true); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateInvisibleFirstPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, true, false); }

    UFUNCTION(BlueprintCallable)
    ABaseWeapon* CreateVisibleFirstPersonWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint) { return CreateWeapon(Owner, AttachMesh, WeaponBlueprint, true, true); }
};
