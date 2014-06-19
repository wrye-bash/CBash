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
// Visitors.cpp
#include "Visitors.h"
#include "Oblivion/Records/MGEFRecord.h"

FormIDMatchCounter::FormIDMatchCounter(const uint32_t &_FormIDToMatch):
    FormIDOp(),
    FormIDToMatch(_FormIDToMatch)
    {
    //
    }

FormIDMatchCounter::~FormIDMatchCounter()
    {
    //
    }

bool FormIDMatchCounter::Accept(uint32_t &curFormID)
    {
    if(curFormID == FormIDToMatch)
        ++count;
    return stop;
    }

bool FormIDMatchCounter::AcceptMGEF(uint32_t &curMgefCode)
    {
    if(curMgefCode == FormIDToMatch)
        ++count;
    return stop;
    }

RecordUnloader::RecordUnloader():
    RecordOp()
    {
    //
    }

RecordUnloader::~RecordUnloader()
    {
    //
    }

bool RecordUnloader::Accept(Record *&curRecord)
    {
    if(!curRecord->IsChanged())
        curRecord->Unload();
    return stop;
    }

RecordIDRetriever::RecordIDRetriever(RECORDIDARRAY _RecordIDs):
    RecordOp(),
    RecordIDs(_RecordIDs)
    {
    //
    }

RecordIDRetriever::~RecordIDRetriever()
    {
    //
    }

bool RecordIDRetriever::Accept(Record *&curRecord)
    {
    RecordIDs[count++] = curRecord;
    return stop;
    }

FormIDSwapper::FormIDSwapper(const uint32_t &_FormIDToMatch, const uint32_t &_FormIDToSwap, FormIDHandlerClass &_FormIDHandler):
    FormIDOp(),
    FormIDToMatch(_FormIDToMatch),
    FormIDToSwap(_FormIDToSwap),
    checker(_FormIDHandler)
    {
    //
    }

FormIDSwapper::~FormIDSwapper()
    {
    //
    }

bool FormIDSwapper::Accept(uint32_t &curFormID)
    {
    result = curFormID == FormIDToMatch;
    if(result)
        {
        curFormID = FormIDToSwap;
        checker.Accept(curFormID);
        ++count;
        }
    return stop;
    }

bool FormIDSwapper::AcceptMGEF(uint32_t &curMgefCode)
    {
    result = curMgefCode == FormIDToMatch;
    if(result)
        {
        curMgefCode = FormIDToSwap;
        checker.Accept(curMgefCode);
        ++count;
        }
    return stop;
    }

RecordIndexer::RecordIndexer(ModFile *_curModFile, EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    curModFile(_curModFile),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordIndexer::RecordIndexer(EditorID_Map &_EditorID_Map, FormID_Map &_FormID_Map):
    RecordOp(),
    EditorID_ModFile_Record(_EditorID_Map),
    FormID_ModFile_Record(_FormID_Map)
    {
    //
    }

RecordIndexer::~RecordIndexer()
    {
    //
    }

bool RecordIndexer::Accept(Record *&curRecord)
    {
    if(curRecord->formID != 0)
        FormID_ModFile_Record.insert(std::make_pair(curRecord->formID,curRecord));
    if(curRecord->IsKeyedByEditorID() && curRecord->GetEditorIDKey() != NULL) //Should only be null on deleted records (they'll get indexed after being undeleted)
        EditorID_ModFile_Record.insert(std::make_pair(curRecord->GetEditorIDKey(),curRecord));
    return false;
    }

void RecordIndexer::SetModFile(ModFile *_curModFile)
    {
    curModFile = _curModFile;
    }