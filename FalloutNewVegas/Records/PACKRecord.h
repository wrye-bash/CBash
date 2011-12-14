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
class PACKRecord : public FNVRecord //Package
    {
    private:
        struct PACKPKDT //General
            {
            UINT32  flags; //General Flags
            UINT8   aiType, unused1; //Type, Unused
            UINT16  behaviorFlags; //Fallout Behavior Flags
            //Below are not always present in chunk...
            UINT16  specificFlags; //Type Specific Flags
            UINT8   unused2[2]; //Unused

            PACKPKDT();
            ~PACKPKDT();

            bool operator ==(const PACKPKDT &other) const;
            bool operator !=(const PACKPKDT &other) const;
            };

        struct PACKPLDT //Location
            {
            SINT32  locType;
            FORMID_OR_UINT32  locId;
            SINT32  locRadius;

            PACKPLDT();
            ~PACKPLDT();

            bool operator ==(const PACKPLDT &other) const;
            bool operator !=(const PACKPLDT &other) const;
            };

        struct PACKPSDT //Schedule
            {
            SINT8   month, day;
            UINT8   date;
            SINT8   time;
            SINT32  duration;

            PACKPSDT();
            ~PACKPSDT();

            bool operator ==(const PACKPSDT &other) const;
            bool operator !=(const PACKPSDT &other) const;
            };

        struct PACKPTDT //Target
            {
            SINT32  targetType; //Type
            FORMID_OR_UINT32 targetId; //Reference
            SINT32  targetCountOrDistance; //Count / Distance
            FLOAT32 unknown; //Unknown

            PACKPTDT();
            ~PACKPTDT();

            bool operator ==(const PACKPTDT &other) const;
            bool operator !=(const PACKPTDT &other) const;
            };

        struct PACKPKW3 //Use Weapon Data
            {
            UINT32  flags; //Flags
            UINT8   fireRate, fireType; //Fire Rate, Fire Count
            UINT16  burstNum, minShots, maxShots; //Number of Bursts, Shoots Per Volleys (Min, Max)
            FLOAT32 minPause, maxPause; //Pause Between Volleys (Min, Max)
            UINT8   unused[4]; //Unused

            PACKPKW3();
            ~PACKPKW3();

            bool operator ==(const PACKPKW3 &other) const;
            bool operator !=(const PACKPKW3 &other) const;
            };

        struct PACKPKDD //Dialogue Data
            {
            FLOAT32 FOV; //FOV
            FORMID  topic; //Topic
            UINT32  flags; //Flags
            UINT8   unused1[4];
            UINT32  dialType;
            UINT8   unknown[4];

            PACKPKDD();
            ~PACKPKDD();

            bool operator ==(const PACKPKDD &other) const;
            bool operator !=(const PACKPKDD &other) const;
            };

        enum flagsFlags
            {
            fIsOffersServices       = 0x00000001,
            fIsMustReachLocation    = 0x00000002,
            fIsMustComplete         = 0x00000004,
            fIsLockAtStart          = 0x00000008,
            fIsLockAtEnd            = 0x00000010,
            fIsLockAtLocation       = 0x00000020,
            fIsUnlockAtStart        = 0x00000040,
            fIsUnlockAtEnd          = 0x00000080,
            fIsUnlockAtLocation     = 0x00000100,
            fIsContinueIfPcNear     = 0x00000200,
            fIsOncePerDay           = 0x00000400,
            fIsSkipFallout          = 0x00001000,
            fIsAlwaysRun            = 0x00002000,
            fIsAlwaysSneak          = 0x00020000,
            fIsAllowSwimming        = 0x00040000,
            fIsAllowFalls           = 0x00080000,
            fIsHeadTrackingOff      = 0x00100000,
            fIsUnequipWeapons       = 0x00200000,
            fIsDefensiveCombat      = 0x00400000,
            fIsWeaponDrawn          = 0x00800000,
            fIsNoIdleAnims          = 0x01000000,
            fIsPretendInCombat      = 0x02000000,
            fIsContinueDuringCombat = 0x04000000,
            fIsNoCombatAlert        = 0x08000000,
            fIsNoWarnAttackBehavior = 0x10000000
            };

        enum behaviorFlags
            {
            fIsHellosToPlayer          = 0x00000001,
            fIsRandomConversations     = 0x00000002,
            fIsObserveCombatBehavior   = 0x00000004,
            fIsUnknown4                = 0x00000008,
            fIsReactionToPlayerActions = 0x00000010,
            fIsFriendlyFireComments    = 0x00000020,
            fIsAggroRadiusBehavior     = 0x00000040,
            fIsAllowIdleChatter        = 0x00000080,
            fIsAvoidRadiation          = 0x00000100
            };

        enum specificFlags
            {
            fIsHide                = 0x00000001, //Ambush only
            fIsNoEating            = 0x00000001,
            fIsNoSleeping          = 0x00000002,
            fIsSitDown             = 0x00000002, //Use Item At only
            fIsNoConversation      = 0x00000004,
            fIsRemainNearReference = 0x00000004, //Guard only
            fIsNoIdleMarkers       = 0x00000008,
            fIsNoFurniture         = 0x00000010,
            fIsNoWandering         = 0x00000020,
            fIsAllowBuying         = 0x00000100,
            fIsAllowKilling        = 0x00000200,
            fIsAllowStealing       = 0x00000400
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
            eAISandbox       = 12,
            eAIPatrol        = 13,
            eAIGuard         = 14,
            eAIDialogue      = 15,
            eAIUseWeapon     = 16
            };

        enum locTypeType
            {
            eLocNearReference       = 0,
            eLocInCell              = 1,
            eLocNearCurrentLocation = 2,
            eLocNearEditorLocation  = 3,
            eLocObjectID            = 4,
            eLocObjectType          = 5,
            eLocNearLinkedReference = 6,
            eLocAtPackageLocation   = 7
            };

        enum schedDayType
            {
            eAnyDay    = -1,
            eSunday    = 0,
            eMonday    = 1,
            eTuesday   = 2,
            eWednesday = 3,
            eThursday  = 4,
            eFriday    = 5,
            eSaturday  = 6,
            eWeekdays  = 7,
            eWeekends  = 8,
            eMWF       = 9,
            eTTh       = 10
            };

        enum targetTypeType
            {
            eTargetReference       = 0,
            eTargetObjectID        = 1,
            eTargetObjectType      = 2,
            eTargetLinkedReference = 3
            };

        enum idleFlags
            {
            fIsRunInSequence = 0x00000001,
            fIsDoOnce        = 0x00000004
            };

        enum pkptTypes
            {
            eNotRepeatable = 0,
            eRepeatable    = 1
            };

        enum weaponFlags
            {
            fIsAlwaysHit           = 0x00000001,
            fIsDoNoDamage          = 0x00000100,
            fIsCrouchToReload      = 0x00010000,
            fIsHoldFireWhenBlocked = 0x01000000
            };

        enum weaponRateTypes
            {
            eAutoFire   = 0,
            eVolleyFire = 1
            };

        enum weaponFireTypes
            {
            eNumberOfBursts = 0,
            eRepeatFire     = 1
            };

        enum dialogueFlags
            {
            fIsNoHeadtracking            = 0x00000001,
            fIsDontControlTargetMovement = 0x00000100
            };

        enum dialogueTypes
            {
            eConversation = 0,
            eSayTo        = 1
            };

        enum schrFlags
            {
            fIsEnabled = 0x0001
            };

        enum scriptTypeTypes
            {
            eObject = 0x0000,
            eQuest  = 0x0001,
            eEffect = 0x0100
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<PACKPKDT> PKDT; //General
        OptSubRecord<PACKPLDT> PLDT; //Location 1
        OptSubRecord<PACKPLDT> PLD2; //Location 2
        ReqSubRecord<PACKPSDT> PSDT; //Schedule
        OptSubRecord<PACKPTDT> PTDT; //Target 1
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
        OptSimpleSubRecord<UINT8> IDLF; //Idle Animation Flags
        OptSimpleSubRecord<UINT8> IDLC; //Idle Animation Count (may be a UINT32 instead, but only the lower 8 bits are used, so check size on read)
        OptSimpleFloatSubRecord<flt_0> IDLT; //Idle Timer Setting
        UnorderedPackedArray<FORMID> IDLA; //Animations
        RawRecord IDLB; //Unused
        //OptSubRecord<GENPKED> PKED; //Eat Marker (Empty)
        OptSimpleSubRecord<UINT32> PKE2; //Escort Distance
        OptSimpleSubRecord<FORMID> CNAM; //Combat Style
        OptSimpleFloatSubRecord<flt_0> PKFD; //Follow - Start Location - Trigger Radius
        OptSimpleSubRecord<UINT16> PKPT; //Patrol Flags, is sometimes a UINT8
        OptSubRecord<PACKPKW3> PKW3; //Use Weapon Data
        OptSubRecord<PACKPTDT> PTD2; //Target 2
        //OptSubRecord<GENPUID> PUID; //Use Item Marker (Empty)
        //OptSubRecord<GENPKAM> PKAM; //Ambush Marker (Empty)
        OptSubRecord<PACKPKDD> PKDD; //Dialogue Data
        //OptSubRecord<PACKPLDT> PLD2b; //Target 2 (again??)

        //OptSubRecord<PACKSCRI> POBA; //OnBegin Empty Marker
        ReqSimpleSubRecord<FORMID> BeginINAM;
        ReqSubRecord<FNVSCHR> BeginSCHR;
        RawRecord BeginSCDA;
        NonNullStringRecord BeginSCTX;
        OrderedSparseArray<GENVARS *, sortVARS> BeginVARS;
        OrderedSparseArray<GENSCR_ *> BeginSCR_;
        ReqSimpleSubRecord<FORMID> BeginTNAM;

        //OptSubRecord<PACKSCRI> POEA; //OnEnd Empty Marker
        ReqSimpleSubRecord<FORMID> EndINAM;
        ReqSubRecord<FNVSCHR> EndSCHR;
        RawRecord EndSCDA;
        NonNullStringRecord EndSCTX;
        OrderedSparseArray<GENVARS *, sortVARS> EndVARS;
        OrderedSparseArray<GENSCR_ *> EndSCR_;
        ReqSimpleSubRecord<FORMID> EndTNAM;

        //OptSubRecord<PACKSCRI> POCA; //OnChange Empty Marker
        ReqSimpleSubRecord<FORMID> ChangeINAM;
        ReqSubRecord<FNVSCHR> ChangeSCHR;
        RawRecord ChangeSCDA;
        NonNullStringRecord ChangeSCTX;
        OrderedSparseArray<GENVARS *, sortVARS> ChangeVARS;
        OrderedSparseArray<GENSCR_ *> ChangeSCR_;
        ReqSimpleSubRecord<FORMID> ChangeTNAM;

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
        bool   IsHeadTrackingOff();
        void   IsHeadTrackingOff(bool value);
        bool   IsUnequipWeapons();
        void   IsUnequipWeapons(bool value);
        bool   IsDefensiveCombat();
        void   IsDefensiveCombat(bool value);
        bool   IsWeaponDrawn();
        void   IsWeaponDrawn(bool value);
        bool   IsNoIdleAnims();
        void   IsNoIdleAnims(bool value);
        bool   IsPretendInCombat();
        void   IsPretendInCombat(bool value);
        bool   IsContinueDuringCombat();
        void   IsContinueDuringCombat(bool value);
        bool   IsNoCombatAlert();
        void   IsNoCombatAlert(bool value);
        bool   IsNoWarnAttackBehavior();
        void   IsNoWarnAttackBehavior(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsHellosToPlayer();
        void   IsHellosToPlayer(bool value);
        bool   IsRandomConversations();
        void   IsRandomConversations(bool value);
        bool   IsObserveCombatBehavior();
        void   IsObserveCombatBehavior(bool value);
        bool   IsUnknown4();
        void   IsUnknown4(bool value);
        bool   IsReactionToPlayerActions();
        void   IsReactionToPlayerActions(bool value);
        bool   IsFriendlyFireComments();
        void   IsFriendlyFireComments(bool value);
        bool   IsAggroRadiusBehavior();
        void   IsAggroRadiusBehavior(bool value);
        bool   IsAllowIdleChatter();
        void   IsAllowIdleChatter(bool value);
        bool   IsAvoidRadiation();
        void   IsAvoidRadiation(bool value);
        bool   IsBehaviorFlagMask(UINT16 Mask, bool Exact=false);
        void   SetBehaviorFlagMask(UINT16 Mask);

        bool   IsHide();//Ambush only
        void   IsHide(bool value);//Ambush only
        bool   IsNoEating();
        void   IsNoEating(bool value);
        bool   IsNoSleeping();
        void   IsNoSleeping(bool value);
        bool   IsSitDown();//Use Item At only
        void   IsSitDown(bool value);//Use Item At only
        bool   IsNoConversation();
        void   IsNoConversation(bool value);
        bool   IsRemainNearReference();//Guard only
        void   IsRemainNearReference(bool value);//Guard only
        bool   IsNoIdleMarkers();
        void   IsNoIdleMarkers(bool value);
        bool   IsNoFurniture();
        void   IsNoFurniture(bool value);
        bool   IsNoWandering();
        void   IsNoWandering(bool value);
        bool   IsAllowBuying();
        void   IsAllowBuying(bool value);
        bool   IsAllowKilling();
        void   IsAllowKilling(bool value);
        bool   IsAllowStealing();
        void   IsAllowStealing(bool value);
        bool   IsSpecificFlagMask(UINT16 Mask, bool Exact=false);
        void   SetSpecificFlagMask(UINT16 Mask);

        bool   IsRunInSequence();
        void   IsRunInSequence(bool value);
        bool   IsDoOnce();
        void   IsDoOnce(bool value);
        bool   IsIdleFlagMask(UINT8 Mask, bool Exact=false);
        void   SetIdleFlagMask(UINT8 Mask);

        bool   IsAlwaysHit();
        void   IsAlwaysHit(bool value);
        bool   IsDoNoDamage();
        void   IsDoNoDamage(bool value);
        bool   IsCrouchToReload();
        void   IsCrouchToReload(bool value);
        bool   IsHoldFireWhenBlocked();
        void   IsHoldFireWhenBlocked(bool value);
        bool   IsWeaponFlagMask(UINT32 Mask, bool Exact=false);
        void   SetWeaponFlagMask(UINT32 Mask);

        bool   IsNoHeadtracking();
        void   IsNoHeadtracking(bool value);
        bool   IsDontControlTargetMovement();
        void   IsDontControlTargetMovement(bool value);
        bool   IsDialogueFlagMask(UINT32 Mask, bool Exact=false);
        void   SetDialogueFlagMask(UINT32 Mask);

        bool   IsBeginScriptEnabled();
        void   IsBeginScriptEnabled(bool value);
        bool   IsBeginScriptFlagMask(UINT16 Mask, bool Exact=false);
        void   SetBeginScriptFlagMask(UINT16 Mask);

        bool   IsEndScriptEnabled();
        void   IsEndScriptEnabled(bool value);
        bool   IsEndScriptFlagMask(UINT16 Mask, bool Exact=false);
        void   SetEndScriptFlagMask(UINT16 Mask);

        bool   IsChangeScriptEnabled();
        void   IsChangeScriptEnabled(bool value);
        bool   IsChangeScriptFlagMask(UINT16 Mask, bool Exact=false);
        void   SetChangeScriptFlagMask(UINT16 Mask);

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
        bool   IsAISandbox();
        void   IsAISandbox(bool value);
        bool   IsAIPatrol();
        void   IsAIPatrol(bool value);
        bool   IsAIGuard();
        void   IsAIGuard(bool value);
        bool   IsAIDialogue();
        void   IsAIDialogue(bool value);
        bool   IsAIUseWeapon();
        void   IsAIUseWeapon(bool value);
        bool   IsAIType(UINT8 Type);
        void   SetAIType(UINT8 Type);

        bool   IsLoc1NearReference();
        void   IsLoc1NearReference(bool value);
        bool   IsLoc1InCell();
        void   IsLoc1InCell(bool value);
        bool   IsLoc1NearCurrentLocation();
        void   IsLoc1NearCurrentLocation(bool value);
        bool   IsLoc1NearEditorLocation();
        void   IsLoc1NearEditorLocation(bool value);
        bool   IsLoc1ObjectID();
        void   IsLoc1ObjectID(bool value);
        bool   IsLoc1ObjectType();
        void   IsLoc1ObjectType(bool value);
        bool   IsLoc1NearLinkedReference();
        void   IsLoc1NearLinkedReference(bool value);
        bool   IsLoc1AtPackageLocation();
        void   IsLoc1AtPackageLocation(bool value);
        bool   IsLoc1Type(SINT32 Type);
        void   SetLoc1Type(SINT32 Type);

        bool   IsLoc2NearReference();
        void   IsLoc2NearReference(bool value);
        bool   IsLoc2InCell();
        void   IsLoc2InCell(bool value);
        bool   IsLoc2NearCurrentLocation();
        void   IsLoc2NearCurrentLocation(bool value);
        bool   IsLoc2NearEditorLocation();
        void   IsLoc2NearEditorLocation(bool value);
        bool   IsLoc2ObjectID();
        void   IsLoc2ObjectID(bool value);
        bool   IsLoc2ObjectType();
        void   IsLoc2ObjectType(bool value);
        bool   IsLoc2NearLinkedReference();
        void   IsLoc2NearLinkedReference(bool value);
        bool   IsLoc2AtPackageLocation();
        void   IsLoc2AtPackageLocation(bool value);
        bool   IsLoc2Type(SINT32 Type);
        void   SetLoc2Type(SINT32 Type);

        bool   IsTarget1Reference();
        void   IsTarget1Reference(bool value);
        bool   IsTarget1ObjectID();
        void   IsTarget1ObjectID(bool value);
        bool   IsTarget1ObjectType();
        void   IsTarget1ObjectType(bool value);
        bool   IsTarget1LinkedReference();
        void   IsTarget1LinkedReference(bool value);
        bool   IsTarget1Type(SINT32 Type);
        void   SetTarget1Type(SINT32 Type);

        bool   IsTarget2Reference();
        void   IsTarget2Reference(bool value);
        bool   IsTarget2ObjectID();
        void   IsTarget2ObjectID(bool value);
        bool   IsTarget2ObjectType();
        void   IsTarget2ObjectType(bool value);
        bool   IsTarget2LinkedReference();
        void   IsTarget2LinkedReference(bool value);
        bool   IsTarget2Type(SINT32 Type);
        void   SetTarget2Type(SINT32 Type);

        bool   IsAnyDay();
        void   IsAnyDay(bool value);
        bool   IsSunday();
        void   IsSunday(bool value);
        bool   IsMonday();
        void   IsMonday(bool value);
        bool   IsTuesday();
        void   IsTuesday(bool value);
        bool   IsWednesday();
        void   IsWednesday(bool value);
        bool   IsThursday();
        void   IsThursday(bool value);
        bool   IsFriday();
        void   IsFriday(bool value);
        bool   IsSaturday();
        void   IsSaturday(bool value);
        bool   IsWeekdays();
        void   IsWeekdays(bool value);
        bool   IsWeekends();
        void   IsWeekends(bool value);
        bool   IsMWF();
        void   IsMWF(bool value);
        bool   IsTTh();
        void   IsTTh(bool value);
        bool   IsDayType(SINT8 Type);
        void   SetDayType(SINT8 Type);

        bool   IsNotRepeatable();
        void   IsNotRepeatable(bool value);
        bool   IsRepeatable();
        void   IsRepeatable(bool value);
        bool   IsRepeatType(UINT16 Type);
        void   SetRepeatType(UINT16 Type);

        bool   IsAutoFire();
        void   IsAutoFire(bool value);
        bool   IsVolleyFire();
        void   IsVolleyFire(bool value);
        bool   IsFireType(UINT8 Type);
        void   SetFireType(UINT8 Type);

        bool   IsNumberOfBursts();
        void   IsNumberOfBursts(bool value);
        bool   IsRepeatFire();
        void   IsRepeatFire(bool value);
        bool   IsFireCountType(UINT8 Type);
        void   SetFireCountType(UINT8 Type);

        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsSayTo();
        void   IsSayTo(bool value);
        bool   IsDialogueType(UINT32 Type);
        void   SetDialogueType(UINT32 Type);

        bool   IsBeginObject();
        void   IsBeginObject(bool value);
        bool   IsBeginQuest();
        void   IsBeginQuest(bool value);
        bool   IsBeginEffect();
        void   IsBeginEffect(bool value);
        bool   IsBeginType(UINT16 Type);
        void   SetBeginType(UINT16 Type);

        bool   IsEndObject();
        void   IsEndObject(bool value);
        bool   IsEndQuest();
        void   IsEndQuest(bool value);
        bool   IsEndEffect();
        void   IsEndEffect(bool value);
        bool   IsEndType(UINT16 Type);
        void   SetEndType(UINT16 Type);

        bool   IsChangeObject();
        void   IsChangeObject(bool value);
        bool   IsChangeQuest();
        void   IsChangeQuest(bool value);
        bool   IsChangeEffect();
        void   IsChangeEffect(bool value);
        bool   IsChangeType(UINT16 Type);
        void   SetChangeType(UINT16 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const PACKRecord &other) const;
        bool operator !=(const PACKRecord &other) const;
        bool equals(Record *other);
    };
}