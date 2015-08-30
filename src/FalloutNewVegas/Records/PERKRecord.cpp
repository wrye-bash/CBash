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
#include "PERKRecord.h"

namespace FNV
{
PERKRecord::PERKDATA::PERKDATA():
    trait(eNotTrait), minLevel(0), ranks(0), playable(eNotPlayable), hidden(eNotHidden)
    {
    //
    }

PERKRecord::PERKDATA::~PERKDATA()
    {
    //
    }

bool PERKRecord::PERKDATA::operator ==(const PERKDATA &other) const
    {
    return (trait == other.trait &&
            minLevel == other.minLevel &&
            ranks == other.ranks &&
            playable == other.playable &&
            hidden == other.hidden
            );
    }

bool PERKRecord::PERKDATA::operator !=(const PERKDATA &other) const
    {
    return !(*this == other);
    }

PERKRecord::PERKPRKE::PERKPRKE():
    perkType(eQuestStage),
    rank(0),
    priority(0)
    {
    //
    }

PERKRecord::PERKPRKE::~PERKPRKE()
    {
    //
    }

bool PERKRecord::PERKPRKE::operator ==(const PERKPRKE &other) const
    {
    return (perkType == other.perkType &&
            rank == other.rank &&
            priority == other.priority
            );
    }

bool PERKRecord::PERKPRKE::operator !=(const PERKPRKE &other) const
    {
    return !(*this == other);
    }

bool PERKRecord::PERKCondition::operator ==(const PERKCondition &other) const
    {
    return (PRKC == other.PRKC &&
            CTDA == other.CTDA
            );
    }

bool PERKRecord::PERKCondition::operator !=(const PERKCondition &other) const
    {
    return !(*this == other);
    }

bool PERKRecord::PERKEffect::operator ==(const PERKEffect &other) const
    {
    return (PRKE == other.PRKE &&
            DATAfid == other.DATAfid &&
            DATAS8 == other.DATAS8 &&
            DATAU81 == other.DATAU81 &&
            DATAU82 == other.DATAU82 &&
            DATAU83 == other.DATAU83 &&
            CTDA == other.CTDA &&
            EPFT == other.EPFT &&
            EPFDf1 == other.EPFDf1 &&
            EPFDf2 == other.EPFDf2 &&
            EPFDav1 == other.EPFDav1 &&
            EPFDfid1 == other.EPFDfid1 &&
            EPF2.equals(other.EPF2) &&
            EPF3 == other.EPF3 &&
            SCHR == other.SCHR &&
            SCDA == other.SCDA &&
            SCTX.equals(other.SCTX) &&
            VARS == other.VARS &&
            SCR_ == other.SCR_
            );
    }

bool PERKRecord::PERKEffect::operator !=(const PERKEffect &other) const
    {
    return !(*this == other);
    }

bool PERKRecord::PERKEffect::IsRunImmediately()
    {
    if (!EPF3.IsLoaded()) return false;
    return (EPF3.value & fIsRunImmediately) != 0;
    }

void PERKRecord::PERKEffect::IsRunImmediately(bool value)
    {
    if (!EPF3.IsLoaded()) return;
    SETBIT(EPF3.value, fIsRunImmediately, value);
    }

bool PERKRecord::PERKEffect::IsFlagMask(uint16_t Mask, bool Exact)
    {
    if (!EPF3.IsLoaded()) return false;
    return Exact ? ((EPF3.value & Mask) == Mask) : ((EPF3.value & Mask) != 0);
    }

void PERKRecord::PERKEffect::SetFlagMask(uint16_t Mask)
    {
    EPF3.Load();
    EPF3.value = Mask;
    }

bool PERKRecord::PERKEffect::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void PERKRecord::PERKEffect::IsScriptEnabled(bool value)
    {
    SETBIT(SCHR.value.flags, fIsEnabled, value);
    }

bool PERKRecord::PERKEffect::IsScriptFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void PERKRecord::PERKEffect::SetScriptFlagMask(uint16_t Mask)
    {
    SCHR.value.flags = Mask;
    }

PERKRecord::PERKRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PERKRecord::PERKRecord(PERKRecord *srcRecord):
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
    FULL = srcRecord->FULL;
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    CTDA = srcRecord->CTDA;
    DATA = srcRecord->DATA;
    PRKE = srcRecord->PRKE;
    //PRKC = srcRecord->PRKC;
    CTDA = srcRecord->CTDA;
    //if(srcRecord->EPFT.IsLoaded())
    //    {
    //    EPFT.Load();
    //    EPFT->EPFT = srcRecord->EPFT->EPFT;
    //    EPFT->DATA = srcRecord->EPFT->DATA;
    //    }
    //EPF2 = srcRecord->EPF2;
    //EPF3 = srcRecord->EPF3;
    //if(srcRecord->SCHR.IsLoaded())
    //    {
    //    SCHR.Load();
    //    SCHR->SCHR = srcRecord->SCHR->SCHR;
    //    SCHR->SCDA = srcRecord->SCHR->SCDA;
    //    SCHR->SCTX = srcRecord->SCHR->SCTX;
    //    SCHR->SLSD = srcRecord->SCHR->SLSD;
    //    SCHR->SCVR = srcRecord->SCHR->SCVR;
    //    SCHR->SCRO = srcRecord->SCHR->SCRO;
    //    SCHR->SCRV = srcRecord->SCHR->SCRV;
    //    }
    //PRKF = srcRecord->PRKF;
    return;
    }

