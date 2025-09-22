#include "Weapons/BaseWeapon.h"
#include "Weapons/Bullet.h"

ABaseWeapon::ABaseWeapon() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetupAttachment(RootComponent);
}

void ABaseWeapon::Shoot(const FTransform SpawnTransform) {
	if (!bCanShoot) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, SpawnTransform, SpawnParams);
	if (!Bullet) return;
	Bullet->SetDamage(GunDamage);
	Bullet->SetInitialSpeed(BulletSpeed);
	Bullet->SetCharacterToIgnore(OwningCharacter);
	bCanShoot = false;
	GetWorldTimerManager().SetTimer(ShootCooldownHandle, this, &ABaseWeapon::ResetShot, TimeBetweenShots, false);
}

void ABaseWeapon::SetOwningCharacter(ACharacter* Character) { OwningCharacter = Character; }

void ABaseWeapon::ResetShot() { bCanShoot = true; }