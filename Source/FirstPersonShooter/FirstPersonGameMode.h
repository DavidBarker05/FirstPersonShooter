#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Events/EventListener.h"
#include "Interfaces/Spawner.h"
#include "FirstPersonCharacter.h"
#include "AIController.h"
#include "FirstPersonGameMode.generated.h"

UENUM()
enum class GameMatchState : uint8
{
	None,
	StartCountdownPhase,
	MatchRoundPhase,
	EndLeaderboardPhase
};

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonGameMode : public AGameModeBase, public IEventListener, public ISpawner
{
	GENERATED_BODY()

	EVENTS_TO_LISTEN_TO("RespawnEvent")

	TMap<TSubclassOf<AFirstPersonCharacter>, FTimerHandle> RespawnHandles;

	TMap<AActor*, FTimerHandle> OccupiedSpawns;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFirstPersonCharacter> PlayerBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Spawning", meta = (AllowPrivateAccess = "true", DisplayName = "AI Blueprints"))
	TArray<TSubclassOf<AFirstPersonCharacter>> AIBlueprints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Spawning", meta = (AllowPrivateAccess = "true", DisplayName = "AI Controller Blueprint"))
	TSubclassOf<AAIController> AIControllerBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = 0.0f, Units = "s", AllowPrivateAccess = "true", ToolTip = "The time until a spawn point is considered as not occupied"))
	float OccupiedDuration = 2.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true", ToolTip = "The current state that the match is in"))
	GameMatchState CurrentMatchState = GameMatchState::None;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true", Units = "s", ClampMin = 0.0))
	float MatchStartDuration = 10.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true", Units = "s", ClampMin = 0.0))
	float MatchRoundDuration = 300.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true", Units = "s"))
	float CountdownTimer;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true"))
	bool bDisplayStartTimer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true"))
	bool bDisplayRoundTimer = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Match", meta = (AllowPrivateAccess = "true"))
	bool bDisplayEndLeaderboard = false;

public:
	AFirstPersonGameMode();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	virtual void Tick(float DeltaSeconds) override;
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SpawnCharacterAfterDelay(TSubclassOf<AActor> ActorToSpawn, float Delay, FTimerHandle& RespawnHandle);

	UFUNCTION(BlueprintCallable)
	virtual void OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params) override;

	UFUNCTION(BlueprintCallable)
	void SetCurrentMatchState(GameMatchState NewState);

	inline GameMatchState GetCurrentMatchState() const { return CurrentMatchState; }

protected:
	UFUNCTION()
	virtual void Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) override;

private:
	UFUNCTION()
	FTransform GetValidSpawnPoint();

	UFUNCTION()
	void MakeSpawnValid(AActor* SpawnPoint);

	void MoveToNextPhase();
	void DoStartCountdownPhase();
	void DoMatchRoundPhase();
	void DoEndLeaderboardPhase();

	void PauseAllCharacters(const FString& Reason);
	void ResumeAllCharacters(const FString& Reason);
};
