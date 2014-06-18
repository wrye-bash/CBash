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
class WEAPRecord : public Record
    {
    private:
        #pragma pack(push)
        #pragma pack(2)
        struct WEAPDATA
            {
            uint32_t  weaponType;
            float speed, reach;
            uint32_t  flags, value, health;
            float weight;
            uint16_t  damage;

            WEAPDATA();
            ~WEAPDATA();

            bool operator ==(const WEAPDATA &other) const;
            bool operator !=(const WEAPDATA &other) const;
            };
        #pragma pack(pop)

        enum flagsFlags
            {
            fIsNotNormalWeapon = 0x00000001
            };

        enum eWeaponType
            {
            eBlade1Hand = 0,
            eBlade2Hand = 1,
            eBlunt1Hand = 2,
            eBlunt2Hand = 3,
            eStaff      = 4,
            eBow        = 5
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<FORMID> ENAM; //Enchantment
        OptSimpleSubRecord<uint16_t> ANAM; //Enchantment Points
        ReqSubRecord<WEAPDATA> DATA; //Weapon Data

        WEAPRecord(unsigned char *_recData=NULL);
        WEAPRecord(WEAPRecord *srcRecord);
        ~WEAPRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNotNormalWeapon();
        void   IsNotNormalWeapon(bool value);
        bool   IsNotNormal();
        void   IsNotNormal(bool value);
        bool   IsNormalWeapon();
        void   IsNormalWeapon(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsBlade1Hand();
        void   IsBlade1Hand(bool value);
        bool   IsBlade2Hand();
        void   IsBlade2Hand(bool value);
        bool   IsBlunt1Hand();
        void   IsBlunt1Hand(bool value);
        bool   IsBlunt2Hand();
        void   IsBlunt2Hand(bool value);
        bool   IsStaff();
        void   IsStaff(bool value);
        bool   IsBow();
        void   IsBow(bool value);
        bool   IsType(uint32_t Type);
        void   SetType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const WEAPRecord &other) const;
        bool operator !=(const WEAPRecord &other) const;
        bool equals(Record *other);
    };
}