#pragma once

#include <type_traits>

namespace Mani
{
	template<typename T>
	concept IsNumericType = std::is_arithmetic<T>::value;
}