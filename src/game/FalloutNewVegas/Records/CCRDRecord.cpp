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
#include "CCRDRecord.h"

namespace FNV
{
CCRDRecord::CCRDRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CCRDRecord::CCRDRecord(CCRDRecord *srcRecord):
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

    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    SCRI = srcRecord->SCRI;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    if (srcRecord->TX00.IsLoaded())
        {
        TX00 = srcRecord->TX00;
        TX01 = srcRecord->TX01;
        }
    if(srcRecord->INTV1.IsLoaded())
        {
        INTV1 = srcRecord->INTV1;
        INTV2 = srcRecord->INTV2;
        }
    DATA = srcRecord->DATA;
    return;
    }

CCRDRecord::~CCRDRecord()
    {
    //
    }

bool CCRDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);

    return op.Stop();
    }

bool CCRDRecord::IsNone()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eNone);
    }

bool CCRDRecord::IsHearts()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eHearts);
    }

bool CCRDRecord::IsSpades()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eSpades);
    }

bool CCRDRecord::IsDiamonds()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eDiamonds);
    }

bool CCRDRecord::IsClubs()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eClubs);
    }

bool CCRDRecord::IsJoker()
    {
    if (!INTV1.IsLoaded()) return false;
    return (INTV1.value == eJoker);
    }

bool CCRDRecord::IsType(uint32_t Type)
    {
    if (!INTV1.IsLoaded()) return false;
    return INTV1.value == Type;
    }

void CCRDRecord::SetType(uint32_t Type)
    {
    INTV1.value = Type;
    }

uint32_t CCRDRecord::GetType()
    {
    return REV32(CCRD);
    }

char * CCRDRecord::GetStrType()
    {
    return "CCRD";
    }

int32_t CCRDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(YNAM):
                YNAM.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(TX00):
                TX00.Load();
                TX00.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(TX01):
                TX01.Load();
                TX01.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(INTV):
                if (!INTV1.IsLoaded())
                    INTV1.Read(buffer, subSize);
                else
                    INTV2.Read(buffer, subSize);
           case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t CCRDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    MICO.Unload();
    SCRI.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    TX00.Unload();
    INTV1.Unload();
    INTV2.Unload();
    DATA.Unload();
    return 1;
    }

int32_t CCRDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);

    MODL.Write(writer);

    WRITE(ICON);
    WRITE(MICO);
    WRITE(SCRI);
    WRITE(YNAM);
    WRITE(ZNAM);

    if(TX00.IsLoaded())
        {
        WRITE(TX00);
        WRITE(TX01);
        }

    if(INTV1.IsLoaded() && INTV2.IsLoaded())
        {
        INTV1.Write(REV32(INTV), writer);
        INTV2.Write(REV32(INTV), writer);
        }

    WRITE(DATA);

    return -1;
    }

bool CCRDRecord::operator ==(const CCRDRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            SCRI == other.SCRI &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            TX00.equalsi(other.TX00) &&
            TX01.equalsi(other.TX01) &&
            INTV1 == other.INTV1 &&
            INTV2 == other.INTV2 &&
            DATA == other.DATA);
    }

bool CCRDRecord::operator !=(const CCRDRecord &other) const
    {
    return !(*this == other);
    }

bool CCRDRecord::equals(Record *other)
    {
    return *this == *(CCRDRecord *)other;
    }
}