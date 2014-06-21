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
#include "..\CREARecord.h"

namespace Ob
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
        case 9: //spells
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
        case 10: //bodyParts
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
        case 11: //nift_p
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
        case 12: //flags
            return CB_UINT32_FLAG_FIELD;
        case 13: //baseSpell
            return CB_UINT16_FIELD;
        case 14: //fatigue
            return CB_UINT16_FIELD;
        case 15: //barterGold
            return CB_UINT16_FIELD;
        case 16: //level
            return CB_SINT16_FIELD;
        case 17: //calcMin
            return CB_UINT16_FIELD;
        case 18: //calcMax
            return CB_UINT16_FIELD;
        case 19: //factions
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
        case 20: //deathItem
            return CB_FORMID_FIELD;
        case 21: //script
            return CB_FORMID_FIELD;
        case 22: //items
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
        case 23: //aggression
            return CB_UINT8_FIELD;
        case 24: //confidence
            return CB_UINT8_FIELD;
        case 25: //energyLevel
            return CB_UINT8_FIELD;
        case 26: //responsibility
            return CB_UINT8_FIELD;
        case 27: //services
            return CB_UINT32_FLAG_FIELD;
        case 28: //trainSkill
            return CB_SINT8_FIELD;
        case 29: //trainLevel
            return CB_UINT8_FIELD;
        case 30: //unused1
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
        case 31: //aiPackages
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
        case 32: //animations
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
        case 33: //creatureType
            return CB_UINT8_TYPE_FIELD;
        case 34: //combat
            return CB_UINT8_FIELD;
        case 35: //magic
            return CB_UINT8_FIELD;
        case 36: //stealth
            return CB_UINT8_FIELD;
        case 37: //soulType
            return CB_UINT8_TYPE_FIELD;
        case 38: //unused2
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
        case 39: //health
            return CB_UINT16_FIELD;
        case 40: //unused3
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
        case 41: //attackDamage
            return CB_UINT16_FIELD;
        case 42: //strength
            return CB_UINT8_FIELD;
        case 43: //intelligence
            return CB_UINT8_FIELD;
        case 44: //willpower
            return CB_UINT8_FIELD;
        case 45: //agility
            return CB_UINT8_FIELD;
        case 46: //speed
            return CB_UINT8_FIELD;
        case 47: //endurance
            return CB_UINT8_FIELD;
        case 48: //personality
            return CB_UINT8_FIELD;
        case 49: //luck
            return CB_UINT8_FIELD;
        case 50: //attackReach
            return CB_UINT8_FIELD;
        case 51: //combatStyle
            return CB_FORMID_FIELD;
        case 52: //turningSpeed
            return CB_FLOAT32_FIELD;
        case 53: //baseScale
            return CB_FLOAT32_FIELD;
        case 54: //footWeight
            return CB_FLOAT32_FIELD;
        case 55: //inheritsSoundsFrom
            return CB_FORMID_FIELD;
        case 56: //bloodSprayPath
            return CB_ISTRING_FIELD;
        case 57: //bloodDecalPath
            return CB_ISTRING_FIELD;
        case 58: //sounds
            if(ListFieldID == 0) //sounds
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Sounds.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Sounds.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //soundType
                    return CB_UINT32_FIELD;
                case 2: //sound
                    return CB_FORMID_FIELD;
                case 3: //chance
                    return CB_UINT8_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
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
        case 9: //spells
            *FieldValues = SPLO.value.size() ? &SPLO.value[0] : NULL;
            return NULL;
        case 10: //bodyParts
            for(uint32_t p = 0;p < NIFZ.value.size();p++)
                FieldValues[p] = NIFZ.value[p];
            return NULL;
        case 11: //nift_p
            *FieldValues = NIFT.value;
            return NULL;
        case 12: //flags
            return &ACBS.value.flags;
        case 13: //baseSpell
            return &ACBS.value.baseSpell;
        case 14: //fatigue
            return &ACBS.value.fatigue;
        case 15: //barterGold
            return &ACBS.value.barterGold;
        case 16: //level
            return &ACBS.value.level;
        case 17: //calcMin
            return &ACBS.value.calcMin;
        case 18: //calcMax
            return &ACBS.value.calcMax;
        case 19: //factions
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
        case 20: //deathItem
            return INAM.IsLoaded() ? &INAM.value : NULL;
        case 21: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 22: //items
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
        case 23: //aggression
            return &AIDT.value.aggression;
        case 24: //confidence
            return &AIDT.value.confidence;
        case 25: //energyLevel
            return &AIDT.value.energyLevel;
        case 26: //responsibility
            return &AIDT.value.responsibility;
        case 27: //services
            return &AIDT.value.flags;
        case 28: //trainSkill
            return &AIDT.value.trainSkill;
        case 29: //trainLevel
            return &AIDT.value.trainLevel;
        case 30: //unused1
            *FieldValues = &AIDT.value.unused1[0];
            return NULL;
        case 31: //aiPackages
            *FieldValues = PKID.value.size() ? &PKID.value[0] : NULL;
            return NULL;
        case 32: //animations
            for(uint32_t p = 0;p < KFFZ.value.size();p++)
                FieldValues[p] = KFFZ.value[p];
            return NULL;
        case 33: //creatureType
            return &DATA.value.creatureType;
        case 34: //combat
            return &DATA.value.combat;
        case 35: //magic
            return &DATA.value.magic;
        case 36: //stealth
            return &DATA.value.stealth;
        case 37: //soulType
            return &DATA.value.soul;
        case 38: //unused2
            *FieldValues = &DATA.value.unused1;
            return NULL;
        case 39: //health
            return &DATA.value.health;
        case 40: //unused3
            *FieldValues = &DATA.value.unused2[0];
            return NULL;
        case 41: //attackDamage
            return &DATA.value.attackDamage;
        case 42: //strength
            return &DATA.value.strength;
        case 43: //intelligence
            return &DATA.value.intelligence;
        case 44: //willpower
            return &DATA.value.willpower;
        case 45: //agility
            return &DATA.value.agility;
        case 46: //speed
            return &DATA.value.speed;
        case 47: //endurance
            return &DATA.value.endurance;
        case 48: //personality
            return &DATA.value.personality;
        case 49: //luck
            return &DATA.value.luck;
        case 50: //attackReach
            return &RNAM.value;
        case 51: //combatStyle
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 52: //turningSpeed
            return &TNAM.value;
        case 53: //baseScale
            return &BNAM.value;
        case 54: //footWeight
            return &WNAM.value;
        case 55: //inheritsSoundsFrom
            return CSCR.IsLoaded() ? &CSCR.value : NULL;
        case 56: //bloodSprayPath
            return NAM0.value;
        case 57: //bloodDecalPath
            return NAM1.value;
        case 58: //sounds
            if(ListIndex >= Sounds.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //soundType
                    return &Sounds.value[ListIndex]->CSDT.value;
                case 2: //sound
                    return &Sounds.value[ListIndex]->CSDI.value;
                case 3: //chance
                    return &Sounds.value[ListIndex]->CSDC.value;
                default:
                    return NULL;
                }
            return NULL;
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
        case 9: //spells
            SPLO.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                SPLO.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 10: //bodyParts
            NIFZ.Copy((STRINGARRAY)FieldValue, ArraySize);
            break;
        case 11: //nift_p
            NIFT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 12: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 13: //baseSpell
            ACBS.value.baseSpell = *(uint16_t *)FieldValue;
            break;
        case 14: //fatigue
            ACBS.value.fatigue = *(uint16_t *)FieldValue;
            break;
        case 15: //barterGold
            ACBS.value.barterGold = *(uint16_t *)FieldValue;
            break;
        case 16: //level
            ACBS.value.level = *(int16_t *)FieldValue;
            break;
        case 17: //calcMin
            ACBS.value.calcMin = *(uint16_t *)FieldValue;
            break;
        case 18: //calcMax
            ACBS.value.calcMax = *(uint16_t *)FieldValue;
            break;
        case 19: //factions
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
        case 20: //deathItem
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 21: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 22: //items
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
        case 23: //aggression
            AIDT.value.aggression = *(uint8_t *)FieldValue;
            break;
        case 24: //confidence
            AIDT.value.confidence = *(uint8_t *)FieldValue;
            break;
        case 25: //energyLevel
            AIDT.value.energyLevel = *(uint8_t *)FieldValue;
            break;
        case 26: //responsibility
            AIDT.value.responsibility = *(uint8_t *)FieldValue;
            break;
        case 27: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 28: //trainSkill
            AIDT.value.trainSkill = *(int8_t *)FieldValue;
            break;
        case 29: //trainLevel
            AIDT.value.trainLevel = *(uint8_t *)FieldValue;
            break;
        case 30: //unused1
            if(ArraySize != 2)
                break;
            AIDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            AIDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 31: //aiPackages
            PKID.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                PKID.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 32: //animations
            KFFZ.Copy((STRINGARRAY)FieldValue, ArraySize);
            break;
        case 33: //creatureType
            SetType(*(uint8_t *)FieldValue);
            break;
        case 34: //combat
            DATA.value.combat = *(uint8_t *)FieldValue;
            break;
        case 35: //magic
            DATA.value.magic = *(uint8_t *)FieldValue;
            break;
        case 36: //stealth
            DATA.value.stealth = *(uint8_t *)FieldValue;
            break;
        case 37: //soulType
            SetSoul(*(uint8_t *)FieldValue);
            break;
        case 38: //unused2
            if(ArraySize != 1)
                break;
            DATA.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 39: //health
            DATA.value.health = *(uint16_t *)FieldValue;
            break;
        case 40: //unused3
            if(ArraySize != 2)
                break;
            DATA.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 41: //attackDamage
            DATA.value.attackDamage = *(uint16_t *)FieldValue;
            break;
        case 42: //strength
            DATA.value.strength = *(uint8_t *)FieldValue;
            break;
        case 43: //intelligence
            DATA.value.intelligence = *(uint8_t *)FieldValue;
            break;
        case 44: //willpower
            DATA.value.willpower = *(uint8_t *)FieldValue;
            break;
        case 45: //agility
            DATA.value.agility = *(uint8_t *)FieldValue;
            break;
        case 46: //speed
            DATA.value.speed = *(uint8_t *)FieldValue;
            break;
        case 47: //endurance
            DATA.value.endurance = *(uint8_t *)FieldValue;
            break;
        case 48: //personality
            DATA.value.personality = *(uint8_t *)FieldValue;
            break;
        case 49: //luck
            DATA.value.luck = *(uint8_t *)FieldValue;
            break;
        case 50: //attackReach
            RNAM.value = *(uint8_t *)FieldValue;
            break;
        case 51: //combatStyle
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 52: //turningSpeed
            TNAM.value = *(float *)FieldValue;
            break;
        case 53: //baseScale
            BNAM.value = *(float *)FieldValue;
            break;
        case 54: //footWeight
            WNAM.value = *(float *)FieldValue;
            break;
        case 55: //inheritsSoundsFrom
            CSCR.value = *(FORMID *)FieldValue;
            return true;
        case 56: //bloodSprayPath
            NAM0.Copy((char *)FieldValue);
            break;
        case 57: //bloodDecalPath
            NAM1.Copy((char *)FieldValue);
            break;
        case 58: //sounds
            if(ListFieldID == 0) //soundsSize
                {
                Sounds.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Sounds.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //soundType
                    Sounds.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    break;
                case 2: //sound
                    Sounds.value[ListIndex]->CSDI.value = *(FORMID *)FieldValue;
                    return true;
                case 3: //chance
                    Sounds.value[ListIndex]->CSDC.value = *(uint8_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void CREARecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENAIDT defaultAIDT;
    GENACBS defaultACBS;
    CREADATA defaultDATA;
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
        case 9: //spells
            SPLO.Unload();
            return;
        case 10: //bodyParts
            NIFZ.Unload();
            return;
        case 11: //nift_p
            NIFT.Unload();
            return;
        case 12: //flags
            ACBS.value.flags = defaultACBS.flags;
            return;
        case 13: //baseSpell
            ACBS.value.baseSpell = defaultACBS.baseSpell;
            return;
        case 14: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            return;
        case 15: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            return;
        case 16: //level
            ACBS.value.level = defaultACBS.level;
            return;
        case 17: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            return;
        case 18: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            return;
        case 19: //factions
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
        case 20: //deathItem
            INAM.Unload();
            return;
        case 21: //script
            SCRI.Unload();
            return;
        case 22: //items
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
        case 23: //aggression
            AIDT.value.aggression = defaultAIDT.aggression;
            return;
        case 24: //confidence
            AIDT.value.confidence = defaultAIDT.confidence;
            return;
        case 25: //energyLevel
            AIDT.value.confidence = defaultAIDT.confidence;
            return;
        case 26: //responsibility
            AIDT.value.responsibility = defaultAIDT.responsibility;
            return;
        case 27: //services
            AIDT.value.flags = defaultAIDT.flags;
            return;
        case 28: //trainSkill
            AIDT.value.trainSkill = defaultAIDT.trainSkill;
            return;
        case 29: //trainLevel
            AIDT.value.trainLevel = defaultAIDT.trainLevel;
            return;
        case 30: //unused1
            AIDT.value.unused1[0] = defaultAIDT.unused1[0];
            AIDT.value.unused1[1] = defaultAIDT.unused1[1];
            return;
        case 31: //aiPackages
            PKID.Unload();
            return;
        case 32: //animations
            KFFZ.Unload();
            return;
        case 33: //creatureType
            DATA.value.creatureType = defaultDATA.creatureType;
            return;
        case 34: //combat
            DATA.value.combat = defaultDATA.combat;
            return;
        case 35: //magic
            DATA.value.magic = defaultDATA.magic;
            return;
        case 36: //stealth
            DATA.value.stealth = defaultDATA.stealth;
            return;
        case 37: //soulType
            DATA.value.soul = defaultDATA.soul;
            return;
        case 38: //unused2
            DATA.value.unused1 = defaultDATA.unused1;
            return;
        case 39: //health
            DATA.value.health = defaultDATA.health;
            return;
        case 40: //unused3
            DATA.value.unused2[0] = defaultDATA.unused2[0];
            DATA.value.unused2[1] = defaultDATA.unused2[1];
            return;
        case 41: //attackDamage
            DATA.value.attackDamage = defaultDATA.attackDamage;
            return;
        case 42: //strength
            DATA.value.strength = defaultDATA.strength;
            return;
        case 43: //intelligence
            DATA.value.intelligence = defaultDATA.intelligence;
            return;
        case 44: //willpower
            DATA.value.willpower = defaultDATA.willpower;
            return;
        case 45: //agility
            DATA.value.agility = defaultDATA.agility;
            return;
        case 46: //speed
            DATA.value.speed = defaultDATA.speed;
            return;
        case 47: //endurance
            DATA.value.endurance = defaultDATA.endurance;
            return;
        case 48: //personality
            DATA.value.personality = defaultDATA.personality;
            return;
        case 49: //luck
            DATA.value.luck = defaultDATA.luck;
            return;
        case 50: //attackReach
            RNAM.Unload();
            return;
        case 51: //combatStyle
            ZNAM.Unload();
            return;
        case 52: //turningSpeed
            TNAM.Unload();
            return;
        case 53: //baseScale
            BNAM.Unload();
            return;
        case 54: //footWeight
            WNAM.Unload();
            return;
        case 55: //inheritsSoundsFrom
            CSCR.Unload();
            return;
        case 56: //bloodSprayPath
            NAM0.Unload();
            return;
        case 57: //bloodDecalPath
            NAM1.Unload();
            return;
        case 58: //sounds
            if(ListFieldID == 0) //sounds
                {
                Sounds.Unload();
                return;
                }

            if(ListIndex >= Sounds.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //soundType
                    Sounds.value[ListIndex]->CSDT.Unload();
                    return;
                case 2: //sound
                    Sounds.value[ListIndex]->CSDI.Unload();
                    return;
                case 3: //chance
                    Sounds.value[ListIndex]->CSDC.Unload();
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}