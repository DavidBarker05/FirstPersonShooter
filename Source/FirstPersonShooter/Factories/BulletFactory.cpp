#include "Factories/BulletFactory.h"
#include "Weapons/Bullet.h"

void UBulletFactory::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	if (!GetWorld()) return;
	BulletPool.Init(nullptr, StartingPoolSize);
	AvailableBullets.Init(-1, StartingPoolSize);
	for (int i = 0; i < StartingPoolSize; ++i)
		AvailableBullets[i] = i;
}

void UBulletFactory::Deinitialize()
{
	if (GetWorld())
	{
		for (int32 i = BulletPool.Num() - 1; i > -1; --i)
		{
			if (BulletPool[i] && IsValid(BulletPool[i])) GetWorld()->DestroyActor(BulletPool[i]);
			BulletPool[i] = nullptr;
		}
	}
	BulletPool.Empty();
	AvailableBullets.Empty();
	Super::Deinitialize();
}

ABullet* UBulletFactory::CreateBullet(TSubclassOf<ABullet> BulletBlueprint, const FTransform& SpawnTransform, int32 Damage, float StartingSpeed, AActor* ActorToIgnore)
{
	if (!BulletBlueprint || !IsValid(BulletBlueprint) || !SpawnTransform.IsValid() || !ActorToIgnore || !IsValid(ActorToIgnore) || !GetWorld()) return nullptr;
	ABullet* Bullet = nullptr;
	for (int32 i = AvailableBullets.Num() - 1; i > -1; --i) // Reverse iteration because we're going to resize the array
	{
		int32 Index = AvailableBullets[i];
		if (Index > BulletPool.Num() - 1) // Out of range so we should remove this as a valid index
		{
			AvailableBullets.RemoveAt(i);
			continue;
		}
		if (!BulletPool[Index] || !IsValid(BulletPool[Index])) // BulletPool at index either doesn't exist or is scheduled for deletion so we make a new one
		{
			BulletPool[Index] = GetWorld()->SpawnActor<ABullet>(BulletBlueprint);
			Bullet = BulletPool[Index];
			break;
		}
		else // A bullet is available so we make it the bullet for whoever shot it and make it no longer available
		{
			Bullet = BulletPool[Index];
			AvailableBullets.RemoveAt(i);
			break;
		}
	}
	if (!Bullet) // No available bullets so make a new one
	{
		Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint);
		if (Bullet) BulletPool.Add(Bullet); // Add the bullet to the bullet pool if it was successfully created
		else return nullptr; // Return nullptr if it wasn't successfully created
	}
	Bullet->SetActorTransform(SpawnTransform);
	Bullet->SetDamage(Damage);
	Bullet->SetInitialSpeed(StartingSpeed);
	Bullet->SetActorToIgnore(ActorToIgnore);
	Bullet->ActivateBullet();
	return Bullet;
}

void UBulletFactory::DeactivateBullet(ABullet* Bullet)
{
	if (!Bullet || !IsValid(Bullet)) return;
	int32 Index =  BulletPool.AddUnique(Bullet);
	AvailableBullets.AddUnique(Index);
}
