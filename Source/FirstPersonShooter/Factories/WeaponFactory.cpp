#include "Factories/WeaponFactory.h"

ABaseWeapon* UWeaponFactory::CreateWeapon(AActor* Owner, USkeletalMeshComponent* AttachMesh, TSubclassOf<ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson, bool bIsVisible)
{
	if (!Owner || !AttachMesh || !WeaponBlueprint || !GetWorld()) return nullptr;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();
	ABaseWeapon* Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponBlueprint, SpawnParams);
	if (!Weapon) return nullptr;
	Weapon->AttachToComponent(AttachMesh, FAttachmentTransformRules::SnapToTargetIncludingScale, FName("WeaponSocket"));
	Weapon->GetWeaponMesh()->FirstPersonPrimitiveType = bIsFirstPerson ? EFirstPersonPrimitiveType::FirstPerson : EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	bIsFirstPerson ? Weapon->GetWeaponMesh()->SetOnlyOwnerSee(true) : Weapon->GetWeaponMesh()->SetOwnerNoSee(true);
	Weapon->SetWeaponOwner(Cast<APawn>(Owner));
	Weapon->GetWeaponMesh()->SetVisibility(bIsVisible);
	return Weapon;
}
