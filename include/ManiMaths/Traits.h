#pragma once

#include <type_traits>

namespace Mani
{
	template<typename T>
	concept IsNumeric = std::is_arithmetic<T>::value;

	template<typename T>
	concept IsInteger = std::is_integral<T>::value;

	template<typename T>
	concept IsUnsignedInteger = std::is_integral<T>::value && std::is_unsigned<T>::value;

	template<typename T>
	concept Is8BytesType = (sizeof(T) == 8);

	template<typename T>
	concept Is4BytesType = (sizeof(T) == 4);
}