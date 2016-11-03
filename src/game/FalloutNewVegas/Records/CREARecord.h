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
class CREARecord : public FNVRecord //Creature
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct CREADATA
            {
            uint8_t   creatureType, combat, magic, stealth;
            uint16_t  health;
            uint8_t   unused1[2];
            int16_t  attackDamage;
            uint8_t   strength, perception, endurance, charisma, intelligence, agility, luck;

            CREADATA();
            ~CREADATA();

            bool operator ==(const CREADATA &other) const;
            bool operator !=(const CREADATA &other) const;
            };
        #pragma pack(pop)

        struct CREASound //Sound
            {
            ReqSimpleSubRecord<FORMID> CSDI; //Sound
            ReqSimpleSubRecord<uint8_t>  CSDC; //Sound Chance

            void Write(FileWriter &writer);

            bool operator ==(const CREASound &other) const;
            bool operator !=(const CREASound &other) const;
            };

        struct CREASoundType //Sound Type
            {
            ReqSimpleSubRecord<uint32_t> CSDT; //Type
            UnorderedSparseArray<CREASound *> Sounds; //Sounds

            enum eSoundType
                {
                eLeftFoot       = 0,
                eRightFoot      = 1,
                eLeftBackFoot   = 2,
                eRightBackFoot  = 3,
                eIdle           = 4,
                eAware          = 5,
                eAttack         = 6,
                eHit            = 7,
                eDeath          = 8,
                eWeapon         = 9,
                eMovementLoop   = 10,
                eConsciousLoop  = 11,
                eAuxiliary1     = 12,
                eAuxiliary2     = 13,
                eAuxiliary3     = 14,
                eAuxiliary4     = 15,
                eAuxiliary5     = 16,
                eAuxiliary6     = 17,
                eAuxiliary7     = 18,
                eAuxiliary8     = 19,
                eJump           = 20,
                ePlayRandomLoop = 21
                };

            bool   IsLeftFoot();
            void   IsLeftFoot(bool value);
            bool   IsRightFoot();
            void   IsRightFoot(bool value);
            bool   IsLeftBackFoot();
            void   IsLeftBackFoot(bool value);
            bool   IsRightBackFoot();
            void   IsRightBackFoot(bool value);
            bool   IsIdle();
            void   IsIdle(bool value);
            bool   IsAware();
            void   IsAware(bool value);
            bool   IsAttack();
            void   IsAttack(bool value);
            bool   IsHit();
            void   IsHit(bool value);
            bool   IsDeath();
            void   IsDeath(bool value);
            bool   IsWeapon();
            void   IsWeapon(bool value);
            bool   IsMovementLoop();
            void   IsMovementLoop(bool value);
            bool   IsConsciousLoop();
            void   IsConsciousLoop(bool value);
            bool   IsAuxiliary1();
            void   IsAuxiliary1(bool value);
            bool   IsAuxiliary2();
            void   IsAuxiliary2(bool value);
            bool   IsAuxiliary3();
            void   IsAuxiliary3(bool value);
            bool   IsAuxiliary4();
            void   IsAuxiliary4(bool value);
            bool   IsAuxiliary5();
            void   IsAuxiliary5(bool value);
            bool   IsAuxiliary6();
            void   IsAuxiliary6(bool value);
            bool   IsAuxiliary7();
            void   IsAuxiliary7(bool value);
            bool   IsAuxiliary8();
            void   IsAuxiliary8(bool value);
            bool   IsJump();
            void   IsJump(bool value);
            bool   IsPlayRandomLoop();
            void   IsPlayRandomLoop(bool value);
            bool   IsType(uint32_t Type);
            void   SetType(uint32_t Type);

            void Write(FileWriter &writer);

            bool operator ==(const CREASoundType &other) const;
            bool operator !=(const CREASoundType &other) const;
            };

        enum flagsFlags
            {
            fIsBiped           = 0x00000001,
            fIsEssential       = 0x00000002,
            fIsWeaponAndShield = 0x00000004, // ?
            fIsRespawn         = 0x00000008,
            fIsSwims           = 0x00000010,
            fIsFlies           = 0x00000020,
            fIsWalks           = 0x00000040,
            fIsPCLevelOffset   = 0x00000080,
            fIsUnknown1        = 0x00000100,
            fIsNoLowLevel      = 0x00000200,
            fIsNoBloodSpray    = 0x00000800,
            fIsNoBloodDecal    = 0x00001000,
            //fIsSummonable    = 0x00004000, //OBSE
            fIsNoHead          = 0x00008000,
            fIsNoRightArm      = 0x00010000,
            fIsNoLeftArm       = 0x00020000,
            fIsNoCombatInWater = 0x00040000,
            fIsNoShadow        = 0x00080000,
            fIsNoVATSMelee     = 0x00100000,
            fIsAllowPCDialogue = 0x00200000,
            fIsCantOpenDoors   = 0x00400000,
            fIsImmobile        = 0x00800000,
            fIsTiltFrontBack   = 0x01000000,
            fIsTiltLeftRight   = 0x02000000,
            fIsNoKnockdowns    = 0x03000000, //3?
            fIsNotPushable     = 0x08000000,
            fIsAllowPickpocket = 0x10000000,
            fIsGhost           = 0x20000000,
            fIsNoHeadTracking  = 0x40000000,
            fIsInvulnerable    = 0x80000000
            };

        enum templateFlags
            {
            fIsUseTraits     = 0x00000001,
            fIsUseStats      = 0x00000002,
            fIsUseFactions   = 0x00000004,
            fIsUseAEList     = 0x00000008,
            fIsUseAIData     = 0x00000010,
            fIsUseAIPackages = 0x00000020,
            fIsUseModelAnim  = 0x00000040,
            fIsUseBaseData   = 0x00000080,
            fIsUseInventory  = 0x00000100,
            fIsUseScript     = 0x00000200
            };

        enum attackAnimTypes
            {
            eAttackLeft         = 26,
            eAttackLeftUp       = 27,
            eAttackLeftDown     = 28,
            eAttackLeftIS       = 29,
            eAttackLeftISUp     = 30,
            eAttackLeftISDown   = 31,
            eAttackRight        = 32,
            eAttackRightUp      = 33,
            eAttackRightDown    = 34,
            eAttackRightIS      = 35,
            eAttackRightISUp    = 36,
            eAttackRightISDown  = 37,
            eAttack3            = 38,
            eAttack3Up          = 39,
            eAttack3Down        = 40,
            eAttack3IS          = 41,
            eAttack3ISUp        = 42,
            eAttack3ISDown      = 43,
            eAttack4            = 44,
            eAttack4Up          = 45,
            eAttack4Down        = 46,
            eAttack4IS          = 47,
            eAttack4ISUp        = 48,
            eAttack4ISDown      = 49,
            eAttack5            = 50,
            eAttack5Up          = 51,
            eAttack5Down        = 52,
            eAttack5IS          = 53,
            eAttack5ISUp        = 54,
            eAttack5ISDown      = 55,
            eAttack6            = 56,
            eAttack6Up          = 57,
            eAttack6Down        = 58,
            eAttack6IS          = 59,
            eAttack6ISUp        = 60,
            eAttack6ISDown      = 61,
            eAttack7            = 62,
            eAttack7Up          = 63,
            eAttack7Down        = 64,
            eAttack7IS          = 65,
            eAttack7ISUp        = 66,
            eAttack7ISDown      = 67,
            eAttack8            = 68,
            eAttack8Up          = 69,
            eAttack8Down        = 70,
            eAttack8IS          = 71,
            eAttack8ISUp        = 72,
            eAttack8ISDown      = 73,
            eAttackLoop         = 74,
            eAttackLoopUp       = 75,
            eAttackLoopDown     = 76,
            eAttackLoopIS       = 77,
            eAttackLoopISUp     = 78,
            eAttackLoopISDown   = 79,
            eAttackSpin         = 80,
            eAttackSpinUp       = 81,
            eAttackSpinDown     = 82,
            eAttackSpinIS       = 83,
            eAttackSpinISUp     = 84,
            eAttackSpinISDown   = 85,
            eAttackSpin2        = 86,
            eAttackSpin2Up      = 87,
            eAttackSpin2Down    = 88,
            eAttackSpin2IS      = 89,
            eAttackSpin2ISUp    = 90,
            eAttackSpin2ISDown  = 91,
            eAttackPower        = 92,
            eAttackForwardPower = 93,
            eAttackBackPower    = 94,
            eAttackLeftPower    = 95,
            eAttackRightPower   = 96,
            ePlaceMine          = 97,
            ePlaceMineUp        = 98,
            ePlaceMineDown      = 99,
            ePlaceMineIS        = 100,
            ePlaceMineISUp      = 101,
            ePlaceMineISDown    = 102,
            ePlaceMine2         = 103,
            ePlaceMine2Up       = 104,
            ePlaceMine2Down     = 105,
            ePlaceMine2IS       = 106,
            ePlaceMine2ISUp     = 107,
            ePlaceMine2ISDown   = 108,
            eAttackThrow        = 109,
            eAttackThrowUp      = 110,
            eAttackThrowDown    = 111,
            eAttackThrowIS      = 112,
            eAttackThrowISUp    = 113,
            eAttackThrowISDown  = 114,
            eAttackThrow2       = 115,
            eAttackThrow2Up     = 116,
            eAttackThrow2Down   = 117,
            eAttackThrow2IS     = 118,
            eAttackThrow2ISUp   = 119,
            eAttackThrow2ISDown = 120,
            eAttackThrow3       = 121,
            eAttackThrow3Up     = 122,
            eAttackThrow3Down   = 123,
            eAttackThrow3IS     = 124,
            eAttackThrow3ISUp   = 125,
            eAttackThrow3ISDown = 126,
            eAttackThrow4       = 127,
            eAttackThrow4Up     = 128,
            eAttackThrow4Down   = 129,
            eAttackThrow4IS     = 130,
            eAttackThrow4ISUp   = 131,
            eAttackThrow4ISDown = 132,
            eAttackThrow5       = 133,
            eAttackThrow5Up     = 134,
            eAttackThrow5Down   = 135,
            eAttackThrow5IS     = 136,
            eAttackThrow5ISUp   = 137,
            eAttackThrow5ISDown = 138,
            ePipBoy             = 167,
            ePipBoyChild        = 178,
            eANY                = 255
            };

        enum creatureTypes
            {
            eAnimal = 0,
            eMutatedAnimal,
            eMutatedInsect,
            eAbomination,
            eSuperMutant,
            eFeralGhoul,
            eRobot,
            eGiant
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };

        enum aggressionTypes
            {
            eUnaggressive = 0,
            eAggressive,
            eVeryAggressive,
            eFrenzied
            };

        enum confidenceTypes
            {
            eCowardly = 0,
            eCautious,
            eAverage,
            eBrave,
            eFoolhardy
            };

        enum moodTypes
            {
            eNeutral = 0,
            eAfraid,
            eAnnoyed,
            eCocky,
            eDrugged,
            ePleasant,
            eAngry,
            eSad
            };

        enum assistanceTypes
            {
            eHelpsNobody = 0,
            eHelpsAllies,
            eHelpsFriendsAndAllies
            };

        enum aggroFlags
            {
            fIsAggroRadiusBehavior = 0x01
            };

        enum impactTypes
            {
            eStone = 0,
            eDirt,
            eGrass,
            eGlass,
            eMetal,
            eWood,
            eOrganic,
            eCloth,
            eWater,
            eHollowMetal,
            eOrganicBug,
            eOrganicGlow
            };

        enum servicesFlags
            {
            fIsServicesWeapons   = 0x00000001,
            fIsServicesArmor     = 0x00000002,
            fIsServicesClothing  = 0x00000004,
            fIsServicesBooks     = 0x00000008,
            fIsServicesFood      = 0x00000010,
            fIsServicesChems     = 0x00000020,
            fIsServicesStimpacks = 0x00000040,
            fIsServicesLights    = 0x00000080, // ?
            fIsServicesMiscItems = 0x00000400,
            fIsServicesPotions   = 0x00002000, // ?
            fIsServicesTraining  = 0x00004000,
            fIsServicesRecharge  = 0x00010000,
            fIsServicesRepair    = 0x00020000
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        UnorderedSparseArray<FORMID> SPLO; //Actor Effects
        OptSimpleSubRecord<FORMID> EITM; //Unarmed Attack Effect
        OptSimpleSubRecord<uint16_t> EAMT; //Unarmed Attack Animation
        UnorderedPackedStrings NIFZ; //Model List
        RawRecord NIFT; //Texture Files Hashes
        ReqSubRecord<FNVACBS> ACBS; //Configuration
        UnorderedSparseArray<GENSNAM *> SNAM; //Factions
        OptSimpleSubRecord<FORMID> INAM; //Death item
        OptSimpleSubRecord<FORMID> VTCK; //Voice
        OptSimpleSubRecord<FORMID> TPLT; //Template
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> SCRI; //Script
        UnorderedSparseArray<FNVCNTO *> CNTO;  //Items
        ReqSubRecord<FNVAIDT> AIDT; //AI Data
        OrderedSparseArray<FORMID> PKID; //Packages
        UnorderedPackedStrings KFFZ; //Animations
        ReqSubRecord<CREADATA> DATA; //Data
        OptSimpleSubRecord<uint8_t, 32> RNAM; //Attack reach
        OptSimpleSubRecord<FORMID> ZNAM; //Combat Style
        OptSimpleSubRecord<FORMID> PNAM; //Body Part Data
        SemiOptSimpleFloatSubRecord<flt_0> TNAM; //Turning Speed
        SemiOptSimpleFloatSubRecord<flt_1> BNAM; //Base Scale
        OptSimpleFloatSubRecord<flt_3> WNAM; //Foot Weight
        OptSimpleSubRecord<uint32_t> NAM4; //Impact Material Type
        OptSimpleSubRecord<uint32_t> NAM5; //Sound Level
        OptSimpleSubRecord<FORMID> CSCR; //Inherits Sounds from
        UnorderedSparseArray<CREASoundType *> Types; //Sound Types
        OptSimpleSubRecord<FORMID> CNAM; //Impact Dataset
        OptSimpleSubRecord<FORMID> LNAM; //Melee Weapon List

        CREARecord(unsigned char *_recData=NULL);
        CREARecord(CREARecord *srcRecord);
        ~CREARecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsBiped();
        void   IsBiped(bool value);
        bool   IsEssential();
        void   IsEssential(bool value);
        bool   IsWeaponAndShield();
        void   IsWeaponAndShield(bool value);
        bool   IsRespawn();
        void   IsRespawn(bool value);
        bool   IsSwims();
        void   IsSwims(bool value);
        bool   IsFlies();
        void   IsFlies(bool value);
        bool   IsWalks();
        void   IsWalks(bool value);
        bool   IsPCLevelOffset();
        void   IsPCLevelOffset(bool value);
        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsNoLowLevel();
        void   IsNoLowLevel(bool value);
        bool   IsNoBloodSpray();
        void   IsNoBloodSpray(bool value);
        bool   IsNoBloodDecal();
        void   IsNoBloodDecal(bool value);
        bool   IsNoHead();
        void   IsNoHead(bool value);
        bool   IsNoRightArm();
        void   IsNoRightArm(bool value);
        bool   IsNoLeftArm();
        void   IsNoLeftArm(bool value);
        bool   IsNoCombatInWater();
        void   IsNoCombatInWater(bool value);
        bool   IsNoShadow();
        void   IsNoShadow(bool value);
        bool   IsNoVATSMelee();
        void   IsNoVATSMelee(bool value);
        bool   IsAllowPCDialogue();
        void   IsAllowPCDialogue(bool value);
        bool   IsCantOpenDoors();
        void   IsCantOpenDoors(bool value);
        bool   IsImmobile();
        void   IsImmobile(bool value);
        bool   IsTiltFrontBack();
        void   IsTiltFrontBack(bool value);
        bool   IsTiltLeftRight();
        void   IsTiltLeftRight(bool value);
        bool   IsNoKnockdowns();
        void   IsNoKnockdowns(bool value);
        bool   IsNotPushable();
        void   IsNotPushable(bool value);
        bool   IsAllowPickpocket();
        void   IsAllowPickpocket(bool value);
        bool   IsGhost();
        void   IsGhost(bool value);
        bool   IsNoHeadTracking();
        void   IsNoHeadTracking(bool value);
        bool   IsInvulnerable();
        void   IsInvulnerable(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsUseTraits();
        void   IsUseTraits(bool value);
        bool   IsUseStats();
        void   IsUseStats(bool value);
        bool   IsUseFactions();
        void   IsUseFactions(bool value);
        bool   IsUseAEList();
        void   IsUseAEList(bool value);
        bool   IsUseAIData();
        void   IsUseAIData(bool value);
        bool   IsUseAIPackages();
        void   IsUseAIPackages(bool value);
        bool   IsUseModelAnim();
        void   IsUseModelAnim(bool value);
        bool   IsUseBaseData();
        void   IsUseBaseData(bool value);
        bool   IsUseInventory();
        void   IsUseInventory(bool value);
        bool   IsUseScript();
        void   IsUseScript(bool value);
        bool   IsTemplateFlagMask(uint16_t Mask, bool Exact=false);
        void   SetTemplateFlagMask(uint16_t Mask);

        bool   IsAggroRadiusBehavior();
        void   IsAggroRadiusBehavior(bool value);
        bool   IsAggroFlagMask(uint8_t Mask, bool Exact=false);
        void   SetAggroFlagMask(uint8_t Mask);

        bool   IsServicesWeapons();
        void   IsServicesWeapons(bool value);
        bool   IsServicesArmor();
        void   IsServicesArmor(bool value);
        bool   IsServicesClothing();
        void   IsServicesClothing(bool value);
        bool   IsServicesBooks();
        void   IsServicesBooks(bool value);
        bool   IsServicesFood();
        void   IsServicesFood(bool value);
        bool   IsServicesChems();
        void   IsServicesChems(bool value);
        bool   IsServicesStimpacks();
        void   IsServicesStimpacks(bool value);
        bool   IsServicesLights();
        void   IsServicesLights(bool value);
        bool   IsServicesMiscItems();
        void   IsServicesMiscItems(bool value);
        bool   IsServicesPotions();
        void   IsServicesPotions(bool value);
        bool   IsServicesTraining();
        void   IsServicesTraining(bool value);
        bool   IsServicesRecharge();
        void   IsServicesRecharge(bool value);
        bool   IsServicesRepair();
        void   IsServicesRepair(bool value);
        bool   IsServicesFlagMask(uint32_t Mask, bool Exact=false);
        void   SetServicesFlagMask(uint32_t Mask);

        bool   IsAnimal();
        void   IsAnimal(bool value);
        bool   IsMutatedAnimal();
        void   IsMutatedAnimal(bool value);
        bool   IsMutatedInsect();
        void   IsMutatedInsect(bool value);
        bool   IsAbomination();
        void   IsAbomination(bool value);
        bool   IsSuperMutant();
        void   IsSuperMutant(bool value);
        bool   IsFeralGhoul();
        void   IsFeralGhoul(bool value);
        bool   IsRobot();
        void   IsRobot(bool value);
        bool   IsGiant();
        void   IsGiant(bool value);
        bool   IsType(uint8_t Type);
        void   SetType(uint8_t Type);

        bool   IsAttackLeft();
        void   IsAttackLeft(bool value);
        bool   IsAttackLeftUp();
        void   IsAttackLeftUp(bool value);
        bool   IsAttackLeftDown();
        void   IsAttackLeftDown(bool value);
        bool   IsAttackLeftIS();
        void   IsAttackLeftIS(bool value);
        bool   IsAttackLeftISUp();
        void   IsAttackLeftISUp(bool value);
        bool   IsAttackLeftISDown();
        void   IsAttackLeftISDown(bool value);
        bool   IsAttackRight();
        void   IsAttackRight(bool value);
        bool   IsAttackRightUp();
        void   IsAttackRightUp(bool value);
        bool   IsAttackRightDown();
        void   IsAttackRightDown(bool value);
        bool   IsAttackRightIS();
        void   IsAttackRightIS(bool value);
        bool   IsAttackRightISUp();
        void   IsAttackRightISUp(bool value);
        bool   IsAttackRightISDown();
        void   IsAttackRightISDown(bool value);
        bool   IsAttack3();
        void   IsAttack3(bool value);
        bool   IsAttack3Up();
        void   IsAttack3Up(bool value);
        bool   IsAttack3Down();
        void   IsAttack3Down(bool value);
        bool   IsAttack3IS();
        void   IsAttack3IS(bool value);
        bool   IsAttack3ISUp();
        void   IsAttack3ISUp(bool value);
        bool   IsAttack3ISDown();
        void   IsAttack3ISDown(bool value);
        bool   IsAttack4();
        void   IsAttack4(bool value);
        bool   IsAttack4Up();
        void   IsAttack4Up(bool value);
        bool   IsAttack4Down();
        void   IsAttack4Down(bool value);
        bool   IsAttack4IS();
        void   IsAttack4IS(bool value);
        bool   IsAttack4ISUp();
        void   IsAttack4ISUp(bool value);
        bool   IsAttack4ISDown();
        void   IsAttack4ISDown(bool value);
        bool   IsAttack5();
        void   IsAttack5(bool value);
        bool   IsAttack5Up();
        void   IsAttack5Up(bool value);
        bool   IsAttack5Down();
        void   IsAttack5Down(bool value);
        bool   IsAttack5IS();
        void   IsAttack5IS(bool value);
        bool   IsAttack5ISUp();
        void   IsAttack5ISUp(bool value);
        bool   IsAttack5ISDown();
        void   IsAttack5ISDown(bool value);
        bool   IsAttack6();
        void   IsAttack6(bool value);
        bool   IsAttack6Up();
        void   IsAttack6Up(bool value);
        bool   IsAttack6Down();
        void   IsAttack6Down(bool value);
        bool   IsAttack6IS();
        void   IsAttack6IS(bool value);
        bool   IsAttack6ISUp();
        void   IsAttack6ISUp(bool value);
        bool   IsAttack6ISDown();
        void   IsAttack6ISDown(bool value);
        bool   IsAttack7();
        void   IsAttack7(bool value);
        bool   IsAttack7Up();
        void   IsAttack7Up(bool value);
        bool   IsAttack7Down();
        void   IsAttack7Down(bool value);
        bool   IsAttack7IS();
        void   IsAttack7IS(bool value);
        bool   IsAttack7ISUp();
        void   IsAttack7ISUp(bool value);
        bool   IsAttack7ISDown();
        void   IsAttack7ISDown(bool value);
        bool   IsAttack8();
        void   IsAttack8(bool value);
        bool   IsAttack8Up();
        void   IsAttack8Up(bool value);
        bool   IsAttack8Down();
        void   IsAttack8Down(bool value);
        bool   IsAttack8IS();
        void   IsAttack8IS(bool value);
        bool   IsAttack8ISUp();
        void   IsAttack8ISUp(bool value);
        bool   IsAttack8ISDown();
        void   IsAttack8ISDown(bool value);
        bool   IsAttackLoop();
        void   IsAttackLoop(bool value);
        bool   IsAttackLoopUp();
        void   IsAttackLoopUp(bool value);
        bool   IsAttackLoopDown();
        void   IsAttackLoopDown(bool value);
        bool   IsAttackLoopIS();
        void   IsAttackLoopIS(bool value);
        bool   IsAttackLoopISUp();
        void   IsAttackLoopISUp(bool value);
        bool   IsAttackLoopISDown();
        void   IsAttackLoopISDown(bool value);
        bool   IsAttackSpin();
        void   IsAttackSpin(bool value);
        bool   IsAttackSpinUp();
        void   IsAttackSpinUp(bool value);
        bool   IsAttackSpinDown();
        void   IsAttackSpinDown(bool value);
        bool   IsAttackSpinIS();
        void   IsAttackSpinIS(bool value);
        bool   IsAttackSpinISUp();
        void   IsAttackSpinISUp(bool value);
        bool   IsAttackSpinISDown();
        void   IsAttackSpinISDown(bool value);
        bool   IsAttackSpin2();
        void   IsAttackSpin2(bool value);
        bool   IsAttackSpin2Up();
        void   IsAttackSpin2Up(bool value);
        bool   IsAttackSpin2Down();
        void   IsAttackSpin2Down(bool value);
        bool   IsAttackSpin2IS();
        void   IsAttackSpin2IS(bool value);
        bool   IsAttackSpin2ISUp();
        void   IsAttackSpin2ISUp(bool value);
        bool   IsAttackSpin2ISDown();
        void   IsAttackSpin2ISDown(bool value);
        bool   IsAttackPower();
        void   IsAttackPower(bool value);
        bool   IsAttackForwardPower();
        void   IsAttackForwardPower(bool value);
        bool   IsAttackBackPower();
        void   IsAttackBackPower(bool value);
        bool   IsAttackLeftPower();
        void   IsAttackLeftPower(bool value);
        bool   IsAttackRightPower();
        void   IsAttackRightPower(bool value);
        bool   IsPlaceMine();
        void   IsPlaceMine(bool value);
        bool   IsPlaceMineUp();
        void   IsPlaceMineUp(bool value);
        bool   IsPlaceMineDown();
        void   IsPlaceMineDown(bool value);
        bool   IsPlaceMineIS();
        void   IsPlaceMineIS(bool value);
        bool   IsPlaceMineISUp();
        void   IsPlaceMineISUp(bool value);
        bool   IsPlaceMineISDown();
        void   IsPlaceMineISDown(bool value);
        bool   IsPlaceMine2();
        void   IsPlaceMine2(bool value);
        bool   IsPlaceMine2Up();
        void   IsPlaceMine2Up(bool value);
        bool   IsPlaceMine2Down();
        void   IsPlaceMine2Down(bool value);
        bool   IsPlaceMine2IS();
        void   IsPlaceMine2IS(bool value);
        bool   IsPlaceMine2ISUp();
        void   IsPlaceMine2ISUp(bool value);
        bool   IsPlaceMine2ISDown();
        void   IsPlaceMine2ISDown(bool value);
        bool   IsAttackThrow();
        void   IsAttackThrow(bool value);
        bool   IsAttackThrowUp();
        void   IsAttackThrowUp(bool value);
        bool   IsAttackThrowDown();
        void   IsAttackThrowDown(bool value);
        bool   IsAttackThrowIS();
        void   IsAttackThrowIS(bool value);
        bool   IsAttackThrowISUp();
        void   IsAttackThrowISUp(bool value);
        bool   IsAttackThrowISDown();
        void   IsAttackThrowISDown(bool value);
        bool   IsAttackThrow2();
        void   IsAttackThrow2(bool value);
        bool   IsAttackThrow2Up();
        void   IsAttackThrow2Up(bool value);
        bool   IsAttackThrow2Down();
        void   IsAttackThrow2Down(bool value);
        bool   IsAttackThrow2IS();
        void   IsAttackThrow2IS(bool value);
        bool   IsAttackThrow2ISUp();
        void   IsAttackThrow2ISUp(bool value);
        bool   IsAttackThrow2ISDown();
        void   IsAttackThrow2ISDown(bool value);
        bool   IsAttackThrow3();
        void   IsAttackThrow3(bool value);
        bool   IsAttackThrow3Up();
        void   IsAttackThrow3Up(bool value);
        bool   IsAttackThrow3Down();
        void   IsAttackThrow3Down(bool value);
        bool   IsAttackThrow3IS();
        void   IsAttackThrow3IS(bool value);
        bool   IsAttackThrow3ISUp();
        void   IsAttackThrow3ISUp(bool value);
        bool   IsAttackThrow3ISDown();
        void   IsAttackThrow3ISDown(bool value);
        bool   IsAttackThrow4();
        void   IsAttackThrow4(bool value);
        bool   IsAttackThrow4Up();
        void   IsAttackThrow4Up(bool value);
        bool   IsAttackThrow4Down();
        void   IsAttackThrow4Down(bool value);
        bool   IsAttackThrow4IS();
        void   IsAttackThrow4IS(bool value);
        bool   IsAttackThrow4ISUp();
        void   IsAttackThrow4ISUp(bool value);
        bool   IsAttackThrow4ISDown();
        void   IsAttackThrow4ISDown(bool value);
        bool   IsAttackThrow5();
        void   IsAttackThrow5(bool value);
        bool   IsAttackThrow5Up();
        void   IsAttackThrow5Up(bool value);
        bool   IsAttackThrow5Down();
        void   IsAttackThrow5Down(bool value);
        bool   IsAttackThrow5IS();
        void   IsAttackThrow5IS(bool value);
        bool   IsAttackThrow5ISUp();
        void   IsAttackThrow5ISUp(bool value);
        bool   IsAttackThrow5ISDown();
        void   IsAttackThrow5ISDown(bool value);
        bool   IsPipBoy();
        void   IsPipBoy(bool value);
        bool   IsPipBoyChild();
        void   IsPipBoyChild(bool value);
        bool   IsANY();
        void   IsANY(bool value);
        bool   IsAttackAnimType(uint16_t Type);
        void   SetAttackAnimType(uint16_t Type);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(uint32_t Type);
        void   SetSoundLevelType(uint32_t Type);

        bool   IsUnaggressive();
        void   IsUnaggressive(bool value);
        bool   IsAggressive();
        void   IsAggressive(bool value);
        bool   IsVeryAggressive();
        void   IsVeryAggressive(bool value);
        bool   IsFrenzied();
        void   IsFrenzied(bool value);
        bool   IsAggressionType(uint8_t Type);
        void   SetAggressionType(uint8_t Type);

        bool   IsCowardly();
        void   IsCowardly(bool value);
        bool   IsCautious();
        void   IsCautious(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsBrave();
        void   IsBrave(bool value);
        bool   IsFoolhardy();
        void   IsFoolhardy(bool value);
        bool   IsConfidenceType(uint8_t Type);
        void   SetConfidenceType(uint8_t Type);

        bool   IsNeutral();
        void   IsNeutral(bool value);
        bool   IsAfraid();
        void   IsAfraid(bool value);
        bool   IsAnnoyed();
        void   IsAnnoyed(bool value);
        bool   IsCocky();
        void   IsCocky(bool value);
        bool   IsDrugged();
        void   IsDrugged(bool value);
        bool   IsPleasant();
        void   IsPleasant(bool value);
        bool   IsAngry();
        void   IsAngry(bool value);
        bool   IsSad();
        void   IsSad(bool value);
        bool   IsMoodType(uint8_t Type);
        void   SetMoodType(uint8_t Type);

        bool   IsHelpsNobody();
        void   IsHelpsNobody(bool value);
        bool   IsHelpsAllies();
        void   IsHelpsAllies(bool value);
        bool   IsHelpsFriendsAndAllies();
        void   IsHelpsFriendsAndAllies(bool value);
        bool   IsAssistanceType(uint8_t Type);
        void   SetAssistanceType(uint8_t Type);

        bool   IsStone();
        void   IsStone(bool value);
        bool   IsDirt();
        void   IsDirt(bool value);
        bool   IsGrass();
        void   IsGrass(bool value);
        bool   IsGlass();
        void   IsGlass(bool value);
        bool   IsMetal();
        void   IsMetal(bool value);
        bool   IsWood();
        void   IsWood(bool value);
        bool   IsOrganic();
        void   IsOrganic(bool value);
        bool   IsCloth();
        void   IsCloth(bool value);
        bool   IsWater();
        void   IsWater(bool value);
        bool   IsHollowMetal();
        void   IsHollowMetal(bool value);
        bool   IsOrganicBug();
        void   IsOrganicBug(bool value);
        bool   IsOrganicGlow();
        void   IsOrganicGlow(bool value);
        bool   IsImpactType(uint32_t Type);
        void   SetImpactType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const CREARecord &other) const;
        bool operator !=(const CREARecord &other) const;
        bool equals(Record *other);
    };
}