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
#include "TREERecord.h"

namespace FNV
{
TREERecord::TREECNAM::TREECNAM():
    curvature(0.0f),
    minAngle(0.0f),
    maxAngle(0.0f),
    branchDim(0.0f),
    leafDim(0.0f),
    shadowRadius(0),
    rockSpeed(0.0f),
    rustleSpeed(0.0f)
    {
    //
    }

TREERecord::TREECNAM::~TREECNAM()
    {
    //
    }

bool TREERecord::TREECNAM::operator ==(const TREECNAM &other) const
    {
    return (AlmostEqual(curvature,other.curvature,2) &&
            AlmostEqual(minAngle,other.minAngle,2) &&
            AlmostEqual(maxAngle,other.maxAngle,2) &&
            AlmostEqual(branchDim,other.branchDim,2) &&
            AlmostEqual(leafDim,other.leafDim,2) &&
            shadowRadius == other.shadowRadius &&
            AlmostEqual(rockSpeed,other.rockSpeed,2) &&
            AlmostEqual(rustleSpeed,other.rustleSpeed,2));
    }

bool TREERecord::TREECNAM::operator !=(const TREECNAM &other) const
    {
    return !(*this == other);
    }

TREERecord::TREEBNAM::TREEBNAM():
    widthBill(0.0f),
    heightBill(0.0f)
    {
    //
    }

TREERecord::TREEBNAM::~TREEBNAM()
    {
    //
    }

bool TREERecord::TREEBNAM::operator ==(const TREEBNAM &other) const
    {
    return (AlmostEqual(widthBill,other.widthBill,2) &&
            AlmostEqual(heightBill,other.heightBill,2));
    }

bool TREERecord::TREEBNAM::operator !=(const TREEBNAM &other) const
    {
    return !(*this == other);
    }

TREERecord::TREERecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TREERecord::TREERecord(TREERecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SNAM = srcRecord->SNAM;
    CNAM = srcRecord->CNAM;
    BNAM = srcRecord->BNAM;
    return;
    }

TREERecord::~TREERecord()
    {
    //
    }

bool TREERecord::VisitFormIDs(FormIDOp &op)
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

uint32_t TREERecord::GetType()
    {
    return REV32(TREE);
    }

char * TREERecord::GetStrType()
    {
    return "TREE";
    }

int32_t TREERecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  TREE: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t TREERecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SNAM.Unload();
    CNAM.Unload();
    BNAM.Unload();
    return 1;
    }

int32_t TREERecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(SNAM);
    WRITE(CNAM);
    WRITE(BNAM);
    return -1;
    }

bool TREERecord::operator ==(const TREERecord &other) const
    {
    return (OBND == other.OBND &&
            SNAM == other.SNAM &&
            CNAM == other.CNAM &&
            BNAM == other.BNAM &&
            MODL == other.MODL &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO));
    }

bool TREERecord::operator !=(const TREERecord &other) const
    {
    return !(*this == other);
    }

bool TREERecord::equals(Record *other)
    {
    return *this == *(TREERecord *)other;
    }
}