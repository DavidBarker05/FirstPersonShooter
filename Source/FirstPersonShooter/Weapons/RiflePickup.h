#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RiflePickup.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARiflePickup : public AActor {
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

	private:
		void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
