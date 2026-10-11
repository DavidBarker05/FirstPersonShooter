#include "Weapons/Pistol/PistolWeapon.h"

#include "Weapons/Components/WeaponShootComponent.h"

APistolWeapon::APistolWeapon()
{
    WeaponShootComponent->SetTimeBetweenShots(0.25f);
    WeaponShootComponent->SetGunDamage(3);
    WeaponShootComponent->SetBulletSpeed(6000.0f);
    WeaponShootComponent->SetVerticalRecoil(1.0f);
}
