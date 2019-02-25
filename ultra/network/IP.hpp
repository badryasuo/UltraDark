#pragma once
#include <string>
#include <iosfwd>
namespace u
{
	struct IP
	{
		unsigned char b1;
		unsigned char b2;
		unsigned char b3;
		unsigned char b4;
		friend std::ostream &operator<<(std::ostream&, struct IP);
		IP(){}
		IP(const char* ip_str) { sscanf(ip_str, "%c.%c.%c.%c", b1, b2, b3, b4); }
		IP(std::string ip_str) { sscanf(ip_str.c_str(), "%c.%c.%c.%c", b1, b2, b3, b4); }
		operator char*()
		{
			char s[16];
			sprintf(s, "%c.%c.%c.%c", b1, b2, b3, b4);
			char* ip_str = strdup(s);
			return ip_str;
		}
		//IP operator=(IP ip) { *this = ip; }
	};
	std::ostream &operator<<(std::ostream& os, struct IP ip)
	{
		os << ip.b1 << "." << ip.b1 << "." << ip.b1 << "." << ip.b4;
		return os;
	}
}