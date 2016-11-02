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
#include "RACERecord.h"

namespace Ob
{
RACERecord::RACEATTR::RACEATTR():
    maleStrength(50), maleIntelligence(50),
    maleWillpower(50), maleAgility(50),
    maleSpeed(50), maleEndurance(50),
    malePersonality(50), maleLuck(50),
    femaleStrength(50), femaleIntelligence(50),
    femaleWillpower(50), femaleAgility(50),
    femaleSpeed(50), femaleEndurance(50),
    femalePersonality(50), femaleLuck(50)
    {
    //
    }

RACERecord::RACEATTR::~RACEATTR()
    {
    //
    }

bool RACERecord::RACEATTR::operator ==(const RACEATTR &other) const
    {
    return (maleStrength == other.maleStrength &&
            maleIntelligence == other.maleIntelligence &&
            maleWillpower == other.maleWillpower &&
            maleAgility == other.maleAgility &&
            maleSpeed == other.maleSpeed &&
            maleEndurance == other.maleEndurance &&
            malePersonality == other.malePersonality &&
            maleLuck == other.maleLuck &&
            femaleStrength == other.femaleStrength &&
            femaleIntelligence == other.femaleIntelligence &&
            femaleWillpower == other.femaleWillpower &&
            femaleAgility == other.femaleAgility &&
            femaleSpeed == other.femaleSpeed &&
            femaleEndurance == other.femaleEndurance &&
            femalePersonality == other.femalePersonality &&
            femaleLuck == other.femaleLuck);
    }

bool RACERecord::RACEATTR::operator !=(const RACEATTR &other) const
    {
    return !(*this == other);
    }

void RACERecord::RACEMODEL::Write(FileWriter &writer)
    {
    if(MODL.IsLoaded())
        {
        WRITE(MODL);
        WRITE(MODB);
        WRITE(MODT);
        }
    WRITE(ICON);
    }

bool RACERecord::RACEMODEL::operator ==(const RACEMODEL &other) const
    {
    return (MODB == other.MODB &&
            MODL.equalsi(other.MODL) &&
            ICON.equalsi(other.ICON) &&
            MODT == other.MODT);
    }

bool RACERecord::RACEMODEL::operator !=(const RACEMODEL &other) const
    {
    return !(*this == other);
    }

RACERecord::RACERecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

RACERecord::RACERecord(RACERecord *srcRecord):
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
    SPLO = srcRecord->SPLO;
    XNAM = srcRecord->XNAM;
    DATA = srcRecord->DATA;
    VNAM = srcRecord->VNAM;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    PNAM = srcRecord->PNAM;
    UNAM = srcRecord->UNAM;
    ATTR = srcRecord->ATTR;
    MOD0 = srcRecord->MOD0;
    MOD1 = srcRecord->MOD1;
    MOD2 = srcRecord->MOD2;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    MOD5 = srcRecord->MOD5;
    MOD6 = srcRecord->MOD6;
    MOD7 = srcRecord->MOD7;
    MOD8 = srcRecord->MOD8;
    MMODL = srcRecord->MMODL;
    MICON0 = srcRecord->MICON0;
    MICON1 = srcRecord->MICON1;
    MICON2 = srcRecord->MICON2;
    MICON3 = srcRecord->MICON3;
    MICON4 = srcRecord->MICON4;
    FMODL = srcRecord->FMODL;
    FICON0 = srcRecord->FICON0;
    FICON1 = srcRecord->FICON1;
    FICON2 = srcRecord->FICON2;
    FICON3 = srcRecord->FICON3;
    FICON4 = srcRecord->FICON4;
    HNAM = srcRecord->HNAM;
    ENAM = srcRecord->ENAM;
    FGGS = srcRecord->FGGS;
    FGGA = srcRecord->FGGA;
    FGTS = srcRecord->FGTS;
    SNAM = srcRecord->SNAM;
    }

RACERecord::~RACERecord()
    {
    //
    }

