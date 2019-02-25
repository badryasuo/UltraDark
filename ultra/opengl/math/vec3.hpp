#pragma once
#ifndef DARK_GLSL
#define DARK_GLSL
#endif
#include "consts.h"
#include "vec2.hpp"
#include <math.h>
#include <ostream>
/*----------1x3 vector */
namespace u
{
	struct vec3
	{
		union
		{
			struct { GLfloat x, y, z; };
			struct { GLfloat r, g, b; };
			struct { GLfloat s, t, p; };

			vec2_swizzle<vec2, 0, 1> xy;
			vec3_swizzle<vec3, 0, 1, 2> xyz;
			//struct { vec2 rg; };
			//struct { vec2 st; };
			//
			//struct { float x; vec2 yz; };
			//struct { float r; vec2 gb; };
			//struct { float s; vec2 tp; };
			GLfloat d[3] = { 0.f, 0.f, 0.f };
		};

		/* Constructors */

		vec3() {}
		explicit vec3(GLfloat all) : x(all), y(all), z(all)
		{

		}
		vec3(GLfloat a, GLfloat b, GLfloat c)
		{
			x = a;
			y = b;
			z = c;
		}
		/* Positivating / Negating */

		vec3 operator+() const
		{
			return vec3(+x, +y, +z);
		}
		vec3 operator-() const
		{
			return vec3(-x, -y, -z);
		}

		/* Basic Math Operations with Scalars */

		vec3 operator*(const GLfloat &S) const
		{
			return vec3(x * S, y * S, z * S);
		}
		vec3 operator/(const GLfloat &S) const
		{
			return vec3(x / S, y / S, z / S);
		}
		vec3 operator+(const GLfloat &S) const
		{
			return vec3(x + S, y + S, z + S);
		}
		vec3 operator-(const GLfloat &S) const
		{
			return vec3(x - S, y - S, z - S);
		}

		/* Basic Math Operations with Vectors */

		vec3 operator*(const vec3 &vec) const
		{
			return vec3(x * vec.x, y * vec.y, z * vec.z);
		}
		vec3 operator/(const vec3 &vec) const
		{
			return vec3(x / vec.x, y / vec.y, z / vec.z);
		}
		vec3 operator+(const vec3 &vec) const
		{
			return vec3(x + vec.x, y + vec.y, z + vec.z);
		}
		vec3 operator-(const vec3 &vec) const
		{
			return vec3(x - vec.x, y - vec.y, z - vec.z);
		}

		/* Basic Math Operators with modifying the Object */

		vec3 &operator*=(const vec3 &vec)
		{
			return *this = vec3(x * vec.x, y * vec.y, z * vec.z);
		}
		vec3 &operator/=(const vec3 &vec)
		{
			return *this = vec3(x / vec.x, y / vec.y, z / vec.z);
		}
		vec3 &operator+=(const vec3 &vec)
		{
			return *this = vec3(x + vec.x, y + vec.y, z + vec.z);
		}
		vec3 &operator-=(const vec3 &vec)
		{
			return *this = vec3(x - vec.x, y - vec.y, z - vec.z);
		}
		
		/* Incrementing and Decrementing Operators */

		vec3 operator++(int)
		{
			return vec3(x++, y++, z++);
		}
		vec3 operator--(int)
		{
			return vec3(x--, y--, z--);
		}
		vec3 operator++()
		{
			return vec3(++x, ++y, ++z);
		}
		vec3 operator--()
		{
			return vec3(--x, --y, --z);
		}
		// Indexing
		GLfloat &operator[](const int i) const
		{
			return (GLfloat&)(d[i > 2 ? -1 : i]);
		}
		// Is equal too?
		const bool operator==(const vec3 &vec) const
		{
			return x == vec.x && y == vec.y && z == vec.z;
		}

		/* Member Functions */

		// Retrives the length of a vector.
		GLfloat length() const
		{
			return sqrtf(pow2(x) + pow2(y) + pow2(z));
		}
		void cout() const
		{
			printf("(%f, %f, %f)", this->x, this->y, this->z);
		}
	};
	/* Basic Math Operations with Scalars */
	inline std::ostream &operator <<(std::ostream& os, const u::vec3 &vec)
	{
		os << '(' << vec.x << ", " << vec.y << ", " << vec.z << ')';
		return os;
	}
	inline vec3 operator*(const GLfloat &S, vec3 vec)
	{
		return vec3(vec.x * S, vec.y * S, vec.z * S);
	}
}