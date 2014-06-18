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
#include "STATRecord.h"

namespace FNV
{
STATRecord::STATRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

STATRecord::STATRecord(STATRecord *srcRecord):
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
    MODL = srcRecord->MODL;
    BRUS = srcRecord->BRUS;
    RNAM = srcRecord->RNAM;
    return;
    }

STATRecord::~STATRecord()
    {
    //
    }

bool STATRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);

    return op.Stop();
    }

bool STATRecord::IsSoundNone()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eNone);
    }

void STATRecord::IsSoundNone(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eNone : eBushA;
    }

bool STATRecord::IsSoundBushA()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushA);
    }

void STATRecord::IsSoundBushA(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushA : eNone;
    }

bool STATRecord::IsSoundBushB()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushB);
    }

void STATRecord::IsSoundBushB(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushB : eNone;
    }

bool STATRecord::IsSoundBushC()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushC);
    }

void STATRecord::IsSoundBushC(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushC : eNone;
    }

bool STATRecord::IsSoundBushD()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushD);
    }

void STATRecord::IsSoundBushD(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushD : eNone;
    }

bool STATRecord::IsSoundBushE()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushE);
    }

void STATRecord::IsSoundBushE(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushE : eNone;
    }

bool STATRecord::IsSoundBushF()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushF);
    }

void STATRecord::IsSoundBushF(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushF : eNone;
    }

bool STATRecord::IsSoundBushG()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushG);
    }

void STATRecord::IsSoundBushG(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushG : eNone;
    }

bool STATRecord::IsSoundBushH()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushH);
    }

void STATRecord::IsSoundBushH(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushH : eNone;
    }

bool STATRecord::IsSoundBushI()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushI);
    }

void STATRecord::IsSoundBushI(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushI : eNone;
    }

bool STATRecord::IsSoundBushJ()
    {
    if(!BRUS.IsLoaded()) return false;
    return (*BRUS.value == eBushJ);
    }

void STATRecord::IsSoundBushJ(bool value)
    {
    if(!BRUS.IsLoaded()) return;
    *BRUS.value = value ? eBushJ : eNone;
    }

bool STATRecord::IsSoundType(int8_t Type)
    {
    if(!BRUS.IsLoaded()) return false;
    return *BRUS.value == Type;
    }

void STATRecord::SetSoundType(int8_t Type)
    {
    BRUS.Load();
    *BRUS.value = Type;
    }

uint32_t STATRecord::GetType()
    {
    return REV32(STAT);
    }

char * STATRecord::GetStrType()
    {
    return "STAT";
    }

int32_t STATRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(BRUS):
                BRUS.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  STAT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t STATRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    BRUS.Unload();
    RNAM.Unload();
    return 1;
    }

int32_t STATRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(BRUS);
    WRITE(RNAM);
    return -1;
    }

bool STATRecord::operator ==(const STATRecord &other) const
    {
    return (OBND == other.OBND &&
            BRUS == other.BRUS &&
            RNAM == other.RNAM &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool STATRecord::operator !=(const STATRecord &other) const
    {
    return !(*this == other);
    }

bool STATRecord::equals(Record *other)
    {
    return *this == *(STATRecord *)other;
    }
}