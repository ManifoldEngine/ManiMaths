#pragma once

#include "_Vec.h"
#include "Debug.h"
#include "Traits.h"
#include "ManiMaths/Maths.h"
#include <format>

namespace Mani
{
	template<IsNumeric T>
	struct Vec<T, 2>
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static bool isNearlyEqual(const Vec<T1, 2>& lhs, const Vec<T2, 2> rhs, double tolerance = FLT_EPSILON)
		{
			return	abs(lhs.x - rhs.x) <= tolerance &&
				abs(lhs.y - rhs.y) <= tolerance;
		}

		template<IsNumeric T2>
		[[nodiscard]] bool isNearlyEqual(const Vec<T2, 2>& rhs, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}

		[[nodiscard]] T length() const
		{
			return sqrt(x * x + y * y);
		}

		[[nodiscard]] T lengthSquared() const
		{
			return x * x + y * y;
		}

		[[nodiscard]] Vec<T, 2> normalize() const
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
		[[nodiscard]] static T distance(const Vec<T1, 2>& v1, const Vec<T2, 2>& v2)
		{
			return sqrt((v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y));
		}

		template<IsNumeric T2>
		[[nodiscard]] T distance(const Vec<T2, 2>& other) const
		{
			return distance(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T distanceSquared(const Vec<T1, 2>& v1, const Vec<T2, 2>& v2)
		{
			return (v2.x - v1.x) * (v2.x - v1.x) + (v2.y - v1.y) * (v2.y - v1.y);
		}

		template<IsNumeric T2>
		[[nodiscard]] T distanceSquared(const Vec<T2, 2>& other) const
		{
			return distanceSquared(*this, other);
		}

		template<IsNumeric T1, IsNumeric T2>
		[[nodiscard]] static T dot(const Vec<T1, 2>& v1, const Vec<T2, 2>& v2)
		{
			return v1.x * v2.x + v1.y * v2.y;
		}

		template<IsNumeric T2>
		[[nodiscard]] T dot(const Vec<T2, 2>& other) const
		{
			return dot(*this, other);
		}

		operator Vec<T, 3>() const { return { x, y, static_cast<T>(0) }; }
		operator Vec<T, 4>() const { return { x, y, static_cast<T>(0), static_cast<T>(0) }; }
		Vec<T, 4> homogenous() const { return { x, y, static_cast<T>(0), static_cast<T>(1) }; }

		[[nodiscard]] std::string toString() const
		{
			return std::format("({}, {})", x, y);
		}
	};

	typedef Vec<int,			2> Vec2i;
	typedef Vec<long,			2> Vec2l;
	typedef Vec<float,			2> Vec2f;
	typedef Vec<double,			2> Vec2d;
	typedef Vec<unsigned int,	2> Vec2ui;
	typedef Vec<unsigned long,	2> Vec2ul;

	template<IsNumeric T1, IsNumeric T2>
	bool operator==(const Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y;
	}

	template<IsNumeric T1, IsNumeric T2>
	bool operator!=(const Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y;
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 2> operator+(const Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		return {
			lhs.x + rhs.x,
			lhs.y + rhs.y
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 2> operator-(const Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		return {
			lhs.x - rhs.x,
			lhs.y - rhs.y
		};
	}

	template<IsNumeric T1, IsNumeric T2, IsNumeric TReturn = T1>
	Vec<TReturn, 2> operator*(const Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		return {
			lhs.x * rhs.x,
			lhs.y * rhs.y
		};
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator+=(Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator-=(Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
	}

	template<IsNumeric T1, IsNumeric T2>
	void operator*=(Vec<T1, 2>& lhs, const Vec<T2, 2>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 2> operator*(const Vec<T, 2>& lhs, TScale scale)
	{
		return {
			lhs.x * scale,
			lhs.y * scale
		};
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 2> operator*(TScale scale, const Vec<T, 2>& rhs)
	{
		return {
			rhs.x * scale,
			rhs.y * scale
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator*=(Vec<T, 2>& lhs, TScale scale)
	{
		lhs.x *= scale;
		lhs.y *= scale;
	}

	template<IsNumeric T, IsNumeric TScale, IsNumeric TReturn = T>
	Vec<TReturn, 2> operator/(const Vec<T, 2>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(abs(scale) > 0);
		return {
			lhs.x / scale,
			lhs.y / scale
		};
	}

	template<IsNumeric T, IsNumeric TScale>
	void operator/=(Vec<T, 2>& lhs, TScale scale)
	{
		MANIMATHS_ASSERT(abs(scale) > 0);
		lhs.x /= scale;
		lhs.y /= scale;
	}

	namespace VEC2I
	{
		constexpr Vec2i 	ZERO		= {  0,  0 };
		constexpr Vec2i 	ONE			= {  1,  1 };
		constexpr Vec2i 	RIGHT		= {  1,  0 };
		constexpr Vec2i 	LEFT		= { -1,  0 };
		constexpr Vec2i 	UP			= {  0,  1 };
		constexpr Vec2i 	DOWN		= {  0, -1 };
	}

	namespace VEC2L
	{
		constexpr Vec2l		ZERO		= {  0,  0 };
		constexpr Vec2l		ONE			= {  1,  1 };
		constexpr Vec2l		RIGHT		= {  1,  0 };
		constexpr Vec2l		LEFT		= { -1,  0 };
		constexpr Vec2l		UP			= {  0,  1 };
		constexpr Vec2l		DOWN		= {  0, -1 };
	}

	namespace VEC2F
	{
		constexpr Vec2f		ZERO		= {  0,  0 };
		constexpr Vec2f		ONE			= {  1,  1 };
		constexpr Vec2f		RIGHT		= {  1,  0 };
		constexpr Vec2f		LEFT		= { -1,  0 };
		constexpr Vec2f		UP			= {  0,  1 };
		constexpr Vec2f		DOWN		= {  0, -1 };
	}

	namespace VEC2D
	{
		constexpr Vec2d		ZERO		= {  0,  0 };
		constexpr Vec2d		ONE			= {  1,  1 };
		constexpr Vec2d		RIGHT		= {  1,  0 };
		constexpr Vec2d		LEFT		= { -1,  0 };
		constexpr Vec2d		UP			= {  0,  1 };
		constexpr Vec2d		DOWN		= {  0, -1 };
	}

	namespace VEC2UI
	{
		constexpr Vec2ui	ZERO		= {  0,  0 };
		constexpr Vec2ui	ONE			= {  1,  1 };
		constexpr Vec2ui	RIGHT		= {  1,  0 };
		constexpr Vec2ui	LEFT		= { -1,  0 };
		constexpr Vec2ui	UP			= {  0,  1 };
		constexpr Vec2ui	DOWN		= {  0, -1 };
	}

	namespace VEC2UL
	{
		constexpr Vec2ul	ZERO		= {  0,  0 };
		constexpr Vec2ul	ONE			= {  1,  1 };
		constexpr Vec2ul	RIGHT		= {  1,  0 };
		constexpr Vec2ul	LEFT		= { -1,  0 };
		constexpr Vec2ul	UP			= {  0,  1 };
		constexpr Vec2ul	DOWN		= {  0, -1 };
	}
}