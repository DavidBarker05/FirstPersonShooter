#include "Weapons/BaseWeapon.h"

#include "Weapons/Components/WeaponShootComponent.h"

ABaseWeapon::ABaseWeapon()
{
    Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
    SetRootComponent(Root);
    WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
    WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
    WeaponMesh->SetupAttachment(RootComponent);
    WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("Weapon Shoot Component"));
}

void ABaseWeapon::SetWeaponOwner(APawn* WeaponOwner)
{
    if (WeaponOwner) WeaponShootComponent->SetWeaponOwner(WeaponOwner);
}

bool ABaseWeapon::Shoot(const FTransform& SpawnTransform) { return WeaponShootComponent->Shoot(SpawnTransform); }
