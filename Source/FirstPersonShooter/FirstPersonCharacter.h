#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonCharacter : public ACharacter {
	GENERATED_BODY()

	bool bIsPressingSprint = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh; // What the player can see in first person, won't clip with environment

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCharacterHealthComponent* CharacterHealthComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Camera", meta = (ClampMin = 0.1f, AllowPrivateAccess = "true", ToolTip = "The minimum distance the camera needs to be from the head bone to move there (stop head bobbing)"))
	float CameraMoveThreshold = 5.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Movement", meta = (ClampMin = 0f, ClampMax = 1f, AllowPrivateAccess = "true", ToolTip = "Deadzone for movement key to be considered pressed"))
	float MovementDeadzone = 0.05f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk", meta = (ClampMin = 400.0f, ClampMax = 600.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The base movement speed of the character when walking forwards"))
	float BaseWalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk", meta = (ClampMin = 350.0f, ClampMax = 550.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The movement speed of the character when walking diagonally forwards"))
	float DiagonalWalkSpeed = 450.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk", meta = (ClampMin = 325.0f, ClampMax = 525.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The movement speed of the character when walking sideways"))
	float StrafeWalkSpeed = 425.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk", meta = (ClampMin = 300.0f, ClampMax = 500.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The movement speed of the character when walking backwards"))
	float BackwardsWalkSpeed = 400.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint", meta = (ClampMin = 750.0f, ClampMax = 850.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The base movement speed of the character when sprinting forwards"))
	float BaseSprintSpeed = 800.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint", meta = (ClampMin = 700.0f, ClampMax = 800.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The base movement speed of the character when sprinting forwards"))
	float DiagonalSprintSpeed = 750.0f;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true", ToolTip = "Indicates if the character is moving to the left"))
	bool bIsMovingLeft = false;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true", ToolTip = "Indicates if the character is moving to the right"))
	bool bIsMovingRight = false;

	protected:
		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* MoveAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* MouseLookAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* JumpAction;

		UPROPERTY(EditAnywhere, Category = "Input")
		class UInputAction* SprintAction;

	public:
		AFirstPersonCharacter();

	protected:
		virtual void BeginPlay() override;

	public:
		virtual void Tick(float DeltaSeconds) override;

	protected:
		virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	protected:
		void Move(const struct FInputActionValue& Value);

		void Look(const struct FInputActionValue& Value);

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

	private:
		void MoveCameraToSocket();

		float GetMaxMovementSpeed(const float Right, const float Forward);

	public:
		class UCharacterHealthComponent* GetCharacterHealthComponent();
};
