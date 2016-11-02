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
#include "EFSHRecord.h"

namespace Ob
{
EFSHRecord::EFSHDATA::EFSHDATA():
    flags(0),
    memSBlend(5),
    memBlendOp(1),
    memZFunc(3),
    fillAIn(0.0f),
    fillAFull(0.0f),
    fillAOut(0.0f),
    fillAPRatio(0.0f),
    fillAAmp(0.0f),
    fillAFreq(1.0f),
    fillAnimSpdU(0.0f),
    fillAnimSpdV(0.0f),
    edgeOff(1.0f),
    edgeAIn(0.0f),
    edgeAFull(0.0f),
    edgeAOut(0.0f),
    edgeAPRatio(0.0f),
    edgeAAmp(0.0f),
    edgeAFreq(1.0f),
    fillAFRatio(1.0f),
    edgeAFRatio(1.0f),
    memDBlend(6),
    partSBlend(5),
    partBlendOp(1),
    partZFunc(4),
    partDBlend(6),
    partBUp(0.0f),
    partBFull(0.0f),
    partBDown(0.0f),
    partBFRatio(1.0f),
    partBPRatio(1.0f),
    partLTime(1.0f),
    partLDelta(0.0f),
    partNSpd(0.0f),
    partNAcc(0.0f),
    partVel1(0.0f),
    partVel2(0.0f),
    partVel3(0.0f),
    partAcc1(0.0f),
    partAcc2(0.0f),
    partAcc3(0.0f),
    partKey1(1.0f),
    partKey2(1.0f),
    partKey1Time(0.0f),
    partKey2Time(1.0f),
    key1(0xFF, 0xFF, 0xFF, 0x00),
    key2(0xFF, 0xFF, 0xFF, 0x00),
    key3(0xFF, 0xFF, 0xFF, 0x00),
    key1A(1.0f),
    key2A(1.0f),
    key3A(1.0f),
    key1Time(0.0f),
    key2Time(0.5f),
    key3Time(1.0f)
    {
    memset(&unused1[0], 0xCD, sizeof(unused1));
    }

EFSHRecord::EFSHDATA::~EFSHDATA()
    {
    //
    }

bool EFSHRecord::EFSHDATA::operator ==(const EFSHDATA &other) const
    {
    return (flags == other.flags &&
            memSBlend == other.memSBlend &&
            memBlendOp == other.memBlendOp &&
            memZFunc == other.memZFunc &&
            fill == other.fill &&
            AlmostEqual(fillAIn,other.fillAIn,2) &&
            AlmostEqual(fillAFull,other.fillAFull,2) &&
            AlmostEqual(fillAOut,other.fillAOut,2) &&
            AlmostEqual(fillAPRatio,other.fillAPRatio,2) &&
            AlmostEqual(fillAAmp,other.fillAAmp,2) &&
            AlmostEqual(fillAFreq,other.fillAFreq,2) &&
            AlmostEqual(fillAnimSpdU,other.fillAnimSpdU,2) &&
            AlmostEqual(fillAnimSpdV,other.fillAnimSpdV,2) &&
            AlmostEqual(edgeOff,other.edgeOff,2) &&
            edge == other.edge &&
            AlmostEqual(edgeAIn,other.edgeAIn,2) &&
            AlmostEqual(edgeAFull,other.edgeAFull,2) &&
            AlmostEqual(edgeAOut,other.edgeAOut,2) &&
            AlmostEqual(edgeAPRatio,other.edgeAPRatio,2) &&
            AlmostEqual(edgeAAmp,other.edgeAAmp,2) &&
            AlmostEqual(edgeAFreq,other.edgeAFreq,2) &&
            AlmostEqual(fillAFRatio,other.fillAFRatio,2) &&
            AlmostEqual(edgeAFRatio,other.edgeAFRatio,2) &&
            memDBlend == other.memDBlend &&
            partSBlend == other.partSBlend &&
            partBlendOp == other.partBlendOp &&
            partZFunc == other.partZFunc &&
            partDBlend == other.partDBlend &&
            AlmostEqual(partBUp,other.partBUp,2) &&
            AlmostEqual(partBFull,other.partBFull,2) &&
            AlmostEqual(partBDown,other.partBDown,2) &&
            AlmostEqual(partBFRatio,other.partBFRatio,2) &&
            AlmostEqual(partBPRatio,other.partBPRatio,2) &&
            AlmostEqual(partLTime,other.partLTime,2) &&
            AlmostEqual(partLDelta,other.partLDelta,2) &&
            AlmostEqual(partNSpd,other.partNSpd,2) &&
            AlmostEqual(partNAcc,other.partNAcc,2) &&
            AlmostEqual(partVel1,other.partVel1,2) &&
            AlmostEqual(partVel2,other.partVel2,2) &&
            AlmostEqual(partVel3,other.partVel3,2) &&
            AlmostEqual(partAcc1,other.partAcc1,2) &&
            AlmostEqual(partAcc2,other.partAcc2,2) &&
            AlmostEqual(partAcc3,other.partAcc3,2) &&
            AlmostEqual(partKey1,other.partKey1,2) &&
            AlmostEqual(partKey2,other.partKey2,2) &&
            AlmostEqual(partKey1Time,other.partKey1Time,2) &&
            AlmostEqual(partKey2Time,other.partKey2Time,2) &&
            key1 == other.key1 &&
            key2 == other.key2 &&
            key3 == other.key3 &&
            AlmostEqual(key1A,other.key1A,2) &&
            AlmostEqual(key2A,other.key2A,2) &&
            AlmostEqual(key3A,other.key3A,2) &&
            AlmostEqual(key1Time,other.key1Time,2) &&
            AlmostEqual(key2Time,other.key2Time,2) &&
            AlmostEqual(key3Time,other.key3Time,2));
    }

bool EFSHRecord::EFSHDATA::operator !=(const EFSHDATA &other) const
    {
    return !(*this == other);
    }

EFSHRecord::EFSHRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }
EFSHRecord::EFSHRecord(EFSHRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    ICO2 = srcRecord->ICO2;
    DATA = srcRecord->DATA;
    return;
    }

