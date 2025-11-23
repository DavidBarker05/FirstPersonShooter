#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Events/EventListener.h"
#include "Interfaces/Spawner.h"
#include "FirstPersonCharacter.h"
#include "FirstPersonGameMode.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonGameMode : public AGameModeBase, public IEventListener, public ISpawner
{
	GENERATED_BODY()

	EVENTS_TO_LISTEN_TO("RespawnEvent")

	TMap<TSubclassOf<AFirstPersonCharacter>, FTimerHandle> RespawnHandles { };

	TMap<AActor*, FTimerHandle> OccupiedSpawns { };

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Player Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AFirstPersonCharacter> PlayerBlueprint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "AI Spawning", meta = (AllowPrivateAccess = "true", DisplayName = "AI Blueprints"))
	TArray<TSubclassOf<AFirstPersonCharacter>> AIBlueprints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = 0.0f, Units = "s", AllowPrivateAccess = "true", ToolTip = "The time until a spawn point is considered as not occupied"))
	float OccupiedDuration = 2.0f;

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;
	
public:
	UFUNCTION(BlueprintCallable)
	virtual void SpawnCharacterAfterDelay(TSubclassOf<AActor> ActorToSpawn, float Delay, FTimerHandle& RespawnHandle);

	UFUNCTION(BlueprintCallable)
	virtual void OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params) override;

protected:
	UFUNCTION()
	virtual void Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) override;

private:
	UFUNCTION()
	FTransform GetValidSpawnPoint();

	void MakeSpawnValid(AActor* SpawnPoint);
};
