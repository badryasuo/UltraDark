/*********************************************************/
//	Dark World Library Header	**************************/
// 	Version 	: 	Pre-Beta 	**************************/
// 	Copyright 	: 	Dark World 	**************************/
// 	Se tu vuoi 	: 	Programmed By Only Kira. 	**********/
/*#######################################################*/
#ifndef _DARK_
#define _DARK_
#ifndef D_A_R_K_CONSTANTS
#define D_A_R_K_CONSTANTS
#define DARK_TRUE 1
#define DARK_FALSE 0
#endif
#ifdef __cplusplus
#include "darkdef.h"
#include "math.hpp"
#include "string.hpp"
#include "char.hpp"
#include "algorithms.hpp"
namespace dark
{
	class out
	{
	public:
		template<typename Data>
		out(Data data)
		{
			int i = 0;
			while (data[i] && putchar(data[i++]));
		}
		out operator <<(const out&data)
		{

		}
	};
	class to
	{
	public:
		static inline int32 int32(const char* from)
		{
			int to = isdigit(*from) ? *from - char_0 : 0;
			while ((*(++from)) && (to *= 10) && isdigit(*from))
				to += *from - char_0;
			return to;
		}
		static inline int64 int64(const char * from)
		{
			long long to = isdigit(*from) ? *from - char_0 : 0;
			while ((*(++from)) && (to *= 10) && isdigit(*from))
				to += *from - char_0;
			return to;
		}
		static inline uchar uchar(int8 from)
		{
			return from == 0 ? '0' :
				from == 1 ? '1' : from == 1 ? '1' : from == 2 ? '2' :
				from == 3 ? '3' : from == 4 ? '4' : from == 5 ? '5' :
				from == 6 ? '6' : from == 7 ? '7' : from == 8 ? '8' :
				from == 9 ? '9' : '\0';
		}
		static inline char_ptr char_ptr(long long from)
		{
			unsigned char negative = from < 0;
			ushort i = math::digits(from);
			char* to = dark::cstr::allocate(i);
			if (negative && (*to = '-') & (from = -from) & i++);
			*(to + i) = 0;
			while (
				(i>0 + negative) &&
				(*(to + (--i)) = to::uchar(((from) % 10))) |
				(from /= 10)
				);
			return to;
		}
	};
}
#endif
#endif