PERKRecord::~PERKRecord()
    {
    //
    }

bool PERKRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(PRKE.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(PRKE->value);
    //if(CTDA.IsLoaded()) //FILL IN MANUALLY
    //    op.Accept(CTDA->value);
    //if(EPFT.IsLoaded() && EPFT->DATA.IsLoaded())
    //    op.Accept(EPFT->DATA->value);
    //if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
    //    op.Accept(SCHR->SCRO->value);

    return op.Stop();
    }

bool PERKRecord::IsNotTrait()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->trait == eNotTrait);
    }

bool PERKRecord::IsTrait()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->trait == eTrait);
    }

bool PERKRecord::IsTraitType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->trait == Type;
    }

void PERKRecord::SetTraitType(uint8_t Type)
    {
    DATA.Load();
    DATA->trait = Type;
    }

bool PERKRecord::IsNotPlayable()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->playable == eNotPlayable);
    }

bool PERKRecord::IsPlayable()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->playable == ePlayable);
    }

bool PERKRecord::IsPlayableType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->playable == Type;
    }

void PERKRecord::SetPlayableType(uint8_t Type)
    {
    DATA.Load();
    DATA->playable = Type;
    }

bool PERKRecord::IsNotHidden()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->hidden == eNotHidden);
    }

bool PERKRecord::IsHidden()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->hidden == eHidden);
    }

bool PERKRecord::IsHiddenType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->hidden == Type;
    }

void PERKRecord::SetHiddenType(uint8_t Type)
    {
    DATA.Load();
    DATA->hidden = Type;
    }

/*
bool PERKRecord::IsQuestStage()
    {
    if(!PRKE.IsLoaded()) return false;
    return (PRKE->perkType == eQuestStage);
    }

bool PERKRecord::IsAbility()
    {
    if (!PRKE.IsLoaded()) return false;
    return (PRKE->perkType == eAbility);
    }

bool PERKRecord::IsEntryPoint()
    {
    if (!PRKE.IsLoaded()) return false;
    return (PRKE->perkType == eEntryPoint);
    }

bool PERKRecord::IsType(uint8_t Type)
    {
    if (!PRKE.IsLoaded()) return false;
    return PRKE->perkType == Type;
    }

void PERKRecord::SetType(uint8_t Type)
    {
    PRKE.Load();
    PRKE->perkType = Mask;
    }
*/

uint32_t PERKRecord::GetType()
    {
    return REV32(PERK);
    }

char * PERKRecord::GetStrType()
    {
    return "PERK";
    }

