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
#include "SLGMRecord.h"

namespace Ob
{
SLGMRecord::SLGMRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SLGMRecord::SLGMRecord(SLGMRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    DATA = srcRecord->DATA;
    SOUL = srcRecord->SOUL;
    SLCP = srcRecord->SLCP;
    }

SLGMRecord::~SLGMRecord()
    {
    //
    }

bool SLGMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    return op.Stop();
    }

bool SLGMRecord::IsNoSoul()
    {
    return (SOUL.value == eNone);
    }

void SLGMRecord::IsNoSoul(bool value)
    {
    if(value)
        SOUL.value = eNone;
    else if(IsNoSoul())
        SOUL.value = ePetty;
    }

bool SLGMRecord::IsPettySoul()
    {
    return (SOUL.value == ePetty);
    }

void SLGMRecord::IsPettySoul(bool value)
    {
    if(value)
        SOUL.value = ePetty;
    else if(IsPettySoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsLesserSoul()
    {
    return (SOUL.value == eLesser);
    }

void SLGMRecord::IsLesserSoul(bool value)
    {
    if(value)
        SOUL.value = eLesser;
    else if(IsLesserSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsCommonSoul()
    {
    return (SOUL.value == eCommon);
    }

void SLGMRecord::IsCommonSoul(bool value)
    {
    if(value)
        SOUL.value = eCommon;
    else if(IsCommonSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsGreaterSoul()
    {
    return (SOUL.value == eGreater);
    }

void SLGMRecord::IsGreaterSoul(bool value)
    {
    if(value)
        SOUL.value = eGreater;
    else if(IsGreaterSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsGrandSoul()
    {
    return (SOUL.value == eGrand);
    }

void SLGMRecord::IsGrandSoul(bool value)
    {
    if(value)
        SOUL.value = eGrand;
    else if(IsGrandSoul())
        SOUL.value = eNone;
    }

bool SLGMRecord::IsSoul(uint8_t Type)
    {
    return (SOUL.value == Type);
    }

void SLGMRecord::SetSoul(uint8_t Type)
    {
    SOUL.value = Type;
    }

bool SLGMRecord::IsNoCapacity()
    {
    return (SLCP.value== eNone);
    }

void SLGMRecord::IsNoCapacity(bool value)
    {
    if(value)
        SLCP.value= eNone;
    else if(IsNoCapacity())
        SLCP.value= ePetty;
    }

bool SLGMRecord::IsPettyCapacity()
    {
    return (SLCP.value== ePetty);
    }

void SLGMRecord::IsPettyCapacity(bool value)
    {
    if(value)
        SLCP.value= ePetty;
    else if(IsPettyCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsLesserCapacity()
    {
    return (SLCP.value== eLesser);
    }

void SLGMRecord::IsLesserCapacity(bool value)
    {
    if(value)
        SLCP.value= eLesser;
    else if(IsLesserCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsCommonCapacity()
    {
    return (SLCP.value== eCommon);
    }

void SLGMRecord::IsCommonCapacity(bool value)
    {
    if(value)
        SLCP.value= eCommon;
    else if(IsCommonCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsGreaterCapacity()
    {
    return (SLCP.value== eGreater);
    }

void SLGMRecord::IsGreaterCapacity(bool value)
    {
    if(value)
        SLCP.value= eGreater;
    else if(IsGreaterCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsGrandCapacity()
    {
    return (SLCP.value== eGrand);
    }

void SLGMRecord::IsGrandCapacity(bool value)
    {
    if(value)
        SLCP.value= eGrand;
    else if(IsGrandCapacity())
        SLCP.value= eNone;
    }

bool SLGMRecord::IsCapacity(uint8_t Type)
    {
    return (SLCP.value== Type);
    }

void SLGMRecord::SetCapacity(uint8_t Type)
    {
    SLCP.value= Type;
    }

uint32_t SLGMRecord::GetType()
    {
    return REV32(SLGM);
    }

char * SLGMRecord::GetStrType()
    {
    return "SLGM";
    }

int32_t SLGMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SOUL):
                SOUL.Read(buffer, subSize);
                break;
            case REV32(SLCP):
                SLCP.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SLGM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SLGMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    DATA.Unload();
    SOUL.Unload();
    SLCP.Unload();
    return 1;
    }

int32_t SLGMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    WRITE(DATA);
    WRITE(SOUL);
    WRITE(SLCP);
    return -1;
    }

bool SLGMRecord::operator ==(const SLGMRecord &other) const
    {
    return (SCRI == other.SCRI &&
            SOUL == other.SOUL &&
            SLCP == other.SLCP &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            MODL == other.MODL);
    }

bool SLGMRecord::operator !=(const SLGMRecord &other) const
    {
    return !(*this == other);
    }

bool SLGMRecord::equals(Record *other)
    {
    return *this == *(SLGMRecord *)other;
    }
}