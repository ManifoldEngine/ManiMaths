#pragma once

#include "ManiMaths/_Mat.h"
#include "Debug.h"
#include "Traits.h"

namespace Mani
{
	template<IsNumeric T>
	struct Mat<T, 4, 4>
	{
		T _00, _01, _02, _03;
		T _10, _11, _12, _13;
		T _20, _21, _22, _23;
		T _30, _31, _32, _33;
	};

	typedef Mat<float,	4, 4> Mat4f;
	typedef Mat<double, 4, 4> Mat4d;

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
}