#pragma once

#include "Debug.h"
#include "Traits.h"
#include <cmath>

namespace Mani
{
	template<IsNumeric T>
	struct Vec3
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static bool isNearlyEqual(const Vec3<T1>& lhs, const Vec3<T2> rhs, double tolerance = FLT_EPSILON)
		{
			return	std::abs(lhs.x - rhs.x) <= tolerance &&
					std::abs(lhs.y - rhs.y) <= tolerance &&
					std::abs(lhs.z - rhs.z) <= tolerance;
		}

		template<IsNumeric T2>
		[[nodiscard]] bool isNearlyEqual(const Vec3<T2>& rhs, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}

		[[nodiscard]] T length() const
		{
			return std::sqrt(x * x + y * y + z * z);
		}

		[[nodiscard]] T lengthSquared() const
		{
			return x * x + y * y + z * z;
		}

		[[nodiscard]] Vec3<T> normalize() const
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
		[[nodiscard]] static T distance(const Vec3<T1>& v1, const Vec3<T2>& v2)
		{
			return std::sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z));
		}

		template<IsNumeric T2>
		[[nodiscard]] T distance(const Vec3<T2>& other) const
		{
			return distance(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T distanceSquared(const Vec3<T1>& v1, const Vec3<T2>& v2)
		{
			return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y) + (v2.z - v1.z) * (v2.z - v1.z);
		}

		template<IsNumeric T2>
		[[nodiscard]] T distanceSquared(const Vec3<T2>& other) const
		{
			return distanceSquared(*this, other);
		}

		[[nodiscard]] std::string toString() const
		{
			return std::format("({}, {}, {})", x, y, z);
		}
	};

	typedef Vec3<int>			Vec3i;
	typedef Vec3<long>			Vec3l;
	typedef Vec3<float>			Vec3f;
	typedef Vec3<double>		Vec3d;
	typedef Vec3<unsigned int>	Vec3ui;
	typedef Vec3<unsigned long>	Vec3ul;

	template<IsNumeric T1, IsNumeric T2>
	bool operator==(const Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2>
	bool operator!=(const Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec3<TReturn> operator+(const Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		return { 
			lhs.x + rhs.x, 
			lhs.y + rhs.y, 
			lhs.z + rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec3<TReturn> operator-(const Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		return { 
			lhs.x - rhs.x, 
			lhs.y - rhs.y, 
			lhs.z - rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec3<TReturn> operator*(const Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		return { 
			lhs.x * rhs.x, 
			lhs.y * rhs.y, 
			lhs.z * rhs.z 
		};
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator+=(Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;		
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator-=(Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator*=(Vec3<T1>& lhs, const Vec3<T2>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec3<TReturn> operator*(const Vec3<T>& lhs, TScale scale)
	{
		return {
			lhs.x * scale,
			lhs.y * scale,
			lhs.z * scale,
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator*=(Vec3<T>& lhs, TScale scale)
	{
		lhs.x *= scale;
		lhs.y *= scale;
		lhs.z *= scale;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec3<TReturn> operator/(const Vec3<T>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(std::abs(scale) > 0);
		return {
			lhs.x / scale,
			lhs.y / scale,
			lhs.z / scale,
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator/=(Vec3<T>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(std::abs(scale) > 0);
		lhs.x /= scale;
		lhs.y /= scale;
		lhs.z /= scale;
	}

	namespace VEC3I
	{
		constexpr Vec3<int>			ZERO		= {  0,  0,  0 };
		constexpr Vec3<int>			ONE			= {  1,  1,  1 };
		constexpr Vec3<int>			RIGHT		= {  1,  0,  0 };
		constexpr Vec3<int>			LEFT		= { -1,  0,  0 };
		constexpr Vec3<int>			UP			= {  0,  1,  0 };
		constexpr Vec3<int>			DOWN		= {  0, -1,  0 };
		constexpr Vec3<int>			FORWARD		= {  0,  0,  1 };
		constexpr Vec3<int>			BACK		= {  0,  0, -1 };
	}

	namespace VEC3L
	{
		constexpr Vec3<long>			ZERO		= {  0,  0,  0 };
		constexpr Vec3<long>			ONE			= {  1,  1,  1 };
		constexpr Vec3<long>			RIGHT		= {  1,  0,  0 };
		constexpr Vec3<long>			LEFT		= { -1,  0,  0 };
		constexpr Vec3<long>			UP			= {  0,  1,  0 };
		constexpr Vec3<long>			DOWN		= {  0, -1,  0 };
		constexpr Vec3<long>			FORWARD		= {  0,  0,  1 };
		constexpr Vec3<long>			BACK		= {  0,  0, -1 };
	}

	namespace VEC3F
	{
		constexpr Vec3<float>		ZERO		= {  0,  0,  0 };
		constexpr Vec3<float>		ONE			= {  1,  1,  1 };
		constexpr Vec3<float>		RIGHT		= {  1,  0,  0 };
		constexpr Vec3<float>		LEFT		= { -1,  0,  0 };
		constexpr Vec3<float>		UP			= {  0,  1,  0 };
		constexpr Vec3<float>		DOWN		= {  0, -1,  0 };
		constexpr Vec3<float>		FORWARD		= {  0,  0,  1 };
		constexpr Vec3<float>		BACK		= {  0,  0, -1 };
	}

	namespace VEC3D
	{
		constexpr Vec3<double>		ZERO		= {  0,  0,  0 };
		constexpr Vec3<double>		ONE			= {  1,  1,  1 };
		constexpr Vec3<double>		RIGHT		= {  1,  0,  0 };
		constexpr Vec3<double>		LEFT		= { -1,  0,  0 };
		constexpr Vec3<double>		UP			= {  0,  1,  0 };
		constexpr Vec3<double>		DOWN		= {  0, -1,  0 };
		constexpr Vec3<double>		FORWARD		= {  0,  0,  1 };
		constexpr Vec3<double>		BACK		= {  0,  0, -1 };
	}

	namespace VEC3UI
	{
		constexpr Vec3<unsigned int>		ZERO		= {  0,  0,  0 };
		constexpr Vec3<unsigned int>		ONE			= {  1,  1,  1 };
		constexpr Vec3<unsigned int>		RIGHT		= {  1,  0,  0 };
		constexpr Vec3<unsigned int>		LEFT		= { -1,  0,  0 };
		constexpr Vec3<unsigned int>		UP			= {  0,  1,  0 };
		constexpr Vec3<unsigned int>		DOWN		= {  0, -1,  0 };
		constexpr Vec3<unsigned int>		FORWARD		= {  0,  0,  1 };
		constexpr Vec3<unsigned int>		BACK		= {  0,  0, -1 };
	}

	namespace VEC3UL
	{
		constexpr Vec3<unsigned long>	ZERO		= {  0,  0,  0 };
		constexpr Vec3<unsigned long>	ONE			= {  1,  1,  1 };
		constexpr Vec3<unsigned long>	RIGHT		= {  1,  0,  0 };
		constexpr Vec3<unsigned long>	LEFT		= { -1,  0,  0 };
		constexpr Vec3<unsigned long>	UP			= {  0,  1,  0 };
		constexpr Vec3<unsigned long>	DOWN		= {  0, -1,  0 };
		constexpr Vec3<unsigned long>	FORWARD		= {  0,  0,  1 };
		constexpr Vec3<unsigned long>	BACK		= {  0,  0, -1 };
	}
}