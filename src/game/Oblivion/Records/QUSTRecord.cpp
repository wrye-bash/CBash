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
#include "QUSTRecord.h"

namespace Ob
{
QUSTRecord::QUSTDATA::QUSTDATA():
    flags(0),
    priority(0)
    {
    //
    }

QUSTRecord::QUSTDATA::~QUSTDATA()
    {
    //
    }

bool QUSTRecord::QUSTDATA::operator ==(const QUSTDATA &other) const
    {
    return (flags == other.flags &&
            priority == other.priority);
    }

bool QUSTRecord::QUSTDATA::operator !=(const QUSTDATA &other) const
    {
    return !(*this == other);
    }

bool QUSTRecord::QUSTEntry::IsCompletes()
    {
    return (QSDT.value & fIsCompletes) != 0;
    }

void QUSTRecord::QUSTEntry::IsCompletes(bool value)
    {
    SETBIT(QSDT.value, fIsCompletes, value);
    }

bool QUSTRecord::QUSTEntry::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((QSDT.value & Mask) == Mask) : ((QSDT.value & Mask) != 0);
    }

void QUSTRecord::QUSTEntry::SetFlagMask(uint8_t Mask)
    {
    QSDT.value = Mask;
    }

bool QUSTRecord::QUSTEntry::IsObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void QUSTRecord::QUSTEntry::IsObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool QUSTRecord::QUSTEntry::IsQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void QUSTRecord::QUSTEntry::IsQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool QUSTRecord::QUSTEntry::IsEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void QUSTRecord::QUSTEntry::IsEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool QUSTRecord::QUSTEntry::IsType(uint16_t Type)
    {
    return SCHR.value.scriptType == Type;
    }

void QUSTRecord::QUSTEntry::SetType(uint16_t Type)
    {
    SCHR.value.scriptType = Type;
    }

void QUSTRecord::QUSTEntry::Write(FileWriter &writer)
    {
    WRITE(QSDT);
    CTDA.Write(writer, true);
    WRITE(CNAM);
    SCHR.value.numRefs = (uint32_t)SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    //for(uint32_t x = 0; x < VARS.value.size(); ++x) //Just to ensure that the value is correct
    //    SCHR.value.lastIndex = (SCHR.value.lastIndex > VARS.value[x]->SLSD.value.index) ? SCHR.value.lastIndex : VARS.value[x]->SLSD.value.index;
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    SCR_.Write(writer, true);
    }

bool QUSTRecord::QUSTEntry::operator ==(const QUSTEntry &other) const
    {
    return (QSDT == other.QSDT &&
            CNAM.equals(other.CNAM) &&
            SCHR == other.SCHR &&
            SCDA == other.SCDA &&
            SCTX.equalsi(other.SCTX) &&
            SCR_ == other.SCR_ &&
            CTDA == other.CTDA);
    }

bool QUSTRecord::QUSTEntry::operator !=(const QUSTEntry &other) const
    {
    return !(*this == other);
    }

void QUSTRecord::QUSTStage::Write(FileWriter &writer)
    {
    WRITE(INDX);
    Entries.Write(writer);
    }

bool QUSTRecord::QUSTStage::operator ==(const QUSTStage &other) const
    {
    return (INDX == other.INDX &&
            Entries == other.Entries);
    }

bool QUSTRecord::QUSTStage::operator !=(const QUSTStage &other) const
    {
    return !(*this == other);
    }

QUSTRecord::QUSTQSTA::QUSTQSTA():
    targetId(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    }

QUSTRecord::QUSTQSTA::~QUSTQSTA()
    {
    //
    }

bool QUSTRecord::QUSTQSTA::operator ==(const QUSTQSTA &other) const
    {
    return (targetId == other.targetId &&
            flags == other.flags);
    }

bool QUSTRecord::QUSTQSTA::operator !=(const QUSTQSTA &other) const
    {
    return !(*this == other);
    }

bool QUSTRecord::QUSTTarget::IsIgnoresLocks()
    {
    return (QSTA.value.flags & fIsIgnoresLocks) != 0;
    }

void QUSTRecord::QUSTTarget::IsIgnoresLocks(bool value)
    {
    SETBIT(QSTA.value.flags, fIsIgnoresLocks, value);
    }

bool QUSTRecord::QUSTTarget::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((QSTA.value.flags & Mask) == Mask) : ((QSTA.value.flags & Mask) != 0);
    }

void QUSTRecord::QUSTTarget::SetFlagMask(uint8_t Mask)
    {
    QSTA.value.flags = Mask;
    }

void QUSTRecord::QUSTTarget::Write(FileWriter &writer)
    {
    WRITE(QSTA);
    CTDA.Write(writer, true);
    }

bool QUSTRecord::QUSTTarget::operator ==(const QUSTTarget &other) const
    {
    return (QSTA == other.QSTA &&
            CTDA == other.CTDA);
    }

bool QUSTRecord::QUSTTarget::operator !=(const QUSTTarget &other) const
    {
    return !(*this == other);
    }

QUSTRecord::QUSTRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

QUSTRecord::QUSTRecord(QUSTRecord *srcRecord):
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
    SCRI = srcRecord->SCRI;
    FULL = srcRecord->FULL;
    ICON = srcRecord->ICON;
    DATA = srcRecord->DATA;
    CTDA = srcRecord->CTDA;
    Stages = srcRecord->Stages;
    Targets = srcRecord->Targets;
    return;
    }

QUSTRecord::~QUSTRecord()
    {
    //
    }

