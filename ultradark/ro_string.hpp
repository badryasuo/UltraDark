#pragma once
#include "ro_int.hpp"
#include <iosfwd>
#include <string>
#pragma warning(disable : 4996)
namespace ultra
{
	template <typename write_access> struct ro_string;

	template <typename T>
	bool operator == (const char*, ro_string<T>);
	template <typename T>
	bool operator == (ro_string<T>, const char*);
	template <typename T>
	bool operator == (ro_string<T>, ro_string<T>);
	template <typename T>
	bool operator == (ro_string<T>, std::string);
	template <typename T>
	bool operator == (std::string, ro_string<T>);

	template <typename T>
	std::string operator + (const ro_string<T>&, const std::string&);
	template <typename T>
	std::string operator + (const std::string&, const ro_string<T>&);

	template<typename T>
	std::ostream& operator << (std::ostream&, ro_string<T>&);

	template<typename write_access>
	struct ro_string
	{
		friend write_access;
		friend bool operator == <write_access> (const char*, ro_string&);
		friend bool operator == <write_access> (ro_string&, const char*);
		friend bool operator == <write_access> (ro_string&, ro_string&);
		friend bool operator == <write_access> (ro_string&, std::string&);
		friend bool operator == <write_access> (std::string&, ro_string&);
		friend std::string operator + <write_access> (const ro_string&, const std::string&);
		friend std::string operator + <write_access> (const std::string&, const ro_string&);

		friend std::ostream& operator << <write_access> (std::ostream&, ro_string&);
		friend struct ro_int;

		ro_size_t<ro_string> length;
		operator std::string() { return std::string(this->s); }
		char* c_str() { return this->s; }
		std::string toString() { return std::string(this->s); }

		char operator [] (unsigned int i)
		{
			if (i < length.v)
				return s[i];
			else return 0;
		}
		ro_string operator + (ro_string str)
		{
			char * new_str = new char[this->length + str.length + 1];
			strcpy(new_str, this->s);
			strcpy(new_str + length, str.s);
			return ro_string(new_str);
		}
		char* operator + (const char* str)
		{
			char * new_str = new char[this->length + strlen(str) + 1];
			strcpy(new_str, this->s);
			strcpy(new_str + length, str);
			return new_str;
		}
		~ro_string()
		{
			if (this->s && *this->s && this->s != NULL && (this->s+2))
			{
				s = new char[length + 1];
				delete[] this->s;
			}
		}
	private:
		char* s = NULL;
		ro_string() { s = new char[2]; }
		explicit ro_string(const char* str)
		{
			if (str)
			{
				length = strlen(str);
				this->s = new char[length + 1];
				strcpy(this->s, str);
			}
		}
		explicit ro_string(std::string& str)
		{
			length = str.length();
			this->s = new char[length + 1];
			strcpy(this->s, str.c_str());
		}
		ro_string operator = (std::string& str)
		{
			length = str.length();
			this->s = new char[length + 1];
			strcpy(this->s, str.c_str());
			return *this;
		}
		ro_string operator = (const char* str)
		{
			length = strlen(str);
			this->s = new char[length + 1];
			strcpy(this->s, str);
			return *this;
		}
		ro_string operator += (const char* str)
		{
			this->s = (char*)realloc(this->s, this->length + strlen(str) + 1);
			strcpy(this->s + this->length, str);
			return *this;
		}
		ro_string operator += (ro_string& str)
		{
			this->s = (char*)realloc(this->s, this->length + str.length + 1);
			strcpy(this->s + this->length, str.s);
			return *this;
		}
		ro_string operator += (std::string& str)
		{
			this->s = (char*)realloc(this->s, this->length + str.length() + 1);
			strcpy(this->s + this->length, str.c_str());
			return *this;
		}
	};
	/*   ==   */
	/*--------*/
	// cstr : ro_string 
	template<typename T>
	inline bool operator==(const char * str, ro_string<T>& ro_str)
	{
		return strcmp(str, ro_str.s) == 0;
	}
	// ro_string : cstr 
	template<typename T>
	inline bool operator == (ro_string<T>& ro_str, const char* str)
	{
		return strcmp(ro_str.s, str) == 0;
	}
	// ro_string : ro_string 
	template<typename T>
	inline bool operator == (ro_string<T>& ro_str1, ro_string<T>& ro_str2)
	{
		return strcmp(ro_str1.s, ro_str2.s) == 0;
	}
	// ro_string : std::string 
	template<typename T>
	inline bool operator == (ro_string<T>& ro_str, std::string& str)
	{
		return ro_str.s == str;
	}
	// std::string : ro_string 
	template<typename T>
	inline bool operator == (std::string& str, ro_string<T>& ro_str)
	{
		return str == ro_str.s;
	}
	/*    +    */
	/*---------*/
	// std::string : ro_string 
	template<typename T>
	inline std::string operator + (const std::string& str, const ro_string<T>& ro_str)
	{
		return str + ro_str.s;
	}
	// ro_string : std::string
	template<typename T>
	inline std::string operator + (const ro_string<T>& ro_str, const std::string& str)
	{
		std::string data = ro_str.s;
		return  data + str;
	}
	/*   >   */
	/*-------*/
	// cstr : ro_string 
	template<typename T>
	inline bool operator > (const char* lhs, ro_string<T> rhs)
	{
		return strlen(lhs) > rhs.length;
	}
	// ro_string : cstr 
	template<typename T>
	inline bool operator > (ro_string<T> lhs, const char* rhs)
	{
		return lhs.length > strlen(rhs);
	}
	// ro_string_1 : ro_string_2 
	template<typename T1, typename T2>
	inline bool operator > (ro_string<T1> lhs, ro_string<T2> rhs)
	{
		return lhs.length > rhs.length;
	}
	// ro_string : std::string 
	template<typename T>
	inline bool operator > (ro_string<T> lhs, std::string rhs)
	{
		return lhs.length > rhs.length();
	}
	// std::string : ro_string 
	template<typename T>
	inline bool operator > (std::string lhs, ro_string<T> rhs)
	{
		return lhs.length() > rhs.length;
	}
	/*   <   */
	/*-------*/
	// cstr : ro_string 
	template<typename T>
	inline bool operator < (const char* lhs, ro_string<T> rhs)
	{
		return strlen(lhs) < rhs.length;
	}
	// ro_string : cstr 
	template<typename T>
	inline bool operator < (ro_string<T> lhs, const char* rhs)
	{
		return lhs.length < strlen(rhs);
	}
	// ro_string_1 : ro_string_2 
	template<typename T1, typename T2>
	inline bool operator < (ro_string<T1> lhs, ro_string<T2> rhs)
	{
		return lhs.length < rhs.length;
	}
	// ro_string : std::string 
	template<typename T>
	inline bool operator < (ro_string<T> lhs, std::string rhs)
	{
		return lhs.length < rhs.length();
	}
	// std::string : ro_string 
	template<typename T>
	inline bool operator < (std::string lhs, ro_string<T> rhs)
	{
		return lhs.length() < rhs.length;
	}

	template<typename T>
	inline std::ostream &operator<<(std::ostream& os, ro_string<T> &str)
	{
		os << str.s;
		return os;
	}
}