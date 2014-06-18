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
#include "WRLDRecord.h"

namespace Sk
{
WRLDRecord::WRLDRecord(unsigned char *_recData):
    TES5Record(_recData),
    CELL(NULL)
    {
    //
    }

WRLDRecord::WRLDRecord(WRLDRecord *srcRecord):
    TES5Record((TES5Record *)srcRecord),
    CELL(NULL)
    {
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    XEZN = srcRecord->XEZN;
    WNAM = srcRecord->WNAM;
    PNAM = srcRecord->PNAM;
    CNAM = srcRecord->CNAM;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    DNAM = srcRecord->DNAM;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    MNAM = srcRecord->MNAM;
    ONAM = srcRecord->ONAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    NAM0 = srcRecord->NAM0;
    NAM9 = srcRecord->NAM9;
    ZNAM = srcRecord->ZNAM;
    NNAM = srcRecord->NNAM;
    XNAM = srcRecord->XNAM;
    IMPS = srcRecord->IMPS;
    IMPF = srcRecord->IMPF;
    OFST = srcRecord->OFST;
    RNAM = srcRecord->RNAM;
    NAMA = srcRecord->NAMA;
    TNAM = srcRecord->TNAM;
    UNAM = srcRecord->UNAM;
    }

WRLDRecord::~WRLDRecord()
    {
      /* TODO: PROBLEMS! */
#if 0
    delete CELL;
    for(uint32_t x = 0; x < CELLS.size(); ++x)
      delete CELLS[x];
#endif
    }

bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    op.Accept(NAM2.value);
    op.Accept(NAM3.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    for(uint32_t ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }

    return op.Stop();
    }

bool WRLDRecord::IsSmallWorld()
    {
    return (DATA.value & fIsSmallWorld) != 0;
    }

void WRLDRecord::IsSmallWorld(bool value)
    {
    SETBIT(DATA.value, fIsSmallWorld, value);
    }

bool WRLDRecord::IsNoFastTravel()
    {
    return (DATA.value & fIsNoFastTravel) != 0;
    }

void WRLDRecord::IsNoFastTravel(bool value)
    {
    SETBIT(DATA.value, fIsNoFastTravel, value);
    }

bool WRLDRecord::IsFastTravel()
    {
    return !IsNoFastTravel();
    }

void WRLDRecord::IsFastTravel(bool value)
    {
    IsNoFastTravel(!value);
    }

bool WRLDRecord::IsNoLODWater()
    {
    return (DATA.value & fIsNoLODWater) != 0;
    }

void WRLDRecord::IsNoLODWater(bool value)
    {
    SETBIT(DATA.value, fIsNoLODWater, value);
    }

bool WRLDRecord::IsLODWater()
    {
    return !IsNoLODWater();
    }

void WRLDRecord::IsLODWater(bool value)
    {
    IsNoLODWater(!value);
    }

/*
bool WRLDRecord::IsNoLODNoise()
    {
    return (DATA.value & fIsNoLODNoise) != 0;
    }

void WRLDRecord::IsNoLODNoise(bool value)
    {
    SETBIT(DATA.value, fIsNoLODNoise, value);
    }

bool WRLDRecord::IsLODNoise()
    {
    return !IsNoLODNoise();
    }

void WRLDRecord::IsLODNoise(bool value)
    {
    IsNoLODNoise(!value);
    }

bool WRLDRecord::IsNoNPCFallDmg()
    {
    return (DATA.value & fIsNoNPCFallDmg) != 0;
    }

void WRLDRecord::IsNoNPCFallDmg(bool value)
    {
    SETBIT(DATA.value, fIsNoNPCFallDmg, value);
    }

bool WRLDRecord::IsNPCFallDmg()
    {
    return !IsNoNPCFallDmg();
    }

void WRLDRecord::IsNPCFallDmg(bool value)
    {
    IsNoNPCFallDmg(!value);
    }
*/

bool WRLDRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void WRLDRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value = Mask;
    }

bool WRLDRecord::IsUseLandData()
    {
    return (PNAM.value & fIsUseLandData) != 0;
    }

void WRLDRecord::IsUseLandData(bool value)
    {
    SETBIT(PNAM.value, fIsUseLandData, value);
    }

bool WRLDRecord::IsUseLODData()
    {
    return (PNAM.value & fIsUseLODData) != 0;
    }

void WRLDRecord::IsUseLODData(bool value)
    {
    SETBIT(PNAM.value, fIsUseLODData, value);
    }

bool WRLDRecord::IsUseMapData()
    {
    return (PNAM.value & fIsUseMapData) != 0;
    }

void WRLDRecord::IsUseMapData(bool value)
    {
    SETBIT(PNAM.value, fIsUseMapData, value);
    }

bool WRLDRecord::IsUseWaterData()
    {
    return (PNAM.value & fIsUseWaterData) != 0;
    }

void WRLDRecord::IsUseWaterData(bool value)
    {
    SETBIT(PNAM.value, fIsUseWaterData, value);
    }

bool WRLDRecord::IsUseClimateData()
    {
    return (PNAM.value & fIsUseClimateData) != 0;
    }

