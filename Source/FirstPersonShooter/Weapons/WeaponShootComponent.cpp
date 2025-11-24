#include "Weapons/WeaponShootComponent.h"
#include "GameFramework/Controller.h"
#include "Weapons/Bullet.h"


UWeaponShootComponent::UWeaponShootComponent() : TimeBetweenShots(0.01f), GunDamage(0), BulletSpeed(1000.0f), VerticalRecoil(0.0f) { PrimaryComponentTick.bCanEverTick = true; }

void UWeaponShootComponent::BeginPlay()
{
	Super::BeginPlay();
	RecoilTimer = RecoilTime;
	bCanShoot = true;
}

void UWeaponShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (RecoilTimer >= RecoilTime || !WeaponOwner) return;
	RecoilTimer += DeltaTime;
	float Alpha = FMath::Clamp(RecoilTimer / RecoilTime, 0.0f, 1.0f);
	float DesiredPitch = FMath::Lerp(PitchWhenShot, RecoilPitch, Alpha);
	float DeltaPitch = DesiredPitch - LastAppliedPitch;
	WeaponOwner->AddControllerPitchInput(-DeltaPitch);
	LastAppliedPitch = DesiredPitch;
}

bool UWeaponShootComponent::Shoot(const FTransform& SpawnTransform)
{
	if (!bCanShoot || !BulletBlueprint || !WeaponOwner) return false;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, SpawnTransform, SpawnParams);
	if (!Bullet) return false;
	Bullet->SetDamage(GunDamage);
	Bullet->SetInitialSpeed(BulletSpeed);
	Bullet->SetActorToIgnore(WeaponOwner);
	bCanShoot = false;
	GetOwner()->GetWorldTimerManager().SetTimer(ShootCooldownHandle, this, &UWeaponShootComponent::ResetShot, TimeBetweenShots, false);
	RecoilTimer = 0.0f;
	PitchWhenShot = WeaponOwner->GetController()->GetControlRotation().Pitch;
	RecoilPitch = PitchWhenShot + VerticalRecoil;
	LastAppliedPitch = PitchWhenShot;
	return true;
}

void UWeaponShootComponent::ResetShot() { bCanShoot = true; }