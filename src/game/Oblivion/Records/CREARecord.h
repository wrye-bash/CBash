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
class CREARecord : public Record //Creature
    {
    private:
        struct CREADATA
            {
            uint8_t   creatureType, combat, magic, stealth, soul;
            uint8_t   unused1;
            uint16_t  health;
            uint8_t   unused2[2];
            uint16_t  attackDamage;
            uint8_t   strength, intelligence, willpower, agility, speed, endurance, personality, luck;

            CREADATA();
            ~CREADATA();

            bool operator ==(const CREADATA &other) const;
            bool operator !=(const CREADATA &other) const;
            };

        struct CREASound //Sound
            {
            ReqSimpleSubRecord<uint32_t> CSDT; //Sound Type
            ReqSimpleSubRecord<FORMID> CSDI; //Sound
            ReqSimpleSubRecord<uint8_t>  CSDC; //Sound Chance

            enum eSoundType
                {
                eLeftFoot      = 0,
                eRightFoot     = 1,
                eLeftBackFoot  = 2,
                eRightBackFoot = 3,
                eIdle          = 4,
                eAware         = 5,
                eAttack        = 6,
                eHit           = 7,
                eDeath         = 8,
                eWeapon        = 9
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
            bool   IsType(uint32_t Type);
            void   SetType(uint32_t Type);

            void   Write(FileWriter &writer);

            bool   operator ==(const CREASound &other) const;
            bool   operator !=(const CREASound &other) const;
            };

        enum flagsFlags
            {
            fIsBiped           = 0x00000001,
            fIsEssential       = 0x00000002,
            fIsWeaponAndShield = 0x00000004,
            fIsRespawn         = 0x00000008,
            fIsSwims           = 0x00000010,
            fIsFlies           = 0x00000020,
            fIsWalks           = 0x00000040,
            fIsPCLevelOffset   = 0x00000080,
            fIsNoLowLevel      = 0x00000200,
            fIsNoBloodSpray    = 0x00000800,
            fIsNoBloodDecal    = 0x00001000,
            //fIsSummonable    = 0x00004000, //OBSE
            fIsNoHead          = 0x00008000,
            fIsNoRightArm      = 0x00010000,
            fIsNoLeftArm       = 0x00020000,
            fIsNoCombatInWater = 0x00040000,
            fIsNoShadow        = 0x00080000,
            fIsNoCorpseCheck   = 0x00100000
            };

        enum servicesFlags
            {
            fWeapons     = 0x00000001,
            fArmor       = 0x00000002,
            fClothing    = 0x00000004,
            fBooks       = 0x00000008,
            fIngredients = 0x00000010,
            fLights      = 0x00000080,
            fApparatus   = 0x00000100,
            fMiscItems   = 0x00000400,
            fSpells      = 0x00000800,
            fMagicItems  = 0x00001000,
            fPotions     = 0x00002000,
            fTraining    = 0x00004000,
            fRecharge    = 0x00010000,
            fRepair      = 0x00020000
            };

        enum eCreatureType
            {
            eCreature = 0,
            eDaedra   = 1,
            eUndead   = 2,
            eHumanoid = 3,
            eHorse    = 4,
            eGiant    = 5
            };

        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model
        UnorderedSparseArray<FORMID> SPLO; //Spells
        UnorderedPackedStrings NIFZ; //Model List
        RawRecord NIFT; //Texture Files Hashes
        ReqSubRecord<GENACBS> ACBS; //Configuration
        UnorderedSparseArray<GENSNAM *> SNAM; //Factions
        OptSimpleSubRecord<FORMID> INAM; //Death item
        OptSimpleSubRecord<FORMID> SCRI; //Script
        UnorderedSparseArray<GENCNTO *> CNTO;  //Items
        ReqSubRecord<GENAIDT> AIDT; //AI Data
        OrderedSparseArray<FORMID> PKID; //Packages
        UnorderedPackedStrings KFFZ; //Animations
        ReqSubRecord<CREADATA> DATA; //Data
        ReqSimpleSubRecord<uint8_t, 32> RNAM; //Attack reach
        OptSimpleSubRecord<FORMID> ZNAM; //Combat Style
        ReqSimpleFloatSubRecord<flt_0> TNAM; //Turning Speed
        ReqSimpleFloatSubRecord<flt_1> BNAM; //Base Scale
        ReqSimpleFloatSubRecord<flt_3> WNAM; //Foot Weight
        OptSimpleSubRecord<FORMID> CSCR; //Sound Template
        StringRecord NAM0; //Blood Spray filename
        StringRecord NAM1; //Blood Decal filename
        UnorderedSparseArray<CREASound *> Sounds; //Sounds

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
        bool   IsNoLowLevel();
        void   IsNoLowLevel(bool value);
        bool   IsLowLevel();
        void   IsLowLevel(bool value);
        bool   IsNoBloodSpray();
        void   IsNoBloodSpray(bool value);
        bool   IsBloodSpray();
        void   IsBloodSpray(bool value);
        bool   IsNoBloodDecal();
        void   IsNoBloodDecal(bool value);
        bool   IsBloodDecal();
        void   IsBloodDecal(bool value);
        bool   IsNoHead();
        void   IsNoHead(bool value);
        bool   IsHead();
        void   IsHead(bool value);
        bool   IsNoRightArm();
        void   IsNoRightArm(bool value);
        bool   IsRightArm();
        void   IsRightArm(bool value);
        bool   IsNoLeftArm();
        void   IsNoLeftArm(bool value);
        bool   IsLeftArm();
        void   IsLeftArm(bool value);
        bool   IsNoCombatInWater();
        void   IsNoCombatInWater(bool value);
        bool   IsCombatInWater();
        void   IsCombatInWater(bool value);
        bool   IsNoShadow();
        void   IsNoShadow(bool value);
        bool   IsShadow();
        void   IsShadow(bool value);
        bool   IsNoCorpseCheck();
        void   IsNoCorpseCheck(bool value);
        bool   IsCorpseCheck();
        void   IsCorpseCheck(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsCreature();
        void   IsCreature(bool value);
        bool   IsDaedra();
        void   IsDaedra(bool value);
        bool   IsUndead();
        void   IsUndead(bool value);
        bool   IsHumanoid();
        void   IsHumanoid(bool value);
        bool   IsHorse();
        void   IsHorse(bool value);
        bool   IsGiant();
        void   IsGiant(bool value);
        bool   IsType(uint8_t Type);
        void   SetType(uint8_t Type);

        bool   IsNoSoul();
        void   IsNoSoul(bool value);
        bool   IsPettySoul();
        void   IsPettySoul(bool value);
        bool   IsLesserSoul();
        void   IsLesserSoul(bool value);
        bool   IsCommonSoul();
        void   IsCommonSoul(bool value);
        bool   IsGreaterSoul();
        void   IsGreaterSoul(bool value);
        bool   IsGrandSoul();
        void   IsGrandSoul(bool value);
        bool   IsSoul(uint8_t Type);
        void   SetSoul(uint8_t Type);

        bool   IsServicesWeapons();
        void   IsServicesWeapons(bool value);
        bool   IsServicesArmor();
        void   IsServicesArmor(bool value);
        bool   IsServicesClothing();
        void   IsServicesClothing(bool value);
        bool   IsServicesBooks();
        void   IsServicesBooks(bool value);
        bool   IsServicesIngredients();
        void   IsServicesIngredients(bool value);
        bool   IsServicesLights();
        void   IsServicesLights(bool value);
        bool   IsServicesApparatus();
        void   IsServicesApparatus(bool value);
        bool   IsServicesMiscItems();
        void   IsServicesMiscItems(bool value);
        bool   IsServicesSpells();
        void   IsServicesSpells(bool value);
        bool   IsServicesMagicItems();
        void   IsServicesMagicItems(bool value);
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