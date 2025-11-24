#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "WeaponFactory.generated.h"

#ifndef WEAPON_FACTORY_EXISTS
	#define WEAPON_FACTORY_EXISTS UWeaponFactory* WeaponFactory = GetOwner()->GetGameInstance()->GetSubsystem<UWeaponFactory>()
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
