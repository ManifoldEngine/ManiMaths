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
		Matrix<T, H, W> matrix;
	};
}