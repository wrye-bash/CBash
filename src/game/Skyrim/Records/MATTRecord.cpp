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
 * Ethatron
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
#include "MATTRecord.h"

namespace Sk
{

MATTRecord::MATTCNAM::MATTCNAM() :
    red(0.0), green(0.0), blue(0.0)
{
    //
}

MATTRecord::MATTCNAM::~MATTCNAM()
{

}

bool MATTRecord::MATTCNAM::operator == (const MATTCNAM &other) const
{
    return (AlmostEqual(red, other.red, 2) &&
            AlmostEqual(green, other.green, 2) &&
            AlmostEqual(blue, other.blue, 2)
            );
}

bool MATTRecord::MATTCNAM::operator != (const MATTCNAM &other) const
{
    return !(*this == other);
}

bool MATTRecord::IsStairMaterial() const
{
    return (FNAM.value & fIsStairMaterial) != 0;
}

void MATTRecord::IsStairMaterial(bool value)
{
    SETBIT(FNAM.value, fIsStairMaterial, value);
}

bool MATTRecord::IsArrowsStick() const
{
    return (FNAM.value & fIsArrowsStick) != 0;
}

void MATTRecord::IsArrowsStick(bool value)
{
    SETBIT(FNAM.value, fIsArrowsStick, value);
}

bool MATTRecord::IsFlagMask(uint32_t Mask, bool Exact)
{
    return Exact ? (FNAM.value & Mask) == Mask : (FNAM.value & Mask) != 0;
}

void MATTRecord::SetFlagMask(uint32_t Mask)
{
    FNAM.value = Mask;
}

MATTRecord::MATTRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
    //
    }

MATTRecord::MATTRecord(MATTRecord *srcRecord):
    TES5Record((TES5Record *)srcRecord)
    {
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    PNAM = srcRecord->PNAM;
    MNAM = srcRecord->MNAM;
    CNAM = srcRecord->CNAM;
    BNAM = srcRecord->BNAM;
    FNAM = srcRecord->FNAM;
    HNAM = srcRecord->HNAM;
    }

MATTRecord::~MATTRecord()
    {
    //
    }

uint32_t MATTRecord::GetType()
    {
    return REV32(MATT);
    }

char * MATTRecord::GetStrType()
    {
    return "MATT";
    }

int32_t MATTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(EDID): // MaterialInsect
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PNAM): // Material Parent
                PNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM): // Material Name
                MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CNAM): // Havok Display Color
                CNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM): // Bouyancy
                BNAM.Read(buffer, subSize);
                break;
            case REV32(FNAM): // Flags
                FNAM.Read(buffer, subSize);
                break;
            case REV32(HNAM): // Havok Impact Data Set
                HNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  MATT: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t MATTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    PNAM.Unload();
    MNAM.Unload();
    CNAM.Unload();
    BNAM.Unload();
    FNAM.Unload();
    HNAM.Unload();
    return 1;
    }

int32_t MATTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(PNAM);
    WRITE(MNAM);
    WRITE(CNAM);
    WRITE(BNAM);
    WRITE(FNAM);
    WRITE(HNAM);
    return -1;
    }

bool MATTRecord::operator ==(const MATTRecord &other) const
    {
    return (MNAM.equalsi(other.MNAM) &&
            PNAM == other.PNAM &&
            CNAM == other.CNAM &&
            BNAM == other.BNAM &&
            FNAM == other.FNAM &&
            HNAM == other.HNAM
            );
    }

bool MATTRecord::operator !=(const MATTRecord &other) const
    {
    return !(*this == other);
    }

bool MATTRecord::equals(Record *other)
{
    try
    {
        return *this == *reinterpret_cast<MATTRecord *>(other);
    }
    catch (...)
    {
        return false;
    }
}

} // namespace Sk
