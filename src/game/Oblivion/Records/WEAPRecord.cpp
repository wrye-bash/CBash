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
#include "WEAPRecord.h"

namespace Ob
{
WEAPRecord::WEAPDATA::WEAPDATA():
    weaponType(0),
    speed(0.0f),
    reach(0.0f),
    flags(0),
    value(0),
    health(0),
    weight(0.0f),
    damage(0)
    {
    //
    }

WEAPRecord::WEAPDATA::~WEAPDATA()
    {
    //
    }

bool WEAPRecord::WEAPDATA::operator ==(const WEAPDATA &other) const
    {
    return (weaponType == other.weaponType &&
            AlmostEqual(speed,other.speed,2) &&
            AlmostEqual(reach,other.reach,2) &&
            flags == other.flags &&
            value == other.value &&
            health == other.health &&
            AlmostEqual(weight,other.weight,2) &&
            damage == other.damage);
    }

bool WEAPRecord::WEAPDATA::operator !=(const WEAPDATA &other) const
    {
    return !(*this == other);
    }

WEAPRecord::WEAPRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WEAPRecord::WEAPRecord(WEAPRecord *srcRecord):Record()
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
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    }

WEAPRecord::~WEAPRecord()
    {
    //
    }

bool WEAPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool WEAPRecord::IsNotNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormalWeapon(bool value)
    {
    SETBIT(DATA.value.flags, fIsNotNormalWeapon, value);
    }

bool WEAPRecord::IsNotNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void WEAPRecord::IsNotNormal(bool value)
    {
    SETBIT(DATA.value.flags, fIsNotNormalWeapon, value);
    }

bool WEAPRecord::IsNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void WEAPRecord::IsNormalWeapon(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool WEAPRecord::IsNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void WEAPRecord::IsNormal(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool WEAPRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void WEAPRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool WEAPRecord::IsBlade1Hand()
    {
    return (DATA.value.weaponType == eBlade1Hand);
    }

void WEAPRecord::IsBlade1Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlade1Hand;
    else if(IsBlade1Hand())
        DATA.value.weaponType = eBlade2Hand;
    }

bool WEAPRecord::IsBlade2Hand()
    {
    return (DATA.value.weaponType == eBlade2Hand);
    }

void WEAPRecord::IsBlade2Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlade2Hand;
    else if(IsBlade2Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBlunt1Hand()
    {
    return (DATA.value.weaponType == eBlunt1Hand);
    }

void WEAPRecord::IsBlunt1Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlunt1Hand;
    else if(IsBlunt1Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBlunt2Hand()
    {
    return (DATA.value.weaponType == eBlunt2Hand);
    }

void WEAPRecord::IsBlunt2Hand(bool value)
    {
    if(value)
        DATA.value.weaponType = eBlunt2Hand;
    else if(IsBlunt2Hand())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsStaff()
    {
    return (DATA.value.weaponType == eStaff);
    }

void WEAPRecord::IsStaff(bool value)
    {
    if(value)
        DATA.value.weaponType = eStaff;
    else if(IsStaff())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsBow()
    {
    return (DATA.value.weaponType == eBow);
    }

void WEAPRecord::IsBow(bool value)
    {
    if(value)
        DATA.value.weaponType = eBow;
    else if(IsBow())
        DATA.value.weaponType = eBlade1Hand;
    }

bool WEAPRecord::IsType(uint32_t Type)
    {
    return (DATA.value.weaponType == Type);
    }

void WEAPRecord::SetType(uint32_t Type)
    {
    DATA.value.weaponType = Type;
    }

uint32_t WEAPRecord::GetType()
    {
    return REV32(WEAP);
    }

char * WEAPRecord::GetStrType()
    {
    return "WEAP";
    }

int32_t WEAPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WEAP: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t WEAPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    ENAM.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

int32_t WEAPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool WEAPRecord::operator ==(const WEAPRecord &other) const
    {
    return (ANAM == other.ANAM &&
            SCRI == other.SCRI &&
            ENAM == other.ENAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool WEAPRecord::operator !=(const WEAPRecord &other) const
    {
    return !(*this == other);
    }

bool WEAPRecord::equals(Record *other)
    {
    return *this == *(WEAPRecord *)other;
    }
}