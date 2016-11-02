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
#include "PROJRecord.h"

namespace FNV
{
PROJRecord::PROJDATA::PROJDATA():
    flags(0),
    projType(0),
    gravity(0.0f),
    speed(0.0f),
    range(0.0f),
    light(0),
    flash(0),
    tracerChance(0.0f),
    altExplProximityTrigger(0.0f),
    altExplProximityTimer(0.0f),
    explosion(0),
    sound(0),
    flashDuration(0.0f),
    fadeDuration(0.0f),
    impactForce(0.0f),
    soundCountdown(0),
    soundDisable(0),
    defaultWeaponSource(0),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f),
    bouncyMult(0.0f)
    {
    //
    }

PROJRecord::PROJDATA::~PROJDATA()
    {
    //
    }

bool PROJRecord::PROJDATA::operator ==(const PROJDATA &other) const
    {
    return (flags == other.flags &&
            projType == other.projType &&
            light == other.light &&
            flash == other.flash &&
            explosion == other.explosion &&
            sound == other.sound &&
            soundCountdown == other.soundCountdown &&
            soundDisable == other.soundDisable &&
            defaultWeaponSource == other.defaultWeaponSource &&
            AlmostEqual(gravity,other.gravity,2) &&
            AlmostEqual(speed,other.speed,2) &&
            AlmostEqual(range,other.range,2) &&
            AlmostEqual(tracerChance,other.tracerChance,2) &&
            AlmostEqual(altExplProximityTrigger,other.altExplProximityTrigger,2) &&
            AlmostEqual(altExplProximityTimer,other.altExplProximityTimer,2) &&
            AlmostEqual(flashDuration,other.flashDuration,2) &&
            AlmostEqual(fadeDuration,other.fadeDuration,2) &&
            AlmostEqual(impactForce,other.impactForce,2) &&
            AlmostEqual(rotX,other.rotX,2) &&
            AlmostEqual(rotY,other.rotY,2) &&
            AlmostEqual(rotZ,other.rotZ,2) &&
            AlmostEqual(bouncyMult,other.bouncyMult,2));
    }

bool PROJRecord::PROJDATA::operator !=(const PROJDATA &other) const
    {
    return !(*this == other);
    }

PROJRecord::PROJRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PROJRecord::PROJRecord(PROJRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    Destructable = srcRecord->Destructable;
    DATA = srcRecord->DATA;
    NAM1 = srcRecord->NAM1;
    NAM2 = srcRecord->NAM2;
    VNAM = srcRecord->VNAM;
    return;
    }

PROJRecord::~PROJRecord()
    {
    //
    }

bool PROJRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(Destructable.IsLoaded())
        {
        for(uint32_t x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.flash);
    op.Accept(DATA.value.explosion);
    op.Accept(DATA.value.sound);
    op.Accept(DATA.value.soundCountdown);
    op.Accept(DATA.value.soundDisable);
    op.Accept(DATA.value.defaultWeaponSource);
    return op.Stop();
    }

bool PROJRecord::IsHitscan()
    {
    return (DATA.value.flags & fIsHitscan) != 0;
    }

void PROJRecord::IsHitscan(bool value)
    {
    SETBIT(DATA.value.flags, fIsHitscan, value);
    }

bool PROJRecord::IsExplosion()
    {
    return (DATA.value.flags & fIsExplosion) != 0;
    }

void PROJRecord::IsExplosion(bool value)
    {
    SETBIT(DATA.value.flags, fIsExplosion, value);
    }

bool PROJRecord::IsAltTrigger()
    {
    return (DATA.value.flags & fIsAltTrigger) != 0;
    }

void PROJRecord::IsAltTrigger(bool value)
    {
    SETBIT(DATA.value.flags, fIsAltTrigger, value);
    }

bool PROJRecord::IsMuzzleFlash()
    {
    return (DATA.value.flags & fIsMuzzleFlash) != 0;
    }

void PROJRecord::IsMuzzleFlash(bool value)
    {
    SETBIT(DATA.value.flags, fIsMuzzleFlash, value);
    }

bool PROJRecord::IsDisableable()
    {
    return (DATA.value.flags & fIsDisableable) != 0;
    }

void PROJRecord::IsDisableable(bool value)
    {
    SETBIT(DATA.value.flags, fIsDisableable, value);
    }

bool PROJRecord::IsPickupable()
    {
    return (DATA.value.flags & fIsPickupable) != 0;
    }

void PROJRecord::IsPickupable(bool value)
    {
    SETBIT(DATA.value.flags, fIsPickupable, value);
    }

bool PROJRecord::IsSupersonic()
    {
    return (DATA.value.flags & fIsSupersonic) != 0;
    }

