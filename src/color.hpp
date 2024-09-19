#ifndef COLOR_HPP
#define COLOR_HPP
#include <algorithm>
#include "types.hpp"

struct Color
{
	f32 r, g, b, a;
};

Color operator+(Color c1, Color c2);
Color operator*(f32 s, Color c);

#endif // COLOR_HPP
