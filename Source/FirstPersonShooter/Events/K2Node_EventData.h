#pragma once

#include "CoreMinimal.h"
#include "K2Node_CallFunction.h"
#include "K2Node_EventData.generated.h"

UCLASS()
class FIRSTPERSONSHOOTER_API UK2Node_EventData : public UK2Node_CallFunction {
	GENERATED_BODY()

	//~ Begin UEdGraphNode Interface
	virtual void GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const override;
	//~ End UEdGraphNode Interface

	//~ Begin K2Node Interface
	virtual bool IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const override;
	//~ End K2Node Interface

	protected:
		//~ UK2Node_CallFunction interface
		virtual bool CanToggleNodePurity() const override { return false; }
		//~ End UK2Node_CallFunction interface
};
