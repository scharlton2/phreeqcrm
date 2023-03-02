cmake_minimum_required(VERSION 3.14) # SWIG_MODULE_NAME

# SWIG: use SWIG_MODULE_NAME property.
# for more run 'cmake --help-policy CMP0086'
if(POLICY CMP0086)
  cmake_policy(SET CMP0086 NEW)
endif()

project(phreeqcrm-bmi)

find_package(SWIG REQUIRED)

find_package(Python REQUIRED COMPONENTS Interpreter Development)

# this defines swig_add_library and was set by FindSWIG aka find_package(SWIG ...)
# see https://cmake.org/cmake/help/latest/module/FindSWIG.html
# and https://cmake.org/cmake/help/latest/module/UseSWIG.html
include(${SWIG_USE_FILE})

# phreeqc.dat
configure_file(phreeqc.dat phreeqc.dat COPYONLY)

# units.pqi
configure_file(units.pqi units.pqi COPYONLY)

# advection_cpp.py
configure_file(advection_cpp.py advection_cpp.py COPYONLY)

# phreeqcrm-bmi.i
set_property(SOURCE phreeqcrm-bmi.i PROPERTY SWIG_MODULE_NAME phreeqcrm)
set_property(SOURCE phreeqcrm-bmi.i PROPERTY CPLUSPLUS ON)
set_property(SOURCE phreeqcrm-bmi.i PROPERTY SWIG_FLAGS "-includeall")
set_property(SOURCE phreeqcrm-bmi.i PROPERTY SWIG_FLAGS "-Wall")
swig_add_library(phreeqcrm LANGUAGE python SOURCES phreeqcrm-bmi.i ${PhreeqcRM_SOURCES})
## swig_add_library(phreeqcrm LANGUAGE python SOURCES phreeqcrm-bmi.i ${PhreeqcRM_SOURCES})
###set_property(TARGET phreeqcrm PROPERTY SWIG_COMPILE_DEFINITIONS NO_NAMELESS_UNION IPQ_DLL_EXPORT)
set_property(TARGET phreeqcrm PROPERTY SWIG_COMPILE_DEFINITIONS NO_NAMELESS_UNION)

# target_include_directories(phreeqcrm
#   PUBLIC
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src>
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast>
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc>
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp>
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp/common>
#   $<BUILD_INTERFACE:${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp/PhreeqcKeywords>
#   # $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
# )

set(PhreeqcRM_SOURCE_DIR "/home/charlton/source/repos/coupled/phreeqcrm/")

set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src)
set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast)
set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc)
set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp)
set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp/common)
set_property(TARGET phreeqcrm PROPERTY SWIG_INCLUDE_DIRECTORIES ${PhreeqcRM_SOURCE_DIR}/src/IPhreeqcPhast/IPhreeqc/phreeqcpp/PhreeqcKeywords)


# target_compile_definitions(phreeqcrm
#   PRIVATE
#     NO_NAMELESS_UNION
# )


target_link_libraries(phreeqcrm
  PRIVATE
    Python::Python
    ###PhreeqcRM::PhreeqcRM
)

if (MSVC AND BUILD_SHARED_LIBS)
  # copy dll
  add_custom_command(TARGET phreeqcrm POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_FILE:PhreeqcRM::PhreeqcRM> $<TARGET_FILE_DIR:phreeqcrm>
  )
  # @TODO Update for python install
  if (PHREEQCRM_USE_ZLIB)
    add_custom_command(TARGET phreeqcrm POST_BUILD
      COMMAND ${CMAKE_COMMAND} -E echo "When running tests you may need to copy the zlib.dll to the directory: $<TARGET_FILE_DIR:phreeqcrm>"
    )
  endif()
endif()
