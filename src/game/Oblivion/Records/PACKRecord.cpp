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
#include "PACKRecord.h"

namespace Ob
{
PACKRecord::PACKPKDT::PACKPKDT():
    flags(0),
    aiType(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

PACKRecord::PACKPKDT::~PACKPKDT()
    {
    //
    }

bool PACKRecord::PACKPKDT::operator ==(const PACKPKDT &other) const
    {
    return (flags == other.flags &&
            aiType == other.aiType);
    }

bool PACKRecord::PACKPKDT::operator !=(const PACKPKDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPLDT::PACKPLDT():
    locType(0),
    locId(0),
    locRadius(0)
    {
    //
    }

PACKRecord::PACKPLDT::~PACKPLDT()
    {
    //
    }

bool PACKRecord::PACKPLDT::operator ==(const PACKPLDT &other) const
    {
    return (locType == other.locType &&
            locId == other.locId &&
            locRadius == other.locRadius);
    }

bool PACKRecord::PACKPLDT::operator !=(const PACKPLDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPSDT::PACKPSDT():
    month(0),
    day(0),
    date(0),
    time(0),
    duration(0)
    {
    //
    }

PACKRecord::PACKPSDT::~PACKPSDT()
    {
    //
    }

bool PACKRecord::PACKPSDT::operator ==(const PACKPSDT &other) const
    {
    return (month == other.month &&
            day == other.day &&
            date == other.date &&
            time == other.time &&
            duration == other.duration);
    }

bool PACKRecord::PACKPSDT::operator !=(const PACKPSDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKPTDT::PACKPTDT():
    targetType(0),
    targetId(0),
    targetCount(0)
    {
    //
    }

PACKRecord::PACKPTDT::~PACKPTDT()
    {
    //
    }

bool PACKRecord::PACKPTDT::operator ==(const PACKPTDT &other) const
    {
    return (targetType == other.targetType &&
            targetId == other.targetId &&
            targetCount == other.targetCount);
    }

bool PACKRecord::PACKPTDT::operator !=(const PACKPTDT &other) const
    {
    return !(*this == other);
    }

PACKRecord::PACKRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

PACKRecord::PACKRecord(PACKRecord *srcRecord):
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
    PKDT = srcRecord->PKDT;
    PLDT = srcRecord->PLDT;
    PSDT = srcRecord->PSDT;
    PTDT = srcRecord->PTDT;
    CTDA = srcRecord->CTDA;
    return;
    }

PACKRecord::~PACKRecord()
    {
    //
    }

bool PACKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(PLDT.IsLoaded() && (PLDT->locType < 2 || PLDT->locType == 4))
        op.Accept(PLDT->locId);

    if(PTDT.IsLoaded() && PTDT->targetType != 2)
        op.Accept(PTDT->targetId);

    for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

bool PACKRecord::IsOffersServices()
    {
    return (PKDT.value.flags & fIsOffersServices) != 0;
    }

void PACKRecord::IsOffersServices(bool value)
    {
    SETBIT(PKDT.value.flags, fIsOffersServices, value);
    }

bool PACKRecord::IsMustReachLocation()
    {
    return (PKDT.value.flags & fIsMustReachLocation) != 0;
    }

void PACKRecord::IsMustReachLocation(bool value)
    {
    SETBIT(PKDT.value.flags, fIsMustReachLocation, value);
    }

bool PACKRecord::IsMustComplete()
    {
    return (PKDT.value.flags & fIsMustComplete) != 0;
    }

void PACKRecord::IsMustComplete(bool value)
    {
    SETBIT(PKDT.value.flags, fIsMustComplete, value);
    }

bool PACKRecord::IsLockAtStart()
    {
    return (PKDT.value.flags & fIsLockAtStart) != 0;
    }

void PACKRecord::IsLockAtStart(bool value)
    {
    SETBIT(PKDT.value.flags, fIsLockAtStart, value);
    }

bool PACKRecord::IsLockAtEnd()
    {
    return (PKDT.value.flags & fIsLockAtEnd) != 0;
    }

void PACKRecord::IsLockAtEnd(bool value)
    {
    SETBIT(PKDT.value.flags, fIsLockAtEnd, value);
    }

bool PACKRecord::IsLockAtLocation()
    {
    return (PKDT.value.flags & fIsLockAtLocation) != 0;
    }

void PACKRecord::IsLockAtLocation(bool value)
    {
    SETBIT(PKDT.value.flags, fIsLockAtLocation, value);
    }

bool PACKRecord::IsUnlockAtStart()
    {
    return (PKDT.value.flags & fIsUnlockAtStart) != 0;
    }

void PACKRecord::IsUnlockAtStart(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUnlockAtStart, value);
    }

bool PACKRecord::IsUnlockAtEnd()
    {
    return (PKDT.value.flags & fIsUnlockAtEnd) != 0;
    }

void PACKRecord::IsUnlockAtEnd(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUnlockAtEnd, value);
    }

bool PACKRecord::IsUnlockAtLocation()
    {
    return (PKDT.value.flags & fIsUnlockAtLocation) != 0;
    }

void PACKRecord::IsUnlockAtLocation(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUnlockAtLocation, value);
    }

bool PACKRecord::IsContinueIfPcNear()
    {
    return (PKDT.value.flags & fIsContinueIfPcNear) != 0;
    }

void PACKRecord::IsContinueIfPcNear(bool value)
    {
    SETBIT(PKDT.value.flags, fIsContinueIfPcNear, value);
    }

bool PACKRecord::IsOncePerDay()
    {
    return (PKDT.value.flags & fIsOncePerDay) != 0;
    }

void PACKRecord::IsOncePerDay(bool value)
    {
    SETBIT(PKDT.value.flags, fIsOncePerDay, value);
    }

bool PACKRecord::IsSkipFallout()
    {
    return (PKDT.value.flags & fIsSkipFallout) != 0;
    }

void PACKRecord::IsSkipFallout(bool value)
    {
    SETBIT(PKDT.value.flags, fIsSkipFallout, value);
    }

bool PACKRecord::IsAlwaysRun()
    {
    return (PKDT.value.flags & fIsAlwaysRun) != 0;
    }

void PACKRecord::IsAlwaysRun(bool value)
    {
    SETBIT(PKDT.value.flags, fIsAlwaysRun, value);
    }

bool PACKRecord::IsAlwaysSneak()
    {
    return (PKDT.value.flags & fIsAlwaysSneak) != 0;
    }

void PACKRecord::IsAlwaysSneak(bool value)
    {
    SETBIT(PKDT.value.flags, fIsAlwaysSneak, value);
    }

bool PACKRecord::IsAllowSwimming()
    {
    return (PKDT.value.flags & fIsAllowSwimming) != 0;
    }

void PACKRecord::IsAllowSwimming(bool value)
    {
    SETBIT(PKDT.value.flags, fIsAllowSwimming, value);
    }

bool PACKRecord::IsAllowFalls()
    {
    return (PKDT.value.flags & fIsAllowFalls) != 0;
    }

void PACKRecord::IsAllowFalls(bool value)
    {
    SETBIT(PKDT.value.flags, fIsAllowFalls, value);
    }

bool PACKRecord::IsUnequipArmor()
    {
    return (PKDT.value.flags & fIsUnequipArmor) != 0;
    }

void PACKRecord::IsUnequipArmor(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUnequipArmor, value);
    }

