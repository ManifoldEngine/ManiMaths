#pragma once

#pragma once

#include "_Mat.h"
#include "_Vec.h"
#include "Debug.h"
#include "Traits.h"
#include "Maths.h"
#include <format>

namespace Mani
{
	template<IsNumeric T>
	struct Mat<T, 3, 3>
	{
		T _00, _01, _02;
		T _10, _11, _12;
		T _20, _21, _22;

		MatLineView<T, 3>		operator[](Size i) { return MatLineView<T, 3>{ &this->_00, i }; };
		const MatLineView<T, 3>	operator[](Size i) const { return MatLineView<T, 3>{ &this->_00, i }; };

		Vec<T, 4> getLineAt(Size i) const
		{
			switch (i)
			{
			case 0: return { _00, _01, _02 };
			case 1: return { _10, _11, _12 };
			case 2: return { _20, _21, _22 };
			default: MANIMATHS_ASSERT(false); return {}; // bad access
			}
		}

		void setLineAt(Size i, const Vec<T, 3>& v)
		{
			switch (i)
			{
			case 0: _00 = v.x; _01 = v.y; _02 = v.z; break;
			case 1: _10 = v.x; _11 = v.y; _12 = v.z; break;
			case 2: _20 = v.x; _21 = v.y; _22 = v.z; break;
			default: MANIMATHS_ASSERT(false); // bad access
			}
		}

		static Mat<T, 3, 3> make(T v)
		{
			return {
				v, v, v,
				v, v, v,
				v, v, v
			};
		}

		template<IsNumeric T1, IsNumeric T2>
		static bool isNearlyEqual(const Mat<T1, 3, 3>& lhs, const Mat<T2, 3, 3>& rhs, double tolerance = FLT_EPSILON)
		{
			return	Math::abs(lhs._00 - rhs._00) <= tolerance &&
					Math::abs(lhs._10 - rhs._10) <= tolerance &&
					Math::abs(lhs._20 - rhs._20) <= tolerance &&

					Math::abs(lhs._01 - rhs._01) <= tolerance &&
					Math::abs(lhs._11 - rhs._11) <= tolerance &&
					Math::abs(lhs._21 - rhs._21) <= tolerance &&

					Math::abs(lhs._02 - rhs._02) <= tolerance &&
					Math::abs(lhs._12 - rhs._12) <= tolerance &&
					Math::abs(lhs._22 - rhs._22) <= tolerance;
		}

		template<IsNumeric T2>
		bool isNearlyEqual(const Mat<T2, 3, 3>& other, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, other, tolerance);
		}

		Mat<T, 3, 3> transpose() const
		{
			return {
				_00, _10, _20,
				_01, _11, _21,
				_02, _12, _22
			};
		}

		Mat<T, 3, 3> inverse() const
		{
			constexpr T _1 = static_cast<T>(1);

			const T inv01 =  _22 * _11 - _12 * _21;
			const T inv11 = -_22 * _10 + _12 * _20;
			const T inv21 =  _21 * _10 - _11 * _20;

			// determinant
			const T det = _00 * inv01 + _01 * inv11 + _02 * inv21;
			const T f = _1 / det;

			return {
				inv01 * f, ( _22 * _01 + _02 * _21) * f, ( _12 * _01 - _02 * _11) * f,
				inv11 * f, ( _22 * _00 - _02 * _20) * f, (-_12 * _00 + _02 * _10) * f,
				inv21 * f, (-_21 * _00 + _01 * _20) * f, ( _11 * _00 - _01 * _10) * f
			};
		}

		T determinant() const
		{
			return {
				_00 * ( _22 * _11 - _12 * _21) +
				_01 * (-_22 * _10 + _12 * _20) +
				_02 * ( _21 * _10 - _11 * _20)
			};
		}

		operator Mat<T, 4, 4>() const
		{
			constexpr T _0 = static_cast<T>(0);
			constexpr T _1 = static_cast<T>(1);
			return {
				_00, _01, _02, _0,
				_10, _11, _12, _0,
				_20, _21, _22, _0,
				 _0,  _0,  _0, _1,
			};
		}

		std::string toString() const
		{
			return std::format("({}, {}, {})\n({}, {}, {})\n({}, {}, {})",
				_00, _01, _02, _10, _11, _12, _20, _21, _22);
		}

