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
 *  Jacob "Lojack" Lojewski
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
#include "EQUPRecord.h"

namespace Sk {

EQUPRecord::EQUPRecord(unsigned char *_recData)
    : TES5Record(_recData)
    {
        //
    }

EQUPRecord::EQUPRecord(EQUPRecord *srcRecord)
    : TES5Record((TES5Record *)srcRecord)
    {
        if (srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        PNAM = srcRecord->PNAM;
        DATA = srcRecord->DATA;
    }

EQUPRecord::~EQUPRecord()
    {
        //
    }

bool EQUPRecord::IsUseAllParents() const
    {
        return DATA.value == 0x01;
    }

bool EQUPRecord::IsUseAllParents(bool value)
    {
        DATA.value = value ? 0x01 : 0x00;
    }

UINT32 EQUPRecord::GetType()
    {
        return REV32(EQUP);
    }

STRING EQUPRecord::GetStrType()
    {
        return "EQUP";
    }

SINT32 EQUPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        UINT32 subType = 0;
        UINT32 subSize = 0;
        while(buffer < end_buffer)
        {
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
                case REV32(PNAM):
                    PNAM.Read(buffer, subSize);
                    break;
                case REV32(DATA):
                    DATA.Read(buffer, subSize);
                    break;
                default:
                    //printer("Filename = %s\n", FileName);
                    printer("  APPA: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n", buffer - 6);
                    buffer = end_buffer;
                    break;
            }
        };
        return 0;
    }

SINT32 EQUPRecord::Unload()
    {
        IsLoaded(false);
        IsChanged(false);
        EDID.Unload();
        PNAM.Unload();
        DATA.Unload();
        return 1;
    }

SINT32 EQUPRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(PNAM);
        WRITE(DATA);
        return -1;
    }

bool EQUPRecord::operator ==(const EQUPRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                PNAM == other.PNAM &&
                DATA == other.DATA
                );
    }

bool EQUPRecord::operator !=(const EQUPRecord &other) const
    {
        return !(*this == other);
    }

bool EQUPRecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const EQUPRecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk
