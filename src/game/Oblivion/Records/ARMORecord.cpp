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
#include "ARMORecord.h"

namespace Ob
{
ARMORecord::ARMODATA::ARMODATA():
    strength(0),
    value(0),
    health(0),
    weight(0.0f)
    {
    //
    }

ARMORecord::ARMODATA::~ARMODATA()
    {
    //
    }

bool ARMORecord::ARMODATA::operator ==(const ARMODATA &other) const
    {
    return (strength == other.strength &&
            value == other.value &&
            health == other.health &&
            AlmostEqual(weight,other.weight,2));
    }

bool ARMORecord::ARMODATA::operator !=(const ARMODATA &other) const
    {
    return !(*this == other);
    }

ARMORecord::ARMORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ARMORecord::ARMORecord(ARMORecord *srcRecord):
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

ARMORecord::~ARMORecord()
    {
    //
    }

bool ARMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool ARMORecord::IsHead()
    {
    return (BMDT.value & fIsHead) != 0;
    }

void ARMORecord::IsHead(bool value)
    {
    SETBIT(BMDT.value, fIsHead, value);
    }

bool ARMORecord::IsHair()
    {
    return (BMDT.value & fIsHair) != 0;
    }

void ARMORecord::IsHair(bool value)
    {
    SETBIT(BMDT.value, fIsHair, value);
    }

bool ARMORecord::IsUpperBody()
    {
    return (BMDT.value & fIsUpperBody) != 0;
    }

void ARMORecord::IsUpperBody(bool value)
    {
    SETBIT(BMDT.value, fIsUpperBody, value);
    }

bool ARMORecord::IsLowerBody()
    {
    return (BMDT.value & fIsLowerBody) != 0;
    }

void ARMORecord::IsLowerBody(bool value)
    {
    SETBIT(BMDT.value, fIsLowerBody, value);
    }

bool ARMORecord::IsHand()
    {
    return (BMDT.value & fIsHand) != 0;
    }

void ARMORecord::IsHand(bool value)
    {
    SETBIT(BMDT.value, fIsHand, value);
    }

bool ARMORecord::IsFoot()
    {
    return (BMDT.value & fIsFoot) != 0;
    }

void ARMORecord::IsFoot(bool value)
    {
    SETBIT(BMDT.value, fIsFoot, value);
    }

bool ARMORecord::IsRightRing()
    {
    return (BMDT.value & fIsRightRing) != 0;
    }

void ARMORecord::IsRightRing(bool value)
    {
    SETBIT(BMDT.value, fIsRightRing, value);
    }

bool ARMORecord::IsLeftRing()
    {
    return (BMDT.value & fIsLeftRing) != 0;
    }

void ARMORecord::IsLeftRing(bool value)
    {
    SETBIT(BMDT.value, fIsLeftRing, value);
    }

bool ARMORecord::IsAmulet()
    {
    return (BMDT.value & fIsAmulet) != 0;
    }

void ARMORecord::IsAmulet(bool value)
    {
    SETBIT(BMDT.value, fIsAmulet, value);
    }

bool ARMORecord::IsWeapon()
    {
    return (BMDT.value & fIsWeapon) != 0;
    }

void ARMORecord::IsWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsWeapon, value);
    }

bool ARMORecord::IsBackWeapon()
    {
    return (BMDT.value & fIsBackWeapon) != 0;
    }

void ARMORecord::IsBackWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsBackWeapon, value);
    }

bool ARMORecord::IsSideWeapon()
    {
    return (BMDT.value & fIsSideWeapon) != 0;
    }

void ARMORecord::IsSideWeapon(bool value)
    {
    SETBIT(BMDT.value, fIsSideWeapon, value);
    }

bool ARMORecord::IsQuiver()
    {
    return (BMDT.value & fIsQuiver) != 0;
    }

void ARMORecord::IsQuiver(bool value)
    {
    SETBIT(BMDT.value, fIsQuiver, value);
    }

bool ARMORecord::IsShield()
    {
    return (BMDT.value & fIsShield) != 0;
    }

void ARMORecord::IsShield(bool value)
    {
    SETBIT(BMDT.value, fIsShield, value);
    }

bool ARMORecord::IsTorch()
    {
    return (BMDT.value & fIsTorch) != 0;
    }

void ARMORecord::IsTorch(bool value)
    {
    SETBIT(BMDT.value, fIsTorch, value);
    }

bool ARMORecord::IsTail()
    {
    return (BMDT.value & fIsTail) != 0;
    }

void ARMORecord::IsTail(bool value)
    {
    SETBIT(BMDT.value, fIsTail, value);
    }

bool ARMORecord::IsHideRings()
    {
    return (BMDT.value & fIsHideRings) != 0;
    }

void ARMORecord::IsHideRings(bool value)
    {
    SETBIT(BMDT.value, fIsHideRings, value);
    }

bool ARMORecord::IsHideAmulets()
    {
    return (BMDT.value & fIsHideAmulets) != 0;
    }

void ARMORecord::IsHideAmulets(bool value)
    {
    SETBIT(BMDT.value, fIsHideAmulets, value);
    }

bool ARMORecord::IsNonPlayable()
    {
    return (BMDT.value & fIsNonPlayable) != 0;
    }

void ARMORecord::IsNonPlayable(bool value)
    {
    SETBIT(BMDT.value, fIsNonPlayable, value);
    }

bool ARMORecord::IsHeavyArmor()
    {
    return (BMDT.value & fIsHeavyArmor) != 0;
    }

void ARMORecord::IsHeavyArmor(bool value)
    {
    SETBIT(BMDT.value, fIsHeavyArmor, value);
    }

bool ARMORecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((BMDT.value & Mask) == Mask) : ((BMDT.value & Mask) != 0);
    }

void ARMORecord::SetFlagMask(uint32_t Mask)
    {
    BMDT.value = Mask;
    }

uint32_t ARMORecord::GetType()
    {
    return REV32(ARMO);
    }

char * ARMORecord::GetStrType()
    {
    return "ARMO";
    }

int32_t ARMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                printer("  ARMO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t ARMORecord::Unload()
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

int32_t ARMORecord::WriteRecord(FileWriter &writer)
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

bool ARMORecord::operator ==(const ARMORecord &other) const
    {
    return (SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            BMDT == other.BMDT &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            ICO2.equalsi(other.ICO2) &&
            MODL == other.MODL &&
            MOD2 == other.MOD2 &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4);
    }

bool ARMORecord::operator !=(const ARMORecord &other) const
    {
    return !(*this == other);
    }

bool ARMORecord::equals(Record *other)
    {
    return *this == *(ARMORecord *)other;
    }
}