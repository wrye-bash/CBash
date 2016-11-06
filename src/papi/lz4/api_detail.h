#pragma once

namespace lz4 { namespace api {

    namespace _detail
    {
        namespace 
        {
            #include <lz4.h>

            constexpr auto MAX_INPUT_SIZE = LZ4_MAX_INPUT_SIZE;
            
            constexpr auto VERSION_NUMBER = LZ4_VERSION_NUMBER;
            constexpr auto VERSION_MAJOR = LZ4_VERSION_MAJOR;
            constexpr auto VERSION_MINOR = LZ4_VERSION_MINOR;
            constexpr auto VERSION_RELEASE = LZ4_VERSION_RELEASE;
            constexpr const char VERSION_STRING[] = LZ4_VERSION_STRING; 

            template<int Size>
                constexpr auto COMPRESSBOUND = LZ4_COMPRESSBOUND(Size);

            #include <lz4frame.h>
        };  
    };
};
};