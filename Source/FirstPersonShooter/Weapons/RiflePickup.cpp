#include "Weapons/RiflePickup.h"
#include "Components/BoxComponent.h"
#include "FirstPersonCharacter.h"
#include "Weapons/WeaponHolderComponent.h"
#include "Weapons/RiflePickupSpawner.h"
#include "Events/EventData.h"
#include "Events/EventBus.h"

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

void ARiflePickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { OnPickup_Implementation(OtherActor); }

void ARiflePickup::OnPickup_Implementation(AActor* CollidedActor) {
	if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(CollidedActor)) {
		FirstPersonCharacter->GetWeaponHolderComponent()->PickUpRifle();
		Respawn_Implementation();
	}
}

void ARiflePickup::Respawn_Implementation() {
	if (UEventBus* EventBus = GetGameInstance()->GetSubsystem<UEventBus>()) {
		EventBus->Broadcast(FName("RespawnEvent"), { FUObjectStruct(this) });
		GetWorld()->DestroyActor(this);
	}
}
