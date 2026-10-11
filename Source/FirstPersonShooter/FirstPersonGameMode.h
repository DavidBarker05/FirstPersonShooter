#pragma once

#include "CoreMinimal.h"

#include "Events/EventListener.h"
#include "GameFramework/GameModeBase.h"
#include "Interfaces/Spawner.h"
#include "UObject/StrongObjectPtr.h"

#include "FirstPersonGameMode.generated.h"

class AAIController;
class AFirstPersonCharacter;

UENUM(BlueprintType)
enum class EGameMatchState : uint8
{
    None,
    StartCountdownPhase,
    MatchRoundPhase,
    EndLeaderboardPhase
};

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonGameMode : public AGameModeBase,
                                                    public IEventListener,
                                                    public ISpawner
{
    GENERATED_BODY()

    EVENTS_TO_LISTEN_TO(TEXT("RespawnEvent"))

public:
    AFirstPersonGameMode();

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintCallable)
    virtual void OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params) override;

    UFUNCTION()
    virtual void Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) override;

    UFUNCTION(BlueprintCallable)
    virtual void SpawnCharacterAfterDelay(TSubclassOf<AActor> ActorToSpawn, float Delay, FTimerHandle& RespawnHandle);

    float GetOccupiedDuration() const { return OccupiedDuration; }

    const TSubclassOf<AFirstPersonCharacter>& GetPlayerBlueprint() const { return PlayerBlueprint; }

    const TArray<TSubclassOf<AFirstPersonCharacter>>& GetAIBlueprints() const { return AIBlueprints; }

    const TSubclassOf<AAIController>& GetAIControllerBlueprint() const { return AIControllerBlueprint; }

    UFUNCTION(BlueprintCallable)
    void SetCurrentMatchState(const EGameMatchState NewState);

    EGameMatchState GetCurrentMatchState() const { return CurrentMatchState; }

    float GetMatchStartDuration() const { return MatchStartDuration; }

    float GetMatchRoundDuration() const { return MatchRoundDuration; }

    float GetCountDownTimer() const { return CountdownTimer; }

    bool GetDisplayStartTimer() const { return bDisplayStartTimer; }

    bool GetDisplayRoundTimer() const { return bDisplayRoundTimer; }

    bool GetDisplayEndLeaderboard() const { return bDisplayEndLeaderboard; }

private:
    UFUNCTION()
    FTransform GetValidSpawnPoint();

    UFUNCTION()
    void MakeSpawnValid(AActor* SpawnPoint);

    void MoveToNextPhase();
    void DoStartCountdownPhase();
    void DoMatchRoundPhase();
    void DoEndLeaderboardPhase();

    void PauseAllCharacters(const FString& Reason) const;
    void ResumeAllCharacters(const FString& Reason) const;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning",
              meta = (ClampMin = 0.0, UIMin = 0.0, Units = "Seconds",
                      ToolTip = "The time until a spawn point is considered as not occupied",
                      AllowPrivateAccess = true))
    float OccupiedDuration = 2.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning|Player", meta = (AllowPrivateAccess = true))
    TSubclassOf<AFirstPersonCharacter> PlayerBlueprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning|AI",
              meta = (DisplayName = "AI Blueprints", AllowPrivateAccess = true))
    TArray<TSubclassOf<AFirstPersonCharacter>> AIBlueprints;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning|AI",
              meta = (DisplayName = "AI Controller Blueprint", AllowPrivateAccess = true))
    TSubclassOf<AAIController> AIControllerBlueprint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match",
              meta = (ToolTip = "The current state that the match is in", AllowPrivateAccess = true))
    EGameMatchState CurrentMatchState = EGameMatchState::None;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match",
              meta = (ClampMin = 0.0, UIMin = 0.0, Units = "Seconds", AllowPrivateAccess = true))
    float MatchStartDuration = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match",
              meta = (ClampMin = 0.0, UIMin = 0.0, Units = "Seconds", AllowPrivateAccess = true))
    float MatchRoundDuration = 300.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match",
              meta = (Units = "Seconds", AllowPrivateAccess = true))
    float CountdownTimer;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = true))
    bool bDisplayStartTimer = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = true))
    bool bDisplayRoundTimer = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = true))
    bool bDisplayEndLeaderboard = false;

    TMap<TSubclassOf<AFirstPersonCharacter>, FTimerHandle> RespawnHandles;

    TMap<TStrongObjectPtr<AActor>, FTimerHandle> OccupiedSpawns;
};
