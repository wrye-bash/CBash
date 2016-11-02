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
class CHALRecord : public FNVRecord //Challenge
    {
    private:
        struct CHALDATA //Data
            {
            uint32_t  challengeType, threshold, flags, interval; //Type, Threshold, Flags, Interval
            uint8_t   var1[2], var2[2], var3[4]; //(depends on type)

            CHALDATA();
            ~CHALDATA();

            bool operator ==(const CHALDATA &other) const;
            bool operator !=(const CHALDATA &other) const;
            };

        enum challengeTypeTypes
            {
            eKillFromList = 0,
            eKillFormID,
            eKillInCategory,
            eHitEnemy,
            eDiscoverMapMarker,
            eUseItem,
            eGetItem,
            eUseSkill,
            eDoDamage,
            eUseItemFromList,
            eGetItemFromList,
            eMiscStat
            };

        enum challengeFlags
            {
            fIsStartDisabled    = 0x00000001,
            fIsRecurring        = 0x00000002,
            fIsShowZeroProgress = 0x00000004
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> SCRI; //Script
        StringRecord DESC; //Description
        OptSubRecord<CHALDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> SNAM; //(depends on type)
        OptSimpleSubRecord<FORMID> XNAM; //(depends on type)

        CHALRecord(unsigned char *_recData=NULL);
        CHALRecord(CHALRecord *srcRecord);
        ~CHALRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsStartDisabled();
        void   IsStartDisabled(bool value);
        bool   IsRecurring();
        void   IsRecurring(bool value);
        bool   IsShowZeroProgress();
        void   IsShowZeroProgress(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        bool   IsKillFromList();
        bool   IsKillFormID();
        bool   IsKillInCategory();
        bool   IsHitEnemy();
        bool   IsDiscoverMapMarker();
        bool   IsUseItem();
        bool   IsGetItem();
        bool   IsUseSkill();
        bool   IsDoDamage();
        bool   IsUseItemFromList();
        bool   IsGetItemFromList();
        bool   IsMiscStat();
        bool   IsType(uint8_t Type);
        void   SetType(uint8_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const CHALRecord &other) const;
        bool operator !=(const CHALRecord &other) const;
        bool equals(Record *other);
    };
}