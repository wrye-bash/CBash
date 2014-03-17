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
#include "IPCTRecord.h"

namespace FNV
{
IPCTRecord::IPCTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IPCTRecord::IPCTRecord(IPCTRecord *srcRecord):
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

    MODL = srcRecord->MODL;

    DATA = srcRecord->DATA;
    DODT = srcRecord->DODT;
    DNAM = srcRecord->DNAM;
    SNAM = srcRecord->SNAM;
    NAM1 = srcRecord->NAM1;
    return;
    }

IPCTRecord::~IPCTRecord()
    {
    //
    }

bool IPCTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(DNAM.IsLoaded())
        op.Accept(DNAM.value);
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(NAM1.IsLoaded())
        op.Accept(NAM1.value);

    return op.Stop();
    }

bool IPCTRecord::IsNoDecalData()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsNoDecalData) != 0;
    }

void IPCTRecord::IsNoDecalData(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsNoDecalData, value);
    }

bool IPCTRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA->flags & Mask) == Mask) : ((DATA->flags & Mask) != 0);
    }

void IPCTRecord::SetFlagMask(UINT32 Mask)
    {
    DATA.Load();
    DATA->flags = Mask;
    }

bool IPCTRecord::IsLoud()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->soundLevel == eLoud);
    }

bool IPCTRecord::IsNormal()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->soundLevel == eNormal);
    }

bool IPCTRecord::IsSilent()
    {
    if(!DATA.IsLoaded()) return false;
    return (DATA->soundLevel == eSilent);
    }

bool IPCTRecord::IsObjectParallax()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsParallax) != 0 : false;
    }

void IPCTRecord::IsObjectParallax(bool value)
    {
    if (!DODT.IsLoaded()) return;
    SETBIT(DODT->flags, fIsParallax, value);
    }

bool IPCTRecord::IsObjectAlphaBlending()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaBlending) != 0 : false;
    }

void IPCTRecord::IsObjectAlphaBlending(bool value)
    {
    if (!DODT.IsLoaded()) return;
    SETBIT(DODT->flags, fIsAlphaBlending, value);
    }

bool IPCTRecord::IsObjectAlphaTesting()
    {
    return DODT.IsLoaded() ? (DODT->flags & fIsAlphaTesting) != 0 : false;
    }

void IPCTRecord::IsObjectAlphaTesting(bool value)
    {
    if (!DODT.IsLoaded()) return;
    SETBIT(DODT->flags, fIsAlphaTesting, value);
    }

bool IPCTRecord::IsObjectFlagMask(UINT8 Mask, bool Exact)
    {
    if(!DODT.IsLoaded()) return false;
    return Exact ? ((DODT->flags & Mask) == Mask) : ((DODT->flags & Mask) != 0);
    }

void IPCTRecord::SetObjectFlagMask(UINT8 Mask)
    {
    DODT.Load();
    DODT->flags = Mask;
    }

bool IPCTRecord::IsSoundLevelType(UINT8 Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->soundLevel == Type;
    }

void IPCTRecord::SetSoundLevelType(UINT8 Type)
    {
    DATA.Load();
    DATA->soundLevel = Type;
    }

UINT32 IPCTRecord::GetType()
    {
    return REV32(IPCT);
    }

STRING IPCTRecord::GetStrType()
    {
    return "IPCT";
    }

SINT32 IPCTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(DODT):
                DODT.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(NAM1):
                NAM1.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  IPCT: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 IPCTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    MODL.Unload();
    DATA.Unload();
    DODT.Unload();
    DNAM.Unload();
    SNAM.Unload();
    NAM1.Unload();
    return 1;
    }

SINT32 IPCTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);

    MODL.Write(writer);

    WRITE(DATA);
    WRITE(DODT);
    WRITE(DNAM);
    WRITE(SNAM);
    WRITE(NAM1);

    return -1;
    }

bool IPCTRecord::operator ==(const IPCTRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            MODL == other.MODL &&
            DATA == other.DATA &&
            DODT == other.DODT &&
            DNAM == other.DNAM &&
            SNAM == other.SNAM &&
            NAM1 == other.NAM1);
    }

bool IPCTRecord::operator !=(const IPCTRecord &other) const
    {
    return !(*this == other);
    }

bool IPCTRecord::equals(Record *other)
    {
    return *this == *(IPCTRecord *)other;
    }
}