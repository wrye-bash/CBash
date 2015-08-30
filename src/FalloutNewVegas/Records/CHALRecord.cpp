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
#include "CHALRecord.h"

namespace FNV
{
CHALRecord::CHALDATA::CHALDATA():
    challengeType(eKillFromList),
    threshold(0),
    flags(0),
    interval(0)
    {
    memset(&var1, 0, sizeof(var1));
    memset(&var2, 0, sizeof(var2));
    memset(&var3, 0, sizeof(var3));
    }

CHALRecord::CHALDATA::~CHALDATA()
    {
    //
    }

bool CHALRecord::CHALDATA::operator ==(const CHALDATA &other) const
    {
    return (challengeType == other.challengeType &&
            threshold == other.threshold &&
            flags == other.flags &&
            interval == other.interval &&
            memcmp(&var1, &other.var1, sizeof(var1)) == 0 &&
            memcmp(&var2, &other.var2, sizeof(var2)) == 0 &&
            memcmp(&var3, &other.var3, sizeof(var3)) == 0
            );
    }

bool CHALRecord::CHALDATA::operator !=(const CHALDATA &other) const
    {
    return !(*this == other);
    }

CHALRecord::CHALRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CHALRecord::CHALRecord(CHALRecord *srcRecord):
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
    SCRI = srcRecord->SCRI;
    DESC = srcRecord->DESC;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    XNAM = srcRecord->XNAM;
    return;
    }

CHALRecord::~CHALRecord()
    {
    //
    }

bool CHALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(XNAM.IsLoaded())
        op.Accept(XNAM.value);

    return op.Stop();
    }

bool CHALRecord::IsStartDisabled()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsStartDisabled) != 0;
    }

void CHALRecord::IsStartDisabled(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsStartDisabled, value);
    }

bool CHALRecord::IsRecurring()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsRecurring) != 0;
    }

void CHALRecord::IsRecurring(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsRecurring, value);
    }

bool CHALRecord::IsShowZeroProgress()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsShowZeroProgress) != 0;
    }

void CHALRecord::IsShowZeroProgress(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsShowZeroProgress, value);
    }

bool CHALRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA->flags & Mask) == Mask) : ((DATA->flags & Mask) != 0);
    }

void CHALRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.Load();
    DATA->flags = Mask;
    }

bool CHALRecord::IsKillFromList()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eKillFromList);
    }

bool CHALRecord::IsKillFormID()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eKillFormID);
    }

bool CHALRecord::IsKillInCategory()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eKillInCategory);
    }

bool CHALRecord::IsHitEnemy()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eHitEnemy);
    }

bool CHALRecord::IsDiscoverMapMarker()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eDiscoverMapMarker);
    }

bool CHALRecord::IsUseItem()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eUseItem);
    }

bool CHALRecord::IsGetItem()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eGetItem);
    }

bool CHALRecord::IsUseSkill()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eUseSkill);
    }

bool CHALRecord::IsDoDamage()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eDoDamage);
    }

bool CHALRecord::IsUseItemFromList()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eUseItemFromList);
    }

bool CHALRecord::IsGetItemFromList()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eGetItemFromList);
    }

bool CHALRecord::IsMiscStat()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->challengeType == eMiscStat);
    }

bool CHALRecord::IsType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->challengeType == Type;
    }

void CHALRecord::SetType(uint8_t Type)
    {
    DATA.Load();
    DATA->challengeType = Type;
    }

uint32_t CHALRecord::GetType()
    {
    return REV32(CHAL);
    }

char * CHALRecord::GetStrType()
    {
    return "CHAL";
    }

int32_t CHALRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t CHALRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    SCRI.Unload();
    DESC.Unload();
    DATA.Unload();
    SNAM.Unload();
    XNAM.Unload();
    return 1;
    }

int32_t CHALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(SCRI);
    WRITE(DESC);
    WRITE(DATA);
    WRITE(SNAM);
    WRITE(XNAM);

    return -1;
    }

bool CHALRecord::operator ==(const CHALRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            SCRI == other.SCRI &&
            DESC.equals(other.DESC) &&
            DATA == other.DATA &&
            SNAM == other.SNAM &&
            XNAM == other.XNAM);
    }

bool CHALRecord::operator !=(const CHALRecord &other) const
    {
    return !(*this == other);
    }

bool CHALRecord::equals(Record *other)
    {
    return *this == *(CHALRecord *)other;
    }
}