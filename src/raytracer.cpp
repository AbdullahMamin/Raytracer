#include "raytracer.hpp"

std::pair<f32, f32> Sphere::getRayIntersection(Ray ray)
{
	Vector c_to_p = ray.origin - position;
	f32 a = ray.direction.dot(ray.direction);
	f32 b = 2.f*c_to_p.dot(ray.direction);
	f32 c = c_to_p.dot(c_to_p) - radius*radius;

	f32 discriminant = b*b - 4*a*c;
	if (discriminant < 0.f)
	{
		return {INFINITY, INFINITY};
	}

	f32 root_discriminant = sqrtf(discriminant);
	return {(-b - root_discriminant)/(2.f*a), (-b + root_discriminant)/(2.f*a)};
}

Scene::Scene(i32 size, const char *file_path)
	: m_size(size)
{
	lua_State *L = luaL_newstate();
	if (!L)
	{
		std::cout << "Couldn't init lua state\n";
		exit(1);
	}
	if (luaL_dofile(L, file_path) != LUA_OK)
	{
		std::cout << "Couldn't open lua scene\n";
		exit(1);
	}
	
	i32 n_spheres = lua_rawlen(L, -1);
	
	// m_spheres.reserve(n_spheres);
	for (i32 i = 0; i < n_spheres; i++)
	{
		Sphere sphere;
		lua_pushinteger(L, i + 1);
		lua_gettable(L, -2);
			lua_getfield(L, -1, "position");
				lua_pushinteger(L, 1);
				lua_gettable(L, -2);
					sphere.position.x = lua_tonumber(L, -1);
				lua_pop(L, 1);
				
				lua_pushinteger(L, 2);
				lua_gettable(L, -2);
					sphere.position.y = lua_tonumber(L, -1);
				lua_pop(L, 1);
				
				lua_pushinteger(L, 3);
				lua_gettable(L, -2);
					sphere.position.z = lua_tonumber(L, -1);
				lua_pop(L, 1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "radius");
				sphere.radius = lua_tonumber(L, -1);
			lua_pop(L, 1);
			
			lua_getfield(L, -1, "color");
				lua_pushinteger(L, 1);
				lua_gettable(L, -2);
					sphere.color.r = lua_tonumber(L, -1);
				lua_pop(L, 1);
				
				lua_pushinteger(L, 2);
				lua_gettable(L, -2);
					sphere.color.g = lua_tonumber(L, -1);
				lua_pop(L, 1);
				
				lua_pushinteger(L, 3);
				lua_gettable(L, -2);
					sphere.color.b = lua_tonumber(L, -1);
				lua_pop(L, 1);
				
				lua_pushinteger(L, 4);
				lua_gettable(L, -2);
					sphere.color.a = lua_tonumber(L, -1);
				lua_pop(L, 1);
			lua_pop(L, 1);
		lua_pop(L, 1);
		
		m_spheres.push_back(sphere);
	}
	// print();

	lua_close(L);
}

void Scene::print() const
{
	for (auto sphere : m_spheres)
	{
		std::cout << "----------------------\n";
		std::cout << "\tposition = {" << sphere.position.x << ", " << sphere.position.y << ", " << sphere.position.z << "}\n";
		std::cout << "\tradius = " << sphere.radius << "\n";
		std::cout << "\tcolor = {" << sphere.color.r << ", " << sphere.color.g << ", " << sphere.color.b << ", " << sphere.color.a << "}\n";
	}
	std::cout << "----------------------\n";
}

void Scene::render(const char *file_path)
{
	std::ofstream out_file(file_path);

	out_file << "P3\n" << m_size << " " << m_size << "\n255\n";
	for (i32 y = 0; y < m_size; y++)
	{
		for (i32 x = 0; x < m_size; x++)
		{
			Color color = castRay(x, y);
			out_file << 255*color.r << " " << 255*color.g << " " << 255*color.b << " ";
		}
	}
}

Color Scene::castRay(i32 x, i32 y)
{
	Ray ray{{0.f, 0.f, 0.f}, {(f32)x/(f32)m_size - 0.5f, 0.5f - (f32)y/(f32)m_size, 1.f}};

	f32 t_best = INFINITY;
	Color color_best = m_background_color;
	for (auto sphere : m_spheres)
	{
		auto t = sphere.getRayIntersection(ray);
		if (t.first > 0.f && t.first < t_best)
		{
			t_best = t.first;
			color_best = sphere.color;
		}
	}
	
	return color_best;
}
