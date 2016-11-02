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
#include "ASPCRecord.h"

namespace FNV
{
ASPCRecord::ASPCRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

ASPCRecord::ASPCRecord(ASPCRecord *srcRecord):
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
    DawnSNAM = srcRecord->DawnSNAM;
    AfternoonSNAM = srcRecord->AfternoonSNAM;
    DuskSNAM = srcRecord->DuskSNAM;
    NightSNAM = srcRecord->NightSNAM;
    WallaSNAM = srcRecord->WallaSNAM;
    WNAM = srcRecord->WNAM;
    RDAT = srcRecord->RDAT;
    ANAM = srcRecord->ANAM;
    INAM = srcRecord->INAM;
    return;
    }

ASPCRecord::~ASPCRecord()
    {
    //
    }

bool ASPCRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(DawnSNAM.value);
    op.Accept(AfternoonSNAM.value);
    op.Accept(DuskSNAM.value);
    op.Accept(NightSNAM.value);
    op.Accept(WallaSNAM.value);

    if(RDAT.IsLoaded())
        op.Accept(RDAT.value);

    return op.Stop();
    }

bool ASPCRecord::IsEnvironmentNone()
    {
    return (ANAM.value == eNone);
    }

void ASPCRecord::IsEnvironmentNone(bool value)
    {
    ANAM.value = value ? eNone : eDefault;
    }

bool ASPCRecord::IsEnvironmentDefault()
    {
    return (ANAM.value == eDefault);
    }

void ASPCRecord::IsEnvironmentDefault(bool value)
    {
    ANAM.value = value ? eDefault : eNone;
    }

bool ASPCRecord::IsEnvironmentGeneric()
    {
    return (ANAM.value == eGeneric);
    }

void ASPCRecord::IsEnvironmentGeneric(bool value)
    {
    ANAM.value = value ? eGeneric : eDefault;
    }

bool ASPCRecord::IsEnvironmentPaddedCell()
    {
    return (ANAM.value == ePaddedCell);
    }

void ASPCRecord::IsEnvironmentPaddedCell(bool value)
    {
    ANAM.value = value ? ePaddedCell : eDefault;
    }

bool ASPCRecord::IsEnvironmentRoom()
    {
    return (ANAM.value == eRoom);
    }

