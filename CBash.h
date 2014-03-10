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

 /**
    @file CBash.h
    @brief This file declares the C API functions.
*/

#pragma once
// CBash.h
//#define _UNICODE
#include "MacroDefinitions.h"
#include "Collection.h"

#define COMPILING_STATIC
#ifdef COMPILING_STATIC
    #define DLLEXTERN
#else
#ifdef COMPILING_CBASH
    #define DLLEXTERN extern "C" __declspec(dllexport)
#else
    #define DLLEXTERN extern "C" __declspec(dllimport)
#endif
#endif

//Exported Functions
/**************************//**
    @name Version Functions
******************************/
///@{

/**
    @brief Get CBash's minor version number.
    @returns Cbash's major version number.
*/
DLLEXTERN UINT32 GetVersionMajor();

/**
    @brief Get CBash's minor version number.
    @returns Cbash's major version number.
*/
DLLEXTERN UINT32 GetVersionMinor();

/**
    @brief Get CBash's revision (patch) version number.
    @returns Cbash's revision (patch) version number.
*/
DLLEXTERN UINT32 GetVersionRevision();

///@}
/**************************//**
    @name Logging action functions
******************************/
///@{

/**
    @brief Register a callback function for logging messages.
    @details Register a callback function for logging messages.
    @param _LoggingCallback A pointer to a function that takes a message string argument and returns a signed 32-bit integer.
*/
DLLEXTERN void RedirectMessages(SINT32 (*_LoggingCallback)(const STRING));

/**
    @brief Register a callback function for error messages.
    @details Register a callback function for error messages.
    @param _RaiseCallback A pointer to a function that takes a message string argument and returns no value.
*/
DLLEXTERN void AllowRaising(void (*_RaiseCallback)(const STRING));

///@}
/**************************//**
    @name Collection action functions
******************************/
///@{

/**
    @brief Create a mod plugin collection.
    @details
    @param
    @param
    @returns
*/
DLLEXTERN Collection * CreateCollection(STRING const ModsPath, const UINT32 CollectionType);

/**
    @brief Delete a mod plugin collection.
    @details
    @param CollectionID The pointer to the collection to be deleted.
    @returns
*/
DLLEXTERN SINT32 DeleteCollection(Collection *CollectionID);

/**
    @brief
    @details
    @param
    @param
    @returns
*/
// Callback(position, maximum, modfile-name);
DLLEXTERN SINT32 LoadCollection(Collection *CollectionID, bool (*_ProgressCallback)(const UINT32, const UINT32, const STRING) = NULL);

/**
    @brief
    @details
    @param
    @returns
*/
DLLEXTERN SINT32 UnloadCollection(Collection *CollectionID);

/**
    @brief
    @details
    @param
    @returns
*/
DLLEXTERN SINT32 GetCollectionType(Collection *CollectionID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 UnloadAllCollections();

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 DeleteAllCollections();

///@}
/**************************//**
    @name Mod action functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN ModFile * AddMod(Collection *CollectionID, STRING const ModName, const UINT32 ModFlagsField);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 LoadMod(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 UnloadMod(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 CleanModMasters(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 SaveMod(ModFile *ModID, const UINT32 SaveFlagsField, STRING const DestinationName);

///@}
/**************************//**
    @name Mod info functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetAllNumMods(Collection *CollectionID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetAllModIDs(Collection *CollectionID, MODIDARRAY ModIDs);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetLoadOrderNumMods(Collection *CollectionID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetLoadOrderModIDs(Collection *CollectionID, MODIDARRAY ModIDs);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN STRING GetFileNameByID(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN STRING GetFileNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN STRING GetModNameByID(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN STRING GetModNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN ModFile * GetModIDByName(Collection *CollectionID, STRING const ModName);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN ModFile * GetModIDByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModLoadOrderByName(Collection *CollectionID, STRING const ModName);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModLoadOrderByID(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN ModFile * GetModIDByRecordID(Record *RecordID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN Collection * GetCollectionIDByRecordID(Record *RecordID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN Collection * GetCollectionIDByModID(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
//DLLEXTERN SINT32 GetShortIDIndex(Collection *CollectionID, const SINT32 ModID, STRING const ModName);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN UINT32 IsModEmpty(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModNumTypes(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModTypes(ModFile *ModID, UINT32ARRAY RecordTypes);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModNumEmptyGRUPs(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModNumOrphans(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetModOrphansFormIDs(ModFile *ModID, FORMIDARRAY FormIDs);

///@}
/**************************//**
    @name FormID functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN STRING GetLongIDName(Record *RecordID, const UINT32 FormID, const bool IsMGEFCode);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN UINT32 MakeShortFormID(ModFile *ModID, const UINT32 ObjectID, const bool IsMGEFCode);

///@}
/**************************//**
    @name Record action functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN Record * CreateRecord(ModFile *ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, Record *ParentID, const UINT32 CreateFlags);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN Record * CopyRecord(Record *RecordID, ModFile *DestModID, Record *DestParentID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 UnloadRecord(Record *RecordID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 ResetRecord(Record *RecordID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 DeleteRecord(Record *RecordID);

///@}
/**************************//**
    @name Record info functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN Record * GetRecordID(ModFile *ModID, const FORMID RecordFormID, STRING const RecordEditorID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetNumRecords(ModFile *ModID, const UINT32 RecordType);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetRecordIDs(ModFile *ModID, const UINT32 RecordType, RECORDIDARRAY RecordIDs);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 IsRecordWinning(Record *RecordID, const bool GetExtendedConflicts);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetNumRecordConflicts(Record *RecordID, const bool GetExtendedConflicts);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetRecordConflicts(Record *RecordID, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetRecordHistory(Record *RecordID, RECORDIDARRAY RecordIDs);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetNumIdenticalToMasterRecords(ModFile *ModID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetIdenticalToMasterRecords(ModFile *ModID, RECORDIDARRAY RecordIDs);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 IsRecordsFormIDsInvalid(Record *RecordID);

///@}
/**************************//**
    @name Mod or Record action functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 UpdateReferences(ModFile *ModID, Record *RecordID, FORMIDARRAY OldFormIDs, FORMIDARRAY NewFormIDs, UINT32ARRAY Changes, const UINT32 ArraySize);

///@}
/**************************//**
    @name Mod or Record info functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 GetRecordUpdatedReferences(Collection *CollectionID, Record *RecordID);

///@}
/**************************//**
    @name Field action functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN SINT32 SetIDFields(Record *RecordID, const FORMID FormID, STRING const EditorID);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN void   SetField(Record *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN void   DeleteField(Record *RecordID, FIELD_IDENTIFIERS);

///@}
/**************************//**
    @name Field info functions
******************************/
///@{

/**
    @brief
    @details
    @returns
*/
DLLEXTERN UINT32 GetFieldAttribute(Record *RecordID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute);

/**
    @brief
    @details
    @returns
*/
DLLEXTERN void * GetField(Record *RecordID, FIELD_IDENTIFIERS, void **FieldValues);

///@}
