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
#include "HAIRRecord.h"

namespace Ob
{
HAIRRecord::HAIRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

HAIRRecord::HAIRRecord(HAIRRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    }

HAIRRecord::~HAIRRecord()
    {
    //
    }

bool HAIRRecord::IsPlayable()
    {
    return (DATA.value & fIsPlayable) != 0;
    }

void HAIRRecord::IsPlayable(bool value)
    {
    SETBIT(DATA.value, fIsPlayable, value);
    }

bool HAIRRecord::IsNotMale()
    {
    return (DATA.value & fIsNotMale) != 0;
    }

void HAIRRecord::IsNotMale(bool value)
    {
    SETBIT(DATA.value, fIsNotMale, value);
    }

bool HAIRRecord::IsMale()
    {
    return !IsNotMale();
    }

void HAIRRecord::IsMale(bool value)
    {
    IsNotMale(!value);
    }

bool HAIRRecord::IsNotFemale()
    {
    return (DATA.value & fIsNotFemale) != 0;
    }

void HAIRRecord::IsNotFemale(bool value)
    {
    SETBIT(DATA.value, fIsNotFemale, value);
    }

bool HAIRRecord::IsFemale()
    {
    return !IsNotFemale();
    }

void HAIRRecord::IsFemale(bool value)
    {
    IsNotFemale(!value);
    }

bool HAIRRecord::IsFixedColor()
    {
    return (DATA.value & fIsFixedColor) != 0;
    }

void HAIRRecord::IsFixedColor(bool value)
    {
    SETBIT(DATA.value, fIsFixedColor, value);
    }

bool HAIRRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void HAIRRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value = Mask;
    }

uint32_t HAIRRecord::GetType()
    {
    return REV32(HAIR);
    }

char * HAIRRecord::GetStrType()
    {
    return "HAIR";
    }

int32_t HAIRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  HAIR: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t HAIRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    DATA.Unload();
    return 1;
    }

int32_t HAIRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(DATA);
    return -1;
    }

bool HAIRRecord::operator ==(const HAIRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            DATA == other.DATA);
    }

bool HAIRRecord::operator !=(const HAIRRecord &other) const
    {
    return !(*this == other);
    }

bool HAIRRecord::equals(Record *other)
    {
    return *this == *(HAIRRecord *)other;
    }
}