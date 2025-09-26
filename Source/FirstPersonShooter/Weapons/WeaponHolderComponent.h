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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
	bool bHasRifle = false;

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class APistolWeapon> PistolBlueprint;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
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
		bool Shoot(const FTransform& SpawnTransform, class AController* Controller);

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void PickUpRifle();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void EquipPistol();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void EquipRifle();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		class APistolWeapon* GetPistol();

		UFUNCTION(BlueprintCallable, Category = "Weapons")
		class ARifleWeapon* GetRifle();

	private:
		void CreateWeapons();
		class ABaseWeapon* CreateWeapon(FActorSpawnParameters& SpawnParams, FAttachmentTransformRules& AttachRules, TSubclassOf<class ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson);
		void SwitchWeapon();
};