void WRLDRecord::IsUseClimateData(bool value)
    {
    SETBIT(PNAM.value, fIsUseClimateData, value);
    }

bool WRLDRecord::IsUseImageSpaceData()
    {
    return (PNAM.value & fIsUseImageSpaceData) != 0;
    }

void WRLDRecord::IsUseImageSpaceData(bool value)
    {
    SETBIT(PNAM.value, fIsUseImageSpaceData, value);
    }

bool WRLDRecord::IsNeedsWaterAdjustment()
    {
    return (PNAM.value & fIsNeedsWaterAdjustment) != 0;
    }

void WRLDRecord::IsNeedsWaterAdjustment(bool value)
    {
    SETBIT(PNAM.value, fIsNeedsWaterAdjustment, value);
    }

bool WRLDRecord::IsUseFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((PNAM.value & Mask) == Mask) : ((PNAM.value & Mask) != 0);
    }

void WRLDRecord::SetUseFlagMask(uint16_t Mask)
    {
    PNAM.value = Mask;
    }

uint32_t WRLDRecord::GetType()
    {
    return REV32(WRLD);
    }

char * WRLDRecord::GetStrType()
    {
    return "WRLD";
    }

int32_t WRLDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(IMPS):
                IMPS.Read(buffer, subSize);
                break;
            case REV32(IMPF):
                IMPF.Read(buffer, subSize);
                break;
            case REV32(OFST):
                OFST.Read(buffer, subSize, CompressedOnDisk);
                break;
            /* Skyrim --------------------------------------- */
            case REV32(RNAM): // 264 bytes
                RNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAMA): // 4 bytes
                NAMA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TNAM): // 53 bytes, Data\Textures\Landscape\Mountains\MountainSlab02.dds
                TNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(UNAM): // 53 bytes, Data\Textures\Landscape\Mountains\MountainSlab02_N.dds
                UNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WRLD: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t WRLDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    XEZN.Unload();
    WNAM.Unload();
    PNAM.Unload();
    CNAM.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    DNAM.Unload();
    ICON.Unload();
    MICO.Unload();
    MNAM.Unload();
    ONAM.Unload();
    INAM.Unload();
    DATA.Unload();
    NAM0.Unload();
    NAM9.Unload();
    ZNAM.Unload();
    NNAM.Unload();
    XNAM.Unload();
    IMPS.Unload();
    IMPF.Unload();
    OFST.Unload();
    RNAM.Unload();
    NAMA.Unload();
    TNAM.Unload();
    UNAM.Unload();
    return 1;
    }

int32_t WRLDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(XEZN);
    WRITE(WNAM);
    WRITE(PNAM);
    WRITE(CNAM);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(NAM4);
    WRITE(DNAM);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(MNAM);
    WRITE(ONAM);
    WRITE(INAM);
    WRITE(DATA);
    WRITE(NAM0);
    WRITE(NAM9);
    WRITE(ZNAM);
    WRITEREQ(NNAM);
    WRITEREQ(XNAM);
    WRITE(IMPS);
    WRITE(IMPF);
    WRITE(OFST);
    WRITE(RNAM);
    WRITE(NAMA);
    WRITE(TNAM);
    WRITE(UNAM);

    return -1;
    }

bool WRLDRecord::operator ==(const WRLDRecord &other) const
    {
    return (XEZN == other.XEZN &&
            WNAM == other.WNAM &&
            PNAM == other.PNAM &&
            CNAM == other.CNAM &&
            NAM2 == other.NAM2 &&
            NAM3 == other.NAM3 &&
            NAM4 == other.NAM4 &&
            DNAM == other.DNAM &&
            MNAM == other.MNAM &&
            ONAM == other.ONAM &&
            INAM == other.INAM &&
            DATA == other.DATA &&
            NAM0 == other.NAM0 &&
            NAM9 == other.NAM9 &&
            ZNAM == other.ZNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            NNAM.equalsi(other.NNAM) &&
            XNAM.equalsi(other.XNAM) &&
            IMPS == other.IMPS &&
            IMPF == other.IMPF &&
            OFST == other.OFST &&
            RNAM == other.RNAM &&
            NAMA == other.NAMA &&
            TNAM.equalsi(other.TNAM) &&
            UNAM.equalsi(other.UNAM));
    }

bool WRLDRecord::operator !=(const WRLDRecord &other) const
    {
    return !(*this == other);
    }

bool WRLDRecord::equals(Record *other)
    {
    return *this == *(WRLDRecord *)other;
    }

bool WRLDRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited
    const WRLDRecord *master_wrld = (WRLDRecord *)master;

    if(CELLS.size() > master_wrld->CELLS.size())
        return false;

    if(CELL != NULL)
        {
        if(master_wrld->CELL != NULL)
            {
            if(identical_records.count(CELL) == 0)
                return false;
            }
        else
            return false;
        }

    for(uint32_t ListIndex = 0; ListIndex < CELLS.size(); ++ListIndex)
        if(identical_records.count(CELLS[ListIndex]) == 0)
                return false;
    return true;
    }
}