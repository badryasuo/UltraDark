#pragma once
#include <string>
#include <time.h>
#include <thread>
#include "defines.h"
#include "Encryption.hpp"

#include "../ro_string.hpp"
namespace u
{
	/*- -----------------*/
	/*- TCP	stream_packet Class-*/
	/*- -----------------*/
	struct stream_packet
	{
		int size;
		stream_packet() : bytes(""), size(0)
		{}
		stream_packet(int size) : bytes(""), size(size)
		{}
		stream_packet(const char* packet) : bytes(packet ? packet : ""), size(strlen(packet)) {}
		stream_packet(std::string packet) : bytes(packet), size(packet.size()) {}
		stream_packet(const char * bytes, int length) : bytes(bytes ? bytes : ""), size(length)
		{}
		stream_packet& setData(std::string packet)
		{
			this->bytes = packet;
			this->size = packet.size();
			return *this;
		}
		const std::string& data()
		{
			return this->bytes;
		}
		bool operator<(stream_packet packet)
		{
			return this->size < packet.size;
		}

		stream_packet operator+(stream_packet packet)
		{
			stream_packet newData = this->bytes + packet.bytes;
			return newData;
		}
	protected:
		friend struct stream_socket;
		friend struct seasion;
	private:
		friend std::string operator+(const std::string &, const stream_packet &);
		friend std::ostream& operator<<(std::ostream&, stream_packet &);
		std::string bytes;
	};
	inline std::string operator+(const std::string &s, const stream_packet &p)
	{
		return s + p.bytes;
	}
	inline std::ostream& operator<<(std::ostream& os, stream_packet &packet)
	{
		os << packet.bytes;
		return os;
	}
}