/*
    tests/pybind11_tests.cpp -- pybind example plugin

    Copyright (c) 2016 Wenzel Jakob <wenzel.jakob@epfl.ch>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#include "cint.h"
#include "CBash.h"

std::list<std::function<void(py::module &)>> &initializers() {
    static std::list<std::function<void(py::module &)>> inits;
    return inits;
}

test_initializer::test_initializer(std::function<void(py::module &)> initializer) {
    initializers().push_back(std::move(initializer));
}

PYBIND11_PLUGIN(cint) {
    py::module m("cint", "CBash interface for Python");

    for (const auto &initializer : initializers())
        initializer(m);

    return m.ptr();
}
