#pragma once
#include <string>
namespace u
{
	typedef bool bit;
	struct byte
	{
		byte() {}
		byte(const char byte_string[8])
		{
			bits[0] = byte_string[0] & 1;
			bits[1] = byte_string[1] & 1;
			bits[2] = byte_string[2] & 1;
			bits[3] = byte_string[3] & 1;
			bits[4] = byte_string[4] & 1;
			bits[5] = byte_string[5] & 1;
			bits[6] = byte_string[6] & 1;
			bits[7] = byte_string[7] & 1;
		}
		bit operator[](const int &i)
		{
			if (i < 0)
				return this->operator[](8 - i);
			else if (i >= 8)
				return this->operator[](i - 8);
			return bits[i];
		}
	private:
		bit bits[8] = { 0 };
		friend std::ostream &operator<<(std::ostream &, byte &);
	};
	std::ostream &operator<<(std::ostream &os, byte &b)
	{
		for (char i = 0; i < 8; ++i)
			os << b.bits[i];
		return os;
	}
}