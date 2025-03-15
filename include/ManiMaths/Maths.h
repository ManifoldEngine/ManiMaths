#pragma once

#include "Traits.h"
#include <cmath>

namespace Mani
{
	namespace Math
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
		[[nodiscard]] T tan(T v)
		{
			return std::tan(v);
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
		[[nodiscard]] T atan(T v)
		{
			return std::atan(v);
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

		template <IsNumeric T1>
		[[nodiscard]] constexpr T1 min(T1 lhs, T1 rhs)
		{
			return lhs <= rhs ? lhs : rhs;
		}

		template <IsNumeric T1>
		[[nodiscard]] constexpr T1 max(T1 lhs, T1 rhs)
		{
			return lhs >= rhs ? lhs : rhs;
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
			constexpr T pi_over_180 = pi / _180;
			return v * pi_over_180;
		}

		template<IsNumeric T>
		[[nodiscard]] T radToDeg(T v)
		{
			constexpr T pi = static_cast<T>(PId);
			constexpr T _180 = static_cast<T>(180);
			constexpr T _180_over_pi = _180 / pi;
			return v * _180_over_pi;
		}
	}
}