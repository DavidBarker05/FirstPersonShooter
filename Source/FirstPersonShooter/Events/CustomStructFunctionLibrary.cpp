#include "Events/CustomStructFunctionLibrary.h"
#include "Blueprint/BlueprintExceptionInfo.h"

#define LOCTEXT_NAMESPACE "UCustomStructFunctionLibrary"

// FEventData
FEventData UCustomStructFunctionLibrary::MakeEventData(const int32& Value) {
	checkNoEntry();
	return {};
}

FInstancedStruct UCustomStructFunctionLibrary::BreakEventData(const FEventData& EventData) { return EventData.Data; }

bool UCustomStructFunctionLibrary::EventData_IsValid(const FEventData& EventData) { return EventData.IsValid(); }

void UCustomStructFunctionLibrary::EventData_IsValidBranch(const FEventData& EventData, EIsValidOutputPints& OutputPins) { OutputPins = EventData.IsValid() ? EIsValidOutputPints::Valid : EIsValidOutputPints::NotValid; }

FInstancedStruct UCustomStructFunctionLibrary::EventData_Get(const FEventData& InEventData) { return InEventData.Data; }

void UCustomStructFunctionLibrary::EventDataGetAsStruct(UPARAM(ref) const FEventData& InEventData, EIsAOutputPins& OutputPins, int32& Value) { checkNoEntry(); }

FEventData UCustomStructFunctionLibrary::SetEventData(const int32& Value) {
	checkNoEntry();
	return {};
}

DEFINE_FUNCTION(UCustomStructFunctionLibrary::execMakeEventData) {
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.MostRecentPropertyContainer = nullptr;
    Stack.StepCompiledIn<FStructProperty>(nullptr);
    const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
    const void* ValuePtr = Stack.MostRecentPropertyAddress;
    P_FINISH;
    if (!ValueProp || !ValuePtr) {
        FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AbortExecution, LOCTEXT("EventDataMake_MakeInvalidValueWarning", "Failed to resolve the Value for Make Event Data"));
        FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
        P_NATIVE_BEGIN;
        *(FEventData*) RESULT_PARAM = FEventData();
        P_NATIVE_END;
    }
    else {
        P_NATIVE_BEGIN;
        FInstancedStruct Instanced;
        Instanced.InitializeAs(ValueProp->Struct);
        ValueProp->Struct->CopyScriptStruct(Instanced.GetMutableMemory(), ValuePtr);
        *(FEventData*) RESULT_PARAM = FEventData(Instanced);
        P_NATIVE_END;
    }
}

DEFINE_FUNCTION(UCustomStructFunctionLibrary::execEventDataGetAsStruct) {
    P_GET_STRUCT_REF(FEventData, InEventData);
    P_GET_ENUM_REF(EIsAOutputPins, OutputPins);
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.MostRecentPropertyContainer = nullptr;
    Stack.StepCompiledIn<FStructProperty>(nullptr);
    const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
    void* ValuePtr = Stack.MostRecentPropertyAddress;
    P_FINISH;
    OutputPins = EIsAOutputPins::IsNotType;
    if (!ValueProp || !ValuePtr)
    {
        FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AbortExecution, LOCTEXT("InstancedStruct_GetInvalidValueWarning", "Failed to resolve the Value for Get Event Data As Struct"));
        FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
    }
    else
    {
        P_NATIVE_BEGIN;
        if (InEventData.Data.IsValid() && InEventData.Data.GetScriptStruct()->IsChildOf(ValueProp->Struct))
        {
            ValueProp->Struct->CopyScriptStruct(ValuePtr, InEventData.Data.GetMemory());
            OutputPins = EIsAOutputPins::IsType;
        }
        else OutputPins = EIsAOutputPins::IsNotType;
        P_NATIVE_END;
    }
}

DEFINE_FUNCTION(UCustomStructFunctionLibrary::execSetEventData) {
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.MostRecentPropertyContainer = nullptr;
    Stack.StepCompiledIn<FStructProperty>(nullptr);
    const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
    const void* ValuePtr = Stack.MostRecentPropertyAddress;
    P_FINISH;
    if (!ValueProp || !ValuePtr)
    {
        FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AbortExecution, LOCTEXT("InstancedStruct_SetInvalidValueWarning", "Failed to resolve the Value for Set Event Data"));
        FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
        P_NATIVE_BEGIN;
        *(FEventData*) RESULT_PARAM = FEventData();
        P_NATIVE_END;
    }
    else
    {
        P_NATIVE_BEGIN;
        FInstancedStruct Instanced;
        Instanced.InitializeAs(ValueProp->Struct);
        ValueProp->Struct->CopyScriptStruct(Instanced.GetMutableMemory(), ValuePtr);
        *(FEventData*) RESULT_PARAM = FEventData(Instanced);
        P_NATIVE_END;
    }
}

