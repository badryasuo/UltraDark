#pragma once
#include <string>
#include <sstream>
#include <vector>
#include <fstream>
#include <filesystem>
#include <map>
#if __cplusplus < 201703L // If the version of C++ is less than 17
// It was still in the experimental:: namespace
namespace fs = std::experimental::filesystem;
#else
namespace fs = std::filesystem;
#endif
namespace u
{
	struct directory
	{
		std::string path;
	};
	class filesystem
	{
		std::string encrypt(const std::string &data, const std::string &key)
		{
			std::string encrypted;
			for (unsigned i = 0; i < data.size(); ++i)
				encrypted += (data[i] + key[i % key.size()]) ^ 0xff;
			return encrypted;
		}
		std::string decrypt(const std::string &data, const std::string &key)
		{
			std::string decrypted;
			for (unsigned i = 0; i < data.size(); ++i)
				decrypted += (data[i] ^ 0xff) - key[i % key.size()];
			return decrypted;
		}
	public:
		static std::vector<fs::path> geteverything(const fs::path &path)
		{
			std::vector<fs::path> dirs;
			for (const auto & entry : fs::directory_iterator(path))
			{
				dirs.push_back(entry);
				if (fs::is_directory(entry))
				{
					auto subdirs = geteverything(entry);
					dirs.insert(dirs.end(), subdirs.begin(), subdirs.end());
				}
			}
			return dirs;
		}
		static std::vector<fs::path> getallfiles(const fs::path &path)
		{
			std::vector<fs::path> files;
			for (const auto & entry : fs::directory_iterator(path))
			{
				if (fs::is_directory(entry))
				{
					auto subfiles = getallfiles(entry);
					files.insert(files.end(), subfiles.begin(), subfiles.end());
				}
				else
					files.push_back(entry);
			}
			return files;
		}
		static std::string getfilename(std::string path)
		{
			path = path.substr(path.find_last_of("/\\") + 1);
			std::string::size_type dot_i = path.find_last_of('.');
			return path.substr(0, dot_i);
		}
		static void pack(std::string path, std::string out)
		{
			auto vec = getallfiles(path);
			std::map<std::string, std::string> files;
			for (const auto& filepath : vec)
			{
				std::string path = filepath.string();
				std::replace(path.begin(), path.end(), '\\', '/');
				std::ifstream file(path);
				std::stringstream data;
				data << file.rdbuf();
				files[path] = data.str();
			}
		}
	};
}