void ASPCRecord::IsEnvironmentRoom(bool value)
    {
    ANAM.value = value ? eRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentBathroom()
    {
    return (ANAM.value == eBathroom);
    }

void ASPCRecord::IsEnvironmentBathroom(bool value)
    {
    ANAM.value = value ? eBathroom : eDefault;
    }

bool ASPCRecord::IsEnvironmentLivingroom()
    {
    return (ANAM.value == eLivingroom);
    }

void ASPCRecord::IsEnvironmentLivingroom(bool value)
    {
    ANAM.value = value ? eLivingroom : eDefault;
    }

bool ASPCRecord::IsEnvironmentStoneRoom()
    {
    return (ANAM.value == eStoneRoom);
    }

void ASPCRecord::IsEnvironmentStoneRoom(bool value)
    {
    ANAM.value = value ? eStoneRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentAuditorium()
    {
    return (ANAM.value == eAuditorium);
    }

void ASPCRecord::IsEnvironmentAuditorium(bool value)
    {
    ANAM.value = value ? eAuditorium : eDefault;
    }

bool ASPCRecord::IsEnvironmentConcerthall()
    {
    return (ANAM.value == eConcerthall);
    }

void ASPCRecord::IsEnvironmentConcerthall(bool value)
    {
    ANAM.value = value ? eConcerthall : eDefault;
    }

bool ASPCRecord::IsEnvironmentCave()
    {
    return (ANAM.value == eCave);
    }

void ASPCRecord::IsEnvironmentCave(bool value)
    {
    ANAM.value = value ? eCave : eDefault;
    }

bool ASPCRecord::IsEnvironmentArena()
    {
    return (ANAM.value == eArena);
    }

void ASPCRecord::IsEnvironmentArena(bool value)
    {
    ANAM.value = value ? eArena : eDefault;
    }

bool ASPCRecord::IsEnvironmentHangar()
    {
    return (ANAM.value == eHangar);
    }

void ASPCRecord::IsEnvironmentHangar(bool value)
    {
    ANAM.value = value ? eHangar : eDefault;
    }

bool ASPCRecord::IsEnvironmentCarpetedHallway()
    {
    return (ANAM.value == eCarpetedHallway);
    }

void ASPCRecord::IsEnvironmentCarpetedHallway(bool value)
    {
    ANAM.value = value ? eCarpetedHallway : eDefault;
    }

bool ASPCRecord::IsEnvironmentHallway()
    {
    return (ANAM.value == eHallway);
    }

void ASPCRecord::IsEnvironmentHallway(bool value)
    {
    ANAM.value = value ? eHallway : eDefault;
    }

bool ASPCRecord::IsEnvironmentStoneCorridor()
    {
    return (ANAM.value == eStoneCorridor);
    }

void ASPCRecord::IsEnvironmentStoneCorridor(bool value)
    {
    ANAM.value = value ? eStoneCorridor : eDefault;
    }

bool ASPCRecord::IsEnvironmentAlley()
    {
    return (ANAM.value == eAlley);
    }

void ASPCRecord::IsEnvironmentAlley(bool value)
    {
    ANAM.value = value ? eAlley : eDefault;
    }

bool ASPCRecord::IsEnvironmentForest()
    {
    return (ANAM.value == eForest);
    }

void ASPCRecord::IsEnvironmentForest(bool value)
    {
    ANAM.value = value ? eForest : eDefault;
    }

bool ASPCRecord::IsEnvironmentCity()
    {
    return (ANAM.value == eCity);
    }

void ASPCRecord::IsEnvironmentCity(bool value)
    {
    ANAM.value = value ? eCity : eDefault;
    }

bool ASPCRecord::IsEnvironmentMountains()
    {
    return (ANAM.value == eMountains);
    }

void ASPCRecord::IsEnvironmentMountains(bool value)
    {
    ANAM.value = value ? eMountains : eDefault;
    }

bool ASPCRecord::IsEnvironmentQuarry()
    {
    return (ANAM.value == eQuarry);
    }

void ASPCRecord::IsEnvironmentQuarry(bool value)
    {
    ANAM.value = value ? eQuarry : eDefault;
    }

bool ASPCRecord::IsEnvironmentPlain()
    {
    return (ANAM.value == ePlain);
    }

void ASPCRecord::IsEnvironmentPlain(bool value)
    {
    ANAM.value = value ? ePlain : eDefault;
    }

bool ASPCRecord::IsEnvironmentParkinglot()
    {
    return (ANAM.value == eParkinglot);
    }

void ASPCRecord::IsEnvironmentParkinglot(bool value)
    {
    ANAM.value = value ? eParkinglot : eDefault;
    }

bool ASPCRecord::IsEnvironmentSewerpipe()
    {
    return (ANAM.value == eSewerpipe);
    }

void ASPCRecord::IsEnvironmentSewerpipe(bool value)
    {
    ANAM.value = value ? eSewerpipe : eDefault;
    }

bool ASPCRecord::IsEnvironmentUnderwater()
    {
    return (ANAM.value == eUnderwater);
    }

void ASPCRecord::IsEnvironmentUnderwater(bool value)
    {
    ANAM.value = value ? eUnderwater : eDefault;
    }

bool ASPCRecord::IsEnvironmentSmallRoom()
    {
    return (ANAM.value == eSmallRoom);
    }

void ASPCRecord::IsEnvironmentSmallRoom(bool value)
    {
    ANAM.value = value ? eSmallRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentMediumRoom()
    {
    return (ANAM.value == eMediumRoom);
    }

void ASPCRecord::IsEnvironmentMediumRoom(bool value)
    {
    ANAM.value = value ? eMediumRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentLargeRoom()
    {
    return (ANAM.value == eLargeRoom);
    }

void ASPCRecord::IsEnvironmentLargeRoom(bool value)
    {
    ANAM.value = value ? eLargeRoom : eDefault;
    }

bool ASPCRecord::IsEnvironmentMediumHall()
    {
    return (ANAM.value == eMediumHall);
    }

void ASPCRecord::IsEnvironmentMediumHall(bool value)
    {
    ANAM.value = value ? eMediumHall : eDefault;
    }

bool ASPCRecord::IsEnvironmentLargeHall()
    {
    return (ANAM.value == eLargeHall);
    }

void ASPCRecord::IsEnvironmentLargeHall(bool value)
    {
    ANAM.value = value ? eLargeHall : eDefault;
    }

bool ASPCRecord::IsEnvironmentPlate()
    {
    return (ANAM.value == ePlate);
    }

void ASPCRecord::IsEnvironmentPlate(bool value)
    {
    ANAM.value = value ? ePlate : eDefault;
    }

bool ASPCRecord::IsEnvironmentType(uint32_t Type)
    {
    return ANAM.value == Type;
    }

void ASPCRecord::SetEnvironmentType(uint32_t Type)
    {
    ANAM.value = Type;
    }

bool ASPCRecord::IsSpaceExterior()
    {
    return (INAM.value == eIsExterior);
    }

void ASPCRecord::IsSpaceExterior(bool value)
    {
    INAM.value = value ? eIsExterior : eIsInterior;
    }

bool ASPCRecord::IsSpaceInterior()
    {
    return (INAM.value == eIsInterior);
    }

void ASPCRecord::IsSpaceInterior(bool value)
    {
    INAM.value = value ? eIsInterior : eIsExterior;
    }

bool ASPCRecord::IsSpaceType(uint32_t Type)
    {
    return INAM.value == Type;
    }

void ASPCRecord::SetSpaceType(uint32_t Type)
    {
    INAM.value = Type;
    }

uint32_t ASPCRecord::GetType()
    {
    return REV32(ASPC);
    }

char * ASPCRecord::GetStrType()
    {
    return "ASPC";
    }

int32_t ASPCRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t curSNAM = 0;
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
            case REV32(SNAM):
                switch(curSNAM)
                    {
                    case 0:
                        DawnSNAM.Read(buffer, subSize);
                        break;
                    case 1:
                        AfternoonSNAM.Read(buffer, subSize);
                        break;
                    case 2:
                        DuskSNAM.Read(buffer, subSize);
                        break;
                    case 3:
                        NightSNAM.Read(buffer, subSize);
                        break;
                    case 4:
                        WallaSNAM.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  ASPC: %08X - Unexpected SNAM\n", formID);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                ++curSNAM;
                break;
            case REV32(WNAM):
                WNAM.Read(buffer, subSize);
                break;
            case REV32(RDAT):
                RDAT.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ASPC: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t ASPCRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    DawnSNAM.Unload();
    AfternoonSNAM.Unload();
    DuskSNAM.Unload();
    NightSNAM.Unload();
    WallaSNAM.Unload();
    WNAM.Unload();
    RDAT.Unload();
    ANAM.Unload();
    INAM.Unload();
    return 1;
    }

int32_t ASPCRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITEAS(DawnSNAM,SNAM);
    WRITEAS(AfternoonSNAM,SNAM);
    WRITEAS(DuskSNAM,SNAM);
    WRITEAS(NightSNAM,SNAM);
    WRITEAS(WallaSNAM,SNAM);
    WRITE(WNAM);
    WRITE(RDAT);
    WRITE(ANAM);
    WRITE(INAM);
    return -1;
    }

bool ASPCRecord::operator ==(const ASPCRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            DawnSNAM == other.DawnSNAM &&
            AfternoonSNAM == other.AfternoonSNAM &&
            DuskSNAM == other.DuskSNAM &&
            NightSNAM == other.NightSNAM &&
            WallaSNAM == other.WallaSNAM &&
            WNAM == other.WNAM &&
            RDAT == other.RDAT &&
            ANAM == other.ANAM &&
            INAM == other.INAM);
    }

bool ASPCRecord::operator !=(const ASPCRecord &other) const
    {
    return !(*this == other);
    }

bool ASPCRecord::equals(Record *other)
    {
    return *this == *(ASPCRecord *)other;
    }
}