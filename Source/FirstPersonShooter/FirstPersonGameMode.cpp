#include "FirstPersonGameMode.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Controller.h"
#include "MatchLeaderboard.h"
#include "BehaviorTree/BehaviorTreeComponent.h"

AFirstPersonGameMode::AFirstPersonGameMode() { PrimaryActorTick.bCanEverTick = true; }

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
	ORDER_LEADERBOARD();
	CurrentMatchState = GameMatchState::None;
	MoveToNextPhase();
}

void AFirstPersonGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UNSUBSCRIBE_FROM_EVENTS();
	CLEAR_LEADERBOARD();
	Super::EndPlay(EndPlayReason);
}

void AFirstPersonGameMode::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (CurrentMatchState == GameMatchState::None || CurrentMatchState == GameMatchState::EndLeaderboardPhase) return;
	CountdownTimer -= DeltaSeconds;
	if (CountdownTimer <= 0.0f) MoveToNextPhase();
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
	if (EVENT_MATCHES("RespawnEvent", 3) && PARAMS_ARE_VALID && PARAMS_ARE_CORRECT_TYPES(FUObjectStruct, FUObjectStruct, FFloatStruct))
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
					GetWorldTimerManager().SetTimerForNextTick([this, ActorToDestroy = ActorToSpawn]()
					{
						if (IsValid(ActorToDestroy))
							GetWorld()->DestroyActor(ActorToDestroy);
					});
				}
				else
				{
					for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
					{
						if (!AIBlueprint || !ActorToSpawn->IsA(AIBlueprint) || !RespawnHandles.Contains(AIBlueprint)) continue;
						SpawnCharacterAfterDelay(AIBlueprint, *SpawnDelay, RespawnHandles[AIBlueprint]);
						if (APawn* AI = Cast<APawn>(ActorToSpawn))
						{
							if (AController* AIController = AI->GetController())
							{
								AIController->UnPossess();
								GetWorld()->DestroyActor(AIController);
							}
						}
						GetWorldTimerManager().SetTimerForNextTick([this, ActorToDestroy = ActorToSpawn]()
						{
							if (IsValid(ActorToDestroy))
								GetWorld()->DestroyActor(ActorToDestroy);
						});
						break;
					}
				}
			}
		}
	}
}

void AFirstPersonGameMode::SetCurrentMatchState(GameMatchState NewState)
{
	CurrentMatchState = NewState;
	switch (CurrentMatchState)
	{
		case GameMatchState::None:
			break;
		case GameMatchState::StartCountdownPhase:
			DoStartCountdownPhase();
			break;
		case GameMatchState::MatchRoundPhase:
			DoMatchRoundPhase();
			break;
		case GameMatchState::EndLeaderboardPhase:
			DoEndLeaderboardPhase();
			break;
		default:
			break;
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
		if (AFirstPersonCharacter* Player = Cast<AFirstPersonCharacter>(Actor))
		{
			ADD_CHARACTER_TO_LEADERBOARD(Player->GetLeaderboardName());
			if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0)) PlayerController->Possess(Player);
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
			if (AFirstPersonCharacter* AI = Cast<AFirstPersonCharacter>(Actor))
			{
				ADD_CHARACTER_TO_LEADERBOARD(AI->GetLeaderboardName());
				AIController->Possess(AI);
			}
			break;
		}
	}
}

FTransform AFirstPersonGameMode::GetValidSpawnPoint()
{
	if (!GetWorld()) return FTransform();
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
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

void AFirstPersonGameMode::MoveToNextPhase()
{
	switch (CurrentMatchState)
	{
		case GameMatchState::None:
			SetCurrentMatchState(GameMatchState::StartCountdownPhase);
			break;
		case GameMatchState::StartCountdownPhase:
			SetCurrentMatchState(GameMatchState::MatchRoundPhase);
			break;
		case GameMatchState::MatchRoundPhase:
			SetCurrentMatchState(GameMatchState::EndLeaderboardPhase);
			break;
		case GameMatchState::EndLeaderboardPhase:
			SetCurrentMatchState(GameMatchState::None);
			break;
		default:
			break;
	}
}

void AFirstPersonGameMode::DoStartCountdownPhase()
{
	bDisplayStartTimer = true;
	bDisplayRoundTimer = false;
	bDisplayEndLeaderboard = false;
	CountdownTimer = MatchStartDuration;
	PauseAllCharacters(TEXT("Countdown Phase Started"));
}

void AFirstPersonGameMode::DoMatchRoundPhase()
{
	bDisplayStartTimer = false;
	bDisplayRoundTimer = true;
	bDisplayEndLeaderboard = false;
	CountdownTimer = MatchRoundDuration;
	ResumeAllCharacters(TEXT("Match Phase Started"));
}

void AFirstPersonGameMode::DoEndLeaderboardPhase()
{
	bDisplayStartTimer = false;
	bDisplayRoundTimer = false;
	bDisplayEndLeaderboard = true;
	PauseAllCharacters(TEXT("End Leaderboard Phase Started"));
}

void AFirstPersonGameMode::PauseAllCharacters(const FString& Reason)
{
	if (!GetWorld()) return;
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			Player->DisableInput(PlayerController);
	}
	TArray<AActor*> AIControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIController::StaticClass(), AIControllers);
	for (AActor* Actor : AIControllers)
	{
		if (AAIController* AIController = Cast<AAIController>(Actor))
		{
			if (UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent()))
			{
				if (!BehaviorTreeComponent->IsPaused()) BehaviorTreeComponent->PauseLogic(Reason);
			}
		}
	}
}

void AFirstPersonGameMode::ResumeAllCharacters(const FString& Reason)
{
	if (!GetWorld()) return;
	if (ACharacter* Player = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0))
	{
		if (APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0))
			Player->EnableInput(PlayerController);
	}
	TArray<AActor*> AIControllers;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAIController::StaticClass(), AIControllers);
	for (AActor* Actor : AIControllers)
	{
		if (AAIController* AIController = Cast<AAIController>(Actor))
		{
			if (UBehaviorTreeComponent* BehaviorTreeComponent = Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent()))
			{
				if (BehaviorTreeComponent->IsPaused()) BehaviorTreeComponent->ResumeLogic(Reason);
			}
		}
	}
}
