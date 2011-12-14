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
#include "NPC_Record.h"

namespace Ob
{
NPC_Record::NPC_DATA::NPC_DATA():
    armorer(5),
    athletics(5),
    blade(5),
    block(5),
    blunt(5),
    h2h(5),
    heavyArmor(5),
    alchemy(5),
    alteration(5),
    conjuration(5),
    destruction(5),
    illusion(5),
    mysticism(5),
    restoration(5),
    acrobatics(5),
    lightArmor(5),
    marksman(5),
    mercantile(5),
    security(5),
    sneak(5),
    speechcraft(5),
    health(50),
    strength(50),
    intelligence(50),
    willpower(50),
    agility(50),
    speed(50),
    endurance(50),
    personality(50),
    luck(50)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

NPC_Record::NPC_DATA::~NPC_DATA()
    {
    //
    }

bool NPC_Record::NPC_DATA::operator ==(const NPC_DATA &other) const
    {
    return (armorer == other.armorer &&
            athletics == other.athletics &&
            blade == other.blade &&
            block == other.block &&
            blunt == other.blunt &&
            h2h == other.h2h &&
            heavyArmor == other.heavyArmor &&
            alchemy == other.alchemy &&
            alteration == other.alteration &&
            conjuration == other.conjuration &&
            destruction == other.destruction &&
            illusion == other.illusion &&
            mysticism == other.mysticism &&
            restoration == other.restoration &&
            acrobatics == other.acrobatics &&
            lightArmor == other.lightArmor &&
            marksman == other.marksman &&
            mercantile == other.mercantile &&
            security == other.security &&
            sneak == other.sneak &&
            speechcraft == other.speechcraft &&
            health == other.health &&
            strength == other.strength &&
            intelligence == other.intelligence &&
            willpower == other.willpower &&
            agility == other.agility &&
            speed == other.speed &&
            endurance == other.endurance &&
            personality == other.personality &&
            luck == other.luck);
    }

bool NPC_Record::NPC_DATA::operator !=(const NPC_DATA &other) const
    {
    return !(*this == other);
    }

NPC_Record::NPC_Record(unsigned char *_recData):
    Record(_recData)
    {
    //NPC_ records are normally compressed
    if(_recData == NULL)
        IsCompressed(true);
    HCLR.value.red = 75;
    HCLR.value.green = 50;
    HCLR.value.blue = 25;
    }

NPC_Record::NPC_Record(NPC_Record *srcRecord):
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
    ACBS = srcRecord->ACBS;
    SNAM = srcRecord->SNAM;
    INAM = srcRecord->INAM;
    RNAM = srcRecord->RNAM;
    SPLO = srcRecord->SPLO;
    SCRI = srcRecord->SCRI;
    CNTO = srcRecord->CNTO;
    AIDT = srcRecord->AIDT;
    PKID = srcRecord->PKID;
    KFFZ = srcRecord->KFFZ;
    CNAM = srcRecord->CNAM;
    DATA = srcRecord->DATA;
    HNAM = srcRecord->HNAM;
    LNAM = srcRecord->LNAM;
    ENAM = srcRecord->ENAM;
    HCLR = srcRecord->HCLR;
    ZNAM = srcRecord->ZNAM;
    FGGS = srcRecord->FGGS;
    FGGA = srcRecord->FGGA;
    FGTS = srcRecord->FGTS;
    FNAM = srcRecord->FNAM;
    }

NPC_Record::~NPC_Record()
    {
    //
    }

