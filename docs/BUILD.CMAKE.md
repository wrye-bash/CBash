# Building CBash Using CMake

These instructions were used to build CBash using Microsoft Visual Studio 2012 and Microsoft Visual Studio Express 2013 for Desktop, though they should also apply to other compilers with minimal adaptation.

CBash's CMake configuration builds an executable that can be run on Windows XP, but this support has only been implemented for MSVC 2012, 2013 and 2015 - other versions of MSVC may require editing of CBash's [CMakeLists.txt](../CMakeLists.txt) file.

CBash uses the following CMake variables to set build parameters:

Parameter | Values | Description
----------|--------|------------
`CBash_BUILD_SHARED_LIBS` | `ON`, `OFF` | Whether or not to build a shared CBash binary (DLL). Defaults to `ON`.
`CBash_USE_STATIC_RUNTIME` | `ON`, `OFF` | Whether to link the C++ runtime statically or not. This also affects the Boost libraries used. Defaults to `ON`.
`CBash_NO_BOOST_ZLIB` | `ON`, `OFF` | Whether to use the zlib binary distributed with the prebuilt Boost library binaries. Defaults to `OFF`.

Depending on your configuration, you may also need to define the `BOOST_ROOT`, `BOOST_LIBRARYDIR` and `ZLIB_ROOT` folder paths for CMake to find the required libraries. Use the paths you noted down when you installed/extracted the dependencies.

**General procedure**
1. Set CMake up so that it builds the binaries in the `build` subdirectory of the CBash folder.
2. Define any necessary parameters.
3. Configure CMake, then generate a build system for Visual Studio 2013.
4. Open the generated solution file, and build it.



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
set ZLIB_BASE=<PATH>
set BOOST_BASE=<PATH>

set ZLIB_VERSION=<ZLIB TAG>
set BOOST_VERSION=boost-X.YY.Z