EFSHRecord::~EFSHRecord()
    {
    //
    }

bool EFSHRecord::IsNoMemShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMemShader(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoMemShader, value);
    }

bool EFSHRecord::IsNoMembraneShader()
    {
    return (DATA.value.flags & fIsNoMemShader) != 0;
    }

void EFSHRecord::IsNoMembraneShader(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoMemShader, value);
    }

bool EFSHRecord::IsNoPartShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoPartShader(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoPartShader, value);
    }

bool EFSHRecord::IsNoParticleShader()
    {
    return (DATA.value.flags & fIsNoPartShader) != 0;
    }

void EFSHRecord::IsNoParticleShader(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoPartShader, value);
    }

bool EFSHRecord::IsEdgeInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeInverse(bool value)
    {
    SETBIT(DATA.value.flags, fIsEdgeInverse, value);
    }

bool EFSHRecord::IsEdgeEffectInverse()
    {
    return (DATA.value.flags & fIsEdgeInverse) != 0;
    }

void EFSHRecord::IsEdgeEffectInverse(bool value)
    {
    SETBIT(DATA.value.flags, fIsEdgeInverse, value);
    }

bool EFSHRecord::IsMemSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMemSkinOnly(bool value)
    {
    SETBIT(DATA.value.flags, fIsMemSkinOnly, value);
    }

bool EFSHRecord::IsMembraneShaderSkinOnly()
    {
    return (DATA.value.flags & fIsMemSkinOnly) != 0;
    }

void EFSHRecord::IsMembraneShaderSkinOnly(bool value)
    {
    SETBIT(DATA.value.flags, fIsMemSkinOnly, value);
    }

bool EFSHRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void EFSHRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
    }

int32_t EFSHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICO2):
                ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  EFSH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

uint32_t EFSHRecord::GetType()
    {
    return REV32(EFSH);
    }

char * EFSHRecord::GetStrType()
    {
    return "EFSH";
    }

int32_t EFSHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    ICO2.Unload();
    DATA.Unload();
    return 1;
    }

int32_t EFSHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(ICO2);
    WRITE(DATA);
    return -1;
    }

bool EFSHRecord::operator ==(const EFSHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            ICO2.equalsi(other.ICO2) &&
            DATA == other.DATA);
    }

bool EFSHRecord::operator !=(const EFSHRecord &other) const
    {
    return !(*this == other);
    }

bool EFSHRecord::equals(Record *other)
    {
    return *this == *(EFSHRecord *)other;
    }
}