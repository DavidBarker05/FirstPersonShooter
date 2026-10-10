#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "WeaponHolderComponent.generated.h"

class ABaseWeapon;
class APistolWeapon;
class ARifleWeapon;

UCLASS(ClassGroup = (Weapons), meta = (BlueprintSpawnableComponent))
class FIRSTPERSONSHOOTER_API UWeaponHolderComponent : public UActorComponent
{
    GENERATED_BODY()

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<APistolWeapon> PistolBlueprint;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    TSubclassOf<ARifleWeapon> RifleBlueprint;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
    bool bIsHoldingRifle = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons",
              meta = (ClampMin = 0.0f, Units = "deg", AllowPrivateAccess = "true"))
    float MovementBulletSpread = 3.0f;

public:
    UWeaponHolderComponent();

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    bool Shoot(FTransform SpawnTransform, bool bDoBulletSpread);

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void PickUpRifle();

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void EquipPistol();

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    void EquipRifle();

    const ABaseWeapon* GetCurrentWeapon() const { return CurrentWeapon; }
    ABaseWeapon* GetCurrentWeapon() { return CurrentWeapon; }

    const APistolWeapon* GetPistol() const { return Pistol; }
    APistolWeapon* GetPistol() { return Pistol; }

    const ARifleWeapon* GetRifle() const { return Rifle; }
    ARifleWeapon* GetRifle() { return Rifle; }

private:
    void CreateWeapons();
    void SwitchWeapon();
    void CleanupWeapons();

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    bool bHasRifle = false;

    UPROPERTY()
    USkeletalMeshComponent* OwnerMesh;
    UPROPERTY()
    USkeletalMeshComponent* OwnerFirstPersonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    ABaseWeapon* CurrentWeapon;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    APistolWeapon* Pistol;
    UPROPERTY()
    APistolWeapon* PistolFirstPerson;

    UPROPERTY(BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = true))
    ARifleWeapon* Rifle;
    UPROPERTY()
    ARifleWeapon* RifleFirstPerson;
};
