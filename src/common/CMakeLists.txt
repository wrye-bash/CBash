
# Include source and library directories.
# include_directories (${CBASH_INCLUDE}
#                      ${Boost_INCLUDE_DIRS}
#                      ${ZLIB_INCLUDE_DIR})

set (COMMON_HEADERS
    "Allocator.h"
    "Common.h"
    "GenericChunks.h"
    "GenericRecord.h"
    "MacroDefinitions.h"
    "ModFile.h"
    "TES4Record.h"
    )

set (COMMON_SOURCES 

    "Common.cpp"
    "GenericChunks.cpp"
    "GenericRecord.cpp"
    "ModFile.cpp"
    "TES4Record.cpp"
    "TES4RecordAPI.cpp"
    )

include_directories (${CBASH_INCLUDE} ${Boost_INCLUDE_DIRS} ${ZLIB_INCLUDE_DIR})

add_library(libcommon STATIC ${COMMON_HEADERS} ${COMMON_SOURCES})

cotire(libcommon)