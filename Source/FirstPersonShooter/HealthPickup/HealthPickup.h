#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/Pickup.h"
#include "Interfaces/Respawnable.h"

#include "HealthPickup.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AHealthPickup : public AActor,
                                             public IPickup,
                                             public IRespawnable
{
    GENERATED_BODY()

public:
    AHealthPickup();

    UFUNCTION()
    virtual void OnPickup_Implementation(AActor* CollidedActor) override;

    UFUNCTION()
    virtual void Respawn_Implementation() override;

protected:
    UFUNCTION()
    void OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                 UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep,
                                 const FHitResult& SweepResult);

public:
    const UBoxComponent* GetTriggerCollider() const { return TriggerCollider; }
    UBoxComponent* GetTriggerCollider() { return TriggerCollider; }

    const UStaticMeshComponent* GetPickupMesh() const { return PickupMesh; }
    UStaticMeshComponent* GetPickupMesh() { return PickupMesh; }

    int32 GetHealAmount() const { return HealAmount; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = true))
    UBoxComponent* TriggerCollider;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* PickupMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = true))
    int32 HealAmount = 25;
};
