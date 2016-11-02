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
#include "common/Common.h"
#include "MGEFRecord.h"

namespace Ob
{
MGEFRecord::MGEFDATA::MGEFDATA():
    flags(0),
    baseCost(0.0f),
    associated(0),
    schoolType(0),
    resistValue(0xFFFFFFFF),
    numCounters(0),
    light(0),
    projectileSpeed(0.0f),
    effectShader(0),
    enchantEffect(0),
    castingSound(0),
    boltSound(0),
    hitSound(0),
    areaSound(0),
    cefEnchantment(0.0f),
    cefBarter(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

MGEFRecord::MGEFDATA::~MGEFDATA()
    {
    //
    }

bool MGEFRecord::MGEFDATA::operator ==(const MGEFDATA &other) const
    {
    return (flags == other.flags &&
            associated == other.associated &&
            schoolType == other.schoolType &&
            resistValue == other.resistValue &&
            numCounters == other.numCounters &&
            light == other.light &&
            effectShader == other.effectShader &&
            enchantEffect == other.enchantEffect &&
            castingSound == other.castingSound &&
            boltSound == other.boltSound &&
            hitSound == other.hitSound &&
            areaSound == other.areaSound &&
            AlmostEqual(baseCost,other.baseCost,2) &&
            AlmostEqual(projectileSpeed,other.projectileSpeed,2) &&
            AlmostEqual(cefEnchantment,other.cefEnchantment,2) &&
            AlmostEqual(cefBarter,other.cefBarter,2));
    }

bool MGEFRecord::MGEFDATA::operator !=(const MGEFDATA &other) const
    {
    return !(*this == other);
    }

MGEFRecord::OBMEEDDX::OBMEEDDX()
    {
    memset(&mgefCode[0], 0x00, sizeof(mgefCode));
    }

MGEFRecord::OBMEEDDX::~OBMEEDDX()
    {
    //
    }

bool MGEFRecord::OBMEEDDX::operator ==(const OBMEEDDX &other) const
    {
    return mgefCode == other.mgefCode;
    }

bool MGEFRecord::OBMEEDDX::operator !=(const OBMEEDDX &other) const
    {
    return !(*this == other);
    }

MGEFRecord::MGEFOBME::MGEFOBME():
    recordVersion(0),
    betaVersion(0),
    minorVersion(0),
    majorVersion(0),
    mgefParamAInfo(0),
    mgefParamBInfo(0),
    handlerCode(0),
    flags(0),
    mgefParamB(0)
    {
    memset(&reserved1[0], 0x00, sizeof(reserved1));
    memset(&reserved2[0], 0x00, sizeof(reserved2));
    }

MGEFRecord::MGEFOBME::~MGEFOBME()
    {
    //
    }

bool MGEFRecord::MGEFOBME::operator ==(const MGEFOBME &other) const
    {
    return (recordVersion == other.recordVersion &&
            betaVersion == other.betaVersion &&
            minorVersion == other.minorVersion &&
            majorVersion == other.majorVersion &&
            mgefParamAInfo == other.mgefParamAInfo &&
            mgefParamBInfo == other.mgefParamBInfo &&
            reserved1 == other.reserved1 &&
            handlerCode == other.handlerCode &&
            flags == other.flags &&
            mgefParamB == other.mgefParamB &&
            reserved2 == other.reserved2);
    }

bool MGEFRecord::MGEFOBME::operator !=(const MGEFOBME &other) const
    {
    return !(*this == other);
    }

bool MGEFRecord::OBMEMGEF::operator ==(const OBMEMGEF &other) const
    {
    return (OBME == other.OBME &&
            EDDX == other.EDDX &&
            DATX == other.DATX);
    }

bool MGEFRecord::OBMEMGEF::operator !=(const OBMEMGEF &other) const
    {
    return !(*this == other);
    }

MGEFRecord::MGEFRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

MGEFRecord::MGEFRecord(MGEFRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    EDID = srcRecord->EDID;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MODL = srcRecord->MODL;
    DATA = srcRecord->DATA;
    ESCE = srcRecord->ESCE;
    OBME = srcRecord->OBME;
    }

MGEFRecord::~MGEFRecord()
    {
    //
    }

bool MGEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(OBME.IsLoaded())
        {
        //Conditional resolution of mgefCode's based on JRoush's OBME mod
        //It's resolved just like a formID, except it uses the lower byte instead of the upper
        if(*(MGEFCODE *)&OBME->EDDX.value.mgefCode[0] >= 0x80000000)
            {
            MGEFCODE tempMgef = *(MGEFCODE *)&OBME->EDDX.value.mgefCode[0];
            op.AcceptMGEF(tempMgef);
            memcpy(&OBME->EDDX.value.mgefCode[0], &tempMgef, sizeof(OBME->EDDX.value.mgefCode) - 1);
            OBME->EDDX.value.mgefCode[4] = 0;
            }

        if(OBME->OBME.IsLoaded())
            {
            switch(OBME->OBME.value.mgefParamAInfo)
                {
                case 1: //It's a regular formID, so nothing fancy.
                    op.Accept(DATA.value.associated);
                    break;
                case 2: //It's a mgefCode, and not a formID at all.
                    //Conditional resolution of mgefCode's based on JRoush's OBME mod
                    //It's resolved just like a formID, except it uses the lower byte instead of the upper
                    if(DATA.value.associated >= 0x80000000)
                        op.AcceptMGEF(DATA.value.associated);
                    break;
                case 3: //It's an actor value, and not a formID at all.
                    //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                    //It's resolved just like a formID
                    if(DATA.value.associated >= 0x800)
                        op.Accept(DATA.value.associated);
                    break;
                default: //It's not a formID, mgefCode, or fancied up actor value
                    //so do nothing
                    break;
                }
            switch(OBME->OBME.value.mgefParamBInfo)
                {
                case 1: //It's a regular formID, so nothing fancy.
                    op.Accept(OBME->OBME.value.mgefParamB);
                    break;
                case 2: //It's a mgefCode, and not a formID at all.
                    //Conditional resolution of mgefCode's based on JRoush's OBME mod
                    //It's resolved just like a formID, except it uses the lower byte instead of the upper
                    if(OBME->OBME.value.mgefParamB >= 0x80000000)
                        op.AcceptMGEF(OBME->OBME.value.mgefParamB);
                    break;
                case 3: //It's an actor value, and not a formID at all.
                    //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                    //It's resolved just like a formID
                    if(OBME->OBME.value.mgefParamB >= 0x800)
                        op.Accept(OBME->OBME.value.mgefParamB);
                    break;
                default: //It's not a formID, mgefCode, or fancied up actor value
                    //so do nothing
                    break;
                }
            }

        op.Accept(DATA.value.light);
        op.Accept(DATA.value.effectShader);
        op.Accept(DATA.value.enchantEffect);
        op.Accept(DATA.value.castingSound);
        op.Accept(DATA.value.boltSound);
        op.Accept(DATA.value.hitSound);
        op.Accept(DATA.value.areaSound);

        if(DATA.value.resistValue >= 0x800)
            op.Accept(DATA.value.resistValue);

        for(uint32_t ListIndex = 0; ListIndex < ESCE.value.size(); ++ListIndex)
            if(ESCE.value[ListIndex] >= 0x80000000)
                op.AcceptMGEF(ESCE.value[ListIndex]);
        }
    else
        {
        op.Accept(DATA.value.associated);
        op.Accept(DATA.value.light);
        op.Accept(DATA.value.effectShader);
        op.Accept(DATA.value.enchantEffect);
        op.Accept(DATA.value.castingSound);
        op.Accept(DATA.value.boltSound);
        op.Accept(DATA.value.hitSound);
        op.Accept(DATA.value.areaSound);
        }

    return op.Stop();
    }

bool MGEFRecord::IsHostile()
    {
    return (DATA.value.flags & fIsHostile) != 0;
    }

void MGEFRecord::IsHostile(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsHostile, value);
    }

