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
#include "..\..\Common.h"
#include "CREARecord.h"

namespace FNV
{
CREARecord::CREADATA::CREADATA():
    creatureType(eAnimal),
    combat(50),
    magic(50),
    stealth(50),
    health(50),
    attackDamage(0),
    strength(5),
    perception(5),
    endurance(5),
    charisma(5),
    intelligence(5),
    agility(5),
    luck(5)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

CREARecord::CREADATA::~CREADATA()
    {
    //
    }

bool CREARecord::CREADATA::operator ==(const CREADATA &other) const
    {
    return (creatureType == other.creatureType &&
            combat == other.combat &&
            magic == other.magic &&
            stealth == other.stealth &&
            health == other.health &&
            attackDamage == other.attackDamage &&
            strength == other.strength &&
            perception == other.perception &&
            endurance == other.endurance &&
            charisma == other.charisma &&
            intelligence == other.intelligence &&
            agility == other.agility &&
            luck == other.luck);
    }

bool CREARecord::CREADATA::operator !=(const CREADATA &other) const
    {
    return !(*this == other);
    }

void CREARecord::CREASound::Write(FileWriter &writer)
    {
    WRITE(CSDI);
    WRITE(CSDC);
    }

bool CREARecord::CREASound::operator ==(const CREASound &other) const
    {
    return (CSDI == other.CSDI &&
            CSDC == other.CSDC);
    }

bool CREARecord::CREASound::operator !=(const CREASound &other) const
    {
    return !(*this == other);
    }

bool CREARecord::CREASoundType::IsLeftFoot()
    {
    return (CSDT.value == eLeftFoot);
    }

void CREARecord::CREASoundType::IsLeftFoot(bool value)
    {
    CSDT.value = value ? eLeftFoot : eRightFoot;
    }

bool CREARecord::CREASoundType::IsRightFoot()
    {
    return (CSDT.value == eRightFoot);
    }

void CREARecord::CREASoundType::IsRightFoot(bool value)
    {
    CSDT.value = value ? eRightFoot : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsLeftBackFoot()
    {
    return (CSDT.value == eLeftBackFoot);
    }

void CREARecord::CREASoundType::IsLeftBackFoot(bool value)
    {
    CSDT.value = value ? eLeftBackFoot : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsRightBackFoot()
    {
    return (CSDT.value == eRightBackFoot);
    }

void CREARecord::CREASoundType::IsRightBackFoot(bool value)
    {
    CSDT.value = value ? eRightBackFoot : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsIdle()
    {
    return (CSDT.value == eIdle);
    }

void CREARecord::CREASoundType::IsIdle(bool value)
    {
    CSDT.value = value ? eIdle : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAware()
    {
    return (CSDT.value == eAware);
    }

void CREARecord::CREASoundType::IsAware(bool value)
    {
    CSDT.value = value ? eAware : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAttack()
    {
    return (CSDT.value == eAttack);
    }

void CREARecord::CREASoundType::IsAttack(bool value)
    {
    CSDT.value = value ? eAttack : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsHit()
    {
    return (CSDT.value == eHit);
    }

void CREARecord::CREASoundType::IsHit(bool value)
    {
    CSDT.value = value ? eHit : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsDeath()
    {
    return (CSDT.value == eDeath);
    }

void CREARecord::CREASoundType::IsDeath(bool value)
    {
    CSDT.value = value ? eDeath : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsWeapon()
    {
    return (CSDT.value == eWeapon);
    }

void CREARecord::CREASoundType::IsWeapon(bool value)
    {
    CSDT.value = value ? eWeapon : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsMovementLoop()
    {
    return (CSDT.value == eMovementLoop);
    }

void CREARecord::CREASoundType::IsMovementLoop(bool value)
    {
    CSDT.value = value ? eMovementLoop : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsConsciousLoop()
    {
    return (CSDT.value == eConsciousLoop);
    }

void CREARecord::CREASoundType::IsConsciousLoop(bool value)
    {
    CSDT.value = value ? eConsciousLoop : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary1()
    {
    return (CSDT.value == eAuxiliary1);
    }

void CREARecord::CREASoundType::IsAuxiliary1(bool value)
    {
    CSDT.value = value ? eAuxiliary1 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary2()
    {
    return (CSDT.value == eAuxiliary2);
    }

void CREARecord::CREASoundType::IsAuxiliary2(bool value)
    {
    CSDT.value = value ? eAuxiliary2 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary3()
    {
    return (CSDT.value == eAuxiliary3);
    }

void CREARecord::CREASoundType::IsAuxiliary3(bool value)
    {
    CSDT.value = value ? eAuxiliary3 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary4()
    {
    return (CSDT.value == eAuxiliary4);
    }

void CREARecord::CREASoundType::IsAuxiliary4(bool value)
    {
    CSDT.value = value ? eAuxiliary4 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary5()
    {
    return (CSDT.value == eAuxiliary5);
    }

void CREARecord::CREASoundType::IsAuxiliary5(bool value)
    {
    CSDT.value = value ? eAuxiliary5 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary6()
    {
    return (CSDT.value == eAuxiliary6);
    }

void CREARecord::CREASoundType::IsAuxiliary6(bool value)
    {
    CSDT.value = value ? eAuxiliary6 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary7()
    {
    return (CSDT.value == eAuxiliary7);
    }

void CREARecord::CREASoundType::IsAuxiliary7(bool value)
    {
    CSDT.value = value ? eAuxiliary7 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsAuxiliary8()
    {
    return (CSDT.value == eAuxiliary8);
    }

void CREARecord::CREASoundType::IsAuxiliary8(bool value)
    {
    CSDT.value = value ? eAuxiliary8 : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsJump()
    {
    return (CSDT.value == eJump);
    }

void CREARecord::CREASoundType::IsJump(bool value)
    {
    CSDT.value = value ? eJump : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsPlayRandomLoop()
    {
    return (CSDT.value == ePlayRandomLoop);
    }

void CREARecord::CREASoundType::IsPlayRandomLoop(bool value)
    {
    CSDT.value = value ? ePlayRandomLoop : eLeftFoot;
    }

bool CREARecord::CREASoundType::IsType(uint32_t Type)
    {
    return CSDT.value == Type;
    }

void CREARecord::CREASoundType::SetType(uint32_t Type)
    {
    CSDT.value = Type;
    }

void CREARecord::CREASoundType::Write(FileWriter &writer)
    {
    WRITE(CSDT);
    Sounds.Write(writer);
    }

bool CREARecord::CREASoundType::operator ==(const CREASoundType &other) const
    {
    return (CSDT == other.CSDT &&
            Sounds == other.Sounds);
    }

bool CREARecord::CREASoundType::operator !=(const CREASoundType &other) const
    {
    return !(*this == other);
    }

CREARecord::CREARecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //Creature AI differs by default from NPC AI
    AIDT.value.aggression = eAggressive;
    AIDT.value.energyLevel = 2;
    //Creature Configuration differs by default from NPC Configuration
    ACBS.value.flags = fIsWalks | fIsNoLowLevel;
    }

CREARecord::CREARecord(CREARecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SPLO = srcRecord->SPLO;
    EITM = srcRecord->EITM;
    EAMT = srcRecord->EAMT;
    NIFZ = srcRecord->NIFZ;
    NIFT = srcRecord->NIFT;
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    VTCK = srcRecord->VTCK;
    TPLT = srcRecord->TPLT;
    Destructable = srcRecord->Destructable;
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    AIDT = srcRecord->AIDT;
    PKID = srcRecord->PKID;
    KFFZ = srcRecord->KFFZ;
    DATA = srcRecord->DATA;
    RNAM = srcRecord->RNAM;
    ZNAM = srcRecord->ZNAM;
    PNAM = srcRecord->PNAM;
    TNAM = srcRecord->TNAM;
    BNAM = srcRecord->BNAM;
    WNAM = srcRecord->WNAM;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    CSCR = srcRecord->CSCR;
    Types = srcRecord->Types;
    CNAM = srcRecord->CNAM;
    LNAM = srcRecord->LNAM;
    return;
    }

CREARecord::~CREARecord()
    {
    //
    }

bool CREARecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t x = 0; x < SPLO.value.size(); x++)
        op.Accept(SPLO.value[x]);
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    for(uint32_t x = 0; x < SNAM.value.size(); x++)
        op.Accept(SNAM.value[x]->faction);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(VTCK.IsLoaded())
        op.Accept(VTCK.value);
    if(TPLT.IsLoaded())
        op.Accept(TPLT.value);
    if(Destructable.IsLoaded())
        {
        for(uint32_t x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(uint32_t x = 0; x < CNTO.value.size(); ++x)
        {
        op.Accept(CNTO.value[x]->CNTO.value.item);
        if(CNTO.value[x]->IsGlobal())
            op.Accept(CNTO.value[x]->COED->globalOrRank);
        }
    for(uint32_t x = 0; x < PKID.value.size(); x++)
        op.Accept(PKID.value[x]);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM.value);
    if(CSCR.IsLoaded())
        op.Accept(CSCR.value);
    for(uint32_t x = 0; x < Types.value.size(); x++)
        for(uint32_t p = 0; p < Types.value[x]->Sounds.value.size(); ++p)
            op.Accept(Types.value[x]->Sounds.value[p]->CSDI.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    if(LNAM.IsLoaded())
        op.Accept(LNAM.value);
    return op.Stop();
    }

bool CREARecord::IsBiped()
    {
    return (ACBS.value.flags & fIsBiped) != 0;
    }

void CREARecord::IsBiped(bool value)
    {
    SETBIT(ACBS.value.flags, fIsBiped, value);
    }

bool CREARecord::IsEssential()
    {
    return (ACBS.value.flags & fIsEssential) != 0;
    }

void CREARecord::IsEssential(bool value)
    {
    SETBIT(ACBS.value.flags, fIsEssential, value);
    }

bool CREARecord::IsWeaponAndShield()
    {
    return (ACBS.value.flags & fIsWeaponAndShield) != 0;
    }

void CREARecord::IsWeaponAndShield(bool value)
    {
    SETBIT(ACBS.value.flags, fIsWeaponAndShield, value);
    }

bool CREARecord::IsRespawn()
    {
    return (ACBS.value.flags & fIsRespawn) != 0;
    }

void CREARecord::IsRespawn(bool value)
    {
    SETBIT(ACBS.value.flags, fIsRespawn, value);
    }

bool CREARecord::IsSwims()
    {
    return (ACBS.value.flags & fIsSwims) != 0;
    }

void CREARecord::IsSwims(bool value)
    {
    SETBIT(ACBS.value.flags, fIsSwims, value);
    }

bool CREARecord::IsFlies()
    {
    return (ACBS.value.flags & fIsFlies) != 0;
    }

void CREARecord::IsFlies(bool value)
    {
    SETBIT(ACBS.value.flags, fIsFlies, value);
    }

bool CREARecord::IsWalks()
    {
    return (ACBS.value.flags & fIsWalks) != 0;
    }

void CREARecord::IsWalks(bool value)
    {
    SETBIT(ACBS.value.flags, fIsWalks, value);
    }

bool CREARecord::IsPCLevelOffset()
    {
    return (ACBS.value.flags & fIsPCLevelOffset) != 0;
    }

void CREARecord::IsPCLevelOffset(bool value)
    {
    SETBIT(ACBS.value.flags, fIsPCLevelOffset, value);
    }

bool CREARecord::IsUnknown1()
    {
    return (ACBS.value.flags & fIsUnknown1) != 0;
    }

void CREARecord::IsUnknown1(bool value)
    {
    SETBIT(ACBS.value.flags, fIsUnknown1, value);
    }

bool CREARecord::IsNoLowLevel()
    {
    return (ACBS.value.flags & fIsNoLowLevel) != 0;
    }

void CREARecord::IsNoLowLevel(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoLowLevel, value);
    }

bool CREARecord::IsNoBloodSpray()
    {
    return (ACBS.value.flags & fIsNoBloodSpray) != 0;
    }

void CREARecord::IsNoBloodSpray(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoBloodSpray, value);
    }

bool CREARecord::IsNoBloodDecal()
    {
    return (ACBS.value.flags & fIsNoBloodDecal) != 0;
    }

void CREARecord::IsNoBloodDecal(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoBloodDecal, value);
    }

bool CREARecord::IsNoHead()
    {
    return (ACBS.value.flags & fIsNoHead) != 0;
    }

void CREARecord::IsNoHead(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoHead, value);
    }

bool CREARecord::IsNoRightArm()
    {
    return (ACBS.value.flags & fIsNoRightArm) != 0;
    }

void CREARecord::IsNoRightArm(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoRightArm, value);
    }

bool CREARecord::IsNoLeftArm()
    {
    return (ACBS.value.flags & fIsNoLeftArm) != 0;
    }

void CREARecord::IsNoLeftArm(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoLeftArm, value);
    }

bool CREARecord::IsNoCombatInWater()
    {
    return (ACBS.value.flags & fIsNoCombatInWater) != 0;
    }

void CREARecord::IsNoCombatInWater(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoCombatInWater, value);
    }

bool CREARecord::IsNoShadow()
    {
    return (ACBS.value.flags & fIsNoShadow) != 0;
    }

void CREARecord::IsNoShadow(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoShadow, value);
    }

bool CREARecord::IsNoVATSMelee()
    {
    return (ACBS.value.flags & fIsNoVATSMelee) != 0;
    }

void CREARecord::IsNoVATSMelee(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoVATSMelee, value);
    }

bool CREARecord::IsAllowPCDialogue()
    {
    return (ACBS.value.flags & fIsAllowPCDialogue) != 0;
    }

void CREARecord::IsAllowPCDialogue(bool value)
    {
    SETBIT(ACBS.value.flags, fIsAllowPCDialogue, value);
    }

bool CREARecord::IsCantOpenDoors()
    {
    return (ACBS.value.flags & fIsCantOpenDoors) != 0;
    }

void CREARecord::IsCantOpenDoors(bool value)
    {
    SETBIT(ACBS.value.flags, fIsCantOpenDoors, value);
    }

bool CREARecord::IsImmobile()
    {
    return (ACBS.value.flags & fIsImmobile) != 0;
    }

void CREARecord::IsImmobile(bool value)
    {
    SETBIT(ACBS.value.flags, fIsImmobile, value);
    }

bool CREARecord::IsTiltFrontBack()
    {
    return (ACBS.value.flags & fIsTiltFrontBack) != 0;
    }

void CREARecord::IsTiltFrontBack(bool value)
    {
    SETBIT(ACBS.value.flags, fIsTiltFrontBack, value);
    }

bool CREARecord::IsTiltLeftRight()
    {
    return (ACBS.value.flags & fIsTiltLeftRight) != 0;
    }

void CREARecord::IsTiltLeftRight(bool value)
    {
    SETBIT(ACBS.value.flags, fIsTiltLeftRight, value);
    }

bool CREARecord::IsNoKnockdowns()
    {
    return (ACBS.value.flags & fIsNoKnockdowns) != 0;
    }

void CREARecord::IsNoKnockdowns(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoKnockdowns, value);
    }

bool CREARecord::IsNotPushable()
    {
    return (ACBS.value.flags & fIsNotPushable) != 0;
    }

void CREARecord::IsNotPushable(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNotPushable, value);
    }

bool CREARecord::IsAllowPickpocket()
    {
    return (ACBS.value.flags & fIsAllowPickpocket) != 0;
    }

void CREARecord::IsAllowPickpocket(bool value)
    {
    SETBIT(ACBS.value.flags, fIsAllowPickpocket, value);
    }

bool CREARecord::IsGhost()
    {
    return (ACBS.value.flags & fIsGhost) != 0;
    }

void CREARecord::IsGhost(bool value)
    {
    SETBIT(ACBS.value.flags, fIsGhost, value);
    }

bool CREARecord::IsNoHeadTracking()
    {
    return (ACBS.value.flags & fIsNoHeadTracking) != 0;
    }

void CREARecord::IsNoHeadTracking(bool value)
    {
    SETBIT(ACBS.value.flags, fIsNoHeadTracking, value);
    }

bool CREARecord::IsInvulnerable()
    {
    return (ACBS.value.flags & fIsInvulnerable) != 0;
    }

void CREARecord::IsInvulnerable(bool value)
    {
    SETBIT(ACBS.value.flags, fIsInvulnerable, value);
    }

bool CREARecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.flags & Mask) == Mask) : ((ACBS.value.flags & Mask) != 0);
    }

void CREARecord::SetFlagMask(uint32_t Mask)
    {
    ACBS.value.flags = Mask;
    }

bool CREARecord::IsUseTraits()
    {
    return (ACBS.value.templateFlags & fIsUseTraits) != 0;
    }

void CREARecord::IsUseTraits(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseTraits, value);
    }

bool CREARecord::IsUseStats()
    {
    return (ACBS.value.templateFlags & fIsUseStats) != 0;
    }

void CREARecord::IsUseStats(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseStats, value);
    }

bool CREARecord::IsUseFactions()
    {
    return (ACBS.value.templateFlags & fIsUseFactions) != 0;
    }

void CREARecord::IsUseFactions(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseFactions, value);
    }

bool CREARecord::IsUseAEList()
    {
    return (ACBS.value.templateFlags & fIsUseAEList) != 0;
    }

void CREARecord::IsUseAEList(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseAEList, value);
    }

bool CREARecord::IsUseAIData()
    {
    return (ACBS.value.templateFlags & fIsUseAIData) != 0;
    }

void CREARecord::IsUseAIData(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseAIData, value);
    }

bool CREARecord::IsUseAIPackages()
    {
    return (ACBS.value.templateFlags & fIsUseAIPackages) != 0;
    }

void CREARecord::IsUseAIPackages(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseAIPackages, value);
    }

