#include "Weapons/WeaponShootComponent.h"
#include "Weapons/Bullet.h"
#include "Weapons/BaseWeapon.h"

UWeaponShootComponent::UWeaponShootComponent() : TimeBetweenShots(0.01f), GunDamage(0), BulletSpeed(1000.0f) { }

void UWeaponShootComponent::Shoot(const FTransform SpawnTransform) {
	if (!bCanShoot) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, SpawnTransform, SpawnParams);
	if (!Bullet) return;
	Bullet->SetDamage(GunDamage);
	Bullet->SetInitialSpeed(BulletSpeed);
	Bullet->SetCharacterToIgnore(OwningCharacter);
	bCanShoot = false;
	GetOwner()->GetWorldTimerManager().SetTimer(ShootCooldownHandle, this, &UWeaponShootComponent::ResetShot, TimeBetweenShots, false);
}

void UWeaponShootComponent::ResetShot() { bCanShoot = true; }