bool MGEFRecord::IsRecover()
    {
    return (DATA.value.flags & fIsRecover) != 0;
    }

void MGEFRecord::IsRecover(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsRecover, value);
    }

bool MGEFRecord::IsDetrimental()
    {
    return (DATA.value.flags & fIsDetrimental) != 0;
    }

void MGEFRecord::IsDetrimental(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsDetrimental, value);
    }

bool MGEFRecord::IsMagnitudeIsPercent()
    {
    return (DATA.value.flags & fIsMagnitudeIsPercent) != 0;
    }

void MGEFRecord::IsMagnitudeIsPercent(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsMagnitudeIsPercent, value);
    }

bool MGEFRecord::IsSelf()
    {
    return (DATA.value.flags & fIsSelf) != 0;
    }

void MGEFRecord::IsSelf(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsSelf, value);
    }

bool MGEFRecord::IsTouch()
    {
    return (DATA.value.flags & fIsTouch) != 0;
    }

void MGEFRecord::IsTouch(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsTouch, value);
    }

bool MGEFRecord::IsTarget()
    {
    return (DATA.value.flags & fIsTarget) != 0;
    }

void MGEFRecord::IsTarget(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsTarget, value);
    }

bool MGEFRecord::IsNoDuration()
    {
    return (DATA.value.flags & fIsNoDuration) != 0;
    }

