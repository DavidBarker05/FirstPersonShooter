#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "EventData.generated.h"

USTRUCT(BlueprintType)
struct FIRSTPERSONSHOOTER_API FEventData {
	GENERATED_BODY()
	public:
		FInstancedStruct Data;

	public:
		FEventData() = default;

		template<typename T>
		FEventData(T&& InData) {
			Data.InitializeAs<T>();
			*Data.GetMutable<T>() = Forward<T>(InData);
		}

	public:
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