bool CREARecord::IsUseModelAnim()
    {
    return (ACBS.value.templateFlags & fIsUseModelAnim) != 0;
    }

void CREARecord::IsUseModelAnim(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseModelAnim, value);
    }

bool CREARecord::IsUseBaseData()
    {
    return (ACBS.value.templateFlags & fIsUseBaseData) != 0;
    }

void CREARecord::IsUseBaseData(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseBaseData, value);
    }

bool CREARecord::IsUseInventory()
    {
    return (ACBS.value.templateFlags & fIsUseInventory) != 0;
    }

void CREARecord::IsUseInventory(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseInventory, value);
    }

bool CREARecord::IsUseScript()
    {
    return (ACBS.value.templateFlags & fIsUseScript) != 0;
    }

void CREARecord::IsUseScript(bool value)
    {
    SETBIT(ACBS.value.templateFlags, fIsUseScript, value);
    }

bool CREARecord::IsTemplateFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.templateFlags & Mask) == Mask) : ((ACBS.value.templateFlags & Mask) != 0);
    }

void CREARecord::SetTemplateFlagMask(uint16_t Mask)
    {
    ACBS.value.templateFlags = Mask;
    }

bool CREARecord::IsAggroRadiusBehavior()
    {
    return (AIDT.value.aggroFlags & fIsAggroRadiusBehavior) != 0;
    }

