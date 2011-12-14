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
#include "FURNRecord.h"

namespace FNV
{
FURNRecord::FURNRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

FURNRecord::FURNRecord(FURNRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    SCRI = srcRecord->SCRI;
    Destructable = srcRecord->Destructable;
    MNAM = srcRecord->MNAM;
    return;
    }

FURNRecord::~FURNRecord()
    {
    //
    }

bool FURNRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(Destructable.IsLoaded())
        {
        for(UINT32 x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }

    return op.Stop();
    }

bool FURNRecord::IsAnim01()
    {
    return (MNAM.value & fIsAnim01) != 0;
    }

void FURNRecord::IsAnim01(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim01) : (MNAM.value & ~fIsAnim01);
    }

bool FURNRecord::IsAnim02()
    {
    return (MNAM.value & fIsAnim02) != 0;
    }

void FURNRecord::IsAnim02(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim02) : (MNAM.value & ~fIsAnim02);
    }

bool FURNRecord::IsAnim03()
    {
    return (MNAM.value & fIsAnim03) != 0;
    }

void FURNRecord::IsAnim03(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim03) : (MNAM.value & ~fIsAnim03);
    }

bool FURNRecord::IsAnim04()
    {
    return (MNAM.value & fIsAnim04) != 0;
    }

void FURNRecord::IsAnim04(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim04) : (MNAM.value & ~fIsAnim04);
    }

bool FURNRecord::IsAnim05()
    {
    return (MNAM.value & fIsAnim05) != 0;
    }

void FURNRecord::IsAnim05(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim05) : (MNAM.value & ~fIsAnim05);
    }

bool FURNRecord::IsAnim06()
    {
    return (MNAM.value & fIsAnim06) != 0;
    }

void FURNRecord::IsAnim06(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim06) : (MNAM.value & ~fIsAnim06);
    }

bool FURNRecord::IsAnim07()
    {
    return (MNAM.value & fIsAnim07) != 0;
    }

void FURNRecord::IsAnim07(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim07) : (MNAM.value & ~fIsAnim07);
    }

bool FURNRecord::IsAnim08()
    {
    return (MNAM.value & fIsAnim08) != 0;
    }

void FURNRecord::IsAnim08(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim08) : (MNAM.value & ~fIsAnim08);
    }

bool FURNRecord::IsAnim09()
    {
    return (MNAM.value & fIsAnim09) != 0;
    }

void FURNRecord::IsAnim09(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim09) : (MNAM.value & ~fIsAnim09);
    }

bool FURNRecord::IsAnim10()
    {
    return (MNAM.value & fIsAnim10) != 0;
    }

void FURNRecord::IsAnim10(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim10) : (MNAM.value & ~fIsAnim10);
    }

bool FURNRecord::IsAnim11()
    {
    return (MNAM.value & fIsAnim11) != 0;
    }

void FURNRecord::IsAnim11(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim11) : (MNAM.value & ~fIsAnim11);
    }

bool FURNRecord::IsAnim12()
    {
    return (MNAM.value & fIsAnim12) != 0;
    }

void FURNRecord::IsAnim12(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim12) : (MNAM.value & ~fIsAnim12);
    }

bool FURNRecord::IsAnim13()
    {
    return (MNAM.value & fIsAnim13) != 0;
    }

void FURNRecord::IsAnim13(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim13) : (MNAM.value & ~fIsAnim13);
    }

bool FURNRecord::IsAnim14()
    {
    return (MNAM.value & fIsAnim14) != 0;
    }

void FURNRecord::IsAnim14(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim14) : (MNAM.value & ~fIsAnim14);
    }

bool FURNRecord::IsAnim15()
    {
    return (MNAM.value & fIsAnim15) != 0;
    }

void FURNRecord::IsAnim15(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim15) : (MNAM.value & ~fIsAnim15);
    }

bool FURNRecord::IsAnim16()
    {
    return (MNAM.value & fIsAnim16) != 0;
    }

void FURNRecord::IsAnim16(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim16) : (MNAM.value & ~fIsAnim16);
    }

bool FURNRecord::IsAnim17()
    {
    return (MNAM.value & fIsAnim17) != 0;
    }

void FURNRecord::IsAnim17(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim17) : (MNAM.value & ~fIsAnim17);
    }

bool FURNRecord::IsAnim18()
    {
    return (MNAM.value & fIsAnim18) != 0;
    }

void FURNRecord::IsAnim18(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim18) : (MNAM.value & ~fIsAnim18);
    }

bool FURNRecord::IsAnim19()
    {
    return (MNAM.value & fIsAnim19) != 0;
    }

void FURNRecord::IsAnim19(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim19) : (MNAM.value & ~fIsAnim19);
    }

bool FURNRecord::IsAnim20()
    {
    return (MNAM.value & fIsAnim20) != 0;
    }

