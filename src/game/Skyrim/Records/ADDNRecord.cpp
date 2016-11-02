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
#include "ADDNRecord.h"

namespace Sk {

ADDNRecord::ADDNDNAM::ADDNDNAM() :
    masterParticleSystemCap(0),
    flags(0)
{
    //
}

ADDNRecord::ADDNDNAM::~ADDNDNAM()
{
    //
}

bool ADDNRecord::ADDNDNAM::operator == (const ADDNDNAM &other) const
{
    return (masterParticleSystemCap == other.masterParticleSystemCap &&
            flags == other.flags
            );
}

bool ADDNRecord::ADDNDNAM::operator != (const ADDNDNAM &other) const
{
    return !(*this == other);
}

ADDNRecord::ADDNRecord(unsigned char *_recData) :
    TES5Record(_recData)
{
    //
}

ADDNRecord::ADDNRecord(ADDNRecord *srcRecord) :
    TES5Record((TES5Record *)srcRecord)
{
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    MODL = srcRecord->MODL;
    DATA = srcRecord->DATA;
    SNAM = srcRecord->SNAM;
    DNAM = srcRecord->DNAM;
}

ADDNRecord::~ADDNRecord()
{
    //
}

bool ADDNRecord::VisitFormIDs(FormIDOp &op)
{
    if(!IsLoaded())
        return false;

    if (SNAM.IsLoaded())
        op.Accept(SNAM.value);

    return op.Stop();
}

bool ADDNRecord::IsUnknown() const
{
    return (DNAM->flags & fUnknown) != 0;
}

void ADDNRecord::IsUnknown(bool value)
{
    SETBIT(DNAM->flags, fUnknown, value);
}

bool ADDNRecord::IsAlwaysLoaded() const
{
    return (DNAM->flags & fIsAlwaysLoaded) != 0;
}

void ADDNRecord::IsAlwaysLoaded(bool value)
{
    SETBIT(DNAM->flags, fIsAlwaysLoaded, value);
}

bool ADDNRecord::IsFlagMask(uint16_t Mask, bool Exact)
{
    return Exact ? ((DNAM->flags & Mask) == Mask) : ((DNAM->flags & Mask) != 0);
}

void ADDNRecord::SetFlagMask(uint16_t Mask)
{
    DNAM->flags = Mask;
}

uint32_t ADDNRecord::GetType()
{
    return REV32(ADDN);
}

char * ADDNRecord::GetStrType()
{
    return "ADDN";
}

int32_t ADDNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
        case REV32(MODL):
            MODL.Load();
            MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(MODT):
            MODL.Load();
            MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(DATA):
            DATA.Read(buffer, subSize);
            break;
        case REV32(SNAM):
            SNAM.Read(buffer, subSize);
            break;
        case REV32(DNAM):
            DNAM.Read(buffer, subSize);
            break;
        default:
            //printer("FileName = %s\n", FileName);
            printer("  LVLN: %08X - Unknown subType = %04x\n", formID, subType);
            CBASH_CHUNK_DEBUG
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t ADDNRecord::Unload()
{
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    DATA.Unload();
    SNAM.Unload();
    DNAM.Unload();
    return 1;
}

int32_t ADDNRecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(OBND);
    WRITE(MODL);
    WRITE(DATA);
    WRITE(SNAM);
    WRITE(DNAM);
    return -1;
}

bool ADDNRecord::operator ==(const ADDNRecord &other) const
{
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            SNAM == other.SNAM &&
            DNAM == other.DNAM
            );
}

bool ADDNRecord::operator !=(const ADDNRecord &other) const
{
    return !(*this == other);
}

bool ADDNRecord::equals(Record *other)
{
    try
    {
        return *this == *reinterpret_cast<const ADDNRecord *>(other);
    }
    catch (...)
    {
        return false;
    }
}

} // namespace Sk
