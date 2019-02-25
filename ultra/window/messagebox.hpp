#pragma once
#include "defines.h"
#include "window.hpp"
namespace u
{
	class messagebox
	{
	public:
		enum type
		{
			OK_BUTTON = 0x00000000L,
			YesNo,
		};
		enum action
		{
			OK,
			CANCEL,
			YES,
			NO,
		};
		static action show(std::string Title, std::string Content, type t = (type)0, window parent = window())
		{
			action a = OK;
			MessageBoxA(parent.get_handler(), Content.c_str(), Title.c_str(), t);
			return a;
		}
	};
}