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
 *  Jacob "Lojack" Lojewski
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
#include "COLLRecord.h"
#include "common/ModFile.h"
#include "../TES5Record.h"
#include "../TES5File.h"

namespace Sk {

COLLRecord::COLLRecord(unsigned char *_recData) :
    TES5Record(_recData)
{
    //
}

COLLRecord::COLLRecord(COLLRecord *srcRecord) :
    TES5Record((TES5Record *)srcRecord)
{
    if (srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    DESC = srcRecord->DESC;
    BNAM = srcRecord->BNAM;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    MNAM = srcRecord->MNAM;
    CNAM = srcRecord->CNAM;
}

COLLRecord::~COLLRecord()
{
    //
}

bool COLLRecord::IsTriggerVolume() const
{
    return (GNAM.value & fIsTriggerVolume) != 0;
}

void COLLRecord::IsTriggerVolume(bool value)
{
    SETBIT(GNAM.value, fIsTriggerVolume, value);
}

bool COLLRecord::IsSensor() const
{
    return (GNAM.value & fIsSensor) != 0;
}

void COLLRecord::IsSensor(bool value)
{
    SETBIT(GNAM.value, fIsSensor, value);
}

bool COLLRecord::IsNavmeshObstacle() const
{
    return (GNAM.value & fIsNavmeshObstacle) != 0;
}

void COLLRecord::IsNavmeshObstacle(bool value)
{
    SETBIT(GNAM.value, fIsNavmeshObstacle, value);
}

bool COLLRecord::IsFlagMask(uint32_t Mask, bool Exact)
{
    return Exact ? (GNAM.value & Mask) == Mask : (GNAM.value & Mask) != 0;
}

void COLLRecord::SetFlagMask(uint32_t Mask)
{
    GNAM.value = Mask;
}

bool COLLRecord::VisitFormIDs(FormIDOp &op)
{
    if (!IsLoaded())
        return false;

    for (uint32_t i = 0; i < CNAM.value.size(); ++i)
        op.Accept(CNAM.value[i]);

    return op.Stop();
}

uint32_t COLLRecord::GetType()
{
    return REV32(COLL);
}

char * COLLRecord::GetStrType()
{
    return "COLL";
}

int32_t COLLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
{
    uint32_t subType = 0;
    uint32_t subSize = 0;
    auto LookupStrings = GetParentMod()->LookupStrings();
    while(buffer < end_buffer)
    {
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
        case REV32(DESC):
            DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
            break;
        case REV32(BNAM):
            BNAM.Read(buffer, subSize);
            break;
        case REV32(FNAM):
            FNAM.Read(buffer, subSize);
            break;
        case REV32(GNAM):
            GNAM.Read(buffer, subSize);
            break;
        case REV32(MNAM):
            MNAM.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(INTV):
            // Skip
            buffer += subSize;
            break;
        case REV32(CNAM):
            CNAM.Read(buffer, subSize);
            break;
        default:
            //printer("Filename = %s\n", FileName);
            printer("  APPA: %08X - Unknown subType = %04x\n", formID, subType);
            CBASH_CHUNK_DEBUG
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t COLLRecord::Unload()
{
    IsLoaded(false);
    IsChanged(false);
    EDID.Unload();
    DESC.Unload();
    BNAM.Unload();
    FNAM.Unload();
    GNAM.Unload();
    MNAM.Unload();
    CNAM.Unload();
    return 1;
}

int32_t COLLRecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(DESC);
    WRITE(BNAM);
    WRITE(FNAM);
    WRITE(GNAM);
    WRITE(MNAM);
    WRITE(CNAM);
    return -1;
}

bool COLLRecord::operator ==(const COLLRecord &other) const
{
    return (EDID.equalsi(other.EDID) &&
            DESC.equals(other.DESC) &&
            BNAM == other.BNAM &&
            FNAM == other.FNAM &&
            GNAM == other.GNAM &&
            MNAM.equalsi(other.MNAM) &&
            CNAM == other.CNAM
            );
}

bool COLLRecord::operator !=(const COLLRecord &other) const
    {
        return !(*this == other);
    }

bool COLLRecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const COLLRecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk
