#include "Weapons/Bullet.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "FirstPersonCharacter.h"
#include "CharacterHealthComponent.h"
#include "Kismet/KismetSystemLibrary.h"

ABullet::ABullet() {
	PrimaryActorTick.bCanEverTick = true;
	BulletMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Bullet Mesh"));
	BulletMesh->SetCollisionProfileName(FName("NoCollision"));
	SetRootComponent(BulletMesh);
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = false;
}

void ABullet::BeginPlay() {
	Super::BeginPlay();
	LastPosition = GetActorLocation();
}

void ABullet::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	FHitResult OutHit;
	if (CheckForHit(OutHit)) {
		if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(OutHit.GetActor())) FirstPersonCharacter->GetCharacterHealthComponent()->TakeDamage(Damage);
		GetWorld()->DestroyActor(this);
	}
	LastPosition = GetActorLocation();
}

void ABullet::SetDamage(const int32 _Damage) { Damage = _Damage; }

void ABullet::SetInitialSpeed(const float Speed) {
	ProjectileMovementComponent->InitialSpeed = Speed;
	ProjectileMovementComponent->MaxSpeed = Speed;
	ProjectileMovementComponent->Velocity = GetActorForwardVector() * Speed;
	ProjectileMovementComponent->Activate(true);
}

void ABullet::SetCharacterToIgnore(ACharacter* Character) { CharacterToIgnore = Character; }

bool ABullet::CheckForHit(FHitResult& OutHit) {
	UObject* WorldContextObject = GetWorld();
	FVector Start = LastPosition;
	FVector End = GetActorLocation();
	bool bTraceComplex = false;
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add((AActor*)CharacterToIgnore);
	bool bIgnoreSelf = true;
	return UKismetSystemLibrary::LineTraceSingle(WorldContextObject, Start, End, ETraceTypeQuery::TraceTypeQuery1, bTraceComplex, ActorsToIgnore, EDrawDebugTrace::ForDuration, OutHit, bIgnoreSelf);
}