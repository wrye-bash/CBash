# CBash

CBash is a library for reading and writing TES IV: Oblivion, TES V: Skyrim and Fallout: New Vegas plugin files. It's used by the [Wrye Bash](https://github.com/wrye-bash/wrye-bash) modding utility to build its Bashed Patch plugins.

Instructions on how to build CBash can be found [here](docs/BUILD.md).

The plugin file formats are documented at the following locations:

* Oblivion: [UESP.net](http://www.uesp.net/wiki/Tes4Mod:Mod_File_Format)
* Skyrim: [UESP.net](http://www.uesp.net/wiki/Tes5Mod:Mod_File_Format)
* Fallout: New Vegas: [FOPDoc](https://github.com/WrinklyNinja/fopdoc)

The CBash API is currently sparsely documented. There is some Doxygen-style documentation of the API functions exposed in [CBash.h](CBash.h), but some details of the field-related functions' arguments can only be found by reading the source of the `.cpp` files for the record type you are trying to access the fields of.

CBash's record and field support is incomplete. For information on what has and has not ben implemented, see the [wiki](https://github.com/lojack5/CBash/wiki).
