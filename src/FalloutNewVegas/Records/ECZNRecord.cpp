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
#include "ECZNRecord.h"

namespace FNV
{
ECZNRecord::ECZNDATA::ECZNDATA():
    owner(0),
    rank(0),
    minLevel(0),
    flags(0),
    unused1(0)
    {
    //
    }

ECZNRecord::ECZNDATA::~ECZNDATA()
    {
    //
    }

bool ECZNRecord::ECZNDATA::operator ==(const ECZNDATA &other) const
    {
    return (owner == other.owner &&
            rank == other.rank &&
            minLevel == other.minLevel &&
            flags == other.flags
            // && unused1 == other.unused1  // unused - so probably should effect the compare?
            );
    }

bool ECZNRecord::ECZNDATA::operator !=(const ECZNDATA &other) const
    {
    return !(*this == other);
    }

ECZNRecord::ECZNRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ECZNRecord::ECZNRecord(ECZNRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    return;
    }

ECZNRecord::~ECZNRecord()
    {
    //
    }

bool ECZNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }

bool ECZNRecord::IsNeverResets()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsNeverResets) != 0;
    }

void ECZNRecord::IsNeverResets(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsNeverResets, value);
    }

bool ECZNRecord::IsMatchPCBelowMinLevel()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsMatchPCBelowMinLevel) != 0;
    }

void ECZNRecord::IsMatchPCBelowMinLevel(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsMatchPCBelowMinLevel, value);
    }

bool ECZNRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA->flags & Mask) == Mask) : ((DATA->flags & Mask) != 0);
    }

void ECZNRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.Load();
    DATA->flags = Mask;
    }

uint32_t ECZNRecord::GetType()
    {
    return REV32(ECZN);
    }

char * ECZNRecord::GetStrType()
    {
    return "ECZN";
    }

int32_t ECZNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t ECZNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DATA.Unload();
    return 1;
    }

int32_t ECZNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DATA);

    return -1;
    }

bool ECZNRecord::operator ==(const ECZNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA);
    }

bool ECZNRecord::operator !=(const ECZNRecord &other) const
    {
    return !(*this == other);
    }

bool ECZNRecord::equals(Record *other)
    {
    return *this == *(ECZNRecord *)other;
    }
}