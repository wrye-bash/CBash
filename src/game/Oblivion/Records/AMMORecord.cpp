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
#include "AMMORecord.h"

namespace Ob
{
AMMORecord::AMMODATA::AMMODATA():
    speed(0.0f),
    flags(0),
    value(0),
    weight(0.0f),
    damage(0)
    {
    memset(&unused1[0], 0xCD, sizeof(unused1));
    }

AMMORecord::AMMODATA::~AMMODATA()
    {
    //
    }

bool AMMORecord::AMMODATA::operator ==(const AMMODATA &other) const
    {
    return (AlmostEqual(speed,other.speed,2) &&
            flags == other.flags &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2) &&
            damage == other.damage);
    }

bool AMMORecord::AMMODATA::operator !=(const AMMODATA &other) const
    {
    return !(*this == other);
    }

AMMORecord::AMMORecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

AMMORecord::AMMORecord(AMMORecord *srcRecord):
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
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    ENAM = srcRecord->ENAM;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

AMMORecord::~AMMORecord()
    {
    //
    }

bool AMMORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    return op.Stop();
    }

bool AMMORecord::IsNotNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void AMMORecord::IsNotNormalWeapon(bool value)
    {
    SETBIT(DATA.value.flags, fIsNotNormalWeapon, value);
    }

bool AMMORecord::IsNotNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) != 0;
    }

void AMMORecord::IsNotNormal(bool value)
    {
    SETBIT(DATA.value.flags, fIsNotNormalWeapon, value);
    }

bool AMMORecord::IsNormalWeapon()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void AMMORecord::IsNormalWeapon(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool AMMORecord::IsNormal()
    {
    return (DATA.value.flags & fIsNotNormalWeapon) == 0;
    }

void AMMORecord::IsNormal(bool value)
    {
    DATA.value.flags = value ? DATA.value.flags & ~fIsNotNormalWeapon : DATA.value.flags | fIsNotNormalWeapon;
    }

bool AMMORecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void AMMORecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t AMMORecord::GetType()
    {
    return REV32(AMMO);
    }

char * AMMORecord::GetStrType()
    {
    return "AMMO";
    }

int32_t AMMORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                printer("  AMMO: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t AMMORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    ENAM.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

int32_t AMMORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(ENAM);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool AMMORecord::operator ==(const AMMORecord &other) const
    {
    return (ENAM == other.ENAM &&
            ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool AMMORecord::operator !=(const AMMORecord &other) const
    {
    return !(*this == other);
    }

bool AMMORecord::equals(Record *other)
    {
    return *this == *(AMMORecord *)other;
    }
}