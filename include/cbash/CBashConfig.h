/* ***** BEGIN LICENSE BLOCK *****
* Version: MPL 1.1/GPL 2.0/LGPL 2.1
*
* The contents of this file are subject to the Mozilla Public License Version
* 1.1 (the "License"); you may not use this file except in compliance with
* the License. You may obtain a copy of the License at
* http://www.mozilla.org/MPL/
*
* Software distributed under the License is distributed on an "AS IS" basis,
* WITHOUT WARRANTY OF ANY KIND, either express or implied. See the License
* for the specific language governing rights and limitations under the
* License.
*
* The Original Code is CBash code.
*
* The Initial Developer of the Original Code is
* Waruddar.
* Portions created by the Initial Developer are Copyright (C) 2010
* the Initial Developer. All Rights Reserved.
*
* Contributor(s):
*
* Alternatively, the contents of this file may be used under the terms of
* either the GNU General Public License Version 2 or later (the "GPL"), or
* the GNU Lesser General Public License Version 2.1 or later (the "LGPL"),
* in which case the provisions of the GPL or the LGPL are applicable instead
* of those above. If you wish to allow use of your version of this file only
* under the terms of either the GPL or the LGPL, and not to allow others to
* use your version of this file under the terms of the MPL, indicate your
* decision by deleting the provisions above and replace them with the notice
* and other provisions required by the GPL or the LGPL. If you do not delete
* the provisions above, a recipient may use your version of this file under
* the terms of any one of the MPL, the GPL or the LGPL.
*
* ***** END LICENSE BLOCK ***** */
#pragma once
// CBashConfig.h


/* This header includes project configuration macros that changes some things
   depending on if CBash is being built or linked against.  Most of the options
   are automatically detected, with the exception of COMPILING_CBASH (which is
   manually defined in CBash.cpp).  As an API user, nothing special should be
   needed.  As a user building CBash, care must be taken to ensure the defines
   you want in place are defined before the first time this file is included.

   Options for all uses of CBash are:
       CBASH_STATIC - you are building/linking against the lib
       CBASH_DLL - you are building/linking against the dll

   Options for building CBash are:
       COMPILING_CBASH - you are building CBash dll/lib
       CBASH_NO_BOOST_ZLIB - do not link against Boost's version of zlib
*/


// If nothing is defined, assume linking against CBash.dll
#if !defined(CBASH_STATIC) & !defined(COMPILING_CBASH) &!defined(CBASH_DLL)
    #define CBASH_DLL
#endif


// Building CBash
#ifdef COMPILING_CBASH
    #if !defined(CBASH_DLL) & !defined(CBASH_STATIC)
        // Not specified if we're building the dll or lib, try to auto-detect
        // from the project settings.  _USRDLL is defined by the project
        // wizard for dll project, but this won't work if the settings are
        // changed afterwards.  In that case, manually specify which to build.
        #ifdef _USRDLL
            #define CBASH_DLL
        #else
            #define CBASH_STATIC
        #endif
    #endif
#endif


// Sanity checks for defines
#if defined(CBASH_STATIC) & defined(CBASH_DLL)
    #error "CBash cannot be used as both a static and dynamic library."
#elif !defined(CBASH_STATIC) & !defined(CBASH_DLL)
    #error "Could not determine CBash build/link configuration."
#endif


// DLLExport/Import
#ifdef __cplusplus
    #define CBEXTERN extern "C"
#else
    #define CBEXTERN
#endif
#define DLLEXPORT CBEXTERN __declspec(dllexport)
#define DLLIMPORT CBEXTERN __declspec(dllimport)


// Setup some defines/includes for use in CBash.h/.cpp
#ifdef COMPILING_CBASH
    // On MSVC 2005 and greater, prevent warnings about insecure CRT functions
    // Make sure this is defined before any other includes, so as to be defined
    // before any CRT headers are included (for example, via boost/config/auto_link.hpp)
    #if defined(_MSC_VER) && _MSC_VER >= 1400
        #define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
    #endif
    // Compiling either CBash static or dynamic library
    #ifdef CBASH_STATIC
        // Static (CBash.lib)
        #define DLLEXTERN CBEXTERN
        #define CPPDLLEXTERN CBEXTERN
    #else
        // Dynamic (CBash.dll)
        #define DLLEXTERN DLLEXPORT
        #define CPPDLLEXTERN DLLEXPORT
    #endif
    // Also, link against the Boost zlib library
    #if !defined(CBash_NO_BOOST_ZLIB)
        #define BOOST_LIB_NAME boost_zlib
        #include <boost/config/auto_link.hpp>
    #else
        // Cleanup
        #undef CBASH_NO_BOOST_ZLIB
    #endif
    // And prevent short name aliases for API functions
    #undef CBASH_SHORT_NAMES
#elif defined CBASH_STATIC
    // Linking to static CBash.lib
    #define DLLEXTERN CBEXTERN
#elif defined CBASH_DLL
    // Linking to dynamic CBash.dll
    #define DLLEXTERN DLLIMPORT
#endif


