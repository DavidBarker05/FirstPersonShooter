#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UWeaponShootComponent* WeaponShootComponent;

public:
	ABaseWeapon();

public:
	UFUNCTION(BlueprintCallable, Category = "Weapons")
	virtual bool Shoot(const FTransform& SpawnTransform);

	UFUNCTION(BlueprintCallable, Category = "Owner")
	void SetWeaponOwner(APawn* WeaponOwner);

	UFUNCTION(BlueprintCallable, Category = "Components")
	UStaticMeshComponent* GetWeaponMesh();
};
