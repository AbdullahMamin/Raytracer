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

Scene::Scene(const char *file_path, i32 size, i32 max_bounces)
	: m_size(size), m_max_bounces(max_bounces)
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

	// Read lights
	lua_getfield(L, -1, "lights");
		i32 n_lights = lua_rawlen(L, -1);
		for (i32 i = 0; i < n_lights; i++)
		{
			Light light;
			lua_pushinteger(L, i + 1);
			lua_gettable(L, -2);
				lua_getfield(L, -1, "type");
					std::string type = lua_tostring(L, -1);
					if (type == "ambient")
					{
						light.type = LT_AMBIENT;
					}
					else if (type == "directional")
					{
						light.type = LT_DIRECTIONAL;
					}
					else // type == "point"
					{
						light.type = LT_POINT;
					}
				lua_pop(L, 1);
				
				lua_getfield(L, -1, "intensity");
					light.intensity = lua_tonumber(L, -1);
				lua_pop(L, 1);

				if (light.type == LT_DIRECTIONAL)
				{
					lua_getfield(L, -1, "direction");
						lua_pushinteger(L, 1);
						lua_gettable(L, -2);
							light.direction.x = lua_tonumber(L, -1);
						lua_pop(L, 1);
						
						lua_pushinteger(L, 2);
						lua_gettable(L, -2);
							light.direction.y = lua_tonumber(L, -1);
						lua_pop(L, 1);
						
						lua_pushinteger(L, 3);
						lua_gettable(L, -2);
							light.direction.z = lua_tonumber(L, -1);
						lua_pop(L, 1);
					lua_pop(L, 1);
				}
				else if (light.type == LT_POINT)
				{
					lua_getfield(L, -1, "position");
						lua_pushinteger(L, 1);
						lua_gettable(L, -2);
							light.position.x = lua_tonumber(L, -1);
						lua_pop(L, 1);
						
						lua_pushinteger(L, 2);
						lua_gettable(L, -2);
							light.position.y = lua_tonumber(L, -1);
						lua_pop(L, 1);
						
						lua_pushinteger(L, 3);
						lua_gettable(L, -2);
							light.position.z = lua_tonumber(L, -1);
						lua_pop(L, 1);
					lua_pop(L, 1);
				}
			lua_pop(L, 1);
			
			m_lights.push_back(light);
		}
	lua_pop(L, 1);
	
	// Read spheres
	lua_getfield(L, -1, "spheres");
		i32 n_spheres = lua_rawlen(L, -1);
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

				lua_getfield(L, -1, "specular");
					sphere.specular = lua_tonumber(L, -1);
				lua_pop(L, 1);

				lua_getfield(L, -1, "reflective");
					sphere.reflective = lua_tonumber(L, -1);
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
	lua_pop(L, 1);
	
	lua_close(L);
}

void Scene::print() const
{
	std:: cout << "------SPHERES------\n";
	for (auto sphere : m_spheres)
	{
		std::cout << "\tposition = {" << sphere.position.x << ", " << sphere.position.y << ", " << sphere.position.z << "}\n";
		std::cout << "\tradius = " << sphere.radius << "\n";
		std::cout << "\tspecular = " << sphere.specular << "\n";
		std::cout << "\treflective = " << sphere.reflective << "\n";
		std::cout << "\tcolor = {" << sphere.color.r << ", " << sphere.color.g << ", " << sphere.color.b << ", " << sphere.color.a << "}\n";
		std::cout << "----------------------\n";
	}
	std:: cout << "------LIGHTS------\n";
	for (auto light : m_lights)
	{
		std::cout << "\ttype = ";
		if (light.type == LT_AMBIENT)
		{
			std::cout << "ambient\n";
		}
		else if (light.type == LT_POINT)
		{
			std::cout << "point\n";
		}
		else // light.type == LT_DIRECTIONAL
		{
			std::cout << "directional\n";
		}
		std::cout << "\tintensity = " << light.intensity << "\n";
		if (light.type == LT_POINT)
		{
			std::cout << "\tposition = {" << light.position.x << ", " << light.position.y << ", " << light.position.z << "}\n";
		}
		else if (light.type == LT_DIRECTIONAL)
		{
			std::cout << "\tdirection = {" << light.direction.x << ", " << light.direction.y << ", " << light.direction.z << "}\n";
		}
		std::cout << "----------------------\n";
	}
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
			out_file << (i32)(255*color.r) << " " << (i32)(255*color.g) << " " << (i32)(255*color.b) << " ";
		}
	}
}

Color Scene::castRay(i32 x, i32 y)
{
	Ray ray{{0.f, 0.f, 0.f}, {(f32)x/(f32)m_size - 0.5f, 0.5f - (f32)y/(f32)m_size, 1.f}};

	f32 t_best = INFINITY;
	Sphere sphere_best;
	for (auto sphere : m_spheres)
	{
		auto t = sphere.getRayIntersection(ray);
		if (t.first > 0.f && t.first < t_best)
		{
			t_best = t.first;
			sphere_best = sphere;
		}
	}

	if (t_best != INFINITY)
	{
		Vector position = ray.at(t_best);
		Vector normal = (position - sphere_best.position).normalize();

		return getLightIntensityAt(sphere_best.specular, -ray.direction, position, normal)*sphere_best.color;
	}

	return m_background_color;
}

f32 Scene::getLightIntensityAt(f32 specular_term, Vector view_direciton, Vector point, Vector normal)
{
	assert(fabs(normal.magnitude() - 1.f) < EPSILON); // make sure normal is unit length

	f32 total_intensity = 0.f;
	for (auto light : m_lights)
	{
		if (light.type == LT_AMBIENT)
		{
			total_intensity += light.intensity;
		}
		else if (light.type == LT_DIRECTIONAL)
		{
			// Check for spheres that may block this light
			bool in_shadow = false;
			Ray ray = {point, light.direction};
			for (auto sphere : m_spheres)
			{
				auto t = sphere.getRayIntersection(ray);
				if (t.first > 0.f && t.first < INFINITY)
				{
					in_shadow = true;
					break;
				}
			}

			if (!in_shadow)
			{
				f32 diffuse_scale = light.direction.normalize().dot(normal);
				f32 cos_alpha = view_direciton.normalize().dot(light.direction.reflect(normal).normalize());
				if (diffuse_scale > 0.f) // to not add lights coming from behind the surface
				{
					total_intensity += light.intensity*diffuse_scale;
				}
				if (cos_alpha > 0.f && specular_term > 0.f)
				{
					total_intensity += light.intensity*powf(cos_alpha, specular_term);
				}
			}
		}
		else // light.type == LT_POINT
		{
			// Check for spheres that may block this light
			bool in_shadow = false;
			Ray ray = {point, light.position - point};
			for (auto sphere : m_spheres)
			{
				auto t = sphere.getRayIntersection(ray);
				if (t.first > 0.f && t.first < 1.f) // Less than 1 since we don't want spheres further than the light to block the light
				{
					in_shadow = true;
					break;
				}
			}

			if (!in_shadow)
			{
				f32 diffuse_scale = (light.position - point).normalize().dot(normal);
				f32 cos_alpha = view_direciton.normalize().dot((light.position - point).reflect(normal).normalize());
				if (diffuse_scale > 0.f) // to not add lights coming from behind the surface
				{
					total_intensity += light.intensity*diffuse_scale;
				}
				if (cos_alpha > 0.f && specular_term > 0.f)
				{
					total_intensity += light.intensity*powf(cos_alpha, specular_term);
				}
			}
		}
	}

	return total_intensity;
}
