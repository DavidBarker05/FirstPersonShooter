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
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		ACharacter* OwningCharacter;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0.01f, ClampMax = 2.0f, Units = "s", AllowPrivateAccess = "true"))
		float TimeBetweenShots;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0, ClampMax = 15, AllowPrivateAccess = "true"))
		int32 GunDamage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 1000.0f, ClampMax = 5000.0f, Units = "cm/s", AllowPrivateAccess = "true"))
		float BulletSpeed;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletBlueprint;

	public:
		UWeaponShootComponent();

	public:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		virtual void Shoot(const FTransform& SpawnTransform);

	protected:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void ResetShot();
};
