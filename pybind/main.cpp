#include <vector>
#include <iostream>

#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/numpy.h>
// #include <chrono>
// #include <thread>

#include "BMIPhreeqcRM.h"

#define STRINGIFY(x) #x
#define MACRO_STRINGIFY(x) STRINGIFY(x)

namespace py = pybind11;

// PYBIND11_MODULE(phreeqcrm, m) {
//   m.doc() = "I'm a docstring hehe";
//   m.def("some_fn_python_name", &some_fn);
//   py::class_<BMIPhreeqcRM>(
// 			m, "bmi_phreeqcrm"
// 			)
//       .def(py::init())
//       .def("initialize", &BMIPhreeqcRM::Initialize)
//       ;
// }

int add(int x, int y=0) {
    return x + y;
}

const std::string bmi_initialize_docstring = 
R"pbdoc(A YAML file can be used to initialize an instance of bmi_phreeqcrm.

Parameters
----------
filename : str, optional
    Path to name of input file.
)pbdoc";


const std::string bmi_set_value_docstring = 
R"pbdoc("Use the vector of concentrations (c) to set the moles of components in each 
reaction cell. The volume of water in a cell is the product of porosity 
(:meth:`SetPorosity`), saturation (:meth:`SetSaturation`), and reference volume 
(:meth:`SetRepresentativeVolume`). The moles of each component are determined 
by the volume of water and per liter concentrations. If concentration units 
(:meth:`SetUnitsSolution`) are mass fraction, the density (as specified by 
:meth:`SetDensity`) is used to convert from mass fraction to per mass per liter.

:param c: a list or numpy array of doubles.

Args:
	c (double list, numpy.ndarray, or tuple): Component concentrations. Size of 
		vector is ncomps times nxyz, where ncomps is the number of components as 
		determined by :meth:`FindComponents` or :meth:`GetComponentCount` and nxyz 
		is the number of grid cells in the user model (:meth:`GetGridCellCount`).
)pbdoc";



