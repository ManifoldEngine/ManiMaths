#pragma once

#include "_Mat.h"
#include "_Vec.h"
#include "Quat.h"
#include "Debug.h"
#include "Traits.h"
#include "Maths.h"
#include <format>

namespace Mani
{
	template<IsNumeric T>
	struct Mat<T, 4, 4>
	{
		T _00, _01, _02, _03;
		T _10, _11, _12, _13;
		T _20, _21, _22, _23;
		T _30, _31, _32, _33;

		MatLineView<T, 4>		operator[](Size i)			{ return MatLineView<T, 4>{ &this->_00, i }; };
		const MatLineView<T, 4>	operator[](Size i) const	{ return MatLineView<T, 4>{ &this->_00, i }; };

		Vec<T, 4> getLineAt(Size i) const
		{
			switch (i)
			{
				case 0: return { _00, _01, _02, _03 };
				case 1: return { _10, _11, _12, _13 };
				case 2: return { _20, _21, _22, _23 };
				case 3: return { _30, _31, _32, _33 };
				default: MANIMATHS_ASSERT(false); return {}; // bad access
			}
		}

		void setLineAt(Size i, const Vec<T, 4>& v)
		{
			switch (i)
			{
				case 0: _00 = v.x; _01 = v.y; _02 = v.z; _03 = v.w; break;
				case 1: _10 = v.x; _11 = v.y; _12 = v.z; _13 = v.w; break;
				case 2: _20 = v.x; _21 = v.y; _22 = v.z; _23 = v.w; break;
				case 3: _30 = v.x; _31 = v.y; _32 = v.z; _33 = v.w; break;
				default: MANIMATHS_ASSERT(false); // bad access
			}
		}

		static Mat<T, 4, 4> make(T v) 
		{
			return {
				v, v, v, v,
				v, v, v, v,
				v, v, v, v,
				v, v, v, v
			};
		}

		template<IsNumeric T1, IsNumeric T2>
		static bool isNearlyEqual(const Mat<T1, 4, 4>& lhs, const Mat<T2, 4, 4>& rhs, double tolerance = FLT_EPSILON)
		{
			return	abs(lhs._00 - rhs._00) <= tolerance &&
					abs(lhs._10 - rhs._10) <= tolerance &&
					abs(lhs._20 - rhs._20) <= tolerance &&
					abs(lhs._30 - rhs._30) <= tolerance &&

					abs(lhs._01 - rhs._01) <= tolerance &&
					abs(lhs._11 - rhs._11) <= tolerance &&
					abs(lhs._21 - rhs._21) <= tolerance &&
					abs(lhs._31 - rhs._31) <= tolerance &&

					abs(lhs._02 - rhs._02) <= tolerance &&
					abs(lhs._12 - rhs._12) <= tolerance &&
					abs(lhs._22 - rhs._22) <= tolerance &&
					abs(lhs._32 - rhs._32) <= tolerance &&

					abs(lhs._03 - rhs._03) <= tolerance &&
					abs(lhs._13 - rhs._13) <= tolerance &&
					abs(lhs._23 - rhs._23) <= tolerance &&
					abs(lhs._33 - rhs._33) <= tolerance;
		}


		template<IsNumeric T2>
		bool isNearlyEqual(const Mat<T2, 4, 4>& other, double tolerance = FLT_EPSILON) const
		{
			return isNearlyEqual(*this, other, tolerance);
		}

		Mat<T, 4, 4> transpose() const
		{
			return {
				_00, _10, _20, _30,
				_01, _11, _21, _31,
				_02, _12, _22, _32,
				_03, _13, _23, _33
			};
		}

