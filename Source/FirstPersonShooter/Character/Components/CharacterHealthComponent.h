#pragma once

#include "CoreMinimal.h"

#include "Components/ActorComponent.h"

#include "CharacterHealthComponent.generated.h"

UCLASS(ClassGroup = (Character), meta = (BlueprintSpawnableComponent))
class FIRSTPERSONSHOOTER_API UCharacterHealthComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UCharacterHealthComponent();

    virtual void BeginPlay() override;

    float GetSpawnImmunityDuration() const { return SpawnImmunityDuration; }

    float GetRespawnDelay() const { return RespawnDelay; }

    int GetMaxHealth() const { return MaxHealth; }

    int GetCurrentHealth() const { return CurrentHealth; }

    UFUNCTION(BlueprintCallable, Category = "Health")
    void TakeDamage(const int32 Damage);

    UFUNCTION(BlueprintCallable, Category = "Health")
    void ReceiveHealth(const int32 Health);

    bool IsDead() const { return bIsDead; }

private:
    void EndImmunity();

protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning",
              meta = (ClampMin = 0.0, UIMin = 0.0, ClampMax = 5.0, UIMax = 5.0, Units = "Seconds",
                      AllowPrivateAccess = true))
    float SpawnImmunityDuration = 2.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawning",
              meta = (ClampMin = 0.0, UIMin = 0.0, Units = "Seconds", AllowPrivateAccess = true))
    float RespawnDelay = 5.0f;

private:
    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health",
              meta = (ClampMin = 100, UIMin = 100, AllowPrivateAccess = true))
    int32 MaxHealth = 100;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = true))
    int32 CurrentHealth;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Health", meta = (AllowPrivateAccess = true))
    bool bIsDead = false;

    bool bIsImmune = false;
    FTimerHandle RespawnImmunityHandle;
};
