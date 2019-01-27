#ifndef YOTTA_CONFIG_PARSER_H
#define YOTTA_CONFIG_PARSER_H
#pragma warning(disable : 4996)
#include <string>
#include <vector>
#include <fstream>

#include <sstream>
#include <algorithm>
#include <ultra/dark/utils.hpp>
namespace ultra
{
	inline std::string clearSpace(std::string& data)
	{
		std::string newString;
		for (int i = 0; data[i] != 0; ++i)
			if (data[i] != ' ' && data[i] != '\t' && data[i] != ' ' && data[i] != '\r')
				newString += data[i];
		data = newString;
		return newString;
	}
	class ConfigParser
	{
	public:
		ConfigParser(){}
		ConfigParser(std::string fileName)
		{
			name = (char*)calloc(1, fileName.size() + 1);
			strcpy(name, fileName.c_str());
			std::stringstream datastream;
			std::ifstream file = std::ifstream(fileName);
			if (file)
			{
				datastream << file.rdbuf();
				file.close();
				std::string data(datastream.str());
				clearSpace(data);
				std::vector<std::string>lines = split(data, '\n');
				for (int i = 0; i < lines.size(); ++i)
				{
					std::vector<std::string>KeyAndValue = split(lines[i], '=');
					if (KeyAndValue.size() > 1)
					{
						keys.push_back(KeyAndValue.at(0));
						values.push_back(KeyAndValue.at(1));
					}
				}
			}
			else
			{
				std::ofstream outConfig(name);
				outConfig.close();
			}
		}
		bool reload()
		{
			std::stringstream datastream;
			std::ifstream file = std::ifstream(name);
			if (file)
			{
				keys.clear();
				values.clear();
				datastream << file.rdbuf();
				file.close();
				std::string data(datastream.str());
				clearSpace(data);
				std::vector<std::string>lines = split(data, '\n');
				for (int i = 0; i < lines.size(); ++i)
				{
					std::vector<std::string>KeyAndValue = split(lines[i], '=');
					if (KeyAndValue.size() > 1)
					{
						keys.push_back(KeyAndValue.at(0));
						values.push_back(KeyAndValue.at(1));
					}
				}
				return true;
			}
			std::ofstream outConfig(name);
			outConfig.close();
			return false;
		}
		std::vector<std::string> keys;
		std::vector<std::string> values;
		std::string getValue(std::string Key)
		{
			size_t s = keys.size();
			for (int i = 0; i < s; ++i)
				if (keys[i] == Key)
					return values[i];
			return "(null)";
		}
		std::string getValue(std::string Key, int Whom)
		{
			size_t s = keys.size();
			std::vector<std::string> found_values;
			for (int i = 0; i < s; ++i)
				if (keys[i] == Key)
					found_values.push_back(values[i]);
			return found_values.size() < 1 || found_values.size() <= Whom ? "(null)" : found_values[Whom];
		}
		static bool to_bool(std::string value)
		{
			std::transform(value.begin(), value.end(), value.begin(), ::tolower);
			return value == "true" || value == "1" ? true : false;
		}
	private:
		char* name;
	};
}

#endif