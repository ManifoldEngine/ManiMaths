#pragma once

#include "Traits.h"
#include <cmath>

namespace Mani
{
	template<is_numeric T>
	struct Quat
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);
		T w = static_cast<T>(0);
	};

	typedef Quat<float> Quatf;
	typedef Quat<double> Quatd;

	template<is_numeric T1, is_numeric T2>
	bool operator==(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	template<is_numeric T1, is_numeric T2>
	bool operator!=(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
	}
}