void MGEFRecord::IsNoDuration(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsNoDuration, value);
    }

bool MGEFRecord::IsNoMagnitude()
    {
    return (DATA.value.flags & fIsNoMagnitude) != 0;
    }

void MGEFRecord::IsNoMagnitude(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsNoMagnitude, value);
    }

bool MGEFRecord::IsNoArea()
    {
    return (DATA.value.flags & fIsNoArea) != 0;
    }

void MGEFRecord::IsNoArea(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsNoArea, value);
    }

bool MGEFRecord::IsFXPersist()
    {
    return (DATA.value.flags & fIsFXPersist) != 0;
    }

void MGEFRecord::IsFXPersist(bool value)
    {
    SETBIT(DATA.value.flags, fIsFXPersist, value);
    }

bool MGEFRecord::IsSpellmaking()
    {
    return (DATA.value.flags & fIsSpellmaking) != 0;
    }

void MGEFRecord::IsSpellmaking(bool value)
    {
    SETBIT(DATA.value.flags, fIsSpellmaking, value);
    }

bool MGEFRecord::IsEnchanting()
    {
    return (DATA.value.flags & fIsEnchanting) != 0;
    }

void MGEFRecord::IsEnchanting(bool value)
    {
    SETBIT(DATA.value.flags, fIsEnchanting, value);
    }

bool MGEFRecord::IsNoIngredient()
    {
    return (DATA.value.flags & fIsNoIngredient) != 0;
    }

void MGEFRecord::IsNoIngredient(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoIngredient, value);
    }

bool MGEFRecord::IsUnknownF()
    {
    return (DATA.value.flags & fIsUnknownF) != 0;
    }

void MGEFRecord::IsUnknownF(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUnknownF, value);
    }

bool MGEFRecord::IsNoRecast()
    {
    return (DATA.value.flags & fIsNoRecast) != 0;
    }

void MGEFRecord::IsNoRecast(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsNoRecast, value);
    }

bool MGEFRecord::IsUseWeapon()
    {
    return (DATA.value.flags & fIsUseWeapon) != 0;
    }

void MGEFRecord::IsUseWeapon(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUseWeapon, value);
    }

bool MGEFRecord::IsUseArmor()
    {
    return (DATA.value.flags & fIsUseArmor) != 0;
    }

void MGEFRecord::IsUseArmor(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUseArmor, value);
    }

bool MGEFRecord::IsUseCreature()
    {
    return (DATA.value.flags & fIsUseCreature) != 0;
    }

void MGEFRecord::IsUseCreature(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUseCreature, value);
    }

bool MGEFRecord::IsUseSkill()
    {
    return (DATA.value.flags & fIsUseSkill) != 0;
    }

void MGEFRecord::IsUseSkill(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUseSkill, value);
    }

bool MGEFRecord::IsUseAttribute()
    {
    return (DATA.value.flags & fIsUseAttr) != 0;
    }

