# Building CBash

## Requirements/Tools

The build process requires that the user has a modern Python distribution installed, and if he choses to go the CMake route as I assume you're doing since you're reading this, then a CMake installation is, of course, required.

* [Python](https://www.python.org/downloads/) - Last version used: 2.7.13
* [CMake](https://cmake.org/download/) - Last version used: 3.7.0-rc2

## C++ compiler

A compiler of your choice, but it must be C++11 compliant at least. This code was last built and developed using Visual Studio Community Edition 2015 on Windows, so I'd recommend sticking to that (or a later version) unless you know what you're doing. For the purposes of this write-up I'm asumming that you'll go that route and direct you to the corresponding downloads.

* [Visual Studio Community Edition](https://www.visualstudio.com/downloads/) - Can be downloaded for free from MS, use at least v14.0 (VS2015). Only the compilers and runtimes are strictly required.
* *OPTIONAL*: [Visual Studio Code Editor](https://code.visualstudio.com) - This is what I've been using for coding lately, and it's much more light-weight than the full-blown VS IDE and has many useful functions. I'd recommend to give it a try if you hate the VS IDE, like I do :)

## Detailed explanation

Two methods of building CBash are documented:

* [Automated](BUILD.CMAKE.md): Using [CMake](http://cmake.org) to generate a Microsoft Visual C++ solution to build.
* [Manual](BUILD.MANUAL.md): Manually creating a Microsoft Visual C++ solution to build (**NOT RECOMMENDED**). 

The instructions for both methods are tailored to the creation of MSVC solutions, though the automated method does allow for other build systems and platforms, at the expense of requiring CMake to be installed.

Make sure you have satisfied the dependencies below before following the instructions for either build method.

