#include "HealthPickupSpawner.h"
#include "HealthPickup.h"
#include "Factories/PickupFactory.h"

AHealthPickupSpawner::AHealthPickupSpawner()
{
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);
	SpawnerBase = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Spawner Base"));
	SpawnerBase->SetCollisionProfileName(FName("NoCollision"));
	SpawnerBase->SetupAttachment(RootComponent);
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
	UNSUBSCRIBE_FROM_EVENTS();
	Super::EndPlay(EndPlayReason);
}

void AHealthPickupSpawner::SpawnNewPickupAfterDelay()
{
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), HealthPickupBlueprint);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}

void AHealthPickupSpawner::OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params)
{
	if (EVENT_MATCHES(TEXT("RespawnEvent"), 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(UObject*))
	{
		if (*Params[0].Get<UObject*>() == this) SpawnNewPickupAfterDelay();
	}
}

void AHealthPickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn)
{
	if (!ActorToSpawn || !ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
	if (PICKUP_FACTORY_EXISTS) CREATE_PICKUP_AND_ATTACH_TO_COMPONENT(this, SpawnTransform, ActorToSpawn);
}

