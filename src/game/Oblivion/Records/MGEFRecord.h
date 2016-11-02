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
class MGEFRecord : public Record //Base Effect
    {
    private:
        struct MGEFDATA
            {
            uint32_t  flags;
            float baseCost;
            FORMID  associated;
            uint32_t  schoolType;
            uint32_t  resistValue;
            uint16_t  numCounters; //According to OBME
            uint8_t   unused1[2];
            FORMID  light;
            float projectileSpeed;
            FORMID  effectShader, enchantEffect, castingSound, boltSound, hitSound, areaSound;
            float cefEnchantment, cefBarter;

            MGEFDATA();
            ~MGEFDATA();

            bool operator ==(const MGEFDATA &other) const;
            bool operator !=(const MGEFDATA &other) const;
            };

        struct OBMEEDDX
            {
            char    mgefCode[5];

            OBMEEDDX();
            ~OBMEEDDX();

            bool operator ==(const OBMEEDDX &other) const;
            bool operator !=(const OBMEEDDX &other) const;
            };

        struct MGEFOBME
            {
            uint8_t   recordVersion, betaVersion, minorVersion, majorVersion;
            uint8_t   mgefParamAInfo;
            uint8_t   mgefParamBInfo;
            uint8_t   reserved1[2];
            uint32_t  handlerCode;
            uint32_t  flags;
            uint32_t  mgefParamB;
            uint8_t   reserved2[0x1C];

            MGEFOBME();
            ~MGEFOBME();

            bool operator ==(const MGEFOBME &other) const;
            bool operator !=(const MGEFOBME &other) const;
            };

        struct OBMEMGEF
            {
            ReqSubRecord<MGEFOBME> OBME;
            //Uses SubRecord so that it isn't reloaded everytime the record is parsed
            SubRecord<OBMEEDDX> EDDX; //Is switched with the normal EDID on read and write so that the EDID field is a char *as expected
            RawRecord DATX;

            bool operator ==(const OBMEMGEF &other) const;
            bool operator !=(const OBMEMGEF &other) const;
            };

        //Note: the vanilla code discards mod changes to most flag bits
        //  only those listed as changeable below may be edited by non-obme mods
        // comments garnered from JRoush's OBME
        enum flagsFlags
            {
            fIsHostile            = 0x00000001,
            fIsRecover            = 0x00000002,
            fIsDetrimental        = 0x00000004, //OBME Deprecated, used for ValueModifier effects AV is decreased rather than increased
            fIsMagnitudeIsPercent = 0x00000008, //OBME Deprecated
            fIsSelf               = 0x00000010,
            fIsTouch              = 0x00000020,
            fIsTarget             = 0x00000040,
            fIsNoDuration         = 0x00000080,
            fIsNoMagnitude        = 0x00000100,
            fIsNoArea             = 0x00000200,
            fIsFXPersist          = 0x00000400, //Changeable
            fIsSpellmaking        = 0x00000800, //Changeable
            fIsEnchanting         = 0x00001000, //Changeable
            fIsNoIngredient       = 0x00002000, //Changeable
            fIsUnknownF           = 0x00004000, //no effects have this flag set
            fIsNoRecast           = 0x00008000, //no effects have this flag set
            fIsUseWeapon          = 0x00010000, //OBME Deprecated
            fIsUseArmor           = 0x00020000, //OBME Deprecated
            fIsUseCreature        = 0x00040000, //OBME Deprecated
            fIsUseSkill           = 0x00080000, //OBME Deprecated
            fIsUseAttr            = 0x00100000, //OBME Deprecated
            fIsPCHasEffect        = 0x00200000, //whether or not PC has effect, forced to zero during loading
            fIsDisabled           = 0x00400000, //Changeable, many (all?) methods that loop over effects ignore those with this flag.
                                                //  Spells with an effect with this flag are apparently uncastable.

            fIsUnknownO           = 0x00800000, //Changeable, POSN,DISE - these effects have *only* this bit set,
                                                //  perhaps a flag for meta effects

            fIsUseAV              = 0x01000000, //OBME Deprecated, Changeable, but once set (by default or by a previously loaded mod file)
                                                //  it cannot be unset by another mod, nor can the mgefParam be overriden

            fIsSprayType          = 0x02000000, //Changeable
            fIsBoltType           = 0x04000000, //Changeable
            fIsFogType            = 0x06000000, //Changeable
            fIsNoHitEffect        = 0x08000000, //Changeable, no hit shader on target
            fIsPersistOnDeath     = 0x10000000, //Effect is not automatically removed when its target dies
            fIsExplodesWithForce  = 0x20000000, //causes explosion that can move loose objects (e.g. ragdolls)
            fIsMagnitudeIsLevel   = 0x40000000, //OBME Deprecated
            fIsMagnitudeIsFeet    = 0x80000000  //OBME Deprecated
            };

        //When OBME is in use, flagsFlags with the same bits are redefined to the following
        //  The new flags are also stored in a new field
        enum obmeFlags
            {
            fOBME_IsBeneficial       = 0x00000008,
            fOBME_IsMagnitudeIsRange = 0x00020000,
            fOBME_IsAtomicResistance = 0x00040000,
            fOBME_IsParamFlagA       = 0x00000004, //Meaning varies with effect handler
            fOBME_IsParamFlagB       = 0x00010000, //Meaning varies with effect handler
            fOBME_IsParamFlagC       = 0x00080000, //Meaning varies with effect handler
            fOBME_IsParamFlagD       = 0x00100000, //Meaning varies with effect handler
            fOBME_IsHidden           = 0x40000000
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
        OptSubRecord<GENMODEL> MODL; //Model
        ReqSubRecord<MGEFDATA> DATA; //Data
        UnorderedPackedArray<MGEFCODE_OR_UINT32> ESCE; //Counter Effects
        OptSubRecord<OBMEMGEF> OBME; //OBME Extended Data

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
        bool   IsMagnitudeIsPercent();
        void   IsMagnitudeIsPercent(bool value);
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
        bool   IsSpellmaking();
        void   IsSpellmaking(bool value);
        bool   IsEnchanting();
        void   IsEnchanting(bool value);
        bool   IsNoIngredient();
        void   IsNoIngredient(bool value);
        bool   IsUnknownF();
        void   IsUnknownF(bool value);
        bool   IsNoRecast();
        void   IsNoRecast(bool value);
        bool   IsUseWeapon();
        void   IsUseWeapon(bool value);
        bool   IsUseArmor();
        void   IsUseArmor(bool value);
        bool   IsUseCreature();
        void   IsUseCreature(bool value);
        bool   IsUseSkill();
        void   IsUseSkill(bool value);
        bool   IsUseAttribute();
        void   IsUseAttribute(bool value);
        bool   IsUseAttr();
        void   IsUseAttr(bool value);
        bool   IsPCHasEffect();
        void   IsPCHasEffect(bool value);
        bool   IsDisabled();
        void   IsDisabled(bool value);
        bool   IsUnknownO();
        void   IsUnknownO(bool value);
        bool   IsUseActorValue();
        void   IsUseActorValue(bool value);
        bool   IsUseAV();
        void   IsUseAV(bool value);
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
        bool   IsExplodesWithForce();
        void   IsExplodesWithForce(bool value);
        bool   IsMagnitudeIsLevel();
        void   IsMagnitudeIsLevel(bool value);
        bool   IsMagnitudeIsFeet();
        void   IsMagnitudeIsFeet(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        //OBME flags
        bool   IsBeneficial();
        void   IsBeneficial(bool value);
        bool   IsMagnitudeIsRange();
        void   IsMagnitudeIsRange(bool value);
        bool   IsAtomicResistance();
        void   IsAtomicResistance(bool value);
        bool   IsParamFlagA();
        void   IsParamFlagA(bool value);
        bool   IsParamFlagB();
        void   IsParamFlagB(bool value);
        bool   IsParamFlagC();
        void   IsParamFlagC(bool value);
        bool   IsParamFlagD();
        void   IsParamFlagD(bool value);
        bool   IsHidden();
        void   IsHidden(bool value);
        bool   IsOBMEFlagMask(uint32_t Mask, bool Exact=false);
        void   SetOBMEFlagMask(uint32_t Mask);

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
        bool   IsSchool(uint32_t Type);
        void   SetSchool(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();
        bool   IsKeyedByEditorID();
        char * GetEditorIDKey();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const MGEFRecord &other) const;
        bool operator !=(const MGEFRecord &other) const;
        bool equals(Record *other);
    };
}