void PROJRecord::IsSupersonic(bool value)
    {
    SETBIT(DATA.value.flags, fIsSupersonic, value);
    }

bool PROJRecord::IsPinsLimbs()
    {
    return (DATA.value.flags & fIsPinsLimbs) != 0;
    }

void PROJRecord::IsPinsLimbs(bool value)
    {
    SETBIT(DATA.value.flags, fIsPinsLimbs, value);
    }

bool PROJRecord::IsPassSmallTransparent()
    {
    return (DATA.value.flags & fIsPassSmallTransparent) != 0;
    }

void PROJRecord::IsPassSmallTransparent(bool value)
    {
    SETBIT(DATA.value.flags, fIsPassSmallTransparent, value);
    }

bool PROJRecord::IsDetonates()
    {
    return (DATA.value.flags & fIsDetonates) != 0;
    }

void PROJRecord::IsDetonates(bool value)
    {
    SETBIT(DATA.value.flags, fIsDetonates, value);
    }

bool PROJRecord::IsRotation()
    {
    return (DATA.value.flags & fIsRotation) != 0;
    }

void PROJRecord::IsRotation(bool value)
    {
    SETBIT(DATA.value.flags, fIsRotation, value);
    }

bool PROJRecord::IsFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void PROJRecord::SetFlagMask(uint16_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool PROJRecord::IsMissile()
    {
    return DATA.value.projType == eMissile;
    }

void PROJRecord::IsMissile(bool value)
    {
    DATA.value.projType = value ? eMissile : eLobber;
    }

bool PROJRecord::IsLobber()
    {
    return DATA.value.projType == eLobber;
    }

void PROJRecord::IsLobber(bool value)
    {
    DATA.value.projType = value ? eLobber : eMissile;
    }

bool PROJRecord::IsBeam()
    {
    return DATA.value.projType == eBeam;
    }

void PROJRecord::IsBeam(bool value)
    {
    DATA.value.projType = value ? eBeam : eMissile;
    }

bool PROJRecord::IsFlame()
    {
    return DATA.value.projType == eFlame;
    }

void PROJRecord::IsFlame(bool value)
    {
    DATA.value.projType = value ? eFlame : eMissile;
    }

bool PROJRecord::IsContinuousBeam()
    {
    return DATA.value.projType == eContinuousBeam;
    }

void PROJRecord::IsContinuousBeam(bool value)
    {
    DATA.value.projType = value ? eContinuousBeam : eMissile;
    }

bool PROJRecord::IsType(uint16_t Type)
    {
    return DATA.value.projType == Type;
    }

void PROJRecord::SetType(uint16_t Type)
    {
    DATA.value.projType = Type;
    }

bool PROJRecord::IsLoud()
    {
    return VNAM.value == eLoud;
    }

void PROJRecord::IsLoud(bool value)
    {
    VNAM.value = value ? eLoud : eNormal;
    }

bool PROJRecord::IsNormal()
    {
    return VNAM.value == eNormal;
    }

void PROJRecord::IsNormal(bool value)
    {
    VNAM.value = value ? eNormal : eLoud;
    }

bool PROJRecord::IsSilent()
    {
    return VNAM.value == eSilent;
    }

void PROJRecord::IsSilent(bool value)
    {
    VNAM.value = value ? eSilent : eLoud;
    }

bool PROJRecord::IsSoundLevelType(uint32_t Type)
    {
    return VNAM.value == Type;
    }

void PROJRecord::SetSoundLevelType(uint32_t Type)
    {
    VNAM.value = Type;
    }

uint32_t PROJRecord::GetType()
    {
    return REV32(PROJ);
    }

char * PROJRecord::GetStrType()
    {
    return "PROJ";
    }

int32_t PROJRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM2):
                NAM2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(VNAM):
                VNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PROJ: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PROJRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    Destructable.Unload();
    DATA.Unload();
    NAM1.Unload();
    NAM2.Unload();
    VNAM.Unload();
    return 1;
    }

int32_t PROJRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    Destructable.Write(writer);
    WRITE(DATA);
    WRITE(NAM1);
    WRITE(NAM2);
    WRITE(VNAM);
    return -1;
    }

bool PROJRecord::operator ==(const PROJRecord &other) const
    {
    return (OBND == other.OBND &&
            DATA == other.DATA &&
            NAM2 == other.NAM2 &&
            VNAM == other.VNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            NAM1.equalsi(other.NAM1) &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool PROJRecord::operator !=(const PROJRecord &other) const
    {
    return !(*this == other);
    }

bool PROJRecord::equals(Record *other)
    {
    return *this == *(PROJRecord *)other;
    }
}