#include "Weapons/RiflePickupSpawner.h"
#include "Weapons/RiflePickup.h"

ARiflePickupSpawner::ARiflePickupSpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SpawnerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Base"));
	SpawnerBase->SetCollisionProfileName(FName("NoCollision"));
	SpawnerBase->SetupAttachment(RootComponent);
	SpawnTransform = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Transform"));
	SpawnTransform->SetupAttachment(RootComponent);
}

void ARiflePickupSpawner::BeginPlay()
{
	Super::BeginPlay();
	SUBSCRIBE_TO_EVENTS();
	Spawn_Implementation(RiflePickupBlueprint);
}

void ARiflePickupSpawner::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UNSUBSCRIBE_FROM_EVENTS();
	Super::EndPlay(EndPlayReason);
}

void ARiflePickupSpawner::SpawnNewPickupAfterDelay()
{
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), RiflePickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void ARiflePickupSpawner::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params)
{
	if (EVENT_MATCHES("RespawnEvent", 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct))
	{
		if (*Params[0].Get<FUObjectStruct>() == this) SpawnNewPickupAfterDelay();
	}
}

void ARiflePickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn)
{
	if (!ActorToSpawn || !ActorToSpawn->ImplementsInterface(URespawnable::StaticClass()) || !GetWorld()) return;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	AActor* Pickup = GetWorld()->SpawnActor<AActor>(ActorToSpawn, SpawnTransform->GetComponentTransform(), SpawnParams);
}