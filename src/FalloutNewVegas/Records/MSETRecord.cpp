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
        op.Accept(HNAM.value);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);

    return op.Stop();
    }

bool MSETRecord::IsDayOuter()
    {
    if (!ONAM.IsLoaded()) return false;
    return (PNAM.value & fIsDayOuter) != 0;
    }

void MSETRecord::IsDayOuter(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsDayOuter, value);
    }

bool MSETRecord::IsDayMiddle()
    {
    if (!PNAM.IsLoaded()) return false;
    return (PNAM.value & fIsDayMiddle) != 0;
    }

void MSETRecord::IsDayMiddle(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsDayMiddle, value);
    }

bool MSETRecord::IsDayInner()
    {
    if (!PNAM.IsLoaded()) return false;
    return (PNAM.value & fIsDayInner) != 0;
    }

void MSETRecord::IsDayInner(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsDayInner, value);
    }

bool MSETRecord::IsNightOuter()
    {
    if (!PNAM.IsLoaded()) return false;
    return (PNAM.value & fIsNightOuter) != 0;
    }

void MSETRecord::IsNightOuter(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsNightOuter, value);
    }

bool MSETRecord::IsNightMiddle()
    {
    if (!PNAM.IsLoaded()) return false;
    return (PNAM.value & fIsNightMiddle) != 0;
    }

void MSETRecord::IsNightMiddle(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsNightMiddle, value);
    }

bool MSETRecord::IsNightInner()
    {
    if (!PNAM.IsLoaded()) return false;
    return (PNAM.value & fIsNightInner) != 0;
    }

void MSETRecord::IsNightInner(bool value)
    {
    if (!PNAM.IsLoaded()) return;
    SETBIT(PNAM.value, fIsNightInner, value);
    }

bool MSETRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!PNAM.IsLoaded()) return false;
    return Exact ? ((PNAM.value & Mask) == Mask) : ((PNAM.value & Mask) != 0);
    }

void MSETRecord::SetFlagMask(uint8_t Mask)
    {
    PNAM.Load();
    PNAM.value = Mask;
    }

bool MSETRecord::IsNone()
    {
    if (!NAM1.IsLoaded()) return false;
    return (NAM1.value == eNone);
    }

bool MSETRecord::IsBattle()
    {
    if (!NAM1.IsLoaded()) return false;
    return (NAM1.value == eBattle);
    }

bool MSETRecord::IsLocation()
    {
    if (!NAM1.IsLoaded()) return false;
    return (NAM1.value == eLocation);
    }

bool MSETRecord::IsDungeon()
    {
    if (!NAM1.IsLoaded()) return false;
    return (NAM1.value == eDungeon);
    }

bool MSETRecord::IsIncidential()
    {
    if (!NAM1.IsLoaded()) return false;
    return (NAM1.value == eIncidential);
    }

bool MSETRecord::IsType(uint32_t Type)
    {
    if (!NAM1.IsLoaded()) return false;
    return NAM1.value == Type;
    }

void MSETRecord::SetType(uint32_t Type)
    {
    NAM1.Load();
    NAM1.value = Type;
    }

uint32_t MSETRecord::GetType()
    {
    return REV32(MSET);
    }

char * MSETRecord::GetStrType()
    {
    return "MSET";
    }

int32_t MSETRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM3):
                NAM3.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM4):
                NAM4.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM5):
                NAM5.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM6):
                NAM6.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM7):
                NAM7.Read(buffer, subSize, CompressedOnDisk);
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
                DATA.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t MSETRecord::Unload()
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

int32_t MSETRecord::WriteRecord(FileWriter &writer)
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

bool MSETRecord::equals(Record *other)
    {
    return *this == *(MSETRecord *)other;
    }
}