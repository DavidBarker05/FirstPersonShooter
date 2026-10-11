#pragma once

#include "CoreMinimal.h"

#include "Events/EventListener.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Spawner.h"

#include "HealthPickupSpawner.generated.h"

class AHealthPickup;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AHealthPickupSpawner : public AActor,
                                                    public ISpawner,
                                                    public IEventListener
{
    GENERATED_BODY()

    EVENTS_TO_LISTEN_TO(TEXT("RespawnEvent"))

public:
    AHealthPickupSpawner();

protected:
    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
    UFUNCTION(BlueprintCallable)
    virtual void OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params) override;

    UFUNCTION()
    virtual void Spawn_Implementation(TSubclassOf<AActor> ActorToSpawn) override;

    UFUNCTION(BlueprintCallable)
    void SpawnNewPickupAfterDelay();

    const UStaticMeshComponent* GetSpawnerBase() const { return SpawnerBase; }
    UStaticMeshComponent* GetSpawnerBase() { return SpawnerBase; }

    const USceneComponent* GetSpawnTransform() const { return SpawnTransform; }
    USceneComponent* GetSpawnTransform() { return SpawnTransform; }

    const TSubclassOf<AHealthPickup>& GetHealthPickupBlueprint() const { return HealthPickupBlueprint; }

    float GetRespawnDelay() const { return RespawnDelay; }

private:
    UPROPERTY()
    USceneComponent* Root;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* SpawnerBase;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))
    USceneComponent* SpawnTransform;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (AllowPrivateAccess = true))
    TSubclassOf<AHealthPickup> HealthPickupBlueprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning",
              meta = (ClampMin = 1.0, UIMin = 1.0, Units = "Seconds", AllowPrivateAccess = true))
    float RespawnDelay = 5.0f;

    FTimerHandle RespawnHandle;
};
