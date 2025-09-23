#include "Weapons/RifleWeapon.h"
#include "Weapons/WeaponShootComponent.h"

ARifleWeapon::ARifleWeapon() {
	WeaponShootComponent->TimeBetweenShots = 0.5f;
	WeaponShootComponent->GunDamage = 12;
	WeaponShootComponent->BulletSpeed = 4000.0f;
}

void ARifleWeapon::Shoot(const FTransform SpawnTransform) {
	if (CurrentAmmo <= 0) return;
	--CurrentAmmo;
	Super::Shoot(SpawnTransform);
}

void ARifleWeapon::AddAmmo(int32 Ammo) { CurrentAmmo = FMath::Clamp(CurrentAmmo + Ammo, 0, MaxAmmo); }