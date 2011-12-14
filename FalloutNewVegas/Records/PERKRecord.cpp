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
bool PERKRecord::PERKEffect::IsRunImmediately()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsRunImmediately) != 0;
    }

void PERKRecord::PERKEffect::IsRunImmediately(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsRunImmediately) : (Dummy->flags & ~fIsRunImmediately);
    }

bool PERKRecord::PERKEffect::IsFlagMask(UINT16 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void PERKRecord::PERKEffect::SetFlagMask(UINT16 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PERKRecord::PERKEffect::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void PERKRecord::PERKEffect::IsScriptEnabled(bool value)
    {
    SCHR.value.flags = value ? (SCHR.value.flags | fIsEnabled) : (SCHR.value.flags & ~fIsEnabled);
    }

bool PERKRecord::PERKEffect::IsScriptFlagMask(UINT16 Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void PERKRecord::PERKEffect::SetScriptFlagMask(UINT16 Mask)
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
    PRKC = srcRecord->PRKC;
    CTDA = srcRecord->CTDA;
    if(srcRecord->EPFT.IsLoaded())
        {
        EPFT.Load();
        EPFT->EPFT = srcRecord->EPFT->EPFT;
        EPFT->DATA = srcRecord->EPFT->DATA;
        }
    EPF2 = srcRecord->EPF2;
    EPF3 = srcRecord->EPF3;
    if(srcRecord->SCHR.IsLoaded())
        {
        SCHR.Load();
        SCHR->SCHR = srcRecord->SCHR->SCHR;
        SCHR->SCDA = srcRecord->SCHR->SCDA;
        SCHR->SCTX = srcRecord->SCHR->SCTX;
        SCHR->SLSD = srcRecord->SCHR->SLSD;
        SCHR->SCVR = srcRecord->SCHR->SCVR;
        SCHR->SCRO = srcRecord->SCHR->SCRO;
        SCHR->SCRV = srcRecord->SCHR->SCRV;
        }
    PRKF = srcRecord->PRKF;
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
    if(EPFT.IsLoaded() && EPFT->DATA.IsLoaded())
        op.Accept(EPFT->DATA->value);
    if(SCHR.IsLoaded() && SCHR->SCRO.IsLoaded())
        op.Accept(SCHR->SCRO->value);

    return op.Stop();
    }

bool PERKRecord::IsNotTrait()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNotTrait);
    }

void PERKRecord::IsNotTrait(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNotTrait : eDummyDefault;
    }

bool PERKRecord::IsTrait()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eTrait);
    }

void PERKRecord::IsTrait(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eTrait : eDummyDefault;
    }

bool PERKRecord::IsTraitType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void PERKRecord::SetTraitType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PERKRecord::IsNotPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNotPlayable);
    }

void PERKRecord::IsNotPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNotPlayable : eDummyDefault;
    }

bool PERKRecord::IsPlayable()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == ePlayable);
    }

void PERKRecord::IsPlayable(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? ePlayable : eDummyDefault;
    }

bool PERKRecord::IsPlayableType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void PERKRecord::SetPlayableType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PERKRecord::IsNotHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNotHidden);
    }

void PERKRecord::IsNotHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNotHidden : eDummyDefault;
    }

bool PERKRecord::IsHidden()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eHidden);
    }

void PERKRecord::IsHidden(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eHidden : eDummyDefault;
    }

bool PERKRecord::IsHiddenType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void PERKRecord::SetHiddenType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool PERKRecord::IsQuestStage()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eQuestStage);
    }

void PERKRecord::IsQuestStage(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eQuestStage : eDummyDefault;
    }

bool PERKRecord::IsAbility()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eAbility);
    }

void PERKRecord::IsAbility(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eAbility : eDummyDefault;
    }

bool PERKRecord::IsEntryPoint()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eEntryPoint);
    }

void PERKRecord::IsEntryPoint(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eEntryPoint : eDummyDefault;
    }

bool PERKRecord::IsType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void PERKRecord::SetType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 PERKRecord::GetType()
    {
    return REV32(PERK);
    }

STRING PERKRecord::GetStrType()
    {
    return "PERK";
    }

SINT32 PERKRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
                PRKC.Read(buffer, subSize);
                break;
            case REV32(CTDA):
                CTDA.Read(buffer, subSize);
                break;
            case REV32(EPFT):
                EPFT.Load();
                EPFT->EPFT.Read(buffer, subSize);
                break;
            case REV32(DATA):
                EPFT.Load();
                EPFT->DATA.Read(buffer, subSize);
                break;
            case REV32(EPF2):
                EPF2.Read(buffer, subSize);
                break;
            case REV32(EPF3):
                EPF3.Read(buffer, subSize);
                break;
            case REV32(SCHR):
                SCHR.Load();
                SCHR->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                SCHR.Load();
                SCHR->SCDA.Read(buffer, subSize);
                break;
            case REV32(SCTX):
                SCHR.Load();
                SCHR->SCTX.Read(buffer, subSize);
                break;
            case REV32(SLSD):
                SCHR.Load();
                SCHR->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                SCHR.Load();
                SCHR->SCVR.Read(buffer, subSize);
                break;
            case REV32(SCRO):
                SCHR.Load();
                SCHR->SCRO.Read(buffer, subSize);
                break;
            case REV32(SCRV):
                SCHR.Load();
                SCHR->SCRV.Read(buffer, subSize);
                break;
            case REV32(PRKF):
                //PRKF.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  PERK: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 PERKRecord::Unload()
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
    PRKC.Unload();
    CTDA.Unload();
    EPFT.Unload();
    EPF2.Unload();
    EPF3.Unload();
    SCHR.Unload();
    //PRKF.Unload(); //FILL IN MANUALLY
    return 1;
    }

SINT32 PERKRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(CTDA);
    WRITE(DATA);
    WRITE(PRKE);
    WRITE(PRKC);
    WRITE(CTDA);

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
            PRKC == other.PRKC &&
            CTDA == other.CTDA &&
            EPFT == other.EPFT &&
            EPF2.equalsi(other.EPF2) &&
            EPF3 == other.EPF3 &&
            SCHR == other.SCHR &&
            //Empty);
    }

bool PERKRecord::operator !=(const PERKRecord &other) const
    {
    return !(*this == other);
    }

bool PERKRecord::equals(const Record *other) const
    {
    return *this == *(PERKRecord *)other;
    }
}