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
#include "CSTYRecord.h"

namespace FNV
{
CSTYRecord::CSTYCSTD::CSTYCSTD():
    dodgeChance(0),
    lrChance(0),
    lrTimerMin(0.0f),
    lrTimerMax(0.0f),
    forTimerMin(0.0f),
    forTimerMax(0.0f),
    backTimerMin(0.0f),
    backTimerMax(0.0f),
    idleTimerMin(0.0f),
    idleTimerMax(0.0f),
    blkChance(0),
    atkChance(0),
    atkBRecoil(0.0f),
    atkBUnc(0.0f),
    atkBh2h(0.0f),
    pAtkChance(0),
    pAtkBRecoil(0.0f),
    pAtkBUnc(0.0f),
    pAtkNormal(0),
    pAtkFor(0),
    pAtkBack(0),
    pAtkL(0),
    pAtkR(0),
    holdTimerMin(0.0f),
    holdTimerMax(0.0f),
    flags(0),
    acroDodge(0),
    rushChance(0),
    rushMult(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    memset(&unused3[0], 0x00, sizeof(unused3));
    memset(&unused4[0], 0x00, sizeof(unused4));
    memset(&unused5[0], 0x00, sizeof(unused5));
    memset(&unused6[0], 0x00, sizeof(unused6));
    }

CSTYRecord::CSTYCSTD::~CSTYCSTD()
    {
    //
    }

bool CSTYRecord::CSTYCSTD::operator ==(const CSTYCSTD &other) const
    {
    return (dodgeChance == other.dodgeChance &&
            lrChance == other.lrChance &&
            blkChance == other.blkChance &&
            atkChance == other.atkChance &&
            pAtkChance == other.pAtkChance &&
            pAtkNormal == other.pAtkNormal &&
            pAtkFor == other.pAtkFor &&
            pAtkBack == other.pAtkBack &&
            pAtkL == other.pAtkL &&
            pAtkR == other.pAtkR &&
            flags == other.flags &&
            acroDodge == other.acroDodge &&
            rushChance == other.rushChance &&
            AlmostEqual(lrTimerMin,other.lrTimerMin,2) &&
            AlmostEqual(lrTimerMax,other.lrTimerMax,2) &&
            AlmostEqual(forTimerMin,other.forTimerMin,2) &&
            AlmostEqual(forTimerMax,other.forTimerMax,2) &&
            AlmostEqual(backTimerMin,other.backTimerMin,2) &&
            AlmostEqual(backTimerMax,other.backTimerMax,2) &&
            AlmostEqual(idleTimerMin,other.idleTimerMin,2) &&
            AlmostEqual(idleTimerMax,other.idleTimerMax,2) &&
            AlmostEqual(atkBRecoil,other.atkBRecoil,2) &&
            AlmostEqual(atkBUnc,other.atkBUnc,2) &&
            AlmostEqual(atkBh2h,other.atkBh2h,2) &&
            AlmostEqual(pAtkBRecoil,other.pAtkBRecoil,2) &&
            AlmostEqual(pAtkBUnc,other.pAtkBUnc,2) &&
            AlmostEqual(holdTimerMin,other.holdTimerMin,2) &&
            AlmostEqual(holdTimerMax,other.holdTimerMax,2) &&
            AlmostEqual(rushMult,other.rushMult,2));
    }

bool CSTYRecord::CSTYCSTD::operator !=(const CSTYCSTD &other) const
    {
    return !(*this == other);
    }

CSTYRecord::CSTYCSAD::CSTYCSAD():
    dodgeFMult(0.0f),
    dodgeFBase(0.0f),
    encSBase(0.0f),
    encSMult(0.0f),
    dodgeAtkMult(0.0f),
    dodgeNAtkMult(0.0f),
    dodgeBAtkMult(0.0f),
    dodgeBNAtkMult(0.0f),
    dodgeFAtkMult(0.0f),
    dodgeFNAtkMult(0.0f),
    blockMult(0.0f),
    blockBase(0.0f),
    blockAtkMult(0.0f),
    blockNAtkMult(0.0f),
    atkMult(0.0f),
    atkBase(0.0f),
    atkAtkMult(0.0f),
    atkNAtkMult(0.0f),
    atkBlockMult(0.0f),
    pAtkFBase(0.0f),
    pAtkFMult(0.0f)
    {
    //
    }

CSTYRecord::CSTYCSAD::~CSTYCSAD()
    {
    //
    }

bool CSTYRecord::CSTYCSAD::operator ==(const CSTYCSAD &other) const
    {
    return (AlmostEqual(dodgeFMult,other.dodgeFMult,2) &&
            AlmostEqual(dodgeFBase,other.dodgeFBase,2) &&
            AlmostEqual(encSBase,other.encSBase,2) &&
            AlmostEqual(encSMult,other.encSMult,2) &&
            AlmostEqual(dodgeAtkMult,other.dodgeAtkMult,2) &&
            AlmostEqual(dodgeNAtkMult,other.dodgeNAtkMult,2) &&
            AlmostEqual(dodgeBAtkMult,other.dodgeBAtkMult,2) &&
            AlmostEqual(dodgeBNAtkMult,other.dodgeBNAtkMult,2) &&
            AlmostEqual(dodgeFAtkMult,other.dodgeFAtkMult,2) &&
            AlmostEqual(dodgeFNAtkMult,other.dodgeFNAtkMult,2) &&
            AlmostEqual(blockMult,other.blockMult,2) &&
            AlmostEqual(blockBase,other.blockBase,2) &&
            AlmostEqual(blockAtkMult,other.blockAtkMult,2) &&
            AlmostEqual(blockNAtkMult,other.blockNAtkMult,2) &&
            AlmostEqual(atkMult,other.atkMult,2) &&
            AlmostEqual(atkBase,other.atkBase,2) &&
            AlmostEqual(atkAtkMult,other.atkAtkMult,2) &&
            AlmostEqual(atkNAtkMult,other.atkNAtkMult,2) &&
            AlmostEqual(atkBlockMult,other.atkBlockMult,2) &&
            AlmostEqual(pAtkFBase,other.pAtkFBase,2) &&
            AlmostEqual(pAtkFMult,other.pAtkFMult,2));
    }

bool CSTYRecord::CSTYCSAD::operator !=(const CSTYCSAD &other) const
    {
    return !(*this == other);
    }

CSTYRecord::CSTYCSSD::CSTYCSSD():
    coverRadius(0.0f),
    coverChance(0.0f),
    waitTimerMin(0.0f),
    waitTimerMax(0.0f),
    waitFireTimerMin(0.0f),
    waitFireTimerMax(0.0f),
    fireTimerMin(0.0f),
    fireTimerMax(0.0f),
    rangedRangeMultMin(0.0f),
    weaponRestrictions(0),
    rangedRangeMultMax(0.0f),
    targetMaxFOV(0.0f),
    combatRadius(0.0f),
    semiAutoFireDelayMultMin(0.0f),
    semiAutoFireDelayMultMax(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

CSTYRecord::CSTYCSSD::~CSTYCSSD()
    {
    //
    }

bool CSTYRecord::CSTYCSSD::operator ==(const CSTYCSSD &other) const
    {
    return (weaponRestrictions == other.weaponRestrictions &&
            AlmostEqual(coverRadius,other.coverRadius,2) &&
            AlmostEqual(coverChance,other.coverChance,2) &&
            AlmostEqual(waitTimerMin,other.waitTimerMin,2) &&
            AlmostEqual(waitTimerMax,other.waitTimerMax,2) &&
            AlmostEqual(waitFireTimerMin,other.waitFireTimerMin,2) &&
            AlmostEqual(waitFireTimerMax,other.waitFireTimerMax,2) &&
            AlmostEqual(fireTimerMin,other.fireTimerMin,2) &&
            AlmostEqual(fireTimerMax,other.fireTimerMax,2) &&
            AlmostEqual(rangedRangeMultMin,other.rangedRangeMultMin,2) &&
            AlmostEqual(rangedRangeMultMax,other.rangedRangeMultMax,2) &&
            AlmostEqual(targetMaxFOV,other.targetMaxFOV,2) &&
            AlmostEqual(combatRadius,other.combatRadius,2) &&
            AlmostEqual(semiAutoFireDelayMultMin,other.semiAutoFireDelayMultMin,2) &&
            AlmostEqual(semiAutoFireDelayMultMax,other.semiAutoFireDelayMultMax,2));
    }

bool CSTYRecord::CSTYCSSD::operator !=(const CSTYCSSD &other) const
    {
    return !(*this == other);
    }

CSTYRecord::CSTYRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CSTYRecord::CSTYRecord(CSTYRecord *srcRecord):
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
    CSTD = srcRecord->CSTD;
    CSAD = srcRecord->CSAD;
    CSSD = srcRecord->CSSD;
    return;
    }

CSTYRecord::~CSTYRecord()
    {
    //
    }

bool CSTYRecord::IsUseChanceForAttack()
    {
    return (CSTD.value.flags & fIsUseChanceForAttack) != 0;
    }

void CSTYRecord::IsUseChanceForAttack(bool value)
    {
    SETBIT(CSTD.value.flags, fIsUseChanceForAttack, value);
    }

bool CSTYRecord::IsMeleeAlertOK()
    {
    return (CSTD.value.flags & fIsMeleeAlertOK) != 0;
    }

void CSTYRecord::IsMeleeAlertOK(bool value)
    {
    SETBIT(CSTD.value.flags, fIsMeleeAlertOK, value);
    }

bool CSTYRecord::IsFleeForSurvival()
    {
    return (CSTD.value.flags & fIsFleeForSurvival) != 0;
    }

void CSTYRecord::IsFleeForSurvival(bool value)
    {
    SETBIT(CSTD.value.flags, fIsFleeForSurvival, value);
    }

bool CSTYRecord::IsIgnoreThreats()
    {
    return (CSTD.value.flags & fIsIgnoreThreats) != 0;
    }

void CSTYRecord::IsIgnoreThreats(bool value)
    {
    SETBIT(CSTD.value.flags, fIsIgnoreThreats, value);
    }

bool CSTYRecord::IsIgnoreDamagingSelf()
    {
    return (CSTD.value.flags & fIsIgnoreDamagingSelf) != 0;
    }

void CSTYRecord::IsIgnoreDamagingSelf(bool value)
    {
    SETBIT(CSTD.value.flags, fIsIgnoreDamagingSelf, value);
    }

bool CSTYRecord::IsIgnoreDamagingGroup()
    {
    return (CSTD.value.flags & fIsIgnoreDamagingGroup) != 0;
    }

void CSTYRecord::IsIgnoreDamagingGroup(bool value)
    {
    SETBIT(CSTD.value.flags, fIsIgnoreDamagingGroup, value);
    }

bool CSTYRecord::IsIgnoreDamagingSpectator()
    {
    return (CSTD.value.flags & fIsIgnoreDamagingSpectator) != 0;
    }

void CSTYRecord::IsIgnoreDamagingSpectator(bool value)
    {
    SETBIT(CSTD.value.flags, fIsIgnoreDamagingSpectator, value);
    }

bool CSTYRecord::IsNoUseStealthboy()
    {
    return (CSTD.value.flags & fIsNoUseStealthboy) != 0;
    }

void CSTYRecord::IsNoUseStealthboy(bool value)
    {
    SETBIT(CSTD.value.flags, fIsNoUseStealthboy, value);
    }

bool CSTYRecord::IsFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((CSTD.value.flags & Mask) == Mask) : ((CSTD.value.flags & Mask) != 0);
    }

