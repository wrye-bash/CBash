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

namespace Ob
{
CSTYRecord::CSTYCSTD::CSTYCSTD():
    dodgeChance(75),
    lrChance(50),
    lrTimerMin(0.5f),
    lrTimerMax(1.5f),
    forTimerMin(0.5f),
    forTimerMax(1.0f),
    backTimerMin(0.25f),
    backTimerMax(0.75f),
    idleTimerMin(0.5f),
    idleTimerMax(1.5f),
    blkChance(30),
    atkChance(40),
    atkBRecoil(5.0f),
    atkBUnc(5.0f),
    atkBh2h(5.0f),
    pAtkChance(25),
    pAtkBRecoil(5.0f),
    pAtkBUnc(5.0f),
    pAtkNormal(20),
    pAtkFor(20),
    pAtkBack(20),
    pAtkL(20),
    pAtkR(20),
    holdTimerMin(0.5f),
    holdTimerMax(1.5f),
    flagsA(0),
    acroDodge(0),
    rMultOpt(1.0f),
    rMultMax(1.0f),
    mDistance(250.0f),
    rDistance(1000.0f),
    buffStand(325.0f),
    rStand(500.0f),
    groupStand(325.0f),
    rushChance(25),
    rushMult(1.0f),
    flagsB(0)
    {
     memset(&unused1[0], 0xCD, sizeof(unused1));
     memset(&unused2[0], 0xCD, sizeof(unused2));
     memset(&unused3[0], 0xCD, sizeof(unused3));
     memset(&unused4[0], 0xCD, sizeof(unused4));
     memset(&unused5[0], 0xCD, sizeof(unused5));
     memset(&unused6[0], 0xCD, sizeof(unused6));
    }

CSTYRecord::CSTYCSTD::~CSTYCSTD()
    {
    //
    }

bool CSTYRecord::CSTYCSTD::operator ==(const CSTYCSTD &other) const
    {
    return (dodgeChance == other.dodgeChance &&
            lrChance == other.lrChance &&
            AlmostEqual(lrTimerMin,other.lrTimerMin,2) &&
            AlmostEqual(lrTimerMax,other.lrTimerMax,2) &&
            AlmostEqual(forTimerMin,other.forTimerMin,2) &&
            AlmostEqual(forTimerMax,other.forTimerMax,2) &&
            AlmostEqual(backTimerMin,other.backTimerMin,2) &&
            AlmostEqual(backTimerMax,other.backTimerMax,2) &&
            AlmostEqual(idleTimerMin,other.idleTimerMin,2) &&
            AlmostEqual(idleTimerMax,other.idleTimerMax,2) &&
            blkChance == other.blkChance &&
            atkChance == other.atkChance &&
            AlmostEqual(atkBRecoil,other.atkBRecoil,2) &&
            AlmostEqual(atkBUnc,other.atkBUnc,2) &&
            AlmostEqual(atkBh2h,other.atkBh2h,2) &&
            pAtkChance == other.pAtkChance &&
            AlmostEqual(pAtkBRecoil,other.pAtkBRecoil,2) &&
            AlmostEqual(pAtkBUnc,other.pAtkBUnc,2) &&
            pAtkNormal == other.pAtkNormal &&
            pAtkFor == other.pAtkFor &&
            pAtkBack == other.pAtkBack &&
            pAtkL == other.pAtkL &&
            pAtkR == other.pAtkR &&
            AlmostEqual(holdTimerMin,other.holdTimerMin,2) &&
            AlmostEqual(holdTimerMax,other.holdTimerMax,2) &&
            flagsA == other.flagsA &&
            acroDodge == other.acroDodge &&
            AlmostEqual(rMultOpt,other.rMultOpt,2) &&
            AlmostEqual(rMultMax,other.rMultMax,2) &&
            AlmostEqual(mDistance,other.mDistance,2) &&
            AlmostEqual(rDistance,other.rDistance,2) &&
            AlmostEqual(buffStand,other.buffStand,2) &&
            AlmostEqual(rStand,other.rStand,2) &&
            AlmostEqual(groupStand,other.groupStand,2) &&
            rushChance == other.rushChance &&
            AlmostEqual(rushMult,other.rushMult,2) &&
            flagsB == other.flagsB);
    }

bool CSTYRecord::CSTYCSTD::operator !=(const CSTYCSTD &other) const
    {
    return !(*this == other);
    }

CSTYRecord::CSTYCSAD::CSTYCSAD():
    dodgeFMult(-20.0f),
    dodgeFBase(0.0f),
    encSBase(-110.0f),
    encSMult(1.0f),
    dodgeAtkMult(1.0f),
    dodgeNAtkMult(0.75f),
    dodgeBAtkMult(1.0f),
    dodgeBNAtkMult(0.7f),
    dodgeFAtkMult(1.0f),
    dodgeFNAtkMult(0.5f),
    blockMult(20.0f),
    blockBase(0.0f),
    blockAtkMult(2.0f),
    blockNAtkMult(1.0f),
    atkMult(20.0f),
    atkBase(0.0f),
    atkAtkMult(0.75f),
    atkNAtkMult(1.0f),
    atkBlockMult(0.5f),
    pAtkFBase(5.0f),
    pAtkFMult(-10.0f)
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

CSTYRecord::CSTYRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CSTYRecord::CSTYRecord(CSTYRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    CSTD = srcRecord->CSTD;
    CSAD = srcRecord->CSAD;
    return;
    }

CSTYRecord::~CSTYRecord()
    {
    //
    }

bool CSTYRecord::IsUseAdvanced()
    {
    return (CSTD.value.flagsA & fIsUseAdvanced) != 0;
    }

void CSTYRecord::IsUseAdvanced(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsUseAdvanced, value);
    }

