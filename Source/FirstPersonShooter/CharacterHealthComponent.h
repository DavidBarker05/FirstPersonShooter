#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CharacterHealthComponent.generated.h"

UCLASS(ClassGroup = (Character), meta = (BlueprintSpawnableComponent))
class FIRSTPERSONSHOOTER_API UCharacterHealthComponent : public UActorComponent {
	GENERATED_BODY()

	int32 CurrentHealth;
	bool bIsImmune = false;
	FTimerHandle RespawnImmunityHandle;
	bool bIsDead = false;

	public:
		static const int32 MaxHealth = 100;

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = 0.0f, ClampMax = 5.0f, Units = "s", AllowPrivateAccess = "true"))
		float SpawnImmunityDuration = 2.0f;

	public:
		UCharacterHealthComponent();

	protected:
		virtual void BeginPlay() override;

	public:
		UFUNCTION(BlueprintCallable, Category = "Health")
		int GetCurrentHealth();

		UFUNCTION(BlueprintCallable, Category = "Health")
		int GetMaxHealth();

		UFUNCTION(BlueprintCallable, Category = "Health")
		void TakeDamage(int32 Damage);

		UFUNCTION(BlueprintCallable, Category = "Health")
		void ReceiveHealth(int32 Health);

	private:
		void EndImmunity();
};
