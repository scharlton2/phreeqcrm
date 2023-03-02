#ifdef SWIGJAVA
%module(directors="1") phreeqcrm_java
#elif SWIGRUBY
%module(directors="1") phreeqcrm_ruby
#else
%module(directors="1") phreeqcrm
#endif

%{
//{{
#include "PHRQ_exports.h"
//#include "IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
//#include "IPhreeqcPhast/IPhreeqc/Var.h"
//#include "IPhreeqcPhast/IPhreeqc/BasicCallback.h"
#include "IPhreeqc.hpp"
#include "Var.h"
#include "BasicCallback.h"
//}}
/////#include "IPhreeqcPhast/IPhreeqcPhast.h"
///////#include "IPhreeqcPhast/IPhreeqcPhast.h"
#include "IPhreeqcPhast.h"

#include "IrmResult.h"
#include "PhreeqcRM.h"
%}

///%feature("director") BasicCallback;

%include "stl.i"
%include "std_except.i"
%include "std_string.i"

/* ignore */
//%ignore SetBasicFortranCallback;
//%ignore ::SetBasicFortranCallbackF;
%ignore SetBasicFortranCallbackF;
%ignore IPhreeqc::SetBasicFortranCallback;

%ignore IPhreeqc::error_msg;
%ignore IPhreeqc::fpunchf_end_row;
%ignore IPhreeqc::fpunchf;
%ignore IPhreeqc::log_msg;
%ignore IPhreeqc::output_msg;
%ignore IPhreeqc::output_open;
%ignore IPhreeqc::punch_msg;
%ignore IPhreeqc::punch_open;
%ignore IPhreeqc::screen_msg;
%ignore IPhreeqc::warning_msg;


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
%include "PHRQ_exports.h"
// %include "IPhreeqcPhast/IPhreeqc/IPhreeqc.hpp"
// %include "IPhreeqcPhast/IPhreeqc/Var.h"
// %include "IPhreeqcPhast/IPhreeqc/BasicCallback.h"
// %include "IPhreeqcPhast/IPhreeqc/Var.h"
// %include "IPhreeqcPhast/IPhreeqc/BasicCallback.h"
%include "IPhreeqc.hpp"
%include "Var.h"
%include "BasicCallback.h"
%include "Var.h"
%include "BasicCallback.h"
//}}    
// Adding (%include "IPhreeqcPhast.h") forces inclusion of the
// following classes cxxSolution, cxxExchange, cxxGasPhase,
// cxxKinetics, cxxPPassemblage, cxxSSassemblage, cxxSurface
// cxxMix, cxxReaction, cxxTemperature, cxxPressure
%include "IrmResult.h"
%include "PhreeqcRM.h"
