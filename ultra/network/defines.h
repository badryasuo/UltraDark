#pragma once
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4820)
#include <algorithm>
#include <vector>
#include "connection.hpp"
#ifdef _WIN32
#include <WinSock2.h>
#include <ws2tcpip.h>
#include <mstcpip.h>
#define _WINSOCKAPI_
#pragma comment(lib, "Ws2_32.lib")
#else
#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <poll.h>
#endif

#ifdef uDARK_DEBUG_SOCKET
#define set_socket_error(x) (puts(lastError = x))
#else
#define set_socket_error(x) (lastError = x)
#endif

#ifdef _WIN32
#else
#define udark_test_winsock_init(wsaData)(wsaData)
#define INVALID_SOCKET -1
#endif
#include "../ro_int.hpp"
#include "../ro_string.hpp"
namespace u
{
	struct stream_socket;

	typedef const char byte;
	typedef const void * data;

	typedef std::vector<std::string> Header;
	struct Address
	{
		const char* ip = nullptr;
		unsigned short port = 0;
		Address() {}
		Address(const char* IP, unsigned short Port) : ip(IP), port(Port) {}
		Address(unsigned short Port) : port(Port) {}
	};

	enum {
		AUTO,
	};
	/*enum Protocol {
		TCPSocket,
		UDPSocket,
		HTTP,
		HTTPS
	};*/

}