bool RACERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < SPLO.value.size(); ListIndex++)
        op.Accept(SPLO.value[ListIndex]);
    for(uint32_t ListIndex = 0; ListIndex < XNAM.value.size(); ListIndex++)
        op.Accept(XNAM.value[ListIndex]->faction);
    if(VNAM.IsLoaded())
        {
        op.Accept(VNAM.value.femaleVoice);
        op.Accept(VNAM.value.maleVoice);
        }
    if(DNAM.IsLoaded())
        {
        op.Accept(DNAM.value.defaultHairFemale);
        op.Accept(DNAM.value.defaultHairMale);
        }
    for(uint32_t ListIndex = 0; ListIndex < HNAM.value.size(); ListIndex++)
        op.Accept(HNAM.value[ListIndex]);
    for(uint32_t ListIndex = 0; ListIndex < ENAM.value.size(); ListIndex++)
        op.Accept(ENAM.value[ListIndex]);

    return op.Stop();
    }

bool RACERecord::IsPlayable()
    {
    return (DATA.value.flags & fIsPlayable) != 0;
    }

void RACERecord::IsPlayable(bool value)
    {
    SETBIT(DATA.value.flags, fIsPlayable, value);
    }

bool RACERecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void RACERecord::SetFlagMask(uint32_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t RACERecord::GetType()
    {
    return REV32(RACE);
    }

char * RACERecord::GetStrType()
    {
    return "RACE";
    }

int32_t RACERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    enum faceEnum
        {
        eHead = 0,
        eMaleEars,
        eFemaleEars,
        eMouth,
        eLowerTeeth,
        eUpperTeeth,
        eTongue,
        eLeftEye,
        eRightEye
        };

    enum bodyEnum
        {
        eUpperBody = 0,
        eLowerBody,
        eHand,
        eFoot,
        eTail
        };

    enum namEnum
        {
        fIsFace   = 0x10000000,
        fIsBody   = 0x20000000,
        fIsMale   = 0x40000000,
        fIsFemale = 0x80000000
        };

    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t part_id = 0;
    uint32_t temp_id = 0;
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
            case REV32(SPLO):
                SPLO.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(VNAM):
                if(VNAM.Read(buffer, subSize))
                    {
                    if(formID == VNAM.value.maleVoice)
                        VNAM.value.maleVoice = 0;
                    if(formID == VNAM.value.femaleVoice)
                        VNAM.value.femaleVoice = 0;
                    }
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(UNAM):
                UNAM.Read(buffer, subSize);
                break;
            case REV32(ATTR):
                ATTR.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                part_id = fIsFace;
                break;
            case REV32(NAM1):
                part_id = fIsBody;
                break;
            case REV32(INDX):
                temp_id = *(uint32_t *)buffer;
                buffer += 4;
                part_id = (part_id & 0xFF000000) | temp_id;
                break;
            case REV32(MNAM):
                part_id = fIsMale;
                break;
            case REV32(FNAM):
                part_id = fIsFemale;
                break;
            case REV32(MODL):
                switch(part_id)
                    {
                    case fIsFace | eHead:
                        MOD0.Load();
                        MOD0->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMaleEars:
                        MOD1.Load();
                        MOD1->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eFemaleEars:
                        MOD2.Load();
                        MOD2->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMouth:
                        MOD3.Load();
                        MOD3->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLowerTeeth:
                        MOD4.Load();
                        MOD4->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eUpperTeeth:
                        MOD5.Load();
                        MOD5->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eTongue:
                        MOD6.Load();
                        MOD6->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLeftEye:
                        MOD7.Load();
                        MOD7->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eRightEye:
                        MOD8.Load();
                        MOD8->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale:
                        MMODL.Load();
                        MMODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale:
                        FMODL.Load();
                        FMODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODL\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(ICON):
                switch(part_id)
                    {
                    case fIsFace | eHead:
                        MOD0.Load();
                        MOD0->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMaleEars:
                        MOD1.Load();
                        MOD1->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eFemaleEars:
                        MOD2.Load();
                        MOD2->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMouth:
                        MOD3.Load();
                        MOD3->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLowerTeeth:
                        MOD4.Load();
                        MOD4->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eUpperTeeth:
                        MOD5.Load();
                        MOD5->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eTongue:
                        MOD6.Load();
                        MOD6->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLeftEye:
                        MOD7.Load();
                        MOD7->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eRightEye:
                        MOD8.Load();
                        MOD8->ICON.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale | eUpperBody:
                        MICON0.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale | eLowerBody:
                        MICON1.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale | eHand:
                        MICON2.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale | eFoot:
                        MICON3.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale | eTail:
                        MICON4.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale | eUpperBody:
                        FICON0.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale | eLowerBody:
                        FICON1.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale | eHand:
                        FICON2.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale | eFoot:
                        FICON3.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale | eTail:
                        FICON4.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected ICON\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODB):
                switch(part_id)
                    {
                    case fIsFace | eHead:
                        MOD0.Load();
                        MOD0->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eMaleEars:
                        MOD1.Load();
                        MOD1->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eFemaleEars:
                        MOD2.Load();
                        MOD2->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eMouth:
                        MOD3.Load();
                        MOD3->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eLowerTeeth:
                        MOD4.Load();
                        MOD4->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eUpperTeeth:
                        MOD5.Load();
                        MOD5->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eTongue:
                        MOD6.Load();
                        MOD6->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eLeftEye:
                        MOD7.Load();
                        MOD7->MODB.Read(buffer, subSize);
                        break;
                    case fIsFace | eRightEye:
                        MOD8.Load();
                        MOD8->MODB.Read(buffer, subSize);
                        break;
                    case fIsMale:
                        MMODL.Load();
                        MMODL->MODB.Read(buffer, subSize);
                        break;
                    case fIsFemale:
                        FMODL.Load();
                        FMODL->MODB.Read(buffer, subSize);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODB\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(MODT):
                switch(part_id)
                    {
                    case fIsFace | eHead:
                        MOD0.Load();
                        MOD0->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMaleEars:
                        MOD1.Load();
                        MOD1->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eFemaleEars:
                        MOD2.Load();
                        MOD2->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eMouth:
                        MOD3.Load();
                        MOD3->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLowerTeeth:
                        MOD4.Load();
                        MOD4->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eUpperTeeth:
                        MOD5.Load();
                        MOD5->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eTongue:
                        MOD6.Load();
                        MOD6->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eLeftEye:
                        MOD7.Load();
                        MOD7->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFace | eRightEye:
                        MOD8.Load();
                        MOD8->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsMale:
                        MMODL.Load();
                        MMODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case fIsFemale:
                        FMODL.Load();
                        FMODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        //ERROR
                        //printer("FileName = %s\n", FileName);
                        printer("  RACE: %08X - Unexpected MODT\n", formID);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(FGGS):
                FGGS.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FGGA):
                FGGA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FGTS):
                FGTS.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  RACE: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t RACERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    SPLO.Unload();
    XNAM.Unload();
    DATA.Unload();
    VNAM.Unload();
    DNAM.Unload();
    CNAM.Unload();
    PNAM.Unload();
    UNAM.Unload();
    ATTR.Unload();
    MOD0.Unload();
    MOD1.Unload();
    MOD2.Unload();
    MOD3.Unload();
    MOD4.Unload();
    MOD5.Unload();
    MOD6.Unload();
    MOD7.Unload();
    MOD8.Unload();
    MMODL.Unload();
    MICON0.Unload();
    MICON1.Unload();
    MICON2.Unload();
    MICON3.Unload();
    MICON4.Unload();
    FMODL.Unload();
    FICON0.Unload();
    FICON1.Unload();
    FICON2.Unload();
    FICON3.Unload();
    FICON4.Unload();
    HNAM.Unload();
    ENAM.Unload();
    FGGS.Unload();
    FGGA.Unload();
    FGTS.Unload();
    SNAM.Unload();
    return 1;
    }

int32_t RACERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(SPLO);
    XNAM.Write(REV32(XNAM), writer, true);
    WRITE(DATA);
    WRITE(VNAM);
    WRITE(DNAM);
    WRITE(CNAM);
    WRITE(PNAM);
    WRITE(UNAM);
    WRITE(ATTR);

    WRITEEMPTY(NAM0);
    uint32_t curINDX = 0;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD0.Write(writer);
    curINDX = 1;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD1.Write(writer);
    curINDX = 2;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD2.Write(writer);
    curINDX = 3;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD3.Write(writer);
    curINDX = 4;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD4.Write(writer);
    curINDX = 5;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD5.Write(writer);
    curINDX = 6;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD6.Write(writer);
    curINDX = 7;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD7.Write(writer);
    curINDX = 8;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    MOD8.Write(writer);

    WRITEEMPTY(NAM1);
    WRITEEMPTY(MNAM);
    MMODL.Write(writer);
    curINDX = 0;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(MICON0,ICON);
    curINDX = 1;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(MICON1,ICON);
    curINDX = 2;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(MICON2,ICON);
    curINDX = 3;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(MICON3,ICON);
    curINDX = 4;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(MICON4,ICON);

    WRITEEMPTY(FNAM);
    FMODL.Write(writer);
    curINDX = 0;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(FICON0,ICON);
    curINDX = 1;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(FICON1,ICON);
    curINDX = 2;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(FICON2,ICON);
    curINDX = 3;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(FICON3,ICON);
    curINDX = 4;
    writer.record_write_subrecord(REV32(INDX), &curINDX, 4);
    WRITEAS(FICON4,ICON);

    if(HNAM.value.size())
        WRITE(HNAM);
    else
        WRITEEMPTY(HNAM);

    if(ENAM.value.size())
        WRITE(ENAM);
    else
        WRITEEMPTY(ENAM);

    WRITE(FGGS);
    WRITE(FGGA);
    WRITE(FGTS);
    WRITE(SNAM);

    return -1;
    }

