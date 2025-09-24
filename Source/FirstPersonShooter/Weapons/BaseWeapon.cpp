#include "Weapons/BaseWeapon.h"
#include "Weapons/WeaponShootComponent.h"

ABaseWeapon::ABaseWeapon() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("Weapon Shoot Component"));
}

void ABaseWeapon::Shoot(const FTransform SpawnTransform) { WeaponShootComponent->Shoot(SpawnTransform); }

void ABaseWeapon::SetOwningCharacter(ACharacter* Character) { if (Character) WeaponShootComponent->OwningCharacter = Character; }

UStaticMeshComponent* ABaseWeapon::GetWeaponMesh() { return WeaponMesh; }