#pragma once
#include <vector>
#include <string>
namespace ultra
{
	inline bool isalpha(const char &x)
	{
		return (x >= 'A' && x <= 'Z') || (x >= 'a' && x <= 'z');
	}
	inline bool isdigit(const char &x)
	{
		return x >= '0' && x <= '9';
	}
	inline bool isalphanumeric(const char & x)
	{
		return isalpha(x) || isdigit(x);
	}
	inline bool isspace(const char & x)
	{
		return x == ' ' || x == '\t' || x == '\r' || x == '\n';
	}
	inline bool is_string_alphanumeric(const std::string &str)
	{
		int i = 0;
		while (str[i])
		{
			if (!isalphanumeric(str[i]))
				return false;
			i++;
		}
		return true;
	}
	inline bool isnumeric(const std::string &str)
	{
		int i = 0;
		while (str[i])
		{
			if (!isdigit(str[i]))
				return false;
			i++;
		}
		return true;
	}
	inline bool is_there(std::string key, char x)
	{
		int i = 0;
		while (key[i])
		{
			if (key[i++] == x)
				return true;
		}
		return false;
	}
	inline int to_int(const char c)
	{
		return isdigit(c) ? c - '0' : NULL;
	}
	template< typename character>
	inline int to_int(const character *s)
	{
		size_t len = ultra::strlen(s);
		int r = NULL;
		while (*s)
		{
			r = isdigit(*s) ? to_int(*s) + (r * 10) : NULL;
			*s++;
		}
		return r;
	}
	
	template<typename character>
	inline size_t strlen(character* str)
	{
		size_t i = 0;
		while (str[++i]);
		return i;
	}
	template<typename character>
	inline character* copy(character *destination, const character *source)
	{
		character *p = destination;
		while (*destination++ = *source++);
		return p;
	}
	template<typename character>
	inline character* multiply(const character *str, unsigned times)
	{
		size_t len = ultra::strlen(str);
		character *multiplied_str = (character*)calloc(1, len * times + 1);
		for (unsigned i = 0; i < times; ++i)
			ultra::copy(multiplied_str + (len * i), str);
		return multiplied_str;
	}
	
	/* Splitting a string by a delimiter */
	
	inline std::vector<std::string> split(std::string data, char delimiter)
	{
		std::vector<std::string> list;
		std::string tmp;
		size_t i = 0;
		for (; data[i] != NULL; ++i)
		{
			tmp += data[i];
			if (data[i] == delimiter)
			{
				tmp.erase(tmp.end() - 1);
				list.push_back(tmp);
				tmp.clear();
			}
		}
		if (tmp.length() > 0)
			list.push_back(tmp);
		return list;
	}
	inline std::vector<std::string> split(std::string data, char delimiter, bool delimeter_included)
	{
		std::vector<std::string> list;
		std::string tmp;
		size_t i = 0;
		for (; data[i] != NULL; ++i)
		{
			tmp += data[i];
			if (data[i] == delimiter)
			{
				if(!delimeter_included)
					tmp.erase(tmp.end() - 1);
				list.push_back(tmp);
				tmp.clear();
			}
		}
		if (tmp.length() > 0)
			list.push_back(tmp);
		return list;
	}
	inline std::vector<std::string> split(std::string data, std::vector<char> delimiters)
	{
		std::vector<std::string> list;
		std::string tmp;
		size_t i = 0;
		for (; data[i] != NULL; ++i)
		{
			tmp += data[i];
			if (std::find(delimiters.begin(), delimiters.end(), data[i]) != delimiters.end())
			{
				tmp.erase(tmp.end() - 1);
				list.push_back(tmp);
				tmp.clear();
			}
		}
		if (tmp.length() > 0)
			list.push_back(tmp);
		return list;
	}
	inline std::vector<std::string> split(std::string data, std::vector<char> delimiters, bool delimeter_included)
	{
		std::vector<std::string> list;
		std::string tmp;
		size_t i = 0;
		for (; data[i] != NULL; ++i)
		{
			tmp += data[i];
			if (std::find(delimiters.begin(), delimiters.end(), data[i]) != delimiters.end())
			{
				if (!delimeter_included)
					tmp.erase(tmp.end() - 1);
				list.push_back(tmp);
				tmp.clear();
			}
		}
		if (tmp.length() > 0)
			list.push_back(tmp);
		return list;
	}

