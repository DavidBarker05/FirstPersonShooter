#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Pickup.generated.h"

#ifndef CREATE_TRIGGER_COLLIDER
	#define CREATE_TRIGGER_COLLIDER(TriggerCollider, Type, Name, OverlapFunction)\
		do\
		{\
			TriggerCollider = CreateDefaultSubobject<Type>(TEXT(Name));\
			SetRootComponent(TriggerCollider);\
			TriggerCollider->SetCollisionProfileName(FName("OverlapOnlyPawn"));\
			TriggerCollider->SetGenerateOverlapEvents(true);\
			TriggerCollider->OnComponentBeginOverlap.AddDynamic(this, OverlapFunction);\
		} while (0)
#endif

#ifndef CREATE_MESH
	#define CREATE_MESH(Mesh, Type, Name)\
		do\
		{\
			Mesh = CreateDefaultSubobject<Type>(TEXT(Name));\
			Mesh->SetupAttachment(RootComponent);\
			Mesh->SetCollisionProfileName(FName("NoCollision"));\
		} while (0)
#endif


UINTERFACE(MinimalAPI, BlueprintType)
class UPickup : public UInterface
{
	GENERATED_BODY()
};

class FIRSTPERSONSHOOTER_API IPickup
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void OnPickup(AActor* CollidedActor);
};
