#pragma once
#include <ios>
#include <string.h>
#ifdef _WIN32
#include <winsock2.h>
#define _WINSOCKAPI_
#pragma comment(lib, "Ws2_32.lib")
#else
#include <sys/socket.h>
#include <netinet/in.h>
#endif
#include <initializer_list>
namespace ultra
{
	enum REQUEST
	{
		REQ_NOTHING = 0,
		REQ_CONNECTION = 1,
		REQ_MESSAGE = 2
	};
	struct request
	{
		const bool operator ==(const REQUEST &r)
		{
			return this->req == r;
		}
	private:
		friend struct request_list;
		friend struct stream_socket;
		request() {}
		template<typename I1, typename I2>
		request(const I1 &connection_fd, const I2 &server_fd, const sockaddr_in &fd_addr) :
			fd(connection_fd), master_fd(server_fd), addr(fd_addr)
		{
			if (connection_fd == server_fd)
				req = REQ_CONNECTION;
			else
				req = REQ_MESSAGE;
		}

#ifdef _WIN32
		SOCKET master_fd;
		SOCKET fd;
#else
		int master_fd;
		int fd;
#endif
		sockaddr_in addr;
		REQUEST req;
	};
	struct request_list
	{

		//construct/copy/destroy:
		request_list() noexcept { arr = new request[rsrv_sz]; }
		explicit request_list(unsigned n)
		{
			unsigned i;
			rsrv_sz = n << 2;
			arr = new request[rsrv_sz];
			for (i = 0; i < n; ++i)
				arr[i] = request();
			sz = n;
		}
		request_list(unsigned n, const request &val)
		{
			unsigned i;
			rsrv_sz = n << 2;
			arr = new request[rsrv_sz];
			for (i = 0; i < n; ++i)
				arr[i] = val;
			sz = n;
		}
		request_list(std::initializer_list<request> lst)
		{
			rsrv_sz = lst.size() << 2;
			arr = new request[rsrv_sz];
			for (auto &item : lst)
				arr[sz++] = item;
		}
		request_list(const request_list &other)
		{
			unsigned i;
			rsrv_sz = other.rsrv_sz;
			arr = new request[rsrv_sz];
			for (i = 0; i < other.sz; ++i)
				arr[i] = other.arr[i];
			sz = other.sz;
		}
		request_list(request_list &&other) noexcept
		{
			unsigned i;
			rsrv_sz = other.rsrv_sz;
			arr = new request[rsrv_sz];
			for (i = 0; i < other.sz; ++i)
				arr[i] = std::move(other.arr[i]);
			sz = other.sz;
		}
		~request_list()
		{
			if (arr && arr->req >= REQ_NOTHING)
			{
				delete[] arr;
			}
		}

		request_list &operator =(const request_list &other)
		{
			unsigned i;
			if (rsrv_sz < other.sz) {
				rsrv_sz = other.sz << 2;
				reallocate();
			}
			for (i = 0; i < other.sz; ++i)
				arr[i] = other.arr[i];
			sz = other.sz;
			return *this;
		}
		request_list &operator = (request_list &&other)
		{
			unsigned i;
			if (rsrv_sz < other.sz) {
				rsrv_sz = other.sz << 2;
				reallocate();
			}
			for (i = 0; i < other.sz; ++i)
				arr[i] = std::move(other.arr[i]);
			sz = other.sz;
			return *this;
		}
		request_list &operator = (std::initializer_list<request> lst)
		{
			if (rsrv_sz < lst.size()) {
				rsrv_sz = lst.size() << 2;
				reallocate();
			}
			sz = 0;
			for (auto &item : lst)
				arr[sz++] = item;
			return *this;
		}

		// capacity:

		unsigned size() const noexcept { return sz; }

		// element access

		request &operator [](const unsigned idx) const { return arr[idx]; }
		request &back() { return arr[sz - 1]; }
		const request &back() const { return arr[sz - 1]; }

		// data access:

		request * data() noexcept { return arr; }
		const request * data() const noexcept { return arr; }

		// modifiers:

		request &push_back(const request &conn)
		{
			if (sz == rsrv_sz) {
				rsrv_sz <<= 2;
				reallocate();
			}
			arr[sz] = conn;
			return arr[sz++];
		}
		request &add(const request &&conn)
		{
			if (sz == rsrv_sz)
				rsrv_sz <<= 2;
			arr[sz] = std::move(conn);
			return arr[sz++];
		}
		request &last() { return arr[sz > 0 ? sz - 1 : sz]; }

	private:
		unsigned rsrv_sz = 4;
		unsigned sz = 0;
		request *arr;

		inline void reallocate()
		{
			request *tarr = new request[rsrv_sz];
			memcpy(tarr, arr, sz * sizeof(request));
			delete[] arr;
			arr = tarr;
		}
	};
}