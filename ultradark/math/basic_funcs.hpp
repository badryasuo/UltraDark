#pragma once
namespace ultra
{
	template<typename numeric>
	inline const numeric &abs(const numeric &x)
	{
		return x < 0 ? -x : x;
	}
	inline const double &pow(const int &x, const int &n)
	{
		if (x == 1)
			return x;
		if(x == 0x2)
			return n > 0 ? x << (n-1) : 1. / (double)(x << (abs(n)-1));
		else
		{
			return -1;
		}

	}
}