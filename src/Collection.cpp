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
// Collection.cpp
#include "Collection.h"
#include <direct.h>
//#include <boost/threadpool.hpp>

//SortedRecords::SortedRecords():
//    size(0),
//    records(NULL)
//    {
//    //
//    }
//
//SortedRecords::~SortedRecords()
//    {
//    delete []records;
//    }
//
//void SortedRecords::push_back(ModFile *&mod, Record *&record)
//    {
//    Record ** temp_records = new Record *[size + 1];
//    bool placed = false;
//    for(uint32_t x = 0, y = 0; x < size; ++y)
//        {
//        if(!placed && records[x]->GetParentMod()->ModID > record->GetParentMod()->ModID)
//            {
//            placed = true;
//            temp_records[y] = record;
//            }
//        else
//            {
//            temp_records[y] = records[x];
//            ++x;
//            }
//        }
//    if(!placed)
//        temp_records[size] = record;
//    size++;
//    delete []records;
//    records = temp_records;
//    }
//
//void SortedRecords::erase(uint32_t &index)
//    {
//    Record ** temp_records = new Record *[size - 1];
//    for(uint32_t x = 0, y = 0; x < size; ++x)
//        {
//        if(x == index)
//            continue;
//        temp_records[y] = records[x];
//        ++y;
//        }
//    size--;
//    delete []records;
//    records = temp_records;
//    }

bool compHistory(Record *&lhs, Record *&rhs)
    {
    return lhs->GetParentMod()->ModID < rhs->GetParentMod()->ModID;
    }

bool compConflicts(Record *&lhs, Record *&rhs)
    {
    return lhs->GetParentMod()->ModID > rhs->GetParentMod()->ModID;
    }

bool sortMod(ModFile *lhs, ModFile *rhs)
    {
    //Esp's sort after esm's
    //Non-existent esms sort before existing esps
    //Non-existent esms retain their relative load order
    //Existing esps sort by modified date
    //Non-existent esps sort before existing esps
    //Non-existent esps retain their relative load order
    //New esps load last
    #ifndef LHS_BEFORE_RHS
        #define LHS_BEFORE_RHS true
        #define LHS_AFTER_RHS false
    #endif

    const time_t MIN_TIME = std::numeric_limits<time_t>::min();
    const time_t MAX_TIME = std::numeric_limits<time_t>::max();

    bool leftEsm = lhs->TES4.IsESM();
    bool rightEsm = rhs->TES4.IsESM();

    bool leftNew = (lhs->ModTime == 0) || lhs->Flags.IsCreateNew;
    bool rightNew = (rhs->ModTime == 0) || rhs->Flags.IsCreateNew;

    time_t leftTime = leftNew ? MAX_TIME : lhs->ModTime;
    time_t rightTime = rightNew ? MAX_TIME : rhs->ModTime;

    if (leftEsm != rightEsm)
        {
            return leftEsm ? LHS_BEFORE_RHS : LHS_AFTER_RHS;
        }
    else if (leftNew != rightNew)
        {
            return leftNew ? LHS_AFTER_RHS : LHS_BEFORE_RHS;
        }
    else 
        // They are in the same "partition", strict ordering applies within each
        {
            return leftTime < rightTime;
        }

    // should never reach here, but not important enough to assert IMO.
    return LHS_BEFORE_RHS;
    }

Collection::Collection(char * const &ModsPath, uint32_t _CollectionType):
    ModsDir(NULL),
    IsLoaded(false),
    CollectionType(),
    identical_records(),
    changed_records(),
    filter_records(),
    filter_wspaces(),
    filter_inclusive(false)
    {
    if (_CollectionType >= CB_UNKNOWN_GAME_TYPE)
        throw std::exception("CreateCollection: Error - Unable to create the collection. Invalid collection type specified.\n");
    CollectionType = (cb_game_type_t)_CollectionType;
    ModsDir = new char[strlen(ModsPath)+1];
    strcpy_s(ModsDir, strlen(ModsPath)+1, ModsPath);
    }

Collection::~Collection()
    {
    delete []ModsDir;
    for(uint32_t p = 0; p < ModFiles.size(); p++)
        delete ModFiles[p];
    for(uint32_t p = 0; p < Expanders.size(); p++)
        delete Expanders[p];
    //LoadOrder255 is shared with ModFiles, so no deleting
    }

void Collection::SetFilterMode(bool inclusive) {
    filter_inclusive = inclusive;
}

void Collection::AddRecordFilter(uint32_t recordtype) {
    filter_records.insert(recordtype);
}

void Collection::AddWSpaceFilter(FORMID worldspace) {
    filter_wspaces.insert(worldspace);
}

void Collection::ResetFilter() {
    filter_records.clear();
    filter_wspaces.clear();
}

ModFile * Collection::AddMod(char * const &_FileName, ModFlags &flags, bool IsPreloading)
    {
    _chdir(ModsDir);
    //Mods may not be added after collection is loaded.
    //Prevent loading mods more than once

    char * ModName = DeGhostModName(_FileName);
    ModFile *ModID = IsModAdded(ModName ? ModName : _FileName);
    if(ModID != NULL)
        {
        //Suppress any warnings if masters are being loaded, or if the mod is being added with the same flags as before
        if(IsPreloading || ModID->Flags.GetFlags() == flags.GetFlags())
            {
            delete []ModName;
            return IsPreloading ? NULL : ModID;
            }
        printer("AddMod: Warning - Unable to add mod \"%s\". It already exists in the collection.\n", ModName ? ModName : _FileName);
        delete []ModName;
        return NULL;
        }

    if(IsLoaded)
        {
        if(!IsPreloading)
            printer("AddMod: Error - Unable to add mod \"%s\". The collection has already been loaded.\n", ModName ? ModName : _FileName);
        delete []ModName;
        return NULL;
        }

    char * FileName = new char[strlen(_FileName) + 1];
    strcpy_s(FileName, strlen(_FileName) + 1, _FileName);
    ModName = ModName ? ModName : FileName;

    switch(CollectionType)
        {
        case CB_OBLIVION:
            ModFiles.push_back(new TES4File(this, FileName, ModName, flags.GetFlags()));
            ModFiles.back()->TES4.whichGame = CB_OBLIVION;
            break;
        case CB_FALLOUT3:
            printer("AddMod: Error - Unable to add mod \"%s\". Fallout 3 mod support is unimplemented.\n", ModName);
            delete []ModName;
            return NULL;
        case CB_FALLOUT_NEW_VEGAS:
            ModFiles.push_back(new FNVFile(this, FileName, ModName, flags.GetFlags()));
            ModFiles.back()->TES4.whichGame = CB_FALLOUT_NEW_VEGAS;
            break;
        case CB_SKYRIM:
            ModFiles.push_back(new TES5File(this, FileName, ModName, flags.GetFlags()));
            ModFiles.back()->TES4.whichGame = CB_SKYRIM;
            break;
        default:
            printer("AddMod: Error - Unable to add mod \"%s\". Invalid collection type.\n", ModName);
            delete []ModName;
            return NULL;
        }
    return ModFiles.back();
    }