		Mat<T, 4, 4> inverse() const
		{
			constexpr T __0 = static_cast<T>(0);
			constexpr T __1 = static_cast<T>(1);

			T inv00 = _00 * _11 - _01 * _10;
			T inv01 = _00 * _12 - _02 * _10;
			T inv02 = _00 * _13 - _03 * _10;
			T inv03 = _01 * _12 - _02 * _11;
			T inv04 = _01 * _13 - _03 * _11;
			T inv05 = _02 * _13 - _03 * _12;
			T inv06 = _20 * _31 - _21 * _30;
			T inv07 = _20 * _32 - _22 * _30;
			T inv08 = _20 * _33 - _23 * _30;
			T inv09 = _21 * _32 - _22 * _31;
			T inv10 = _21 * _33 - _23 * _31;
			T inv11 = _22 * _33 - _23 * _32;

			// determinant
			T det = inv00 * inv11 - inv01 * inv10 + inv02 * inv09 + inv03 * inv08 - inv04 * inv07 + inv05 * inv06;
			MANIMATHS_ASSERT(!isEqual(det, __0));
			T invDet = __1 / det;

			return {
				(_11 * inv11 - _12 * inv10 + _13 * inv09) * invDet,
				(_02 * inv10 - _01 * inv11 - _03 * inv09) * invDet,
				(_31 * inv05 - _32 * inv04 + _33 * inv03) * invDet,
				(_22 * inv04 - _21 * inv05 - _23 * inv03) * invDet,
				(_12 * inv08 - _10 * inv11 - _13 * inv07) * invDet,
				(_00 * inv11 - _02 * inv08 + _03 * inv07) * invDet,
				(_32 * inv02 - _30 * inv05 - _33 * inv01) * invDet,
				(_20 * inv05 - _22 * inv02 + _23 * inv01) * invDet,
				(_10 * inv10 - _11 * inv08 + _13 * inv06) * invDet,
				(_01 * inv08 - _00 * inv10 - _03 * inv06) * invDet,
				(_30 * inv04 - _31 * inv02 + _33 * inv00) * invDet,
				(_21 * inv02 - _20 * inv04 - _23 * inv00) * invDet,
				(_11 * inv07 - _10 * inv09 - _12 * inv06) * invDet,
				(_00 * inv09 - _01 * inv07 + _02 * inv06) * invDet,
				(_31 * inv01 - _30 * inv03 - _32 * inv00) * invDet,
				(_20 * inv03 - _21 * inv01 + _22 * inv00) * invDet
			};
		}

		T determinant() const
		{
			T s0 = _00 * _11 - _01 * _10;
			T s1 = _00 * _12 - _02 * _10;
			T s2 = _01 * _12 - _02 * _11;
			T s3 = _20 * _31 - _21 * _30;
			T s4 = _20 * _32 - _22 * _30;
			T s5 = _21 * _32 - _22 * _31;
			
			T c0 = _00 * s5 - _01 * s4 + _02 * s3;
			T c1 = _10 * s5 - _11 * s4 + _12 * s3;
			T c2 = _20 * s2 - _21 * s1 + _22 * s0;
			T c3 = _30 * s2 - _31 * s1 + _32 * s0;

			return _13 * c0 - _03 * c1 + _33 * c2 - _23 * c3;
		}

		operator Mat<T, 3, 3>() const
		{
			return {
				_00, _01, _02,
				_10, _11, _12,
				_20, _21, _22,
			};
		}

		static Mat<T, 4, 4> translate(const Mat<T, 4, 4>& mat, const Vec<T, 3>& v)
		{
			Mat<T, 4, 4> r = mat;
			r.setLineAt(3,	mat.getLineAt(0) * v.x +
							mat.getLineAt(1) * v.y +
							mat.getLineAt(2) * v.z +
							mat.getLineAt(3));
			return r;
		}

		Mat<T, 4, 4>& translate(const Vec<T, 3>& v)
		{
			*this = translate(*this, v);
			return *this;
		}

		Mat<T, 4, 4> translate(const Vec<T, 3>& v) const
		{
			return translate(*this, v);
		}

		static Mat<T, 4, 4> rotate(const Mat<T, 4, 4>& m, const Quat<T>& q)
		{
			return m * static_cast<Mat<T, 4, 4>>(q);
		}

		Mat<T, 4, 4>& rotate(const Quat<T>& q)
		{
			*this = *this * static_cast<Mat<T, 4, 4>>(q);
			return *this;
		}

		Mat<T, 4, 4> rotate(const Quat<T>& q) const
		{
			return *this * static_cast<Mat<T, 4, 4>>(q);
		}

		static Mat<T, 4, 4> scale(const Mat<T, 4, 4>& mat, const Vec<T, 3>& s)
		{
			return {
				mat._00 * s.x, mat._01 * s.x, mat._02 * s.x, mat._03 * s.x,
				mat._10 * s.y, mat._11 * s.y, mat._12 * s.y, mat._13 * s.y,
				mat._20 * s.z, mat._21 * s.z, mat._22 * s.z, mat._23 * s.z,
				mat._30      , mat._31      , mat._32      , mat._33,
			};
		}

		Mat<T, 4, 4>& scale(const Vec<T, 3>& s)
		{
			*this = scale(*this, s);
			return *this;
		}

		Mat<T, 4, 4> scale(const Vec<T, 3>& s) const
		{
			return scale(*this, s);
		}

