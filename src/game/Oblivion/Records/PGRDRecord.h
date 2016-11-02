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
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace Ob
{
class PGRDRecord : public Record
    {
    private:
        //struct PGRDPGRR
        //    {
        //    unsigned short start, end;
        //    PGRDPGRR():start(0), end(0) {}
        //    #ifdef _DEBUG
        //    void Debug(int32_t debugLevel, size_t &indentation)
        //        {
        //        if(debugLevel > 3)
        //            {
        //            indentation += 2;
        //            PrintIndent(indentation);
        //            printer("start = %u\n", start);
        //            PrintIndent(indentation);
        //            printer("end   = %u\n", end);
        //            indentation -= 2;
        //            }
        //        }
        //    #endif
        //    };

        struct PGRDPGRI
            {
            uint16_t  point;
            uint8_t   unused1[2];
            float x, y, z;

            PGRDPGRI();
            ~PGRDPGRI();

            bool operator ==(const PGRDPGRI &other) const;
            bool operator !=(const PGRDPGRI &other) const;
            };

        struct PGRDPGRL
            {
            UnorderedPackedArray<uint32_t> points;

            PGRDPGRL();
            ~PGRDPGRL();

            void Write(FileWriter &writer);

            bool operator ==(const PGRDPGRL &other) const;
            bool operator !=(const PGRDPGRL &other) const;
            };

    public:
        ReqSimpleSubRecord<uint16_t> DATA; //Point Count
        UnorderedPackedArray<GENPGRP> PGRP; //Points
        RawRecord PGAG; //Unknown
        RawRecord PGRR; //UnorderedPackedArray<PGRDPGRR> ? //Point-to-Point Connections
        UnorderedPackedArray<PGRDPGRI> PGRI; //Inter-cell Connections
        UnorderedSparseArray<PGRDPGRL *> PGRL; //Point-to-Reference Mappings

        PGRDRecord(unsigned char *_recData=NULL);
        PGRDRecord(PGRDRecord *srcRecord);
        ~PGRDRecord();

        bool   VisitFormIDs(FormIDOp &op);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const PGRDRecord &other) const;
        bool operator !=(const PGRDRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}