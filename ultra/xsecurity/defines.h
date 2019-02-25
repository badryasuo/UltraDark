#pragma once
#if defined(_MSC_VER)
//  Microsoft 
#define declspec_naked __declspec(naked)
#define fastcall __fastcall
#elif defined(__GNUC__)
//  GCC
#define declspec_naked __attribute__ ((naked))
#define fastcall __attribute__((fastcall))
#else

#endif
#include <string>