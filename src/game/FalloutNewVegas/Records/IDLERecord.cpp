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
#include "IDLERecord.h"

namespace FNV
{
IDLERecord::IDLEDATA::IDLEDATA():
    group(0),
    minLooping(0),
    maxLooping(0),
    unused1(0),
    replayDelay(0),
    flags(0),
    unused2(0)
    {
    //
    }

IDLERecord::IDLEDATA::~IDLEDATA()
    {
    //
    }

bool IDLERecord::IDLEDATA::operator ==(const IDLEDATA &other) const
    {
    return (group == other.group &&
            minLooping == other.minLooping &&
            maxLooping == other.maxLooping &&
            replayDelay == other.replayDelay &&
            flags == other.flags);
    }

bool IDLERecord::IDLEDATA::operator !=(const IDLEDATA &other) const
    {
    return !(*this == other);
    }

IDLERecord::IDLERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IDLERecord::IDLERecord(IDLERecord *srcRecord):
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
    MODL = srcRecord->MODL;
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

IDLERecord::~IDLERecord()
    {
    //
    }

bool IDLERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(uint32_t ListIndex = 0; ListIndex < ANAM.value.size(); ListIndex++)
        op.Accept(ANAM.value[ListIndex]);

    return op.Stop();
    }

bool IDLERecord::IsNoAttacking()
    {
    return (DATA.value.flags & fIsNoAttacking) != 0;
    }

void IDLERecord::IsNoAttacking(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoAttacking, value);
    }

bool IDLERecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void IDLERecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool IDLERecord::IsIdle()
    {
    return ((DATA.value.group & ~0xC0) == eIdle);
    }

void IDLERecord::IsIdle(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    else if(IsIdle())
        DATA.value.group = DATA.value.group & 0xC0 | eMovement;
    }

bool IDLERecord::IsMovement()
    {
    return ((DATA.value.group & ~0xC0) == eMovement);
    }

void IDLERecord::IsMovement(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eMovement;
    else if(IsMovement())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsLeftArm()
    {
    return ((DATA.value.group & ~0xC0) == eLeftArm);
    }

void IDLERecord::IsLeftArm(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eLeftArm;
    else if(IsLeftArm())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsLeftHand()
    {
    return ((DATA.value.group & ~0xC0) == eLeftHand);
    }

void IDLERecord::IsLeftHand(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eLeftHand;
    else if(IsLeftHand())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeapon()
    {
    return ((DATA.value.group & ~0xC0) == eWeapon);
    }

void IDLERecord::IsWeapon(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeapon;
    else if(IsWeapon())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeaponUp()
    {
    return ((DATA.value.group & ~0xC0) == eWeaponUp);
    }

void IDLERecord::IsWeaponUp(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeaponUp;
    else if(IsWeaponUp())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWeaponDown()
    {
    return ((DATA.value.group & ~0xC0) == eWeaponDown);
    }

void IDLERecord::IsWeaponDown(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWeaponDown;
    else if(IsWeaponDown())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsSpecialIdle()
    {
    return ((DATA.value.group & ~0xC0) == eSpecialIdle);
    }

void IDLERecord::IsSpecialIdle(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eSpecialIdle;
    else if(IsLeftArm())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsWholeBody()
    {
    return ((DATA.value.group & ~0xC0) == eWholeBody);
    }

void IDLERecord::IsWholeBody(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eWholeBody;
    else if(IsWholeBody())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsUpperBody()
    {
    return ((DATA.value.group & ~0xC0) == eUpperBody);
    }

void IDLERecord::IsUpperBody(bool value)
    {
    if(value)
        DATA.value.group = DATA.value.group & 0xC0 | eUpperBody;
    else if(IsUpperBody())
        DATA.value.group = DATA.value.group & 0xC0 | eIdle;
    }

bool IDLERecord::IsType(uint8_t Type)
    {
    return ((DATA.value.group & ~0xC0) == (Type & ~0xC0));
    }

void IDLERecord::SetType(uint8_t Type)
    {
    DATA.value.group = DATA.value.group & 0xC0 | (Type & ~0xC0);
    }

bool IDLERecord::IsUnknown1()
    {
    return (DATA.value.group & fIsUnknown1) != 0;
    }

void IDLERecord::IsUnknown1(bool value)
    {
    SETBIT(DATA.value.group, fIsUnknown1, value);
    }

bool IDLERecord::IsNotReturnFile()
    {
    return (DATA.value.group & fIsNotReturnFile) != 0;
    }

void IDLERecord::IsNotReturnFile(bool value)
    {
    SETBIT(DATA.value.group, fIsNotReturnFile, value);
    }

bool IDLERecord::IsReturnFile()
    {
    return !(IsNotReturnFile());
    }

void IDLERecord::IsReturnFile(bool value)
    {
    IsNotReturnFile(!value);
    }

bool IDLERecord::IsIdleFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? (((DATA.value.group & 0xC0) & (Mask & 0xC0)) == Mask) : (((DATA.value.group & 0xC0) & (Mask & 0xC0)) != 0);
    }

void IDLERecord::SetIdleFlagMask(uint8_t Mask)
    {
    DATA.value.group = DATA.value.group & ~0xC0 | (Mask & 0xC0);
    }

uint32_t IDLERecord::GetType()
    {
    return REV32(IDLE);
    }

char * IDLERecord::GetStrType()
    {
    return "IDLE";
    }

int32_t IDLERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  IDLE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t IDLERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    MODL.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

int32_t IDLERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    MODL.Write(writer);
    CTDA.Write(writer, true);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool IDLERecord::operator ==(const IDLERecord &other) const
    {
    return (ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            CTDA == other.CTDA);
    }

bool IDLERecord::operator !=(const IDLERecord &other) const
    {
    return !(*this == other);
    }

bool IDLERecord::equals(Record *other)
    {
    return *this == *(IDLERecord *)other;
    }
}