ModFile * Collection::IsModAdded(char * const &ModName)
    {
    for(uint32_t p = 0;p < ModFiles.size();p++)
        if(icmps(ModName, ModFiles[p]->ModName) == 0)
            return ModFiles[p];
    return NULL;
    }

int32_t Collection::SaveMod(ModFile *&curModFile, SaveFlags &flags, char * const DestinationName)
    {
    if(!curModFile->Flags.IsSaveable)
        {
        printer("SaveMod: Error - Unable to save mod \"%s\". It is flagged as being non-saveable.\n", curModFile->ModName);
        return -1;
        }

    if(flags.IsCloseCollection)
        {
        //clear up some memory
        EditorID_ModFile_Record.clear();
        FormID_ModFile_Record.clear();
        ExtendedEditorID_ModFile_Record.clear();
        ExtendedFormID_ModFile_Record.clear();
        }

    if(flags.IsCleanMasters)
        CleanModMasters(curModFile);

    //Some records (WRLD->CELL) may be created during the save process if necessary
    RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);

    _chdir(ModsDir);

    char * temp_name = GetTemporaryFileName(DestinationName != NULL ? DestinationName : curModFile->ModName); //deleted when RenameOp is destroyed

    //Save the mod to temp file
    curModFile->Save(temp_name, Expanders, flags.IsCloseCollection, indexer);
    //Delay renaming temp file to original filename until collection is closed
    //This way the file mapping can remain open and the entire file doesn't have to be loaded into memory
    closing_ops.push_back(new RenameOp(temp_name, DestinationName != NULL ? DestinationName : curModFile->FileName));
    return 0;
    }

int32_t Collection::Load(bool (*_ProgressCallback)(const uint32_t, const uint32_t, const char *))
    {
    ModFile *curModFile = NULL;
    RecordIndexer indexer(EditorID_ModFile_Record, FormID_ModFile_Record);
    RecordIndexer extended_indexer(ExtendedEditorID_ModFile_Record, ExtendedFormID_ModFile_Record);
    bool Preloading = false;
    std::vector<std::pair<ModFile *, std::vector<Record *> > > DeletedRecords;

    if(IsLoaded)
        {
        printer("Load: Warning - Unable to load collection. It is already loaded.\n");
        return 0;
        }
    try
        {
        _chdir(ModsDir);
        //Brute force approach to loading all masters
        //Could be done more elegantly with recursion
        //printer("Before Preloading\n");
        do {
            Preloading = false;
            for(uint32_t p = 0; p < (uint32_t)ModFiles.size(); ++p)
                {
                curModFile = ModFiles[p];
                curModFile->LoadTES4();
                if(!curModFile->Flags.IsCreateNew && curModFile->Flags.IsAddMasters)
                    {
                    //Any new mods loaded this way inherit their flags
                    ModFlags preloadFlags(curModFile->Flags.GetFlags());
                    preloadFlags.IsNoLoad = !curModFile->Flags.IsLoadMasters;
                    for(uint8_t x = 0; x < curModFile->TES4.MAST.size(); ++x)
                        Preloading = (AddMod(curModFile->TES4.MAST[x], preloadFlags, true) != NULL || Preloading);
                    }
                }
        }while(Preloading);
        //printer("Load order before sort\n");
        //for(uint32_t x = 0; x < ModFiles.size(); ++x)
        //    printer("%02X: %s\n", x, ModFiles[x]->FileName);
        //printer("\n");
        std::_Insertion_sort_unchecked(ModFiles.begin(), ModFiles.end(), sortMod);
        std::vector<char *> strLoadOrder255;
        std::vector<char *> strTempLoadOrder;
        std::vector< std::vector<char *> > strAllLoadOrder;
        LoadOrder255.clear(); //shouldn't be needed
        //printer("Load order:\n");
        for(uint32_t p = 0; p < (uint32_t)ModFiles.size(); ++p)
            {
            curModFile = ModFiles[p];
            curModFile->ModID = p;
            //printer("ModID %02X: %s", p, curModFile->FileName);
            if(curModFile->Flags.IsInLoadOrder)
                {
                if(LoadOrder255.size() >= 255)
                    throw std::exception("Tried to load more than 255 mods.");
                LoadOrder255.push_back(curModFile);
                strLoadOrder255.push_back(curModFile->ModName);
                //printer(" , OrderID %02X", LoadOrder255.size() - 1);
                }
            else if(!curModFile->Flags.IsIgnoreInactiveMasters) //every mod not in the std load order exists as if it and its masters are the only ones loaded
                {//No need to sort since the masters should be in order well enough
                for(uint8_t x = 0; x < curModFile->TES4.MAST.size(); ++x)
                    strTempLoadOrder.push_back(curModFile->TES4.MAST[x]);
                strAllLoadOrder.push_back(strTempLoadOrder);
                strTempLoadOrder.clear();
                }
            //printer("\n");
            }
        //printer("Load Set\n");
        uint8_t expandedIndex = 0;
        uint32_t x = 0;

        for(uint32_t p = 0; p < (uint32_t)ModFiles.size(); ++p)
        {
            curModFile = ModFiles[p];

            if(_ProgressCallback && !(*_ProgressCallback)(p, (uint32_t)ModFiles.size() - 1, curModFile->FileName))
            {
                /* TODO: clean abort */
            }

            RecordReader read_parser(curModFile);
            //Loads GRUP and Record Headers.  Fully loads GMST records.
            curModFile->FormIDHandler.SetLoadOrder((curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters) ? strLoadOrder255 : strAllLoadOrder[x++]);
            //VHDPRINT(curModFile->Flags.IsSkipNewRecords ? 0xFF : curModFile->Flags.IsInLoadOrder ? expandedIndex : (uint8_t)curModFile->TES4.MAST.size());
            curModFile->FormIDHandler.CreateFormIDLookup(curModFile->Flags.IsSkipNewRecords ? 0xFF :
                                                         curModFile->Flags.IsInLoadOrder ? expandedIndex++ :
                                                         (uint8_t)curModFile->TES4.MAST.size());
            Expanders.push_back(new FormIDResolver(curModFile->FormIDHandler.ExpandTable, curModFile->FormIDHandler.FileStart, curModFile->FormIDHandler.FileEnd));
            DeletedRecords.push_back(std::make_pair(curModFile, std::vector<Record *>()));
            RecordIndexer &used_indexer = curModFile->Flags.IsExtendedConflicts ? extended_indexer : indexer;
            used_indexer.SetModFile(curModFile);
            curModFile->SetFilter(filter_inclusive, filter_records, filter_wspaces);
            curModFile->Load(read_parser, used_indexer, Expanders, DeletedRecords.back().second);
        }
        //printer("Loaded\n");
        strAllLoadOrder.clear();
        UndeleteRecords(DeletedRecords);
        IsLoaded = true;
        }
    catch(...)
        {
        IsLoaded = false;
        throw;
        }
    return 0;
    }

