#pragma once
#include <string>
#include "consts.h"
namespace ultra
{

	/*- -----------------*/
	/*- UDP	Packet Class-*/
	/*- -----------------*/
	struct datagram_packet
	{
		size_t size;
		/*--- Constructors */
		/*##################*/
		datagram_packet() : _Length(0), _AddrLen(sizeof(this->_Addr))
		{}
		datagram_packet(size_t size) : size(size), _AddrLen(sizeof(this->_Addr))
		{
			this->_Data = (char*)calloc(1, size);
}
		datagram_packet(byte * address, int port) : _AddrLen(sizeof(this->_Addr))
		{
			this->_Addr.sin_family = AF_INET;
			this->_Addr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
			this->_Addr.sin_port = htons(port);
		}
		datagram_packet(byte * bytes, ultra::byte * address, int port) : size(strlen(bytes)), _AddrLen(sizeof(this->_Addr))
		{
			this->_Data = (char*)bytes;
			this->_Addr.sin_family = AF_INET;
			this->_Addr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
			this->_Addr.sin_port = htons(port);
		}
		datagram_packet(data data, size_t length, ultra::byte * address, int port) : size(length), _AddrLen(sizeof(this->_Addr)), _Data((byte *)data)
		{
			this->_Addr.sin_family = AF_INET;
			this->_Addr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
			this->_Addr.sin_port = htons(port);
		}
		/*--- Get Functions */
		/*##################*/
		/* Return the Network IP address in American Standard Code */
		byte * ip()
		{
			return inet_ntoa(this->_Addr.sin_addr);
		}
		/* Returns the Network Host Port */
		int port()
		{
			return ntohs(this->_Addr.sin_port);
		}
		/* Return the data buffer. */
		byte * bytes()
		{
			return (ultra::byte*)this->_Data;
		}
		/* Return a boolean whether the packet buffer equals the parameter. */
		int eq(byte * bytes)
		{
			return strcmp(this->_Data, bytes) == 0;
		}
		/* Return the length of the packet buffer */
		int len()
		{
			return (int)(sizeof(this->_Data) == sizeof(int) ? strlen(this->_Data) : sizeof(this->_Data));
		}
		/* Return the data in a string. */
		std::string getString()
		{
			return std::string(this->_Data);
		}
		Address getAddress()
		{
			Address addr;
			addr.IP = inet_ntoa(_Addr.sin_addr);
			addr.PORT = ntohs(_Addr.sin_port);
			return addr;
		}
		/*--- Set Functions */
		/*##################*/
		/* Set the IP Address for this packet. */
		void address(ultra::byte * address)
		{
			this->_Addr.sin_family = AF_INET;
			this->_Addr.sin_addr.s_addr = address ? inet_addr(address) : INADDR_ANY;
		}
		/* Set the port for this packet. */
		void port(int port)
		{
			this->_Addr.sin_port = htons(port);
		}
		/* Set the data buffer for this packet. */
		void bytes(byte * bytes)
		{
			if (bytes)
			{
				this->_Data = bytes;
				this->size = strlen(bytes);
			}
			else
			{
				bytes = "";
				this->size = 0;
			}
		}

	protected:
		friend struct Socket;
		friend struct datagram_socket;
	private:
		byte * _Data;
		struct sockaddr_in _Addr;
		int _AddrLen;
	};
}