#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FirstPersonCharacter.generated.h"

UCLASS(Abstract)
class FIRSTPERSONSHOOTER_API AFirstPersonCharacter : public ACharacter {
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class USkeletalMeshComponent* FirstPersonMesh; // What the player can see in first person, won't clip with environment

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* PlayerCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Walk", meta = (ClampMin = 400.0f, ClampMax = 600.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The base movement speed of the character when walking forwards"))
	float BaseWalkSpeed = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Sprint", meta = (ClampMin = 750.0f, ClampMax = 850.0f, Units = "cm/s", AllowPrivateAccess = "true", ToolTip = "The base movement speed of the character when sprinting forwards"))
	float BaseSprintSpeed = 800.0f;

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
};
