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
    #define DLLEXPORT extern "C" __declspec(dllexport)
    #define DLLIMPORT extern "C" __declspec(dllimport)
#else
    #define DLLEXPORT __declspec(dllexport)
    #define DLLIMPORT __declspec(dllimport)
#endif


// Setup some defines/includes for use in CBash.h/.cpp
#ifdef CBASH_STATIC
    #define DLLEXTERN
    #define CPPDLLEXTERN
#elif defined COMPILING_CBASH
    #define DLLEXTERN DLLEXPORT
    #define CPPDLLEXTERN DLLEXPORT
    // Also, link against the Boost zlib library
    #if !defined(CBASH_NO_BOOST_ZLIB)
        #define BOOST_LIB_NAME "boost_zlib"
        #include <boost/config/auto_link.hpp>
    #else
        // Cleanup
        #undef CBASH_NO_BOOST_ZLIB
    #endif
#elif defined CBASH_DLL
    // Not compiling, just an API user of the DLL
    #define DLLEXTERN DLLIMPORT
#endif
