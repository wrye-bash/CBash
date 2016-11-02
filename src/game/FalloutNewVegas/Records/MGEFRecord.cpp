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
#include "MGEFRecord.h"

namespace FNV
{
MGEFRecord::MGEFDATA::MGEFDATA():
    flags(0),
    baseCost(0.0f),
    associated(0),
    schoolType(0),
    resistType(-1),
    numCounters(0),
    light(0),
    projectileSpeed(0.0f),
    effectShader(0),
    displayShader(0),
    effectSound(0),
    boltSound(0),
    hitSound(0),
    areaSound(0),
    cefEnchantment(0.0f),
    cefBarter(0.0f),
    archType(0),
    actorValue(-1)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

MGEFRecord::MGEFDATA::~MGEFDATA()
    {
    //
    }

bool MGEFRecord::MGEFDATA::operator ==(const MGEFDATA &other) const
    {
    return (flags == other.flags &&
            associated == other.associated &&
            resistType == other.resistType &&
            numCounters == other.numCounters &&
            light == other.light &&
            AlmostEqual(projectileSpeed,other.projectileSpeed,2) &&
            effectShader == other.effectShader &&
            displayShader == other.displayShader &&
            effectSound == other.effectSound &&
            boltSound == other.boltSound &&
            hitSound == other.hitSound &&
            areaSound == other.areaSound &&
            archType == other.archType &&
            actorValue == other.actorValue);
    }

bool MGEFRecord::MGEFDATA::operator !=(const MGEFDATA &other) const
    {
    return !(*this == other);
    }

MGEFRecord::MGEFRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

MGEFRecord::MGEFRecord(MGEFRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    MODL = srcRecord->MODL;
    DATA = srcRecord->DATA;
    return;
    }

MGEFRecord::~MGEFRecord()
    {
    //
    }

bool MGEFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    op.Accept(DATA.value.associated);
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.effectShader);
    op.Accept(DATA.value.displayShader);
    op.Accept(DATA.value.effectSound);
    op.Accept(DATA.value.boltSound);
    op.Accept(DATA.value.hitSound);
    op.Accept(DATA.value.areaSound);
    return op.Stop();
    }

bool MGEFRecord::IsHostile()
    {
    return (DATA.value.flags & fIsHostile) != 0;
    }

void MGEFRecord::IsHostile(bool value)
    {
    SETBIT(DATA.value.flags, fIsHostile, value);
    }

bool MGEFRecord::IsRecover()
    {
    return (DATA.value.flags & fIsRecover) != 0;
    }

void MGEFRecord::IsRecover(bool value)
    {
    SETBIT(DATA.value.flags, fIsRecover, value);
    }

bool MGEFRecord::IsDetrimental()
    {
    return (DATA.value.flags & fIsDetrimental) != 0;
    }

void MGEFRecord::IsDetrimental(bool value)
    {
    SETBIT(DATA.value.flags, fIsDetrimental, value);
    }

bool MGEFRecord::IsSelf()
    {
    return (DATA.value.flags & fIsSelf) != 0;
    }

void MGEFRecord::IsSelf(bool value)
    {
    SETBIT(DATA.value.flags, fIsSelf, value);
    }

bool MGEFRecord::IsTouch()
    {
    return (DATA.value.flags & fIsTouch) != 0;
    }

void MGEFRecord::IsTouch(bool value)
    {
    SETBIT(DATA.value.flags, fIsTouch, value);
    }

bool MGEFRecord::IsTarget()
    {
    return (DATA.value.flags & fIsTarget) != 0;
    }

void MGEFRecord::IsTarget(bool value)
    {
    SETBIT(DATA.value.flags, fIsTarget, value);
    }

bool MGEFRecord::IsNoDuration()
    {
    return (DATA.value.flags & fIsNoDuration) != 0;
    }

void MGEFRecord::IsNoDuration(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoDuration, value);
    }

bool MGEFRecord::IsNoMagnitude()
    {
    return (DATA.value.flags & fIsNoMagnitude) != 0;
    }

void MGEFRecord::IsNoMagnitude(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoMagnitude, value);
    }

