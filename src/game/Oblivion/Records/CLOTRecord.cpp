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
#include "CLOTRecord.h"

namespace Ob
{
CLOTRecord::CLOTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CLOTRecord::CLOTRecord(CLOTRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    BMDT = srcRecord->BMDT;
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    ICON = srcRecord->ICON;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    ICO2 = srcRecord->ICO2;
    DATA = srcRecord->DATA;
    return;
    }

CLOTRecord::~CLOTRecord()
    {
    //
    }

bool CLOTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool CLOTRecord::IsHead()
    {
    return (BMDT.value & fIsHead) != 0;
    }

void CLOTRecord::IsHead(bool value)
    {
    SETBIT(BMDT.value, fIsHead, value);
    }

bool CLOTRecord::IsHair()
    {
    return (BMDT.value & fIsHair) != 0;
    }

void CLOTRecord::IsHair(bool value)
    {
    SETBIT(BMDT.value, fIsHair, value);
    }

bool CLOTRecord::IsUpperBody()
    {
    return (BMDT.value & fIsUpperBody) != 0;
    }

void CLOTRecord::IsUpperBody(bool value)
    {
    SETBIT(BMDT.value, fIsUpperBody, value);
    }

bool CLOTRecord::IsLowerBody()
    {
    return (BMDT.value & fIsLowerBody) != 0;
    }

void CLOTRecord::IsLowerBody(bool value)
    {
    SETBIT(BMDT.value, fIsLowerBody, value);
    }

bool CLOTRecord::IsHand()
    {
    return (BMDT.value & fIsHand) != 0;
    }

void CLOTRecord::IsHand(bool value)
    {
    SETBIT(BMDT.value, fIsHand, value);
    }

bool CLOTRecord::IsFoot()
    {
    return (BMDT.value & fIsFoot) != 0;
    }

void CLOTRecord::IsFoot(bool value)
    {
    SETBIT(BMDT.value, fIsFoot, value);
    }

bool CLOTRecord::IsRightRing()
    {
    return (BMDT.value & fIsRightRing) != 0;
    }

void CLOTRecord::IsRightRing(bool value)
    {
    SETBIT(BMDT.value, fIsRightRing, value);
    }

bool CLOTRecord::IsLeftRing()
    {
    return (BMDT.value & fIsLeftRing) != 0;
    }

void CLOTRecord::IsLeftRing(bool value)
    {
    SETBIT(BMDT.value, fIsLeftRing, value);
    }

bool CLOTRecord::IsAmulet()
    {
    return (BMDT.value & fIsAmulet) != 0;
    }

void CLOTRecord::IsAmulet(bool value)
    {
    SETBIT(BMDT.value, fIsAmulet, value);
    }

bool CLOTRecord::IsWeapon()
    {
    return (BMDT.value & fIsWeapon) != 0;
    }

void CLOTRecord::IsWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsWeapon, value);
    }

bool CLOTRecord::IsBackWeapon()
    {
    return (BMDT.value & fIsBackWeapon) != 0;
    }

void CLOTRecord::IsBackWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsBackWeapon, value);
    }

bool CLOTRecord::IsSideWeapon()
    {
    return (BMDT.value & fIsSideWeapon) != 0;
    }

void CLOTRecord::IsSideWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsSideWeapon, value);
    }

bool CLOTRecord::IsQuiver()
    {
    return (BMDT.value & fIsQuiver) != 0;
    }

void CLOTRecord::IsQuiver(bool value)
    {
    SETBIT(BMDT.value, fIsQuiver, value);
    }

bool CLOTRecord::IsShield()
    {
    return (BMDT.value & fIsShield) != 0;
    }

void CLOTRecord::IsShield(bool value)
    {
    SETBIT(BMDT.value, fIsShield, value);
    }

bool CLOTRecord::IsTorch()
    {
    return (BMDT.value & fIsTorch) != 0;
    }

void CLOTRecord::IsTorch(bool value)
    {
    SETBIT(BMDT.value, fIsTorch, value);
    }

