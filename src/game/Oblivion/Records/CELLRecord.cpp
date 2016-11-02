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
#include "CELLRecord.h"

namespace Ob
{
CELLRecord::CELLXCLL::CELLXCLL():
    fogNear(0),
    fogFar(0),
    directionalXY(0),
    directionalZ(0),
    directionalFade(1.0f),
    fogClip(0)
    {
    //
    }

CELLRecord::CELLXCLL::~CELLXCLL()
    {
    //
    }

bool CELLRecord::CELLXCLL::operator ==(const CELLXCLL &other) const
    {
    return (ambient == other.ambient &&
            directional == other.directional &&
            fog == other.fog &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            directionalXY == other.directionalXY &&
            directionalZ == other.directionalZ &&
            AlmostEqual(directionalFade,other.directionalFade,2) &&
            AlmostEqual(fogClip,other.fogClip,2));
    }

bool CELLRecord::CELLXCLL::operator !=(const CELLXCLL &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLXCLC::CELLXCLC():
    posX(0),
    posY(0)
    {
    //
    }

CELLRecord::CELLXCLC::~CELLXCLC()
    {
    //
    }

bool CELLRecord::CELLXCLC::operator ==(const CELLXCLC &other) const
    {
    return (posX == other.posX &&
            posY == other.posY);
    }

bool CELLRecord::CELLXCLC::operator !=(const CELLXCLC &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLRecord(unsigned char *_recData):
    Record(_recData),
    PGRD(NULL),
    LAND(NULL)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
    Record(),
    PGRD(NULL),
    LAND(NULL)
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
    DATA = srcRecord->DATA;
    XCLL = srcRecord->XCLL;
    XCMT = srcRecord->XCMT;
    Ownership = srcRecord->Ownership;
    XCCM = srcRecord->XCCM;
    XCLW = srcRecord->XCLW;
    XCLR = srcRecord->XCLR;
    XCLC = srcRecord->XCLC;
    XCWT = srcRecord->XCWT;
    return;
    }

CELLRecord::~CELLRecord()
    {
    //
    //ACHRs are owned at the mod level, so must be destroyed there
    //ACREs are owned at the mod level, so must be destroyed there
    //REFRs are owned at the mod level, so must be destroyed there
    //PGRD is owned at the mod level, so must be destroyed there
    //LAND is owned at the mod level, so must be destroyed there
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    }

bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(Ownership.IsLoaded())
        {
        if(Ownership->XOWN.IsLoaded())
            op.Accept(Ownership->XOWN.value);
        if(Ownership->XGLB.IsLoaded())
            op.Accept(Ownership->XGLB.value);
        }
    if(XCCM.IsLoaded())
        op.Accept(XCCM.value);
    for(uint32_t ListIndex = 0; ListIndex < XCLR.value.size(); ListIndex++)
        op.Accept(XCLR.value[ListIndex]);

    if(XCWT.IsLoaded())
        op.Accept(XCWT.value);

    return op.Stop();
    }

bool CELLRecord::IsInterior()
    {
    return (DATA.value & fIsInterior) != 0;
    }

void CELLRecord::IsInterior(bool value)
    {
    SETBIT(DATA.value, fIsInterior, value);
    }

bool CELLRecord::IsHasWater()
    {
    return (DATA.value & fHasWater) != 0;
    }

void CELLRecord::IsHasWater(bool value)
    {
    SETBIT(DATA.value, fHasWater, value);
    }

bool CELLRecord::IsInvertFastTravel()
    {
    return (DATA.value & fInvertFastTravel) != 0;
    }

void CELLRecord::IsInvertFastTravel(bool value)
    {
    SETBIT(DATA.value, fInvertFastTravel, value);
    }

bool CELLRecord::IsForceHideLand()
    {
    return (DATA.value & fForceHideLand) != 0;
    }

void CELLRecord::IsForceHideLand(bool value)
    {
    SETBIT(DATA.value, fForceHideLand, value);
    }

bool CELLRecord::IsPublicPlace()
    {
    return (DATA.value & fPublicPlace) != 0;
    }

void CELLRecord::IsPublicPlace(bool value)
    {
    SETBIT(DATA.value, fPublicPlace, value);
    }

bool CELLRecord::IsHandChanged()
    {
    return (DATA.value & fHandChanged) != 0;
    }

void CELLRecord::IsHandChanged(bool value)
    {
    SETBIT(DATA.value, fHandChanged, value);
    }

bool CELLRecord::IsBehaveLikeExterior()
    {
    return (DATA.value & fBehaveLikeExterior) != 0;
    }

void CELLRecord::IsBehaveLikeExterior(bool value)
    {
    SETBIT(DATA.value, fBehaveLikeExterior, value);
    }

bool CELLRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void CELLRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value = Mask;
    }

bool CELLRecord::IsDefaultMusic()
    {
    XCMT.Load();
    return XCMT.value == eDefault;
    }

void CELLRecord::IsDefaultMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = eDefault;
    else if(IsDefaultMusic())
        XCMT.value = ePublic;
    }

