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
#include "../FNVRecord.h"

namespace FNV
{
class PERKRecord : public FNVRecord //Perk
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct PERKDATA
            {
            uint8_t   trait, minLevel, ranks, playable, hidden;

            PERKDATA();
            ~PERKDATA();

            bool operator ==(const PERKDATA &other) const;
            bool operator !=(const PERKDATA &other) const;
            };
        #pragma pack(pop)

        #pragma pack(push)
        #pragma pack(1)
        struct PERKPRKE //Header
            {
            uint8_t   perkType, rank, priority;

            PERKPRKE();
            ~PERKPRKE();

            bool operator ==(const PERKPRKE &other) const;
            bool operator !=(const PERKPRKE &other) const;
            };
        #pragma pack(pop)

        struct PERKCondition //Perk Condition
            {
            ReqSimpleSubRecord<int8_t> PRKC; //Run On
            OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

            bool   operator ==(const PERKCondition &other) const;
            bool   operator !=(const PERKCondition &other) const;
            };

        //This struct is...well, it's complicated
        //Essentially, widely different structs share the same chunk sig
        //and which struct gets used depends on an earlier chunk
        //The commented out pseudocode shows how each struct is composed
        //So this struct gets a lot of personal attention...
        struct PERKEffect //Effect
            {
            OptSubRecord<PERKPRKE> PRKE; //Header
            //if(PRKE.value.perkType == 0) //Quest + Stage
            //    {
            //    ReqSimpleSubRecord<FORMID> DATAfid; //quest
            //    ReqSimpleSubRecord<int8_t> DATAS8; //stage
            //    ReqSimpleSubRecord<uint8_t> DATAU81; //unused
            //    ReqSimpleSubRecord<uint8_t> DATAU82; //unused
            //    ReqSimpleSubRecord<uint8_t> DATAU83; //unused
            //    }
            //else if(PRKE.value.perkType == 1) //Ability
            //    {
            //    ReqSimpleSubRecord<FORMID> DATAfid; //ability
            //    }
            //else if(PRKE.value.perkType == 2) //Entry Point
            //    {
            //    ReqSimpleSubRecord<uint8_t> DATAU81; //entryType
            //    ReqSimpleSubRecord<uint8_t> DATAU82; //functionType
            //    ReqSimpleSubRecord<uint8_t> DATAU83; //tabCount
            //    }

            //Effect Data
            ReqSimpleSubRecord<FORMID> DATAfid; //quest or ability
            ReqSimpleSubRecord<int8_t> DATAS8; //stage
            ReqSimpleSubRecord<uint8_t> DATAU81; //unused or entryType
            ReqSimpleSubRecord<uint8_t> DATAU82; //unused or functionType
            ReqSimpleSubRecord<uint8_t> DATAU83; //unused or tabCount

            OrderedSparseArray<PERKCondition *> CTDA; //Conditions

            OptSimpleSubRecord<uint8_t> EPFT; //Type
            //if(EPFT.value == 1)
            //    ReqSimpleFloatSubRecord<flt_0> EPFDf1; //Data
            //else if(EPFT.value == 2)// Quest + Stage
            //    {
            //    if(DATA->DATA3.func == 5)// Ability
            //        {
            //        ReqSimpleSubRecord<uint32_t> EPFDav1; //Data
            //        ReqSimpleFloatSubRecord<flt_0> EPFDf2; //Data
            //        }
            //    else
            //        {
            //        ReqSimpleFloatSubRecord<flt_0> EPFDf1; //Data
            //        ReqSimpleFloatSubRecord<flt_0> EPFDf2; //Data
            //        }
            //    }
            //else if(EPFT.value == 3)
            //    ReqSimpleSubRecord<FORMID> EPFDfid1; //Data
            //else if(EPFT.value == 4)
            //    {
            //    StringRecord EPF2; //Button Label
            //    OptSimpleSubRecord<uint16_t> EPF3; //Script Flags
            //    ReqSubRecord<FNVSCHR> SCHR;
            //    RawRecord SCDA;
            //    NonNullStringRecord SCTX;
            //    OrderedSparseArray<GENVARS *, sortVARS> VARS;
            //    OrderedSparseArray<GENSCR_ *> SCR_;
            //    }
            ReqSimpleFloatSubRecord<flt_0> EPFDf1; //Data
            ReqSimpleFloatSubRecord<flt_0> EPFDf2; //Data
            ReqSimpleSubRecord<uint32_t> EPFDav1; //Data
            ReqSimpleSubRecord<FORMID> EPFDfid1; //Data
            StringRecord EPF2; //Button Label
            OptSimpleSubRecord<uint16_t> EPF3; //Script Flags
            ReqSubRecord<FNVSCHR> SCHR;
            RawRecord SCDA;
            NonNullStringRecord SCTX;
            OrderedSparseArray<GENVARS *, sortVARS> VARS;
            OrderedSparseArray<GENSCR_ *> SCR_;
            //OptSubRecord<GENPRKF> PRKF; //End Marker

