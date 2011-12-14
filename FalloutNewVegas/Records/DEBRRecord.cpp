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
#include "DEBRRecord.h"

namespace FNV
{
DEBRRecord::DEBRModel::DEBRModel():
    percentage(0),
    modPath(NULL),
    flags(0)
    {
    //
    }

DEBRRecord::DEBRModel::~DEBRModel()
    {
    delete []modPath;
    }

bool DEBRRecord::DEBRModel::IsHasCollisionData()
    {
    return (flags & fIsHasCollisionData) != 0;
    }

void DEBRRecord::DEBRModel::IsHasCollisionData(bool value)
    {
    flags = value ? (flags | fIsHasCollisionData) : (flags & ~fIsHasCollisionData);
    }

bool DEBRRecord::DEBRModel::IsFlagMask(UINT8 Mask, bool Exact)
    {
    return Exact ? ((flags & Mask) == Mask) : ((flags & Mask) != 0);
    }

void DEBRRecord::DEBRModel::SetFlagMask(UINT8 Mask)
    {
    flags = Mask;
    }

bool DEBRRecord::DEBRModel::Read(unsigned char *&buffer, const UINT32 &subSize)
    {
    if(subSize < 3)
        {
        printer("DEBRModel: Warning - Unable to parse chunk (%c%c%c%c). Size "
               "of chunk (%u) is less than the minimum size of the subrecord (%u). "
               "The chunk has been skipped.\n",
               buffer[-6], buffer[-5], buffer[-4], buffer[-3], subSize, 3);
        buffer += subSize;
        return false;
        }
    percentage = *(UINT8 *)buffer;
    buffer++;

    UINT32 size = (UINT32)strlen((STRING)buffer) + 1;
    modPath = new char[size];
    strcpy_s(modPath, size, (STRING)buffer);
    buffer += size;

    flags = *(UINT8 *)buffer;
    buffer++;

    size += 2;
    if(size != subSize)
        {
        printer("DEBRModel: Warning - Unable to parse chunk (%c%c%c%c). Size "
               "of chunk (%u) is not equal to the parsed size (%u). "
               "The loaded fields are likely corrupt.\n",
               buffer[-6], buffer[-5], buffer[-4], buffer[-3], subSize, size);
        }
    return true;
    }

void DEBRRecord::DEBRModel::Write(FileWriter &writer)
    {
    UINT32 size = 3; //null terminator, percentage, and flags
    if(modPath != NULL)
        {
        size += (UINT32)strlen(modPath);
        writer.record_write_subheader(REV32(DATA), size);
        writer.record_write(&percentage, 1);
        writer.record_write(modPath, size - 2);
        writer.record_write(&flags, 1);
        }
    else
        {
        writer.record_write_subheader(REV32(DATA), size);
        writer.record_write(&percentage, 1);
        size = 0;
        writer.record_write(&size, 1); //single null terminator
        writer.record_write(&flags, 1);
        }
    WRITE(MODT);
    }

bool DEBRRecord::DEBRModel::operator ==(const DEBRModel &other) const
    {
    return (flags == other.flags &&
            percentage == other.percentage &&
            (icmps(modPath, other.modPath) == 0) &&
            MODT == other.MODT);
    }

bool DEBRRecord::DEBRModel::operator !=(const DEBRModel &other) const
    {
    return !(*this == other);
    }

DEBRRecord::DEBRModels::DEBRModels()
    {
    //
    }

DEBRRecord::DEBRModels::~DEBRModels()
    {
    Unload();
    }

bool DEBRRecord::DEBRModels::IsLoaded() const
    {
    return (MODS.size() != 0);
    }

void DEBRRecord::DEBRModels::Load()
    {
    //
    }

void DEBRRecord::DEBRModels::Unload()
    {
    for(UINT32 x = 0; x < MODS.size(); ++x)
        delete MODS[x];
    MODS.clear();
    }

void DEBRRecord::DEBRModels::resize(UINT32 newSize)
    {
    //Shrink
    UINT32 size = (UINT32)MODS.size();
    for(; size > newSize;)
        delete MODS[--size];
    MODS.resize(newSize);
    //Grow
    for(; size < newSize;)
        MODS[size++] = new DEBRModel;
    }

void DEBRRecord::DEBRModels::Write(FileWriter &writer)
    {
    for(UINT32 p = 0; p < MODS.size(); p++)
        MODS[p]->Write(writer);
    }

DEBRRecord::DEBRModels& DEBRRecord::DEBRModels::operator = (const DEBRModels &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if(rhs.MODS.size() != 0)
            {
            MODS.resize(rhs.MODS.size());
            UINT32 pathSize = 0;
            for(UINT32 p = 0; p < rhs.MODS.size(); p++)
                {
                MODS[p] = new DEBRModel;
                MODS[p]->percentage = rhs.MODS[p]->percentage;

                if(rhs.MODS[p]->modPath != NULL)
                    {
                    pathSize = (UINT32)strlen(rhs.MODS[p]->modPath) + 1;
                    MODS[p]->modPath = new char[pathSize];
                    strcpy_s(MODS[p]->modPath, pathSize, rhs.MODS[p]->modPath);
                    }
                MODS[p]->flags = rhs.MODS[p]->flags;
                }
            }
        }
    return *this;
    }

bool DEBRRecord::DEBRModels::operator ==(const DEBRModels &other) const
    {
    if(MODS.size() == other.MODS.size())
        {
        //Not sure if record order matters on debris models, so equality testing is a guess
        //Fix-up later
        for(UINT32 x = 0; x < MODS.size(); ++x)
            if(*MODS[x] != *other.MODS[x])
                return false;
        return true;
        }
    return false;
    }

bool DEBRRecord::DEBRModels::operator !=(const DEBRModels &other) const
    {
    return !(*this == other);
    }

DEBRRecord::DEBRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DEBRRecord::DEBRRecord(DEBRRecord *srcRecord):
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
    Models = srcRecord->Models;
    return;
    }

DEBRRecord::~DEBRRecord()
    {
    //
    }

UINT32 DEBRRecord::GetType()
    {
    return REV32(DEBR);
    }

STRING DEBRRecord::GetStrType()
    {
    return "DEBR";
    }

SINT32 DEBRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                Models.MODS.push_back(new DEBRModel);
                Models.MODS.back()->Read(buffer, subSize);
                break;
            case REV32(MODT):
                if(Models.MODS.size() == 0)
                    Models.MODS.push_back(new DEBRModel);
                Models.MODS.back()->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DEBR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 DEBRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    Models.Unload();
    return 1;
    }

SINT32 DEBRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    Models.Write(writer);
    return -1;
    }

bool DEBRRecord::operator ==(const DEBRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            Models == other.Models);
    }

bool DEBRRecord::operator !=(const DEBRRecord &other) const
    {
    return !(*this == other);
    }

bool DEBRRecord::equals(Record *other)
    {
    return *this == *(DEBRRecord *)other;
    }
}