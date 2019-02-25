		static inline object parse(std::string json_string)
		{
			json::object o;
			std::string tmp;
			std::string key, value;
			bool is_key = true;
			bool is_arr_or_record = false;
			if (json_string.front() == '{' && json_string.back() == '}' && json_string[1] == '"')
			{
				for (size_t i = 1; i < json_string.size(); ++i)
				{
					type t = type::undefined;
					// BUG 1: This function doesn't parse both key && value in one iteration.
					key.clear(); // which results to a problem because of that line!
					if (json_string[i] == '"')
					{
						while (++i)
						{
							tmp += json_string[i];
							if (json_string[i + 1] == '"' && ++i)
								break;
						}
						if (json_string[++i] == ':')
						{
							is_key = true;
							key = tmp;
							tmp.clear();
							switch (json_string[i + 1])
							{
							case '{':
								t = type::record;
								break;
							case '[':
								t = type::array;
								break;
							case '"':
								t = type::string;
								break;
							default:
								t = type::number;
								break;
							}
							if (json_string[i + 1] == '[')

								if (u::is_digit(json_string[i + 1]))
									t = type::number;
							bool found_endof_arr_or_record = false;
							while (++i)
							{
								tmp += json_string[i];
								if (is_arr_or_record)
								{
									if (tmp.back() == ']' or tmp.back() == '}')
										if (json_string[i + 1] == ',' && ++i)
											break;
								}
								else
									if (json_string[i + 1] == ',' || json_string[i + 1] == '}')
									{
										++i;
										break;
									}
							}
							is_key = false;
							value = tmp;
							tmp.clear();
						}
						else
						{
							is_key = false;
							value = tmp;
							tmp.clear();
						}
					}
					else
					{
						value.clear();
						is_key = false;
						while (json_string[i] != ',')
						{
							tmp += json_string[i];
						}
						value = tmp;
					}
					if (!key.empty() && !value.empty())
					{
						o[key] = value;
					}
				}
			}
			ret:
			return o;
		}