void FURNRecord::IsAnim20(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim20) : (MNAM.value & ~fIsAnim20);
    }

bool FURNRecord::IsAnim21()
    {
    return (MNAM.value & fIsAnim21) != 0;
    }

void FURNRecord::IsAnim21(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim21) : (MNAM.value & ~fIsAnim21);
    }

bool FURNRecord::IsAnim22()
    {
    return (MNAM.value & fIsAnim22) != 0;
    }

void FURNRecord::IsAnim22(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim22) : (MNAM.value & ~fIsAnim22);
    }

bool FURNRecord::IsAnim23()
    {
    return (MNAM.value & fIsAnim23) != 0;
    }

void FURNRecord::IsAnim23(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim23) : (MNAM.value & ~fIsAnim23);
    }

bool FURNRecord::IsAnim24()
    {
    return (MNAM.value & fIsAnim24) != 0;
    }

void FURNRecord::IsAnim24(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim24) : (MNAM.value & ~fIsAnim24);
    }

bool FURNRecord::IsAnim25()
    {
    return (MNAM.value & fIsAnim25) != 0;
    }

void FURNRecord::IsAnim25(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim25) : (MNAM.value & ~fIsAnim25);
    }

bool FURNRecord::IsAnim26()
    {
    return (MNAM.value & fIsAnim26) != 0;
    }

void FURNRecord::IsAnim26(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim26) : (MNAM.value & ~fIsAnim26);
    }

bool FURNRecord::IsAnim27()
    {
    return (MNAM.value & fIsAnim27) != 0;
    }

void FURNRecord::IsAnim27(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim27) : (MNAM.value & ~fIsAnim27);
    }

bool FURNRecord::IsAnim28()
    {
    return (MNAM.value & fIsAnim28) != 0;
    }

void FURNRecord::IsAnim28(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim28) : (MNAM.value & ~fIsAnim28);
    }

bool FURNRecord::IsAnim29()
    {
    return (MNAM.value & fIsAnim29) != 0;
    }

void FURNRecord::IsAnim29(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim29) : (MNAM.value & ~fIsAnim29);
    }

bool FURNRecord::IsAnim30()
    {
    return (MNAM.value & fIsAnim30) != 0;
    }

void FURNRecord::IsAnim30(bool value)
    {
    MNAM.value = value ? (MNAM.value | fIsAnim30) : (MNAM.value & ~fIsAnim30);
    }

bool FURNRecord::IsSitAnim()
    {
    return (MNAM.value & fIsSitAnim) != 0;
    }

void FURNRecord::IsSitAnim(bool value)
    {
    if(value)
        {
        MNAM.value &= ~fIsSleepAnim;
        MNAM.value |= fIsSitAnim;
        }
    else
        {
        MNAM.value &= ~fIsSitAnim;
        MNAM.value |= fIsSleepAnim;
        }
    }

bool FURNRecord::IsSleepAnim()
    {
    return (MNAM.value & fIsSleepAnim) != 0;
    }

void FURNRecord::IsSleepAnim(bool value)
    {
    if(value)
        {
        MNAM.value &= ~fIsSitAnim;
        MNAM.value |= fIsSleepAnim;
        }
    else
        {
        MNAM.value &= ~fIsSleepAnim;
        MNAM.value |= fIsSitAnim;
        }
    }

bool FURNRecord::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((MNAM.value & Mask) == Mask) : ((MNAM.value & Mask) != 0);
    }

void FURNRecord::SetFlagMask(UINT32 Mask)
    {
    MNAM.value = Mask;
    }

UINT32 FURNRecord::GetType()
    {
    return REV32(FURN);
    }

STRING FURNRecord::GetStrType()
    {
    return "FURN";
    }

SINT32 FURNRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DEST):
                Destructable.Load();
                Destructable->DEST.Read(buffer, subSize);
                break;
            case REV32(DSTD):
                Destructable.Load();
                Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DSTD.Read(buffer, subSize);
                break;
            case REV32(DMDL):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DMDT):
                Destructable.Load();
                if(Destructable->Stages.value.size() == 0)
                    Destructable->Stages.value.push_back(new DESTSTAGE);
                Destructable->Stages.value.back()->DMDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DSTF):
                //Marks end of a destruction stage
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  FURN: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 FURNRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    Destructable.Unload();
    MNAM.Unload();
    return 1;
    }

SINT32 FURNRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(MNAM);
    return -1;
    }

bool FURNRecord::operator ==(const FURNRecord &other) const
    {
    return (OBND == other.OBND &&
            SCRI == other.SCRI &&
            MNAM == other.MNAM &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            Destructable == other.Destructable);
    }

bool FURNRecord::operator !=(const FURNRecord &other) const
    {
    return !(*this == other);
    }

bool FURNRecord::equals(Record *other)
    {
    return *this == *(FURNRecord *)other;
    }
}