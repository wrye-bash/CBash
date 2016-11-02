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
#include "SCPTRecord.h"

namespace FNV
{
SCPTRecord::SCPTRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

SCPTRecord::SCPTRecord(SCPTRecord *srcRecord):
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
    SCHR = srcRecord->SCHR;
    SCDA = srcRecord->SCDA;
    SCTX = srcRecord->SCTX;
    VARS = srcRecord->VARS;
    SCR_ = srcRecord->SCR_;
    return;
    }

SCPTRecord::~SCPTRecord()
    {
    //
    }

bool SCPTRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < SCR_.value.size(); ListIndex++)
        if(SCR_.value[ListIndex]->isSCRO)
            op.Accept(SCR_.value[ListIndex]->reference);

    return op.Stop();
    }

bool SCPTRecord::IsScriptEnabled()
    {
    return (SCHR.value.flags & fIsEnabled) != 0;
    }

void SCPTRecord::IsScriptEnabled(bool value)
    {
    SETBIT(SCHR.value.flags, fIsEnabled, value);
    }

bool SCPTRecord::IsScriptFlagMask(uint16_t Mask, bool Exact)
    {
    return Exact ? (SCHR.value.flags & Mask) == Mask : (SCHR.value.flags & Mask) != 0;
    }

void SCPTRecord::SetScriptFlagMask(uint16_t Mask)
    {
    SCHR.value.flags = Mask;
    }

bool SCPTRecord::IsObject()
    {
    return SCHR.value.scriptType == eObject;
    }

void SCPTRecord::IsObject(bool value)
    {
    SCHR.value.scriptType = value ? eObject : eQuest;
    }

bool SCPTRecord::IsQuest()
    {
    return SCHR.value.scriptType == eQuest;
    }

void SCPTRecord::IsQuest(bool value)
    {
    SCHR.value.scriptType = value ? eQuest : eObject;
    }

bool SCPTRecord::IsEffect()
    {
    return SCHR.value.scriptType == eEffect;
    }

void SCPTRecord::IsEffect(bool value)
    {
    SCHR.value.scriptType = value ? eEffect : eObject;
    }

bool SCPTRecord::IsType(uint16_t Type)
    {
    return SCHR.value.scriptType == Type;
    }

void SCPTRecord::SetType(uint16_t Type)
    {
    SCHR.value.scriptType = Type;
    }

uint32_t SCPTRecord::GetType()
    {
    return REV32(SCPT);
    }

char * SCPTRecord::GetStrType()
    {
    return "SCPT";
    }

int32_t SCPTRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(SCHR):
                SCHR.Read(buffer, subSize);
                break;
            case REV32(SCDA):
                SCDA.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCTX):
                SCTX.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SLSD):
                VARS.value.push_back(new GENVARS);
                VARS.value.back()->SLSD.Read(buffer, subSize);
                break;
            case REV32(SCVR):
                if(VARS.value.size() == 0)
                    VARS.value.push_back(new GENVARS);
                VARS.value.back()->SCVR.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SCRV):
                SCR_.Read(buffer, subSize);
                SCR_.value.back()->isSCRO = false;
                break;
            case REV32(SCRO):
                SCR_.Read(buffer, subSize);
                SCR_.value.back()->isSCRO = true;
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  SCPT: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t SCPTRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    SCHR.Unload();
    SCDA.Unload();
    SCTX.Unload();
    VARS.Unload();
    SCR_.Unload();
    return 1;
    }

int32_t SCPTRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    SCHR.value.numRefs = (uint32_t)SCR_.value.size(); //Just to ensure that the value is correct
    SCHR.value.compiledSize = SCDA.GetSize(); //Just to ensure that the value is correct
    //for(uint32_t x = 0; x < VARS.value.size(); ++x) //Just to ensure that the value is correct
    //    SCHR.value.lastIndex = (SCHR.value.lastIndex > VARS.value[x]->SLSD.value.index) ? SCHR.value.lastIndex : VARS.value[x]->SLSD.value.index;
    WRITE(SCHR);
    WRITE(SCDA);
    WRITE(SCTX);
    VARS.Write(writer);
    SCR_.Write(writer, true);
    return -1;
    }

bool SCPTRecord::operator ==(const SCPTRecord &other) const
    {
    return (SCHR == other.SCHR &&
            EDID.equalsi(other.EDID) &&
            SCDA == other.SCDA &&
            VARS == other.VARS &&
            SCR_ == other.SCR_ &&
            SCTX.equalsi(other.SCTX));
    }

bool SCPTRecord::operator !=(const SCPTRecord &other) const
    {
    return !(*this == other);
    }

bool SCPTRecord::equals(Record *other)
    {
    return *this == *(SCPTRecord *)other;
    }
}