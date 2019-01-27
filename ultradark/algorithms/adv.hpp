#pragma once
#include <ultradark/algorithms/basic.hpp>
#include <algorithm>
#include <string>
#undef offsetof
namespace ultra
{
	struct position
	{
		int x =	0, y = 0;
		void operator +=(position p)
		{
			x += p.x;
			y += p.y;
		}
	};
	static void append_position(std::string s, position &p)
	{
		if (p.y == 0)
			p.y = 1;
		std::vector<std::string> lines = { "" };
		for(char c : s)
		{
			if (c == '\n')
			{
				p.x = 0;
				lines.push_back(std::string());
			}
			else
				lines.back() += c;
				
		}
		p.y += lines.size() - 1;
		p.x += lines.back().size();	
	}
	std::string takewhile_addpos(std::string &string, bool(*condition)(const char &x), position &pos)
	{
		std::string taken = takewhile(string, condition, from::START_TO_END);
		append_position(taken, pos);
		return taken;
	}
	std::string skipwhile_addpos(std::string &string, bool(*condition)(const char &x), position &pos)
	{
		std::string taken = takewhile(string, condition, from::START_TO_END);
		append_position(taken, pos);
		return string;
	}
	std::string takebetween_addpos(std::string &string, char start, char to, position &pos)
	{
		std::string taken = takebetween(string, start, to);
		append_position(taken, pos);
		pos.x += 2;
		return taken;
	}
	static inline std::string trim(const std::string &s) {
		std::string str = s;
		for (unsigned i = 0; i < str.size(); ++i)
			if (ultra::isspace(str[i]))
				str.erase(i, 1);
		return str;
	}
	template<typename T, typename U>
	constexpr size_t offsetof(U T::*member)
	{
		return ((char*)&((T*)nullptr->*member) - (char*)nullptr) / sizeof(&member);
	}
}