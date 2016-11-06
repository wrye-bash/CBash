#ifndef __CINT_LZ4_MODULE__
#define __CINT_LZ4_MODULE__
#pragma once

#include <pybind11/pybind11.h>

#include "api.h"    

namespace py = pybind11;
using namespace pybind11::literals;

namespace lz4 {


    class context {
        context();
        ~context();
    };


    py::bytes compress(const py::bytes& buffer);
    py::bytes decompress(const py::bytes& buffer, int expectedSize = 0);
};
#endif // __CINT_LZ4_MODULE__