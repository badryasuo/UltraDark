#pragma once
#include "defines.h"
namespace u
{
	class window
	{
		WindowHandler handler = nullptr;
	public:
		WindowHandler get_handler()
		{
			return this->handler;
		}
	};
}