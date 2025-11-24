#include "Weapons/BaseWeapon.h"
#include "Weapons/WeaponShootComponent.h"

ABaseWeapon::ABaseWeapon()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("Weapon Shoot Component"));
}

bool ABaseWeapon::Shoot(const FTransform& SpawnTransform) { return WeaponShootComponent->Shoot(SpawnTransform); }

void ABaseWeapon::SetWeaponOwner(APawn* WeaponOwner) { if (WeaponOwner) WeaponShootComponent->WeaponOwner = WeaponOwner; }

UStaticMeshComponent* ABaseWeapon::GetWeaponMesh() { return WeaponMesh; }