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
#include "SOUNRecord.h"

namespace Ob
{
SOUNRecord::SOUNSNDX::SOUNSNDX():
    minDistance(0),
    maxDistance(0),
    freqAdjustment(0),
    unused1(0),
    flags(0),
    staticAtten(0),
    stopTime(0),
    startTime(0)
    {
    memset(&unused2[0], 0x00, sizeof(unused2));
    }

SOUNRecord::SOUNSNDX::~SOUNSNDX()
    {
    //
    }

bool SOUNRecord::SOUNSNDX::operator ==(const SOUNSNDX &other) const
    {
    return (minDistance == other.minDistance &&
            maxDistance == other.maxDistance &&
            freqAdjustment == other.freqAdjustment &&
            flags == other.flags &&
            staticAtten == other.staticAtten &&
            stopTime == other.stopTime &&
            startTime == other.startTime);
    }

bool SOUNRecord::SOUNSNDX::operator !=(const SOUNSNDX &other) const
    {
    return !(*this == other);
    }

SOUNRecord::SOUNRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SOUNRecord::SOUNRecord(SOUNRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FNAM = srcRecord->FNAM;
    SNDX = srcRecord->SNDX;
    }

SOUNRecord::~SOUNRecord()
    {
    //
    }

bool SOUNRecord::IsRandomFrequencyShift()
    {
    return (SNDX.value.flags & fIsRandomFrequencyShift) != 0;
    }

void SOUNRecord::IsRandomFrequencyShift(bool value)
    {
    SETBIT(SNDX.value.flags, fIsRandomFrequencyShift, value);
    }

bool SOUNRecord::IsPlayAtRandom()
    {
    return (SNDX.value.flags & fIsPlayAtRandom) != 0;
    }

void SOUNRecord::IsPlayAtRandom(bool value)
    {
    SETBIT(SNDX.value.flags, fIsPlayAtRandom, value);
    }

bool SOUNRecord::IsEnvironmentIgnored()
    {
    return (SNDX.value.flags & fIsEnvironmentIgnored) != 0;
    }

void SOUNRecord::IsEnvironmentIgnored(bool value)
    {
    SETBIT(SNDX.value.flags, fIsEnvironmentIgnored, value);
    }

bool SOUNRecord::IsRandomLocation()
    {
    return (SNDX.value.flags & fIsRandomLocation) != 0;
    }

void SOUNRecord::IsRandomLocation(bool value)
    {
    SETBIT(SNDX.value.flags, fIsRandomLocation, value);
    }

bool SOUNRecord::IsLoop()
    {
    return (SNDX.value.flags & fIsLoop) != 0;
    }

void SOUNRecord::IsLoop(bool value)
    {
    SETBIT(SNDX.value.flags, fIsLoop, value);
    }

bool SOUNRecord::IsMenuSound()
    {
    return (SNDX.value.flags & fIsMenuSound) != 0;
    }

void SOUNRecord::IsMenuSound(bool value)
    {
    SETBIT(SNDX.value.flags, fIsMenuSound, value);
    }

bool SOUNRecord::Is2D()
    {
    return (SNDX.value.flags & fIs2D) != 0;
    }

void SOUNRecord::Is2D(bool value)
    {
    SETBIT(SNDX.value.flags, fIs2D, value);
    }

bool SOUNRecord::Is360LFE()
    {
    return (SNDX.value.flags & fIs360LFE) != 0;
    }

void SOUNRecord::Is360LFE(bool value)
    {
    SETBIT(SNDX.value.flags, fIs360LFE, value);
    }

bool SOUNRecord::IsFlagMask(unsigned short Mask, bool Exact)
    {
    return Exact ? ((SNDX.value.flags & Mask) == Mask) : ((SNDX.value.flags & Mask) != 0);
    }

void SOUNRecord::SetFlagMask(unsigned short Mask)
    {
    SNDX.value.flags = Mask;
    }

uint32_t SOUNRecord::GetType()
    {
    return REV32(SOUN);
    }

char * SOUNRecord::GetStrType()
    {
    return "SOUN";
    }

int32_t SOUNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNDD):
            case REV32(SNDX):
                SNDX.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SOUN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SOUNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FNAM.Unload();
    SNDX.Unload();
    return 1;
    }

int32_t SOUNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FNAM);
    WRITE(SNDX);
    return -1;
    }

bool SOUNRecord::operator ==(const SOUNRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FNAM.equalsi(other.FNAM) &&
            SNDX == other.SNDX);
    }

bool SOUNRecord::operator !=(const SOUNRecord &other) const
    {
    return !(*this == other);
    }

bool SOUNRecord::equals(Record *other)
    {
    return *this == *(SOUNRecord *)other;
    }
}