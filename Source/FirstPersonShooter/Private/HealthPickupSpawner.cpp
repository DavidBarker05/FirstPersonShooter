#include "HealthPickupSpawner.h"
#include "HealthPickup.h"

AHealthPickupSpawner::AHealthPickupSpawner() {
	SpawnerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Base"));
	SetRootComponent(SpawnerBase);
	SpawnerBase->SetCollisionProfileName(FName("NoCollision"));
	SpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Transform"));
	SpawnTransform->SetupAttachment(RootComponent);
}

void AHealthPickupSpawner::BeginPlay() {
	Super::BeginPlay();
	SUBSCRIBE_TO_EVENTS();
	Spawn_Implementation(HealthPickupBlueprint);
}

void AHealthPickupSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	UNSUBSCRIBE_FROM_EVENTS();
}

void AHealthPickupSpawner::SpawnNewPickupAfterDelay() {
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), HealthPickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void AHealthPickupSpawner::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params) {
	if (EventName.IsEqual("RespawnEvent") && Params.Num() == 1) {
		if (!ActivePickup) return;
		if (AActor* Pickup = Params[0].Get<FUObjectStruct>()->CastAs<AActor>()) {
			if (ActivePickup != Pickup) return;
			SpawnNewPickupAfterDelay();
			ActivePickup = nullptr;
		}
	}
}

void AHealthPickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) {
	if (!ActorToSpawn || ActivePickup) return;
	if (!ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* Pickup = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform->GetComponentTransform(), SpawnParams);
	if (Pickup) ActivePickup = Pickup;
}

