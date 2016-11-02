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
class BPTDRecord : public FNVRecord //Body Part Data
    {
    private:
        struct BPTDBPND
            {
            float damageMult;
            uint8_t   flags, partType, healthPercent;
            int8_t   actorValue;
            uint8_t   hitChance, explodableExplosionChance;
            uint16_t  explodableDebrisCount;
            FORMID  explodableDebris, explodableExplosion;
            float maxTrackAngle, explodableDebrisScale;
            int32_t  severableDebrisCount;
            FORMID  severableDebris, severableExplosion;
            float severableDebrisScale;

            //Gore Positioning
            float transX, transY, transZ, rotX, rotY, rotZ;

            FORMID  severableImpact, explodableImpact;
            uint8_t   severableDecalCount, explodableDecalCount, unused1[2];
            float limbReplaceScale;

            BPTDBPND();
            ~BPTDBPND();

            bool operator ==(const BPTDBPND &other) const;
            bool operator !=(const BPTDBPND &other) const;
            };

        struct BPTDPart //Body Part
            {
            StringRecord BPTN; //Part Name
            StringRecord BPNN; //Part Node
            StringRecord BPNT; //VATS Target
            StringRecord BPNI; //IK Data - Start Node
            ReqSubRecord<BPTDBPND> BPND; //Data
            StringRecord NAM1; //Limb Replacement Model
            StringRecord NAM4; //Gore Effects - Target Bone
            RawRecord NAM5; //Texture Files Hashes

            enum flagFlags
                {
                fIsSeverable          = 0x00000001,
                fIsIKData             = 0x00000002,
                fIsIKDataBipedData    = 0x00000004,
                fIsExplodable         = 0x00000008,
                fIsIKDataIsHead       = 0x00000010,
                fIsIKDataHeadTracking = 0x00000020,
                fIsAbsoluteHitChance  = 0x00000040
                };

            enum partTypes
                {
                eTorso = 0,
                eHead1,
                eHead2,
                eLeftArm1,
                eLeftArm2,
                eRightArm1,
                eRightArm2,
                eLeftLeg1,
                eLeftLeg2,
                eLeftLeg3,
                eRightLeg1,
                eRightLeg2,
                eRightLeg3,
                eBrain,
                eWeapon
                };

            bool   IsSeverable();
            void   IsSeverable(bool value);
            bool   IsIKData();
            void   IsIKData(bool value);
            bool   IsIKDataBipedData();
            void   IsIKDataBipedData(bool value);
            bool   IsExplodable();
            void   IsExplodable(bool value);
            bool   IsIKDataIsHead();
            void   IsIKDataIsHead(bool value);
            bool   IsIKDataHeadTracking();
            void   IsIKDataHeadTracking(bool value);
            bool   IsAbsoluteHitChance();
            void   IsAbsoluteHitChance(bool value);
            bool   IsFlagMask(uint8_t Mask, bool Exact=false);
            void   SetFlagMask(uint8_t Mask);

            bool   IsTorso();
            void   IsTorso(bool value);
            bool   IsHead1();
            void   IsHead1(bool value);
            bool   IsHead2();
            void   IsHead2(bool value);
            bool   IsLeftArm1();
            void   IsLeftArm1(bool value);
            bool   IsLeftArm2();
            void   IsLeftArm2(bool value);
            bool   IsRightArm1();
            void   IsRightArm1(bool value);
            bool   IsRightArm2();
            void   IsRightArm2(bool value);
            bool   IsLeftLeg1();
            void   IsLeftLeg1(bool value);
            bool   IsLeftLeg2();
            void   IsLeftLeg2(bool value);
            bool   IsLeftLeg3();
            void   IsLeftLeg3(bool value);
            bool   IsRightLeg1();
            void   IsRightLeg1(bool value);
            bool   IsRightLeg2();
            void   IsRightLeg2(bool value);
            bool   IsRightLeg3();
            void   IsRightLeg3(bool value);
            bool   IsBrain();
            void   IsBrain(bool value);
            bool   IsWeapon();
            void   IsWeapon(bool value);
            bool   IsType(uint8_t Type);
            void   SetType(uint8_t Type);

            void Write(FileWriter &writer);

            bool operator ==(const BPTDPart &other) const;
            bool operator !=(const BPTDPart &other) const;
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        UnorderedSparseArray<BPTDPart *> Parts; //Body Parts
        ReqSimpleSubRecord<FORMID> RAGA; //Ragdoll

        BPTDRecord(unsigned char *_recData=NULL);
        BPTDRecord(BPTDRecord *srcRecord);
        ~BPTDRecord();

        bool   VisitFormIDs(FormIDOp &op);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk = false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const BPTDRecord &other) const;
        bool operator !=(const BPTDRecord &other) const;
        bool equals(Record *other);
    };
}