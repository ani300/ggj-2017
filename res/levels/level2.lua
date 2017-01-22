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
		r = 0,
		g = 255,
		b = 0,
		a = 255
	},
	negative_amp = {
		r = 0,
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
		a = 0
	}
}
receivers = {
	{
		type = "RGB",
		color = {
			r = 255,
			g = 255,
			b = 0,
			a = 255
		},
		position = {500, 500}
	},
}
generators = {
	StandardGenerators = 0,
	OffsetGenerators = 0,
	WavelengthGenerators = 0,
	FrequencyGenerators = 0,
	EditableGenerators = 0,
	ColorGenerators = 3
}
generator_colors = {
	"Red",
	"Blue",
	"Green"
}
