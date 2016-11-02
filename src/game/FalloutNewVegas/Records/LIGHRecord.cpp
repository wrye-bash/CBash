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
#include "LIGHRecord.h"

namespace FNV
{
LIGHRecord::LIGHDATA::LIGHDATA():
    duration(0),
    radius(0),
    flags(0),
    falloff(0.0f),
    fov(0.0f),
    value(0),
    weight(0.0f)
    {
    //
    }

LIGHRecord::LIGHDATA::~LIGHDATA()
    {
    //
    }

bool LIGHRecord::LIGHDATA::operator ==(const LIGHDATA &other) const
    {
    return (duration == other.duration &&
            radius == other.radius &&
            color == other.color &&
            flags == other.flags &&
            AlmostEqual(falloff,other.falloff,2) &&
            AlmostEqual(fov,other.fov,2) &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2));
    }

bool LIGHRecord::LIGHDATA::operator !=(const LIGHDATA &other) const
    {
    return !(*this == other);
    }

LIGHRecord::LIGHRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LIGHRecord::LIGHRecord(LIGHRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    FULL = srcRecord->FULL;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DATA = srcRecord->DATA;
    FNAM = srcRecord->FNAM;
    SNAM = srcRecord->SNAM;
    return;
    }

LIGHRecord::~LIGHRecord()
    {
    //
    }

bool LIGHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);

    return op.Stop();
    }

bool LIGHRecord::IsDynamic()
    {
    return (DATA.value.flags & fIsDynamic) != 0;
    }

void LIGHRecord::IsDynamic(bool value)
    {
    SETBIT(DATA.value.flags, fIsDynamic, value);
    }

bool LIGHRecord::IsCanTake()
    {
    return (DATA.value.flags & fIsCanTake) != 0;
    }

void LIGHRecord::IsCanTake(bool value)
    {
    SETBIT(DATA.value.flags, fIsCanTake, value);
    }

bool LIGHRecord::IsTakeable()
    {
    return (DATA.value.flags & fIsCanTake) != 0;
    }

void LIGHRecord::IsTakeable(bool value)
    {
    SETBIT(DATA.value.flags, fIsCanTake, value);
    }

bool LIGHRecord::IsNegative()
    {
    return (DATA.value.flags & fIsNegative) != 0;
    }

void LIGHRecord::IsNegative(bool value)
    {
    SETBIT(DATA.value.flags, fIsNegative, value);
    }

bool LIGHRecord::IsFlickers()
    {
    return (DATA.value.flags & fIsFlickers) != 0;
    }

void LIGHRecord::IsFlickers(bool value)
    {
    SETBIT(DATA.value.flags, fIsFlickers, value);
    }

bool LIGHRecord::IsOffByDefault()
    {
    return (DATA.value.flags & fIsOffByDefault) != 0;
    }

void LIGHRecord::IsOffByDefault(bool value)
    {
    SETBIT(DATA.value.flags, fIsOffByDefault, value);
    }

bool LIGHRecord::IsFlickerSlow()
    {
    return (DATA.value.flags & fIsFlickerSlow) != 0;
    }

void LIGHRecord::IsFlickerSlow(bool value)
    {
    SETBIT(DATA.value.flags, fIsFlickerSlow, value);
    }

bool LIGHRecord::IsPulse()
    {
    return (DATA.value.flags & fIsPulse) != 0;
    }

void LIGHRecord::IsPulse(bool value)
    {
    SETBIT(DATA.value.flags, fIsPulse, value);
    }

bool LIGHRecord::IsPulseSlow()
    {
    return (DATA.value.flags & fIsPulseSlow) != 0;
    }

void LIGHRecord::IsPulseSlow(bool value)
    {
    SETBIT(DATA.value.flags, fIsPulseSlow, value);
    }

bool LIGHRecord::IsSpotLight()
    {
    return (DATA.value.flags & fIsSpotLight) != 0;
    }

void LIGHRecord::IsSpotLight(bool value)
    {
    SETBIT(DATA.value.flags, fIsSpotLight, value);
    }

bool LIGHRecord::IsSpotShadow()
    {
    return (DATA.value.flags & fIsSpotShadow) != 0;
    }

void LIGHRecord::IsSpotShadow(bool value)
    {
    SETBIT(DATA.value.flags, fIsSpotShadow, value);
    }

bool LIGHRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void LIGHRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t LIGHRecord::GetType()
    {
    return REV32(LIGH);
    }

char * LIGHRecord::GetStrType()
    {
    return "LIGH";
    }

int32_t LIGHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LIGH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t LIGHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    SCRI.Unload();
    FULL.Unload();
    ICON.Unload();
    MICO.Unload();
    DATA.Unload();
    FNAM.Unload();
    SNAM.Unload();
    return 1;
    }

int32_t LIGHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(SCRI);
    WRITE(FULL);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DATA);
    WRITE(FNAM);
    WRITE(SNAM);
    return -1;
    }

bool LIGHRecord::operator ==(const LIGHRecord &other) const
    {
    return (OBND == other.OBND &&
            SNAM == other.SNAM &&
            SCRI == other.SCRI &&
            DATA == other.DATA &&
            FNAM == other.FNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MODL == other.MODL);
    }

bool LIGHRecord::operator !=(const LIGHRecord &other) const
    {
    return !(*this == other);
    }

bool LIGHRecord::equals(Record *other)
    {
    return *this == *(LIGHRecord *)other;
    }
}