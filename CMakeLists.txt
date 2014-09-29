# Settings passed on the command line:
#
# BUILD_SHARED_LIBS
# PROJECT_STATIC_RUNTIME
# CBASH_NO_BOOST_ZLIB

##############################
# General Settings
##############################

cmake_minimum_required (VERSION 3.0)
project (CBash)

option(BUILD_SHARED_LIBS "Build a shared library" ON)
option(PROJECT_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)
option(CBASH_NO_BOOST_ZLIB "Build with external Zlib" OFF)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_USE_STATIC_RUNTIME PROJECT_STATIC_RUNTIME)

file (GLOB_RECURSE CBASH_GEN_HDRS "${CMAKE_SOURCE_DIR}/src/*.h" )

set (CBASH_SRC  "${CMAKE_SOURCE_DIR}/src/CBash.cpp"
                "${CMAKE_SOURCE_DIR}/src/Collection.cpp"
                "${CMAKE_SOURCE_DIR}/src/Common.cpp"
                "${CMAKE_SOURCE_DIR}/src/GenericChunks.cpp"
                "${CMAKE_SOURCE_DIR}/src/GenericRecord.cpp"
                "${CMAKE_SOURCE_DIR}/src/ModFile.cpp"
                "${CMAKE_SOURCE_DIR}/src/TES4Record.cpp"
                "${CMAKE_SOURCE_DIR}/src/TES4RecordAPI.cpp"
                "${CMAKE_SOURCE_DIR}/src/Visitors.cpp"
                "${CMAKE_SOURCE_DIR}/src/CBash.rc"
                )


file(GLOB_RECURSE TMP_FILES_HDRS
    "${CMAKE_SOURCE_DIR}/src/*.h"
)

foreach(f ${TMP_FILES_HDRS})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR "${CMAKE_SOURCE_DIR}/src/" ${f})
    set(SRCGR "Headers/${SRCGR}")

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

IF (CBASH_NO_BOOST_ZLIB)
    add_definitions(-DCBASH_NO_BOOST_ZLIB)
    find_package(Boost REQUIRED COMPONENTS iostreams)
    find_package(ZLIB REQUIRED)
    set (CBASH_LIBS ${ZLIB_LIBRARY})
ELSE ()
    find_package(Boost REQUIRED COMPONENTS iostreams zlib)
    find_package(ZLIB)
    set (CBASH_LIBS "")
ENDIF ()

# Include source and library directories.
include_directories ("${CMAKE_SOURCE_DIR}/include/cbash"
                     ${Boost_INCLUDE_DIRS}
                     ${ZLIB_INCLUDE_DIR})


##############################
# System-Specific Settings
##############################

# Settings when compiling for Windows. Since it's a Windows-only app this is always true, but useful to check for copy/paste into other projects.
IF (CMAKE_SYSTEM_NAME MATCHES "Windows")
    add_definitions (-DUNICODE -D_UNICODE -DNDEBUG -DWIN32 -D_WINDOWS)
    IF (BUILD_SHARED_LIBS)
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
    IF (PROJECT_STATIC_RUNTIME)
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


##############################
# Actual Building
##############################

# Build CBash.
add_library           (CBash ${CBASH_SRC} ${CBASH_GEN_HDRS} )
target_link_libraries (CBash ${Boost_LIBRARIES} ${CBASH_LIBS})
