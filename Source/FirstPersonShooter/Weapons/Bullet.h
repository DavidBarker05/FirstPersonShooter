#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABullet : public AActor
{
	GENERATED_BODY()

	int32 Damage;
	FVector LastPosition;
	AActor* ActorToIgnore;
	bool bIsActive;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BulletMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UProjectileMovementComponent* ProjectileMovementComponent;
	
public:	
	ABullet();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetDamage(UPARAM(DisplayName = "Damage") const int32 _Damage);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetInitialSpeed(const float Speed);

	UFUNCTION(BlueprintCallable, Category = "Weapons")
	void SetActorToIgnore(AActor* Actor);

	UFUNCTION()
	void ActivateBullet();

private:
	bool CheckForHit(FHitResult& OutHit);
	void DeactivateBullet();
};
