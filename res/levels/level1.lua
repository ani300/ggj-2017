level1 = {
	rgb = false,
	time = true,
	recivers = {
		{
			type = "AlwaysOn",
			position = {200, 300}
		},
		{
			type = "Threshold",
			position = {1200, 600},
			threshold = 3,
			comparator = "<",
			absolute = false

		}
	},
	generators = {
		StandardGenerators = 3,
		OffsetGenerators = 1,
		WavelengthGenerators = 0,
		FrequencyGenerators = 0,
		EditableGenerators = 0
	}
}