bool CLOTRecord::IsTail()
    {
    return (BMDT.value & fIsTail) != 0;
    }

void CLOTRecord::IsTail(bool value)
    {
    SETBIT(BMDT.value, fIsTail, value);
    }

bool CLOTRecord::IsHideRings()
    {
    return (BMDT.value & fIsHideRings) != 0;
    }

void CLOTRecord::IsHideRings(bool value)
    {
    SETBIT(BMDT.value, fIsHideRings, value);
    }

bool CLOTRecord::IsHideAmulets()
    {
    return (BMDT.value & fIsHideAmulets) != 0;
    }

void CLOTRecord::IsHideAmulets(bool value)
    {
    SETBIT(BMDT.value, fIsHideAmulets, value);
    }

bool CLOTRecord::IsNonPlayable()
    {
    return (BMDT.value & fIsNonPlayable) != 0;
    }

void CLOTRecord::IsNonPlayable(bool value)
    {
    SETBIT(BMDT.value, fIsNonPlayable, value);
    }

bool CLOTRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((BMDT.value & Mask) == Mask) : ((BMDT.value & Mask) != 0);
    }

void CLOTRecord::SetFlagMask(uint32_t Mask)
    {
    BMDT.value = Mask;
    }

uint32_t CLOTRecord::GetType()
    {
    return REV32(CLOT);
    }

char * CLOTRecord::GetStrType()
    {
    return "CLOT";
    }

int32_t CLOTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(BMDT):
                BMDT.Read(buffer, subSize);
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
            case REV32(MOD2):
                MOD2.Load();
                MOD2->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO2B):
                MOD2.Load();
                MOD2->MODB.Read(buffer, subSize);
                break;
            case REV32(MO2T):
                MOD2.Load();
                MOD2->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Load();
                MOD3->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO3B):
                MOD3.Load();
                MOD3->MODB.Read(buffer, subSize);
                break;
            case REV32(MO3T):
                MOD3.Load();
                MOD3->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD4):
                MOD4.Load();
                MOD4->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MO4B):
                MOD4.Load();
                MOD4->MODB.Read(buffer, subSize);
                break;
            case REV32(MO4T):
                MOD4.Load();
                MOD4->MODT.Read(buffer, subSize, CompressedOnDisk);
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
                printer("  CLOT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CLOTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    SCRI.Unload();
    ENAM.Unload();
    ANAM.Unload();
    BMDT.Unload();
    MODL.Unload();
    MOD2.Unload();
    ICON.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICO2.Unload();
    DATA.Unload();
    return 1;
    }

int32_t CLOTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(SCRI);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(BMDT);
    MODL.Write(writer);
    if(MOD2.IsLoaded())
        {
        MOD2->WRITEAS(MODL,MOD2);
        MOD2->WRITEAS(MODB,MO2B);
        MOD2->WRITEAS(MODT,MO2T);
        }
    WRITE(ICON);
    if(MOD3.IsLoaded())
        {
        MOD3->WRITEAS(MODL,MOD3);
        MOD3->WRITEAS(MODB,MO3B);
        MOD3->WRITEAS(MODT,MO3T);
        }
    if(MOD4.IsLoaded())
        {
        MOD4->WRITEAS(MODL,MOD4);
        MOD4->WRITEAS(MODB,MO4B);
        MOD4->WRITEAS(MODT,MO4T);
        }
    WRITE(ICO2);
    WRITE(DATA);
    return -1;
    }

bool CLOTRecord::operator ==(const CLOTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            BMDT == other.BMDT &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            ICON.equalsi(other.ICON) &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            ICO2.equalsi(other.ICO2) &&
            DATA == other.DATA);
    }

bool CLOTRecord::operator !=(const CLOTRecord &other) const
    {
    return !(*this == other);
    }

bool CLOTRecord::equals(Record *other)
    {
    return *this == *(CLOTRecord *)other;
    }
}