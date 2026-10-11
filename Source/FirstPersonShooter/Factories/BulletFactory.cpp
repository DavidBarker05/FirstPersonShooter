#include "Factories/BulletFactory.h"
#include "Weapons/Bullet.h"

void UBulletFactory::Deinitialize()
{
    ClearPool();
    Super::Deinitialize();
}

ABullet* UBulletFactory::CreateBullet(const TSubclassOf<ABullet>& BulletBlueprint, const FTransform& SpawnTransform,
                                      int32 Damage, float StartingSpeed, AActor* ActorToIgnore)
{
    if (!IsValid(BulletBlueprint) || !SpawnTransform.IsValid() || !ActorToIgnore || !IsValid(ActorToIgnore) ||
        !GetWorld())
        return nullptr;
    if (AvailableBullets.IsEmpty() && UnavailableBullets.IsEmpty()) CreatePool(BulletBlueprint);
    FVector SpawnLocation = SpawnTransform.GetLocation();
    const FTransform SpawnLocationAndRotation(SpawnTransform.GetRotation(), SpawnLocation);
    const auto* BulletPtr = AvailableBullets.FindArbitraryElement();
    ABullet* Bullet = nullptr;
    if (BulletPtr)
    {
        Bullet = BulletPtr->Get();
        AvailableBullets.Remove(*BulletPtr);
        Bullet->SetActorTransform(SpawnLocationAndRotation, false, nullptr, ETeleportType::ResetPhysics);
    }
    else
    {
        FActorSpawnParameters SpawnParams;
        SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
        Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, SpawnLocationAndRotation, SpawnParams);
    }
    if (Bullet)
    {
        UnavailableBullets.Emplace(Bullet);
        Bullet->ActivateBullet(Damage, StartingSpeed, ActorToIgnore);
    }
    return Bullet;
}

void UBulletFactory::DeactivateBullet(ABullet* Bullet)
{
    if (!IsValid(Bullet)) return;
    const TStrongObjectPtr<ABullet> StrongBullet(Bullet);
    if (!UnavailableBullets.Contains(StrongBullet)) return;
    AvailableBullets.Add(StrongBullet);
    UnavailableBullets.Remove(StrongBullet);
}

void UBulletFactory::ClearPool()
{
    AvailableBullets.Empty();
    UnavailableBullets.Empty();
}

void UBulletFactory::CreatePool(const TSubclassOf<ABullet>& BulletBlueprint)
{
    AvailableBullets.Reserve(StartingPoolSize);
    FActorSpawnParameters SpawnParams;
    SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
    for (int32 i = 0; i < StartingPoolSize; ++i)
    {
        if (ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, FTransform::Identity, SpawnParams))
            AvailableBullets.Emplace(Bullet);
    }
    UnavailableBullets.Reserve(StartingPoolSize);
}
