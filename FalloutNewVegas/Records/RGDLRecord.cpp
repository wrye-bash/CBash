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
#include "RGDLRecord.h"

namespace FNV
{
RGDLRecord::RGDLRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

RGDLRecord::RGDLRecord(RGDLRecord *srcRecord):
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
    NVER = srcRecord->NVER;
    DATA = srcRecord->DATA;
    XNAM = srcRecord->XNAM;
    TNAM = srcRecord->TNAM;
    RAFD = srcRecord->RAFD;
    RAFB = srcRecord->RAFB;
    RAPS = srcRecord->RAPS;
    ANAM = srcRecord->ANAM;
    return;
    }

RGDLRecord::~RGDLRecord()
    {
    //
    }

bool RGDLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(XNAM.IsLoaded())
        op.Accept(XNAM->value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM->value);

    return op.Stop();
    }

bool RGDLRecord::IsDisableOnMove()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->flags & fIsDisableOnMove) != 0;
    }

void RGDLRecord::IsDisableOnMove(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? (Dummy->flags | fIsDisableOnMove) : (Dummy->flags & ~fIsDisableOnMove);
    }

bool RGDLRecord::IsFlagMask(UINT8 Mask, bool Exact)
    {
    if(!Dummy.IsLoaded()) return false;
    return Exact ? ((Dummy->flags & Mask) == Mask) : ((Dummy->flags & Mask) != 0);
    }

void RGDLRecord::SetFlagMask(UINT8 Mask)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoFeedback()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoFeedback);
    }

void RGDLRecord::IsNoFeedback(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoFeedback : eDummyDefault;
    }

bool RGDLRecord::IsFeedback()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFeedback);
    }

void RGDLRecord::IsFeedback(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFeedback : eDummyDefault;
    }

bool RGDLRecord::IsFeedbackType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetFeedbackType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoFootIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoFootIK);
    }

void RGDLRecord::IsNoFootIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoFootIK : eDummyDefault;
    }

bool RGDLRecord::IsFootIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eFootIK);
    }

void RGDLRecord::IsFootIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eFootIK : eDummyDefault;
    }

bool RGDLRecord::IsFootType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetFootType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoLookIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoLookIK);
    }

void RGDLRecord::IsNoLookIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoLookIK : eDummyDefault;
    }

bool RGDLRecord::IsLookIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eLookIK);
    }

void RGDLRecord::IsLookIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eLookIK : eDummyDefault;
    }

bool RGDLRecord::IsLookType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetLookType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoGrabIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoGrabIK);
    }

void RGDLRecord::IsNoGrabIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoGrabIK : eDummyDefault;
    }

bool RGDLRecord::IsGrabIK()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eGrabIK);
    }

void RGDLRecord::IsGrabIK(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eGrabIK : eDummyDefault;
    }

bool RGDLRecord::IsGrabType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetGrabType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

bool RGDLRecord::IsNoMatchPose()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eNoMatchPose);
    }

void RGDLRecord::IsNoMatchPose(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eNoMatchPose : eDummyDefault;
    }

bool RGDLRecord::IsMatchPose()
    {
    if(!Dummy.IsLoaded()) return false;
    return (Dummy->type == eMatchPose);
    }

void RGDLRecord::IsMatchPose(bool value)
    {
    if(!Dummy.IsLoaded()) return;
    Dummy->flags = value ? eMatchPose : eDummyDefault;
    }

bool RGDLRecord::IsMatchType(UINT8 Type)
    {
    if(!Dummy.IsLoaded()) return false;
    return Dummy->type == Type;
    }

void RGDLRecord::SetMatchType(UINT8 Type)
    {
    Dummy.Load();
    Dummy->flags = Mask;
    }

UINT32 RGDLRecord::GetType()
    {
    return REV32(RGDL);
    }

STRING RGDLRecord::GetStrType()
    {
    return "RGDL";
    }

SINT32 RGDLRecord::ParseRecord(unsigned char *buffer, const UINT32 &recSize)
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
            case REV32(NVER):
                NVER.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(RAFD):
                RAFD.Read(buffer, subSize);
                break;
            case REV32(RAFB):
                RAFB.Read(buffer, subSize);
                break;
            case REV32(RAPS):
                RAPS.Read(buffer, subSize);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            default:
                //printf("FileName = %s\n", FileName);
                printf("  RGDL: %08X - Unknown subType = %04x\n", formID, subType);
                printf("  Size = %i\n", subSize);
                printf("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

SINT32 RGDLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    NVER.Unload();
    DATA.Unload();
    XNAM.Unload();
    TNAM.Unload();
    RAFD.Unload();
    RAFB.Unload();
    RAPS.Unload();
    ANAM.Unload();
    return 1;
    }

SINT32 RGDLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NVER);
    WRITE(DATA);
    WRITE(XNAM);
    WRITE(TNAM);
    WRITE(RAFD);
    WRITE(RAFB);
    WRITE(RAPS);
    WRITE(ANAM);

    return -1;
    }

bool RGDLRecord::operator ==(const RGDLRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NVER == other.NVER &&
            DATA == other.DATA &&
            XNAM == other.XNAM &&
            TNAM == other.TNAM &&
            RAFD == other.RAFD &&
            RAFB == other.RAFB &&
            RAPS == other.RAPS &&
            ANAM.equalsi(other.ANAM));
    }

bool RGDLRecord::operator !=(const RGDLRecord &other) const
    {
    return !(*this == other);
    }

bool RGDLRecord::equals(const Record *other) const
    {
    return *this == *(RGDLRecord *)other;
    }
}