bool RACERecord::operator ==(const RACERecord &other) const
    {
    return (DATA == other.DATA &&
            VNAM == other.VNAM &&
            DNAM == other.DNAM &&
            CNAM == other.CNAM &&
            ATTR == other.ATTR &&
            SNAM == other.SNAM &&
            PNAM == other.PNAM &&
            UNAM == other.UNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            MICON0.equalsi(other.MICON0) &&
            MICON1.equalsi(other.MICON1) &&
            MICON2.equalsi(other.MICON2) &&
            MICON3.equalsi(other.MICON3) &&
            MICON4.equalsi(other.MICON4) &&
            FICON0.equalsi(other.FICON0) &&
            FICON1.equalsi(other.FICON1) &&
            FICON2.equalsi(other.FICON2) &&
            FICON3.equalsi(other.FICON3) &&
            FICON4.equalsi(other.FICON4) &&
            MOD0 == other.MOD0 &&
            MOD1 == other.MOD1 &&
            MOD2 == other.MOD2 &&
            MOD3 == other.MOD3 &&
            MOD4 == other.MOD4 &&
            MOD5 == other.MOD5 &&
            MOD6 == other.MOD6 &&
            MOD7 == other.MOD7 &&
            MOD8 == other.MOD8 &&
            MMODL == other.MMODL &&
            FMODL == other.FMODL &&
            FGGS == other.FGGS &&
            FGGA == other.FGGA &&
            FGTS == other.FGTS &&
            SPLO == other.SPLO &&
            HNAM == other.HNAM &&
            ENAM == other.ENAM &&
            XNAM == other.XNAM);
    }

bool RACERecord::operator !=(const RACERecord &other) const
    {
    return !(*this == other);
    }

bool RACERecord::equals(Record *other)
    {
    return *this == *(RACERecord *)other;
    }
}