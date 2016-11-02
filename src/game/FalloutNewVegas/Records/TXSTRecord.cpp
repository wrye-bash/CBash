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
#include "TXSTRecord.h"

namespace FNV
{
TXSTRecord::TXSTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TXSTRecord::TXSTRecord(TXSTRecord *srcRecord):
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
    OBND = srcRecord->OBND;

    TX00 = srcRecord->TX00;
    TX01 = srcRecord->TX01;
    TX02 = srcRecord->TX02;
    TX03 = srcRecord->TX03;
    TX04 = srcRecord->TX04;
    TX05 = srcRecord->TX05;

    DODT = srcRecord->DODT;
    DNAM = srcRecord->DNAM;
    return;
    }

TXSTRecord::~TXSTRecord()
    {
    //
    }

bool TXSTRecord::IsNoSpecularMap()
    {
    if(!DNAM.IsLoaded()) return false;
    return (*DNAM.value & fIsNoSpecularMap) != 0;
    }

void TXSTRecord::IsNoSpecularMap(bool value)
    {
    if(!DNAM.IsLoaded()) return;
    *DNAM.value = value ? (*DNAM.value | fIsNoSpecularMap) : (*DNAM.value & ~fIsNoSpecularMap);
    }

bool TXSTRecord::IsFlagMask(uint16_t Mask, bool Exact)
    {
    if(!DNAM.IsLoaded()) return false;
    return Exact ? ((*DNAM.value & Mask) == Mask) : ((*DNAM.value & Mask) != 0);
    }

void TXSTRecord::SetFlagMask(uint16_t Mask)
    {
    DNAM.Load();
    *DNAM.value = Mask;
    }

bool TXSTRecord::IsObjectParallax()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsParallax) != 0 : false;
    }

void TXSTRecord::IsObjectParallax(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsParallax) : (DODT->flags & ~fIsParallax);
    }

bool TXSTRecord::IsObjectAlphaBlending()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaBlending) != 0 : false;
    }

void TXSTRecord::IsObjectAlphaBlending(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaBlending) : (DODT->flags & ~fIsAlphaBlending);
    }

bool TXSTRecord::IsObjectAlphaTesting()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaTesting) != 0 : false;
    }

void TXSTRecord::IsObjectAlphaTesting(bool value)
    {
    if(!DODT.IsLoaded()) return;
    DODT->flags = value ? (DODT->flags | fIsAlphaTesting) : (DODT->flags & ~fIsAlphaTesting);
    }

bool TXSTRecord::IsObjectFlagMask(uint8_t Mask, bool Exact)
    {
    if(!DODT.IsLoaded()) return false;
    return Exact ? ((DODT->flags & Mask) == Mask) : ((DODT->flags & Mask) != 0);
    }

void TXSTRecord::SetObjectFlagMask(uint8_t Mask)
    {
    DODT.Load();
    DODT->flags = Mask;
    }

uint32_t TXSTRecord::GetType()
    {
    return REV32(TXST);
    }

char * TXSTRecord::GetStrType()
    {
    return "TXST";
    }

int32_t TXSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(TX00):
                TX00.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX01):
                TX01.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX02):
                TX02.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX03):
                TX03.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX04):
                TX04.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX05):
                TX05.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DODT):
                DODT.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  TXST: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t TXSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    TX00.Unload();
    TX01.Unload();
    TX02.Unload();
    TX03.Unload();
    TX04.Unload();
    TX05.Unload();
    DODT.Unload();
    DNAM.Unload();
    return 1;
    }

int32_t TXSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(TX00);
    WRITE(TX01);
    WRITE(TX02);
    WRITE(TX03);
    WRITE(TX04);
    WRITE(TX05);
    WRITE(DODT);
    WRITE(DNAM);
    return -1;
    }

bool TXSTRecord::operator ==(const TXSTRecord &other) const
    {
    return (OBND == other.OBND &&
            DODT == other.DODT &&
            DNAM == other.DNAM &&
            EDID.equalsi(other.EDID) &&
            TX00.equalsi(other.TX00) &&
            TX01.equalsi(other.TX01) &&
            TX02.equalsi(other.TX02) &&
            TX03.equalsi(other.TX03) &&
            TX04.equalsi(other.TX04) &&
            TX05.equalsi(other.TX05)
            );
    }

bool TXSTRecord::operator !=(const TXSTRecord &other) const
    {
    return !(*this == other);
    }

bool TXSTRecord::equals(Record *other)
    {
    return *this == *(TXSTRecord *)other;
    }
}