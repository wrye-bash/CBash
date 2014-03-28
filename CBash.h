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
// CBash.h
//#define _UNICODE
#include "MacroDefinitions.h"


#ifdef CBASH_STATIC
    // Define CBASH_STATIC to either build or link to CBash as a static
    // library
    #define DLLEXTERN 
    #include "Collection.h"
#elif defined COMPILING_CBASH
    #define DLLEXTERN extern "C" __declspec(dllexport)
    #include "Collection.h"
#else
    // API user, just define Collection *, ModFile *, and Record * as void *
    #define DLLEXTERN extern "C" __declspec(dllimport)
    #define Collection void
    #define ModFile void
    #define Record void
#endif


//Exported Functions
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Version info functions
DLLEXTERN UINT32 GetVersionMajor();
DLLEXTERN UINT32 GetVersionMinor();
DLLEXTERN UINT32 GetVersionRevision();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Logging action functions
DLLEXTERN void RedirectMessages(SINT32 (*_LoggingCallback)(const STRING));
DLLEXTERN void AllowRaising(void (*_RaiseCallback)(const STRING));
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Collection action functions
DLLEXTERN Collection * CreateCollection(STRING const ModsPath, const UINT32 CollectionType);
DLLEXTERN SINT32 DeleteCollection(Collection *CollectionID);
// Callback(position, maximum, modfile-name);
DLLEXTERN SINT32 LoadCollection(Collection *CollectionID, bool (*_ProgressCallback)(const UINT32, const UINT32, const STRING) = NULL);
DLLEXTERN SINT32 UnloadCollection(Collection *CollectionID);
DLLEXTERN SINT32 GetCollectionType(Collection *CollectionID);
DLLEXTERN SINT32 UnloadAllCollections();
DLLEXTERN SINT32 DeleteAllCollections();
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Mod action functions
DLLEXTERN ModFile * AddMod(Collection *CollectionID, STRING const ModName, const UINT32 ModFlagsField);
DLLEXTERN SINT32 LoadMod(ModFile *ModID);
DLLEXTERN SINT32 UnloadMod(ModFile *ModID);
DLLEXTERN SINT32 CleanModMasters(ModFile *ModID);
DLLEXTERN SINT32 SaveMod(ModFile *ModID, const UINT32 SaveFlagsField, STRING const DestinationName);
////////////////////////////////////////////////////////////////////////
//Mod info functions
DLLEXTERN SINT32 GetAllNumMods(Collection *CollectionID);
DLLEXTERN SINT32 GetAllModIDs(Collection *CollectionID, MODIDARRAY ModIDs);
DLLEXTERN SINT32 GetLoadOrderNumMods(Collection *CollectionID);
DLLEXTERN SINT32 GetLoadOrderModIDs(Collection *CollectionID, MODIDARRAY ModIDs);
DLLEXTERN STRING GetFileNameByID(ModFile *ModID);
DLLEXTERN STRING GetFileNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN STRING GetModNameByID(ModFile *ModID);
DLLEXTERN STRING GetModNameByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN ModFile * GetModIDByName(Collection *CollectionID, STRING const ModName);
DLLEXTERN ModFile * GetModIDByLoadOrder(Collection *CollectionID, const UINT32 ModIndex);
DLLEXTERN SINT32 GetModLoadOrderByName(Collection *CollectionID, STRING const ModName);
DLLEXTERN SINT32 GetModLoadOrderByID(ModFile *ModID);
DLLEXTERN ModFile * GetModIDByRecordID(Record *RecordID);
DLLEXTERN Collection * GetCollectionIDByRecordID(Record *RecordID);
DLLEXTERN Collection * GetCollectionIDByModID(ModFile *ModID);
//DLLEXTERN SINT32 GetShortIDIndex(Collection *CollectionID, const SINT32 ModID, STRING const ModName);
DLLEXTERN UINT32 IsModEmpty(ModFile *ModID);
DLLEXTERN SINT32 GetModNumTypes(ModFile *ModID);
DLLEXTERN SINT32 GetModTypes(ModFile *ModID, UINT32ARRAY RecordTypes);
DLLEXTERN SINT32 GetModNumEmptyGRUPs(ModFile *ModID);
DLLEXTERN SINT32 GetModNumOrphans(ModFile *ModID);
DLLEXTERN SINT32 GetModOrphansFormIDs(ModFile *ModID, FORMIDARRAY FormIDs);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//FormID functions
DLLEXTERN STRING GetLongIDName(Record *RecordID, const UINT32 FormID, const bool IsMGEFCode);
DLLEXTERN UINT32 MakeShortFormID(ModFile *ModID, const UINT32 ObjectID, const bool IsMGEFCode);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Record action functions
DLLEXTERN Record * CreateRecord(ModFile *ModID, const UINT32 RecordType, const FORMID RecordFormID, STRING const RecordEditorID, Record *ParentID, const UINT32 CreateFlags);
DLLEXTERN Record * CopyRecord(Record *RecordID, ModFile *DestModID, Record *DestParentID, const FORMID DestRecordFormID, STRING const DestRecordEditorID, const UINT32 CreateFlags);
DLLEXTERN SINT32 UnloadRecord(Record *RecordID);
DLLEXTERN SINT32 ResetRecord(Record *RecordID);
DLLEXTERN SINT32 DeleteRecord(Record *RecordID);
////////////////////////////////////////////////////////////////////////
//Record info functions
DLLEXTERN Record * GetRecordID(ModFile *ModID, const FORMID RecordFormID, STRING const RecordEditorID);
DLLEXTERN SINT32 GetNumRecords(ModFile *ModID, const UINT32 RecordType);
DLLEXTERN SINT32 GetRecordIDs(ModFile *ModID, const UINT32 RecordType, RECORDIDARRAY RecordIDs);
DLLEXTERN SINT32 IsRecordWinning(Record *RecordID, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetNumRecordConflicts(Record *RecordID, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetRecordConflicts(Record *RecordID, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);
DLLEXTERN SINT32 GetRecordHistory(Record *RecordID, RECORDIDARRAY RecordIDs);
DLLEXTERN SINT32 GetNumIdenticalToMasterRecords(ModFile *ModID);
DLLEXTERN SINT32 GetIdenticalToMasterRecords(ModFile *ModID, RECORDIDARRAY RecordIDs);
DLLEXTERN SINT32 IsRecordsFormIDsInvalid(Record *RecordID);
////////////////////////////////////////////////////////////////////////
//Mod or Record action functions
DLLEXTERN SINT32 UpdateReferences(ModFile *ModID, Record *RecordID, FORMIDARRAY OldFormIDs, FORMIDARRAY NewFormIDs, UINT32ARRAY Changes, const UINT32 ArraySize);
////////////////////////////////////////////////////////////////////////
//Mod or Record info functions
DLLEXTERN SINT32 GetRecordUpdatedReferences(Collection *CollectionID, Record *RecordID);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//Field action functions
DLLEXTERN SINT32 SetIDFields(Record *RecordID, const FORMID FormID, STRING const EditorID);
DLLEXTERN void   SetField(Record *RecordID, FIELD_IDENTIFIERS, void *FieldValue, const UINT32 ArraySize);
DLLEXTERN void   DeleteField(Record *RecordID, FIELD_IDENTIFIERS);
////////////////////////////////////////////////////////////////////////
//Field info functions
DLLEXTERN UINT32 GetFieldAttribute(Record *RecordID, FIELD_IDENTIFIERS, const UINT32 WhichAttribute);
DLLEXTERN void * GetField(Record *RecordID, FIELD_IDENTIFIERS, void **FieldValues);
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////