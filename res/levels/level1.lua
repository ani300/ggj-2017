rgb = true
time = true
colors = {
	positive_amp = {
		r = 255,
		g = 0,
		b = 0,
		a = 255
	},
	zero = {
		r = 255,
		g = 0,
		b = 0,
		a = 255
	},
	negative_amp = {
		r = 255,
		g = 0,
		b = 255,
		a = 255
	}
}
grid = {
	size = {60, 60}, -- by default it will be 60, 60, there is no need to declare it
	color = {
		r = 255,
		g = 0,
		b = 0,
		a = 255
	}
}
receivers = {
	{
		type = "AlwaysOn",
		position = {200, 300}
	},
	{
		type = "AlwaysOn",
		position = {800, 400}
	},
	{
		type = "Threshold",
		position = {1200, 600},
		threshold = 3,
		comparator = "<",
		absolute = false

	}
}
generators = {
	StandardGenerators = 2,
	OffsetGenerators = 1,
	WavelengthGenerators = 0,
	FrequencyGenerators = 0,
	EditableGenerators = 0
}