bool PACKRecord::IsUnequipWeapons()
    {
    return (PKDT.value.flags & fIsUnequipWeapons) != 0;
    }

void PACKRecord::IsUnequipWeapons(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUnequipWeapons, value);
    }

bool PACKRecord::IsDefensiveCombat()
    {
    return (PKDT.value.flags & fIsDefensiveCombat) != 0;
    }

void PACKRecord::IsDefensiveCombat(bool value)
    {
    SETBIT(PKDT.value.flags, fIsDefensiveCombat, value);
    }

bool PACKRecord::IsUseHorse()
    {
    return (PKDT.value.flags & fIsUseHorse) != 0;
    }

void PACKRecord::IsUseHorse(bool value)
    {
    SETBIT(PKDT.value.flags, fIsUseHorse, value);
    }

bool PACKRecord::IsNoIdleAnims()
    {
    return (PKDT.value.flags & fIsNoIdleAnims) != 0;
    }

void PACKRecord::IsNoIdleAnims(bool value)
    {
    SETBIT(PKDT.value.flags, fIsNoIdleAnims, value);
    }

bool PACKRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((PKDT.value.flags & Mask) == Mask) : ((PKDT.value.flags & Mask) != 0);
    }

void PACKRecord::SetFlagMask(uint32_t Mask)
    {
    PKDT.value.flags = Mask;
    }

