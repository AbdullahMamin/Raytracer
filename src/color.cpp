#include "color.hpp"

Color operator+(Color c1, Color c2)
{
	Color result;
	result.r = std::min(std::max((1.f - c2.a)*c1.r + c2.a*c2.r, 0.f), 1.f);
	result.g = std::min(std::max((1.f - c2.a)*c1.g + c2.a*c2.g, 0.f), 1.f);
	result.b = std::min(std::max((1.f - c2.a)*c1.b + c2.a*c2.b, 0.f), 1.f);
	return result;
}

Color operator*(f32 s, Color c)
{
	Color result;
	result.r = std::min(std::max(s*c.r, 0.f), 1.f);
	result.g = std::min(std::max(s*c.g, 0.f), 1.f);
	result.b = std::min(std::max(s*c.b, 0.f), 1.f);
	return result;
}
