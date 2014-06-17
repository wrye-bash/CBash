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
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class RGDLRecord : public FNVRecord //Ragdoll
    {
    private:
        struct RGDLDATA //General Data
            {
            UINT32  numBones;
            UINT8   unused1[4], feedbackType;
            UINT8   footIKType, lookIKType, grabIKType; //Broken, don't use
            UINT8   matchPoseType, unused2;

            RGDLDATA();
            ~RGDLDATA();

            bool operator ==(const RGDLDATA &other) const;
            bool operator !=(const RGDLDATA &other) const;
            };

        struct RGDLRAFD //Feedback Data
            {
            FLOAT32 blendAmt, hierachyGain, posGain,
                    velGain, accGain, snapGain, velDamping,
                    snapLinVel, snapAngVel, snapLinDist,
                    snapAngDist, posLinVel, posAngVel;
            SINT32  posProjectileVel, posMeleeVel;

            RGDLRAFD();
            ~RGDLRAFD();

            bool operator ==(const RGDLRAFD &other) const;
            bool operator !=(const RGDLRAFD &other) const;
            };

        struct RGDLRAPS //Pose Matching Data
            {
            UINT16  matchBones1, matchBones2, matchBones3;
            UINT8   flags, unused;
            FLOAT32 motorsStrength, poseDelay, errorAllowance,
                    disableDisplacement;

            RGDLRAPS();
            ~RGDLRAPS();

            bool operator ==(const RGDLRAPS &other) const;
            bool operator !=(const RGDLRAPS &other) const;
            };

        enum flagsFlags
            {
            fIsDisableOnMove = 0x01
            };

        enum feedbackTypes
            {
            eNoFeedback = 0,
            eFeedback
            };

        enum footIKTypes
            {
            eNoFootIK = 0,
            eFootIK
            };

        enum lookIKTypes
            {
            eNoLookIK = 0,
            eLookIK
            };

        enum grabIKTypes
            {
            eNoGrabIK = 0,
            eGrabIK
            };

        enum matchPoseTypes
            {
            eNoMatchPose = 0,
            eMatchPose
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<UINT32> NVER; //Version
        OptSubRecord<RGDLDATA> DATA; //General Data
        OptSimpleSubRecord<FORMID> XNAM; //Actor Base
        OptSimpleSubRecord<FORMID> TNAM; //Body Part Data
        OptSubRecord<RGDLRAFD> RAFD; //Feedback Data
        UnorderedPackedArray<UINT16> RAFB; //Feedback Dynamic Bones
        OptSubRecord<RGDLRAPS> RAPS; //Pose Matching Data
        StringRecord ANAM; //Death Pose

        RGDLRecord(unsigned char *_recData=NULL);
        RGDLRecord(RGDLRecord *srcRecord);
        ~RGDLRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDisableOnMove();
        void   IsDisableOnMove(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        bool   IsNoFeedback();
        bool   IsFeedback();
        bool   IsFeedbackType(UINT8 Type);
        void   SetFeedbackType(UINT8 Type);

        bool   IsNoFootIK();
        bool   IsFootIK();
        bool   IsFootType(UINT8 Type);
        void   SetFootType(UINT8 Type);

        bool   IsNoLookIK();
        bool   IsLookIK();
        bool   IsLookType(UINT8 Type);
        void   SetLookType(UINT8 Type);

        bool   IsNoGrabIK();
        bool   IsGrabIK();
        bool   IsGrabType(UINT8 Type);
        void   SetGrabType(UINT8 Type);

        bool   IsNoMatchPose();
        bool   IsMatchPose();
        bool   IsMatchType(UINT8 Type);
        void   SetMatchType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const RGDLRecord &other) const;
        bool operator !=(const RGDLRecord &other) const;
        bool equals(Record *other);
    };
}