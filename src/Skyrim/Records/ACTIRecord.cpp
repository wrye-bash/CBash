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
#include "ACTIRecord.h"
#include "..\..\ModFile.h"

namespace Sk
{
ACTIRecord::ACTIRecord(unsigned char *_recData) :
    TES5Record(_recData)
{
    //
}

ACTIRecord::ACTIRecord(ACTIRecord *srcRecord) :
    TES5Record((TES5Record *)srcRecord)
{
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    VMAD = srcRecord->VMAD;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    Destructable = srcRecord->Destructable;
    KWDA = srcRecord->KWDA;
    PNAM = srcRecord->PNAM;
    SNAM = srcRecord->SNAM;
    VNAM = srcRecord->VNAM;
    WNAM = srcRecord->WNAM;
    RNAM = srcRecord->RNAM;
    FNAM = srcRecord->FNAM;
    KNAM = srcRecord->KNAM;
}

ACTIRecord::~ACTIRecord()
{
    //
}

bool ACTIRecord::VisitFormIDs(FormIDOp &op)
{
    if(!IsLoaded())
        return false;

    if (MODL.IsLoaded())
        MODL->Textures.VisitFormIDs(op);

    if (Destructable.IsLoaded())
        Destructable->VisitFormIDs(op);

    for (uint32_t x = 0; x < KWDA.value.size(); ++x)
        op.Accept(KWDA.value[x]);

    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(VNAM.IsLoaded())
        op.Accept(VNAM.value);
    if (WNAM.IsLoaded())
        op.Accept(WNAM.value);
    if (KNAM.IsLoaded())
        op.Accept(KNAM.value);

    return op.Stop();
}

uint32_t ACTIRecord::GetType()
{
    return REV32(ACTI);
}

char * ACTIRecord::GetStrType()
{
    return "ACTI";
}

int32_t ACTIRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            MODL.Load();
            MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(MODT):
            MODL.Load();
            MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(MODS):
            MODL.Load();
            MODL->Textures.Read(buffer, subSize);
            break;
        case REV32(DEST):
            Destructable.Load();
            Destructable->DEST.Read(buffer, subSize);
            break;
        case REV32(DSTD):
            Destructable.Load();
            Destructable->Stages.value.push_back(new SKDESTSTAGE);
            Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
            break;
        case REV32(DMDL):
            Destructable.Load();
            if(Destructable->Stages.value.size() == 0)
                Destructable->Stages.value.push_back(new SKDESTSTAGE);
            Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(DMDT):
            Destructable.Load();
            if(Destructable->Stages.value.size() == 0)
                Destructable->Stages.value.push_back(new SKDESTSTAGE);
            Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(DMDS):
            Destructable.Load();
            if (Destructable->Stages.value.size() == 0)
                Destructable->Stages.value.push_back(new SKDESTSTAGE);
            Destructable->Stages.value.back()->DMDS.Read(buffer, subSize);
            break;
        case REV32(DSTF):
            //Marks end of a destruction stage
            buffer += subSize;
            break;
        case REV32(KSIZ):
            // Number of KWDAs
            buffer += subSize;
            break;
        case REV32(KWDA):
            KWDA.Read(buffer, subSize);
            break;
        case REV32(PNAM):
            PNAM.Read(buffer, subSize);
            break;
        case REV32(SNAM):
            SNAM.Read(buffer, subSize);
            break;
        case REV32(VNAM):
            VNAM.Read(buffer, subSize);
            break;
        case REV32(WNAM):
            WNAM.Read(buffer, subSize);
            break;
        case REV32(RNAM):
            RNAM.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
            break;
        case REV32(FNAM):
            FNAM.Read(buffer, subSize);
            break;
        case REV32(KNAM):
            KNAM.Read(buffer, subSize);
            break;
        default:
            //printer("FileName = %s\n", FileName);
            printer("  ACTI: %08X - Unknown subType = %04x\n", formID, subType);
            CBASH_CHUNK_DEBUG
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t ACTIRecord::Unload()
{
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    VMAD.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    Destructable.Unload();
    KWDA.Unload();
    PNAM.Unload();
    SNAM.Unload();
    VNAM.Unload();
    WNAM.Unload();
    RNAM.Unload();
    FNAM.Unload();
    KNAM.Unload();
    return 1;
}

int32_t ACTIRecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(VMAD);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    Destructable.Write(writer);
    WRITE(KWDA);
    WRITE(PNAM);
    WRITE(SNAM);
    WRITE(VNAM);
    WRITE(WNAM);
    WRITE(RNAM);
    WRITE(FNAM);
    WRITE(KNAM);
    return -1;
}

bool ACTIRecord::operator ==(const ACTIRecord &other) const
{
    return (EDID.equalsi(other.EDID) &&
            VMAD == other.VMAD &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            Destructable == other.Destructable &&
            KWDA == other.KWDA &&
            PNAM == other.PNAM &&
            SNAM == other.SNAM &&
            VNAM == other.VNAM &&
            WNAM == other.WNAM &&
            RNAM.equals(other.RNAM) &&
            FNAM == other.FNAM &&
            KNAM == other.KNAM
            );
}

bool ACTIRecord::operator !=(const ACTIRecord &other) const
{
    return !(*this == other);
}

bool ACTIRecord::equals(Record *other)
{
    return *this == *(ACTIRecord *)other;
}

} // namespace Sk
