#include "Weapons/BaseWeapon.h"
#include "Weapons/WeaponShootComponent.h"
#include "GameFramework/Controller.h"

ABaseWeapon::ABaseWeapon() {
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("Weapon Shoot Component"));
}

bool ABaseWeapon::Shoot(const FTransform& SpawnTransform, AController* Controller) { return WeaponShootComponent->Shoot(SpawnTransform, Controller); }

void ABaseWeapon::SetOwningCharacter(ACharacter* Character) { if (Character) WeaponShootComponent->OwningCharacter = Character; }

UStaticMeshComponent* ABaseWeapon::GetWeaponMesh() { return WeaponMesh; }