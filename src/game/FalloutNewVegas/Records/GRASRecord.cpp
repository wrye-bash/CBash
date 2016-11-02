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
#include "GRASRecord.h"

namespace FNV
{
GRASRecord::GRASDATA::GRASDATA():
    density(0),
    minSlope(0),
    maxSlope(0),
    unused1(0xCD),
    waterDistance(0),
    waterOp(0),
    posRange(0.0f),
    heightRange(0.0f),
    colorRange(0.0f),
    wavePeriod(0.0f),
    flags(0)
    {
    memset(&unused2[0], 0xCD, sizeof(unused2));
    memset(&unused3[0], 0xCD, sizeof(unused3));
    }

GRASRecord::GRASDATA::~GRASDATA()
    {
    //
    }

bool GRASRecord::GRASDATA::operator ==(const GRASDATA &other) const
    {
    return (density == other.density &&
            minSlope == other.minSlope &&
            maxSlope == other.maxSlope &&
            waterDistance == other.waterDistance &&
            waterOp == other.waterOp &&
            AlmostEqual(posRange,other.posRange,2) &&
            AlmostEqual(heightRange,other.heightRange,2) &&
            AlmostEqual(colorRange,other.colorRange,2) &&
            AlmostEqual(wavePeriod,other.wavePeriod,2) &&
            flags == other.flags);
    }

bool GRASRecord::GRASDATA::operator !=(const GRASDATA &other) const
    {
    return !(*this == other);
    }

GRASRecord::GRASRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

GRASRecord::GRASRecord(GRASRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    return;
    }

GRASRecord::~GRASRecord()
    {
    //
    }

bool GRASRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }

    return op.Stop();
    }

bool GRASRecord::IsVLighting()
    {
    return (DATA.value.flags & fIsVLighting) != 0;
    }

void GRASRecord::IsVLighting(bool value)
    {
    SETBIT(DATA.value.flags, fIsVLighting, value);
    }

bool GRASRecord::IsUScaling()
    {
    return (DATA.value.flags & fIsUScaling) != 0;
    }

void GRASRecord::IsUScaling(bool value)
    {
    SETBIT(DATA.value.flags, fIsUScaling, value);
    }

bool GRASRecord::IsFitSlope()
    {
    return (DATA.value.flags & fIsFitSlope) != 0;
    }

void GRASRecord::IsFitSlope(bool value)
    {
    SETBIT(DATA.value.flags, fIsFitSlope, value);
    }

bool GRASRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void GRASRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t GRASRecord::GetType()
    {
    return REV32(GRAS);
    }

char * GRASRecord::GetStrType()
    {
    return "GRAS";
    }

int32_t GRASRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  GRAS: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t GRASRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t GRASRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(DATA);
    return -1;
    }

bool GRASRecord::operator ==(const GRASRecord &other) const
    {
    return (OBND == other.OBND &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool GRASRecord::operator !=(const GRASRecord &other) const
    {
    return !(*this == other);
    }

bool GRASRecord::equals(Record *other)
    {
    return *this == *(GRASRecord *)other;
    }
}