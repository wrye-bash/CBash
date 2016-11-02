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

namespace Ob
{
CLASRecord::CLASDATA::CLASDATA():
    specialization(0),
    flags(0),
    services(0),
    trainSkill(0),
    trainLevel(0)
    {
    primary[0]=0;
    primary[1]=1;
    major[0]=12;
    major[1]=13;
    major[2]=14;
    major[3]=15;
    major[4]=16;
    major[5]=17;
    major[6]=18;
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

CLASRecord::CLASDATA::~CLASDATA()
    {
    //
    }

bool CLASRecord::CLASDATA::operator ==(const CLASDATA &other) const
    {
    return (primary[0] == other.primary[0] &&
            primary[1] == other.primary[1] &&
            specialization == other.specialization &&
            major[0] == other.major[0] &&
            major[1] == other.major[1] &&
            major[2] == other.major[2] &&
            major[3] == other.major[3] &&
            major[4] == other.major[4] &&
            major[5] == other.major[5] &&
            major[6] == other.major[6] &&
            flags == other.flags &&
            services == other.services &&
            trainSkill == other.trainSkill &&
            trainLevel == other.trainLevel);
    }

bool CLASRecord::CLASDATA::operator !=(const CLASDATA &other) const
    {
    return !(*this == other);
    }

CLASRecord::CLASRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

CLASRecord::CLASRecord(CLASRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
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
    return (DATA.value.services & fWeapons) != 0;
    }

void CLASRecord::IsServicesWeapons(bool value)
    {
    SETBIT(DATA.value.services, fWeapons, value);
    }

bool CLASRecord::IsServicesArmor()
    {
    return (DATA.value.services & fArmor) != 0;
    }

void CLASRecord::IsServicesArmor(bool value)
    {
    SETBIT(DATA.value.services, fArmor, value);
    }

bool CLASRecord::IsServicesClothing()
    {
    return (DATA.value.services & fClothing) != 0;
    }

void CLASRecord::IsServicesClothing(bool value)
    {
    SETBIT(DATA.value.services, fClothing, value);
    }

bool CLASRecord::IsServicesBooks()
    {
    return (DATA.value.services & fBooks) != 0;
    }

void CLASRecord::IsServicesBooks(bool value)
    {
    SETBIT(DATA.value.services, fBooks, value);
    }

bool CLASRecord::IsServicesIngredients()
    {
    return (DATA.value.services & fIngredients) != 0;
    }

void CLASRecord::IsServicesIngredients(bool value)
    {
    SETBIT(DATA.value.services, fIngredients, value);
    }

bool CLASRecord::IsServicesLights()
    {
    return (DATA.value.services & fLights) != 0;
    }

void CLASRecord::IsServicesLights(bool value)
    {
    SETBIT(DATA.value.services, fLights, value);
    }

bool CLASRecord::IsServicesApparatus()
    {
    return (DATA.value.services & fApparatus) != 0;
    }

void CLASRecord::IsServicesApparatus(bool value)
    {
    SETBIT(DATA.value.services, fApparatus, value);
    }

bool CLASRecord::IsServicesMiscItems()
    {
    return (DATA.value.services & fMiscItems) != 0;
    }

void CLASRecord::IsServicesMiscItems(bool value)
    {
    SETBIT(DATA.value.services, fMiscItems, value);
    }

bool CLASRecord::IsServicesSpells()
    {
    return (DATA.value.services & fSpells) != 0;
    }

void CLASRecord::IsServicesSpells(bool value)
    {
    SETBIT(DATA.value.services, fSpells, value);
    }

bool CLASRecord::IsServicesMagicItems()
    {
    return (DATA.value.services & fMagicItems) != 0;
    }

void CLASRecord::IsServicesMagicItems(bool value)
    {
    SETBIT(DATA.value.services, fMagicItems, value);
    }

bool CLASRecord::IsServicesPotions()
    {
    return (DATA.value.services & fPotions) != 0;
    }

void CLASRecord::IsServicesPotions(bool value)
    {
    SETBIT(DATA.value.services, fPotions, value);
    }

bool CLASRecord::IsServicesTraining()
    {
    return (DATA.value.services & fTraining) != 0;
    }

void CLASRecord::IsServicesTraining(bool value)
    {
    SETBIT(DATA.value.services, fTraining, value);
    }

bool CLASRecord::IsServicesRecharge()
    {
    return (DATA.value.services & fRecharge) != 0;
    }

void CLASRecord::IsServicesRecharge(bool value)
    {
    SETBIT(DATA.value.services, fRecharge, value);
    }

bool CLASRecord::IsServicesRepair()
    {
    return (DATA.value.services & fRepair) != 0;
    }

void CLASRecord::IsServicesRepair(bool value)
    {
    SETBIT(DATA.value.services, fRepair, value);
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CLAS: Unknown subType = %04X\n", subType);
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
    DATA.Unload();
    return 1;
    }

int32_t CLASRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(DATA);
    return -1;
    }

bool CLASRecord::operator ==(const CLASRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            DATA == other.DATA);
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