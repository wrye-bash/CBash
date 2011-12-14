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
#include "CSNORecord.h"

namespace FNV
{
CSNORecord::CSNORecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CSNORecord::CSNORecord(CSNORecord *srcRecord):
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
    if(srcRecord->MODL.IsLoaded())
        {
        MODL.Load();
        MODL->MODL = srcRecord->MODL->MODL;
        }
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    if(srcRecord->ICON.IsLoaded())
        {
        ICON.Load();
        ICON->ICON = srcRecord->ICON->ICON;
        }
    if(srcRecord->ICO2.IsLoaded())
        {
        ICO2.Load();
        ICO2->ICO2 = srcRecord->ICO2->ICO2;
        }
    return;
    }

CSNORecord::~CSNORecord()
    {
    //
    }

bool CSNORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(DATA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(DATA->value);

    return op.Stop();
    }

bool CSNORecord::IsDealerStayOnSoft17()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDealerStayOnSoft17) != 0;
    }

void CSNORecord::IsDealerStayOnSoft17(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDealerStayOnSoft17) : (Dummy->flags & ~fIsDealerStayOnSoft17);
    }

bool CSNORecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CSNORecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CSNORecord::GetType()
    {
    return REV32(CSNO);
    }

STRING CSNORecord::GetStrType()
    {
    return "CSNO";
    }

SINT32 CSNORecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize);
                break;
            case REV32(MODL):
                MODL.Read(buffer, subSize);
                break;
            case REV32(MOD2):
                MOD2.Read(buffer, subSize);
                break;
            case REV32(MOD3):
                MOD3.Read(buffer, subSize);
                break;
            case REV32(MOD4):
                MOD4.Read(buffer, subSize);
                break;
            case REV32(ICON):
                ICON.Load();
                ICON->ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICO2):
                ICO2.Load();
                ICO2->ICO2.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CSNO: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CSNORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    MODL.Unload();
    MODL.Unload();
    MOD2.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICON.Unload();
    ICO2.Unload();
    return 1;
    }

SINT32 CSNORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    if(MODL.IsLoaded())
        {
        if(MODL->MODL.IsLoaded())
            SaveHandler.writeSubRecord(REV32(MODL), MODL->MODL.value, MODL->MODL.GetSize());

        }

    WRITE(MODL);
    WRITE(MOD2);
    WRITE(MOD3);
    WRITE(MOD4);

    if(ICON.IsLoaded())
        {
        if(ICON->ICON.IsLoaded())
            SaveHandler.writeSubRecord(REV32(ICON), ICON->ICON.value, ICON->ICON.GetSize());

        }

    if(ICO2.IsLoaded())
        {
        if(ICO2->ICO2.IsLoaded())
            SaveHandler.writeSubRecord(REV32(ICO2), ICO2->ICO2.value, ICO2->ICO2.GetSize());

        }

    return -1;
    }

bool CSNORecord::operator ==(const CSNORecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            MODL == other.MODL &&
            MODL.equalsi(other.MODL) &&
            MOD2.equalsi(other.MOD2) &&
            MOD3.equalsi(other.MOD3) &&
            MOD4.equalsi(other.MOD4) &&
            ICON == other.ICON &&
            ICO2 == other.ICO2);
    }

bool CSNORecord::operator !=(const CSNORecord &other) const
    {
    return !(*this == other);
    }

bool CSNORecord::equals(const Record *other) const
    {
    return *this == *(CSNORecord *)other;
    }
}