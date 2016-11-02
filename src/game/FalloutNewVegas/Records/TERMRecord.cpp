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
#include "TERMRecord.h"

namespace FNV
{
TERMRecord::TERMDNAM::TERMDNAM():
    difficultyType(eVeryEasy),
    flags(0),
    serverType(0),
    unused1(0)
    {
    //
    }

TERMRecord::TERMDNAM::~TERMDNAM()
    {
    //
    }

bool TERMRecord::TERMDNAM::operator ==(const TERMDNAM &other) const
    {
    return (difficultyType == other.difficultyType &&
            flags == other.flags &&
            serverType == other.serverType);
    }

bool TERMRecord::TERMDNAM::operator !=(const TERMDNAM &other) const
    {
    return !(*this == other);
    }

void TERMRecord::TERMMenu::Write(FileWriter &writer)
    {
    WRITE(ITXT);
    WRITE(RNAM);
    WRITE(ANAM);
    WRITE(INAM);
    WRITE(TNAM);
    SCHR.value.numRefs = (uint32_t)SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    //for(uint32_t x = 0; x < VARS.value.size(); ++x) //Just to ensure that the value is correct
    //    SCHR.value.lastIndex = (SCHR.value.lastIndex > VARS.value[x]->SLSD.value.index) ? SCHR.value.lastIndex : VARS.value[x]->SLSD.value.index;
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    VARS.Write(writer);
    SCR_.Write(writer, true);
    CTDA.Write(writer, true);
    }

bool TERMRecord::TERMMenu::IsAddNote()
    {
    return (ANAM.value & fIsAddNote) != 0;
    }

void TERMRecord::TERMMenu::IsAddNote(bool value)
    {
    SETBIT(ANAM.value, fIsAddNote, value);
    }

bool TERMRecord::TERMMenu::IsForceRedraw()
    {
    return (ANAM.value & fIsForceRedraw) != 0;
    }

void TERMRecord::TERMMenu::IsForceRedraw(bool value)
    {
    SETBIT(ANAM.value, fIsForceRedraw, value);
    }

bool TERMRecord::TERMMenu::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((ANAM.value & Mask) == Mask) : ((ANAM.value & Mask) != 0);
    }

void TERMRecord::TERMMenu::SetFlagMask(uint8_t Mask)
    {
    ANAM.value = Mask;
    }

bool TERMRecord::TERMMenu::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void TERMRecord::TERMMenu::IsScriptEnabled(bool value)
    {
    SETBIT(SCHR.value.flags, fIsEnabled, value);
    }

bool TERMRecord::TERMMenu::IsScriptFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void TERMRecord::TERMMenu::SetScriptFlagMask(uint16_t Mask)
    {
    SCHR.value.flags = Mask;
    }

bool TERMRecord::TERMMenu::IsObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void TERMRecord::TERMMenu::IsObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool TERMRecord::TERMMenu::IsQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void TERMRecord::TERMMenu::IsQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool TERMRecord::TERMMenu::IsEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void TERMRecord::TERMMenu::IsEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool TERMRecord::TERMMenu::IsType(uint16_t Type)
    {
    return SCHR.value.scriptType == Type;
    }

void TERMRecord::TERMMenu::SetType(uint16_t Type)
    {
    SCHR.value.scriptType = Type;
    }

bool TERMRecord::TERMMenu::operator ==(const TERMMenu &other) const
    {
    return (ANAM == other.ANAM &&
            INAM == other.INAM &&
            TNAM == other.TNAM &&
            SCHR == other.SCHR &&
            SCDA == other.SCDA &&
            ITXT.equals(other.ITXT) &&
            RNAM.equals(other.RNAM) &&
            SCTX.equalsi(other.SCTX) &&
            VARS == other.VARS &&
            SCR_ == other.SCR_ &&
            CTDA == other.CTDA);
    }

bool TERMRecord::TERMMenu::operator !=(const TERMMenu &other) const
    {
    return !(*this == other);
    }

TERMRecord::TERMRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

TERMRecord::TERMRecord(TERMRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    SNAM = srcRecord->SNAM;
    PNAM = srcRecord->PNAM;
    DNAM = srcRecord->DNAM;
    Menus = srcRecord->Menus;
    return;
    }

TERMRecord::~TERMRecord()
    {
    //
    }

