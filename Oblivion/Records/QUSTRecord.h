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
class QUSTRecord : public Record //Quest
    {
    private:
        struct QUSTDATA
            {
            UINT8   flags, priority;

            QUSTDATA();
            ~QUSTDATA();

            bool operator ==(const QUSTDATA &other) const;
            bool operator !=(const QUSTDATA &other) const;
            };

        struct QUSTEntry //Log Entry
            {
            ReqSimpleSubRecord<UINT8> QSDT; //Stage Flags
            OrderedSparseArray<GENCTDA *> CTDA; //Conditions
            StringRecord CNAM; //Log Entry
            ReqSubRecord<GENSCHR> SCHR; //Basic Script Data
            RawRecord SCDA; //Unknown (Script Header?)
            NonNullStringRecord SCTX; //Script Source
            OrderedSparseArray<GENSCR_ *> SCR_; //References

            enum entriesFlags
                {
                fIsCompletes = 0x00000001
                };

            enum scriptTypeTypes
                {
                eObject = 0x0000,
                eQuest  = 0x0001,
                eEffect = 0x0100
                };

            bool IsCompletes();
            void IsCompletes(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            bool IsObject();
            void IsObject(bool value);
            bool IsQuest();
            void IsQuest(bool value);
            bool IsEffect();
            void IsEffect(bool value);
            bool IsType(UINT16 Type);
            void SetType(UINT16 Type);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTEntry &other) const;
            bool operator !=(const QUSTEntry &other) const;
            };

        struct QUSTStage //Stage
            {
            ReqSimpleSubRecord<UINT16> INDX; //Stage Index
            UnorderedSparseArray<QUSTEntry *> Entries; //Log Entries

            void Write(FileWriter &writer);

            bool operator ==(const QUSTStage &other) const;
            bool operator !=(const QUSTStage &other) const;
            };

        struct QUSTQSTA //Target
            {
            FORMID  targetId; //Target
            UINT8   flags, unused1[3]; //Flags, Unused

            QUSTQSTA();
            ~QUSTQSTA();

            bool operator ==(const QUSTQSTA &other) const;
            bool operator !=(const QUSTQSTA &other) const;
            };

        struct QUSTTarget //Target
            {
            ReqSubRecord<QUSTQSTA> QSTA; //Target
            OrderedSparseArray<GENCTDA *> CTDA; //Conditions

            enum targetsFlags
                {
                fIsIgnoresLocks = 0x00000001
                };

            bool IsIgnoresLocks();
            void IsIgnoresLocks(bool value);
            bool IsFlagMask(UINT8 Mask, bool Exact=false);
            void SetFlagMask(UINT8 Mask);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTTarget &other) const;
            bool operator !=(const QUSTTarget &other) const;
            };

        enum flagsFlags
            {
            fIsStartEnabled   = 0x00000001,
            fIsRepeatedTopics = 0x00000004,
            fIsRepeatedStages = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord FULL; //Name
        StringRecord ICON; //Large Icon Filename
        ReqSubRecord<QUSTDATA> DATA; //General
        OrderedSparseArray<GENCTDA *> CTDA; //Conditions
        UnorderedSparseArray<QUSTStage *> Stages; //Stages
        UnorderedSparseArray<QUSTTarget *> Targets; //Targets

        QUSTRecord(unsigned char *_recData=NULL);
        QUSTRecord(QUSTRecord *srcRecord);
        ~QUSTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsStartEnabled();
        void   IsStartEnabled(bool value);
        bool   IsRepeatedTopics();
        void   IsRepeatedTopics(bool value);
        bool   IsRepeatedStages();
        void   IsRepeatedStages(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const QUSTRecord &other) const;
        bool operator !=(const QUSTRecord &other) const;
        bool equals(Record *other);
    };
}