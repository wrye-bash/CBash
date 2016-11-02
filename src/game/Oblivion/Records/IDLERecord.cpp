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
#include "IDLERecord.h"

namespace Ob
{
IDLERecord::IDLEDATA::IDLEDATA():
    parent(0),
    prevId(0)
    {
    //
    }

IDLERecord::IDLEDATA::~IDLEDATA()
    {
    //
    }

bool IDLERecord::IDLEDATA::operator ==(const IDLEDATA &other) const
    {
    return (parent == other.parent &&
            prevId == other.prevId);
    }
bool IDLERecord::IDLEDATA::operator !=(const IDLEDATA &other) const
    {
    return !(*this == other);
    }

IDLERecord::IDLERecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

IDLERecord::IDLERecord(IDLERecord *srcRecord):
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
    MODL = srcRecord->MODL;
    CTDA = srcRecord->CTDA;
    ANAM = srcRecord->ANAM;
    DATA = srcRecord->DATA;
    return;
    }

IDLERecord::~IDLERecord()
    {
    //
    }

bool IDLERecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);

    op.Accept(DATA.value.parent);
    op.Accept(DATA.value.prevId);

    return op.Stop();
    }

bool IDLERecord::IsLowerBody()
    {
    return ((ANAM.value & ~0x80) == eLowerBody);
    }

void IDLERecord::IsLowerBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    else if(IsLowerBody())
        ANAM.value = ANAM.value & 0x80 | eLeftArm;
    }

bool IDLERecord::IsLeftArm()
    {
    return ((ANAM.value & ~0x80) == eLeftArm);
    }

void IDLERecord::IsLeftArm(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLeftArm;
    else if(IsLeftArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsLeftHand()
    {
    return ((ANAM.value & ~0x80) == eLeftHand);
    }

void IDLERecord::IsLeftHand(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eLeftHand;
    else if(IsLeftHand())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsRightArm()
    {
    return ((ANAM.value & ~0x80) == eRightArm);
    }

void IDLERecord::IsRightArm(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eRightArm;
    else if(IsRightArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsSpecialIdle()
    {
    return ((ANAM.value & ~0x80) == eSpecialIdle);
    }

void IDLERecord::IsSpecialIdle(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eSpecialIdle;
    else if(IsLeftArm())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsWholeBody()
    {
    return ((ANAM.value & ~0x80) == eWholeBody);
    }

void IDLERecord::IsWholeBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eWholeBody;
    else if(IsWholeBody())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsUpperBody()
    {
    return ((ANAM.value & ~0x80) == eUpperBody);
    }

void IDLERecord::IsUpperBody(bool value)
    {
    if(value)
        ANAM.value = ANAM.value & 0x80 | eUpperBody;
    else if(IsUpperBody())
        ANAM.value = ANAM.value & 0x80 | eLowerBody;
    }

bool IDLERecord::IsType(uint8_t Type)
    {
    return ((ANAM.value & ~0x80) == (Type & ~0x80));
    }

void IDLERecord::SetType(uint8_t Type)
    {
    ANAM.value = ANAM.value & 0x80 | (Type & ~0x80);
    }

bool IDLERecord::IsNotReturnFile()
    {
    return (ANAM.value & fIsNotReturnFile) != 0;
    }

void IDLERecord::IsNotReturnFile(bool value)
    {
    SETBIT(ANAM.value, fIsNotReturnFile, value);
    }

bool IDLERecord::IsReturnFile()
    {
    return !(IsNotReturnFile());
    }

void IDLERecord::IsReturnFile(bool value)
    {
    IsNotReturnFile(!value);
    }

bool IDLERecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? (((ANAM.value & 0x80) & (Mask & 0x80)) == Mask) : (((ANAM.value & 0x80) & (Mask & 0x80)) != 0);
    }

void IDLERecord::SetFlagMask(uint8_t Mask)
    {
    ANAM.value = ANAM.value & ~0x80 | (Mask & 0x80);
    }

uint32_t IDLERecord::GetType()
    {
    return REV32(IDLE);
    }

char * IDLERecord::GetStrType()
    {
    return "IDLE";
    }

int32_t IDLERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(CTDT):
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  IDLE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t IDLERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    CTDA.Unload();
    ANAM.Unload();
    DATA.Unload();
    return 1;
    }

int32_t IDLERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    MODL.Write(writer);
    CTDA.Write(writer, true);
    WRITE(ANAM);
    WRITE(DATA);
    return -1;
    }

bool IDLERecord::operator ==(const IDLERecord &other) const
    {
    return (ANAM == other.ANAM &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            CTDA == other.CTDA);
    }

bool IDLERecord::operator !=(const IDLERecord &other) const
    {
    return !(*this == other);
    }

bool IDLERecord::equals(Record *other)
    {
    return *this == *(IDLERecord *)other;
    }
}