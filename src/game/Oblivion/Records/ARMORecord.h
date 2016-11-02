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
#include "common/Common.h"
#include "common/GenericRecord.h"

namespace Ob
{
class ARMORecord : public Record //Armor
    {
    private:
        #pragma pack(push)
        #pragma pack(2)
        struct ARMODATA
            {
            uint16_t  strength;
            uint32_t  value, health;
            float weight;

            ARMODATA();
            ~ARMODATA();

            bool operator ==(const ARMODATA &other) const;
            bool operator !=(const ARMODATA &other) const;
            };
        #pragma pack(pop)

        enum flagsFlags
            {
            fIsHead        = 0x00000001,
            fIsHair        = 0x00000002,
            fIsUpperBody   = 0x00000004,
            fIsLowerBody   = 0x00000008,
            fIsHand        = 0x00000010,
            fIsFoot        = 0x00000020,
            fIsRightRing   = 0x00000040,
            fIsLeftRing    = 0x00000080,
            fIsAmulet      = 0x00000100,
            fIsWeapon      = 0x00000200,
            fIsBackWeapon  = 0x00000400,
            fIsSideWeapon  = 0x00000800,
            fIsQuiver      = 0x00001000,
            fIsShield      = 0x00002000,
            fIsTorch       = 0x00004000,
            fIsTail        = 0x00008000,
            fIsHideRings   = 0x00010000,
            fIsHideAmulets = 0x00020000,
            fIsNonPlayable = 0x00400000,
            fIsHeavyArmor  = 0x00800000
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSimpleSubRecord<FORMID> ENAM; //Enchantment
        OptSimpleSubRecord<uint16_t> ANAM; //Enchantment Points
        ReqSimpleSubRecord<uint32_t> BMDT; //Biped Flags
        OptSubRecord<GENMODEL> MODL; //Male Biped Model
        OptSubRecord<GENMODEL> MOD2; //Male World Model
        StringRecord ICON; //Male icon filename
        OptSubRecord<GENMODEL> MOD3; //Female Biped Model
        OptSubRecord<GENMODEL> MOD4; //Female World Model
        StringRecord ICO2; //Female icon filename
        ReqSubRecord<ARMODATA> DATA; //Equipment Data

        ARMORecord(unsigned char *_recData=NULL);
        ARMORecord(ARMORecord *srcRecord);
        ~ARMORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHead();
        void   IsHead(bool value);
        bool   IsHair();
        void   IsHair(bool value);
        bool   IsUpperBody();
        void   IsUpperBody(bool value);
        bool   IsLowerBody();
        void   IsLowerBody(bool value);
        bool   IsHand();
        void   IsHand(bool value);
        bool   IsFoot();
        void   IsFoot(bool value);
        bool   IsRightRing();
        void   IsRightRing(bool value);
        bool   IsLeftRing();
        void   IsLeftRing(bool value);
        bool   IsAmulet();
        void   IsAmulet(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsBackWeapon();
        void   IsBackWeapon(bool value);
        bool   IsSideWeapon();
        void   IsSideWeapon(bool value);
        bool   IsQuiver();
        void   IsQuiver(bool value);
        bool   IsShield();
        void   IsShield(bool value);
        bool   IsTorch();
        void   IsTorch(bool value);
        bool   IsTail();
        void   IsTail(bool value);
        bool   IsHideRings();
        void   IsHideRings(bool value);
        bool   IsHideAmulets();
        void   IsHideAmulets(bool value);
        bool   IsNonPlayable();
        void   IsNonPlayable(bool value);
        bool   IsHeavyArmor();
        void   IsHeavyArmor(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const ARMORecord &other) const;
        bool operator !=(const ARMORecord &other) const;
        bool equals(Record *other);
    };
}