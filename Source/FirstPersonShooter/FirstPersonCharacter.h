#pragma once

#include "CoreMinimal.h"

#include "Events/EventListener.h"
#include "GameFramework/Character.h"

#include "FirstPersonCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitMarkerDelegate);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FHitEffectDelegate);

struct FInputActionValue;
class UCharacterHealthComponent;
class UCharacterState;
class UIdleState;
class UInputAction;
class UMoveState;
class UNiagaraSystem;
class USprintState;
class UWeaponHolderComponent;

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonCharacter : public ACharacter,
                                                     public IEventListener
{
    GENERATED_BODY()

    EVENTS_TO_LISTEN_TO(TEXT("RiflePickupEvent"), TEXT("BulletHitEvent"), TEXT("HealthPickupEvent"), TEXT("DeathEvent"))

public:
    AFirstPersonCharacter();

    virtual void BeginPlay() override;

    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    virtual void Tick(float DeltaSeconds) override;

    virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;

    UFUNCTION(BlueprintCallable)
    virtual void OnEventReceived_Implementation(const FName& EventName, const TArray<FAny>& Params) override;

protected:
    void Move(const FInputActionValue& Value);

    void Look(const FInputActionValue& Value);

public:
    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoMove(const float Right, const float Forward);

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoLook(const float Yaw, const float Pitch);

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpStart();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoJumpEnd();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoSprintStart();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoSprintEnd();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoShoot();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoSelectWeaponOne();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoSelectWeaponTwo();

    UFUNCTION(BlueprintCallable, Category = "Input")
    virtual void DoPause();

    UFUNCTION(BlueprintCallable, Category = "Speed")
    float GetMaxMovementSpeed(const float Right, const float Forward) const;

    const UCharacterHealthComponent* GetCharacterHealthComponent() const { return CharacterHealthComponent; }
    UCharacterHealthComponent* GetCharacterHealthComponent() { return CharacterHealthComponent; }

    const UWeaponHolderComponent* GetWeaponHolderComponent() const { return WeaponHolderComponent; }
    UWeaponHolderComponent* GetWeaponHolderComponent() { return WeaponHolderComponent; }

    const USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
    USkeletalMeshComponent* GetFirstPersonMesh() { return FirstPersonMesh; }

    const FName& GetLeaderboardName() const { return LeaderboardName; }

    bool IsPaused() const { return bIsPaused; }

    void SetPaused(bool bPaused) { bIsPaused = bPaused; }

    float GetMovementDeadzone() const { return MovementDeadzone; }

    void SetIsPressingSprint(bool bPressingSprint) { bIsPressingSprint = bPressingSprint; }

    void SetIsMovingLeft(bool bMovingLeft) { bIsMovingLeft = bMovingLeft; }

    void SetIsMovingRight(bool bMovingRight) { bIsMovingRight = bMovingRight; }

    const USceneComponent* GetBulletSpawnTransform() const { return BulletSpawnTransform; }
    USceneComponent* GetBulletSpawnTransform() { return BulletSpawnTransform; }

    const UCharacterState* GetCurrentCharacterState() const { return CurrentCharacterState; }
    UCharacterState* GetCurrentCharacterState() { return CurrentCharacterState; }

    void SetCurrentCharacterState(UCharacterState* NewState);

    const UIdleState* GetIdleState() const { return IdleState; }
    UIdleState* GetIdleState() { return IdleState; }

    const UMoveState* GetMoveState() const { return MoveState; }
    UMoveState* GetMoveState() { return MoveState; }

    const USprintState* GetSprintState() const { return SprintState; }
    USprintState* GetSprintState() { return SprintState; }

private:
    void UpdateBulletSpawnPos() const;

public:
    UPROPERTY(BlueprintAssignable)
    FHitMarkerDelegate HitMarkerDelegate;

    UPROPERTY(BlueprintAssignable)
    FHitEffectDelegate HitEffectDelegate;

protected:
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MoveAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* MouseLookAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* JumpAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* SprintAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* ShootAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* WeaponOneSelectAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* WeaponTwoSelectAction;

    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* PauseAction;

private:
    UPROPERTY()
    UCharacterState* CurrentCharacterState;

    UPROPERTY()
    UIdleState* IdleState;

    UPROPERTY()
    UMoveState* MoveState;

    UPROPERTY()
    USprintState* SprintState;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UNiagaraSystem* SparkSystem;

    UPROPERTY(EditDefaultsOnly, Category = "Effects")
    UNiagaraSystem* BloodSystem;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pause", meta = (AllowPrivateAccess = true))
    bool bIsPaused = false;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Leaderboard", meta = (AllowPrivateAccess = true))
    FName LeaderboardName;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    USkeletalMeshComponent* FirstPersonMesh;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UCameraComponent* PlayerCamera;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UCharacterHealthComponent* CharacterHealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    UWeaponHolderComponent* WeaponHolderComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    USpringArmComponent* BulletSpawnOffset;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = true))
    USceneComponent* BulletSpawnTransform;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 0.0f, ClampMax = 1.0f, AllowPrivateAccess = true,
                      ToolTip = "Deadzone for movement key to be considered pressed"))
    float MovementDeadzone = 0.05f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 400.0f, ClampMax = 600.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The base movement speed of the character when walking forwards"))
    float BaseWalkSpeed = 500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 350.0f, ClampMax = 550.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The movement speed of the character when walking diagonally forwards"))
    float DiagonalWalkSpeed = 450.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 325.0f, ClampMax = 525.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The movement speed of the character when walking sideways"))
    float StrafeWalkSpeed = 425.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 300.0f, ClampMax = 500.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The movement speed of the character when walking backwards"))
    float BackwardsWalkSpeed = 400.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 750.0f, ClampMax = 850.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The base movement speed of the character when sprinting forwards"))
    float BaseSprintSpeed = 800.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 700.0f, ClampMax = 800.0f, Units = "cm/s", AllowPrivateAccess = true,
                      ToolTip = "The base movement speed of the character when sprinting forwards"))
    float DiagonalSprintSpeed = 750.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
              meta = (AllowPrivateAccess = true, ToolTip = "Indicates if the character is moving to the left"))
    bool bIsMovingLeft = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement",
              meta = (AllowPrivateAccess = true, ToolTip = "Indicates if the character is moving to the right"))
    bool bIsMovingRight = false;

    bool bIsPressingSprint = false;

    FName CharacterThatLastShotThisCharacter;
};
