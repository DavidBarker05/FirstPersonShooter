#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "Bullet.generated.h"

class UProjectileMovementComponent;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABullet : public AActor
{
    GENERATED_BODY()

public:
    ABullet();

    virtual void Tick(float DeltaTime) override;

    const UStaticMeshComponent* GetBulletMesh() const { return BulletMesh; }
    UStaticMeshComponent* GetBulletMesh() { return BulletMesh; }

    const UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovementComponent; }
    UProjectileMovementComponent* GetProjectileMovement() { return ProjectileMovementComponent; }

    int32 GetDamage() const { return Damage; }

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void ActivateBullet(const int32 InDamage, const float Speed, AActor* InActorToIgnore);

private:
    bool CheckForHit(FHitResult& OutHit);

    void DeactivateBullet();

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* BulletMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UProjectileMovementComponent* ProjectileMovementComponent;

private:
    void SetInitialSpeed(const float Speed) const;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    int32 Damage;

    FVector LastPosition;

    UPROPERTY()
    AActor* ActorToIgnore;

    bool bIsActive;
};
