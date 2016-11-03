
# Include source and library directories.
# include_directories (${CBASH_INCLUDE}
#                      ${Boost_INCLUDE_DIRS}
#                      ${ZLIB_INCLUDE_DIR})


file (GLOB_RECURSE FALLOUTNV_RECORD_HEADERS "Records/*.h" )
file (GLOB_RECURSE FALLOUTNV_RECORD_SOURCES "Records/*.cpp" )
file (GLOB_RECURSE FALLOUTNV_RECORD_API "Records/API/*.cpp" )

set (FALLOUTNV_HEADERS

    "GRUPRecord.h"
    "FNVFile.h"
    "FNVRecord.h"
    ${FALLOUTNV_RECORD_HEADERS}
    )

set (FALLOUTNV_SOURCES 

    "FNVFile.cpp"
    "FNVRecord.cpp"
    ${FALLOUTNV_RECORD_SOURCES}
    ${FALLOUTNV_RECORD_API}
    )

add_library(libgame_falloutnv STATIC ${FALLOUTNV_HEADERS} ${FALLOUTNV_SOURCES}) 
target_link_libraries (libgame_falloutnv ${Boost_LIBRARIES} ${CBASH_LIBS} libcommon)

cotire(libgame_falloutnv)
