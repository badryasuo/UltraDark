#pragma once
#include "consts.h"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "mat3.hpp"
#include <ostream>
#include <iomanip>
/*----------4x4 Matrix */
namespace u
{
	struct mat4
	{
		constexpr mat4()
		{
			
		}
		constexpr mat4(GL_FLAG flag)
		{
			if (flag == zero)
			{
				d[0][0] = 0;
				d[1][1] = 0;
				d[2][2] = 0;
				d[3][3] = 0;
			}
		}
		template<typename T>
		constexpr explicit mat4(T v)
		{
			d[0][0] = float(v);
			d[1][1] = float(v);
			d[2][2] = float(v);
			d[3][3] = float(v);
		}
		constexpr mat4(
			GLfloat c0r0, GLfloat c1r0, GLfloat c2r0, GLfloat c3r0,
			GLfloat c0r1, GLfloat c1r1, GLfloat c2r1, GLfloat c3r1,
			GLfloat c0r2, GLfloat c1r2, GLfloat c2r2, GLfloat c3r2,
			GLfloat c0r3, GLfloat c1r3, GLfloat c2r3, GLfloat c3r3)
		{
			d[0][0] = c0r0; d[1][0] = c1r0; d[2][0] = c2r0; d[3][0] = c3r0;
			d[0][1] = c0r1; d[1][1] = c1r1; d[2][1] = c2r1; d[3][1] = c3r1;
			d[0][2] = c0r2; d[1][2] = c1r2; d[2][2] = c2r2; d[3][2] = c3r2;
			d[0][3] = c0r3; d[1][3] = c1r3; d[2][3] = c2r3; d[3][3] = c3r3;
		}
		/* Indexing */
		vec4 &operator[](const int &i) const
		{
			return (vec4&)c[i];
		}

