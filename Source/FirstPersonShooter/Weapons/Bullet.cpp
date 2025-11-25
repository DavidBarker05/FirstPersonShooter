#include "Weapons/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Events/EventBus.h"
#include "Factories/BulletFactory.h"

ABullet::ABullet()
{
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetCollisionProfileName(FName("NoCollision"));
	SetRootComponent(BulletMesh);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
}

void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsActive) return;
	FHitResult OutHit;
	if (CheckForHit(OutHit))
	{
		DeactivateBullet();
		BROADCAST_EVENT("BulletHitEvent", FUObjectStruct(OutHit.GetActor()), FInt32Struct(Damage), FUObjectStruct(ActorToIgnore));
	}
	LastPosition = GetActorLocation();
}

void ABullet::SetDamage(UPARAM(DisplayName = "Damage") const int32 _Damage) { Damage = _Damage; }

void ABullet::SetInitialSpeed(const float Speed)
{
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * Speed;
}

void ABullet::SetActorToIgnore(AActor* Actor) { ActorToIgnore = Actor; }

void ABullet::ActivateBullet()
{
	bIsActive = true;
	if (BulletMesh) BulletMesh->SetVisibility(true);
	ProjectileMovementComponent->Activate(true);
	LastPosition = GetActorLocation();
}

bool ABullet::CheckForHit(FHitResult& OutHit)
{
	UObject* WorldContextObject = GetWorld();
	FVector Start = LastPosition;
	FVector End = GetActorLocation();
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;
	if (ActorToIgnore) ActorsToIgnore.Add(ActorToIgnore);
	bool bIgnoreSelf = true;
	return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, ETraceTypeQuery::TraceTypeQuery1, bTraceComplex, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, bIgnoreSelf);
}

void ABullet::DeactivateBullet()
{
	bIsActive = false;
	if (BulletMesh) BulletMesh->SetVisibility(false);
	SetInitialSpeed(0.0f);
	SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
	if (BULLET_FACTORY_EXISTS) DEACTIVATE_BULLET(this);
}
