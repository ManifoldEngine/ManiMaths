#pragma once

#include <type_traits>

namespace Mani
{
	template<typename T>
	concept is_numeric = std::is_arithmetic<T>::value;
}