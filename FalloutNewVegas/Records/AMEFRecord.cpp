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
#include "AMEFRecord.h"

namespace FNV
{
AMEFRecord::AMEFRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

AMEFRecord::AMEFRecord(AMEFRecord *srcRecord):
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

AMEFRecord::~AMEFRecord()
    {
    //
    }

bool AMEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool AMEFRecord::IsDamage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDamage);
    }

void AMEFRecord::IsDamage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDamage : eDummyDefault;
    }

bool AMEFRecord::IsDR()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDR);
    }

void AMEFRecord::IsDR(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDR : eDummyDefault;
    }

bool AMEFRecord::IsDT()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDT);
    }

void AMEFRecord::IsDT(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDT : eDummyDefault;
    }

bool AMEFRecord::IsSpread()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpread);
    }

void AMEFRecord::IsSpread(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpread : eDummyDefault;
    }

bool AMEFRecord::IsCondition()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eCondition);
    }

void AMEFRecord::IsCondition(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eCondition : eDummyDefault;
    }

bool AMEFRecord::IsFatigue()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFatigue);
    }

void AMEFRecord::IsFatigue(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFatigue : eDummyDefault;
    }

bool AMEFRecord::IsModType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void AMEFRecord::SetModType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool AMEFRecord::IsAdd()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAdd);
    }

void AMEFRecord::IsAdd(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAdd : eDummyDefault;
    }

bool AMEFRecord::IsMultiply()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMultiply);
    }

void AMEFRecord::IsMultiply(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMultiply : eDummyDefault;
    }

bool AMEFRecord::IsSubtract()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSubtract);
    }

void AMEFRecord::IsSubtract(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSubtract : eDummyDefault;
    }

bool AMEFRecord::IsOpType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void AMEFRecord::SetOpType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 AMEFRecord::GetType()
    {
    return REV32(AMEF);
    }

STRING AMEFRecord::GetStrType()
    {
    return "AMEF";
    }

SINT32 AMEFRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  AMEF: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 AMEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 AMEFRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    return -1;
    }

bool AMEFRecord::operator ==(const AMEFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA);
    }

bool AMEFRecord::operator !=(const AMEFRecord &other) const
    {
    return !(*this == other);
    }

bool AMEFRecord::equals(const Record *other) const
    {
    return *this == *(AMEFRecord *)other;
    }
}