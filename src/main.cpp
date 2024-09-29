#include "raytracer.hpp"

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		std::cout << "Usage: raytracer scene.lua out.ppm size max_bounces\n";
		return 1;
	}

	Scene scene(argv[1], atoi(argv[3]), atoi(argv[4]));
	scene.print();
	scene.render(argv[2]);

	return 0;
}
