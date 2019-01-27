#ifndef DARK_PARSER
#define DARK_PARSER
#include "std.hpp"
#include <stdlib.h>
#include <fstream>
#include <sstream>
namespace dark
{
	class cfgparser
	{
	private:
		std::ifstream file;
		const wchar_t * path;
		std::stringstream datastream;
		dark::str data;
	protected:
	public:
		cfgparser(const wchar_t * name) : path(name)
		{
			file.open(name);
			datastream << file.rdbuf();
			std::string s = datastream.str();
			data = datastream.str().c_str();
		}
		~cfgparser()
		{
			file.close();
		}
		char_ptr valueof(const char * key, size_t length)
		{
			char_ptr value = dark::cstr::allocate(length+1);
			dark::index pos = 0;
			size_t newline = 0;
			/*if ((pos = data.indexof(key)) != -1)
			{
				while (data[pos])
				{
					if (data[pos] == '=')
					{
						while (dark::c::isalpha(data[pos]) || dark::c::isdigit(data[pos]))
						{
							//dark::cstr::append(value, data[pos]);
							pos++;
						}
					}
					pos++;
				}
				std::cout << "pos=" << pos << std::endl;
				if ((newline = dark::cstr::find(data, "\n")) != -1)
				{
					std::cout << "newline=" << newline << std::endl;
					//val = data.substr(pos, newline);
				}
			}*/
			return 0;
		}
	};
}
#endif