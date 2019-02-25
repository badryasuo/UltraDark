#pragma once
#include "defines.h"
#include "../xvector.hpp"
namespace u
{
	struct bitstring
	{
		bitstring() {}
		bitstring(std::string bitstr)
		{
			for(unsigned i = 0; i < bitstr.size(); ++i)
				bits.push_back(bitstr[i] & 1);
		}
	private:
		u::xvector<u::bit> bits;
	};
}