#pragma once

#include "CoreMinimal.h"

#include "Engine.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "UObject/StrongObjectPtr.h"

#include "BulletFactory.generated.h"

#ifndef BULLET_FACTORY_EXISTS
#define BULLET_FACTORY_EXISTS \
    UBulletFactory* BulletFactory = [](const UWorld* World) -> UBulletFactory* \
    { \
        if (World; const UGameInstance* GameInstance = World->GetGameInstance()) \
            return GameInstance->GetSubsystem<UBulletFactory>(); \
        return nullptr; \
    }(GEngine->GetWorldFromContextObject(this, EGetWorldErrorMode::LogAndReturnNull))
#endif

#ifndef CREATE_BULLET
    #define CREATE_BULLET(BulletBlueprint, SpawnTransform, Damage, StartingSpeed, ActorToIgnore) BulletFactory->CreateBullet(BulletBlueprint, SpawnTransform, Damage, StartingSpeed, ActorToIgnore)
#endif

#ifndef DEACTIVATE_BULLET
    #define DEACTIVATE_BULLET(Bullet) BulletFactory->DeactivateBullet(Bullet)
#endif

class ABullet;

UCLASS()
class FIRSTPERSONSHOOTER_API UBulletFactory : public UGameInstanceSubsystem
{
	GENERATED_BODY()

public:
    virtual void Deinitialize() override;
	
public:
    UFUNCTION(BlueprintCallable)
    ABullet* CreateBullet(const TSubclassOf<ABullet>& BulletBlueprint, const FTransform& SpawnTransform, int32 Damage, float StartingSpeed, AActor* ActorToIgnore);

    UFUNCTION(BlueprintCallable)
    void DeactivateBullet(ABullet* Bullet);
	
	UFUNCTION(BlueprintCallable)
    void ClearPool();
	
private:
	void CreatePool(const TSubclassOf<ABullet>& BulletBlueprint);

    TSet<TStrongObjectPtr<ABullet>> AvailableBullets;
    TSet<TStrongObjectPtr<ABullet>> UnavailableBullets;

    const int32 StartingPoolSize = 10;
};
