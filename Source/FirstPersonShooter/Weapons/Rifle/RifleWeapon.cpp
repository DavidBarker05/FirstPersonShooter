#include "Weapons/Rifle/RifleWeapon.h"

#include "Weapons/Components/WeaponShootComponent.h"

ARifleWeapon::ARifleWeapon()
{
    WeaponShootComponent->SetTimeBetweenShots(0.5f);
    WeaponShootComponent->SetGunDamage(12);
    WeaponShootComponent->SetBulletSpeed(8000.0f);
    WeaponShootComponent->SetVerticalRecoil(2.0f);
}

bool ARifleWeapon::Shoot(const FTransform& SpawnTransform)
{
    if (CurrentAmmo <= 0) return false;
    const bool DidShoot = Super::Shoot(SpawnTransform);
    if (DidShoot) --CurrentAmmo;
    return DidShoot;
}

void ARifleWeapon::AddAmmo() { CurrentAmmo = FMath::Clamp(CurrentAmmo + AmmoPickUpAmount, 0, MaxAmmo); }
