# Building CBash

Two methods of building CBash are documented:

* [Automated](BUILD.CMAKE.md): Using [CMake](http://cmake.org) to generate a Microsoft Visual C++ solution to build.
* [Manual](BUILD.MANUAL.md): Manually creating a Microsoft Visual C++ solution to build.

The instructions for both methods are tailored to the creation of MSVC 2013 solutions, though the automated method does allow for other build systems and platforms, at the expense of requiring CMake to be installed.

Make sure you have satisfied the dependencies below before following the instructions for either build method.

## Dependencies

CBash depends on two external libraries:

* [Boost](http://www.boost.org)
* [Zlib](http://zlib.net)

Both libraries can be built from source. However, it is generally easier to install the [prebuilt Boost binaries](http://sourceforge.net/projects/boost/files/boost-binaries/), which also include zlib binaries. Both build methods allow for either approach.

### Using Prebuilt Binaries

If using the prebuilt Boost binaries, download and install them, then make a note of the install path and the path the binary files themselves are found in.

Although it is not necessary to build a zlib binary when using the prebuilt binaries, the header files are still required for linking, so download and extract the zlib source. Make a note of where the source is extracted to.

### Building From Source

If building from source, extract the source archives and make a note of the paths they were extracted to. See the instructions below for how to build them on Windows using MSVC.

#### Boost

The Boost.Iostreams library must be built, which can be done using the commands below.

```
bootstrap.bat
b2 toolset=msvc link=static runtime-link=static variant=release address-model=32 --with-iostreams
```

`link`, `runtime-link` and `address-model` can all be modified if shared linking or 64 bit builds are desired. CBash uses statically-linked Boost libraries by default: to change this, edit [CMakeLists.txt](../CMakeLists.txt).

#### Zlib

There are a variety of ways to build zlib: for details, see the zlib documentation. To build zlib using CMake, do the following:

1. Configure CMake and generate a build system for Visual Studio by running CMake with keys `-DCMAKE_ARCHIVE_OUTPUT_DIRECTORY=build`.
2. Open the generated solution file, and build target `zlibstatic` with `Release` configuration.
