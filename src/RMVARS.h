#if !defined(RMVARS_H)
#define RMVARS_H
enum class RMVARS {
	ComponentCount,
	Components,
	Concentrations,
	Density,
	ErrorString,
	FilePrefix,
	Gfw,
	GridCellCount,
	InputVarNames,
	NthSelectedOutput,
	OutputVarNames,
	Saturation,
	SelectedOutput,
	SelectedOutputColumnCount,
	SelectedOutputCount,
	SelectedOutputHeadings,
	SelectedOutputRowCount,
	SolutionVolume,
	Time,
	TimeStep,
	CurrentSelectedOutputUserNumber,
	Porosity,
	Pressure,
	SelectedOutputOn,
	Temperature,
	Viscosity,
#if defined(WITH_PYBIND11)
	UseSolutionDensityVolume,
#endif
	NotFound
};
#endif
