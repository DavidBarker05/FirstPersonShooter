#include "Weapons/RiflePickup.h"
#include "Components/BoxComponent.h"
#include "Events/EventBus.h"
#include "GameFramework/Character.h"

ARiflePickup::ARiflePickup()
{
	CREATE_TRIGGER_COLLIDER(TriggerCollider, UBoxComponent, "Trigger Collider", &ARiflePickup::OnComponentBeginOverlap);
	CREATE_MESH(RifleMesh, UStaticMeshComponent, "Rifle Mesh");
}

void ARiflePickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { OnPickup_Implementation(OtherActor); }

void ARiflePickup::OnPickup_Implementation(AActor* CollidedActor)
{
	if (IsValid(CollidedActor) && CollidedActor->IsA<ACharacter>())
	{
		BROADCAST_EVENT(TEXT("RiflePickupEvent"), CollidedActor);
		Respawn_Implementation();
	}
}

void ARiflePickup::Respawn_Implementation()
{
	BROADCAST_EVENT(TEXT("RespawnEvent"), GetOwner());
	GetWorld()->DestroyActor(this);
}
