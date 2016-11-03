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
        uint32_t count;
        bool stop;

    public:
        bool result;

        FormIDOp();
        virtual ~FormIDOp();

        virtual bool Accept(uint32_t &curFormID) abstract {};
        virtual bool AcceptMGEF(uint32_t &curMgefCode) abstract {};

        uint32_t GetCount();
        void ResetCount();
        bool Stop();
    };

class FormIDResolver : public FormIDOp
    {
    private:
        const uint8_t (&ResolveTable)[256];
        //uint8_t ModIndex;

    public:
        const unsigned char * const FileStart;
        const unsigned char * const FileEnd;

        FormIDResolver(const uint8_t (&_ResolveTable)[256], const unsigned char * const _FileStart, const unsigned char * const _FileEnd);
        ~FormIDResolver();

        bool Accept(uint32_t &curFormID);
        bool AcceptMGEF(uint32_t &curMgefCode);
    };

struct GENXNAM
    {
    FORMID  faction;
    int32_t  mod;

    GENXNAM();
    ~GENXNAM();

    bool operator ==(const GENXNAM &other) const;
    bool operator !=(const GENXNAM &other) const;
    };

struct GENSCHR
    {
    uint8_t   unused1[4];
    uint32_t  numRefs, compiledSize, lastIndex, scriptType;

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
    uint32_t  index;
    uint8_t   unused1[12], flags, unused2[7];

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
    bool   IsFlagMask(uint8_t Mask, bool Exact=false);
    void   SetFlagMask(uint8_t Mask);

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
    uint8_t   unused1[4];
    uint32_t  numRefs, compiledSize, lastIndex;
    uint16_t  scriptType, flags;

    FNVSCHR();
    ~FNVSCHR();

    bool operator ==(const FNVSCHR &other) const;
    bool operator !=(const FNVSCHR &other) const;
    };

struct GENEFIT
    {
    MGEFCODE_OR_UINT32 name;
    uint32_t  magnitude, area, duration, rangeType;
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 actorValue;

    GENEFIT();
    ~GENEFIT();

    bool operator ==(const GENEFIT &other) const;
    bool operator !=(const GENEFIT &other) const;
    };

struct GENSCIT
    {
    FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 script;
    uint32_t  schoolType;
    MGEFCODE_OR_UINT32 visual;
    uint8_t   flags, unused1[3];

    GENSCIT();
    ~GENSCIT();

    bool operator ==(const GENSCIT &other) const;
    bool operator !=(const GENSCIT &other) const;
    };

struct OBMEEFME
    {
    uint8_t   recordVersion, betaVersion, minorVersion, majorVersion;
    uint8_t   efitParamInfo;
    uint8_t   efixParamInfo;
    uint8_t   reserved[0xA];

    OBMEEFME();
    ~OBMEEFME();

    bool operator ==(const OBMEEFME &other) const;
    bool operator !=(const OBMEEFME &other) const;
    };

struct OBMEEFIX
    {
    uint32_t  efixOverrides;
    uint32_t  efixFlags;
    float baseCost;
    ACTORVALUE resistAV;
    uint8_t   reserved[0x10];

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
    ReqSimpleSubRecord<uint32_t> EFID; //Effect ID
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
    bool IsSchool(uint32_t Type);
    void SetSchool(uint32_t Type);

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
    bool IsFlagMask(uint8_t Mask, bool Exact=false);
    void SetFlagMask(uint8_t Mask);

    bool IsRangeSelf();
    void IsRangeSelf(bool value);
    bool IsRangeTouch();
    void IsRangeTouch(bool value);
    bool IsRangeTarget();
    void IsRangeTarget(bool value);
    bool IsRange(uint32_t Type);
    void SetRange(uint32_t Type);

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

    bool OBME_IsOverrideFlagMask(uint32_t Mask, bool Exact=false);
    void OBME_SetOverrideFlagMask(uint32_t Mask);

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

    bool OBME_IsFlagMask(uint32_t Mask, bool Exact=false);
    void OBME_SetFlagMask(uint32_t Mask);

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const GENEffect &other) const;
    bool operator !=(const GENEffect &other) const;
    };

