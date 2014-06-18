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
#include "DIALRecord.h"

namespace FNV
{
void DIALRecord::DIALUNK::Write(FileWriter &writer)
    {
    WRITE(INFC);
    WRITE(INFX);
    }

bool DIALRecord::DIALUNK::operator ==(const DIALUNK &other) const
    {
    return (INFC == other.INFC &&
            INFX == other.INFX);
    }

bool DIALRecord::DIALUNK::operator !=(const DIALUNK &other) const
    {
    return !(*this == other);
    }

void DIALRecord::DIALQSTI::Write(FileWriter &writer)
    {
    WRITE(QSTI);
    Unknown.Write(writer);
    }

bool DIALRecord::DIALQSTI::operator ==(const DIALQSTI &other) const
    {
    return (QSTI == other.QSTI &&
            Unknown == other.Unknown);
    }

bool DIALRecord::DIALQSTI::operator !=(const DIALQSTI &other) const
    {
    return !(*this == other);
    }

void DIALRecord::DIALQSTR::Write(FileWriter &writer)
    {
    WRITE(QSTR);
    Unknown.Write(writer);
    }

bool DIALRecord::DIALQSTR::operator ==(const DIALQSTR &other) const
    {
    return (QSTR == other.QSTR &&
            Unknown == other.Unknown);
    }

bool DIALRecord::DIALQSTR::operator !=(const DIALQSTR &other) const
    {
    return !(*this == other);
    }

DIALRecord::DIALDATA::DIALDATA():
    dialType(0),
    flags(0)
    {
    //
    }

DIALRecord::DIALDATA::~DIALDATA()
    {
    //
    }

bool DIALRecord::DIALDATA::operator ==(const DIALDATA &other) const
    {
    return (dialType == other.dialType &&
            flags == other.flags);
    }

bool DIALRecord::DIALDATA::operator !=(const DIALDATA &other) const
    {
    return !(*this == other);
    }

DIALRecord::DIALRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

DIALRecord::DIALRecord(DIALRecord *srcRecord):
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
    QSTI = srcRecord->QSTI;
    QSTR = srcRecord->QSTR;
    FULL = srcRecord->FULL;
    PNAM = srcRecord->PNAM;
    TDUM = srcRecord->TDUM;
    DATA = srcRecord->DATA;
    return;
    }

DIALRecord::~DIALRecord()
    {
    for(uint32_t x = 0; x < INFO.size(); x++)
        delete INFO[x];
    }

bool DIALRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < QSTI.value.size(); ListIndex++)
        {
        op.Accept(QSTI.value[ListIndex]->QSTI.value);
        for(uint32_t ListX2Index = 0; ListX2Index < QSTI.value[ListIndex]->Unknown.value.size(); ListX2Index++)
            op.Accept(QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value);
        }
    for(uint32_t ListIndex = 0; ListIndex < QSTR.value.size(); ListIndex++)
        {
        op.Accept(QSTR.value[ListIndex]->QSTR.value);
        for(uint32_t ListX2Index = 0; ListX2Index < QSTR.value[ListIndex]->Unknown.value.size(); ListX2Index++)
            op.Accept(QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value);
        }

    return op.Stop();
    }

bool DIALRecord::IsTopic()
    {
    return (DATA.value.dialType == eTopic);
    }

void DIALRecord::IsTopic(bool value)
    {
    DATA.value.dialType = value ? eTopic : eConversation;
    }

bool DIALRecord::IsConversation()
    {
    return (DATA.value.dialType == eConversation);
    }

void DIALRecord::IsConversation(bool value)
    {
    DATA.value.dialType = value ? eConversation : eTopic;
    }

bool DIALRecord::IsCombat()
    {
    return (DATA.value.dialType == eCombat);
    }

void DIALRecord::IsCombat(bool value)
    {
    DATA.value.dialType = value ? eCombat : eTopic;
    }

bool DIALRecord::IsPersuasion()
    {
    return (DATA.value.dialType == ePersuasion);
    }

void DIALRecord::IsPersuasion(bool value)
    {
    DATA.value.dialType = value ? ePersuasion : eTopic;
    }

bool DIALRecord::IsDetection()
    {
    return (DATA.value.dialType == eDetection);
    }

void DIALRecord::IsDetection(bool value)
    {
    DATA.value.dialType = value ? eDetection : eTopic;
    }

bool DIALRecord::IsService()
    {
    return (DATA.value.dialType == eService);
    }

void DIALRecord::IsService(bool value)
    {
    DATA.value.dialType = value ? eService : eTopic;
    }

bool DIALRecord::IsMisc()
    {
    return (DATA.value.dialType == eMisc);
    }

