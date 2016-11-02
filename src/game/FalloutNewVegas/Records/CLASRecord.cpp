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
#include "CLASRecord.h"

namespace FNV
{
CLASRecord::CLASDATA::CLASDATA():
    flags(0),
    services(0),
    trainSkill(0),
    trainLevel(0)
    {
    tagSkills[0] = 0;
    tagSkills[1] = 0;
    tagSkills[2] = 0;
    tagSkills[3] = 0;
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

CLASRecord::CLASDATA::~CLASDATA()
    {
    //
    }

bool CLASRecord::CLASDATA::operator ==(const CLASDATA &other) const
    {
    return (tagSkills[0] == other.tagSkills[0] &&
            tagSkills[1] == other.tagSkills[1] &&
            tagSkills[2] == other.tagSkills[2] &&
            tagSkills[3] == other.tagSkills[3] &&
            flags == other.flags &&
            services == other.services &&
            trainSkill == other.trainSkill &&
            trainLevel == other.trainLevel);
    }

bool CLASRecord::CLASDATA::operator !=(const CLASDATA &other) const
    {
    return !(*this == other);
    }

CLASRecord::CLASATTR::CLASATTR():
    strength(0),
    perception(0),
    endurance(0),
    charisma(0),
    intelligence(0),
    agility(0),
    luck(0)
    {
    //
    }

CLASRecord::CLASATTR::~CLASATTR()
    {
    //
    }

bool CLASRecord::CLASATTR::operator ==(const CLASATTR &other) const
    {
    return (strength == other.strength &&
            perception == other.perception &&
            endurance == other.endurance &&
            charisma == other.charisma &&
            intelligence == other.intelligence &&
            agility == other.agility &&
            luck == other.luck);
    }

bool CLASRecord::CLASATTR::operator !=(const CLASATTR &other) const
    {
    return !(*this == other);
    }

CLASRecord::CLASRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CLASRecord::CLASRecord(CLASRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    ATTR = srcRecord->ATTR;
    return;
    }

CLASRecord::~CLASRecord()
    {
    //
    }

bool CLASRecord::IsPlayable()
    {
    return (DATA.value.flags & fIsPlayable) != 0;
    }

void CLASRecord::IsPlayable(bool value)
    {
    SETBIT(DATA.value.flags, fIsPlayable, value);
    }

bool CLASRecord::IsGuard()
    {
    return (DATA.value.flags & fIsGuard) != 0;
    }

void CLASRecord::IsGuard(bool value)
    {
    SETBIT(DATA.value.flags, fIsGuard, value);
    }

bool CLASRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void CLASRecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

bool CLASRecord::IsServicesWeapons()
    {
    return (DATA.value.services & fIsServicesWeapons) != 0;
    }

void CLASRecord::IsServicesWeapons(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesWeapons, value);
    }

bool CLASRecord::IsServicesArmor()
    {
    return (DATA.value.services & fIsServicesArmor) != 0;
    }

void CLASRecord::IsServicesArmor(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesArmor, value);
    }

bool CLASRecord::IsServicesClothing()
    {
    return (DATA.value.services & fIsServicesClothing) != 0;
    }

void CLASRecord::IsServicesClothing(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesClothing, value);
    }

bool CLASRecord::IsServicesBooks()
    {
    return (DATA.value.services & fIsServicesBooks) != 0;
    }

void CLASRecord::IsServicesBooks(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesBooks, value);
    }

bool CLASRecord::IsServicesFood()
    {
    return (DATA.value.services & fIsServicesFood) != 0;
    }

void CLASRecord::IsServicesFood(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesFood, value);
    }

bool CLASRecord::IsServicesChems()
    {
    return (DATA.value.services & fIsServicesChems) != 0;
    }

void CLASRecord::IsServicesChems(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesChems, value);
    }

bool CLASRecord::IsServicesStimpacks()
    {
    return (DATA.value.services & fIsServicesStimpacks) != 0;
    }

void CLASRecord::IsServicesStimpacks(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesStimpacks, value);
    }

bool CLASRecord::IsServicesLights()
    {
    return (DATA.value.services & fIsServicesLights) != 0;
    }

void CLASRecord::IsServicesLights(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesLights, value);
    }

bool CLASRecord::IsServicesMiscItems()
    {
    return (DATA.value.services & fIsServicesMiscItems) != 0;
    }

void CLASRecord::IsServicesMiscItems(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesMiscItems, value);
    }

bool CLASRecord::IsServicesPotions()
    {
    return (DATA.value.services & fIsServicesPotions) != 0;
    }

void CLASRecord::IsServicesPotions(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesPotions, value);
    }

bool CLASRecord::IsServicesTraining()
    {
    return (DATA.value.services & fIsServicesTraining) != 0;
    }

void CLASRecord::IsServicesTraining(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesTraining, value);
    }

bool CLASRecord::IsServicesRecharge()
    {
    return (DATA.value.services & fIsServicesRecharge) != 0;
    }

void CLASRecord::IsServicesRecharge(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesRecharge, value);
    }

bool CLASRecord::IsServicesRepair()
    {
    return (DATA.value.services & fIsServicesRepair) != 0;
    }

void CLASRecord::IsServicesRepair(bool value)
    {
    SETBIT(DATA.value.services, fIsServicesRepair, value);
    }

bool CLASRecord::IsServicesFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.services & Mask) == Mask) : ((DATA.value.services & Mask) != 0);
    }

void CLASRecord::SetServicesFlagMask(uint32_t Mask)
    {
    DATA.value.services = Mask;
    }

uint32_t CLASRecord::GetType()
    {
    return REV32(CLAS);
    }

char * CLASRecord::GetStrType()
    {
    return "CLAS";
    }

int32_t CLASRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ATTR):
                ATTR.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CLAS: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CLASRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    DATA.Unload();
    ATTR.Unload();
    return 1;
    }

int32_t CLASRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITEREQ(DESC);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DATA);
    WRITE(ATTR);
    return -1;
    }

bool CLASRecord::operator ==(const CLASRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DATA == other.DATA &&
            ATTR == other.ATTR);
    }

bool CLASRecord::operator !=(const CLASRecord &other) const
    {
    return !(*this == other);
    }

bool CLASRecord::equals(Record *other)
    {
    return *this == *(CLASRecord *)other;
    }
}