void MGEFRecord::IsUseAttribute(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsUseAttr, value);
    }

bool MGEFRecord::IsUseAttr()
    {
    return IsUseAttribute();
    }

void MGEFRecord::IsUseAttr(bool value)
    {
    IsUseAttribute(value);
    }

bool MGEFRecord::IsPCHasEffect()
    {
    return (DATA.value.flags & fIsPCHasEffect) != 0;
    }

void MGEFRecord::IsPCHasEffect(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsPCHasEffect, value);
    }

bool MGEFRecord::IsDisabled()
    {
    return (DATA.value.flags & fIsUseAttr) != 0;
    }

void MGEFRecord::IsDisabled(bool value)
    {
    SETBIT(DATA.value.flags, fIsDisabled, value);
    }

bool MGEFRecord::IsUnknownO()
    {
    return (DATA.value.flags & fIsUnknownO) != 0;
    }

void MGEFRecord::IsUnknownO(bool value)
    {
    SETBIT(DATA.value.flags, fIsUnknownO, value);
    }

bool MGEFRecord::IsUseActorValue()
    {
    return (DATA.value.flags & fIsUseAV) != 0;
    }

void MGEFRecord::IsUseActorValue(bool value)
    {
    SETBIT(DATA.value.flags, fIsUseAV, value);
    }

bool MGEFRecord::IsUseAV()
    {
    return IsUseActorValue();
    }

void MGEFRecord::IsUseAV(bool value)
    {
    IsUseActorValue(value);
    }

bool MGEFRecord::IsSprayType()
    {
    return ((DATA.value.flags & fIsSprayType) != 0) && ((DATA.value.flags & fIsBoltType) == 0);
    }

void MGEFRecord::IsSprayType(bool value)
    {
    if(value)
        {
        DATA.value.flags &= ~fIsFogType;
        DATA.value.flags |= fIsSprayType;
        }
    else if(IsSprayType())
        IsBallType(true);
    }

bool MGEFRecord::IsBoltType()
    {
    return ((DATA.value.flags & fIsBoltType) != 0) && ((DATA.value.flags & fIsSprayType) == 0);
    }

void MGEFRecord::IsBoltType(bool value)
    {
    if(value)
        {
        DATA.value.flags &= ~fIsFogType;
        DATA.value.flags |= fIsBoltType;
        }
    else if(IsBoltType())
        IsBallType(true);
    }

bool MGEFRecord::IsFogType()
    {
    return (DATA.value.flags & fIsFogType) == fIsFogType;
    }

void MGEFRecord::IsFogType(bool value)
    {
    if(value)
        DATA.value.flags |= fIsFogType;
    else if(IsFogType())
        IsBallType(true);
    }

bool MGEFRecord::IsBallType()
    {
    return (DATA.value.flags & fIsFogType) == 0;
    }

void MGEFRecord::IsBallType(bool value)
    {
    if(value)
        DATA.value.flags &= ~fIsFogType;
    else if(IsBallType())
        IsBoltType(true);
    }

bool MGEFRecord::IsNoHitEffect()
    {
    return (DATA.value.flags & fIsNoHitEffect) != 0;
    }

void MGEFRecord::IsNoHitEffect(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoHitEffect, value);
    }

bool MGEFRecord::IsPersistOnDeath()
    {
    return (DATA.value.flags & fIsPersistOnDeath) != 0;
    }

void MGEFRecord::IsPersistOnDeath(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsPersistOnDeath, value);
    }

bool MGEFRecord::IsExplodesWithForce()
    {
    return (DATA.value.flags & fIsExplodesWithForce) != 0;
    }

void MGEFRecord::IsExplodesWithForce(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsExplodesWithForce, value);
    }

bool MGEFRecord::IsMagnitudeIsLevel()
    {
    return (DATA.value.flags & fIsMagnitudeIsLevel) != 0;
    }

void MGEFRecord::IsMagnitudeIsLevel(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsMagnitudeIsLevel, value);
    }

