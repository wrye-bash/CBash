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

namespace FNV
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
            return CB_UNKNOWN_FIELD;
        case 18: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 19: //flags
            return CB_UINT32_FLAG_FIELD;
        case 20: //fatigue
            return CB_UINT16_FIELD;
        case 21: //barterGold
            return CB_UINT16_FIELD;
        case 22: //level
            return CB_SINT16_FIELD;
        case 23: //calcMin
            return CB_UINT16_FIELD;
        case 24: //calcMax
            return CB_UINT16_FIELD;
        case 25: //speedMult
            return CB_UINT16_FIELD;
        case 26: //karma
            return CB_FLOAT32_FIELD;
        case 27: //dispBase
            return CB_SINT16_FIELD;
        case 28: //templateFlags
            return CB_UINT16_FLAG_FIELD;
        case 29: //factions
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
        case 30: //deathItem
            return CB_FORMID_FIELD;
        case 31: //voice
            return CB_FORMID_FIELD;
        case 32: //template
            return CB_FORMID_FIELD;
        case 33: //race
            return CB_FORMID_FIELD;
        case 34: //actorEffects
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
        case 35: //unarmedEffect
            return CB_FORMID_FIELD;
        case 36: //unarmedAnim
            return CB_UINT16_TYPE_FIELD;
        case 37: //destructableHealth
            return CB_SINT32_FIELD;
        case 38: //destructableCount
            return CB_UINT8_FIELD;
        case 39: //destructableFlags
            return CB_UINT8_FLAG_FIELD;
        case 40: //destructableUnused1
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
        case 41: //destructableStages
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
        case 42: //script
            return CB_FORMID_FIELD;
        case 43: //items
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
        case 44: //aggression
            return CB_UINT8_TYPE_FIELD;
        case 45: //confidence
            return CB_UINT8_TYPE_FIELD;
        case 46: //energyLevel
            return CB_UINT8_FIELD;
        case 47: //responsibility
            return CB_UINT8_TYPE_FIELD;
        case 48: //mood
            return CB_UINT8_TYPE_FIELD;
        case 49: //unused1
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
        case 50: //services
            return CB_UINT32_FLAG_FIELD;
        case 51: //trainSkill
            return CB_SINT8_TYPE_FIELD;
        case 52: //trainLevel
            return CB_UINT8_FIELD;
        case 53: //assistance
            return CB_UINT8_TYPE_FIELD;
        case 54: //aggroFlags
            return CB_UINT8_FLAG_FIELD;
        case 55: //aggroRadius
            return CB_SINT32_FIELD;
        case 56: //aiPackages
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
        case 57: //iclass
            return CB_FORMID_FIELD;
        case 58: //baseHealth
            return CB_SINT32_FIELD;
        case 59: //strength
            return CB_UINT8_FIELD;
        case 60: //perception
            return CB_UINT8_FIELD;
        case 61: //endurance
            return CB_UINT8_FIELD;
        case 62: //charisma
            return CB_UINT8_FIELD;
        case 63: //intelligence
            return CB_UINT8_FIELD;
        case 64: //agility
            return CB_UINT8_FIELD;
        case 65: //luck
            return CB_UINT8_FIELD;
        case 66: //barter
            return CB_UINT8_FIELD;
        case 67: //bigGuns
            return CB_UINT8_FIELD;
        case 68: //energy
            return CB_UINT8_FIELD;
        case 69: //explosives
            return CB_UINT8_FIELD;
        case 70: //lockpick
            return CB_UINT8_FIELD;
        case 71: //medicine
            return CB_UINT8_FIELD;
        case 72: //melee
            return CB_UINT8_FIELD;
        case 73: //repair
            return CB_UINT8_FIELD;
        case 74: //science
            return CB_UINT8_FIELD;
        case 75: //guns
            return CB_UINT8_FIELD;
        case 76: //sneak
            return CB_UINT8_FIELD;
        case 77: //speech
            return CB_UINT8_FIELD;
        case 78: //survival
            return CB_UINT8_FIELD;
        case 79: //unarmed
            return CB_UINT8_FIELD;
        case 80: //barterBoost
            return CB_UINT8_FIELD;
        case 81: //bigGunsBoost
            return CB_UINT8_FIELD;
        case 82: //energyBoost
            return CB_UINT8_FIELD;
        case 83: //explosivesBoost
            return CB_UINT8_FIELD;
        case 84: //lockpickBoost
            return CB_UINT8_FIELD;
        case 85: //medicineBoost
            return CB_UINT8_FIELD;
        case 86: //meleeBoost
            return CB_UINT8_FIELD;
        case 87: //repairBoost
            return CB_UINT8_FIELD;
        case 88: //scienceBoost
            return CB_UINT8_FIELD;
        case 89: //gunsBoost
            return CB_UINT8_FIELD;
        case 90: //sneakBoost
            return CB_UINT8_FIELD;
        case 91: //speechBoost
            return CB_UINT8_FIELD;
        case 92: //survivalBoost
            return CB_UINT8_FIELD;
        case 93: //unarmedBoost
            return CB_UINT8_FIELD;
        case 94: //headParts
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)PNAM.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 95: //hair
            return CB_FORMID_FIELD;
        case 96: //hairLength
            return CB_FLOAT32_FIELD;
        case 97: //eyes
            return CB_FORMID_FIELD;
        case 98: //hairRed
            return CB_UINT8_FIELD;
        case 99: //hairGreen
            return CB_UINT8_FIELD;
        case 100: //hairBlue
            return CB_UINT8_FIELD;
        case 101: //unused2
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
        case 102: //combatStyle
            return CB_FORMID_FIELD;
        case 103: //impactType
            return CB_UINT32_TYPE_FIELD;
        case 104: //fggs_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGS.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 105: //fgga_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGGA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 106: //fgts_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FGTS.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 107: //unknown
            return CB_UINT16_FIELD;
        case 108: //height
            return CB_FLOAT32_FIELD;
        case 109: //weight
            return CB_FLOAT32_FIELD;
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
        case 7:  //boundX1
            return OBND.IsLoaded() ? &OBND.value.x1 : NULL;
        case 8: //boundY1
            return OBND.IsLoaded() ? &OBND.value.y1 : NULL;
        case 9: //boundZ1
            return OBND.IsLoaded() ? &OBND.value.z1 : NULL;
        case 10: //boundX2
            return OBND.IsLoaded() ? &OBND.value.x2 : NULL;
        case 11: //boundY2
            return OBND.IsLoaded() ? &OBND.value.y2 : NULL;
        case 12: //boundZ2
            return OBND.IsLoaded() ? &OBND.value.z2 : NULL;
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
        case 19: //flags
            return &ACBS.value.flags;
        case 20: //fatigue
            return &ACBS.value.fatigue;
        case 21: //barterGold
            return &ACBS.value.barterGold;
        case 22: //level
            return &ACBS.value.level;
        case 23: //calcMin
            return &ACBS.value.calcMin;
        case 24: //calcMax
            return &ACBS.value.calcMax;
        case 25: //speedMult
            return &ACBS.value.speedMult;
        case 26: //karma
            return &ACBS.value.karma;
        case 27: //dispBase
            return &ACBS.value.dispBase;
        case 28: //templateFlags
            return &ACBS.value.templateFlags;
        case 29: //factions
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
        case 30: //deathItem
            return &INAM.value;
        case 31: //voice
            return &VTCK.value;
        case 32: //template
            return &TPLT.value;
        case 33: //race
            return &RNAM.value;
        case 34: //actorEffects
            *FieldValues = SPLO.IsLoaded() ? &SPLO.value[0] : NULL;
            return NULL;
        case 35: //unarmedEffect
            return &EITM.value;
        case 36: //unarmedAnim
            return &EAMT.value;
        case 37: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 38: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 39: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 40: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 41: //destructableStages
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
        case 42: //script
            return &SCRI.value;
        case 43: //items
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
        case 44: //aggression
            return AIDT.IsLoaded() ? &AIDT->aggression : NULL;
        case 45: //confidence
            return AIDT.IsLoaded() ? &AIDT->confidence : NULL;
        case 46: //energyLevel
            return AIDT.IsLoaded() ? &AIDT->energyLevel : NULL;
        case 47: //responsibility
            return AIDT.IsLoaded() ? &AIDT->responsibility : NULL;
        case 48: //mood
            return AIDT.IsLoaded() ? &AIDT->mood : NULL;
        case 49: //unused1
            *FieldValues = AIDT.IsLoaded() ? &AIDT->unused1[0] : NULL;
            return NULL;
        case 50: //services
            return AIDT.IsLoaded() ? &AIDT->flags : NULL;
        case 51: //trainSkill
            return AIDT.IsLoaded() ? &AIDT->trainSkill : NULL;
        case 52: //trainLevel
            return AIDT.IsLoaded() ? &AIDT->trainLevel : NULL;
        case 53: //assistance
            return AIDT.IsLoaded() ? &AIDT->assistance : NULL;
        case 54: //aggroFlags
            return AIDT.IsLoaded() ? &AIDT->aggroFlags : NULL;
        case 55: //aggroRadius
            return AIDT.IsLoaded() ? &AIDT->aggroRadius : NULL;
        case 56: //aiPackages
            *FieldValues = PKID.IsLoaded() ? &PKID.value[0] : NULL;
            return NULL;
        case 57: //iclass
            return &CNAM.value;
        case 58: //baseHealth
            return DATA.IsLoaded() ? &DATA->baseHealth : NULL;
        case 59: //strength
            return DATA.IsLoaded() ? &DATA->strength : NULL;
        case 60: //perception
            return DATA.IsLoaded() ? &DATA->perception : NULL;
        case 61: //endurance
            return DATA.IsLoaded() ? &DATA->endurance : NULL;
        case 62: //charisma
            return DATA.IsLoaded() ? &DATA->charisma : NULL;
        case 63: //intelligence
            return DATA.IsLoaded() ? &DATA->intelligence : NULL;
        case 64: //agility
            return DATA.IsLoaded() ? &DATA->agility : NULL;
        case 65: //luck
            return DATA.IsLoaded() ? &DATA->luck : NULL;
        case 66: //barter
            return DNAM.IsLoaded() ? &DNAM->barter : NULL;
        case 67: //bigGuns
            return DNAM.IsLoaded() ? &DNAM->bigGuns : NULL;
        case 68: //energy
            return DNAM.IsLoaded() ? &DNAM->energy : NULL;
        case 69: //explosives
            return DNAM.IsLoaded() ? &DNAM->explosives : NULL;
        case 70: //lockpick
            return DNAM.IsLoaded() ? &DNAM->lockpick : NULL;
        case 71: //medicine
            return DNAM.IsLoaded() ? &DNAM->medicine : NULL;
        case 72: //melee
            return DNAM.IsLoaded() ? &DNAM->melee : NULL;
        case 73: //repair
            return DNAM.IsLoaded() ? &DNAM->repair : NULL;
        case 74: //science
            return DNAM.IsLoaded() ? &DNAM->science : NULL;
        case 75: //guns
            return DNAM.IsLoaded() ? &DNAM->guns : NULL;
        case 76: //sneak
            return DNAM.IsLoaded() ? &DNAM->sneak : NULL;
        case 77: //speech
            return DNAM.IsLoaded() ? &DNAM->speech : NULL;
        case 78: //survival
            return DNAM.IsLoaded() ? &DNAM->survival : NULL;
        case 79: //unarmed
            return DNAM.IsLoaded() ? &DNAM->unarmed : NULL;
        case 80: //barterBoost
            return DNAM.IsLoaded() ? &DNAM->barterBoost : NULL;
        case 81: //bigGunsBoost
            return DNAM.IsLoaded() ? &DNAM->bigGunsBoost : NULL;
        case 82: //energyBoost
            return DNAM.IsLoaded() ? &DNAM->energyBoost : NULL;
        case 83: //explosivesBoost
            return DNAM.IsLoaded() ? &DNAM->explosivesBoost : NULL;
        case 84: //lockpickBoost
            return DNAM.IsLoaded() ? &DNAM->lockpickBoost : NULL;
        case 85: //medicineBoost
            return DNAM.IsLoaded() ? &DNAM->medicineBoost : NULL;
        case 86: //meleeBoost
            return DNAM.IsLoaded() ? &DNAM->meleeBoost : NULL;
        case 87: //repairBoost
            return DNAM.IsLoaded() ? &DNAM->repairBoost : NULL;
        case 88: //scienceBoost
            return DNAM.IsLoaded() ? &DNAM->scienceBoost : NULL;
        case 89: //gunsBoost
            return DNAM.IsLoaded() ? &DNAM->gunsBoost : NULL;
        case 90: //sneakBoost
            return DNAM.IsLoaded() ? &DNAM->sneakBoost : NULL;
        case 91: //speechBoost
            return DNAM.IsLoaded() ? &DNAM->speechBoost : NULL;
        case 92: //survivalBoost
            return DNAM.IsLoaded() ? &DNAM->survivalBoost : NULL;
        case 93: //unarmedBoost
            return DNAM.IsLoaded() ? &DNAM->unarmedBoost : NULL;
        case 94: //headParts
            *FieldValues = PNAM.IsLoaded() ? &PNAM.value[0] : NULL;
            return NULL;
        case 95: //hair
            return &HNAM.value;
        case 96: //hairLength
            return LNAM.value;
        case 97: //eyes
            return &ENAM.value;
        case 98: //hairRed
            return HCLR.IsLoaded() ? &HCLR->red : NULL;
        case 99: //hairGreen
            return HCLR.IsLoaded() ? &HCLR->green : NULL;
        case 100: //hairBlue
            return HCLR.IsLoaded() ? &HCLR->blue : NULL;
        case 101: //unused2
            *FieldValues = HCLR.IsLoaded() ? &HCLR->unused1 : NULL;
            return NULL;
        case 102: //combatStyle
            return &ZNAM.value;
        case 103: //impactType
            return &NAM4.value;
        case 104: //fggs_p
            *FieldValues = FGGS.value;
            return NULL;
        case 105: //fgga_p
            *FieldValues = FGGA.value;
            return NULL;
        case 106: //fgts_p
            *FieldValues = FGTS.value;
            return NULL;
        case 107: //unknown
            return &NAM5.value;
        case 108: //height
            return NAM6.value;
        case 109: //weight
            return NAM7.value;
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
        case 7:  //boundX1
            OBND.Load();
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.Load();
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.Load();
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.Load();
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.Load();
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.Load();
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
        case 19: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 20: //fatigue
            ACBS.value.fatigue = *(uint16_t *)FieldValue;
            break;
        case 21: //barterGold
            ACBS.value.barterGold = *(uint16_t *)FieldValue;
            break;
        case 22: //level
            ACBS.value.level = *(int16_t *)FieldValue;
            break;
        case 23: //calcMin
            ACBS.value.calcMin = *(uint16_t *)FieldValue;
            break;
        case 24: //calcMax
            ACBS.value.calcMax = *(uint16_t *)FieldValue;
            break;
        case 25: //speedMult
            ACBS.value.speedMult = *(uint16_t *)FieldValue;
            break;
        case 26: //karma
            ACBS.value.karma = *(float *)FieldValue;
            break;
        case 27: //dispBase
            ACBS.value.dispBase = *(int16_t *)FieldValue;
            break;
        case 28: //templateFlags
            SetTemplateFlagMask(*(uint16_t *)FieldValue);
            break;
        case 29: //factions
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
        case 30: //deathItem
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 31: //voice
            VTCK.value = *(FORMID *)FieldValue;
            return true;
        case 32: //template
            TPLT.value = *(FORMID *)FieldValue;
            return true;
        case 33: //race
            RNAM.value = *(FORMID *)FieldValue;
            return true;
        case 34: //actorEffects
            SPLO.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                SPLO.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 35: //unarmedEffect
            EITM.value = *(FORMID *)FieldValue;
            return true;
        case 36: //unarmedAnim
            EAMT.value = *(uint16_t *)FieldValue;
            break;
        case 37: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(int32_t *)FieldValue;
            break;
        case 38: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(uint8_t *)FieldValue;
            break;
        case 39: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 40: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 41: //destructableStages
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
        case 42: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 43: //items
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
        case 44: //aggression
            SetAggressionType(*(uint8_t *)FieldValue);
            break;
        case 45: //confidence
            SetConfidenceType(*(uint8_t *)FieldValue);
            break;
        case 46: //energyLevel
            AIDT.Load();
            AIDT->energyLevel = *(uint8_t *)FieldValue;
            break;
        case 47: //responsibility
            AIDT.Load();
            AIDT->responsibility = *(uint8_t *)FieldValue;
            break;
        case 48: //mood
            SetMoodType(*(uint8_t *)FieldValue);
            break;
        case 49: //unused1
            if(ArraySize != 3)
                break;
            AIDT.Load();
            AIDT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            AIDT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            AIDT->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 50: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 51: //trainSkill
            AIDT.Load();
            AIDT->trainSkill = *(int8_t *)FieldValue;
            break;
        case 52: //trainLevel
            AIDT.Load();
            AIDT->trainLevel = *(uint8_t *)FieldValue;
            break;
        case 53: //assistance
            SetAssistanceType(*(uint8_t *)FieldValue);
            break;
        case 54: //aggroFlags
            SetAggroFlagMask(*(uint8_t *)FieldValue);
            break;
        case 55: //aggroRadius
            AIDT.Load();
            AIDT->aggroRadius = *(int32_t *)FieldValue;
            break;
        case 56: //aiPackages
            PKID.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                PKID.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 57: //iclass
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 58: //baseHealth
            DATA.Load();
            DATA->baseHealth = *(int32_t *)FieldValue;
            break;
        case 59: //strength
            DATA.Load();
            DATA->strength = *(uint8_t *)FieldValue;
            break;
        case 60: //perception
            DATA.Load();
            DATA->perception = *(uint8_t *)FieldValue;
            break;
        case 61: //endurance
            DATA.Load();
            DATA->endurance = *(uint8_t *)FieldValue;
            break;
        case 62: //charisma
            DATA.Load();
            DATA->charisma = *(uint8_t *)FieldValue;
            break;
        case 63: //intelligence
            DATA.Load();
            DATA->intelligence = *(uint8_t *)FieldValue;
            break;
        case 64: //agility
            DATA.Load();
            DATA->agility = *(uint8_t *)FieldValue;
            break;
        case 65: //luck
            DATA.Load();
            DATA->luck = *(uint8_t *)FieldValue;
            break;
        case 66: //barter
            DNAM.Load();
            DNAM->barter = *(uint8_t *)FieldValue;
            break;
        case 67: //bigGuns
            DNAM.Load();
            DNAM->bigGuns = *(uint8_t *)FieldValue;
            break;
        case 68: //energy
            DNAM.Load();
            DNAM->energy = *(uint8_t *)FieldValue;
            break;
        case 69: //explosives
            DNAM.Load();
            DNAM->explosives = *(uint8_t *)FieldValue;
            break;
        case 70: //lockpick
            DNAM.Load();
            DNAM->lockpick = *(uint8_t *)FieldValue;
            break;
        case 71: //medicine
            DNAM.Load();
            DNAM->medicine = *(uint8_t *)FieldValue;
            break;
        case 72: //melee
            DNAM.Load();
            DNAM->melee = *(uint8_t *)FieldValue;
            break;
        case 73: //repair
            DNAM.Load();
            DNAM->repair = *(uint8_t *)FieldValue;
            break;
        case 74: //science
            DNAM.Load();
            DNAM->science = *(uint8_t *)FieldValue;
            break;
        case 75: //guns
            DNAM.Load();
            DNAM->guns = *(uint8_t *)FieldValue;
            break;
        case 76: //sneak
            DNAM.Load();
            DNAM->sneak = *(uint8_t *)FieldValue;
            break;
        case 77: //speech
            DNAM.Load();
            DNAM->speech = *(uint8_t *)FieldValue;
            break;
        case 78: //survival
            DNAM.Load();
            DNAM->survival = *(uint8_t *)FieldValue;
            break;
        case 79: //unarmed
            DNAM.Load();
            DNAM->unarmed = *(uint8_t *)FieldValue;
            break;
        case 80: //barterBoost
            DNAM.Load();
            DNAM->barterBoost = *(uint8_t *)FieldValue;
            break;
        case 81: //bigGunsBoost
            DNAM.Load();
            DNAM->bigGunsBoost = *(uint8_t *)FieldValue;
            break;
        case 82: //energyBoost
            DNAM.Load();
            DNAM->energyBoost = *(uint8_t *)FieldValue;
            break;
        case 83: //explosivesBoost
            DNAM.Load();
            DNAM->explosivesBoost = *(uint8_t *)FieldValue;
            break;
        case 84: //lockpickBoost
            DNAM.Load();
            DNAM->lockpickBoost = *(uint8_t *)FieldValue;
            break;
        case 85: //medicineBoost
            DNAM.Load();
            DNAM->medicineBoost = *(uint8_t *)FieldValue;
            break;
        case 86: //meleeBoost
            DNAM.Load();
            DNAM->meleeBoost = *(uint8_t *)FieldValue;
            break;
        case 87: //repairBoost
            DNAM.Load();
            DNAM->repairBoost = *(uint8_t *)FieldValue;
            break;
        case 88: //scienceBoost
            DNAM.Load();
            DNAM->scienceBoost = *(uint8_t *)FieldValue;
            break;
        case 89: //gunsBoost
            DNAM.Load();
            DNAM->gunsBoost = *(uint8_t *)FieldValue;
            break;
        case 90: //sneakBoost
            DNAM.Load();
            DNAM->sneakBoost = *(uint8_t *)FieldValue;
            break;
        case 91: //speechBoost
            DNAM.Load();
            DNAM->speechBoost = *(uint8_t *)FieldValue;
            break;
        case 92: //survivalBoost
            DNAM.Load();
            DNAM->survivalBoost = *(uint8_t *)FieldValue;
            break;
        case 93: //unarmedBoost
            DNAM.Load();
            DNAM->unarmedBoost = *(uint8_t *)FieldValue;
            break;
        case 94: //headParts
            PNAM.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                PNAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 95: //hair
            HNAM.value = *(FORMID *)FieldValue;
            return true;
        case 96: //hairLength
            LNAM.Load();
            *LNAM.value = *(float *)FieldValue;
            break;
        case 97: //eyes
            ENAM.value = *(FORMID *)FieldValue;
            return true;
        case 98: //hairRed
            HCLR.Load();
            HCLR->red = *(uint8_t *)FieldValue;
            break;
        case 99: //hairGreen
            HCLR.Load();
            HCLR->green = *(uint8_t *)FieldValue;
            break;
        case 100: //hairBlue
            HCLR.Load();
            HCLR->blue = *(uint8_t *)FieldValue;
            break;
        case 101: //unused2
            if(ArraySize != 1)
                break;
            HCLR.Load();
            HCLR->unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 102: //combatStyle
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 103: //impactType
            SetImpactType(*(uint32_t *)FieldValue);
            break;
        case 104: //FGGS
            FGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 105: //FGGA
            FGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 106: //FGTS
            FGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 107: //unknown
            NAM5.value = *(uint16_t *)FieldValue;
            break;
        case 108: //height
            NAM6.Load();
            *NAM6.value = *(float *)FieldValue;
            break;
        case 109: //weight
            NAM7.Load();
            *NAM7.value = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void NPC_Record::DeleteField(FIELD_IDENTIFIERS)
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
    NPC_DATA defaultDATA;
    NPC_DNAM defaultDNAM;
    GENCLR defaultHCLR;

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
        case 7:  //boundX1
            if(OBND.IsLoaded())
                OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            if(OBND.IsLoaded())
                OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            if(OBND.IsLoaded())
                OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            if(OBND.IsLoaded())
                OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            if(OBND.IsLoaded())
                OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            if(OBND.IsLoaded())
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
        case 19: //flags
            SetFlagMask(defaultACBS.flags);
            return;
        case 20: //fatigue
            ACBS.value.fatigue = defaultACBS.fatigue;
            return;
        case 21: //barterGold
            ACBS.value.barterGold = defaultACBS.barterGold;
            return;
        case 22: //level
            ACBS.value.level = defaultACBS.level;
            return;
        case 23: //calcMin
            ACBS.value.calcMin = defaultACBS.calcMin;
            return;
        case 24: //calcMax
            ACBS.value.calcMax = defaultACBS.calcMax;
            return;
        case 25: //speedMult
            ACBS.value.speedMult = defaultACBS.speedMult;
            return;
        case 26: //karma
            ACBS.value.karma = defaultACBS.karma;
            return;
        case 27: //dispBase
            ACBS.value.dispBase = defaultACBS.dispBase;
            return;
        case 28: //templateFlags
            SetTemplateFlagMask(defaultACBS.templateFlags);
            return;
        case 29: //factions
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
        case 30: //deathItem
            INAM.Unload();
            return;
        case 31: //voice
            VTCK.Unload();
            return;
        case 32: //template
            TPLT.Unload();
            return;
        case 33: //race
            RNAM.Unload();
            return;
        case 34: //actorEffects
            SPLO.Unload();
            return;
        case 35: //unarmedEffect
            EITM.Unload();
            return;
        case 36: //unarmedAnim
            EAMT.Unload();
            return;
        case 37: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 38: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 39: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 40: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 41: //destructableStages
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
        case 42: //script
            SCRI.Unload();
            return;
        case 43: //items
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
        case 44: //aggression
            if(AIDT.IsLoaded())
                SetAggressionType(defaultAIDT.aggression);
            return;
        case 45: //confidence
            if(AIDT.IsLoaded())
                SetConfidenceType(defaultAIDT.confidence);
            return;
        case 46: //energyLevel
            if(AIDT.IsLoaded())
                AIDT->energyLevel = defaultAIDT.energyLevel;
            return;
        case 47: //responsibility
            if(AIDT.IsLoaded())
                AIDT->responsibility = defaultAIDT.responsibility;
            return;
        case 48: //mood
            if(AIDT.IsLoaded())
                SetMoodType(defaultAIDT.mood);
            return;
        case 49: //unused1
            if(AIDT.IsLoaded())
                {
                AIDT->unused1[0] = defaultAIDT.unused1[0];
                AIDT->unused1[1] = defaultAIDT.unused1[1];
                AIDT->unused1[2] = defaultAIDT.unused1[2];
                }
            return;
        case 50: //services
            if(AIDT.IsLoaded())
                SetServicesFlagMask(defaultAIDT.flags);
            return;
        case 51: //trainSkill
            if(AIDT.IsLoaded())
                AIDT->trainSkill = defaultAIDT.trainSkill;
            return;
        case 52: //trainLevel
            if(AIDT.IsLoaded())
                AIDT->trainLevel = defaultAIDT.trainLevel;
            return;
        case 53: //assistance
            if(AIDT.IsLoaded())
                SetAssistanceType(defaultAIDT.assistance);
            return;
        case 54: //aggroFlags
            if(AIDT.IsLoaded())
                SetAggroFlagMask(defaultAIDT.aggroFlags);
            return;
        case 55: //aggroRadius
            if(AIDT.IsLoaded())
                AIDT->aggroRadius = defaultAIDT.aggroRadius;
            return;
        case 56: //aiPackages
            PKID.Unload();
            return;
        case 57: //iclass
            CNAM.Unload();
            return;
        case 58: //baseHealth
            if(DATA.IsLoaded())
                DATA->baseHealth = defaultDATA.baseHealth;
            return;
        case 59: //strength
            if(DATA.IsLoaded())
                DATA->strength = defaultDATA.strength;
            return;
        case 60: //perception
            if(DATA.IsLoaded())
                DATA->perception = defaultDATA.perception;
            return;
        case 61: //endurance
            if(DATA.IsLoaded())
                DATA->endurance = defaultDATA.endurance;
            return;
        case 62: //charisma
            if(DATA.IsLoaded())
                DATA->charisma = defaultDATA.charisma;
            return;
        case 63: //intelligence
            if(DATA.IsLoaded())
                DATA->intelligence = defaultDATA.intelligence;
            return;
        case 64: //agility
            if(DATA.IsLoaded())
                DATA->agility = defaultDATA.agility;
            return;
        case 65: //luck
            if(DATA.IsLoaded())
                DATA->luck = defaultDATA.luck;
            return;
        case 66: //barter
            if(DNAM.IsLoaded())
                DNAM->barter = defaultDNAM.barter;
            return;
        case 67: //bigGuns
            if(DNAM.IsLoaded())
                DNAM->bigGuns = defaultDNAM.bigGuns;
            return;
        case 68: //energy
            if(DNAM.IsLoaded())
                DNAM->energy = defaultDNAM.energy;
            return;
        case 69: //explosives
            if(DNAM.IsLoaded())
                DNAM->explosives = defaultDNAM.explosives;
            return;
        case 70: //lockpick
            if(DNAM.IsLoaded())
                DNAM->lockpick = defaultDNAM.lockpick;
            return;
        case 71: //medicine
            if(DNAM.IsLoaded())
                DNAM->medicine = defaultDNAM.medicine;
            return;
        case 72: //melee
            if(DNAM.IsLoaded())
                DNAM->melee = defaultDNAM.melee;
            return;
        case 73: //repair
            if(DNAM.IsLoaded())
                DNAM->repair = defaultDNAM.repair;
            return;
        case 74: //science
            if(DNAM.IsLoaded())
                DNAM->science = defaultDNAM.science;
            return;
        case 75: //guns
            if(DNAM.IsLoaded())
                DNAM->guns = defaultDNAM.guns;
            return;
        case 76: //sneak
            if(DNAM.IsLoaded())
                DNAM->sneak = defaultDNAM.sneak;
            return;
        case 77: //speech
            if(DNAM.IsLoaded())
                DNAM->speech = defaultDNAM.speech;
            return;
        case 78: //survival
            if(DNAM.IsLoaded())
                DNAM->survival = defaultDNAM.survival;
            return;
        case 79: //unarmed
            if(DNAM.IsLoaded())
                DNAM->unarmed = defaultDNAM.unarmed;
            return;
        case 80: //barterBoost
            if(DNAM.IsLoaded())
                DNAM->barterBoost = defaultDNAM.barterBoost;
            return;
        case 81: //bigGunsBoost
            if(DNAM.IsLoaded())
                DNAM->bigGunsBoost = defaultDNAM.bigGunsBoost;
            return;
        case 82: //energyBoost
            if(DNAM.IsLoaded())
                DNAM->energyBoost = defaultDNAM.energyBoost;
            return;
        case 83: //explosivesBoost
            if(DNAM.IsLoaded())
                DNAM->explosivesBoost = defaultDNAM.explosivesBoost;
            return;
        case 84: //lockpickBoost
            if(DNAM.IsLoaded())
                DNAM->lockpickBoost = defaultDNAM.lockpickBoost;
            return;
        case 85: //medicineBoost
            if(DNAM.IsLoaded())
                DNAM->medicineBoost = defaultDNAM.medicineBoost;
            return;
        case 86: //meleeBoost
            if(DNAM.IsLoaded())
                DNAM->meleeBoost = defaultDNAM.meleeBoost;
            return;
        case 87: //repairBoost
            if(DNAM.IsLoaded())
                DNAM->repairBoost = defaultDNAM.repairBoost;
            return;
        case 88: //scienceBoost
            if(DNAM.IsLoaded())
                DNAM->scienceBoost = defaultDNAM.scienceBoost;
            return;
        case 89: //gunsBoost
            if(DNAM.IsLoaded())
                DNAM->gunsBoost = defaultDNAM.gunsBoost;
            return;
        case 90: //sneakBoost
            if(DNAM.IsLoaded())
                DNAM->sneakBoost = defaultDNAM.sneakBoost;
            return;
        case 91: //speechBoost
            if(DNAM.IsLoaded())
                DNAM->speechBoost = defaultDNAM.speechBoost;
            return;
        case 92: //survivalBoost
            if(DNAM.IsLoaded())
                DNAM->survivalBoost = defaultDNAM.survivalBoost;
            return;
        case 93: //unarmedBoost
            if(DNAM.IsLoaded())
                DNAM->unarmedBoost = defaultDNAM.unarmedBoost;
            return;
        case 94: //headParts
            PNAM.Unload();
            return;
        case 95: //hair
            HNAM.Unload();
            return;
        case 96: //hairLength
            LNAM.Unload();
            return;
        case 97: //eyes
            ENAM.Unload();
            return;
        case 98: //hairRed
            if(HCLR.IsLoaded())
                HCLR->red = defaultHCLR.red;
            return;
        case 99: //hairGreen
            if(HCLR.IsLoaded())
                HCLR->green = defaultHCLR.green;
            return;
        case 100: //hairBlue
            if(HCLR.IsLoaded())
                HCLR->blue = defaultHCLR.blue;
            return;
        case 101: //unused2
            if(HCLR.IsLoaded())
                HCLR->unused1 = defaultHCLR.unused1;
            return;
        case 102: //combatStyle
            ZNAM.Unload();
            return;
        case 103: //impactType
            NAM4.Unload();
            return;
        case 104: //FGGS
            FGGS.Unload();
            return;
        case 105: //FGGA
            FGGA.Unload();
            return;
        case 106: //FGTS
            FGTS.Unload();
            return;
        case 107: //unknown
            NAM5.Unload();
            return;
        case 108: //height
            NAM6.Unload();
            return;
        case 109: //weight
            NAM7.Unload();
            return;
        default:
            return;
        }
    }
}