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
#include "NAVIRecord.h"

namespace FNV
{
NAVIRecord::NAVINVMI::NAVINVMI():
    mesh(0),
    location(0),
    xGrid(0),
    yGrid(0),
    unknown2(NULL),
    unknown2Size(0)
    {
    memset(&unknown1[0], 0x00, sizeof(unknown1));
    }

NAVIRecord::NAVINVMI::~NAVINVMI()
    {
    delete []unknown2;
    }

bool NAVIRecord::NAVINVMI::Read(unsigned char *&buffer, const uint32_t &subSize)
    {
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < 16)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVMI: Warning - Unable to fully parse chunk (NVMI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    memcpy(&unknown1[0], buffer, sizeof(unknown1));
    buffer += sizeof(unknown1);
    mesh = *(FORMID *)buffer;
    buffer += 4;
    location = *(FORMID *)buffer;
    buffer += 4;
    xGrid = *(int16_t *)buffer;
    buffer += 2;
    yGrid = *(int16_t *)buffer;
    buffer += 2;
    if(subSize - 16 < subSize)  //Handle case if subSize wraps around
        {
        unknown2Size = subSize - 16;
        unknown2 = new unsigned char[unknown2Size];
        memcpy(unknown2, buffer, unknown2Size);
        buffer += unknown2Size;
        }
    return true;
    }

void NAVIRecord::NAVINVMI::Write(FileWriter &writer)
    {
    writer.record_write_subheader(REV32(NVMI), 16 + unknown2Size);
    writer.record_write(&unknown1[0], 4);
    writer.record_write(&mesh, 4);
    writer.record_write(&location, 4);
    writer.record_write(&xGrid, 2);
    writer.record_write(&yGrid, 2);
    if(unknown2Size)
        writer.record_write(unknown2, unknown2Size);
    }

NAVIRecord::NAVINVMI& NAVIRecord::NAVINVMI::operator = (const NAVINVMI &rhs)
    {
    if(this != &rhs)
        {
        mesh = rhs.mesh;
        location = rhs.location;
        xGrid = rhs.xGrid;
        yGrid = rhs.yGrid;
        unknown1[0] = rhs.unknown1[0];
        unknown1[1] = rhs.unknown1[1];
        unknown1[2] = rhs.unknown1[2];
        unknown1[3] = rhs.unknown1[3];
        unknown2Size = rhs.unknown2Size;
        delete []unknown2;
        unknown2Size = rhs.unknown2Size;
        unknown2 = new unsigned char[unknown2Size];
        memcpy(unknown2, rhs.unknown2, unknown2Size);
        }
    return *this;
    }

bool NAVIRecord::NAVINVMI::operator ==(const NAVINVMI &other) const
    {
    if(mesh == other.mesh &&
        location == other.location &&
        xGrid == other.xGrid &&
        yGrid == other.yGrid &&
        unknown1[0] == other.unknown1[0] &&
        unknown1[1] == other.unknown1[1] &&
        unknown1[2] == other.unknown1[2] &&
        unknown1[3] == other.unknown1[3] &&
        unknown2Size == other.unknown2Size)
        {
        return memcmp(unknown2, other.unknown2, unknown2Size) == 0;
        }
    return false;
    }

bool NAVIRecord::NAVINVMI::operator !=(const NAVINVMI &other) const
    {
    return !(*this == other);
    }

NAVIRecord::NAVINVCI::NAVINVCI():
    unknown1(0)
    {
    //
    }

NAVIRecord::NAVINVCI::~NAVINVCI()
    {
    //
    }

bool NAVIRecord::NAVINVCI::Read(unsigned char *&buffer, const uint32_t &subSize)
    {
    if(unknown1 != 0 || unknown2.size() != 0 || unknown3.size() != 0 || doors.size() != 0)
        {
        buffer += subSize;
        return false;
        }
    unsigned char * init_buffer = buffer;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    unknown1 = *(FORMID *)buffer;
    buffer += 4;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    uint32_t sizeElements = *(FORMID *)buffer * sizeof(FORMID);
    unknown2.resize(*(FORMID *)buffer);
    buffer += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&unknown2[0], buffer, sizeElements);
    buffer += sizeElements;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    sizeElements = *(FORMID *)buffer * sizeof(FORMID);
    unknown3.resize(*(FORMID *)buffer);
    buffer += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&unknown3[0], buffer, sizeElements);
    buffer += sizeElements;

    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + 4)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    sizeElements = *(FORMID *)buffer * sizeof(FORMID);
    doors.resize(*(FORMID *)buffer);
    buffer += 4;
    #ifdef CBASH_CHUNK_LCHECK
        if(subSize < (buffer - init_buffer) + sizeElements)
        {
        #ifdef CBASH_CHUNK_WARN
            printer("NAVIRecord::NAVINVCI: Warning - Unable to fully parse chunk (NVCI). Size "
                   "of chunk (%u) is less than expected and there "
                   "may be corrupt data present.\n",
                   subSize);
            CBASH_CHUNK_DEBUG
        #endif
        return false;
        }
    #endif
    if(sizeElements)
        memcpy(&doors[0], buffer, sizeElements);
    buffer += sizeElements;
    if(subSize != (buffer - init_buffer))
        printer("NAVIRecord::NAVINVCI: Warning - Unable to properly parse chunk (NVCI). An "
               "unexpected format was found and there may be corrupt data present.\n");
    return true;
    }

