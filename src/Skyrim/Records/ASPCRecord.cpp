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
#include "..\..\Common.h"
#include "ASPCRecord.h"

namespace Sk {

ASPCRecord::ASPCRecord(unsigned char *_recData)
    : TES5Record(_recData)
    {
        //
    }

ASPCRecord::ASPCRecord(ASPCRecord *srcRecord)
    : TES5Record((TES5Record *)srcRecord)
    {
        if (srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        OBND = srcRecord->OBND;
        SNAM = srcRecord->SNAM;
        RDAT = srcRecord->RDAT;
        BNAM = srcRecord->BNAM;
    }

ASPCRecord::~ASPCRecord()
    {
        //
    }

bool ASPCRecord::VisitFormIDs(FormIDOp &op)
    {
        if (!IsLoaded())
            return false;

        if (SNAM.IsLoaded())
            op.Accept(SNAM.value);
        if (RDAT.IsLoaded())
            op.Accept(RDAT.value);
        if (BNAM.IsLoaded())
            op.Accept(BNAM.value);

        return op.Stop();
    }


uint32_t ASPCRecord::GetType()
    {
        return REV32(ASPC);
    }

char * ASPCRecord::GetStrType()
    {
        return "ASPC";
    }

int32_t ASPCRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        while(buffer < end_buffer)
        {
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
                case REV32(SNAM):
                    SNAM.Read(buffer, subSize);
                    break;
                case REV32(RDAT):
                    RDAT.Read(buffer, subSize);
                    break;
                case REV32(BNAM):
                    BNAM.Read(buffer, subSize);
                    break;
                default:
                    //printer("Filename = %s\n", FileName);
                    printer("  ASPC: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n", buffer - 6);
                    buffer = end_buffer;
                    break;
            }
        };
        return 0;
    }

int32_t ASPCRecord::Unload()
    {
        IsLoaded(false);
        IsChanged(false);
        EDID.Unload();
        OBND.Unload();
        SNAM.Unload();
        RDAT.Unload();
        BNAM.Unload();
        return 1;
    }

int32_t ASPCRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(OBND);
        WRITE(SNAM);
        WRITE(RDAT);
        WRITE(BNAM);
        return -1;
    }

bool ASPCRecord::operator ==(const ASPCRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                OBND == other.OBND &&
                SNAM == other.SNAM &&
                RDAT == other.RDAT &&
                BNAM == other.BNAM);
    }

bool ASPCRecord::operator !=(const ASPCRecord &other) const
    {
        return !(*this == other);
    }

bool ASPCRecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const ASPCRecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk