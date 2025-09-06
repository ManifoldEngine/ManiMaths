#pragma once

#include "_Vec.h"
#include "Debug.h"
#include "Traits.h"
#include "ManiMaths/Maths.h"
#include <format>

namespace Mani
{
	template<IsNumeric T>
	struct Vec<T, 3>
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static bool isNearlyEqual(const Vec<T1, 3>& lhs, const Vec<T2, 3> rhs, double tolerance = FLT_EPSILON)
		{
			return	abs(lhs.x - rhs.x) <= tolerance &&
					abs(lhs.y - rhs.y) <= tolerance &&
					abs(lhs.z - rhs.z) <= tolerance;
		}

		template<IsNumeric T2>
		[[nodiscard]] bool isNearlyEqual(const Vec<T2, 3>& rhs, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}

		[[nodiscard]] T length() const
		{
			return sqrt(x * x + y * y + z * z);
		}

		[[nodiscard]] T lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		[[nodiscard]] Vec<T, 3> normalize() const
		{
			constexpr T _1 = static_cast<T>(1);
			T l = length();
			if (l > 0)
			{
				return *this * (_1 / l);	
			}
			return *this;
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T distance(const Vec<T1, 3>& v1, const Vec<T2, 3>& v2)
		{
			return sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z));
		}

		template<IsNumeric T2>
		[[nodiscard]] T distance(const Vec<T2, 3>& other) const
		{
			return distance(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T distanceSquared(const Vec<T1, 3>& v1, const Vec<T2, 3>& v2)
		{
			return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z);
		}

		template<IsNumeric T2>
		[[nodiscard]] T distanceSquared(const Vec<T2, 3>& other) const
		{
			return distanceSquared(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T dot(const Vec<T1, 3>& v1, const Vec<T2, 3>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
		}

		template<IsNumeric T2>
		[[nodiscard]] T dot(const Vec<T2, 3>& other) const
		{
			return dot(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
		[[nodiscard]] static Vec<TReturn, 3> cross(const Vec<T1, 3>& v1, const Vec<T2, 3>& v2)
		{
			return {
				v1.y * v2.z - v2.y * v1.z,
				v1.z * v2.x - v2.z * v1.x,
				v1.x * v2.y - v2.x * v1.y
			};
		}

		template<IsNumeric T2>
		[[nodiscard]] Vec<T, 3> cross(const Vec<T2, 3>& other) const
		{
			return cross(*this, other);
		}

		[[nodiscard]] static Vec<T, 3> clamp(const Vec<T, 3>& v, T target)
		{
			if (v.length() > target)
			{
				return v.normalize() * target;
			}
			return v;
		}

		[[nodiscard]] Vec<T, 3> clamp(T target) const
		{
			return clamp(*this, target);
		}

		template<IsNumeric T>
		[[nodiscard]] static Vec<T, 3> sphericalRandom(T radius)
		{
			constexpr T _2PI = static_cast<T>(Math::PId * 2);
			constexpr T _0 = static_cast<T>(0);
			constexpr T __1 = static_cast<T>(-1);
			constexpr T _1 = static_cast<T>(1);
			
			MANIMATHS_ASSERT(radius > _0);

			const float theta = Math::linearRand(_0, _2PI);
			const float phi = Math::acos(Math::linearRand(__1, _1));

			const Vec<T, 3> v = {
				Math::sin(phi) * Math::cos(theta),
				Math::sin(phi) * Math::sin(theta),
				Math::cos(phi),
			};
			return v * radius;
		}

		operator Vec<T, 2>() const { return { x, y }; }
		operator Vec<T, 4>() const { return { x, y, z, static_cast<T>(0) }; }
		Vec<T, 4> homogenous() const { return { x, y, z, static_cast<T>(1) }; }

		[[nodiscard]] std::string toString() const
		{
			return std::format("({}, {}, {})", x, y, z);
		}	
	};

	typedef Vec<int,			3> Vec3i;
	typedef Vec<long,			3> Vec3l;
	typedef Vec<float,			3> Vec3f;
	typedef Vec<double,			3> Vec3d;
	typedef Vec<unsigned int,	3> Vec3ui;
	typedef Vec<unsigned long,	3> Vec3ul;

	template<IsNumeric T1, IsNumeric T2>
	bool operator==(const Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2>
	bool operator!=(const Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 3> operator+(const Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		return { 
			lhs.x + rhs.x, 
			lhs.y + rhs.y, 
			lhs.z + rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 3> operator-(const Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		return { 
			lhs.x - rhs.x, 
			lhs.y - rhs.y, 
			lhs.z - rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 3> operator*(const Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		return { 
			lhs.x * rhs.x, 
			lhs.y * rhs.y, 
			lhs.z * rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator+=(Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;		
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator-=(Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator*=(Vec<T1, 3>& lhs, const Vec<T2, 3>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 3> operator*(const Vec<T, 3>& lhs, TScale scale)
	{
		return {
			lhs.x * scale,
			lhs.y * scale,
			lhs.z * scale,
		};
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 3> operator*(TScale scale, const Vec<T, 3>& rhs)
	{
		return {
			rhs.x * scale,
			rhs.y * scale,
			rhs.z * scale,
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator*=(Vec<T, 3>& lhs, TScale scale)
	{
		lhs.x *= scale;
		lhs.y *= scale;
		lhs.z *= scale;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 3> operator/(const Vec<T, 3>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(abs(scale) > 0);
		return {
			lhs.x / scale,
			lhs.y / scale,
			lhs.z / scale,
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator/=(Vec<T, 3>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(abs(scale) > 0);
		lhs.x /= scale;
		lhs.y /= scale;
		lhs.z /= scale;
	}
}