#include "FirstPersonGameMode.h"

#include "AIController.h"
#include "BehaviorTree/BehaviorTreeComponent.h"
#include "Character/FirstPersonCharacter.h"
#include "GameFramework/Controller.h"
#include "GameFramework/PlayerStart.h"
#include "Kismet/GameplayStatics.h"
#include "MatchLeaderboard.h"

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
    CurrentMatchState = EGameMatchState::None;
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
    if (CurrentMatchState == EGameMatchState::None || CurrentMatchState == EGameMatchState::EndLeaderboardPhase) return;
    CountdownTimer -= DeltaSeconds;
    if (CountdownTimer <= 0.0f) MoveToNextPhase();
}

void AFirstPersonGameMode::OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params)
{
    if (!(EVENT_MATCHES(TEXT("RespawnEvent"), 3) && PARAMS_ARE_VALID &&
          PARAMS_ARE_CORRECT_TYPES(AFirstPersonGameMode*, AActor*, float)))
        return;
    if (*Params[0].Get<AFirstPersonGameMode*>() != this || !GetWorld()) return;
    AActor* ActorThatDied = *Params[1].Get<AActor*>();
    if (!IsValid(ActorThatDied)) return;
    const float SpawnDelay = *Params[2].Get<float>();
    if (PlayerBlueprint && ActorThatDied->IsA(PlayerBlueprint))
    {
        if (!RespawnHandles.Contains(PlayerBlueprint)) return;
        SpawnCharacterAfterDelay(PlayerBlueprint, SpawnDelay, RespawnHandles[PlayerBlueprint]);
    }
    else
    {
        for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
        {
            if (!AIBlueprint || !ActorThatDied->IsA(AIBlueprint) || !RespawnHandles.Contains(AIBlueprint)) continue;
            SpawnCharacterAfterDelay(AIBlueprint, SpawnDelay, RespawnHandles[AIBlueprint]);
            if (const APawn* AI = Cast<APawn>(ActorThatDied))
            {
                if (AController* AIController = AI->GetController())
                {
                    AIController->UnPossess();
                    GetWorld()->DestroyActor(AIController);
                }
            }
            break;
        }
    }
    GetWorld()->DestroyActor(ActorThatDied);
}

void AFirstPersonGameMode::SpawnCharacterAfterDelay(TSubclassOf<AActor> ActorToSpawn, float Delay,
                                                    FTimerHandle& RespawnHandle)
{
    if (!ActorToSpawn) return;
    FTimerDelegate RespawnDelegate;
    RespawnDelegate.BindUFunction(this, FName("Spawn_Implementation"), ActorToSpawn);
    GetWorldTimerManager().SetTimer(RespawnHandle, RespawnDelegate, Delay, false);
}

