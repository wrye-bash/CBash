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
#include "ENCHRecord.h"

namespace Ob
{
ENCHRecord::ENCHENIT::ENCHENIT():
    itemType(0),
    chargeAmount(0),
    enchantCost(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

ENCHRecord::ENCHENIT::~ENCHENIT()
    {
    //
    }

bool ENCHRecord::ENCHENIT::operator ==(const ENCHENIT &other) const
    {
    return (itemType == other.itemType &&
            chargeAmount == other.chargeAmount &&
            enchantCost == other.enchantCost &&
            flags == other.flags);
    }

bool ENCHRecord::ENCHENIT::operator !=(const ENCHENIT &other) const
    {
    return !(*this == other);
    }

ENCHRecord::ENCHRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ENCHRecord::ENCHRecord(ENCHRecord *srcRecord):
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
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
    OBME = srcRecord->OBME;
    return;
    }

ENCHRecord::~ENCHRecord()
    {
    //
    }

bool ENCHRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < Effects.value.size(); ListIndex++)
        Effects.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

bool ENCHRecord::IsNoAutoCalc()
    {
    return (ENIT.value.flags & fIsNoAutoCalc) != 0;
    }

void ENCHRecord::IsNoAutoCalc(bool value)
    {
    SETBIT(ENIT.value.flags, fIsNoAutoCalc, value);
    }

bool ENCHRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((ENIT.value.flags & Mask) == Mask) : ((ENIT.value.flags & Mask) != 0);
    }

void ENCHRecord::SetFlagMask(uint8_t Mask)
    {
    ENIT.value.flags = Mask;
    }

bool ENCHRecord::IsScroll()
    {
    return (ENIT.value.itemType == eScroll);
    }

void ENCHRecord::IsScroll(bool value)
    {
    ENIT.value.itemType = value ? eScroll : eStaff;
    }

bool ENCHRecord::IsStaff()
    {
    return (ENIT.value.itemType == eStaff);
    }

void ENCHRecord::IsStaff(bool value)
    {
    ENIT.value.itemType = value ? eStaff : eScroll;
    }

bool ENCHRecord::IsWeapon()
    {
    return (ENIT.value.itemType == eWeapon);
    }

void ENCHRecord::IsWeapon(bool value)
    {
    ENIT.value.itemType = value ? eWeapon : eScroll;
    }

bool ENCHRecord::IsApparel()
    {
    return (ENIT.value.itemType == eApparel);
    }

void ENCHRecord::IsApparel(bool value)
    {
    ENIT.value.itemType = value ? eApparel : eScroll;
    }

bool ENCHRecord::IsType(uint32_t Type)
    {
    return (ENIT.value.itemType == Type);
    }

void ENCHRecord::SetType(uint32_t Type)
    {
    ENIT.value.itemType = Type;
    }

uint32_t ENCHRecord::GetType()
    {
    return REV32(ENCH);
    }

char * ENCHRecord::GetStrType()
    {
    return "ENCH";
    }

int32_t ENCHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    bool bNoOBME = true;
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
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(FULL):
                if(Effects.value.size() == 0)
                    FULL.Read(buffer, subSize, CompressedOnDisk);
                else
                    Effects.value.back()->FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENIT):
                ENIT.Read(buffer, subSize);
                break;
            case REV32(EFME):
                bNoOBME = false;
                Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFME.Read(buffer, subSize);
                break;
            case REV32(EFID):
                if(bNoOBME || Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                bNoOBME = true;
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(SCIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->SCIT.Read(buffer, subSize);
                break;
            case REV32(EFII):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFII.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(EFIX):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFIX.Read(buffer, subSize);
                break;
            case REV32(EFXX):
                buffer += subSize;
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ENCH: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t ENCHRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    ENIT.Unload();
    Effects.Unload();
    OBME.Unload();
    return 1;
    }

int32_t ENCHRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    if(OBME.IsLoaded())
        OBME->WRITE(OBME);
    WRITE(FULL);
    WRITE(ENIT);
    Effects.Write(writer);
    if(OBME.IsLoaded())
        {
        if(Effects.value.size())
            WRITEEMPTY(EFXX);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        }
    return -1;
    }

bool ENCHRecord::operator ==(const ENCHRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ENIT == other.ENIT &&
            OBME == other.OBME &&
            Effects == other.Effects);
    }

bool ENCHRecord::operator !=(const ENCHRecord &other) const
    {
    return !(*this == other);
    }

bool ENCHRecord::equals(Record *other)
    {
    return *this == *(ENCHRecord *)other;
    }
}