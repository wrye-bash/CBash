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
#include "ROADRecord.h"

namespace Ob
{
ROADRecord::ROADPGRR::ROADPGRR():
    x(0.0f),
    y(0.0f),
    z(0.0f)
    {
    //
    }

ROADRecord::ROADPGRR::~ROADPGRR()
    {
    //
    }

bool ROADRecord::ROADPGRR::operator ==(const ROADPGRR &other) const
    {
    return (AlmostEqual(x,other.x,2) &&
            AlmostEqual(y,other.y,2) &&
            AlmostEqual(z,other.z,2));
    }

bool ROADRecord::ROADPGRR::operator !=(const ROADPGRR &other) const
    {
    return !(*this == other);
    }

ROADRecord::ROADRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

ROADRecord::ROADRecord(ROADRecord *srcRecord):
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

    PGRP = srcRecord->PGRP;
    PGRR = srcRecord->PGRR;
    return;
    }

ROADRecord::~ROADRecord()
    {
    //Parent is a shared pointer that's deleted when the WRLD group is deleted
    }

uint32_t ROADRecord::GetType()
    {
    return REV32(ROAD);
    }

char * ROADRecord::GetStrType()
    {
    return "ROAD";
    }

int32_t ROADRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(PGRP):
                PGRP.Read(buffer, subSize);
                break;
            case REV32(PGRR):
                PGRR.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  ROADPGRR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t ROADRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    PGRP.Unload();
    PGRR.Unload();
    return 1;
    }

int32_t ROADRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(PGRP);
    WRITE(PGRR);
    return -1;
    }

bool ROADRecord::operator ==(const ROADRecord &other) const
    {
    return (PGRP == other.PGRP &&
            PGRP == other.PGRP);
    }

bool ROADRecord::operator !=(const ROADRecord &other) const
    {
    return !(*this == other);
    }

bool ROADRecord::equals(Record *other)
    {
    return *this == *(ROADRecord *)other;
    }

bool ROADRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //Check to make sure the parent world is attached at the same spot
    if(GetParentRecord()->formID != master->GetParentRecord()->formID)
        return false;
    return true;
    }
}