bool MGEFRecord::IsNoArea()
    {
    return (DATA.value.flags & fIsNoArea) != 0;
    }

void MGEFRecord::IsNoArea(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoArea, value);
    }

bool MGEFRecord::IsFXPersist()
    {
    return (DATA.value.flags & fIsFXPersist) != 0;
    }

void MGEFRecord::IsFXPersist(bool value)
    {
    SETBIT(DATA.value.flags, fIsFXPersist, value);
    }

bool MGEFRecord::IsGoryVisuals()
    {
    return (DATA.value.flags & fIsGoryVisuals) != 0;
    }

void MGEFRecord::IsGoryVisuals(bool value)
    {
    SETBIT(DATA.value.flags, fIsGoryVisuals, value);
    }

bool MGEFRecord::IsDisplayNameOnly()
    {
    return (DATA.value.flags & fIsDisplayNameOnly) != 0;
    }

void MGEFRecord::IsDisplayNameOnly(bool value)
    {
    SETBIT(DATA.value.flags, fIsDisplayNameOnly, value);
    }

bool MGEFRecord::IsRadioBroadcast()
    {
    return (DATA.value.flags & fIsRadioBroadcast) != 0;
    }

void MGEFRecord::IsRadioBroadcast(bool value)
    {
    SETBIT(DATA.value.flags, fIsRadioBroadcast, value);
    }

bool MGEFRecord::IsUseSkill()
    {
    return (DATA.value.flags & fIsUseSkill) != 0;
    }

void MGEFRecord::IsUseSkill(bool value)
    {
    SETBIT(DATA.value.flags, fIsUseSkill, value);
    }

bool MGEFRecord::IsUseAttr()
    {
    return (DATA.value.flags & fIsUseAttr) != 0;
    }

void MGEFRecord::IsUseAttr(bool value)
    {
    SETBIT(DATA.value.flags, fIsUseAttr, value);
    }

bool MGEFRecord::IsPainless()
    {
    return (DATA.value.flags & fIsPainless) != 0;
    }

void MGEFRecord::IsPainless(bool value)
    {
    SETBIT(DATA.value.flags, fIsPainless, value);
    }

bool MGEFRecord::IsSprayType()
    {
    return ((DATA.value.flags & fIsSprayType) != 0) && ((DATA.value.flags & fIsBoltType) == 0);
    }

void MGEFRecord::IsSprayType(bool value)
    {
    if(value)
        {
        DATA.value.flags &= ~fIsFogType;
        DATA.value.flags |= fIsSprayType;
        }
    else if(IsSprayType())
        IsBallType(true);
    }

bool MGEFRecord::IsBoltType()
    {
    return ((DATA.value.flags & fIsBoltType) != 0) && ((DATA.value.flags & fIsSprayType) == 0);
    }

void MGEFRecord::IsBoltType(bool value)
    {
    if(value)
        {
        DATA.value.flags &= ~fIsFogType;
        DATA.value.flags |= fIsBoltType;
        }
    else if(IsBoltType())
        IsBallType(true);
    }

bool MGEFRecord::IsFogType()
    {
    return (DATA.value.flags & fIsFogType) == fIsFogType;
    }

void MGEFRecord::IsFogType(bool value)
    {
    if(value)
        DATA.value.flags |= fIsFogType;
    else if(IsFogType())
        IsBallType(true);
    }

bool MGEFRecord::IsBallType()
    {
    return (DATA.value.flags & fIsFogType) == 0;
    }

void MGEFRecord::IsBallType(bool value)
    {
    if(value)
        DATA.value.flags &= ~fIsFogType;
    else if(IsBallType())
        IsBoltType(true);
    }

bool MGEFRecord::IsNoHitEffect()
    {
    return (DATA.value.flags & fIsNoHitEffect) != 0;
    }

void MGEFRecord::IsNoHitEffect(bool value)
    {
    SETBIT(DATA.value.flags, fIsNoHitEffect, value);
    }

bool MGEFRecord::IsPersistOnDeath()
    {
    return (DATA.value.flags & fIsPersistOnDeath) != 0;
    }

