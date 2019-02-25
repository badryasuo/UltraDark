#pragma once
#include <stdint.h>
namespace u
{
	inline auto encrypt(std::string str, size_t key)
	{
		size_t len = str.length();
		const char* data = str.c_str();
		char* newData = new char[len + 1];
		for (int i = 0; i < len; ++i)
			*(newData + i) = (char)(*(data + i) ^ key);
		return newData;
	}
}