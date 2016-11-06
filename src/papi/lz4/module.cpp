#include "module.h"

#include <boost/format.hpp>

#include <gsl/gsl>
#include <string>
#include <vector>
#include <tuple>

using boost::format;

py::bytes lz4::compress(const py::bytes& buffer) 
{
    std::string source{buffer};
    auto size = api::compressBound(source.length());


    std::vector<char> dest(size);

    auto res = api::compress_default(source, dest);

    if (res <= 0) {
        const auto errorMsg = (format("LZ4: compression failed with result code: %1%") % res).str();
        throw std::exception(errorMsg.c_str());
    }

    return py::bytes(dest.data(), res);
};

py::bytes lz4::decompress(const py::bytes& buffer, int expectedSize)
{
    if (expectedSize < 0) {
        throw std::exception("Argument out of valid range: 'expectedSize' was negative.");
    }

    if (expectedSize == 0) {
        expectedSize = 16*1024;
    }

    std::string source{buffer};
    std::vector<char> dest(expectedSize);

    auto res = api::decompress_safe(source, dest);
    if (res <= 0) {
        const auto errorMsg = (format("decompression failed with code: %1%") % res).str();
        throw std::exception(errorMsg.c_str());
    }

    return py::bytes(dest.data(), res);
};