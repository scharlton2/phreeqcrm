%module phreeqcrm
// %include "std_string.i"
// %include "std_vector.i"

// // namespace std {
// //   // %template(vectori)             vector<int>;
// //   // %template(vectord)             vector<double>;
// //   // %template(vectors)             vector<string>;
// //   %template(IntVector)           vector<int>;
// //   %template(DoubleVector)        vector<double>;
// //   %template(BoolVector)          vector<bool>;
// //   %template(StringVector)        vector<string>;
// //   //%template(IPhreeqcPhastVector) vector<IPhreeqcPhast*>;
// //   %template(IntVectorVector)     vector< vector<int> >;
// // };

// %{
// #include ""
// // #include "../src/IPhreeqcPhast/IPhreeqc/phreeqcpp/Solution.h"
// // #include "../src/IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
// #include "../src/IPhreeqcPhast/IPhreeqc/Var.h"
// // //#include "../src/IPhreeqcPhast/IPhreeqc/BasicCallback.h"
// //#include "../src/IPhreeqcPhast/IPhreeqcPhast.h"
// #include "../src/IrmResult.h"
// #include "../src/PhreeqcRM.h"
// %}

// /* ignore */
// %ignore SetBasicFortranCallback;

// %ignore PhreeqcRM::GetSelectedOutputHeading(int icol, std::string& heading);  // no passing by ref???

// %ignore PhreeqcRM::ReturnHandler(IRM_RESULT result, const std::string & e_string);

// namespace std {
//   // %template(vectori)             vector<int>;
//   // %template(vectord)             vector<double>;
//   // %template(vectors)             vector<string>;
//   %template(IntVector)           vector<int>;
//   %template(DoubleVector)        vector<double>;
//   %template(BoolVector)          vector<bool>;
//   %template(StringVector)        vector<string>;
//   //%template(IPhreeqcPhastVector) vector<IPhreeqcPhast*>;
//   %template(IntVectorVector)     vector< vector<int> >;
// };

// ///%include "std_string.i"

// ///%ignore cxxSolution;

// // %include "../src/IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
// %include "../src/IPhreeqcPhast/IPhreeqc/Var.h"
// //%include "../src/IPhreeqcPhast/IPhreeqc/BasicCallback.h"
// //%include "../src/IPhreeqcPhast/IPhreeqcPhast.h"
// %include "../src/IrmResult.h"
// %include "../src/PhreeqcRM.h"



%{
#include "../src/IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
#include "../src/IPhreeqcPhast/IPhreeqc/Var.h"
///#include "../src/IPhreeqcPhast/IPhreeqc/BasicCallback.h"
#include "../src/IPhreeqcPhast/IPhreeqcPhast.h"
#include "IrmResult.h"
#include "PhreeqcRM.h"
%}

%feature("director") BasicCallback;

%include "stl.i"
%include "std_except.i"
%include "std_string.i"

/* ignore */
///%ignore SetBasicFortranCallback;

/* instantiate the required template specializations */
namespace std {
    %template(IntVector)           vector<int>;
    %template(DoubleVector)        vector<double>;
    %template(BoolVector)          vector<bool>;
    %template(StringVector)        vector<string>;
    %template(IPhreeqcPhastVector) vector<IPhreeqcPhast*>;
    %template(IntVectorVector)     vector< vector<int> >;
}

%include "std_string.i"

//{{
%include "../src/IPhreeqcPhast/IPhreeqc/phreeqcpp/common/PHRQ_exports.h"
//}}

%include "../src/IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
%include "../src/IPhreeqcPhast/IPhreeqc/Var.h"
///%include "../src/IPhreeqcPhast/IPhreeqc/BasicCallback.h"
%include "../src/IPhreeqcPhast/IPhreeqcPhast.h"
%include "../src/IrmResult.h"
%include "../src/PhreeqcRM.h"
