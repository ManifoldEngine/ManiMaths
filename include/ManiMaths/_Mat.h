#pragma once

#include "Traits.h"
#include "_Size.h"

namespace Mani
{
	template<IsNumeric T, Size H, Size W>
	struct Mat {};

	// helper struct for matrix that allows to call matrices like so mat[x][y]
	template<IsNumeric T, Size H>
	struct MatLineView
	{
		MatLineView(		T* ptrIn, Size iIn) : m_ptr(ptrIn),			m_i(iIn) {};
		MatLineView(const	T* ptrIn, Size iIn) : m_ptrConst(ptrIn),	m_i(iIn) {};

		T&			operator[](Size j)			{ return *(m_ptr +		(j * H) + m_i); }
		const T&	operator[](Size j) const	{ return *(m_ptrConst + (j * H) + m_i); }
	
	private:
		const T* m_ptrConst = nullptr;
		T* m_ptr = nullptr;
		Size m_i = 0;
	};
}