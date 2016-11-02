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

namespace FNV
{
EFSHRecord::EFSHDATA::EFSHDATA():
    flags(0),
    memSBlend(0),
    memBlendOp(0),
    memZFunc(0),
    fillAIn(0.0f),
    fillAFull(0.0f),
    fillAOut(0.0f),
    fillAPRatio(0.0f),
    fillAAmp(0.0f),
    fillAFreq(0.0f),
    fillAnimSpdU(0.0f),
    fillAnimSpdV(0.0f),
    edgeEffOff(0.0f),
    edgeEffAIn(0.0f),
    edgeEffAFull(0.0f),
    edgeEffAOut(0.0f),
    edgeEffAPRatio(0.0f),
    edgeEffAAmp(0.0f),
    edgeEffAFreq(0.0f),
    fillAFRatio(0.0f),
    edgeEffAFRatio(0.0f),
    memDBlend(0),
    partSBlend(0),
    partBlendOp(0),
    partZFunc(0),
    partDBlend(0),
    partBUp(0.0f),
    partBFull(0.0f),
    partBDown(0.0f),
    partBFRatio(0.0f),
    partBPRatio(0.0f),
    partLTime(0.0f),
    partLDelta(0.0f),
    partNSpd(0.0f),
    partNAcc(0.0f),
    partVel1(0.0f),
    partVel2(0.0f),
    partVel3(0.0f),
    partAcc1(0.0f),
    partAcc2(0.0f),
    partAcc3(0.0f),
    partKey1(0.0f),
    partKey2(0.0f),
    partKey1Time(0.0f),
    partKey2Time(0.0f),
    key1A(0.0f),
    key2A(0.0f),
    key3A(0.0f),
    key1Time(0.0f),
    key2Time(0.0f),
    key3Time(0.0f),
    partInitSpd(0.0f),
    partInitRot(0.0f),
    partInitRotDelta(0.0f),
    partRotSpd(0.0f),
    partRotDelta(0.0f),
    addon(0),
    holesSTime(0.0f),
    holesETime(0.0f),
    holesSValue(0.0f),
    holesEValue(0.0f),
    edgeWidth(0.0f),
    explWindSpd(0.0f),
    textCountU(0),
    textCountV(0),
    addonFITime(0.0f),
    addonFOTime(0.0f),
    addonScaleStart(0.0f),
    addonScaleEnd(0.0f),
    addonScaleInTime(0.0f),
    addonScaleOutTime(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
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
            memDBlend == other.memDBlend &&
            partSBlend == other.partSBlend &&
            partBlendOp == other.partBlendOp &&
            partZFunc == other.partZFunc &&
            partDBlend == other.partDBlend &&
            addon == other.addon &&
            fill == other.fill &&
            edgeEff == other.edgeEff &&
            key1 == other.key1 &&
            key2 == other.key2 &&
            key3 == other.key3 &&
            edge == other.edge &&
            textCountU == other.textCountU &&
            textCountV == other.textCountV &&
            AlmostEqual(fillAIn,other.fillAIn,2) &&
            AlmostEqual(fillAFull,other.fillAFull,2) &&
            AlmostEqual(fillAOut,other.fillAOut,2) &&
            AlmostEqual(fillAPRatio,other.fillAPRatio,2) &&
            AlmostEqual(fillAAmp,other.fillAAmp,2) &&
            AlmostEqual(fillAFreq,other.fillAFreq,2) &&
            AlmostEqual(fillAnimSpdU,other.fillAnimSpdU,2) &&
            AlmostEqual(fillAnimSpdV,other.fillAnimSpdV,2) &&
            AlmostEqual(edgeEffOff,other.edgeEffOff,2) &&
            AlmostEqual(edgeEffAIn,other.edgeEffAIn,2) &&
            AlmostEqual(edgeEffAFull,other.edgeEffAFull,2) &&
            AlmostEqual(edgeEffAOut,other.edgeEffAOut,2) &&
            AlmostEqual(edgeEffAPRatio,other.edgeEffAPRatio,2) &&
            AlmostEqual(edgeEffAAmp,other.edgeEffAAmp,2) &&
            AlmostEqual(edgeEffAFreq,other.edgeEffAFreq,2) &&
            AlmostEqual(fillAFRatio,other.fillAFRatio,2) &&
            AlmostEqual(edgeEffAFRatio,other.edgeEffAFRatio,2) &&
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
            AlmostEqual(key1A,other.key1A,2) &&
            AlmostEqual(key2A,other.key2A,2) &&
            AlmostEqual(key3A,other.key3A,2) &&
            AlmostEqual(key1Time,other.key1Time,2) &&
            AlmostEqual(key2Time,other.key2Time,2) &&
            AlmostEqual(key3Time,other.key3Time,2) &&
            AlmostEqual(partInitSpd,other.partInitSpd,2) &&
            AlmostEqual(partInitRot,other.partInitRot,2) &&
            AlmostEqual(partInitRotDelta,other.partInitRotDelta,2) &&
            AlmostEqual(partRotSpd,other.partRotSpd,2) &&
            AlmostEqual(partRotDelta,other.partRotDelta,2) &&
            AlmostEqual(holesSTime,other.holesSTime,2) &&
            AlmostEqual(holesETime,other.holesETime,2) &&
            AlmostEqual(holesSValue,other.holesSValue,2) &&
            AlmostEqual(holesEValue,other.holesEValue,2) &&
            AlmostEqual(edgeWidth,other.edgeWidth,2) &&
            AlmostEqual(explWindSpd,other.explWindSpd,2) &&
            AlmostEqual(addonFITime,other.addonFITime,2) &&
            AlmostEqual(addonFOTime,other.addonFOTime,2) &&
            AlmostEqual(addonScaleStart,other.addonScaleStart,2) &&
            AlmostEqual(addonScaleEnd,other.addonScaleEnd,2) &&
            AlmostEqual(addonScaleInTime,other.addonScaleInTime,2) &&
            AlmostEqual(addonScaleOutTime,other.addonScaleOutTime,2));
    }

bool EFSHRecord::EFSHDATA::operator !=(const EFSHDATA &other) const
    {
    return !(*this == other);
    }

EFSHRecord::EFSHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EFSHRecord::EFSHRecord(EFSHRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    ICO2 = srcRecord->ICO2;
    NAM7 = srcRecord->NAM7;
    DATA = srcRecord->DATA;
    return;
    }

EFSHRecord::~EFSHRecord()
    {
    //
    }

bool EFSHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(DATA.value.addon);

    return op.Stop();
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

uint32_t EFSHRecord::GetType()
    {
    return REV32(EFSH);
    }

char * EFSHRecord::GetStrType()
    {
    return "EFSH";
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
            case REV32(NAM7):
                NAM7.Read(buffer, subSize, CompressedOnDisk);
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

int32_t EFSHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    ICON.Unload();
    ICO2.Unload();
    NAM7.Unload();
    DATA.Unload();
    return 1;
    }

int32_t EFSHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(ICO2);
    WRITE(NAM7);
    WRITE(DATA);
    return -1;
    }

bool EFSHRecord::operator ==(const EFSHRecord &other) const
    {
    return (DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            ICO2.equalsi(other.ICO2) &&
            NAM7.equalsi(other.NAM7));
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