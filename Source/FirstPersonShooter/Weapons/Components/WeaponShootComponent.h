#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "WeaponShootComponent.generated.h"

class ABullet;

UCLASS(ClassGroup = (Weapons), meta = (BlueprintSpawnableComponent))
class FIRSTPERSONSHOOTER_API UWeaponShootComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UWeaponShootComponent();

    virtual void BeginPlay() override;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType,
                               FActorComponentTickFunction* ThisTickFunction) override;

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    bool Shoot(const FTransform& SpawnTransform);

protected:
    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void ResetShot();

public:
    const TSubclassOf<ABullet>& GetBulletBlueprint() const { return BulletBlueprint; }

    float GetRecoilTime() const { return RecoilTime; }

    const APawn* GetWeaponOwner() const { return WeaponOwner; }
    APawn* GetWeaponOwner() { return WeaponOwner; }

    UWeaponShootComponent& SetWeaponOwner(APawn* InWeaponOwner)
    {
        WeaponOwner = InWeaponOwner;
        return *this;
    }

    float GetTimeBetweenShots() const { return TimeBetweenShots; }

    UWeaponShootComponent& SetTimeBetweenShots(const float InTimeBetweenShots)
    {
        TimeBetweenShots = InTimeBetweenShots;
        return *this;
    }

    int32 GetGunDamage() const { return GunDamage; }

    UWeaponShootComponent& SetGunDamage(const int32 InGunDamage)
    {
        GunDamage = InGunDamage;
        return *this;
    }

    float GetBulletSpeed() const { return BulletSpeed; }

    UWeaponShootComponent& SetBulletSpeed(const float InBulletSpeed)
    {
        BulletSpeed = InBulletSpeed;
        return *this;
    }

    float GetVerticalRecoil() const { return VerticalRecoil; }

    UWeaponShootComponent& SetVerticalRecoil(const float InVerticalRecoil)
    {
        VerticalRecoil = InVerticalRecoil;
        return *this;
    }

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    TSubclassOf<ABullet> BulletBlueprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 0.0, UIMin = 0.0, ClampMax = 1.0, UIMax = 1.0, Units = "Seconds",
                      AllowPrivateAccess = true))
    float RecoilTime = 0.1f;

private:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character", meta = (AllowPrivateAccess = true))
    APawn* WeaponOwner;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 0.01, UIMin = 0.01, ClampMax = 2.0, UIMax = 2.0, Units = "Seconds",
                      AllowPrivateAccess = true))
    float TimeBetweenShots;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 0, UIMin = 0, ClampMax = 15, UIMax = 15, AllowPrivateAccess = true))
    int32 GunDamage;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 1000.0, UIMin = 1000.0, ClampMax = 10000.0, UIMax = 10000.0, Units = "cm/s",
                      AllowPrivateAccess = true))
    float BulletSpeed;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons",
              meta = (ClampMin = 0.0, UIMin = 0.0, ClampMax = 5.0, ClampMax = 5.0, Units = "Degrees",
                      AllowPrivateAccess = true))
    float VerticalRecoil;

    float RecoilTimer;
    float PitchWhenShot;
    float RecoilPitch;
    float LastAppliedPitch;

    bool bCanShoot = true;

    FTimerHandle ShootCooldownHandle;
};
