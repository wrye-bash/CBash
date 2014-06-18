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
#include "LTEXRecord.h"

namespace Ob
{
LTEXRecord::LTEXHNAM::LTEXHNAM():
    types(2),
    friction(30),
    restitution(30)
    {
    //
    }

LTEXRecord::LTEXHNAM::~LTEXHNAM()
    {
    //
    }

bool LTEXRecord::LTEXHNAM::operator ==(const LTEXHNAM &other) const
    {
    return (types == other.types &&
            friction == other.friction &&
            restitution == other.restitution);
    }
bool LTEXRecord::LTEXHNAM::operator !=(const LTEXHNAM &other) const
    {
    return !(*this == other);
    }

LTEXRecord::LTEXRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    HNAM = srcRecord->HNAM;
    SNAM = srcRecord->SNAM;
    GNAM = srcRecord->GNAM;
    return;
    }

LTEXRecord::~LTEXRecord()
    {
    //
    }

bool LTEXRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < GNAM.value.size(); ListIndex++)
        op.Accept(GNAM.value[ListIndex]);

    return op.Stop();
    }

bool LTEXRecord::IsStone()
    {
    HNAM.Load();
    return (HNAM->types == eStone);
    }

void LTEXRecord::IsStone(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eStone : eCloth;
    }

bool LTEXRecord::IsCloth()
    {
    HNAM.Load();
    return (HNAM->types == eCloth);
    }

void LTEXRecord::IsCloth(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eCloth : eDirt;
    }

bool LTEXRecord::IsDirt()
    {
    HNAM.Load();
    return (HNAM->types == eDirt);
    }

void LTEXRecord::IsDirt(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eDirt : eDirt;
    }

bool LTEXRecord::IsGlass()
    {
    HNAM.Load();
    return (HNAM->types == eGlass);
    }

void LTEXRecord::IsGlass(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGlass : eDirt;
    }

bool LTEXRecord::IsGrass()
    {
    HNAM.Load();
    return (HNAM->types == eGrass);
    }

void LTEXRecord::IsGrass(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGrass : eDirt;
    }

bool LTEXRecord::IsMetal()
    {
    HNAM.Load();
    return (HNAM->types == eMetal);
    }

void LTEXRecord::IsMetal(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eMetal : eDirt;
    }

bool LTEXRecord::IsOrganic()
    {
    HNAM.Load();
    return (HNAM->types == eOrganic);
    }

void LTEXRecord::IsOrganic(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eOrganic : eDirt;
    }

bool LTEXRecord::IsSkin()
    {
    HNAM.Load();
    return (HNAM->types == eSkin);
    }

void LTEXRecord::IsSkin(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSkin : eDirt;
    }

bool LTEXRecord::IsWater()
    {
    HNAM.Load();
    return (HNAM->types == eWater);
    }

void LTEXRecord::IsWater(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWater : eDirt;
    }

bool LTEXRecord::IsWood()
    {
    HNAM.Load();
    return (HNAM->types == eWood);
    }

void LTEXRecord::IsWood(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWood : eDirt;
    }

bool LTEXRecord::IsHeavyStone()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyStone);
    }

void LTEXRecord::IsHeavyStone(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyStone : eDirt;
    }

bool LTEXRecord::IsHeavyMetal()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyMetal);
    }

void LTEXRecord::IsHeavyMetal(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyMetal : eDirt;
    }

bool LTEXRecord::IsHeavyWood()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyWood);
    }

void LTEXRecord::IsHeavyWood(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyWood : eDirt;
    }

bool LTEXRecord::IsChain()
    {
    HNAM.Load();
    return (HNAM->types == eChain);
    }

void LTEXRecord::IsChain(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eChain : eDirt;
    }

bool LTEXRecord::IsSnow()
    {
    HNAM.Load();
    return (HNAM->types == eSnow);
    }

void LTEXRecord::IsSnow(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSnow : eDirt;
    }
bool LTEXRecord::IsStoneStairs()
    {
    HNAM.Load();
    return (HNAM->types == eStoneStairs);
    }

void LTEXRecord::IsStoneStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eStoneStairs : eDirt;
    }

bool LTEXRecord::IsClothStairs()
    {
    HNAM.Load();
    return (HNAM->types == eClothStairs);
    }

