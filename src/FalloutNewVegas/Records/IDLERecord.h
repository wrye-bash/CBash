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
class IDLERecord : public FNVRecord //Idle Animation
    {
    private:
        struct IDLEDATA
            {
            uint8_t   group, minLooping, maxLooping, unused1;
            int16_t  replayDelay;
            //Below are not always present on chunk...
            uint8_t   flags, unused2;

            IDLEDATA();
            ~IDLEDATA();

            bool operator ==(const IDLEDATA &other) const;
            bool operator !=(const IDLEDATA &other) const;
            };

        enum groupType
            {
            eIdle        = 0,
            eMovement    = 1,
            eLeftArm     = 2,
            eLeftHand    = 3,
            eWeapon      = 4,
            eWeaponUp    = 5,
            eWeaponDown  = 6,
            eSpecialIdle = 7,
            eWholeBody   = 20,
            eUpperBody   = 21
            };

        enum groupFlag
            {
            fIsUnknown1      = 0x40,
            fIsNotReturnFile = 0x80
            };

        enum flagsFlags
            {
            fIsNoAttacking = 0x01
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
        UnorderedPackedArray<FORMID> ANAM; //Related Idle Animations
        ReqSubRecord<IDLEDATA> DATA; //Data

        IDLERecord(unsigned char *_recData=NULL);
        IDLERecord(IDLERecord *srcRecord);
        ~IDLERecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoAttacking();
        void   IsNoAttacking(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        bool   IsIdle();
        void   IsIdle(bool value);
        bool   IsMovement();
        void   IsMovement(bool value);
        bool   IsLeftArm();
        void   IsLeftArm(bool value);
        bool   IsLeftHand();
        void   IsLeftHand(bool value);
        bool   IsWeapon();
        void   IsWeapon(bool value);
        bool   IsWeaponUp();
        void   IsWeaponUp(bool value);
        bool   IsWeaponDown();
        void   IsWeaponDown(bool value);
        bool   IsSpecialIdle();
        void   IsSpecialIdle(bool value);
        bool   IsWholeBody();
        void   IsWholeBody(bool value);
        bool   IsUpperBody();
        void   IsUpperBody(bool value);
        bool   IsType(uint8_t Type);
        void   SetType(uint8_t Type);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsNotReturnFile();
        void   IsNotReturnFile(bool value);
        bool   IsReturnFile();
        void   IsReturnFile(bool value);
        bool   IsIdleFlagMask(uint8_t Mask, bool Exact=false);
        void   SetIdleFlagMask(uint8_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const IDLERecord &other) const;
        bool operator !=(const IDLERecord &other) const;
        bool equals(Record *other);
    };
}