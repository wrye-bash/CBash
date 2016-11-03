# Settings passed on the command line:
#
# CBash_BUILD_SHARED_LIBS
# CBash_USE_STATIC_RUNTIME
# CBash_NO_BOOST_ZLIB

##############################
# General Settings
##############################

cmake_minimum_required (VERSION 3.0)
project (CBash)

include(CMakeToolsHelpers OPTIONAL)

add_subdirectory (deps/pybind11)
LIST(APPEND CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/deps/cotire/CMake")
include(cotire)

set_property(DIRECTORY . PROPERTY COTIRE_ADD_UNITY_BUILD FALSE)

option(CBash_BUILD_SHARED_LIBS "Build a shared library" ON)
option(CBash_USE_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)
option(CBash_NO_BOOST_ZLIB "Build with external Zlib" ON)

set (BUILD_SHARED_LIBS ${CBash_BUILD_SHARED_LIBS})
set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_NO_BOOST_CMAKE ON)
set (Boost_USE_STATIC_RUNTIME ${CBash_USE_STATIC_RUNTIME})

set(CBASH_RELEASE ${CMAKE_SOURCE_DIR}/release)
set(CBASH_TESTS ${CMAKE_SOURCE_DIR}/tests)
set(CBASH_SOURCE ${CMAKE_SOURCE_DIR}/src)
set(CBASH_INCLUDE ${CMAKE_SOURCE_DIR}/include/cbash)


IF (CBash_NO_BOOST_ZLIB)
    add_definitions(-DCBash_NO_BOOST_ZLIB)
    find_package(Boost REQUIRED COMPONENTS iostreams)
    find_package(ZLIB REQUIRED)
    set (CBASH_LIBS ${ZLIB_LIBRARY})
ELSE ()
    find_package(Boost REQUIRED COMPONENTS iostreams zlib)
    find_package(ZLIB)
    set (CBASH_LIBS "")
ENDIF ()

# Include source and library directories.
include_directories (   
        ${CBASH_INCLUDE}
        ${Boost_INCLUDE_DIRS}
        ${ZLIB_INCLUDE_DIR}
        ${CBASH_SOURCE}
        ${CBASH_SOURCE}/game
)


##############################
# System-Specific Settings
##############################

# Settings when compiling for Windows. Since it's a Windows-only app this is always true, but useful to check for copy/paste into other projects.
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions (-DUNICODE -D_UNICODE -DNDEBUG -DWIN32 -D_WINDOWS)
    IF (CBash_BUILD_SHARED_LIBS)
        add_definitions (-DCBASH_DLL)
    ELSE ()
        add_definitions (-DCBASH_STATIC)
    ENDIF ()
ENDIF ()

IF (MSVC)
    IF (MSVC_VERSION EQUAL 1800)
        set (CMAKE_GENERATOR_TOOLSET "v120_xp" CACHE STRING "Platform Toolset" FORCE)
    ELSEIF (MSVC_VERSION EQUAL 1700)
        set (CMAKE_GENERATOR_TOOLSET "v110_xp" CACHE STRING "Platform Toolset" FORCE)
    ENDIF ()

    # Force static C++ runtime linkage.
    IF (CBash_USE_STATIC_RUNTIME)
        FOREACH(flag
            CMAKE_C_FLAGS_RELEASE CMAKE_C_FLAGS_RELWITHDEBINFO
            CMAKE_C_FLAGS_DEBUG CMAKE_C_FLAGS_DEBUG_INIT
            CMAKE_CXX_FLAGS_RELEASE  CMAKE_CXX_FLAGS_RELWITHDEBINFO
            CMAKE_CXX_FLAGS_DEBUG  CMAKE_CXX_FLAGS_DEBUG_INIT)
            STRING(REPLACE "/MD"  "/MT" "${flag}" "${${flag}}")
            SET("${flag}" "${${flag}} /EHsc")
        ENDFOREACH()
    ENDIF ()

    set (CMAKE_EXE_LINKER_FLAGS "/SUBSYSTEM:WINDOWS")
ENDIF ()


add_subdirectory(src/common)
add_subdirectory(src/game)
add_subdirectory(src/main)
add_subdirectory(src/capi)
add_subdirectory (pyd)

