#include "../cint.h"

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