DEFINE_FUNCTION(UCustomStructFunctionLibrary::execStructToEventData)
{
    Stack.MostRecentPropertyAddress = nullptr;
    Stack.MostRecentPropertyContainer = nullptr;
    Stack.StepCompiledIn<FStructProperty>(nullptr);
    const FStructProperty* ValueProp = CastField<FStructProperty>(Stack.MostRecentProperty);
    const void* ValuePtr = Stack.MostRecentPropertyAddress;
    P_FINISH;
    if (!ValueProp || !ValuePtr)
    {
        FBlueprintExceptionInfo ExceptionInfo(EBlueprintExceptionType::AbortExecution, LOCTEXT("EventDataMake_ToInvalidValueWarning", "Failed to resolve the Value for Struct to Event Data"));
        FBlueprintCoreDelegates::ThrowScriptException(P_THIS, Stack, ExceptionInfo);
        P_NATIVE_BEGIN;
        *(FEventData*) RESULT_PARAM = FEventData();
        P_NATIVE_END;
    }
    else
    {
        P_NATIVE_BEGIN;
        FInstancedStruct Instanced;
        Instanced.InitializeAs(ValueProp->Struct);
        ValueProp->Struct->CopyScriptStruct(Instanced.GetMutableMemory(), ValuePtr);
        *(FEventData*) RESULT_PARAM = FEventData(Instanced);
        P_NATIVE_END;
    }
}

#undef LOCTEXT_NAMESPACE

// FInt32Struct
FInt32Struct UCustomStructFunctionLibrary::MakeInt32Struct(int32 InValue) { return InValue; }

int32 UCustomStructFunctionLibrary::BreakInt32Struct(const FInt32Struct& IntegerStruct) { return IntegerStruct; }

bool UCustomStructFunctionLibrary::FInt32Struct_Equal_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A == B; }

bool UCustomStructFunctionLibrary::FInt32Struct_Equal_Int32(const FInt32Struct& A, int32 B) { return A == B; }

bool UCustomStructFunctionLibrary::FInt32Struct_NotEqual_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A != B; }

bool UCustomStructFunctionLibrary::FInt32Struct_NotEqual_Int32(const FInt32Struct& A, int32 B) { return A != B; }

bool UCustomStructFunctionLibrary::FInt32Struct_LessThan_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A < B; }

bool UCustomStructFunctionLibrary::FInt32Struct_LessThan_Int32(const FInt32Struct& A, int32 B) { return A < B; }

bool UCustomStructFunctionLibrary::FInt32Struct_LessThanOrEqualTo_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A <= B; }

bool UCustomStructFunctionLibrary::FInt32Struct_LessThanOrEqualTo_Int32(const FInt32Struct& A, int32 B) { return A <= B; }

bool UCustomStructFunctionLibrary::FInt32Struct_GreaterThan_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A > B; }

bool UCustomStructFunctionLibrary::FInt32Struct_GreaterThan_Int32(const FInt32Struct& A, int32 B) { return A > B; }

bool UCustomStructFunctionLibrary::FInt32Struct_GreaterThanOrEqualTo_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A >= B; }

