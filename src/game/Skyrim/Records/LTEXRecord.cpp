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
#include "LTEXRecord.h"

namespace Sk
{

LTEXRecord::LTEXHNAM::LTEXHNAM():
    friction(0),
    restitution(0)
    {
    //
    }

LTEXRecord::LTEXHNAM::~LTEXHNAM()
    {
    //
    }

bool LTEXRecord::LTEXHNAM::operator ==(const LTEXHNAM &other) const
    {
    return (friction == other.friction &&
            restitution == other.restitution);
    }
bool LTEXRecord::LTEXHNAM::operator !=(const LTEXHNAM &other) const
    {
    return !(*this == other);
    }

LTEXRecord::LTEXRecord(unsigned char *_recData):
    TES5Record(_recData)
    {
    //
    }

LTEXRecord::LTEXRecord(LTEXRecord *srcRecord):
    TES5Record((TES5Record *)srcRecord)
    {
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    TNAM = srcRecord->TNAM;
    MNAM = srcRecord->MNAM;
    HNAM = srcRecord->HNAM;
    SNAM = srcRecord->SNAM;
    GNAM = srcRecord->GNAM;
    }

LTEXRecord::~LTEXRecord()
    {
    //
    }

bool LTEXRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);
    op.Accept(MNAM.value);
    for(uint32_t x = 0; x < GNAM.value.size(); ++x)
        op.Accept(GNAM.value[x]);

    return op.Stop();
    }

uint32_t LTEXRecord::GetType()
    {
    return REV32(LTEX);
    }

char * LTEXRecord::GetStrType()
    {
    return "LTEX";
    }

int32_t LTEXRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LTEX: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t LTEXRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    TNAM.Unload();
    MNAM.Unload();
    HNAM.Unload();
    SNAM.Unload();
    GNAM.Unload();
    return 1;
    }

int32_t LTEXRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(TNAM);
    WRITE(MNAM);
    WRITE(HNAM);
    WRITE(SNAM);
    WRITE(GNAM);
    return -1;
    }

bool LTEXRecord::operator ==(const LTEXRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MNAM == other.MNAM &&
            TNAM == other.TNAM &&
            HNAM == other.HNAM &&
            SNAM == other.SNAM &&
            GNAM == other.GNAM
            );
    }

bool LTEXRecord::operator !=(const LTEXRecord &other) const
    {
    return !(*this == other);
    }

bool LTEXRecord::equals(Record *other)
{
    try
    {
        return *this == *reinterpret_cast<LTEXRecord *>(other);
    }
    catch (...)
    {
        return false;
    }
}

} // namespace Sk
