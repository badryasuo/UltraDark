#pragma once
#include <ultradark/algorithms/basic.hpp>

#pragma warning(disable : 4996)
#include <time.h>       /* time_t, struct tm, time, localtime */
#include <string.h>

#include <stdio.h>
#ifdef _WIN32
#include <Windows.h>
#endif
#include <iostream> 

namespace u
{
	class console
	{
		static POINT point;
		static char buf[128];
		static WORD default_color;
		static CONSOLE_SCREEN_BUFFER_INFO info;
		static time_t rawtime;
		static struct tm * timeinfo;
		static bool Got_Default;
		static HANDLE hConsole;

		static inline int reverse(int x)
		{
			int reversed = 0, remainder;
			while (x != 0)
			{
				remainder = x % 10;
				reversed = (reversed * 10) + remainder;
				x /= 10;
			}
			return reversed;
		}
		static char *substr(const char *cstr, const char *from, const char *to)
		{
			if (cstr && *cstr)
			{
				char *target = NULL;
				const char *start, *end;
				if (start = strstr(cstr, from))
				{
					start += strlen(from);
					if (end = strstr(start, to))
					{
						target = (char *)malloc(end - start + 1);
						memcpy(target, start, end - start);
						target[end - start] = '\0';
					}
				}
				if (target) return target;
			}
			return nullptr;
		}
		static wchar_t *substr(const wchar_t *cstr, wchar_t *from, wchar_t *to)
		{
			if (cstr && *cstr)
			{
				wchar_t *target = NULL;
				const wchar_t *start, *end;
				if (start = wcsstr(cstr, from))
				{
					start += strlen(from);
					if (end = wcsstr(start, to))
					{
						size_t sz = end - start;
						target = (wchar_t *)malloc((sz + 1) * sizeof(wchar_t));
						memcpy(target, start, (end - start) * sizeof(wchar_t));
						target[end - start] = '\0';
					}
				}
				if (target) return target;
			}
				return nullptr;
		}
		static COORD to_coord(const char* xy_str)
		{
			COORD coord = { -1, -1 };
			char temp[6] = { 0 };
			if (isdigit(*xy_str))
			{
				char* first_offset = (char*)xy_str;
				bool searching = true;
				while (searching && *xy_str++)
				{
					if (!isdigit(*xy_str))
					{
						coord.X = atoi((char*)memcpy(temp, first_offset, xy_str - first_offset));
						memset(temp, 0, sizeof(temp));
						while (searching && *xy_str)
						{
							if (isdigit(*xy_str))
							{
								first_offset = (char*)xy_str;
								while (isdigit(*(++xy_str)));
								coord.Y = atoi((char*)memcpy(temp, first_offset, xy_str - first_offset));
								searching = false;
								break;
							}
							else
								++xy_str;
						}
					}
				}
			}
			else
			{
				while (*xy_str++)
				{
					if (isdigit(*xy_str))
					{
						char* first_offset = (char*)xy_str;
						while (isdigit(*(++xy_str)));
						coord.Y = atoi((char*)memcpy(temp, first_offset, xy_str - first_offset));
						break;
					}
				}
			}
			return coord;
		}
		static COORD to_coord(const wchar_t* xy_str)
		{
			COORD coord = { -1, -1 };
			wchar_t temp[6] = { 0 };
			if (isdigit(*xy_str))
			{
				wchar_t* first_offset = (wchar_t*)xy_str;
				bool searching = true;
				while (searching && *xy_str++)
				{
					if (!isdigit(*xy_str))
					{
						coord.X = _wtoi((wchar_t*)memcpy(temp, first_offset, (xy_str - first_offset) * sizeof(wchar_t)));
						memset(temp, 0, sizeof(temp));
						while (searching && *xy_str)
						{
							if (isdigit(*xy_str))
							{
								first_offset = (wchar_t*)xy_str;
								while (isdigit(*(++xy_str)));
								coord.Y = _wtoi((wchar_t*)memcpy(temp, first_offset, (xy_str - first_offset) * sizeof(wchar_t)));
								searching = false;
								break;
							}
							else
								++xy_str;
						}
					}
				}
			}
			else
			{
				while (*xy_str++)
				{
					if (isdigit(*xy_str))
					{
						wchar_t* first_offset = (wchar_t*)xy_str;
						while (isdigit(*(++xy_str)));
						coord.Y = _wtoi((wchar_t*)memcpy(temp, first_offset, (xy_str - first_offset) * sizeof(wchar_t)));
						break;
					}
				}
			}
			return coord;
		}

