return {
	spheres = {
		{
			position = {0, -1, 3},
			radius = 1,
			color = {1.0, 0.0, 0.0, 1.0}
		},
		{
			position = {2, 0, 4},
			radius = 1,
			color = {0.0, 0.0, 1.0, 1.0}
		},
		{
			position = {-2, 0, 4},
			radius = 1,
			color = {0.0, 1.0, 0.0, 1.0}
		}
	},
	lights = {
		{
			type = "ambient",
			intensity = 1.0
		},
		{
			type = "directional",
			direction = {1.0, 0.0, -1.0}
		},
		{
			type = "point",
			position = {0.0, 0.0, 100.0}
		}
	}
}
