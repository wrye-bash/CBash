#include "../cint.h"

#include "module.h"

#include <pybind11/pybind11.h>
#include <gsl/gsl>
#include <string>
#include <vector>
#include <tuple>

using namespace gsl;

static test_initializer modules([](py::module &m) {

    m.def_submodule("lz4")
        .def("VERSION_NUMBER", lz4::api::VERSION_NUMBER)
        .def("VERSION", [](){
            return py::make_tuple(lz4::api::VERSION_MAJOR(), lz4::api::VERSION_MINOR(), lz4::api::VERSION_RELEASE());
        })
        .def("__version__", [](){
            return py::str(lz4::api::VERSION_STRING());
        })
        .def("compress", [](const py::bytes& buffer){

            std::string source{buffer};
            auto size = lz4::api::compressBound(source.length());


            std::vector<char> dest(size);

            auto res = lz4::api::compress_default(source, dest);

            if (res == 0) {
                throw std::exception("compression failed");
            }


            return py::bytes(dest.data(), res);
        })
    ;
});
