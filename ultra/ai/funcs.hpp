#pragma once
#include "defines.h"
namespace u
{
	/*
	signum function:
	In mathematics, the sign function or signum function is an odd mathematical function
	that extracts the sign of a real number.
	In mathematical expressions the sign function is often represented as sgn.*/
	template<typename N>
	auto sgn(const N x)
	{
		return x >= 0 ? +1 : -1;
	}

	template<typename N>
	auto sgm(const N x)
	{
		//return 1 / (1 + pow(e,-x));
		return x / (1 + abs(x));
	}
	template<typename N>
	auto step(const N x)
	{
		return x >= 0 ? +1 : 0;
	}
	template<typename N>
	auto ramp(const N x)
	{
		return x >= 1 ? +1 : x <= -1 ? -1 : x;
	}

}