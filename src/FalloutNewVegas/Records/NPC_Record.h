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
class NPC_Record : public FNVRecord //Non-Player Character
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct NPC_DATA //Data
            {
            int32_t  baseHealth; //Base Health
            uint8_t   strength, perception, endurance,
                    charisma, intelligence,
                    agility, luck;
            //uint8_t unused1; //only present in old record versions

            NPC_DATA();
            ~NPC_DATA();

            bool operator ==(const NPC_DATA &other) const;
            bool operator !=(const NPC_DATA &other) const;
            };
        #pragma pack(pop)

        struct NPC_DNAM //Skill Data
            {
            uint8_t   barter, bigGuns, energy, explosives,
                    lockpick, medicine, melee, repair,
                    science, guns, sneak, speech,
                    survival, unarmed; //Big Guns is obsolete for FNV
            uint8_t   barterBoost, bigGunsBoost, energyBoost, explosivesBoost,
                    lockpickBoost, medicineBoost, meleeBoost, repairBoost,
                    scienceBoost, gunsBoost, sneakBoost, speechBoost,
                    survivalBoost, unarmedBoost; //Big Guns is obsolete for FNV

            NPC_DNAM();
            ~NPC_DNAM();

            bool operator ==(const NPC_DNAM &other) const;
            bool operator !=(const NPC_DNAM &other) const;
            };

        enum flagsFlags
            {
            fIsFemale            = 0x00000001,
            fIsEssential         = 0x00000002,
            fIsCharGenFacePreset = 0x00000004,
            fIsRespawn           = 0x00000008,
            fIsAutoCalcStats     = 0x00000010,
            //fIsFlies           = 0x00000020, // CREA only?
            //fIsWalks           = 0x00000040, // CREA only?
            fIsPCLevelOffset     = 0x00000080,
            fIsUseTemplate       = 0x00000100,
            fIsNoLowLevel        = 0x00000200,
            fIsNoBloodSpray      = 0x00000800,
            fIsNoBloodDecal      = 0x00001000,
            //fIsSummonable      = 0x00004000, //OBSE
            //fIsNoHead          = 0x00008000, // CREA only?
            //fIsNoRightArm      = 0x00010000, // CREA only?
            //fIsNoLeftArm       = 0x00020000, // CREA only?
            //fIsNoCombatInWater = 0x00040000, // CREA only?
            //fIsNoShadow        = 0x00080000, // CREA only?
            fIsNoVATSMelee       = 0x00100000,
            //fIsAllowPCDialogue = 0x00200000, // CREA only?
            fIsCanBeAllRaces     = 0x00400000,
            fIsAutoCalcService   = 0x00800000,
            //fIsTiltFrontBack   = 0x01000000, // CREA only?
            //fIsTiltLeftRight   = 0x02000000, // CREA only?
            fIsNoKnockdowns      = 0x03000000, //3?
            fIsNotPushable       = 0x08000000,
            //fIsAllowPickpocket = 0x10000000, // CREA only?
            //fIsGhost           = 0x20000000, // CREA only?
            fIsNoHeadTracking    = 0x40000000
            //fIsInvulnerable    = 0x80000000 // CREA only?
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
        ReqSubRecord<FNVACBS> ACBS; //Configuration
        UnorderedSparseArray<GENSNAM *> SNAM; //Factions
        OptSimpleSubRecord<FORMID> INAM; //Death item
        OptSimpleSubRecord<FORMID> VTCK; //Voice
        OptSimpleSubRecord<FORMID> TPLT; //Template
        OptSimpleSubRecord<FORMID> RNAM; //Race
        UnorderedSparseArray<FORMID> SPLO; //Actor Effects
        OptSimpleSubRecord<FORMID> EITM; //Unarmed Attack Effect
        OptSimpleSubRecord<uint16_t> EAMT; //Unarmed Attack Animation
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        OptSimpleSubRecord<FORMID> SCRI; //Script
        UnorderedSparseArray<FNVCNTO *> CNTO;  //Items
        OptSubRecord<FNVAIDT> AIDT; //AI Data
        OrderedSparseArray<FORMID> PKID; //Packages
        OptSimpleSubRecord<FORMID> CNAM; //Class
        OptSubRecord<NPC_DATA> DATA; //Data
        OptSubRecord<NPC_DNAM> DNAM; //Skill Data
        UnorderedSparseArray<FORMID> PNAM; //Head Parts
        OptSimpleSubRecord<FORMID> HNAM; //Hair
        SemiOptSimpleFloatSubRecord<flt_0> LNAM; //Hair length
        OptSimpleSubRecord<FORMID> ENAM; //Eyes
        OptSubRecord<GENCLR> HCLR; //Hair Color
        OptSimpleSubRecord<FORMID> ZNAM; //Combat Style
        OptSimpleSubRecord<uint32_t> NAM4; //Impact Material Type
        RawRecord FGGS; //FaceGen Geometry-Symmetric
        RawRecord FGGA; //FaceGen Geometry-Asymmetric
        RawRecord FGTS; //FaceGen Texture-Symmetric
        ReqSimpleSubRecord<uint16_t> NAM5; //Unknown
        SemiOptSimpleFloatSubRecord<flt_0> NAM6; //Height
        SemiOptSimpleFloatSubRecord<flt_0> NAM7; //Weight

        NPC_Record(unsigned char *_recData=NULL);
        NPC_Record(NPC_Record *srcRecord);
        ~NPC_Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsFemale();
        void   IsFemale(bool value);
        bool   IsEssential();
        void   IsEssential(bool value);
        bool   IsCharGenFacePreset();
        void   IsCharGenFacePreset(bool value);
        bool   IsRespawn();
        void   IsRespawn(bool value);
        bool   IsAutoCalcStats();
        void   IsAutoCalcStats(bool value);
        bool   IsPCLevelOffset();
        void   IsPCLevelOffset(bool value);
        bool   IsUseTemplate();
        void   IsUseTemplate(bool value);
        bool   IsNoLowLevel();
        void   IsNoLowLevel(bool value);
        bool   IsNoBloodSpray();
        void   IsNoBloodSpray(bool value);
        bool   IsNoBloodDecal();
        void   IsNoBloodDecal(bool value);
        bool   IsNoVATSMelee();
        void   IsNoVATSMelee(bool value);
        bool   IsCanBeAllRaces();
        void   IsCanBeAllRaces(bool value);
        bool   IsAutoCalcService();
        void   IsAutoCalcService(bool value);
        bool   IsNoKnockdowns();
        void   IsNoKnockdowns(bool value);
        bool   IsNotPushable();
        void   IsNotPushable(bool value);
        bool   IsNoHeadTracking();
        void   IsNoHeadTracking(bool value);
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

        bool operator ==(const NPC_Record &other) const;
        bool operator !=(const NPC_Record &other) const;
        bool equals(Record *other);
    };
}