set CONFIG=Release
```

* **CMAKE_GENERATOR**: Used for CMAKE generate command. Change this to the version of VS you got. You can Use: ```CMAKE --help``` and look in the Generators list at the end of the help dump
* **ZLIB_BASE**: Any directory will do _(preferably an empty one)_. Example from my own setup: 'C:\Sources\3rdparty\ZLIB', but it can be whatever else works for you.
* **BOOST_BASE**: Same as above. Example from my own setup: 'C:\Sources\3rdparty\Boost'.
* **ZLIB_VERSION**: Use `v1.2.11` or later. Look at https://github.com/madler/zlib for the latest tag.
* **BOOST_VERSION**: Use `boost-1.64.0` or look at https://github.com/boostorg/boost and check for a later tag.
* **CONFIG**: Type of binary to generate, either `Release` -or- `Debug`.

#### Zlib

There are a variety of ways to build zlib: for details, see the zlib documentation. I'm gonna describe how to quickly build ZLIB using CMake here.

1. First, clone source ZLIB repo:
```batch
cd %ZLIB_BASE%
git clone https://github.com/madler/zlib zlib.git -b %ZLIB_VERSION%
cd zlib.git
```
2. Generate the binaries:
```batch
mkdir build
cd build
cmake -G %CMAKE_GENERATOR% ..
```
3. Compile the generated projects (you can open the generated projects in VS and compile them from there):
```batch
cmake --build . --target --config %CONFIG%
```
4. Finally, copy `zconf.h` to the main ZLIB directory, as their build process don't do that autmatically.
```batch
copy zconf.h ..
```

#### Boost

CBash requires the Boost.Iostreams library, which for that reason must be built. Also, we generate the static libraries because CBash links to Boost statically, but the C++ runtime is always dynamically linked.

1. First and longest step: clone Boost repo. Go take a walk, or get some tea/coffee while this runs :)
```batch
cd %BOOST_BASE%
git clone https://github.com/boostorg/boost boost.git -b %BOOST_VERSION%
``` 
2. Second step, and close second in longest time too... another drink maybe?
```batch
cd boost.git
git submodule init
git submodule update
```
3. Bootstrap, which creates the B2 build system needed for the next step.
```batch
bootstrap.bat
```
4. The actual Boost building
```batch
b2 --layout=versioned toolset=msvc-14.0 -sZLIB_LIBPATH=%ZLIB_ROOT% -sZLIB_INCLUDE=%ZLIB_ROOT% address-model=32 link=static variant=release,debug runtime-link=shared threading=multi stage release
```

In the command above `link`, `runtime-link` and `address-model` can all be modified if shared linking is desired or if creating 64 bit builds are desired. CBash uses statically-linked Boost libraries by default: but this can be controlled by specifying CMake options to CBash build.

#### CBash building

All of the above was pre-requisite. Now is the actual stuff that's needed to produce CBash.dll and other outputs.

1. First, let us set some variables to simplify the following commands a bit:

```batch
SET ZLIB_ROOT=%ZLIB_BASE%\zlib.git
SET BOOST_ROOT=%BOOST_BASE%\boost.git
```

* **ZLIB_ROOT**: Just points to the folder where we just built the ZLIB sources.
* **BOOST_BASE**: Same as above, for Boost.

2. Get a copy of the source
```batch
git clone https://github.com/wrye-bash/CBash.git CBash.git -b wip
cd CBash.git
git submodule init
git submodule update
```

3. Prepare for building (the actual `build` directory could be anywhere, though)
```batch
mkdir build && cd build
```

4. CMake Generate
```batch
cmake -G %CMAKE_GENERATOR% ..
 -DCBash_BUILD_SHARED_LIBS=ON
 -DBoost_NO_SYSTEM_PATHS=ON
 -DCBash_USE_STATIC_RUNTIME=OFF
 -DCBash_NO_BOOST_ZLIB=ON
 -DBOOST_ROOT=%BOOST_ROOT%
 -DBOOST_INCLUDEDIR=%BOOST_ROOT%
 -DBOOST_LIBRARYDIR=%BOOST_ROOT%\stage\lib
 -DZLIB_INCLUDE_DIR=%ZLIB_ROOT%
 -DZLIB_LIBRARY_RELEASE=%ZLIB_ROOT%\build\Release\zlibstatic.lib
 -DZLIB_LIBRARY_DEBUG=%ZLIB_ROOT%\build\Debug\zlibstaticd.lib
```

Lets explain the options, since there are many:
* **CBash_BUILD_SHARED_LIBS**: Instructs the CMake process to generate a `CBash.dll` output. You can set this to OFF and generate a static library instead.
* **CBash_USE_STATIC_RUNTIME**: Switch to chose if the runtimes are to be linked statically or dynamically. Preferred option is dynamically, due to the fact that if static linkage is needed, then you'd have to change the build options for Boost and ZLIB to have the same requirements as dynamic and static runtimes cannot be mixed in the same link.
* **CBash_NO_BOOST_ZLIB**:  Instruct CBash not to search for Boost's provided ZLIB implementation, because we're using the real ZLIB here.
* **Boost_NO_SYSTEM_PATHS**: Instruct the CMake's FindBoost command NOT to look on the user's system paths for Boost, as some compilers bring their own Boost distributions (Borland's C++Builder notably) which could be very outdated w.r.t. current Boost implementation, and CMake insists in prioritizing those detected paths instead of the ones we want.
* **BOOST_INCLUDEDIR**: Simply a path to the boost's includes
* **BOOST_LIBRARYDIR**: Path to the boost's produced libraries (*.lib)
* **ZLIB_INCLUDE_DIR**: Path to ZLIB includes
* **ZLIB_LIBRARY_RELEASE**: Path to ZLIB release version of the compiled library file.
* **ZLIB_LIBRARY_DEBUG**: Path to ZLIB debug version of the compiled library file.

5. Once everything is generated, we can actually compile CBash, either from CMake or by opening generated VS solution files from the `build` directory.
```batch
cmake --build . --target --config %CONFIG%
```

