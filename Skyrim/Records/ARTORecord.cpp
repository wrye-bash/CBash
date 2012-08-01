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
#include "ARTORecord.h"

namespace Sk {

ARTORecord::ARTORecord(unsigned char *_recData)
    : TES5Record(_recData)
    {
        //
    }

ARTORecord::ARTORecord(ARTORecord *srcRecord)
    : TES5Record()
    {
        if (srcRecord==NULL)
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
        MODL = srcRecord->MODL;
        DNAM = srcRecord->DNAM;
        return;
    }

ARTORecord::~ARTORecord()
    {
        //
    }

bool ARTORecord::IsFirstPerson() const
    {
        return (DNAM.value & fIsFirstPerson) != 0;
    }

void ARTORecord::IsFirstPerson(bool value)
    {
        SETBIT(DNAM.value, fIsFirstPerson, value);
    }

bool ARTORecord::IsAttachedToModel() const
    {
        return (DNAM.value & fIsAttachedToModel) != 0;
    }

void ARTORecord::IsAttachedToModel(bool value)
    {
        SETBIT(DNAM.value, fIsAttachedToModel, value);
    }

bool ARTORecord::IsFlagMask(UINT32 Mask, bool Exact) const
    {
        return Exact ? ((DNAM.value & Mask) == Mask) : ((DNAM.value & Mask) != 0);
    }

void ARTORecord::SetFlagMask(UINT32 Mask)
    {
        DNAM.value = Mask;
    }

UINT32 ARTORecord::GetType()
    {
        return REV32(ARTO);
    }

STRING ARTORecord::GetStrType()
    {
        return "ARTO";
    }

SINT32 ARTORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                case REV32(OBND):
                    OBND.Read(buffer, subSize);
                    break;
                case REV32(MODL):
                    MODL.Load();
                    MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(MODT):
                    MODL.Load();
                    //MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(DNAM):
                    DNAM.Read(buffer, subSize);
                    break;
                default:
                    //printer("Filename = %s\n", FileName);
                    printer("  AARTO: %08X - Unknown subType = %04x\n", formID, subType);
                    CBASH_CHUNK_DEBUG
                    printer("  Size = %i\n", subSize);
                    printer("  CurPos = %04x\n", buffer - 6);
                    buffer = end_buffer;
                    break;
            }
        };
        return 0;
    }

SINT32 ARTORecord::Unload()
    {
        IsLoaded(false);
        IsChanged(false);
        EDID.Unload();
        OBND.Unload();
        MODL.Unload();
        DNAM.Unload();
        return 1;
    }

SINT32 ARTORecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(OBND);
        WRITE(MODL);
        WRITE(DNAM);
        return -1;
    }

bool ARTORecord::operator ==(const ARTORecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                OBND == other.OBND &&
                MODL == other.MODL &&
                DNAM == other.DNAM);
    }

bool ARTORecord::operator !=(const ARTORecord &other) const
    {
        return !(*this == other);
    }

bool ARTORecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const ARTORecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk