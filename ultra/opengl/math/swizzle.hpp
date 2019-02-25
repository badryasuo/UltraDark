#pragma once
#include <iostream>
namespace u
{
	template<typename vec_type, unsigned int A, unsigned int B>
	struct vec2_swizzle
	{
		float d[2];
		vec_type operator=(const vec_type& vec)
		{
			d[A] = vec.x;
			d[B] = vec.y;
			// Cast this vec2_swizzle* to vec2* and return the *pointed* (i.e *this) object as a reference.
			//return vec_type(d[A], d[B]);
			return *static_cast<vec_type*>(this);
		}
		operator vec_type()
		{
			return vec_type(d[A], d[B]);
		}
	};
	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C>
	struct vec3_swizzle
	{
		float d[3];
		vec_type& operator=(const vec_type& vec)
		{
			d[A] = vec.x;
			d[B] = vec.y;
			d[C] = vec.z;
			return *(vec_type*)this;
		}
		operator vec_type()
		{
			return vec_type(d[A], d[B], d[C]);
		}
	};
	template<typename vec_type, unsigned int A, unsigned int B, unsigned int C, unsigned int D>
	struct vec4_swizzle
	{
		float d[4];
		vec_type& operator=(const vec_type& vec)
		{
			d[A] = vec.x;
			d[B] = vec.y;
			d[C] = vec.z;
			d[D] = vec.w;
			return *(vec_type*)this;
		}
		operator vec_type()
		{
			return vec_type(d[A], d[B], d[C], d[D]);
		}
	};
}