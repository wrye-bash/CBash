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
#include "RCCTRecord.h"

namespace FNV
{
RCCTRecord::RCCTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RCCTRecord::RCCTRecord(RCCTRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    return;
    }

RCCTRecord::~RCCTRecord()
    {
    //
    }

bool RCCTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool RCCTRecord::IsSubcategory()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA.value & fIsSubcategory) != 0;
    }

void RCCTRecord::IsSubcategory(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA.value, fIsSubcategory, value);
    }

bool RCCTRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void RCCTRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.Load();
    DATA.value = Mask;
    }

uint32_t RCCTRecord::GetType()
    {
    return REV32(RCCT);
    }

char * RCCTRecord::GetStrType()
    {
    return "RCCT";
    }

int32_t RCCTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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

int32_t RCCTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t RCCTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    return -1;
    }

bool RCCTRecord::operator ==(const RCCTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA);
    }

bool RCCTRecord::operator !=(const RCCTRecord &other) const
    {
    return !(*this == other);
    }

bool RCCTRecord::equals(Record *other)
    {
    return *this == *(RCCTRecord *)other;
    }
}