void MGEFRecord::IsPersistOnDeath(bool value)
    {
    SETBIT(DATA.value.flags, fIsPersistOnDeath, value);
    }

bool MGEFRecord::IsUnknown1()
    {
    return (DATA.value.flags & fIsUnknown1) != 0;
    }

void MGEFRecord::IsUnknown1(bool value)
    {
    SETBIT(DATA.value.flags, fIsUnknown1, value);
    }

bool MGEFRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void MGEFRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool MGEFRecord::IsValueModifier()
    {
    return (DATA.value.archType == eValueModifier);
    }

void MGEFRecord::IsValueModifier(bool value)
    {
    DATA.value.archType = value ? eValueModifier : eScript;
    }

bool MGEFRecord::IsScript()
    {
    return (DATA.value.archType == eScript);
    }

void MGEFRecord::IsScript(bool value)
    {
    DATA.value.archType = value ? eScript : eValueModifier;
    }

bool MGEFRecord::IsDispel()
    {
    return (DATA.value.archType == eDispel);
    }

void MGEFRecord::IsDispel(bool value)
    {
    DATA.value.archType = value ? eDispel : eValueModifier;
    }

bool MGEFRecord::IsCureDisease()
    {
    return (DATA.value.archType == eCureDisease);
    }

void MGEFRecord::IsCureDisease(bool value)
    {
    DATA.value.archType = value ? eCureDisease : eValueModifier;
    }

bool MGEFRecord::IsInvisibility()
    {
    return (DATA.value.archType == eInvisibility);
    }

void MGEFRecord::IsInvisibility(bool value)
    {
    DATA.value.archType = value ? eInvisibility : eValueModifier;
    }

bool MGEFRecord::IsChameleon()
    {
    return (DATA.value.archType == eChameleon);
    }

void MGEFRecord::IsChameleon(bool value)
    {
    DATA.value.archType = value ? eChameleon : eValueModifier;
    }

bool MGEFRecord::IsLight()
    {
    return (DATA.value.archType == eLight);
    }

void MGEFRecord::IsLight(bool value)
    {
    DATA.value.archType = value ? eLight : eValueModifier;
    }

bool MGEFRecord::IsLock()
    {
    return (DATA.value.archType == eLock);
    }

void MGEFRecord::IsLock(bool value)
    {
    DATA.value.archType = value ? eLock : eValueModifier;
    }

bool MGEFRecord::IsOpen()
    {
    return (DATA.value.archType == eOpen);
    }

void MGEFRecord::IsOpen(bool value)
    {
    DATA.value.archType = value ? eOpen : eValueModifier;
    }

bool MGEFRecord::IsBoundItem()
    {
    return (DATA.value.archType == eBoundItem);
    }

void MGEFRecord::IsBoundItem(bool value)
    {
    DATA.value.archType = value ? eBoundItem : eValueModifier;
    }

bool MGEFRecord::IsSummonCreature()
    {
    return (DATA.value.archType == eSummonCreature);
    }

void MGEFRecord::IsSummonCreature(bool value)
    {
    DATA.value.archType = value ? eSummonCreature : eValueModifier;
    }

bool MGEFRecord::IsParalysis()
    {
    return (DATA.value.archType == eParalysis);
    }

void MGEFRecord::IsParalysis(bool value)
    {
    DATA.value.archType = value ? eParalysis : eValueModifier;
    }

bool MGEFRecord::IsCureParalysis()
    {
    return (DATA.value.archType == eCureParalysis);
    }

void MGEFRecord::IsCureParalysis(bool value)
    {
    DATA.value.archType = value ? eCureParalysis : eValueModifier;
    }

bool MGEFRecord::IsCureAddiction()
    {
    return (DATA.value.archType == eCureAddiction);
    }

void MGEFRecord::IsCureAddiction(bool value)
    {
    DATA.value.archType = value ? eCureAddiction : eValueModifier;
    }

bool MGEFRecord::IsCurePoison()
    {
    return (DATA.value.archType == eCurePoison);
    }

