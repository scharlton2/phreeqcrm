import os
import phreeqcrm as rm
import numpy as np

def test_main():
    print(f"PYTHONPATH={os.getenv('PYTHONPATH')}")

    bmi = rm.bmi_phreeqcrm()
    bmi.initialize("AdvectBMI_py.yaml")

    nxyz = bmi.get_grid_size(0)
    assert(nxyz == 40)

    input_vars = bmi.get_input_var_names()
    assert(isinstance(input_vars, tuple))
    assert(isinstance(input_vars[0], str))

    output_vars = bmi.get_output_var_names()
    assert(isinstance(output_vars, tuple))
    assert(isinstance(output_vars[0], str))

    components = bmi.get_components()
    assert(len(components) == 8)

    temperature = bmi.get_value("Temperature")
    assert(len(temperature) == nxyz)

    sat = bmi.get_value("Saturation")
    assert(len(sat) == nxyz)

    por = bmi.get_value("Porosity")
    assert(len(por) == nxyz)

    volume = bmi.get_value("SolutionVolume")
    assert(len(volume) == nxyz)

    c = bmi.get_value("Concentrations")
    assert(len(c) == 40*len(components))

    density_list = [1.0] * nxyz
    bmi.set_value("Density", density_list)

    density_tuple = tuple([1.0] * nxyz)
    bmi.set_value("Density", density_tuple)

    density_ndarray = np.full((nxyz,), 1.0)
    bmi.set_value("Density", density_ndarray)
