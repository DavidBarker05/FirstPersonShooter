#include "FirstPersonPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"
#include "InputMappingContext.h"

void AFirstPersonPlayerController::SetupInputComponent() {
	Super::SetupInputComponent();
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer())) {
		for (UInputMappingContext* CurrentContext : DefaultMappingContexts) {
			Subsystem->AddMappingContext(CurrentContext, 0);
		}
	}
}