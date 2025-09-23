#include "CharacterHealthComponent.h"

UCharacterHealthComponent::UCharacterHealthComponent() : CurrentHealth(MAX_HEALTH) { }

void UCharacterHealthComponent::BeginPlay() {
	Super::BeginPlay();
	bIsImmune = true;
	GetOwner()->GetWorldTimerManager().SetTimer(RespawnImmunityHandle, this, &UCharacterHealthComponent::EndImmunity, SpawnImmunityDuration, false);
	bIsDead = false;
}

int UCharacterHealthComponent::GetCurrentHealth() { return CurrentHealth; }

void UCharacterHealthComponent::TakeDamage(int32 Damage) {
	if (bIsImmune || bIsDead) return;
	Damage = FMath::Abs(Damage);
	CurrentHealth = FMath::Clamp(CurrentHealth - Damage, 0, MAX_HEALTH);
	if (CurrentHealth <= 0) bIsDead = true; // TODO: Death screen and respawn
}

void UCharacterHealthComponent::ReceiveHealth(int32 Health) {
	if (bIsDead) return;
	Health = FMath::Abs(Health);
	CurrentHealth = FMath::Clamp(CurrentHealth + Health, 0, MAX_HEALTH);
}

void UCharacterHealthComponent::EndImmunity() { bIsImmune = false; }