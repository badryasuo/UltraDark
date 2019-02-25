#pragma once
#include "functions.hpp"
namespace u
{
	inline mat4 lookAt(const vec3 &eye, const vec3 & target, const vec3 & up)
	{
		vec3 z_axis = normalize(eye - target);
		vec3 x_axis = normalize(cross(normalize(up), z_axis));
		vec3 y_axis = cross(z_axis, x_axis);
		// Translation Matrix, Identity Matrix by default.
		mat4 T;
		T.d[3][0] = -eye.x;
		T.d[3][1] = -eye.y;
		T.d[3][2] = -eye.z;
		// Rotation Matrix, Identity Matrix by default.
		mat4 R;
		// 1st row
		R.d[0][0] = x_axis.x;
		R.d[1][0] = x_axis.y;
		R.d[2][0] = x_axis.z;
		// 2nd row
		R.d[0][1] = y_axis.x;
		R.d[1][1] = y_axis.y;
		R.d[2][1] = y_axis.z;
		// 3rd row
		R.d[0][2] = z_axis.x;
		R.d[1][2] = z_axis.y;
		R.d[2][2] = z_axis.z;
		// Multiplying the Translation Matrix with the Rotation Matrix.
		return R * T;
	}
	template<typename T>
	inline mat4 ortho(T left, T right, T bottom, T top)
	{
		GLfloat rl = (right - left);
		GLfloat tb = (top - bottom);
		mat4 res;
		res[0][0] = static_cast<T>(2) / rl;
		res[1][1] = static_cast<T>(2) / tb;
		res[2][2] = -static_cast<T>(1);
		res[3][0] = -(right + left) / rl;
		res[3][1] = -(top + bottom) / tb;
		return res;
	}
	template<typename FOV, typename Aspect_Ratio, typename near_view, typename far_view>
	inline mat4 perspective(FOV fovy, Aspect_Ratio aspect, near_view near_sue, far_view far_sue)
	{
		GLfloat f = 1.f / tanf(float(fovy) * 0.5f);
		GLfloat nf = 1.f / (float(near_sue) - float(far_sue));
		mat4 res(GL_FLAG::zero);
		res.d[0][0] = f / float(aspect);
		res.d[1][1] = f;
		res.d[2][2] = (float(near_sue) + float(far_sue)) * nf;
		res.d[2][3] = -1.f;
		res.d[3][2] = 2.f * float(near_sue) * float(far_sue) * nf;
		return res;
	}
}