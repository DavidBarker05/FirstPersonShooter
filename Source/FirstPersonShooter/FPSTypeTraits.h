#pragma once

#include "CoreMinimal.h"

template<typename T>
constexpr bool TIsPointer_V = false;

template<typename T>
constexpr bool TIsPointer_V<T*> = true;

template<typename T>
constexpr bool TIsPointer_V<const T> = TIsPointer_V<T>;

template<typename T>
constexpr bool TIsPointer_V<volatile T> = TIsPointer_V<T>;

template<typename T>
constexpr bool TIsPointer_V<const volatile T> = TIsPointer_V<T>;

template<typename, typename>
constexpr bool TIsSame_V = false;

template<typename T>
constexpr bool TIsSame_V<T, T> = true;

template<typename T1, typename T2>
constexpr bool TIsDerivedFrom_V = TIsDerivedFrom<T1, T2>::Value;

template<typename T>
using TDecay_T = TDecay<T>::Type;

template<typename T>
using TRemoveObjectPointer_T = TRemoveObjectPointer<T>::Type;

template<typename T>
using TRemovePointer_T = TRemovePointer<T>::Type;
