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
#include "FACTRecord.h"

namespace FNV
{
bool sortRNAM::operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const
    {
    return lhs->RNAM.value < rhs->RNAM.value;
    }

FACTRecord::FACTDATA::FACTDATA():
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

FACTRecord::FACTDATA::~FACTDATA()
    {
    //
    }

bool FACTRecord::FACTDATA::operator ==(const FACTDATA &other) const
    {
    return (flags == other.flags);
    }

bool FACTRecord::FACTDATA::operator !=(const FACTDATA &other) const
    {
    return !(*this == other);
    }

void FACTRecord::FACTRNAM::Write(FileWriter &writer)
    {
    WRITE(RNAM);
    WRITE(MNAM);
    WRITE(FNAM);
    WRITE(INAM);
    }

bool FACTRecord::FACTRNAM::operator ==(const FACTRNAM &other) const
    {
    return (RNAM == other.RNAM &&
            MNAM.equals(other.MNAM) &&
            FNAM.equals(other.FNAM) &&
            INAM.equalsi(other.INAM));
    }

bool FACTRecord::FACTRNAM::operator !=(const FACTRNAM &other) const
    {
    return !(*this == other);
    }

FACTRecord::FACTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

FACTRecord::FACTRecord(FACTRecord *srcRecord):
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
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    CNAM = srcRecord->CNAM;
    RNAM = srcRecord->RNAM;
    WMI1 = srcRecord->WMI1;
    return;
    }

FACTRecord::~FACTRecord()
    {
    //
    }

bool FACTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < XNAM.value.size(); ListIndex++)
        op.Accept(XNAM.value[ListIndex]->faction);
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);

    return op.Stop();
    }

bool FACTRecord::IsHiddenFromPC()
    {
    return (DATA.value.flags & fIsHiddenFromPC) != 0;
    }

void FACTRecord::IsHiddenFromPC(bool value)
    {
    SETBIT(DATA.value.flags, fIsHiddenFromPC, value);
    }

bool FACTRecord::IsEvil()
    {
    return (DATA.value.flags & fIsEvil) != 0;
    }

void FACTRecord::IsEvil(bool value)
    {
    SETBIT(DATA.value.flags, fIsEvil, value);
    }

bool FACTRecord::IsSpecialCombat()
    {
    return (DATA.value.flags & fIsSpecialCombat) != 0;
    }

void FACTRecord::IsSpecialCombat(bool value)
    {
    SETBIT(DATA.value.flags, fIsSpecialCombat, value);
    }

bool FACTRecord::IsTrackCrime()
    {
    return (DATA.value.flags & fIsTrackCrime) != 0;
    }

void FACTRecord::IsTrackCrime(bool value)
    {
    SETBIT(DATA.value.flags, fIsTrackCrime, value);
    }

bool FACTRecord::IsAllowSell()
    {
    return (DATA.value.flags & fIsAllowSell) != 0;
    }

void FACTRecord::IsAllowSell(bool value)
    {
    SETBIT(DATA.value.flags, fIsAllowSell, value);
    }

bool FACTRecord::IsFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void FACTRecord::SetFlagMask(uint16_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t FACTRecord::GetType()
    {
    return REV32(FACT);
    }

char * FACTRecord::GetStrType()
    {
    return "FACT";
    }

int32_t FACTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->RNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FNAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(INAM):
                if(RNAM.value.size() == 0)
                    RNAM.value.push_back(new FACTRNAM);
                RNAM.value.back()->INAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(WMI1):
                WMI1.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  FACT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t FACTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    XNAM.Unload();
    DATA.Unload();
    CNAM.Unload();
    RNAM.Unload();
    WMI1.Unload();
    return 1;
    }

int32_t FACTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    XNAM.Write(REV32(XNAM), writer, true);
    WRITE(DATA);
    WRITE(CNAM);
    RNAM.Write(writer);
    WRITE(WMI1);
    return -1;
    }

bool FACTRecord::operator ==(const FACTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            CNAM == other.CNAM &&
            WMI1 == other.WMI1 &&
            XNAM == other.XNAM &&
            RNAM == other.RNAM);
    }

bool FACTRecord::operator !=(const FACTRecord &other) const
    {
    return !(*this == other);
    }

bool FACTRecord::equals(Record *other)
    {
    return *this == *(FACTRecord *)other;
    }
}