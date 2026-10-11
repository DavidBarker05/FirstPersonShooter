#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"
#include "Interfaces/Pickup.h"
#include "Interfaces/Respawnable.h"

#include "RiflePickup.generated.h"

class UBoxComponent;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARiflePickup : public AActor,
                                            public IPickup,
                                            public IRespawnable
{
    GENERATED_BODY()

public:
    ARiflePickup();

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

    const UStaticMeshComponent* GetRifleMesh() const { return RifleMesh; }
    UStaticMeshComponent* GetRifleMesh() { return RifleMesh; }

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collision", meta = (AllowPrivateAccess = "true"))
    UBoxComponent* TriggerCollider;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
    UStaticMeshComponent* RifleMesh;
};
