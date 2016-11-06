#include "../cint.h"

#include "module.h"

#include <gsl/gsl>
#include <string>
#include <vector>
#include <tuple>


py::bytes lz4::compress(const py::bytes& buffer) 
{
    std::string source{buffer};
    auto size = api::compressBound(source.length());


    std::vector<char> dest(size);

    auto res = api::compress_default(source, dest);

    if (res == 0) {
        throw std::exception("compression failed");
    }

    return py::bytes(dest.data(), res);
};