		[[nodiscard]] static Mat<T, 4, 4> lookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
		{
			constexpr T _0 = static_cast<T>(0);
			constexpr T _1 = static_cast<T>(1);

			const Vec<T, 3> f = (center - eye).normalize();
			const Vec<T, 3> s = Vec<T, 3>::cross(f, up).normalize();
			const Vec<T, 3> u = Vec<T, 3>::cross(s, f);

			// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml
			return {
						 s.x,		  u.x,		 -f.x, _0,
						 s.y,		  u.y,		 -f.y, _0,
						 s.z,		  u.z,		 -f.z, _0,
				 -s.dot(eye), -u.dot(eye), f.dot(eye), _1
			};
		}

		[[nodiscard]] static Mat<T, 4, 4> perspective(T fov, T aspect, T zNear, T zFar)
		{
			constexpr T _0 = static_cast<T>(0);
			constexpr T _1 = static_cast<T>(1);
			constexpr T _2 = static_cast<T>(2);

			MANIMATHS_ASSERT(!isEqual(aspect, _0));

			const T tanHalffov = tan(fov / _2);

			return {
				_1 / (aspect * tanHalffov),				   _0,	 	     						  _0,  _0,
				                        _0,	_1 / (tanHalffov),	 	     						  _0,  _0,
				                        _0,	               _0,      -(zFar + zNear) / (zFar - zNear), -_1,
				                        _0,	               _0, -(_2 * zFar * zNear) / (zFar - zNear),  _0,
			};
		}

		std::string toString() const
		{
			return std::format("({}, {}, {}, {})\n({}, {}, {}, {})\n({}, {}, {}, {})\n({}, {}, {}, {})",
				_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
		}

		std::string toStringOnOneLine() const
		{
			return std::format("({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})({}, {}, {}, {})",
				_00, _01, _02, _03, _10, _11, _12, _13, _20, _21, _22, _23, _30, _31, _32, _33);
		}
	};

	typedef Mat<int,			4, 4> Mat4i;
	typedef Mat<long,			4, 4> Mat4l;
	typedef Mat<float,			4, 4> Mat4f;
	typedef Mat<double,			4, 4> Mat4d;
	typedef Mat<unsigned int,	4, 4> Mat4ui;
	typedef Mat<unsigned long,	4, 4> Mat4ul;

	template<IsNumeric T>
	bool operator==(const Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		return	lhs._00 == rhs._00 && lhs._01 == rhs._01 && lhs._02 == rhs._02 && lhs._03 == rhs._03 &&
				lhs._10 == rhs._10 && lhs._11 == rhs._11 && lhs._12 == rhs._12 && lhs._13 == rhs._13 &&
				lhs._20 == rhs._20 && lhs._21 == rhs._21 && lhs._22 == rhs._22 && lhs._23 == rhs._23 &&
				lhs._30 == rhs._30 && lhs._31 == rhs._31 && lhs._32 == rhs._32 && lhs._33 == rhs._33;
	}

