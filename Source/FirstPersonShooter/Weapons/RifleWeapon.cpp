#include "Weapons/RifleWeapon.h"
#include "Weapons/WeaponShootComponent.h"

ARifleWeapon::ARifleWeapon()
{
	WeaponShootComponent->TimeBetweenShots = 0.5f;
	WeaponShootComponent->GunDamage = 12;
	WeaponShootComponent->BulletSpeed = 8000.0f;
	WeaponShootComponent->VerticalRecoil = 2.0f;
}

bool ARifleWeapon::Shoot(const FTransform& SpawnTransform)
{
	if (CurrentAmmo <= 0) return false;
	bool DidShoot = Super::Shoot(SpawnTransform);
	if(DidShoot) --CurrentAmmo;
	return DidShoot;
}

void ARifleWeapon::AddAmmo() { CurrentAmmo = FMath::Clamp(CurrentAmmo + AmmoPickUpAmount, 0, MaxAmmo); }