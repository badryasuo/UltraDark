#ifndef DARK_STRING
#define DARK_STRING
#include "char.hpp"
#include "darkdef.h"
#ifdef WIN32
#pragma warning(disable:4996)
#endif
#include <memory>
namespace dark
{
	namespace cstr
	{
		int length(const char * cstr);
		// return the size of `cstr`
		int size(const char * cstr)
		{
			if (!cstr)
				return 0;
			int i = 1;
			while (*cstr && ++i && *cstr++);
			return i;
		}
		// return the length of `cstr`
		int length(const char * cstr)
		{
			if (!cstr)
				return 0;
			int i = 0;
			while (*cstr && ++i && *cstr++);
			return i;
		}
		// return the alphabetic letters count
		int count_alpha(const char* cstr)
		{
			if (!cstr || *cstr == 0)
				return 0;

			int len = length(cstr);
			int i = -1;
			int n = 0;
			while (i++ < len)
				if (dark::c::isalpha(cstr[i]))
					++n;
			return n;
		}
		// return the alphabetic words count
		int count_alphawords(const char* cstr)
		{
			if (!cstr || *cstr == 0)
				return 0;
			int n = 0;
			for (int i = length(cstr); i > 0; --i)
				if (dark::c::isalpha(cstr[i]) && !dark::c::isalpha(cstr[i + 1]))
					++n;
			return n;
		}
		char * create(const char * from)
		{
			if (!from)
				return 0;
			size_t len = size(from);
			char * to = new char[len];
			for (int i = len; i > -1; --i)
				to[i] = from[i];
			return to;
		}
		char** arrcpy(char** to, char** from, int size)
		{
			for (int i = 0; i < size; ++i)
			{
				to[i] = (char*)calloc(1, strlen(from[i] + 1));
				strcpy(to[i], from[i]);
			}
			return to;
		}
		char** split(const char * string, char delimiter)
		{
			char ** matrix = (char**)malloc(1);
			size_t len = strlen(string);
			int n, c, i;
			n = c = i = 0;
			char *item = (char*)malloc(i + 1);
			for (; string[c] != '\0'; ++i, ++c)
			{
				item = (char*)realloc(item, 50 + 1);
				item[i] = string[c];
		
				if (string[c] == delimiter)
				{
					item[i] = '\0';
					matrix[n] = (char*)calloc(1, i + 1);
					strcpy(matrix[n], item);
					i = -1;
					++n;
					char** temp = (char**)calloc(1, n + 1);
					arrcpy(temp, matrix, n);
					matrix = (char**)realloc((char**)matrix, n + 1);
					arrcpy(matrix, temp, n);
					//printf("%s\n", matrix[n-1]);
				}
			}
			item[i] = '\0';
			matrix[n] = (char*)calloc(1, i + 1);
			strcpy(matrix[n], item);
			//printf(matrix[1]);
			return matrix;
		}
		char ** split(const char * string, char ** to, char delimiter)
		{
			size_t len = length(string);
			int n = 0;
			if (string && to)
			{
				int n = 0;
				int c = 0;	
				int i = 0;
				for (; string[c] != '\0'; i++, c++)
				{
					to[n][i] = string[c];
					if (string[c] == delimiter)
					{
						to[n][i] = '\0';
						i = -1;
						++n;
					}
				}
				to[n][i] = '\0';
			}
			return to;
		}
		char * allocate(long bytes)
		{
			return (char *)calloc(1, bytes);
		}
		wchar_t * wallocate(long bytes)
		{
			return (wchar_t *)calloc(1, bytes);
		}
		char ** allocate(int slots, long bytes)
		{
			char ** arr = (char **)calloc(1, slots);
			for (int i = 0; i <= slots; ++i)
			{
				arr[i] = (char *)calloc(1, bytes);
			}
			return arr;
		}
		int endsWith(const char * cstring, const char * end)
		{
			if (cstring && end)
			{
				int len = dark::cstr::length(cstring);
				int end_len = dark::cstr::length(end);
				for (int i = 0; i <= end_len; ++i)
					if (cstring[len - end_len + i] != end[i])
						return 0;
				return 1;
			}
			return 0;
		}
		char* tolower(const char * cstring)
		{
			char * str = (char*)calloc(1, size(cstring));
			int i = 0;
			while (cstring[i])
			{
				str[i] = dark::c::tolower(cstring[i]);
				i++;
			}
			return str;
		}
		char* toupper(const char * cstring)
		{
			char * str = (char*)calloc(1, size(cstring));
			int i = 0;
			while (cstring[i])
			{
				str[i] = dark::c::toupper(cstring[i]);
				i++;
			}
			return str;
		}
		dark::index findchar(const char * str, const char x)
		{
			size_t i = 0;
			while (str[i++])
				if (str[i] == x)
					return i;
			return -1;
		}
		dark::index find(const char * str, const char * x)
		{
			size_t result = 0;
			size_t length = dark::cstr::length(x);
			size_t checked = 0;
			while (*str)
			{	
				while (checked < length)
				{
					if (*(str++ + checked) != *(x + checked))
						break;
					else
						if (++checked == length)
							return result;
				}
				result++;
			}
			return -1;
		}
		char* copy(char * str, const char * x)
		{
			if (str && x)
				while (*str++ = *x++);
			else
				return 0;
			return str;
		}
		char * append(const char * str, const char * x)
		{
			char * ptr;
			if (str && x)
			{
				size_t len_str = length(str);
				size_t to_be_copied = size(x);
				ptr = dark::cstr::allocate(len_str + to_be_copied);
				copy(ptr, str);
				int i = 0;
				while (*(ptr + len_str + i++) = *x++);
			}
			else
				return 0;
			str = ptr;
			return ptr;
		}
	}
	class str
	{
	private:
		char_ptr data;
		size_t str_length;
		size_t lastFound = 0;
	protected:
		friend std::ostream& operator <<(std::ostream& os, dark::str string);
	public:
		enum
		{
			first = 1,
			last = -75
		};
		char * operator =(const char* str)
		{
			return (data = dark::cstr::create(str));
		}
		char * operator +(const char* str)
		{
			return dark::cstr::append(data, str);;
		}
		char * operator +=(const char* str)
		{
			char * x = dark::cstr::append(data, str);
			data = x;
			str_length += cstr::length(str);
			return x;
		}
		str() : data(cstr::allocate(1)), str_length(0)
		{
			
		}
		str(const char* str) :data(cstr::create(str)), str_length(cstr::length(str))
		{}
		~str(){}
		size_t length()
		{
			return this->str_length;
		}
		int rewind()
		{
			lastFound = 0;
			return 1;
		}
		dark::index find(const char* x)
		{
			index n = dark::cstr::find(data + lastFound, x);
			if (n != -1)
			{
				lastFound == 0 ? lastFound++ : lastFound = n+1;
				return lastFound;
			}
			return -1;
		}
		dark::index indexof(const char x)
		{
			return dark::cstr::findchar(data, x);
		}
		dark::index indexofpos(const char* x, dark::index position)
		{
			index last_found = 0;
			size_t len = this->str_length;
			while (position--)
			{
				index n = dark::cstr::find(data + last_found, x);
				if (n == -1)
					return last_found == 0 ? -1 : lastFound;
				else
					last_found == 0 ? last_found++ : last_found+=n;
			}
			return last_found;
		}
		dark::index indexof(const char* x)
		{
			return dark::cstr::find(data, x);
		}
		str toupper()
		{
			return str(dark::cstr::toupper(data));
		}
		str tolower()
		{
			return str(dark::cstr::tolower(data));
		}
		char * c_str()
		{
			return cstr::create(this->data);
		}

	};
	std::ostream& operator <<(std::ostream& os, dark::str string)
	{
		return os << string.data;
	}
	namespace _string
	{
		int endsWith(std::string str, std::string end)
		{
				for (unsigned int i = 0; i <= end.size(); ++i)
					if (str[str.size() - end.size() + i] != end[i])
						return 0;
				return 1;
		}
		std::string replace(std::string str, std::string replace, std::string with)
		{
			size_t pattern;
			if ((pattern = str.find(replace)) != std::string::npos)
				str.replace(pattern, replace.length(), with);
			return str;
		}
		std::string replaceall(std::string str, std::string replace, std::string with)
		{
			size_t pattern = 0;
			while ((pattern = str.find(replace, pattern)) != std::string::npos)
				str.replace(pattern, replace.length(), with);
			return str;
		}
		std::string cutout(std::string str, const  std::string start, const  std::string end)
		{
			size_t pattern;
			if ((pattern = str.find(start)) != std::string::npos)
			{
				str.replace(0, pattern + 1, "");
				if ((pattern = str.find(end)) != std::string::npos)
					str.replace(pattern, str.size(), "");
			}
			return str;
		}
		std::string cutout(std::string str, const  std::string start,
			const  std::string end, const  size_t fromPos)
		{
			size_t pattern;
			if ((pattern = str.find(start, fromPos)) != std::string::npos)
			{
				str.replace(0, pattern + 1, "");
				if ((pattern = str.find(end)) != std::string::npos)
					str.replace(pattern, str.size(), "");
			}
			return str;
		}
		std::string cut(std::string str, const  std::string toCut)
		{
			size_t pattern;
			if ((pattern = str.find(toCut)) != std::string::npos)
				str.replace(pattern, toCut.size(), "");
			return str;
		}
		std::string cutall(std::string str, const  std::string toCut)
		{
			size_t pattern = 0;
			while ((pattern = str.find(toCut, pattern)) != std::string::npos)
				str.replace(pattern, toCut.size(), "");
			return str;
		}
	}
}
#endif