struct GENENIT
    {
    int32_t  value;
    uint8_t   flags;
    uint8_t   unused1[3];

    GENENIT();
    ~GENENIT();

    bool operator ==(const GENENIT &other) const;
    bool operator !=(const GENENIT &other) const;
    };

struct GENVALUEWEIGHT
    {
    uint32_t  value;
    float weight;

    GENVALUEWEIGHT();
    ~GENVALUEWEIGHT();

    bool operator ==(const GENVALUEWEIGHT &other) const;
    bool operator !=(const GENVALUEWEIGHT &other) const;
    };

struct GENCNTO
    {
    FORMID  item;
    int32_t  count;

    GENCNTO();
    ~GENCNTO();

    bool operator ==(const GENCNTO &other) const;
    bool operator !=(const GENCNTO &other) const;
    };

struct GENACBS
    {
    uint32_t  flags;
    uint16_t  baseSpell, fatigue, barterGold;
    int16_t  level;
    uint16_t  calcMin, calcMax;

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
    uint8_t   rank, unused1[3];

    GENSNAM();
    ~GENSNAM();

    bool operator ==(const GENSNAM &other) const;
    bool operator !=(const GENSNAM &other) const;
    };

struct GENAIDT
    {
    uint8_t   aggression, confidence, energyLevel, responsibility;
    uint32_t  flags;
    int8_t   trainSkill;
    uint8_t   trainLevel, unused1[2];

    GENAIDT();
    ~GENAIDT();

    bool operator ==(const GENAIDT &other) const;
    bool operator !=(const GENAIDT &other) const;
    };

