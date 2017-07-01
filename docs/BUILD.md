# Building CBash

Two methods of building CBash are documented:

* [Automated](BUILD.CMAKE.md): Using [CMake](http://cmake.org) to generate a Microsoft Visual C++ solution to build.
* [Manual](BUILD.MANUAL.md): Manually creating a Microsoft Visual C++ solution to build.

The instructions for both methods are tailored to the creation of MSVC 2013 solutions, though the automated method does allow for other build systems and platforms, at the expense of requiring CMake to be installed.

Make sure you have satisfied the dependencies below before following the instructions for either build method.

## Requirements/Tools

The build process raquires that the user has a modern Python distribution installed, and if he choses to go the CMake route, then a CMake installation is, of course, required.

* [Python](https://www.python.org/downloads/) - Last version used: 2.7.13
* [CMake](https://cmake.org/download/) - Last version used: 3.7.0-rc2

## C++ compiler

A compiler of your choice, but it must be C++11 compliant at least. This code was last built and developed using Visual Studio Community Edition 2015 on Windows, so I'd recommend sticking to that (or a later version) unless you know what you're doing. For the purposes of this write-up I'm asumming that you'll go that route and direct you to the corresponding downloads.

* [Visual Studio Community Edition](https://www.visualstudio.com/downloads/) - Can be downloaded for free from MS, use at least v14.0 (VS2015). Only the compilers and runtimes are strictly required.
* *OPTIONAL*: [Visual Studio Code Editor](https://code.visualstudio.com) - This is what I've been using for coding lately, and it's much more light-weight than the full-blown VS IDE and has many useful functions. I'd recommend to give it a try if you hate the VS IDE, like I do :)

## Dependencies

CBash depends on two external libraries:

* [Boost](http://www.boost.org) - Last version used: 1.64.0
* [Zlib](http://zlib.net) - Last version used: 1.2.11

Both libraries can be built from source. However, it is generally easier to install the [prebuilt Boost binaries](http://sourceforge.net/projects/boost/files/boost-binaries/), which also include zlib binaries. Both build methods allow for either approach.

### Using Prebuilt Binaries

If using the prebuilt Boost binaries, download and install them, then make a note of the install path and the path the binary files themselves are found in.

Although it is not necessary to build a zlib binary when using the prebuilt binaries, the header files are still required for linking, so download and extract the zlib source. Make a note of where the source is extracted to.

Skip the next sections on building the dependences.

### Building Dependences From Source

If building from source, extract the source archives and make a note of the paths they were extracted to. See the instructions below for how to build them on Windows using MSVC.

#### Variables

I'm gonna use some variables during this explanation to represent the fact that you'd have to chose some directories in your machine where the downloaded/cloned sources are going to be placed.

I cannot hard-code this folders nor give you exact paths for them, so I'll be using symbolic names for the rest of this explanation, as if they were environment variables defined on your system. But it's **not** required to define them as env variables at all... you can take this explanation and search and replace all appearances of a variable with the real path and everything should work.

As an example, in my own setup, I have everything related to third party libraries located in my 'C:\Sources\3rdparty folder', where for each library I create a root folder inside that to hold the possibly different version of libraries that my project could require. 

These are the variables that we're going to need:

```batch
set CMAKE_GENERATOR="Visual Studio 14 2015"
set ZLIB_BASE=<PATH TO EMPTY DIR BASE FOR ZLIB SOURCES>
set BOOST_BASE=<PATH TO EMPTY DIR BASE FOR BOOST SOURCES>
```

* **CMAKE_GENERATOR**: Used for CMAKE generate command. Change this to the version of VS you got. You can Use: ```CMAKE --help``` and look in the Generators list at the end of the help dump
* **ZLIB_BASE**: Any directory will do _(preferably an empty one)_. Example from my own setup: 'C:\Sources\3rdparty\ZLIB', but it can be whatever else works for you.
* **BOOST_BASE**: Same as above. Example from my own setup: 'C:\Sources\3rdparty\Boost'.

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