bool NPC_Record::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(UINT32 ListIndex = 0; ListIndex < SNAM.value.size(); ListIndex++)
        op.Accept(SNAM.value[ListIndex]->faction);

    if(INAM.IsLoaded())
        op.Accept(INAM.value);

    if(RNAM.IsLoaded())
        op.Accept(RNAM.value);

    for(UINT32 ListIndex = 0; ListIndex < SPLO.value.size(); ListIndex++)
        op.Accept(SPLO.value[ListIndex]);

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);

    for(UINT32 ListIndex = 0; ListIndex < CNTO.value.size(); ListIndex++)
        op.Accept(CNTO.value[ListIndex]->item);

    for(UINT32 ListIndex = 0; ListIndex < PKID.value.size(); ListIndex++)
        op.Accept(PKID.value[ListIndex]);

    if(CNAM.IsLoaded())
        op.Accept(CNAM.value);

    if(HNAM.IsLoaded())
        op.Accept(HNAM.value);

    if(ENAM.IsLoaded())
        op.Accept(ENAM.value);

    if(ZNAM.IsLoaded())
        op.Accept(ZNAM.value);

    return op.Stop();
    }

bool NPC_Record::IsFemale()
    {
    return (ACBS.value.flags & fIsFemale) != 0;
    }

void NPC_Record::IsFemale(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsFemale) : (ACBS.value.flags & ~fIsFemale);
    }

bool NPC_Record::IsMale()
    {
    return !IsFemale();
    }

void NPC_Record::IsMale(bool value)
    {
    IsFemale(!value);
    }

bool NPC_Record::IsEssential()
    {
    return (ACBS.value.flags & fIsEssential) != 0;
    }

void NPC_Record::IsEssential(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsEssential) : (ACBS.value.flags & ~fIsEssential);
    }

bool NPC_Record::IsRespawn()
    {
    return (ACBS.value.flags & fIsRespawn) != 0;
    }

void NPC_Record::IsRespawn(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsRespawn) : (ACBS.value.flags & ~fIsRespawn);
    }

bool NPC_Record::IsAutoCalc()
    {
    return (ACBS.value.flags & fIsAutoCalc) != 0;
    }

void NPC_Record::IsAutoCalc(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsAutoCalc) : (ACBS.value.flags & ~fIsAutoCalc);
    }

bool NPC_Record::IsPCLevelOffset()
    {
    return (ACBS.value.flags & fIsPCLevelOffset) != 0;
    }

void NPC_Record::IsPCLevelOffset(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsPCLevelOffset) : (ACBS.value.flags & ~fIsPCLevelOffset);
    }

bool NPC_Record::IsNoLowLevel()
    {
    return (ACBS.value.flags & fIsNoLowLevel) != 0;
    }

void NPC_Record::IsNoLowLevel(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoLowLevel) : (ACBS.value.flags & ~fIsNoLowLevel);
    }

bool NPC_Record::IsLowLevel()
    {
    return !IsNoLowLevel();
    }

void NPC_Record::IsLowLevel(bool value)
    {
    IsNoLowLevel(!value);
    }

bool NPC_Record::IsNoRumors()
    {
    return (ACBS.value.flags & fIsNoRumors) != 0;
    }

void NPC_Record::IsNoRumors(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoRumors) : (ACBS.value.flags & ~fIsNoRumors);
    }

bool NPC_Record::IsRumors()
    {
    return !IsNoRumors();
    }

void NPC_Record::IsRumors(bool value)
    {
    IsNoRumors(!value);
    }

bool NPC_Record::IsSummonable()
    {
    return (ACBS.value.flags & fIsSummonable) != 0;
    }

void NPC_Record::IsSummonable(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsSummonable) : (ACBS.value.flags & ~fIsSummonable);
    }

bool NPC_Record::IsNoPersuasion()
    {
    return (ACBS.value.flags & fIsNoPersuasion) != 0;
    }

void NPC_Record::IsNoPersuasion(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsNoPersuasion) : (ACBS.value.flags & ~fIsNoPersuasion);
    }

bool NPC_Record::IsPersuasion()
    {
    return !IsNoPersuasion();
    }

void NPC_Record::IsPersuasion(bool value)
    {
    IsNoPersuasion(!value);
    }

bool NPC_Record::IsCanCorpseCheck()
    {
    return (ACBS.value.flags & fIsCanCorpseCheck) != 0;
    }

