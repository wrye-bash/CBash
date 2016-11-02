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

namespace FNV
{
class QUSTRecord : public FNVRecord //Quest
    {
    private:
        struct QUSTDATA
            {
            uint8_t   flags, priority, unused1[2]; //unused1 and delay not always present in chunk...
            float delay;

            QUSTDATA();
            ~QUSTDATA();

            bool operator ==(const QUSTDATA &other) const;
            bool operator !=(const QUSTDATA &other) const;
            };

        struct QUSTEntry //Log Entry
            {
            ReqSimpleSubRecord<uint8_t> QSDT; //Stage Flags
            OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
            StringRecord CNAM; //Log Entry
            ReqSubRecord<FNVSCHR> SCHR; //Basic Script Data
            RawRecord SCDA; //Unknown (Script Header?)
            NonNullStringRecord SCTX; //Script Source
            OrderedSparseArray<GENVARS *, sortVARS> VARS; //Local Variables
            OrderedSparseArray<GENSCR_ *> SCR_; //References
            OptSimpleSubRecord<FORMID> NAM0; //Next Quest (only used if IsCompletes or IsFailed...)

            enum entriesFlags
                {
                fIsCompletes = 0x00000001,
                fIsFailed    = 0x00000002
                };

            enum schrFlags
                {
                fIsEnabled = 0x0001
                };

            enum scriptTypeTypes
                {
                eObject = 0x0000,
                eQuest  = 0x0001,
                eEffect = 0x0100
                };

            bool IsCompletes();
            void IsCompletes(bool value);
            bool IsFailed();
            void IsFailed(bool value);
            bool IsFlagMask(uint8_t Mask, bool Exact=false);
            void SetFlagMask(uint8_t Mask);

            bool IsScriptEnabled();
            void IsScriptEnabled(bool value);
            bool IsScriptFlagMask(uint16_t Mask, bool Exact=false);
            void SetScriptFlagMask(uint16_t Mask);

            bool IsObject();
            void IsObject(bool value);
            bool IsQuest();
            void IsQuest(bool value);
            bool IsEffect();
            void IsEffect(bool value);
            bool IsType(uint16_t Type);
            void SetType(uint16_t Type);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTEntry &other) const;
            bool operator !=(const QUSTEntry &other) const;
            };

        struct QUSTStage //Stage
            {
            ReqSimpleSubRecord<int16_t> INDX; //Stage Index
            UnorderedSparseArray<QUSTEntry *> Entries; //Log Entries

            void Write(FileWriter &writer);

            bool operator ==(const QUSTStage &other) const;
            bool operator !=(const QUSTStage &other) const;
            };

        struct QUSTQSTA //Target
            {
            FORMID  targetId; //Target
            uint8_t   flags, unused1[3]; //Flags, Unused

            QUSTQSTA();
            ~QUSTQSTA();

            bool operator ==(const QUSTQSTA &other) const;
            bool operator !=(const QUSTQSTA &other) const;
            };

        struct QUSTTarget //Target
            {
            ReqSubRecord<QUSTQSTA> QSTA; //Target
            OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

            enum targetsFlags
                {
                fIsIgnoresLocks = 0x00000001
                };

            bool IsIgnoresLocks();
            void IsIgnoresLocks(bool value);
            bool IsFlagMask(uint8_t Mask, bool Exact=false);
            void SetFlagMask(uint8_t Mask);

            void Write(FileWriter &writer);

            bool operator ==(const QUSTTarget &other) const;
            bool operator !=(const QUSTTarget &other) const;
            };

        struct QUSTObjective
            {
            ReqSimpleSubRecord<int32_t> QOBJ; //Objective Index
            StringRecord NNAM; //Description
            UnorderedSparseArray<QUSTTarget *> Targets; //Targets

            void Write(FileWriter &writer);

            bool operator ==(const QUSTObjective &other) const;
            bool operator !=(const QUSTObjective &other) const;
            };

        enum flagsFlags
            {
            fIsStartEnabled   = 0x00000001,
            fIsRepeatedTopics = 0x00000004,
            fIsRepeatedStages = 0x00000008,
            fIsUnknown        = 0x00000010
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord FULL; //Name
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        ReqSubRecord<QUSTDATA> DATA; //General
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
        UnorderedSparseArray<QUSTStage *> Stages; //Stages
        UnorderedSparseArray<QUSTObjective *> Objectives; //Objectives

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
        bool   IsUnknown();
        void   IsUnknown(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const QUSTRecord &other) const;
        bool operator !=(const QUSTRecord &other) const;
        bool equals(Record *other);
    };
}