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
// BaseRecord.h
#include "Common.h"
#include <vector>

class FormIDOp
    {
    protected:
        UINT32 count;
        bool stop;

    public:
        bool result;

        FormIDOp();
        virtual ~FormIDOp();

        virtual bool Accept(UINT32 &curFormID) abstract {};
        virtual bool AcceptMGEF(UINT32 &curMgefCode) abstract {};

        UINT32 GetCount();
        void ResetCount();
        bool Stop();
    };

class FormIDResolver : public FormIDOp
    {
    private:
        const UINT8 (&ResolveTable)[256];
        //UINT8 ModIndex;

    public:
        const unsigned char * const FileStart;
        const unsigned char * const FileEnd;

        FormIDResolver(const UINT8 (&_ResolveTable)[256], const unsigned char * const _FileStart, const unsigned char * const _FileEnd);
        ~FormIDResolver();

        bool Accept(UINT32 &curFormID);
        bool AcceptMGEF(UINT32 &curMgefCode);
    };

struct GENXNAM
    {
    FORMID  faction;
    SINT32  mod;

    GENXNAM();
    ~GENXNAM();

    bool operator ==(const GENXNAM &other) const;
    bool operator !=(const GENXNAM &other) const;
    };

struct GENSCHR
    {
    UINT8   unused1[4];
    UINT32  numRefs, compiledSize, lastIndex, scriptType;

    GENSCHR();
    ~GENSCHR();

    bool operator ==(const GENSCHR &other) const;
    bool operator !=(const GENSCHR &other) const;
    };

struct GENSCR_
    {
    FORMID_OR_UINT32 reference;
    bool    isSCRO;

    GENSCR_();
    ~GENSCR_();

    void Write(FileWriter &writer);

    bool operator ==(const GENSCR_ &other) const;
    bool operator !=(const GENSCR_ &other) const;
    };

struct GENSLSD
    {
    UINT32  index;
    UINT8   unused1[12], flags, unused2[7];

    GENSLSD();
    ~GENSLSD();

    bool operator ==(const GENSLSD &other) const;
    bool operator !=(const GENSLSD &other) const;
    };

