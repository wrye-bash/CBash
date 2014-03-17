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
#include "LSCTRecord.h"

namespace FNV
{
LSCTRecord::LSCTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

LSCTRecord::LSCTRecord(LSCTRecord *srcRecord):
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
    DATA = srcRecord->DATA;
    return;
    }

LSCTRecord::~LSCTRecord()
    {
    //
    }

bool LSCTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool LSCTRecord::IsNone()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->screenType == eNone);
    }

bool LSCTRecord::IsXPProgress()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->screenType == eXPProgress);
    }

bool LSCTRecord::IsObjective()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->screenType == eObjective);
    }

bool LSCTRecord::IsTip()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->screenType == eTip);
    }

bool LSCTRecord::IsStats()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->screenType == eStats);
    }

bool LSCTRecord::IsType(UINT32 Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->screenType == Type;
    }

void LSCTRecord::SetType(UINT32 Type)
    {
    DATA.Load();
    DATA->screenType = Type;
    }

UINT32 LSCTRecord::GetType()
    {
    return REV32(LSCT);
    }

STRING LSCTRecord::GetStrType()
    {
    return "LSCT";
    }

SINT32 LSCTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  LSCT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 LSCTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 LSCTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DATA);

    return -1;
    }

bool LSCTRecord::operator ==(const LSCTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DATA == other.DATA);
    }

bool LSCTRecord::operator !=(const LSCTRecord &other) const
    {
    return !(*this == other);
    }

bool LSCTRecord::equals(Record *other)
    {
    return *this == *(LSCTRecord *)other;
    }
}