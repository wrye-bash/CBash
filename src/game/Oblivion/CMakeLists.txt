
# Include source and library directories.
# include_directories (${CBASH_INCLUDE}
#                      ${Boost_INCLUDE_DIRS}
#                      ${ZLIB_INCLUDE_DIR})


file (GLOB_RECURSE OBLIVION_RECORD_HEADERS "Records/*.h" )
file (GLOB_RECURSE OBLIVION_RECORD_SOURCES "Records/*.cpp" )
file (GLOB_RECURSE OBLIVION_RECORD_API "Records/API/*.cpp" )

set (OBLIVION_HEADERS

    "GRUPRecord.h"
    "TES4File.h"
    ${OBLIVION_RECORD_HEADERS}
    )

set (OBLIVION_SOURCES 

    "TES4File.cpp"
    ${OBLIVION_RECORD_SOURCES}
    ${OBLIVION_RECORD_API}
    )


add_library(libgame_oblivion STATIC ${OBLIVION_HEADERS} ${OBLIVION_SOURCES}) 
target_link_libraries (libgame_oblivion ${Boost_LIBRARIES} ${CBASH_LIBS} libcommon)

cotire(libgame_oblivion)