void Collection::UndeleteRecords(std::vector<std::pair<ModFile *, std::vector<Record *> > > &DeletedRecords)
    {
    //Deleted records are only composed of their header. All of their data is missing.
    //This makes undeleting a record a bit tricky since you can't just toggle the records IsDeleted flag.
    //This function tries to restore the data of all deleted records so that toggling the IsDeleted flag works as expected.
    //It goes through the mod's masters, and uses the data from the newest record that hasn't been deleted.
    //It is typically unable to restore the data to deleted injected records
    Record *curRecord = NULL;
    ModFile *curModFile = NULL;
    Record *WinningRecord = NULL;
    ModFile *WinningModFile = NULL;
    int32_t ModID = -1;
    for(uint32_t ListIndex = 0; ListIndex < DeletedRecords.size(); ++ListIndex)
        {
        curModFile = DeletedRecords[ListIndex].first;
        std::vector<Record *> &curRecords = DeletedRecords[ListIndex].second;
        if(!curModFile->Flags.IsLoadMasters || !curModFile->Flags.IsInLoadOrder ||
            curModFile->Flags.IsExtendedConflicts || curModFile->Flags.IsIgnoreInactiveMasters)
            {
            curRecords.clear();
            continue;
            }
        uint8_t &CollapsedIndex = curModFile->FormIDHandler.CollapsedIndex;
        const uint8_t (&CollapseTable)[256] = curModFile->FormIDHandler.CollapseTable;

        for(uint32_t z = 0; z < curRecords.size(); ++z)
            {
            ModID = -1;
            curRecord = curRecords[z];
            WinningRecord = NULL;

            if(curRecord->IsKeyedByEditorID())
                {
                //This is problematic because the EditorID will have been deleted.
                //The only recourse is to try and find its match by FormID (which isn't 100% reliable)
                //Luckily, these records should almost never be marked as deleted, so efficiency isn't a concern
                char * RecordEditorID = NULL;
                for(EditorID_Iterator it = EditorID_ModFile_Record.begin(); it != EditorID_ModFile_Record.end(); ++it)
                    if(it->second->formID == curRecord->formID)
                        {
                        RecordEditorID = it->second->GetEditorIDKey();
                        //DPRINT("%s recovered", RecordEditorID);
                        break;
                        }

                if(RecordEditorID != NULL)
                    {
                    for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                        {
                        WinningModFile = range.first->second->GetParentMod();
                        if((int32_t)WinningModFile->ModID > ModID && (WinningModFile->Flags.IsInLoadOrder || WinningModFile->Flags.IsIgnoreInactiveMasters))
                            //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                            // that means the mod has that other mod as a master.
                            if(CollapseTable[WinningModFile->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                                {
                                if(range.first->second->IsDeleted() == false)
                                    {
                                    ModID = WinningModFile->ModID;
                                    WinningRecord = range.first->second;
                                    }
                                }
                        }
                    }
                if(WinningRecord != NULL)
                    EditorID_ModFile_Record.insert(std::make_pair(RecordEditorID,curRecord));
                }
            else
                {
                for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                    {
                    WinningModFile = range.first->second->GetParentMod();
                    if((int32_t)WinningModFile->ModID > ModID && (WinningModFile->Flags.IsInLoadOrder || WinningModFile->Flags.IsIgnoreInactiveMasters))
                        //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                        // that means the mod has that other mod as a master.
                        if(CollapseTable[WinningModFile->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                            {
                            if(range.first->second->IsDeleted() == false)
                                {
                                ModID = WinningModFile->ModID;
                                WinningRecord = range.first->second;
                                }
                            }
                    }
                }
            if(WinningRecord != NULL)
                curRecord->recData = WinningRecord->recData;
            else
                {
                //Deleted injected record?
                RecordDeindexer deindexer(curRecord);
                curRecord->GetParentMod()->DeleteRecord(curRecord, deindexer);
                //printer("Load: Warning - Unable to undelete record %08X in \"%s\". Was not able to determine its source record.\n", curRecord->formID, curModFile->FileName);
                }
            }
        }
    }

int32_t Collection::Unload()
    {
    RecordUnloader unloader;
    for(uint32_t ListIndex = 0; ListIndex < ModFiles.size(); ++ListIndex)
        ModFiles[ListIndex]->VisitAllRecords(unloader);
    return 0;
    }

FormID_Iterator Collection::LookupRecord(ModFile *&curModFile, const FORMID &RecordFormID, Record *&curRecord)
    {
    for(FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(RecordFormID) : FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        if(curRecord->GetParentMod() == curModFile)
            return range.first;
        }
    curRecord = NULL;
    return curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.end() : FormID_ModFile_Record.end();
    }

EditorID_Iterator Collection::LookupRecord(ModFile *&curModFile, char * const &RecordEditorID, Record *&curRecord)
    {
    for(EditorID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID) : EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        if(curRecord->GetParentMod() == curModFile)
            return range.first;
        }
    curRecord = NULL;
    return curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record.end() : EditorID_ModFile_Record.end();
    }

FormID_Iterator Collection::LookupWinningRecord(const FORMID &RecordFormID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts)
    {
    WinningModFile = NULL;
    WinningRecord = NULL;

    FormID_Iterator Winning_it;
    int32_t ModID = -1;
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    for(FormID_Range range = FormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        curModFile = curRecord->GetParentMod();
        curRecord->IsWinning(false);
        if((int32_t)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters))
            {
            ModID = curModFile->ModID;
            WinningModFile = curModFile;
            WinningRecord = range.first->second;
            Winning_it = range.first;
            }
        }
    if(WinningRecord != NULL)
        WinningRecord->IsWinning(true);
    if(GetExtendedConflicts)
        {
        for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(RecordFormID); range.first != range.second; ++range.first)
            {
            curRecord = range.first->second;
            curModFile = curRecord->GetParentMod();
            curRecord->IsWinning(false);
            if((int32_t)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters))
                {
                ModID = curModFile->ModID;
                WinningModFile = curModFile;
                WinningRecord = range.first->second;
                Winning_it = range.first;
                }
            }
        if(WinningRecord != NULL)
            WinningRecord->IsExtendedWinning(true);
        }
    if(ModID > -1)
        return Winning_it;

    return FormID_ModFile_Record.end();
    }

