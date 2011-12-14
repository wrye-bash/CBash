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
#include "CAMSRecord.h"

namespace FNV
{
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
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(MNAM.IsLoaded())
        op.Accept(MNAM->value);

    return op.Stop();
    }

bool CAMSRecord::IsPosFollowsLocation()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPosFollowsLocation) != 0;
    }

void CAMSRecord::IsPosFollowsLocation(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPosFollowsLocation) : (Dummy->flags & ~fIsPosFollowsLocation);
    }

bool CAMSRecord::IsPosFollowsTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsPosFollowsTarget) != 0;
    }

void CAMSRecord::IsPosFollowsTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsPosFollowsTarget) : (Dummy->flags & ~fIsPosFollowsTarget);
    }

bool CAMSRecord::IsDontFollowBone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDontFollowBone) != 0;
    }

void CAMSRecord::IsDontFollowBone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDontFollowBone) : (Dummy->flags & ~fIsDontFollowBone);
    }

bool CAMSRecord::IsFirstPersonCamera()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsFirstPersonCamera) != 0;
    }

void CAMSRecord::IsFirstPersonCamera(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsFirstPersonCamera) : (Dummy->flags & ~fIsFirstPersonCamera);
    }

bool CAMSRecord::IsNoTracer()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsNoTracer) != 0;
    }

void CAMSRecord::IsNoTracer(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsNoTracer) : (Dummy->flags & ~fIsNoTracer);
    }

bool CAMSRecord::IsStartAtTimeZero()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsStartAtTimeZero) != 0;
    }

void CAMSRecord::IsStartAtTimeZero(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsStartAtTimeZero) : (Dummy->flags & ~fIsStartAtTimeZero);
    }

bool CAMSRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void CAMSRecord::SetFlagMask(UINT32 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsActionShoot()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eShoot);
    }

void CAMSRecord::IsActionShoot(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eShoot : eDummyDefault;
    }

bool CAMSRecord::IsActionFly()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFly);
    }

void CAMSRecord::IsActionFly(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFly : eDummyDefault;
    }

bool CAMSRecord::IsActionHit()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHit);
    }

void CAMSRecord::IsActionHit(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHit : eDummyDefault;
    }

bool CAMSRecord::IsActionZoom()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eZoom);
    }

void CAMSRecord::IsActionZoom(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eZoom : eDummyDefault;
    }

bool CAMSRecord::IsActionType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CAMSRecord::SetActionType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsLocationAttacker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttacker);
    }

void CAMSRecord::IsLocationAttacker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttacker : eDummyDefault;
    }

bool CAMSRecord::IsLocationProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsLocationProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectile : eDummyDefault;
    }

bool CAMSRecord::IsLocationTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsLocationTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTarget : eDummyDefault;
    }

bool CAMSRecord::IsLocationType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CAMSRecord::SetLocationType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool CAMSRecord::IsTargetAttacker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAttacker);
    }

void CAMSRecord::IsTargetAttacker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAttacker : eDummyDefault;
    }

bool CAMSRecord::IsTargetProjectile()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eProjectile);
    }

void CAMSRecord::IsTargetProjectile(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eProjectile : eDummyDefault;
    }

bool CAMSRecord::IsTargetTarget()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTarget);
    }

void CAMSRecord::IsTargetTarget(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTarget : eDummyDefault;
    }

bool CAMSRecord::IsTargetType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CAMSRecord::SetTargetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CAMSRecord::GetType()
    {
    return REV32(CAMS);
    }

STRING CAMSRecord::GetStrType()
    {
    return "CAMS";
    }

SINT32 CAMSRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize);
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
                //printf("FileName = %s\n", FileName);
                printf("  CAMS: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CAMSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    DATA.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 CAMSRecord::WriteRecord(FileWriter &writer)
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

bool CAMSRecord::equals(const Record *other) const
    {
    return *this == *(CAMSRecord *)other;
    }
}