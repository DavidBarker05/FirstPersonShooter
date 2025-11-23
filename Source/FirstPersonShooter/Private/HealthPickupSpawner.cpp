#include "HealthPickupSpawner.h"
#include "HealthPickup.h"

AHealthPickupSpawner::AHealthPickupSpawner()
{
	SpawnerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Base"));
	SetRootComponent(SpawnerBase);
	SpawnerBase->SetCollisionProfileName(FName("NoCollision"));
	SpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Transform"));
	SpawnTransform->SetupAttachment(RootComponent);
}

void AHealthPickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	SUBSCRIBE_TO_EVENTS();
	Spawn_Implementation(HealthPickupBlueprint);
}

void AHealthPickupSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UNSUBSCRIBE_FROM_EVENTS();
}

void AHealthPickupSpawner::SpawnNewPickupAfterDelay()
{
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), HealthPickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void AHealthPickupSpawner::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params)
{
	if (EVENT_MATCHES("RespawnEvent", 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct))
	{
		if (*Params[0].Get<FUObjectStruct>() == this) SpawnNewPickupAfterDelay();
	}
}

void AHealthPickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn)
{
	if (!ActorToSpawn || !ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	AActor* Pickup = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform->GetComponentTransform(), SpawnParams);
}

