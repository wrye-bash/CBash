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
class DIALRecord : public FNVRecord //Dialog Topic
    {
    private:
        struct DIALUNK
            {
            ReqSimpleSubRecord<FORMID> INFC; //Unknown
            SemiOptSimpleSubRecord<int32_t> INFX; //Unknown (index? increases by one for each INFC)

            void Write(FileWriter &writer);

            bool operator ==(const DIALUNK &other) const;
            bool operator !=(const DIALUNK &other) const;
            };

        struct DIALQSTI
            {
            ReqSimpleSubRecord<FORMID> QSTI; //Quest
            UnorderedSparseArray<DIALUNK *> Unknown; //Unknown

            void Write(FileWriter &writer);

            bool operator ==(const DIALQSTI &other) const;
            bool operator !=(const DIALQSTI &other) const;
            };

        struct DIALQSTR
            {
            ReqSimpleSubRecord<FORMID> QSTR; //Quest
            UnorderedSparseArray<DIALUNK *> Unknown; //Unknown

            void Write(FileWriter &writer);

            bool operator ==(const DIALQSTR &other) const;
            bool operator !=(const DIALQSTR &other) const;
            };

        struct DIALDATA
            {
            uint8_t   dialType; //Type
            uint8_t   flags; //Flags, not always present in chunk

            DIALDATA();
            ~DIALDATA();

            bool operator ==(const DIALDATA &other) const;
            bool operator !=(const DIALDATA &other) const;
            };

        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6,
            eRadio        = 7
            };

        enum flagsFlags
            {
            fIsRumors   = 0x01,
            fIsTopLevel = 0x02
            };
    public:
        StringRecord EDID; //Editor ID
        UnorderedSparseArray<DIALQSTI *> QSTI; //Added Quests
        UnorderedSparseArray<DIALQSTR *> QSTR; //Removed Quests
        StringRecord FULL; //Name
        OptSimpleFloatSubRecord<flt_0> PNAM; //Priority
        StringRecord TDUM; //Unknown
        ReqSubRecord<DIALDATA> DATA; //Dialog Data

        std::vector<Record *> INFO;

        DIALRecord(unsigned char *_recData=NULL);
        DIALRecord(DIALRecord *srcRecord);
        ~DIALRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsTopic();
        void   IsTopic(bool value);
        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsCombat();
        void   IsCombat(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsDetection();
        void   IsDetection(bool value);
        bool   IsService();
        void   IsService(bool value);
        bool   IsMisc();
        void   IsMisc(bool value);
        bool   IsRadio();
        void   IsRadio(bool value);
        bool   IsType(uint8_t Type);
        void   SetType(uint8_t Type);

        bool   IsRumors();
        void   IsRumors(bool value);
        bool   IsTopLevel();
        void   IsTopLevel(bool value);
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

        bool operator ==(const DIALRecord &other) const;
        bool operator !=(const DIALRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}