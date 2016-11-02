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
#include "DIALRecord.h"

namespace Ob
{
DIALRecord::DIALRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

DIALRecord::DIALRecord(DIALRecord *srcRecord):
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
    QSTI = srcRecord->QSTI;
    QSTR = srcRecord->QSTR;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    //INFOs are owned at the mod level, so must be destroyed there
    }

bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < QSTI.value.size(); ListIndex++)
        op.Accept(QSTI.value[ListIndex]);

    for(uint32_t ListIndex = 0; ListIndex < QSTR.value.size(); ListIndex++)
        op.Accept(QSTR.value[ListIndex]);

    return op.Stop();
    }

bool DIALRecord::IsTopic()
    {
    return (DATA.value == eTopic);
    }

void DIALRecord::IsTopic(bool value)
    {
    if(value)
        DATA.value = eTopic;
    else if(IsTopic())
        DATA.value = eConversation;
    }

bool DIALRecord::IsConversation()
    {
    return (DATA.value == eConversation);
    }

void DIALRecord::IsConversation(bool value)
    {
    if(value)
        DATA.value = eConversation;
    else if(IsConversation())
        DATA.value = eTopic;
    }

bool DIALRecord::IsCombat()
    {
    return (DATA.value == eCombat);
    }

void DIALRecord::IsCombat(bool value)
    {
    if(value)
        DATA.value = eCombat;
    else if(IsCombat())
        DATA.value = eTopic;
    }

bool DIALRecord::IsPersuasion()
    {
    return (DATA.value == ePersuasion);
    }

void DIALRecord::IsPersuasion(bool value)
    {
    if(value)
        DATA.value = ePersuasion;
    else if(IsPersuasion())
        DATA.value = eTopic;
    }

bool DIALRecord::IsDetection()
    {
    return (DATA.value == eDetection);
    }

void DIALRecord::IsDetection(bool value)
    {
    if(value)
        DATA.value = eDetection;
    else if(IsDetection())
        DATA.value = eTopic;
    }

bool DIALRecord::IsService()
    {
    return (DATA.value == eService);
    }

void DIALRecord::IsService(bool value)
    {
    if(value)
        DATA.value = eService;
    else if(IsService())
        DATA.value = eTopic;
    }

bool DIALRecord::IsMisc()
    {
    return (DATA.value == eMisc);
    }

void DIALRecord::IsMisc(bool value)
    {
    if(value)
        DATA.value = eMisc;
    else if(IsMisc())
        DATA.value = eTopic;
    }

bool DIALRecord::IsType(uint8_t Type)
    {
    return (DATA.value == Type);
    }

void DIALRecord::SetType(uint8_t Type)
    {
    DATA.value = Type;
    }

uint32_t DIALRecord::GetType()
    {
    return REV32(DIAL);
    }

char * DIALRecord::GetStrType()
    {
    return "DIAL";
    }

int32_t DIALRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(QSTI):
                QSTI.Read(buffer, subSize);
                break;
            case REV32(QSTR):
                QSTR.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  DIAL: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t DIALRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    QSTI.Unload();
    QSTR.Unload();
    FULL.Unload();
    DATA.Unload();
    return 1;
    }

int32_t DIALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(QSTI);
    WRITE(QSTR);
    WRITE(FULL);
    WRITE(DATA);
    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    return (DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            QSTI == other.QSTI &&
            QSTR == other.QSTR);
    }

bool DIALRecord::operator !=(const DIALRecord &other) const
    {
    return !(*this == other);
    }

bool DIALRecord::equals(Record *other)
    {
    return *this == *(DIALRecord *)other;
    }

bool DIALRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited
    if(INFO.size() > ((DIALRecord *)master)->INFO.size())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < INFO.size(); ++ListIndex)
        if(identical_records.count(INFO[ListIndex]) == 0)
                return false;
    return true;
    }
}