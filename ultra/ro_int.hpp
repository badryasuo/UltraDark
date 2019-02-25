#pragma once
#include <stdint.h>
#include <iosfwd>
#pragma warning(disable : 4477)

namespace u
{
	// read-only unsigned short.
	template<typename write_access> struct ro_ushort;
	template<typename T> std::ostream &operator << (std::ostream& os, ro_ushort<T>);
	template<typename write_access>
	struct ro_ushort
	{
		friend write_access;
		friend std::ostream &operator << <write_access>(std::ostream&, ro_ushort);
		operator unsigned short()
		{
			return v;
		}
	private:
		ro_ushort() {}
		ro_ushort(unsigned short x) { v = x; }
		unsigned short v;
		unsigned short operator=(unsigned short x)
		{
			return (v = x);
		}
	};
	template<typename T>
	inline std::ostream &operator<<(std::ostream& os, ro_ushort<T> &uint)
	{
		os << uint.v;
		return os;
	}
	// read-only unsigned int.
	template<typename write_access> struct ro_uint;
	template<typename T> std::ostream &operator << (std::ostream& os, ro_uint<T>);
	template<typename write_access>
	struct ro_uint
	{
		friend write_access;
		friend std::ostream &operator << <write_access>(std::ostream&, ro_uint);
		operator unsigned int()
		{
			return v;
		}
	private:
		ro_uint() {}
		ro_uint(unsigned int x) { v = x; }
		unsigned int v;
		unsigned int operator=(unsigned int x)
		{
			return (v = x);
		}
	};
	template<typename T>
	inline std::ostream &operator<<(std::ostream& os, ro_uint<T> &uint)
	{
		os << uint.v;
		return os;
	}
	// read-only size_t.
	template<typename write_access> struct ro_size_t;
	template<typename T> std::ostream &operator << (std::ostream& os, ro_size_t<T>);
	template<typename write_access>
	struct ro_size_t
	{
		friend write_access;
		friend std::ostream &operator << <write_access>(std::ostream&, ro_size_t);
		operator size_t()
		{
			return v;
		}
	private:
		ro_size_t() {}
		ro_size_t(size_t x) { v = x; }
		size_t v;
		size_t operator=(size_t x)
		{
			return (v = x);
		}
	};
	template<typename T>
	inline std::ostream &operator<<(std::ostream& os, ro_size_t<T> &uint)
	{
		os << uint.v;
		return os;
	}
}