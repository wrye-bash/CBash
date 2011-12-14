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
// Collection.h
#include "ModFile.h"
#include "Oblivion/TES4File.h"
#include "FalloutNewVegas/FNVFile.h"
#include "Skyrim/TES5File.h"
#include <vector>
#include <map>
#include "Visitors.h"

//class SortedRecords
//    {
//    public:
//        UINT32 size;
//        Record ** records;
//
//        SortedRecords();
//        ~SortedRecords();
//
//	    void push_back(Record *&record);
//	    void erase(UINT32 &index);
//    };

//struct IndexedRecords
//    {
//    SortedRecords loadordered, extended;
//    };

//typedef std::map<FORMID, SortedRecords>   FormID_Map;
//typedef std::map<STRING, SortedRecords, sameStr> EditorID_Map;
//
//typedef FormID_Map::iterator FormID_Iterator;
//typedef EditorID_Map::iterator EditorID_Iterator;

class Collection
    {
    private:
        STRING ModsDir;
        bool IsLoaded;
        std::vector<Record *> sortedConflicts;

    public:
        whichGameTypes CollectionType;

        std::vector<ModFile *> ModFiles;
        std::vector<ModFile *> LoadOrder255;
        std::vector<FormIDResolver *> Expanders;

        EditorID_Map EditorID_ModFile_Record;
        FormID_Map FormID_ModFile_Record;

        EditorID_Map ExtendedEditorID_ModFile_Record;
        FormID_Map ExtendedFormID_ModFile_Record;

        boost::unordered_set<Record *> identical_records;
        boost::unordered_set<Record *> changed_records;
        std::vector<GenericOp *> closing_ops;

	boost::unordered_set<UINT32> filter_records;
	boost::unordered_set<FORMID> filter_wspaces;
	bool filter_inclusive;

        Collection(STRING const &ModsPath, UINT32 _CollectionType);
        ~Collection();

        ModFile * AddMod(STRING const &_FileName, ModFlags &flags, bool IsPreloading=false);
        ModFile * IsModAdded(STRING const &ModName);
        SINT32 SaveMod(ModFile *&curModFile, SaveFlags &flags, STRING const DestinationName);

	void SetFilterMode(bool inclusive);
	void AddRecordFilter(UINT32 recordtype);
	void AddWSpaceFilter(FORMID worldspace);
	void ResetFilter();

	// Callback(position, maximum, modfile-name);
        SINT32 Load(bool (*_ProgressCallback)(const UINT32, const UINT32, const STRING) = NULL);
        void   UndeleteRecords(std::vector<std::pair<ModFile *, std::vector<Record *> > > &DeletedRecords);
        SINT32 Unload();

        FormID_Iterator LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord);
        EditorID_Iterator LookupRecord(ModFile *&curModFile, STRING const &RecordEditorID, Record *&curRecord);
        FormID_Iterator LookupWinningRecord(const FORMID &RecordFormID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts=false);
        EditorID_Iterator LookupWinningRecord(STRING const &RecordEditorID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts=false);

        UINT32 GetNumRecordConflicts(Record *&curRecord, const bool GetExtendedConflicts);
        SINT32 GetRecordConflicts(Record *&curRecord, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts);
        SINT32 GetRecordHistory(Record *&curRecord, RECORDIDARRAY RecordIDs);

        UINT32 NextFreeExpandedFormID(ModFile *&curModFile, UINT32 depth = 0);
        Record * CreateRecord(ModFile *&curModFile, const UINT32 &RecordType, FORMID RecordFormID, STRING const &RecordEditorID, const FORMID &ParentFormID, UINT32 CreateFlags);
        Record * CopyRecord(Record *&curRecord, ModFile *&DestModFile, const FORMID &DestParentFormID, FORMID DestRecordFormID, STRING const &DestRecordEditorID, UINT32 CreateFlags);
        SINT32 CleanModMasters(ModFile *curModFile);

        SINT32 SetIDFields(Record *&RecordID, FORMID FormID, STRING const &EditorID);
    };

class RecordReader : public RecordOp
    {
    private:
        FormIDResolver expander;
        std::vector<FormIDResolver *> &Expanders;

    public:
        RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        RecordReader(Record *RecordID);
        RecordReader(ModFile *ModID);
        ~RecordReader();

        bool Accept(Record *&curRecord);
    };

class RecordInvalidFormIDChecker : public RecordOp
    {
    private:
        class InvalidFormIDChecker : public FormIDOp
            {
            public:
                InvalidFormIDChecker();
                ~InvalidFormIDChecker();

                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } checker;

    public:
        RecordInvalidFormIDChecker();
        ~RecordInvalidFormIDChecker();

        bool Accept(Record *&curRecord);
    };

class RecordDeindexer : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
        FormID_Map &FormID_ModFile_Record;

    public:
        RecordDeindexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map);
        RecordDeindexer(Record *RecordID);
        RecordDeindexer(ModFile *ModID);
        ~RecordDeindexer();

        bool Accept(Record *&curRecord);
    };

class IdenticalToMasterRetriever : public RecordOp
    {
    private:
        EditorID_Map &EditorID_ModFile_Record;
        FormID_Map &FormID_ModFile_Record;
        const UINT8 &MasterIndex;
        boost::unordered_set<Record *> &identical_records;
        std::vector<FormIDResolver *> &Expanders;

        RecordReader reader;

    public:
        IdenticalToMasterRetriever(ModFile *ModID);
        ~IdenticalToMasterRetriever();

        bool Accept(Record *&curRecord);
    };

class RecordFormIDSwapper : public RecordOp
    {
    private:
        FormIDSwapper swapper;
        RecordReader reader;

    public:
        RecordFormIDSwapper(const UINT32 &_FormIDToMatch, const UINT32 &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordFormIDSwapper();

        bool Accept(Record *&curRecord);
    };

class RecordFormIDMapper : public RecordOp
    {
    private:
        class FormIDMapper : public FormIDOp
            {
            private:
                std::map<FORMID, std::vector<Record *> > &formID_users;

            public:
                Record *curRecord;

                FormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users);
                ~FormIDMapper();

                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } mapper;

        RecordReader reader;

    public:
        RecordFormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordFormIDMapper();

        bool Accept(Record *&curRecord);
    };

class RecordMasterCollector : public RecordOp
    {
    private:
        RecordReader reader;

    public:
        class FormIDMasterCollector : public FormIDOp
            {
            public:
                UINT8 UsedTable[256];
                UINT8 (&CollapseTable)[256];

                FormIDMasterCollector(UINT8 (&CollapseTable)[256]);
                ~FormIDMasterCollector();

                bool Accept(UINT32 &curFormID);
                bool AcceptMGEF(UINT32 &curMgefCode);
            } collector;

        RecordMasterCollector(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordMasterCollector();

        bool Accept(Record *&curRecord);
    };

class RecordChanger : public RecordOp
    {
    private:
        RecordReader reader;

    public:
        RecordChanger(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders);
        ~RecordChanger();

        bool Accept(Record *&curRecord);
    };