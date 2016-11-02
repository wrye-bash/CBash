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
class CAMSRecord : public FNVRecord //Camera Shot
    {
    private:
        struct CAMSDATA //Data
            {
            uint32_t  action, location, target, flags; //Action, Location, Target, Flags
            float playerTimeMult, targetTimeMult, globalTimeMult; //Time Multipliers
            float maxTime, minTime, targetPercentBetweenActors; //Max Time, Min Time, Target % Between Actors

            CAMSDATA();
            ~CAMSDATA();

            bool operator ==(const CAMSDATA &other) const;
            bool operator !=(const CAMSDATA &other) const;
            };

        enum actionTypes
            {
            eShoot = 0,
            eFly,
            eHit,
            eZoom
            };

        enum locationOrTargetTypes
            {
            eAttacker = 0,
            eProjectile,
            eTarget
            };

        enum flagFlags
            {
            fIsPosFollowsLocation = 0x00000001,
            fIsPosFollowsTarget   = 0x00000002,
            fIsDontFollowBone     = 0x00000004,
            fIsFirstPersonCamera  = 0x00000008,
            fIsNoTracer           = 0x00000010,
            fIsStartAtTimeZero    = 0x00000020
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<CAMSDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> MNAM; //Image Space Modifier

        CAMSRecord(unsigned char *_recData=NULL);
        CAMSRecord(CAMSRecord *srcRecord);
        ~CAMSRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPosFollowsLocation();
        void   IsPosFollowsLocation(bool value);
        bool   IsPosFollowsTarget();
        void   IsPosFollowsTarget(bool value);
        bool   IsDontFollowBone();
        void   IsDontFollowBone(bool value);
        bool   IsFirstPersonCamera();
        void   IsFirstPersonCamera(bool value);
        bool   IsNoTracer();
        void   IsNoTracer(bool value);
        bool   IsStartAtTimeZero();
        void   IsStartAtTimeZero(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsActionShoot();
        bool   IsActionFly();
        bool   IsActionHit();
        bool   IsActionZoom();
        bool   IsActionType(uint32_t Type);
        void   SetActionType(uint32_t Type);

        bool   IsLocationAttacker();
        bool   IsLocationProjectile();
        bool   IsLocationTarget();
        bool   IsLocationType(uint32_t Type);
        void   SetLocationType(uint32_t Type);

        bool   IsTargetAttacker();
        bool   IsTargetProjectile();
        bool   IsTargetTarget();
        bool   IsTargetType(uint32_t Type);
        void   SetTargetType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const CAMSRecord &other) const;
        bool operator !=(const CAMSRecord &other) const;
        bool equals(Record *other);
    };
}