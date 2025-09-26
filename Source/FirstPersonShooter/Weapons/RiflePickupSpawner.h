#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RiflePickupSpawner.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARiflePickupSpawner : public AActor {
	GENERATED_BODY()

	FTimerHandle RespawnHandle;
	
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

	private:
		void SpawnPickup();

	public:
		UFUNCTION(BlueprintCallable)
		void SpawnNewPickupAfterDelay();
};