bool CSTYRecord::IsUseChanceForAttack()
    {
    return (CSTD.value.flagsA & fIsUseChanceForAttack) != 0;
    }

void CSTYRecord::IsUseChanceForAttack(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsUseChanceForAttack, value);
    }

bool CSTYRecord::IsIgnoreAllies()
    {
    return (CSTD.value.flagsA & fIsIgnoreAllies) != 0;
    }

void CSTYRecord::IsIgnoreAllies(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsIgnoreAllies, value);
    }

bool CSTYRecord::IsWillYield()
    {
    return (CSTD.value.flagsA & fIsWillYield) != 0;
    }

void CSTYRecord::IsWillYield(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsWillYield, value);
    }

bool CSTYRecord::IsRejectsYields()
    {
    return (CSTD.value.flagsA & fIsRejectsYields) != 0;
    }

void CSTYRecord::IsRejectsYields(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsRejectsYields, value);
    }

bool CSTYRecord::IsFleeingDisabled()
    {
    return (CSTD.value.flagsA & fIsFleeingDisabled) != 0;
    }

void CSTYRecord::IsFleeingDisabled(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsFleeingDisabled, value);
    }

bool CSTYRecord::IsPrefersRanged()
    {
    return (CSTD.value.flagsA & fIsPrefersRanged) != 0;
    }

void CSTYRecord::IsPrefersRanged(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsPrefersRanged, value);
    }

bool CSTYRecord::IsMeleeAlertOK()
    {
    return (CSTD.value.flagsA & fIsMeleeAlertOK) != 0;
    }

void CSTYRecord::IsMeleeAlertOK(bool value)
    {
    SETBIT(CSTD.value.flagsA, fIsMeleeAlertOK, value);
    }

bool CSTYRecord::IsFlagAMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((CSTD.value.flagsA & Mask) == Mask) : ((CSTD.value.flagsA & Mask) != 0);
    }

void CSTYRecord::SetFlagAMask(uint8_t Mask)
    {
    CSTD.value.flagsA = Mask;
    }

bool CSTYRecord::IsDoNotAcquire()
    {
    return (CSTD.value.flagsB & fIsDoNotAcquire) != 0;
    }

void CSTYRecord::IsDoNotAcquire(bool value)
    {
    SETBIT(CSTD.value.flagsB, fIsDoNotAcquire, value);
    }

bool CSTYRecord::IsFlagBMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((CSTD.value.flagsB & Mask) == Mask) : ((CSTD.value.flagsB & Mask) != 0);
    }

void CSTYRecord::SetFlagBMask(uint32_t Mask)
    {
    CSTD.value.flagsB = Mask;
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
    return 1;
    }

int32_t CSTYRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(CSTD);
    WRITE(CSAD);
    return -1;
    }

bool CSTYRecord::operator ==(const CSTYRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            CSTD == other.CSTD &&
            CSAD == other.CSAD);
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