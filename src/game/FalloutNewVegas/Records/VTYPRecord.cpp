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
#include "VTYPRecord.h"

namespace FNV
{
VTYPRecord::VTYPRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

VTYPRecord::VTYPRecord(VTYPRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    return;
    }

VTYPRecord::~VTYPRecord()
    {
    //
    }

bool VTYPRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool VTYPRecord::IsAllowDefaultDialog()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM.value & fIsAllowDefaultDialog) != 0;
    }

void VTYPRecord::IsAllowDefaultDialog(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM.value, fIsAllowDefaultDialog, value);
    }

bool VTYPRecord::IsFemale()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM.value & fIsFemale) != 0;
    }

void VTYPRecord::IsFemale(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM.value, fIsFemale, value);
    }

bool VTYPRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!DNAM.IsLoaded()) return false;
    return Exact ? ((DNAM.value & Mask) == Mask) : ((DNAM.value & Mask) != 0);
    }

void VTYPRecord::SetFlagMask(uint8_t Mask)
    {
    DNAM.Load();
    DNAM.value = Mask;
    }

uint32_t VTYPRecord::GetType()
    {
    return REV32(VTYP);
    }

char * VTYPRecord::GetStrType()
    {
    return "VTYP";
    }

int32_t VTYPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t VTYPRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    return 1;
    }

int32_t VTYPRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);

    return -1;
    }

bool VTYPRecord::operator ==(const VTYPRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM);
    }

bool VTYPRecord::operator !=(const VTYPRecord &other) const
    {
    return !(*this == other);
    }

bool VTYPRecord::equals(Record *other)
    {
    return *this == *(VTYPRecord *)other;
    }
}