void CREARecord::IsAggroRadiusBehavior(bool value)
    {
    SETBIT(AIDT.value.aggroFlags, fIsAggroRadiusBehavior, value);
    }

bool CREARecord::IsAggroFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((AIDT.value.aggroFlags & Mask) == Mask) : ((AIDT.value.aggroFlags & Mask) != 0);
    }

void CREARecord::SetAggroFlagMask(uint8_t Mask)
    {
    AIDT.value.aggroFlags = Mask;
    }

bool CREARecord::IsServicesWeapons()
    {
    return (AIDT.value.flags & fIsServicesWeapons) != 0;
    }

void CREARecord::IsServicesWeapons(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesWeapons, value);
    }

bool CREARecord::IsServicesArmor()
    {
    return (AIDT.value.flags & fIsServicesArmor) != 0;
    }

void CREARecord::IsServicesArmor(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesArmor, value);
    }

bool CREARecord::IsServicesClothing()
    {
    return (AIDT.value.flags & fIsServicesClothing) != 0;
    }

void CREARecord::IsServicesClothing(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesClothing, value);
    }

bool CREARecord::IsServicesBooks()
    {
    return (AIDT.value.flags & fIsServicesBooks) != 0;
    }

void CREARecord::IsServicesBooks(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesBooks, value);
    }

bool CREARecord::IsServicesFood()
    {
    return (AIDT.value.flags & fIsServicesFood) != 0;
    }

void CREARecord::IsServicesFood(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesFood, value);
    }

bool CREARecord::IsServicesChems()
    {
    return (AIDT.value.flags & fIsServicesChems) != 0;
    }

void CREARecord::IsServicesChems(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesChems, value);
    }

bool CREARecord::IsServicesStimpacks()
    {
    return (AIDT.value.flags & fIsServicesStimpacks) != 0;
    }

void CREARecord::IsServicesStimpacks(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesStimpacks, value);
    }

bool CREARecord::IsServicesLights()
    {
    return (AIDT.value.flags & fIsServicesLights) != 0;
    }

void CREARecord::IsServicesLights(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesLights, value);
    }

bool CREARecord::IsServicesMiscItems()
    {
    return (AIDT.value.flags & fIsServicesMiscItems) != 0;
    }

void CREARecord::IsServicesMiscItems(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesMiscItems, value);
    }

bool CREARecord::IsServicesPotions()
    {
    return (AIDT.value.flags & fIsServicesPotions) != 0;
    }

void CREARecord::IsServicesPotions(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesPotions, value);
    }

bool CREARecord::IsServicesTraining()
    {
    return (AIDT.value.flags & fIsServicesTraining) != 0;
    }

void CREARecord::IsServicesTraining(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesTraining, value);
    }

bool CREARecord::IsServicesRecharge()
    {
    return (AIDT.value.flags & fIsServicesRecharge) != 0;
    }

void CREARecord::IsServicesRecharge(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesRecharge, value);
    }

bool CREARecord::IsServicesRepair()
    {
    return (AIDT.value.flags & fIsServicesRepair) != 0;
    }

void CREARecord::IsServicesRepair(bool value)
    {
    SETBIT(AIDT.value.flags, fIsServicesRepair, value);
    }

bool CREARecord::IsServicesFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((AIDT.value.flags & Mask) == Mask) : ((AIDT.value.flags & Mask) != 0);
    }

void CREARecord::SetServicesFlagMask(uint32_t Mask)
    {
    AIDT.value.flags = Mask;
    }

bool CREARecord::IsAnimal()
    {
    return DATA.value.creatureType == eAnimal;
    }

void CREARecord::IsAnimal(bool value)
    {
    DATA.value.creatureType = value ? eAnimal : eMutatedAnimal;
    }

bool CREARecord::IsMutatedAnimal()
    {
    return DATA.value.creatureType == eMutatedAnimal;
    }

void CREARecord::IsMutatedAnimal(bool value)
    {
    DATA.value.creatureType = value ? eMutatedAnimal : eAnimal;
    }

bool CREARecord::IsMutatedInsect()
    {
    return DATA.value.creatureType == eMutatedInsect;
    }

void CREARecord::IsMutatedInsect(bool value)
    {
    DATA.value.creatureType = value ? eMutatedInsect : eAnimal;
    }

bool CREARecord::IsAbomination()
    {
    return DATA.value.creatureType == eAbomination;
    }

void CREARecord::IsAbomination(bool value)
    {
    DATA.value.creatureType = value ? eAbomination : eAnimal;
    }

bool CREARecord::IsSuperMutant()
    {
    return DATA.value.creatureType == eSuperMutant;
    }

void CREARecord::IsSuperMutant(bool value)
    {
    DATA.value.creatureType = value ? eSuperMutant : eAnimal;
    }

bool CREARecord::IsFeralGhoul()
    {
    return DATA.value.creatureType == eFeralGhoul;
    }

void CREARecord::IsFeralGhoul(bool value)
    {
    DATA.value.creatureType = value ? eFeralGhoul : eAnimal;
    }

bool CREARecord::IsRobot()
    {
    return DATA.value.creatureType == eRobot;
    }

void CREARecord::IsRobot(bool value)
    {
    DATA.value.creatureType = value ? eRobot : eAnimal;
    }

bool CREARecord::IsGiant()
    {
    return DATA.value.creatureType == eGiant;
    }

void CREARecord::IsGiant(bool value)
    {
    DATA.value.creatureType = value ? eGiant : eAnimal;
    }

bool CREARecord::IsType(uint8_t Type)
    {
    return DATA.value.creatureType == Type;
    }

void CREARecord::SetType(uint8_t Type)
    {
    DATA.value.creatureType = Type;
    }

bool CREARecord::IsAttackLeft()
    {
    return EAMT.value == eAttackLeft;
    }