bool MGEFRecord::IsMagnitudeIsFeet()
    {
    return (DATA.value.flags & fIsMagnitudeIsFeet) != 0;
    }

void MGEFRecord::IsMagnitudeIsFeet(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    SETBIT(DATA.value.flags, fIsMagnitudeIsFeet, value);
    }

bool MGEFRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void MGEFRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

//OBME flags
bool MGEFRecord::IsBeneficial()
    {
    return (OBME->OBME.value.flags & fOBME_IsBeneficial) != 0;
    }

void MGEFRecord::IsBeneficial(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsBeneficial) : (OBME->OBME.value.flags & ~fOBME_IsBeneficial);
    }

bool MGEFRecord::IsMagnitudeIsRange()
    {
    return (OBME->OBME.value.flags & fOBME_IsMagnitudeIsRange) != 0;
    }

void MGEFRecord::IsMagnitudeIsRange(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsMagnitudeIsRange) : (OBME->OBME.value.flags & ~fOBME_IsMagnitudeIsRange);
    }

bool MGEFRecord::IsAtomicResistance()
    {
    return (OBME->OBME.value.flags & fOBME_IsAtomicResistance) != 0;
    }

void MGEFRecord::IsAtomicResistance(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsAtomicResistance) : (OBME->OBME.value.flags & ~fOBME_IsAtomicResistance);
    }

bool MGEFRecord::IsParamFlagA()
    {
    return (OBME->OBME.value.flags & fOBME_IsParamFlagA) != 0;
    }

void MGEFRecord::IsParamFlagA(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsParamFlagA) : (OBME->OBME.value.flags & ~fOBME_IsParamFlagA);
    }

bool MGEFRecord::IsParamFlagB()
    {
    return (OBME->OBME.value.flags & fOBME_IsParamFlagB) != 0;
    }

void MGEFRecord::IsParamFlagB(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsParamFlagB) : (OBME->OBME.value.flags & ~fOBME_IsParamFlagB);
    }

bool MGEFRecord::IsParamFlagC()
    {
    return (OBME->OBME.value.flags & fOBME_IsParamFlagC) != 0;
    }

void MGEFRecord::IsParamFlagC(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsParamFlagC) : (OBME->OBME.value.flags & ~fOBME_IsParamFlagC);
    }

bool MGEFRecord::IsParamFlagD()
    {
    return (OBME->OBME.value.flags & fOBME_IsParamFlagD) != 0;
    }

void MGEFRecord::IsParamFlagD(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsParamFlagD) : (OBME->OBME.value.flags & ~fOBME_IsParamFlagD);
    }

bool MGEFRecord::IsHidden()
    {
    return (OBME->OBME.value.flags & fOBME_IsHidden) != 0;
    }

void MGEFRecord::IsHidden(bool value)
    {
    if(!OBME.IsLoaded()) return; //Only settable if OBME is enabled
    OBME->OBME.value.flags = value ? (OBME->OBME.value.flags | fOBME_IsHidden) : (OBME->OBME.value.flags & ~fOBME_IsHidden);
    }

bool MGEFRecord::IsOBMEFlagMask(uint32_t Mask, bool Exact)
    {
    if(!OBME.IsLoaded()) return false;
    return Exact ? ((OBME->OBME.value.flags & Mask) == Mask) : ((OBME->OBME.value.flags & Mask) != 0);
    }

void MGEFRecord::SetOBMEFlagMask(uint32_t Mask)
    {
    OBME.Load();
    OBME->OBME.value.flags = Mask;
    }

bool MGEFRecord::IsSchoolAlteration()
    {
    return (DATA.value.schoolType == eAlteration);
    }

void MGEFRecord::IsSchoolAlteration(bool value)
    {
    DATA.value.schoolType = value ? eAlteration : eConjuration;
    }

bool MGEFRecord::IsSchoolConjuration()
    {
    return (DATA.value.schoolType == eConjuration);
    }

void MGEFRecord::IsSchoolConjuration(bool value)
    {
    DATA.value.schoolType = value ? eConjuration : eAlteration;
    }

bool MGEFRecord::IsSchoolDestruction()
    {
    return (DATA.value.schoolType == eDestruction);
    }

