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
#include "LVLNRecord.h"

namespace Sk {

LVLNRecord::LVLNRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
        //
    }

LVLNRecord::LVLNRecord(LVLNRecord *srcRecord):
    TES5Record()
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
        LVLD = srcRecord->LVLD;
        LVLF = srcRecord->LVLF;
        Entries = srcRecord->Entries;
        MODL = srcRecord->MODL;
        return;
    }

LVLNRecord::~LVLNRecord()
    {
        //
    }

bool LVLNRecord::VisitFormIDs(FormIDOp &op)
    {
        if(!IsLoaded())
            return false;

        for(UINT32 x = 0; x < Entries.value.size(); x++)
            {
            op.Accept(Entries.value[x]->LVLO.value.listId);
            if(Entries.value[x]->IsGlobal())
                op.Accept(Entries.value[x]->COED->globalOrRank);
            }
        return op.Stop();
    }

bool LVLNRecord::IsCalcFromAllLevels()
    {
        return (LVLF.value & fCalcFromAllLevels) != 0;
    }

void LVLNRecord::IsCalcFromAllLevels(bool value)
    {
        SETBIT(LVLF.value, fCalcFromAllLevels, value);
    }

bool LVLNRecord::IsCalcForEachItem()
    {
        return (LVLF.value & fCalcForEachItem) != 0;
    }

void LVLNRecord::IsCalcForEachItem(bool value)
    {
        SETBIT(LVLF.value, fCalcForEachItem, value);
    }

bool LVLNRecord::IsUseAllSpells()
    {
        return (LVLF.value & fUseAllSpells) != 0;
    }

void LVLNRecord::IsUseAllSpells(bool value)
    {
        SETBIT(LVLF.value, fUseAllSpells, value);
    }

bool LVLNRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
        return Exact ? ((LVLF.value & Mask) == Mask) : ((LVLF.value & Mask) != 0);
    }

void LVLNRecord::SetFlagMask(UINT8 Mask)
    {
        LVLF.value = Mask;
    }

UINT32 LVLNRecord::GetType()
    {
        return REV32(LVLN);
    }

STRING LVLNRecord::GetStrType()
    {
        return "LVLN";
    }

SINT32 LVLNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        UINT32 subType = 0;
        UINT32 subSize = 0;
        while(buffer < end_buffer){
            subType = *(UINT32 *)buffer;
            buffer += 4;
            switch(subType)
                {
                case REV32(XXXX):
                    buffer += 2;
                    subSize = *(UINT32 *)buffer;
                    buffer += 4;
                    subType = *(UINT32 *)buffer;
                    buffer += 6;
                    break;
                default:
                    subSize = *(UINT16 *)buffer;
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
                case REV32(LVLO):
                    Entries.value.push_back(new FNVLVLO);
                    Entries.value.back()->LVLO.Read(buffer, subSize);
                    break;
                case REV32(COED):
                    if(Entries.value.size() == 0)
                        Entries.value.push_back(new FNVLVLO);
                    Entries.value.back()->COED.Read(buffer, subSize);
                    break;
                case REV32(LLCT):
                    // Skip
                    buffer += subSize;
                    break;
                case REV32(MODL):
                    MODL.Load();
                    MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(MODT):
                    MODL.Load();
                    MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                default:
                    //printer("FileName = %s\n", FileName);
                    printer("  LVLN: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n\n", buffer - 6);
                    buffer = end_buffer;
                    break;
                }
            };
        return 0;
    }

SINT32 LVLNRecord::Unload()
    {
        IsChanged(false);
        IsLoaded(false);
        EDID.Unload();
        OBND.Unload();
        LVLD.Unload();
        LVLF.Unload();
        Entries.Unload();
        MODL.Unload();
        return 1;
    }

SINT32 LVLNRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(OBND);
        WRITE(LVLD);
        WRITE(LVLF);
        //  Write LLCT
        UINT8 count = Entries.value.size();
        writer.record_write_subrecord(REV32(LLCT),&count,sizeof(count));
        Entries.Write(writer);
        WRITE(MODL);
        return -1;
    }

bool LVLNRecord::operator ==(const LVLNRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                OBND == other.OBND &&
                LVLD == other.LVLD &&
                LVLF == other.LVLF &&
                Entries == other.Entries &&
                MODL == other.MODL);
    }

bool LVLNRecord::operator !=(const LVLNRecord &other) const
    {
        return !(*this == other);
    }

bool LVLNRecord::equals(Record *other)
    {
        return *this == *(LVLNRecord *)other;
    }

} // namespace Sk