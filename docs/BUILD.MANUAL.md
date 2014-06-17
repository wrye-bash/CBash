# Building CBash "Manually"

These instructions are for building CBash on Windows by manually creating a Microsoft Visual Studio solution. The instructions were written using MSVC 2013, so slight changes may be required if you are using a different version.

An example of the end result can be found [here](https://drive.google.com/file/d/0B1ddaVyxNcp-ZmpyUENiRFkyUEE/edit?usp=sharing "Google Drive"), though these files are out-of-date compared to the current code, so it's best to create your own solution.

1. Create a new Win32 Application project.  In the creation wizard be sure to select DLL, and tick the Empty Project option.
2. Now add all the CBash source files to the project.  Personally I make the source layout look mostly identical to the actual file layout on disk.  So I have a `Skyrim`, `Fallout New Vegas`, and `Oblivion` sub-filters for each of the `Source Files` and `Header Files`.  Then under those a sub-filter called `Records`, and under that one called `API`.  Just throw every `*.h` and `*.cpp` file into their appropriate filters in the solution explorer. Make sure to include the header files in the `include/cbash` folder too. Finally add `CBash.rc` into the `Resource Files` section.

  Alternatively, you can try running [this](https://github.com/lojack5/utilities/blob/master/project_update.py) Python script, which should correctly add all required files to the project.  **Note:** That script is written only for Visual Studio 2013, I don't know how or if it will work for other versions.
3. Change Project settings for `All Configurations`.  The next few steps will all be changing settings under the following section:
  * Right Click on your project in Visual Studio, select Properties.
  * In the Property Pages window that pops up, select `All Configurations` from the Configuration drop down.
  * All changes will be made under the `Configuration Properties` sub tree on the left.
4. Additional Directories:
  * Go to `VC++ Directories`.
  * Edit `Include Directories` so that it includes the path to Boost, zlib and the `include/cbash` directory.
  * Edit `Library Directories` so that it includes the path to Boost.
  * If you built the zlib binaries and are going to use those instead of Boost's, add that of course.
4. Output Files:
  * Go to `C/C++ -> Output Files`.
  * Edit both `ASM List Location` and `Object File Name` to `$(IntDir)\%(RelativeDir)`.  Note there is no backslash at the end.  This setting is so files with the same name won't end up making object files that overwrite each other.
5. Preprocessor:
  * Go to `C/C++ -> Preprocessor`
  * Edit `Preprocessor Definitions` to include `_CRT_SECURE_NO_WARNINGS`.  This will stop the compiler from throwing errors for using things like `strncat`.
6. Additional Configuration (Optional):
  * CBash uses boost's `auto_link.hpp` to automatically link to the correct boost zlib binary.  If you don't want CBash to use boost's binaries and want to specify your own instead, you need to disable this.  Go to `C/C++ -> Preprocessor -> Preprocessor Definitions` and add `CBASH_NO_BOOST_ZLIB` to the list of definitions.  Then you will need to add your zlib binary under `Linker -> Input -> Additional Dependencies`.
  * CBash automatically detects how you are using it by looking for the `_USRDLL` preprocessor definition in your project file.  This definition is added by the MSVC project wizard when making a new DLL project, so if CBash isn't detecting this correctly, you have two options:
    * Add/remove `_USRDLL` from the preprocessor definitions as applicable.
    * Add/remove `CBASH_DLL` or `CBASH_STATIC` from the preprocessor definitions for your project file to force one or the other.
    * Optionally, you could also `#define` these in CBash.cpp, before the include for CBash.h