void CREARecord::IsAttackLeft(bool value)
    {
    EAMT.value = value ? eAttackLeft : eAttackLeftUp;
    }

bool CREARecord::IsAttackLeftUp()
    {
    return EAMT.value == eAttackLeftUp;
    }

void CREARecord::IsAttackLeftUp(bool value)
    {
    EAMT.value = value ? eAttackLeftUp : eAttackLeft;
    }

bool CREARecord::IsAttackLeftDown()
    {
    return EAMT.value == eAttackLeftDown;
    }

void CREARecord::IsAttackLeftDown(bool value)
    {
    EAMT.value = value ? eAttackLeftDown : eAttackLeft;
    }

bool CREARecord::IsAttackLeftIS()
    {
    return EAMT.value == eAttackLeftIS;
    }

void CREARecord::IsAttackLeftIS(bool value)
    {
    EAMT.value = value ? eAttackLeftIS : eAttackLeft;
    }

bool CREARecord::IsAttackLeftISUp()
    {
    return EAMT.value == eAttackLeftISUp;
    }

void CREARecord::IsAttackLeftISUp(bool value)
    {
    EAMT.value = value ? eAttackLeftISUp : eAttackLeft;
    }

bool CREARecord::IsAttackLeftISDown()
    {
    return EAMT.value == eAttackLeftISDown;
    }

void CREARecord::IsAttackLeftISDown(bool value)
    {
    EAMT.value = value ? eAttackLeftISDown : eAttackLeft;
    }

bool CREARecord::IsAttackRight()
    {
    return EAMT.value == eAttackRight;
    }

void CREARecord::IsAttackRight(bool value)
    {
    EAMT.value = value ? eAttackRight : eAttackLeft;
    }

bool CREARecord::IsAttackRightUp()
    {
    return EAMT.value == eAttackRightUp;
    }

void CREARecord::IsAttackRightUp(bool value)
    {
    EAMT.value = value ? eAttackRightUp : eAttackLeft;
    }

bool CREARecord::IsAttackRightDown()
    {
    return EAMT.value == eAttackRightDown;
    }

void CREARecord::IsAttackRightDown(bool value)
    {
    EAMT.value = value ? eAttackRightDown : eAttackLeft;
    }

bool CREARecord::IsAttackRightIS()
    {
    return EAMT.value == eAttackRightIS;
    }

void CREARecord::IsAttackRightIS(bool value)
    {
    EAMT.value = value ? eAttackRightIS : eAttackLeft;
    }

bool CREARecord::IsAttackRightISUp()
    {
    return EAMT.value == eAttackRightISUp;
    }

void CREARecord::IsAttackRightISUp(bool value)
    {
    EAMT.value = value ? eAttackRightISUp : eAttackLeft;
    }

bool CREARecord::IsAttackRightISDown()
    {
    return EAMT.value == eAttackRightISDown;
    }

void CREARecord::IsAttackRightISDown(bool value)
    {
    EAMT.value = value ? eAttackRightISDown : eAttackLeft;
    }

bool CREARecord::IsAttack3()
    {
    return EAMT.value == eAttack3;
    }

void CREARecord::IsAttack3(bool value)
    {
    EAMT.value = value ? eAttack3 : eAttackLeft;
    }

bool CREARecord::IsAttack3Up()
    {
    return EAMT.value == eAttack3Up;
    }

void CREARecord::IsAttack3Up(bool value)
    {
    EAMT.value = value ? eAttack3Up : eAttackLeft;
    }

bool CREARecord::IsAttack3Down()
    {
    return EAMT.value == eAttack3Down;
    }

void CREARecord::IsAttack3Down(bool value)
    {
    EAMT.value = value ? eAttack3Down : eAttackLeft;
    }

bool CREARecord::IsAttack3IS()
    {
    return EAMT.value == eAttack3IS;
    }

void CREARecord::IsAttack3IS(bool value)
    {
    EAMT.value = value ? eAttack3IS : eAttackLeft;
    }

bool CREARecord::IsAttack3ISUp()
    {
    return EAMT.value == eAttack3ISUp;
    }

