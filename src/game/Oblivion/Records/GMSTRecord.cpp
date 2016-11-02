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
#include "GMSTRecord.h"

namespace Ob
{
GMSTRecord::GMSTDATA::GMSTDATA(char * _DATA):
    format('s'),
    s(_DATA)
    {
    //
    }

GMSTRecord::GMSTDATA::GMSTDATA(int32_t _DATA):
    format('i'),
    i(_DATA)
    {
    //
    }

GMSTRecord::GMSTDATA::GMSTDATA(float _DATA):
    format('f'),
    f(_DATA)
    {
    //
    }

GMSTRecord::GMSTDATA::GMSTDATA():
    format(0),
    i(0)
    {
    //
    }

GMSTRecord::GMSTDATA::~GMSTDATA()
    {
    if(format == 's')
        delete []s;
    }

bool GMSTRecord::GMSTDATA::operator ==(const GMSTDATA &other) const
    {
    if(format != other.format)
        return false;

    switch(format)
        {
        case 's':
            return cmps(s, other.s) == 0;
        case 'i':
            return i == other.i;
        case 'f':
            return AlmostEqual(f, other.f, 2);
        default:
            return false;
        }
    }

bool GMSTRecord::GMSTDATA::operator !=(const GMSTDATA &other) const
    {
    return !(*this == other);
    }

GMSTRecord::GMSTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

GMSTRecord::GMSTRecord(GMSTRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    EDID = srcRecord->EDID;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    DATA.format = srcRecord->DATA.format;
    uint32_t vSize;
    switch(DATA.format)
        {
        case 'f':
            DATA.f = srcRecord->DATA.f;
            break;
        case 'i':
            DATA.i = srcRecord->DATA.i;
            break;
        case 's':
            if(srcRecord->DATA.s != NULL)
                {
                vSize = (uint32_t)strlen(srcRecord->DATA.s) + 1;
                DATA.s = new char [vSize];
                strcpy_s(DATA.s, vSize, srcRecord->DATA.s);
                }
            break;
        default:
            break;
        }
    return;
    }

GMSTRecord::~GMSTRecord()
    {
    //
    }

uint32_t GMSTRecord::GetType()
    {
    return REV32(GMST);
    }

char * GMSTRecord::GetStrType()
    {
    return "GMST";
    }

bool GMSTRecord::IsKeyedByEditorID()
    {
    return true;
    }

int32_t GMSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.format = EDID.value[0];
                switch(DATA.format)
                    {
                    case 's':
                        DATA.s = new char[subSize];
                        memcpy(DATA.s, buffer, subSize);
                        buffer += subSize;
                        break;
                    case 'i':
                        memcpy(&DATA.i, buffer, subSize);
                        buffer += subSize;
                        break;
                    case 'f':
                        memcpy(&DATA.f, buffer, subSize);
                        buffer += subSize;
                        break;
                    default:
                        //printer("FileName = %s\n", FileName);
                        printer("  GMST: %08X - Unknown type = %c\n", formID, DATA.format);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer = end_buffer;
                        break;
                    }
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  GMST: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t GMSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    //Don't unload EDID since it is used to index the record
    if(DATA.format == 's')
        delete []DATA.s;
    DATA.i = 0;
    DATA.format = 0;
    return 1;
    }

int32_t GMSTRecord::WriteRecord(FileWriter &writer)
    {
    if(EDID.IsLoaded()) //Should only be false if the record was marked deleted
        {
        WRITE(EDID);
        uint8_t null = 0;
        switch(DATA.format)
            {
            case 'i':
                writer.record_write_subrecord(REV32(DATA), &DATA.i, 4);
                break;
            case 'f':
                writer.record_write_subrecord(REV32(DATA), &DATA.f, 4);
                break;
            case 's':
                if(DATA.s != NULL)
                    writer.record_write_subrecord(REV32(DATA), DATA.s, (uint32_t)strlen(DATA.s) + 1);
                else
                    writer.record_write_subrecord(REV32(DATA), &null, 1);
                break;
            default:
                printer("Unknown GMST format (%c) when writing: %s\n", DATA.format, EDID.value);
                break;
            }
        }
    return -1;
    }

bool GMSTRecord::operator ==(const GMSTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA);
    }

bool GMSTRecord::operator !=(const GMSTRecord &other) const
    {
    return !(*this == other);
    }

bool GMSTRecord::equals(Record *other)
    {
    return *this == *(GMSTRecord *)other;
    }
}