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
#include "SKILRecord.h"

namespace Ob
{
SKILRecord::SKILDATA::SKILDATA():
    action(26),
    attribute(0),
    specialization(0),
    use0(1.0f),
    use1(1.0f)
    {
    //
    }

SKILRecord::SKILDATA::~SKILDATA()
    {
    //
    }

bool SKILRecord::SKILDATA::operator ==(const SKILDATA &other) const
    {
    return (action == other.action &&
            attribute == other.attribute &&
            specialization == other.specialization &&
            AlmostEqual(use0,other.use0,2) &&
            AlmostEqual(use1,other.use1,2));
    }

bool SKILRecord::SKILDATA::operator !=(const SKILDATA &other) const
    {
    return !(*this == other);
    }

SKILRecord::SKILRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SKILRecord::SKILRecord(SKILRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;

    INDX = srcRecord->INDX;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
    ANAM = srcRecord->ANAM;
    JNAM = srcRecord->JNAM;
    ENAM = srcRecord->ENAM;
    MNAM = srcRecord->MNAM;
    }

SKILRecord::~SKILRecord()
    {
    //
    }

uint32_t SKILRecord::GetType()
    {
    return REV32(SKIL);
    }

char * SKILRecord::GetStrType()
    {
    return "SKIL";
    }

int32_t SKILRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(INDX):
                INDX.Read(buffer, subSize);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(JNAM):
                JNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SKIL: Unknown subType = %04X\n", subType);
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SKILRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    INDX.Unload();
    DESC.Unload();
    ICON.Unload();
    DATA.Unload();
    ANAM.Unload();
    JNAM.Unload();
    ENAM.Unload();
    MNAM.Unload();
    return 1;
    }

int32_t SKILRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(INDX);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(DATA);
    WRITE(ANAM);
    WRITE(JNAM);
    WRITE(ENAM);
    WRITE(MNAM);
    return -1;
    }

bool SKILRecord::operator ==(const SKILRecord &other) const
    {
    return (INDX == other.INDX &&
            DATA == other.DATA &&
            DESC.equals(other.DESC) &&
            ANAM.equals(other.ANAM) &&
            JNAM.equals(other.JNAM) &&
            ENAM.equals(other.ENAM) &&
            MNAM.equals(other.MNAM) &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON));
    }

bool SKILRecord::operator !=(const SKILRecord &other) const
    {
    return !(*this == other);
    }

bool SKILRecord::equals(Record *other)
    {
    return *this == *(SKILRecord *)other;
    }
}