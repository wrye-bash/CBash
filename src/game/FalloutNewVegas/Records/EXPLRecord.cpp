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
#include "EXPLRecord.h"

namespace FNV
{
EXPLRecord::EXPLDATA::EXPLDATA():
    force(0.0f),
    damage(0.0f),
    radius(0.0f),
    light(0),
    sound1(0),
    flags(0),
    ISRadius(0.0f),
    impactDataSet(0),
    sound2(0),
    radLevel(0.0f),
    radTime(0.0f),
    radRadius(0.0f),
    soundLevel(0)
    {
    //
    }

EXPLRecord::EXPLDATA::~EXPLDATA()
    {
    //
    }

bool EXPLRecord::EXPLDATA::operator ==(const EXPLDATA &other) const
    {
    return (light == other.light &&
            sound1 == other.sound1 &&
            flags == other.flags &&
            impactDataSet == other.impactDataSet &&
            sound2 == other.sound2 &&
            soundLevel == other.soundLevel &&
            AlmostEqual(force,other.force,2) &&
            AlmostEqual(damage,other.damage,2) &&
            AlmostEqual(radius,other.radius,2) &&
            AlmostEqual(ISRadius,other.ISRadius,2) &&
            AlmostEqual(radLevel,other.radLevel,2) &&
            AlmostEqual(radTime,other.radTime,2) &&
            AlmostEqual(radRadius,other.radRadius,2));
    }

bool EXPLRecord::EXPLDATA::operator !=(const EXPLDATA &other) const
    {
    return !(*this == other);
    }

EXPLRecord::EXPLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

EXPLRecord::EXPLRecord(EXPLRecord *srcRecord):
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
    EITM = srcRecord->EITM;
    MNAM = srcRecord->MNAM;
    DATA = srcRecord->DATA;
    INAM = srcRecord->INAM;
    return;
    }

EXPLRecord::~EXPLRecord()
    {
    //
    }

bool EXPLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(EITM.IsLoaded())
        op.Accept(EITM.value);
    if(MNAM.IsLoaded())
        op.Accept(MNAM.value);
    op.Accept(DATA.value.light);
    op.Accept(DATA.value.sound1);
    op.Accept(DATA.value.impactDataSet);
    op.Accept(DATA.value.sound2);
    if(INAM.IsLoaded())
        op.Accept(INAM.value);

    return op.Stop();
    }

bool EXPLRecord::IsUnknown1()
    {
    return (DATA.value.flags & fIsUnknown1) != 0;
    }

void EXPLRecord::IsUnknown1(bool value)
    {
    SETBIT(DATA.value.flags, fIsUnknown1, value);
    }

bool EXPLRecord::IsAlwaysUsesWorldOrientation()
    {
    return (DATA.value.flags & fIsAlwaysUsesWorldOrientation) != 0;
    }

void EXPLRecord::IsAlwaysUsesWorldOrientation(bool value)
    {
    SETBIT(DATA.value.flags, fIsAlwaysUsesWorldOrientation, value);
    }

bool EXPLRecord::IsAlwaysKnockDown()
    {
    return (DATA.value.flags & fIsAlwaysKnockDown) != 0;
    }

void EXPLRecord::IsAlwaysKnockDown(bool value)
    {
    SETBIT(DATA.value.flags, fIsAlwaysKnockDown, value);
    }

bool EXPLRecord::IsFormulaKnockDown()
    {
    return (DATA.value.flags & fIsFormulaKnockDown) != 0;
    }

void EXPLRecord::IsFormulaKnockDown(bool value)
    {
    SETBIT(DATA.value.flags, fIsFormulaKnockDown, value);
    }

bool EXPLRecord::IsIgnoreLOS()
    {
    return (DATA.value.flags & fIsIgnoreLOS) != 0;
    }

void EXPLRecord::IsIgnoreLOS(bool value)
    {
    SETBIT(DATA.value.flags, fIsIgnoreLOS, value);
    }

bool EXPLRecord::IsPushExplosionSourceRefOnly()
    {
    return (DATA.value.flags & fIsPushExplosionSourceRefOnly) != 0;
    }

void EXPLRecord::IsPushExplosionSourceRefOnly(bool value)
    {
    SETBIT(DATA.value.flags, fIsPushExplosionSourceRefOnly, value);
    }

bool EXPLRecord::IsIgnoreImageSpaceSwap()
    {
    return (DATA.value.flags & fIsIgnoreImageSpaceSwap) != 0;
    }

void EXPLRecord::IsIgnoreImageSpaceSwap(bool value)
    {
    SETBIT(DATA.value.flags, fIsIgnoreImageSpaceSwap, value);
    }

bool EXPLRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void EXPLRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool EXPLRecord::IsLoud()
    {
    return DATA.value.soundLevel == eLoud;
    }

void EXPLRecord::IsLoud(bool value)
    {
    DATA.value.soundLevel = value ? eLoud : eNormal;
    }

bool EXPLRecord::IsNormal()
    {
    return DATA.value.soundLevel == eNormal;
    }

void EXPLRecord::IsNormal(bool value)
    {
    DATA.value.soundLevel = value ? eNormal : eLoud;
    }

bool EXPLRecord::IsSilent()
    {
    return DATA.value.soundLevel == eSilent;
    }

void EXPLRecord::IsSilent(bool value)
    {
    DATA.value.soundLevel = value ? eSilent : eLoud;
    }

bool EXPLRecord::IsSoundLevelType(uint8_t Type)
    {
    return DATA.value.soundLevel == Type;
    }

void EXPLRecord::SetSoundLevelType(uint8_t Type)
    {
    DATA.value.soundLevel = Type;
    }

uint32_t EXPLRecord::GetType()
    {
    return REV32(EXPL);
    }

char * EXPLRecord::GetStrType()
    {
    return "EXPL";
    }

int32_t EXPLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(EITM):
                EITM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  EXPL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t EXPLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    EITM.Unload();
    MNAM.Unload();
    DATA.Unload();
    INAM.Unload();
    return 1;
    }

int32_t EXPLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(EITM);
    WRITE(MNAM);
    WRITE(DATA);
    WRITE(INAM);
    return -1;
    }

bool EXPLRecord::operator ==(const EXPLRecord &other) const
    {
    return (OBND == other.OBND &&
            EITM == other.EITM &&
            MNAM == other.MNAM &&
            DATA == other.DATA &&
            INAM == other.INAM &&
            MODL == other.MODL &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL));
    }

bool EXPLRecord::operator !=(const EXPLRecord &other) const
    {
    return !(*this == other);
    }

bool EXPLRecord::equals(Record *other)
    {
    return *this == *(EXPLRecord *)other;
    }
}