#include "Weapons/RifleWeapon.h"
#include "Weapons/WeaponShootComponent.h"

ARifleWeapon::ARifleWeapon() {
	WeaponShootComponent->TimeBetweenShots = 0.5f;
	WeaponShootComponent->GunDamage = 12;
	WeaponShootComponent->BulletSpeed = 4000.0f;
}

void ARifleWeapon::Shoot(const FTransform& SpawnTransform) {
	if (CurrentAmmo <= 0) return;
	--CurrentAmmo;
	Super::Shoot(SpawnTransform);
}

void ARifleWeapon::AddAmmo() { CurrentAmmo = FMath::Clamp(CurrentAmmo + AmmoPickUpAmount, 0, MaxAmmo); }