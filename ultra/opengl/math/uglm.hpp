#ifndef DARK_GLSL
#define DARK_GLSL
#endif
#include <iostream>
#include <iomanip>

#include "consts.h"

#include "swizzle.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

#include "mat2.hpp"
#include "mat3.hpp"
#include "mat4.hpp"

#include "transformations.hpp"
#include "projection.hpp"

#include "functions.hpp"
#ifndef DARK_GLSL_DEBUG
#define DARK_GLSL_DEBUG
namespace u
{
	/* DEBUGGING */
	// Returns the angle between two vectors in radians.
	template<typename vector>
	inline GLfloat angle(vector A, vector B) { return acosf(dot(normalize(A), normalize(B))); }
}
#endif