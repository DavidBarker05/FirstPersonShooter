#pragma once

#include "CoreMinimal.h"

#include "Weapons/BaseWeapon.h"

#include "RifleWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ARifleWeapon : public ABaseWeapon
{
    GENERATED_BODY()

public:
    ARifleWeapon();

    virtual bool Shoot(const FTransform& SpawnTransform) override;

    UFUNCTION(BlueprintCallable)
    void AddAmmo();

    int32 GetMaxAmmo() const { return MaxAmmo; }

    int32 GetAmmoPickUpAmount() const { return AmmoPickUpAmount; }

    int32 GetCurrentAmmo() const { return CurrentAmmo; }
    ARifleWeapon& SetCurrentAmmo(int32 NewCurrentAmmo)
    {
        CurrentAmmo = FMath::Clamp(NewCurrentAmmo, 0, MaxAmmo);
        return *this;
    }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons",
              meta = (ClampMin = 3, UIMin = 3, ClampMax = 30, UIMax = 30, AllowPrivateAccess = true))
    int32 MaxAmmo = 15;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons",
              meta = (ClampMin = 0, ClampMin = 0, ClampMax = 30, UIMax = 30, AllowPrivateAccess = true))
    int32 AmmoPickUpAmount = 5;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 0, ClampMin = 0, ClampMax = 30, UIMax = 30, AllowPrivateAccess = true))
    int32 CurrentAmmo = 0;
};
