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
#include "common/Common.h"
#include "common/GenericRecord.h"

namespace Ob
{
class PACKRecord : public Record //Package
    {
    private:
        struct PACKPKDT //General
            {
            uint32_t  flags; //General Flags
            uint8_t   aiType, unused1[3]; //Type, Unused

            PACKPKDT();
            ~PACKPKDT();

            bool operator ==(const PACKPKDT &other) const;
            bool operator !=(const PACKPKDT &other) const;
            };

        struct PACKPLDT //Location
            {
            int32_t  locType;
            FORMID_OR_UINT32  locId;
            int32_t  locRadius;

            PACKPLDT();
            ~PACKPLDT();

            bool operator ==(const PACKPLDT &other) const;
            bool operator !=(const PACKPLDT &other) const;
            };

        struct PACKPSDT //Schedule
            {
            int8_t   month, day;
            uint8_t   date;
            int8_t   time;
            int32_t  duration;

            PACKPSDT();
            ~PACKPSDT();

            bool operator ==(const PACKPSDT &other) const;
            bool operator !=(const PACKPSDT &other) const;
            };

        struct PACKPTDT //Target
            {
            int32_t targetType;
            FORMID_OR_UINT32 targetId;
            int32_t targetCount;

            PACKPTDT();
            ~PACKPTDT();

            bool operator ==(const PACKPTDT &other) const;
            bool operator !=(const PACKPTDT &other) const;
            };

        enum flagsFlags
            {
            fIsOffersServices    = 0x00000001,
            fIsMustReachLocation = 0x00000002,
            fIsMustComplete      = 0x00000004,
            fIsLockAtStart       = 0x00000008,
            fIsLockAtEnd         = 0x00000010,
            fIsLockAtLocation    = 0x00000020,
            fIsUnlockAtStart     = 0x00000040,
            fIsUnlockAtEnd       = 0x00000080,
            fIsUnlockAtLocation  = 0x00000100,
            fIsContinueIfPcNear  = 0x00000200,
            fIsOncePerDay        = 0x00000400,
            fIsSkipFallout       = 0x00001000,
            fIsAlwaysRun         = 0x00002000,
            fIsAlwaysSneak       = 0x00020000,
            fIsAllowSwimming     = 0x00040000,
            fIsAllowFalls        = 0x00080000,
            fIsUnequipArmor      = 0x00100000,
            fIsUnequipWeapons    = 0x00200000,
            fIsDefensiveCombat   = 0x00400000,
            fIsUseHorse          = 0x00800000,
            fIsNoIdleAnims       = 0x01000000
            };

        enum aiTypeType
            {
            eAIFind          = 0,
            eAIFollow        = 1,
            eAIEscort        = 2,
            eAIEat           = 3,
            eAISleep         = 4,
            eAIWander        = 5,
            eAITravel        = 6,
            eAIAccompany     = 7,
            eAIUseItemAt     = 8,
            eAIAmbush        = 9,
            eAIFleeNotCombat = 10,
            eAICastMagic     = 11
            };

        enum locTypeType
            {
            eLocNearReference       = 0,
            eLocInCell              = 1,
            eLocNearCurrentLocation = 2,
            eLocNearEditorLocation  = 3,
            eLocObjectID            = 4,
            eLocObjectType          = 5
            };

        enum targetTypeType
            {
            eTargetReference  = 0,
            eTargetObjectID   = 1,
            eTargetObjectType = 2
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<PACKPKDT> PKDT; //General
        OptSubRecord<PACKPLDT> PLDT; //Location
        ReqSubRecord<PACKPSDT> PSDT; //Schedule
        OptSubRecord<PACKPTDT> PTDT; //Target
        OrderedSparseArray<GENCTDA *> CTDA; //Conditions

        PACKRecord(unsigned char *_recData=NULL);
        PACKRecord(PACKRecord *srcRecord);
        ~PACKRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsOffersServices();
        void   IsOffersServices(bool value);
        bool   IsMustReachLocation();
        void   IsMustReachLocation(bool value);
        bool   IsMustComplete();
        void   IsMustComplete(bool value);
        bool   IsLockAtStart();
        void   IsLockAtStart(bool value);
        bool   IsLockAtEnd();
        void   IsLockAtEnd(bool value);
        bool   IsLockAtLocation();
        void   IsLockAtLocation(bool value);
        bool   IsUnlockAtStart();
        void   IsUnlockAtStart(bool value);
        bool   IsUnlockAtEnd();
        void   IsUnlockAtEnd(bool value);
        bool   IsUnlockAtLocation();
        void   IsUnlockAtLocation(bool value);
        bool   IsContinueIfPcNear();
        void   IsContinueIfPcNear(bool value);
        bool   IsOncePerDay();
        void   IsOncePerDay(bool value);
        bool   IsSkipFallout();
        void   IsSkipFallout(bool value);
        bool   IsAlwaysRun();
        void   IsAlwaysRun(bool value);
        bool   IsAlwaysSneak();
        void   IsAlwaysSneak(bool value);
        bool   IsAllowSwimming();
        void   IsAllowSwimming(bool value);
        bool   IsAllowFalls();
        void   IsAllowFalls(bool value);
        bool   IsUnequipArmor();
        void   IsUnequipArmor(bool value);
        bool   IsUnequipWeapons();
        void   IsUnequipWeapons(bool value);
        bool   IsDefensiveCombat();
        void   IsDefensiveCombat(bool value);
        bool   IsUseHorse();
        void   IsUseHorse(bool value);
        bool   IsNoIdleAnims();
        void   IsNoIdleAnims(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsAIFind();
        void   IsAIFind(bool value);
        bool   IsAIFollow();
        void   IsAIFollow(bool value);
        bool   IsAIEscort();
        void   IsAIEscort(bool value);
        bool   IsAIEat();
        void   IsAIEat(bool value);
        bool   IsAISleep();
        void   IsAISleep(bool value);
        bool   IsAIWander();
        void   IsAIWander(bool value);
        bool   IsAITravel();
        void   IsAITravel(bool value);
        bool   IsAIAccompany();
        void   IsAIAccompany(bool value);
        bool   IsAIUseItemAt();
        void   IsAIUseItemAt(bool value);
        bool   IsAIAmbush();
        void   IsAIAmbush(bool value);
        bool   IsAIFleeNotCombat();
        void   IsAIFleeNotCombat(bool value);
        bool   IsAICastMagic();
        void   IsAICastMagic(bool value);
        bool   IsAIType(uint8_t Type);
        void   SetAIType(uint8_t Type);

        bool   IsLocNearReference();
        void   IsLocNearReference(bool value);
        bool   IsLocInCell();
        void   IsLocInCell(bool value);
        bool   IsLocNearCurrentLoc();
        void   IsLocNearCurrentLoc(bool value);
        bool   IsLocNearEditorLoc();
        void   IsLocNearEditorLoc(bool value);
        bool   IsLocObjectID();
        void   IsLocObjectID(bool value);
        bool   IsLocObjectType();
        void   IsLocObjectType(bool value);
        bool   IsLocType(int32_t Type);
        void   SetLocType(int32_t Type);

        bool   IsTargetReference();
        void   IsTargetReference(bool value);
        bool   IsTargetObjectID();
        void   IsTargetObjectID(bool value);
        bool   IsTargetObjectType();
        void   IsTargetObjectType(bool value);
        bool   IsTargetType(int32_t Type);
        void   SetTargetType(int32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const PACKRecord &other) const;
        bool operator !=(const PACKRecord &other) const;
        bool equals(Record *other);
    };
}