struct GENVARS
    {
    ReqSubRecord<GENSLSD> SLSD;
    StringRecord SCVR;

    enum flagsFlags
        {
        fIsLongOrShort = 0x00000001
        };

    bool   IsLongOrShort();
    void   IsLongOrShort(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    void Write(FileWriter &writer);

    bool operator ==(const GENVARS &other) const;
    bool operator !=(const GENVARS &other) const;
    };

struct sortVARS
    {
    bool operator()(const GENVARS *lhs, const GENVARS *rhs) const;
    };

struct FNVSCHR
    {
    UINT8   unused1[4];
    UINT32  numRefs, compiledSize, lastIndex;
    UINT16  scriptType, flags;

    FNVSCHR();
    ~FNVSCHR();

    bool operator ==(const FNVSCHR &other) const;
    bool operator !=(const FNVSCHR &other) const;
    };

struct GENEFIT
    {
    MGEFCODE_OR_UINT32 name;
    UINT32  magnitude, area, duration, rangeType;
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 actorValue;

    GENEFIT();
    ~GENEFIT();

    bool operator ==(const GENEFIT &other) const;
    bool operator !=(const GENEFIT &other) const;
    };

struct GENSCIT
    {
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 script;
    UINT32  schoolType;
    MGEFCODE_OR_UINT32 visual;
    UINT8   flags, unused1[3];

    GENSCIT();
    ~GENSCIT();

    bool operator ==(const GENSCIT &other) const;
    bool operator !=(const GENSCIT &other) const;
    };

struct OBMEEFME
    {
    UINT8   recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8   efitParamInfo;
    UINT8   efixParamInfo;
    UINT8   reserved[0xA];

    OBMEEFME();
    ~OBMEEFME();

    bool operator ==(const OBMEEFME &other) const;
    bool operator !=(const OBMEEFME &other) const;
    };

struct OBMEEFIX
    {
    UINT32  efixOverrides;
    UINT32  efixFlags;
    FLOAT32 baseCost;
    ACTORVALUE resistAV;
    UINT8   reserved[0x10];

    OBMEEFIX();
    ~OBMEEFIX();

    bool operator ==(const OBMEEFIX &other) const;
    bool operator !=(const OBMEEFIX &other) const;
    };

struct OBMEEffect
    {
    ReqSubRecord<OBMEEFME> EFME;
    StringRecord EFII;
    OBMEEFIXSubRecord<OBMEEFIX> EFIX;

    bool operator ==(const OBMEEffect &other) const;
    bool operator !=(const OBMEEffect &other) const;
    };

struct GENEffect
    {
    ReqSimpleSubRecord<UINT32> EFID; //Effect ID
    ReqSubRecord<GENEFIT> EFIT; //Effect Data
    OptSubRecord<GENSCIT> SCIT; //Script Effect
    StringRecord FULL; //Effect Name
    OptSubRecord<OBMEEffect> OBME; //OBME Extended Data

    enum eSCITSchools
        {
        eAlteration = 0,
        eConjuration,
        eDestruction,
        eIllusion,
        eMysticism,
        eRestoration
        };

    enum SCITFlags
        {
        fIsHostile = 0x01
        };

    enum eRanges
        {
        eRangeSelf   = 0,
        eRangeTouch  = 1,
        eRangeTarget = 2
        };

    bool IsSchoolAlteration();
    void IsSchoolAlteration(bool value);
    bool IsSchoolConjuration();
    void IsSchoolConjuration(bool value);
    bool IsSchoolDestruction();
    void IsSchoolDestruction(bool value);
    bool IsSchoolIllusion();
    void IsSchoolIllusion(bool value);
    bool IsSchoolMysticism();
    void IsSchoolMysticism(bool value);
    bool IsSchoolRestoration();
    void IsSchoolRestoration(bool value);
    bool IsSchool(UINT32 Type);
    void SetSchool(UINT32 Type);

    enum OBMEOverrideFlags
        {
        fOBME_IsHostile           = 0x00000001,
        fOBME_IsRecovers          = 0x00000002,
        fOBME_IsParamFlagA        = 0x00000004,
        fOBME_IsBeneficial        = 0x00000008,
        fOBME_IsFXPersists        = 0x00000400,
        fOBME_IsUnknownF          = 0x00004000,
        fOBME_IsNoRecast          = 0x00008000,
        fOBME_IsParamFlagB        = 0x00010000,
        fOBME_IsMagnitudeIsRange  = 0x00020000,
        fOBME_IsAtomicResistance  = 0x00040000,
        fOBME_IsParamFlagC        = 0x00080000,
        fOBME_IsParamFlagD        = 0x00100000,
        fOBME_IsDisabled          = 0x00400000,
        fOBME_IsUnknownO          = 0x00800000,
        fOBME_IsNoHitEffect       = 0x08000000,
        fOBME_IsPersistOnDeath    = 0x10000000,
        fOBME_IsExplodesWithForce = 0x20000000,
        fOBME_IsHidden            = 0x40000000
        //fOBME_IsMagnitudeIsFeet = 0x80000000 //Marked as Deprecated
        };

    enum OBMEUsingOverrideFlags
        {
        fOBME_IsUsingHostileOverride           = 0x00000001,
        fOBME_IsUsingRecoversOverride          = 0x00000002,
        fOBME_IsUsingParamFlagAOverride        = 0x00000004,
        fOBME_IsUsingBeneficialOverride        = 0x00000008,
        fOBME_IsUsingEFIXParamOverride         = 0x00000010,
        fOBME_IsUsingSchoolOverride            = 0x00000020,
        fOBME_IsUsingNameOverride              = 0x00000040,
        fOBME_IsUsingVFXCodeOverride           = 0x00000080,
        fOBME_IsUsingBaseCostOverride          = 0x00000100,
        fOBME_IsUsingResistAVOverride          = 0x00000200,
        fOBME_IsUsingFXPersistsOverride        = 0x00000400,
        fOBME_IsUsingIconOverride              = 0x00000800,
        fOBME_IsUsingDoesntTeachOverride       = 0x00001000,
        fOBME_IsUsingUnknownFOverride          = 0x00004000,
        fOBME_IsUsingNoRecastOverride          = 0x00008000,
        fOBME_IsUsingParamFlagBOverride        = 0x00010000,
        fOBME_IsUsingMagnitudeIsRangeOverride  = 0x00020000,
        fOBME_IsUsingAtomicResistanceOverride  = 0x00040000,
        fOBME_IsUsingParamFlagCOverride        = 0x00080000,
        fOBME_IsUsingParamFlagDOverride        = 0x00100000,
        fOBME_IsUsingDisabledOverride          = 0x00400000,
        fOBME_IsUsingUnknownOOverride          = 0x00800000,
        fOBME_IsUsingNoHitEffectOverride       = 0x08000000,
        fOBME_IsUsingPersistOnDeathOverride    = 0x10000000,
        fOBME_IsUsingExplodesWithForceOverride = 0x20000000,
        fOBME_IsUsingHiddenOverride            = 0x40000000
        //fOBME_IsUsingMagnitudeIsFeetOverride = 0x80000000 //Marked as Deprecated
        };

    bool IsHostile();
    void IsHostile(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);

    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(UINT32 Type);
    void SetRange(UINT32 Type);

    bool OBME_IsUsingHostileOverride();
    void OBME_IsUsingHostileOverride(bool value);
    bool OBME_IsUsingRecoversOverride();
    void OBME_IsUsingRecoversOverride(bool value);
    bool OBME_IsUsingParamFlagAOverride();
    void OBME_IsUsingParamFlagAOverride(bool value);
    bool OBME_IsUsingBeneficialOverride();
    void OBME_IsUsingBeneficialOverride(bool value);
    bool OBME_IsUsingEFIXParamOverride();
    void OBME_IsUsingEFIXParamOverride(bool value);
    bool OBME_IsUsingSchoolOverride();
    void OBME_IsUsingSchoolOverride(bool value);
    bool OBME_IsUsingNameOverride();
    void OBME_IsUsingNameOverride(bool value);
    bool OBME_IsUsingVFXCodeOverride();
    void OBME_IsUsingVFXCodeOverride(bool value);
    bool OBME_IsUsingBaseCostOverride();
    void OBME_IsUsingBaseCostOverride(bool value);
    bool OBME_IsUsingResistAVOverride();
    void OBME_IsUsingResistAVOverride(bool value);
    bool OBME_IsUsingFXPersistsOverride();
    void OBME_IsUsingFXPersistsOverride(bool value);
    bool OBME_IsUsingIconOverride();
    void OBME_IsUsingIconOverride(bool value);
    bool OBME_IsUsingDoesntTeachOverride();
    void OBME_IsUsingDoesntTeachOverride(bool value);
    bool OBME_IsUsingUnknownFOverride();
    void OBME_IsUsingUnknownFOverride(bool value);
    bool OBME_IsUsingNoRecastOverride();
    void OBME_IsUsingNoRecastOverride(bool value);
    bool OBME_IsUsingParamFlagBOverride();
    void OBME_IsUsingParamFlagBOverride(bool value);
    bool OBME_IsUsingMagnitudeIsRangeOverride();
    void OBME_IsUsingMagnitudeIsRangeOverride(bool value);
    bool OBME_IsUsingAtomicResistanceOverride();
    void OBME_IsUsingAtomicResistanceOverride(bool value);
    bool OBME_IsUsingParamFlagCOverride();
    void OBME_IsUsingParamFlagCOverride(bool value);
    bool OBME_IsUsingParamFlagDOverride();
    void OBME_IsUsingParamFlagDOverride(bool value);
    bool OBME_IsUsingDisabledOverride();
    void OBME_IsUsingDisabledOverride(bool value);
    bool OBME_IsUsingUnknownOOverride();
    void OBME_IsUsingUnknownOOverride(bool value);
    bool OBME_IsUsingNoHitEffectOverride();
    void OBME_IsUsingNoHitEffectOverride(bool value);
    bool OBME_IsUsingPersistOnDeathOverride();
    void OBME_IsUsingPersistOnDeathOverride(bool value);
    bool OBME_IsUsingExplodesWithForceOverride();
    void OBME_IsUsingExplodesWithForceOverride(bool value);
    bool OBME_IsUsingHiddenOverride();
    void OBME_IsUsingHiddenOverride(bool value);

    bool OBME_IsOverrideFlagMask(UINT32 Mask, bool Exact=false);
    void OBME_SetOverrideFlagMask(UINT32 Mask);

    bool OBME_IsHostile();
    void OBME_IsHostile(bool value);
    bool OBME_IsRecovers();
    void OBME_IsRecovers(bool value);
    bool OBME_IsParamFlagA();
    void OBME_IsParamFlagA(bool value);
    bool OBME_IsBeneficial();
    void OBME_IsBeneficial(bool value);
    bool OBME_IsFXPersists();
    void OBME_IsFXPersists(bool value);
    bool OBME_IsUnknownF();
    void OBME_IsUnknownF(bool value);
    bool OBME_IsNoRecast();
    void OBME_IsNoRecast(bool value);
    bool OBME_IsParamFlagB();
    void OBME_IsParamFlagB(bool value);
    bool OBME_IsMagnitudeIsRange();
    void OBME_IsMagnitudeIsRange(bool value);
    bool OBME_IsAtomicResistance();
    void OBME_IsAtomicResistance(bool value);
    bool OBME_IsParamFlagC();
    void OBME_IsParamFlagC(bool value);
    bool OBME_IsParamFlagD();
    void OBME_IsParamFlagD(bool value);
    bool OBME_IsDisabled();
    void OBME_IsDisabled(bool value);
    bool OBME_IsUnknownO();
    void OBME_IsUnknownO(bool value);
    bool OBME_IsNoHitEffect();
    void OBME_IsNoHitEffect(bool value);
    bool OBME_IsPersistOnDeath();
    void OBME_IsPersistOnDeath(bool value);
    bool OBME_IsExplodesWithForce();
    void OBME_IsExplodesWithForce(bool value);
    bool OBME_IsHidden();
    void OBME_IsHidden(bool value);

    bool OBME_IsFlagMask(UINT32 Mask, bool Exact=false);
    void OBME_SetFlagMask(UINT32 Mask);

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const GENEffect &other) const;
    bool operator !=(const GENEffect &other) const;
    };

