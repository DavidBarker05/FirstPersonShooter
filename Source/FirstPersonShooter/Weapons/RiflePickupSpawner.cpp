#include "Weapons/RiflePickupSpawner.h"
#include "Weapons/RiflePickup.h"
#include "Events/EventBus.h"

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
	if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {
		EventBus->AddListener("RespawnEvent", this);
	}
}

void ARiflePickupSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason) {
	Super::EndPlay(EndPlayReason);
	if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {
		EventBus->RemoveListener("RespawnEvent", this);
	}
}

void ARiflePickupSpawner::SpawnNewPickupAfterDelay() {
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), RiflePickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void ARiflePickupSpawner::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params) {
	if (EventName.IsEqual("RespawnEvent")) {
		if (Params.Num() != 1 || !ActivePickup) return;
		if (AActor* Pickup = Params[0].Get<FUObjectStruct>()->CastAs<AActor>()) {
			if (ActivePickup != Pickup) return;
			SpawnNewPickupAfterDelay();
			ActivePickup = nullptr;
		}
	}
}

void ARiflePickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) {
	if (!ActorToSpawn || ActivePickup) return;
	if (!ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* Pickup = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform->GetComponentTransform(), SpawnParams);
	if (Pickup) ActivePickup = Pickup;
}