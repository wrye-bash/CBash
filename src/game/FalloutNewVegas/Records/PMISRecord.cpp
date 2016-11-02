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
#include "PMISRecord.h"
#include "CELLRecord.h"

namespace FNV
{
PMISRecord::PMISRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

PMISRecord::PMISRecord(PMISRecord *srcRecord):
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
    NAME = srcRecord->NAME;
    XEZN = srcRecord->XEZN;
    XRGD = srcRecord->XRGD;
    XRGB = srcRecord->XRGB;
    Patrol = srcRecord->Patrol;
    Ownership = srcRecord->Ownership;
    XCNT = srcRecord->XCNT;
    XRDS = srcRecord->XRDS;
    XHLP = srcRecord->XHLP;
    XDCR = srcRecord->XDCR;
    XLKR = srcRecord->XLKR;
    XCLP = srcRecord->XCLP;
    ActivateParents = srcRecord->ActivateParents;
    XATO = srcRecord->XATO;
    XESP = srcRecord->XESP;
    XEMI = srcRecord->XEMI;
    XMBR = srcRecord->XMBR;
    XPWR = srcRecord->XPWR;
    XIBS = srcRecord->XIBS;
    XSCL = srcRecord->XSCL;
    DATA = srcRecord->DATA;
    return;
    }

PMISRecord::~PMISRecord()
    {
    //
    }

bool PMISRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    op.Accept(NAME.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(Patrol.IsLoaded())
        {
        op.Accept(Patrol->INAM.value);
        for(uint32_t x = 0; x < Patrol->SCR_.value.size(); x++)
            if(Patrol->SCR_.value[x]->isSCRO)
                op.Accept(Patrol->SCR_.value[x]->reference);
        op.Accept(Patrol->TNAM.value);
        }
    if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);
    for(uint32_t x = 0; x < XDCR.value.size(); x++)
        op.Accept(XDCR.value[x]->reference);
    if(XLKR.IsLoaded())
        op.Accept(XLKR.value);
    if(ActivateParents.IsLoaded())
        for(uint32_t x = 0; x < ActivateParents->XAPR.value.size(); x++)
            op.Accept(ActivateParents->XAPR.value[x]->reference);
    if(XESP.IsLoaded())
        op.Accept(XESP->parent);
    if(XEMI.IsLoaded())
        op.Accept(XEMI.value);
    if(XMBR.IsLoaded())
        op.Accept(XMBR.value);
    for(uint32_t x = 0; x < XPWR.value.size(); x++)
        op.Accept(XPWR.value[x]->reference);

    return op.Stop();
    }

bool PMISRecord::IsOppositeParent()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsOppositeParent) != 0 : false;
    }

void PMISRecord::IsOppositeParent(bool value)
    {
    if(!XESP.IsLoaded()) return;
    SETBIT(XESP->flags, fIsOppositeParent, value);
    }

bool PMISRecord::IsPopIn()
    {
    return XESP.IsLoaded() ? (XESP->flags & fIsPopIn) != 0 : false;
    }

void PMISRecord::IsPopIn(bool value)
    {
    if(!XESP.IsLoaded()) return;
    SETBIT(XESP->flags, fIsPopIn, value);
    }

bool PMISRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if(!XESP.IsLoaded()) return false;
    return Exact ? ((XESP->flags & Mask) == Mask) : ((XESP->flags & Mask) != 0);
    }

void PMISRecord::SetFlagMask(uint8_t Mask)
    {
    XESP.Load();
    XESP->flags = Mask;
    }

uint32_t PMISRecord::GetType()
    {
    return REV32(PMIS);
    }

char * PMISRecord::GetStrType()
    {
    return "PMIS";
    }

