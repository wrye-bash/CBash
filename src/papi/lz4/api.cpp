#include "api.h"

using namespace lz4::api;
using namespace gsl;

namespace 
{
    #include <lz4.h> 
};

int compressBound(int inputSize)
    {
    return LZ4_compressBound(inputSize);
    };

int compressBound(const span<char> input)
    {
    return LZ4_compressBound(input.length());
    };

int compress_default(const span<char> source, span<char> dest)
    {
    return LZ4_compress_default(source.data(), dest.data(), source.length(), dest.length());
    };

int decompress_safe (const span<char> source, span<char>  dest)
    {
    return LZ4_decompress_safe(source.data(), dest.data(), source.length(), dest.length());
    };

int sizeofState()
    {
    return LZ4_sizeofState();
    };

int compress_fast_extState(span<byte> state, const span<char> source, span<char> dest, int acceleration)
    {
    return LZ4_compress_fast_extState(state.data(), source.data(), dest.data(), source.length(), dest.length(), acceleration);
    };
    
int compress_destSize (span<char>& source, span<char> dest)
    {
    auto sourceSize = source.length();
    volatile int sourceUsed = sourceSize;
    auto atExit = finally([&](){
        source = source.subspan(sourceSize - sourceUsed);
    });

    return LZ4_compress_destSize(source.data(), dest.data(), const_cast<int*>(&sourceUsed), dest.length());
    };

int decompress_fast (const span<char> source, span<char> dest, int uncompressedSize)
    {
    return LZ4_decompress_fast(source.data(), dest.data(), uncompressedSize);
    };

int decompress_safe_partial (const span<char> source, span<char> dest, int targetOutputSize)
    {
    return LZ4_decompress_safe_partial (source.data(), dest.data(), source.length(), targetOutputSize, dest.length());    
    };