#include "Weapons/WeaponShootComponent.h"
#include "GameFramework/Controller.h"
#include "Weapons/Bullet.h"


UWeaponShootComponent::UWeaponShootComponent() : TimeBetweenShots(0.01f), GunDamage(0), BulletSpeed(1000.0f), VerticalRecoil(0.0f) { PrimaryComponentTick.bCanEverTick = true; }

void UWeaponShootComponent::BeginPlay() {
	Super::BeginPlay();
	RecoilTimer = RecoilTime;
}

void UWeaponShootComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if (RecoilTimer >= RecoilTime) return;
	RecoilTimer += DeltaTime;
	float Alpha = FMath::Clamp(RecoilTimer / RecoilTime, 0.0f, 1.0f);
	float DesiredPitch = FMath::Lerp(PitchWhenShot, RecoilPitch, Alpha);
	float DeltaPitch = DesiredPitch - LastAppliedPitch;
	if (Player) Player->AddControllerPitchInput(-DeltaPitch);
	LastAppliedPitch = DesiredPitch;
}

bool UWeaponShootComponent::Shoot(const FTransform& SpawnTransform, AController* Controller) {
	if (!bCanShoot || !BulletBlueprint) return false;
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	ABullet* Bullet = GetWorld()->SpawnActor<ABullet>(BulletBlueprint, SpawnTransform, SpawnParams);
	if (!Bullet) return false;
	Bullet->SetDamage(GunDamage);
	Bullet->SetInitialSpeed(BulletSpeed);
	Bullet->SetCharacterToIgnore(OwningCharacter);
	bCanShoot = false;
	GetOwner()->GetWorldTimerManager().SetTimer(ShootCooldownHandle, this, &UWeaponShootComponent::ResetShot, TimeBetweenShots, false);
	RecoilTimer = 0.0f;
	Player = Controller->GetPawn();
	PitchWhenShot = Controller->GetControlRotation().Pitch;
	RecoilPitch = PitchWhenShot + VerticalRecoil;
	LastAppliedPitch = PitchWhenShot;
	return true;
}

void UWeaponShootComponent::ResetShot() { bCanShoot = true; }