void AFirstPersonGameMode::SetCurrentMatchState(const EGameMatchState NewState)
{
    switch (CurrentMatchState = NewState)
    {
        case EGameMatchState::None:
            break;
        case EGameMatchState::StartCountdownPhase:
            DoStartCountdownPhase();
            break;
        case EGameMatchState::MatchRoundPhase:
            DoMatchRoundPhase();
            break;
        case EGameMatchState::EndLeaderboardPhase:
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
    AFirstPersonCharacter* Character = Cast<AFirstPersonCharacter>(Actor);
    if (!Character) return;
    AController* Controller = nullptr;
    if (Character->IsA(PlayerBlueprint)) Controller = UGameplayStatics::GetPlayerController(GetWorld(), 0);
    else
    {
        for (const TSubclassOf<AFirstPersonCharacter>& AIBlueprint : AIBlueprints)
        {
            if (!AIBlueprint || !Character->IsA(AIBlueprint)) continue;
            Controller = GetWorld()->SpawnActor<AAIController>(AIControllerBlueprint, ValidSpawn);
            break;
        }
    }
    if (!IsValid(Controller)) return;
    ADD_CHARACTER_TO_LEADERBOARD(Character->GetLeaderboardName());
    Controller->Possess(Character);
    if (CurrentMatchState == EGameMatchState::MatchRoundPhase && Controller->IsA<APlayerController>())
        BROADCAST_EVENT(TEXT("DisplayPlayerScreenEvent"), Controller);
}

FTransform AFirstPersonGameMode::GetValidSpawnPoint()
{
    if (!GetWorld()) return FTransform();
    TArray<AActor*> SpawnPoints;
    UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), SpawnPoints);
    if (SpawnPoints.IsEmpty()) return FTransform();
    TStrongObjectPtr<AActor> PlayerStart;
    do
    {
        const int32 Index = FMath::RandRange(0, SpawnPoints.Num() - 1);
        PlayerStart.Reset(SpawnPoints[Index]);
        SpawnPoints.RemoveAtSwap(Index);
    } while (OccupiedSpawns.Contains(PlayerStart) && SpawnPoints.Num() > 0);
    // ^ 'SpawnPoints.Num() > 0' means that if there are no valid spawn points we just go with the last one we checked
    if (!PlayerStart) return FTransform();
    FTimerHandle& Handle = OccupiedSpawns.FindOrAdd(PlayerStart);
    FTimerDelegate SpawnValidDelegate;
    SpawnValidDelegate.BindUFunction(this, FName("MakeSpawnValid"), PlayerStart);
    GetWorldTimerManager().SetTimer(Handle, SpawnValidDelegate, OccupiedDuration, false);
    return PlayerStart->GetTransform();
}

void AFirstPersonGameMode::MakeSpawnValid(AActor* SpawnPoint)
{
    if (!IsValid(SpawnPoint)) return;
    const TStrongObjectPtr<AActor> StrongSpawnPoint(SpawnPoint);
    OccupiedSpawns.Remove(StrongSpawnPoint);
}

void AFirstPersonGameMode::MoveToNextPhase()
{
    switch (CurrentMatchState)
    {
        case EGameMatchState::None:
            SetCurrentMatchState(EGameMatchState::StartCountdownPhase);
            break;
        case EGameMatchState::StartCountdownPhase:
            SetCurrentMatchState(EGameMatchState::MatchRoundPhase);
            break;
        case EGameMatchState::MatchRoundPhase:
            SetCurrentMatchState(EGameMatchState::EndLeaderboardPhase);
            break;
        case EGameMatchState::EndLeaderboardPhase:
            SetCurrentMatchState(EGameMatchState::None);
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
    BROADCAST_EVENT(TEXT("DisplayStartCountdownEvent"));
}

void AFirstPersonGameMode::DoMatchRoundPhase()
{
    bDisplayStartTimer = false;
    bDisplayRoundTimer = true;
    bDisplayEndLeaderboard = false;
    CountdownTimer = MatchRoundDuration;
    ResumeAllCharacters(TEXT("Match Phase Started"));
    BROADCAST_EVENT(TEXT("DisplayPlayerScreenEvent"), UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void AFirstPersonGameMode::DoEndLeaderboardPhase()
{
    bDisplayStartTimer = false;
    bDisplayRoundTimer = false;
    bDisplayEndLeaderboard = true;
    PauseAllCharacters(TEXT("End Leaderboard Phase Started"));
    BROADCAST_EVENT(TEXT("DisplayEndLeaderboardEvent"));
}

void AFirstPersonGameMode::PauseAllCharacters(const FString& Reason) const
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
        if (const AAIController* AIController = Cast<AAIController>(Actor))
        {
            if (UBehaviorTreeComponent* BehaviorTreeComponent =
                    Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent()))
            {
                if (!BehaviorTreeComponent->IsPaused()) BehaviorTreeComponent->PauseLogic(Reason);
            }
        }
    }
}

void AFirstPersonGameMode::ResumeAllCharacters(const FString& Reason) const
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
        if (const AAIController* AIController = Cast<AAIController>(Actor))
        {
            if (UBehaviorTreeComponent* BehaviorTreeComponent =
                    Cast<UBehaviorTreeComponent>(AIController->GetBrainComponent()))
            {
                if (BehaviorTreeComponent->IsPaused()) BehaviorTreeComponent->ResumeLogic(Reason);
            }
        }
    }
}
