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
#include <thread>
#include "vector.hpp"
#include "color.hpp"

struct Sphere
{
	Vector position;
	f32 radius;
	f32 specular;
	f32 reflective;
	Color color;

	std::pair<f32, f32> getRayIntersection(Ray ray);
};

enum LightType
{
	LT_AMBIENT,
	LT_POINT,
	LT_DIRECTIONAL
};

// Light direction is from surface point towards the light i.e. the light direction of the sun would direct at the sun, not from it.
struct Light
{
	LightType type;
	f32 intensity;
	Vector position;
	Vector direction;
};

class Scene
{
public:
	Scene(const char *file_path, i32 size, i32 max_bounces);
	void print() const;
	void render(const char *file_path);
	
private:
	Color castRay(Ray ray, f32 t_min, i32 depth);
	f32 getLightIntensityAt(f32 specular_term, Vector view_direciton, Vector point, Vector normal);

private:
	const Color m_background_color = {0.f, 0.f, 0.f, 1.f};
	i32 m_size;
	i32 m_max_bounces;
	
	std::vector<Sphere> m_spheres;
	std::vector<Light> m_lights;
};

#endif // RAYTRACER_HPP
