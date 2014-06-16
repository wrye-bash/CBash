# Building CBash Using CMake

These instructions were used to build CBash using Microsoft Visual Studio 2012 and Microsoft Visual Studio Express 2013 for Desktop, though they should also apply to other compilers with minimal adaptation.

CBash's CMake configuration builds an executable that can be run on Windows XP, but this support has only been implemented for MSVC 2012 and 2013 - other versions of MSVC may require editing of CBash's [CMakeLists.txt](../CMakeLists.txt) file.

CBash uses the following CMake variables to set build parameters:

Parameter | Values | Description
----------|--------|------------
`BUILD_SHARED_LIBS` | `ON`, `OFF` | Whether or not to build a shared CBash binary (DLL). Defaults to `ON`.
`PROJECT_STATIC_RUNTIME` | `ON`, `OFF` | Whether to link the C++ runtime statically or not. This also affects the Boost libraries used. Defaults to `ON`.
`CBASH_NO_BOOST_ZLIB` | `ON`, `OFF` | Whether to use the zlib binary distributed with the prebuilt Boost library binaries. Defaults to `OFF`.

Depending on your configuration, you may also need to define the `BOOST_ROOT`, `BOOST_LIBRARYDIR` and `ZLIB_ROOT` folder paths for CMake to find the required libraries. Use the paths you noted down when you installed/extracted the dependencies.

1. Set CMake up so that it builds the binaries in the `build` subdirectory of the CBash folder.
2. Define any necessary parameters.
3. Configure CMake, then generate a build system for Visual Studio 2013.
4. Open the generated solution file, and build it.
