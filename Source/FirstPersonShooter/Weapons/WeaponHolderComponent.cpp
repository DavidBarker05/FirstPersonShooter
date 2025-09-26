#include "Weapons/WeaponHolderComponent.h"
#include "FirstPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Weapons/PistolWeapon.h"
#include "Weapons/RifleWeapon.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"

UWeaponHolderComponent::UWeaponHolderComponent() {
	if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(GetOwner())) {
		OwnerMesh = FirstPersonCharacter->GetMesh();
		OwnerFirstPersonMesh = FirstPersonCharacter->GetFirstPersonMesh();
	}
}

void UWeaponHolderComponent::BeginPlay() {
	Super::BeginPlay();
	bHasRifle = false;
	CreateWeapons();
	CurrentWeapon = Pistol;
}

bool UWeaponHolderComponent::Shoot(const FTransform& SpawnTransform, AController* Controller) {
	if (AFirstPersonCharacter* FirstPersonCharacter = Cast<AFirstPersonCharacter>(GetOwner())) {
		UCharacterMovementComponent* CharacterMovement = FirstPersonCharacter->GetCharacterMovement();
		if (CharacterMovement->MaxWalkSpeed > FirstPersonCharacter->GetFastestWalkSpeed() || CharacterMovement->IsFalling()) return false;
		FTransform BulletSpawnTransform(SpawnTransform);
		if (CharacterMovement->Velocity.SizeSquared2D() > 1.0f) {
			FVector ForwardVector = BulletSpawnTransform.GetRotation().GetForwardVector();
			float SpreadRadians = FMath::DegreesToRadians(MovementBulletSpread);
			FVector ShootDirection = FMath::VRandCone(ForwardVector, SpreadRadians);
			FRotator ShootRotation = ShootDirection.Rotation();
			BulletSpawnTransform.SetRotation(ShootRotation.Quaternion());
		}
		return CurrentWeapon->Shoot(BulletSpawnTransform, Controller);
	}
	return false;
}

void UWeaponHolderComponent::PickUpRifle() {
	bHasRifle = true;
	if (Rifle) Rifle->AddAmmo();
}

void UWeaponHolderComponent::EquipPistol() { if (bIsHoldingRifle) SwitchWeapon(); }

void UWeaponHolderComponent::EquipRifle() { if (bHasRifle && !bIsHoldingRifle) SwitchWeapon(); }

APistolWeapon* UWeaponHolderComponent::GetPistol() { return Pistol; }

ARifleWeapon* UWeaponHolderComponent::GetRifle() { return Rifle; }

void UWeaponHolderComponent::CreateWeapons() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
	EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
	EAttachmentRule ScaleRule = EAttachmentRule::SnapToTarget;
	FAttachmentTransformRules AttachRules(LocationRule, RotationRule, ScaleRule, false);
	Pistol = Cast<APistolWeapon>(CreateWeapon(SpawnParams, AttachRules, PistolBlueprint, false));
	Rifle = Cast<ARifleWeapon>(CreateWeapon(SpawnParams, AttachRules, RifleBlueprint, false));
	if(Rifle) Rifle->GetWeaponMesh()->SetVisibility(false);
	PistolFirstPerson = Cast<APistolWeapon>(CreateWeapon(SpawnParams, AttachRules, PistolBlueprint, true));
	RifleFirstPerson = Cast<ARifleWeapon>(CreateWeapon(SpawnParams, AttachRules, RifleBlueprint, true));
	if(RifleFirstPerson) RifleFirstPerson->GetWeaponMesh()->SetVisibility(false);
}

ABaseWeapon* UWeaponHolderComponent::CreateWeapon(FActorSpawnParameters& SpawnParams, FAttachmentTransformRules& AttachRules, TSubclassOf<class ABaseWeapon> WeaponBlueprint, bool bIsFirstPerson) {
	USkeletalMeshComponent* AttachMesh = bIsFirstPerson ? OwnerFirstPersonMesh : OwnerMesh;
	if (!AttachMesh || !WeaponBlueprint) return nullptr;
	ABaseWeapon* Weapon = GetOwner()->GetWorld()->SpawnActor<ABaseWeapon>(WeaponBlueprint, SpawnParams);
	Weapon->AttachToComponent(AttachMesh, AttachRules, FName("WeaponSocket"));
	Weapon->GetWeaponMesh()->FirstPersonPrimitiveType = bIsFirstPerson ? EFirstPersonPrimitiveType::FirstPerson : EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	bIsFirstPerson ? Weapon->GetWeaponMesh()->SetOnlyOwnerSee(true) : Weapon->GetWeaponMesh()->SetOwnerNoSee(true);
	if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner())) Weapon->SetOwningCharacter(OwningCharacter);
	return Weapon;
}

void UWeaponHolderComponent::SwitchWeapon() {
	if (!(bHasRifle && Pistol && PistolFirstPerson && Rifle && RifleFirstPerson)) return;
	bIsHoldingRifle = !bIsHoldingRifle;
	Pistol->GetWeaponMesh()->SetVisibility(!bIsHoldingRifle);
	PistolFirstPerson->GetWeaponMesh()->SetVisibility(!bIsHoldingRifle);
	Rifle->GetWeaponMesh()->SetVisibility(bIsHoldingRifle);
	RifleFirstPerson->GetWeaponMesh()->SetVisibility(bIsHoldingRifle);
	CurrentWeapon = bIsHoldingRifle ? (ABaseWeapon*)Rifle : (ABaseWeapon*)Pistol;
}