void NAVIRecord::NAVINVCI::Write(FileWriter &writer)
    {
    if(unknown1 != 0 || unknown2.size() != 0 || unknown3.size() != 0 || doors.size() != 0)
        {
        uint32_t cSize = 16; //unknown1, and sizes for unknown2, unknown3, and doors
        cSize += (uint32_t)unknown2.size() * sizeof(FORMID);
        cSize += (uint32_t)unknown3.size() * sizeof(FORMID);
        cSize += (uint32_t)doors.size() * sizeof(FORMID);
        writer.record_write_subheader(REV32(NVCI), cSize);
        writer.record_write(&unknown1, sizeof(FORMID));
        cSize = (uint32_t)unknown2.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&unknown2[0], cSize * sizeof(FORMID));
        cSize = (uint32_t)unknown3.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&unknown3[0], cSize * sizeof(FORMID));
        cSize = (uint32_t)doors.size();
        writer.record_write(&cSize, 4);
        if(cSize)
            writer.record_write(&doors[0], cSize * sizeof(FORMID));
       }
    }

bool NAVIRecord::NAVINVCI::operator ==(const NAVINVCI &other) const
    {
    if(unknown1 == other.unknown1 &&
        unknown2.size() == other.unknown2.size() &&
        unknown3.size() == other.unknown3.size() &&
        doors.size() == other.doors.size())
        {
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(uint32_t x = 0; x < unknown2.size(); ++x)
            if(unknown2[x] != other.unknown2[x])
                return false;
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(uint32_t x = 0; x < unknown3.size(); ++x)
            if(unknown3[x] != other.unknown3[x])
                return false;
        //Not sure if record order matters, so equality testing is a guess
        //Fix-up later
        for(uint32_t x = 0; x < doors.size(); ++x)
            if(doors[x] != other.doors[x])
                return false;
        return true;
        }
    return false;
    }

bool NAVIRecord::NAVINVCI::operator !=(const NAVINVCI &other) const
    {
    return !(*this == other);
    }

NAVIRecord::NAVIRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

NAVIRecord::NAVIRecord(NAVIRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    NVMI = srcRecord->NVMI;
    NVCI = srcRecord->NVCI;
    return;
    }

NAVIRecord::~NAVIRecord()
    {
    //
    }

bool NAVIRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < NVMI.value.size(); ++x)
        {
        op.Accept(NVMI.value[x]->mesh);
        op.Accept(NVMI.value[x]->location);
        }
    for(uint32_t x = 0; x < NVCI.value.size(); ++x)
        {
        op.Accept(NVCI.value[x]->unknown1);
        for(uint32_t p = 0; p < NVCI.value[x]->unknown2.size(); ++p)
            op.Accept(NVCI.value[x]->unknown2[p]);
        for(uint32_t p = 0; p < NVCI.value[x]->unknown3.size(); ++p)
            op.Accept(NVCI.value[x]->unknown3[p]);
        for(uint32_t p = 0; p < NVCI.value[x]->doors.size(); ++p)
            op.Accept(NVCI.value[x]->doors[p]);
        }

    return op.Stop();
    }

uint32_t NAVIRecord::GetType()
    {
    return REV32(NAVI);
    }

char * NAVIRecord::GetStrType()
    {
    return "NAVI";
    }

int32_t NAVIRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(NVER):
                NVER.Read(buffer, subSize);
                break;
            case REV32(NVMI):
                NVMI.value.push_back(new NAVINVMI);
                NVMI.value.back()->Read(buffer, subSize);
                break;
            case REV32(NVCI):
                NVCI.value.push_back(new NAVINVCI);
                NVCI.value.back()->Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NAVI: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t NAVIRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    NVMI.Unload();
    NVCI.Unload();
    return 1;
    }

int32_t NAVIRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    NVMI.Write(writer);
    NVCI.Write(writer);
    return -1;
    }

bool NAVIRecord::operator ==(const NAVIRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            NVMI == other.NVMI &&
            NVCI == other.NVCI);
    }

bool NAVIRecord::operator !=(const NAVIRecord &other) const
    {
    return !(*this == other);
    }

bool NAVIRecord::equals(Record *other)
    {
    return *this == *(NAVIRecord *)other;
    }
}