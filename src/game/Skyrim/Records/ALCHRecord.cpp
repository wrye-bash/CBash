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
#include "ALCHRecord.h"
#include "..\..\ModFile.h"

namespace Sk {

ALCHRecord::ALCHENIT::ALCHENIT() :
    value(0),
    flags(0),
    withdrawalEffect(0),
    addictionChance(0.0),
    consumeSound(0)
{
    //
}

ALCHRecord::ALCHENIT::~ALCHENIT()
{
    //
}

bool ALCHRecord::ALCHENIT::operator == (const ALCHENIT &other) const
{
    return (value == other.value &&
            flags == other.flags &&
            withdrawalEffect == other.withdrawalEffect &&
            AlmostEqual(addictionChance, other.addictionChance, 2) &&
            consumeSound == other.consumeSound
            );
}

bool ALCHRecord::ALCHENIT::operator != (const ALCHENIT &other) const
{
    return !(*this == other);
}

ALCHRecord::ALCHRecord(unsigned char *_recData) :
    TES5Record(_recData)
{
    //
}

ALCHRecord::ALCHRecord(ALCHRecord *srcRecord) :
TES5Record((TES5Record *)srcRecord)
{
    if (srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    OBND = srcRecord->OBND;
    FULL = srcRecord->FULL;
    KWDA = srcRecord->KWDA;
    DESC = srcRecord->DESC;
    MODL = srcRecord->MODL;
    Destructable = srcRecord->Destructable;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    YNAM = srcRecord->YNAM;
    ZNAM = srcRecord->ZNAM;
    ETYP = srcRecord->ETYP;
    DATA = srcRecord->DATA;
    ENIT = srcRecord->ENIT;
    Effects = srcRecord->Effects;
}

ALCHRecord::~ALCHRecord()
{
    //
}

bool ALCHRecord::VisitFormIDs(FormIDOp &op)
{
    for (uint32_t i = 0; i < KWDA.value.size(); ++i)
        op.Accept(KWDA.value[i]);
    if (MODL.IsLoaded())
        MODL->Textures.VisitFormIDs(op);
    if (Destructable.IsLoaded())
        Destructable->VisitFormIDs(op);
    if (YNAM.IsLoaded())
        op.Accept(YNAM.value);
    if (ZNAM.IsLoaded())
        op.Accept(ZNAM.value);
    if (ETYP.IsLoaded())
        op.Accept(ETYP.value);
    op.Accept(ENIT->withdrawalEffect);
    op.Accept(ENIT->consumeSound);
    for (uint32_t i = 0; i < Effects.value.size(); ++i)
        Effects.value[i]->VisitFormIDs(op);

    return op.Stop();
}

bool ALCHRecord::IsNoAutoCalc() const
{
    return (ENIT->flags & fIsNoAutoCalc) != 0;
}

void ALCHRecord::IsNoAutoCalc(bool value)
{
    SETBIT(ENIT->flags, fIsNoAutoCalc, value);
}

bool ALCHRecord::IsFood() const
{
    return (ENIT->flags & fIsFood) != 0;
}

void ALCHRecord::IsFood(bool value)
{
    SETBIT(ENIT->flags, fIsFood, value);
}

bool ALCHRecord::IsMedicine() const
{
    return (ENIT->flags & fIsMedicine) != 0;
}

void ALCHRecord::IsMedicine(bool value)
{
    SETBIT(ENIT->flags, fIsMedicine, value);
}

bool ALCHRecord::IsPoison() const
{
    return (ENIT->flags & fIsPoison) != 0;
}

void ALCHRecord::IsPoison(bool value)
{
    SETBIT(ENIT->flags, fIsPoison, value);
}

bool ALCHRecord::IsFlagMask(uint8_t Mask, bool Exact) const
{
    return Exact ? (ENIT->flags & Mask) == Mask : (ENIT->flags & Mask) != 0;
}

void ALCHRecord::SetFlagMask(uint8_t Mask)
{
    ENIT->flags = Mask;
}

uint32_t ALCHRecord::GetType()
{
    return REV32(ALCH);
}

char * ALCHRecord::GetStrType()
{
    return "ALCH";
}

int32_t ALCHRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
        case REV32(OBND):
            OBND.Read(buffer, subSize);
            break;
        case REV32(FULL):
            FULL.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
            break;
        case REV32(KSIZ):
            // Ignore on read
            buffer += subSize;
            break;
        case REV32(KWDA):
            KWDA.Read(buffer, subSize);
            break;
        case REV32(DESC):
            DESC.Read(buffer, subSize, CompressedOnDisk, LookupStrings);
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
            if (Destructable->Stages.value.size() == 0)
                Destructable->Stages.value.push_back(new SKDESTSTAGE);
            Destructable->Stages.value.back()->DMDL.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(DMDT):
            Destructable.Load();
            if (Destructable->Stages.value.size() == 0)
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
            // Skip on read
            buffer += subSize;
            break;
        case REV32(ICON):
            ICON.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(MICO):
            MICO.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(YNAM):
            YNAM.Read(buffer, subSize);
            break;
        case REV32(ZNAM):
            ZNAM.Read(buffer, subSize);
            break;
        case REV32(ETYP):
            ETYP.Read(buffer, subSize);
            break;
        case REV32(DATA):
            DATA.Read(buffer, subSize);
            break;
        case REV32(ENIT):
            ENIT.Read(buffer, subSize);
            break;
        case REV32(EFID):
            Effects.value.push_back(new SKEffect);
            Effects.value.back()->EFID.Read(buffer, subSize);
            break;
        case REV32(EFIT):
            if (Effects.value.size() == 0)
                Effects.value.push_back(new SKEffect);
            Effects.value.back()->EFIT.Read(buffer, subSize);
            break;
        case REV32(CTDA):
            if (Effects.value.size() == 0)
                Effects.value.push_back(new SKEffect);
            Effects.value.back()->CTDA.value.push_back(new SKCondition);
            Effects.value.back()->CTDA.value.back()->CTDA.Read(buffer, subSize);
            break;
        case REV32(CIS1):
            if (Effects.value.size() == 0)
                Effects.value.push_back(new SKEffect);
            if (Effects.value.back()->CTDA.value.size() == 0)
                Effects.value.back()->CTDA.value.push_back(new SKCondition);
            Effects.value.back()->CTDA.value.back()->CIS1.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(CIS2):
            if (Effects.value.size() == 0)
                Effects.value.push_back(new SKEffect);
            if (Effects.value.back()->CTDA.value.size() == 0)
                Effects.value.back()->CTDA.value.push_back(new SKCondition);
            Effects.value.back()->CTDA.value.back()->CIS2.Read(buffer, subSize, CompressedOnDisk);
            break;
        default:
            //printer("Filename = %s\n", FileName);
            printer("  AACT: %08X - Unknown subType = %04x\n", formID, subType);
            CBASH_CHUNK_DEBUG
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t ALCHRecord::Unload()
{
    IsLoaded(false);
    IsChanged(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    KWDA.Unload();
    DESC.Unload();
    MODL.Unload();
    Destructable.Unload();
    ICON.Unload();
    MICO.Unload();
    YNAM.Unload();
    ZNAM.Unload();
    ETYP.Unload();
    DATA.Unload();
    ENIT.Unload();
    Effects.Unload();
    return 1;
}

int32_t ALCHRecord::WriteRecord(FileWriter &writer)
{
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    WRITE(KWDA);
    WRITE(DESC);
    WRITE(MODL);
    Destructable.Write(writer);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(YNAM);
    WRITE(ZNAM);
    WRITE(ETYP);
    WRITE(ENIT);
    Effects.Write(writer);
    return -1;
}

bool ALCHRecord::operator == (const ALCHRecord &other) const
{
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            FULL.equals(other.FULL) &&
            KWDA == other.KWDA &&
            DESC.equals(other.DESC) &&
            MODL == other.MODL &&
            Destructable == other.Destructable &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            YNAM == other.YNAM &&
            ZNAM == other.ZNAM &&
            ETYP == other.ETYP &&
            DATA == other.DATA &&
            ENIT == other.ENIT &&
            Effects == other.Effects
            );
}

bool ALCHRecord::operator != (const ALCHRecord &other) const
{
    return !(*this == other);
}

bool ALCHRecord::equals(Record *other)
{
    try
    {
        return *this == *dynamic_cast<const ALCHRecord *>(other);
    }
    catch(...)
    {
        return false;
    }
}

} // namespace Sk