bool CELLRecord::IsPublicMusic()
    {
    XCMT.Load();
    return XCMT.value == ePublic;
    }

void CELLRecord::IsPublicMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = ePublic;
    else if(IsPublicMusic())
        XCMT.value = eDefault;
    }

bool CELLRecord::IsDungeonMusic()
    {
    XCMT.Load();
    return XCMT.value == eDungeon;
    }

void CELLRecord::IsDungeonMusic(bool value)
    {
    XCMT.Load();
    if(value)
        XCMT.value = eDungeon;
    else if(IsDungeonMusic())
        XCMT.value = eDefault;
    }

bool CELLRecord::IsMusicType(uint8_t Type)
    {
    XCMT.Load();
    return XCMT.value == Type;
    }

void CELLRecord::SetMusicType(uint8_t Type)
    {
    XCMT.Load();
    XCMT.value = Type;
    }

uint32_t CELLRecord::GetType()
    {
    return REV32(CELL);
    }

char * CELLRecord::GetStrType()
    {
    return "CELL";
    }

int32_t CELLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(XCLL):
                XCLL.Read(buffer, subSize);
                break;
            case REV32(XCMT):
                XCMT.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XGLB):
                Ownership.Load();
                Ownership->XGLB.Read(buffer, subSize);
                break;
            case REV32(XCCM):
                XCCM.Read(buffer, subSize);
                break;
            case REV32(XCLW):
                XCLW.Read(buffer, subSize);
                break;
            case REV32(XCLR):
                XCLR.Read(buffer, subSize);
                break;
            case REV32(XCLC):
                XCLC.Read(buffer, subSize);
                break;
            case REV32(XCWT):
                XCWT.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CELL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CELLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    //DATA.Unload(); //need to keep IsInterior around
    XCLL.Unload();
    XCMT.Unload();
    Ownership.Unload();
    XCCM.Unload();
    XCLW.Unload();
    XCLR.Unload();
    XCLC.Unload();
    XCWT.Unload();
    return 1;
    }

int32_t CELLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    WRITE(FULL);
    WRITE(DATA);
    WRITE(XCLL);
    WRITE(XCMT);
    Ownership.Write(writer);

    WRITE(XCCM);
    WRITE(XCLW);
    WRITE(XCLR);
    if(!IsInterior())
        WRITE(XCLC);
    WRITE(XCWT);
    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    return (DATA == other.DATA &&
            XCMT == other.XCMT &&
            XCCM == other.XCCM &&
            XCWT == other.XCWT &&
            XCLL == other.XCLL &&
            XCLC == other.XCLC &&
            XCLW == other.XCLW &&
            Ownership == other.Ownership &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XCLR == other.XCLR);
    }

bool CELLRecord::operator !=(const CELLRecord &other) const
    {
    return !(*this == other);
    }

bool CELLRecord::equals(Record *other)
    {
    return *this == *(CELLRecord *)other;
    }

bool CELLRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited

    CELLRecord *master_cell = (CELLRecord *)master;
    Record *parent_wrld = GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the CELLs are attached at the same spot
    if(parent_wrld != NULL)
        {
        if(master_wrld != NULL)
            {
            if(parent_wrld->formID != master_wrld->formID)
                return false;
            }
        else
            return false;
        }
    else if(master_wrld != NULL)
        return false;

    if(ACHR.size() > master_cell->ACHR.size())
        return false;
    if(ACRE.size() > master_cell->ACRE.size())
        return false;
    if(REFR.size() > master_cell->REFR.size())
        return false;

    if(PGRD != NULL)
        {
        if(master_cell->PGRD != NULL)
            {
            if(identical_records.count(PGRD) == 0)
                return false;
            }
        else
            return false;
        }

    if(LAND != NULL)
        {
        if(master_cell->LAND != NULL)
            {
            if(identical_records.count(LAND) == 0)
                return false;
            }
        else
            return false;
        }

    for(uint32_t ListIndex = 0; ListIndex < ACHR.size(); ++ListIndex)
        if(identical_records.count(ACHR[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < ACRE.size(); ++ListIndex)
        if(identical_records.count(ACRE[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < REFR.size(); ++ListIndex)
        if(identical_records.count(REFR[ListIndex]) == 0)
            return false;

    //The cell and all its contents are dupes, so remove the child records from identical_records
    // This prevents Bash from trying to double delete records (first the cell, and later a child that was in the cell)
    identical_records.erase(PGRD);
    identical_records.erase(LAND);

    for(uint32_t ListIndex = 0; ListIndex < ACHR.size(); ++ListIndex)
        identical_records.erase(ACHR[ListIndex]);

    for(uint32_t ListIndex = 0; ListIndex < ACRE.size(); ++ListIndex)
        identical_records.erase(ACRE[ListIndex]);

    for(uint32_t ListIndex = 0; ListIndex < REFR.size(); ++ListIndex)
        identical_records.erase(REFR[ListIndex]);

    return true;
    }
}