#include "../cint.h"
#include "module.h"

static test_initializer modules([](py::module &m) {

    using namespace lz4;

    m.def_submodule("lz4")
        .def("VERSION_NUMBER", VERSION_NUMBER)
        .def("VERSION", [](){
                return py::make_tuple(VERSION_MAJOR(), VERSION_MINOR(), VERSION_RELEASE());
            })
        .def("__version__", [](){
                return py::str(VERSION_STRING());
            })
        .def("compress", compress)
        .def("decompress", decompress)
    ;
});