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
#include "CAMSRecord.h"

namespace FNV
{
CAMSRecord::CAMSDATA::CAMSDATA():
    action(eShoot),
    location(eAttacker),
    target(eAttacker),
    flags(0),
    playerTimeMult(0.0),
    targetTimeMult(0.0),
    globalTimeMult(0.0),
    maxTime(0.0),
    minTime(0.0),
    targetPercentBetweenActors(0.0)
    {
    //
    }

CAMSRecord::CAMSDATA::~CAMSDATA()
    {
    //
    }

bool CAMSRecord::CAMSDATA::operator ==(const CAMSDATA &other) const
    {
    return (action == other.action &&
            location == other.location &&
            target == other.target &&
            flags == other.flags &&
            AlmostEqual(playerTimeMult, other.playerTimeMult, 2) &&
            AlmostEqual(targetTimeMult, other.targetTimeMult, 2) &&
            AlmostEqual(globalTimeMult, other.globalTimeMult, 2) &&
            AlmostEqual(maxTime, other.maxTime, 2) &&
            AlmostEqual(minTime, other.minTime, 2) &&
            AlmostEqual(targetPercentBetweenActors, other.targetPercentBetweenActors, 2)
            );
    }

bool CAMSRecord::CAMSDATA::operator !=(const CAMSDATA &other) const
    {
    return !(*this == other);
    }

CAMSRecord::CAMSRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CAMSRecord::CAMSRecord(CAMSRecord *srcRecord):
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

    MODL = srcRecord->MODL;

    DATA = srcRecord->DATA;
    MNAM = srcRecord->MNAM;
    return;
    }

CAMSRecord::~CAMSRecord()
    {
    //
    }

bool CAMSRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(MNAM.IsLoaded())
        op.Accept(MNAM.value);

    return op.Stop();
    }

bool CAMSRecord::IsPosFollowsLocation()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsPosFollowsLocation) != 0;
    }

void CAMSRecord::IsPosFollowsLocation(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsPosFollowsLocation, value);
    }

bool CAMSRecord::IsPosFollowsTarget()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsPosFollowsTarget) != 0;
    }

void CAMSRecord::IsPosFollowsTarget(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsPosFollowsTarget, value);
    }

bool CAMSRecord::IsDontFollowBone()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsDontFollowBone) != 0;
    }

void CAMSRecord::IsDontFollowBone(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsDontFollowBone, value);
    }

bool CAMSRecord::IsFirstPersonCamera()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsFirstPersonCamera) != 0;
    }

void CAMSRecord::IsFirstPersonCamera(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsFirstPersonCamera, value);
    }

bool CAMSRecord::IsNoTracer()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsNoTracer) != 0;
    }

void CAMSRecord::IsNoTracer(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsNoTracer, value);
    }

bool CAMSRecord::IsStartAtTimeZero()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsStartAtTimeZero) != 0;
    }

void CAMSRecord::IsStartAtTimeZero(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsStartAtTimeZero, value);
    }

bool CAMSRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA->flags & Mask) == Mask) : ((DATA->flags & Mask) != 0);
    }

void CAMSRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.Load();
    DATA->flags = Mask;
    }

bool CAMSRecord::IsActionShoot()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->action == eShoot);
    }

bool CAMSRecord::IsActionFly()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->action == eFly);
    }

bool CAMSRecord::IsActionHit()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->action == eHit);
    }

bool CAMSRecord::IsActionZoom()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->action == eZoom);
    }

bool CAMSRecord::IsActionType(uint32_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->action == Type;
    }

void CAMSRecord::SetActionType(uint32_t Type)
    {
    DATA.Load();
    DATA->action = Type;
    }

bool CAMSRecord::IsLocationAttacker()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->location == eAttacker);
    }

bool CAMSRecord::IsLocationProjectile()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->location == eProjectile);
    }

bool CAMSRecord::IsLocationTarget()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->location == eTarget);
    }

bool CAMSRecord::IsLocationType(uint32_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->location == Type;
    }

void CAMSRecord::SetLocationType(uint32_t Type)
    {
    DATA.Load();
    DATA->location = Type;
    }

bool CAMSRecord::IsTargetAttacker()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->target == eAttacker);
    }

bool CAMSRecord::IsTargetProjectile()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->target == eProjectile);
    }

bool CAMSRecord::IsTargetTarget()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->target == eTarget);
    }

bool CAMSRecord::IsTargetType(uint32_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->target == Type;
    }

void CAMSRecord::SetTargetType(uint32_t Type)
    {
    DATA.Load();
    DATA->target = Type;
    }

uint32_t CAMSRecord::GetType()
    {
    return REV32(CAMS);
    }

char * CAMSRecord::GetStrType()
    {
    return "CAMS";
    }

int32_t CAMSRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t CAMSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    DATA.Unload();
    MNAM.Unload();
    return 1;
    }

int32_t CAMSRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(DATA);
    WRITE(MNAM);

    return -1;
    }

bool CAMSRecord::operator ==(const CAMSRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            MNAM == other.MNAM);
    }

bool CAMSRecord::operator !=(const CAMSRecord &other) const
    {
    return !(*this == other);
    }

bool CAMSRecord::equals(Record *other)
    {
    return *this == *(CAMSRecord *)other;
    }
}