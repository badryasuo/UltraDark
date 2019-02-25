#pragma once
#include "consts.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include <ostream>
#include <iomanip>
/*----------2x2 Matrix */
namespace u
{
	struct mat2
	{
		constexpr mat2()
		{
			
		}
		constexpr mat2(GL_FLAG flag)
		{
			if (flag == zero)
			{
				d[0][0] = 0; d[1][1] = 0;
			}
		}
		constexpr mat2(
			GLfloat c0r0, GLfloat c1r0,
			GLfloat c0r1, GLfloat c1r1)
		{
			d[0][0] = c0r0; d[1][0] = c1r0;
			d[0][1] = c0r1; d[1][1] = c1r1;
		}
		template<typename Matrix>
		constexpr mat2(const Matrix &M)
		{
			d[0][0] = M.d[0][0]; d[1][0] = M.d[1][0];
			d[0][1] = M.d[0][1]; d[1][1] = M.d[1][1];
		}
		/*mat2 operator+(int x)
		{
			
		}*/
		/* Indexing */
		const vec2 &operator[](const int &i) const
		{
			return c[i];
		}

		mat2 operator*(const mat2 &M)
		{
			return mat2(
				d[0][0] * M.d[0][0] + d[1][0] * M.d[0][1],
				d[0][0] * M.d[1][0] + d[1][0] * M.d[1][1],
				d[0][1] * M.d[0][0] + d[1][1] * M.d[0][1],
				d[0][1] * M.d[1][0] + d[1][1] * M.d[1][1]);
		}
		mat2 operator*(const GLfloat &S)
		{
			return mat2(d[0][0] * S, d[1][0] * S, d[0][1] * S, d[1][1] * S);
		}
		mat2 operator/(const GLfloat &S)
		{
			return mat2(d[0][0] / S, d[1][0] / S, d[0][1] / S, d[1][1] / S);
		}
		vec2 operator*(vec2 vec) {
			return vec2((d[0][0] * vec.x) + (d[0][1] * vec.y), (d[1][0] * vec.x) + (d[1][1] * vec.y));
		}
	private:
		// Math Operators
		friend mat2 operator*(const GLfloat &, const mat2 &);
		friend mat2 operator/(const GLfloat &, const mat2 &);
		friend vec2 operator*(const vec2 &, const mat2 &);
		// Functions
		friend GLfloat determinant(const mat2 &);
		friend mat2 inverse(const mat2 &);
		friend mat2 transpose(const mat2 &);
		// Other
		friend std::ostream& operator<<(std::ostream &, const mat2 &);
		union
		{
			vec2 c[2];
			GLfloat d[2][2] = {
				1, 0,
				0, 1 };
		};
	};
	/* Basic Math Operators with Matrices */
	inline mat2 operator*(const GLfloat &S, const mat2 &M)
	{
		return mat2(M.d[0][0] * S, M.d[1][0] * S, M.d[0][1] * S, M.d[1][1] * S);
	}
	inline mat2 operator/(const GLfloat &S, const mat2 &M)
	{
		return mat2(S / M.d[0][0], S / M.d[1][0], S / M.d[0][1], S / M.d[1][1]);
	}
	/* Basic Math Operators with Vectors */
	inline vec2 operator*(const vec2 &vec, const mat2 &M)
	{
		return vec2(
			(M.d[0][0] * vec.x) + (M.d[0][1] * vec.y),
			(M.d[1][0] * vec.x) + (M.d[1][1] * vec.y));
	}
	/* Determinant */
	inline GLfloat determinant(const mat2 &M)
	{
		return M.d[0][0] * M.d[1][1] - M.d[1][0] * M.d[0][1];
	}
	/* Inversing a Matrix */
	inline mat2 inverse(const mat2 &M) {
		mat2 matrix(
			M.d[1][1], -M.d[1][0],
			-M.d[0][1], M.d[0][0]);
		// Multiply the Matrix with its inverse determinant.
		return (1 / determinant(M)) * matrix;
	}
	/* M[col][row] >>> M[row][col] */
	inline mat2 transpose(const mat2 &M)
	{
		return mat2(
			M.d[0][0], M.d[0][1],
			M.d[1][0], M.d[1][1]
		);
	}
	/* Debugging */
	inline std::ostream& operator<<(std::ostream& os, const mat2 &M)
	{
		for (int r = 0; r < 2; ++r)
		{
			for (int c = 0; c < 2; ++c)
				os << (c == 0 ? (M.d[c][r] < 0 ? "" : " ") : M.d[c][r] < 0 ? "\t" : "\t ") << std::setprecision(7) << M.d[c][r];
			putchar('\n');
		}
		return os;
	}
}