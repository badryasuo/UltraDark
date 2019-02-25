#pragma once
#include "defines.h"
namespace u
{
	template<typename numeric>
	inline const numeric fastcall abs(const numeric &x)
	{
		return x < 0 ? -x : x;
	}
	// returns the Power of X
	inline const double fastcall pow(double X, double N)
	{
		unsigned p = static_cast<unsigned>(abs(N));
		double result = 1;
		while (p > 0)
		{
			if (p & 1) // if bit is set
				result = result * X;
			p = p >> 1;
			X *= X;
		}
		if (N < 0)
			return 1 / result;
		return result;
	}
	// returns the Square Root of X
	inline const long double declspec_naked fastcall sqrt(const long double X)
	{
		_asm fld qword ptr[esp + 4]
			_asm fsqrt
		_asm ret 8
	}
	// returns the Square Root of X
	template<typename T>
	inline T fastcall sqrt(T &X)
	{
		return static_cast<T>(sqrt(static_cast<long double>(X)));
	}
}