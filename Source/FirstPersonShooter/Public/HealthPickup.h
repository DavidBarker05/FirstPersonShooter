#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interfaces/Pickup.h"
#include "Interfaces/Respawnable.h"
#include "HealthPickup.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AHealthPickup : public AActor, public IPickup, public IRespawnable {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
	class UBoxComponent* TriggerCollider;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* PickupMesh;

	public:
		static const int32 HealAmount = 25;
	
	public:
		AHealthPickup();

	protected:
		UFUNCTION()
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

		UFUNCTION()
		void OnPickup_Implementation(AActor* CollidedActor) override;

		UFUNCTION()
		void Respawn_Implementation() override;
};