bool UCustomStructFunctionLibrary::FInt32Struct_GreaterThanOrEqualTo_Int32(const FInt32Struct& A, int32 B) { return A >= B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Add_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A + B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Add_Int32(const FInt32Struct& A, int32 B) { return A + B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Add_Int32(int32 A, int32 B) { return A + B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Subtract_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A - B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Subtract_Int32(const FInt32Struct& A, int32 B) { return A - B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Subtract_Int32(int32 A, int32 B) { return A - B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Multiply_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A * B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Multiply_Int32(const FInt32Struct& A, int32 B) { return A * B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Multiply_Int32(int32 A, int32 B) { return A * B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Divide_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A / B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Divide_Int32(const FInt32Struct& A, int32 B) { return A / B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Divide_Int32(int32 A, int32 B) { return A / B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Modulo_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A % B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_Modulo_Int32(const FInt32Struct& A, int32 B) { return A % B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Modulo_Int32(int32 A, int32 B) { return A % B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_LeftShift_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A << B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_LeftShift_Int32(const FInt32Struct& A, int32 B) { return A << B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_LeftShift_Int32(int32 A, int32 B) { return A << B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_RightShift_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A >> B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_RightShift_Int32(const FInt32Struct& A, int32 B) { return A >> B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_RightShift_Int32(int32 A, int32 B) { return A >> B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseAnd_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A & B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseAnd_Int32(const FInt32Struct& A, int32 B) { return A & B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_BitwiseAnd_Int32(int32 A, int32 B) { return A & B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseOr_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A | B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseOr_Int32(const FInt32Struct& A, int32 B) { return A | B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_BitwiseOr_Int32(int32 A, int32 B) { return A | B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseXor_FInt32Struct(const FInt32Struct& A, const FInt32Struct& B) { return A ^ B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseXor_Int32(const FInt32Struct& A, int32 B) { return A ^ B; }

FInt32Struct UCustomStructFunctionLibrary::Int32_BitwiseXor_Int32(int32 A, int32 B) { return A ^ B; }

FInt32Struct UCustomStructFunctionLibrary::FInt32Struct_BitwiseNot(const FInt32Struct& A) { return ~A; }

FInt32Struct UCustomStructFunctionLibrary::Int32_BitwiseNot(int32 A) { return ~A; }

FInt32Struct& UCustomStructFunctionLibrary::FInt32Struct_PreIncrement(UPARAM(ref) FInt32Struct& A) { return ++A; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Increment(int32 A) { return ++A; }

FInt32Struct& UCustomStructFunctionLibrary::FInt32Struct_PreDecrement(UPARAM(ref) FInt32Struct& A) { return --A; }

FInt32Struct UCustomStructFunctionLibrary::Int32_Decrement(int32 A) { return --A; }

int32 UCustomStructFunctionLibrary::FInt32Struct_To_Int32(const FInt32Struct& A) { return A; }

FInt32Struct UCustomStructFunctionLibrary::Int32_To_FInt32Struct(int32 A) { return A; }

int32 UCustomStructFunctionLibrary::FInt32Struct_Get(const FInt32Struct& InStruct) { return InStruct.Get(); }

FInt32Struct& UCustomStructFunctionLibrary::FInt32Struct_Set(UPARAM(ref) struct FInt32Struct& InStruct, int32 NewValue) { return InStruct.Set(NewValue); }

// FFloatStruct
FFloatStruct UCustomStructFunctionLibrary::MakeFloatStruct(float InValue) { return InValue; }

float UCustomStructFunctionLibrary::BreakFloatStruct(const FFloatStruct& FloatStruct) { return FloatStruct; }

bool UCustomStructFunctionLibrary::FFloatStruct_Equal_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A == B; }

bool UCustomStructFunctionLibrary::FFloatStruct_Equal_Float(const FFloatStruct& A, float B) { return A == B; }

bool UCustomStructFunctionLibrary::FFloatStruct_NotEqual_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A != B; }

bool UCustomStructFunctionLibrary::FFloatStruct_NotEqual_Float(const FFloatStruct& A, float B) { return A != B; }

bool UCustomStructFunctionLibrary::FFloatStruct_LessThan_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A < B; }

bool UCustomStructFunctionLibrary::FFloatStruct_LessThan_Float(const FFloatStruct& A, float B) { return A < B; }

bool UCustomStructFunctionLibrary::FFloatStruct_LessThanOrEqualTo_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A <= B; }

bool UCustomStructFunctionLibrary::FFloatStruct_LessThanOrEqualTo_Float(const FFloatStruct& A, float B) { return A <= B; }

bool UCustomStructFunctionLibrary::FFloatStruct_GreaterThan_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A > B; }

bool UCustomStructFunctionLibrary::FFloatStruct_GreaterThan_Float(const FFloatStruct& A, float B) { return A > B; }

bool UCustomStructFunctionLibrary::FFloatStruct_GreaterThanOrEqualTo_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A >= B; }

bool UCustomStructFunctionLibrary::FFloatStruct_GreaterThanOrEqualTo_Float(const FFloatStruct& A, float B) { return A >= B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Add_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A + B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Add_Float(const FFloatStruct& A, float B) { return A + B; }

FFloatStruct UCustomStructFunctionLibrary::Float_Add_Float(float A, float B) { return A + B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Subtract_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A - B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Subtract_Float(const FFloatStruct& A, float B) { return A - B; }

FFloatStruct UCustomStructFunctionLibrary::Float_Subtract_Float(float A, float B) { return A - B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Multiply_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A * B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Multiply_Float(const FFloatStruct& A, float B) { return A * B; }

FFloatStruct UCustomStructFunctionLibrary::Float_Multiply_Float(float A, float B) { return A * B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Divide_FFloatStruct(const FFloatStruct& A, const FFloatStruct& B) { return A / B; }

FFloatStruct UCustomStructFunctionLibrary::FFloatStruct_Divide_Float(const FFloatStruct& A, float B) { return A / B; }

FFloatStruct UCustomStructFunctionLibrary::Float_Divide_Float(float A, float B) { return A / B; }

FFloatStruct& UCustomStructFunctionLibrary::FFloatStruct_PreIncrement(UPARAM(ref) FFloatStruct& A) { return A.Set(A + 1.0f); }

FFloatStruct UCustomStructFunctionLibrary::Float_Increment(float A) { return A + 1.0f; }

FFloatStruct& UCustomStructFunctionLibrary::FFloatStruct_PreDecrement(UPARAM(ref) FFloatStruct& A) { return A.Set(A - 1.0f); }

FFloatStruct UCustomStructFunctionLibrary::Float_Decrement(float A) { return A - 1.0f; }

float UCustomStructFunctionLibrary::FFloatStruct_To_Float(const FFloatStruct& A) { return A; }

FFloatStruct UCustomStructFunctionLibrary::Float_To_FFloatStruct(float A) { return A; }

float UCustomStructFunctionLibrary::FFloatStruct_Get(const FFloatStruct& InStruct) { return InStruct.Get(); }

FFloatStruct& UCustomStructFunctionLibrary::FFloatStruct_Set(UPARAM(ref) FFloatStruct& InStruct, float NewValue) { return InStruct.Set(NewValue); }

// FBoolStruct
FBoolStruct UCustomStructFunctionLibrary::MakeBoolStruct(bool InValue) { return InValue; }

bool UCustomStructFunctionLibrary::BreakBoolStruct(const FBoolStruct& BooleanStruct) { return BooleanStruct; }

bool UCustomStructFunctionLibrary::FBoolStruct_Equal_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return A == B; }

bool UCustomStructFunctionLibrary::FBoolStruct_Equal_Bool(const FBoolStruct& A, bool B) { return A == B; }

bool UCustomStructFunctionLibrary::FBoolStruct_NotEqual_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return A != B; }

bool UCustomStructFunctionLibrary::FBoolStruct_NotEqual_Bool(const FBoolStruct& A, bool B) { return A != B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_And_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return A && B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_And_Bool(const FBoolStruct& A, bool B) { return A && B; }

FBoolStruct UCustomStructFunctionLibrary::Bool_And_Bool(bool A, bool B) { return A && B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Or_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return A || B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Or_Bool(const FBoolStruct& A, bool B) { return A || B; }

FBoolStruct UCustomStructFunctionLibrary::Bool_Or_Bool(bool A, bool B) { return FBoolStruct(A || B); }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Nand_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return !(A && B); }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Nand_Bool(const FBoolStruct& A, bool B) { return !(A && B); }

FBoolStruct UCustomStructFunctionLibrary::Bool_Nand_Bool(bool A, bool B) { return !(A && B); }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Nor_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return !(A || B); }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Nor_Bool(const FBoolStruct& A, bool B) { return (!A || B); }

FBoolStruct UCustomStructFunctionLibrary::Bool_Nor_Bool(bool A, bool B) { return !(A || B); }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Xor_FBoolStruct(const FBoolStruct& A, const FBoolStruct& B) { return A ^ B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Xor_Bool(const FBoolStruct& A, bool B) { return A ^ B; }

FBoolStruct UCustomStructFunctionLibrary::Bool_Xor_Bool(bool A, bool B) { return A ^ B; }

FBoolStruct UCustomStructFunctionLibrary::FBoolStruct_Not_FBoolStruct(const FBoolStruct& A) { return !A; }

FBoolStruct UCustomStructFunctionLibrary::Bool_Not_Bool(bool A) { return !A; }

bool UCustomStructFunctionLibrary::FBoolStruct_To_Bool(const FBoolStruct& A) { return A; }

FBoolStruct UCustomStructFunctionLibrary::Bool_ToFBoolStruct(bool A) { return A; }

bool UCustomStructFunctionLibrary::FBoolStruct_Get(const FBoolStruct& InStruct) { return InStruct.Get(); }

FBoolStruct& UCustomStructFunctionLibrary::FBoolStruct_Set(UPARAM(ref) FBoolStruct& InStruct, bool NewValue) { return InStruct.Set(NewValue); }

// FStringStruct
FStringStruct UCustomStructFunctionLibrary::MakeStringStruct(const FString& InValue) { return InValue; }

FString UCustomStructFunctionLibrary::BreakStringStruct(const FStringStruct& StringStruct) { return StringStruct; }

bool UCustomStructFunctionLibrary::FStringStruct_EqualExactly_FStringStruct(const FStringStruct& A, const FStringStruct& B) { return A.Equals(B); }

bool UCustomStructFunctionLibrary::FStringStruct_EqualExactly_FString(const FStringStruct& A, const FString& B) { return A.Equals(B); }

bool UCustomStructFunctionLibrary::FStringStruct_EqualCaseIncensitive_FStringStruct(const FStringStruct& A, const FStringStruct& B) { return A.Equals(B, ESearchCase::IgnoreCase); }

bool UCustomStructFunctionLibrary::FStringStruct_EqualCaseIncensitive_FString(const FStringStruct& A, const FString& B) { return A.Equals(B, ESearchCase::IgnoreCase); }

bool UCustomStructFunctionLibrary::FStringStruct_NotEqualExactly_FStringStruct(const FStringStruct& A, const FStringStruct& B) { return !A.Equals(B); }

bool UCustomStructFunctionLibrary::FStringStruct_NotEqualExactly_FString(const FStringStruct& A, const FString& B) { return !A.Equals(B); }

bool UCustomStructFunctionLibrary::FStringStruct_NotEqualCaseIncensitive_FStringStruct(const FStringStruct& A, const FStringStruct& B) { return !A.Equals(B, ESearchCase::IgnoreCase); }

bool UCustomStructFunctionLibrary::FStringStruct_NotEqualCaseIncensitive_FString(const FStringStruct& A, const FString& B) { return !A.Equals(B, ESearchCase::IgnoreCase); }

FStringStruct UCustomStructFunctionLibrary::FStringStruct_Append_FStringStruct(const FStringStruct& A, const FStringStruct& B) { return A + B; }

FStringStruct UCustomStructFunctionLibrary::FStringStruct_Append_FString(const FStringStruct& A, const FString& B) { return A + B; }

FStringStruct UCustomStructFunctionLibrary::FString_Append_FString(const FString& A, const FString& B) { return A + B; }

FString UCustomStructFunctionLibrary::FStringStruct_To_FString(const FStringStruct& A) { return A; }

FStringStruct UCustomStructFunctionLibrary::FString_To_FStringStruct(const FString& A) { return A; }

FString UCustomStructFunctionLibrary::FStringStruct_Get(const FStringStruct& InStruct) { return InStruct.Get(); }

FStringStruct& UCustomStructFunctionLibrary::FStringStruct_Set(UPARAM(ref) FStringStruct& InStruct, const FString& NewValue) { return InStruct.Set(NewValue); }

// FNameStruct
FNameStruct UCustomStructFunctionLibrary::MakeNameStruct(const FName& InValue) { return InValue; }

FName UCustomStructFunctionLibrary::BreakNameStruct(const FNameStruct& NameStruct) { return NameStruct; }

bool UCustomStructFunctionLibrary::FNameStruct_Equal_FNameStruct(const FNameStruct& A, const FNameStruct& B) { return A == B; }

bool UCustomStructFunctionLibrary::FNameStruct_Equal_FName(const FNameStruct& A, FName B) { return A == B; }

bool UCustomStructFunctionLibrary::FNameStruct_NotEqual_FNameStruct(const FNameStruct& A, const FNameStruct& B) { return A != B; }

bool UCustomStructFunctionLibrary::FNameStruct_NotEqual_FName(const FNameStruct& A, FName B) { return A != B; }

FName UCustomStructFunctionLibrary::FNameStruct_To_FName(const FNameStruct& A) { return A; }

FNameStruct UCustomStructFunctionLibrary::FName_To_FNameStruct(const FName& A) { return A; }

FName UCustomStructFunctionLibrary::FNameStruct_Get(const FNameStruct& InStruct) { return InStruct.Get(); }

FNameStruct& UCustomStructFunctionLibrary::FNameStruct_Set(UPARAM(ref) FNameStruct& InStruct, const FName& NewValue) { return InStruct.Set(NewValue); }

// FTextStruct
FTextStruct UCustomStructFunctionLibrary::MakeTextStruct(const FText& InValue) { return InValue; }

FText UCustomStructFunctionLibrary::BreakTextStruct(const FTextStruct& TextStruct) { return TextStruct; }

FText UCustomStructFunctionLibrary::FTextStruct_To_FText(const FTextStruct& A) { return A; }

FTextStruct UCustomStructFunctionLibrary::FText_ToFTextStruct(const FText& A) { return A; }

FText UCustomStructFunctionLibrary::FTextStruct_Get(const FTextStruct& InStruct) { return InStruct.Get(); }

FTextStruct& UCustomStructFunctionLibrary::FTextStruct_Set(UPARAM(ref) FTextStruct& InStruct, const FText& NewValue) { return InStruct.Set(NewValue); }

// FUObjectStruct
FUObjectStruct UCustomStructFunctionLibrary::MakeObjectStruct(UObject* InValue) { return InValue; }

UObject* UCustomStructFunctionLibrary::BreakObjectStruct(const FUObjectStruct& ObjectStruct) { return ObjectStruct; }

bool UCustomStructFunctionLibrary::FUObjectStruct_Equal_FUObjectStruct(const FUObjectStruct& A, const FUObjectStruct& B) { return A == B; }

bool UCustomStructFunctionLibrary::FUObjectStruct_Equal_UObject(const FUObjectStruct& A, const UObject* B) { return A == B; }

bool UCustomStructFunctionLibrary::FUObjectStruct_NotEqual_FUObjectStruct(const FUObjectStruct& A, const FUObjectStruct& B) { return A != B; }

bool UCustomStructFunctionLibrary::FUObjectStruct_NotEqual_UObject(const FUObjectStruct& A, const UObject* B) { return A != B; }

bool UCustomStructFunctionLibrary::FUObjectStruct_IsValid(const FUObjectStruct& ObjectStruct) { return ObjectStruct; }

void UCustomStructFunctionLibrary::FUObjectStruct_IsValidBranch(const FUObjectStruct& ObjectStruct, EIsValidOutputPints& OutputPins) { OutputPins = ObjectStruct ? EIsValidOutputPints::Valid : EIsValidOutputPints::NotValid; }

bool UCustomStructFunctionLibrary::FUObjectStruct_IsA(const FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class) { return ObjectStruct.IsA(Class); }

void UCustomStructFunctionLibrary::FUObjectStruct_IsABranch(const FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class, EIsAOutputPins& OutputPins) { OutputPins = ObjectStruct.IsA(Class) ? EIsAOutputPins::IsType : EIsAOutputPins::IsNotType; }

UObject* UCustomStructFunctionLibrary::FUObjectStruct_To_UObject(const FUObjectStruct& A) { return A; }

FUObjectStruct UCustomStructFunctionLibrary::UObject_To_FUObjectStruct(UObject* A) { return A; }

UObject* UCustomStructFunctionLibrary::FUObjectStruct_Get(const FUObjectStruct& InStruct) { return InStruct.Get(); }

UObject* UCustomStructFunctionLibrary::FUObjectStruct_GetAsType(const FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class, EIsAOutputPins& OutputPins)
{
	if (ObjectStruct && ObjectStruct.IsA(Class)) {
		OutputPins = EIsAOutputPins::IsType;
		return ObjectStruct;
	}
	OutputPins = EIsAOutputPins::IsNotType;
	return nullptr;
}

FUObjectStruct& UCustomStructFunctionLibrary::FUObjectStruct_Set(UPARAM(ref) FUObjectStruct& InStruct, UObject* NewValue) { return InStruct.Set(NewValue); }

void UCustomStructFunctionLibrary::FUObjectStruct_Clear(UPARAM(ref) FUObjectStruct& InStruct) { InStruct.Clear(); }
