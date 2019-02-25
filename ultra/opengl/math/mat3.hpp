#pragma once
#include "consts.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat2.hpp"
#include <ostream>
#include <iomanip>
/*----------3x3 Matrix */
namespace u
{
	struct mat3
	{
		constexpr mat3()
		{
			
		}
		constexpr mat3(GL_FLAG flag)
		{
			if (flag == zero)
			{
				d[0][0] = 0;
				d[1][1] = 0;
				d[2][2] = 0;
			}
		}
		constexpr mat3(
			GLfloat c0r0, GLfloat c1r0, GLfloat c2r0,
			GLfloat c0r1, GLfloat c1r1, GLfloat c2r1,
			GLfloat c0r2, GLfloat c1r2, GLfloat c2r2)
		{
			d[0][0] = c0r0; d[1][0] = c1r0; d[2][0] = c2r0;
			d[0][1] = c0r1; d[1][1] = c1r1; d[2][1] = c2r1;
			d[0][2] = c0r2; d[1][2] = c1r2; d[2][2] = c2r2;
		}
		template<typename Matrix>
		constexpr mat3(Matrix M)
		{
			d[0][0] = M.d[0][0]; d[1][0] = M.d[1][0]; d[2][0] = M.d[2][0];
			d[0][1] = M.d[0][1]; d[1][1] = M.d[1][1]; d[2][1] = M.d[2][1];
			d[0][2] = M.d[0][2]; d[1][2] = M.d[1][2]; d[2][2] = M.d[2][2];
		}
		//mat3 operator+(int x) {}
		/* Indexing */
		const vec3 &operator[](const int &i) const
		{
			return c[i];
		}
		mat3 operator*(mat3 M)
		{
			return mat3(
				(d[0][0] * M.d[0][0]) + (d[1][0] * M.d[0][1]) + (d[2][0] * M.d[0][2]),
				(d[0][0] * M.d[1][0]) + (d[1][0] * M.d[1][1]) + (d[2][0] * M.d[1][2]),
				(d[0][0] * M.d[2][0]) + (d[1][0] * M.d[2][1]) + (d[2][0] * M.d[2][2]),
				(d[0][1] * M.d[0][0]) + (d[1][1] * M.d[0][1]) + (d[2][1] * M.d[0][2]),
				(d[0][1] * M.d[1][0]) + (d[1][1] * M.d[1][1]) + (d[2][1] * M.d[1][2]),
				(d[0][1] * M.d[2][0]) + (d[1][1] * M.d[2][1]) + (d[2][1] * M.d[2][2]),
				(d[0][2] * M.d[0][0]) + (d[1][2] * M.d[0][1]) + (d[2][2] * M.d[0][2]),
				(d[0][2] * M.d[1][0]) + (d[1][2] * M.d[1][1]) + (d[2][2] * M.d[1][2]),
				(d[0][2] * M.d[2][0]) + (d[1][2] * M.d[2][1]) + (d[2][2] * M.d[2][2]));
		}
		vec3 operator*(vec3 vec)
		{
			return vec3(
				(d[0][0] * vec.x) + (d[0][1] * vec.y) + (d[0][2] * vec.z),
				(d[1][0] * vec.x) + (d[1][1] * vec.y) + (d[1][2] * vec.z),
				(d[2][0] * vec.x) + (d[2][1] * vec.y) + (d[2][2] * vec.z));
		}
		mat3 operator*(const GLfloat &S)
		{
			return mat3(
				d[0][0] * S, d[1][0] * S, d[2][0] * S,
				d[0][1] * S, d[1][1] * S, d[2][1] * S,
				d[0][2] * S, d[1][2] * S, d[2][2] * S);
		}
		mat3 operator/(const GLfloat &S)
		{
			return mat3(
				d[0][0] / S, d[1][0] / S, d[2][0] / S,
				d[0][1] / S, d[1][1] / S, d[2][1] / S,
				d[0][2] / S, d[1][2] / S, d[2][2] / S);
		}
	private:
		// Math Operators
		friend mat3 operator*(const GLfloat &, const mat3 &);
		friend mat3 operator/(const GLfloat &, const mat3 &);
		friend vec3 operator*(const vec3 &, const mat3 &);
		// Functions
		friend GLfloat determinant(const mat3 &);
		friend mat3 inverse(const mat3 &);
		friend mat3 transpose(const mat3 &);
		// Other
		friend std::ostream& operator<<(std::ostream &, const mat3 &);
		union
		{
			vec3 c[3];
			GLfloat d[3][3] = {
				1, 0, 0, 
				0, 1, 0, 
				0, 0, 1 };
		};
	};

