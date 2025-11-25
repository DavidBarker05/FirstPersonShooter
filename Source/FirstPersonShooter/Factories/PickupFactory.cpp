#include "Factories/PickupFactory.h"
#include "Interfaces/Pickup.h"

AActor* UPickupFactory::CreatePickup(AActor* Owner, const FTransform& SpawnTransform, TSubclassOf<AActor> PickupBlueprint)
{
	if (!Owner || !IsValid(Owner) || !SpawnTransform.IsValid() || !PickupBlueprint || !PickupBlueprint->ImplementsInterface(UPickup::StaticClass()) || !GetWorld()) return nullptr;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = Owner;
	SpawnParams.Instigator = Owner->GetInstigator();
	AActor* Pickup = GetWorld()->SpawnActor<AActor>(PickupBlueprint, SpawnTransform, SpawnParams);
	return Pickup;
}

AActor* UPickupFactory::CreatePickupAndAttachToComponent(AActor* Owner, USceneComponent* SceneComponent, TSubclassOf<AActor> PickupBlueprint)
{
	AActor* Pickup = CreatePickup(Owner, SceneComponent->GetComponentTransform(), PickupBlueprint);
	if (Pickup) Pickup->AttachToComponent(SceneComponent, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	return Pickup;
}
