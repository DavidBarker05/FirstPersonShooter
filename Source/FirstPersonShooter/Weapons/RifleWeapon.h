#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "RifleWeapon.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API ARifleWeapon : public ABaseWeapon {
	GENERATED_BODY()

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Ammunition", meta = (ClampMin = 3, ClampMax = 30, AllowPrivateAccess = "true"))
		int32 MaxAmmo = 15;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Ammunition", meta = (ClampMin = 0, ClampMax = 30, AllowPrivateAccess = "true"))
		int32 CurrentAmmo = 0;
	
	public:
		ARifleWeapon();

	public:
		virtual void Shoot(const FTransform SpawnTransform) override;

		UFUNCTION(BlueprintCallable)
		void AddAmmo(int32 Ammo);
};