void NPC_Record::IsCanCorpseCheck(bool value)
    {
    ACBS.value.flags = value ? (ACBS.value.flags | fIsCanCorpseCheck) : (ACBS.value.flags & ~fIsCanCorpseCheck);
    }

bool NPC_Record::IsFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((ACBS.value.flags & Mask) == Mask) : ((ACBS.value.flags & Mask) != 0);
    }

void NPC_Record::SetFlagMask(UINT32 Mask)
    {
    ACBS.value.flags = Mask;
    }

bool NPC_Record::IsServicesWeapons()
    {
    return (AIDT.value.flags & fWeapons) != 0;
    }

void NPC_Record::IsServicesWeapons(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fWeapons) : (AIDT.value.flags & ~fWeapons);
    }

bool NPC_Record::IsServicesArmor()
    {
    return (AIDT.value.flags & fArmor) != 0;
    }

void NPC_Record::IsServicesArmor(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fArmor) : (AIDT.value.flags & ~fArmor);
    }

bool NPC_Record::IsServicesClothing()
    {
    return (AIDT.value.flags & fClothing) != 0;
    }

void NPC_Record::IsServicesClothing(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fClothing) : (AIDT.value.flags & ~fClothing);
    }

bool NPC_Record::IsServicesBooks()
    {
    return (AIDT.value.flags & fBooks) != 0;
    }

void NPC_Record::IsServicesBooks(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fBooks) : (AIDT.value.flags & ~fBooks);
    }

bool NPC_Record::IsServicesIngredients()
    {
    return (AIDT.value.flags & fIngredients) != 0;
    }

void NPC_Record::IsServicesIngredients(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fIngredients) : (AIDT.value.flags & ~fIngredients);
    }

bool NPC_Record::IsServicesLights()
    {
    return (AIDT.value.flags & fLights) != 0;
    }

void NPC_Record::IsServicesLights(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fLights) : (AIDT.value.flags & ~fLights);
    }

bool NPC_Record::IsServicesApparatus()
    {
    return (AIDT.value.flags & fApparatus) != 0;
    }

void NPC_Record::IsServicesApparatus(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fApparatus) : (AIDT.value.flags & ~fApparatus);
    }

bool NPC_Record::IsServicesMiscItems()
    {
    return (AIDT.value.flags & fMiscItems) != 0;
    }

void NPC_Record::IsServicesMiscItems(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fMiscItems) : (AIDT.value.flags & ~fMiscItems);
    }

bool NPC_Record::IsServicesSpells()
    {
    return (AIDT.value.flags & fSpells) != 0;
    }

void NPC_Record::IsServicesSpells(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fSpells) : (AIDT.value.flags & ~fSpells);
    }

bool NPC_Record::IsServicesMagicItems()
    {
    return (AIDT.value.flags & fMagicItems) != 0;
    }

void NPC_Record::IsServicesMagicItems(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fMagicItems) : (AIDT.value.flags & ~fMagicItems);
    }

bool NPC_Record::IsServicesPotions()
    {
    return (AIDT.value.flags & fPotions) != 0;
    }

void NPC_Record::IsServicesPotions(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fPotions) : (AIDT.value.flags & ~fPotions);
    }

bool NPC_Record::IsServicesTraining()
    {
    return (AIDT.value.flags & fTraining) != 0;
    }

void NPC_Record::IsServicesTraining(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fTraining) : (AIDT.value.flags & ~fTraining);
    }

bool NPC_Record::IsServicesRecharge()
    {
    return (AIDT.value.flags & fRecharge) != 0;
    }

void NPC_Record::IsServicesRecharge(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fRecharge) : (AIDT.value.flags & ~fRecharge);
    }

bool NPC_Record::IsServicesRepair()
    {
    return (AIDT.value.flags & fRepair) != 0;
    }

void NPC_Record::IsServicesRepair(bool value)
    {
    AIDT.value.flags = value ? (AIDT.value.flags | fRepair) : (AIDT.value.flags & ~fRepair);
    }

