#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABaseWeapon : public AActor {
	GENERATED_BODY()

	FTimerHandle ShootCooldownHandle;
	ACharacter* OwningCharacter;
	
	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletBlueprint;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 0.01f, ClampMax = 2.0f, Units = "s", AllowPrivateAccess = "true"))
		float TimeBetweenShots;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 3, ClampMax = 12, AllowPrivateAccess = "true"))
		int32 GunDamage;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 1000.0f, ClampMax = 5000.0f, Units = "cm/s", AllowPrivateAccess = "true"))
		float BulletSpeed;

		bool bCanShoot = true;

	public:
		ABaseWeapon();

	public:
		UFUNCTION(BlueprintCallable)
		virtual void Shoot(const FTransform SpawnTransform);

		UFUNCTION(BlueprintCallable)
		void SetOwningCharacter(ACharacter* Character);

	protected:
		UFUNCTION(BlueprintCallable)
		void ResetShot();
};
