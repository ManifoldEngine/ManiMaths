#pragma once

#include "Traits.h"
#include <cmath>

namespace Mani
{
	template<IsNumericType T>
	struct Quat
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);
		T w = static_cast<T>(0);

		template<IsNumericType T1, IsNumericType T2>
		static bool isNearlyEqual(const Quat<T1>& lhs, const Quat<T2> rhs, double tolerance = FLT_EPSILON)
		{
			return	std::abs(lhs.x - rhs.x) <= tolerance &&
				std::abs(lhs.y - rhs.y) <= tolerance &&
				std::abs(lhs.z - rhs.z) <= tolerance &&
				std::abs(lhs.w - rhs.w) <= tolerance;
		}

		template<IsNumericType T2>
		bool isNearlyEqual(const Quat<T2>& rhs, double tolerance = FLT_EPSILON)
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}
	};

	typedef Quat<float> Quatf;
	typedef Quat<double> Quatd;

	template<IsNumericType T1, IsNumericType T2>
	bool operator==(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	template<IsNumericType T1, IsNumericType T2>
	bool operator!=(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
	}

	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Quat<TReturn> operator+(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			lhs.w + rhs.w
		};
	}

	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Quat<TReturn> operator-(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			lhs.w - rhs.w
		};
	}

	// Hamilton product
	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Quat<TReturn> operator*(const Quat<T1>& lhs, const Quat<T2> rhs)
	{
		return {
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
		};
	}
}