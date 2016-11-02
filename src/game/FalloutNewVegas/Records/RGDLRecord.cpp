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
#include "RGDLRecord.h"

namespace FNV
{
RGDLRecord::RGDLDATA::RGDLDATA():
    numBones(0),
    feedbackType(eNoFeedback),
    footIKType(eNoFootIK), lookIKType(eNoLookIK), grabIKType(eNoGrabIK),
    matchPoseType(eNoMatchPose), unused2(0)
    {
    memset(&unused1, 0, sizeof(unused1));
    }

RGDLRecord::RGDLDATA::~RGDLDATA()
    {
    //
    }

bool RGDLRecord::RGDLDATA::operator ==(const RGDLDATA &other) const
    {
    return (numBones == other.numBones &&
            // unused1
            feedbackType == other.feedbackType &&
            footIKType == other.footIKType &&
            lookIKType == other.lookIKType &&
            grabIKType == other.grabIKType &&
            matchPoseType == other.matchPoseType
            // unused2
            );
    }

bool RGDLRecord::RGDLDATA::operator !=(const RGDLDATA &other) const
    {
    return !(*this == other);
    }

RGDLRecord::RGDLRAFD::RGDLRAFD():
    blendAmt(0.0), hierachyGain(0.0), posGain(0.0),
    velGain(0.0), accGain(0.0), snapGain(0.0), velDamping(0.0),
    snapLinVel(0.0), snapAngVel(0.0), snapLinDist(0.0),
    snapAngDist(0.0), posLinVel(0.0), posAngVel(0.0),
    posProjectileVel(0), posMeleeVel(0)
    {
    //
    }

RGDLRecord::RGDLRAFD::~RGDLRAFD()
    {
    //
    }

bool RGDLRecord::RGDLRAFD::operator ==(const RGDLRAFD &other) const
    {
    return (AlmostEqual(blendAmt, other.blendAmt, 2) &&
            AlmostEqual(hierachyGain, other.hierachyGain, 2) &&
            AlmostEqual(posGain, other.posGain, 2) &&
            AlmostEqual(velGain, other.velGain, 2) &&
            AlmostEqual(accGain, other.accGain, 2) &&
            AlmostEqual(snapGain, other.snapGain, 2) &&
            AlmostEqual(velDamping, other.velDamping, 2) &&
            AlmostEqual(snapLinVel, other.snapLinVel, 2) &&
            AlmostEqual(snapAngVel, other.snapAngVel, 2) &&
            AlmostEqual(snapLinDist, other.snapLinDist, 2) &&
            AlmostEqual(snapAngDist, other.snapAngDist, 2) &&
            AlmostEqual(posLinVel, other.posLinVel, 2) &&
            AlmostEqual(posAngVel, other.posAngVel, 2) &&
            posProjectileVel == other.posProjectileVel &&
            posMeleeVel == other.posMeleeVel
            );
    }

bool RGDLRecord::RGDLRAFD::operator !=(const RGDLRAFD &other) const
    {
    return !(*this == other);
    }

RGDLRecord::RGDLRAPS::RGDLRAPS():
    matchBones1(0), matchBones2(0), matchBones3(0),
    flags(0), unused(0),
    motorsStrength(0.0), poseDelay(0.0), errorAllowance(0.0),
    disableDisplacement(0.0)
    {
    //
    }

RGDLRecord::RGDLRAPS::~RGDLRAPS()
    {
    //
    }

bool RGDLRecord::RGDLRAPS::operator ==(const RGDLRAPS &other) const
    {
    return (matchBones1 == other.matchBones1 &&
            matchBones2 == other.matchBones2 &&
            matchBones3 == other.matchBones3 &&
            flags == other.flags &&
            // unused
            AlmostEqual(motorsStrength, other.motorsStrength, 2) &&
            AlmostEqual(poseDelay, other.poseDelay, 2) &&
            AlmostEqual(errorAllowance, other.errorAllowance, 2) &&
            AlmostEqual(disableDisplacement, other.disableDisplacement, 2)
            );
    }

bool RGDLRecord::RGDLRAPS::operator !=(const RGDLRAPS &other) const
    {
    return !(*this == other);
    }

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
        op.Accept(XNAM.value);
    if(TNAM.IsLoaded())
        op.Accept(TNAM.value);

    return op.Stop();
    }

bool RGDLRecord::IsDisableOnMove()
    {
    if (!RAPS.IsLoaded()) return false;
    return (RAPS->flags & fIsDisableOnMove) != 0;
    }

void RGDLRecord::IsDisableOnMove(bool value)
    {
    if (!RAPS.IsLoaded()) return;
    SETBIT(RAPS->flags, fIsDisableOnMove, value);
    }

bool RGDLRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!RAPS.IsLoaded()) return false;
    return Exact ? ((RAPS->flags & Mask) == Mask) : ((RAPS->flags & Mask) != 0);
    }

void RGDLRecord::SetFlagMask(uint8_t Mask)
    {
    RAPS.Load();
    RAPS->flags = Mask;
    }

bool RGDLRecord::IsNoFeedback()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->feedbackType == eNoFeedback);
    }

bool RGDLRecord::IsFeedback()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->feedbackType == eFeedback);
    }

bool RGDLRecord::IsFeedbackType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->feedbackType == Type;
    }

void RGDLRecord::SetFeedbackType(uint8_t Type)
    {
    DATA.Load();
    DATA->feedbackType = Type;
    }

bool RGDLRecord::IsNoFootIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->footIKType == eNoFootIK);
    }

bool RGDLRecord::IsFootIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->footIKType == eFootIK);
    }

bool RGDLRecord::IsFootType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->footIKType == Type;
    }

void RGDLRecord::SetFootType(uint8_t Type)
    {
    DATA.Load();
    DATA->footIKType = Type;
    }

bool RGDLRecord::IsNoLookIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->lookIKType == eNoLookIK);
    }

bool RGDLRecord::IsLookIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->lookIKType == eLookIK);
    }

bool RGDLRecord::IsLookType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->lookIKType == Type;
    }

void RGDLRecord::SetLookType(uint8_t Type)
    {
    DATA.Load();
    DATA->lookIKType = Type;
    }

bool RGDLRecord::IsNoGrabIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->grabIKType == eNoGrabIK);
    }

bool RGDLRecord::IsGrabIK()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->grabIKType == eGrabIK);
    }

bool RGDLRecord::IsGrabType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->grabIKType == Type;
    }

void RGDLRecord::SetGrabType(uint8_t Type)
    {
    DATA.Load();
    DATA->grabIKType = Type;
    }

bool RGDLRecord::IsNoMatchPose()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->matchPoseType == eNoMatchPose);
    }

bool RGDLRecord::IsMatchPose()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->matchPoseType == eMatchPose);
    }

bool RGDLRecord::IsMatchType(uint8_t Type)
    {
    if (!DATA.IsLoaded()) return false;
    return DATA->matchPoseType == Type;
    }

void RGDLRecord::SetMatchType(uint8_t Type)
    {
    DATA.Load();
    DATA->matchPoseType = Type;
    }

uint32_t RGDLRecord::GetType()
    {
    return REV32(RGDL);
    }

char * RGDLRecord::GetStrType()
    {
    return "RGDL";
    }

int32_t RGDLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
                ANAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t RGDLRecord::Unload()
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

int32_t RGDLRecord::WriteRecord(FileWriter &writer)
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

bool RGDLRecord::equals(Record *other)
    {
    return *this == *(RGDLRecord *)other;
    }
}