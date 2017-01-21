rgb = true
time = true
colors = {
	positive_amp = {
		r = 0,
		g = 0,
		b = 255,
		a = 255
	},
	zero = {
		r = 0,
		g = 0,
		b = 0,
		a = 255
	},
	negative_amp = {
		r = 255,
		g = 0,
		b = 0,
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
		type = "AlwaysOff",
		position = {500, 500}
	},
	{
		type = "Threshold",
		position = {1000, 1000},
		threshold_fn = function(amplitude) return amplitude > 2 or amplitude < -1 end	
	}
}
generators = {
	StandardGenerators = 5,
	OffsetGenerators = 0,
	WavelengthGenerators = 0,
	FrequencyGenerators = 0,
	EditableGenerators = 0
}
