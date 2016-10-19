/*
    tests/test_modules.cpp -- nested modules, importing modules, and
                            internal references

    Copyright (c) 2016 Wenzel Jakob <wenzel.jakob@epfl.ch>

    All rights reserved. Use of this source code is governed by a
    BSD-style license that can be found in the LICENSE file.
*/

#include "cint.h"

std::string submodule_func() {
    return "submodule_func()";
}

test_initializer modules([](py::module &m) {
    py::module m_sub = m.def_submodule("submodule");
    m_sub.def("submodule_func", &submodule_func);

    m.attr("OD") = py::module::import("collections").attr("OrderedDict");
});
