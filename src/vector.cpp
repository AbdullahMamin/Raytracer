#include "vector.hpp"

f32 Vector::magnitude() const
{
	return sqrtf(x*x + y*y + z*z);
}

Vector Vector::normalize() const
{
	f32 inv_magnitude = 1.f/magnitude();
	return inv_magnitude*(*this);
}

f32 Vector::dot(Vector v) const
{
	return x*v.x + y*v.y + z*v.z;
}

Vector Vector::cross(Vector v) const
{
	return {y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x};
}

Vector Vector::reflect(Vector normal) const
{
	assert(fabs(normal.magnitude() - 1.f) < EPSILON); // make sure normal is unit length
	return 2.f*dot(normal)*normal - *this;
}

Vector Ray::at(f32 t)
{
	return origin + t*direction;
}

Vector operator+(Vector v1, Vector v2)
{
	return {v1.x + v2.x, v1.y + v2.y, v1.z + v2.z};
}

Vector operator-(Vector v1, Vector v2)
{
	return {v1.x - v2.x, v1.y - v2.y, v1.z - v2.z};
}

Vector operator-(Vector v)
{
	return {-v.x, -v.y, -v.z};
}

Vector operator*(Vector v1, Vector v2)
{
	return {v1.x*v2.x, v1.y*v2.y, v1.z*v2.z};
}

Vector operator*(f32 s, Vector v)
{
	return {s*v.x, s*v.y, s*v.z};
}

Vector operator/(Vector v1, Vector v2)
{
	return {v1.x/v2.x, v1.y/v2.y, v1.z/v2.z};
}
