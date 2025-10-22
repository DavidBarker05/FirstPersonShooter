#include "Weapons/RiflePickup.h"
#include "Components/BoxComponent.h"
#include "Events/EventData.h"
#include "Events/EventBus.h"
#include "GameFramework/Character.h"

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
	if (ACharacter* Character = Cast<ACharacter>(CollidedActor)) {
		BROADCAST_EVENT(RiflePickupEvent, { FUObjectStruct(CollidedActor) });
		Respawn_Implementation();
	}
}

void ARiflePickup::Respawn_Implementation() {
	BROADCAST_EVENT(RespawnEvent, { FUObjectStruct(this) });
	GetWorld()->DestroyActor(this);
}