void CREARecord::IsAttack3ISUp(bool value)
    {
    EAMT.value = value ? eAttack3ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack3ISDown()
    {
    return EAMT.value == eAttack3ISDown;
    }

void CREARecord::IsAttack3ISDown(bool value)
    {
    EAMT.value = value ? eAttack3ISDown : eAttackLeft;
    }

bool CREARecord::IsAttack4()
    {
    return EAMT.value == eAttack4;
    }

void CREARecord::IsAttack4(bool value)
    {
    EAMT.value = value ? eAttack4 : eAttackLeft;
    }

bool CREARecord::IsAttack4Up()
    {
    return EAMT.value == eAttack4Up;
    }

void CREARecord::IsAttack4Up(bool value)
    {
    EAMT.value = value ? eAttack4Up : eAttackLeft;
    }

bool CREARecord::IsAttack4Down()
    {
    return EAMT.value == eAttack4Down;
    }

void CREARecord::IsAttack4Down(bool value)
    {
    EAMT.value = value ? eAttack4Down : eAttackLeft;
    }

bool CREARecord::IsAttack4IS()
    {
    return EAMT.value == eAttack4IS;
    }

void CREARecord::IsAttack4IS(bool value)
    {
    EAMT.value = value ? eAttack4IS : eAttackLeft;
    }

bool CREARecord::IsAttack4ISUp()
    {
    return EAMT.value == eAttack4ISUp;
    }

void CREARecord::IsAttack4ISUp(bool value)
    {
    EAMT.value = value ? eAttack4ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack4ISDown()
    {
    return EAMT.value == eAttack4ISDown;
    }

void CREARecord::IsAttack4ISDown(bool value)
    {
    EAMT.value = value ? eAttack4ISDown : eAttackLeft;
    }

bool CREARecord::IsAttack5()
    {
    return EAMT.value == eAttack5;
    }

void CREARecord::IsAttack5(bool value)
    {
    EAMT.value = value ? eAttack5 : eAttackLeft;
    }

bool CREARecord::IsAttack5Up()
    {
    return EAMT.value == eAttack5Up;
    }

void CREARecord::IsAttack5Up(bool value)
    {
    EAMT.value = value ? eAttack5Up : eAttackLeft;
    }

bool CREARecord::IsAttack5Down()
    {
    return EAMT.value == eAttack5Down;
    }

void CREARecord::IsAttack5Down(bool value)
    {
    EAMT.value = value ? eAttack5Down : eAttackLeft;
    }

bool CREARecord::IsAttack5IS()
    {
    return EAMT.value == eAttack5IS;
    }

void CREARecord::IsAttack5IS(bool value)
    {
    EAMT.value = value ? eAttack5IS : eAttackLeft;
    }

bool CREARecord::IsAttack5ISUp()
    {
    return EAMT.value == eAttack5ISUp;
    }

void CREARecord::IsAttack5ISUp(bool value)
    {
    EAMT.value = value ? eAttack5ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack5ISDown()
    {
    return EAMT.value == eAttack5ISDown;
    }

void CREARecord::IsAttack5ISDown(bool value)
    {
    EAMT.value = value ? eAttack5ISDown : eAttackLeft;
    }

bool CREARecord::IsAttack6()
    {
    return EAMT.value == eAttack6;
    }

void CREARecord::IsAttack6(bool value)
    {
    EAMT.value = value ? eAttack6 : eAttackLeft;
    }

bool CREARecord::IsAttack6Up()
    {
    return EAMT.value == eAttack6Up;
    }

void CREARecord::IsAttack6Up(bool value)
    {
    EAMT.value = value ? eAttack6Up : eAttackLeft;
    }

bool CREARecord::IsAttack6Down()
    {
    return EAMT.value == eAttack6Down;
    }

void CREARecord::IsAttack6Down(bool value)
    {
    EAMT.value = value ? eAttack6Down : eAttackLeft;
    }

bool CREARecord::IsAttack6IS()
    {
    return EAMT.value == eAttack6IS;
    }

void CREARecord::IsAttack6IS(bool value)
    {
    EAMT.value = value ? eAttack6IS : eAttackLeft;
    }

bool CREARecord::IsAttack6ISUp()
    {
    return EAMT.value == eAttack6ISUp;
    }

void CREARecord::IsAttack6ISUp(bool value)
    {
    EAMT.value = value ? eAttack6ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack6ISDown()
    {
    return EAMT.value == eAttack6ISDown;
    }

void CREARecord::IsAttack6ISDown(bool value)
    {
    EAMT.value = value ? eAttack6ISDown : eAttackLeft;
    }

bool CREARecord::IsAttack7()
    {
    return EAMT.value == eAttack7;
    }

void CREARecord::IsAttack7(bool value)
    {
    EAMT.value = value ? eAttack7 : eAttackLeft;
    }

bool CREARecord::IsAttack7Up()
    {
    return EAMT.value == eAttack7Up;
    }

void CREARecord::IsAttack7Up(bool value)
    {
    EAMT.value = value ? eAttack7Up : eAttackLeft;
    }

bool CREARecord::IsAttack7Down()
    {
    return EAMT.value == eAttack7Down;
    }

void CREARecord::IsAttack7Down(bool value)
    {
    EAMT.value = value ? eAttack7Down : eAttackLeft;
    }

bool CREARecord::IsAttack7IS()
    {
    return EAMT.value == eAttack7IS;
    }

void CREARecord::IsAttack7IS(bool value)
    {
    EAMT.value = value ? eAttack7IS : eAttackLeft;
    }

bool CREARecord::IsAttack7ISUp()
    {
    return EAMT.value == eAttack7ISUp;
    }

void CREARecord::IsAttack7ISUp(bool value)
    {
    EAMT.value = value ? eAttack7ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack7ISDown()
    {
    return EAMT.value == eAttack7ISDown;
    }

void CREARecord::IsAttack7ISDown(bool value)
    {
    EAMT.value = value ? eAttack7ISDown : eAttackLeft;
    }

bool CREARecord::IsAttack8()
    {
    return EAMT.value == eAttack8;
    }

void CREARecord::IsAttack8(bool value)
    {
    EAMT.value = value ? eAttack8 : eAttackLeft;
    }

bool CREARecord::IsAttack8Up()
    {
    return EAMT.value == eAttack8Up;
    }

void CREARecord::IsAttack8Up(bool value)
    {
    EAMT.value = value ? eAttack8Up : eAttackLeft;
    }

bool CREARecord::IsAttack8Down()
    {
    return EAMT.value == eAttack8Down;
    }

void CREARecord::IsAttack8Down(bool value)
    {
    EAMT.value = value ? eAttack8Down : eAttackLeft;
    }

bool CREARecord::IsAttack8IS()
    {
    return EAMT.value == eAttack8IS;
    }

void CREARecord::IsAttack8IS(bool value)
    {
    EAMT.value = value ? eAttack8IS : eAttackLeft;
    }

bool CREARecord::IsAttack8ISUp()
    {
    return EAMT.value == eAttack8ISUp;
    }

void CREARecord::IsAttack8ISUp(bool value)
    {
    EAMT.value = value ? eAttack8ISUp : eAttackLeft;
    }

bool CREARecord::IsAttack8ISDown()
    {
    return EAMT.value == eAttack8ISDown;
    }

void CREARecord::IsAttack8ISDown(bool value)
    {
    EAMT.value = value ? eAttack8ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackLoop()
    {
    return EAMT.value == eAttackLoop;
    }

void CREARecord::IsAttackLoop(bool value)
    {
    EAMT.value = value ? eAttackLoop : eAttackLeft;
    }

bool CREARecord::IsAttackLoopUp()
    {
    return EAMT.value == eAttackLoopUp;
    }

void CREARecord::IsAttackLoopUp(bool value)
    {
    EAMT.value = value ? eAttackLoopUp : eAttackLeft;
    }

bool CREARecord::IsAttackLoopDown()
    {
    return EAMT.value == eAttackLoopDown;
    }

void CREARecord::IsAttackLoopDown(bool value)
    {
    EAMT.value = value ? eAttackLoopDown : eAttackLeft;
    }

bool CREARecord::IsAttackLoopIS()
    {
    return EAMT.value == eAttackLoopIS;
    }

void CREARecord::IsAttackLoopIS(bool value)
    {
    EAMT.value = value ? eAttackLoopIS : eAttackLeft;
    }

bool CREARecord::IsAttackLoopISUp()
    {
    return EAMT.value == eAttackLoopISUp;
    }

void CREARecord::IsAttackLoopISUp(bool value)
    {
    EAMT.value = value ? eAttackLoopISUp : eAttackLeft;
    }

bool CREARecord::IsAttackLoopISDown()
    {
    return EAMT.value == eAttackLoopISDown;
    }

void CREARecord::IsAttackLoopISDown(bool value)
    {
    EAMT.value = value ? eAttackLoopISDown : eAttackLeft;
    }

bool CREARecord::IsAttackSpin()
    {
    return EAMT.value == eAttackSpin;
    }

void CREARecord::IsAttackSpin(bool value)
    {
    EAMT.value = value ? eAttackSpin : eAttackLeft;
    }

bool CREARecord::IsAttackSpinUp()
    {
    return EAMT.value == eAttackSpinUp;
    }

void CREARecord::IsAttackSpinUp(bool value)
    {
    EAMT.value = value ? eAttackSpinUp : eAttackLeft;
    }

bool CREARecord::IsAttackSpinDown()
    {
    return EAMT.value == eAttackSpinDown;
    }

void CREARecord::IsAttackSpinDown(bool value)
    {
    EAMT.value = value ? eAttackSpinDown : eAttackLeft;
    }

bool CREARecord::IsAttackSpinIS()
    {
    return EAMT.value == eAttackSpinIS;
    }

void CREARecord::IsAttackSpinIS(bool value)
    {
    EAMT.value = value ? eAttackSpinIS : eAttackLeft;
    }

bool CREARecord::IsAttackSpinISUp()
    {
    return EAMT.value == eAttackSpinISUp;
    }

void CREARecord::IsAttackSpinISUp(bool value)
    {
    EAMT.value = value ? eAttackSpinISUp : eAttackLeft;
    }

bool CREARecord::IsAttackSpinISDown()
    {
    return EAMT.value == eAttackSpinISDown;
    }

void CREARecord::IsAttackSpinISDown(bool value)
    {
    EAMT.value = value ? eAttackSpinISDown : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2()
    {
    return EAMT.value == eAttackSpin2;
    }

void CREARecord::IsAttackSpin2(bool value)
    {
    EAMT.value = value ? eAttackSpin2 : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2Up()
    {
    return EAMT.value == eAttackSpin2Up;
    }

void CREARecord::IsAttackSpin2Up(bool value)
    {
    EAMT.value = value ? eAttackSpin2Up : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2Down()
    {
    return EAMT.value == eAttackSpin2Down;
    }

void CREARecord::IsAttackSpin2Down(bool value)
    {
    EAMT.value = value ? eAttackSpin2Down : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2IS()
    {
    return EAMT.value == eAttackSpin2IS;
    }

void CREARecord::IsAttackSpin2IS(bool value)
    {
    EAMT.value = value ? eAttackSpin2IS : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2ISUp()
    {
    return EAMT.value == eAttackSpin2ISUp;
    }

void CREARecord::IsAttackSpin2ISUp(bool value)
    {
    EAMT.value = value ? eAttackSpin2ISUp : eAttackLeft;
    }

bool CREARecord::IsAttackSpin2ISDown()
    {
    return EAMT.value == eAttackSpin2ISDown;
    }

void CREARecord::IsAttackSpin2ISDown(bool value)
    {
    EAMT.value = value ? eAttackSpin2ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackPower()
    {
    return EAMT.value == eAttackPower;
    }

void CREARecord::IsAttackPower(bool value)
    {
    EAMT.value = value ? eAttackPower : eAttackLeft;
    }

bool CREARecord::IsAttackForwardPower()
    {
    return EAMT.value == eAttackForwardPower;
    }

void CREARecord::IsAttackForwardPower(bool value)
    {
    EAMT.value = value ? eAttackForwardPower : eAttackLeft;
    }

bool CREARecord::IsAttackBackPower()
    {
    return EAMT.value == eAttackBackPower;
    }

void CREARecord::IsAttackBackPower(bool value)
    {
    EAMT.value = value ? eAttackBackPower : eAttackLeft;
    }

bool CREARecord::IsAttackLeftPower()
    {
    return EAMT.value == eAttackLeftPower;
    }

void CREARecord::IsAttackLeftPower(bool value)
    {
    EAMT.value = value ? eAttackLeftPower : eAttackLeft;
    }

bool CREARecord::IsAttackRightPower()
    {
    return EAMT.value == eAttackRightPower;
    }

void CREARecord::IsAttackRightPower(bool value)
    {
    EAMT.value = value ? eAttackRightPower : eAttackLeft;
    }

bool CREARecord::IsPlaceMine()
    {
    return EAMT.value == ePlaceMine;
    }

void CREARecord::IsPlaceMine(bool value)
    {
    EAMT.value = value ? ePlaceMine : eAttackLeft;
    }

bool CREARecord::IsPlaceMineUp()
    {
    return EAMT.value == ePlaceMineUp;
    }

void CREARecord::IsPlaceMineUp(bool value)
    {
    EAMT.value = value ? ePlaceMineUp : eAttackLeft;
    }

bool CREARecord::IsPlaceMineDown()
    {
    return EAMT.value == ePlaceMineDown;
    }

void CREARecord::IsPlaceMineDown(bool value)
    {
    EAMT.value = value ? ePlaceMineDown : eAttackLeft;
    }

bool CREARecord::IsPlaceMineIS()
    {
    return EAMT.value == ePlaceMineIS;
    }

void CREARecord::IsPlaceMineIS(bool value)
    {
    EAMT.value = value ? ePlaceMineIS : eAttackLeft;
    }

bool CREARecord::IsPlaceMineISUp()
    {
    return EAMT.value == ePlaceMineISUp;
    }

void CREARecord::IsPlaceMineISUp(bool value)
    {
    EAMT.value = value ? ePlaceMineISUp : eAttackLeft;
    }

bool CREARecord::IsPlaceMineISDown()
    {
    return EAMT.value == ePlaceMineISDown;
    }

void CREARecord::IsPlaceMineISDown(bool value)
    {
    EAMT.value = value ? ePlaceMineISDown : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2()
    {
    return EAMT.value == ePlaceMine2;
    }

void CREARecord::IsPlaceMine2(bool value)
    {
    EAMT.value = value ? ePlaceMine2 : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2Up()
    {
    return EAMT.value == ePlaceMine2Up;
    }

void CREARecord::IsPlaceMine2Up(bool value)
    {
    EAMT.value = value ? ePlaceMine2Up : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2Down()
    {
    return EAMT.value == ePlaceMine2Down;
    }

void CREARecord::IsPlaceMine2Down(bool value)
    {
    EAMT.value = value ? ePlaceMine2Down : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2IS()
    {
    return EAMT.value == ePlaceMine2IS;
    }

void CREARecord::IsPlaceMine2IS(bool value)
    {
    EAMT.value = value ? ePlaceMine2IS : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2ISUp()
    {
    return EAMT.value == ePlaceMine2ISUp;
    }

void CREARecord::IsPlaceMine2ISUp(bool value)
    {
    EAMT.value = value ? ePlaceMine2ISUp : eAttackLeft;
    }

bool CREARecord::IsPlaceMine2ISDown()
    {
    return EAMT.value == ePlaceMine2ISDown;
    }

void CREARecord::IsPlaceMine2ISDown(bool value)
    {
    EAMT.value = value ? ePlaceMine2ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrow()
    {
    return EAMT.value == eAttackThrow;
    }

void CREARecord::IsAttackThrow(bool value)
    {
    EAMT.value = value ? eAttackThrow : eAttackLeft;
    }

bool CREARecord::IsAttackThrowUp()
    {
    return EAMT.value == eAttackThrowUp;
    }

void CREARecord::IsAttackThrowUp(bool value)
    {
    EAMT.value = value ? eAttackThrowUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrowDown()
    {
    return EAMT.value == eAttackThrowDown;
    }

void CREARecord::IsAttackThrowDown(bool value)
    {
    EAMT.value = value ? eAttackThrowDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrowIS()
    {
    return EAMT.value == eAttackThrowIS;
    }

void CREARecord::IsAttackThrowIS(bool value)
    {
    EAMT.value = value ? eAttackThrowIS : eAttackLeft;
    }

bool CREARecord::IsAttackThrowISUp()
    {
    return EAMT.value == eAttackThrowISUp;
    }

void CREARecord::IsAttackThrowISUp(bool value)
    {
    EAMT.value = value ? eAttackThrowISUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrowISDown()
    {
    return EAMT.value == eAttackThrowISDown;
    }

void CREARecord::IsAttackThrowISDown(bool value)
    {
    EAMT.value = value ? eAttackThrowISDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2()
    {
    return EAMT.value == eAttackThrow2;
    }

void CREARecord::IsAttackThrow2(bool value)
    {
    EAMT.value = value ? eAttackThrow2 : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2Up()
    {
    return EAMT.value == eAttackThrow2Up;
    }

void CREARecord::IsAttackThrow2Up(bool value)
    {
    EAMT.value = value ? eAttackThrow2Up : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2Down()
    {
    return EAMT.value == eAttackThrow2Down;
    }

void CREARecord::IsAttackThrow2Down(bool value)
    {
    EAMT.value = value ? eAttackThrow2Down : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2IS()
    {
    return EAMT.value == eAttackThrow2IS;
    }

void CREARecord::IsAttackThrow2IS(bool value)
    {
    EAMT.value = value ? eAttackThrow2IS : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2ISUp()
    {
    return EAMT.value == eAttackThrow2ISUp;
    }

void CREARecord::IsAttackThrow2ISUp(bool value)
    {
    EAMT.value = value ? eAttackThrow2ISUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrow2ISDown()
    {
    return EAMT.value == eAttackThrow2ISDown;
    }

void CREARecord::IsAttackThrow2ISDown(bool value)
    {
    EAMT.value = value ? eAttackThrow2ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3()
    {
    return EAMT.value == eAttackThrow3;
    }

void CREARecord::IsAttackThrow3(bool value)
    {
    EAMT.value = value ? eAttackThrow3 : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3Up()
    {
    return EAMT.value == eAttackThrow3Up;
    }

void CREARecord::IsAttackThrow3Up(bool value)
    {
    EAMT.value = value ? eAttackThrow3Up : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3Down()
    {
    return EAMT.value == eAttackThrow3Down;
    }

void CREARecord::IsAttackThrow3Down(bool value)
    {
    EAMT.value = value ? eAttackThrow3Down : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3IS()
    {
    return EAMT.value == eAttackThrow3IS;
    }

void CREARecord::IsAttackThrow3IS(bool value)
    {
    EAMT.value = value ? eAttackThrow3IS : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3ISUp()
    {
    return EAMT.value == eAttackThrow3ISUp;
    }

void CREARecord::IsAttackThrow3ISUp(bool value)
    {
    EAMT.value = value ? eAttackThrow3ISUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrow3ISDown()
    {
    return EAMT.value == eAttackThrow3ISDown;
    }

void CREARecord::IsAttackThrow3ISDown(bool value)
    {
    EAMT.value = value ? eAttackThrow3ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4()
    {
    return EAMT.value == eAttackThrow4;
    }

void CREARecord::IsAttackThrow4(bool value)
    {
    EAMT.value = value ? eAttackThrow4 : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4Up()
    {
    return EAMT.value == eAttackThrow4Up;
    }

void CREARecord::IsAttackThrow4Up(bool value)
    {
    EAMT.value = value ? eAttackThrow4Up : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4Down()
    {
    return EAMT.value == eAttackThrow4Down;
    }

void CREARecord::IsAttackThrow4Down(bool value)
    {
    EAMT.value = value ? eAttackThrow4Down : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4IS()
    {
    return EAMT.value == eAttackThrow4IS;
    }

void CREARecord::IsAttackThrow4IS(bool value)
    {
    EAMT.value = value ? eAttackThrow4IS : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4ISUp()
    {
    return EAMT.value == eAttackThrow4ISUp;
    }

void CREARecord::IsAttackThrow4ISUp(bool value)
    {
    EAMT.value = value ? eAttackThrow4ISUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrow4ISDown()
    {
    return EAMT.value == eAttackThrow4ISDown;
    }

void CREARecord::IsAttackThrow4ISDown(bool value)
    {
    EAMT.value = value ? eAttackThrow4ISDown : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5()
    {
    return EAMT.value == eAttackThrow5;
    }

void CREARecord::IsAttackThrow5(bool value)
    {
    EAMT.value = value ? eAttackThrow5 : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5Up()
    {
    return EAMT.value == eAttackThrow5Up;
    }

void CREARecord::IsAttackThrow5Up(bool value)
    {
    EAMT.value = value ? eAttackThrow5Up : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5Down()
    {
    return EAMT.value == eAttackThrow5Down;
    }

void CREARecord::IsAttackThrow5Down(bool value)
    {
    EAMT.value = value ? eAttackThrow5Down : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5IS()
    {
    return EAMT.value == eAttackThrow5IS;
    }

void CREARecord::IsAttackThrow5IS(bool value)
    {
    EAMT.value = value ? eAttackThrow5IS : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5ISUp()
    {
    return EAMT.value == eAttackThrow5ISUp;
    }

void CREARecord::IsAttackThrow5ISUp(bool value)
    {
    EAMT.value = value ? eAttackThrow5ISUp : eAttackLeft;
    }

bool CREARecord::IsAttackThrow5ISDown()
    {
    return EAMT.value == eAttackThrow5ISDown;
    }

void CREARecord::IsAttackThrow5ISDown(bool value)
    {
    EAMT.value = value ? eAttackThrow5ISDown : eAttackLeft;
    }

bool CREARecord::IsPipBoy()
    {
    return EAMT.value == ePipBoy;
    }

void CREARecord::IsPipBoy(bool value)
    {
    EAMT.value = value ? ePipBoy : eAttackLeft;
    }

bool CREARecord::IsPipBoyChild()
    {
    return EAMT.value == ePipBoyChild;
    }

void CREARecord::IsPipBoyChild(bool value)
    {
    EAMT.value = value ? ePipBoyChild : eAttackLeft;
    }

bool CREARecord::IsANY()
    {
    return EAMT.value == eANY;
    }

void CREARecord::IsANY(bool value)
    {
    EAMT.value = value ? eANY : eAttackLeft;
    }

bool CREARecord::IsAttackAnimType(uint16_t Type)
    {
    return EAMT.value == Type;
    }

void CREARecord::SetAttackAnimType(uint16_t Type)
    {
    EAMT.value = Type;
    }

bool CREARecord::IsLoud()
    {
    return NAM5.value == eLoud;
    }

void CREARecord::IsLoud(bool value)
    {
    NAM5.value = value ? eLoud : eNormal;
    }

bool CREARecord::IsNormal()
    {
    return NAM5.value == eNormal;
    }

void CREARecord::IsNormal(bool value)
    {
    NAM5.value = value ? eNormal : eLoud;
    }

bool CREARecord::IsSilent()
    {
    return NAM5.value == eSilent;
    }

void CREARecord::IsSilent(bool value)
    {
    NAM5.value = value ? eSilent : eLoud;
    }

bool CREARecord::IsSoundLevelType(uint32_t Type)
    {
    return NAM5.value == Type;
    }

void CREARecord::SetSoundLevelType(uint32_t Type)
    {
    NAM5.value = Type;
    }

bool CREARecord::IsUnaggressive()
    {
    return AIDT.value.aggression == eUnaggressive;
    }

void CREARecord::IsUnaggressive(bool value)
    {
    AIDT.value.aggression = value ? eUnaggressive : eAggressive;
    }

bool CREARecord::IsAggressive()
    {
    return AIDT.value.aggression == eAggressive;
    }

void CREARecord::IsAggressive(bool value)
    {
    AIDT.value.aggression = value ? eAggressive : eUnaggressive;
    }

bool CREARecord::IsVeryAggressive()
    {
    return AIDT.value.aggression == eVeryAggressive;
    }

void CREARecord::IsVeryAggressive(bool value)
    {
    AIDT.value.aggression = value ? eVeryAggressive : eUnaggressive;
    }

bool CREARecord::IsFrenzied()
    {
    return AIDT.value.aggression == eFrenzied;
    }

void CREARecord::IsFrenzied(bool value)
    {
    AIDT.value.aggression = value ? eFrenzied : eUnaggressive;
    }

bool CREARecord::IsAggressionType(uint8_t Type)
    {
    return AIDT.value.aggression == Type;
    }

void CREARecord::SetAggressionType(uint8_t Type)
    {
    AIDT.value.aggression = Type;
    }

bool CREARecord::IsCowardly()
    {
    return AIDT.value.confidence == eCowardly;
    }

void CREARecord::IsCowardly(bool value)
    {
    AIDT.value.confidence = value ? eCowardly : eCautious;
    }

bool CREARecord::IsCautious()
    {
    return AIDT.value.confidence == eCautious;
    }

void CREARecord::IsCautious(bool value)
    {
    AIDT.value.confidence = value ? eCautious : eCowardly;
    }

bool CREARecord::IsAverage()
    {
    return AIDT.value.confidence == eAverage;
    }

void CREARecord::IsAverage(bool value)
    {
    AIDT.value.confidence = value ? eAverage : eCowardly;
    }

bool CREARecord::IsBrave()
    {
    return AIDT.value.confidence == eBrave;
    }

void CREARecord::IsBrave(bool value)
    {
    AIDT.value.confidence = value ? eBrave : eCowardly;
    }

bool CREARecord::IsFoolhardy()
    {
    return AIDT.value.confidence == eFoolhardy;
    }

void CREARecord::IsFoolhardy(bool value)
    {
    AIDT.value.confidence = value ? eFoolhardy : eCowardly;
    }

bool CREARecord::IsConfidenceType(uint8_t Type)
    {
    return AIDT.value.confidence == Type;
    }

void CREARecord::SetConfidenceType(uint8_t Type)
    {
    AIDT.value.confidence = Type;
    }

bool CREARecord::IsNeutral()
    {
    return AIDT.value.mood == eNeutral;
    }

void CREARecord::IsNeutral(bool value)
    {
    AIDT.value.mood = value ? eNeutral : eAfraid;
    }

bool CREARecord::IsAfraid()
    {
    return AIDT.value.mood == eAfraid;
    }

void CREARecord::IsAfraid(bool value)
    {
    AIDT.value.mood = value ? eAfraid : eNeutral;
    }

bool CREARecord::IsAnnoyed()
    {
    return AIDT.value.mood == eAnnoyed;
    }

void CREARecord::IsAnnoyed(bool value)
    {
    AIDT.value.mood = value ? eAnnoyed : eNeutral;
    }

bool CREARecord::IsCocky()
    {
    return AIDT.value.mood == eCocky;
    }

void CREARecord::IsCocky(bool value)
    {
    AIDT.value.mood = value ? eCocky : eNeutral;
    }

bool CREARecord::IsDrugged()
    {
    return AIDT.value.mood == eDrugged;
    }

void CREARecord::IsDrugged(bool value)
    {
    AIDT.value.mood = value ? eDrugged : eNeutral;
    }

bool CREARecord::IsPleasant()
    {
    return AIDT.value.mood == ePleasant;
    }

void CREARecord::IsPleasant(bool value)
    {
    AIDT.value.mood = value ? ePleasant : eNeutral;
    }

bool CREARecord::IsAngry()
    {
    return AIDT.value.mood == eAngry;
    }

void CREARecord::IsAngry(bool value)
    {
    AIDT.value.mood = value ? eAngry : eNeutral;
    }

bool CREARecord::IsSad()
    {
    return AIDT.value.mood == eSad;
    }

void CREARecord::IsSad(bool value)
    {
    AIDT.value.mood = value ? eSad : eNeutral;
    }

bool CREARecord::IsMoodType(uint8_t Type)
    {
    return AIDT.value.mood == Type;
    }

void CREARecord::SetMoodType(uint8_t Type)
    {
    AIDT.value.mood = Type;
    }

bool CREARecord::IsHelpsNobody()
    {
    return AIDT.value.assistance == eHelpsNobody;
    }

void CREARecord::IsHelpsNobody(bool value)
    {
    AIDT.value.assistance = value ? eHelpsNobody : eHelpsAllies;
    }

bool CREARecord::IsHelpsAllies()
    {
    return AIDT.value.assistance == eHelpsAllies;
    }

void CREARecord::IsHelpsAllies(bool value)
    {
    AIDT.value.assistance = value ? eHelpsAllies : eHelpsNobody;
    }

bool CREARecord::IsHelpsFriendsAndAllies()
    {
    return AIDT.value.assistance == eHelpsFriendsAndAllies;
    }

void CREARecord::IsHelpsFriendsAndAllies(bool value)
    {
    AIDT.value.assistance = value ? eHelpsFriendsAndAllies : eHelpsNobody;
    }

bool CREARecord::IsAssistanceType(uint8_t Type)
    {
    return AIDT.value.assistance == Type;
    }

void CREARecord::SetAssistanceType(uint8_t Type)
    {
    AIDT.value.assistance = Type;
    }

bool CREARecord::IsStone()
    {
    return NAM4.value == eStone;
    }

void CREARecord::IsStone(bool value)
    {
    NAM4.value = value ? eStone : eDirt;
    }

bool CREARecord::IsDirt()
    {
    return NAM4.value == eDirt;
    }

void CREARecord::IsDirt(bool value)
    {
    NAM4.value = value ? eDirt : eStone;
    }

bool CREARecord::IsGrass()
    {
    return NAM4.value == eGrass;
    }

void CREARecord::IsGrass(bool value)
    {
    NAM4.value = value ? eGrass : eStone;
    }

bool CREARecord::IsGlass()
    {
    return NAM4.value == eGlass;
    }

void CREARecord::IsGlass(bool value)
    {
    NAM4.value = value ? eGlass : eStone;
    }

bool CREARecord::IsMetal()
    {
    return NAM4.value == eMetal;
    }

void CREARecord::IsMetal(bool value)
    {
    NAM4.value = value ? eMetal : eStone;
    }

bool CREARecord::IsWood()
    {
    return NAM4.value == eWood;
    }

void CREARecord::IsWood(bool value)
    {
    NAM4.value = value ? eWood : eStone;
    }

bool CREARecord::IsOrganic()
    {
    return NAM4.value == eOrganic;
    }

void CREARecord::IsOrganic(bool value)
    {
    NAM4.value = value ? eOrganic : eStone;
    }

bool CREARecord::IsCloth()
    {
    return NAM4.value == eCloth;
    }

void CREARecord::IsCloth(bool value)
    {
    NAM4.value = value ? eCloth : eStone;
    }

bool CREARecord::IsWater()
    {
    return NAM4.value == eWater;
    }

void CREARecord::IsWater(bool value)
    {
    NAM4.value = value ? eWater : eStone;
    }

bool CREARecord::IsHollowMetal()
    {
    return NAM4.value == eHollowMetal;
    }

void CREARecord::IsHollowMetal(bool value)
    {
    NAM4.value = value ? eHollowMetal : eStone;
    }

bool CREARecord::IsOrganicBug()
    {
    return NAM4.value == eOrganicBug;
    }

void CREARecord::IsOrganicBug(bool value)
    {
    NAM4.value = value ? eOrganicBug : eStone;
    }

bool CREARecord::IsOrganicGlow()
    {
    return NAM4.value == eOrganicGlow;
    }

void CREARecord::IsOrganicGlow(bool value)
    {
    NAM4.value = value ? eOrganicGlow : eStone;
    }

bool CREARecord::IsImpactType(uint32_t Type)
    {
    return NAM4.value == Type;
    }

void CREARecord::SetImpactType(uint32_t Type)
    {
    NAM4.value = Type;
    }

uint32_t CREARecord::GetType()
    {
    return REV32(CREA);
    }

char * CREARecord::GetStrType()
    {
    return "CREA";
    }

int32_t CREARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(SPLO):
                SPLO.Read(buffer, subSize);
                break;
            case REV32(EITM):
                EITM.Read(buffer, subSize);
                break;
            case REV32(EAMT):
                EAMT.Read(buffer, subSize);
                break;
            case REV32(NIFZ):
                NIFZ.Read(buffer, subSize);
                break;
            case REV32(NIFT):
                NIFT.Read(buffer, subSize, CompressedOnDisk);
                //Hack
                {
                bool unload_nift = true;
                for(uint32_t x = 0; x < NIFT.GetSize(); ++x)
                    if(NIFT.value[x] != 0)
                        {
                        unload_nift = false;
                        break;
                        }
                if(unload_nift)
                    NIFT.Unload();
                }
                break;
            case REV32(ACBS):
                ACBS.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(VTCK):
                VTCK.Read(buffer, subSize);
                break;
            case REV32(TPLT):
                TPLT.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(CNTO):
                CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->CNTO.Read(buffer, subSize);
                break;
            case REV32(COED):
                if(CNTO.value.size() == 0)
                    CNTO.value.push_back(new FNVCNTO);
                CNTO.value.back()->COED.Read(buffer, subSize);
                break;
            case REV32(AIDT):
                AIDT.Read(buffer, subSize);
                break;
            case REV32(PKID):
                PKID.Read(buffer, subSize);
                break;
            case REV32(KFFZ):
                KFFZ.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize);
                break;
            case REV32(CSCR):
                CSCR.Read(buffer, subSize);
                break;
            case REV32(CSDT):
                Types.value.push_back(new CREASoundType);
                Types.value.back()->CSDT.Read(buffer, subSize);
                break;
            case REV32(CSDI):
                if(Types.value.size() == 0)
                    Types.value.push_back(new CREASoundType);
                Types.value.back()->Sounds.value.push_back(new CREASound);
                Types.value.back()->Sounds.value.back()->CSDI.Read(buffer, subSize);
                break;
            case REV32(CSDC):
                if(Types.value.size() == 0)
                    Types.value.push_back(new CREASoundType);
                if(Types.value.back()->Sounds.value.size() == 0)
                    Types.value.back()->Sounds.value.push_back(new CREASound);
                Types.value.back()->Sounds.value.back()->CSDC.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CREA: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CREARecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SPLO.Unload();
    EITM.Unload();
    EAMT.Unload();
    NIFZ.Unload();
    NIFT.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    VTCK.Unload();
    TPLT.Unload();
    Destructable.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    KFFZ.Unload();
    DATA.Unload();
    RNAM.Unload();
    ZNAM.Unload();
    PNAM.Unload();
    TNAM.Unload();
    BNAM.Unload();
    WNAM.Unload();
    NAM4.Unload();
    NAM5.Unload();
    CSCR.Unload();
    Types.Unload();
    CNAM.Unload();
    LNAM.Unload();
    return 1;
    }

int32_t CREARecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SPLO);
    WRITE(EITM);
    WRITE(EAMT);
    WRITE(NIFZ);
    WRITE(NIFT);
    WRITE(ACBS);
    WRITE(SNAM);
    WRITE(INAM);
    WRITE(VTCK);
    WRITE(TPLT);
    Destructable.Write(writer);
    WRITE(SCRI);
    CNTO.Write(writer);
    WRITE(AIDT);
    PKID.Write(REV32(PKID), writer, true);
    WRITE(KFFZ);
    WRITE(DATA);
    WRITE(RNAM);
    WRITE(ZNAM);
    WRITE(PNAM);
    WRITE(TNAM);
    WRITE(BNAM);
    WRITE(WNAM);
    WRITE(NAM4);
    WRITE(NAM5);
    WRITE(CSCR);
    Types.Write(writer);
    WRITE(CNAM);
    WRITE(LNAM);
    return -1;
    }

bool CREARecord::operator ==(const CREARecord &other) const
    {
    return (OBND == other.OBND &&
            EITM == other.EITM &&
            EAMT == other.EAMT &&
            NIFT == other.NIFT &&
            ACBS == other.ACBS &&
            SNAM == other.SNAM &&
            INAM == other.INAM &&
            VTCK == other.VTCK &&
            TPLT == other.TPLT &&
            SCRI == other.SCRI &&
            CNTO == other.CNTO &&
            AIDT == other.AIDT &&
            DATA == other.DATA &&
            RNAM == other.RNAM &&
            ZNAM == other.ZNAM &&
            PNAM == other.PNAM &&
            TNAM == other.TNAM &&
            BNAM == other.BNAM &&
            WNAM == other.WNAM &&
            NAM4 == other.NAM4 &&
            NAM5 == other.NAM5 &&
            CSCR == other.CSCR &&
            CNAM == other.CNAM &&
            LNAM == other.LNAM &&
            SPLO == other.SPLO &&
            PKID == other.PKID &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NIFZ.equalsi(other.NIFZ) &&
            KFFZ.equalsi(other.KFFZ) &&
            Destructable == other.Destructable &&
            Types == other.Types &&
            MODL == other.MODL);
    }

bool CREARecord::operator !=(const CREARecord &other) const
    {
    return !(*this == other);
    }

bool CREARecord::equals(Record *other)
    {
    return *this == *(CREARecord *)other;
    }
}