bool PACKRecord::IsAIFind()
    {
    return (PKDT.value.aiType == eAIFind);
    }

void PACKRecord::IsAIFind(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIFind;
    else if(IsAIFind())
        PKDT.value.aiType = eAIFollow;
    }

bool PACKRecord::IsAIFollow()
    {
    return (PKDT.value.aiType == eAIFollow);
    }

void PACKRecord::IsAIFollow(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIFollow;
    else if(IsAIFollow())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIEscort()
    {
    return (PKDT.value.aiType == eAIEscort);
    }

void PACKRecord::IsAIEscort(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIEscort;
    else if(IsAIEscort())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIEat()
    {
    return (PKDT.value.aiType == eAIEat);
    }

void PACKRecord::IsAIEat(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIEat;
    else if(IsAIEat())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAISleep()
    {
    return (PKDT.value.aiType == eAISleep);
    }

void PACKRecord::IsAISleep(bool value)
    {
    if(value)
        PKDT.value.aiType = eAISleep;
    else if(IsAISleep())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIWander()
    {
    return (PKDT.value.aiType == eAIWander);
    }

void PACKRecord::IsAIWander(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIWander;
    else if(IsAIWander())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAITravel()
    {
    return (PKDT.value.aiType == eAITravel);
    }

void PACKRecord::IsAITravel(bool value)
    {
    if(value)
        PKDT.value.aiType = eAITravel;
    else if(IsAIFollow())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIAccompany()
    {
    return (PKDT.value.aiType == eAIAccompany);
    }

void PACKRecord::IsAIAccompany(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIAccompany;
    else if(IsAIAccompany())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIUseItemAt()
    {
    return (PKDT.value.aiType == eAIUseItemAt);
    }

void PACKRecord::IsAIUseItemAt(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIUseItemAt;
    else if(IsAIUseItemAt())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIAmbush()
    {
    return (PKDT.value.aiType == eAIAmbush);
    }

void PACKRecord::IsAIAmbush(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIAmbush;
    else if(IsAIAmbush())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIFleeNotCombat()
    {
    return (PKDT.value.aiType == eAIFleeNotCombat);
    }

void PACKRecord::IsAIFleeNotCombat(bool value)
    {
    if(value)
        PKDT.value.aiType = eAIFleeNotCombat;
    else if(IsAIFleeNotCombat())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAICastMagic()
    {
    return (PKDT.value.aiType == eAICastMagic);
    }

void PACKRecord::IsAICastMagic(bool value)
    {
    if(value)
        PKDT.value.aiType = eAICastMagic;
    else if(IsAICastMagic())
        PKDT.value.aiType = eAIFind;
    }

bool PACKRecord::IsAIType(uint8_t Type)
    {
    return (PKDT.value.aiType == Type);
    }

void PACKRecord::SetAIType(uint8_t Type)
    {
    PKDT.value.aiType = Type;
    }

bool PACKRecord::IsLocNearReference()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocNearReference) : false;
    }

void PACKRecord::IsLocNearReference(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocNearReference;
    else if(IsLocNearReference())
        PLDT->locType = eLocInCell;
    }

bool PACKRecord::IsLocInCell()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocInCell) : false;
    }

void PACKRecord::IsLocInCell(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocInCell;
    else if(IsLocInCell())
        PLDT->locType = eLocNearReference;
    }

bool PACKRecord::IsLocNearCurrentLoc()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocNearCurrentLocation) : false;
    }

void PACKRecord::IsLocNearCurrentLoc(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocNearCurrentLocation;
    else if(IsLocNearCurrentLoc())
        PLDT->locType = eLocNearReference;
    }

bool PACKRecord::IsLocNearEditorLoc()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocNearEditorLocation) : false;
    }

void PACKRecord::IsLocNearEditorLoc(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocNearEditorLocation;
    else if(IsLocNearEditorLoc())
        PLDT->locType = eLocNearReference;
    }

bool PACKRecord::IsLocObjectID()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocObjectID) : false;
    }

