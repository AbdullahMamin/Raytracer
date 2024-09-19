#include "color.hpp"

Color operator+(Color c1, Color c2)
{
	Color result;
	f32 alpha = (f32)c2.a/255.f;
	result.r = std::min(std::max((1.f - alpha)*c1.r + alpha*c2.r, 0.f), 255.f);
	result.g = std::min(std::max((1.f - alpha)*c1.g + alpha*c2.g, 0.f), 255.f);
	result.b = std::min(std::max((1.f - alpha)*c1.b + alpha*c2.b, 0.f), 255.f);
	return result;
}
