#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponShootComponent.generated.h"

UCLASS( ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONSHOOTER_API UWeaponShootComponent : public UActorComponent {
	GENERATED_BODY()

	bool bCanShoot = true;
	FTimerHandle ShootCooldownHandle;

	public:
		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = "true"))
		ACharacter* OwningCharacter;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletBlueprint;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 0.01f, ClampMax = 2.0f, Units = "s", AllowPrivateAccess = "true"))
		float TimeBetweenShots;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 0, ClampMax = 15, AllowPrivateAccess = "true"))
		int32 GunDamage;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Shooting", meta = (ClampMin = 1000.0f, ClampMax = 5000.0f, Units = "cm/s", AllowPrivateAccess = "true"))
		float BulletSpeed;

	public:
		UWeaponShootComponent();

	public:
		UFUNCTION(BlueprintCallable)
		virtual void Shoot(const FTransform SpawnTransform);

	protected:
		UFUNCTION(BlueprintCallable)
		void ResetShot();
};
