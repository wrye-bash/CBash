#include "../cint.h"

#include "module.h"

#include <tuple>

static test_initializer modules([](py::module &m) {

    m.def_submodule("lz4")
        .def("versionNumber", lz4::api::VERSION_NUMBER)
        .def("version", [](){
            return py::make_tuple(lz4::api::VERSION_MAJOR(), lz4::api::VERSION_MINOR(), lz4::api::VERSION_RELEASE());
        })
        .def("versionString", [](){
            return py::str(lz4::api::VERSION_STRING());
        })
    ;
});