bool TERMRecord::VisitFormIDs(FormIDOp &op)
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
    if(Destructable.IsLoaded())
        {
        for(uint32_t x = 0; x < Destructable->Stages.value.size(); ++x)
            {
            op.Accept(Destructable->Stages.value[x]->DSTD.value.explosion);
            op.Accept(Destructable->Stages.value[x]->DSTD.value.debris);
            }
        }
    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(PNAM.IsLoaded())
        op.Accept(PNAM.value);

    for(uint32_t x = 0; x < Menus.value.size(); ++x)
        {
        if(Menus.value[x]->INAM.IsLoaded())
            op.Accept(Menus.value[x]->INAM.value);
        if(Menus.value[x]->INAM.IsLoaded())
            op.Accept(Menus.value[x]->TNAM.value);
        for(uint32_t p = 0; p < Menus.value[x]->SCR_.value.size(); p++)
            if(Menus.value[x]->SCR_.value[p]->isSCRO)
                op.Accept(Menus.value[x]->SCR_.value[p]->reference);
        for(uint32_t p = 0; p < Menus.value[x]->CTDA.value.size(); p++)
            Menus.value[x]->CTDA.value[p]->VisitFormIDs(op);
        }

    return op.Stop();
    }

bool TERMRecord::IsLeveled()
    {
    return (DNAM.value.flags & fIsLeveled) != 0;
    }

void TERMRecord::IsLeveled(bool value)
    {
    SETBIT(DNAM.value.flags, fIsLeveled, value);
    }

bool TERMRecord::IsUnlocked()
    {
    return (DNAM.value.flags & fIsUnlocked) != 0;
    }

void TERMRecord::IsUnlocked(bool value)
    {
    SETBIT(DNAM.value.flags, fIsUnlocked, value);
    }

bool TERMRecord::IsAlternateColors()
    {
    return (DNAM.value.flags & fIsAlternateColors) != 0;
    }

void TERMRecord::IsAlternateColors(bool value)
    {
    SETBIT(DNAM.value.flags, fIsAlternateColors, value);
    }

bool TERMRecord::IsHideWelcomeTextWhenDisplayingImage()
    {
    return (DNAM.value.flags & fIsHideWelcomeTextWhenDisplayingImage) != 0;
    }

void TERMRecord::IsHideWelcomeTextWhenDisplayingImage(bool value)
    {
    SETBIT(DNAM.value.flags, fIsHideWelcomeTextWhenDisplayingImage, value);
    }

bool TERMRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DNAM.value.flags & Mask) == Mask) : ((DNAM.value.flags & Mask) != 0);
    }

void TERMRecord::SetFlagMask(uint8_t Mask)
    {
    DNAM.value.flags = Mask;
    }

bool TERMRecord::IsVeryEasy()
    {
    return (DNAM.value.difficultyType == eVeryEasy);
    }

void TERMRecord::IsVeryEasy(bool value)
    {
    DNAM.value.difficultyType = value ? eVeryEasy : eEasy;
    }

bool TERMRecord::IsEasy()
    {
    return (DNAM.value.difficultyType == eEasy);
    }

void TERMRecord::IsEasy(bool value)
    {
    DNAM.value.difficultyType = value ? eEasy : eVeryEasy;
    }

bool TERMRecord::IsAverage()
    {
    return (DNAM.value.difficultyType == eAverage);
    }

void TERMRecord::IsAverage(bool value)
    {
    DNAM.value.difficultyType = value ? eAverage : eVeryEasy;
    }

bool TERMRecord::IsHard()
    {
    return (DNAM.value.difficultyType == eHard);
    }

void TERMRecord::IsHard(bool value)
    {
    DNAM.value.difficultyType = value ? eHard : eVeryEasy;
    }

bool TERMRecord::IsVeryHard()
    {
    return (DNAM.value.difficultyType == eVeryHard);
    }

void TERMRecord::IsVeryHard(bool value)
    {
    DNAM.value.difficultyType = value ? eVeryHard : eVeryEasy;
    }

bool TERMRecord::IsRequiresKey()
    {
    return (DNAM.value.difficultyType == eRequiresKey);
    }

void TERMRecord::IsRequiresKey(bool value)
    {
    DNAM.value.difficultyType = value ? eRequiresKey : eVeryEasy;
    }

bool TERMRecord::IsLockType(uint8_t Type)
    {
    return DNAM.value.difficultyType == Type;
    }

void TERMRecord::SetLockType(uint8_t Type)
    {
    DNAM.value.difficultyType = Type;
    }

bool TERMRecord::IsServer1()
    {
    return (DNAM.value.serverType == eServer1);
    }

void TERMRecord::IsServer1(bool value)
    {
    DNAM.value.serverType = value ? eServer1 : eServer2;
    }