		template<typename character>
		static character* multiply_str(const character* str)
		{
			unsigned i = 0;
			character* m_str = nullptr;
			character* first_offset = nullptr;
			character* last_offset = nullptr;
			while (*str)
			{
				if (*str == '\'' || *(str) == '"')
				{
					if (first_offset)
					{
						last_offset = (character*)str;
						break;
					}
					first_offset = (character*)str;
				}
				++str;
			}
			size_t len = last_offset - first_offset - 1;
			character *to_print = (character*)memcpy(calloc(1, len + 1), first_offset + 1, len);
			
			return to_print;
		}
	public:
		/*-----________-----*/
		/*   Enumerations   */
		/*-----~~~~~~~~-----*/

		enum color
		{
			normal	= 0x00000010, // Default Console System Color
			red		= 0xFF0000, // Color Red
			green	= 0x00FF00, // Green Color
			blue	= 0x0000FF, // Blue Color
			yellow	= 0xFFFF00, // Yellow Color
			white	= 0xFFFFFF, // Bright White Color
			purple	= 0xFF00FF, // Purple Color
			cyan	= 0x00FFFF, // Cyan Color
			gray	= 0x808080, // Gray Color

			//Dark Colors

			black		= 0x000000, // Black Color
			dark_blue	= 0x0000AA,
			dark_green	= 0x00AA00,
			dark_cyan	= 0x00AAAA,
			dark_red	= 0xAA0000,
			dark_purple	= 0xAA00AA,
			dark_yellow	= 0xAAAA00,
			dark_white	= 0xAAAAAA
		};
		template<typename character>
		static inline void print(const character* format, ...)
		{
			va_list args;
			va_start(args, format);
			int i;
			const character * x;
			while (*format)
			{
				if (*format == '{')
				{
					character* sub_str = substr(format, "{", "}");
					size_t len = u::strlen(sub_str) + 2;
					if (sub_str)
					{
						character* is_multiply_string = substr(sub_str, "'", "'");
						if (!is_multiply_string)
							is_multiply_string = substr(sub_str, "\"", "\"");
						if (is_multiply_string)
						{
							character *to_multiply_str = multiply_str(sub_str);
							print(u::multiply(to_multiply_str, u::to_int(sub_str + u::strlen(to_multiply_str))));
							format += len * sizeof(character);
							free(to_multiply_str);
						}
						else
						{
							COORD coord = to_coord(sub_str);
							if (coord.X == -1)
								coord.X = getxy().X;
							if (coord.Y == -1)
								coord.Y = getxy().Y;
							gotoxy(coord.X, coord.Y);
							format += len * sizeof(character);
						}
						free(sub_str);
					}
				}
				if (*format == '%')
				{
					switch (*(++format))
					{
					case '%':
						putchar('%');
						break;
					case 'd':
						i = va_arg(args, int);
						if (i < 0)
						{
							putchar('-');
							i = -i;
						}
						i == 0 ? putchar('0') : 0;
						i = reverse(i);
						while (i)
						{
							int x = i % 10;
							i /= 10;
							putchar(x + '0');
						}
						break;

					case 'b':
						putchar(va_arg(args, character));
						break;
					case 's':
						x = va_arg(args, const character*);
						while (*x) putchar(*x++);
						break;
					case 'c':
						i = va_arg(args, int);
						if (!Got_Default)
						{
							GetConsoleScreenBufferInfo(hConsole, &info);
							default_color = info.wAttributes;
							Got_Default = true;
						}
						SetConsoleTextAttribute(hConsole, i == color::normal ? default_color :
							i == color::black ? 0 :
							i == color::dark_blue ? 1 :
							i == color::dark_green ? 2 :
							i == color::dark_cyan ? 3 :
							i == color::dark_red ? 4 :
							i == color::dark_purple ? 5 :
							i == color::dark_yellow ? 6 :
							i == color::dark_white ? 7 :
							i == color::gray ? 8 :
							i == color::blue ? 9 :
							i == color::green ? 10 :
							i == color::cyan ? 11 :
							i == color::red ? 12 :
							i == color::purple ? 13 :
							i == color::yellow ? 14 :
							i == color::white ? 15 : i);
						break;
					}
					*format++;
				}
				else
					putchar(*format++);

			}
			//Module 3: Closing argument list to necessary clean-up
			va_end(args);
#ifdef _WIN32
			SetConsoleTextAttribute(hConsole, 7);
#endif
		}/*
		static inline void print(const wchar_t* format, ...)
		{
			va_list args;
			va_start(args, format);
			int i;
			const wchar_t * x;
			while (*format)
			{
				if (*format == '{')
				{
					wchar_t* coord_str = substr(format, '{', '}');
					if (coord_str)
					{
						COORD coord = to_coord(coord_str);
						if (coord.X == -1)
							coord.X = getxy().X;
						if (coord.Y == -1)
							coord.Y = getxy().Y;
						gotoxy(coord.X, coord.Y);
						format += wcslen(coord_str) + 2;
					}
				}
				if (*format == '%')
				{
					switch (*(++format))
					{
					case 'd':
						i = va_arg(args, int);
						if (i < 0)
						{
							putchar('-');
							i = -i;
						}
						i == 0 ? putchar('0') : 0;
						i = reverse(i);
						while (i)
						{
							int x = i % 10;
							i /= 10;
							putchar(x + '0');
						}
						break;

					case 'b':
						putchar(va_arg(args, char));
						break;
					case 's':
						x = va_arg(args, const wchar_t*);
						while (*x) putchar(*x++);
						break;
					case 'c':
						i = va_arg(args, int);
						if (!Got_Default)
						{
							GetConsoleScreenBufferInfo(hConsole, &info);
							default_color = info.wAttributes;
							Got_Default = true;
						}
						SetConsoleTextAttribute(hConsole, i == color::normal ? default_color :
							i == color::black ? 0 :
							i == color::dark_blue ? 1 :
							i == color::dark_green ? 2 :
							i == color::dark_cyan ? 3 :
							i == color::dark_red ? 4 :
							i == color::dark_purple ? 5 :
							i == color::dark_yellow ? 6 :
							i == color::dark_white ? 7 :
							i == color::gray ? 8 :
							i == color::blue ? 9 :
							i == color::green ? 10 :
							i == color::cyan ? 11 :
							i == color::red ? 12 :
							i == color::purple ? 13 :
							i == color::yellow ? 14 :
							i == color::white ? 15 : i);
						break;
					}
					*format++;
				}
				else
					putchar(*format++);

			}
			//Module 3: Closing argument list to necessary clean-up
			va_end(args);
#ifdef _WIN32
			SetConsoleTextAttribute(hConsole, 7);
#endif
		}*/
		struct command
		{
			char* text;
			size_t length;
		};
		static inline const char* my_time(const char * additional_info)
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