EditorID_Iterator Collection::LookupWinningRecord(char * const &RecordEditorID, ModFile *&WinningModFile, Record *&WinningRecord, const bool GetExtendedConflicts)
    {
    WinningModFile = NULL;
    WinningRecord = NULL;

    EditorID_Iterator Winning_it;
    int32_t ModID = -1;
    ModFile *curModFile = NULL;
    Record *curRecord = NULL;
    for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
        {
        curRecord = range.first->second;
        curModFile = curRecord->GetParentMod();
        curRecord->IsWinning(false);
        if((int32_t)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters))
            {
            ModID = curModFile->ModID;
            WinningModFile = curModFile;
            WinningRecord = range.first->second;
            Winning_it = range.first;
            }
        }
    if(WinningRecord != NULL)
        WinningRecord->IsWinning(true);
    if(GetExtendedConflicts)
        {
        for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
            {
            curRecord = range.first->second;
            curModFile = curRecord->GetParentMod();
            curRecord->IsWinning(false);
            if((int32_t)curModFile->ModID > ModID && (curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters))
                {
                ModID = curModFile->ModID;
                WinningModFile = curModFile;
                WinningRecord = range.first->second;
                Winning_it = range.first;
                }
            }
        if(WinningRecord != NULL)
            WinningRecord->IsExtendedWinning(true);
        }
    if(ModID > -1)
        return Winning_it;

    return EditorID_ModFile_Record.end();
    }

uint32_t Collection::GetNumRecordConflicts(Record *&curRecord, const bool GetExtendedConflicts)
    {
    uint32_t count = 0;
    if(curRecord->IsKeyedByEditorID())
        {
        char * RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            count = (uint32_t)EditorID_ModFile_Record.count(RecordEditorID);
            if(GetExtendedConflicts)
                count += (uint32_t)ExtendedEditorID_ModFile_Record.count(RecordEditorID);
            }
        }
    else
        {
        count = (uint32_t)FormID_ModFile_Record.count(curRecord->formID);
        if(GetExtendedConflicts)
            count += (uint32_t)ExtendedFormID_ModFile_Record.count(curRecord->formID);
        }
    return count;
    }

int32_t Collection::GetRecordConflicts(Record *&curRecord, RECORDIDARRAY RecordIDs, const bool GetExtendedConflicts)
    {
    ModFile *curModFile = NULL;
    if(curRecord->IsKeyedByEditorID())
        {
        char * RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                {
                curModFile = range.first->second->GetParentMod();
                if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters)
                    sortedConflicts.push_back(range.first->second);
                }
            if(GetExtendedConflicts)
                {
                for(EditorID_Range range = ExtendedEditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                    {
                    curModFile = range.first->second->GetParentMod();
                    if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters)
                        sortedConflicts.push_back(range.first->second);
                    }
                }
            }
        }
    else
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            {
            curModFile = range.first->second->GetParentMod();
            if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters)
                sortedConflicts.push_back(range.first->second);
            }
        if(GetExtendedConflicts)
            {
            for(FormID_Range range = ExtendedFormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                {
                curModFile = range.first->second->GetParentMod();
                if(curModFile->Flags.IsInLoadOrder || curModFile->Flags.IsIgnoreInactiveMasters)
                    sortedConflicts.push_back(range.first->second);
                }
            }
        }

    uint32_t y = (uint32_t)sortedConflicts.size();
    if(y)
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compConflicts);
        for(uint32_t x = 0; x < y; ++x)
            RecordIDs[x] = sortedConflicts[x];
        sortedConflicts.clear();
        }
    return y;
    }

int32_t Collection::GetRecordHistory(Record *&curRecord, RECORDIDARRAY RecordIDs)
    {
    ModFile *curModFile = curRecord->GetParentMod();
    if(curModFile->Flags.IsExtendedConflicts)
        {
        //Temporarily silenced until I figure out the best way to handle/avoid the issue
        //printer("GetRecordHistory: Warning - No history available. Mod \"%s\" uses extended conflicts.\n", curModFile->ModName);
        return -1;
        }

    uint8_t curCollapsedIndex = curModFile->FormIDHandler.CollapsedIndex;
    const uint8_t (&CollapseTable)[256] = curModFile->FormIDHandler.CollapseTable;

    ModFile *testModFile = NULL;
    if(curRecord->IsKeyedByEditorID())
        {
        char * RecordEditorID = curRecord->GetEditorIDKey();
        if(RecordEditorID != NULL)
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(RecordEditorID); range.first != range.second; ++range.first)
                {
                testModFile = range.first->second->GetParentMod();
                if(testModFile->Flags.IsInLoadOrder || testModFile->Flags.IsIgnoreInactiveMasters)
                    if(CollapseTable[testModFile->FormIDHandler.ExpandedIndex] != curCollapsedIndex)
                        sortedConflicts.push_back(range.first->second);
                }
            }
        }
    else
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            {
            testModFile = range.first->second->GetParentMod();
            if(testModFile->Flags.IsInLoadOrder || testModFile->Flags.IsIgnoreInactiveMasters)
                if(CollapseTable[testModFile->FormIDHandler.ExpandedIndex] != curCollapsedIndex)
                    sortedConflicts.push_back(range.first->second);
            }
        }

    uint32_t y = (uint32_t)sortedConflicts.size();
    if(y)
        {
        std::sort(sortedConflicts.begin(), sortedConflicts.end(), compHistory);
        for(uint32_t x = 0; x < y; ++x)
            RecordIDs[x] = sortedConflicts[x];
        sortedConflicts.clear();
        }
    return y;
    }

uint32_t Collection::NextFreeExpandedFormID(ModFile *&curModFile, uint32_t depth)
    {
    uint32_t curFormID = curModFile->FormIDHandler.NextExpandedFormID();
    FormID_Range range = curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record.equal_range(curFormID) : FormID_ModFile_Record.equal_range(curFormID);
    //FormID doesn't exist in any mod, so it's free for use
    if(range.first == range.second)
        return curFormID;
    //The formID already exists, so try again (either in that mod, or being injected into that mod)
    //Wrap around and check for any freed formIDs until they're all checked. Unlikely to ever occur.
    return (depth < 0x00FFFFFF) ? NextFreeExpandedFormID(curModFile, ++depth) : 0;
    }

