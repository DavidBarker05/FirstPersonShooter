#include "FirstPersonGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"

void AFirstPersonGameMode::BeginPlay()
{
	Super::BeginPlay();
	SUBSCRIBE_TO_EVENTS();
	if (PlayerBlueprint)
	{
		RespawnHandles.FindOrAdd(PlayerBlueprint); // TimerHandle for respawning the player
		Spawn_Implementation(PlayerBlueprint);
	}
	for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
	{
		if (!AIBlueprint) continue;
		RespawnHandles.FindOrAdd(AIBlueprint); // TimerHandles for respawning each AI
		Spawn_Implementation(AIBlueprint);
	}
}

void AFirstPersonGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);
	UNSUBSCRIBE_FROM_EVENTS();
}

void AFirstPersonGameMode::SpawnCharacterAfterDelay(TSubclassOf<AActor> ActorToSpawn, float Delay, FTimerHandle& RespawnHandle)
{
	if (!ActorToSpawn) return;
	FTimerDelegate RespawnDelegate;
	RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), ActorToSpawn);
	GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, Delay, false);
}

void AFirstPersonGameMode::OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params)
{
	if (EVENT_MATCHES("RespawnEvent", 3) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct, FUObjectStruct, FFloatStruct) && OBJECTS_ARE_NOT_NULL)
	{
		if (*Params[0].Get<FUObjectStruct>() != this || !GetWorld()) return;
		if (AActor* ActorToSpawn = Params[1].Get<FUObjectStruct>()->CastAs<AActor>())
		{
			if (const FFloatStruct* SpawnDelay = Params[2].Get<FFloatStruct>())
			{
				if (PlayerBlueprint && ActorToSpawn->IsA(PlayerBlueprint))
				{
					if (!RespawnHandles.Contains(PlayerBlueprint)) return;
					SpawnCharacterAfterDelay(PlayerBlueprint, *SpawnDelay, RespawnHandles[PlayerBlueprint]);
					GetWorld()->DestroyActor(ActorToSpawn);
				}
				else
				{
					for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
					{
						if (!AIBlueprint || !ActorToSpawn->IsA(AIBlueprint) || !RespawnHandles.Contains(AIBlueprint)) continue;
						SpawnCharacterAfterDelay(AIBlueprint, *SpawnDelay, RespawnHandles[AIBlueprint]);
						if (APawn* AI = Cast<APawn>(ActorToSpawn))
						{
							if (AController* AIController = AI->GetController()) GetWorld()->DestroyActor(AIController);
						}
						GetWorld()->DestroyActor(ActorToSpawn);
						break;
					}
				}
			}
		}
	}
}

void AFirstPersonGameMode::Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn)
{
	if (!ActorToSpawn || !GetWorld()) return;
	FTransform ValidSpawn = GetValidSpawnPoint();
	if (!ValidSpawn.IsValid()) return;
	ValidSpawn.SetScale3D(FVector(1.0f, 1.0f, 1.0f));
	AActor* Actor = GetWorld()->SpawnActor<AActor>(ActorToSpawn, ValidSpawn);
	if (!Actor) return;
	if (Actor->IsA(PlayerBlueprint))
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
		{
			if (APawn* Player = Cast<APawn>(Actor)) PlayerController->Possess(Player);
		}
	}
	else
	{
		if (!AIControllerBlueprint) return;
		for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
		{
			if (!AIBlueprint || !Actor->IsA(AIBlueprint)) continue;
			AAIController* AIController = GetWorld()->SpawnActor<AAIController>(AIControllerBlueprint, ValidSpawn);
			if (!AIController) break;
			if (APawn* AI = Cast<APawn>(ActorToSpawn)) AIController->Possess(AI);
			break;
		}
	}
}

FTransform AFirstPersonGameMode::GetValidSpawnPoint()
{
	UObject* WorldContextObject = GetWorld();
	if (!WorldContextObject) return FTransform();
	TArray<AActor*> SpawnPoints { };
	UGameplayStatics::GetAllActorsOfClass(WorldContextObject, APlayerStart::StaticClass(), SpawnPoints);
	if (SpawnPoints.IsEmpty()) return FTransform();
	AActor* PlayerStart;
	do
	{
		int Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
		PlayerStart = SpawnPoints[Index];
		SpawnPoints.RemoveAtSwap(Index);
	} while (OccupiedSpawns.Contains(PlayerStart) && SpawnPoints.Num() > 0); // 'SpawnPoints.Num() > 0' means that if there are no valid spawn points we just go with the last one we checked
	if (!PlayerStart) return FTransform();
	FTimerHandle& Handle = OccupiedSpawns.FindOrAdd(PlayerStart);
	FTimerDelegate SpawnValidDelegate;
	SpawnValidDelegate.BindUFunction(this, FName("MakeSpawnValid"), PlayerStart);
	GetWorldTimerManager().SetTimer(Handle, SpawnValidDelegate, OccupiedDuration, false);
	return PlayerStart->GetTransform();
}

void AFirstPersonGameMode::MakeSpawnValid(AActor* SpawnPoint) { if (SpawnPoint) OccupiedSpawns.Remove(SpawnPoint); }