	template<IsNumeric T>
	bool operator!=(const Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		return	lhs._00 != rhs._00 || lhs._01 != rhs._01 || lhs._02 != rhs._02 || lhs._03 != rhs._03 ||
				lhs._10 != rhs._10 || lhs._11 != rhs._11 || lhs._12 != rhs._12 || lhs._13 != rhs._13 ||
				lhs._20 != rhs._20 || lhs._21 != rhs._21 || lhs._22 != rhs._22 || lhs._23 != rhs._23 ||
				lhs._30 != rhs._30 || lhs._31 != rhs._31 || lhs._32 != rhs._32 || lhs._33 != rhs._33;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator+(const Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		return Mat<T, 4, 4>{
			lhs._00 + rhs._00, lhs._01 + rhs._01, lhs._02 + rhs._02, lhs._03 + rhs._03,
			lhs._10 + rhs._10, lhs._11 + rhs._11, lhs._12 + rhs._12, lhs._13 + rhs._13,
			lhs._20 + rhs._20, lhs._21 + rhs._21, lhs._22 + rhs._22, lhs._23 + rhs._23,
			lhs._30 + rhs._30, lhs._31 + rhs._31, lhs._32 + rhs._32, lhs._33 + rhs._33
		};
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator-(const Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		return Mat<T, 4, 4>{
			lhs._00 - rhs._00, lhs._01 - rhs._01, lhs._02 - rhs._02, lhs._03 - rhs._03,
			lhs._10 - rhs._10, lhs._11 - rhs._11, lhs._12 - rhs._12, lhs._13 - rhs._13,
			lhs._20 - rhs._20, lhs._21 - rhs._21, lhs._22 - rhs._22, lhs._23 - rhs._23,
			lhs._30 - rhs._30, lhs._31 - rhs._31, lhs._32 - rhs._32, lhs._33 - rhs._33
		};
	}

	template<IsNumeric T>
	void operator+=(Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		lhs._00 += rhs._00; lhs._01 += rhs._01; lhs._02 += rhs._02; lhs._03 += rhs._03;
		lhs._10 += rhs._10; lhs._11 += rhs._11; lhs._12 += rhs._12; lhs._13 += rhs._13;
		lhs._20 += rhs._20; lhs._21 += rhs._21; lhs._22 += rhs._22; lhs._23 += rhs._23;
		lhs._30 += rhs._30; lhs._31 += rhs._31; lhs._32 += rhs._32; lhs._33 += rhs._33;
	}

	template<IsNumeric T>
	void operator-=(Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		lhs._00 -= rhs._00; lhs._01 -= rhs._01; lhs._02 -= rhs._02; lhs._03 -= rhs._03;
		lhs._10 -= rhs._10; lhs._11 -= rhs._11; lhs._12 -= rhs._12; lhs._13 -= rhs._13;
		lhs._20 -= rhs._20; lhs._21 -= rhs._21; lhs._22 -= rhs._22; lhs._23 -= rhs._23;
		lhs._30 -= rhs._30; lhs._31 -= rhs._31; lhs._32 -= rhs._32; lhs._33 -= rhs._33;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator*(const Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		return Mat<T, 4, 4>{
			lhs._00 * rhs._00 + lhs._10 * rhs._01 + lhs._20 * rhs._02 + lhs._30 * rhs._03, // _00
			lhs._01 * rhs._00 + lhs._11 * rhs._01 + lhs._21 * rhs._02 + lhs._31 * rhs._03, // _01
			lhs._02 * rhs._00 + lhs._12 * rhs._01 + lhs._22 * rhs._02 + lhs._32 * rhs._03, // _02
			lhs._03 * rhs._00 + lhs._13 * rhs._01 + lhs._23 * rhs._02 + lhs._33 * rhs._03, // _03

			lhs._00 * rhs._10 + lhs._10 * rhs._11 + lhs._20 * rhs._12 + lhs._30 * rhs._13, // _10
			lhs._01 * rhs._10 + lhs._11 * rhs._11 + lhs._21 * rhs._12 + lhs._31 * rhs._13, // _11
			lhs._02 * rhs._10 + lhs._12 * rhs._11 + lhs._22 * rhs._12 + lhs._32 * rhs._13, // _12
			lhs._03 * rhs._10 + lhs._13 * rhs._11 + lhs._23 * rhs._12 + lhs._33 * rhs._13, // _13

			lhs._00 * rhs._20 + lhs._10 * rhs._21 + lhs._20 * rhs._22 + lhs._30 * rhs._23, // _20
			lhs._01 * rhs._20 + lhs._11 * rhs._21 + lhs._21 * rhs._22 + lhs._31 * rhs._23, // _21
			lhs._02 * rhs._20 + lhs._12 * rhs._21 + lhs._22 * rhs._22 + lhs._32 * rhs._23, // _22
			lhs._03 * rhs._20 + lhs._13 * rhs._21 + lhs._23 * rhs._22 + lhs._33 * rhs._23, // _23

			lhs._00 * rhs._30 + lhs._10 * rhs._31 + lhs._20 * rhs._32 + lhs._30 * rhs._33, // _30
			lhs._01 * rhs._30 + lhs._11 * rhs._31 + lhs._21 * rhs._32 + lhs._31 * rhs._33, // _31
			lhs._02 * rhs._30 + lhs._12 * rhs._31 + lhs._22 * rhs._32 + lhs._32 * rhs._33, // _32
			lhs._03 * rhs._30 + lhs._13 * rhs._31 + lhs._23 * rhs._32 + lhs._33 * rhs._33  // _33
		};
	}

	template<IsNumeric T>
	void operator*=(Mat<T, 4, 4>& lhs, const Mat<T, 4, 4>& rhs)
	{
		lhs = lhs * rhs;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator*(const Mat<T, 4, 4>& lhs, T rhs)
	{
		return Mat<T, 4, 4>{
			lhs._00 * rhs, lhs._01 * rhs, lhs._02 * rhs, lhs._03 * rhs,
			lhs._10 * rhs, lhs._11 * rhs, lhs._12 * rhs, lhs._13 * rhs,
			lhs._20 * rhs, lhs._21 * rhs, lhs._22 * rhs, lhs._23 * rhs,
			lhs._30 * rhs, lhs._31 * rhs, lhs._32 * rhs, lhs._33 * rhs
		};
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator*(T lhs, const Mat<T, 4, 4>& rhs)
	{
		return Mat<T, 4, 4>{
			rhs._00 * lhs, rhs._01* lhs, rhs._02 * lhs, rhs._03* lhs,
			rhs._10 * lhs, rhs._11* lhs, rhs._12 * lhs, rhs._13* lhs,
			rhs._20 * lhs, rhs._21* lhs, rhs._22 * lhs, rhs._23* lhs,
			rhs._30 * lhs, rhs._31* lhs, rhs._32 * lhs, rhs._33* lhs
		};
	}

	template<IsNumeric T>
	void operator*=(Mat<T, 4, 4>& lhs, T rhs)
	{
		lhs._00 *= rhs; lhs._01 *= rhs; lhs._02 *= rhs; lhs._03 *= rhs;
		lhs._10 *= rhs; lhs._11 *= rhs; lhs._12 *= rhs; lhs._13 *= rhs;
		lhs._20 *= rhs; lhs._21 *= rhs; lhs._22 *= rhs; lhs._23 *= rhs;
		lhs._30 *= rhs; lhs._31 *= rhs; lhs._32 *= rhs; lhs._33 *= rhs;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> operator/(const Mat<T, 4, 4>& lhs, T rhs)
	{
		return Mat<T, 4, 4>{
			lhs._00 / rhs, lhs._01 / rhs, lhs._02 / rhs, lhs._03 / rhs,
			lhs._10 / rhs, lhs._11 / rhs, lhs._12 / rhs, lhs._13 / rhs,
			lhs._20 / rhs, lhs._21 / rhs, lhs._22 / rhs, lhs._23 / rhs,
			lhs._30 / rhs, lhs._31 / rhs, lhs._32 / rhs, lhs._33 / rhs
		};
	}

	template<IsNumeric T>
	void operator/=(Mat<T, 4, 4>& lhs, T rhs)
	{
		lhs._00 /= rhs; lhs._01 /= rhs; lhs._02 /= rhs; lhs._03 /= rhs;
		lhs._10 /= rhs; lhs._11 /= rhs; lhs._12 /= rhs; lhs._13 /= rhs;
		lhs._20 /= rhs; lhs._21 /= rhs; lhs._22 /= rhs; lhs._23 /= rhs;
		lhs._30 /= rhs; lhs._31 /= rhs; lhs._32 /= rhs; lhs._33 /= rhs;
	}

	template<IsNumeric T>
	Vec<T, 4> operator*(const Mat<T, 4, 4>& mat, const Vec<T, 4>& v)
	{
		return {
			mat._00 * v.x + mat._10 * v.y + mat._20 * v.z + mat._30 * v.w,
			mat._01 * v.x + mat._11 * v.y + mat._21 * v.z + mat._31 * v.w,
			mat._02 * v.x + mat._12 * v.y + mat._22 * v.z + mat._32 * v.w,
			mat._03 * v.x + mat._13 * v.y + mat._23 * v.z + mat._33 * v.w
		};
	}

	template<IsNumeric T>
	Vec<T, 4> operator*(const Vec<T, 4>& v, const Mat<T, 4, 4>& mat)
	{
		return {
			mat._00 * v.x + mat._01 * v.y + mat._02 * v.z + mat._03,
			mat._10 * v.x + mat._11 * v.y + mat._12 * v.z + mat._13,
			mat._20 * v.x + mat._21 * v.y + mat._22 * v.z + mat._23
		};
	}

	template<IsNumeric T>
	Vec<T, 3> operator*(const Mat<T, 4, 4>& mat, const Vec<T, 3>& v)
	{
		const Vec<T, 4> result = mat * v.homogenous();
		return result / result.w;
	}

	namespace MAT4I
	{
		constexpr Mat4i IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}

	namespace MAT4L
	{
		constexpr Mat4l IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	
	namespace MAT4F
	{
		constexpr Mat4f IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	
	namespace MAT4D
	{
		constexpr Mat4d IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	
	namespace MAT4UI
	{
		constexpr Mat4ui IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
	
	namespace MAT4UL
	{
		constexpr Mat4ul IDENTITY = {
			1, 0, 0, 0,
			0, 1, 0, 0,
			0, 0, 1, 0,
			0, 0, 0, 1
		};
	}
}