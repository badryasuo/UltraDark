#pragma once
#include "consts.h"
#include "mat4.hpp"
/*--Transformatios--*/
namespace u
{
	// Translates a Matrixatrix to a given position using a vector.
	template<typename Matrix, typename Position_Vector>
	inline Matrix translate(Matrix M, Position_Vector position)
	{
		// Translation Matrix Transformation.
		auto &p = position;
		mat4 T(
			1.f, 0.f, 0.f, p.x,
			0.f, 1.f, 0.f, p.y,
			0.f, 0.f, 1.f, p.z,
			0.f, 0.f, 0.f, 1.f);
		
		// translates the provided M to a new position keeping its data
		// instead of just returning the T.
		return M * T; // read from right to left.
	}
	// Scales a Matrix to a given size on specific axes using a vector.
	template<typename Matrix, typename Scalar_Vector>
	inline Matrix scale(Matrix M, Scalar_Vector scalar)
	{
		// Scalar Matrix Transformation.
		auto &s = scalar;
		mat4 S(
			s.x, 0.f, 0.f, 0.f,
			0.f, s.y, 0.f, 0.f,
			0.f, 0.f, s.z, 0.f,
			0.f, 0.f, 0.f, 1.f);
		return M * S; // Multiply the S with the provided M
	}
	// Rotates a Matrixatrix around given axes using a vector with some angle theta.
	template<typename Angle, typename Rotation_Vector_Axes>
	inline mat4 rotate(mat4 M, Angle angle_in_radians, Rotation_Vector_Axes rotation_axes)
	{
		// Rotation Matrix Transformation.
		GLfloat cos0 = cosf(angle_in_radians);
		GLfloat sin0 = sinf(angle_in_radians);
		Rotation_Vector_Axes r = normalize(rotation_axes);
		mat4 R(
			 cos0 + (pow2(r.x) * (1-cos0)) , (r.x*r.y*(1-cos0)) - (r.z * sin0), (r.x*r.z*(1-cos0)) + (r.y*sin0), 0,
			(r.y*r.x*(1-cos0)) + (r.z*sin0),    cos0 + pow2(r.y) * (1-cos0)   , (r.y*r.z*(1-cos0)) - (r.x*sin0), 0,
			(r.z*r.x*(1-cos0)) - (r.y*sin0),   r.z*r.y*(1-cos0) + (r.x*sin0)  ,   cos0 + (pow2(r.z)*(1-cos0))  , 0,
						  0.f			   ,		         0.f              , 				0.f            , 1.f);

		return M * R; // Multiply the rotation Matrix with the provided Matrix.
	}
}