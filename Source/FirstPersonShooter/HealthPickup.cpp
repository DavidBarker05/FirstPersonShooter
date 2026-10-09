#include "HealthPickup.h"
#include "Components/BoxComponent.h"
#include "Events/EventBus.h"
#include "GameFramework/Character.h"

AHealthPickup::AHealthPickup()
{
	CREATE_TRIGGER_COLLIDER(TriggerCollider, UBoxComponent, "Trigger Collider", &AHealthPickup::OnComponentBeginOverlap);
	CREATE_MESH(PickupMesh, UStaticMeshComponent, "Pickup Mesh");
}

void AHealthPickup::OnComponentBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) { OnPickup_Implementation(OtherActor); }

void AHealthPickup::OnPickup_Implementation(AActor* CollidedActor)
{
	if (IsValid(CollidedActor) && CollidedActor->IsA<ACharacter>())
	{
		BROADCAST_EVENT(TEXT("HealthPickupEvent"), CollidedActor, HealAmount);
		Respawn_Implementation();
	}
}

void AHealthPickup::Respawn_Implementation()
{
	BROADCAST_EVENT(TEXT("RespawnEvent"), GetOwner());
	GetWorld()->DestroyActor(this);
}