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
#include "PGRDRecord.h"
#include "CELLRecord.h"

namespace Ob
{
PGRDRecord::PGRDPGRI::PGRDPGRI():point(0), x(0.0f), y(0.0f), z(0.0f)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

PGRDRecord::PGRDPGRI::~PGRDPGRI()
    {
    //
    }

bool PGRDRecord::PGRDPGRI::operator ==(const PGRDPGRI &other) const
    {
    return (point == other.point &&
            AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool PGRDRecord::PGRDPGRI::operator !=(const PGRDPGRI &other) const
    {
    return !(*this == other);
    }

PGRDRecord::PGRDPGRL::PGRDPGRL()
    {
    //First element must be allocated since it's where the reference is stored
    points.value.push_back(0);
    }

PGRDRecord::PGRDPGRL::~PGRDPGRL()
    {
    //
    }

void PGRDRecord::PGRDPGRL::Write(FileWriter &writer)
    {
    WRITEAS(points,PGRL);
    }

bool PGRDRecord::PGRDPGRL::operator ==(const PGRDPGRL &other) const
    {
    return points == other.points;
    }

bool PGRDRecord::PGRDPGRL::operator !=(const PGRDPGRL &other) const
    {
    return !(*this == other);
    }

PGRDRecord::PGRDRecord(unsigned char *_recData):
    Record(_recData)
    {
    //PGRD records are normally compressed due to size
    if(_recData == NULL)
        IsCompressed(true);
    }

PGRDRecord::PGRDRecord(PGRDRecord *srcRecord):
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

    DATA = srcRecord->DATA;
    PGRP = srcRecord->PGRP;
    PGAG = srcRecord->PGAG;
    PGRR = srcRecord->PGRR;
    PGRI = srcRecord->PGRI;
    PGRL = srcRecord->PGRL;
    }

PGRDRecord::~PGRDRecord()
    {
    //Parent is a shared pointer that's deleted when the CELL group is deleted
    }

bool PGRDRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < PGRL.value.size(); x++)
        op.Accept(PGRL.value[x]->points.value[0]);

    return op.Stop();
    }

uint32_t PGRDRecord::GetType()
    {
    return REV32(PGRD);
    }

char * PGRDRecord::GetStrType()
    {
    return "PGRD";
    }

int32_t PGRDRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(PGRP):
                PGRP.Read(buffer, subSize);
                break;
            case REV32(PGAG):
                PGAG.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PGRR):
                PGRR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PGRI):
                PGRI.Read(buffer, subSize);
                break;
            case REV32(PGRL):
                PGRL.value.push_back(new PGRDPGRL);
                PGRL.value.back()->points.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  PGRD: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t PGRDRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    DATA.Unload();
    PGRP.Unload();
    PGAG.Unload();
    PGRR.Unload();
    PGRI.Unload();
    PGRL.Unload();
    return 1;
    }

int32_t PGRDRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(DATA);
    WRITE(PGRP);
    WRITE(PGAG);
    WRITE(PGRR);
    WRITE(PGRI);
    PGRL.Write(writer);
    return -1;
    }

bool PGRDRecord::operator ==(const PGRDRecord &other) const
    {
    return (DATA == other.DATA &&
            PGAG == other.PGAG &&
            PGRR == other.PGRR &&
            PGRI == other.PGRI &&
            PGRP == other.PGRP &&
            PGRL == other.PGRL);
    }

bool PGRDRecord::operator !=(const PGRDRecord &other) const
    {
    return !(*this == other);
    }

bool PGRDRecord::equals(Record *other)
    {
    return *this == *(PGRDRecord *)other;
    }

bool PGRDRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
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