int32_t PERKRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(PRKE):
                PRKE.Read(buffer, subSize);
                break;
            case REV32(PRKC):
                //PRKC.Read(buffer, subSize);
                break;
            //case REV32(CTDA):
            //    CTDA.Read(buffer, subSize);
            //    break;
            case REV32(EPFT):
                //EPFT.Load();
                //EPFT->EPFT.Read(buffer, subSize);
                break;
            //case REV32(DATA):
            //    EPFT.Load();
            //    EPFT->DATA.Read(buffer, subSize);
            //    break;
            case REV32(EPF2):
            //    EPF2.Read(buffer, subSize);
                break;
            case REV32(EPF3):
            //    EPF3.Read(buffer, subSize);
                break;
            case REV32(SCHR):
            //    SCHR.Load();
            //    SCHR->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
            //    SCHR.Load();
            //    SCHR->SCDA.Read(buffer, subSize);
                break;
            case REV32(SCTX):
            //    SCHR.Load();
            //    SCHR->SCTX.Read(buffer, subSize);
                break;
            case REV32(SLSD):
            //    SCHR.Load();
            //    SCHR->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
            //    SCHR.Load();
            //    SCHR->SCVR.Read(buffer, subSize);
                break;
            case REV32(SCRO):
            //    SCHR.Load();
            //    SCHR->SCRO.Read(buffer, subSize);
                break;
            case REV32(SCRV):
            //    SCHR.Load();
            //    SCHR->SCRV.Read(buffer, subSize);
                break;
            case REV32(PRKF):
                //PRKF.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t PERKRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    CTDA.Unload();
    DATA.Unload();
    PRKE.Unload();
    //PRKC.Unload();
    CTDA.Unload();
    //EPFT.Unload();
    //EPF2.Unload();
    //EPF3.Unload();
    //SCHR.Unload();
    //PRKF.Unload(); //FILL IN MANUALLY
    return 1;
    }

int32_t PERKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(CTDA);
    WRITE(DATA);
    WRITE(PRKE);
    //WRITE(PRKC);
    WRITE(CTDA);

    /*
    if(EPFT.IsLoaded())
        {
        if(EPFT->EPFT.IsLoaded())
            SaveHandler.writeSubRecord(REV32(EPFT), EPFT->EPFT.value, EPFT->EPFT.GetSize());

        if(EPFT->DATA.IsLoaded())
            SaveHandler.writeSubRecord(REV32(DATA), EPFT->DATA.value, EPFT->DATA.GetSize());

        }

    WRITE(EPF2);
    WRITE(EPF3);

    if(SCHR.IsLoaded())
        {
        if(SCHR->SCHR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCHR), SCHR->SCHR.value, SCHR->SCHR.GetSize());

        if(SCHR->SCDA.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCDA), SCHR->SCDA.value, SCHR->SCDA.GetSize());

        if(SCHR->SCTX.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCTX), SCHR->SCTX.value, SCHR->SCTX.GetSize());

        if(SCHR->SLSD.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SLSD), SCHR->SLSD.value, SCHR->SLSD.GetSize());

        if(SCHR->SCVR.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCVR), SCHR->SCVR.value, SCHR->SCVR.GetSize());

        if(SCHR->SCRO.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRO), SCHR->SCRO.value, SCHR->SCRO.GetSize());

        if(SCHR->SCRV.IsLoaded())
            SaveHandler.writeSubRecord(REV32(SCRV), SCHR->SCRV.value, SCHR->SCRV.GetSize());

        }
    */

    //if(PRKF.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(PRKF), PRKF.value, PRKF.GetSize());

    return -1;
    }

bool PERKRecord::operator ==(const PERKRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            CTDA == other.CTDA &&
            DATA == other.DATA &&
            PRKE == other.PRKE &&
            //PRKC == other.PRKC &&
            CTDA == other.CTDA
            //EPFT == other.EPFT &&
            //EPF2.equalsi(other.EPF2) &&
            //EPF3 == other.EPF3 &&
            //SCHR == other.SCHR &&
            //Empty
            );
    }

bool PERKRecord::operator !=(const PERKRecord &other) const
    {
    return !(*this == other);
    }

bool PERKRecord::equals(Record *other)
    {
    return *this == *(PERKRecord *)other;
    }
}