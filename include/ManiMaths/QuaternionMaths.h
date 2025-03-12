#pragma once

#include "Traits.h"
#include "Quat.h"
#include "Vec3.h"
#include "Maths.h"

namespace Mani
{
	// https://raw.org/proof/vector-rotation-using-quaternions/
	template<IsNumeric T1, IsNumeric T2 = T1, IsNumeric TReturn = T1>
	[[nodiscard]] Vec<TReturn, 3> rotate(const Quat<T1>& q, const Vec<T2, 3>& v)
	{
		constexpr T1 _2 = static_cast<T1>(2);

		// t = 2q x v
		const Vec<T1, 3> t = {
			_2 * (q.y * v.z - q.z * v.y),
			_2 * (q.z * v.x - q.x * v.z),
			_2 * (q.x * v.y - q.y * v.x)
		};
		
		// v + w t + q x t
		return {
			v.x + q.w * t.x + q.y * t.z - q.z * t.y,
			v.y + q.w * t.y + q.z * t.x - q.x * t.z,
			v.z + q.w * t.z + q.x * t.y - q.y * t.x,
		};
	}

	template<IsNumeric T>
	[[nodiscard]] Quat<T> fromAxisAngleRad(T angle, Vec<T, 3> axis)
	{
		constexpr T _2 = 2;
		const T cosHalfAngle = cos(angle / _2);
		const T sinHalfAngle = sin(angle / _2);

		return {
			sinHalfAngle * axis.x,
			sinHalfAngle * axis.y,
			sinHalfAngle * axis.z,
			cosHalfAngle
		};
	}

	template<IsNumeric T>
	[[nodiscard]] Quat<T> fromAxisAngleDeg(T angle , Vec<T, 3> axis)
	{
		return fromAxisAngleRad<T>(degToRad(angle), axis);
	}
}