struct GENCTDA
    {
    uint8_t   operType, unused1[3];
    FORMID_OR_FLOAT32 compValue;
    uint32_t  ifunc;
    FORMID_OR_UINT32 param1, param2;
    uint8_t   unused2[4];

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
    bool IsType(uint8_t Type);
    void SetType(uint8_t Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal() const;
    void IsUseGlobal(bool value);
    bool IsFlagMask(uint8_t Mask, bool Exact=false);
    void SetFlagMask(uint8_t Mask);

    bool VisitFormIDs(FormIDOp &op);
    void Write(FileWriter &writer);

    bool operator ==(const GENCTDA &other) const;
    bool operator !=(const GENCTDA &other) const;
    };

struct GENCLR
    {
    uint8_t   red, green, blue, unused1;

    GENCLR(uint8_t _red=0, uint8_t _green=0, uint8_t _blue=0, uint8_t _unused1=0);
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
    SemiOptSimpleSubRecord<int32_t> XRNK;
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
    float lod1, lod2, lod3;

    GENXLOD();
    ~GENXLOD();

    bool operator ==(const GENXLOD &other) const;
    bool operator !=(const GENXLOD &other) const;
    };

struct GENXESP
    {
    FORMID  parent;
    uint8_t   flags, unused1[3];

    GENXESP();
    ~GENXESP();

    bool operator ==(const GENXESP &other) const;
    bool operator !=(const GENXESP &other) const;
    };

struct GENPOSDATA
    {
    float posX, posY, posZ, rotX, rotY, rotZ;

    GENPOSDATA();
    ~GENPOSDATA();

    bool operator ==(const GENPOSDATA &other) const;
    bool operator !=(const GENPOSDATA &other) const;
    };

struct GENPGRP
    {
    float x, y, z;
    uint8_t   connections;
    uint8_t   unused1[3];

    GENPGRP();
    ~GENPGRP();

    bool operator ==(const GENPGRP &other) const;
    bool operator !=(const GENPGRP &other) const;
    };

struct LVLLVLO
    {
    int16_t  level;
    uint8_t   unused1[2];
    FORMID  listId;
    int16_t  count;
    uint8_t   unused2[2];

    LVLLVLO();
    ~LVLLVLO();

    bool operator ==(const LVLLVLO &other) const;
    bool operator !=(const LVLLVLO &other) const;
    };

struct MAGICOBME
    {
    uint8_t   recordVersion, betaVersion, minorVersion, majorVersion;
    uint8_t   reserved[0x1C];

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
    int32_t  dimX, dimY;
    int16_t  NWCellX, NWCellY, SECellX, SECellY;

    GENMNAM();
    ~GENMNAM();

    bool operator ==(const GENMNAM &other) const;
    bool operator !=(const GENMNAM &other) const;
    };

struct GENNAM0
    {
    float x, y;

    GENNAM0();
    ~GENNAM0();

    bool operator ==(const GENNAM0 &other) const;
    bool operator !=(const GENNAM0 &other) const;
    };

struct GENNAM9
    {
    float x, y;

    GENNAM9();
    ~GENNAM9();

    bool operator ==(const GENNAM9 &other) const;
    bool operator !=(const GENNAM9 &other) const;
    };

struct GENTNAM
    {
    uint8_t   markerType, unused1;

    GENTNAM();
    ~GENTNAM();

    bool operator ==(const GENTNAM &other) const;
    bool operator !=(const GENTNAM &other) const;
    };

struct RACESKILL
    {
    int8_t   value, boost;

    RACESKILL();
    ~RACESKILL();

    bool operator ==(const RACESKILL &other) const;
    bool operator !=(const RACESKILL &other) const;
    };

struct RACEDATA
    {
    RACESKILL skills[7];
    uint8_t   unused1[2];
    float maleHeight, femaleHeight, maleWeight, femaleWeight;
    uint32_t  flags;

    RACEDATA();
    ~RACEDATA();

    bool operator ==(const RACEDATA &other) const;
    bool operator !=(const RACEDATA &other) const;
    };

struct RACESNAM
    {
    uint8_t   SNAM[2];

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
    uint8_t  defaultHairMale, defaultHairFemale;

    RACECNAM();
    ~RACECNAM();

    bool operator ==(const RACECNAM &other) const;
    bool operator !=(const RACECNAM &other) const;
    };

//Fallout New Vegas Chunks
struct GENOBND
    {
    int16_t   x1, y1, z1, x2, y2, z2;

    GENOBND();
    ~GENOBND();

    bool operator ==(const GENOBND &other) const;
    bool operator !=(const GENOBND &other) const;
    };

struct GENDODT
    {
    float minWidth, maxWidth, minHeight, maxHeight,
            depth, shininess, scale;
    uint8_t   passes, flags, unused1[2], red, green, blue, unused2;

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
    bool IsScriptFlagMask(uint16_t Mask, bool Exact=false);
    void SetScriptFlagMask(uint16_t Mask);

    bool IsObject();
    void IsObject(bool value);
    bool IsQuest();
    void IsQuest(bool value);
    bool IsEffect();
    void IsEffect(bool value);
    bool IsType(uint16_t Type);
    void SetType(uint16_t Type);

    void Write(FileWriter &writer);

    bool operator ==(const GENPATROL &other) const;
    bool operator !=(const GENPATROL &other) const;
    };

struct FNVXNAM
    {
    FORMID  faction;
    int32_t  mod;
    uint32_t  groupReactionType;

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
    bool   IsType(uint32_t Type);
    void   SetType(uint32_t Type);

    bool operator ==(const FNVXNAM &other) const;
    bool operator !=(const FNVXNAM &other) const;
    };

struct FNVMODS //Alternate Texture
    {
    char *  name; //3D Name
    FORMID  texture; //New Texture
    int32_t  index; //3D Index

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

    uint32_t GetSize() const;

    bool IsLoaded() const;
    void Load();
    void Unload();

    void resize(uint32_t newSize);

    bool Read(unsigned char *&buffer, const uint32_t &subSize);
    void Write(FileWriter &writer);
    void Write(uint32_t _Type, FileWriter &writer);

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
    OptSimpleSubRecord<uint8_t> MODD; //FaceGen Model Flags

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
    bool   IsFlagMask(uint8_t Mask, bool Exact=false);
    void   SetFlagMask(uint8_t Mask);

    void   Write(FileWriter &writer);

    bool operator ==(const FNVMODEL &other) const;
    bool operator !=(const FNVMODEL &other) const;
    };

struct FNVBIPEDMODEL
    {
    StringRecord MODL; //Model Filename
    RawRecord MODT; //Texture Files Hashes
    FNVAlternateTextures Textures; //Alternate Textures
    OptSimpleSubRecord<uint8_t> MODD; //FaceGen Model Flags

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
    bool   IsFlagMask(uint8_t Mask, bool Exact=false);
    void   SetFlagMask(uint8_t Mask);

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
    uint8_t   operType, unused1[3]; //Type, Unused
    FORMID_OR_FLOAT32 compValue; //Float or Global (if fIsUseGlobal is true)
    uint32_t  ifunc;
    FORMID_OR_UINT32 param1, param2;
    //Below are not always present on chunk...
    uint32_t  runOnType; //Run On
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
    bool IsType(uint8_t Type);
    void SetType(uint8_t Type);

    bool IsNone();
    void IsNone(bool value);
    bool IsOr();
    void IsOr(bool value);
    bool IsRunOnTarget();
    void IsRunOnTarget(bool value);
    bool IsUseGlobal() const;
    void IsUseGlobal(bool value);
    bool IsFlagMask(uint8_t Mask, bool Exact=false);
    void SetFlagMask(uint8_t Mask);

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
    bool IsResultOnType(uint32_t Type);
    void SetResultOnType(uint32_t Type);
    };

struct FNVEFIT
    {
    uint32_t  magnitude, area, duration, rangeType;
    int32_t  actorValue;

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
    bool IsRange(uint32_t Mask);
    void SetRange(uint32_t Mask);

    bool operator ==(const FNVEffect &other) const;
    bool operator !=(const FNVEffect &other) const;
    };

struct DESTDSTD //Destruction Stage Data
    {
    uint8_t   health, index, stage, flags; //Health, Index, Damage Stage, Flags
    int32_t  dps; //Self Damage per Second
    FORMID  explosion, debris;
    int32_t  debrisCount;

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
    bool   IsFlagMask(uint8_t Mask, bool Exact=false);
    void   SetFlagMask(uint8_t Mask);

    bool operator ==(const DESTSTAGE &other) const;
    bool operator !=(const DESTSTAGE &other) const;
    };

struct sortDESTStages
    {
    bool operator()(const DESTSTAGE *lhs, const DESTSTAGE *rhs) const;
    };

struct GENDEST //Destructable Header
    {
    int32_t  health; //Health
    uint8_t   count; //Count
    uint8_t   flags; //Flags
    uint8_t   unused1[2]; //Unused

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
    bool   IsFlagMask(uint8_t Mask, bool Exact=false);
    void   SetFlagMask(uint8_t Mask);

    bool operator ==(const GENDESTRUCT &other) const;
    bool operator !=(const GENDESTRUCT &other) const;
    };

struct GENBMDT
    {
    uint32_t  bipedFlags; //Type
    uint8_t   generalFlags, unused1[3]; //Flags, Unused

    GENBMDT();
    ~GENBMDT();

    bool operator ==(const GENBMDT &other) const;
    bool operator !=(const GENBMDT &other) const;
    };

struct FNVEQUIPDATA
    {
    int32_t  value, health; //Value, Health
    float weight; //Weight

    FNVEQUIPDATA();
    ~FNVEQUIPDATA();

    bool operator ==(const FNVEQUIPDATA &other) const;
    bool operator !=(const FNVEQUIPDATA &other) const;
    };

struct FNVEQUIPDNAM
    {
    int16_t  AR; //Armor Resistance
    uint16_t  flags; //Flags
    //Below are not always present in chunk
    float DT; //Damage Threshold
    uint8_t   unknown[4]; //Unknown ?

    FNVEQUIPDNAM();
    ~FNVEQUIPDNAM();

    bool operator ==(const FNVEQUIPDNAM &other) const;
    bool operator !=(const FNVEQUIPDNAM &other) const;
    };

struct GENCOED // Extra Data
    {
    FORMID  owner; // Owner
    FORMID_OR_UINT32 globalOrRank; // Global Variable / Required Rank (global if owner is NPC_, rank if owner is FACT)
    float condition; // Item Condition

    GENCOED();
    ~GENCOED();

    bool IsGlobal() const; // Hack
    bool IsRank() const; // Hack

    bool operator ==(const GENCOED &other) const;
    bool operator !=(const GENCOED &other) const;
    };
SIZE_CHECK(GENCOED, 12);

struct FNVCNTO
    {
    ReqSubRecord<GENCNTO> CNTO;
    OptSubRecord<GENCOED> COED;

    bool IsGlobal() const; //Hack
    bool IsRank() const;   //Hack

    void Write(FileWriter &writer);

    bool operator ==(const FNVCNTO &other) const;
    bool operator !=(const FNVCNTO &other) const;
    };

struct GENDNAM
    {
    float  defaultLandHeight, defaultWaterHeight;

    GENDNAM();
    ~GENDNAM();

    bool operator ==(const GENDNAM &other) const;
    bool operator !=(const GENDNAM &other) const;
    };

struct GENONAM
    {
    float  mapScale, xCellOffset, yCellOffset;

    GENONAM();
    ~GENONAM();

    bool operator ==(const GENONAM &other) const;
    bool operator !=(const GENONAM &other) const;
    };

struct GENIMPS
    {
    uint32_t   material;
    FORMID   oldImpact, newImpact;

    GENIMPS();
    ~GENIMPS();

    bool operator ==(const GENIMPS &other) const;
    bool operator !=(const GENIMPS &other) const;
    };

struct GENXPRM
    {
    float  xBound, yBound, zBound;
    float  red, green, blue, unknown;
    uint32_t   type;

    GENXPRM();
    ~GENXPRM();

    bool operator ==(const GENXPRM &other) const;
    bool operator !=(const GENXPRM &other) const;
    };

struct GENXMBO
    {
    float  x, y, z;

    GENXMBO();
    ~GENXMBO();

    bool operator ==(const GENXMBO &other) const;
    bool operator !=(const GENXMBO &other) const;
    };

struct GENXTEL
    {
    FORMID  destinationFid;
    GENPOSDATA destination;
    uint32_t  flags;

    GENXTEL();
    ~GENXTEL();

    bool operator ==(const GENXTEL &other) const;
    bool operator !=(const GENXTEL &other) const;
    };

struct GENMAPDATA
    {
    //XMRK; //Map Data Marker (Empty)
    ReqSimpleSubRecord<uint8_t> FNAM; //Flags
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
    float  rangeRadius;
    uint32_t   rangeType;
    float  staticPercentage;
    FORMID   positionReference;

    GENXRDO();
    ~GENXRDO();

    bool operator ==(const GENXRDO &other) const;
    bool operator !=(const GENXRDO &other) const;
    };

struct GENAMMO
    {
    OptSimpleSubRecord<FORMID> XAMT; //Type
    OptSimpleSubRecord<int32_t> XAMC; //Count

    void Write(FileWriter &writer);

    bool operator ==(const GENAMMO &other) const;
    bool operator !=(const GENAMMO &other) const;
    };

struct GENXPWR
    {
    FORMID reference; //reference
    uint32_t type; //type

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
    bool IsType(uint32_t Type);
    void SetType(uint32_t Type);

    bool operator ==(const GENXPWR &other) const;
    bool operator !=(const GENXPWR &other) const;
    };

struct GENXDCR //Linked Decal (almost entirely unused, possibly not fully implemented by Bethesda)
    {
    FORMID reference; //Reference
    uint8_t  unknown1[24]; //Unknown (zero filled)

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
    float delay; //Delay

    GENXAPR();
    ~GENXAPR();

    bool operator ==(const GENXAPR &other) const;
    bool operator !=(const GENXAPR &other) const;
    };

struct GENACTPARENT
    {
    ReqSimpleSubRecord<uint8_t> XAPD; //Flags
    UnorderedSparseArray<GENXAPR *> XAPR; //Activate Parent Refs

    enum flagsFlags
        {
        fIsParentActivateOnly = 0x00000001
        };

    bool IsParentActivateOnly();
    void IsParentActivateOnly(bool value);
    bool IsFlagMask(uint8_t Mask, bool Exact=false);
    void SetFlagMask(uint8_t Mask);

    void Write(FileWriter &writer);

    bool operator ==(const GENACTPARENT &other) const;
    bool operator !=(const GENACTPARENT &other) const;
    };

struct GENXNDP
    {
    FORMID navMesh; //Navigation Mesh
    uint16_t unknown1; //Unknown
    uint8_t  unused1[2]; //Unused

    GENXNDP();
    ~GENXNDP();

    bool operator ==(const GENXNDP &other) const;
    bool operator !=(const GENXNDP &other) const;
    };

struct GENPOSITION
    {
    float width, height, //Size
            xPos, yPos, zPos, //Position
            q1, q2, q3, q4; //Rotation (Quaternion?)

    GENPOSITION();
    ~GENPOSITION();

    bool operator ==(const GENPOSITION &other) const;
    bool operator !=(const GENPOSITION &other) const;
    };

struct GENXRMR
    {
    uint16_t  count; //Linked Rooms Count
    uint8_t   unknown1[2]; //Unknown

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
    SemiOptSimpleSubRecord<int32_t> XRNK; //Faction Rank

    void Write(FileWriter &writer);

    bool operator ==(const FNVXOWN &other) const;
    bool operator !=(const FNVXOWN &other) const;
    };

struct FNVXLOC
    {
    uint8_t   level, unused1[3];
    FORMID  key;
    uint8_t   flags, unused2[3], unknown[8]; //unknown[8] not always present on chunk...

    FNVXLOC();
    ~FNVXLOC();

    bool operator ==(const FNVXLOC &other) const;
    bool operator !=(const FNVXLOC &other) const;
    };

struct FNVAIDT
    {
    uint8_t   aggression, confidence, energyLevel, responsibility, mood, unused1[3];
    uint32_t  flags;
    int8_t   trainSkill;
    uint8_t   trainLevel, assistance, aggroFlags;
    int32_t  aggroRadius;

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
    uint32_t  flags; // Flags
    uint16_t  fatigue, barterGold; // Fatigue, Barter gold
    int16_t  level; // Level or Level Multiplier
    uint16_t  calcMin, calcMax, speedMult; // Calc min, Calc max, Speed Multiplier
    float karma; // Karma (Alignment)
    int16_t  dispBase; // Disposition Base
    uint16_t  templateFlags; // Template Flags

    FNVACBS();
    ~FNVACBS();

    bool operator ==(const FNVACBS &other) const;
    bool operator !=(const FNVACBS &other) const;
    };

struct FNVLVLO
    {
    ReqSubRecord<LVLLVLO> LVLO;
    OptSubRecord<GENCOED> COED;

    bool IsGlobal() const; //Hack
    bool IsRank() const;   //Hack

    void Write(FileWriter &writer);

    bool operator ==(const FNVLVLO &other) const;
    bool operator !=(const FNVLVLO &other) const;
    };

struct SURVDATA // Data
    {
    uint32_t  threshold; // Trigger Threshold
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
    float fogNear, fogFar; //Fog Near, Fog Far
    int32_t  directionalXY, directionalZ; //Directional Rotation XY, Directional Rotation Z
    float directionalFade, fogClip, fogPower; //Directional Fade, Fog Clip Dist, Fog Power

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
