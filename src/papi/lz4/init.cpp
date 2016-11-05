#include "../cint.h"

#include "module.h"

static test_initializer modules([](py::module &m) {
    auto lz4 = m.def_submodule("lz4");
    
});
