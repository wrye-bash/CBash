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
#include "../TES5Record.h"
#include "SHOURecord.h"
#include "common/ModFile.h"

namespace Sk {

SHOURecord::SHOUSNAM::SHOUSNAM() :
    word(0),
    spell(0),
    recovery(0.0)
{
    //
}

SHOURecord::SHOUSNAM::~SHOUSNAM()
{
    //
}

bool SHOURecord::SHOUSNAM::operator == (const SHOUSNAM &other) const
{
    return (word == other.word &&
            spell == other.spell &&
            AlmostEqual(recovery, other.recovery, 2)
            );
}

bool SHOURecord::SHOUSNAM::operator != (const SHOUSNAM &other) const
{
    return !(*this == other);
}

SHOURecord::SHOURecord(unsigned char *_recData) :
    TES5Record(_recData)
{
    //
}

SHOURecord::SHOURecord(SHOURecord *srcRecord) :
    TES5Record((TES5Record *)srcRecord)
{
    if (srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MDOB = srcRecord->MDOB;
    SNAM = srcRecord->SNAM;
}

SHOURecord::~SHOURecord()
{
    //
}

bool SHOURecord::VisitFormIDs(FormIDOp &op)
{
    if (!IsLoaded())
        return false;

    if (MDOB.IsLoaded())
        op.Accept(MDOB.value);

    for (uint32_t x = 0; x < SNAM.value.size(); ++x)
    {
        op.Accept(SNAM.value[x].word);
        op.Accept(SNAM.value[x].spell);
    }

    return op.Stop();
}


uint32_t SHOURecord::GetType()
{
    return REV32(SHOU);
}

char * SHOURecord::GetStrType()
{
    return "SHOU";
}

int32_t SHOURecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
{
    uint32_t subType = 0;
    uint32_t subSize = 0;
    StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
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
        case REV32(FULL):
            FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
            break;
        case REV32(MDOB):
            MDOB.Read(buffer, subSize);
            break;
        case REV32(SNAM):
            SNAM.Read(buffer, subSize);
            break;
        default:
            //printer("Filename = %s\n", FileName);
            printer("  AACT: %08X - Unknown subType = %04x\n", formID, subType);
            CBASH_CHUNK_DEBUG
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t SHOURecord::Unload()
{
    IsLoaded(false);
    IsChanged(false);
    EDID.Unload();
    FULL.Unload();
    MDOB.Unload();
    SNAM.Unload();
    return 1;
}

int32_t SHOURecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(FULL);
    WRITE(MDOB);
    WRITE(SNAM);
    return -1;
}

bool SHOURecord::operator ==(const SHOURecord &other) const
{
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MDOB == other.MDOB &&
            SNAM == other.SNAM
            );
}

bool SHOURecord::operator !=(const SHOURecord &other) const
{
    return !(*this == other);
}

bool SHOURecord::equals(Record *other)
{
    try
    {
        return *this == *dynamic_cast<const SHOURecord *>(other);
    }
    catch(...)
    {
        return false;
    }
}

} // namespace Sk
