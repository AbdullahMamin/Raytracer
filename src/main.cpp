#include "raytracer.hpp"

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		std::cout << "Usage: raytracer scene.lua out.bmp size max_bounces\n";
		return 1;
	}

	Scene scene(atoi(argv[3]), argv[1]);
	scene.print();
	scene.render(argv[2]);

	return 0;
}
