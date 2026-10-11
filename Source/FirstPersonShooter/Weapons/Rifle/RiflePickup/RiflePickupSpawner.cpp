#include "Weapons/Rifle/RiflePickup/RiflePickupSpawner.h"

#include "Factories/PickupFactory.h"
#include "Weapons/Rifle/RiflePickup/RiflePickup.h"

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

void ARiflePickupSpawner::OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params)
{
    if (!(EVENT_MATCHES(TEXT("RespawnEvent"), 1) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(UObject*))) return;
    if (*Params[0].Get<UObject*>() == this) SpawnNewPickupAfterDelay();
}

void ARiflePickupSpawner::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn)
{
    if (!ActorToSpawn || !ActorToSpawn->ImplementsInterface(URespawnable::StaticClass())) return;
    CREATE_PICKUP_AND_ATTACH_TO_COMPONENT(this, SpawnTransform, ActorToSpawn);
}

void ARiflePickupSpawner::SpawnNewPickupAfterDelay()
{
    FTimerDelegate RespawnDelegate;
    RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), RiflePickupBlueprint);
    GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, RespawnDelay, false);
}
