if(NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
  message(STATUS "Setting tests build type to MinSizeRel as none was specified")
  set(CMAKE_BUILD_TYPE MinSizeRel CACHE STRING "Choose the type of build." FORCE)
  set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug" "Release"
    "MinSizeRel" "RelWithDebInfo")
endif()


set (CINT_PYTEST_FILES
    test1.py
    #test2.py
  )


# Make sure pytest is found or produce a fatal error
if(NOT PYBIND11_PYTEST_FOUND)
  execute_process(COMMAND ${PYTHON_EXECUTABLE} -m pytest --version --noconftest OUTPUT_QUIET ERROR_QUIET
                  RESULT_VARIABLE PYBIND11_EXEC_PYTHON_ERR)
  if(PYBIND11_EXEC_PYTHON_ERR)
    message(FATAL_ERROR "Running the tests requires pytest.  Please install it manually (try: ${PYTHON_EXECUTABLE} -m pip install pytest)")
  endif()
  set(PYBIND11_PYTEST_FOUND TRUE CACHE INTERNAL "")
endif()

add_custom_target(pytest COMMAND ${CMAKE_COMMAND} -E env "PYTHONPATH=${CBASH_RELEASE}" ${PYTHON_EXECUTABLE} -m pytest -rws ${CINT_PYTEST_FILES} 
            DEPENDS cint WORKING_DIRECTORY ${CMAKE_CURRENT_LIST_DIR})

