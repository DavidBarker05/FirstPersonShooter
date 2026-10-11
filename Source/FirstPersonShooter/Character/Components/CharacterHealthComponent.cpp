#include "Character/Components/CharacterHealthComponent.h"

#include "Events/EventBus.h"

UCharacterHealthComponent::UCharacterHealthComponent() : CurrentHealth(MaxHealth) { }

void UCharacterHealthComponent::BeginPlay()
{
    Super::BeginPlay();
    bIsImmune = true;
    GetOwner()->GetWorldTimerManager().SetTimer(RespawnImmunityHandle, this, &UCharacterHealthComponent::EndImmunity,
                                                SpawnImmunityDuration, false);
    bIsDead = false;
}

void UCharacterHealthComponent::TakeDamage(const int32 Damage)
{
    if (bIsImmune || bIsDead || Damage <= 0) return;
    CurrentHealth = FMath::Max(CurrentHealth - Damage, 0);
    if (CurrentHealth <= 0)
    {
        bIsDead = true;
        BROADCAST_EVENT(TEXT("DeathEvent"), GetOwner());
    }
}

void UCharacterHealthComponent::ReceiveHealth(const int32 Health)
{
    if (bIsDead || Health <= 0) return;
    CurrentHealth = FMath::Min(CurrentHealth + Health, MaxHealth);
}

void UCharacterHealthComponent::EndImmunity() { bIsImmune = false; }
