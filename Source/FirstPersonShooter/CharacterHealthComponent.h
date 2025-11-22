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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = "true"))
	bool bIsDead = false;

	public:
		static const int32 MaxHealth = 100;

	protected:
		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = 0.0f, ClampMax = 5.0f, Units = "s", AllowPrivateAccess = "true"))
		float SpawnImmunityDuration = 2.0f;

		UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning", meta = (ClampMin = 0.0f, Units = "s", AllowPrivateAccess = "true"))
		float RespawnDelay = 5.0f;

	public:
		UCharacterHealthComponent();

	protected:
		virtual void BeginPlay() override;

	public:
		UFUNCTION(BlueprintPure, Category = "Health")
		int GetCurrentHealth();

		UFUNCTION(BlueprintPure, Category = "Health")
		int GetMaxHealth();

		UFUNCTION(BlueprintCallable, Category = "Health")
		void TakeDamage(int32 Damage);

		UFUNCTION(BlueprintCallable, Category = "Health")
		void ReceiveHealth(int32 Health);

		inline float GetRespawnDelay() { return RespawnDelay; }

		inline bool IsDead() { return bIsDead; }

	private:
		void EndImmunity();
};
