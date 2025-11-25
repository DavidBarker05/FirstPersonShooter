#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "BulletFactory.generated.h"

namespace Internal
{
    static UBulletFactory* GetBulletFactoryFromContext(const UObject* contextObject)
    {
        if (!contextObject || !IsValid(contextObject)) return nullptr;
        const UWorld* world = nullptr;
        if (const AActor* actor = Cast<AActor>(contextObject)) world = actor->GetWorld();
        else if (const USceneComponent* sceneComponent = Cast<USceneComponent>(contextObject)) world = sceneComponent->GetWorld();
        else if (const UActorComponent* component = Cast<UActorComponent>(contextObject))
        {
            if (AActor* owner = component->GetOwner()) world = owner->GetWorld();
        }
        if (!world) return nullptr;
        if (UGameInstance* gameInstance = world->GetGameInstance()) return gameInstance->GetSubsystem<UBulletFactory>();
        return nullptr;
    }
}

#ifndef BULLET_FACTORY_EXISTS
    #define BULLET_FACTORY_EXISTS UBulletFactory* BulletFactory = Internal::GetBulletFactoryFromContext(this)
#endif

#ifndef CREATE_BULLET
    #define CREATE_BULLET(BulletBlueprint, SpawnTransform, Damage, StartingSpeed, ActorToIgnore) BulletFactory->CreateBullet(BulletBlueprint, SpawnTransform, Damage, StartingSpeed, ActorToIgnore)
#endif

#ifndef DEACTIVATE_BULLET
    #define DEACTIVATE_BULLET(Bullet) BulletFactory->DeactivateBullet(Bullet)
#endif

UCLASS()
class FIRSTPERSONSHOOTER_API UBulletFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

    const int32 StartingPoolSize = 10;

    TArray<class ABullet*> BulletPool;
    TArray<int32> AvailableBullets;

public:
    virtual void Initialize(FSubsystemCollectionBase& Collection) override;
    virtual void Deinitialize() override;
	
public:
    UFUNCTION(BlueprintCallable)
    class ABullet* CreateBullet(TSubclassOf<ABullet> BulletBlueprint, const FTransform& SpawnTransform, int32 Damage, float StartingSpeed, AActor* ActorToIgnore);

    UFUNCTION()
    void DeactivateBullet(class ABullet* Bullet);
};
