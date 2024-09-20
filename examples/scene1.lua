return {
	spheres = {
		{
			position = {0, -1, 3},
			radius = 1,
			color = {1.0, 0.0, 0.0, 1.0},
			specular = 500,
			reflective = 0.2
		},
		{
			position = {2, 0, 4},
			radius = 1,
			color = {0.0, 0.0, 1.0, 1.0},
			specular = 500,
			reflective = 0.3
		},
		{
			position = {-2, 0, 4},
			radius = 1,
			color = {0.0, 1.0, 0.0, 1.0},
			specular = 10,
			reflective = 0.4
		},
		{
			position = {0, -5001, 0},
			radius = 5000,
			color = {1.0, 1.0, 0.0, 1.0},
			specular = 1000,
			reflective = 0.5
		}
	},
	lights = {
		{
			type = "ambient",
			intensity = 0.2
		},
		{
			type = "point",
			intensity = 0.6,
			position = {2, 1, 0}
		},
		{
			type = "directional",
			intensity = 0.2,
			direction = {1, 4, 4}
		}
	}
}
