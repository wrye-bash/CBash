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
class MGEFRecord : public FNVRecord //Base Effect
    {
    private:
        struct MGEFDATA
            {
            UINT32  flags;
            FLOAT32 baseCost; //Unused
            FORMID  associated;
            UINT32  schoolType; //Unused
            SINT32  resistType;
            UINT16  numCounters; //According to OBME
            UINT8   unused1[2];
            FORMID  light;
            FLOAT32 projectileSpeed;
            FORMID  effectShader, displayShader, effectSound, boltSound, hitSound, areaSound;
            FLOAT32 cefEnchantment, cefBarter; //Unused, Unused
            UINT32  archType;
            SINT32  actorValue;

            MGEFDATA();
            ~MGEFDATA();

            bool operator ==(const MGEFDATA &other) const;
            bool operator !=(const MGEFDATA &other) const;
            };

        enum flagsFlags
            {
            fIsHostile              = 0x00000001,
            fIsRecover              = 0x00000002,
            fIsDetrimental          = 0x00000004,
            //fIsMagnitudeIsPercent = 0x00000008,
            fIsSelf                 = 0x00000010,
            fIsTouch                = 0x00000020,
            fIsTarget               = 0x00000040,
            fIsNoDuration           = 0x00000080,
            fIsNoMagnitude          = 0x00000100,
            fIsNoArea               = 0x00000200,
            fIsFXPersist            = 0x00000400,
            //fIsSpellmaking        = 0x00000800,
            fIsGoryVisuals          = 0x00001000,
            fIsDisplayNameOnly      = 0x00002000,
            //fIsUnknownF           = 0x00004000,
            fIsRadioBroadcast       = 0x00008000, //??
            //fIsUseWeapon          = 0x00010000,
            //fIsUseArmor           = 0x00020000,
            //fIsUseCreature        = 0x00040000,
            fIsUseSkill             = 0x00080000,
            fIsUseAttr              = 0x00100000,
            //fIsPCHasEffect        = 0x00200000,
            //fIsDisabled           = 0x00400000,
            //fIsUnknownO           = 0x00800000,
            fIsPainless             = 0x01000000,
            fIsSprayType            = 0x02000000,
            fIsBoltType             = 0x04000000,
            fIsFogType              = 0x06000000,
            fIsNoHitEffect          = 0x08000000,
            fIsPersistOnDeath       = 0x10000000,
            fIsUnknown1             = 0x20000000
            };

        enum archTypes
            {
            eValueModifier  = 0,
            eScript         = 1,
            eDispel         = 2,
            eCureDisease    = 3,
            eInvisibility   = 11,
            eChameleon      = 12,
            eLight          = 13,
            eLock           = 16,
            eOpen           = 17,
            eBoundItem      = 18,
            eSummonCreature = 19,
            eParalysis      = 24,
            eCureParalysis  = 30,
            eCureAddiction  = 31,
            eCurePoison     = 32,
            eConcussion     = 33,
            eValueAndParts  = 34,
            eLimbCondition  = 35,
            eTurbo          = 36
            };

        enum eSchools
            {
            eAlteration = 0,
            eConjuration,
            eDestruction,
            eIllusion,
            eMysticism,
            eRestoration
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSubRecord<FNVMODEL> MODL; //Model
        ReqSubRecord<MGEFDATA> DATA; //Data

        MGEFRecord(unsigned char *_recData=NULL);
        MGEFRecord(MGEFRecord *srcRecord);
        ~MGEFRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHostile();
        void   IsHostile(bool value);
        bool   IsRecover();
        void   IsRecover(bool value);
        bool   IsDetrimental();
        void   IsDetrimental(bool value);
        bool   IsSelf();
        void   IsSelf(bool value);
        bool   IsTouch();
        void   IsTouch(bool value);
        bool   IsTarget();
        void   IsTarget(bool value);
        bool   IsNoDuration();
        void   IsNoDuration(bool value);
        bool   IsNoMagnitude();
        void   IsNoMagnitude(bool value);
        bool   IsNoArea();
        void   IsNoArea(bool value);
        bool   IsFXPersist();
        void   IsFXPersist(bool value);
        bool   IsGoryVisuals();
        void   IsGoryVisuals(bool value);
        bool   IsDisplayNameOnly();
        void   IsDisplayNameOnly(bool value);
        bool   IsRadioBroadcast();
        void   IsRadioBroadcast(bool value);
        bool   IsUseSkill();
        void   IsUseSkill(bool value);
        bool   IsUseAttr();
        void   IsUseAttr(bool value);
        bool   IsPainless();
        void   IsPainless(bool value);
        bool   IsSprayType();
        void   IsSprayType(bool value);
        bool   IsBoltType();
        void   IsBoltType(bool value);
        bool   IsFogType();
        void   IsFogType(bool value);
        bool   IsBallType();
        void   IsBallType(bool value);
        bool   IsNoHitEffect();
        void   IsNoHitEffect(bool value);
        bool   IsPersistOnDeath();
        void   IsPersistOnDeath(bool value);
        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsValueModifier();
        void   IsValueModifier(bool value);
        bool   IsScript();
        void   IsScript(bool value);
        bool   IsDispel();
        void   IsDispel(bool value);
        bool   IsCureDisease();
        void   IsCureDisease(bool value);
        bool   IsInvisibility();
        void   IsInvisibility(bool value);
        bool   IsChameleon();
        void   IsChameleon(bool value);
        bool   IsLight();
        void   IsLight(bool value);
        bool   IsLock();
        void   IsLock(bool value);
        bool   IsOpen();
        void   IsOpen(bool value);
        bool   IsBoundItem();
        void   IsBoundItem(bool value);
        bool   IsSummonCreature();
        void   IsSummonCreature(bool value);
        bool   IsParalysis();
        void   IsParalysis(bool value);
        bool   IsCureParalysis();
        void   IsCureParalysis(bool value);
        bool   IsCureAddiction();
        void   IsCureAddiction(bool value);
        bool   IsCurePoison();
        void   IsCurePoison(bool value);
        bool   IsConcussion();
        void   IsConcussion(bool value);
        bool   IsValueAndParts();
        void   IsValueAndParts(bool value);
        bool   IsLimbCondition();
        void   IsLimbCondition(bool value);
        bool   IsTurbo();
        void   IsTurbo(bool value);
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        bool   IsSchoolAlteration();
        void   IsSchoolAlteration(bool value);
        bool   IsSchoolConjuration();
        void   IsSchoolConjuration(bool value);
        bool   IsSchoolDestruction();
        void   IsSchoolDestruction(bool value);
        bool   IsSchoolIllusion();
        void   IsSchoolIllusion(bool value);
        bool   IsSchoolMysticism();
        void   IsSchoolMysticism(bool value);
        bool   IsSchoolRestoration();
        void   IsSchoolRestoration(bool value);
        bool   IsSchool(UINT32 Type);
        void   SetSchool(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const MGEFRecord &other) const;
        bool operator !=(const MGEFRecord &other) const;
        bool equals(Record *other);
    };
}