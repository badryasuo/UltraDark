#pragma once
#include <string>
namespace ultra
{
	struct Http
	{
		static std::string GetRoot(const char * URL)
		{
			std::string url(URL ? URL : "");
			size_t pattern;

			if ((pattern = url.find("http://")) != std::string::npos)
				url.replace(pattern, 7, "");

			else if ((pattern = url.find("https://")) != std::string::npos)
				url.replace(pattern, 8, "");

			if ((pattern = url.find("/")) != std::string::npos)
				url.replace(pattern, url.length(), "");
			return url;
		}
		static std::string ClearURL(const char * URL)
		{
			std::string url(URL ? URL : "");
			size_t pattern;

			if ((pattern = url.find("http://")) != std::string::npos)
				url.replace(pattern, 7, "");

			else if ((pattern = url.find("https://")) != std::string::npos)
				url.replace(pattern, 8, "");

			return url;
		}
	};
}