		mat4 operator*(mat4 M)
		{
			return mat4(
				d[0][0] * M.d[0][0] + d[1][0] * M.d[0][1] + d[2][0] * M.d[0][2] + d[3][0] * M.d[0][3],
				d[0][0] * M.d[1][0] + d[1][0] * M.d[1][1] + d[2][0] * M.d[1][2] + d[3][0] * M.d[1][3],
				d[0][0] * M.d[2][0] + d[1][0] * M.d[2][1] + d[2][0] * M.d[2][2] + d[3][0] * M.d[2][3],
				d[0][0] * M.d[3][0] + d[1][0] * M.d[3][1] + d[2][0] * M.d[3][2] + d[3][0] * M.d[3][3],
				d[0][1] * M.d[0][0] + d[1][1] * M.d[0][1] + d[2][1] * M.d[0][2] + d[3][1] * M.d[0][3],
				d[0][1] * M.d[1][0] + d[1][1] * M.d[1][1] + d[2][1] * M.d[1][2] + d[3][1] * M.d[1][3],
				d[0][1] * M.d[2][0] + d[1][1] * M.d[2][1] + d[2][1] * M.d[2][2] + d[3][1] * M.d[2][3],
				d[0][1] * M.d[3][0] + d[1][1] * M.d[3][1] + d[2][1] * M.d[3][2] + d[3][1] * M.d[3][3],
				d[0][2] * M.d[0][0] + d[1][2] * M.d[0][1] + d[2][2] * M.d[0][2] + d[3][2] * M.d[0][3],
				d[0][2] * M.d[1][0] + d[1][2] * M.d[1][1] + d[2][2] * M.d[1][2] + d[3][2] * M.d[1][3],
				d[0][2] * M.d[2][0] + d[1][2] * M.d[2][1] + d[2][2] * M.d[2][2] + d[3][2] * M.d[2][3],
				d[0][2] * M.d[3][0] + d[1][2] * M.d[3][1] + d[2][2] * M.d[3][2] + d[3][2] * M.d[3][3],
				d[0][3] * M.d[0][0] + d[1][3] * M.d[0][1] + d[2][3] * M.d[0][2] + d[3][3] * M.d[0][3],
				d[0][3] * M.d[1][0] + d[1][3] * M.d[1][1] + d[2][3] * M.d[1][2] + d[3][3] * M.d[1][3],
				d[0][3] * M.d[2][0] + d[1][3] * M.d[2][1] + d[2][3] * M.d[2][2] + d[3][3] * M.d[2][3],
				d[0][3] * M.d[3][0] + d[1][3] * M.d[3][1] + d[2][3] * M.d[3][2] + d[3][3] * M.d[3][3]);
		}
		vec4 operator*(vec4 vec)
		{
			return vec4(
				(d[0][0] * vec.x) + (d[0][1] * vec.y) + (d[0][2] * vec.z) + (d[3][0] * vec.w),
				(d[1][0] * vec.x) + (d[1][1] * vec.y) + (d[1][2] * vec.z) + (d[3][1] * vec.w),
				(d[2][0] * vec.x) + (d[2][1] * vec.y) + (d[2][2] * vec.z) + (d[3][2] * vec.w),
				(d[3][0] * vec.x) + (d[3][1] * vec.y) + (d[3][2] * vec.z) + (d[3][3] * vec.w));
		}
		// Multiply the Matrix with a Scalar.
		mat4 operator*(const GLfloat &S)
		{
			return mat4(
				d[0][0] * S, d[1][0] * S, d[2][0] * S, d[3][0] * S,
				d[0][1] * S, d[1][1] * S, d[2][1] * S, d[3][1] * S,
				d[0][2] * S, d[1][2] * S, d[2][2] * S, d[3][2] * S,
				d[0][3] * S, d[1][3] * S, d[2][3] * S, d[3][3] * S);
		}
		// Divide the Matrix on a Scalar.
		mat4 operator/(const GLfloat &S)
		{
			return mat4(
				d[0][0] / S, d[1][0] / S, d[2][0] / S, d[3][0] / S,
				d[0][1] / S, d[1][1] / S, d[2][1] / S, d[3][1] / S,
				d[0][2] / S, d[1][2] / S, d[2][2] / S, d[3][2] / S,
				d[0][3] / S, d[1][3] / S, d[2][3] / S, d[3][3] / S);
		}

		/* Member Functions */

		// Retrives the minor of the Matrix from a given position.
		mat3 minor(unsigned int col, unsigned int row)
		{
			mat3 minor(u::GL_FLAG::zero);
			if (col < 3 && row < 3)
			{
				unsigned _col = 0;
				unsigned _row = 0;
				for (unsigned _r = 0; _r < 4; ++_r)
				{
					for (unsigned _c = 0; _c < 4; ++_c)
					{
						if (_r == row)
							break;
						if (_c != col)
						{
							minor[_col][_row] = d[_c][_r];
							if (_col == 2)
							{
								_row++;
								_col = 0;
							}
							else
								_col++;
						}
					}
				}
			}
			return minor;
		}
		private:
			// Math Operators
			friend mat4 operator*(const GLfloat &, const mat4 &);
			friend mat4 operator/(const GLfloat &, const mat4 &);
			friend vec4 operator*(const vec4 &, const mat4 &);
			// Functions
			friend GLfloat determinant(mat4);
			friend mat4 inverse(const mat4 &);
			friend mat4 transpose(mat4);
			// Projection
			friend mat4 lookAt(const vec3 &, const vec3 &, const vec3 &);
			friend mat4 ortho(GLfloat, GLfloat, GLfloat, GLfloat, GLfloat, GLfloat);
			template<typename FOV, typename Aspect_Ratio, typename near_view, typename far_view>
			friend inline mat4 perspective(FOV fovy, Aspect_Ratio aspect, near_view near_sue, far_view far_sue);
			// Other
			friend std::ostream& operator<<(std::ostream&, mat4&);
			union
			{
				vec4 c[4];
				GLfloat d[4][4] = {
					1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0 ,0 , 1 };
			};
	};

