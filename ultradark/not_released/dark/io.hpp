#ifndef DARK_IO
#define DARK_IO
#include <filesystem>
#include <iostream>
#include <fstream>
#include <ostream>
#include <sstream>
#include <stdio.h> // FILENAME_MAX
#include <sys/stat.h>
// the following code is used for debugging.
#ifdef _WIN32
// change the value to 0 to test other functions with different system-methods
// works only with windows-able functions.
// 1 is by default for best windows performance.
#define Windows 0x1;
#include <direct.h>
#define DarkGetCurrentDir _getcwd
#else
#define Windows 0x0;
#include <unistd.h>
#define DarkGetCurrentDir getcwd
#endif
// --- end
#pragma warning(disable:4996)
#pragma warning(disable:4018)
#pragma warning(disable:4067)

namespace dark
{
	namespace input
	{
		class file
		{
#if Windows
			static WIN32_FIND_DATAW data;
			static HANDLE h;
#else
			static std::ifstream f;
#endif
		public:
			static int64 get_length(const wchar_t * path)
			{
#if Windows
				return (h = FindFirstFileW(path, &data)) == INVALID_HANDLE_VALUE ? -1 :
					data.nFileSizeLow | (int64)data.nFileSizeHigh << 32;
#else
				f.open(path, std::ifstream::ate | std::ifstream::binary);
				return f.tellg();
#endif
			}
		};
#if Windows
		WIN32_FIND_DATAW file::data;
		HANDLE file::h;
#else
		std::ifstream file::f;
#endif
	}
	namespace io
	{
		using namespace std;
#if __cplusplus <= 201700L
		namespace fs = std::experimental::filesystem;
#else
		namespace fs = std::filesystem;
#endif
		const char * get_currentpath()
		{
			char path[FILENAME_MAX];
			DarkGetCurrentDir(path, sizeof(path));
			char* ret = new char[FILENAME_MAX];
			strcpy(ret, path);
			return ret;
		}
		vector<std::string> get_allfiles(std::string path)
		{
			vector<std::string> s;
			for (auto p : fs::directory_iterator(path))
			{
				ostringstream oss;
				oss << p;
				s.push_back(oss.str());
			}
			return s;
		}
		vector<std::string> get_allsubfiles(std::string path)
		{
			vector<std::string> s;
			for (auto p : fs::recursive_directory_iterator(path))
			{
				ostringstream oss;
				oss << p;
				s.push_back(oss.str());
			}
			return s;
		}
		// return the number of (files) deleted.
		template <typename Path>
		int remove(Path path)
		{
			return fs::remove_all(path);
		}
		// clear an file.
		template <typename Path>
		void clear(Path path)
		{
			std::ifstream ofs(path, std::ofstream::out | std::ofstream::trunc);
		}
		template <typename Path>
		int exists(Path path)
		{
			struct stat Stat;
			return stat(path, &Stat) == 0;
		}
	}
}
#endif