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
// ModFile.h
#include "Common.h"
#include "GenericRecord.h"
#include "TES4Record.h" //Is shared across all mod types

class Collection;

class ModFile
    {
    public:
        boost::iostreams::mapped_file_source file_map;

        STRING FileName;
        STRING ModName;

        unsigned char *buffer_start, *buffer_position, *buffer_end;

	boost::unordered_set<UINT32> filter_records;
	boost::unordered_set<FORMID> filter_wspaces;
	bool filter_inclusive;

        FormIDHandlerClass FormIDHandler;
        ModFlags Flags;
        time_t ModTime;
        UINT32 ModID;

        Collection *Parent;

        TES4Record TES4;

        ModFile(Collection *_Parent, STRING FileName, STRING ModName, const UINT32 _flags);
        virtual ~ModFile();

        bool operator <(ModFile &other);
        bool operator >(ModFile &other);

        time_t mtime();
        bool   exists();

        bool   Open();
        bool   Close();

        virtual SINT32   LoadTES4() abstract {};
        virtual SINT32   Load(RecordOp &read_parser, RecordOp &indexer, std::vector<FormIDResolver *> &Expanders, std::vector<Record *> &DeletedRecords) abstract {};
        virtual UINT32   GetNumRecords(const UINT32 &RecordType) abstract {};
        virtual Record * CreateRecord(const UINT32 &RecordType, STRING const &RecordEditorID, Record *&SourceRecord, Record *&ParentRecord, CreationFlags &options) abstract {};
        virtual SINT32   DeleteRecord(Record *&curRecord, RecordOp &deindexer) abstract {};
        virtual SINT32   Save(STRING const &SaveName, std::vector<FormIDResolver *> &Expanders, bool CloseMod, RecordOp &indexer) abstract {};

	virtual void	 SetFilter(bool inclusive, boost::unordered_set<UINT32> &RecordTypes, boost::unordered_set<FORMID> &WorldSpaces) abstract {};

        virtual void     VisitAllRecords(RecordOp &op) abstract {};
        virtual void     VisitRecords(const UINT32 &RecordType, RecordOp &op) abstract {};
    };

class FormIDMasterUpdater : public FormIDOp
    {
    private:
        FormIDHandlerClass &FormIDHandler;
        const UINT8 &ExpandedIndex;
        const UINT8 &CollapsedIndex;
        const UINT8 (&ExpandTable)[256];
        const UINT8 (&CollapseTable)[256];

    public:
        FormIDMasterUpdater(FormIDHandlerClass &_FormIDHandler);
        FormIDMasterUpdater(ModFile *ModID);
        FormIDMasterUpdater(Record *RecordID);
        ~FormIDMasterUpdater();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };