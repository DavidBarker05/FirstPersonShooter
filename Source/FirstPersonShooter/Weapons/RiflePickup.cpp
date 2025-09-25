#include "Weapons/RiflePickup.h"
#include "Components/BoxComponent.h"
#include "FirstPersonCharacter.h"
#include "Weapons/WeaponHolderComponent.h"
#include "Weapons/RiflePickupSpawner.h"

ARiflePickup::ARiflePickup() {
	TriggerCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Collider"));
	SetRootComponent(TriggerCollider);
	TriggerCollider->SetCollisionProfileName(FName("OverlapOnlyPawn"));
	TriggerCollider->SetGenerateOverlapEvents(true);
	TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, &ARiflePickup::OnComponentBeginOverlap);
	RifleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Rifle Mesh"));
	RifleMesh->SetupAttachment(RootComponent);
	RifleMesh->SetCollisionProfileName(FName("NoCollision"));
}

void ARiflePickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) {
	if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(OtherActor)) {
		FirstPersonCharacter->GetWeaponHolderComponent()->PickUpRifle();
		if (Spawner) Spawner->SpawnNewPickupAfterDelay();
		GetWorld()->DestroyActor(this);
	}
}