void MGEFRecord::IsSchoolDestruction(bool value)
    {
    DATA.value.schoolType = value ? eDestruction : eAlteration;
    }

bool MGEFRecord::IsSchoolIllusion()
    {
    return (DATA.value.schoolType == eIllusion);
    }

void MGEFRecord::IsSchoolIllusion(bool value)
    {
    DATA.value.schoolType = value ? eIllusion : eAlteration;
    }

bool MGEFRecord::IsSchoolMysticism()
    {
    return (DATA.value.schoolType == eMysticism);
    }

void MGEFRecord::IsSchoolMysticism(bool value)
    {
    DATA.value.schoolType = value ? eMysticism : eAlteration;
    }

bool MGEFRecord::IsSchoolRestoration()
    {
    return (DATA.value.schoolType == eRestoration);
    }

void MGEFRecord::IsSchoolRestoration(bool value)
    {
    DATA.value.schoolType = value ? eRestoration : eAlteration;
    }

bool MGEFRecord::IsSchool(uint32_t Type)
    {
    return (DATA.value.schoolType == Type);
    }

void MGEFRecord::SetSchool(uint32_t Type)
    {
    DATA.value.schoolType = Type;
    }

uint32_t MGEFRecord::GetType()
    {
    return REV32(MGEF);
    }

char * MGEFRecord::GetStrType()
    {
    return "MGEF";
    }

bool MGEFRecord::IsKeyedByEditorID()
    {
    return true;
    }

char * MGEFRecord::GetEditorIDKey()
    {
    if(OBME.IsLoaded())
        return &OBME->EDDX.value.mgefCode[0];
    else
        return (char *)GetField(4);
    }

int32_t MGEFRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(EDDX):
                //Is switched with the normal EDID on read and write so that the EDID field is a char *as expected
                OBME.Load();
                memcpy(&OBME->EDDX.value.mgefCode[0], EDID.value, sizeof(OBME->EDDX.value.mgefCode) - 1);
                OBME->EDDX.value.mgefCode[4] = 0x00;
                EDID.Unload();
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ESCE):
                ESCE.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  MGEF: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t MGEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    if(OBME.IsLoaded())
        EDID.Unload(); //Don't unload OBME since OBME->EDDX.value.mgefCode is used to index the record
    else
        OBME.Unload(); //Don't unload EDID since it is used to index the record

    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MODL.Unload();
    DATA.Unload();
    ESCE.Unload();
    return 1;
    }

int32_t MGEFRecord::WriteRecord(FileWriter &writer)
    {
    if(OBME.IsLoaded())
        {
        //EDDX and EDID are switched internally for consistency
        //So EDDX is written as if it was the EDID chunk, and vice versa
        //Hence the mismatched type in record_write_subrecord
        if(OBME->EDDX.IsLoaded())
            OBME->WRITEAS(EDDX,EDID);
        if(OBME->OBME.IsLoaded())
            OBME->WRITE(OBME);
        WRITEAS(EDID,EDDX);
        WRITE(FULL);
        WRITE(DESC);
        WRITE(ICON);
        MODL.Write(writer);
        DATA.value.numCounters = (uint16_t)ESCE.value.size(); //Just to ensure that the proper value is written
        WRITE(DATA);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        WRITE(ESCE);
        }
    else
        {
        WRITE(EDID);
        WRITE(FULL);
        WRITE(DESC);
        WRITE(ICON);
        MODL.Write(writer);
        DATA.value.numCounters = (uint16_t)ESCE.value.size(); //Just to ensure that the proper value is written
        WRITE(DATA);
        WRITE(ESCE);
        }

    return -1;
    }

bool MGEFRecord::operator ==(const MGEFRecord &other) const
    {
    return (FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            OBME == other.OBME &&
            ESCE == other.ESCE);
    }

bool MGEFRecord::operator !=(const MGEFRecord &other) const
    {
    return !(*this == other);
    }

bool MGEFRecord::equals(Record *other)
    {
    return *this == *(MGEFRecord *)other;
    }
}