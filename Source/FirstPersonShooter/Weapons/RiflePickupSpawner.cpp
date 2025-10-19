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
	Spawn_Implementation(RiflePickupBlueprint);
}

void ARiflePickupSpawner::SpawnNewPickupAfterDelay() {
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), RiflePickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void ARiflePickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) {
	if (!ActorToSpawn) return;
	if (!ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* SpawnedActor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform->GetComponentTransform(), SpawnParams);
	if (ARiflePickup* RiflePickup = Cast<ARiflePickup>(SpawnedActor)) RiflePickup->Spawner = this;
}