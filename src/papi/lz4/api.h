#ifndef __CINT_LZ4_API__
#define __CINT_LZ4_API__
#pragma once

#include <gsl/gsl>
#include "module.h"

namespace lz4 { namespace api {
    namespace _detail{};

    using namespace gsl;

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


    namespace _detail {
        #include <lz4.h>

        constexpr auto VERSION_NUMBER = LZ4_VERSION_NUMBER;
        constexpr auto MAX_INPUT_SIZE = LZ4_MAX_INPUT_SIZE;

        template<int Size>
            constexpr auto COMPRESSBOUND = LZ4_COMPRESSBOUND(Size);
    };

    using _detail::MAX_INPUT_SIZE; 
    using _detail::COMPRESSBOUND;

    constexpr int versionNumber()
        {
            return _detail::VERSION_NUMBER;
        };

    inline int compressBound(int inputSize)
        {
        return _detail::LZ4_compressBound(inputSize);
        };

    inline int compressBound(const span<char> input)
        {
        return _detail::LZ4_compressBound(input.length());
        };

    inline int compress_default(const span<char> source, span<char> dest)
        {
        return _detail::LZ4_compress_default(source.data(), dest.data(), source.length(), dest.length());
        };

    inline int decompress_safe (const span<char> source, span<char>  dest)
        {
        return _detail::LZ4_decompress_safe(source.data(), dest.data(), source.length(), dest.length());
        };

    inline int sizeofState()
        {
        return _detail::LZ4_sizeofState();
        };

    inline int compress_fast_extState(span<byte> state, const span<char> source, span<char> dest, int acceleration)
        {
        return _detail::LZ4_compress_fast_extState(state.data(), source.data(), dest.data(), source.length(), dest.length(), acceleration);
        };
        
    inline int compress_destSize (span<char>& source, span<char> dest)
        {
        auto sourceSize = source.length();
        volatile int sourceUsed = sourceSize;
        auto atExit = finally([&](){
            source = source.subspan(sourceSize - sourceUsed);
        });

        return _detail::LZ4_compress_destSize(source.data(), dest.data(), const_cast<int*>(&sourceUsed), dest.length());
        };

    inline int decompress_fast (const span<char> source, span<char> dest, int uncompressedSize)
        {
        return _detail::LZ4_decompress_fast(source.data(), dest.data(), uncompressedSize);
        };

    inline int decompress_safe_partial (const span<char> source, span<char> dest, int targetOutputSize)
        {
        return _detail::LZ4_decompress_safe_partial (source.data(), dest.data(), source.length(), targetOutputSize, dest.length());    
        };    
};
};

#endif // __CINT_LZ4_API__
