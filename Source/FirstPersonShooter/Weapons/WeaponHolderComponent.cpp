#include "Weapons/WeaponHolderComponent.h"
#include "FirstPersonCharacter.h"
#include "Weapons/BaseWeapon.h"
#include "Weapons/PistolWeapon.h"
#include "Weapons/RifleWeapon.h"
#include "Factories/WeaponFactory.h"

UWeaponHolderComponent::UWeaponHolderComponent()
{
	if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(GetOwner()))
	{
		OwnerMesh = FirstPersonCharacter->GetMesh();
		OwnerFirstPersonMesh = FirstPersonCharacter->GetFirstPersonMesh();
	}
}

void UWeaponHolderComponent::BeginPlay()
{
	Super::BeginPlay();
	bHasRifle = false;
	CreateWeapons();
	CurrentWeapon = Pistol;
}

void UWeaponHolderComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	CleanupWeapons();
	Super::EndPlay(EndPlayReason);
}

bool UWeaponHolderComponent::Shoot(FTransform SpawnTransform, bool bDoBulletSpread)
{
	if (!SpawnTransform.IsValid()) return false;
	if (bDoBulletSpread)
	{
		FVector ForwardVector = SpawnTransform.GetRotation().GetForwardVector();
		float SpreadRadians = FMath::DegreesToRadians(MovementBulletSpread);
		FVector ShootDirection = FMath::VRandCone(ForwardVector, SpreadRadians);
		FRotator ShootRotation = ShootDirection.Rotation();
		SpawnTransform.SetRotation(ShootRotation.Quaternion());
	}
	return CurrentWeapon->Shoot(SpawnTransform); // SpawnTransform isn't a reference because we would need to make a copy anyways so that we don't affect the original rotation
}

void UWeaponHolderComponent::PickUpRifle()
{
	bHasRifle = true;
	if (Rifle) Rifle->AddAmmo();
}

void UWeaponHolderComponent::EquipPistol() { if (bIsHoldingRifle) SwitchWeapon(); }

void UWeaponHolderComponent::EquipRifle() { if (bHasRifle && !bIsHoldingRifle) SwitchWeapon(); }

APistolWeapon* UWeaponHolderComponent::GetPistol() { return Pistol; }

ARifleWeapon* UWeaponHolderComponent::GetRifle() { return Rifle; }

void UWeaponHolderComponent::CreateWeapons()
{
	if (WEAPON_FACTORY_EXISTS)
	{
		Pistol = Cast<APistolWeapon>(CREATE_VISIBLE_THIRD_PERSON_WEAPON(GetOwner(), OwnerMesh, PistolBlueprint));
		Rifle = Cast<ARifleWeapon>(CREATE_INVISIBLE_THIRD_PERSON_WEAPON(GetOwner(), OwnerMesh, RifleBlueprint));
		PistolFirstPerson = Cast<APistolWeapon>(CREATE_VISIBLE_FIRST_PERSON_WEAPON(GetOwner(), OwnerFirstPersonMesh, PistolBlueprint));
		RifleFirstPerson = Cast<ARifleWeapon>(CREATE_INVISIBLE_FIRST_PERSON_WEAPON(GetOwner(), OwnerFirstPersonMesh, RifleBlueprint));
	}
}

void UWeaponHolderComponent::SwitchWeapon()
{
	if (!(bHasRifle && Pistol && PistolFirstPerson && Rifle && RifleFirstPerson)) return;
	bIsHoldingRifle = !bIsHoldingRifle;
	Pistol->GetWeaponMesh()->SetVisibility(!bIsHoldingRifle);
	PistolFirstPerson->GetWeaponMesh()->SetVisibility(!bIsHoldingRifle);
	Rifle->GetWeaponMesh()->SetVisibility(bIsHoldingRifle);
	RifleFirstPerson->GetWeaponMesh()->SetVisibility(bIsHoldingRifle);
	CurrentWeapon = bIsHoldingRifle ? (ABaseWeapon*)Rifle : (ABaseWeapon*)Pistol;
}

void UWeaponHolderComponent::CleanupWeapons()
{
	if (!GetWorld()) return;
	if (Pistol && IsValid(Pistol)) GetWorld()->DestroyActor(Pistol);
	if (Rifle && IsValid(Rifle)) GetWorld()->DestroyActor(Rifle);
	if (PistolFirstPerson && IsValid(PistolFirstPerson)) GetWorld()->DestroyActor(PistolFirstPerson);
	if (RifleFirstPerson && IsValid(RifleFirstPerson)) GetWorld()->DestroyActor(RifleFirstPerson);
	Pistol = nullptr;
	Rifle = nullptr;
	PistolFirstPerson = nullptr;
	RifleFirstPerson = nullptr;
}