struct GENENIT
    {
    SINT32  value;
    UINT8   flags;
    UINT8   unused1[3];

    GENENIT();
    ~GENENIT();

    bool operator ==(const GENENIT &other) const;
    bool operator !=(const GENENIT &other) const;
    };

struct GENVALUEWEIGHT
    {
    UINT32  value;
    FLOAT32 weight;

    GENVALUEWEIGHT();
    ~GENVALUEWEIGHT();

    bool operator ==(const GENVALUEWEIGHT &other) const;
    bool operator !=(const GENVALUEWEIGHT &other) const;
    };

struct GENCNTO
    {
    FORMID  item;
    SINT32  count;

    GENCNTO();
    ~GENCNTO();

    bool operator ==(const GENCNTO &other) const;
    bool operator !=(const GENCNTO &other) const;
    };

struct GENACBS
    {
    UINT32  flags;
    UINT16  baseSpell, fatigue, barterGold;
    SINT16  level;
    UINT16  calcMin, calcMax;

    enum flagsFlags //Used by both npc_ and crea
        {
        fIsEssential     = 0x00000002,
        fIsRespawn       = 0x00000008,
        fIsPCLevelOffset = 0x00000080,
        fIsNoLowLevel    = 0x00000200,
        fIsSummonable    = 0x00004000
        };

    enum npc_Flags
        {
        fIsFemale         = 0x00000001,
        fIsAutoCalc       = 0x00000010,
        fIsNoRumors       = 0x00002000,
        fIsNoPersuasion   = 0x00008000,
        fIsCanCorpseCheck = 0x00100000
        };

    enum creaFlags
        {
        fIsBiped           = 0x00000001,
        fIsWeaponAndShield = 0x00000004,
        fIsSwims           = 0x00000010,
        fIsFlies           = 0x00000020,
        fIsWalks           = 0x00000040,
        fIsNoBloodSpray    = 0x00000800,
        fIsNoBloodDecal    = 0x00001000,
        fIsNoHead          = 0x00008000,
        fIsNoRightArm      = 0x00010000,
        fIsNoLeftArm       = 0x00020000,
        fIsNoCombatInWater = 0x00040000,
        fIsNoShadow        = 0x00080000,
        fIsNoCorpseCheck   = 0x00100000
        };

    GENACBS();
    ~GENACBS();

    bool operator ==(const GENACBS &other) const;
    bool operator !=(const GENACBS &other) const;
    };

struct GENSNAM
    {
    FORMID  faction;
    UINT8   rank, unused1[3];

    GENSNAM();
    ~GENSNAM();

    bool operator ==(const GENSNAM &other) const;
    bool operator !=(const GENSNAM &other) const;
    };

struct GENAIDT
    {
    UINT8   aggression, confidence, energyLevel, responsibility;
    UINT32  flags;
    SINT8   trainSkill;
    UINT8   trainLevel, unused1[2];

    GENAIDT();
    ~GENAIDT();

    bool operator ==(const GENAIDT &other) const;
    bool operator !=(const GENAIDT &other) const;
    };