void MGEFRecord::IsCurePoison(bool value)
    {
    DATA.value.archType = value ? eCurePoison : eValueModifier;
    }

bool MGEFRecord::IsConcussion()
    {
    return (DATA.value.archType == eConcussion);
    }

void MGEFRecord::IsConcussion(bool value)
    {
    DATA.value.archType = value ? eConcussion : eValueModifier;
    }

bool MGEFRecord::IsValueAndParts()
    {
    return (DATA.value.archType == eValueAndParts);
    }

void MGEFRecord::IsValueAndParts(bool value)
    {
    DATA.value.archType = value ? eValueAndParts : eValueModifier;
    }

bool MGEFRecord::IsLimbCondition()
    {
    return (DATA.value.archType == eLimbCondition);
    }

void MGEFRecord::IsLimbCondition(bool value)
    {
    DATA.value.archType = value ? eLimbCondition : eValueModifier;
    }

bool MGEFRecord::IsTurbo()
    {
    return (DATA.value.archType == eTurbo);
    }

void MGEFRecord::IsTurbo(bool value)
    {
    DATA.value.archType = value ? eTurbo : eValueModifier;
    }

bool MGEFRecord::IsType(uint32_t Type)
    {
    return DATA.value.archType == Type;
    }

void MGEFRecord::SetType(uint32_t Type)
    {
    DATA.value.archType = Type;
    }

bool MGEFRecord::IsSchoolAlteration()
    {
    return (DATA.value.schoolType == eAlteration);
    }

void MGEFRecord::IsSchoolAlteration(bool value)
    {
    DATA.value.schoolType = value ? eAlteration : eConjuration;
    }

bool MGEFRecord::IsSchoolConjuration()
    {
    return (DATA.value.schoolType == eConjuration);
    }

void MGEFRecord::IsSchoolConjuration(bool value)
    {
    DATA.value.schoolType = value ? eConjuration : eAlteration;
    }

bool MGEFRecord::IsSchoolDestruction()
    {
    return (DATA.value.schoolType == eDestruction);
    }

void MGEFRecord::IsSchoolDestruction(bool value)
    {
    DATA.value.schoolType = value ? eDestruction : eAlteration;
    }

bool MGEFRecord::IsSchoolIllusion()
    {
    return (DATA.value.schoolType == eIllusion);
    }

void MGEFRecord::IsSchoolIllusion(bool value)
    {
    DATA.value.schoolType = value ? eIllusion : eAlteration;
    }

bool MGEFRecord::IsSchoolMysticism()
    {
    return (DATA.value.schoolType == eMysticism);
    }

void MGEFRecord::IsSchoolMysticism(bool value)
    {
    DATA.value.schoolType = value ? eMysticism : eAlteration;
    }

bool MGEFRecord::IsSchoolRestoration()
    {
    return (DATA.value.schoolType == eRestoration);
    }

void MGEFRecord::IsSchoolRestoration(bool value)
    {
    DATA.value.schoolType = value ? eRestoration : eAlteration;
    }

bool MGEFRecord::IsSchool(uint32_t Type)
    {
    return (DATA.value.schoolType == Type);
    }

void MGEFRecord::SetSchool(uint32_t Type)
    {
    DATA.value.schoolType = Type;
    }

uint32_t MGEFRecord::GetType()
    {
    return REV32(MGEF);
    }

char * MGEFRecord::GetStrType()
    {
    return "MGEF";
    }

int32_t MGEFRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
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
            default:
                //printer("FileName = %s\n", FileName);
                printer("  MGEF: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t MGEFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    MODL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t MGEFRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITEREQ(DESC);
    WRITE(ICON);
    WRITE(MICO);
    MODL.Write(writer);
    WRITE(DATA);
    return -1;
    }

bool MGEFRecord::operator ==(const MGEFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MODL == other.MODL &&
            DATA == other.DATA);
    }

bool MGEFRecord::operator !=(const MGEFRecord &other) const
    {
    return !(*this == other);
    }

bool MGEFRecord::equals(Record *other)
    {
    return *this == *(MGEFRecord *)other;
    }
}