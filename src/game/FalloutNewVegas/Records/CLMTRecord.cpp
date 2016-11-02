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
#include "CLMTRecord.h"

namespace FNV
{
CLMTRecord::CLMTWLST::CLMTWLST():
    weather(0),
    chance(0),
    globalId(0)
    {
    //
    }

CLMTRecord::CLMTWLST::~CLMTWLST()
    {
    //
    }

bool CLMTRecord::CLMTWLST::operator ==(const CLMTWLST &other) const
    {
    return (weather == other.weather &&
            chance == other.chance &&
            globalId == other.globalId);
    }

bool CLMTRecord::CLMTWLST::operator !=(const CLMTWLST &other) const
    {
    return !(*this == other);
    }

CLMTRecord::CLMTTNAM::CLMTTNAM():
    riseBegin(0),
    riseEnd(0),
    setBegin(0),
    setEnd(0),
    volatility(0),
    phaseLength(0)
    {
    //
    }

CLMTRecord::CLMTTNAM::~CLMTTNAM()
    {
    //
    }

bool CLMTRecord::CLMTTNAM::operator ==(const CLMTTNAM &other) const
    {
    return (riseBegin == other.riseBegin &&
            riseEnd == other.riseEnd &&
            setBegin == other.setBegin &&
            setEnd == other.setEnd &&
            volatility == other.volatility &&
            phaseLength == other.phaseLength);
    }

bool CLMTRecord::CLMTTNAM::operator !=(const CLMTTNAM &other) const
    {
    return !(*this == other);
    }

CLMTRecord::CLMTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CLMTRecord::CLMTRecord(CLMTRecord *srcRecord):
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
    Weathers = srcRecord->Weathers;
    FNAM = srcRecord->FNAM;
    GNAM = srcRecord->GNAM;
    MODL = srcRecord->MODL;
    TNAM = srcRecord->TNAM;
    return;
    }

CLMTRecord::~CLMTRecord()
    {
    //
    }

bool CLMTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < Weathers.value.size(); x++)
        {
        op.Accept(Weathers.value[x].weather);
        op.Accept(Weathers.value[x].globalId);
        }
    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }

    return op.Stop();
    }

uint32_t CLMTRecord::GetType()
    {
    return REV32(CLMT);
    }

char * CLMTRecord::GetStrType()
    {
    return "CLMT";
    }

int32_t CLMTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(WLST):
                Weathers.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CLMT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CLMTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    Weathers.Unload();
    FNAM.Unload();
    GNAM.Unload();
    MODL.Unload();
    TNAM.Unload();
    return 1;
    }

int32_t CLMTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITEAS(Weathers,WLST);
    WRITE(FNAM);
    WRITE(GNAM);
    MODL.Write(writer);
    WRITE(TNAM);
    return -1;
    }

bool CLMTRecord::operator ==(const CLMTRecord &other) const
    {
    return (TNAM == other.TNAM &&
            EDID.equalsi(other.EDID) &&
            FNAM.equalsi(other.FNAM) &&
            GNAM.equalsi(other.GNAM) &&
            Weathers == other.Weathers &&
            MODL == other.MODL);
    }

bool CLMTRecord::operator !=(const CLMTRecord &other) const
    {
    return !(*this == other);
    }

bool CLMTRecord::equals(Record *other)
    {
    return *this == *(CLMTRecord *)other;
    }
}