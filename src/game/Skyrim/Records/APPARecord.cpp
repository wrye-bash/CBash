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
#include "..\..\ModFile.h"
#include "APPARecord.h"

namespace Sk {

APPARecord::APPADATA::APPADATA() :
    value(0),
    weight(0.0)
    {
        //
    }

APPARecord::APPADATA::~APPADATA()
    {
    //
    }

bool APPARecord::APPADATA::operator == (const APPADATA &other) const
    {
    return (value == other.value &&
            AlmostEqual(weight, other.weight, 2)
            );
    }

bool APPARecord::APPADATA::operator != (const APPADATA &other) const
    {
    return !(*this == other);
    }

APPARecord::APPARecord(unsigned char *_recData)
    : TES5Record(_recData)
    {
        //
    }

APPARecord::APPARecord(APPARecord *srcRecord)
    : TES5Record((TES5Record *)srcRecord)
    {
        if (srcRecord == NULL || !srcRecord->IsChanged())
            return;

        EDID = srcRecord->EDID;
        VMAD = srcRecord->VMAD;
        OBND = srcRecord->OBND;
        FULL = srcRecord->FULL;
        MODL = srcRecord->MODL;
        ICON = srcRecord->ICON;
        MICO = srcRecord->MICO;
        DEST = srcRecord->DEST;
        YNAM = srcRecord->YNAM;
        ZNAM = srcRecord->ZNAM;
        QUAL = srcRecord->QUAL;
        DESC = srcRecord->DESC;
        DATA = srcRecord->DATA;
    }

APPARecord::~APPARecord()
    {
        //
    }

bool APPARecord::VisitFormIDs(FormIDOp &op)
{
    if (!IsLoaded())
        return false;

    if (VMAD.IsLoaded())
        VMAD.VisitFormIDs(op);
    if (YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if (ZNAM.IsLoaded())
        op.Accept(ZNAM.value);

    return op.Stop();
}

uint32_t APPARecord::GetType()
    {
        return REV32(APPA);
    }

char * APPARecord::GetStrType()
    {
        return "APPA";
    }

int32_t APPARecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
        uint32_t subType = 0;
        uint32_t subSize = 0;
        StringLookups *LookupStrings = GetParentMod()->TES4.LookupStrings;
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
                case REV32(VMAD):
                    VMAD.Read(buffer, subSize, GetType(), CompressedOnDisk);
                    break;
                case REV32(OBND):
                    OBND.Read(buffer, subSize);
                    break;
                case REV32(FULL):
                    FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
                    break;
                case REV32(MODL):
                    MODL.Read(buffer, subSize);
                    break;
                case REV32(ICON):
                    ICON.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(MICO):
                    MICO.Read(buffer, subSize, CompressedOnDisk);
                    break;
                case REV32(DEST):
                    DEST.Read(buffer, subSize);
                    break;
                case REV32(YNAM):
                    YNAM.Read(buffer, subSize);
                    break;
                case REV32(ZNAM):
                    ZNAM.Read(buffer, subSize);
                    break;
                case REV32(QUAL):
                    QUAL.Read(buffer, subSize);
                    break;
                case REV32(DESC):
                    DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
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

int32_t APPARecord::Unload()
    {
        IsLoaded(false);
        IsChanged(false);
        EDID.Unload();
        VMAD.Unload();
        OBND.Unload();
        FULL.Unload();
        MODL.Unload();
        ICON.Unload();
        MICO.Unload();
        DEST.Unload();
        YNAM.Unload();
        ZNAM.Unload();
        QUAL.Unload();
        DESC.Unload();
        DATA.Unload();
        return 1;
    }

int32_t APPARecord::WriteRecord(FileWriter &writer)
    {
        WRITE(EDID);
        WRITE(VMAD);
        WRITE(OBND);
        WRITE(FULL);
        WRITE(MODL);
        WRITE(ICON);
        WRITE(MICO);
        WRITE(DEST);
        WRITE(YNAM);
        WRITE(ZNAM);
        WRITE(QUAL);
        WRITE(DESC);
        WRITE(DATA);
        return -1;
    }

bool APPARecord::operator ==(const APPARecord &other) const
    {
        return (EDID.equalsi(other.EDID) &&
                VMAD == other.VMAD &&
                OBND == other.OBND &&
                FULL.equals(other.FULL) &&
                MODL == other.MODL &&
                ICON.equalsi(other.ICON) &&
                MICO.equalsi(other.MICO) &&
                DEST == other.DEST &&
                YNAM == other.YNAM &&
                ZNAM == other.ZNAM &&
                QUAL == other.QUAL &&
                DESC.equals(other.DESC) &&
                DATA == other.DATA);
    }

bool APPARecord::operator !=(const APPARecord &other) const
    {
        return !(*this == other);
    }

bool APPARecord::equals(Record *other)
    {
        try
        {
            return *this == *dynamic_cast<const APPARecord *>(other);
        }
        catch(...)
        {
            return false;
        }
    }

} // namespace Sk