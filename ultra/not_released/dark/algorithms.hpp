#ifndef DARK_ALGORITHMS
#define DARK_ALGORITHMS
#include "std.hpp"
#ifdef WIN32
#pragma warning(disable:4390)
#endif
namespace dark
{
	size_t is_char_there(const char * str, char x)
	{
		while (*str)
			if (*str++ == x)
				return 1;
		return 0;
	}
	char * removeDuplicates(char* str)
	{
		char seen[UCHAR_MAX + 1] = { 0 };

		//
		// Smallest data type is a char (unless you want to bit
		// twiddle, and that has been shown to be not worth it
		// see the complaints about std::vector<bool> in C++).
		// 256 bytes is not much.
		// 
		// By using char as they type it prevents all the complex
		// multiplication/division an bit twiddling that Ant was doing.
		int size = dark::cstr::size(str);
		unsigned char* ptr = (unsigned char*)calloc(1, size);
		memcpy(ptr, str, size);
		unsigned char* source = (unsigned char*)ptr;
		unsigned char* dest = (unsigned char*)ptr;
		unsigned char  next;
		do
		{
			next = *source;       // Get next character.
			if (!seen[next])       // Only enter the `if block` if we have not seen it.
			{
				seen[next] = 1;    // Mark it as seen
				*dest = next;      // Move it to destination.
								   // Note: source will change faster than dest when we
								   //       start seeing dupes, this acts as the copy back
								   //       over the duplicates.
				++dest;
			}
			++source;
		} while (next != '\0');      // Once we have copied the null terminator quit.

		return (char *)ptr;
	}


	char * similar(const char * s1, const char * s2)
	{
		if (!s1 || !s2 || *s1 == 0 || *s2 == 0)
			return 0;
		unsigned s1_len = dark::cstr::length(s1);
		unsigned s2_len = dark::cstr::length(s2);
		char * found = (char*)calloc(1, s1_len > s2_len ? s1_len : s2_len);
		char * ptr = found;
		for (unsigned long long x = 0; x < s1_len; ++x)
		{
			for (unsigned long long y = 0; y < s2_len; ++y)
			{
				if (s1[x] == s2[y] && !is_char_there(found, s2[y]) && (*ptr++ = s1[x]))
				{
					++x;
				}

			}
		}
		return found;
	}

	double similarity(const char * str1, const char * str2)
	{
		char* s1 = removeDuplicates((char*)str1);
		char* s2 = removeDuplicates((char*)str2);

		unsigned long long s1_len = strlen(s1);
		unsigned long long s2_len = strlen(s2);
		unsigned long long max = s1_len > s2_len ? s1_len : s2_len;
		int similar = 0;
		for (unsigned long long x = 0; x < s1_len; ++x)
			for (unsigned long long y = 0; y < s2_len; ++y)
				if (s1[x] == s2[y] && ++similar);
		return ((double)similar / (double)max);
	}
};
#endif