#include "Weapons/PistolWeapon.h"
#include "Weapons/WeaponShootComponent.h"

APistolWeapon::APistolWeapon() {
	WeaponShootComponent->TimeBetweenShots = 0.5f;
	WeaponShootComponent->GunDamage = 3;
	WeaponShootComponent->BulletSpeed = 3000.0f;
	WeaponShootComponent->VerticalRecoil = 1.0f;
}