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
#include "IMGSRecord.h"

namespace FNV
{
IMGSRecord::IMGSRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IMGSRecord::IMGSRecord(IMGSRecord *srcRecord):
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

IMGSRecord::~IMGSRecord()
    {
    //
    }

bool IMGSRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool IMGSRecord::IsSaturation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsSaturation) != 0;
    }

void IMGSRecord::IsSaturation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsSaturation) : (Dummy->flags & ~fIsSaturation);
    }

bool IMGSRecord::IsContrast()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsContrast) != 0;
    }

void IMGSRecord::IsContrast(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsContrast) : (Dummy->flags & ~fIsContrast);
    }

bool IMGSRecord::IsTint()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsTint) != 0;
    }

void IMGSRecord::IsTint(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsTint) : (Dummy->flags & ~fIsTint);
    }

bool IMGSRecord::IsBrightness()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsBrightness) != 0;
    }

void IMGSRecord::IsBrightness(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsBrightness) : (Dummy->flags & ~fIsBrightness);
    }

bool IMGSRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void IMGSRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 IMGSRecord::GetType()
    {
    return REV32(IMGS);
    }

STRING IMGSRecord::GetStrType()
    {
    return "IMGS";
    }

SINT32 IMGSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
    {
    UINT32 subType = 0;
    UINT32 subSize = 0;
    while(buffer < end_buffer){
        subType = *(UINT32 *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(UINT32 *)buffer;
                buffer += 4;
                subType = *(UINT32 *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(UINT16 *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IMGS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 IMGSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    return 1;
    }

SINT32 IMGSRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);

    return -1;
    }

bool IMGSRecord::operator ==(const IMGSRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM);
    }

bool IMGSRecord::operator !=(const IMGSRecord &other) const
    {
    return !(*this == other);
    }

bool IMGSRecord::equals(const Record *other) const
    {
    return *this == *(IMGSRecord *)other;
    }
}