#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "WeaponShootComponent.generated.h"

UCLASS( ClassGroup=(Weapons), meta=(BlueprintSpawnableComponent) )
class FIRSTPERSONSHOOTER_API UWeaponShootComponent : public UActorComponent {
	GENERATED_BODY()

	bool bCanShoot = true;
	FTimerHandle ShootCooldownHandle;
	float RecoilTimer;
	float PitchWhenShot;
	float RecoilPitch;
	float LastAppliedPitch;
	class APawn* Player;

	public:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Character", meta = (AllowPrivateAccess = "true"))
		ACharacter* OwningCharacter;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0.01f, ClampMax = 2.0f, Units = "s", AllowPrivateAccess = "true"))
		float TimeBetweenShots;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0, ClampMax = 15, AllowPrivateAccess = "true"))
		int32 GunDamage;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 1000.0f, ClampMax = 5000.0f, Units = "cm/s", AllowPrivateAccess = "true"))
		float BulletSpeed;

		UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0.0f, ClampMax = 5.0f, Units = "deg", AllowPrivateAccess = "true"))
		float VerticalRecoil;

	protected:
		UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapons", meta = (AllowPrivateAccess = "true"))
		TSubclassOf<class ABullet> BulletBlueprint;

		UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapons", meta = (ClampMin = 0.0f, ClampMax = 1.0f, Units = "s", AllowPrivateAccess = "true"))
		float RecoilTime = 0.1f;

	public:
		UWeaponShootComponent();

	protected:
		virtual void BeginPlay() override;

	public:
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	public:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		bool Shoot(const FTransform& SpawnTransform, class AController* Controller);

	protected:
		UFUNCTION(BlueprintCallable, Category = "Weapons")
		void ResetShot();
};
