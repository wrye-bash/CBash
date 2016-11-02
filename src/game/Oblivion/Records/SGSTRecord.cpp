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
#include "SGSTRecord.h"

namespace Ob
{
SGSTRecord::SGSTDATA::SGSTDATA():
    uses(0),
    value(0),
    weight(0.0f)
    {
    //
    }

SGSTRecord::SGSTDATA::~SGSTDATA()
    {
    //
    }

bool SGSTRecord::SGSTDATA::operator ==(const SGSTDATA &other) const
    {
    return (uses == other.uses &&
            value == other.value &&
            AlmostEqual(weight,other.weight,2));
    }

bool SGSTRecord::SGSTDATA::operator !=(const SGSTDATA &other) const
    {
    return !(*this == other);
    }

SGSTRecord::SGSTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

SGSTRecord::SGSTRecord(SGSTRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    MODL = srcRecord->MODL;
    ICON = srcRecord->ICON;
    SCRI = srcRecord->SCRI;
    Effects = srcRecord->Effects;
    DATA = srcRecord->DATA;
    OBME = srcRecord->OBME;
    }

SGSTRecord::~SGSTRecord()
    {
    //
    }

bool SGSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    for(uint32_t ListIndex = 0; ListIndex < Effects.value.size(); ListIndex++)
        Effects.value[ListIndex]->VisitFormIDs(op);

    return op.Stop();
    }

uint32_t SGSTRecord::GetType()
    {
    return REV32(SGST);
    }

char * SGSTRecord::GetStrType()
    {
    return "SGST";
    }

int32_t SGSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    bool bNoOBME = true;
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
            case REV32(OBME):
                OBME.Load();
                OBME->OBME.Read(buffer, subSize);
                break;
            case REV32(FULL):
                if(Effects.value.size())
                    Effects.value.back()->FULL.Read(buffer, subSize, CompressedOnDisk);
                else
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
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(EFME):
                bNoOBME = false;
                Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFME.Read(buffer, subSize);
                break;
            case REV32(EFID):
                if(bNoOBME || Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFID.Read(buffer, subSize);
                bNoOBME = true;
                break;
            case REV32(EFIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->EFIT.Read(buffer, subSize);
                break;
            case REV32(SCIT):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->SCIT.Read(buffer, subSize);
                break;
            case REV32(EFII):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFII.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(EFIX):
                if(Effects.value.size() == 0)
                    Effects.value.push_back(new GENEffect);
                Effects.value.back()->OBME.Load();
                Effects.value.back()->OBME->EFIX.Read(buffer, subSize);
                break;
            case REV32(EFXX):
                buffer += subSize;
                break;
            case REV32(DATX):
                OBME.Load();
                OBME->DATX.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SGST: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SGSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ICON.Unload();
    SCRI.Unload();
    Effects.Unload();
    DATA.Unload();
    OBME.Unload();
    return 1;
    }

int32_t SGSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    if(OBME.IsLoaded())
        OBME->WRITE(OBME);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ICON);
    WRITE(SCRI);
    Effects.Write(writer);
    if(OBME.IsLoaded())
        {
        if(Effects.value.size())
            WRITEEMPTY(EFXX);
        if(OBME->DATX.IsLoaded())
            OBME->WRITE(DATX);
        }
    WRITE(DATA);
    return -1;
    }

bool SGSTRecord::operator ==(const SGSTRecord &other) const
    {
    return (SCRI == other.SCRI &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            ICON.equalsi(other.ICON) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            OBME == other.OBME &&
            Effects == other.Effects);
    }

bool SGSTRecord::operator !=(const SGSTRecord &other) const
    {
    return !(*this == other);
    }

bool SGSTRecord::equals(Record *other)
    {
    return *this == *(SGSTRecord *)other;
    }
}