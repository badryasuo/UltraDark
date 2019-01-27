#pragma once
#include "datagram_packet.hpp"
namespace ultra
{
	
	/*- -----------------*/
	/*- UDP	Socket Class-*/
	/*- -----------------*/
	struct datagram_socket
	{
		datagram_socket() : addr_len(sizeof(this->addr))
		{
#ifdef _WIN32
			if ((&wsaData == NULL) && WSAStartup(0x101, &wsaData) != 0)
				set_socket_error("Couldn't start WSA");
#endif
			if ((this->master = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
				set_socket_error("failed to create UDP socket.");
		}
		datagram_socket(const ultra::Address address) : addr_len(sizeof(this->addr))
		{
#ifdef _WIN32
			if (WSAStartup(0x101, &wsaData) != 0)
				set_socket_error("Couldn't start WSA");
#endif
			this->addr.sin_family = AF_INET;
			this->addr.sin_addr.s_addr = address.ip ? inet_addr(address.ip) : htonl(INADDR_ANY);
			this->addr.sin_port = htons(address.port);
			if ((this->master = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
				set_socket_error("failed to create UDP socket.");
		}
		ultra::Address setAddress(const Address &address)
		{
			this->addr.sin_addr.s_addr = address.ip ? inet_addr(address.ip) : htonl(INADDR_ANY);
			this->addr.sin_family = AF_INET;
			this->addr.sin_port = htons(address.port);
			if ((this->master = socket(AF_INET, SOCK_DGRAM, 0)) == -1)
				set_socket_error("failed to create a TCP socket.");
			return address;
		}
		ultra::Address address()
		{
			return ultra::Address(inet_ntoa(this->addr.sin_addr), ntohs(this->addr.sin_port));
		}
		void bind_address()
		{
			if (::bind(this->master, (struct sockaddr*)&this->addr, sizeof(this->addr)) != 0)
				set_socket_error("failed to bind the socket with the specified address");
		}
		int sendto(datagram_packet packet)
		{
			return ::sendto(this->master, packet._Data, packet.size, 0, (struct sockaddr*)&packet.addr, packet.addr_len);
		}
		int recvfrom(datagram_packet & packet)
		{
			char* PACKET = (char*)calloc(1, packet._Length);
			int len = ::recvfrom(this->master, PACKET, packet.size, 0, (struct sockaddr*)&packet.addr, &packet.addr_len);
			PACKET[packet.size] = '\0';
			packet._Data = PACKET;
			return len;
		}
		int mode(long cmd, u_long argp)
		{
			return ioctlsocket(this->master, cmd, &argp);
		}
		/* Returns the Network IP address in American Standard Code */
		const char* ip()
		{
			return inet_ntoa(this->addr.sin_addr);
		}
		/* Returns the Network Host Port */
		unsigned short port()
		{
			return ntohs(this->addr.sin_port);
		}
	private:
#ifdef _WIN32
		WSAData wsaData;
#endif
		byte * lastError = "");
		int _Ping;
#ifdef _WIN32
		SOCKET master;
#else
		int master;
#endif
		master_set _MasterSet;
		struct sockaddr_in addr;
		int addr_len;
	};
}