#include "Weapons/WeaponHolderComponent.h"
#include "FirstPersonCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Weapons/BaseWeapon.h"
#include "Weapons/PistolWeapon.h"
#include "Weapons/RifleWeapon.h"

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
	EquipPistol();
}

void UWeaponHolderComponent::Shoot(FTransform SpawnTransform) { if (CurrentWeapon) CurrentWeapon->Shoot(SpawnTransform); }

void UWeaponHolderComponent::PickUpRifle() {
	bHasRifle = true;
	if (Rifle) Rifle->AddAmmo();
}

void UWeaponHolderComponent::EquipPistol() { if (bIsHoldingRifle) SwitchWeapon(); }

void UWeaponHolderComponent::EquipRifle() { if (bHasRifle && !bIsHoldingRifle) SwitchWeapon(); }

void UWeaponHolderComponent::CreateWeapons() {
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = GetOwner();
	SpawnParams.Instigator = GetOwner()->GetInstigator();
	EAttachmentRule LocationRule = EAttachmentRule::SnapToTarget;
	EAttachmentRule RotationRule = EAttachmentRule::SnapToTarget;
	EAttachmentRule ScaleRule = EAttachmentRule::KeepWorld;
	FAttachmentTransformRules AttachRules(LocationRule, RotationRule, ScaleRule, false);
	CreateWeapon(SpawnParams, AttachRules, PistolBlueprint, Pistol, false);
	CreateWeapon(SpawnParams, AttachRules, RifleBlueprint, Rifle, false);
	if (Rifle) Rifle->GetWeaponMesh()->SetVisibility(false);
	CreateWeapon(SpawnParams, AttachRules, PistolBlueprint, PistolFirstPerson, true);
	CreateWeapon(SpawnParams, AttachRules, RifleBlueprint, RifleFirstPerson, true);
	if (RifleFirstPerson) RifleFirstPerson->GetWeaponMesh()->SetVisibility(false);
}

void UWeaponHolderComponent::CreateWeapon(FActorSpawnParameters& SpawnParams, FAttachmentTransformRules& AttachRules, TSubclassOf<class ABaseWeapon> WeaponBlueprint, class ABaseWeapon* Weapon, bool bIsFirstPerson) {
	USkeletalMeshComponent* AttachMesh = bIsFirstPerson ? OwnerFirstPersonMesh : OwnerMesh;
	if (!AttachMesh || !WeaponBlueprint) return;
	Weapon = GetOwner()->GetWorld()->SpawnActor<ABaseWeapon>(WeaponBlueprint, SpawnParams);
	Weapon->AttachToComponent(AttachMesh, AttachRules, FName("WeaponSocket"));
	Weapon->GetWeaponMesh()->FirstPersonPrimitiveType = bIsFirstPerson ? EFirstPersonPrimitiveType::FirstPerson : EFirstPersonPrimitiveType::WorldSpaceRepresentation;
	bIsFirstPerson ? Weapon->GetWeaponMesh()->SetOnlyOwnerSee(true) : Weapon->GetWeaponMesh()->SetOwnerNoSee(true);
	if (ACharacter* OwningCharacter = Cast<ACharacter>(GetOwner())) Weapon->SetOwningCharacter(OwningCharacter);
	Weapon->GetWeaponMesh()->SetVisibility(false);
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