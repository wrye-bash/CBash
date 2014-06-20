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
// Types.h

 /**
    @file Types.h
    @brief This file contains some type definitions and enum values used by the API.

    @details This documentation was not written by the original developer, and so may be inaccurate.
*/

#include <stddef.h>
#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Collection collection_t;
typedef struct ModFile mod_t;
typedef struct Record record_t;

typedef uint32_t FORMID;

#ifndef FIELD_IDENTIFIERS
    #define FIELD_IDENTIFIERS const uint32_t FieldID, const uint32_t ListIndex, const uint32_t ListFieldID, const uint32_t ListX2Index, const uint32_t ListX2FieldID, const uint32_t ListX3Index, const uint32_t ListX3FieldID
#endif

/**
    @brief The game types CBash can create collections for.
    @details The game type determines the file format CBash should assume when reading and writing plugin data.
*/
typedef enum {
    eIsOblivion = 0, ///< TES IV: Oblivion game type.
    eIsFallout3, ///< Fallout 3 game type.
    eIsFalloutNewVegas, ///< Fallout: New Vegas game type.
    eIsSkyrim, ///< TES V: Skyrim game type.
    eIsUnknownGameType
} whichGameTypes;

/**
    @brief Flags that specify how a plugin is to be loaded.
    @details ::fIsMinLoad and ::fIsFullLoad are exclusive. If both are set, ::fIsFullLoad takes
             priority. If neither is set, the mod isn't loaded.

             Only the following combinations are tested via Bash:
             - Normal:  (::fIsMinLoad or ::fIsFullLoad) + ::fIsInLoadOrder + ::fIsSaveable + ::fIsAddMasters + ::fIsLoadMasters
             - Dummy:    ::fIsAddMasters
             - Merged:  (::fIsMinLoad or ::fIsFullLoad) + ::fIsSkipNewRecords + ::fIsIgnoreInactiveMasters
             - Scanned: (::fIsMinLoad or ::fIsFullLoad) + ::fIsSkipNewRecords + ::fIsExtendedConflicts
*/
typedef enum {
    fIsMinLoad               = 0x00000001,  ///< Causes only the TES4 header record to be loaded.
    fIsFullLoad              = 0x00000002,  ///< Causes all records to be loaded (unless overriden by another flag).
    /**
        @brief Causes any new record to be ignored when the mod is loaded.
        @details This may leave broken records behind (such as a quest override
                 pointing to a new script that was ignored). So it shouldn't be
                 used if planning on copying records unless you check that
                 there are no new records being referenced.
    */
    fIsSkipNewRecords        = 0x00000004,
    /**
        @brief Makes the mod count towards the 255 limit and enables record creation and copying as new.
        @details If it is false, it forces Saveable to be false.
                 Any mod with new records should have this set unless you're ignoring the new records.
                 It causes the mod to be reported by GetLoadOrderNumMods(), GetLoadOrderModIDs().
    */
    fIsInLoadOrder           = 0x00000008,
    fIsSaveable              = 0x00000010,  ///< Allows the mod to be saved.
    /**
        @brief Causes the mod's masters to be added to the load order.
        @details This is essential for most mod editing functions.
    */
    fIsAddMasters            = 0x00000020,
    /**
        @brief Causes the mod's masters to be loaded into memory after being added.
        @details This has no effect if ::fIsAddMasters is false. This is
                 required if you want to lookup overridden records.
    */
    fIsLoadMasters           = 0x00000040,
    /**
        @brief Causes any conflicting records to be ignored by most functions.
        @details IsRecordWinning(), GetNumRecordConflicts(), GetRecordConflicts() will report the extended conflicts only if asked.
    */
    fIsExtendedConflicts     = 0x00000080,
    /**
        @brief Causes the loader to track which record types in a mod are new and not overrides.
        @details Increases load time per mod. It enables GetModNumTypes() and GetModTypes() for the mod.
    */
    fIsTrackNewTypes         = 0x00000100,
    /**
        @brief Causes LAND records to have extra indexing.
        @details Increases load time per mod. It allows the safe editing of
                 land records' heights. Modifying one LAND may require changes
                 in an adjacent LAND to prevent seams.
    */
    fIsIndexLANDs            = 0x00000200,
    /**
        @brief Mmoves any REFR,ACHR,ACRE records in a world cell to the actual
               cell they belong to.
        @details Increases load time per mod. Use if you're planning on
                 iterating through every placeable in a specific cell, so that
                 you don't have to check the world cell as well.
    */
    fIsFixupPlaceables       = 0x00000400,
    fIsCreateNew             = 0x00000800,  ///< Creates a new mod instead of loading an existing one.
    /**
        @brief Causes any records that override masters not in the load order to be dropped.
        @details If it is true, it forces IsAddMasters to be false.  Allows
                 mods not in load order to copy records.
    */
    fIsIgnoreInactiveMasters = 0x00001000,
    fIsSkipAllRecords        = 0x00002000,  ///< Causes all records in groups to be skipped once one of each type is read.
} modFlags;

/**
    @brief Flags that specify how a plugin is to be saved.
*/
typedef enum {
    /**
        @brief Cleans the mod's masters.
        @details Removed any unreferenced masters. Requires the mod to have
                 been loaded with the ::fIsInLoadOrder flag.
    */
    fIsCleanMasters    = 0x00000001,
    fIsCloseCollection = 0x00000002  ///< Delete the parent collection after the mod is saved.
} saveFlags;

/**
    @brief Flags that specify how a record is to be created.
*/
typedef enum {
    fSetAsOverride     = 0x00000001,  ///< Create the record as an override of the source record.
    fCopyWinningParent = 0x00000002   ///< Populate the record using data from the winning parent.
} createFlags;

#ifdef __cplusplus
}
#endif
