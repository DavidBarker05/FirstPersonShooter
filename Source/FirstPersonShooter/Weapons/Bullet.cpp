#include "Weapons/Bullet.h"

#include "Events/EventBus.h"
#include "Factories/BulletFactory.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABullet::ABullet()
{
    PrimaryActorTick.bCanEverTick = true;
    BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
    BulletMesh->SetCollisionProfileName(FName("NoCollision"));
    SetRootComponent(BulletMesh);
    ProjectileMovementComponent =
        CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
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
        BROADCAST_EVENT(TEXT("BulletHitEvent"), OutHit.GetActor(), Damage, ActorToIgnore, OutHit.Location,
                        OutHit.ImpactNormal);
    }
    LastPosition = GetActorLocation();
}

void ABullet::ActivateBullet(const int32 InDamage, const float Speed, AActor* InActorToIgnore)
{
    Damage = InDamage;
    SetInitialSpeed(Speed);
    ActorToIgnore = InActorToIgnore;
    bIsActive = true;
    if (BulletMesh) BulletMesh->SetVisibility(true);
    ProjectileMovementComponent->Activate(true);
    LastPosition = GetActorLocation();
}

bool ABullet::CheckForHit(FHitResult& OutHit)
{
    return UKismetSystemLibrary::LineTraceSingle(this, LastPosition, GetActorLocation(), TraceTypeQuery1, false,
                                                 {ActorToIgnore}, EDrawDebugTrace::None, OutHit, true);
}

void ABullet::DeactivateBullet()
{
    bIsActive = false;
    if (BulletMesh) BulletMesh->SetVisibility(false);
    SetInitialSpeed(0.0f);
    SetActorLocation(FVector(0.0f, 0.0f, 0.0f));
    if (BULLET_FACTORY_EXISTS) DEACTIVATE_BULLET(this);
}

void ABullet::SetInitialSpeed(const float Speed) const
{
    ProjectileMovementComponent->InitialSpeed = Speed;
    ProjectileMovementComponent->MaxSpeed = Speed;
    ProjectileMovementComponent->Velocity = GetActorForwardVector() * Speed;
}
