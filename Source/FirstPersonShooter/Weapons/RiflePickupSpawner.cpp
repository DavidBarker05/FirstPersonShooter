#include "Weapons/RiflePickupSpawner.h"
#include "Weapons/RiflePickup.h"

ARiflePickupSpawner::ARiflePickupSpawner() {
	SpawnerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Base"));
	SetRootComponent(SpawnerBase);
	SpawnerBase->SetCollisionProfileName(FName("NoCollision"));
	SpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Transform"));
	SpawnTransform->SetupAttachment(RootComponent);
}

void ARiflePickupSpawner::BeginPlay() {
	Super::BeginPlay();
	SpawnPickup();
}


void ARiflePickupSpawner::SpawnPickup() {
	if (!RiflePickupBlueprint) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	ARiflePickup* RiflePickup = GetWorld()->SpawnActor<ARiflePickup>(RiflePickupBlueprint, SpawnTransform->GetComponentTransform(), SpawnParams);
	if (RiflePickup) RiflePickup->Spawner = this;
}

void ARiflePickupSpawner::SpawnNewPickupAfterDelay() { GetWorldTimerManager().SetTimer(RespawnHandle, this, &ARiflePickupSpawner::SpawnPickup, RespawnDelay, false); }