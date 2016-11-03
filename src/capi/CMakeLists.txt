# Settings passed on the command line:
#
# CBash_BUILD_SHARED_LIBS
# CBash_USE_STATIC_RUNTIME
# CBash_NO_BOOST_ZLIB

##############################
# General Settings
##############################


file (GLOB_RECURSE CBASH_HEADERS "${CBASH_INCLUDE}/*.h" )

list(APPEND CBASH_HEADERS
    "Version.h"
    "resource.h"
)

set (CBASH_SOURCES  
        "CBash.cpp"
        "CBash.rc"
    )


# Include source and library directories.
include_directories (${CBASH_INCLUDE} ${CBASH_SOURCE} ${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR})

##############################
# Actual Building
##############################

# Build CBash.
add_library           (CBash ${CBASH_SOURCES} ${CBASH_HEADERS} ${CBASH_GEN_HDRS})
target_link_libraries (CBash ${Boost_LIBRARIES} ${CBASH_LIBS} libcommon libgame libmain)


# Always write the output file directly into the 'tests' directory (even on MSVC)
if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
  set_target_properties(CBash PROPERTIES LIBRARY_OUTPUT_DIRECTORY ${CBASH_RELEASE})
  set_target_properties(CBash PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CBASH_RELEASE})
  foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} config)
    set_target_properties(CBash PROPERTIES LIBRARY_OUTPUT_DIRECTORY_${config} ${CBASH_RELEASE})
    set_target_properties(CBash PROPERTIES RUNTIME_OUTPUT_DIRECTORY_${config} ${CBASH_RELEASE})
  endforeach()
endif()

cotire(CBash)

