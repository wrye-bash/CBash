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
class NPC_Record : public Record //Non-Player Character
    {
    private:
        #pragma pack(push)
        #pragma pack(1)
        struct NPC_DATA //Data
            {
            uint8_t   armorer, athletics, blade, block, blunt,
                    h2h, heavyArmor, alchemy, alteration,
                    conjuration, destruction, illusion,
                    mysticism, restoration, acrobatics,
                    lightArmor, marksman, mercantile,
                    security, sneak, speechcraft;
            uint16_t  health;
            uint8_t   unused1[2], strength, intelligence,
                    willpower, agility, speed, endurance,
                    personality, luck;

            NPC_DATA();
            ~NPC_DATA();

            bool operator ==(const NPC_DATA &other) const;
            bool operator !=(const NPC_DATA &other) const;
            };
        #pragma pack(pop)

        enum flagsFlags
            {
            fIsFemale         = 0x00000001,
            fIsEssential      = 0x00000002,
            fIsRespawn        = 0x00000008,
            fIsAutoCalc       = 0x00000010,
            fIsPCLevelOffset  = 0x00000080,
            fIsNoLowLevel     = 0x00000200,
            fIsNoRumors       = 0x00002000,
            fIsSummonable     = 0x00004000,
            fIsNoPersuasion   = 0x00008000,
            fIsCanCorpseCheck = 0x00100000
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

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model
        ReqSubRecord<GENACBS> ACBS; //Configuration
        UnorderedSparseArray<GENSNAM *> SNAM; //Factions
        OptSimpleSubRecord<FORMID> INAM; //Death item
        OptSimpleSubRecord<FORMID, 0x19/*VampireRace*/> RNAM; //Race
        UnorderedSparseArray<FORMID> SPLO; //Spells
        OptSimpleSubRecord<FORMID> SCRI; //Script
        UnorderedSparseArray<GENCNTO *> CNTO; //Items
        ReqSubRecord<GENAIDT> AIDT; //AI Data
        OrderedSparseArray<FORMID> PKID; //Packages
        UnorderedPackedStrings KFFZ; //Animations
        ReqSimpleSubRecord<FORMID> CNAM; //Class
        ReqSubRecord<NPC_DATA> DATA; //Data
        OptSimpleSubRecord<FORMID> HNAM; //Hair
        SemiOptSimpleFloatSubRecord<flt_0> LNAM; //Hair length
        OptSimpleSubRecord<FORMID> ENAM; //Eyes
        ReqSubRecord<GENCLR> HCLR; //Hair Color
        OptSimpleSubRecord<FORMID> ZNAM; //Combat Style
        RawRecord FGGS; //FaceGen Geometry-Symmetric
        RawRecord FGGA; //FaceGen Geometry-Asymmetric
        RawRecord FGTS; //FaceGen Texture-Symmetric
        ReqSimpleSubRecord<uint16_t> FNAM; //Unknown

        NPC_Record(unsigned char *_recData=NULL);
        NPC_Record(NPC_Record *srcRecord);
        ~NPC_Record();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsFemale();
        void   IsFemale(bool value);
        bool   IsMale();
        void   IsMale(bool value);
        bool   IsEssential();
        void   IsEssential(bool value);
        bool   IsRespawn();
        void   IsRespawn(bool value);
        bool   IsAutoCalc();
        void   IsAutoCalc(bool value);
        bool   IsPCLevelOffset();
        void   IsPCLevelOffset(bool value);
        bool   IsNoLowLevel();
        void   IsNoLowLevel(bool value);
        bool   IsLowLevel();
        void   IsLowLevel(bool value);
        bool   IsNoRumors();
        void   IsNoRumors(bool value);
        bool   IsRumors();
        void   IsRumors(bool value);
        bool   IsSummonable();
        void   IsSummonable(bool value);
        bool   IsNoPersuasion();
        void   IsNoPersuasion(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsCanCorpseCheck();
        void   IsCanCorpseCheck(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

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

        bool operator ==(const NPC_Record &other) const;
        bool operator !=(const NPC_Record &other) const;
        bool equals(Record *other);
    };
}