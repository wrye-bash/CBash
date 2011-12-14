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
#include "MSETRecord.h"

namespace FNV
{
MSETRecord::MSETRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

MSETRecord::MSETRecord(MSETRecord *srcRecord):
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
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    NAM3 = srcRecord->NAM3;
    NAM4 = srcRecord->NAM4;
    NAM5 = srcRecord->NAM5;
    NAM6 = srcRecord->NAM6;
    NAM7 = srcRecord->NAM7;
    NAM8 = srcRecord->NAM8;
    NAM9 = srcRecord->NAM9;
    NAM0 = srcRecord->NAM0;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;
    CNAM = srcRecord->CNAM;
    JNAM = srcRecord->JNAM;
    KNAM = srcRecord->KNAM;
    LNAM = srcRecord->LNAM;
    MNAM = srcRecord->MNAM;
    NNAM = srcRecord->NNAM;
    ONAM = srcRecord->ONAM;
    PNAM = srcRecord->PNAM;
    DNAM = srcRecord->DNAM;
    ENAM = srcRecord->ENAM;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    HNAM = srcRecord->HNAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    return;
    }

MSETRecord::~MSETRecord()
    {
    //
    }

bool MSETRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(HNAM.IsLoaded())
        op.Accept(HNAM->value);
    if(INAM.IsLoaded())
        op.Accept(INAM->value);

    return op.Stop();
    }

bool MSETRecord::IsDayOuter()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayOuter) != 0;
    }

void MSETRecord::IsDayOuter(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDayOuter) : (Dummy->flags & ~fIsDayOuter);
    }

bool MSETRecord::IsDayMiddle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayMiddle) != 0;
    }

void MSETRecord::IsDayMiddle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDayMiddle) : (Dummy->flags & ~fIsDayMiddle);
    }

bool MSETRecord::IsDayInner()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDayInner) != 0;
    }

void MSETRecord::IsDayInner(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDayInner) : (Dummy->flags & ~fIsDayInner);
    }

bool MSETRecord::IsNightOuter()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightOuter) != 0;
    }

void MSETRecord::IsNightOuter(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNightOuter) : (Dummy->flags & ~fIsNightOuter);
    }

bool MSETRecord::IsNightMiddle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightMiddle) != 0;
    }

void MSETRecord::IsNightMiddle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNightMiddle) : (Dummy->flags & ~fIsNightMiddle);
    }

bool MSETRecord::IsNightInner()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNightInner) != 0;
    }

void MSETRecord::IsNightInner(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNightInner) : (Dummy->flags & ~fIsNightInner);
    }

bool MSETRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void MSETRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool MSETRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void MSETRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool MSETRecord::IsBattle()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eBattle);
    }

void MSETRecord::IsBattle(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eBattle : eDummyDefault;
    }

bool MSETRecord::IsLocation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLocation);
    }

void MSETRecord::IsLocation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLocation : eDummyDefault;
    }

bool MSETRecord::IsDungeon()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDungeon);
    }

void MSETRecord::IsDungeon(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDungeon : eDummyDefault;
    }

bool MSETRecord::IsIncidential()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eIncidential);
    }

void MSETRecord::IsIncidential(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eIncidential : eDummyDefault;
    }

bool MSETRecord::IsType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void MSETRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 MSETRecord::GetType()
    {
    return REV32(MSET);
    }

STRING MSETRecord::GetStrType()
    {
    return "MSET";
    }

SINT32 MSETRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize);
                break;
            case REV32(NAM8):
                NAM8.Read(buffer, subSize);
                break;
            case REV32(NAM9):
                NAM9.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                NAM0.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(JNAM):
                JNAM.Read(buffer, subSize);
                break;
            case REV32(KNAM):
                KNAM.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(NNAM):
                NNAM.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  MSET: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 MSETRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    NAM1.Unload();
    NAM2.Unload();
    NAM3.Unload();
    NAM4.Unload();
    NAM5.Unload();
    NAM6.Unload();
    NAM7.Unload();
    NAM8.Unload();
    NAM9.Unload();
    NAM0.Unload();
    ANAM.Unload();
    BNAM.Unload();
    CNAM.Unload();
    JNAM.Unload();
    KNAM.Unload();
    LNAM.Unload();
    MNAM.Unload();
    NNAM.Unload();
    ONAM.Unload();
    PNAM.Unload();
    DNAM.Unload();
    ENAM.Unload();
    FNAM.Unload();
    GNAM.Unload();
    HNAM.Unload();
    INAM.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 MSETRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(NAM3);
    WRITE(NAM4);
    WRITE(NAM5);
    WRITE(NAM6);
    WRITE(NAM7);
    WRITE(NAM8);
    WRITE(NAM9);
    WRITE(NAM0);
    WRITE(ANAM);
    WRITE(BNAM);
    WRITE(CNAM);
    WRITE(JNAM);
    WRITE(KNAM);
    WRITE(LNAM);
    WRITE(MNAM);
    WRITE(NNAM);
    WRITE(ONAM);
    WRITE(PNAM);
    WRITE(DNAM);
    WRITE(ENAM);
    WRITE(FNAM);
    WRITE(GNAM);
    WRITE(HNAM);
    WRITE(INAM);
    WRITE(DATA);

    return -1;
    }

bool MSETRecord::operator ==(const MSETRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1 == other.NAM1 &&
            NAM2.equalsi(other.NAM2) &&
            NAM3.equalsi(other.NAM3) &&
            NAM4.equalsi(other.NAM4) &&
            NAM5.equalsi(other.NAM5) &&
            NAM6.equalsi(other.NAM6) &&
            NAM7.equalsi(other.NAM7) &&
            NAM8 == other.NAM8 &&
            NAM9 == other.NAM9 &&
            NAM0 == other.NAM0 &&
            ANAM == other.ANAM &&
            BNAM == other.BNAM &&
            CNAM == other.CNAM &&
            JNAM == other.JNAM &&
            KNAM == other.KNAM &&
            LNAM == other.LNAM &&
            MNAM == other.MNAM &&
            NNAM == other.NNAM &&
            ONAM == other.ONAM &&
            PNAM == other.PNAM &&
            DNAM == other.DNAM &&
            ENAM == other.ENAM &&
            FNAM == other.FNAM &&
            GNAM == other.GNAM &&
            HNAM == other.HNAM &&
            INAM == other.INAM &&
            DATA == other.DATA);
    }

bool MSETRecord::operator !=(const MSETRecord &other) const
    {
    return !(*this == other);
    }

bool MSETRecord::equals(const Record *other) const
    {
    return *this == *(MSETRecord *)other;
    }
}