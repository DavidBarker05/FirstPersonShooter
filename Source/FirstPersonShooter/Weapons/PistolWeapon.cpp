#include "Weapons/PistolWeapon.h"
#include "Weapons/WeaponShootComponent.h"

APistolWeapon::APistolWeapon() {
	WeaponShootComponent->TimeBetweenShots = 0.25f;
	WeaponShootComponent->GunDamage = 3;
	WeaponShootComponent->BulletSpeed = 6000.0f;
	WeaponShootComponent->VerticalRecoil = 1.0f;
}