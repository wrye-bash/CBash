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

#include <cstdint>

#ifdef __cplusplus
extern "C"
{
#endif

typedef struct Collection cb_collection_t;
typedef struct ModFile cb_mod_t;
typedef struct Record cb_record_t;

typedef uint32_t cb_formid_t;

#ifndef FIELD_IDENTIFIERS
    #define FIELD_IDENTIFIERS const uint32_t FieldID, const uint32_t ListIndex, const uint32_t ListFieldID, const uint32_t ListX2Index, const uint32_t ListX2FieldID, const uint32_t ListX3Index, const uint32_t ListX3FieldID
#endif

/**
    @brief The game types CBash can create collections for.
    @details The game type determines the file format CBash should assume when reading and writing plugin data.
*/
typedef enum {
    CB_OBLIVION = 0, ///< TES IV: Oblivion game type.
    CB_FALLOUT3, ///< Fallout 3 game type.
    CB_FALLOUT_NEW_VEGAS, ///< Fallout: New Vegas game type.
    CB_SKYRIM, ///< TES V: Skyrim game type.
    CB_UNKNOWN_GAME_TYPE
} cb_game_type_t;

/**
    @brief Flags that specify how a plugin is to be loaded.
    @details ::CB_MIN_LOAD and ::CB_FULL_LOAD are exclusive. If both are set, ::CB_FULL_LOAD takes
             priority. If neither is set, the mod isn't loaded.

             Only the following combinations are tested via Bash:
             - Normal:  (::CB_MIN_LOAD or ::CB_FULL_LOAD) + ::CB_IN_LOAD_ORDER + ::CB_SAVEABLE + ::CB_ADD_MASTERS + ::CB_LOAD_MASTERS
             - Dummy:    ::CB_ADD_MASTERS
             - Merged:  (::CB_MIN_LOAD or ::CB_FULL_LOAD) + ::CB_SKIP_NEW_RECORDS + ::CB_IGNORE_INACTIVE_MASTERS
             - Scanned: (::CB_MIN_LOAD or ::CB_FULL_LOAD) + ::CB_SKIP_NEW_RECORDS + ::CB_EXTENDED_CONFLICTS
*/
typedef enum {
    CB_MIN_LOAD               = 0x00000001,  ///< Causes only the TES4 header record to be loaded.
    CB_FULL_LOAD              = 0x00000002,  ///< Causes all records to be loaded (unless overridden by another flag).
    /**
        @brief Causes any new record to be ignored when the mod is loaded.
        @details This may leave broken records behind (such as a quest override
                 pointing to a new script that was ignored). So it shouldn't be
                 used if planning on copying records unless you check that
                 there are no new records being referenced.
    */
    CB_SKIP_NEW_RECORDS        = 0x00000004,
    /**
        @brief Makes the mod count towards the 255 limit and enables record creation and copying as new.
        @details If it is false, it forces Saveable to be false.
                 Any mod with new records should have this set unless you're ignoring the new records.
                 It causes the mod to be reported by cb_GetLoadOrderNumMods(), cb_GetLoadOrderModIDs().
    */
    CB_IN_LOAD_ORDER           = 0x00000008,
    CB_SAVEABLE              = 0x00000010,  ///< Allows the mod to be saved.
    /**
        @brief Causes the mod's masters to be added to the load order.
        @details This is essential for most mod editing functions.
    */
    CB_ADD_MASTERS            = 0x00000020,
    /**
        @brief Causes the mod's masters to be loaded into memory after being added.
        @details This has no effect if ::CB_ADD_MASTERS is false. This is
                 required if you want to lookup overridden records.
    */
    CB_LOAD_MASTERS           = 0x00000040,
    /**
        @brief Causes any conflicting records to be ignored by most functions.
        @details cb_IsRecordWinning(), cb_GetNumRecordConflicts(), cb_GetRecordConflicts() will report the extended conflicts only if asked.
    */
    CB_EXTENDED_CONFLICTS     = 0x00000080,
    /**
        @brief Causes the loader to track which record types in a mod are new and not overrides.
        @details Increases load time per mod. It enables cb_GetModNumTypes() and cb_GetModTypes() for the mod.
    */
    CB_TRACK_NEW_TYPES         = 0x00000100,
    /**
        @brief Causes LAND records to have extra indexing.
        @details Increases load time per mod. It allows the safe editing of
                 land records' heights. Modifying one LAND may require changes
                 in an adjacent LAND to prevent seams.
    */
    CB_INDEX_LANDS            = 0x00000200,
    /**
        @brief Mmoves any REFR,ACHR,ACRE records in a world cell to the actual
               cell they belong to.
        @details Increases load time per mod. Use if you're planning on
                 iterating through every placeable in a specific cell, so that
                 you don't have to check the world cell as well.
    */
    CB_FIXUP_PLACEABLES       = 0x00000400,
    CB_CREATE_NEW             = 0x00000800,  ///< Creates a new mod instead of loading an existing one.
    /**
        @brief Causes any records that override masters not in the load order to be dropped.
        @details If it is true, it forces IsAddMasters to be false.  Allows
                 mods not in load order to copy records.
    */
    CB_IGNORE_INACTIVE_MASTERS = 0x00001000,
    CB_SKIP_ALL_RECORDS        = 0x00002000,  ///< Causes all records in groups to be skipped once one of each type is read.
} cb_mod_flags_t;

/**
    @brief Flags that specify how a plugin is to be saved.
*/
typedef enum {
    /**
        @brief Cleans the mod's masters.
        @details Removed any unreferenced masters. Requires the mod to have
                 been loaded with the ::CB_IN_LOAD_ORDER flag.
    */
    CB_CLEAN_MASTERS    = 0x00000001,
    CB_CLOSE_COLLECTION = 0x00000002  ///< Delete the parent collection after the mod is saved.
} cb_save_flags_t;

/**
    @brief Flags that specify how a record is to be created.
*/
typedef enum {
    CB_SET_AS_OVERRIDE     = 0x00000001,  ///< Create the record as an override of the source record.
    CB_COPY_WINNING_PARENT = 0x00000002   ///< Populate the record using data from the winning parent.
} cb_create_flags_t;

/**
    @brief Flags that specify the type of a field.
*/
typedef enum {
    CB_UNKNOWN_FIELD = 0,  ///< Data of an unknown type.
    CB_MISSING_FIELD,  ///< The field is missing. Used for some fields that are not quite universal, eg. Editor IDs.
    CB_JUNK_FIELD,  ///< Junk data of unknown type.
    CB_BOOL_FIELD,  ///< A boolean value.
    CB_SINT8_FIELD,  ///< An 8-bit signed integer.
    CB_UINT8_FIELD,  ///< An 8-bit unsigned integer.
    CB_SINT16_FIELD,  ///< A 16-bit signed integer.
    CB_UINT16_FIELD,  ///< A 16-bit unsigned integer.
    CB_SINT32_FIELD,  ///< A 32-bit signed integer.
    CB_UINT32_FIELD,  ///< A 32-bit unsigned integer.
    CB_FLOAT32_FIELD,  ///< A 32-bit floating point value.
    CB_RADIAN_FIELD,  ///< A 32-bit floating point value that should be interpreted as an angle measured in radians.
    CB_FORMID_FIELD,  ///< A 32-bit unsigned integer that should be interpreted as a FormID.
    CB_MGEFCODE_FIELD,  ///< A 32-bit unsigned integer that should be interpreted as an MGEF code.
    CB_ACTORVALUE_FIELD,  ///< A 32-bit unsigned integer that should be interpreted as an actor value.
    CB_FORMID_OR_UINT32_FIELD,  ///< A 32-bit unsigned integer that may be a FormID or not.
    CB_FORMID_OR_FLOAT32_FIELD,  ///< A FormID or a 32-bit floating point value.
    CB_UINT8_OR_UINT32_FIELD,  ///< An 8-bit or 32-bit unsigned integer.
    CB_FORMID_OR_STRING_FIELD,  ///< A FormID or a C string.
    CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD,  ///< A FormID, a 32-bit unsigned integer, or some unknown type.
    CB_UNKNOWN_OR_SINT32_FIELD,  ///< A 32-bit signed integer, or some unknown type.
    CB_UNKNOWN_OR_UINT32_FLAG_FIELD,  ///< 32 bits of bit flag values, or some unknown type.
    CB_MGEFCODE_OR_CHAR4_FIELD,  ///< An MGEF code or 4 8-bit characters.
    CB_FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_FIELD,  ///< A FormID, an MGEF code, an actor value or a 32-bit unsigned integer.
    CB_RESOLVED_MGEFCODE_FIELD,  ///< A mod-added MGEF code.
    CB_STATIC_MGEFCODE_FIELD,  ///< A standard MGEF code.
    CB_RESOLVED_ACTORVALUE_FIELD,  ///< A mod-added actor value.
    CB_STATIC_ACTORVALUE_FIELD,  ///< A standard actor value.
    CB_CHAR_FIELD,  ///< An 8-bit character.
    CB_CHAR4_FIELD,  ///< 4 8-bit characters.
    CB_STRING_FIELD,  ///< A C string.
    CB_ISTRING_FIELD,  ///< A C string that is handled case-insensitively by CBash.
    CB_STRING_OR_FLOAT32_OR_SINT32_FIELD,  ///< A C string, 32-bit floating point value, or 32-bit signed integer.
    CB_LIST_FIELD,  ///< The field is actually a list of fields.
    CB_PARENTRECORD_FIELD,  ///< A parent record of the current record. Eg. each `DIAL` record can have `INFO` record children.
    CB_SUBRECORD_FIELD,  ///< A child record associated with the current record (which is the parent). Eg. each `INFO` record is a child of a `DIAL` record.
    CB_SINT8_FLAG_FIELD,  ///< Unused.
    CB_SINT8_TYPE_FIELD,  ///< An 8-bit signed integer that should be interpreted as some enum value.
    CB_SINT8_FLAG_TYPE_FIELD,  ///< Unused.
    CB_SINT8_ARRAY_FIELD,  ///< Unused.
    CB_UINT8_FLAG_FIELD,  ///< 8 bits of bit flag values.
    CB_UINT8_TYPE_FIELD,  ///< An 8-bit unsigned integer that should be interpreted as some enum value.
    CB_UINT8_FLAG_TYPE_FIELD,  ///< An 8-bit unsigned integer that is either a collection of bit flag values or some enum value.
    CB_UINT8_ARRAY_FIELD,  ///< An array of 8-bit unsigned integers.
    CB_SINT16_FLAG_FIELD,  ///< Unused.
    CB_SINT16_TYPE_FIELD,  ///< Unused.
    CB_SINT16_FLAG_TYPE_FIELD,  ///< Unused.
    CB_SINT16_ARRAY_FIELD,  ///< An array of 16-bit unsigned integers.
    CB_UINT16_FLAG_FIELD,  ///< 16 bits of bit flag values.
    CB_UINT16_TYPE_FIELD,  ///< A 16-bit unsigned integer that should be interpreted as some enum value.
    CB_UINT16_FLAG_TYPE_FIELD,  ///< Unused.
    CB_UINT16_ARRAY_FIELD,  ///< Unused.
    CB_SINT32_FLAG_FIELD,  ///< Unused.
    CB_SINT32_TYPE_FIELD,  ///< A 32-bit signed integer that should be interpreted as some enum value.
    CB_SINT32_FLAG_TYPE_FIELD,  ///< Unused.
    CB_SINT32_ARRAY_FIELD,  ///< Unused.
    CB_UINT32_FLAG_FIELD,  ///< 32 bits of bit flag values.
    CB_UINT32_TYPE_FIELD,  ///< A 32-bit unsigned integer that should be interpreted as some enum value.
    CB_UINT32_FLAG_TYPE_FIELD,  ///< Unused.
    CB_UINT32_ARRAY_FIELD,  ///< An array of 32-bit unsigned integers.
    CB_FLOAT32_ARRAY_FIELD,  ///< Unused.
    CB_RADIAN_ARRAY_FIELD,  ///< Unused.
    CB_FORMID_ARRAY_FIELD,  ///< An array of FormIDs.
    CB_FORMID_OR_UINT32_ARRAY_FIELD,  ///< An array of FormIDs or 32-bit unsigned integers.
    CB_MGEFCODE_OR_UINT32_ARRAY_FIELD,  ///< An array of MGEF codes or 32-bit unsigned integers.
    CB_STRING_ARRAY_FIELD,  ///< Unused.
    CB_ISTRING_ARRAY_FIELD,  ///< An array of C strings that are handled case-insensitively by CBash.
    CB_SUBRECORD_ARRAY_FIELD,  ///< An array of records that are children associated with the current record (which is their parent). Eg. each `DIAL` record can have `INFO` record children.
    CB_UNDEFINED_FIELD  ///< Unused.
} cb_field_type_t;

#ifdef __cplusplus
}
#endif