void LTEXRecord::IsClothStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eClothStairs : eDirt;
    }

bool LTEXRecord::IsDirtStairs()
    {
    HNAM.Load();
    return (HNAM->types == eDirtStairs);
    }

void LTEXRecord::IsDirtStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eDirtStairs : eDirt;
    }

bool LTEXRecord::IsGlassStairs()
    {
    HNAM.Load();
    return (HNAM->types == eGlassStairs);
    }

void LTEXRecord::IsGlassStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGlassStairs : eDirt;
    }

bool LTEXRecord::IsGrassStairs()
    {
    HNAM.Load();
    return (HNAM->types == eGrassStairs);
    }

void LTEXRecord::IsGrassStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eGrassStairs : eDirt;
    }

bool LTEXRecord::IsMetalStairs()
    {
    HNAM.Load();
    return (HNAM->types == eMetalStairs);
    }

void LTEXRecord::IsMetalStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eMetalStairs : eDirt;
    }

bool LTEXRecord::IsOrganicStairs()
    {
    HNAM.Load();
    return (HNAM->types == eOrganicStairs);
    }

void LTEXRecord::IsOrganicStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eOrganicStairs : eDirt;
    }

bool LTEXRecord::IsSkinStairs()
    {
    HNAM.Load();
    return (HNAM->types == eSkinStairs);
    }

void LTEXRecord::IsSkinStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSkinStairs : eDirt;
    }

bool LTEXRecord::IsWaterStairs()
    {
    HNAM.Load();
    return (HNAM->types == eWaterStairs);
    }

void LTEXRecord::IsWaterStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWaterStairs : eDirt;
    }

bool LTEXRecord::IsWoodStairs()
    {
    HNAM.Load();
    return (HNAM->types == eWoodStairs);
    }

void LTEXRecord::IsWoodStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eWoodStairs : eDirt;
    }

bool LTEXRecord::IsHeavyStoneStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyStoneStairs);
    }

void LTEXRecord::IsHeavyStoneStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyStoneStairs : eDirt;
    }

bool LTEXRecord::IsHeavyMetalStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyMetalStairs);
    }

void LTEXRecord::IsHeavyMetalStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyMetalStairs : eDirt;
    }

bool LTEXRecord::IsHeavyWoodStairs()
    {
    HNAM.Load();
    return (HNAM->types == eHeavyWoodStairs);
    }

void LTEXRecord::IsHeavyWoodStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eHeavyWoodStairs : eDirt;
    }

bool LTEXRecord::IsChainStairs()
    {
    HNAM.Load();
    return (HNAM->types == eChainStairs);
    }

void LTEXRecord::IsChainStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eChainStairs : eDirt;
    }

bool LTEXRecord::IsSnowStairs()
    {
    HNAM.Load();
    return (HNAM->types == eSnowStairs);
    }

void LTEXRecord::IsSnowStairs(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eSnowStairs : eDirt;
    }

bool LTEXRecord::IsElevator()
    {
    HNAM.Load();
    return (HNAM->types == eElevator);
    }

void LTEXRecord::IsElevator(bool value)
    {
    HNAM.Load();
    HNAM->types = value ? eElevator : eDirt;
    }

bool LTEXRecord::IsType(uint8_t Type)
    {
    HNAM.Load();
    return (HNAM->types == Type);
    }

void LTEXRecord::SetType(uint8_t Type)
    {
    HNAM.Load();
    HNAM->types = Type;
    }

uint32_t LTEXRecord::GetType()
    {
    return REV32(LTEX);
    }

char * LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

int32_t LTEXRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LTEX: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t LTEXRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    ICON.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.Unload();
    return 1;
    }

int32_t LTEXRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(HNAM);
    WRITE(SNAM);
    WRITE(GNAM);
    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    return (HNAM == other.HNAM &&
            SNAM == other.SNAM &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            GNAM == other.GNAM);
    }

bool LTEXRecord::operator !=(const LTEXRecord &other) const
    {
    return !(*this == other);
    }

bool LTEXRecord::equals(Record *other)
    {
    return *this == *(LTEXRecord *)other;
    }
}