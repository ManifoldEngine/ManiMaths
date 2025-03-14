#pragma once

#include "Traits.h"
#include "Maths.h"

#include "Mat4.h"
#include "Mat3.h"

#include "Vec3.h"
#include "Vec4.h"

#include "Quat.h"

namespace Mani
{
	template<IsNumeric T>
	Mat<T, 4, 4> translate(const Mat<T, 4, 4>& mat, const Vec<T, 3>& v)
	{
		Mat<T, 4, 4> r = mat;
		r.setLineAt(3,	mat.getLineAt(0) * v.x + 
						mat.getLineAt(1) * v.y + 
						mat.getLineAt(2) * v.z + 
						mat.getLineAt(3));
		return r;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> lookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
	{
		constexpr T _0 = static_cast<T>(0);
		constexpr T _1 = static_cast<T>(1);

		const Vec<T, 3> f = (center - eye).normalize();
		const Vec<T, 3> s = Vec<T, 3>::cross(f, up).normalize();
		const Vec<T, 3> u = Vec<T, 3>::cross(s, f);

		// glm's
		/*return {
					s.x,		 u.x,		-f.x, _1,
					s.y,		 u.y,		-f.y, _1,
					s.z,		 u.z,		-f.z, _1,
			-s.dot(eye), -u.dot(eye), f.dot(eye), _1,
		};*/
		// https://registry.khronos.org/OpenGL-Refpages/gl2.1/xhtml/gluLookAt.xml
		return {
			 s.x,  s.y,  s.z, _0,
			 u.x,  u.y,  u.z, _0,
			-f.x, -f.y, -f.z, _0,
			  _0,   _0,   _0, _1
		};
	}

	template<IsNumeric T>
	Mat<T, 4, 4> rotate(const Mat<T, 4, 4>& mat, T angle, Vec<T, 3> axisIn)
	{
		constexpr T _1 = static_cast<T>(1);

		const T a = angle;
		const T c = cos(a);
		const T s = sin(a);

		const Vec<T, 3> axis = axisIn.normalize();
		const Vec<T, 3> temp = (_1 - c) * axis;

		Mat<T, 4, 4> rotate;
		rotate._00 = c + temp.x * axis.x;
		rotate._01 =	 temp.x * axis.y + s * axis.z;
		rotate._02 =	 temp.x * axis.z - s * axis.y;

		rotate._10 =	 temp.y * axis.x - s * axis.z;
		rotate._11 = c + temp.y * axis.y;
		rotate._12 =	 temp.y * axis.z + s * axis.x;
		
		rotate._20 =	 temp.z * axis.x + s * axis.y;
		rotate._21 =	 temp.z * axis.y - s * axis.x;
		rotate._22 = c + temp.z * axis.z;

		const Vec<T, 4> m0 = mat.getLineAt(0);
		const Vec<T, 4> m1 = mat.getLineAt(1);
		const Vec<T, 4> m2 = mat.getLineAt(2);
		const Vec<T, 4> m3 = mat.getLineAt(3);

		Mat<T, 4, 4> result;
		result.setLineAt(0, m0 * rotate._00 + m1 * rotate._01 + m2 * rotate._02);
		result.setLineAt(1, m0 * rotate._10 + m1 * rotate._11 + m2 * rotate._12);
		result.setLineAt(2, m0 * rotate._20 + m1 * rotate._21 + m2 * rotate._22);
		result.setLineAt(3, m3);
		return result;
	}

	template<IsNumeric T>
	Mat<T, 4, 4> rotateDeg(const Mat<T, 4, 4>& mat, T angle, Vec<T, 3> axis)
	{
		return rotate(mat, degToRad(angle), axis);
	}

	template<IsNumeric T>
	Mat<T, 4, 4> scale(const Mat<T, 4, 4>& mat, const Vec<T, 3>& s)
	{
		return {
			mat._00 * s.x, mat._01 * s.x, mat._02 * s.x, mat._03 * s.x,
			mat._10 * s.y, mat._11 * s.y, mat._12 * s.y, mat._13 * s.y,
			mat._20 * s.z, mat._21 * s.z, mat._22 * s.z, mat._23 * s.z,
			mat._30      , mat._31      , mat._32      , mat._33,
		};
	}

	template<IsNumeric T>
	Mat<T, 3, 3> toMat3(const Quat<T>& q)
	{
		constexpr T _1 = static_cast<T>(1);
		constexpr T _2 = static_cast<T>(2);
		
		const T qxx = q.x * q.x;
		const T qyy = q.y * q.y;
		const T qzz = q.z * q.z;
		const T qxz = q.x * q.z;
		const T qxy = q.x * q.y;
		const T qyz = q.y * q.z;
		const T qwx = q.w * q.x;
		const T qwy = q.w * q.y;
		const T qwz = q.w * q.z;

		return {
			_1 - _2 * (qyy + qzz), _2 * (qxy + qwz), _2 * (qxz - qwy),
			_2 * (qxy - qwz), _1 - _2 * (qxx + qzz), _2 * (qyz + qwx),
			_2 * (qxz + qwy), _2* (qyz - qwx), _1 - _2 * (qxx + qyy),
		};
	}

	template<IsNumeric T>
	Mat<T, 4, 4> toMat4(const Quat<T>& q)
	{
		return toMat3(q);
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
	Vec<T, 3> operator*(const Mat<T, 4, 4>& mat, const Vec<T, 3>& v)
	{
		const Vec<T, 4> result = mat * v.homogenous();
		return result / result.w;
	}
}