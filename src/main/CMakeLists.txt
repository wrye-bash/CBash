# Settings passed on the command line:
#
# CBash_BUILD_SHARED_LIBS
# CBash_USE_STATIC_RUNTIME
# CBash_NO_BOOST_ZLIB

##############################
# General Settings
##############################



set(CBASH_HEADERS
    "Collection.h"
    "Visitors.h"
    )

set (CBASH_SOURCES  
        "Collection.cpp"
        "Visitors.cpp"
    )

##############################
# Actual Building
##############################

include_directories (   
        ${CBASH_SOURCE}/game
    )

# Build CBash.
add_library           (libmain STATIC ${CBASH_HEADERS} ${CBASH_SOURCES})
target_link_libraries (libmain libcommon libgame)


cotire(libmain)