void DIALRecord::IsMisc(bool value)
    {
    DATA.value.dialType = value ? eMisc : eTopic;
    }

bool DIALRecord::IsRadio()
    {
    return (DATA.value.dialType == eRadio);
    }

void DIALRecord::IsRadio(bool value)
    {
    DATA.value.dialType = value ? eRadio : eTopic;
    }

bool DIALRecord::IsType(uint8_t Type)
    {
    return DATA.value.dialType == Type;
    }

void DIALRecord::SetType(uint8_t Type)
    {
    DATA.value.dialType = Type;
    }

bool DIALRecord::IsRumors()
    {
    return (DATA.value.flags & fIsRumors) != 0;
    }

void DIALRecord::IsRumors(bool value)
    {
    SETBIT(DATA.value.flags, fIsRumors, value);
    }

bool DIALRecord::IsTopLevel()
    {
    return (DATA.value.flags & fIsTopLevel) != 0;
    }

void DIALRecord::IsTopLevel(bool value)
    {
    SETBIT(DATA.value.flags, fIsTopLevel, value);
    }

bool DIALRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void DIALRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
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
    uint32_t lastChunk = 0;
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
                QSTI.value.push_back(new DIALQSTI);
                QSTI.value.back()->QSTI.Read(buffer, subSize);
                lastChunk = REV32(QSTI);
                break;
            case REV32(INFC):
                switch(lastChunk)
                    {
                    case REV32(QSTI):
                        if(QSTI.value.size() == 0)
                            QSTI.value.push_back(new DIALQSTI);
                        QSTI.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTI.value.back()->Unknown.value.back()->INFC.Read(buffer, subSize);
                        break;
                    case REV32(QSTR):
                        if(QSTR.value.size() == 0)
                            QSTR.value.push_back(new DIALQSTR);
                        QSTR.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTR.value.back()->Unknown.value.back()->INFC.Read(buffer, subSize);
                        break;
                    default:
                        //Occurs a limited number of times in FalloutNV.esm
                        //Presumably the CS was broken when writing these records at some point
                        //May not be ideal to junk them, but not much else can be done while their use is unknown
                        buffer += subSize;
                        break;
                        //printer("  DIAL: %08X - Unexpected INFC chunk\n", formID);
                        //CBASH_CHUNK_DEBUG
                        //printer("  Size = %i\n", subSize);
                        //printer("  CurPos = %04x\n\n", buffer - 6);
                        //buffer += subSize;
                        //break;
                    }
                break;
            case REV32(INFX):
                switch(lastChunk)
                    {
                    case REV32(QSTI):
                        if(QSTI.value.size() == 0)
                            QSTI.value.push_back(new DIALQSTI);
                        if(QSTI.value.back()->Unknown.value.size() == 0)
                            QSTI.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTI.value.back()->Unknown.value.back()->INFX.Read(buffer, subSize);
                        break;
                    case REV32(QSTR):
                        if(QSTR.value.size() == 0)
                            QSTR.value.push_back(new DIALQSTR);
                        if(QSTR.value.back()->Unknown.value.size() == 0)
                            QSTR.value.back()->Unknown.value.push_back(new DIALUNK);
                        QSTR.value.back()->Unknown.value.back()->INFX.Read(buffer, subSize);
                        break;
                    default:
                        //Occurs a limited number of times in FalloutNV.esm
                        //Presumably the CS was broken when writing these records at some point
                        //May not be ideal to junk them, but not much else can be done while their use is unknown
                        buffer += subSize;
                        break;
                        //printer("  DIAL: %08X - Unexpected INFX chunk\n", formID);
                        //CBASH_CHUNK_DEBUG
                        //printer("  Size = %i\n", subSize);
                        //printer("  CurPos = %04x\n\n", buffer - 6);
                        //buffer += subSize;
                        //break;
                    }
                break;
            case REV32(QSTR):
                QSTR.value.push_back(new DIALQSTR);
                QSTR.value.back()->QSTR.Read(buffer, subSize);
                lastChunk = REV32(QSTR);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize);
                break;
            case REV32(TDUM):
                TDUM.Read(buffer, subSize, CompressedOnDisk);
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
    PNAM.Unload();
    TDUM.Unload();
    DATA.Unload();
    return 1;
    }

int32_t DIALRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    QSTI.Write(writer);
    QSTR.Write(writer);
    WRITE(FULL);
    WRITE(PNAM);
    WRITE(TDUM);
    WRITE(DATA);
    return -1;
    }

bool DIALRecord::operator ==(const DIALRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            QSTI == other.QSTI &&
            QSTR == other.QSTR &&
            FULL.equals(other.FULL) &&
            PNAM == other.PNAM &&
            TDUM.equals(other.TDUM) &&
            DATA == other.DATA);
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