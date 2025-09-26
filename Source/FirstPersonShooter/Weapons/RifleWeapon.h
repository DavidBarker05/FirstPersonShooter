#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "RifleWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARifleWeapon : public ABaseWeapon {
	GENERATED_BODY()

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (ClampMin = 3, ClampMax = 30, AllowPrivateAccess = "true"))
		int32 MaxAmmo = 15;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0, ClampMax = 30, AllowPrivateAccess = "true"))
		int32 AmmoPickUpAmount = 5;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0, ClampMax = 30, AllowPrivateAccess = "true"))
		int32 CurrentAmmo = 0;
	
	public:
		ARifleWeapon();

	public:
		virtual bool Shoot(const FTransform& SpawnTransform, class AController* Controller) override;

		UFUNCTION(BlueprintCallable)
		void AddAmmo();
};