		static inline void gotoxy(short x, short y)
		{
			COORD coords = { x, y };
			SetConsoleCursorPosition(hConsole, coords);
		}
		static COORD getxy()
		{
			CONSOLE_SCREEN_BUFFER_INFO cbsi;
			if (GetConsoleScreenBufferInfo(hConsole, &cbsi))
				return cbsi.dwCursorPosition;
			else
			{
				// The function failed. Call GetLastError() for details.
				COORD invalid = { 0, 0 };
				return invalid;
			}
		}
		static inline void getcmd(const char* out, command &cmd)
		{
			GetCursorPos(&point);
			CONSOLE_SCREEN_BUFFER_INFO csbi;
			int columns, rows;
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
			columns = csbi.srWindow.Right - csbi.srWindow.Left + 1;
			rows = csbi.srWindow.Bottom - csbi.srWindow.Top + 1;
			gotoxy(0, rows);
			print(out);
			char buf[512];
			ZeroMemory(buf, 512);
			fgets(buf, 512, stdin);
			cmd.length = strlen(buf);
			cmd.text = (char*)calloc(1, cmd.length + 1);
			strcpy(cmd.text, buf);
			gotoxy(short(point.x), short(point.y));
		}
		static inline short getrealY()
		{
			return short(point.y);
		}
	};
	POINT console::point;
	char console::buf[128];
	WORD console::default_color;
	CONSOLE_SCREEN_BUFFER_INFO console::info;
	time_t console::rawtime;
	struct tm *console::timeinfo;
	bool console::Got_Default = false;
	HANDLE console::hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
}