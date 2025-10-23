#include "Weapons/BaseWeapon.h"
#include "Weapons/WeaponShootComponent.h"
#include "GameFramework/Controller.h"

ABaseWeapon::ABaseWeapon() {
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetCollisionProfileName(FName("NoCollision"));
	WeaponMesh->SetupAttachment(RootComponent);
	WeaponShootComponent = CreateDefaultSubobject<UWeaponShootComponent>(TEXT("Weapon Shoot Component"));
}

bool ABaseWeapon::Shoot(const FTransform& SpawnTransform, AController* Controller) { return WeaponShootComponent->Shoot(SpawnTransform, Controller); }

void ABaseWeapon::SetOwningActor(AActor* Actor) { if (Actor) WeaponShootComponent->OwningActor = Actor; }

UStaticMeshComponent* ABaseWeapon::GetWeaponMesh() { return WeaponMesh; }