struct GENCTDA
    {
    UINT8   operType, unused1[3];
    FORMID_OR_FLOAT32 compValue;
    UINT32  ifunc;
    FORMID_OR_UINT32 param1, param2;
    UINT8   unused2[4];

    enum operTypeType
        {
        eEqual          = 0x00,
        eNotEqual       = 0x20,
        eGreater        = 0x40,
        eGreaterOrEqual = 0x60,
        eLess           = 0x80,
        eLessOrEqual    = 0xA0
        };
    enum operTypeFlag
        {
        fIsNone        = 0x00,
        fIsOr          = 0x01,
        fIsRunOnTarget = 0x02,
        fIsUseGlobal   = 0x04
        };

    GENCTDA();
    ~GENCTDA();

    bool IsEqual();
    void IsEqual(bool value);
    bool IsNotEqual();
    void IsNotEqual(bool value);
    bool IsGreater();
    void IsGreater(bool value);
    bool IsGreaterOrEqual();
    void IsGreaterOrEqual(bool value);
    bool IsLess();
    void IsLess(bool value);
    bool IsLessOrEqual();
    void IsLessOrEqual(bool value);
    bool IsType(UINT8 Type);
    void SetType(UINT8 Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal() const;
    void IsUseGlobal(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const GENCTDA &other) const;
    bool operator !=(const GENCTDA &other) const;
    };

struct GENCLR
    {
    UINT8   red, green, blue, unused1;

    GENCLR(UINT8 _red=0, UINT8 _green=0, UINT8 _blue=0, UINT8 _unused1=0);
    ~GENCLR();

    bool operator ==(const GENCLR &other) const;
    bool operator !=(const GENCLR &other) const;
    };

struct GENMODEL
    {
    ReqSimpleFloatSubRecord<flt_0> MODB;
    StringRecord MODL;
    RawRecord MODT;

    void Write(FileWriter &writer);

    bool operator ==(const GENMODEL &other) const;
    bool operator !=(const GENMODEL &other) const;
    };

struct GENXOWN
    {
    ReqSimpleSubRecord<FORMID> XOWN;
    SemiOptSimpleSubRecord<SINT32> XRNK;
    OptSimpleSubRecord<FORMID> XGLB;

    void Write(FileWriter &writer);

    bool operator ==(const GENXOWN &other) const;
    bool operator !=(const GENXOWN &other) const;
    };

struct GENXPCI
    {
    OptSimpleSubRecord<FORMID> XPCI;
    StringRecord FULL;

    void Write(FileWriter &writer);

    bool operator ==(const GENXPCI &other) const;
    bool operator !=(const GENXPCI &other) const;
    };

struct GENXLOD
    {
    FLOAT32 lod1, lod2, lod3;

    GENXLOD();
    ~GENXLOD();

    bool operator ==(const GENXLOD &other) const;
    bool operator !=(const GENXLOD &other) const;
    };

struct GENXESP
    {
    FORMID  parent;
    UINT8   flags, unused1[3];

    GENXESP();
    ~GENXESP();

    bool operator ==(const GENXESP &other) const;
    bool operator !=(const GENXESP &other) const;
    };

struct GENPOSDATA
    {
    FLOAT32 posX, posY, posZ, rotX, rotY, rotZ;

    GENPOSDATA();
    ~GENPOSDATA();

    bool operator ==(const GENPOSDATA &other) const;
    bool operator !=(const GENPOSDATA &other) const;
    };

struct GENPGRP
    {
    FLOAT32 x, y, z;
    UINT8   connections;
    UINT8   unused1[3];

    GENPGRP();
    ~GENPGRP();

    bool operator ==(const GENPGRP &other) const;
    bool operator !=(const GENPGRP &other) const;
    };

struct LVLLVLO
    {
    SINT16  level;
    UINT8   unused1[2];
    FORMID  listId;
    SINT16  count;
    UINT8   unused2[2];

    LVLLVLO();
    ~LVLLVLO();

    bool operator ==(const LVLLVLO &other) const;
    bool operator !=(const LVLLVLO &other) const;
    };

struct MAGICOBME
    {
    UINT8   recordVersion, betaVersion, minorVersion, majorVersion;
    UINT8   reserved[0x1C];

    MAGICOBME();
    ~MAGICOBME();

    bool operator ==(const MAGICOBME &other) const;
    bool operator !=(const MAGICOBME &other) const;
    };

struct OBMEMAGIC
    {
    ReqSubRecord<MAGICOBME> OBME;
    RawRecord DATX;

    bool operator ==(const OBMEMAGIC &other) const;
    bool operator !=(const OBMEMAGIC &other) const;
    };

struct GENMNAM
    {
    SINT32  dimX, dimY;
    SINT16  NWCellX, NWCellY, SECellX, SECellY;

    GENMNAM();
    ~GENMNAM();

    bool operator ==(const GENMNAM &other) const;
    bool operator !=(const GENMNAM &other) const;
    };

struct GENNAM0
    {
    FLOAT32 x, y;

    GENNAM0();
    ~GENNAM0();

    bool operator ==(const GENNAM0 &other) const;
    bool operator !=(const GENNAM0 &other) const;
    };

struct GENNAM9
    {
    FLOAT32 x, y;

    GENNAM9();
    ~GENNAM9();

    bool operator ==(const GENNAM9 &other) const;
    bool operator !=(const GENNAM9 &other) const;
    };

struct GENTNAM
    {
    UINT8   markerType, unused1;

    GENTNAM();
    ~GENTNAM();

    bool operator ==(const GENTNAM &other) const;
    bool operator !=(const GENTNAM &other) const;
    };

struct RACESKILL
    {
    SINT8   value, boost;

    RACESKILL();
    ~RACESKILL();

    bool operator ==(const RACESKILL &other) const;
    bool operator !=(const RACESKILL &other) const;
    };

struct RACEDATA
    {
    RACESKILL skills[7];
    UINT8   unused1[2];
    FLOAT32 maleHeight, femaleHeight, maleWeight, femaleWeight;
    UINT32  flags;

    RACEDATA();
    ~RACEDATA();

    bool operator ==(const RACEDATA &other) const;
    bool operator !=(const RACEDATA &other) const;
    };

struct RACESNAM
    {
    UINT8   SNAM[2];

    RACESNAM();
    ~RACESNAM();

    bool operator ==(const RACESNAM &other) const;
    bool operator !=(const RACESNAM &other) const;
    };

struct RACEVNAM
    {
    FORMID  maleVoice, femaleVoice;

    RACEVNAM();
    ~RACEVNAM();

    bool operator ==(const RACEVNAM &other) const;
    bool operator !=(const RACEVNAM &other) const;
    };

struct RACEDNAM
    {
    FORMID  defaultHairMale, defaultHairFemale;

    RACEDNAM();
    ~RACEDNAM();

    bool operator ==(const RACEDNAM &other) const;
    bool operator !=(const RACEDNAM &other) const;
    };

struct RACECNAM
    {
    UINT8  defaultHairMale, defaultHairFemale;

    RACECNAM();
    ~RACECNAM();

    bool operator ==(const RACECNAM &other) const;
    bool operator !=(const RACECNAM &other) const;
    };

//Fallout New Vegas Chunks
struct GENOBND
    {
    SINT16   x1, y1, z1, x2, y2, z2;

    GENOBND();
    ~GENOBND();

    bool operator ==(const GENOBND &other) const;
    bool operator !=(const GENOBND &other) const;
    };

struct GENDODT
    {
    FLOAT32 minWidth, maxWidth, minHeight, maxHeight,
            depth, shininess, scale;
    UINT8   passes, flags, unused1[2], red, green, blue, unused2;

    GENDODT();
    ~GENDODT();

    bool operator ==(const GENDODT &other) const;
    bool operator !=(const GENDODT &other) const;
    };

struct GENPATROL
    {
    ReqSimpleFloatSubRecord<flt_0> XPRD; //Idle Time
    //XPPA, Patrol Script Marker (Empty)
    ReqSimpleSubRecord<FORMID> INAM; //Idle
    ReqSubRecord<FNVSCHR> SCHR;
    RawRecord SCDA;
    NonNullStringRecord SCTX;
    OrderedSparseArray<GENVARS *, sortVARS> VARS;
    OrderedSparseArray<GENSCR_ *> SCR_;
    ReqSimpleSubRecord<FORMID> TNAM; //Topic

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

    bool IsScriptEnabled();
    void IsScriptEnabled(bool value);
    bool IsScriptFlagMask(UINT16 Mask, bool Exact=false);
    void SetScriptFlagMask(UINT16 Mask);

    bool IsObject();
    void IsObject(bool value);
    bool IsQuest();
    void IsQuest(bool value);
    bool IsEffect();
    void IsEffect(bool value);
    bool IsType(UINT16 Type);
    void SetType(UINT16 Type);

    void Write(FileWriter &writer);

    bool operator ==(const GENPATROL &other) const;
    bool operator !=(const GENPATROL &other) const;
    };

struct FNVXNAM
    {
    FORMID  faction;
    SINT32  mod;
    UINT32  groupReactionType;

    enum groupReactionTypes
        {
        eNeutral = 0,
        eEnemy,
        eAlly,
        eFriend,
        };

    FNVXNAM();
    ~FNVXNAM();

    bool   IsNeutral();
    void   IsNeutral(bool value);
    bool   IsEnemy();
    void   IsEnemy(bool value);
    bool   IsAlly();
    void   IsAlly(bool value);
    bool   IsFriend();
    void   IsFriend(bool value);
    bool   IsType(UINT32 Type);
    void   SetType(UINT32 Type);

    bool operator ==(const FNVXNAM &other) const;
    bool operator !=(const FNVXNAM &other) const;
    };

struct FNVMODS //Alternate Texture
    {
    STRING  name; //3D Name
    FORMID  texture; //New Texture
    SINT32  index; //3D Index

    FNVMODS();
    ~FNVMODS();

    bool operator ==(const FNVMODS &other) const;
    bool operator !=(const FNVMODS &other) const;
    };

//This subrecord uses a very non-standard format
//It combines an array of strings, formids, and longs into a single chunk
//Normally, it would be expected for the strings to be in separate chunks
struct FNVAlternateTextures
    {
    std::vector<FNVMODS *> MODS; //Alternate Textures

    FNVAlternateTextures();
    ~FNVAlternateTextures();

    UINT32 GetSize() const;

    bool IsLoaded() const;
    void Load();
    void Unload();

    void resize(UINT32 newSize);

    bool Read(unsigned char *&buffer, const UINT32 &subSize);
    void Write(FileWriter &writer);
    void Write(UINT32 _Type, FileWriter &writer);

    void VisitFormIDs(FormIDOp &op);

    FNVAlternateTextures& operator = (const FNVAlternateTextures &rhs);
    bool operator ==(const FNVAlternateTextures &other) const;
    bool operator !=(const FNVAlternateTextures &other) const;
    };

struct FNVMODEL
    {
    StringRecord MODL; //Model Filename
    OptSimpleFloatSubRecord<flt_0> MODB; //Bound Radius (Unknown?)
    RawRecord MODT; //Texture Files Hashes
    FNVAlternateTextures Textures; //Alternate Textures
    OptSimpleSubRecord<UINT8> MODD; //FaceGen Model Flags

    enum moddFlags
        {
        fIsHead      = 0x01,
        fIsTorso     = 0x02,
        fIsRightHand = 0x04,
        fIsLeftHand  = 0x08
        };

    FNVMODEL();
    ~FNVMODEL();

    bool   IsHead();
    void   IsHead(bool value);
    bool   IsTorso();
    void   IsTorso(bool value);
    bool   IsRightHand();
    void   IsRightHand(bool value);
    bool   IsLeftHand();
    void   IsLeftHand(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    void   Write(FileWriter &writer);

    bool operator ==(const FNVMODEL &other) const;
    bool operator !=(const FNVMODEL &other) const;
    };

struct FNVBIPEDMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes
    FNVAlternateTextures Textures; //Alternate Textures
    OptSimpleSubRecord<UINT8> MODD; //FaceGen Model Flags

    enum moddFlags
        {
        fIsHead      = 0x00000001,
        fIsTorso     = 0x00000002,
        fIsRightHand = 0x00000004,
        fIsLeftHand  = 0x00000008
        };

    bool   IsHead();
    void   IsHead(bool value);
    bool   IsTorso();
    void   IsTorso(bool value);
    bool   IsRightHand();
    void   IsRightHand(bool value);
    bool   IsLeftHand();
    void   IsLeftHand(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    void Write(FileWriter &writer);

    bool operator ==(const FNVBIPEDMODEL &other) const;
    bool operator !=(const FNVBIPEDMODEL &other) const;
    };

struct FNVWORLDMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes
    FNVAlternateTextures Textures; //Alternate Textures

    void Write(FileWriter &writer);

    bool operator ==(const FNVWORLDMODEL &other) const;
    bool operator !=(const FNVWORLDMODEL &other) const;
    };

struct FNVCTDA //Condition
    {
    UINT8   operType, unused1[3]; //Type, Unused
    FORMID_OR_FLOAT32 compValue; //Float or Global (if fIsUseGlobal is true)
    UINT32  ifunc;
    FORMID_OR_UINT32 param1, param2;
    //Below are not always present on chunk...
    UINT32  runOnType; //Run On
    FORMID_OR_UINT32 reference; //Reference (if runOn == 2) or Unused

    enum operTypeType
        {
        eEqual          = 0x00,
        eNotEqual       = 0x20,
        eGreater        = 0x40,
        eGreaterOrEqual = 0x60,
        eLess           = 0x80,
        eLessOrEqual    = 0xA0
        };

    enum operTypeFlag
        {
        fIsNone        = 0x00,
        fIsOr          = 0x01,
        fIsRunOnTarget = 0x02,
        fIsUseGlobal   = 0x04
        };

    enum operRunOnType
        {
        eSubject = 0,
        eTarget,
        eReference,
        eCombatTarget,
        eLinkedReference
        };

    FNVCTDA();
    ~FNVCTDA();

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const FNVCTDA &other) const;
    bool operator !=(const FNVCTDA &other) const;

    bool IsEqual();
    void IsEqual(bool value);
    bool IsNotEqual();
    void IsNotEqual(bool value);
    bool IsGreater();
    void IsGreater(bool value);
    bool IsGreaterOrEqual();
    void IsGreaterOrEqual(bool value);
    bool IsLess();
    void IsLess(bool value);
    bool IsLessOrEqual();
    void IsLessOrEqual(bool value);
    bool IsType(UINT8 Type);
    void SetType(UINT8 Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal() const;
    void IsUseGlobal(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);

    bool IsResultOnSubject();
    void IsResultOnSubject(bool value);
    bool IsResultOnTarget();
    void IsResultOnTarget(bool value);
    bool IsResultOnReference();
    void IsResultOnReference(bool value);
    bool IsResultOnCombatTarget();
    void IsResultOnCombatTarget(bool value);
    bool IsResultOnLinkedReference();
    void IsResultOnLinkedReference(bool value);
    bool IsResultOnType(UINT32 Type);
    void SetResultOnType(UINT32 Type);
    };

struct FNVEFIT
    {
    UINT32  magnitude, area, duration, rangeType;
    SINT32  actorValue;

    FNVEFIT();
    ~FNVEFIT();

    bool operator ==(const FNVEFIT &other) const;
    bool operator !=(const FNVEFIT &other) const;
    };

struct FNVEffect
    {
    ReqSimpleSubRecord<FORMID> EFID; //Effect ID
    ReqSubRecord<FNVEFIT> EFIT; //Effect Data
    OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

    enum eRanges
        {
        eRangeSelf   = 0,
        eRangeTouch  = 1,
        eRangeTarget = 2
        };

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(UINT32 Mask);
    void SetRange(UINT32 Mask);

    bool operator ==(const FNVEffect &other) const;
    bool operator !=(const FNVEffect &other) const;
    };

struct DESTDSTD //Destruction Stage Data
    {
    UINT8   health, index, stage, flags; //Health, Index, Damage Stage, Flags
    SINT32  dps; //Self Damage per Second
    FORMID  explosion, debris;
    SINT32  debrisCount;

    DESTDSTD();
    ~DESTDSTD();

    bool operator ==(const DESTDSTD &other) const;
    bool operator !=(const DESTDSTD &other) const;
    };

struct DESTSTAGE //Destructable Stage
    {
    ReqSubRecord<DESTDSTD> DSTD; //Destruction Stage Data
    StringRecord DMDL; //Model Filename
    RawRecord DMDT; //Texture Files Hashes

    enum flagsFlags
        {
        fIsCapDamage = 0x01,
        fIsDisable   = 0x02,
        fIsDestroy   = 0x04
        };

    void Write(FileWriter &writer);

    bool   IsCapDamage();
    void   IsCapDamage(bool value);
    bool   IsDisable();
    void   IsDisable(bool value);
    bool   IsDestroy();
    void   IsDestroy(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const DESTSTAGE &other) const;
    bool operator !=(const DESTSTAGE &other) const;
    };

struct sortDESTStages
    {
    bool operator()(const DESTSTAGE *lhs, const DESTSTAGE *rhs) const;
    };

struct GENDEST //Destructable Header
    {
    SINT32  health; //Health
    UINT8   count; //Count
    UINT8   flags; //Flags
    UINT8   unused1[2]; //Unused

    GENDEST();
    ~GENDEST();

    bool operator ==(const GENDEST &other) const;
    bool operator !=(const GENDEST &other) const;
    };

struct GENDESTRUCT //Destructable
    {
    ReqSubRecord<GENDEST> DEST; //Destructable Header
    OrderedSparseArray<DESTSTAGE *, sortDESTStages> Stages; //Destructable Stages

    enum flagsFlags
        {
        fIsVATSTargetable = 0x01
        };

    void Write(FileWriter &writer);

    bool   IsVATSTargetable();
    void   IsVATSTargetable(bool value);
    bool   IsFlagMask(UINT8 Mask, bool Exact=false);
    void   SetFlagMask(UINT8 Mask);

    bool operator ==(const GENDESTRUCT &other) const;
    bool operator !=(const GENDESTRUCT &other) const;
    };

struct GENBMDT
    {
    UINT32  bipedFlags; //Type
    UINT8   generalFlags, unused1[3]; //Flags, Unused

    GENBMDT();
    ~GENBMDT();

    bool operator ==(const GENBMDT &other) const;
    bool operator !=(const GENBMDT &other) const;
    };

struct FNVEQUIPDATA
    {
    SINT32  value, health; //Value, Health
    FLOAT32 weight; //Weight

    FNVEQUIPDATA();
    ~FNVEQUIPDATA();

    bool operator ==(const FNVEQUIPDATA &other) const;
    bool operator !=(const FNVEQUIPDATA &other) const;
    };

struct FNVEQUIPDNAM
    {
    SINT16  AR; //Armor Resistance
    UINT16  flags; //Flags
    //Below are not always present in chunk
    FLOAT32 DT; //Damage Threshold
    UINT8   unknown[4]; //Unknown ?

    FNVEQUIPDNAM();
    ~FNVEQUIPDNAM();

    bool operator ==(const FNVEQUIPDNAM &other) const;
    bool operator !=(const FNVEQUIPDNAM &other) const;
    };

struct GENCOED // Extra Data
    {
    FORMID  owner; // Owner
    FORMID_OR_UINT32 globalOrRank; // Global Variable / Required Rank (global if owner is NPC_, rank if owner is FACT)
    FLOAT32 condition; // Item Condition

    GENCOED();
    ~GENCOED();

    bool operator ==(const GENCOED &other) const;
    bool operator !=(const GENCOED &other) const;
    };

struct FNVCNTO
    {
    ReqSubRecord<GENCNTO> CNTO;
    OptSubRecord<GENCOED> COED;

    bool IsGlobal(); //Hack
    bool IsRank();   //Hack

    void Write(FileWriter &writer);

    bool operator ==(const FNVCNTO &other) const;
    bool operator !=(const FNVCNTO &other) const;
    };

struct GENDNAM
    {
    FLOAT32  defaultLandHeight, defaultWaterHeight;

    GENDNAM();
    ~GENDNAM();

    bool operator ==(const GENDNAM &other) const;
    bool operator !=(const GENDNAM &other) const;
    };

struct GENONAM
    {
    FLOAT32  mapScale, xCellOffset, yCellOffset;

    GENONAM();
    ~GENONAM();

    bool operator ==(const GENONAM &other) const;
    bool operator !=(const GENONAM &other) const;
    };

struct GENIMPS
    {
    UINT32   material;
    FORMID   oldImpact, newImpact;

    GENIMPS();
    ~GENIMPS();

    bool operator ==(const GENIMPS &other) const;
    bool operator !=(const GENIMPS &other) const;
    };

struct GENXPRM
    {
    FLOAT32  xBound, yBound, zBound;
    FLOAT32  red, green, blue, unknown;
    UINT32   type;

    GENXPRM();
    ~GENXPRM();

    bool operator ==(const GENXPRM &other) const;
    bool operator !=(const GENXPRM &other) const;
    };

struct GENXMBO
    {
    FLOAT32  x, y, z;

    GENXMBO();
    ~GENXMBO();

    bool operator ==(const GENXMBO &other) const;
    bool operator !=(const GENXMBO &other) const;
    };

struct GENXTEL
    {
    FORMID  destinationFid;
    GENPOSDATA destination;
    UINT32  flags;

    GENXTEL();
    ~GENXTEL();

    bool operator ==(const GENXTEL &other) const;
    bool operator !=(const GENXTEL &other) const;
    };

struct GENMAPDATA
    {
    //XMRK; //Map Data Marker (Empty)
    ReqSimpleSubRecord<UINT8> FNAM; //Flags
    StringRecord FULL; //Name
    ReqSubRecord<GENTNAM> TNAM; //Type
    OptSimpleSubRecord<FORMID> WMI1; //Reputation

    void Write(FileWriter &writer);

    bool operator ==(const GENMAPDATA &other) const;
    bool operator !=(const GENMAPDATA &other) const;
    };

struct GENAUDIODATA
    {
    //MMRK; //Audio Data Marker (Empty)
    RawRecord FULL; //Unknown
    OptSimpleSubRecord<FORMID> CNAM; //Audio Location
    RawRecord BNAM; //Unknown
    OptSimpleFloatSubRecord<flt_0> MNAM; //Unknown
    OptSimpleFloatSubRecord<flt_0> NNAM; //Unknown

    void Write(FileWriter &writer);

    bool operator ==(const GENAUDIODATA &other) const;
    bool operator !=(const GENAUDIODATA &other) const;
    };

struct GENXRDO
    {
    FLOAT32  rangeRadius;
    UINT32   rangeType;
    FLOAT32  staticPercentage;
    FORMID   positionReference;

    GENXRDO();
    ~GENXRDO();

    bool operator ==(const GENXRDO &other) const;
    bool operator !=(const GENXRDO &other) const;
    };

struct GENAMMO
    {
    OptSimpleSubRecord<FORMID> XAMT; //Type
    OptSimpleSubRecord<SINT32> XAMC; //Count

    void Write(FileWriter &writer);

    bool operator ==(const GENAMMO &other) const;
    bool operator !=(const GENAMMO &other) const;
    };

struct GENXPWR
    {
    FORMID reference; //reference
    UINT32 type; //type

    enum xpwrTypes
        {
        eReflection = 0,
        eRefraction
        };

    GENXPWR();
    ~GENXPWR();

    bool IsReflection();
    void IsReflection(bool value);
    bool IsRefraction();
    void IsRefraction(bool value);
    bool IsType(UINT32 Type);
    void SetType(UINT32 Type);

    bool operator ==(const GENXPWR &other) const;
    bool operator !=(const GENXPWR &other) const;
    };

struct GENXDCR //Linked Decal (almost entirely unused, possibly not fully implemented by Bethesda)
    {
    FORMID reference; //Reference
    UINT8  unknown1[24]; //Unknown (zero filled)

    GENXDCR();
    ~GENXDCR();

    bool operator ==(const GENXDCR &other) const;
    bool operator !=(const GENXDCR &other) const;
    };

struct GENXCLP
    {
    GENCLR start; //Link Start Color
    GENCLR end; //Link End Color

    bool operator ==(const GENXCLP &other) const;
    bool operator !=(const GENXCLP &other) const;
    };

struct GENXAPR
    {
    FORMID reference; //Reference
    FLOAT32 delay; //Delay

    GENXAPR();
    ~GENXAPR();

    bool operator ==(const GENXAPR &other) const;
    bool operator !=(const GENXAPR &other) const;
    };

struct GENACTPARENT
    {
    ReqSimpleSubRecord<UINT8> XAPD; //Flags
    UnorderedSparseArray<GENXAPR *> XAPR; //Activate Parent Refs

    enum flagsFlags
        {
        fIsParentActivateOnly = 0x00000001
        };

    bool IsParentActivateOnly();
    void IsParentActivateOnly(bool value);
    bool IsFlagMask(UINT8 Mask, bool Exact=false);
    void SetFlagMask(UINT8 Mask);

    void Write(FileWriter &writer);

    bool operator ==(const GENACTPARENT &other) const;
    bool operator !=(const GENACTPARENT &other) const;
    };

struct GENXNDP
    {
    FORMID navMesh; //Navigation Mesh
    UINT16 unknown1; //Unknown
    UINT8  unused1[2]; //Unused

    GENXNDP();
    ~GENXNDP();

    bool operator ==(const GENXNDP &other) const;
    bool operator !=(const GENXNDP &other) const;
    };

struct GENPOSITION
    {
    FLOAT32 width, height, //Size
            xPos, yPos, zPos, //Position
            q1, q2, q3, q4; //Rotation (Quaternion?)

    GENPOSITION();
    ~GENPOSITION();

    bool operator ==(const GENPOSITION &other) const;
    bool operator !=(const GENPOSITION &other) const;
    };

struct GENXRMR
    {
    UINT16  count; //Linked Rooms Count
    UINT8   unknown1[2]; //Unknown

    GENXRMR();
    ~GENXRMR();

    bool operator ==(const GENXRMR &other) const;
    bool operator !=(const GENXRMR &other) const;
    };

struct GENROOM
    {
    OptSubRecord<GENXRMR> XRMR; //Room Data
    UnorderedPackedArray<FORMID> XLRM; //Linked Rooms

    void Write(FileWriter &writer);

    bool operator ==(const GENROOM &other) const;
    bool operator !=(const GENROOM &other) const;
    };

struct FNVXOWN
    {
    ReqSimpleSubRecord<FORMID> XOWN;
    SemiOptSimpleSubRecord<SINT32> XRNK; //Faction Rank

    void Write(FileWriter &writer);

    bool operator ==(const FNVXOWN &other) const;
    bool operator !=(const FNVXOWN &other) const;
    };

struct FNVXLOC
    {
    UINT8   level, unused1[3];
    FORMID  key;
    UINT8   flags, unused2[3], unknown[8]; //unknown[8] not always present on chunk...

    FNVXLOC();
    ~FNVXLOC();

    bool operator ==(const FNVXLOC &other) const;
    bool operator !=(const FNVXLOC &other) const;
    };

struct FNVAIDT
    {
    UINT8   aggression, confidence, energyLevel, responsibility, mood, unused1[3];
    UINT32  flags;
    SINT8   trainSkill;
    UINT8   trainLevel, assistance, aggroFlags;
    SINT32  aggroRadius;

    enum aggressionTypes
        {
        eUnaggressive = 0,
        eAggressive,
        eVeryAggressive,
        eFrenzied
        };

    enum confidenceTypes
        {
        eCowardly = 0,
        eCautious,
        eAverage,
        eBrave,
        eFoolhardy
        };

    enum moodTypes
        {
        eNeutral = 0,
        eAfraid,
        eAnnoyed,
        eCocky,
        eDrugged,
        ePleasant,
        eAngry,
        eSad
        };

    enum assistanceTypes
        {
        eHelpsNobody = 0,
        eHelpsAllies,
        eHelpsFriendsAndAllies
        };

    enum aggroFlags
        {
        fIsAggroRadiusBehavior = 0x01
        };

    FNVAIDT();
    ~FNVAIDT();

    bool operator ==(const FNVAIDT &other) const;
    bool operator !=(const FNVAIDT &other) const;
    };

struct FNVACBS // Configuration
    {
    UINT32  flags; // Flags
    UINT16  fatigue, barterGold; // Fatigue, Barter gold
    SINT16  level; // Level or Level Multiplier
    UINT16  calcMin, calcMax, speedMult; // Calc min, Calc max, Speed Multiplier
    FLOAT32 karma; // Karma (Alignment)
    SINT16  dispBase; // Disposition Base
    UINT16  templateFlags; // Template Flags

    FNVACBS();
    ~FNVACBS();

    bool operator ==(const FNVACBS &other) const;
    bool operator !=(const FNVACBS &other) const;
    };

struct FNVLVLO
    {
    ReqSubRecord<LVLLVLO> LVLO;
    OptSubRecord<GENCOED> COED;

    bool IsGlobal(); //Hack
    bool IsRank();   //Hack

    void Write(FileWriter &writer);

    bool operator ==(const FNVLVLO &other) const;
    bool operator !=(const FNVLVLO &other) const;
    };

struct SURVDATA // Data
    {
    UINT32  threshold; // Trigger Threshold
    FORMID  actorEffect; // Actor Effect

    SURVDATA();
    ~SURVDATA();

    bool operator ==(const SURVDATA &other) const;
    bool operator !=(const SURVDATA &other) const;
    };

struct FNVLIGHT
    {
    GENCLR  ambient; //Ambient Color
    GENCLR  directional; //Directional Color
    GENCLR  fog; //Fog Color
    FLOAT32 fogNear, fogFar; //Fog Near, Fog Far
    SINT32  directionalXY, directionalZ; //Directional Rotation XY, Directional Rotation Z
    FLOAT32 directionalFade, fogClip, fogPower; //Directional Fade, Fog Clip Dist, Fog Power

    FNVLIGHT();
    ~FNVLIGHT();

    bool operator ==(const FNVLIGHT &other) const;
    bool operator !=(const FNVLIGHT &other) const;
    };

struct GENXPOD
    {
    FORMID room1, room2;

    GENXPOD();
    ~GENXPOD();

    bool operator ==(const GENXPOD &other) const;
    bool operator !=(const GENXPOD &other) const;
    };

struct GENXORD
    {
    FORMID right, left, bottom, top;

    GENXORD();
    ~GENXORD();

    bool operator ==(const GENXORD &other) const;
    bool operator !=(const GENXORD &other) const;
    };

struct GENIMPF
    {
    char concSolid[30];
    char concBroken[30];
    char metalSolid[30];
    char metalHollow[30];
    char metalSheet[30];
    char wood[30];
    char sand[30];
    char dirt[30];
    char grass[30];
    char water[30];

    GENIMPF();
    ~GENIMPF();

    bool operator ==(const GENIMPF &other) const;
    bool operator !=(const GENIMPF &other) const;
    };