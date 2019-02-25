#pragma once
#ifdef _WIN32
#include <Windows.h>
#include <string>
typedef HWND WindowHandler;
#else
typedef unsigned* WindowHandler;
#endif