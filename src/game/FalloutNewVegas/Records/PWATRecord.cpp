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
#include "common/Common.h"
#include "PWATRecord.h"

namespace FNV
{
PWATRecord::PWATDNAM::PWATDNAM():
    flags(0),
    water(0)
    {
    //
    }

PWATRecord::PWATDNAM::~PWATDNAM()
    {
    //
    }

bool PWATRecord::PWATDNAM::operator ==(const PWATDNAM &other) const
    {
    return (flags == other.flags &&
            water == other.water);
    }

bool PWATRecord::PWATDNAM::operator !=(const PWATDNAM &other) const
    {
    return !(*this == other);
    }

PWATRecord::PWATRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PWATRecord::PWATRecord(PWATRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    return;
    }

PWATRecord::~PWATRecord()
    {
    //
    }

bool PWATRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    op.Accept(DNAM.value.water);

    return op.Stop();
    }

bool PWATRecord::IsReflects()
    {
    return (DNAM.value.flags & fIsReflects) != 0;
    }

void PWATRecord::IsReflects(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflects, value);
    }

bool PWATRecord::IsReflectsActors()
    {
    return (DNAM.value.flags & fIsReflectsActors) != 0;
    }

void PWATRecord::IsReflectsActors(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsActors, value);
    }

bool PWATRecord::IsReflectsLand()
    {
    return (DNAM.value.flags & fIsReflectsLand) != 0;
    }

void PWATRecord::IsReflectsLand(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsLand, value);
    }

bool PWATRecord::IsReflectsLODLand()
    {
    return (DNAM.value.flags & fIsReflectsLODLand) != 0;
    }

void PWATRecord::IsReflectsLODLand(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsLODLand, value);
    }

bool PWATRecord::IsReflectsLODBuildings()
    {
    return (DNAM.value.flags & fIsReflectsLODBuildings) != 0;
    }

void PWATRecord::IsReflectsLODBuildings(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsLODBuildings, value);
    }

bool PWATRecord::IsReflectsTrees()
    {
    return (DNAM.value.flags & fIsReflectsTrees) != 0;
    }

void PWATRecord::IsReflectsTrees(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsTrees, value);
    }

bool PWATRecord::IsReflectsSky()
    {
    return (DNAM.value.flags & fIsReflectsSky) != 0;
    }

void PWATRecord::IsReflectsSky(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsSky, value);
    }

bool PWATRecord::IsReflectsDynamicObjects()
    {
    return (DNAM.value.flags & fIsReflectsDynamicObjects) != 0;
    }

void PWATRecord::IsReflectsDynamicObjects(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsDynamicObjects, value);
    }

bool PWATRecord::IsReflectsDeadBodies()
    {
    return (DNAM.value.flags & fIsReflectsDeadBodies) != 0;
    }

void PWATRecord::IsReflectsDeadBodies(bool value)
    {
    SETBIT(DNAM.value.flags, fIsReflectsDeadBodies, value);
    }

bool PWATRecord::IsRefracts()
    {
    return (DNAM.value.flags & fIsRefracts) != 0;
    }

void PWATRecord::IsRefracts(bool value)
    {
    SETBIT(DNAM.value.flags, fIsRefracts, value);
    }

bool PWATRecord::IsRefractsActors()
    {
    return (DNAM.value.flags & fIsRefractsActors) != 0;
    }

void PWATRecord::IsRefractsActors(bool value)
    {
    SETBIT(DNAM.value.flags, fIsRefractsActors, value);
    }

bool PWATRecord::IsRefractsLand()
    {
    return (DNAM.value.flags & fIsRefractsLand) != 0;
    }

void PWATRecord::IsRefractsLand(bool value)
    {
    SETBIT(DNAM.value.flags, fIsRefractsLand, value);
    }

bool PWATRecord::IsRefractsDynamicObjects()
    {
    return (DNAM.value.flags & fIsRefractsDynamicObjects) != 0;
    }

void PWATRecord::IsRefractsDynamicObjects(bool value)
    {
    SETBIT(DNAM.value.flags, fIsRefractsDynamicObjects, value);
    }

bool PWATRecord::IsRefractsDeadBodies()
    {
    return (DNAM.value.flags & fIsRefractsDeadBodies) != 0;
    }

void PWATRecord::IsRefractsDeadBodies(bool value)
    {
    SETBIT(DNAM.value.flags, fIsRefractsDeadBodies, value);
    }

bool PWATRecord::IsSilhouetteReflections()
    {
    return (DNAM.value.flags & fIsSilhouetteReflections) != 0;
    }

void PWATRecord::IsSilhouetteReflections(bool value)
    {
    SETBIT(DNAM.value.flags, fIsSilhouetteReflections, value);
    }

bool PWATRecord::IsDepth()
    {
    return (DNAM.value.flags & fIsDepth) != 0;
    }

void PWATRecord::IsDepth(bool value)
    {
    SETBIT(DNAM.value.flags, fIsDepth, value);
    }

bool PWATRecord::IsObjectTextureCoordinates()
    {
    return (DNAM.value.flags & fIsObjectTextureCoordinates) != 0;
    }

void PWATRecord::IsObjectTextureCoordinates(bool value)
    {
    SETBIT(DNAM.value.flags, fIsObjectTextureCoordinates, value);
    }

bool PWATRecord::IsNoUnderwaterFog()
    {
    return (DNAM.value.flags & fIsNoUnderwaterFog) != 0;
    }

void PWATRecord::IsNoUnderwaterFog(bool value)
    {
    SETBIT(DNAM.value.flags, fIsNoUnderwaterFog, value);
    }

bool PWATRecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags & Mask) == Mask) : ((DNAM.value.flags & Mask) != 0);
    }

void PWATRecord::SetFlagMask(uint32_t Mask)
    {
    DNAM.value.flags = Mask;
    }

uint32_t PWATRecord::GetType()
    {
    return REV32(PWAT);
    }

char * PWATRecord::GetStrType()
    {
    return "PWAT";
    }

int32_t PWATRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PWAT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PWATRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    MODL.Unload();
    DNAM.Unload();
    return 1;
    }

int32_t PWATRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    MODL.Write(writer);
    WRITE(DNAM);
    return -1;
    }

bool PWATRecord::operator ==(const PWATRecord &other) const
    {
    return (OBND == other.OBND &&
            DNAM == other.DNAM &&
            EDID.equalsi(other.EDID) &&
            MODL == other.MODL);
    }

bool PWATRecord::operator !=(const PWATRecord &other) const
    {
    return !(*this == other);
    }

bool PWATRecord::equals(Record *other)
    {
    return *this == *(PWATRecord *)other;
    }
}