void PACKRecord::IsLocObjectID(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocObjectID;
    else if(IsLocObjectID())
        PLDT->locType = eLocNearReference;
    }

bool PACKRecord::IsLocObjectType()
    {
    return PLDT.IsLoaded() ? (PLDT->locType == eLocObjectType) : false;
    }

void PACKRecord::IsLocObjectType(bool value)
    {
    if(!PLDT.IsLoaded()) return;
    if(value)
        PLDT->locType = eLocObjectType;
    else if(IsLocObjectType())
        PLDT->locType = eLocNearReference;
    }

bool PACKRecord::IsLocType(int32_t Type)
    {
    return PLDT.IsLoaded() ? (PLDT->locType == Type) : false;
    }

void PACKRecord::SetLocType(int32_t Type)
    {
    PLDT.Load();
    PLDT->locType = Type;
    }

bool PACKRecord::IsTargetReference()
    {
    return PTDT.IsLoaded() ? (PTDT->targetType == eTargetReference) : false;
    }

void PACKRecord::IsTargetReference(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    if(value)
        PTDT->targetType = eTargetReference;
    else if(IsTargetReference())
        PTDT->targetType = eTargetObjectID;
    }

bool PACKRecord::IsTargetObjectID()
    {
    return PTDT.IsLoaded() ? (PTDT->targetType == eTargetObjectID) : false;
    }

void PACKRecord::IsTargetObjectID(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    if(value)
        PTDT->targetType = eTargetObjectID;
    else if(IsTargetObjectID())
        PTDT->targetType = eTargetReference;
    }

bool PACKRecord::IsTargetObjectType()
    {
    return PTDT.IsLoaded() ? (PTDT->targetType == eTargetObjectType) : false;
    }

void PACKRecord::IsTargetObjectType(bool value)
    {
    if(!PTDT.IsLoaded()) return;
    if(value)
        PTDT->targetType = eTargetObjectType;
    else if(IsTargetObjectType())
        PTDT->targetType = eTargetReference;
    }

bool PACKRecord::IsTargetType(int32_t Type)
    {
    return PTDT.IsLoaded() ? (PTDT->targetType == Type) : false;
    }

void PACKRecord::SetTargetType(int32_t Type)
    {
    PTDT.Load();
    PTDT->targetType = Type;
    }

uint32_t PACKRecord::GetType()
    {
    return REV32(PACK);
    }

char * PACKRecord::GetStrType()
    {
    return "PACK";
    }

int32_t PACKRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(PKDT):
                switch(subSize)
                    {
                    case 4:
                        //old format (flags was originally a short, but changed to a uint; this change also affected the padding)
                        //PKDT.size = 8; //Force it to write out the updated version
                        PKDT.value.flags = *(uint16_t *)buffer;
                        buffer += 2;
                        PKDT.value.aiType = *(uint8_t *)buffer;
                        buffer += 2; //Skip over junk value. unused padding will default to 0
                        break;
                    default:
                        PKDT.Read(buffer, subSize);
                        break;
                    }
                break;
            case REV32(PLDT):
                PLDT.Read(buffer, subSize);
                break;
            case REV32(PSDT):
                PSDT.Read(buffer, subSize);
                break;
            case REV32(PTDT):
                PTDT.Read(buffer, subSize);
                break;
            case REV32(CTDT):
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PACK: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PACKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    PKDT.Unload();
    PLDT.Unload();
    PSDT.Unload();
    PTDT.Unload();
    CTDA.Unload();
    return 1;
    }

int32_t PACKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(PKDT);
    WRITE(PLDT);
    WRITE(PSDT);
    WRITE(PTDT);
    CTDA.Write(writer, true);
    return -1;
    }

bool PACKRecord::operator ==(const PACKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            PKDT == other.PKDT &&
            PLDT == other.PLDT &&
            PSDT == other.PSDT &&
            PTDT == other.PTDT &&
            CTDA == other.CTDA);
    }

bool PACKRecord::operator !=(const PACKRecord &other) const
    {
    return !(*this == other);
    }

bool PACKRecord::equals(Record *other)
    {
    return *this == *(PACKRecord *)other;
    }
}