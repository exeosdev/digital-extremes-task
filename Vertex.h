#ifndef VERTEX_H
#define VERTEX_H

#include <cmath>

struct Vertex
{
    Vertex() = default;

    Vertex(float iX, float iY, float iZ)
	: x(iX)
	, y(iY)
	, z(iZ)
    {}

    float x, y, z;
};

inline Vertex operator-(const Vertex &v1, const Vertex &v2)
{
	return {
		v1.x - v2.x,
		v1.y - v2.y,
		v1.z - v2.z
	};
}

inline float length(const Vertex &v)
{
	return std::sqrtf(v.x*v.x + v.y*v.y + v.z*v.z);
}

#endif // VERTEX_H
