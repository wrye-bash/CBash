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
#include "..\..\..\Common.h"
#include "..\NPC_Record.h"

namespace Ob
{
uint32_t NPC_Record::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return CB_UINT32_FLAG_FIELD;
        case 2: //fid
            return CB_FORMID_FIELD;
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //full
            return CB_STRING_FIELD;
        case 6: //modPath
            return CB_ISTRING_FIELD;
        case 7: //modb
            return CB_FLOAT32_FIELD;
        case 8: //modt_p
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
        case 9: //flags
            return CB_UINT32_FLAG_FIELD;
        case 10: //baseSpell
            return CB_UINT16_FIELD;
        case 11: //fatigue
            return CB_UINT16_FIELD;
        case 12: //barterGold
            return CB_UINT16_FIELD;
        case 13: //level
            return CB_SINT16_FIELD;
        case 14: //calcMin
            return CB_UINT16_FIELD;
        case 15: //calcMax
            return CB_UINT16_FIELD;
        case 16: //factions
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
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //deathItem
            return CB_FORMID_FIELD;
        case 18: //race
            return CB_FORMID_FIELD;
        case 19: //spells
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
        case 20: //script
            return CB_FORMID_FIELD;
        case 21: //items
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
                }

            if(ListIndex >= CNTO.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //item
                    return CB_FORMID_FIELD;
                case 2: //count
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 22: //aggression
            return CB_UINT8_FIELD;
        case 23: //confidence
            return CB_UINT8_FIELD;
        case 24: //energyLevel
            return CB_UINT8_FIELD;
        case 25: //responsibility
            return CB_UINT8_FIELD;
        case 26: //services
            return CB_UINT32_FLAG_FIELD;
        case 27: //trainSkill
            return CB_SINT8_FIELD;
        case 28: //trainLevel
            return CB_UINT8_FIELD;
        case 29: //unused1
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
        case 30: //aiPackages
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
        case 31: //animations
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
        case 32: //iclass
            return CB_FORMID_FIELD;
        case 33: //armorer
            return CB_UINT8_FIELD;
        case 34: //athletics
            return CB_UINT8_FIELD;
        case 35: //blade
            return CB_UINT8_FIELD;
        case 36: //block
            return CB_UINT8_FIELD;
        case 37: //blunt
            return CB_UINT8_FIELD;
        case 38: //h2h
            return CB_UINT8_FIELD;
        case 39: //heavyArmor
            return CB_UINT8_FIELD;
        case 40: //alchemy
            return CB_UINT8_FIELD;
        case 41: //alteration
            return CB_UINT8_FIELD;
        case 42: //conjuration
            return CB_UINT8_FIELD;
        case 43: //destruction
            return CB_UINT8_FIELD;
        case 44: //illusion
            return CB_UINT8_FIELD;
        case 45: //mysticism
            return CB_UINT8_FIELD;
        case 46: //restoration
            return CB_UINT8_FIELD;
        case 47: //acrobatics
            return CB_UINT8_FIELD;
        case 48: //lightArmor
            return CB_UINT8_FIELD;
        case 49: //marksman
            return CB_UINT8_FIELD;
        case 50: //mercantile
            return CB_UINT8_FIELD;
        case 51: //security
            return CB_UINT8_FIELD;
        case 52: //sneak
            return CB_UINT8_FIELD;
        case 53: //speechcraft
            return CB_UINT8_FIELD;
        case 54: //health
            return CB_UINT16_FIELD;
        case 55: //unused2
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
        case 56: //strength
            return CB_UINT8_FIELD;
        case 57: //intelligence
            return CB_UINT8_FIELD;
        case 58: //willpower
            return CB_UINT8_FIELD;
        case 59: //agility
            return CB_UINT8_FIELD;
        case 60: //speed
            return CB_UINT8_FIELD;
        case 61: //endurance
            return CB_UINT8_FIELD;
        case 62: //personality
            return CB_UINT8_FIELD;
        case 63: //luck
            return CB_UINT8_FIELD;
        case 64: //hair
            return CB_FORMID_FIELD;
        case 65: //hairLength
            return CB_FLOAT32_FIELD;
        case 66: //eye
            return CB_FORMID_FIELD;
        case 67: //hairRed
            return CB_UINT8_FIELD;
        case 68: //hairGreen
            return CB_UINT8_FIELD;
        case 69: //hairBlue
            return CB_UINT8_FIELD;
        case 70: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 71: //combatStyle
            return CB_FORMID_FIELD;
        case 72: //fggs_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 73: //fgga_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGA.IsLoaded() ? 120 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 74: //fgts_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGTS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 75: //fnam
            return CB_UINT16_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * NPC_Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //full
            return FULL.value;
        case 6: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 7: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 8: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 9: //flags
            return &ACBS.value.flags;
        case 10: //baseSpell
            return &ACBS.value.baseSpell;
        case 11: //fatigue
            return &ACBS.value.fatigue;
        case 12: //barterGold
            return &ACBS.value.barterGold;
        case 13: //level
            return &ACBS.value.level;
        case 14: //calcMin
            return &ACBS.value.calcMin;
        case 15: //calcMax
            return &ACBS.value.calcMax;
        case 16: //factions
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
        case 17: //deathItem
            return INAM.IsLoaded() ? &INAM.value : NULL;
        case 18: //race
            return RNAM.IsLoaded() ? &RNAM.value : NULL;
        case 19: //spells
            *FieldValues = SPLO.value.size() ? &SPLO.value[0] : NULL;
            return NULL;
        case 20: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 21: //items
            if(ListIndex >= CNTO.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //item
                    return &CNTO.value[ListIndex]->item;
                case 2: //count
                    return &CNTO.value[ListIndex]->count;
                default:
                    return NULL;
                }
            return NULL;
        case 22: //aggression
            return &AIDT.value.aggression;
        case 23: //confidence
            return &AIDT.value.confidence;
        case 24: //energyLevel
            return &AIDT.value.energyLevel;
        case 25: //responsibility
            return &AIDT.value.responsibility;
        case 26: //services
            return &AIDT.value.flags;
        case 27: //trainSkill
            return &AIDT.value.trainSkill;
        case 28: //trainLevel
            return &AIDT.value.trainLevel;
        case 29: //unused1
            *FieldValues = &AIDT.value.unused1[0];
            return NULL;
        case 30: //aiPackages
            *FieldValues = PKID.value.size() ? &PKID.value[0] : NULL;
            return NULL;
        case 31: //animations
            for(uint32_t p = 0;p < KFFZ.value.size();p++)
                FieldValues[p] = KFFZ.value[p];
            return NULL;
        case 32: //iclass
            return &CNAM.value;
        case 33: //armorer
            return &DATA.value.armorer;
        case 34: //athletics
            return &DATA.value.athletics;
        case 35: //blade
            return &DATA.value.blade;
        case 36: //block
            return &DATA.value.block;
        case 37: //blunt
            return &DATA.value.blunt;
        case 38: //h2h
            return &DATA.value.h2h;
        case 39: //heavyArmor
            return &DATA.value.heavyArmor;
        case 40: //alchemy
            return &DATA.value.alchemy;
        case 41: //alteration
            return &DATA.value.alteration;
        case 42: //conjuration
            return &DATA.value.conjuration;
        case 43: //destruction
            return &DATA.value.destruction;
        case 44: //illusion
            return &DATA.value.illusion;
        case 45: //mysticism
            return &DATA.value.mysticism;
        case 46: //restoration
            return &DATA.value.restoration;
        case 47: //acrobatics
            return &DATA.value.acrobatics;
        case 48: //lightArmor
            return &DATA.value.lightArmor;
        case 49: //marksman
            return &DATA.value.marksman;
        case 50: //mercantile
            return &DATA.value.mercantile;
        case 51: //security
            return &DATA.value.security;
        case 52: //sneak
            return &DATA.value.sneak;
        case 53: //speechcraft
            return &DATA.value.speechcraft;
        case 54: //health
            return &DATA.value.health;
        case 55: //unused2
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 56: //strength
            return &DATA.value.strength;
        case 57: //intelligence
            return &DATA.value.intelligence;
        case 58: //willpower
            return &DATA.value.willpower;
        case 59: //agility
            return &DATA.value.agility;
        case 60: //speed
            return &DATA.value.speed;
        case 61: //endurance
            return &DATA.value.endurance;
        case 62: //personality
            return &DATA.value.personality;
        case 63: //luck
            return &DATA.value.luck;
        case 64: //hair
            return HNAM.IsLoaded() ? &HNAM.value : NULL;
        case 65: //hairLength
            return LNAM.IsLoaded() ? LNAM.value : NULL;
        case 66: //eye
            return ENAM.IsLoaded() ? &ENAM.value : NULL;
        case 67: //hairRed
            return &HCLR.value.red;
        case 68: //hairGreen
            return &HCLR.value.green;
        case 69: //hairBlue
            return &HCLR.value.blue;
        case 70: //unused3
            *FieldValues = &HCLR.value.unused1;
            return NULL;
        case 71: //combatStyle
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 72: //fggs_p
            *FieldValues = FGGS.value;
            return NULL;
        case 73: //fgga_p
            *FieldValues = FGGA.value;
            return NULL;
        case 74: //fgts_p
            *FieldValues = FGTS.value;
            return NULL;
        case 75: //fnam
            return &FNAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool NPC_Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 7: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 10: //baseSpell
            ACBS.value.baseSpell = *(uint16_t *)FieldValue;
            break;
        case 11: //fatigue
            ACBS.value.fatigue = *(uint16_t *)FieldValue;
            break;
        case 12: //barterGold
            ACBS.value.barterGold = *(uint16_t *)FieldValue;
            break;
        case 13: //level
            ACBS.value.level = *(int16_t *)FieldValue;
            break;
        case 14: //calcMin
            ACBS.value.calcMin = *(uint16_t *)FieldValue;
            break;
        case 15: //calcMax
            ACBS.value.calcMax = *(uint16_t *)FieldValue;
            break;
        case 16: //factions
            if(ListFieldID == 0) //factionsSize
                {
                SNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= SNAM.value.size())
                break;

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
                    break;
                }
            break;
        case 17: //deathItem
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 18: //race
            RNAM.value = *(FORMID *)FieldValue;
            return true;
        case 19: //spells
            SPLO.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                SPLO.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 20: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 21: //items
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
                    CNTO.value[ListIndex]->item = *(FORMID *)FieldValue;
                    return true;
                case 2: //count
                    CNTO.value[ListIndex]->count = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 22: //aggression
            AIDT.value.aggression = *(uint8_t *)FieldValue;
            break;
        case 23: //confidence
            AIDT.value.confidence = *(uint8_t *)FieldValue;
            break;
        case 24: //energyLevel
            AIDT.value.energyLevel = *(uint8_t *)FieldValue;
            break;
        case 25: //responsibility
            AIDT.value.responsibility = *(uint8_t *)FieldValue;
            break;
        case 26: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 27: //trainSkill
            AIDT.value.trainSkill = *(int8_t *)FieldValue;
            break;
        case 28: //trainLevel
            AIDT.value.trainLevel = *(uint8_t *)FieldValue;
            break;
        case 29: //unused1
            if(ArraySize != 2)
                break;
            AIDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            AIDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 30: //aiPackages
            PKID.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                PKID.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 31: //animations
            KFFZ.Copy((STRINGARRAY)FieldValue, ArraySize);
            break;
        case 32: //iclass
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 33: //armorer
            DATA.value.armorer = *(uint8_t *)FieldValue;
            break;
        case 34: //athletics
            DATA.value.athletics = *(uint8_t *)FieldValue;
            break;
        case 35: //blade
            DATA.value.blade = *(uint8_t *)FieldValue;
            break;
        case 36: //block
            DATA.value.block = *(uint8_t *)FieldValue;
            break;
        case 37: //blunt
            DATA.value.blunt = *(uint8_t *)FieldValue;
            break;
        case 38: //h2h
            DATA.value.h2h = *(uint8_t *)FieldValue;
            break;
        case 39: //heavyArmor
            DATA.value.heavyArmor = *(uint8_t *)FieldValue;
            break;
        case 40: //alchemy
            DATA.value.alchemy = *(uint8_t *)FieldValue;
            break;
        case 41: //alteration
            DATA.value.alteration = *(uint8_t *)FieldValue;
            break;
        case 42: //conjuration
            DATA.value.conjuration = *(uint8_t *)FieldValue;
            break;
        case 43: //destruction
            DATA.value.destruction = *(uint8_t *)FieldValue;
            break;
        case 44: //illusion
            DATA.value.illusion = *(uint8_t *)FieldValue;
            break;
        case 45: //mysticism
            DATA.value.mysticism = *(uint8_t *)FieldValue;
            break;
        case 46: //restoration
            DATA.value.restoration = *(uint8_t *)FieldValue;
            break;
        case 47: //acrobatics
            DATA.value.acrobatics = *(uint8_t *)FieldValue;
            break;
        case 48: //lightArmor
            DATA.value.lightArmor = *(uint8_t *)FieldValue;
            break;
        case 49: //marksman
            DATA.value.marksman = *(uint8_t *)FieldValue;
            break;
        case 50: //mercantile
            DATA.value.mercantile = *(uint8_t *)FieldValue;
            break;
        case 51: //security
            DATA.value.security = *(uint8_t *)FieldValue;
            break;
        case 52: //sneak
            DATA.value.sneak = *(uint8_t *)FieldValue;
            break;
        case 53: //speechcraft
            DATA.value.speechcraft = *(uint8_t *)FieldValue;
            break;
        case 54: //health
            DATA.value.health = *(uint16_t *)FieldValue;
            break;
        case 55: //unused2
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 56: //strength
            DATA.value.strength = *(uint8_t *)FieldValue;
            break;
        case 57: //intelligence
            DATA.value.intelligence = *(uint8_t *)FieldValue;
            break;
        case 58: //willpower
            DATA.value.willpower = *(uint8_t *)FieldValue;
            break;
        case 59: //agility
            DATA.value.agility = *(uint8_t *)FieldValue;
            break;
        case 60: //speed
            DATA.value.speed = *(uint8_t *)FieldValue;
            break;
        case 61: //endurance
            DATA.value.endurance = *(uint8_t *)FieldValue;
            break;
        case 62: //personality
            DATA.value.personality = *(uint8_t *)FieldValue;
            break;
        case 63: //luck
            DATA.value.luck = *(uint8_t *)FieldValue;
            break;
        case 64: //hair
            HNAM.value = *(FORMID *)FieldValue;
            return true;
        case 65: //hairLength
            LNAM.Load();
            *LNAM.value = *(float *)FieldValue;
            break;
        case 66: //eye
            ENAM.value = *(FORMID *)FieldValue;
            return true;
        case 67: //hairRed
            HCLR.value.red = *(uint8_t *)FieldValue;
            break;
        case 68: //hairGreen
            HCLR.value.green = *(uint8_t *)FieldValue;
            break;
        case 69: //hairBlue
            HCLR.value.blue = *(uint8_t *)FieldValue;
            break;
        case 70: //unused3
            if(ArraySize != 1)
                break;
            HCLR.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 71: //combatStyle
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 72: //fggs_p
            if(ArraySize != 200)
                break;
            FGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 73: //fgga_p
            if(ArraySize != 120)
                break;
            FGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 74: //fgts_p
            if(ArraySize != 200)
                break;
            FGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 75: //fnam
            FNAM.value = *(uint16_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void NPC_Record::DeleteField(FIELD_IDENTIFIERS)
    {
    GENAIDT defaultAIDT;
    GENACBS defaultACBS;
    NPC_DATA defaultDATA;
    GENCLR defaultHCLR;

    GENSNAM defaultSNAM;
    GENCNTO defaultCNTO;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //full
            FULL.Unload();
            return;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 9: //flags
            ACBS.value.flags = defaultACBS.flags;
            return;
        case 10: //baseSpell
            ACBS.value.baseSpell = defaultACBS.baseSpell;
            return;
        case 11: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            return;
        case 12: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            return;
        case 13: //level
            ACBS.value.level = defaultACBS.level;
            return;
        case 14: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            return;
        case 15: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            return;
        case 16: //factions
            if(ListFieldID == 0) //factions
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
        case 17: //deathItem
            INAM.Unload();
            return;
        case 18: //race
            RNAM.Unload();
            return;
        case 19: //spells
            SPLO.Unload();
            return;
        case 20: //script
            SCRI.Unload();
            return;
        case 21: //items
            if(ListFieldID == 0) //items
                {
                CNTO.Unload();
                return;
                }

            if(ListIndex >= CNTO.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //item
                    CNTO.value[ListIndex]->item = defaultCNTO.item;
                    return;
                case 2: //count
                    CNTO.value[ListIndex]->count = defaultCNTO.count;
                    return;
                default:
                    return;
                }
            return;
        case 22: //aggression
            AIDT.value.aggression = defaultAIDT.aggression;
            return;
        case 23: //confidence
            AIDT.value.confidence = defaultAIDT.confidence;
            return;
        case 24: //energyLevel
            AIDT.value.confidence = defaultAIDT.confidence;
            return;
        case 25: //responsibility
            AIDT.value.responsibility = defaultAIDT.responsibility;
            return;
        case 26: //services
            AIDT.value.flags = defaultAIDT.flags;
            return;
        case 27: //trainSkill
            AIDT.value.trainSkill = defaultAIDT.trainSkill;
            return;
        case 28: //trainLevel
            AIDT.value.trainLevel = defaultAIDT.trainLevel;
            return;
        case 29: //unused1
            AIDT.value.unused1[0] = defaultAIDT.unused1[0];
            AIDT.value.unused1[1] = defaultAIDT.unused1[1];
            return;
        case 30: //aiPackages
            PKID.Unload();
            return;
        case 31: //animations
            KFFZ.Unload();
            return;
        case 32: //iclass
            CNAM.Unload();
            return;
        case 33: //armorer
            DATA.value.armorer = defaultDATA.armorer;
            return;
        case 34: //athletics
            DATA.value.athletics = defaultDATA.athletics;
            return;
        case 35: //blade
            DATA.value.blade = defaultDATA.blade;
            return;
        case 36: //block
            DATA.value.block = defaultDATA.block;
            return;
        case 37: //blunt
            DATA.value.blunt = defaultDATA.blunt;
            return;
        case 38: //h2h
            DATA.value.h2h = defaultDATA.h2h;
            return;
        case 39: //heavyArmor
            DATA.value.heavyArmor = defaultDATA.heavyArmor;
            return;
        case 40: //alchemy
            DATA.value.alchemy = defaultDATA.alchemy;
            return;
        case 41: //alteration
            DATA.value.alteration = defaultDATA.alteration;
            return;
        case 42: //conjuration
            DATA.value.conjuration = defaultDATA.conjuration;
            return;
        case 43: //destruction
            DATA.value.destruction = defaultDATA.destruction;
            return;
        case 44: //illusion
            DATA.value.illusion = defaultDATA.illusion;
            return;
        case 45: //mysticism
            DATA.value.mysticism = defaultDATA.mysticism;
            return;
        case 46: //restoration
            DATA.value.restoration = defaultDATA.restoration;
            return;
        case 47: //acrobatics
            DATA.value.acrobatics = defaultDATA.acrobatics;
            return;
        case 48: //lightArmor
            DATA.value.lightArmor = defaultDATA.lightArmor;
            return;
        case 49: //marksman
            DATA.value.marksman = defaultDATA.marksman;
            return;
        case 50: //mercantile
            DATA.value.mercantile = defaultDATA.mercantile;
            return;
        case 51: //security
            DATA.value.security = defaultDATA.security;
            return;
        case 52: //sneak
            DATA.value.sneak = defaultDATA.sneak;
            return;
        case 53: //speechcraft
            DATA.value.speechcraft = defaultDATA.speechcraft;
            return;
        case 54: //health
            DATA.value.health = defaultDATA.health;
            return;
        case 55: //unused2
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 56: //strength
            DATA.value.strength = defaultDATA.strength;
            return;
        case 57: //intelligence
            DATA.value.intelligence = defaultDATA.intelligence;
            return;
        case 58: //willpower
            DATA.value.willpower = defaultDATA.willpower;
            return;
        case 59: //agility
            DATA.value.agility = defaultDATA.agility;
            return;
        case 60: //speed
            DATA.value.speed = defaultDATA.speed;
            return;
        case 61: //endurance
            DATA.value.endurance = defaultDATA.endurance;
            return;
        case 62: //personality
            DATA.value.personality = defaultDATA.personality;
            return;
        case 63: //luck
            DATA.value.luck = defaultDATA.luck;
            return;
        case 64: //hair
            HNAM.Unload();
            return;
        case 65: //hairLength
            LNAM.Unload();
            return;
        case 66: //eye
            ENAM.Unload();
            return;
        case 67: //hairRed
            HCLR.value.red = defaultHCLR.red;
            return;
        case 68: //hairGreen
            HCLR.value.green = defaultHCLR.green;
            return;
        case 69: //hairBlue
            HCLR.value.blue = defaultHCLR.blue;
            return;
        case 70: //unused3
            HCLR.value.unused1 = defaultHCLR.unused1;
            return;
        case 71: //combatStyle
            ZNAM.Unload();
            return;
        case 72: //fggs_p
            FGGS.Unload();
            return;
        case 73: //fgga_p
            FGGA.Unload();
            return;
        case 74: //fgts_p
            FGTS.Unload();
            return;
        case 75: //fnam
            FNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}