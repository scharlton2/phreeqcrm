import phreeqcrm as rm
import numpy as np

def test_main():
    bmi = rm.bmi_phreeqcrm()
    bmi.initialize("AdvectBMI_py.yaml")

    input_vars = bmi.get_input_var_names()
    assert(isinstance(input_vars, tuple))
    assert(isinstance(input_vars[0], str))

    output_vars = bmi.get_output_var_names()
    assert(isinstance(output_vars, tuple))
    assert(isinstance(output_vars[0], str))

    components = bmi.get_components()
    assert(len(components) == 8)

    temperature = bmi.get_value("Temperature")
    assert(len(temperature) == 40)

    sat = bmi.get_value("Saturation")
    assert(len(sat) == 40)

    por = bmi.get_value("Porosity")
    assert(len(por) == 40)

    volume = bmi.get_value("SolutionVolume")
    assert(len(volume) == 40)

    c = bmi.get_value("Concentrations")
    assert(len(c) == 40*len(components))

    nxyz = bmi.get_grid_size(0)
    assert(nxyz == 40)

    density_list = [1.0] * nxyz
    bmi.set_value("Density", density_list)

    density_tuple = tuple([1.0] * nxyz)
    bmi.set_value("Density", density_tuple)

    density_ndarray = np.full((nxyz,), 1.0)
    bmi.set_value("Density", density_ndarray)

