# CBash

CBash is a C/C++ library for reading and writing TES IV: Oblivion, TES V: Skyrim and Fallout: New Vegas plugin files. It's used by the [Wrye Bash](https://github.com/wrye-bash/wrye-bash) modding utility to build its Bashed Patch plugins.

For bugs and feature request, feel free to open a new Issue in the Issue tracker.  For other discussions, open a new thread [here](http://ost.io/@lojack5/CBash "ost.io"), for example asking questions about what specific parts of the code do, etc.

## Build CBash

Instructions on how to build CBash can be found [in this document](docs/BUILD.md) in the source code distribution.  Also, always check the [wiki](https://github.com/wrye-bash/CBash/wiki) in case there's more general information to find there.

## CBash provided API

The CBash API is currently sparsely documented. There is some Doxygen-style documentation of the API in the [include headers](include/cbash).

## Supported Record formats

The plugin file formats are documented at the following locations:

* Oblivion: [UESP.net](http://www.uesp.net/wiki/Tes4Mod:Mod_File_Format)
* Skyrim: [UESP.net](http://www.uesp.net/wiki/Tes5Mod:Mod_File_Format)
* Fallout: New Vegas: [FOPDoc](https://github.com/WrinklyNinja/fopdoc)

CBash's record and field support is incomplete. For information on what has and has not ben implemented, see the [wiki](https://github.com/wrye-bash/CBash/wiki).

## History and credits

This repository was created from the [current state](https://github.com/lojack5/CBash/commit/1f90085a27c6847685d6eb9589a1d7fda5c85862) (as of 10/15/2016) of Lojack's [CBash repository](https://github.com/lojack5/CBash).

## License

See [gpl.txt](gpl.txt)