            enum entryPointTypes
                {
                eCalculateWeaponDamage         = 0,
                eCalculateMyCriticalHitChance  = 1,
                eCalculateMyCriticalHitDamage  = 2,
                eCalculateWeaponAttackAPCost   = 3,
                eCalculateMineExplodeChance    = 4,
                eAdjustRangePenalty            = 5,
                eAdjustLimbDamage              = 6,
                eCalculateWeaponRange          = 7,
                eCalculateToHitChance          = 8,
                eAdjustExperiencePoints        = 9,
                eAdjustGainedSkillPoints       = 10,
                eAdjustBookSkillPoints         = 11,
                eModifyRecoveredHealth         = 12,
                eCalculateInventoryAPCost      = 13,
                eGetDisposition                = 14,
                eGetShouldAttack               = 15,
                eGetShouldAssist               = 16,
                eCalculateBuyPrice             = 17,
                eGetBadKarma                   = 18,
                eGetGoodKarma                  = 19,
                eIgnoreLockedTerminal          = 20,
                eAddLeveledListOnDeath         = 21,
                eGetMaxCarryWeight             = 22,
                eModifyAddictionChance         = 23,
                eModifyAddictionDuration       = 24,
                eModifyPositiveChemDuration    = 25,
                eAdjustDrinkingRadiation       = 26,
                eActivate                      = 27,
                eMysteriousStranger            = 28,
                eHasParalyzingPalm             = 29,
                eHackingScienceBonus           = 30,
                eIgnoreRunningDuringDetection  = 31,
                eIgnoreBrokenLock              = 32,
                eHasConcentratedFire           = 33,
                eCalculateGunSpread            = 34,
                ePlayerKillAPReward            = 35,
                eModifyEnemyCriticalHitChance  = 36,
                eReloadSpeed                   = 37,
                eEquipSpeed                    = 38,
                eActionPointRegen              = 39,
                eActionPointCost               = 40,
                eMissFortune                   = 41,
                eModifyRunSpeed                = 42,
                eModifyAttackSpeed             = 43,
                eModifyRadiationConsumed       = 44,
                eHasPipHacker                  = 45,
                eHasMeltdown                   = 46,
                eSeeEnemyHealth                = 47,
                eHasJuryRigging                = 48,
                eModifyThreatRange             = 49,
                eModifyThread                  = 50,
                eHasFastTravelAlways           = 51,
                eKnockdownChance               = 52,
                eModifyWeaponStrengthReq       = 53,
                eModifyAimingMoveSpeed         = 54,
                eModifyLightItems              = 55,
                eModifyDamageThresholdDefender = 56,
                eModifyChanceforAmmoItem       = 57,
                eModifyDamageThresholdAttacker = 58,
                eModifyThrowingVelocity        = 59,
                eChanceforItemonFire           = 60,
                eHasUnarmedForwardPowerAttack  = 61,
                eHasUnarmedBackPowerAttack     = 62,
                eHasUnarmedCrouchedPowerAttack = 63,
                eHasUnarmedCounterAttack       = 64,
                eHasUnarmedLeftPowerAttack     = 65,
                eHasUnarmedRightPowerAttack    = 66,
                eVATSHelperChance              = 67,
                eModifyItemDamage              = 68,
                eHasImprovedDetection          = 69,
                eHasImprovedSpotting           = 70,
                eHasImprovedItemDetection      = 71,
                eAdjustExplosionRadius         = 72,
                eReserved                      = 73
                };

            enum epf3Flags
                {
                fIsRunImmediately = 0x0001
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

            bool   IsRunImmediately();
            void   IsRunImmediately(bool value);
            bool   IsFlagMask(uint16_t Mask, bool Exact=false);
            void   SetFlagMask(uint16_t Mask);

            bool   IsScriptEnabled();
            void   IsScriptEnabled(bool value);
            bool   IsScriptFlagMask(uint16_t Mask, bool Exact=false);
            void   SetScriptFlagMask(uint16_t Mask);

            void   Write(FileWriter &writer);

            bool   operator ==(const PERKEffect &other) const;
            bool   operator !=(const PERKEffect &other) const;
            };

        enum traitTypes
            {
            eNotTrait = 0,
            eTrait
            };

        enum playableTypes
            {
            eNotPlayable = 0,
            ePlayable
            };

        enum hiddenTypes
            {
            eNotHidden = 0,
            eHidden
            };

        enum perkTypeTypes
            {
            eQuestStage = 0,
            eAbility,
            eEntryPoint
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord DESC; //Description
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions
        OptSubRecord<PERKDATA> DATA; //Data
        UnorderedSparseArray<PERKEffect *> PRKE; //Effects

        PERKRecord(unsigned char *_recData=NULL);
        PERKRecord(PERKRecord *srcRecord);
        ~PERKRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNotTrait();
        bool   IsTrait();
        bool   IsTraitType(uint8_t Type);
        void   SetTraitType(uint8_t Type);

        bool   IsNotPlayable();
        bool   IsPlayable();
        bool   IsPlayableType(uint8_t Type);
        void   SetPlayableType(uint8_t Type);

        bool   IsNotHidden();
        bool   IsHidden();
        bool   IsHiddenType(uint8_t Type);
        void   SetHiddenType(uint8_t Type);

        //bool   IsQuestStage();
        //bool   IsAbility();
        //bool   IsEntryPoint();
        //bool   IsType(uint8_t Type);
        //void   SetType(uint8_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const PERKRecord &other) const;
        bool operator !=(const PERKRecord &other) const;
        bool equals(Record *other);
    };
}