PYBIND11_MODULE(phreeqcrm, m) {

    m.def("add", &add, "A function that adds two integers.", py::arg("x"), py::arg("y")=0);

    m.doc() = R"pbdoc(
        PhreeqcRM plugin
        -----------------------

        .. currentmodule:: phreeqcrm

        .. autosummary::
           :toctree: _generate

    )pbdoc";

    py::class_<BMIPhreeqcRM>(
			m, "bmi_phreeqcrm"
    )
    .def(py::init())

    // Model control functions.
    // .def("initialize", &BMIPhreeqcRM::Initialize, R"pbdoc(
    //     A YAML file can be used to initialize an instance of bmi_phreeqcrm.

    //     Parameters
    //     ----------
	//     filename : str, optional
    //         Path to name of input file.
    // )pbdoc", py::arg("filename"))

    // .def("initialize2", [](BMIPhreeqcRM &self, py::str filename) {
    //     if (filename.is_none()) {
    //         return self.Initialize("");
    //     }
    //     return self.Initialize(std::string(py::str(filename)));
    // }, bmi_initialize_docstring2.c_str(), py::arg("filename") = py::none())

    .def("initialize", [](BMIPhreeqcRM &self, py::str filename) {
        if (filename.is_none()) {
            return self.Initialize("");
        }
        return self.Initialize(std::string(py::str(filename)));
    }, bmi_initialize_docstring.c_str(), py::arg("filename") = py::none())



    // Model information functions.
    .def("get_component_name", &BMIPhreeqcRM::GetComponentName)

    // .def("get_input_var_names", &BMIPhreeqcRM::GetInputVarNames)
    .def("get_input_var_names", [](BMIPhreeqcRM &self) {
        auto output = self.GetInputVarNames();
        py::tuple out = py::cast(output);
        return out;
    })

    .def("get_output_var_names", [](BMIPhreeqcRM &self) {
        auto output = self.GetOutputVarNames();
        py::tuple out = py::cast(output);
        return out;
    })



    // Variable getters
    //   virtual void GetValue(std::string name, void *dest) = 0;
    .def("get_value", [](BMIPhreeqcRM &self, const std::string &input) {
        std::vector<double> output;
        self.GetValue(input, output);
        py::array out = py::cast(output);
        return out;
    })
    //   virtual void *GetValuePtr(std::string name) = 0;
    //   virtual void GetValueAtIndices(std::string name, void *dest, int *inds, int count) = 0;



    // Variable setters
    //   virtual void SetValue(std::string name, void *src) = 0;
    //.def("set_value", py::overload_cast<std::string, std::vector<double>>(&BMIPhreeqcRM::SetValue), py::arg("name", std::string()), py::arg("src", std::vector<double>()))
    // .def("set_value", py::overload_cast<std::string, std::vector<double>>(&BMIPhreeqcRM::SetValue), py::arg("name"), py::arg("src").noconvert(), py::keep_alive<1, 2>(),
    //     bmi_set_value_docstring.c_str()
    // )


    .def("set_value", [](BMIPhreeqcRM &self, std::string name, const py::array_t<double>& src) {
        // Extract the buffer information from the numpy array.
        py::buffer_info info = src.request();

        // Construct a std::vector<double> from the buffer data.
        double* ptr = static_cast<double*>(info.ptr);
        size_t size = info.shape[0];
        std::vector<double> src_vec(ptr, ptr + size);

        self.SetValue(name, src_vec);
    },
        py::arg("name"),
        //py::arg("src").noconvert(),       // this will fail if a List is used
        py::arg("src"),
        bmi_set_value_docstring.c_str()
    )


    .def("set_value", [](BMIPhreeqcRM &self, std::string name, const py::array_t<int>& src) {
        // Extract the buffer information from the numpy array.
        py::buffer_info info = src.request();

        // Construct a std::vector<double> from the buffer data.
        int* ptr = static_cast<int*>(info.ptr);
        size_t size = info.shape[0];
        std::vector<int> src_vec(ptr, ptr + size);

        self.SetValue(name, src_vec);
    },
        py::arg("name"),
        //py::arg("src").noconvert(),       // this will fail if a List is used
        py::arg("src"),
        bmi_set_value_docstring.c_str()
    )




    // .def("set_value", [](BMIPhreeqcRM &self, const std::string &input, std::vector<double> values) {
    //     self.GetValue(input, output);
    //     py::array out = py::cast(output);
    //     return out;
    // })


    //   virtual void SetValueAtIndices(std::string name, int *inds, int count, void *src) = 0;    


    // Grid information functions    
    .def("get_grid_size", &BMIPhreeqcRM::GetGridSize)
    //   virtual int GetGridRank(const int grid) = 0;
    //   virtual int GetGridSize(const int grid) = 0;
    //   virtual std::string GetGridType(const int grid) = 0;

    //   virtual void GetGridShape(const int grid, int *shape) = 0;
    //   virtual void GetGridSpacing(const int grid, double *spacing) = 0;
    //   virtual void GetGridOrigin(const int grid, double *origin) = 0;

    //   virtual void GetGridX(const int grid, double *x) = 0;
    //   virtual void GetGridY(const int grid, double *y) = 0;
    //   virtual void GetGridZ(const int grid, double *z) = 0;

    //   virtual int GetGridNodeCount(const int grid) = 0;
    //   virtual int GetGridEdgeCount(const int grid) = 0;
    //   virtual int GetGridFaceCount(const int grid) = 0;

    //   virtual void GetGridEdgeNodes(const int grid, int *edge_nodes) = 0;
    //   virtual void GetGridFaceEdges(const int grid, int *face_edges) = 0;
    //   virtual void GetGridFaceNodes(const int grid, int *face_nodes) = 0;
    //   virtual void GetGridNodesPerFace(const int grid, int *nodes_per_face) = 0;


    // Extras
    .def("get_components", &BMIPhreeqcRM::GetComponents)

    ;



#ifdef VERSION_INFO
    m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
#else
    m.attr("__version__") = "dev";
#endif
}



// #include <pybind11/pybind11.h>

// #define STRINGIFY(x) #x
// #define MACRO_STRINGIFY(x) STRINGIFY(x)

// int add(int i, int j) {
//     return i + j;
// }

// namespace py = pybind11;

// PYBIND11_MODULE(cmake_example, m) {
//     m.doc() = R"pbdoc(
//         Pybind11 example plugin
//         -----------------------

//         .. currentmodule:: cmake_example

//         .. autosummary::
//            :toctree: _generate

//            add
//            subtract
//     )pbdoc";

//     m.def("add", &add, R"pbdoc(
//         Add two numbers

//         Some other explanation about the add function.
//     )pbdoc");

//     m.def("subtract", [](int i, int j) { return i - j; }, R"pbdoc(
//         Subtract two numbers

//         Some other explanation about the subtract function.
//     )pbdoc");

// #ifdef VERSION_INFO
//     m.attr("__version__") = MACRO_STRINGIFY(VERSION_INFO);
// #else
//     m.attr("__version__") = "dev";
// #endif
// }
