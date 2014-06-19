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
#include "IDLMRecord.h"

namespace FNV
{
IDLMRecord::IDLMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IDLMRecord::IDLMRecord(IDLMRecord *srcRecord):
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
    IDLF = srcRecord->IDLF;
    IDLC = srcRecord->IDLC;
    IDLT = srcRecord->IDLT;
    IDLA = srcRecord->IDLA;
    return;
    }

IDLMRecord::~IDLMRecord()
    {
    //
    }

bool IDLMRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < IDLA.value.size(); x++)
        op.Accept(IDLA.value[x]);

    return op.Stop();
    }

bool IDLMRecord::IsRunInSequence()
    {
    return (IDLF.value & fIsRunInSequence) != 0;
    }

void IDLMRecord::IsRunInSequence(bool value)
    {
    SETBIT(IDLF.value, fIsRunInSequence, value);
    }

bool IDLMRecord::IsDoOnce()
    {
    return (IDLF.value & fIsDoOnce) != 0;
    }

void IDLMRecord::IsDoOnce(bool value)
    {
    SETBIT(IDLF.value, fIsDoOnce, value);
    }

bool IDLMRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((IDLF.value & Mask) == Mask) : ((IDLF.value & Mask) != 0);
    }

void IDLMRecord::SetFlagMask(uint8_t Mask)
    {
    IDLF.value = Mask;
    }

uint32_t IDLMRecord::GetType()
    {
    return REV32(IDLM);
    }

char * IDLMRecord::GetStrType()
    {
    return "IDLM";
    }

int32_t IDLMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(IDLF):
                IDLF.Read(buffer, subSize);
                break;
            case REV32(IDLC):
                //may be a uint32_t instead, but only the lower 8 bits are used, so skip extra
                //IDLC.Read(buffer, 1);
                //buffer += subSize - 1;
                //Testing snippet. Verified that the extra bits aren't in use in FalloutNV.esm
                switch(subSize)
                    {
                    case 1:
                        IDLC.Read(buffer, subSize);
                        break;
                    case 4:
                        {
                        IDLC.Read(buffer, 1);
                        uint32_t test = 0;
                        memcpy(&test, buffer, 3);
                        buffer += 3;
                        if(test != 0)
                            {
                            printer("  IDLM: %08X - Unexpected IDLC value. Expected (0) and got (%u). IDLC = %u.\n", formID, test, IDLC.value);
                            CBASH_CHUNK_DEBUG
                            printer("  Size = %i\n", subSize);
                            printer("  CurPos = %04x\n\n", buffer - 6);
                            }
                        }
                        break;
                    default:
                        printer("  IDLM: %08X - Unexpected IDLC chunk size. Expected (1 or 4) and got (%u)\n", formID, subSize);
                        CBASH_CHUNK_DEBUG
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(IDLT):
                IDLT.Read(buffer, subSize);
                break;
            case REV32(IDLA):
                IDLA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  IDLM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t IDLMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    IDLF.Unload();
    IDLC.Unload();
    IDLT.Unload();
    IDLA.Unload();
    return 1;
    }

int32_t IDLMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(IDLF);
    WRITE(IDLC);
    WRITE(IDLT);
    WRITE(IDLA);
    return -1;
    }

bool IDLMRecord::operator ==(const IDLMRecord &other) const
    {
    return (OBND == other.OBND &&
            IDLF == other.IDLF &&
            IDLC == other.IDLC &&
            IDLT == other.IDLT &&
            EDID.equalsi(other.EDID) &&
            IDLA == other.IDLA);
    }

bool IDLMRecord::operator !=(const IDLMRecord &other) const
    {
    return !(*this == other);
    }

bool IDLMRecord::equals(Record *other)
    {
    return *this == *(IDLMRecord *)other;
    }
}