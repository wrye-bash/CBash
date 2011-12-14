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
    if(srcRecord->TX00.IsLoaded())
        {
        TX00.Load();
        TX00->TX00 = srcRecord->TX00->TX00;
        TX00->TX01 = srcRecord->TX00->TX01;
        }
    if(srcRecord->INTV.IsLoaded())
        {
        INTV.Load();
        INTV->INTV = srcRecord->INTV->INTV;
        }
    INTV = srcRecord->INTV;
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
        for(UINT32 x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    if(SCRI.IsLoaded())
        op.Accept(SCRI->value);
    if(YNAM.IsLoaded())
        op.Accept(YNAM->value);
    if(ZNAM.IsLoaded())
        op.Accept(ZNAM->value);

    return op.Stop();
    }

bool CCRDRecord::IsNone()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNone);
    }

void CCRDRecord::IsNone(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNone : eDummyDefault;
    }

bool CCRDRecord::IsHearts()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHearts);
    }

void CCRDRecord::IsHearts(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHearts : eDummyDefault;
    }

bool CCRDRecord::IsSpades()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eSpades);
    }

void CCRDRecord::IsSpades(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eSpades : eDummyDefault;
    }

bool CCRDRecord::IsDiamonds()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eDiamonds);
    }

void CCRDRecord::IsDiamonds(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eDiamonds : eDummyDefault;
    }

bool CCRDRecord::IsClubs()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eClubs);
    }

void CCRDRecord::IsClubs(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eClubs : eDummyDefault;
    }

bool CCRDRecord::IsJoker()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eJoker);
    }

void CCRDRecord::IsJoker(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eJoker : eDummyDefault;
    }

bool CCRDRecord::IsType(UINT32 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void CCRDRecord::SetType(UINT32 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 CCRDRecord::GetType()
    {
    return REV32(CCRD);
    }

STRING CCRDRecord::GetStrType()
    {
    return "CCRD";
    }

SINT32 CCRDRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                EDID.Read(buffer, subSize);
                break;
            case REV32(OBND):
                OBND.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize);
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
                TX00->TX00.Read(buffer, subSize);
                break;
            case REV32(TX01):
                TX00.Load();
                TX00->TX01.Read(buffer, subSize);
                break;
            case REV32(INTV):
                INTV.Load();
                INTV->INTV.Read(buffer, subSize);
                break;
            case REV32(INTV):
                INTV.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  CCRD: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 CCRDRecord::Unload()
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
    INTV.Unload();
    INTV.Unload();
    DATA.Unload();
    return 1;
    }

SINT32 CCRDRecord::WriteRecord(FileWriter &writer)
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
        if(TX00->TX00.IsLoaded())
            SaveHandler.writeSubRecord(REV32(TX00), TX00->TX00.value, TX00->TX00.GetSize());

        if(TX00->TX01.IsLoaded())
            SaveHandler.writeSubRecord(REV32(TX01), TX00->TX01.value, TX00->TX01.GetSize());

        }

    if(INTV.IsLoaded())
        {
        if(INTV->INTV.IsLoaded())
            SaveHandler.writeSubRecord(REV32(INTV), INTV->INTV.value, INTV->INTV.GetSize());

        }

    WRITE(INTV);
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
            TX00 == other.TX00 &&
            INTV == other.INTV &&
            INTV == other.INTV &&
            DATA == other.DATA);
    }

bool CCRDRecord::operator !=(const CCRDRecord &other) const
    {
    return !(*this == other);
    }

bool CCRDRecord::equals(const Record *other) const
    {
    return *this == *(CCRDRecord *)other;
    }
}