	enum from
	{
		START_TO_END = 0,
		END_TO_START = 1,
		FIRST_TO_LAST = 2
	};
	template<typename T, typename Item>
	T takebetween(T &object, Item start, Item to)
	{
		int start_index = -1, last_index = -1;
		if (start == to)
		{
			for (unsigned i = 0; i < object.size(); ++i)
			{
				if (object[i] == start)
				{
					if (start_index >= 0)
					{
						if (object[i - 1] != '\\')
						{
							last_index = i;
							break;
						}
					}
					else
						start_index = i;
				}
			}
		}
		else
		{
			unsigned n = 0;
			for (unsigned i = 0; i < object.size(); ++i)
				if (object[i] == start)
				{
					start_index = i;
					break;
				}
			for (unsigned i = start_index; i < object.size(); ++i)
			{
				if (object[i] == start)
					++n;
				else if (n > 1 && object[i] == to)
					--n;
				else if (n == 1 && object[i] == to)
				{
					last_index = i;
					break;
				}
			}
		}
		if (last_index == -1)
			return T();
		T t(object.begin() + ++start_index, object.begin() + last_index);
		object.erase(start_index, t.size());
		return t;
	}
	template<typename T, typename Item>
	T takebetween(const T &object, Item start, Item to)
	{
		unsigned start_index = 0, last_index = 0;
		unsigned n = 0;
		for (unsigned i = 0; i < object.size(); ++i)
			if (object[i] == start)
			{
				start_index = i;
				break;
			}
		for (unsigned i = start_index; i < object.size(); ++i)
		{
			if (object[i] == start)
				++n;
			else if (n > 1 && object[i] == to)
				--n;
			else if (n == 1 && object[i] == to)
			{
				last_index = i;
				break;
			}
		}
		if (last_index == 0)
			return T();
		return T(object.begin() + ++start_index, object.begin() + last_index);
	}


	/* takewhile */
	
