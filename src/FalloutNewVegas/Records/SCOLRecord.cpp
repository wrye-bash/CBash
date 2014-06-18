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
#include "SCOLRecord.h"

namespace FNV
{
SCOLRecord::SCOLDATA::SCOLDATA():
    posX(0.0f),
    posY(0.0f),
    posZ(0.0f),
    rotX(0.0f),
    rotY(0.0f),
    rotZ(0.0f),
    scale(1.0f)
    {
    //
    }

SCOLRecord::SCOLDATA::~SCOLDATA()
    {
    //
    }

bool SCOLRecord::SCOLDATA::operator ==(const SCOLDATA &other) const
    {
    return (AlmostEqual(posX, other.posX, 2) &&
            AlmostEqual(posY, other.posY, 2) &&
            AlmostEqual(posZ, other.posZ, 2) &&
            AlmostEqual(rotX, other.rotX, 2) &&
            AlmostEqual(rotY, other.rotY, 2) &&
            AlmostEqual(rotZ, other.rotZ, 2) &&
            AlmostEqual(scale, other.scale, 2));
    }

bool SCOLRecord::SCOLDATA::operator !=(const SCOLDATA &other) const
    {
    return !(*this == other);
    }

void SCOLRecord::SCOLPart::Write(FileWriter &writer)
    {
    WRITE(ONAM);
    WRITE(DATA);
    }

bool SCOLRecord::SCOLPart::operator ==(const SCOLPart &other) const
    {
    return (ONAM == other.ONAM &&
            DATA == other.DATA);
    }
bool SCOLRecord::SCOLPart::operator !=(const SCOLPart &other) const
    {
    return !(*this == other);
    }

SCOLRecord::SCOLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SCOLRecord::SCOLRecord(SCOLRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    Parts = srcRecord->Parts;
    return;
    }

SCOLRecord::~SCOLRecord()
    {
    //
    }

bool SCOLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t x = 0; x < Parts.value.size(); x++)
        op.Accept(Parts.value[x]->ONAM.value);

    return op.Stop();
    }

uint32_t SCOLRecord::GetType()
    {
    return REV32(SCOL);
    }

char * SCOLRecord::GetStrType()
    {
    return "SCOL";
    }

int32_t SCOLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                Parts.value.push_back(new SCOLPart);
                Parts.value.back()->ONAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                if(Parts.value.size() == 0)
                    Parts.value.push_back(new SCOLPart);
                Parts.value.back()->DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SCOL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SCOLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    Parts.Unload();
    return 1;
    }

int32_t SCOLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    Parts.Write(writer);
    return -1;
    }

bool SCOLRecord::operator ==(const SCOLRecord &other) const
    {
    return (OBND == other.OBND &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            Parts == other.Parts);
    }

bool SCOLRecord::operator !=(const SCOLRecord &other) const
    {
    return !(*this == other);
    }

bool SCOLRecord::equals(Record *other)
    {
    return *this == *(SCOLRecord *)other;
    }
}