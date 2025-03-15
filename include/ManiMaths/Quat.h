#pragma once

#include "_Vec.h"
#include "_Mat.h"
#include "Debug.h"
#include "Traits.h"
#include "Maths.h"

namespace Mani
{
	template<IsNumeric T>
	struct Quat
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);
		T w = static_cast<T>(1);

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static bool isNearlyEqual(const Quat<T1>& lhs, const Quat<T2> rhs, double tolerance = FLT_EPSILON)
		{
			return	abs(lhs.x - rhs.x) <= tolerance &&
					abs(lhs.y - rhs.y) <= tolerance &&
					abs(lhs.z - rhs.z) <= tolerance &&
					abs(lhs.w - rhs.w) <= tolerance;
		}

		template<IsNumeric T2>
		[[nodiscard]] bool isNearlyEqual(const Quat<T2>& rhs, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}

		[[nodiscard]] Quat<T> conjugate() const
		{
			return { -x, -y, -z, w };
		}

		[[nodiscard]] T length() const
		{
			return std::sqrt(x * x + y * y + z * z + w * w);
		}

		[[nodiscard]] T lengthSquared() const
		{
			return x * x + y * y + z * z + w * w;
		}

		[[nodiscard]] Quat<T> normalize() const
		{
			constexpr T _1 = static_cast<T>(1);
			const float l = length();
			if (l > 0)
			{
				return *this * (_1 / l);
			}
			return *this;
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T dot(const Quat<T1>& q1, const Quat<T2>& q2)
		{
			return	q1.x * q2.x +
					q1.y * q2.y +
					q1.z * q2.z + 
					q1.w * q2.w;
		}

		template<IsNumeric T2>
		[[nodiscard]] T dot(const Quat<T2>& other) const
		{
			return dot(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T angleRad(const Quat<T1>& q1, const Quat<T2>& q2)
		{
			constexpr T _2 = static_cast<T>(2);
			const T1 q1Length = q1.length();
			const T2 q2Length = q2.length();
			MANIMATHS_ASSERT(abs(q1Length) > 0 && abs(q2Length) > 0);
			return _2 * acos(dot(q1, q2) / (q1Length * q2Length));
		}

		template<IsNumeric T2>
		[[nodiscard]] T angleRad(const Quat<T2>& other) const
		{
			return angleRad(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T angleDeg(const Quat<T1>& q1, const Quat<T2>& q2)
		{
			return Mani::radToDeg(angleRad(q1, q2));
		}

		template<IsNumeric T2>
		[[nodiscard]] T angleDeg(const Quat<T2>& other) const
		{
			return Mani::radToDeg(angleRad(*this, other));
		}

		[[nodiscard]] static Quat<T> axisAngle(T angle, Vec<T, 3> axis)
		{
			constexpr T _0_5 = static_cast<T>(0.5);
			const T sinHalfAngle = sin(angle * _0_5);
			const T cosHalfAngle = cos(angle * _0_5);
			return {
				axis.x * sinHalfAngle,
				axis.y * sinHalfAngle,
				axis.z * sinHalfAngle,
				cosHalfAngle,
			};
		}

		[[nodiscard]] static Quat<T> axisAngleDeg(T angle, Vec<T, 3> axis)
		{
			return axisAngle(degToRad(angle), axis);
		}

		// https://raw.org/proof/vector-rotation-using-quaternions/
		[[nodiscard]] static Vec<T, 3> rotate(const Quat<T>& q, const Vec<T, 3>& v)
		{
			constexpr T _2 = static_cast<T>(2);

			// t = 2q x v
			const Vec<T, 3> t = {
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

		[[nodiscard]] Vec<T, 3> rotate(const Vec<T, 3>& v) const
		{
			return rotate(*this, v);
		}
				
		template<IsNumeric TTime>
		[[nodiscard]] static Quat<T> slerp(const Quat<T>& q1, const Quat<T>& q2, TTime t)
		{
			constexpr T _1		= static_cast<T>(1);
			constexpr T _0_001	= static_cast<T>(0.001);
			constexpr T _0_5	= static_cast<T>(0.5);

			const T cosHalfTheta = dot(q1, q2);
			if (abs(cosHalfTheta) >= _1)
			{
				return q1;
			}

			const T sinHalfTheta = sqrt(_1 - cosHalfTheta * cosHalfTheta);
			if (abs(sinHalfTheta) < _0_001)
			{
				// result is not fully defined
				return q1 * _0_5 + q2 * _0_5;
			}

			const T halfTheta = acos(cosHalfTheta);

			const T ta = sin((_1 - t) * halfTheta) / sinHalfTheta;
			const T tb = sin(t * halfTheta) / sinHalfTheta;

			return q1 * ta + q2 * tb;
		}

		operator Vec<T, 3>() const { return { x, y, z }; }
		operator Vec<T, 4>() const { return { x, y, z, w }; }

		operator Mat<T, 3, 3>() const
		{
			constexpr T _1 = static_cast<T>(1);
			constexpr T _2 = static_cast<T>(2);

			const T qxx = x * x;
			const T qyy = y * y;
			const T qzz = z * z;
			const T qxz = x * z;
			const T qxy = x * y;
			const T qyz = y * z;
			const T qwx = w * x;
			const T qwy = w * y;
			const T qwz = w * z;

			return {
				_1 - _2 * (qyy + qzz), _2 * (qxy + qwz), _2 * (qxz - qwy),
				_2 * (qxy - qwz), _1 - _2 * (qxx + qzz), _2 * (qyz + qwx),
				_2 * (qxz + qwy), _2 * (qyz - qwx), _1 - _2 * (qxx + qyy),
			};
		}

		operator Mat<T, 4, 4>() const
		{
			return static_cast<Mat<T, 3, 3>>(*this);
		}

		[[nodiscard]] std::string toString() const
		{
			return std::format("({}, {}, {}, {})", x, y, z, w);
		}
	};

	typedef Quat<float> Quatf;
	typedef Quat<double> Quatd;

	template<IsNumeric T>
	[[nodiscard]] Mat<T, 3, 3> toMat3(const Quat<T>& q)
	{
		return static_cast<Mat<T, 3, 3>>(q);
	}

	template<IsNumeric T>
	[[nodiscard]] Mat<T, 4, 4> toMat4(const Quat<T>& q)
	{
		return toMat3(q);
	}

	template<IsNumeric T1, IsNumeric T2>
	[[nodiscard]] bool operator==(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z && lhs.w == rhs.w;
	}

	template<IsNumeric T1, IsNumeric T2>
	[[nodiscard]] bool operator!=(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z || lhs.w != rhs.w;
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	[[nodiscard]] Quat<TReturn> operator+(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y,
			lhs.z + rhs.z,
			lhs.w + rhs.w
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	[[nodiscard]] Quat<TReturn> operator-(const Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y,
			lhs.z - rhs.z,
			lhs.w - rhs.w
		};
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator+=(Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;
		lhs.w += rhs.w;
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator-=(Quat<T1>& lhs, const Quat<T2>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
		lhs.w -= rhs.w;
	}

	// Hamilton product
	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	[[nodiscard]] Quat<TReturn> operator*(const Quat<T1>& lhs, const Quat<T2> rhs)
	{
		return {
			lhs.w * rhs.x + lhs.x * rhs.w + lhs.y * rhs.z - lhs.z * rhs.y,
			lhs.w * rhs.y + lhs.y * rhs.w + lhs.z * rhs.x - lhs.x * rhs.z,
			lhs.w * rhs.z + lhs.z * rhs.w + lhs.x * rhs.y - lhs.y * rhs.x,
			lhs.w * rhs.w - lhs.x * rhs.x - lhs.y * rhs.y - lhs.z * rhs.z
		};
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	[[nodiscard]] Quat<TReturn> operator*(const Quat<T>& lhs, TScale scale)
	{
		return { lhs.x * scale, lhs.y * scale, lhs.z * scale, lhs.w * scale };
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	[[nodiscard]] Quat<TReturn> operator*(TScale scale, const Quat<T>& rhs)
	{
		return { rhs.x * scale, rhs.y * scale, rhs.z * scale, rhs.w * scale };
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator*=(Quat<T>& lhs, TScale scale)
	{
		lhs.x *= scale;
		lhs.y *= scale;
		lhs.z *= scale;
		lhs.w *= scale;
	}

	namespace QUATF
	{
		constexpr Quatf IDENTITY = { 0, 0, 0, 1 };
	}

	namespace QUATD
	{
		constexpr Quatd IDENTITY = { 0, 0, 0, 1 };
	}
}
