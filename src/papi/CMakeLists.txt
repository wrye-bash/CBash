if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting tests build type to MinSizeRel as none was specified")
  set(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()


SET(CINT_SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR})

file(GLOB CINT_SOURCES "*.cpp")
file(GLOB CINT_HEADERS "*.h")

file(GLOB CINT_PYTEST_FILES "${CBASH_TESTS}/test_*.py")

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

# Make sure pytest is found or produce a fatal error
if(NOT PYBIND11_PYTEST_FOUND)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -m pytest --version --noconftest OUTPUT_QUIET ERROR_QUIET
                  RESULT_VARIABLE PYBIND11_EXEC_PYTHON_ERR)
  if(PYBIND11_EXEC_PYTHON_ERR)
    message(FATAL_ERROR "Running the tests requires pytest.  Please install it manually (try: ${PYTHON_EXECUTABLE} -m pip install pytest)")
  endif()
  set(PYBIND11_PYTEST_FOUND TRUE CACHE INTERNAL "")
endif()

# A single command to compile and run the tests
add_custom_target(pytest COMMAND ${PYTHON_EXECUTABLE} -m pytest -rws ${CINT_PYTEST_FILES}
                  DEPENDS cint WORKING_DIRECTORY ${CBASH_TESTS})
