#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API ABaseWeapon : public AActor {
	GENERATED_BODY()
	
	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* WeaponMesh;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
		class UWeaponShootComponent* WeaponShootComponent;

	public:
		ABaseWeapon();

	public:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		virtual void Shoot(const FTransform SpawnTransform);

		UFUNCTION(BlueprintCallable, Category = "Character")
		void SetOwningCharacter(ACharacter* Character);

		UFUNCTION(BlueprintCallable, Category = "Components")
		UStaticMeshComponent* GetWeaponMesh();
};