bool NPC_Record::IsServicesFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? ((AIDT.value.flags & Mask) == Mask) : ((AIDT.value.flags & Mask) != 0);
    }

void NPC_Record::SetServicesFlagMask(UINT32 Mask)
    {
    AIDT.value.flags = Mask;
    }

UINT32 NPC_Record::GetType()
    {
    return REV32(NPC_);
    }

STRING NPC_Record::GetStrType()
    {
    return "NPC_";
    }

SINT32 NPC_Record::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(ACBS):
                ACBS.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(RNAM):
                RNAM.Read(buffer, subSize);
                break;
            case REV32(SPLO):
                SPLO.Read(buffer, subSize);
                break;
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(CNTO):
                CNTO.Read(buffer, subSize);
                break;
            case REV32(AIDT):
                AIDT.Read(buffer, subSize);
                break;
            case REV32(PKID):
                PKID.Read(buffer, subSize);
                break;
            case REV32(KFFZ):
                KFFZ.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(HNAM):
                HNAM.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(ENAM):
                ENAM.Read(buffer, subSize);
                break;
            case REV32(HCLR):
                HCLR.Read(buffer, subSize);
                break;
            case REV32(ZNAM):
                ZNAM.Read(buffer, subSize);
                break;
            case REV32(FGGS):
                FGGS.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FGGA):
                FGGA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FGTS):
                FGTS.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  NPC_: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;

            }
        }
    return 0;
    }

SINT32 NPC_Record::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    MODL.Unload();
    ACBS.Unload();
    SNAM.Unload();
    INAM.Unload();
    RNAM.Unload();
    SPLO.Unload();
    SCRI.Unload();
    CNTO.Unload();
    AIDT.Unload();
    PKID.Unload();
    KFFZ.Unload();
    CNAM.Unload();
    DATA.Unload();
    HNAM.Unload();
    LNAM.Unload();
    ENAM.Unload();
    HCLR.Unload();
    ZNAM.Unload();
    FGGS.Unload();
    FGGA.Unload();
    FGTS.Unload();
    FNAM.Unload();
    return 1;
    }

SINT32 NPC_Record::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(ACBS);
    WRITE(SNAM);
    WRITE(INAM);
    WRITE(RNAM);
    WRITE(SPLO);
    WRITE(SCRI);
    WRITE(CNTO);
    WRITE(AIDT);
    PKID.Write(REV32(PKID), writer, true);
    WRITE(KFFZ);
    WRITE(CNAM);
    WRITE(DATA);
    WRITE(HNAM);
    WRITE(LNAM);
    WRITE(ENAM);
    WRITE(HCLR);
    WRITE(ZNAM);
    WRITE(FGGS);
    WRITE(FGGA);
    WRITE(FGTS);
    WRITE(FNAM);
    return -1;
    }

bool NPC_Record::operator ==(const NPC_Record &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            MODL == other.MODL &&
            ACBS == other.ACBS &&
            INAM == other.INAM &&
            RNAM == other.RNAM &&
            SCRI == other.SCRI &&
            AIDT == other.AIDT &&
            CNAM == other.CNAM &&
            DATA == other.DATA &&
            HNAM == other.HNAM &&
            LNAM == other.LNAM &&
            ENAM == other.ENAM &&
            HCLR == other.HCLR &&
            ZNAM == other.ZNAM &&
            FNAM == other.FNAM &&
            FGGS == other.FGGS &&
            FGGA == other.FGGA &&
            FGTS == other.FGTS &&
            SNAM == other.SNAM &&
            SPLO == other.SPLO &&
            CNTO == other.CNTO &&
            PKID == other.PKID &&
            KFFZ.equalsi(other.KFFZ));
    }

bool NPC_Record::operator !=(const NPC_Record &other) const
    {
    return !(*this == other);
    }

bool NPC_Record::equals(Record *other)
    {
    return *this == *(NPC_Record *)other;
    }
}