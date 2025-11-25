#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Spawner.h"
#include "Events/EventListener.h"
#include "RiflePickupSpawner.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARiflePickupSpawner : public AActor, public ISpawner, public IEventListener
{
	GENERATED_BODY()
	
	EVENTS_TO_LISTEN_TO("RespawnEvent")

	FTimerHandle RespawnHandle;

	USceneComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* SpawnerBase;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	USceneComponent* SpawnTransform;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class ARiflePickup> RiflePickupBlueprint;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spawning", meta = (ClampMin = 1.0f, Units = "s", AllowPrivateAccess = "true"))
	float RespawnDelay = 10.0f;

public:
	ARiflePickupSpawner();

protected:
	virtual void BeginPlay() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnNewPickupAfterDelay();

	UFUNCTION(BlueprintCallable)
	void OnEventReceived_Implementation(FName EventName, const TArray<FEventData>& Params) override;

protected:
	UFUNCTION()
	void Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) override;
};
