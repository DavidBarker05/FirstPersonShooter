#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponHolderComponent.generated.h"

UCLASS( ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONSHOOTER_API UWeaponHolderComponent : public UActorComponent {
	GENERATED_BODY()

	class USkeletalMeshComponent* OwnerMesh;
	class USkeletalMeshComponent* OwnerFirstPersonMesh;
	class ABaseWeapon* CurrentWeapon;
	class APistolWeapon* Pistol;
	class APistolWeapon* PistolFirstPerson;
	class ARifleWeapon* Rifle;
	class ARifleWeapon* RifleFirstPerson;
	bool bHasRifle = false;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class APistolWeapon> PistolBlueprint;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ARifleWeapon> RifleBlueprint;

		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		bool bIsHoldingRifle = false;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (ClampMin = 0.0f, Units = "deg", AllowPrivateAccess = "true"))
		float MovementBulletSpread = 3.0f;

	public:
		UWeaponHolderComponent();

	protected:
		virtual void BeginPlay() override;

	public:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void Shoot(const FTransform& SpawnTransform);

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void PickUpRifle();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void EquipPistol();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void EquipRifle();

	private:
		void CreateWeapons();
		void CreateWeapon(FActorSpawnParameters& SpawnParams, FAttachmentTransformRules& AttachRules, TSubclassOf<class ABaseWeapon> WeaponBlueprint, class ABaseWeapon* Weapon, bool bIsFirstPerson);
		void SwitchWeapon();
};
