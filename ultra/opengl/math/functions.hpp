#pragma once
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
namespace u
{
	// Converts degrees to radians.
	template<typename Degrees>
	inline auto radians(Degrees deg) { return deg * 0.0174532925f; }
	// Converts radians to degrees.
	template<typename Radians>
	inline auto degrees(Radians rad) { return rad * 57.295779513f; }

	// Returns the Cross Product between 2D vectors as a scalar.
	inline GLfloat cross(vec2 A, vec2 B) { return (A.x * B.y) - (A.y * B.x); }
	// Returns the Cross Product between 3D vectors as another vector that's perpendicular to both of A & B.
	inline vec3 cross(vec3 A, vec3 B) { return vec3((A.y * B.z) - (A.z * B.y), (A.z * B.x) - (A.x * B.z), (A.x * B.y) - (A.y * B.x)); }
	// Calculating the length of an area.
	template<typename area>
	inline GLfloat length(area A) { return sqrtf(A); }
	// Calculating the length of a 2D vector.
	inline GLfloat length(vec2 V) { return sqrtf(pow2(V.x) + pow2(V.y)); }
	// Calculating the length of a 3D vector.
	inline GLfloat length(vec3 V) { return sqrtf(pow2(V.x) + pow2(V.y) + pow2(V.z)); }
	// Calculating the length of a 4D vector.
	inline GLfloat length(vec4 V) { return sqrtf(pow2(V.x) + pow2(V.y) + pow2(V.z) + pow2(V.w)); }
	// Returns the Dot Product of a 2D vector using |A| . |B| . cos(theta)
	// If both A & B are normalized (length = 1), It returns the cosine angle between A & B.
	inline GLfloat dot(vec2 A, vec2 B) { return (A.x * B.x) + (A.y * B.y); }
	// Returns the Dot Product of a 3D vector, |A| . |B| . cos(theta)
	// if A && B are normalized, it returns the cosine angle between A & B.
	inline GLfloat dot(vec3 A, vec3 B) { return (A.x * B.x) + (A.y * B.y) + (A.z * B.z); }
	// Returns the Dot Product of a 4D vector, |A| . |B| . cos(theta)
	// if A && B are normalized, it returns the cosine angle between A & B.
	inline GLfloat dot(vec4 A, vec4 B) { return (A.x * B.x) + (A.y * B.y) + (A.z * B.z) + (A.w * B.w); }
	// Normalizing
	template<typename Vector>
	inline Vector normalize(Vector V) { return V / V.length(); }
	// Reflecting
	template<typename vector, typename normal_vector>
	inline vector reflect(vector I, normal_vector N) { return (I - N * dot(N, I) * 2); }
	// Compares a and b and returns the greatest.
	template<typename value>
	inline value max(value A, value B) { return (A > B ? A : B); }
	// Compares a and b and returns the smallest.
	template<typename value>
	inline value min(value A, value B) { return (A < B ? A : B); }
}