// Allow the user to specify they want macro aliases of the API functions
// to use the non-prefixed function names
#ifdef CBASH_SHORT_NAMES
    #define GetVersionMajor(...) cb_GetVersionMajor(__VA_ARGS__)
    #define GetVersionMinor(...) cb_GetVersionMinor(__VA_ARGS__)
    #define GetVersionRevision(...) cb_GetVersionRevision(__VA_ARGS__)
    #define CreateCollection(...) cb_CreateCollection(__VA_ARGS__)
    #define DeleteCollection(...) cb_DeleteCollection(__VA_ARGS__)
    #define LoadCollection(...) cb_LoadCollection(__VA_ARGS__)
    #define UnloadCollection(...) cb_UnloadCollection(__VA_ARGS__)
    #define GetCollectionType(...) cb_GetCollectionType(__VA_ARGS__)
    #define UnloadAllCollections(...) cb_UnloadAllCollections(__VA_ARGS__)
    #define DeleteAllCollections(...) cb_DeleteAllCollections(__VA_ARGS__)
    #define AddMod(...) cb_AddMod(__VA_ARGS__)
    #define LoadMod(...) cb_LoadMod(__VA_ARGS__)
    #define UnloadMod(...) cb_UnloadMod(__VA_ARGS__)
    #define CleanModMasters(...) cb_CleanModMasters(__VA_ARGS__)
    #define SaveMod(...) cb_SaveMod(__VA_ARGS__)
    #define GetAllNumMods(...) cb_GetAllNumMods(__VA_ARGS__)
    #define GetAllModIDs(...) cb_GetAllModIDs(__VA_ARGS__)
    #define GetLoadOrderNumMods(...) cb_GetLoadOrderNumMods(__VA_ARGS__)
    #define GetLoadOrderModIDs(...) cb_GetLoadOrderModIDs(__VA_ARGS__)
    #define GetFileNameByID(...) cb_GetFileNameByID(__VA_ARGS__)
    #define GetFileNameByLoadOrder(...) cb_GetFileNameByLoadOrder(__VA_ARGS__)
    #define GetModNameByID(...) cb_GetModNameByID(__VA_ARGS__)
    #define GetModNameByLoadOrder(...) cb_GetModNameByLoadOrder(__VA_ARGS__)
    #define GetModIDByName(...) cb_GetModIDByName(__VA_ARGS__)
    #define GetModIDByLoadOrder(...) cb_GetModIDByLoadOrder(__VA_ARGS__)
    #define GetModLoadOrderByName(...) cb_GetModLoadOrderByName(__VA_ARGS__)
    #define GetModLoadOrderByID(...) cb_GetModLoadOrderByID(__VA_ARGS__)
    #define GetModIDByRecordID(...) cb_GetModIDByRecordID(__VA_ARGS__)
    #define GetCollectionIDByRecordID(...) cb_GetCollectionIDByRecordID(__VA_ARGS__)
    #define GetCollectionIDByModID(...) cb_GetCollectionIDByModID(__VA_ARGS__)
    #define IsModEmpty(...) cb_IsModEmpty(__VA_ARGS__)
    #define GetModNumTypes(...) cb_GetModNumTypes(__VA_ARGS__)
    #define GetModTypes(...) cb_GetModTypes(__VA_ARGS__)
    #define GetModNumEmptyGRUPs(...) cb_GetModNumEmptyGRUPs(__VA_ARGS__)
    #define GetModNumOrphans(...) cb_GetModNumOrphans(__VA_ARGS__)
    #define GetModOrphansFormIDs(...) cb_GetModOrphansFormIDs(__VA_ARGS__)
    #define GetLongIDName(...) cb_GetLongIDName(__VA_ARGS__)
    #define MakeShortFormID(...) cb_MakeShortFormID(__VA_ARGS__)
    #define CreateRecord(...) cb_CreateRecord(__VA_ARGS__)
    #define CopyRecord(...) cb_CopyRecord(__VA_ARGS__)
    #define UnloadRecord(...) cb_UnloadRecord(__VA_ARGS__)
    #define ResetRecord(...) cb_ResetRecord(__VA_ARGS__)
    #define DeleteRecord(...) cb_DeleteRecord(__VA_ARGS__)
    #define GetRecordID(...) cb_GetRecordID(__VA_ARGS__)
    #define GetNumRecords(...) cb_GetNumRecords(__VA_ARGS__)
    #define GetRecordIDs(...) cb_GetRecordIDs(__VA_ARGS__)
    #define IsRecordWinning(...) cb_IsRecordWinning(__VA_ARGS__)
    #define GetNumRecordConflicts(...) cb_GetNumRecordConflicts(__VA_ARGS__)
    #define GetRecordConflicts(...) cb_GetRecordConflicts(__VA_ARGS__)
    #define GetRecordHistory(...) cb_GetRecordHistory(__VA_ARGS__)
    #define GetNumIdenticalToMasterRecords(...) cb_GetNumIdenticalToMasterRecords(__VA_ARGS__)
    #define GetIdenticalToMasterRecords(...) cb_GetIdenticalToMasterRecords(__VA_ARGS__)
    #define IsRecordFormIDsInvalid(...) cb_IsRecordFormIDsInvalid(__VA_ARGS__)
    #define UpdateReferences(...) cb_UpdateReferences(__VA_ARGS__)
    #define GetRecordUpdatedReferences(...) cb_GetRecordUpdatedReferences(__VA_ARGS__)
    #define SetIDFields(...) cb_SetIDFields(__VA_ARGS__)
    #define SetField(...) cb_SetField(__VA_ARGS__)
    #define DeleteField(...) cb_DeleteField(__VA_ARGS__)
    #define GetFieldAttribute(...) cb_GetFieldAttribute(__VA_ARGS__)
    #define GetField(...) cb_GetField(__VA_ARGS__)
#endif
