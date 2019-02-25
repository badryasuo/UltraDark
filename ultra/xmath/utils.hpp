#pragma once
namespace u
{
	bool prime(unsigned long&x)
	{
		unsigned long l = u::sqrt(x);
		for (unsigned long i = 2; i <= l; ++i)
			if (x % l == 0)
				return false;
		return true;
	}
}