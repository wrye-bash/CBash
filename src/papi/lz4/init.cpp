#include "../cint.h"

#include "module.h"

static test_initializer modules([](py::module &m) {
    m.def_submodule("lz4")
        .def("version", lz4::api::versionNumber);
});
