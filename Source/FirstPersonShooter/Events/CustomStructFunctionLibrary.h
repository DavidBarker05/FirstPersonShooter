#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "CustomStructFunctionLibrary.generated.h"

// If blueprints let me use void* would have been so much easier... :(

UENUM()
enum class EIsValidOutputPints : uint8 {
    Valid,
    NotValid
};

UENUM()
enum class EIsAOutputPins : uint8 {
    IsType,
    IsNotType
};


UCLASS()
class FIRSTPERSONSHOOTER_API UCustomStructFunctionLibrary : public UBlueprintFunctionLibrary {
    GENERATED_BODY()

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Equal (==) (Integer Struct, Integer Struct)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FInt32Struct_Equal_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Equal (==) (Integer Struct, Integer)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FInt32Struct_Equal_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Integer Struct, Integer Struct)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FInt32Struct_NotEqual_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Integer Struct, Integer)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FInt32Struct_NotEqual_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Less (<) (Integer Struct, Integer Struct)", CompactNodeTitle = "<", ToolTip = "Less (<)"))
        static bool FInt32Struct_LessThan_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Less (<) (Integer Struct, Integer)", CompactNodeTitle = "<", ToolTip = "Less (<)"))
        static bool FInt32Struct_LessThan_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Less Equal (<=) (Integer Struct, Integer Struct)", CompactNodeTitle = "<=", ToolTip = "Less Equal (<=)"))
        static bool FInt32Struct_LessThanOrEqualTo_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Less Equal (<=) (Integer Struct, Integer)", CompactNodeTitle = "<=", ToolTip = "Less Equal (<=)"))
        static bool FInt32Struct_LessThanOrEqualTo_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Greater (>) (Integer Struct, Integer Struct)", CompactNodeTitle = ">", ToolTip = "Greater (>)"))
        static bool FInt32Struct_GreaterThan_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Greater (>) (Integer Struct, Integer)", CompactNodeTitle = ">", ToolTip = "Greater (>)"))
        static bool FInt32Struct_GreaterThan_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Greater Equal (>=) (Integer Struct, Integer Struct)", CompactNodeTitle = ">=", ToolTip = "Greater Equal (>=)"))
        static bool FInt32Struct_GreaterThanOrEqualTo_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Greater Equal (>=) (Integer Struct, Integer)", CompactNodeTitle = ">=", ToolTip = "Greater Equal (>=)"))
        static bool FInt32Struct_GreaterThanOrEqualTo_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Add (Integer Struct, Integer Struct)", CompactNodeTitle = "+", ToolTip = "Add (A + B)"))
        static struct FInt32Struct FInt32Struct_Add_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Add (Integer Struct, Integer)", CompactNodeTitle = "+", ToolTip = "Add (A + B)"))
        static struct FInt32Struct FInt32Struct_Add_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Add (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "+", ToolTip = "Add (A + B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_Add_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Subtract (Integer Struct, Integer Struct)", CompactNodeTitle = "-", ToolTip = "Subtract (A - B)"))
        static struct FInt32Struct FInt32Struct_Subtract_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Subtract (Integer Struct, Integer)", CompactNodeTitle = "-" , ToolTip = "Subtract (A - B)"))
        static struct FInt32Struct FInt32Struct_Subtract_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Subtract (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "-", ToolTip = "Subtract (A - B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_Subtract_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Multiply (Integer Struct, Integer Struct)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)"))
        static struct FInt32Struct FInt32Struct_Multiply_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Multiply (Integer Struct, Integer)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)"))
        static struct FInt32Struct FInt32Struct_Multiply_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Multiply (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_Multiply_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Divide (Integer Struct, Integer Struct)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)"))
        static struct FInt32Struct FInt32Struct_Divide_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Divide (Integer Struct, Integer)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)"))
        static struct FInt32Struct FInt32Struct_Divide_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Divide (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_Divide_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Modulo (Integer Struct, Integer Struct)", CompactNodeTitle = "%", ToolTip = "Modulo (A % B)"))
        static struct FInt32Struct FInt32Struct_Modulo_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Modulo (Integer Struct, Integer)", CompactNodeTitle = "%", ToolTip = "Modulo (A % B)"))
        static struct FInt32Struct FInt32Struct_Modulo_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Operators", meta = (DisplayName = "Modulo (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "%", ToolTip = "Modulo (A % B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_Modulo_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Left Shift (Integer Struct, Integer Struct)", CompactNodeTitle = "<<", ToolTip = "Left Shift (A << B)"))
        static struct FInt32Struct FInt32Struct_LeftShift_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Left Shift (Integer Struct, Integer)", CompactNodeTitle = "<<", ToolTip = "Left Shift (A << B)"))
        static struct FInt32Struct FInt32Struct_LeftShift_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Left Shift (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "<<", ToolTip = "Left Shift (A << B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_LeftShift_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Right Shift (Integer Struct, Integer Struct)", CompactNodeTitle = ">>", ToolTip = "Right Shift (A >> B)"))
        static struct FInt32Struct FInt32Struct_RightShift_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Right Shift (Integer Struct, Integer)", CompactNodeTitle = ">>", ToolTip = "Right Shift (A >> B)"))
        static struct FInt32Struct FInt32Struct_RightShift_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Right Shift (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = ">>", ToolTip = "Right Shift (A >> B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_RightShift_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise AND (Integer Struct, Integer Struct)", CompactNodeTitle = "&", ToolTip = "Bitwise AND (A & B)"))
        static struct FInt32Struct FInt32Struct_BitwiseAnd_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise AND (Integer Struct, Integer)", CompactNodeTitle = "&", ToolTip = "Bitwise AND (A & B)"))
        static struct FInt32Struct FInt32Struct_BitwiseAnd_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise AND (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "&", ToolTip = "Bitwise AND (A & B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_BitwiseAnd_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise OR (Integer Struct, Integer Struct)", CompactNodeTitle = "|", ToolTip = "Bitwise OR (A | B)"))
        static struct FInt32Struct FInt32Struct_BitwiseOr_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise OR (Integer Struct, Integer)", CompactNodeTitle = "|", ToolTip = "Bitwise OR (A | B)"))
        static struct FInt32Struct FInt32Struct_BitwiseOr_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise OR (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "|", ToolTip = "Bitwise OR (A | B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_BitwiseOr_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise XOR (Integer Struct, Integer Struct)", CompactNodeTitle = "^", ToolTip = "Bitwise XOR (A ^ B)"))
        static struct FInt32Struct FInt32Struct_BitwiseXor_FInt32Struct(const struct FInt32Struct& A, const struct FInt32Struct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise XOR (Integer Struct, Integer)", CompactNodeTitle = "^", ToolTip = "Bitwise XOR (A ^ B)"))
        static struct FInt32Struct FInt32Struct_BitwiseXor_Int32(const struct FInt32Struct& A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise XOR (Integer, Integer) -> (Integer Struct)", CompactNodeTitle = "^", ToolTip = "Bitwise XOR (A ^ B)\nTakes two Integers as parameters and returns an Integer Struct"))
        static struct FInt32Struct Int32_BitwiseXor_Int32(int32 A, int32 B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise NOT (Integer Struct)", CompactNodeTitle = "~", ToolTip = "Bitwise NOT (~A)"))
        static struct FInt32Struct FInt32Struct_BitwiseNot(const struct FInt32Struct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Bitwise NOT (Integer) -> (Integer Struct)", CompactNodeTitle = "~", ToolTip = "Bitwise NOT (~A)\nTakes an Integer as a parameter and returns an Integer Struct"))
        static struct FInt32Struct Int32_BitwiseNot(int32 A);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Increment (Integer Struct)", CompactNodeTitle = "++", ToolTip = "Increment (++A)"))
        static struct FInt32Struct& FInt32Struct_PreIncrement(UPARAM(ref) struct FInt32Struct& A);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Increment (Integer) -> (Integer Struct)", CompactNodeTitle = "++", ToolTip = "Increment (++A)\nTakes an Integer as a parameter and returns an Integer Struct"))
        static struct FInt32Struct Int32_Increment(int32 A);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Decrement (Integer Struct)", CompactNodeTitle = "--", ToolTip = "Decrement (--A)"))
        static struct FInt32Struct& FInt32Struct_PreDecrement(UPARAM(ref) struct FInt32Struct& A);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|IntegerStruct|Integer", meta = (DisplayName = "Decrement (Integer) -> (Integer Struct)", CompactNodeTitle = "--", ToolTip = "Decrement (--A)\nTakes an Integer as a parameter and returns an Integer Struct"))
        static struct FInt32Struct Int32_Decrement(int32 A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (BlueprintAutocast, DisplayName = "Integer Struct To Integer", CompactNodeTitle = "->", ToolTip = "Converts an Integer Struct to an Integer"))
        static int32 FInt32Struct_To_Int32(const struct FInt32Struct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Integer", meta = (BlueprintAutocast, DisplayName = "Integer To Integer Struct", CompactNodeTitle = "->", ToolTip = "Converts an Integer to an Integer Struct"))
        static struct FInt32Struct Int32_To_FInt32Struct(int32 A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|IntegerStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Integer stored in the Integer Struct"))
        static int32 FInt32Struct_Get(const struct FInt32Struct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|IntegerStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Integer stored in the Integer Struct"))
        static struct FInt32Struct& FInt32Struct_Set(UPARAM(ref) struct FInt32Struct& InStruct, int32 NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Equal (==) (Float Struct, Float Struct)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FFloatStruct_Equal_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Equal (==) (Float Struct, Float)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FFloatStruct_Equal_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Float Struct, Float Struct)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FFloatStruct_NotEqual_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Float Struct, Float)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FFloatStruct_NotEqual_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Less (<) (Float Struct, Float Struct)", CompactNodeTitle = "<", ToolTip = "Less (<)"))
        static bool FFloatStruct_LessThan_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Less (<) (Float Struct, Float)", CompactNodeTitle = "<", ToolTip = "Less (<)"))
        static bool FFloatStruct_LessThan_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Less Equal (<=) (Float Struct, Float Struct)", CompactNodeTitle = "<=", ToolTip = "Less Equal (<=)"))
        static bool FFloatStruct_LessThanOrEqualTo_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Less Equal (<=) (Float Struct, Float)", CompactNodeTitle = "<=", ToolTip = "Less Equal (<=)"))
        static bool FFloatStruct_LessThanOrEqualTo_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Greater (>) (Float Struct, Float Struct)", CompactNodeTitle = ">", ToolTip = "Greater (>)"))
        static bool FFloatStruct_GreaterThan_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Greater (>) (Float Struct, Float)", CompactNodeTitle = ">", ToolTip = "Greater (>)"))
        static bool FFloatStruct_GreaterThan_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Greater Equal (>=) (Float Struct, Float Struct)", CompactNodeTitle = ">=", ToolTip = "Greater Equal (>=)"))
        static bool FFloatStruct_GreaterThanOrEqualTo_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Greater Equal (>=) (Float Struct, Float)", CompactNodeTitle = ">=", ToolTip = "Greater Equal (>=)"))
        static bool FFloatStruct_GreaterThanOrEqualTo_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|Float Struct|Operators", meta = (DisplayName = "Add (Float Struct, Float Struct)", CompactNodeTitle = "+", ToolTip = "Add (A + B)"))
        static struct FFloatStruct FFloatStruct_Add_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Add (Float Struct, Float)", CompactNodeTitle = "+", ToolTip = "Add (A + B)"))
        static struct FFloatStruct FFloatStruct_Add_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Add (Float, Float) -> (Float Struct)", CompactNodeTitle = "+", ToolTip = "Add (A + B)\nTakes two Floats as parameters and returns a Float Struct"))
        static struct FFloatStruct Float_Add_Float(float A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Subtract (Float Struct, Float Struct)", CompactNodeTitle = "-", ToolTip = "Subtract (A - B)"))
        static struct FFloatStruct FFloatStruct_Subtract_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Subtract (Float Struct, Float)", CompactNodeTitle = "-", ToolTip = "Subtract (A - B)"))
        static struct FFloatStruct FFloatStruct_Subtract_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Subtract (Float, Float) -> (Float Struct)", CompactNodeTitle = "-", ToolTip = "Subtract (A - B)\nTakes two Floats as parameters and returns a Float Struct"))
        static struct FFloatStruct Float_Subtract_Float(float A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Multiply (Float Struct, Float Struct)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)"))
        static struct FFloatStruct FFloatStruct_Multiply_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Multiply (Float Struct, Float)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)"))
        static struct FFloatStruct FFloatStruct_Multiply_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Multiply (Float, Float) -> (Float Struct)", CompactNodeTitle = "*", ToolTip = "Multiply (A * B)\nTakes two Floats as parameters and returns a Float Struct"))
        static struct FFloatStruct Float_Multiply_Float(float A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Divide (Float Struct, Float Struct)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)"))
        static struct FFloatStruct FFloatStruct_Divide_FFloatStruct(const struct FFloatStruct& A, const struct FFloatStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Divide (Float Struct, Float)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)"))
        static struct FFloatStruct FFloatStruct_Divide_Float(const struct FFloatStruct& A, float B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Operators", meta = (DisplayName = "Divide (Float, Float) -> (Float Struct)", CompactNodeTitle = "/", ToolTip = "Divide (A / B)\nTakes two Floats as parameters and returns a Float Struct"))
        static struct FFloatStruct Float_Divide_Float(float A, float B);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|FloatStruct|Float", meta = (DisplayName = "Increment (Float Struct)", CompactNodeTitle = "++", ToolTip = "Increment (++A)\nAdds 1.0 to A"))
        static struct FFloatStruct& FFloatStruct_PreIncrement(UPARAM(ref) struct FFloatStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Float", meta = (DisplayName = "Increment (Float) -> (Float Struct)", CompactNodeTitle = "++", ToolTip = "Increment (++A)\nAdds 1.0 to A\nTakes a Float as a parameter and returns a Float Struct"))
        static struct FFloatStruct Float_Increment(float A);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|FloatStruct|Float", meta = (DisplayName = "Decrement (Float Struct)", CompactNodeTitle = "--", ToolTip = "Decrement (--A)\nSubtracts 1.0 from A"))
        static struct FFloatStruct& FFloatStruct_PreDecrement(UPARAM(ref) struct FFloatStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Float", meta = (DisplayName = "Decrement (Float) -> (Float Struct)", CompactNodeTitle = "--", ToolTip = "Decrement (--A)\Subtracts 1.0 from A\nTakes a Float as a parameter and returns a Float Struct"))
        static struct FFloatStruct Float_Decrement(float A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Float", meta = (BlueprintAutocast, DisplayName = "Float Struct To Float", CompactNodeTitle = "->", ToolTip = "Converts a Float Struct to a Float"))
        static float FFloatStruct_To_Float(const struct FFloatStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Float", meta = (BlueprintAutocast, DisplayName = "Float To Float Struct", CompactNodeTitle = "->", ToolTip = "Converts a Float to a Float Struct"))
        static struct FFloatStruct Float_To_FFloatStruct(float A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|FloatStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Float stored in the Float Struct"))
        static float FFloatStruct_Get(const struct FFloatStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|FloatStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Float stored in the Float Struct"))
        static struct FFloatStruct& FFloatStruct_Set(UPARAM(ref) struct FFloatStruct& InStruct, float NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Operators", meta = (DisplayName = "Equal (==) (Boolean Struct, Boolean Struct)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FBoolStruct_Equal_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Operators", meta = (DisplayName = "Equal (==) (Boolean Struct, Boolean)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FBoolStruct_Equal_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Boolean Struct, Boolean Struct)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FBoolStruct_NotEqual_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Boolean Struct, Boolean)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FBoolStruct_NotEqual_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "AND (Boolean Struct, Boolean Struct)", CompactNodeTitle = "&&", ToolTip = "AND (A && B)"))
        static FBoolStruct FBoolStruct_And_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "AND (Boolean Struct, Boolean)", CompactNodeTitle = "&&", ToolTip = "AND (A && B)"))
        static FBoolStruct FBoolStruct_And_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "AND (Boolean, Boolean) -> (Boolean Struct)", CompactNodeTitle = "&&", ToolTip = "AND (A && B)\nTakes two Booleans as parameters and returns a Boolean Struct"))
        static FBoolStruct Bool_And_Bool(bool A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "OR (Boolean Struct, Boolean Struct)", CompactNodeTitle = "||", ToolTip = "OR (A || B)"))
        static FBoolStruct FBoolStruct_Or_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "OR (Boolean Struct, Boolean)", CompactNodeTitle = "||", ToolTip = "OR (A || B)"))
        static FBoolStruct FBoolStruct_Or_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "OR (Boolean, Boolean) -> (Boolean Struct)", CompactNodeTitle = "||", ToolTip = "OR (A || B)\nTakes two Booleans as parameters and returns a Boolean Struct"))
        static FBoolStruct Bool_Or_Bool(bool A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NAND (Boolean Struct, Boolean Struct)", CompactNodeTitle = "NAND", ToolTip = "NAND (A NAND B)"))
        static FBoolStruct FBoolStruct_Nand_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NAND (Boolean Struct, Boolean)", CompactNodeTitle = "NAND", ToolTip = "NAND (A NAND B)"))
        static FBoolStruct FBoolStruct_Nand_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NAND (Boolean, Boolean) -> (Boolean Struct)", CompactNodeTitle = "NAND", ToolTip = "NAND (A NAND B)\nTakes two Booleans as parameters and returns a Boolean Struct"))
        static FBoolStruct Bool_Nand_Bool(bool A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NOR (Boolean Struct, Boolean Struct)", CompactNodeTitle = "NOR", ToolTip = "NOR (A NOR B)"))
        static FBoolStruct FBoolStruct_Nor_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NOR (Boolean Struct, Boolean)", CompactNodeTitle = "NOR", ToolTip = "NOR (A NOR B)"))
        static FBoolStruct FBoolStruct_Nor_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NOR (Boolean, Boolean) -> (Boolean Struct)", CompactNodeTitle = "NOR", ToolTip = "NOR (A NOR B)\nTakes two Booleans as parameters and returns a Boolean Struct"))
        static FBoolStruct Bool_Nor_Bool(bool A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "XOR (Boolean Struct, Boolean Struct)", CompactNodeTitle = "XOR", ToolTip = "XOR (A XOR B)"))
        static FBoolStruct FBoolStruct_Xor_FBoolStruct(const struct FBoolStruct& A, const struct FBoolStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "XOR (Boolean Struct, Boolean)", CompactNodeTitle = "XOR", ToolTip = "XOR (A XOR B)"))
        static FBoolStruct FBoolStruct_Xor_Bool(const struct FBoolStruct& A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "XOR (Boolean, Boolean) -> (Boolean Struct)", CompactNodeTitle = "XOR", ToolTip = "XOR (A XOR B)\nTakes two Booleans as parameters and returns a Boolean Struct"))
        static FBoolStruct Bool_Xor_Bool(bool A, bool B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NOT (Boolean Struct)", CompactNodeTitle = "NOT", ToolTip = "NOT (!A)"))
        static FBoolStruct FBoolStruct_Not_FBoolStruct(const struct FBoolStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (DisplayName = "NOT (Boolean) -> (Boolean Struct)", CompactNodeTitle = "NOT", ToolTip = "Not (!A)\nTakes a Boolean as a parameter and returns a Boolean Struct"))
        static FBoolStruct Bool_Not_Bool(bool A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Boolean", meta = (BlueprintAutocast, DisplayName = "Boolean Struct To Boolean", CompactNodeTitle = "->", ToolTip = "Converts a Boolean Struct to a Boolean"))
        static bool FBoolStruct_To_Bool(const struct FBoolStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BoolStruct|Boolean", meta = (BlueprintAutocast, DisplayName = "Boolean To Boolean Struct", CompactNodeTitle = "->", ToolTip = "Converts a Boolean to a Boolean Struct"))
        static struct FBoolStruct Bool_ToFBoolStruct(bool A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|BooleanStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Boolean stored in the Boolean Struct"))
        static bool FBoolStruct_Get(const struct FBoolStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|BooleanStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Boolean stored in the Boolean Struct"))
        static struct FBoolStruct& FBoolStruct_Set(UPARAM(ref) struct FBoolStruct& InStruct, bool NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Equal Exacly (String Struct, String Struct)", CompactNodeTitle = "===", ToolTip = "Test if the input String Structs are equal (A == B)"))
        static bool FStringStruct_EqualExactly_FStringStruct(const struct FStringStruct& A, const struct FStringStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Equal Exacly (String Struct, String)", CompactNodeTitle = "===", ToolTip = "Test if the input String Struct and String are equal (A == B)"))
        static bool FStringStruct_EqualExactly_FString(const struct FStringStruct& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Equal, Case Incensitive (String Struct, String Struct)", CompactNodeTitle = "==", ToolTip = "Test if the input String Structs are equal (A == B), ignoring case"))
        static bool FStringStruct_EqualCaseIncensitive_FStringStruct(const struct FStringStruct& A, const struct FStringStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Equal, Case Incensitive (String Struct, String)", CompactNodeTitle = "==", ToolTip = "Test if the input String Struct and String are equal (A == B), ignoring case"))
        static bool FStringStruct_EqualCaseIncensitive_FString(const struct FStringStruct& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Not Equal Exacly (String Struct, String Struct)", CompactNodeTitle = "!==", ToolTip = "Test if the input String Structs are not equal (A != B)"))
        static bool FStringStruct_NotEqualExactly_FStringStruct(const struct FStringStruct& A, const struct FStringStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Not Equal Exacly (String Struct, String)", CompactNodeTitle = "!==", ToolTip = "Test if the input String Struct and String are not equal (A != B)"))
        static bool FStringStruct_NotEqualExactly_FString(const struct FStringStruct& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Not Equal, Case Incensitive (String Struct, String Struct)", CompactNodeTitle = "!=", ToolTip = "Test if the input String Structs are noy equal (A != B), ignoring case"))
        static bool FStringStruct_NotEqualCaseIncensitive_FStringStruct(const struct FStringStruct& A, const struct FStringStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Not Equal, Case Incensitive (String Struct, String)", CompactNodeTitle = "!=", ToolTip = "Test if the input String Struct and String are not equal (A != B), ignoring case"))
        static bool FStringStruct_NotEqualCaseIncensitive_FString(const struct FStringStruct& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Append (String Struct, String Struct)", ToolTip = "Concatenates two String Structs together to make a new String Struct"))
        static struct FStringStruct FStringStruct_Append_FStringStruct(const struct FStringStruct& A, const struct FStringStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Append (String Struct, String)", ToolTip = "Concatenates a String Struct and a String together to make a new String Struct"))
        static struct FStringStruct FStringStruct_Append_FString(const struct FStringStruct& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (DisplayName = "Append (String, String) -> (String Struct)", ToolTip = "Concatenates two Strings together to make a new String Struct"))
        static struct FStringStruct FString_Append_FString(const FString& A, const FString& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (BlueprintAutocast, DisplayName = "String Struct To String", CompactNodeTitle = "->", ToolTip = "Converts a String Struct to a String"))
        static FString FStringStruct_To_FString(const struct FStringStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|String", meta = (BlueprintAutocast, DisplayName = "String To String Struct", CompactNodeTitle = "->", ToolTip = "Converts a String to a String Struct"))
        static struct FStringStruct FString_To_FStringStruct(const FString& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|StringStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the String stored in the String Struct"))
        static FString FStringStruct_Get(const struct FStringStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|StringStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the String stored in the String Struct"))
        static struct FStringStruct& FStringStruct_Set(UPARAM(ref) struct FStringStruct& InStruct, FString NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Operators", meta = (DisplayName = "Equal (==) (Name Struct, Name Struct)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FNameStruct_Equal_FNameStruct(const struct FNameStruct& A, const struct FNameStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Operators", meta = (DisplayName = "Equal (==) (Name Struct, Name)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FNameStruct_Equal_FName(const struct FNameStruct& A, FName B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Name Struct, Name Struct)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FNameStruct_NotEqual_FNameStruct(const struct FNameStruct& A, const struct FNameStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Name Struct, Name)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FNameStruct_NotEqual_FName(const struct FNameStruct& A, FName B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Name", meta = (BlueprintAutocast, DisplayName = "Name Struct To Name", CompactNodeTitle = "->", ToolTip = "Converts a Name Struct to a Name"))
        static FName FNameStruct_To_FName(const struct FNameStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Name", meta = (BlueprintAutocast, DisplayName = "Name To Name Struct", CompactNodeTitle = "->", ToolTip = "Converts a Name to a Name Struct"))
        static struct FNameStruct FName_To_FNameStruct(const FName& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|NameStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Name stored in the Name Struct"))
        static FName FNameStruct_Get(const struct FNameStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|NameStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Name stored in the Name Struct"))
        static struct FNameStruct& FNameStruct_Set(UPARAM(ref) struct FNameStruct& InStruct, FName NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|TextStruct|Text", meta = (BlueprintAutocast, DisplayName = "Text Struct To Text", CompactNodeTitle = "->", ToolTip = "Converts a Text Struct to a Text"))
        static FText FTextStruct_To_FText(const struct FTextStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|TextStruct|Text", meta = (BlueprintAutocast, DisplayName = "Text To Text Struct", CompactNodeTitle = "->", ToolTip = "Converts a Text to a Text Struct"))
        static struct FTextStruct FText_ToFTextStruct(const FText& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|TextStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Text stored in the Text Struct"))
        static FText FTextStruct_Get(const struct FTextStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|TextStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Text stored in the Text Struct"))
        static struct FTextStruct& FTextStruct_Set(UPARAM(ref) struct FTextStruct& InStruct, FText NewValue);

    public:
        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Operators", meta = (DisplayName = "Equal (==) (Object Struct, Object Struct)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FUObjectStruct_Equal_FUObjectStruct(const struct FUObjectStruct& A, const struct FUObjectStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Operators", meta = (DisplayName = "Equal (==) (Object Struct, Object)", CompactNodeTitle = "==", ToolTip = "Equal (==)"))
        static bool FUObjectStruct_Equal_UObject(const struct FUObjectStruct& A, const UObject* B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Object Struct, Object Struct)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FUObjectStruct_NotEqual_FUObjectStruct(const struct FUObjectStruct& A, const struct FUObjectStruct& B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Operators", meta = (DisplayName = "Not Equal (!=) (Object Struct, Object)", CompactNodeTitle = "!=", ToolTip = "Not Equal (!=)"))
        static bool FUObjectStruct_NotEqual_UObject(const struct FUObjectStruct& A, const UObject* B);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Is Valid", ToolTip = "Checks whether the Object Struct contains a valid Object"))
        static bool FUObjectStruct_IsValid(const struct FUObjectStruct& ObjectStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Is Valid (Branch)", ToolTip = "Checks whether the Object Struct contains a valid Object", ExpandEnumAsExecs = "OutputPins"))
        static void FUObjectStruct_IsValidBranch(const struct FUObjectStruct& ObjectStruct, EIsValidOutputPints& OutputPins);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Cast To Object", ToolTip = "Casts the Object inside the Object Struct to the specified class"))
        static UObject* FUObjectStruct_CastAs(const struct FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Is A Class", ToolTip = "Checks whether the Object inside the Object Struct is the same type as the specified class"))
        static bool FUObjectStruct_IsA(const struct FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Is A Class (Branch)", ToolTip = "Checks whether the Object inside the Object Struct is the same type as the specified class", ExpandEnumAsExecs = "OutputPins"))
        static void FUObjectStruct_IsABranch(const struct FUObjectStruct& ObjectStruct, TSubclassOf<UObject> Class, EIsAOutputPins& OutputPins);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Object", meta = (BlueprintAutocast, DisplayName = "Object Struct To Object", CompactNodeTitle = "->", ToolTip = "Converts an Object Struct to an Object"))
        static UObject* FUObjectStruct_To_UObject(const struct FUObjectStruct& A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Object", meta = (BlueprintAutocast, DisplayName = "Object To Object Struct", CompactNodeTitle = "->", ToolTip = "Converts an Object to an Object Struct"))
        static struct FUObjectStruct UObject_To_FUObjectStruct(UObject* A);

        UFUNCTION(BlueprintPure, Category = "CustomStructs|ObjectStruct|Value", meta = (DisplayName = "Get", ToolTip = "Gets the Object stored in the Object Struct"))
        static UObject* FUObjectStruct_Get(const struct FUObjectStruct& InStruct);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|ObjectStruct|Value", meta = (DisplayName = "Set", ToolTip = "Sets the Object stored in the Object Struct"))
        static struct FUObjectStruct& FUObjectStruct_Set(UPARAM(ref) struct FUObjectStruct& InStruct, UObject* NewValue);

        UFUNCTION(BlueprintCallable, Category = "CustomStructs|ObjectStruct|Object", meta = (DisplayName = "Clear", ToolTip = "Clears the Object stored in the Object Struct\nDoesn't delete the object just removes the reference from the struct"))
        static void FUObjectStruct_Clear(UPARAM(ref) struct FUObjectStruct& InStruct);
};
