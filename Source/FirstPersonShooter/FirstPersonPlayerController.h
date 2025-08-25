#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FirstPersonPlayerController.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API AFirstPersonPlayerController : public APlayerController {
	GENERATED_BODY()

	protected:
		UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
		TArray<class UInputMappingContext*> DefaultMappingContexts;

		virtual void SetupInputComponent() override;
};
