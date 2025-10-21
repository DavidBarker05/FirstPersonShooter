#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "EventData.generated.h"

// All of this is because blueprints don't allow void* and unreal doesn't allow template ustructs

USTRUCT(BlueprintType)
struct FIRSTPERSONSHOOTER_API FEventData {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FInstancedStruct Data;

	FEventData() = default;

	template<typename T>
	FEventData(T&& InData) {
		Data.InitializeAs<T>();
		*Data.GetMutable<T>() = Forward<T>(InData);
	}

	template<typename T>
	void SetData(T&& InData) {
		Data.InitializeAs<T>();
		*Data.GetMutable<T>() = Forward<T>(InData);
	}

	template<typename T>
	T* Get() { return Data.GetScriptStruct() == TBaseStructure<T>::Get() ? Data.GetMutable<T>() : nullptr; }

	template<typename T>
	const T* Get() const { return Data.GetScriptStruct() == TBaseStructure<T>::Get() ? Data.Get<T>() : nullptr; }
};

USTRUCT(BlueprintType, meta = (DisplayName = "Integer Struct"))
struct FIRSTPERSONSHOOTER_API FInt32Struct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 Value = 0;

	FInt32Struct() = default;

	FInt32Struct(const FInt32Struct& Other) : Value(Other.Value) {}

	FInt32Struct(int32 InValue) : Value(InValue) {}

	inline FInt32Struct& operator=(const FInt32Struct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FInt32Struct& operator=(int32 OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline bool operator==(const FInt32Struct& Other) const { return Value == Other.Value; }

	inline bool operator==(const int32 OtherValue) const { return Value == OtherValue; }

	inline bool operator!=(const FInt32Struct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const int32 OtherValue) const { return Value != OtherValue; }

	inline bool operator<(const FInt32Struct& Other) const { return Value < Other.Value; }

	inline bool operator<(const int32 OtherValue) const { return Value < OtherValue; }

	inline bool operator<=(const FInt32Struct& Other) const { return Value <= Other.Value; }

	inline bool operator<=(const int32 OtherValue) const { return Value <= OtherValue; }

	inline bool operator>(const FInt32Struct& Other) const { return Value > Other.Value; }

	inline bool operator>(const int32 OtherValue) const { return Value > OtherValue; }

	inline bool operator>=(const FInt32Struct& Other) const { return Value >= Other.Value; }

	inline bool operator>=(const int32 OtherValue) const { return Value >= OtherValue; }

	inline FInt32Struct operator+(const FInt32Struct& Other) const { return FInt32Struct(Value + Other.Value); }

	inline FInt32Struct operator+(const int32 OtherValue) const { return FInt32Struct(Value + OtherValue); }

	inline FInt32Struct operator-(const FInt32Struct& Other) const { return FInt32Struct(Value - Other.Value); }

	inline FInt32Struct operator-(const int32 OtherValue) const { return FInt32Struct(Value - OtherValue); }

	inline FInt32Struct operator*(const FInt32Struct& Other) const { return FInt32Struct(Value * Other.Value); }

	inline FInt32Struct operator*(const int32 OtherValue) const { return FInt32Struct(Value * OtherValue); }

	inline FInt32Struct operator/(const FInt32Struct& Other) const { return FInt32Struct(Value / Other.Value); }

	inline FInt32Struct operator/(const int32 OtherValue) const { return FInt32Struct(Value / OtherValue); }

	inline FInt32Struct operator%(const FInt32Struct& Other) const { return FInt32Struct(Value % Other.Value); }

	inline FInt32Struct operator%(const int32 OtherValue) const { return FInt32Struct(Value % OtherValue); }

	inline FInt32Struct operator<<(const FInt32Struct& Other) const { return FInt32Struct(Value << Other.Value); }

	inline FInt32Struct operator<<(const int32 OtherValue) const { return FInt32Struct(Value << OtherValue); }

	inline FInt32Struct operator>>(const FInt32Struct& Other) const { return FInt32Struct(Value >> Other.Value); }

	inline FInt32Struct operator>>(const int32 OtherValue) const { return FInt32Struct(Value >> OtherValue); }

	inline FInt32Struct operator&(const FInt32Struct& Other) const { return FInt32Struct(Value & Other.Value); }

	inline FInt32Struct operator&(const int32 OtherValue) const { return FInt32Struct(Value & OtherValue); }

	inline FInt32Struct operator|(const FInt32Struct& Other) const { return FInt32Struct(Value | Other.Value); }

	inline FInt32Struct operator|(const int32 OtherValue) const { return FInt32Struct(Value | OtherValue); }

	inline FInt32Struct operator^(const FInt32Struct& Other) const { return FInt32Struct(Value ^ Other.Value); }

	inline FInt32Struct operator^(const int32 OtherValue) const { return FInt32Struct(Value ^ OtherValue); }

	inline FInt32Struct operator~() const { return FInt32Struct(~Value); }

	inline FInt32Struct& operator+=(const FInt32Struct& Other) {
		Value += Other.Value;
		return *this;
	}

	inline FInt32Struct& operator+=(const int32 OtherValue) {
		Value += OtherValue;
		return *this;
	}

	inline FInt32Struct& operator-=(const FInt32Struct& Other) {
		Value -= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator-=(const int32 OtherValue) {
		Value -= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator*=(const FInt32Struct& Other) {
		Value *= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator*=(const int32 OtherValue) {
		Value *= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator/=(const FInt32Struct& Other) {
		Value /= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator/=(const int32 OtherValue) {
		Value /= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator%=(const FInt32Struct& Other) {
		Value %= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator%=(const int32 OtherValue) {
		Value %= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator<<=(const FInt32Struct& Other) {
		Value <<= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator<<=(const int32 OtherValue) {
		Value <<= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator>>=(const FInt32Struct& Other) {
		Value >>= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator>>=(const int32 OtherValue) {
		Value >>= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator&=(const FInt32Struct& Other) {
		Value &= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator&=(const int32 OtherValue) {
		Value &= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator|=(const FInt32Struct& Other) {
		Value |= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator|=(const int32 OtherValue) {
		Value |= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator^=(const FInt32Struct& Other) {
		Value ^= Other.Value;
		return *this;
	}

	inline FInt32Struct& operator^=(const int32 OtherValue) {
		Value ^= OtherValue;
		return *this;
	}

	inline FInt32Struct& operator++() {
		++Value;
		return *this;
	}

	inline FInt32Struct& operator--() {
		--Value;
		return *this;
	}

	inline FInt32Struct operator++(int) {
		FInt32Struct Temp = *this;
		++Value;
		return Temp;
	}

	inline FInt32Struct operator--(int) {
		FInt32Struct Temp = *this;
		--Value;
		return Temp;
	}

	operator bool() const { return Value != 0; }

	operator int32() const { return Value; }

	inline int32 Get() const { return Value; }

	inline FInt32Struct& Set(int32 NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "Float Struct"))
struct FIRSTPERSONSHOOTER_API FFloatStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Value = 0.0f;

	FFloatStruct() = default;

	FFloatStruct(const FFloatStruct& Other) : Value(Other.Value) {}

	FFloatStruct(float InValue) : Value(InValue) { }

	inline FFloatStruct& operator=(const FFloatStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FFloatStruct& operator=(float OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline bool operator==(const FFloatStruct& Other) const { return Value == Other.Value; }

	inline bool operator==(const float OtherValue) const { return Value == OtherValue; }

	inline bool operator!=(const FFloatStruct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const float OtherValue) const { return Value != OtherValue; }

	inline bool operator<(const FFloatStruct& Other) const { return Value < Other.Value; }

	inline bool operator<(const float OtherValue) const { return Value < OtherValue; }

	inline bool operator<=(const FFloatStruct& Other) const { return Value <= Other.Value; }

	inline bool operator<=(const float OtherValue) const { return Value <= OtherValue; }

	inline bool operator>(const FFloatStruct& Other) const { return Value > Other.Value; }

	inline bool operator>(const float OtherValue) const { return Value > OtherValue; }

	inline bool operator>=(const FFloatStruct& Other) const { return Value >= Other.Value; }

	inline bool operator>=(const float OtherValue) const { return Value >= OtherValue; }

	inline FFloatStruct operator+(const FFloatStruct& Other) const { return FFloatStruct(Value + Other.Value); }

	inline FFloatStruct operator+(const float OtherValue) const { return FFloatStruct(Value + OtherValue); }

	inline FFloatStruct operator-(const FFloatStruct& Other) const { return FFloatStruct(Value - Other.Value); }

	inline FFloatStruct operator-(const float OtherValue) const { return FFloatStruct(Value - OtherValue); }

	inline FFloatStruct operator*(const FFloatStruct& Other) const { return FFloatStruct(Value * Other.Value); }

	inline FFloatStruct operator*(const float OtherValue) const { return FFloatStruct(Value * OtherValue); }

	inline FFloatStruct operator/(const FFloatStruct& Other) const { return FFloatStruct(Value / Other.Value); }

	inline FFloatStruct operator/(const float OtherValue) const { return FFloatStruct(Value / OtherValue); }

	inline FFloatStruct& operator+=(const FFloatStruct& Other) {
        Value += Other.Value;
        return *this;
    }

	inline FFloatStruct& operator+=(const float OtherValue) {
		Value += OtherValue;
		return *this;
	}

	inline FFloatStruct& operator-=(const FFloatStruct& Other) {
		Value -= Other.Value;
		return *this;
	}

	inline FFloatStruct& operator-=(const float OtherValue) {
		Value -= OtherValue;
		return *this;
	}

	inline FFloatStruct& operator*=(const FFloatStruct& Other) {
		Value *= Other.Value;
		return *this;
	}

	inline FFloatStruct& operator*=(const float OtherValue) {
		Value *= OtherValue;
		return *this;
	}

	inline FFloatStruct& operator/=(const FFloatStruct& Other) {
		Value /= Other.Value;
		return *this;
	}

	inline FFloatStruct& operator/=(const float OtherValue) {
		Value /= OtherValue;
		return *this;
	}

	operator bool() const { return Value != 0.0f; }

	operator float() const { return Value; }

	inline float Get() const { return Value; }

	inline FFloatStruct& Set(float NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "Boolean Struct"))
struct FIRSTPERSONSHOOTER_API FBoolStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool Value = false;

	FBoolStruct() = default;

	FBoolStruct(const FBoolStruct& Other) : Value(Other.Value) {}

	FBoolStruct(bool InValue) : Value(InValue) {}

	inline FBoolStruct& operator=(const FBoolStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FBoolStruct& operator=(bool OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline bool operator==(const FBoolStruct& Other) const { return Value == Other.Value; }

	inline bool operator==(const bool OtherValue) const { return Value == OtherValue; }

	inline bool operator!=(const FBoolStruct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const bool OtherValue) const { return Value != OtherValue; }

	inline FBoolStruct& operator&=(const FBoolStruct& Other) {
		Value &= Other.Value;
		return *this;
	}

	inline FBoolStruct& operator&=(const bool OtherValue) {
		Value &= OtherValue;
		return *this;
	}

	inline FBoolStruct& operator|=(const FBoolStruct& Other) {
		Value |= Other.Value;
		return *this;
	}

	inline FBoolStruct& operator|=(const bool OtherValue) {
		Value |= OtherValue;
		return *this;
	}

	operator bool() const { return Value; }

	inline bool Get() const { return Value; }

	inline FBoolStruct& Set(bool NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "String Struct"))
struct FIRSTPERSONSHOOTER_API FStringStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FString Value = "";

	FStringStruct() = default;

	FStringStruct(const FStringStruct& Other) : Value(Other.Value) { }

	FStringStruct(const FString& InValue) : Value(InValue) { }

	FStringStruct(const char* InString) : Value(InString) { }

	FStringStruct(char* InString) : Value(InString) {}

	inline FStringStruct& operator=(const FStringStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FStringStruct& operator=(const FString& OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline FStringStruct& operator=(const char* OtherString) {
		Value = OtherString;
		return *this;
	}

	inline FStringStruct& operator=(char* OtherString) {
		Value = OtherString;
		return *this;
	}

	inline bool operator==(const FStringStruct& Other) const { return Value == Other.Value; }

	inline bool operator==(const FString& OtherValue) const { return Value == OtherValue; }

	inline bool operator==(const char* OtherString) const { return Value == OtherString; }

	inline bool operator==(char* OtherString) const { return Value == OtherString; }

	inline bool operator!=(const FStringStruct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const FString& OtherValue) const { return Value != OtherValue; }

	inline bool operator!=(const char* OtherString) const { return Value != OtherString; }

	inline bool operator!=(char* OtherString) const { return Value != OtherString; }

	inline FStringStruct operator+(const FStringStruct& Other) const { return FStringStruct(Value + Other.Value); }

	inline FStringStruct operator+(const FString& OtherValue) const { return FStringStruct(Value + OtherValue); }

	inline FStringStruct operator+(const char* OtherString) const { return FStringStruct(Value + OtherString); }

	inline FStringStruct operator+(char* OtherString) const { return FStringStruct(Value + OtherString); }

	inline FStringStruct& operator+=(const FStringStruct& Other) {
		Value += Other.Value;
		return *this;
	}

	inline FStringStruct& operator+=(const FString& OtherValue) {
		Value += OtherValue;
		return *this;
	}

	inline FStringStruct& operator+=(const char* OtherString) {
		Value += OtherString;
		return *this;
	}

	inline FStringStruct& operator+=(char* OtherString) {
		Value += OtherString;
		return *this;
	}

	operator FString() const { return Value; }

	inline FStringStruct& Append(const FStringStruct& Other) {
		Value.Append(Other.Value);
		return *this;
	}

	inline FStringStruct& Append(const FString& OtherValue) {
		Value.Append(OtherValue);
		return *this;
	}

	inline FStringStruct& Append(const char* OtherString) {
		Value.Append(OtherString);
		return *this;
	}

	inline FStringStruct& Append(char* OtherString) {
		Value.Append(OtherString);
		return *this;
	}

	inline bool Equals(const FStringStruct& Other, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const { return Value.Equals(Other.Value, SearchCase); }

	inline bool Equals(const FString& OtherValue, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const { return Value.Equals(OtherValue, SearchCase); }

	inline bool Equals(const char* OtherString, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const { return Value.Equals(OtherString, SearchCase); }

	inline bool Equals(char* OtherString, ESearchCase::Type SearchCase = ESearchCase::CaseSensitive) const { return Value.Equals(OtherString, SearchCase); }

	inline FString Get() const { return Value; }

	inline FStringStruct& Set(FString NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "Name Struct"))
struct FIRSTPERSONSHOOTER_API FNameStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Value = "";

	FNameStruct() = default;

	FNameStruct(const FNameStruct& Other) : Value(Other.Value) {}

	FNameStruct(const FName& InValue) : Value(InValue) {}

	FNameStruct(const FString& InString) : Value(InString) {}

	FNameStruct(const char* InString) : Value(InString) {}

	FNameStruct(char* InString) : Value(InString) {}

	inline FNameStruct& operator=(const FNameStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FNameStruct& operator=(const FName& OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline FNameStruct& operator=(const char* OtherString) {
		Value = OtherString;
		return *this;
	}

	inline FNameStruct& operator=(char* OtherString) {
		Value = OtherString;
		return *this;
	}

	inline bool operator==(const FNameStruct& Other) const { return Value == Other.Value; }

	inline bool operator==(const FName& OtherValue) const { return Value == OtherValue; }

	inline bool operator==(const FString& OtherString) const { return Value == OtherString; }

	inline bool operator==(const char* OtherString) const { return Value == OtherString; }

	inline bool operator==(char* OtherString) const { return Value == OtherString; }

	inline bool operator!=(const FNameStruct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const FName& OtherValue) const { return Value != OtherValue; }

	inline bool operator!=(const FString& OtherString) const { return Value != OtherString; }

	inline bool operator!=(const char* OtherString) const { return Value != OtherString; }

	inline bool operator!=(char* OtherString) const { return Value != OtherString; }

	operator FName() const { return Value; }

	inline FString ToString() const { return Value.ToString(); }

	inline FStringStruct ToStringStruct() const { return FStringStruct(Value.ToString()); }

	inline FName Get() const { return Value; }

	inline FNameStruct& Set(FName NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "Text Struct"))
struct FIRSTPERSONSHOOTER_API FTextStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FText Value = FText::FromString("");

	FTextStruct() = default;

	FTextStruct(const FTextStruct& Other) : Value(Other.Value) {}

	FTextStruct(const FText& InValue) : Value(InValue) {}

	FTextStruct(const FString& InString) : Value(FText::FromString(InString)) {}

	FTextStruct(const FName& InName) : Value(FText::FromName(InName)) {}

	FTextStruct(const char* InString) : Value(FText::FromString(InString)) {}

	FTextStruct(char* InString) : Value(FText::FromString(InString)) {}

	inline FTextStruct& operator=(const FTextStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FTextStruct& operator=(const FText& OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline FTextStruct& operator=(const FString& OtherString) {
		Value = FText::FromString(OtherString);
		return *this;
	}

	inline FTextStruct& operator=(const FName& OtherName) {
		Value = FText::FromName(OtherName);
		return *this;
	}

	inline FTextStruct& operator=(const char* OtherString) {
		Value = FText::FromString(OtherString);
		return *this;
	}

	inline FTextStruct& operator=(char* OtherString) {
		Value = FText::FromString(OtherString);
		return *this;
	}

	operator FText() const { return Value; }

	inline FTextStruct FromeName(const FNameStruct& InName) const { return FTextStruct(FText::FromName(InName.Value)); }

	inline FTextStruct FromeName(const FName& InName) const { return FTextStruct(FText::FromName(InName)); }

	inline FTextStruct FromString(const FStringStruct& InString) const { return FTextStruct(FText::FromString(InString.Value)); };

	inline FTextStruct FromString(const FString& InString) const { return FTextStruct(FText::FromString(InString)); };

	inline FTextStruct FromString(const char* InString) const { return FTextStruct(FText::FromString(InString)); };

	inline FTextStruct FromString(char* InString) const { return FTextStruct(FText::FromString(InString)); };

	inline FString ToString() const { return Value.ToString(); }

	inline FStringStruct ToStringStruct() const { return FStringStruct(Value.ToString()); }

	inline FText Get() const { return Value; }

	inline FTextStruct& Set(FText NewValue) {
		Value = NewValue;
		return *this;
	}
};

USTRUCT(BlueprintType, meta = (DisplayName = "Object Struct"))
struct FIRSTPERSONSHOOTER_API FUObjectStruct {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UObject> Value = nullptr;

	FUObjectStruct() = default;

	FUObjectStruct(const FUObjectStruct& Other) : Value(Other.Value) { }

	FUObjectStruct(TObjectPtr<UObject> InValue) : Value(InValue) { }

	FUObjectStruct(UObject* InValue) : Value(InValue) { }

	inline FUObjectStruct& operator=(const FUObjectStruct& Other) {
		Value = Other.Value;
		return *this;
	}

	inline FUObjectStruct& operator=(TObjectPtr<UObject> OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline FUObjectStruct& operator=(UObject* OtherValue) {
		Value = OtherValue;
		return *this;
	}

	inline bool operator==(const FUObjectStruct& Other) const { return Value == Other.Value; }

	inline bool operator==(const TObjectPtr<UObject> OtherValue) const { return Value == OtherValue; }

	inline bool operator==(const UObject* OtherValue) const { return Value == OtherValue; }

	inline bool operator!=(const FUObjectStruct& Other) const { return Value != Other.Value; }

	inline bool operator!=(const TObjectPtr<UObject> OtherValue) const { return Value != OtherValue; }

	inline bool operator!=(const UObject* OtherValue) const { return Value != OtherValue; }

	operator bool() const { return Value != nullptr; }

	operator UObject* () const { return Value; }

	template<typename T>
	inline T* CastAs() const {
		static_assert(TIsDerivedFrom<T, UObject>::IsDerived, "FUObjectStruct::CastAs() can only be used with UObject-derived types");
		return Cast<T>(Value);
	}

	template<typename T>
	inline bool IsA() const {
		static_assert(TIsDerivedFrom<T, UObject>::IsDerived, "FUObjectStruct::IsA() can only be used with UObject-derived types");
		return Value != nullptr && Value->IsA(T::StaticClass());
	}

	inline bool IsA(const UObject* SomeObject) const { return Value != nullptr && Value->IsA(SomeObject->StaticClass()); }

	inline bool IsA(const UClass* SomeBase) const { return Value != nullptr && Value->IsA(SomeBase); }

	inline UObject* Get() const { return Value; }

	inline FUObjectStruct& Set(UObject* NewValue) {
		Value = NewValue;
		return *this;
	}

	inline void Clear() { Value = nullptr; }
};