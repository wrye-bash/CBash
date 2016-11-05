#ifndef __CINT_LZ4_API__
#define __CINT_LZ4_API__
#pragma once

#include <string>
#include <gsl/gsl>
#include "module.h"
#include "api_detail.h"

namespace lz4 { namespace api {

    using namespace gsl;

    constexpr int MAX_INPUT_SIZE = _detail::MAX_INPUT_SIZE;
    
    template<int Size>
        constexpr int COMPRESSBOUND = _detail::_COMPRESSBOUND<Size>; 

    constexpr int VERSION_NUMBER()
        {
            return _detail::VERSION_NUMBER;
        };

    constexpr int VERSION_MAJOR()
        {
            return _detail::VERSION_MAJOR;
        };

    constexpr int VERSION_MINOR()
        {
            return _detail::VERSION_MINOR;
        };        

    constexpr int VERSION_RELEASE()
        {
            return _detail::VERSION_RELEASE;
        };        

    constexpr auto VERSION_STRING() 
        {
            return _detail::VERSION_STRING;
        };

    /**
        Provides the maximum size that LZ4 compression may output in a "worst case" scenario (input data not compressible)
        This function is primarily useful for memory allocation purposes (destination buffer size).

        Macro COMPRESSBOUND is also provided for compilation-time evaluation (stack memory allocation for example).
        Note that compress_default() compress faster when dest buffer size is >= compressBound(srcSize)

        @param inputSize  max supported value is MAX_INPUT_SIZE
        @return maximum output size in a "worst case" scenario
                or 0, if input size is too large ( > MAX_INPUT_SIZE)
    */
    int compressBound(int inputSize);
    int compressBound(const span<char> input);

    /**
        Compresses buffer 'source' into already allocated 'dest' buffer.

        Compression is guaranteed to succeed if 'dest.lenght()' >= compressBound(source.length()).
        It also runs faster, so it's a recommended setting.

        If the function cannot compress 'source' into a more limited 'dest' budget,
            compression stops *immediately*, and the function result is zero.
        As a consequence, 'dest' content is not valid.

        This function never writes outside 'dest' buffer, nor read outside 'source' buffer.

        @param source   The input data buffer. Max supported input size is LZ4_MAX_INPUT_VALUE
        @param dest     The output data buffer for compressed data.

        @return The number of bytes written into buffer 'dest' (necessarily <= dest.length())
            or 0 if compression fails
    */
    int compress_default(const span<char> source, span<char> dest);

    int decompress_safe (const span<char> source, span<char> dest);
    int sizeofState();
    int compress_fast_extState(span<byte> state, const span<char> source, span<char> dest, int acceleration);
    int compress_destSize (span<char>& source, span<char> dest);
    int decompress_fast (const span<char> source, span<char> dest, int uncompressedSize);
    int decompress_safe_partial (const span<char> source, span<char> dest, int targetOutputSize);
};
};

#include "api_impl.h"

#endif // __CINT_LZ4_API__
