#ifndef VECTOR_HPP
#define VECTOR_HPP
#include <cmath>
#include <cassert>
#include "types.hpp"

#define EPSILON (1e-5f)

struct Vector
{
	f32 x, y, z;

	f32 magnitude() const;
	Vector normalize() const;
	f32 dot(Vector v) const;
	Vector cross(Vector v) const;
	Vector reflect(Vector normal) const;
};

struct Ray
{
	Vector origin, direction;
	Vector at(f32 t);
};

Vector operator+(Vector v1, Vector v2);
Vector operator-(Vector v1, Vector v2);
Vector operator*(Vector v1, Vector v2);
Vector operator*(f32 s, Vector v);
Vector operator/(Vector v1, Vector v2);

#endif // VECTOR_HPP
