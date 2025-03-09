#pragma once

#include "Traits.h"
#include "Quaternion.h"
#include "Vector.h"
#include "Maths.h"

namespace Mani
{
	template<IsNumeric T>
	[[nodiscard]] Vec3<T> convert(const Quat<T>& q) { return { q.x, q.y, q.z }; }

	// https://raw.org/proof/vector-rotation-using-quaternions/
	template<IsNumeric T1, IsNumeric T2 = T1, IsNumeric TReturn = T1>
	[[nodiscard]] Vec3<TReturn> rotate(const Quat<T1>& q, const Vec3<T2>& v)
	{
		constexpr T1 _2 = static_cast<T1>(2);

		// t = 2q x v
		const Vec3<T1> t = {
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
	[[nodiscard]] Quat<T> fromAxisAngleRad(T angle, Vec3<T> axis)
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
	[[nodiscard]] Quat<T> fromAxisAngleDeg(T angle , Vec3<T> axis)
	{
		return fromAxisAngleRad<T>(degToRad(angle), axis);
	}
}