#pragma once

#include "Traits.h"

namespace Mani
{
	constexpr double PId = 3.141592653589793238462643383279502884L;
	constexpr float PIf = static_cast<float>(PId);

	template<IsNumeric T>
	[[nodiscard]] T abs(T v)
	{
		return std::abs(v);
	}

	template<IsNumeric T>
	[[nodiscard]] T cos(T v)
	{
		return std::cos(v);
	}

	template<IsNumeric T>
	[[nodiscard]] T sin(T v)
	{
		return std::sin(v);
	}

	template<IsNumeric T>
	[[nodiscard]] T acos(T v)
	{
		return std::acos(v);
	}

	template<IsNumeric T>
	[[nodiscard]] T asin(T v)
	{
		return std::asin(v);
	}

	template<IsNumeric T>
	[[nodiscard]] T sqrt(T v)
	{
		return std::sqrt(v);
	}

	template<IsNumeric T1, IsInteger T2>
	[[nodiscard]] T1 pow(T1 v, T2 p)
	{
		return std::pow(v, p);
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric T3 = float>
	[[nodiscard]] bool isEqual(T1 v1, T2 v2, T3 tolerance = FLT_EPSILON)
	{
		return abs(v2 - v1) < tolerance;
	}

	template<IsNumeric T>
	[[nodiscard]] T degToRad(T v)
	{
		constexpr T pi = static_cast<T>(PId);
		constexpr T _180 = static_cast<T>(180);
		return v * (pi / _180);
	}

	template<IsNumeric T>
	[[nodiscard]] T radToDeg(T v)
	{
		constexpr T pi = static_cast<T>(PId);
		constexpr T _180 = static_cast<T>(180);
		return v * (_180 / pi);
	}
}