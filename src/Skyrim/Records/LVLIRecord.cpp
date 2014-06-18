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
 *  Jacob "Lojack" Lojewski
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
#include "LVLIRecord.h"

namespace Sk {

LVLIRecord::LVLIRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
        //
    }

LVLIRecord::LVLIRecord(LVLIRecord *srcRecord):
    TES5Record((TES5Record *)srcRecord)
    {
        if(srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        OBND = srcRecord->OBND;
        LVLD = srcRecord->LVLD;
        LVLF = srcRecord->LVLF;
        LVLG = srcRecord->LVLG;
        Entries = srcRecord->Entries;
    }

LVLIRecord::~LVLIRecord()
    {
        //
    }

bool LVLIRecord::VisitFormIDs(FormIDOp &op)
    {
        if(!IsLoaded())
            return false;

        for(uint32_t x = 0; x < Entries.value.size(); x++)
            {
            op.Accept(Entries.value[x]->LVLO.value.listId);
            if(Entries.value[x]->IsGlobal())
                op.Accept(Entries.value[x]->COED->globalOrRank);
            }
        if(LVLG.IsLoaded())
            op.Accept(LVLG.value);
        return op.Stop();
    }

bool LVLIRecord::IsCalcFromAllLevels()
    {
        return (LVLF.value & fCalcFromAllLevels) != 0;
    }

void LVLIRecord::IsCalcFromAllLevels(bool value)
    {
        SETBIT(LVLF.value, fCalcFromAllLevels, value);
    }

bool LVLIRecord::IsCalcForEachItem()
    {
        return (LVLF.value & fCalcForEachItem) != 0;
    }

void LVLIRecord::IsCalcForEachItem(bool value)
    {
        SETBIT(LVLF.value, fCalcForEachItem, value);
    }

bool LVLIRecord::IsUseAllSpells()
    {
        return (LVLF.value & fUseAllSpells) != 0;
    }

void LVLIRecord::IsUseAllSpells(bool value)
    {
        SETBIT(LVLF.value, fUseAllSpells, value);
    }

bool LVLIRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
        return Exact ? ((LVLF.value & Mask) == Mask) : ((LVLF.value & Mask) != 0);
    }

void LVLIRecord::SetFlagMask(uint8_t Mask)
    {
        LVLF.value = Mask;
    }

uint32_t LVLIRecord::GetType()
    {
        return REV32(LVLI);
    }

char * LVLIRecord::GetStrType()
    {
        return "LVLI";
    }

int32_t LVLIRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                case REV32(LVLD):
                    LVLD.Read(buffer, subSize);
                    break;
                case REV32(LVLF):
                    LVLF.Read(buffer, subSize);
                    break;
                case REV32(LVLG):
                    LVLG.Read(buffer, subSize);
                    break;
                case REV32(LVLO):
                    Entries.value.push_back(new SKLVLOCOED);
                    Entries.value.back()->LVLO.Read(buffer, subSize);
                    break;
                case REV32(COED):
                    if(Entries.value.size() == 0)
                        Entries.value.push_back(new SKLVLOCOED);
                    Entries.value.back()->COED.Read(buffer, subSize);
                    break;
                case REV32(LLCT):
                    // Skip
                    buffer += subSize;
                    break;
                default:
                    //printer("FileName = %s\n", FileName);
                    printer("  LVLI: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n\n", buffer - 6);
                    buffer = end_buffer;
                    break;
                }
            };
        return 0;
    }

int32_t LVLIRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        OBND.Unload();
        LVLD.Unload();
        LVLF.Unload();
        LVLG.Unload();
        Entries.Unload();
        return 1;
    }

int32_t LVLIRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(OBND);
        WRITE(LVLD);
        WRITE(LVLF);
        Entries.Write(writer);
        WRITE(LVLG);
        return -1;
    }

bool LVLIRecord::operator ==(const LVLIRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                OBND == other.OBND &&
                LVLD == other.LVLD &&
                LVLF == other.LVLF &&
                LVLG == other.LVLG &&
                Entries == other.Entries);
    }

bool LVLIRecord::operator !=(const LVLIRecord &other) const
    {
        return !(*this == other);
    }

bool LVLIRecord::equals(Record *other)
    {
        return *this == *(LVLIRecord *)other;
    }

} // namespace Sk