Record * Collection::CreateRecord(ModFile *&curModFile, const uint32_t &RecordType, FORMID RecordFormID, char * const &RecordEditorID, const FORMID &ParentFormID, uint32_t CreateFlags)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        {
        printer("CreateRecord: Error - Unable to create any records in mod \"%s\". It is not in the load order.\n", curModFile->ModName);
        return NULL;
        }

    CreationFlags options(CreateFlags);
    Record *DummyRecord = NULL;
    Record *ParentRecord = NULL;

    if((RecordFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        RecordFormID &= 0x00FFFFFF;

    //See if the requested record already exists
    if(RecordFormID != 0)
        LookupRecord(curModFile, RecordFormID, DummyRecord);
    else if(RecordEditorID != NULL)
        LookupRecord(curModFile, RecordEditorID, DummyRecord);

    if(DummyRecord != NULL)
        return DummyRecord;

    //Lookup the required data, and ensure it exists
    if(ParentFormID)
        {
        LookupRecord(curModFile, ParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            {
            printer("CreateRecord: Error - Unable to locate parent record (%08X). It does not exist in \"%s\".\n", ParentFormID, curModFile->ModName);
            return NULL;
            }
        }

    //Create the new record
    Record *curRecord = curModFile->CreateRecord(RecordType, RecordEditorID, DummyRecord, ParentRecord, options);
    if(curRecord == NULL)
        {
        printer("CreateRecord: Error - Unable to create record of type \"%c%c%c%c\" in mod \"%s\". An unknown error occurred.\n", ((char *)&RecordType)[0], ((char *)&RecordType)[1], ((char *)&RecordType)[2], ((char *)&RecordType)[3], curModFile->ModName);
        return NULL;
        }

    //See if an existing record was returned instead of a new record
    if(options.ExistingReturned)
        return curRecord;

    //Assign the new record a formID
    //Ideally, if keyed by editor id, assign a new formID so that FormIDMasterUpdater doesn't add unneeded masters
    //curRecord->formID = (RecordFormID == 0 || curRecord->IsKeyedByEditorID()) ? NextFreeExpandedFormID(curModFile) : RecordFormID;

    //Trying to keep existing formID if possible to make TES4Edit happy
    // and so future undeleting of EditorID keyed records has a chance of working
    curRecord->formID = RecordFormID == 0 ? NextFreeExpandedFormID(curModFile) : RecordFormID;

    //Then the destination mod's tables get used so that they can be updated
    FormIDMasterUpdater checker(curModFile->FormIDHandler);
    checker.Accept(curRecord->formID);
    //curRecord->VisitFormIDs(checker); //Shouldn't be needed unless a record defaults to having formIDs set (none do atm)

    //Index the new record
    RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(curRecord);

    if(RecordFormID != 0)
        {
        //Update the IsWinning flags for all related records
        ModFile *WinningModfile = NULL;
        Record *WinningRecord = NULL;
        if(curRecord->IsKeyedByEditorID())
            LookupWinningRecord(curRecord->GetEditorIDKey(), WinningModfile, WinningRecord, true);
        else
            LookupWinningRecord(curRecord->formID, WinningModfile, WinningRecord, true);
        }

    return curRecord;
    }

Record * Collection::CopyRecord(Record *&curRecord, ModFile *&DestModFile, const FORMID &DestParentFormID, FORMID DestRecordFormID, char * const &DestRecordEditorID, uint32_t CreateFlags)
    {
    ModFile *curModFile = curRecord->GetParentMod();
    if(!curModFile->Flags.IsInLoadOrder && !curModFile->Flags.IsIgnoreInactiveMasters)
        {
        printer("CopyRecord: Error - Unable to copy any records from source mod \"%s\". It is not in the load order and may require absent masters.\n", curModFile->ModName);
        return NULL;
        }

    CreationFlags options(CreateFlags);
    Record *ParentRecord = NULL;
    Record *RecordCopy = NULL;

    if(options.SetAsOverride)
        {
        //See if its trying to copy a record that already exists in the destination mod
        if(curRecord->IsKeyedByEditorID())
            LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        else
            LookupRecord(DestModFile, DestRecordFormID ? DestRecordFormID : curRecord->formID, RecordCopy);
        }
    else if(DestRecordFormID != 0)
        {
        //If the objectID of a formID is less than END_HARDCODED_IDS, then it doesn't use the modIndex portion
        //instead, it "belongs" to the engine, and they all override each other
        if((DestRecordFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
            DestRecordFormID &= 0x00FFFFFF;

        //See if its trying to copy a record that already exists in the destination mod
        if(curRecord->IsKeyedByEditorID())
            LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        else
            LookupRecord(DestModFile, DestRecordFormID, RecordCopy);
        }
    else if(curRecord->IsKeyedByEditorID())
        {
        //See if its trying to copy a record that already exists in the destination mod
        LookupRecord(DestModFile, DestRecordEditorID ? DestRecordEditorID : curRecord->GetEditorIDKey(), RecordCopy);
        }

    if(RecordCopy != NULL)
        return RecordCopy;

    if(DestParentFormID)
        {
        //See if the parent record already exists in the destination mod
        LookupRecord(DestModFile, DestParentFormID, ParentRecord);
        if(ParentRecord == NULL)
            {
            ModFile *ParentModFile = NULL;
            //If it doesn't, try and create it.
            if(options.CopyWinningParent)
                LookupWinningRecord(DestParentFormID, ParentModFile, ParentRecord);
            else
                LookupRecord(curModFile, DestParentFormID, ParentRecord);
            if(ParentRecord == NULL)
                {
                printer("CopyRecord: Error - Unable to locate destination parent record (%08X). It does not exist in \"%s\" or \"%s\".\n", DestParentFormID, DestModFile->ModName, curModFile->ModName);
                return NULL;
                }
            ParentRecord = CopyRecord(ParentRecord, DestModFile, ParentRecord->GetParentRecord() != NULL ? ParentRecord->GetParentRecord()->formID : 0, 0, 0, options.GetFlags());
            if(ParentRecord == NULL)
                {
                printer("CopyRecord: Error - Unable to copy missing destination parent record (%08X). It does not exist in \"%s\", and there was an error copying it from \"%s\".\n", DestParentFormID, DestModFile->ModName, curModFile->ModName);
                return NULL;
                }
            }
        }

    if(curModFile == DestModFile && options.SetAsOverride)
        {
        printer("CopyRecord: Error - Unable to copy (%08X) as an override record. Source and destination mods \"%s\" are the same.\n", curRecord->formID, curModFile->ModName);
        return NULL;
        }

    if(!DestModFile->Flags.IsInLoadOrder && !options.SetAsOverride)
        {
        printer("CopyRecord: Error - Unable to copy (%08X) as a new record. Destination \"%s\" is not in the load order.\n", curRecord->formID, DestModFile->ModName);
        return NULL;
        }

    //Create the record copy
    RecordCopy = DestModFile->CreateRecord(curRecord->GetType(), DestRecordEditorID, curRecord, ParentRecord, options);
    if(RecordCopy == NULL)
        {
        printer("CopyRecord: Error - Unable to create the copied record (%08X). An unknown error occurred when copying the record from \"%s\" to \"%s\".\n", curRecord->formID, DestModFile->ModName, curModFile->ModName);
        return NULL;
        }

    //See if an existing record was returned instead of the requested copy
    if(options.ExistingReturned)
        return RecordCopy;

    //Copy over the internal flags
    RecordCopy->CBash_Flags = curRecord->CBash_Flags;
    if(!curRecord->IsChanged())
        RecordCopy->IsLoaded(false);

    //Give the record a new formID if it isn't an override record
    if(!options.SetAsOverride)
        RecordCopy->formID = DestRecordFormID ? DestRecordFormID : NextFreeExpandedFormID(DestModFile);
    //DPRINT("Copied %08X from %s to %s", RecordCopy->formID, curRecord->GetParentMod()->FileName, DestModFile->FileName);

    //Ideally, assign the formID to the destination mod so that FormIDMasterUpdater doesn't add unneeded masters
    //else if(RecordCopy->IsKeyedByEditorID())
    //    RecordCopy->formID = NextFreeExpandedFormID(DestModFile);
    //Trying to keep existing formID if possible to make TES4Edit happy
    // and so future undeleting of EditorID keyed records has a chance of working

    //See if the destination mod masters need updating
    //Ensure the record has been fully read
    //Uses the source mod's formID resolution tables
    RecordReader reader(curModFile->FormIDHandler, Expanders);
    reader.Accept(RecordCopy);

    //Then the destination mod's tables get used so that they can be updated
    FormIDMasterUpdater checker(DestModFile->FormIDHandler);
    checker.Accept(RecordCopy->formID);
    RecordCopy->VisitFormIDs(checker);

    //Index the record
    RecordIndexer indexer(DestModFile, DestModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, DestModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
    indexer.Accept(RecordCopy);

    if(curRecord->IsWinningDetermined() || curRecord->formID != RecordCopy->formID)
        {
        //Update the IsWinning flags for all related records
        ModFile *WinningModfile = NULL;
        Record *WinningRecord = NULL;
        if(RecordCopy->IsKeyedByEditorID())
            LookupWinningRecord(RecordCopy->GetEditorIDKey(), WinningModfile, WinningRecord, true);
        else
            LookupWinningRecord(RecordCopy->formID, WinningModfile, WinningRecord, true);
        }

    if(reader.result) //If the record was read, go ahead and unload it
        RecordCopy->Unload();
    return RecordCopy;
    }

int32_t Collection::CleanModMasters(ModFile *curModFile)
    {
    if(!curModFile->Flags.IsInLoadOrder)
        {
        printer("CleanModMasters: Error - Unable to clean \"%s\"'s masters. It is not in the load order.\n", curModFile->ModName);
        return NULL;
        }

    RecordMasterCollector collector(curModFile->FormIDHandler, Expanders);
    curModFile->VisitAllRecords(collector);

    uint32_t cleaned = 0;
    for(int32_t ListIndex = curModFile->TES4.MAST.size() - 1; ListIndex >= 0 ; --ListIndex)
        {
        if(collector.collector.UsedTable[ListIndex] == 0)
            {
            delete []curModFile->TES4.MAST[ListIndex];
            curModFile->TES4.MAST.erase(curModFile->TES4.MAST.begin() + ListIndex);
            cleaned++;
            }
        }
    if(cleaned > 0)
        curModFile->FormIDHandler.UpdateFormIDLookup();
    return cleaned;
    }

int32_t Collection::SetIDFields(Record *&RecordID, FORMID FormID, char * const &EditorID)
    {
    ModFile *curModFile = RecordID->GetParentMod();
    char * OldEditorID = RecordID->GetEditorIDKey();
    FORMID OldFormID = RecordID->formID;

    if((FormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        FormID &= 0x00FFFFFF;
    bool bChangingFormID = OldFormID != FormID;
    bool bChangingEditorID = false;
    if(OldEditorID == NULL)
        {
        if(EditorID != NULL)
            bChangingEditorID = true;
        }
    else
        {
        if(EditorID == NULL)
            bChangingEditorID = true;
        else if(cmps(OldEditorID, EditorID) != 0)
            bChangingEditorID = true;
        }

    //Not allowed to set the FormID to 0
    bChangingFormID = bChangingFormID && FormID != 0;
    //Not allowed to delete the EditorID if the record is keyed by it
    if(RecordID->IsKeyedByEditorID())
        bChangingEditorID = bChangingEditorID && EditorID != NULL;

    if(!(bChangingFormID || bChangingEditorID))
        return -1;

    Record *curRecord = NULL;

    //If the FormID is already in use by the mod, do nothing.
    if(bChangingFormID)
        LookupRecord(curModFile, FormID, curRecord);

    if(curRecord != NULL)
        {
        printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". The formID is already in use.\n", FormID, EditorID, curRecord->formID, curRecord->GetEditorIDKey(), curModFile->ModName);
        return -1;
        }

    //If the EditorID is already in use by the mod, do nothing.
    //This only cares about records keyed by editorID since they'd get the most confused
    if(bChangingEditorID && EditorID != NULL)
        LookupRecord(curModFile, EditorID, curRecord);

    if(curRecord != NULL)
        {
        printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". The EditorID is already in use.\n", FormID, EditorID, curRecord->formID, curRecord->GetEditorIDKey(), curModFile->ModName);
        return -1;
        }

    //De-index the record
    if(bChangingFormID || (bChangingEditorID && RecordID->IsKeyedByEditorID()))
        {
        RecordDeindexer deindexer(RecordID);
        deindexer.Accept(RecordID);
        if(deindexer.GetCount() == 0)
            {
            printer("SetRecordIDs: Error - Unable to set the new record ids (%08X, %s) on record (%08X, %s) in mod \"%s\". Unable to deindex the record.\n", FormID, EditorID, RecordID->formID, RecordID->GetEditorIDKey(), curModFile->ModName);
            return -1;
            }
        }

    //Update the formID
    if(bChangingFormID)
        {
        RecordID->formID = FormID;
        FormIDMasterUpdater checker(curModFile->FormIDHandler);
        checker.Accept(RecordID->formID);
        }

    //Update the editorID
    if(bChangingEditorID)
        {
        //Ensure the record is fully loaded, otherwise any changes could be lost when the record is later loaded
        RecordReader reader(curModFile->FormIDHandler, Expanders);
        reader.Accept(RecordID);
        RecordID->SetEditorIDKey(EditorID);
        RecordID->IsChanged(true);
        }

    //Re-index the record
    if(bChangingFormID || (bChangingEditorID && RecordID->IsKeyedByEditorID()))
        {
        RecordIndexer indexer(curModFile, curModFile->Flags.IsExtendedConflicts ? ExtendedEditorID_ModFile_Record: EditorID_ModFile_Record, curModFile->Flags.IsExtendedConflicts ? ExtendedFormID_ModFile_Record: FormID_ModFile_Record);
        indexer.Accept(RecordID);
        }

    //Update the IsWinning flags for all related records
    ModFile *WinningModfile = NULL;
    Record *WinningRecord = NULL;
    if(bChangingEditorID && RecordID->IsKeyedByEditorID())
        {
        LookupWinningRecord(OldEditorID, WinningModfile, WinningRecord, true);
        LookupWinningRecord(RecordID->GetEditorIDKey(), WinningModfile, WinningRecord, true);
        }
    if(bChangingFormID)
        {
        LookupWinningRecord(OldFormID, WinningModfile, WinningRecord, true);
        LookupWinningRecord(RecordID->formID, WinningModfile, WinningRecord, true);
        }

    uint8_t ModIndex = (uint8_t)(RecordID->formID >> 24);
    if(ModIndex == 0xFF)
        {
        //RecordID->HasInvalidFormIDs(true);
        ModFile *ModID = RecordID->GetParentMod();
        printer("SetIDFields: Error! Record (%08X) in mod %s uses an invalid FormID!\n", RecordID->formID, ModID->ModName);
        }

    return (bChangingFormID || bChangingEditorID) ? 1 : -1;
    }

RecordDeindexer::RecordDeindexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordDeindexer::RecordDeindexer(Record *RecordID):
    RecordOp(),
    EditorID_ModFile_Record(RecordID->GetParentMod()->Flags.IsExtendedConflicts ? RecordID->GetParentMod()->Parent->ExtendedEditorID_ModFile_Record: RecordID->GetParentMod()->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(RecordID->GetParentMod()->Flags.IsExtendedConflicts ? RecordID->GetParentMod()->Parent->ExtendedFormID_ModFile_Record: RecordID->GetParentMod()->Parent->FormID_ModFile_Record)
    {
    //
    }

RecordDeindexer::RecordDeindexer(ModFile *ModID):
    RecordOp(),
    EditorID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedEditorID_ModFile_Record: ModID->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedFormID_ModFile_Record: ModID->Parent->FormID_ModFile_Record)
    {
    //
    }

RecordDeindexer::~RecordDeindexer()
    {
    //
    }

bool RecordDeindexer::Accept(Record *&curRecord)
    {
    if(curRecord != NULL)
        {
        //De-Index the record
        if(curRecord->formID != 0)
            {
            for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
                if(range.first->second == curRecord)
                    {
                    FormID_ModFile_Record.erase(range.first);
                    ++count;
                    result = true;
                    break;
                    }
            }
        if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records that weren't able to be undeleted
            {
            for(EditorID_Range range = EditorID_ModFile_Record.equal_range(curRecord->GetEditorIDKey()); range.first != range.second; ++range.first)
                if(range.first->second == curRecord)
                    {
                    EditorID_ModFile_Record.erase(range.first);
                    ++count;
                    result = true;
                    break;
                    }
            }
        }
    return false;
    }

IdenticalToMasterRetriever::IdenticalToMasterRetriever(ModFile *ModID):
    RecordOp(),
    reader(ModID->FormIDHandler, ModID->Parent->Expanders),
    MasterIndex(ModID->FormIDHandler.ExpandedIndex),
    identical_records(ModID->Parent->identical_records),
    EditorID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedEditorID_ModFile_Record: ModID->Parent->EditorID_ModFile_Record),
    FormID_ModFile_Record(ModID->Flags.IsExtendedConflicts ? ModID->Parent->ExtendedFormID_ModFile_Record: ModID->Parent->FormID_ModFile_Record),
    Expanders(ModID->Parent->Expanders)
    {
    //
    }

IdenticalToMasterRetriever::~IdenticalToMasterRetriever()
    {
    //
    }

bool IdenticalToMasterRetriever::Accept(Record *&curRecord)
    {
    uint8_t ModIndex = (uint8_t)(curRecord->formID >> 24);

    //The record has no master
    if(ModIndex == MasterIndex)
        return false;

    Record *master_record = NULL;
    ModFile *master_mod = curRecord->GetParentMod();

    const uint8_t &CollapsedIndex = master_mod->FormIDHandler.CollapsedIndex;
    const uint8_t (&CollapseTable)[256] = master_mod->FormIDHandler.CollapseTable;
    int32_t ModID = -1;

    if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records (they'll get indexed after being undeleted)
        {
        for(EditorID_Range range = EditorID_ModFile_Record.equal_range(curRecord->GetEditorIDKey()); range.first != range.second; ++range.first)
            {
            master_mod = range.first->second->GetParentMod();
            if((int32_t)master_mod->ModID > ModID && (master_mod->Flags.IsInLoadOrder || master_mod->Flags.IsIgnoreInactiveMasters))
                //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                // that means the mod has that other mod as a master.
                if(CollapseTable[master_mod->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                    {
                    ModID = master_mod->ModID;
                    master_record = range.first->second;
                    }
            }
        }
    else if(curRecord->formID != 0)
        {
        for(FormID_Range range = FormID_ModFile_Record.equal_range(curRecord->formID); range.first != range.second; ++range.first)
            {
            master_mod = range.first->second->GetParentMod();
            if((int32_t)master_mod->ModID > ModID && (master_mod->Flags.IsInLoadOrder || master_mod->Flags.IsIgnoreInactiveMasters))
                //If the CollapseTable at a given expanded index is set to something other than the mod's CollapsedIndex,
                // that means the mod has that other mod as a master.
                if(CollapseTable[master_mod->FormIDHandler.ExpandedIndex] != CollapsedIndex)
                    {
                    ModID = master_mod->ModID;
                    master_record = range.first->second;
                    }
            }
        }

    if(master_record == NULL)
        return false;

    RecordReader read_other(master_record->GetParentMod()->FormIDHandler, Expanders);

    if(curRecord->master_equality(master_record, reader, read_other, identical_records))
        identical_records.insert(curRecord);

    //Keep memory usage at a minimum
    if(!curRecord->IsChanged())
        curRecord->Unload();
    if(!master_record->IsChanged())
        master_record->Unload();

    return false;
    }

RecordReader::RecordReader(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Expanders(_Expanders)
    {
    //
    }

RecordReader::RecordReader(Record *RecordID):
    RecordOp(),
    expander(RecordID->GetParentMod()->FormIDHandler.ExpandTable, RecordID->GetParentMod()->FormIDHandler.FileStart, RecordID->GetParentMod()->FormIDHandler.FileEnd),
    Expanders(RecordID->GetParentMod()->Parent->Expanders)
    {
    //
    }

RecordReader::RecordReader(ModFile *ModID):
    RecordOp(),
    expander(ModID->FormIDHandler.ExpandTable, ModID->FormIDHandler.FileStart, ModID->FormIDHandler.FileEnd),
    Expanders(ModID->Parent->Expanders)
    {
    //
    }

RecordReader::~RecordReader()
    {
    //
    }

bool RecordReader::Accept(Record *&curRecord)
    {
    result = curRecord->Read();
    if(result)
        {
        if(curRecord->IsValid(expander))
            {
            //expander.result = false;
            curRecord->VisitFormIDs(expander);
            //curRecord->HasInvalidFormIDs(expander.result);
            }
        else
            {
            int32_t index = -1;
            for(uint32_t x = 0; x < Expanders.size(); ++x)
                if(curRecord->IsValid(*Expanders[x]))
                    {
                    //if(index != -1)
                    //    printer("Multiple 'Correct' expanders found! Using last one found (likely incorrect unless lucky)\n");
                    index = x;
                    break;
                    }
            if(index == -1)
                {
                uint8_t ModIndex = (uint8_t)(curRecord->formID >> 24);
                ModFile *ModID = curRecord->GetParentMod();
                uint8_t CollapsedIndex = ModID->FormIDHandler.CollapseTable[ModIndex];
                char * LongID = CollapsedIndex >= ModID->TES4.MAST.size() ? ModID->ModName : ModID->TES4.MAST[CollapsedIndex];

                printer("RecordReader: Error - Unable to find the correct expander for record (%s, %06X) in mod %s!\n", LongID, curRecord->formID & 0x00FFFFFF, ModID->ModName);
                //expander.result = false;
                curRecord->VisitFormIDs(expander);
                //curRecord->HasInvalidFormIDs(expander.result);
                }
            else
                {
                //Expanders[index]->result = false;
                curRecord->VisitFormIDs(*Expanders[index]);
                //curRecord->HasInvalidFormIDs(Expanders[index]->result);
                }
            }
        ++count;
        }
    return stop;
    }

RecordInvalidFormIDChecker::InvalidFormIDChecker::InvalidFormIDChecker():
    FormIDOp()
    {
    //
    }

RecordInvalidFormIDChecker::InvalidFormIDChecker::~InvalidFormIDChecker()
    {
    //
    }

bool RecordInvalidFormIDChecker::InvalidFormIDChecker::Accept(uint32_t &curFormID)
    {
    if((curFormID & 0x00FFFFFF) > END_HARDCODED_IDS)
        result = result || ((curFormID >> 24) == 0xFF);
    return stop;
    }

bool RecordInvalidFormIDChecker::InvalidFormIDChecker::AcceptMGEF(uint32_t &curMgefCode)
    {
    result = result || ((curMgefCode & 0x000000FF) == 0xFF);
    return stop;
    }

RecordInvalidFormIDChecker::RecordInvalidFormIDChecker():
    RecordOp()
    {
    //
    }

RecordInvalidFormIDChecker::~RecordInvalidFormIDChecker()
    {
    //
    }

bool RecordInvalidFormIDChecker::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    if(!curRecord->IsLoaded())
        {
        RecordReader reader(curRecord);
        reader.Accept(curRecord);
        }
    checker.result = false;
    checker.Accept(curRecord->formID);
    curRecord->VisitFormIDs(checker);

    return checker.result;
    }

RecordFormIDSwapper::RecordFormIDSwapper(const uint32_t &_FormIDToMatch, const uint32_t &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    swapper(_FormIDToMatch, _FormIDToSwap, _FormIDHandler)
    {
    //
    }

RecordFormIDSwapper::~RecordFormIDSwapper()
    {
    //
    }

bool RecordFormIDSwapper::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    //Perform the swap
    stop = curRecord->VisitFormIDs(swapper);

    //Check if anything was swapped
    if(count != swapper.GetCount())
        {
        //If so, mark the record as changed
        curRecord->IsChanged(true);
        count = swapper.GetCount();
        }

    //If the record was read, but not changed, unload it again
    if(reader.result && !curRecord->IsChanged())
        curRecord->Unload();

    return stop;
    }

RecordFormIDMapper::FormIDMapper::FormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users):
    FormIDOp(),
    formID_users(_formID_users),
    curRecord(NULL)
    {
    //
    }

RecordFormIDMapper::FormIDMapper::~FormIDMapper()
    {
    //
    }

bool RecordFormIDMapper::FormIDMapper::Accept(uint32_t &curFormID)
    {
    formID_users[curFormID].push_back(curRecord);
    return stop;
    }

bool RecordFormIDMapper::FormIDMapper::AcceptMGEF(uint32_t &curMgefCode)
    {
    formID_users[curMgefCode].push_back(curRecord);
    return stop;
    }

RecordFormIDMapper::RecordFormIDMapper(std::map<FORMID, std::vector<Record *> > &_formID_users, FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    mapper(_formID_users)
    {
    //
    }

RecordFormIDMapper::~RecordFormIDMapper()
    {
    //
    }

bool RecordFormIDMapper::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    //Perform the map
    mapper.curRecord = curRecord;
    stop = curRecord->VisitFormIDs(mapper);

    //If the record was read, but not changed, unload it again
    if(reader.result && !curRecord->IsChanged())
        curRecord->Unload();

    return stop;
    }

RecordMasterCollector::FormIDMasterCollector::FormIDMasterCollector(uint8_t (&_CollapseTable)[256]):
    FormIDOp(),
    CollapseTable(_CollapseTable)
    {
    memset(&UsedTable[0], 0x00, sizeof(UsedTable));
    }

RecordMasterCollector::FormIDMasterCollector::~FormIDMasterCollector()
    {
    //
    }

bool RecordMasterCollector::FormIDMasterCollector::Accept(uint32_t &curFormID)
    {
    //Any formID <= 0x800 is hardcoded in the engine and doesn't 'belong' to a mod.
    if((curFormID & 0x00FFFFFF) < END_HARDCODED_IDS)
        return stop;
    UsedTable[CollapseTable[curFormID >> 24]] = 1;
    return stop;
    }

bool RecordMasterCollector::FormIDMasterCollector::AcceptMGEF(uint32_t &curMgefCode)
    {
    UsedTable[CollapseTable[curMgefCode & 0x000000FF]] = 1;
    return stop;
    }

RecordMasterCollector::RecordMasterCollector(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders),
    collector(_FormIDHandler.CollapseTable)
    {
    //
    }

RecordMasterCollector::~RecordMasterCollector()
    {
    //
    }

bool RecordMasterCollector::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);

    collector.Accept(curRecord->formID);
    curRecord->VisitFormIDs(collector);

    //If the record was read, but not changed, unload it again
    if(reader.result && !curRecord->IsChanged())
        curRecord->Unload();

    return stop;
    }

RecordChanger::RecordChanger(FormIDHandlerClass &_FormIDHandler, std::vector<FormIDResolver *> &_Expanders):
    RecordOp(),
    reader(_FormIDHandler, _Expanders)
    {
    //
    }

RecordChanger::~RecordChanger()
    {
    //
    }

bool RecordChanger::Accept(Record *&curRecord)
    {
    //Ensure the record is read
    reader.Accept(curRecord);
    //Mark it as changed
    curRecord->IsChanged(true);

    return stop;
    }