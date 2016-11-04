

file(GLOB CINT_SOURCES "*.cpp")
file(GLOB CINT_HEADERS "*.h")

# Create the binding library
pybind11_add_module(cint ${CINT_SOURCES} ${CINT_HEADERS} ${PYBIND11_HEADERS})

pybind11_enable_warnings(cint)


#set_property(TARGET CBash PROPERTY IMPORTED_LOCATION "/home/sources/lib/libfoo1.so")
target_link_libraries (cint PRIVATE libmain libgame libcommon)

# Always write the output file directly into the 'tests' directory (even on MSVC)
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set_target_properties(cint PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CBASH_RELEASE})
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    set_target_properties(cint PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${config} ${CBASH_RELEASE})
  endforeach()
endif()

