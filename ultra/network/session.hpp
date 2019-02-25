#pragma once
#include "Socket.hpp"
#include "Http.hpp"
namespace u
{
	struct seasion
	{
		seasion()
		{
#ifdef _WIN32
			if ((&wsaData == NULL) && WSAStartup(0x101, &wsaData) != 0)
			{
				lastError = "Couldn't start WSA";
			}
#endif
			m_so.setPort(80);
			m_so.setProtocol(TCPSocket);
		}
		seasion(const char * URL, Protocol connection)
		{
#ifdef _WIN32
			if ((&wsaData == NULL) && WSAStartup(0x101, &wsaData) != 0)
			{
				lastError = "Couldn't start WSA";
			}
#endif
			m_so.setAddress(Socket::GetIP(Http::GetRoot(URL).c_str()));
			m_so.setPort(connection == HTTPS ? 443 : 80);
			m_so.setProtocol(TCPSocket);
			m_url = Http::ClearURL(URL);
			m_pro = connection;
		}
		~seasion()
		{
			if (m_pro == HTTPS)
			{

			}
		}
		bool run()
		{
			if (m_so.connect())
			{
				//m_pro == 0;
				return 1;
			}
			return 0;
		}
		void setHeader(Header header)
		{
			for (int i = 0; i < header.size(); ++i)
			{
				// i % 2 != 0 = true, cause we start from 0 then 1 woud be the value and 0 is the key
				if (i > 0 && (i % 2))
				{
					m_header.append(header.at(i));
					m_header.append("\r\n");
				}
				else
				{
					m_header.append(header.at(i));
					m_header.append(": ");
				}
			}
			m_header.append("\r\n");
		}
		auto get()
		{
			m_data = "";
			m_data.append("GET ");
			m_data.append(m_pro == HTTP ? "http://" : "https://");
			m_data.append(m_url);
			m_data.append(" HTTP/1.1\r\n");
			m_data.append(m_header);
			Packet packet(m_data.c_str());
			return m_so.send(packet);
		}
		auto post()
		{
			m_data = "";
			m_data.append("POST ");
			m_data.append(m_pro == HTTP ? "http://" : "https://");
			m_data.append(m_url);
			m_data.append(" HTTP/1.1\r\n");
			m_data.append(m_header);
			Packet packet(m_data.c_str());
			return m_so.send(packet);
		}
		auto getResponse(Packet & packet, int size)
		{
			return m_so.recv(packet, size);
		}
		const char * getLastRequest()
		{
			return m_data.c_str();
		}
	private:
#ifdef _WIN32
		WSAData wsaData;
#endif
		u::byte * lastError = "";
		std::string m_data;
		std::string m_header;
		Socket m_so;
		std::string m_url;
		Protocol m_pro;
	};
}