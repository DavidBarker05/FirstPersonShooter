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

    const UCharacterState* GetCurrentCharacterState() const { return CurrentCharacterState; }
    UCharacterState* GetCurrentCharacterState() { return CurrentCharacterState; }

    void SetCurrentCharacterState(UCharacterState* NewState);

    const UIdleState* GetIdleState() const { return IdleState; }
    UIdleState* GetIdleState() { return IdleState; }

    const UMoveState* GetMoveState() const { return MoveState; }
    UMoveState* GetMoveState() { return MoveState; }

    const USprintState* GetSprintState() const { return SprintState; }
    USprintState* GetSprintState() { return SprintState; }

    const UNiagaraSystem* GetBloodSystem() const { return BloodSystem; }
    UNiagaraSystem* GetBloodSystem() { return BloodSystem; }

    const UNiagaraSystem* GetSparkSystem() const { return SparkSystem; }
    UNiagaraSystem* GetSparkSystem() { return SparkSystem; }

    bool IsPaused() const { return bIsPaused; }

    AFirstPersonCharacter& SetPaused(const bool bPaused)
    {
        bIsPaused = bPaused;
        return *this;
    }

    const FName& GetLeaderboardName() const { return LeaderboardName; }

    const USkeletalMeshComponent* GetFirstPersonMesh() const { return FirstPersonMesh; }
    USkeletalMeshComponent* GetFirstPersonMesh() { return FirstPersonMesh; }

    const UCameraComponent* GetPlayerCamera() const { return PlayerCamera; }
    UCameraComponent* GetPlayerCamera() { return PlayerCamera; }

    const UCharacterHealthComponent* GetCharacterHealthComponent() const { return CharacterHealthComponent; }
    UCharacterHealthComponent* GetCharacterHealthComponent() { return CharacterHealthComponent; }

    const UWeaponHolderComponent* GetWeaponHolderComponent() const { return WeaponHolderComponent; }
    UWeaponHolderComponent* GetWeaponHolderComponent() { return WeaponHolderComponent; }

    const USpringArmComponent* GetBulletSpawnOffset() const { return BulletSpawnOffset; }
    USpringArmComponent* GetBulletSpawnOffset() { return BulletSpawnOffset; }

    const USceneComponent* GetBulletSpawnTransform() const { return BulletSpawnTransform; }
    USceneComponent* GetBulletSpawnTransform() { return BulletSpawnTransform; }

    float GetMovementDeadzone() const { return MovementDeadzone; }

    float GetBaseWalkSpeed() const { return BaseWalkSpeed; }

    float GetDiagonalWalkSpeed() const { return DiagonalWalkSpeed; }

    float GetStrafeWalkSpeed() const { return StrafeWalkSpeed; }

    float GetBackwardsWalkSpeed() const { return BackwardsWalkSpeed; }

    float GetBaseSprintSpeed() const { return BaseSprintSpeed; }

    float GetDiagonalSprintSpeed() const { return DiagonalSprintSpeed; }

    bool IsMovingLeft() const { return bIsMovingLeft; }

    AFirstPersonCharacter& SetIsMovingLeft(const bool bMovingLeft)
    {
        bIsMovingLeft = bMovingLeft;
        return *this;
    }

    bool IsMovingRight() const { return bIsMovingRight; }

    AFirstPersonCharacter& SetIsMovingRight(const bool bMovingRight)
    {
        bIsMovingRight = bMovingRight;
        return *this;
    }

    bool IsPressingSprint() const { return bIsPressingSprint; }
    AFirstPersonCharacter& SetIsPressingSprint(const bool bPressingSprint)
    {
        bIsPressingSprint = bPressingSprint;
        return *this;
    }

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

#if WITH_EDITORONLY_DATA
    UPROPERTY(EditAnywhere, Category = "Input")
    UInputAction* EditorPauseAction;
#endif

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
              meta = (ClampMin = 0.0, UIMin = 0.0, ClampMax = 1.0, UIMax = 1.0,
                      ToolTip = "Deadzone for movement key to be considered pressed", AllowPrivateAccess = true))
    float MovementDeadzone = 0.05f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 400.0, UIMin = 400.0, ClampMax = 600.0, UIMax = 600.0, Units = "cm/s",
                      ToolTip = "The base movement speed of the character when walking forwards",
                      AllowPrivateAccess = true))
    float BaseWalkSpeed = 500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 350.0, UIMin = 350.0, ClampMax = 550.0, UIMax = 550.0, Units = "cm/s",
                      ToolTip = "The movement speed of the character when walking diagonally forwards",
                      AllowPrivateAccess = true))
    float DiagonalWalkSpeed = 450.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 325.0, UIMin = 325.0, ClampMax = 525.0, UIMax = 525.0, Units = "cm/s",
                      ToolTip = "The movement speed of the character when walking sideways", AllowPrivateAccess = true))
    float StrafeWalkSpeed = 425.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 300.0, UIMin = 300.0, ClampMax = 500.0, UIMax = 500.0, Units = "cm/s",
                      ToolTip = "The movement speed of the character when walking backwards",
                      AllowPrivateAccess = true))
    float BackwardsWalkSpeed = 400.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 750.0, UIMin = 750.0, ClampMax = 850.0, UIMax = 850.0, Units = "cm/s",
                      ToolTip = "The base movement speed of the character when sprinting forwards",
                      AllowPrivateAccess = true))
    float BaseSprintSpeed = 800.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Movement",
              meta = (ClampMin = 700.0, UIMin = 700.0, ClampMax = 800.0, UIMax = 800.0, Units = "cm/s",
                      ToolTip = "The base movement speed of the character when sprinting forwards",
                      AllowPrivateAccess = true))
    float DiagonalSprintSpeed = 750.0f;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement",
              meta = (ToolTip = "Indicates if the character is moving to the left", AllowPrivateAccess = true))
    bool bIsMovingLeft = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement",
              meta = (ToolTip = "Indicates if the character is moving to the right", AllowPrivateAccess = true))
    bool bIsMovingRight = false;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Movement",
              meta = (ToolTip = "Indicates if the player is pressing the sprint key", AllowPrivateAccess = true))
    bool bIsPressingSprint = false;

    FName CharacterThatLastShotThisCharacter;
};
