rgb = true
time = true
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
