#pragma once

namespace Mani
{
	template<IsNumeric T>
	struct Mat<T, 3, 3>
	{
		T _00, _01, _02;
		T _10, _11, _12;
		T _20, _21, _22;

		operator Mat<T, 4, 4>() {
			constexpr T _0 = static_cast<T>(0);
			constexpr T _1 = static_cast<T>(1);
			return {
				_00, _01, _02, _0,
				_10, _11, _12, _0,
				_20, _21, _22, _0,
				 _0,  _0,  _0, _1,
			};
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
}