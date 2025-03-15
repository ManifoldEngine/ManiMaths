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
	Mat<T, 4, 4> lookAt(const Vec<T, 3>& eye, const Vec<T, 3>& center, const Vec<T, 3>& up)
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

	template<IsNumeric T>
	Mat<T, 3, 3> toMat3(const Quat<T>& q)
	{
		return static_cast<Mat<T, 3, 3>>(q);
	}

	template<IsNumeric T>
	Mat<T, 4, 4> toMat4(const Quat<T>& q)
	{
		return toMat3(q);
	}
}