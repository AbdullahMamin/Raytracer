#ifndef RAYTRACER_HPP
#define RAYTRACER_HPP
#include <lua5.4/lua.h>
#include <lua5.4/lauxlib.h>
#include <lua5.4/lualib.h>
#include <vector>
#include <cassert>
#include <iostream>
#include <fstream>
#include <utility>
#include "vector.hpp"
#include "color.hpp"

struct Sphere
{
	Vector position;
	f32 radius;
	Color color;

	std::pair<f32, f32> getRayIntersection(Ray ray);
};

class Scene
{
public:
	Scene(i32 size, const char *file_path);
	void print() const;
	void render(const char *file_path);
	
private:
	Color castRay(i32 x, i32 y);

private:
	const Color m_background_color = {1.f, 1.f, 1.f, 1.f};
	i32 m_size;
	std::vector<Sphere> m_spheres;
};

#endif // RAYTRACER_HPP
