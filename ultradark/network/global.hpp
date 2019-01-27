#include "defines.h"
#include "exception.hpp"
namespace ultra
{
	inline void init_api()
	{
#ifdef _WIN32
		WSAData wsaData;
		if(WSAStartup(0x101, &wsaData) != 0)
			throw network_exception("Couldn't start WSA");
#endif
	}
#ifdef _WIN32
#define get_fd(FD_SET, i) (FD_SET.fd_array[i])
#define close_fd(fd) ::closesocket(fd)
#define poll(fd, nfds, timeout) WSAPoll(fd, nfds, timeout)
#define nfds_t ULONG
#else
#define get_fd(FD_SET, i) (FD_SET.fd_array[i])
#define close_fd(fd) ::close(fd)
#endif
}