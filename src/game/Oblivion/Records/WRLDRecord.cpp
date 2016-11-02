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

namespace Ob
{
WRLDRecord::WRLDRecord(unsigned char *_recData):
    Record(_recData),
    ROAD(NULL),
    CELL(NULL)
    {
    //
    }

WRLDRecord::WRLDRecord(WRLDRecord *srcRecord):
    Record(),
    ROAD(NULL),
    CELL(NULL)
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
    FULL = srcRecord->FULL;
    WNAM = srcRecord->WNAM;
    CNAM = srcRecord->CNAM;
    NAM2 = srcRecord->NAM2;
    ICON = srcRecord->ICON;
    MNAM = srcRecord->MNAM;
    DATA = srcRecord->DATA;
    NAM0 = srcRecord->NAM0;
    NAM9 = srcRecord->NAM9;
    SNAM = srcRecord->SNAM;
    OFST = srcRecord->OFST;
    }

WRLDRecord::~WRLDRecord()
    {
    //ROAD is owned at the mod level, so must be destroyed there
    //CELL is owned at the mod level, so must be destroyed there
    //CELLS are owned at the mod level, so must be destroyed there
    }

bool WRLDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);
    if(NAM2.IsLoaded())
        op.Accept(NAM2.value);

    return op.Stop();
    }

bool WRLDRecord::IsSmallWorld()
    {
    return (DATA.value & fSmallWorld) != 0;
    }

void WRLDRecord::IsSmallWorld(bool value)
    {
    SETBIT(DATA.value, fSmallWorld, value);
    }

bool WRLDRecord::IsNoFastTravel()
    {
    return (DATA.value & fNoFastTravel) != 0;
    }

void WRLDRecord::IsNoFastTravel(bool value)
    {
    SETBIT(DATA.value, fNoFastTravel, value);
    }

bool WRLDRecord::IsFastTravel()
    {
    return !IsNoFastTravel();
    }

void WRLDRecord::IsFastTravel(bool value)
    {
    IsNoFastTravel(!value);
    }

bool WRLDRecord::IsOblivionWorldspace()
    {
    return (DATA.value & fOblivionWorldspace) != 0;
    }

void WRLDRecord::IsOblivionWorldspace(bool value)
    {
    SETBIT(DATA.value, fOblivionWorldspace, value);
    }

bool WRLDRecord::IsNoLODWater()
    {
    return (DATA.value & fNoLODWater) != 0;
    }

void WRLDRecord::IsNoLODWater(bool value)
    {
    SETBIT(DATA.value, fNoLODWater, value);
    }

bool WRLDRecord::IsLODWater()
    {
    return !IsNoLODWater();
    }

void WRLDRecord::IsLODWater(bool value)
    {
    IsNoLODWater(!value);
    }

bool WRLDRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void WRLDRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value = Mask;
    }

bool WRLDRecord::IsDefaultMusic()
    {
    return (SNAM.value == eDefault);
    }

void WRLDRecord::IsDefaultMusic(bool value)
    {
    if(value)
        SNAM.value = eDefault;
    else if(IsDefaultMusic())
        SNAM.value = ePublic;
    }

bool WRLDRecord::IsPublicMusic()
    {
    return (SNAM.value == ePublic);
    }

void WRLDRecord::IsPublicMusic(bool value)
    {
    if(value)
        SNAM.value = ePublic;
    else if(IsPublicMusic())
        SNAM.value = eDefault;
    }

bool WRLDRecord::IsDungeonMusic()
    {
    return (SNAM.value == eDungeon);
    }

void WRLDRecord::IsDungeonMusic(bool value)
    {
    if(value)
        SNAM.value = eDungeon;
    else if(IsDungeonMusic())
        SNAM.value = eDefault;
    }

bool WRLDRecord::IsMusicType(uint32_t Type)
    {
    return (SNAM.value == Type);
    }

void WRLDRecord::SetMusicType(uint32_t Type)
    {
    SNAM.value = Type;
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
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
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
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(OFST):
                OFST.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WRLD: %08X - Unknown subType = %04x\n", formID, subType);
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
    WNAM.Unload();
    CNAM.Unload();
    NAM2.Unload();
    ICON.Unload();
    MNAM.Unload();
    DATA.Unload();
    NAM0.Unload();
    NAM9.Unload();
    SNAM.Unload();
    OFST.Unload();
    return 1;
    }

int32_t WRLDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(WNAM);
    WRITE(CNAM);
    WRITE(NAM2);
    WRITE(ICON);
    WRITE(MNAM);
    WRITE(DATA);
    WRITE(NAM0);
    WRITE(NAM9);
    WRITE(SNAM);
    WRITE(OFST);
    return -1;
    }

bool WRLDRecord::operator ==(const WRLDRecord &other) const
    {
    return (DATA == other.DATA &&
            SNAM == other.SNAM &&
            WNAM == other.WNAM &&
            CNAM == other.CNAM &&
            NAM2 == other.NAM2 &&
            MNAM == other.MNAM &&
            NAM0 == other.NAM0 &&
            NAM9 == other.NAM9 &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            OFST == other.OFST);
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

    if(ROAD != NULL)
        {
        if(master_wrld->ROAD != NULL)
            {
            if(identical_records.count(ROAD) == 0)
                return false;
            }
        else
            return false;
        }

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

    //The cell and all its contents are dupes, so remove the child records from identical_records
    // This prevents Bash from trying to double delete records (first the cell, and later a child that was in the cell)
    identical_records.erase(ROAD);
    identical_records.erase(CELL);

    for(uint32_t ListIndex = 0; ListIndex < CELLS.size(); ++ListIndex)
        identical_records.erase(CELLS[ListIndex]);
    return true;
    }
}