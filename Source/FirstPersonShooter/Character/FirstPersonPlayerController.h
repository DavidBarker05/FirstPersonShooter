#pragma once

#include "CoreMinimal.h"

#include "GameFramework/PlayerController.h"

#include "FirstPersonPlayerController.generated.h"

class UInputMappingContext;

UCLASS()
class FIRSTPERSONSHOOTER_API AFirstPersonPlayerController : public APlayerController
{
    GENERATED_BODY()

public:
    const TArray<UInputMappingContext*>& GetDefaultMappingContexts() const { return DefaultMappingContexts; }
    TArray<UInputMappingContext*>& GetDefaultMappingContexts() { return DefaultMappingContexts; }

protected:
    virtual void SetupInputComponent() override;

    UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input", meta = (AllowPrivateAccess = "true"))
    TArray<UInputMappingContext*> DefaultMappingContexts;
};