	/* Basic Math Operators with Matrices */
	inline mat3 operator*(const GLfloat &S, const mat3 &M)
	{
		return mat3(
			S * M.d[0][0], S * M.d[1][0], S * M.d[2][0],
			S * M.d[0][1], S * M.d[1][1], S * M.d[2][1],
			S * M.d[0][2], S * M.d[1][2], S * M.d[2][2]);
	}
	inline mat3 operator/(const GLfloat &S, const mat3 &M)
	{
		return mat3(
			S / M.d[0][0], S / M.d[1][0], S / M.d[2][0],
			S / M.d[0][1], S / M.d[1][1], S / M.d[2][1],
			S / M.d[0][2], S / M.d[1][2], S / M.d[2][2]);
	}
	/* Basic Math Operators with Vectors */
	inline vec3 operator*(const vec3 &vec, const mat3 &M)
	{
		return vec3(
			(M.d[0][0] * vec.x) + (M.d[0][1] * vec.y) + (M.d[0][2] * vec.z),
			(M.d[1][0] * vec.x) + (M.d[1][1] * vec.y) + (M.d[1][2] * vec.z),
			(M.d[2][0] * vec.x) + (M.d[2][1] * vec.y) + (M.d[2][2] * vec.z));
	}
	/* Matrix Of Minors */
#define m3_minor_0x0(M)mat2(M.d[1][1], M.d[2][1], M.d[1][2], M.d[2][2])
#define m3_minor_1x0(M)mat2(M.d[0][1], M.d[2][1], M.d[0][2], M.d[2][2])
#define m3_minor_2x0(M)mat2(M.d[0][1], M.d[1][1], M.d[0][2], M.d[1][2])
#define m3_minor_0x1(M)mat2(M.d[1][0], M.d[2][0], M.d[1][2], M.d[2][2])
#define m3_minor_1x1(M)mat2(M.d[0][0], M.d[2][0], M.d[0][2], M.d[2][2])
#define m3_minor_2x1(M)mat2(M.d[0][0], M.d[1][0], M.d[0][2], M.d[1][2])
#define m3_minor_0x2(M)mat2(M.d[1][0], M.d[2][0], M.d[1][1], M.d[2][1])
#define m3_minor_1x2(M)mat2(M.d[0][0], M.d[2][0], M.d[0][1], M.d[2][1])
#define m3_minor_2x2(M)mat2(M.d[0][0], M.d[1][0], M.d[0][1], M.d[1][1])


	/* Determinant */
	/*inline GLfloat determinant(const mat2 &M) { return M.d[0][0] * M.d[1][1] - M.d[1][0] * M.d[0][1]; }*/
	inline GLfloat determinant(const mat3 &M) {
		return
			(M.d[0][0] * ((M.d[1][1] * M.d[2][2]) - (M.d[2][1] * M.d[1][2]))) -
			(M.d[1][0] * ((M.d[0][1] * M.d[2][2]) - (M.d[2][1] * M.d[0][2]))) +
			(M.d[2][0] * ((M.d[0][1] * M.d[1][2]) - (M.d[1][1] * M.d[0][2])));
	}
	/* Inversing a Matrix */
	inline mat3 inverse(const mat3 &M) {
		mat3 matrix(
			determinant(m3_minor_0x0(M)),-determinant(m3_minor_0x1(M)), determinant(m3_minor_0x2(M)),
		   -determinant(m3_minor_1x0(M)), determinant(m3_minor_1x1(M)),-determinant(m3_minor_1x2(M)),
			determinant(m3_minor_2x0(M)),-determinant(m3_minor_2x1(M)), determinant(m3_minor_2x2(M)));
		// Multiply the Matrix with its inverse determinant.
		return (1 / determinant(M)) * matrix;
	}
	/* M[col][row] >>> M[row][col] */
	inline mat3 transpose(const mat3 &M)
	{
		return mat3(
			M.d[0][0], M.d[0][1], M.d[0][2],
			M.d[1][0], M.d[1][1], M.d[1][2],
			M.d[2][0], M.d[2][1], M.d[2][2]
		);
	}
	/* Debugging */
	inline std::ostream& operator<<(std::ostream &os, const mat3 &M)
	{
		for (int r = 0; r < 3; ++r)
		{
			for (int c = 0; c < 3; ++c)
				os << (c == 0 ? (M.d[c][r] < 0 ? "" : " ") : M.d[c][r] < 0 ? "\t" : "\t ") << std::setprecision(7) << (abs(M.d[c][r]) < 0.0000005f ? 0 : M.d[c][r]);
			putchar('\n');
		}
		return os;
	}
}