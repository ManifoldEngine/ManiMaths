#pragma once

#include "Traits.h"
#include <array>

namespace Mani
{
	using MSize = uint8_t;

	template<IsNumeric T, MSize H, MSize W>
	using Matrix = std::array<std::array<T, W>, H>;

	template<IsNumeric T, MSize H, MSize W>
	struct Mat
	{
		Mat() = default;
		template<IsNumeric ...Ts>
		Mat(Ts... args) : values(args...) {};

		MSize height() const { return H; }
		MSize width() const { return W; }
		
		std::array<T, W>& operator[](MSize index) { return values[index]; }
		const std::array<T, W>& operator[](MSize index) const { return values[index]; }

		Matrix<T, H, W> values;
	};

	typedef Mat<float, 4, 4>	Mat4f;
	typedef Mat<double, 4, 4>	Mat4d;
	typedef Mat<float, 3, 3>	Mat3f;
	typedef Mat<double, 3, 3>	Mat3d;

#define TWO_ARGS_TEMPLATE template<IsNumeric T1, MSize H1, MSize W1, IsNumeric T2, MSize H2, MSize W2>

	TWO_ARGS_TEMPLATE
	[[nodiscard]] bool operator==(const Mat<T1, H1, W1>& lhs, const Mat<T2, H2, W2>& rhs)
	{
		static_assert(H1 == H2 && W1 == W2);
		return lhs.values == rhs.values;
	}
}