	/* Basic Math Operators with Matrices */
	inline mat4 operator*(const GLfloat &S, const mat4 &M)
	{
		return mat4(
			S * M.d[0][0], S * M.d[1][0], S * M.d[2][0], S * M.d[3][0],
			S * M.d[0][1], S * M.d[1][1], S * M.d[2][1], S * M.d[3][1],
			S * M.d[0][2], S * M.d[1][2], S * M.d[2][2], S * M.d[3][2],
			S * M.d[0][3], S * M.d[1][3], S * M.d[2][3], S * M.d[3][3]);
	}
	inline mat4 operator/(const GLfloat &S, const mat4 &M)
	{
		return mat4(
			S / M.d[0][0], S / M.d[1][0], S / M.d[2][0], S / M.d[3][0],
			S / M.d[0][1], S / M.d[1][1], S / M.d[2][1], S / M.d[3][1],
			S / M.d[0][2], S / M.d[1][2], S / M.d[2][2], S / M.d[3][2],
			S / M.d[0][3], S / M.d[1][3], S / M.d[2][3], S / M.d[3][3]);
	}
	/* Basic Math Operators with Vectors */
	inline vec4 operator*(const vec4 &vec, const mat4 &M) {
		return vec4(
			(M.d[0][0] * vec.x) + (M.d[0][1] * vec.y) + (M.d[0][2] * vec.z) + (M.d[3][0] * vec.w),
			(M.d[1][0] * vec.x) + (M.d[1][1] * vec.y) + (M.d[1][2] * vec.z) + (M.d[3][1] * vec.w),
			(M.d[2][0] * vec.x) + (M.d[2][1] * vec.y) + (M.d[2][2] * vec.z) + (M.d[3][2] * vec.w),
			(M.d[3][0] * vec.x) + (M.d[3][1] * vec.y) + (M.d[3][2] * vec.z) + (M.d[3][3] * vec.w));
	}
	/* Matrix Of Minors */
#define minor_0x0(m)mat3(m.d[1][1], m.d[2][1], m.d[3][1], m.d[1][2], m.d[2][2], m.d[3][2], m.d[1][3], m.d[2][3], m.d[3][3])
#define minor_1x0(m)mat3(m.d[0][1], m.d[2][1], m.d[3][1], m.d[0][2], m.d[2][2], m.d[3][2], m.d[0][3], m.d[2][3], m.d[3][3])
#define minor_2x0(m)mat3(m.d[0][1], m.d[1][1], m.d[3][1], m.d[0][2], m.d[1][2], m.d[3][2], m.d[0][3], m.d[1][3], m.d[3][3])
#define minor_3x0(m)mat3(m.d[0][1], m.d[1][1], m.d[2][1], m.d[0][2], m.d[1][2], m.d[2][2], m.d[0][3], m.d[1][3], m.d[2][3])
#define minor_0x1(m)mat3(m.d[1][0], m.d[2][0], m.d[3][0], m.d[1][2], m.d[2][2], m.d[3][2], m.d[1][3], m.d[2][3], m.d[3][3])
#define minor_1x1(m)mat3(m.d[0][0], m.d[2][0], m.d[3][0], m.d[0][2], m.d[2][2], m.d[3][2], m.d[0][3], m.d[2][3], m.d[3][3])
#define minor_2x1(m)mat3(m.d[0][0], m.d[1][0], m.d[3][0], m.d[0][2], m.d[1][2], m.d[3][2], m.d[0][3], m.d[1][3], m.d[3][3])
#define minor_3x1(m)mat3(m.d[0][0], m.d[1][0], m.d[2][0], m.d[0][2], m.d[1][2], m.d[2][2], m.d[0][3], m.d[1][3], m.d[2][3])
#define minor_0x2(m)mat3(m.d[1][0], m.d[2][0], m.d[3][0], m.d[1][1], m.d[2][1], m.d[3][1], m.d[1][3], m.d[2][3], m.d[3][3])
#define minor_1x2(m)mat3(m.d[0][0], m.d[2][0], m.d[3][0], m.d[0][1], m.d[2][1], m.d[3][1], m.d[0][3], m.d[2][3], m.d[3][3])
#define minor_2x2(m)mat3(m.d[0][0], m.d[1][0], m.d[3][0], m.d[0][1], m.d[1][1], m.d[3][1], m.d[0][3], m.d[1][3], m.d[3][3])
#define minor_3x2(m)mat3(m.d[0][0], m.d[1][0], m.d[2][0], m.d[0][1], m.d[1][1], m.d[2][1], m.d[0][3], m.d[1][3], m.d[2][3])
#define minor_0x3(m)mat3(m.d[1][0], m.d[2][0], m.d[3][0], m.d[1][1], m.d[2][1], m.d[3][1], m.d[1][2], m.d[2][2], m.d[3][2])
#define minor_1x3(m)mat3(m.d[0][0], m.d[2][0], m.d[3][0], m.d[0][1], m.d[2][1], m.d[3][1], m.d[0][2], m.d[2][2], m.d[3][2])
#define minor_2x3(m)mat3(m.d[0][0], m.d[1][0], m.d[3][0], m.d[0][1], m.d[1][1], m.d[3][1], m.d[0][2], m.d[1][2], m.d[3][2])
#define minor_3x3(m)mat3(m.d[0][0], m.d[1][0], m.d[2][0], m.d[0][1], m.d[1][1], m.d[2][1], m.d[0][2], m.d[1][2], m.d[2][2])
	/* Determinant */
	inline GLfloat determinant(mat4 M)
	{
		return
			(M.d[0][0] * determinant(minor_0x0(M))) -
			(M.d[1][0] * determinant(minor_1x0(M))) +
			(M.d[2][0] * determinant(minor_2x0(M))) -
			(M.d[3][0] * determinant(minor_3x0(M)));
	}
	/* Inversing a Matrixatrix */
	inline mat4 inverse(const mat4 &M)
	{
		mat4 matrix(
			determinant(minor_0x0(M)), -determinant(minor_0x1(M)), determinant(minor_0x2(M)), -determinant(minor_0x3(M)),
			-determinant(minor_1x0(M)), determinant(minor_1x1(M)), -determinant(minor_1x2(M)), determinant(minor_1x3(M)),
			determinant(minor_2x0(M)), -determinant(minor_2x1(M)), determinant(minor_2x2(M)), -determinant(minor_2x3(M)),
			-determinant(minor_3x0(M)), determinant(minor_3x1(M)), -determinant(minor_3x2(M)), determinant(minor_3x3(M)));
		return (1 / determinant(M)) * matrix;
	}
	/* M[col][row] >>> M[row][col] */
	inline mat4 transpose(mat4 M)
	{
		return mat4(
			M.d[0][0], M.d[0][1], M.d[0][2], M.d[0][3],
			M.d[1][0], M.d[1][1], M.d[1][2], M.d[1][3],
			M.d[2][0], M.d[2][1], M.d[2][2], M.d[2][3],
			M.d[3][0], M.d[3][1], M.d[3][2], M.d[3][3]
		);
	}
	/* Debugging */
	inline std::ostream& operator<<(std::ostream& os, mat4& M)
	{
		for (int r = 0; r < 4; ++r)
		{
			for (int c = 0; c < 4; ++c)
				os << (c == 0 ? (M.d[c][r] < 0 ? "" : " ") : M.d[c][r] < 0 ? "\t" : "\t ") << std::setprecision(7) << (abs(M.d[c][r]) < 0.0000005f ? 0 : M.d[c][r]);
			putchar('\n');
		}
		return os;
	}
}