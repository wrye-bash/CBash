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

option(CBash_BUILD_SHARED_LIBS "Build a shared library" ON)
option(CBash_USE_STATIC_RUNTIME "Build with static runtime libs (/MT)" ON)
option(CBash_NO_BOOST_ZLIB "Build with external Zlib" ON)

set (Boost_USE_STATIC_LIBS ON)
set (Boost_USE_MULTITHREADED ON)
set (Boost_NO_BOOST_CMAKE ON)
set (Boost_USE_STATIC_RUNTIME ${CBash_USE_STATIC_RUNTIME})

set(CBASH_RELEASE ${CMAKE_SOURCE_DIR}/release)
set(CBASH_TESTS ${CMAKE_SOURCE_DIR}/tests)
set(CBASH_SOURCE ${CMAKE_SOURCE_DIR}/src)

file (GLOB_RECURSE CBASH_GEN_HDRS "${CBASH_SOURCE}/*.h" )

file (GLOB_RECURSE CBASH_FONV "${CBASH_SOURCE}/FalloutNewVegas/*.cpp")
file (GLOB_RECURSE CBASH_OBLIVION "${CBASH_SOURCE}/Oblivion/*.cpp")
file (GLOB_RECURSE CBASH_SKYRIM "${CBASH_SOURCE}/Skyrim/*.cpp")

set (CBASH_SRC  "${CBASH_SOURCE}/CBash.cpp"
                "${CBASH_SOURCE}/Collection.cpp"
                "${CBASH_SOURCE}/Common.cpp"
                "${CBASH_SOURCE}/GenericChunks.cpp"
                "${CBASH_SOURCE}/GenericRecord.cpp"
                "${CBASH_SOURCE}/ModFile.cpp"
                "${CBASH_SOURCE}/TES4Record.cpp"
                "${CBASH_SOURCE}/TES4RecordAPI.cpp"
                "${CBASH_SOURCE}/Visitors.cpp"
                "${CBASH_SOURCE}/CBash.rc"
                ${CBASH_FONV}
                ${CBASH_OBLIVION}
                ${CBASH_SKYRIM}
                )


file(GLOB_RECURSE TMP_FILES_HDRS
    "${CBASH_SOURCE}/*.h"
)

foreach(f ${TMP_FILES_HDRS})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR "${CBASH_SOURCE}/" ${f})
    set(SRCGR "Headers/${SRCGR}")

    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})

    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

file(GLOB_RECURSE TMP_FILES
    "${CBASH_SOURCE}/*.cpp"
)
foreach(f ${TMP_FILES})
    # Get the path of the file relative to ${DIRECTORY},
    # then alter it (not compulsory)
    file(RELATIVE_PATH SRCGR "${CBASH_SOURCE}/" ${f})
    set(SRCGR "Source Files/${SRCGR}")
    # Extract the folder, ie remove the filename part
    string(REGEX REPLACE "(.*)(/[^/]*)$" "\\1" SRCGR ${SRCGR})
    # Source_group expects \\ (double antislash), not / (slash)
    string(REPLACE / \\ SRCGR ${SRCGR})
    source_group("${SRCGR}" FILES ${f})
endforeach()

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
include_directories ("${CMAKE_SOURCE_DIR}/include/cbash"
                     ${Boost_INCLUDE_DIRS}
                     ${ZLIB_INCLUDE_DIR})


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


##############################
# Actual Building
##############################

# Build CBash.
add_library           (CBash ${CBASH_SRC} ${CBASH_GEN_HDRS} )
target_link_libraries (CBash ${Boost_LIBRARIES} ${CBASH_LIBS})

add_subdirectory (deps/pybind11)

