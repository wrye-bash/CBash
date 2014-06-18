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
#include "LSCRRecord.h"

namespace FNV
{
LSCRRecord::LSCRLNAM::LSCRLNAM():
    direct(0),
    indirect(0),
    gridY(0),
    gridX(0)
    {
    //
    }

LSCRRecord::LSCRLNAM::~LSCRLNAM()
    {
    //
    }

bool LSCRRecord::LSCRLNAM::operator ==(const LSCRLNAM &other) const
    {
    return (direct == other.direct &&
            indirect == other.indirect &&
            gridY == other.gridY &&
            gridX == other.gridX);
    }

bool LSCRRecord::LSCRLNAM::operator !=(const LSCRLNAM &other) const
    {
    return !(*this == other);
    }

LSCRRecord::LSCRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LSCRRecord::LSCRRecord(LSCRRecord *srcRecord):
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
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    DESC = srcRecord->DESC;
    LNAM = srcRecord->LNAM;
    WMI1 = srcRecord->WMI1;
    return;
    }

LSCRRecord::~LSCRRecord()
    {
    //
    }

bool LSCRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < LNAM.value.size(); ListIndex++)
        {
        op.Accept(LNAM.value[ListIndex]->direct);
        op.Accept(LNAM.value[ListIndex]->indirect);
        }
    if(WMI1.IsLoaded())
        op.Accept(WMI1.value);

    return op.Stop();
    }

uint32_t LSCRRecord::GetType()
    {
    return REV32(LSCR);
    }

char * LSCRRecord::GetStrType()
    {
    return "LSCR";
    }

int32_t LSCRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(WMI1):
                WMI1.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  LSCR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t LSCRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    ICON.Unload();
    MICO.Unload();
    DESC.Unload();
    LNAM.Unload();
    WMI1.Unload();
    return 1;
    }

int32_t LSCRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(DESC);
    WRITE(LNAM);
    WRITE(WMI1);
    return -1;
    }

bool LSCRRecord::operator ==(const LSCRRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            DESC.equals(other.DESC) &&
            LNAM == other.LNAM &&
            WMI1 == other.WMI1);
    }

bool LSCRRecord::operator !=(const LSCRRecord &other) const
    {
    return !(*this == other);
    }

bool LSCRRecord::equals(Record *other)
    {
    return *this == *(LSCRRecord *)other;
    }
}