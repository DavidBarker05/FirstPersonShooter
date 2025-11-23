#include "Events/K2Node_EventData.h"
#include "EdGraphSchema_K2.h"
#include "BlueprintNodeSpawner.h"
#include "BlueprintActionDatabaseRegistrar.h"
#include "Events/CustomStructFunctionLibrary.h"

#include UE_INLINE_GENERATED_CPP_BY_NAME(K2Node_EventData)

#define LOCTEXT_NAMESPACE "EventData"

void UK2Node_EventData::GetMenuActions(FBlueprintActionDatabaseRegistrar& ActionRegistrar) const
{
	Super::GetMenuActions(ActionRegistrar);
	UClass* Action = GetClass();
	if (ActionRegistrar.IsOpenForRegistration(Action))
	{
		auto CustomizeLambda = [](UEdGraphNode* NewNode, bool bIsTemplateNode, const FName FunctionName)
		{
			UK2Node_EventData* Node = CastChecked<UK2Node_EventData>(NewNode);
			UFunction* Function = UCustomStructFunctionLibrary::StaticClass()->FindFunctionByName(FunctionName);
			check(Function);
			Node->SetFromFunction(Function);
		};
		// MakeEventData()
		UBlueprintNodeSpawner* MakeNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(MakeNodeSpawner != nullptr);
		MakeNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UCustomStructFunctionLibrary, MakeEventData));
		ActionRegistrar.AddBlueprintAction(Action, MakeNodeSpawner);
		// EventDataGetAsStruct()
		UBlueprintNodeSpawner* GetNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(GetNodeSpawner != nullptr);
		GetNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UCustomStructFunctionLibrary, EventDataGetAsStruct));
		ActionRegistrar.AddBlueprintAction(Action, GetNodeSpawner);
		// SetEventData()
		UBlueprintNodeSpawner* SetNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(SetNodeSpawner != nullptr);
		SetNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UCustomStructFunctionLibrary, SetEventData));
		ActionRegistrar.AddBlueprintAction(Action, SetNodeSpawner);
		// StructToEventData()
		UBlueprintNodeSpawner* ToNodeSpawner = UBlueprintNodeSpawner::Create(GetClass());
		check(ToNodeSpawner != nullptr);
		MakeNodeSpawner->CustomizeNodeDelegate = UBlueprintNodeSpawner::FCustomizeNodeDelegate::CreateStatic(CustomizeLambda, GET_FUNCTION_NAME_CHECKED(UCustomStructFunctionLibrary, StructToEventData));
		ActionRegistrar.AddBlueprintAction(Action, ToNodeSpawner);
	}
}

bool UK2Node_EventData::IsConnectionDisallowed(const UEdGraphPin* MyPin, const UEdGraphPin* OtherPin, FString& OutReason) const
{
	const UEdGraphPin* ValuePin = FindPinChecked(FName(TEXT("Value")));
	if (MyPin == ValuePin && MyPin->PinType.PinCategory == UEdGraphSchema_K2::PC_Wildcard)
	{
		if (OtherPin->PinType.PinCategory != UEdGraphSchema_K2::PC_Struct)
		{
			OutReason = TEXT("Value must be a struct.");
			return true;
		}
	}
	return false;
}

#undef LOCTEXT_NAMESPACE