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

namespace FNV
{
class PROJRecord : public FNVRecord //Projectile
    {
    private:
        struct PROJDATA
            {
            uint16_t  flags, projType;
            float gravity, speed, range;
            FORMID  light, flash;
            float tracerChance, altExplProximityTrigger, altExplProximityTimer;
            FORMID  explosion, sound;
            float flashDuration, fadeDuration, impactForce;
            FORMID  soundCountdown, soundDisable, defaultWeaponSource;
            //Below are not always in chunk...
            float rotX, rotY, rotZ, bouncyMult;

            PROJDATA();
            ~PROJDATA();

            bool operator ==(const PROJDATA &other) const;
            bool operator !=(const PROJDATA &other) const;
            };

        enum flagsFlags
            {
            fIsHitscan              = 0x0001,
            fIsExplosion            = 0x0002,
            fIsAltTrigger           = 0x0004,
            fIsMuzzleFlash          = 0x0008,
            fIsDisableable          = 0x0020,
            fIsPickupable           = 0x0040,
            fIsSupersonic           = 0x0080,
            fIsPinsLimbs            = 0x0100,
            fIsPassSmallTransparent = 0x0200,
            fIsDetonates            = 0x0400,
            fIsRotation             = 0x0800
            };

        enum projTypeTypes
            {
            eMissile        = 1,
            eLobber         = 2,
            eBeam           = 4,
            eFlame          = 8,
            eContinuousBeam = 16
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };
    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        ReqSubRecord<PROJDATA> DATA; //Data
        StringRecord NAM1; //Model Filename
        RawRecord NAM2; //Texture Files Hashes
        OptSimpleSubRecord<uint32_t> VNAM; //Sound Level

        PROJRecord(unsigned char *_recData=NULL);
        PROJRecord(PROJRecord *srcRecord);
        ~PROJRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHitscan();
        void   IsHitscan(bool value);
        bool   IsExplosion();
        void   IsExplosion(bool value);
        bool   IsAltTrigger();
        void   IsAltTrigger(bool value);
        bool   IsMuzzleFlash();
        void   IsMuzzleFlash(bool value);
        bool   IsDisableable();
        void   IsDisableable(bool value);
        bool   IsPickupable();
        void   IsPickupable(bool value);
        bool   IsSupersonic();
        void   IsSupersonic(bool value);
        bool   IsPinsLimbs();
        void   IsPinsLimbs(bool value);
        bool   IsPassSmallTransparent();
        void   IsPassSmallTransparent(bool value);
        bool   IsDetonates();
        void   IsDetonates(bool value);
        bool   IsRotation();
        void   IsRotation(bool value);
        bool   IsFlagMask(uint16_t Mask, bool Exact=false);
        void   SetFlagMask(uint16_t Mask);

        bool   IsMissile();
        void   IsMissile(bool value);
        bool   IsLobber();
        void   IsLobber(bool value);
        bool   IsBeam();
        void   IsBeam(bool value);
        bool   IsFlame();
        void   IsFlame(bool value);
        bool   IsContinuousBeam();
        void   IsContinuousBeam(bool value);
        bool   IsType(uint16_t Type);
        void   SetType(uint16_t Type);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(uint32_t Type);
        void   SetSoundLevelType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const PROJRecord &other) const;
        bool operator !=(const PROJRecord &other) const;
        bool equals(Record *other);
    };
}