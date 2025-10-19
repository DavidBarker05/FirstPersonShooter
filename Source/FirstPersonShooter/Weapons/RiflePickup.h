#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickup.h"
#include "Interfaces/Respawnable.h"
#include "RiflePickup.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARiflePickup : public AActor, public IPickup, public IRespawnable {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* RifleMesh;

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class ARiflePickupSpawner* Spawner;
	
	public:
		ARiflePickup();

	protected:
		UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnPickup_Implementation(AActor* CollidedActor) override;

		UFUNCTION()
		void Respawn_Implementation() override;
};
