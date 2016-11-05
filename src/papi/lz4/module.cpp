#include "../cint.h"

#include "module.h"

#include <gsl/gsl>
#include <string>
#include <vector>
#include <tuple>



static test_initializer modules([](py::module &m) {

    using namespace gsl;
    using namespace lz4;

    m.def_submodule("lz4")
        .def("VERSION_NUMBER", VERSION_NUMBER)
        .def("VERSION", [](){
            return py::make_tuple(VERSION_MAJOR(), VERSION_MINOR(), VERSION_RELEASE());
        })
        .def("__version__", [](){
            return py::str(VERSION_STRING());
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
