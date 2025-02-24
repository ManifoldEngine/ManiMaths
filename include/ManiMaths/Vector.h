#pragma once

#include <type_traits>
#include <cmath>

namespace Mani
{
	template<typename T>
	concept IsNumericType = std::is_arithmetic<T>::value;

	template<IsNumericType T>
	struct Vector3
	{
		T x = static_cast<T>(0);
		T y = static_cast<T>(0);
		T z = static_cast<T>(0);

		static bool isNearlyEqual(const Vector3<T>& lhs, const Vector3<T> rhs, double tolerance = FLT_EPSILON)
		{
			return	std::abs(lhs.x - rhs.x) <= tolerance &&
					std::abs(lhs.y - rhs.y) <= tolerance &&
					std::abs(lhs.z - rhs.z) <= tolerance;
		}

		bool isNearlyEqual(const Vector3<T>& rhs, double tolerance = FLT_EPSILON)
		{
			return isNearlyEqual(*this, rhs, tolerance);
		}

		std::string toString() const
		{
			return std::format("({}, {}, {})", x, y, z);
		}
	};

	typedef Vector3<int> Vector3i;
	typedef Vector3<long> Vector3l;
	typedef Vector3<float> Vector3f;
	typedef Vector3<double> Vector3d;
	typedef Vector3<unsigned int> Vector3ui;
	typedef Vector3<unsigned long> Vector3ul;

	template<IsNumericType T1, IsNumericType T2>
	bool operator==(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		return lhs.x == rhs.x && lhs.y == rhs.y && lhs.z == rhs.z;
	}

	template<IsNumericType T1, IsNumericType T2>
	bool operator!=(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		return lhs.x != rhs.x || lhs.y != rhs.y || lhs.z != rhs.z;
	}

	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Vector3<TReturn> operator+(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		return { 
			lhs.x + rhs.x, 
			lhs.y + rhs.y, 
			lhs.z + rhs.z 
		};
	}

	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Vector3<TReturn> operator-(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		return { 
			lhs.x - rhs.x, 
			lhs.y - rhs.y, 
			lhs.z - rhs.z 
		};
	}

	template<IsNumericType T1, IsNumericType T2, IsNumericType TReturn = T1>
	Vector3<TReturn> operator*(const Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		return { 
			lhs.x * rhs.x, 
			lhs.y * rhs.y, 
			lhs.z * rhs.z 
		};
	}

	template<IsNumericType T1, IsNumericType T2>
	void operator+=(Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;		
	}

	template<IsNumericType T1, IsNumericType T2>
	void operator-=(Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;
	}

	template<IsNumericType T1, IsNumericType T2>
	void operator*=(Vector3<T1>& lhs, const Vector3<T2>& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;
	}

	template<IsNumericType T, IsNumericType TScale, IsNumericType TReturn = T>
	Vector3<TReturn> operator*(const Vector3<T>& lhs, TScale scale)
	{
		return {
			lhs.x * scale,
			lhs.y* scale,
			lhs.z* scale,
		};
	}

	template<IsNumericType T, IsNumericType TScale>
	void operator*=(Vector3<T>& lhs, TScale scale)
	{
		lhs.x *= scale;
		lhs.y *= scale;
		lhs.z *= scale;
	}

	template<IsNumericType T, IsNumericType TScale, IsNumericType TReturn = T>
	Vector3<TReturn> operator/(const Vector3<T>& lhs, TScale scale)
	{
		assert(scale != 0);
		return {
			lhs.x / scale,
			lhs.y / scale,
			lhs.z / scale,
		};
	}

	template<IsNumericType T, IsNumericType TScale>
	void operator/=(Vector3<T>& lhs, TScale scale)
	{
		assert(scale != 0);
		lhs.x /= scale;
		lhs.y /= scale;
		lhs.z /= scale;
	}
}