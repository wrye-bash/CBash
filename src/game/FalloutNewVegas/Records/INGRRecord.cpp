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
#include "INGRRecord.h"

namespace FNV
{
INGRRecord::INGRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

INGRRecord::INGRRecord(INGRRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    return;
    }

INGRRecord::~INGRRecord()
    {
    //
    }

bool INGRRecord::VisitFormIDs(FormIDOp &op)
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
    for(uint32_t x = 0; x < Effects.value.size(); x++)
        Effects.value[x]->VisitFormIDs(op);

    return op.Stop();
    }

bool INGRRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void INGRRecord::IsNoAutoCalc(bool value)
    {
    SETBIT(ENIT.value.flags, fIsNoAutoCalc, value);
    }

bool INGRRecord::IsFood()
    {
    return (ENIT.value.flags & fIsFood) != 0;
    }

void INGRRecord::IsFood(bool value)
    {
    SETBIT(ENIT.value.flags, fIsFood, value);
    }

bool INGRRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void INGRRecord::SetFlagMask(uint8_t Mask)
    {
    ENIT.value.flags = Mask;
    }

bool INGRRecord::IsNone()
    {
    return (ETYP.value == eNone);
    }

void INGRRecord::IsNone(bool value)
    {
    ETYP.value = value ? eNone : eBigGuns;
    }

bool INGRRecord::IsBigGuns()
    {
    return (ETYP.value == eBigGuns);
    }

void INGRRecord::IsBigGuns(bool value)
    {
    ETYP.value = value ? eBigGuns : eNone;
    }

bool INGRRecord::IsEnergyWeapons()
    {
    return (ETYP.value == eEnergyWeapons);
    }

void INGRRecord::IsEnergyWeapons(bool value)
    {
    ETYP.value = value ? eEnergyWeapons : eNone;
    }

bool INGRRecord::IsSmallGuns()
    {
    return (ETYP.value == eSmallGuns);
    }

void INGRRecord::IsSmallGuns(bool value)
    {
    ETYP.value = value ? eSmallGuns : eNone;
    }

bool INGRRecord::IsMeleeWeapons()
    {
    return (ETYP.value == eMeleeWeapons);
    }

void INGRRecord::IsMeleeWeapons(bool value)
    {
    ETYP.value = value ? eMeleeWeapons : eNone;
    }

bool INGRRecord::IsUnarmedWeapon()
    {
    return (ETYP.value == eUnarmedWeapon);
    }

void INGRRecord::IsUnarmedWeapon(bool value)
    {
    ETYP.value = value ? eUnarmedWeapon : eNone;
    }

bool INGRRecord::IsThrownWeapons()
    {
    return (ETYP.value == eThrownWeapons);
    }

void INGRRecord::IsThrownWeapons(bool value)
    {
    ETYP.value = value ? eThrownWeapons : eNone;
    }

bool INGRRecord::IsMine()
    {
    return (ETYP.value == eMine);
    }

void INGRRecord::IsMine(bool value)
    {
    ETYP.value = value ? eMine : eNone;
    }

bool INGRRecord::IsBodyWear()
    {
    return (ETYP.value == eBodyWear);
    }

void INGRRecord::IsBodyWear(bool value)
    {
    ETYP.value = value ? eBodyWear : eNone;
    }

bool INGRRecord::IsHeadWear()
    {
    return (ETYP.value == eHeadWear);
    }

void INGRRecord::IsHeadWear(bool value)
    {
    ETYP.value = value ? eHeadWear : eNone;
    }

bool INGRRecord::IsHandWear()
    {
    return (ETYP.value == eHandWear);
    }

void INGRRecord::IsHandWear(bool value)
    {
    ETYP.value = value ? eHandWear : eNone;
    }

bool INGRRecord::IsChems()
    {
    return (ETYP.value == eChems);
    }

void INGRRecord::IsChems(bool value)
    {
    ETYP.value = value ? eChems : eNone;
    }

bool INGRRecord::IsStimpack()
    {
    return (ETYP.value == eStimpack);
    }

void INGRRecord::IsStimpack(bool value)
    {
    ETYP.value = value ? eStimpack : eNone;
    }

bool INGRRecord::IsEdible()
    {
    return (ETYP.value == eEdible);
    }

void INGRRecord::IsEdible(bool value)
    {
    ETYP.value = value ? eEdible : eNone;
    }

bool INGRRecord::IsAlcohol()
    {
    return (ETYP.value == eAlcohol);
    }

void INGRRecord::IsAlcohol(bool value)
    {
    ETYP.value = value ? eAlcohol : eNone;
    }

bool INGRRecord::IsEquipmentType(int32_t Type)
    {
    return ETYP.value == Type;
    }

void INGRRecord::SetEquipmentType(int32_t Type)
    {
    ETYP.value = Type;
    }

uint32_t INGRRecord::GetType()
    {
    return REV32(INGR);
    }

char * INGRRecord::GetStrType()
    {
    return "INGR";
    }

int32_t INGRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(ETYP):
                ETYP.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ENIT):
                ENIT.Read(buffer, subSize);
                break;
            case REV32(EFID):
                Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new FNVEffect);
                Effects.value.back()->CTDA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  INGR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t INGRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    ETYP.Unload();
    DATA.Unload();
    ENIT.Unload();
    Effects.Unload();
    return 1;
    }

int32_t INGRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    WRITE(ETYP);
    WRITE(DATA);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
    }

bool INGRRecord::operator ==(const INGRRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            MODL == other.MODL &&
            Effects == other.Effects);
    }

bool INGRRecord::operator !=(const INGRRecord &other) const
    {
    return !(*this == other);
    }

bool INGRRecord::equals(Record *other)
    {
    return *this == *(INGRRecord *)other;
    }
}