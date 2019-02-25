#pragma once
#include "consts.h"
#include "swizzle.hpp"
#include <math.h>
#include <ostream>
/*----------1x2 vector */
namespace u
{
	struct vec2
	{
		union
		{
			struct { GLfloat x, y; };
			struct { GLfloat r, g; };
			struct { GLfloat s, t; };
			vec2_swizzle<vec2, 0, 0> xx;
			vec2_swizzle<vec2, 1, 1> yy;

			GLfloat d[2] = { 0.f, 0.f };
		};

		/* Constructors */

		vec2() {}
		explicit vec2(GLfloat all) : x(all), y(all)
		{

		}
		vec2(GLfloat a, GLfloat b)
		{
			x = a;
			y = b;
		}

		/* Positivating / Negating */

		vec2 operator+() const
		{
			return vec2(+x, +y);
		}
		vec2 operator-() const
		{
			return vec2(-x, -y);
		}

		/* Basic Math Operations with Scalars */

		vec2 operator+(const GLfloat &S) const
		{
			return vec2(x + S, y + S);
		}
		vec2 operator-(const GLfloat &S) const
		{
			return vec2(x - S, y - S);
		}
		vec2 operator*(const GLfloat &S) const
		{
			return vec2(x * S, y * S);
		}
		vec2 operator/(const GLfloat &S) const
		{
			return vec2(x / S, y / S);
		}

		/* Basic Math Operations with Vectors */

		vec2 operator*(const vec2 &vec) const
		{
			return vec2(x * vec.x, y * vec.y);
		}
		vec2 operator/(const vec2 &vec) const
		{
			return vec2(x / vec.x, y / vec.y);
		}
		vec2 operator+(const vec2 &vec) const
		{
			return vec2(x + vec.x, y + vec.y);
		}
		vec2 operator-(const vec2 &vec) const
		{
			return vec2(x - vec.x, y - vec.y);
		}

		/* Basic Math Operators with modifying the Object */

		vec2 &operator*=(const vec2 &vec)
		{
			return *this = vec2(x * vec.x, y * vec.y);
		}
		vec2 &operator/=(const vec2 &vec)
		{
			return *this = vec2(x / vec.x, y / vec.y);
		}
		vec2 &operator+=(const vec2 &vec)
		{
			return *this = vec2(x + vec.x, y + vec.y);
		}
		vec2 &operator-=(const vec2 &vec)
		{
			return *this = vec2(x - vec.x, y - vec.y);
		}
		
		/* Incrementing and Decrementing Operators */

		vec2 operator++(int)
		{
			return vec2(x++, y++);
		}
		vec2 operator--(int)
		{
			return vec2(x--, y--);
		}
		vec2 operator++()
		{
			return vec2(++x, ++y);
		}
		vec2 operator--()
		{
			return vec2(--x, --y);
		}

		vec2 &operator=(const float &x)
		{
			this->x = x;
			this->y = x;
			return *this;
		}
		// Indexing
		GLfloat &operator[](const int i) const
		{
			return (GLfloat&)(d[i > 1 ? -1 : i]);
		}
		// Is equal too?
		const bool operator==(const vec2 &vec) const
		{
			return x == vec.x && y == vec.y;
		}

		/* Member Functions */

		// Retrives the length of a vector.
		GLfloat length() const
		{
			return sqrtf(pow2(x) + pow2(y));
		}
		void cout() const
		{
			printf("(%f, %f)", this->x, this->y);
		}

	};
	/* Basic Math Operations with Scalars */

	inline vec2 operator*(const GLfloat &S, vec2 &vec)
	{
		return vec2(vec.x * S, vec.y * S);
	}

	struct ivec2 : public vec2
	{
		union
		{
			struct { int x, y; };
			struct { int r, g; };
			struct { int s, t; };
			vec2_swizzle<vec2, 0, 0> xx;
			vec2_swizzle<vec2, 1, 1> yy;

			int d[2] = { 0, 0 };
		};

		/* Constructors */

		ivec2() {}
		explicit ivec2(int all) : x(all), y(all) {}
		ivec2(int a, int b)
		{
			x = a;
			y = b;
		}
		int &operator[](const int i) const
		{
			return (int&)(d[i > 1 ? -1 : i]);
		}
	};
	/* Basic Math Operations with Scalars */
	inline ivec2 operator*(const GLfloat &S, ivec2 &vec)
	{
		return ivec2(static_cast<int>(vec.x * S), static_cast<int>(vec.y * S));
	}
}