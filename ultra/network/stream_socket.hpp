#pragma once
#include "stream_packet.hpp"
#include "global.hpp"
#include <iostream>
namespace u
{
	/*- -----------------*/
	/*- TCP	Socket Class-*/
	/*- -----------------*/
	class SocketList;
	struct stream_socket
	{
		bool encrypted = false;
		/* Operators */
		bool operator==(const stream_socket &socket) const
		{
			return socket.fd == this->fd;
		}
		bool operator!=(const stream_socket &socket) const
		{
			return socket.fd != this->fd;
		}
		/* Constructors */
		
		// Empty Constructor
		stream_socket() : enabled(false), encrypted(false)
		{
			init_api();
			//FD_ZERO(fds);
		}
		// Address Constructor:
		// Specify address.port `only` for Multi-Address server.
		// Specify an address.ip && address.port for a specfic socket (server/client) properties.
		stream_socket(const u::Address &address) : addr_len(sizeof(this->addr)), enabled(false), encrypted(false)
		{
			init_api();
			//FD_ZERO(fds);
			addr.sin_addr.s_addr = address.ip ? inet_addr(GetIP(address.ip)) : htonl(INADDR_ANY);
			addr.sin_family = AF_INET;
			addr.sin_port = htons(address.port);
			if ((fd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
				throw network_exception("failed to create a TCP socket.");
		}

		/* Setters */

		u::Address setAddress(const Address &address)
		{
			addr.sin_addr.s_addr = address.ip ? inet_addr(GetIP(address.ip)) : htonl(INADDR_ANY);
			addr.sin_family = AF_INET;
			addr.sin_port = htons(address.port);
			if ((fd = ::socket(AF_INET, SOCK_STREAM, 0)) == -1)
				throw network_exception("failed to create a TCP socket.");
			return address;
		}

		/* Getters */

		const bool running(void) noexcept
		{
			return enabled;
		}

		u::Address address()
		{
			return u::Address(inet_ntoa(this->addr.sin_addr), ntohs(this->addr.sin_port));
		}

		std::string ip()
		{
			return inet_ntoa(this->addr.sin_addr);
		}
		unsigned short port()
		{
			return ntohs(this->addr.sin_port);
		}
		const bool connected(void) noexcept
		{
			return this->is_connected;
		}
		const bool has_errors()
		{
			return err_log.length() > 0;
		}
		const std::string &error_log()
		{
			return this->err_log;
		}
		auto getCore()
		{
			return this->fd;
		}
		/* Functions */

		const void bind_address()
		{
			//setsockopt(this->fd, SOL_SOCKET, SO_REUSEADDR, (char *)&on, sizeof(on));
			//ioctlsocket(this->fd, FIONBIO, (u_long *)&on);
			if (::bind(this->fd, (struct sockaddr*)&this->addr, sizeof(this->addr)) != 0)
				throw network_exception("failed to bind the socket with the specified address");
		}
		const stream_socket accept()
		{
			stream_socket socket;
			auto x = ::accept(this->fd, reinterpret_cast<struct sockaddr*>(&socket.addr), &addr_len);
			if (x == INVALID_SOCKET)
				throw network_exception("Error accepting a client: Descriptor is not a socket.");
			socket.is_connected = true;
			socket.fd = x;
			//FD_SET(socket.fd, fds);
			polls.push_back({ x, POLLIN });
			clients.push_back(socket);
			return socket;
		}
		bool connect()
		{
			if (::connect(this->fd, (const struct sockaddr*)&this->addr, sizeof(this->addr)) != 0)
			{
				//throw get_network_except();
				return false;
			}
			this->is_connected = true;
			return true;
		}
		bool trytoconnect(int timeInMs, int times, byte * print, int startFrom)
		{
			int i;
			times == AUTO ? i = -1 : i = startFrom;
			while (i <= times)
			{
				if (this->connect())
					return true;
				else
					std::this_thread::sleep_for(std::chrono::milliseconds(timeInMs));
				printf(print ? print : "", i);
				times == AUTO ? i = -1 : ++i;
			}
			return false;
		}
		int on = 1;
		bool listen()
		{
			if (!enabled)
			{
				if (::listen(this->fd, SOMAXCONN) != 0)
					throw get_network_except();
				polls.push_back({ this->fd, POLLIN });
				enabled = true;
				return true;
			}
			return false;
		}

		request_list get_requests()
		{
			request_list requests;
			auto rc = poll(polls.data(), (nfds_t)polls.size(), -1);
			if (rc > 0)
			{
				for (auto poll : polls)
				{
					if (poll.revents == 0 || poll.revents == POLLNVAL)
						continue;
					auto req_fd = poll.fd;
					sockaddr_in req_addr;
					getsockname(req_fd, (sockaddr*)&req_addr, &addr_len);
					requests.push_back(request(req_fd, this->fd, req_addr));
				}
			}
			return requests;
		}

		int send(stream_packet packet)
		{
			int res = ::send(this->fd,
				this->encrypted ? encrypt(packet.bytes, packet.size) : packet.bytes.c_str(),
				(int)packet.size, 0);
			if (res < 0)
				throw get_network_except();
			return res;
		}
		stream_packet receive(int maxByte)
		{
			stream_packet packet;
			char* data = (char*)calloc(1, maxByte);
			auto i = ::recv(this->fd, data, maxByte, 0);
			if (i != -1)
			{
				this->is_connected = true;
				data[maxByte] = '\0';
				packet.setData(this->encrypted ? encrypt(data, packet.size) : data);
				return packet;
			}
			else
				this->is_connected = false;
			return packet;
		}

		int close()
		{
			return close_fd(this->fd);
		}

		void remove_client(const stream_socket &client)
		{
			for (unsigned i = 1; i < polls.size(); ++i)
			{
				auto p = polls[i];
				if (p.fd == client.fd)
					polls.erase(polls.begin() + i);
			}
			clients.erase(std::find(clients.begin(), clients.end(), client));
		}

		static const char * GetIP(const char * host)
		{
			init_api();
			hostent * h = gethostbyname(host);
			return (host && h) ? inet_ntoa(*(in_addr *)h->h_addr) : "";
		}
		time_t rawtime;
		struct tm * timeinfo;
		char buf[128];
		const char *GetTime(const char* additional_info)
		{
			time(&rawtime);
			timeinfo = localtime(&rawtime);
			memset(buf, 0, 128);
			if (additional_info)
				sprintf(buf, "[%.2d:%.2d:%.2d %s]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec, additional_info);
			else
				sprintf(buf, "[%.2d:%.2d:%.2d]", timeinfo->tm_hour, timeinfo->tm_min, timeinfo->tm_sec);
			return buf;
		}
		// Converts `Incoming` structure into a Socket structure.
		// *** Use only if the incoming connection is a message from a Client. ***
		static stream_socket parse(const request &incoming_connection)
		{
			stream_socket s;
			s.enabled = false;
			s.encrypted = false;
			s.fd = incoming_connection.fd;
			//FD_SET(s.fd, &incoming_connection.master_fd);
			s.addr = incoming_connection.addr;
			return s;
		}
		bool enabled = false;
		std::vector<stream_socket> clients;
		// Can be set from 0 up to 18,446,744,073,709,551,615.
		unsigned long long max_clients;
	private:
		std::string err_log;
		bool is_connected = false;
		//(void*)()
#ifdef _WIN32
		WSAData wsaData;
		SOCKET fd;
		int addr_len = (int)sizeof(sockaddr_in);
#else
		int fd;
		socklen_t addr_len = (socklen_t)sizeof(sockaddr_in);
#endif
		std::vector<pollfd> polls;
		struct sockaddr_in addr;
	};
	class SocketList
	{
		friend struct stream_socket;
		std::vector<stream_socket> sockets;
		fd_set master_set;
		explicit SocketList(fd_set fd_set, std::vector<stream_socket> sockets) : sockets(sockets), master_set(fd_set)
		{

		}
	public:
		stream_socket &operator[] (const unsigned &index)
		{
			return sockets[index];
		}
	};
}