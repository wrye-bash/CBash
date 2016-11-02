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
#include "..\CREARecord.h"

namespace FNV
{
uint32_t CREARecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return CB_UINT32_FLAG_FIELD;
        case 2: //fid
            return CB_FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //formVersion
            return CB_UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 7: //boundX1
            return CB_SINT16_FIELD;
        case 8: //boundY1
            return CB_SINT16_FIELD;
        case 9: //boundZ1
            return CB_SINT16_FIELD;
        case 10: //boundX2
            return CB_SINT16_FIELD;
        case 11: //boundY2
            return CB_SINT16_FIELD;
        case 12: //boundZ2
            return CB_SINT16_FIELD;
        case 13: //full
            return CB_STRING_FIELD;
        case 14: //modPath
            return CB_ISTRING_FIELD;
        case 15: //modb
            return CB_FLOAT32_FIELD;
        case 16: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_STRING_FIELD;
                case 2: //texture
                    return CB_FORMID_FIELD;
                case 3: //index
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }

        case 18: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 19: //actorEffects
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)SPLO.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 20: //unarmedEffect
            return CB_FORMID_FIELD;
        case 21: //unarmedAnim
            return CB_UINT16_TYPE_FIELD;
        case 22: //bodyParts
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_ISTRING_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)NIFZ.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 23: //nift_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NIFT.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 24: //flags
            return CB_UINT32_FLAG_FIELD;
        case 25: //fatigue
            return CB_UINT16_FIELD;
        case 26: //barterGold
            return CB_UINT16_FIELD;
        case 27: //level
            return CB_SINT16_FIELD;
        case 28: //calcMin
            return CB_UINT16_FIELD;
        case 29: //calcMax
            return CB_UINT16_FIELD;
        case 30: //speedMult
            return CB_UINT16_FIELD;
        case 31: //karma
            return CB_FLOAT32_FIELD;
        case 32: //dispBase
            return CB_SINT16_FIELD;
        case 33: //templateFlags
            return CB_UINT16_FLAG_FIELD;
        case 34: //factions
            if(ListFieldID == 0) //factions
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)SNAM.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= SNAM.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //faction
                    return CB_FORMID_FIELD;
                case 2: //rank
                    return CB_UINT8_FIELD;
                case 3: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 3;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 35: //deathItem
            return CB_FORMID_FIELD;
        case 36: //voice
            return CB_FORMID_FIELD;
        case 37: //template
            return CB_FORMID_FIELD;
        case 38: //destructableHealth
            return CB_SINT32_FIELD;
        case 39: //destructableCount
            return CB_UINT8_FIELD;
        case 40: //destructableFlags
            return CB_UINT8_FLAG_FIELD;
        case 41: //destructableUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Destructable.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 42: //destructableStages
            if(!Destructable.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //destructableStages
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Destructable->Stages.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Destructable->Stages.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //health
                    return CB_UINT8_FIELD;
                case 2: //index
                    return CB_UINT8_FIELD;
                case 3: //stage
                    return CB_UINT8_FIELD;
                case 4: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 5: //dps
                    return CB_SINT32_FIELD;
                case 6: //explosion
                    return CB_FORMID_FIELD;
                case 7: //debris
                    return CB_FORMID_FIELD;
                case 8: //debrisCount
                    return CB_SINT32_FIELD;
                case 9: //modPath
                    return CB_ISTRING_FIELD;
                case 10: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 43: //script
            return CB_FORMID_FIELD;
        case 44: //items
            if(ListFieldID == 0) //items
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)CNTO.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= CNTO.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //item
                    return CB_FORMID_FIELD;
                case 2: //count
                    return CB_SINT32_FIELD;
                case 3: //owner
                    return CB_FORMID_FIELD;
                case 4: //globalOrRank
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return CNTO.value[ListIndex]->IsGlobal() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                case 5: //condition
                    return CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 45: //aggression
            return CB_UINT8_TYPE_FIELD;
        case 46: //confidence
            return CB_UINT8_TYPE_FIELD;
        case 47: //energyLevel
            return CB_UINT8_FIELD;
        case 48: //responsibility
            return CB_UINT8_FIELD;
        case 49: //mood
            return CB_UINT8_TYPE_FIELD;
        case 50: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 51: //services
            return CB_UINT32_FLAG_FIELD;
        case 52: //trainSkill
            return CB_SINT8_TYPE_FIELD;
        case 53: //trainLevel
            return CB_UINT8_FIELD;
        case 54: //assistance
            return CB_UINT8_TYPE_FIELD;
        case 55: //aggroFlags
            return CB_UINT8_FLAG_FIELD;
        case 56: //aggroRadius
            return CB_SINT32_FIELD;
        case 57: //aiPackages
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)PKID.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 58: //animations
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_ISTRING_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)KFFZ.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 59: //creatureType
            return CB_UINT8_TYPE_FIELD;
        case 60: //combat
            return CB_UINT8_FIELD;
        case 61: //magic
            return CB_UINT8_FIELD;
        case 62: //stealth
            return CB_UINT8_FIELD;
        case 63: //health
            return CB_UINT16_FIELD;
        case 64: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 65: //attackDamage
            return CB_SINT16_FIELD;
        case 66: //strength
            return CB_UINT8_FIELD;
        case 67: //perception
            return CB_UINT8_FIELD;
        case 68: //endurance
            return CB_UINT8_FIELD;
        case 69: //charisma
            return CB_UINT8_FIELD;
        case 70: //intelligence
            return CB_UINT8_FIELD;
        case 71: //agility
            return CB_UINT8_FIELD;
        case 72: //luck
            return CB_UINT8_FIELD;
        case 73: //attackReach
            return CB_UINT8_FIELD;
        case 74: //combatStyle
            return CB_FORMID_FIELD;
        case 75: //partData
            return CB_FORMID_FIELD;
        case 76: //turningSpeed
            return CB_FLOAT32_FIELD;
        case 77: //baseScale
            return CB_FLOAT32_FIELD;
        case 78: //footWeight
            return CB_FLOAT32_FIELD;
        case 79: //impactType
            return CB_UINT32_TYPE_FIELD;
        case 80: //soundLevel
            return CB_UINT32_FIELD;
        case 81: //inheritsSoundsFrom
            return CB_FORMID_FIELD;
        case 82: //soundTypes
            if(ListFieldID == 0) //soundTypes
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Types.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Types.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //soundType
                    return CB_UINT32_TYPE_FIELD;
                case 2: //sounds
                    if(ListX2FieldID == 0) //sounds
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Types.value[ListIndex]->Sounds.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= Types.value[ListIndex]->Sounds.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return CB_FORMID_FIELD;
                        case 2: //chance
                            return CB_UINT8_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 83: //impactData
            return CB_FORMID_FIELD;
        case 84: //meleeList
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CREARecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 4: //eid
            return EDID.value;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //full
            return FULL.value;
        case 14: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 15: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 16: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 18: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 19: //actorEffects
            *FieldValues = SPLO.IsLoaded() ? &SPLO.value[0] : NULL;
            return NULL;
        case 20: //unarmedEffect
            return &EITM.value;
        case 21: //unarmedAnim
            return &EAMT.value;
        case 22: //bodyParts
            for(uint32_t p = 0;p < NIFZ.value.size();p++)
                FieldValues[p] = NIFZ.value[p];
            return NULL;
        case 23: //nift_p
            *FieldValues = NIFT.value;
            return NULL;
        case 24: //flags
            return &ACBS.value.flags;
        case 25: //fatigue
            return &ACBS.value.fatigue;
        case 26: //barterGold
            return &ACBS.value.barterGold;
        case 27: //level
            return &ACBS.value.level;
        case 28: //calcMin
            return &ACBS.value.calcMin;
        case 29: //calcMax
            return &ACBS.value.calcMax;
        case 30: //speedMult
            return &ACBS.value.speedMult;
        case 31: //karma
            return &ACBS.value.karma;
        case 32: //dispBase
            return &ACBS.value.dispBase;
        case 33: //templateFlags
            return &ACBS.value.templateFlags;
        case 34: //faction
            if(ListIndex >= SNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    return &SNAM.value[ListIndex]->faction;
                case 2: //rank
                    return &SNAM.value[ListIndex]->rank;
                case 3: //unused1
                    *FieldValues = &SNAM.value[ListIndex]->unused1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 35: //deathItem
            return &INAM.value;
        case 36: //voice
            return &VTCK.value;
        case 37: //template
            return &TPLT.value;
        case 38: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 39: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 40: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 41: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 42: //destructableStages
            if(!Destructable.IsLoaded())
                return NULL;

            if(ListIndex >= Destructable->Stages.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //health
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.health;
                case 2: //index
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.index;
                case 3: //stage
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.stage;
                case 4: //flags
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.flags;
                case 5: //dps
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.dps;
                case 6: //explosion
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.explosion;
                case 7: //debris
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debris;
                case 8: //debrisCount
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount;
                case 9: //modPath
                    return Destructable->Stages.value[ListIndex]->DMDL.value;
                case 10: //modt_p
                    *FieldValues = Destructable->Stages.value[ListIndex]->DMDT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 43: //script
            return &SCRI.value;
        case 44: //items
            if(ListIndex >= CNTO.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //item
                    return &CNTO.value[ListIndex]->CNTO.value.item;
                case 2: //count
                    return &CNTO.value[ListIndex]->CNTO.value.count;
                case 3: //owner
                    return CNTO.value[ListIndex]->COED.IsLoaded() ? &CNTO.value[ListIndex]->COED->owner : NULL;
                case 4: //globalOrRank
                    return CNTO.value[ListIndex]->COED.IsLoaded() ? &CNTO.value[ListIndex]->COED->globalOrRank : NULL;
                case 5: //condition
                    return CNTO.value[ListIndex]->COED.IsLoaded() ? &CNTO.value[ListIndex]->COED->condition : NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 45: //aggression
            return &AIDT.value.aggression;
        case 46: //confidence
            return &AIDT.value.confidence;
        case 47: //energyLevel
            return &AIDT.value.energyLevel;
        case 48: //responsibility
            return &AIDT.value.responsibility;
        case 49: //mood
            return &AIDT.value.mood;
        case 50: //unused1
            *FieldValues = &AIDT.value.unused1[0];
            return NULL;
        case 51: //services
            return &AIDT.value.flags;
        case 52: //trainSkill
            return &AIDT.value.trainSkill;
        case 53: //trainLevel
            return &AIDT.value.trainLevel;
        case 54: //assistance
            return &AIDT.value.assistance;
        case 55: //aggroFlags
            return &AIDT.value.aggroFlags;
        case 56: //aggroRadius
            return &AIDT.value.aggroRadius;
        case 57: //aiPackages
            *FieldValues = PKID.IsLoaded() ? &PKID.value[0] : NULL;
            return NULL;
        case 58: //animations
            for(uint32_t p = 0;p < KFFZ.value.size();p++)
                FieldValues[p] = KFFZ.value[p];
            return NULL;
        case 59: //creatureType
            return &DATA.value.creatureType;
        case 60: //combat
            return &DATA.value.combat;
        case 61: //magic
            return &DATA.value.magic;
        case 62: //stealth
            return &DATA.value.stealth;
        case 63: //health
            return &DATA.value.health;
        case 64: //unused2
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 65: //attackDamage
            return &DATA.value.attackDamage;
        case 66: //strength
            return &DATA.value.strength;
        case 67: //perception
            return &DATA.value.perception;
        case 68: //endurance
            return &DATA.value.endurance;
        case 69: //charisma
            return &DATA.value.charisma;
        case 70: //intelligence
            return &DATA.value.intelligence;
        case 71: //agility
            return &DATA.value.agility;
        case 72: //luck
            return &DATA.value.luck;
        case 73: //attackReach
            return &RNAM.value;
        case 74: //combatStyle
            return &ZNAM.value;
        case 75: //partData
            return &PNAM.value;
        case 76: //turningSpeed
            return TNAM.value;
        case 77: //baseScale
            return BNAM.value;
        case 78: //footWeight
            return &WNAM.value;
        case 79: //impactType
            return &NAM4.value;
        case 80: //soundLevel
            return &NAM5.value;
        case 81: //inheritsSoundsFrom
            return &CSCR.value;
        case 82: //soundTypes
            if(ListIndex >= Types.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //soundType
                    return &Types.value[ListIndex]->CSDT.value;
                case 2: //sounds
                    if(ListX2Index >= Types.value[ListIndex]->Sounds.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return &Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDI.value;
                        case 2: //chance
                            return &Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDC.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 83: //impactData
            return &CNAM.value;
        case 84: //meleeList
            return &LNAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool CREARecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(uint16_t *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //boundX1
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(int16_t *)FieldValue;
            break;
        case 13: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 14: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 15: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 16: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 18: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 19: //actorEffects
            SPLO.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                SPLO.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 20: //unarmedEffect
            EITM.value = *(FORMID *)FieldValue;
            return true;
        case 21: //unarmedAnim
            SetAttackAnimType(*(uint16_t *)FieldValue);
            break;
        case 22: //bodyParts
            NIFZ.Copy((STRINGARRAY)FieldValue, ArraySize);
            break;
        case 23: //nift_p
            NIFT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 24: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 25: //fatigue
            ACBS.value.fatigue = *(uint16_t *)FieldValue;
            break;
        case 26: //barterGold
            ACBS.value.barterGold = *(uint16_t *)FieldValue;
            break;
        case 27: //level
            ACBS.value.level = *(int16_t *)FieldValue;
            break;
        case 28: //calcMin
            ACBS.value.calcMin = *(uint16_t *)FieldValue;
            break;
        case 29: //calcMax
            ACBS.value.calcMax = *(uint16_t *)FieldValue;
            break;
        case 30: //speedMult
            ACBS.value.speedMult = *(uint16_t *)FieldValue;
            break;
        case 31: //karma
            ACBS.value.karma = *(float *)FieldValue;
            break;
        case 32: //dispBase
            ACBS.value.dispBase = *(int16_t *)FieldValue;
            break;
        case 33: //templateFlags
            SetTemplateFlagMask(*(uint16_t *)FieldValue);
            break;
        case 34: //factions
            if(ListFieldID == 0) //altTexturesSize
                {
                SNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= SNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    SNAM.value[ListIndex]->faction = *(FORMID *)FieldValue;
                    return true;
                case 2: //rank
                    SNAM.value[ListIndex]->rank = *(uint8_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 3)
                        break;
                    SNAM.value[ListIndex]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    SNAM.value[ListIndex]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    SNAM.value[ListIndex]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                default:
                    return NULL;
                }
            return NULL;
        case 35: //deathItem
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 36: //voice
            VTCK.value = *(FORMID *)FieldValue;
            return true;
        case 37: //template
            TPLT.value = *(FORMID *)FieldValue;
            return true;
        case 38: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(int32_t *)FieldValue;
            break;
        case 39: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(uint8_t *)FieldValue;
            break;
        case 40: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 41: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 42: //destructableStages
            Destructable.Load();
            if(ListFieldID == 0) //destructableStagesSize
                {
                Destructable->Stages.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Destructable->Stages.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //health
                    Destructable->Stages.value[ListIndex]->DSTD.value.health = *(uint8_t *)FieldValue;
                    break;
                case 2: //index
                    Destructable->Stages.value[ListIndex]->DSTD.value.index = *(uint8_t *)FieldValue;
                    break;
                case 3: //stage
                    Destructable->Stages.value[ListIndex]->DSTD.value.stage = *(uint8_t *)FieldValue;
                    break;
                case 4: //flags
                    Destructable->Stages.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 5: //dps
                    Destructable->Stages.value[ListIndex]->DSTD.value.dps = *(int32_t *)FieldValue;
                    break;
                case 6: //explosion
                    Destructable->Stages.value[ListIndex]->DSTD.value.explosion = *(FORMID *)FieldValue;
                    return true;
                case 7: //debris
                    Destructable->Stages.value[ListIndex]->DSTD.value.debris = *(FORMID *)FieldValue;
                    return true;
                case 8: //debrisCount
                    Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = *(int32_t *)FieldValue;
                    break;
                case 9: //modPath
                    Destructable->Stages.value[ListIndex]->DMDL.Copy((char *)FieldValue);
                    break;
                case 10: //modt_p
                    Destructable->Stages.value[ListIndex]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 43: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 44: //items
            if(ListFieldID == 0) //itemsSize
                {
                CNTO.resize(ArraySize);
                return false;
                }

            if(ListIndex >= CNTO.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //item
                    CNTO.value[ListIndex]->CNTO.value.item = *(FORMID *)FieldValue;
                    return true;
                case 2: //count
                    CNTO.value[ListIndex]->CNTO.value.count = *(int32_t *)FieldValue;
                    break;
                case 3: //owner
                    CNTO.value[ListIndex]->COED.Load();
                    CNTO.value[ListIndex]->COED->owner = *(FORMID *)FieldValue;
                    return true;
                case 4: //globalOrRank
                    CNTO.value[ListIndex]->COED.Load();
                    CNTO.value[ListIndex]->COED->globalOrRank = *(FORMID_OR_UINT32 *)FieldValue;
                    return true;
                case 5: //condition
                    CNTO.value[ListIndex]->COED.Load();
                    CNTO.value[ListIndex]->COED->condition = *(float *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 45: //aggression
            SetAggressionType(*(uint8_t *)FieldValue);
            break;
        case 46: //confidence
            SetConfidenceType(*(uint8_t *)FieldValue);
            break;
        case 47: //energyLevel
            AIDT.value.energyLevel = *(uint8_t *)FieldValue;
            break;
        case 48: //responsibility
            AIDT.value.responsibility = *(uint8_t *)FieldValue;
            break;
        case 49: //mood
            SetMoodType(*(uint8_t *)FieldValue);
            break;
        case 50: //unused1
            if(ArraySize != 3)
                break;
            AIDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            AIDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            AIDT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 51: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 52: //trainSkill
            AIDT.value.trainSkill = *(int8_t *)FieldValue;
            break;
        case 53: //trainLevel
            AIDT.value.trainLevel = *(uint8_t *)FieldValue;
            break;
        case 54: //assistance
            SetAssistanceType(*(uint8_t *)FieldValue);
            break;
        case 55: //aggroFlags
            SetAggroFlagMask(*(uint8_t *)FieldValue);
            break;
        case 56: //aggroRadius
            AIDT.value.aggroRadius = *(int32_t *)FieldValue;
            break;
        case 57: //aiPackages
            PKID.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                PKID.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 58: //animations
            KFFZ.Copy((STRINGARRAY)FieldValue, ArraySize);
            break;
        case 59: //creatureType
            SetType(*(uint8_t *)FieldValue);
            break;
        case 60: //combat
            DATA.value.combat = *(uint8_t *)FieldValue;
            break;
        case 61: //magic
            DATA.value.magic = *(uint8_t *)FieldValue;
            break;
        case 62: //stealth
            DATA.value.stealth = *(uint8_t *)FieldValue;
            break;
        case 63: //health
            DATA.value.health = *(uint16_t *)FieldValue;
            break;
        case 64: //unused2
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 65: //attackDamage
            DATA.value.attackDamage = *(int16_t *)FieldValue;
            break;
        case 66: //strength
            DATA.value.strength = *(uint8_t *)FieldValue;
            break;
        case 67: //perception
            DATA.value.perception = *(uint8_t *)FieldValue;
            break;
        case 68: //endurance
            DATA.value.endurance = *(uint8_t *)FieldValue;
            break;
        case 69: //charisma
            DATA.value.charisma = *(uint8_t *)FieldValue;
            break;
        case 70: //intelligence
            DATA.value.intelligence = *(uint8_t *)FieldValue;
            break;
        case 71: //agility
            DATA.value.agility = *(uint8_t *)FieldValue;
            break;
        case 72: //luck
            DATA.value.luck = *(uint8_t *)FieldValue;
            break;
        case 73: //attackReach
            RNAM.value = *(uint8_t *)FieldValue;
            break;
        case 74: //combatStyle
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 75: //partData
            PNAM.value = *(FORMID *)FieldValue;
            return true;
        case 76: //turningSpeed
            TNAM.Load();
            *TNAM.value = *(float *)FieldValue;
            break;
        case 77: //baseScale
            BNAM.Load();
            *BNAM.value = *(float *)FieldValue;
            break;
        case 78: //footWeight
            WNAM.value = *(float *)FieldValue;
            break;
        case 79: //impactType
            SetImpactType(*(uint32_t *)FieldValue);
            break;
        case 80: //soundLevel
            SetSoundLevelType(*(uint32_t *)FieldValue);
            break;
        case 81: //inheritsSoundsFrom
            CSCR.value = *(FORMID *)FieldValue;
            return true;
        case 82: //soundTypes
            if(ListFieldID == 0) //soundTypesSize
                {
                Types.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Types.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //soundType
                    Types.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    break;
                case 2: //sounds
                    if(ListX2FieldID == 0) //soundTypesSize
                        {
                        Types.value[ListIndex]->Sounds.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Types.value[ListIndex]->Sounds.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDI.value = *(FORMID *)FieldValue;
                            return true;
                        case 2: //chance
                            Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDC.value = *(uint8_t *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 83: //impactData
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 84: //meleeList
            LNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CREARecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    FNVACBS defaultACBS;
    GENSNAM defaultSNAM;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    GENCNTO defaultCNTO;
    GENCOED defaultCOED;
    FNVAIDT defaultAIDT;
    CREADATA defaultDATA;
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //full
            FULL.Unload();
            return;
        case 14: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 15: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 16: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 17: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 18: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 19: //actorEffects
            SPLO.Unload();
            return;
        case 20: //unarmedEffect
            EITM.Unload();
            return;
        case 21: //unarmedAnim
            EAMT.Unload();
            return;
        case 22: //bodyParts
            NIFZ.Unload();
            return;
        case 23: //nift_p
            NIFT.Unload();
            return;
        case 24: //flags
            SetFlagMask(defaultACBS.flags);
            return;
        case 25: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            return;
        case 26: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            return;
        case 27: //level
            ACBS.value.level = defaultACBS.level;
            return;
        case 28: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            return;
        case 29: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            return;
        case 30: //speedMult
            ACBS.value.speedMult = defaultACBS.speedMult;
            return;
        case 31: //karma
            ACBS.value.karma = defaultACBS.karma;
            return;
        case 32: //dispBase
            ACBS.value.dispBase = defaultACBS.dispBase;
            return;
        case 33: //templateFlags
            SetTemplateFlagMask(defaultACBS.templateFlags);
            return;
        case 34: //factions
            if(ListFieldID == 0) //altTexturesSize
                {
                SNAM.Unload();
                return;
                }

            if(ListIndex >= SNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //faction
                    SNAM.value[ListIndex]->faction = defaultSNAM.faction;
                    return;
                case 2: //rank
                    SNAM.value[ListIndex]->rank = defaultSNAM.rank;
                    return;
                case 3: //unused1
                    SNAM.value[ListIndex]->unused1[0] = defaultSNAM.unused1[0];
                    SNAM.value[ListIndex]->unused1[1] = defaultSNAM.unused1[1];
                    SNAM.value[ListIndex]->unused1[2] = defaultSNAM.unused1[2];
                    return;
                default:
                    return;
                }
            return;
        case 35: //deathItem
            INAM.Unload();
            return;
        case 36: //voice
            VTCK.Unload();
            return;
        case 37: //template
            TPLT.Unload();
            return;
        case 38: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 39: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 40: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 41: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 42: //destructableStages
            if(Destructable.IsLoaded())
                {
                if(ListFieldID == 0) //destructableStages
                    {
                    Destructable->Stages.Unload();
                    return;
                    }

                if(ListIndex >= Destructable->Stages.value.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //health
                        Destructable->Stages.value[ListIndex]->DSTD.value.health = defaultDSTD.health;
                        return;
                    case 2: //index
                        Destructable->Stages.value[ListIndex]->DSTD.value.index = defaultDSTD.index;
                        return;
                    case 3: //stage
                        Destructable->Stages.value[ListIndex]->DSTD.value.stage = defaultDSTD.stage;
                        return;
                    case 4: //flags
                        Destructable->Stages.value[ListIndex]->SetFlagMask(defaultDSTD.flags);
                        return;
                    case 5: //dps
                        Destructable->Stages.value[ListIndex]->DSTD.value.dps = defaultDSTD.dps;
                        return;
                    case 6: //explosion
                        Destructable->Stages.value[ListIndex]->DSTD.value.explosion = defaultDSTD.explosion;
                        return;
                    case 7: //debris
                        Destructable->Stages.value[ListIndex]->DSTD.value.debris = defaultDSTD.debris;
                        return;
                    case 8: //debrisCount
                        Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = defaultDSTD.debrisCount;
                        return;
                    case 9: //modPath
                        Destructable->Stages.value[ListIndex]->DMDL.Unload();
                        return;
                    case 10: //modt_p
                        Destructable->Stages.value[ListIndex]->DMDT.Unload();
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 43: //script
            SCRI.Unload();
            return;
        case 44: //items
            if(ListFieldID == 0) //itemsSize
                {
                CNTO.Unload();
                return;
                }

            if(ListIndex >= CNTO.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //item
                    CNTO.value[ListIndex]->CNTO.value.item = defaultCNTO.item;
                    return;
                case 2: //count
                    CNTO.value[ListIndex]->CNTO.value.count = defaultCNTO.count;
                    return;
                case 3: //owner
                    if(CNTO.value[ListIndex]->COED.IsLoaded())
                        CNTO.value[ListIndex]->COED->owner = defaultCOED.owner;
                    return;
                case 4: //globalOrRank
                    if(CNTO.value[ListIndex]->COED.IsLoaded())
                        CNTO.value[ListIndex]->COED->globalOrRank = defaultCOED.globalOrRank;
                    return;
                case 5: //condition
                    if(CNTO.value[ListIndex]->COED.IsLoaded())
                        CNTO.value[ListIndex]->COED->condition = defaultCOED.condition;
                    return;
                default:
                    return;
                }
            return;
        case 45: //aggression
            SetAggressionType(defaultAIDT.aggression);
            return;
        case 46: //confidence
            SetConfidenceType(defaultAIDT.confidence);
            return;
        case 47: //energyLevel
            AIDT.value.energyLevel = defaultAIDT.energyLevel;
            return;
        case 48: //responsibility
            AIDT.value.responsibility = defaultAIDT.responsibility;
            return;
        case 49: //mood
            SetMoodType(defaultAIDT.mood);
            return;
        case 50: //unused1
            AIDT.value.unused1[0] = defaultAIDT.unused1[0];
            AIDT.value.unused1[1] = defaultAIDT.unused1[1];
            AIDT.value.unused1[2] = defaultAIDT.unused1[2];
            return;
        case 51: //services
            SetServicesFlagMask(defaultAIDT.flags);
            return;
        case 52: //trainSkill
            AIDT.value.trainSkill = defaultAIDT.trainSkill;
            return;
        case 53: //trainLevel
            AIDT.value.trainLevel = defaultAIDT.trainLevel;
            return;
        case 54: //assistance
            SetAssistanceType(defaultAIDT.assistance);
            return;
        case 55: //aggroFlags
            SetAggroFlagMask(defaultAIDT.aggroFlags);
            return;
        case 56: //aggroRadius
            AIDT.value.aggroRadius = defaultAIDT.aggroRadius;
            return;
        case 57: //aiPackages
            PKID.Unload();
            return;
        case 58: //animations
            KFFZ.Unload();
            return;
        case 59: //creatureType
            SetType(defaultDATA.creatureType);
            return;
        case 60: //combat
            DATA.value.combat = defaultDATA.combat;
            return;
        case 61: //magic
            DATA.value.magic = defaultDATA.magic;
            return;
        case 62: //stealth
            DATA.value.stealth = defaultDATA.stealth;
            return;
        case 63: //health
            DATA.value.health = defaultDATA.health;
            return;
        case 64: //unused2
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 65: //attackDamage
            DATA.value.attackDamage = defaultDATA.attackDamage;
            return;
        case 66: //strength
            DATA.value.strength = defaultDATA.strength;
            return;
        case 67: //perception
            DATA.value.perception = defaultDATA.perception;
            return;
        case 68: //endurance
            DATA.value.endurance = defaultDATA.endurance;
            return;
        case 69: //charisma
            DATA.value.charisma = defaultDATA.charisma;
            return;
        case 70: //intelligence
            DATA.value.intelligence = defaultDATA.intelligence;
            return;
        case 71: //agility
            DATA.value.agility = defaultDATA.agility;
            return;
        case 72: //luck
            DATA.value.luck = defaultDATA.luck;
            return;
        case 73: //attackReach
            RNAM.Unload();
            return;
        case 74: //combatStyle
            ZNAM.Unload();
            return;
        case 75: //partData
            PNAM.Unload();
            return;
        case 76: //turningSpeed
            TNAM.Unload();
            return;
        case 77: //baseScale
            BNAM.Unload();
            return;
        case 78: //footWeight
            WNAM.Unload();
            return;
        case 79: //impactType
            NAM4.Unload();
            return;
        case 80: //soundLevel
            NAM5.Unload();
            return;
        case 81: //inheritsSoundsFrom
            CSCR.Unload();
            return;
        case 82: //soundTypes
            if(ListFieldID == 0) //soundTypesSize
                {
                Types.Unload();
                return;
                }

            if(ListIndex >= Types.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //soundType
                    Types.value[ListIndex]->CSDT.Unload();
                    return;
                case 2: //sounds
                    if(ListX2FieldID == 0) //soundTypesSize
                        {
                        Types.value[ListIndex]->Sounds.Unload();
                        return;
                        }

                    if(ListX2Index >= Types.value[ListIndex]->Sounds.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDI.Unload();
                            return;
                        case 2: //chance
                            Types.value[ListIndex]->Sounds.value[ListX2Index]->CSDC.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 83: //impactData
            CNAM.Unload();
            return;
        case 84: //meleeList
            LNAM.Unload();
            return;
        default:
            return;
        }
    }
}