bool QUSTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SCRI.IsLoaded())
        op.Accept(SCRI.value);
    for(uint32_t ListIndex = 0; ListIndex < CTDA.value.size(); ListIndex++)
        CTDA.value[ListIndex]->VisitFormIDs(op);
    for(uint32_t ListIndex = 0; ListIndex < Stages.value.size(); ListIndex++)
        {
        for(uint32_t ListX2Index = 0; ListX2Index < Stages.value[ListIndex]->Entries.value.size(); ListX2Index++)
            {
            for(uint32_t ListX3Index = 0; ListX3Index < Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size(); ListX3Index++)
                Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->VisitFormIDs(op);
            for(uint32_t ListX3Index = 0; ListX3Index < Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size(); ListX3Index++)
                {
                if(Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->isSCRO)
                    op.Accept(Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->reference);
                }
            }
        }
    for(uint32_t ListIndex = 0; ListIndex < Targets.value.size(); ListIndex++)
        {
        op.Accept(Targets.value[ListIndex]->QSTA.value.targetId);
        for(uint32_t ListX2Index = 0; ListX2Index < Targets.value[ListIndex]->CTDA.value.size(); ListX2Index++)
            Targets.value[ListIndex]->CTDA.value[ListX2Index]->VisitFormIDs(op);
        }

    return op.Stop();
    }

bool QUSTRecord::IsStartEnabled()
    {
    return (DATA.value.flags & fIsStartEnabled) != 0;
    }

void QUSTRecord::IsStartEnabled(bool value)
    {
    SETBIT(DATA.value.flags, fIsStartEnabled, value);
    }

bool QUSTRecord::IsRepeatedTopics()
    {
    return (DATA.value.flags & fIsRepeatedTopics) != 0;
    }

void QUSTRecord::IsRepeatedTopics(bool value)
    {
    SETBIT(DATA.value.flags, fIsRepeatedTopics, value);
    }

bool QUSTRecord::IsRepeatedStages()
    {
    return (DATA.value.flags & fIsRepeatedStages) != 0;
    }

void QUSTRecord::IsRepeatedStages(bool value)
    {
    SETBIT(DATA.value.flags, fIsRepeatedStages, value);
    }

bool QUSTRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.flags & Mask) == Mask) : ((DATA.value.flags & Mask) != 0);
    }

void QUSTRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.flags = Mask;
    }

uint32_t QUSTRecord::GetType()
    {
    return REV32(QUST);
    }

char * QUSTRecord::GetStrType()
    {
    return "QUST";
    }

int32_t QUSTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t lastChunk = REV32(NONE);
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
            case REV32(SCRI):
                SCRI.Read(buffer, subSize);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(CTDT):
                //fallthrough is intentional
            case REV32(CTDA):
                switch(lastChunk)
                    {
                    case REV32(NONE):
                        CTDA.Read(buffer, subSize);
                        break;
                    case REV32(INDX):
                        if(Stages.value.size() == 0)
                            Stages.value.push_back(new QUSTStage);
                        if(Stages.value.back()->Entries.value.size() == 0)
                            Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                        Stages.value.back()->Entries.value.back()->CTDA.Read(buffer, subSize);
                        break;
                    case REV32(QSTA):
                        if(Targets.value.size() == 0)
                            Targets.value.push_back(new QUSTTarget);
                        Targets.value.back()->CTDA.Read(buffer, subSize);
                        break;
                    default:
                        printer("  QUST: %08X - Unexpected CTDA chunk\n", formID);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(INDX):
                Stages.value.push_back(new QUSTStage);
                Stages.value.back()->INDX.Read(buffer, subSize);
                lastChunk = REV32(INDX);
                break;
            case REV32(QSDT):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->QSDT.Read(buffer, subSize);
                break;
            case REV32(CNAM):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->CNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCHR):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRV):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->SCR_.Read(buffer, subSize);
                Stages.value.back()->Entries.value.back()->SCR_.value.back()->isSCRO = false;
                break;
            case REV32(SCRO):
                if(Stages.value.size() == 0)
                    Stages.value.push_back(new QUSTStage);
                if(Stages.value.back()->Entries.value.size() == 0)
                    Stages.value.back()->Entries.value.push_back(new QUSTEntry);
                Stages.value.back()->Entries.value.back()->SCR_.Read(buffer, subSize);
                Stages.value.back()->Entries.value.back()->SCR_.value.back()->isSCRO = true;
                break;
            case REV32(QSTA):
                Targets.value.push_back(new QUSTTarget);
                Targets.value.back()->QSTA.Read(buffer, subSize);
                lastChunk = REV32(QSTA);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  QUST: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t QUSTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);

    EDID.Unload();
    SCRI.Unload();
    FULL.Unload();
    ICON.Unload();
    DATA.Unload();
    CTDA.Unload();
    Stages.Unload();
    Targets.Unload();
    return 1;
    }

int32_t QUSTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(SCRI);
    WRITE(FULL);
    WRITE(ICON);
    WRITE(DATA);
    CTDA.Write(writer, true);
    Stages.Write(writer);
    Targets.Write(writer);
    return -1;
    }

bool QUSTRecord::operator ==(const QUSTRecord &other) const
    {
    return (SCRI == other.SCRI &&
            DATA == other.DATA &&
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            ICON.equalsi(other.ICON) &&
            CTDA == other.CTDA &&
            Stages == other.Stages &&
            Targets == other.Targets);
    }

bool QUSTRecord::operator !=(const QUSTRecord &other) const
    {
    return !(*this == other);
    }

bool QUSTRecord::equals(Record *other)
    {
    return *this == *(QUSTRecord *)other;
    }
}