bool TERMRecord::IsServer2()
    {
    return (DNAM.value.serverType == eServer2);
    }

void TERMRecord::IsServer2(bool value)
    {
    DNAM.value.serverType = value ? eServer2 : eServer1;
    }

bool TERMRecord::IsServer3()
    {
    return (DNAM.value.serverType == eServer3);
    }

void TERMRecord::IsServer3(bool value)
    {
    DNAM.value.serverType = value ? eServer3 : eServer1;
    }

bool TERMRecord::IsServer4()
    {
    return (DNAM.value.serverType == eServer4);
    }

void TERMRecord::IsServer4(bool value)
    {
    DNAM.value.serverType = value ? eServer4 : eServer1;
    }

bool TERMRecord::IsServer5()
    {
    return (DNAM.value.serverType == eServer5);
    }

void TERMRecord::IsServer5(bool value)
    {
    DNAM.value.serverType = value ? eServer5 : eServer1;
    }

bool TERMRecord::IsServer6()
    {
    return (DNAM.value.serverType == eServer6);
    }

void TERMRecord::IsServer6(bool value)
    {
    DNAM.value.serverType = value ? eServer6 : eServer1;
    }

bool TERMRecord::IsServer7()
    {
    return (DNAM.value.serverType == eServer7);
    }

void TERMRecord::IsServer7(bool value)
    {
    DNAM.value.serverType = value ? eServer7 : eServer1;
    }

bool TERMRecord::IsServer8()
    {
    return (DNAM.value.serverType == eServer8);
    }

void TERMRecord::IsServer8(bool value)
    {
    DNAM.value.serverType = value ? eServer8 : eServer1;
    }

bool TERMRecord::IsServer9()
    {
    return (DNAM.value.serverType == eServer9);
    }

void TERMRecord::IsServer9(bool value)
    {
    DNAM.value.serverType = value ? eServer9 : eServer1;
    }

bool TERMRecord::IsServer10()
    {
    return (DNAM.value.serverType == eServer10);
    }

void TERMRecord::IsServer10(bool value)
    {
    DNAM.value.serverType = value ? eServer10 : eServer1;
    }

bool TERMRecord::IsServerType(uint8_t Type)
    {
    return DNAM.value.serverType == Type;
    }

void TERMRecord::SetServerType(uint8_t Type)
    {
    DNAM.value.serverType = Type;
    }

uint32_t TERMRecord::GetType()
    {
    return REV32(TERM);
    }

char * TERMRecord::GetStrType()
    {
    return "TERM";
    }

int32_t TERMRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(ITXT):
                Menus.value.push_back(new TERMMenu);
                Menus.value.back()->ITXT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(RNAM):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->RNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ANAM):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->ANAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->INAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->TNAM.Read(buffer, subSize);
                break;
            case REV32(SCHR):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->VARS.value.push_back(new GENVARS);
                Menus.value.back()->VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                if(Menus.value.back()->VARS.value.size() == 0)
                    Menus.value.back()->VARS.value.push_back(new GENVARS);
                Menus.value.back()->VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRO):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->SCR_.Read(buffer, subSize);
                Menus.value.back()->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(SCRV):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->SCR_.Read(buffer, subSize);
                Menus.value.back()->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(CTDA):
                if(Menus.value.size() == 0)
                    Menus.value.push_back(new TERMMenu);
                Menus.value.back()->CTDA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  TERM: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t TERMRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    OBND.Unload();
    FULL.Unload();
    MODL.Unload();
    SCRI.Unload();
    Destructable.Unload();
    DESC.Unload();
    SNAM.Unload();
    PNAM.Unload();
    DNAM.Unload();
    Menus.Unload();
    return 1;
    }

int32_t TERMRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(OBND);
    WRITE(FULL);
    MODL.Write(writer);
    WRITE(SCRI);
    Destructable.Write(writer);
    WRITE(DESC);
    WRITE(SNAM);
    WRITE(PNAM);
    WRITE(DNAM);
    Menus.Write(writer);
    return -1;
    }

bool TERMRecord::operator ==(const TERMRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            OBND == other.OBND &&
            SCRI == other.SCRI &&
            SNAM == other.SNAM &&
            PNAM == other.PNAM &&
            DNAM == other.DNAM &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            MODL == other.MODL &&
            Menus == other.Menus &&
            Destructable == other.Destructable);
    }

bool TERMRecord::operator !=(const TERMRecord &other) const
    {
    return !(*this == other);
    }

bool TERMRecord::equals(Record *other)
    {
    return *this == *(TERMRecord *)other;
    }
}