int32_t PMISRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(NAME):
                NAME.Read(buffer, subSize);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(XRGD):
                XRGD.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XRGB):
                XRGB.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XPRD):
                Patrol.Load();
                Patrol->XPRD.Read(buffer, subSize);
                break;
            case REV32(XPPA):
                //XPPA, Patrol Script Marker (Empty)
                break;
            case REV32(INAM):
                Patrol.Load();
                Patrol->INAM.Read(buffer, subSize);
                break;
            case REV32(SCHR):
                Patrol.Load();
                Patrol->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                Patrol.Load();
                Patrol->SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                Patrol.Load();
                Patrol->SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                Patrol.Load();
                Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                Patrol.Load();
                if(Patrol->VARS.value.size() == 0)
                    Patrol->VARS.value.push_back(new GENVARS);
                Patrol->VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRO):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(SCRV):
                Patrol.Load();
                Patrol->SCR_.Read(buffer, subSize);
                Patrol->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(TNAM):
                Patrol.Load();
                Patrol->TNAM.Read(buffer, subSize);
                break;
            case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XCNT):
                XCNT.Read(buffer, subSize);
                break;
            case REV32(XRDS):
                XRDS.Read(buffer, subSize);
                break;
            case REV32(XHLP):
                XHLP.Read(buffer, subSize);
                break;
            case REV32(XDCR):
                XDCR.Read(buffer, subSize);
                break;
            case REV32(XLKR):
                XLKR.Read(buffer, subSize);
                break;
            case REV32(XCLP):
                XCLP.Read(buffer, subSize);
                break;
            case REV32(XAPD):
                ActivateParents.Load();
                ActivateParents->XAPD.Read(buffer, subSize);
                break;
            case REV32(XAPR):
                ActivateParents.Load();
                ActivateParents->XAPR.Read(buffer, subSize);
                break;
            case REV32(XATO):
                XATO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XESP):
                XESP.Read(buffer, subSize);
                break;
            case REV32(XEMI):
                XEMI.Read(buffer, subSize);
                break;
            case REV32(XMBR):
                XMBR.Read(buffer, subSize);
                break;
            case REV32(XPWR):
                XPWR.Read(buffer, subSize);
                break;
            case REV32(XIBS):
                //XIBS.Read(buffer, subSize);
                XIBS.value = 1;
                break;
            case REV32(XSCL):
                XSCL.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PMIS: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PMISRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    NAME.Unload();
    XEZN.Unload();
    XRGD.Unload();
    XRGB.Unload();
    Patrol.Unload();
    Ownership.Unload();
    XCNT.Unload();
    XRDS.Unload();
    XHLP.Unload();
    XDCR.Unload();
    XLKR.Unload();
    XCLP.Unload();
    ActivateParents.Unload();
    XATO.Unload();
    XESP.Unload();
    XEMI.Unload();
    XMBR.Unload();
    XPWR.Unload();
    XIBS.Unload();
    XSCL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t PMISRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    WRITE(XEZN);
    WRITE(XRGD);
    WRITE(XRGB);
    Patrol.Write(writer);
    Ownership.Write(writer);
    WRITE(XCNT);
    WRITE(XRDS);
    WRITE(XHLP);
    WRITE(XDCR);
    WRITE(XLKR);
    WRITE(XCLP);
    ActivateParents.Write(writer);
    WRITE(XATO);
    WRITE(XESP);
    WRITE(XEMI);
    WRITE(XMBR);
    WRITE(XPWR);
    if(XIBS.IsLoaded())
        WRITEEMPTY(XIBS);
    WRITE(XSCL);
    WRITE(DATA);
    return -1;
    }

bool PMISRecord::operator ==(const PMISRecord &other) const
    {
    return (NAME == other.NAME &&
            XIBS.IsLoaded() == other.XIBS.IsLoaded() &&
            XEZN == other.XEZN &&
            XCNT == other.XCNT &&
            XRDS == other.XRDS &&
            XHLP == other.XHLP &&
            XLKR == other.XLKR &&
            XCLP == other.XCLP &&
            XESP == other.XESP &&
            XEMI == other.XEMI &&
            XMBR == other.XMBR &&
            DATA == other.DATA &&
            XSCL == other.XSCL &&
            XDCR == other.XDCR &&
            EDID.equalsi(other.EDID) &&
            XATO.equals(other.XATO) &&
            XRGD == other.XRGD &&
            XRGB == other.XRGB &&
            ActivateParents == other.ActivateParents &&
            XPWR == other.XPWR &&
            Patrol == other.Patrol &&
            Ownership == other.Ownership);
    }

bool PMISRecord::operator !=(const PMISRecord &other) const
    {
    return !(*this == other);
    }

bool PMISRecord::equals(Record *other)
    {
    return *this == *(PMISRecord *)other;
    }

bool PMISRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)master->GetParentRecord();
    Record *parent_wrld = parent_cell->GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(parent_wrld != NULL)
        {
        if(master_wrld != NULL)
            {
            if(parent_wrld->formID != master_wrld->formID)
                return false;
            }
        else
            return false;
        }
    else if(master_wrld != NULL)
        return false;
    if(parent_wrld)
        {
        read_self.Accept((Record *&)parent_cell);
        read_master.Accept((Record *&)master_cell);
        parent_cell->XCLC.Load();
        master_cell->XCLC.Load();
        if(parent_cell->XCLC->posX != master_cell->XCLC->posX)
            return false;
        if(parent_cell->XCLC->posY != master_cell->XCLC->posY)
            return false;
        }
    return true;
    }
}