void CSTYRecord::SetFlagMask(uint16_t Mask)
    {
    CSTD.value.flags = Mask;
    }

bool CSTYRecord::IsNone()
    {
    return CSSD.value.weaponRestrictions == eNone;
    }

void CSTYRecord::IsNone(bool value)
    {
    CSSD.value.weaponRestrictions = value ? eNone : eMeleeOnly;
    }

bool CSTYRecord::IsMeleeOnly()
    {
    return CSSD.value.weaponRestrictions == eMeleeOnly;
    }

void CSTYRecord::IsMeleeOnly(bool value)
    {
    CSSD.value.weaponRestrictions = value ? eMeleeOnly : eNone;
    }

bool CSTYRecord::IsRangedOnly()
    {
    return CSSD.value.weaponRestrictions == eRangedOnly;
    }

void CSTYRecord::IsRangedOnly(bool value)
    {
    CSSD.value.weaponRestrictions = value ? eRangedOnly : eNone;
    }

bool CSTYRecord::IsType(uint32_t Type)
    {
    return CSSD.value.weaponRestrictions == Type;
    }

void CSTYRecord::SetType(uint32_t Type)
    {
    CSSD.value.weaponRestrictions = Type;
    }

uint32_t CSTYRecord::GetType()
    {
    return REV32(CSTY);
    }

char * CSTYRecord::GetStrType()
    {
    return "CSTY";
    }

int32_t CSTYRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(CSTD):
                CSTD.Read(buffer, subSize);
                break;
            case REV32(CSAD):
                CSAD.Read(buffer, subSize);
                break;
            case REV32(CSSD):
                CSSD.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CSTY: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CSTYRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    CSTD.Unload();
    CSAD.Unload();
    CSSD.Unload();
    return 1;
    }

int32_t CSTYRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(CSTD);
    WRITE(CSAD);
    WRITE(CSSD);
    return -1;
    }

bool CSTYRecord::operator ==(const CSTYRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CSTD == other.CSTD &&
            CSAD == other.CSAD &&
            CSSD == other.CSSD);
    }

bool CSTYRecord::operator !=(const CSTYRecord &other) const
    {
    return !(*this == other);
    }

bool CSTYRecord::equals(Record *other)
    {
    return *this == *(CSTYRecord *)other;
    }
}