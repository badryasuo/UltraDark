/* THIS LIBRARY ISN'T FOR USING YET! */


#pragma once
#include <ostream>
#include <vector>
#include <ultradark/algorithms/adv.hpp>
namespace ultra
{
	struct json
	{
		enum type
		{
			undefined = -0xffff,
			null = 0,
			string = 1,
			t_array = 2,
			t_record = 5,
			// Represents any integer.
			number = 7,
			t_double = 8,
			// Represents a true (1) or false (0).
			boolean = 10
		};
		struct object
		{
			object() {}
			explicit object(json::object *Parent)
			{
				this->parent = Parent;
			}
			explicit object(const std::string &json)
			{
				*this = json::parse(json);
			}
			explicit object(const std::vector<std::string> &Keys, const std::vector<std::string> &Values)
			{
				this->keys = Keys;
				this->values = Values;
			}
			object operator = (std::string new_value)
			{
				if (this->parent)
				{
					std::string &val = this->parent->values.back();
					if (val == "null")
					{
						val = new_value;
						char front = new_value.front();
						char back = new_value.back();
						if (front == '{' && back == '}')
						{
							*this = parse(new_value);
						}
						else if (front == '[' && back == ']')
						{
							json::array arr = json::parse_array(new_value);
							this->values = arr.get_vector();
						}
					}
				}
				return *this;
			}
			bool to_bool()
			{
				return ultra::to_bool(this->json);
			}
			std::string value()
			{
				return this->json;
			}
			std::string to_string()
			{
				const char &front = json.front();
				const char &back = json.back();
				std::string str = json;
				if ((front == '"' && back == '"') || (front == '\'' && back == '\''))
				{
					str.erase(0, 1);
					str.erase(str.size() - 1, 1);
				}
				return str;
			}
			// Returns a value using index of the key or the value itself.
			object operator [] (const int & key_index)
			{
				return object(values[key_index]);
			}
			// Returns the value of the key specified or creates a new one.
			object operator [] (const std::string & key)
			{
				auto pos = std::find(keys.begin(), keys.end(), key) - keys.begin();
				if ((size_t)pos >= keys.size())
				{
					keys.push_back(key);
					values.push_back("null");
					object o(this);
					return o;
				}
				else
				{
					object o(values[pos]);
					return o;
				}
			}
			size_t size()
			{
				return keys.size();
			}
			bool has_errors()
			{
				return !error.empty();
			}
			void set_error(std::string message)
			{
				error.assign(message);
			}
			void clear_error()
			{
				error = "";
			}
			// This function is recieved for parsing purposes. never, ever use it except for coding your own parser.
			void set_string_no_parse(std::string str)
			{
				json = str;
			}
			void set_values(const std::vector<std::string> &Values)
			{
				this->values = Values;
			}
		private:
			json::object *parent = NULL;
			std::string json, error;
			std::vector<std::string> keys;
			std::vector<std::string> values;
		};
		static bool valid_value(const std::string &val)
		{
			char front = val.front(), back = val.back();
			try
			{
				return
					((front == '"' && back == '"')
					|| (front == '\'' && back == '\'')
					|| (front == '[' && back == ']')
					|| (front == '{' && back == '}')
					|| val == "-0" || val == "null"
					|| val == "true" || val == "false")
					|| ultra::isnumeric(val) || std::stod(val);
			}
			catch(std::exception e)
			{
				return false;
			}
		}
		static json::type get_type(const std::string &val)
		{
			json::type t;
			if (valid_value(val))
			{
				switch (val.front())
				{
				case '[':
					t = type::t_array;
					break;
				case '{':
					t = type::t_record;
					break;
				case '""':
					t = type::string;
					break;
				case '\'':
					t = type::string;
					break;
				case 't':
					t = type::boolean;
				case 'f':
					t = type::boolean;
				case 'n':
					t = type::null;
				default:
					t = type::number;
				}
			}
			else
				t = type::undefined;
			return t;
		}
		struct array
		{
			void push_back(std::string val)
			{
				char c = val.front();
				if (valid_value)
					vec.push_back(val);
				bool found_invalid = false;
				std::for_each(vec.begin(), vec.end(), [&found_invalid](std::string s) { if (!valid_value(s)) found_invalid = true; });
				_errors = found_invalid;
			}
			std::vector<std::string> get_vector()
			{
				return vec;
			}
			std::string &back()
			{
				return vec.back();
			}
			bool has_errors()
			{
				return this->_errors;
			}
		private:
			bool _errors = false;
			std::vector<std::string> vec;
		};
		static inline object parse(const std::string &json)
		{
			std::string json_string = json;
			json::object o;
			if (!json.empty())
			{
				o.set_string_no_parse(json);
				std::string taken, error;
				//std::string tmp;
				std::string key, value;
				char c;
				position pos;
				//bool is_key = true;
				//bool is_arr_or_record = false;
				taken = ultra::takewhile_addpos(json_string, ultra::isspace, pos);
				if (json_string.front() == '{')
				{
					json_string.erase(0, 1);
					++pos.x;
					while (json_string.begin() != json_string.end())
					{
						ultra::skipwhile_addpos(json_string, ultra::isspace, pos);
						if (json_string.size() > 0)
							c = json_string.front();
						else
							break;
						// BUG: May not report missing `,`.
						if (c == '"' || c == '\'')
						{
							key = ultra::takebetween_addpos(json_string, c, c, pos);
							json_string.erase(0, 2);
							ultra::skipwhile_addpos(json_string, ultra::isspace, pos);
							if (json_string.front() == ':')
							{
								json_string.erase(0, 1);
								++pos.x;
								skipwhile_addpos(json_string, ultra::isspace, pos);
								c = json_string.front();
								if (ultra::isdigit(c))
								{
									value = takewhile_addpos(json_string, ultra::isdigit, pos);
									if (json_string.front() == '.')
									{
										value += '.';
										json_string.erase(0, 1);
										value += takewhile_addpos(json_string, ultra::isdigit, pos);
									}
								}
								else if (ultra::isalpha(c))
								{
									taken = takewhile_addpos(json_string, ultra::isalpha, pos);
									if (taken == "true" || taken == "false")
										value = taken;
									else
									{

									}
								}
								else if (c == '"' || c == '\'')
								{
									taken = ultra::takebetween_addpos(json_string, c, c, pos);
									json_string.erase(0, 2);
									value = "\"" + taken + "\"";
									skipwhile_addpos(json_string, isspace, pos);
								}
								else if (c == '[')
								{
									taken = '[' + takebetween_addpos(json_string, '[', ']', pos) + ']';
									json_string.erase(0, 2);
									if (json::parse_array(taken, pos).has_errors())
									{
										//pos.x -= taken.size() + 1; // +1 to point to the position of the first character of the json array. 
										error = "Parse error [Invalid Array]";
										break;
									}
									else
									{
										value = taken;
									}
								}
								else if (c == '{')
								{

									taken = '{' + takebetween_addpos(json_string, '{', '}', pos) + '}';
									json_string.erase(0, 2);
									if (json::parse(taken).has_errors())
									{
										error = "Parse error [Invalid Record]";
										break;
									}
									else
									{
										value = taken;
									}
								}
								else if (c == ',' || ultra::isspace(c))
								{
									json_string.erase(0, 1);
									++pos.x;
								}
								else
								{
									error = std::string("Expecting ',' but got '") + json_string.front() + "'";
									break;
								}
								o[key] = value;
								key.clear();
								value.clear();
							}
						}
						else if (c == '}' || c == ',')
						{
							json_string.erase(0, 1);
							++pos.x;
						}
						else
						{
							error = std::string("Expecting 'STRING', 'NUMBER', 'NULL', 'TRUE', 'FALSE', '{', '[', ']', got '")
								+ json_string.front() + "'.";
							break;
						}
					}
				}
				else if (json_string.front() == '[' && json_string.back() == ']')
				{
					array arr = json::parse_array(json_string, pos);
					o.set_values(arr.get_vector());
				}
				else if (json::valid_value(json_string))
				{
					return o;
				}
				else
					error = "Expecting 'STRING', 'NUMBER', 'NULL', 'TRUE', 'FALSE', '{', '[', ']', got 'undefined'.";
				if (!error.empty())
				{
					o.set_error("Parse error on " + std::to_string(pos.y) + ':' + std::to_string(pos.x) + " | " + error);
				}
			}
			return o;
		}
		private:
			static inline json::array parse_array(const std::string &json_array, position pos = position())
			{
				array arr;
				std::string str = json_array;
				if (pos.y == 0)
				{
					skipwhile(str, ultra::isspace);
					if (str.front() == '[' && str.back() == ']')
					{
						str.erase(0, 1);
						skipwhile(str, ultra::isspace);
						std::string val;
						while (str.begin() != str.end())
						{
							char c = str.front();
							if (c != ',' && c != ']')
							{
								val += c;
								str.erase(0, 1);
							}
							else
							{
								str.erase(0, 1);
								skipwhile(str, ultra::isspace);
								arr.push_back(val);
								char &front = arr.back().front();
								char &back = arr.back().back();
								if (front == '\'' && back == '\'')
								{
									front = '"';
									back = '"';
								}
								val.clear();
							}
						}
					}
				}
				else
				{
					skipwhile_addpos(str, ultra::isspace, pos);
					if (str.front() == '[' && str.back() == ']')
					{
						str.erase(0, 1);
						skipwhile_addpos(str, ultra::isspace, pos);
						std::string val;
						while (str.begin() != str.end())
						{
							char c = str.front();
							if (c != ',' && c != ']')
							{
								val += c;
								str.erase(0, 1);
							}
							else
							{
								str.erase(0, 1);
								skipwhile_addpos(str, ultra::isspace, pos);
								arr.push_back(val);
								char &front = arr.back().front();
								char &back = arr.back().back();
								if (front == '\'' && back == '\'')
								{
									front = '"';
									back = '"';
								}
								val.clear();
							}
							++pos.x;
						}
					}
				}
				return arr;
			}
	};
}