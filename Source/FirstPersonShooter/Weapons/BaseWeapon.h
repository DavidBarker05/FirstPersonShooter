#pragma once

#include "CoreMinimal.h"

#include "GameFramework/Actor.h"

#include "BaseWeapon.generated.h"

class UWeaponShootComponent;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABaseWeapon : public AActor
{
    GENERATED_BODY()

public:
    ABaseWeapon();

    UFUNCTION(BlueprintCallable, Category = "Owner")
    void SetWeaponOwner(APawn* WeaponOwner);

    UFUNCTION(BlueprintCallable, Category = "Weapons")
    virtual bool Shoot(const FTransform& SpawnTransform);

    const UStaticMeshComponent* GetWeaponMesh() const { return WeaponMesh; }
    UStaticMeshComponent* GetWeaponMesh() { return WeaponMesh; }

    const UWeaponShootComponent* GetWeaponShootComponent() const { return WeaponShootComponent; }
    UWeaponShootComponent* GetWeaponShootComponent() { return WeaponShootComponent; }

protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UStaticMeshComponent* WeaponMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UWeaponShootComponent* WeaponShootComponent;

private:
    UPROPERTY()
    USceneComponent* Root;
};
