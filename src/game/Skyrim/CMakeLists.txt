
# Include source and library directories.
# include_directories (${CBASH_INCLUDE}
#                      ${Boost_INCLUDE_DIRS}
#                      ${ZLIB_INCLUDE_DIR})


file (GLOB SKYRIM_RECORD_HEADERS "Records/*.h" )
file (GLOB SKYRIM_RECORD_SOURCES "Records/*.cpp" )

file (GLOB_RECURSE SKYRIM_VMAD_HEADERS "VMAD/*.h" )
file (GLOB_RECURSE SKYRIM_VMAD_SOURCES "VMAD/*.cpp" )

file (GLOB SKYRIM_RECORD_API "Records/API/*.cpp" )

set (SKYRIM_HEADERS

    "GRUPRecord.h"
    "SkyrimCommon.h"
    "SkyrimChunks.h"
    "TES5ModFile.h"
    "TES5Record.h"
    "TES5File.h"

    ${SKYRIM_VMAD_HEADERS}
    ${SKYRIM_RECORD_HEADERS}
    )

set (SKYRIM_SOURCES 

    "SkyrimChunks.cpp"
    "SkyrimCommon.cpp"
    "TES5File.cpp"
    "TES5Record.cpp"

    ${SKYRIM_VMAD_SOURCES}
    ${SKYRIM_RECORD_SOURCES}
    ${SKYRIM_RECORD_API}
    )

add_library(libgame_skyrim STATIC ${SKYRIM_HEADERS} ${SKYRIM_SOURCES}) 
target_link_libraries (libgame_skyrim ${Boost_LIBRARIES} ${CBASH_LIBS} libcommon)

cotire(libgame_skyrim)