	template<typename T, typename Items>
	T takewhile(T &object, std::initializer_list<Items> eqs, from f = from::START_TO_END)
	{
		T taken;
		// copy the whole pointer of the string.
		auto start = object.begin();
		// copy the pointer at the end of the string
		auto end = object.end();
		if (!object.empty())
		{
			if (f == from::START_TO_END)
			{
				auto till = start;
				while (till != end)
				{
					// if condition is true, then just increament `till` pointer.
					if (std::find(eqs.begin(), eqs.end(), *till) == eqs.end())
						// otherwise if false, break!
						break;
					++till;
				}
				taken = T(start, till);
				// till - start = the number of taken items;
				object.erase(0, till - start);
			}
			else
			{
				auto till = end;
				while (--till != start)
				{
					// if condition is true, then just increament `till` pointer.
					if (std::find(eqs.begin(), eqs.end(), *till) == eqs.end())
						// otherwise if false, break!
						break;
				}
				taken = T(till + 1, end);
				object.erase(object.size() - taken.size(), object.size());
			}
		}
		return taken;
	}
	template<typename T, typename Item>
	T takewhile(T &object, bool(*condition)(Item x), from f = from::START_TO_END)
	{
		T taken;
		// copy the whole pointer of the string.
		auto start = object.begin();
		// copy the pointer at the end of the string
		auto end = object.end();
		if (!object.empty())
		{
			if (f == from::START_TO_END)
			{
				auto till = start;
				while (till != end)
				{
					// if condition is true, then just increament `till` pointer.
					if (!condition(*till))
						// otherwise if false, break!
						break;
					++till;
				}
				taken = T(start, till);
				// till - start = the number of taken items;
				object.erase(0, till - start);
			}
			else
			{
				auto till = end;
				while (--till != start)
				{
					// if condition is true, then just increament `till` pointer.
					if (!condition(*till))
						// otherwise if false, break!
						break;
				}
				taken = T(till + 1, end);
				object.erase(object.size() - taken.size(), object.size());
			}
		}
		return taken;
	}
	template<typename T, typename Item>
	T takewhilenot(const T &t, bool(*condition)(Item x))
	{
		auto start = t.begin();
		auto till = start;
		auto end = t.end();
		while (till != end)
		{
			if (!condition(*start))
				++till;
			else
				break;
		}
		return T(start, till);
	}
	template<typename T, typename Items>
	T takewhilenot(T &object, std::initializer_list<Items> eqs)
	{
		auto start = object.begin();
		auto till = start;
		auto end = object.end();
		while (till != end)
		{
			if (std::find(eqs.begin(), eqs.end(), *till) == eqs.end())
				++till;
			else
				break;
		}
		T t(start, till);
		object.erase(0, till - start);
		return t;
	}
	// skipwhile : 4 overloads.
	/// <param name='object'>Object to skip items in it, *must have* ::begin() and ::end() as public functions.</param>
	/// <param name='condition'>Either you can choose a condition from the ultra:: namespace or use ultra::equals&lt;Your_Object_Type&gt;(initializer_list) or even create your own condition but make sure it returns only a boolean.</param>
	/// <summary>
	/// <para>Skips the items in an Object while they meet certain condition.</para>
	/// <para>And finally returns the rest of the object.</para>
	/// </summary>
	template<typename T, typename Item>
	T skipwhile(T &object, bool(*predicate)(Item x), from f = from::START_TO_END)
	{
		auto start = object.begin();
		auto end = object.end();
		unsigned i = 0;
		if (!object.empty())
		{
			if (f == from::START_TO_END)
			{
				for(; i < object.size(); ++i)
					if (!predicate(object[i]))
						break;
				object.erase(0, i);
			}
			else
			{
				while (--end != start)
					if (!predicate(*end))
						break;
				// object.end() - end == skipped characters;
				object.erase((object.size() + 1) - (object.end() - end), object.size());
			}
		}
		return T(start, end);
	}
	template<typename T, typename Items>
	T skipwhile(T &object, std::initializer_list<Items> eqs, from f = from::START_TO_END)
	{
		auto start = object.begin();
		auto end = object.end();
		if (!object.empty())
		{
			if (f == from::START_TO_END)
			{
				while (start != end)
				{
					if (std::find(eqs.begin(), eqs.end(), *start) == eqs.end())
						break;
					++start;
				}
				object.erase(0, start - object.begin());
			}
			else
			{
				while (--end != start)
				{
					if (std::find(eqs.begin(), eqs.end(), *end) == eqs.end())
						break;
				}
				// object.end() - end == skipped characters;
				object.erase((object.size() + 1) - (object.end() - end), object.size());
			}
		}
		return T(start, end + 1);
	}
	// skipwhilenot : 4 overloads.

	template<typename T, typename Item>
	T skipwhilenot(const T &t, bool(*predicate)(Item x))
	{
		auto start = t.begin();
		auto end = t.end();
		while (start != end)
		{
			if (predicate(*start))
				break;
			++start;
		}
		return T(start, end);
	}
	template<typename T, typename Items>
	T skipwhilenot(T &object, std::initializer_list<Items> eqs, from f = from::START_TO_END)
	{
		auto start = object.begin();
		auto end = object.end();
		if (!object.empty())
		{
			if (f == from::START_TO_END)
			{
				while (start != end)
				{
					if (std::find(eqs.begin(), eqs.end(), *start) != eqs.end())
						break;
					++start;
				}
				object.erase(0, start - object.begin());
			}
			else
			{
				while (--end != start)
				{
					if (std::find(eqs.begin(), eqs.end(), *end) != eqs.end())
						break;
				}
				// object.end() - end == skipped characters;
				object.erase((object.size() + 1) - (object.end() - end), object.size());
			}
		}
		return T(start, end);
	}

	/* Convert x to string */
	
	inline std::string to_string(const bool &x)
	{
		return x ? "true" : "false";
	}

	/* Convert x to bool*/
	inline bool to_bool(std::string x)
	{
		return x == "true" || x == "1" ? true : false;
	}

}