		std::string toStringOnOneLine() const
		{
			return std::format("({}, {}, {})({}, {}, {})({}, {}, {})",
				_00, _01, _02, _10, _11, _12, _20, _21, _22);
		}
	};

	typedef Mat<int,			3, 3> Mat3i;
	typedef Mat<long,			3, 3> Mat3l;
	typedef Mat<float,			3, 3> Mat3f;
	typedef Mat<double,			3, 3> Mat3d;
	typedef Mat<unsigned int,	3, 3> Mat3ui;
	typedef Mat<unsigned long,	3, 3> Mat3ul;

	template<IsNumeric T>
	bool operator==(const Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		return	lhs._00 == rhs._00 && lhs._01 == rhs._01 && lhs._02 == rhs._02 &&
				lhs._10 == rhs._10 && lhs._11 == rhs._11 && lhs._12 == rhs._12 &&
				lhs._20 == rhs._20 && lhs._21 == rhs._21 && lhs._22 == rhs._22;
	}

	template<IsNumeric T>
	bool operator!=(const Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		return	lhs._00 != rhs._00 || lhs._01 != rhs._01 || lhs._02 != rhs._02 ||
				lhs._10 != rhs._10 || lhs._11 != rhs._11 || lhs._12 != rhs._12 ||
				lhs._20 != rhs._20 || lhs._21 != rhs._21 || lhs._22 != rhs._22;
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator+(const Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		return Mat<T, 3, 3>{
			lhs._00 + rhs._00, lhs._01 + rhs._01, lhs._02 + rhs._02,
			lhs._10 + rhs._10, lhs._11 + rhs._11, lhs._12 + rhs._12,
			lhs._20 + rhs._20, lhs._21 + rhs._21, lhs._22 + rhs._22
		};
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator-(const Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		return Mat<T, 3, 3>{
			lhs._00 - rhs._00, lhs._01 - rhs._01, lhs._02 - rhs._02,
			lhs._10 - rhs._10, lhs._11 - rhs._11, lhs._12 - rhs._12,
			lhs._20 - rhs._20, lhs._21 - rhs._21, lhs._22 - rhs._22
		};
	}

	template<IsNumeric T>
	void operator+=(Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		lhs._00 += rhs._00; lhs._01 += rhs._01; lhs._02 += rhs._02;
		lhs._10 += rhs._10; lhs._11 += rhs._11; lhs._12 += rhs._12;
		lhs._20 += rhs._20; lhs._21 += rhs._21; lhs._22 += rhs._22;
	}

	template<IsNumeric T>
	void operator-=(Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		lhs._00 -= rhs._00; lhs._01 -= rhs._01; lhs._02 -= rhs._02;
		lhs._10 -= rhs._10; lhs._11 -= rhs._11; lhs._12 -= rhs._12;
		lhs._20 -= rhs._20; lhs._21 -= rhs._21; lhs._22 -= rhs._22;
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator*(const Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		return Mat<T, 3, 3>{
			lhs._00 * rhs._00 + lhs._10 * rhs._01 + lhs._20 * rhs._02, // _00
			lhs._01 * rhs._00 + lhs._11 * rhs._01 + lhs._21 * rhs._02, // _01
			lhs._02 * rhs._00 + lhs._12 * rhs._01 + lhs._22 * rhs._02, // _02

			lhs._00 * rhs._10 + lhs._10 * rhs._11 + lhs._20 * rhs._12, // _10
			lhs._01 * rhs._10 + lhs._11 * rhs._11 + lhs._21 * rhs._12, // _11
			lhs._02 * rhs._10 + lhs._12 * rhs._11 + lhs._22 * rhs._12, // _12

			lhs._00 * rhs._20 + lhs._10 * rhs._21 + lhs._20 * rhs._22, // _20
			lhs._01 * rhs._20 + lhs._11 * rhs._21 + lhs._21 * rhs._22, // _21
			lhs._02 * rhs._20 + lhs._12 * rhs._21 + lhs._22 * rhs._22  // _22
		};
	}

	template<IsNumeric T>
	void operator*=(Mat<T, 3, 3>& lhs, const Mat<T, 3, 3>& rhs)
	{
		lhs = lhs * rhs;
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator*(const Mat<T, 3, 3>& lhs, T rhs)
	{
		return Mat<T, 3, 3>{
			lhs._00 * rhs, lhs._01 * rhs, lhs._02 * rhs,
			lhs._10 * rhs, lhs._11 * rhs, lhs._12 * rhs,
			lhs._20 * rhs, lhs._21 * rhs, lhs._22 * rhs
		};
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator*(T lhs, const Mat<T, 3, 3>& rhs)
	{
		return Mat<T, 3, 3>{
			rhs._00 * lhs, rhs._01 * lhs, rhs._02 * lhs,
			rhs._10 * lhs, rhs._11 * lhs, rhs._12 * lhs,
			rhs._20 * lhs, rhs._21 * lhs, rhs._22 * lhs
		};
	}

	template<IsNumeric T>
	void operator*=(Mat<T, 3, 3>& lhs, T rhs)
	{
		lhs._00 *= rhs; lhs._01 *= rhs; lhs._02 *= rhs;
		lhs._10 *= rhs; lhs._11 *= rhs; lhs._12 *= rhs;
		lhs._20 *= rhs; lhs._21 *= rhs; lhs._22 *= rhs;
	}

	template<IsNumeric T>
	Mat<T, 3, 3> operator/(const Mat<T, 3, 3>& lhs, T rhs)
	{
		return Mat<T, 3, 3>{
			lhs._00 / rhs, lhs._01 / rhs, lhs._02 / rhs,
			lhs._10 / rhs, lhs._11 / rhs, lhs._12 / rhs,
			lhs._20 / rhs, lhs._21 / rhs, lhs._22 / rhs,
		};
	}

	template<IsNumeric T>
	void operator/=(Mat<T, 3, 3>& lhs, T rhs)
	{
		lhs._00 /= rhs; lhs._01 /= rhs; lhs._02 /= rhs;
		lhs._10 /= rhs; lhs._11 /= rhs; lhs._12 /= rhs;
		lhs._20 /= rhs; lhs._21 /= rhs; lhs._22 /= rhs;
	}

	template<IsNumeric T>
	Vec<T, 3> operator*(const Mat<T, 3, 3>& mat, const Vec<T, 3>& v)
	{
		return {
			mat._00 * v.x + mat._10 * v.y + mat._20 * v.z,
			mat._01 * v.x + mat._11 * v.y + mat._21 * v.z,
			mat._02 * v.x + mat._12 * v.y + mat._22 * v.z
		};
	}

	namespace MAT3I
	{
		constexpr Mat3i IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	namespace MAT3L
	{
		constexpr Mat3l IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	namespace MAT3F
	{
		constexpr Mat3f IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	namespace MAT3D
	{
		constexpr Mat3d IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	namespace MAT3UI
	{
		constexpr Mat3ui IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}

	namespace MAT3UL
	{
		constexpr Mat3ul IDENTITY = {
			1, 0, 0,
			0, 1, 0,
			0, 0, 1
		};
	}
}