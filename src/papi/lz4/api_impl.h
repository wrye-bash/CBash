#pragma once


namespace lz4 { namespace api {

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
