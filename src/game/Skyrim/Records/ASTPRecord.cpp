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
#include "ASTPRecord.h"

namespace Sk {

ASTPRecord::ASTPRecord(unsigned char *_recData)
    : TES5Record(_recData)
    {
        //
    }

ASTPRecord::ASTPRecord(ASTPRecord *srcRecord)
    : TES5Record((TES5Record *)srcRecord)
    {
        if (srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        MPRT = srcRecord->MPRT;
        FPRT = srcRecord->FPRT;
        MCHT = srcRecord->MCHT;
        FCHT = srcRecord->FCHT;
        DATA = srcRecord->DATA;
    }

ASTPRecord::~ASTPRecord()
    {
        //
    }

bool ASTPRecord::IsRelated() const
    {
        return DATA.value & fIsRelated;
    }

void ASTPRecord::IsRelated(bool value)
    {
        SETBIT(DATA.value, fIsRelated, value);
    }

bool ASTPRecord::IsFlagMask(uint32_t Mask, bool Exact) const
    {
        return Exact ? ((DATA.value & Mask) == Mask) : (DATA.value & Mask) != 0;
    }

void ASTPRecord::SetFlagMask(uint32_t Mask)
    {
        DATA.value = Mask;
    }

uint32_t ASTPRecord::GetType()
    {
        return REV32(ASTP);
    }

char * ASTPRecord::GetStrType()
    {
        return "ASTP";
    }

int32_t ASTPRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                case REV32(MPRT):
                    MPRT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(FPRT):
                    FPRT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(MCHT):
                    MCHT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(FCHT):
                    FCHT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(DATA):
                    DATA.Read(buffer, subSize);
                    break;
                default:
                    //printer("Filename = %s\n", FileName);
                    printer("  ASTP: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n", buffer - 6);
                    buffer = end_buffer;
                    break;
            }
        };
        return 0;
    }

int32_t ASTPRecord::Unload()
    {
        IsLoaded(false);
        IsChanged(false);
        EDID.Unload();
        MPRT.Unload();
        FPRT.Unload();
        MCHT.Unload();
        FCHT.Unload();
        DATA.Unload();
        return 1;
    }

int32_t ASTPRecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(MPRT);
        WRITE(FPRT);
        WRITE(MCHT);
        WRITE(FCHT);
        WRITE(DATA);
        return -1;
    }

bool ASTPRecord::operator ==(const ASTPRecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                MPRT.equals(other.MPRT) &&
                FPRT.equals(other.FPRT) &&
                MCHT.equals(other.MCHT) &&
                FCHT.equals(other.FCHT) &&
                DATA == other.DATA);
    }

bool ASTPRecord::operator !=(const ASTPRecord &other) const
    {
        return !(*this == other);
    }

bool ASTPRecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const ASTPRecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk