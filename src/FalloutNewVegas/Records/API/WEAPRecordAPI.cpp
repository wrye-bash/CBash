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
#include "..\WEAPRecord.h"

namespace FNV
{
uint32_t WEAPRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags
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
        case 19: //iconPath
            return CB_ISTRING_FIELD;
        case 20: //smallIconPath
            return CB_ISTRING_FIELD;
        case 21: //script
            return CB_FORMID_FIELD;
        case 22: //effect
            return CB_FORMID_FIELD;
        case 23: //chargeAmount
            return CB_SINT16_FIELD;
        case 24: //ammo
            return CB_FORMID_FIELD;
        case 25: //destructableHealth
            return CB_SINT32_FIELD;
        case 26: //destructableCount
            return CB_UINT8_FIELD;
        case 27: //destructableFlags
            return CB_UINT8_FLAG_FIELD;
        case 28: //destructableUnused1
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
        case 29: //destructableStages
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
        case 30: //repairList
            return CB_FORMID_FIELD;
        case 31: //equipmentType
            return CB_SINT32_TYPE_FIELD;
        case 32: //modelList
            return CB_FORMID_FIELD;
        case 33: //pickupSound
            return CB_FORMID_FIELD;
        case 34: //dropSound
            return CB_FORMID_FIELD;
        case 35: //shell_modPath
            return CB_ISTRING_FIELD;
        case 36: //shell_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD2.IsLoaded() ? MOD2->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 37: //shell_altTextures
            if(!MOD2.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MOD2->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
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
        case 38: //scope_modPath
            return CB_ISTRING_FIELD;
        case 39: //scope_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD2.IsLoaded() ? MOD2->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 40: //scope_altTextures
            if(!MOD2.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MOD2->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
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
        case 41: //scopeEffect
            return CB_FORMID_FIELD;
        case 42: //world_modPath
            return CB_ISTRING_FIELD;
        case 43: //world_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD2.IsLoaded() ? MOD2->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 44: //world_altTextures
            if(!MOD2.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MOD2->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
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
        case 45: //vatsName
            return CB_STRING_FIELD;
        case 46: //weaponNode
            return CB_STRING_FIELD;
        case 47: //model1Path
            return CB_ISTRING_FIELD;
        case 48: //model2Path
            return CB_ISTRING_FIELD;
        case 49: //model12Path
            return CB_ISTRING_FIELD;
        case 50: //model3Path
            return CB_ISTRING_FIELD;
        case 51: //model13Path
            return CB_ISTRING_FIELD;
        case 52: //model23Path
            return CB_ISTRING_FIELD;
        case 53: //model123Path
            return CB_ISTRING_FIELD;
        case 54: //impact
            return CB_FORMID_FIELD;
        case 55: //model
            return CB_FORMID_FIELD;
        case 56: //model1
            return CB_FORMID_FIELD;
        case 57: //model2
            return CB_FORMID_FIELD;
        case 58: //model12
            return CB_FORMID_FIELD;
        case 59: //model3
            return CB_FORMID_FIELD;
        case 60: //model13
            return CB_FORMID_FIELD;
        case 61: //model23
            return CB_FORMID_FIELD;
        case 62: //model123
            return CB_FORMID_FIELD;
        case 63: //mod1
            return CB_FORMID_FIELD;
        case 64: //mod2
            return CB_FORMID_FIELD;
        case 65: //mod3
            return CB_FORMID_FIELD;
        case 66: //sound3D
            return CB_FORMID_FIELD;
        case 67: //soundDist
            return CB_FORMID_FIELD;
        case 68: //sound2D
            return CB_FORMID_FIELD;
        case 69: //sound3DLoop
            return CB_FORMID_FIELD;
        case 70: //soundMelee
            return CB_FORMID_FIELD;
        case 71: //soundBlock
            return CB_FORMID_FIELD;
        case 72: //soundIdle
            return CB_FORMID_FIELD;
        case 73: //soundEquip
            return CB_FORMID_FIELD;
        case 74: //soundUnequip
            return CB_FORMID_FIELD;
        case 75: //soundMod3D
            return CB_FORMID_FIELD;
        case 76: //soundModDist
            return CB_FORMID_FIELD;
        case 77: //soundMod2D
            return CB_FORMID_FIELD;
        case 78: //value
            return CB_SINT32_FIELD;
        case 79: //health
            return CB_SINT32_FIELD;
        case 80: //weight
            return CB_FLOAT32_FIELD;
        case 81: //damage
            return CB_SINT16_FIELD;
        case 82: //clipSize
            return CB_UINT8_FIELD;
        case 83: //animType
            return CB_UINT32_TYPE_FIELD;
        case 84: //animMult
            return CB_FLOAT32_FIELD;
        case 85: //reach
            return CB_FLOAT32_FIELD;
        case 86: //flags
            return CB_UINT8_FLAG_FIELD;
        case 87: //gripAnim
            return CB_UINT8_TYPE_FIELD;
        case 88: //ammoUse
            return CB_UINT8_FIELD;
        case 89: //reloadAnim
            return CB_UINT8_TYPE_FIELD;
        case 90: //minSpread
            return CB_FLOAT32_FIELD;
        case 91: //spread
            return CB_FLOAT32_FIELD;
        case 92: //unknown1
            return CB_FLOAT32_FIELD;
        case 93: //sightFOV
            return CB_FLOAT32_FIELD;
        case 94: //unknown2
            return CB_FLOAT32_FIELD;
        case 95: //projectile
            return CB_FORMID_FIELD;
        case 96: //VATSHitChance
            return CB_UINT8_FIELD;
        case 97: //attackAnim
            return CB_UINT8_TYPE_FIELD;
        case 98: //projectileCount
            return CB_UINT8_FIELD;
        case 99: //weaponAV
            return CB_UINT8_TYPE_FIELD;
        case 100: //minRange
            return CB_FLOAT32_FIELD;
        case 101: //maxRange
            return CB_FLOAT32_FIELD;
        case 102: //onHit
            return CB_UINT32_TYPE_FIELD;
        case 103: //extraFlags
            return CB_UINT32_FLAG_FIELD;
        case 104: //animAttackMult
            return CB_FLOAT32_FIELD;
        case 105: //fireRate
            return CB_FLOAT32_FIELD;
        case 106: //overrideAP
            return CB_FLOAT32_FIELD;
        case 107: //leftRumble
            return CB_FLOAT32_FIELD;
        case 108: //timeRumble
            return CB_FLOAT32_FIELD;
        case 109: //overrideDamageToWeapon
            return CB_FLOAT32_FIELD;
        case 110: //reloadTime
            return CB_FLOAT32_FIELD;
        case 111: //jamTime
            return CB_FLOAT32_FIELD;
        case 112: //aimArc
            return CB_FLOAT32_FIELD;
        case 113: //skill
            return CB_SINT32_FIELD;
        case 114: //rumbleType
            return CB_UINT32_TYPE_FIELD;
        case 115: //rumbleWavelength
            return CB_FLOAT32_FIELD;
        case 116: //limbDamageMult
            return CB_FLOAT32_FIELD;
        case 117: //resistType
            return CB_SINT32_TYPE_FIELD;
        case 118: //sightUsage
            return CB_FLOAT32_FIELD;
        case 119: //semiFireDelayMin
            return CB_FLOAT32_FIELD;
        case 120: //semiFireDelayMax
            return CB_FLOAT32_FIELD;
        case 121: //unknown3
            return CB_FLOAT32_FIELD;
        case 122: //effectMod1
            return CB_UINT32_FIELD;
        case 123: //effectMod2
            return CB_UINT32_FIELD;
        case 124: //effectMod3
            return CB_UINT32_FIELD;
        case 125: //valueAMod1
            return CB_FLOAT32_FIELD;
        case 126: //valueAMod2
            return CB_FLOAT32_FIELD;
        case 127: //valueAMod3
            return CB_FLOAT32_FIELD;
        case 128: //overridePwrAtkAnim
            return CB_UINT32_TYPE_FIELD;
        case 129: //strengthReq
            return CB_UINT32_FIELD;
        case 130: //unknown4
            return CB_UINT8_FIELD;
        case 131: //reloadAnimMod
            return CB_UINT8_TYPE_FIELD;
        case 132: //unknown5
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
        case 133: //regenRate
            return CB_FLOAT32_FIELD;
        case 134: //killImpulse
            return CB_FLOAT32_FIELD;
        case 135: //valueBMod1
            return CB_FLOAT32_FIELD;
        case 136: //valueBMod2
            return CB_FLOAT32_FIELD;
        case 137: //valueBMod3
            return CB_FLOAT32_FIELD;
        case 138: //skillReq
            return CB_UINT32_FIELD;
        case 139: //critDamage
            return CB_UINT16_FIELD;
        case 140: //unused1
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
        case 141: //critMult
            return CB_FLOAT32_FIELD;
        case 142: //critFlags
            return CB_UINT8_FLAG_FIELD;
        case 143: //unused2
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
        case 144: //critEffect
            return CB_FORMID_FIELD;
        case 145: //vatsEffect
            return CB_FORMID_FIELD;
        case 146: //vatsSkill
            return CB_FLOAT32_FIELD;
        case 147: //vatsDamageMult
            return CB_FLOAT32_FIELD;
        case 148: //AP
            return CB_FLOAT32_FIELD;
        case 149: //silenceType
            return CB_UINT8_TYPE_FIELD;
        case 150: //modRequiredType
            return CB_UINT8_TYPE_FIELD;
        case 151: //unused3
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
        case 152: //soundLevelType
            return CB_UINT32_TYPE_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * WEAPRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags
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
        case 19: //iconPath
            return ICON.value;
        case 20: //smallIconPath
            return MICO.value;
        case 21: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 22: //effect
            return EITM.IsLoaded() ? &EITM.value : NULL;
        case 23: //chargeAmount
            return EAMT.IsLoaded() ? &EAMT.value : NULL;
        case 24: //ammo
            return NAM0.IsLoaded() ? &NAM0.value : NULL;
        case 25: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 26: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 27: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 28: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 29: //destructableStages
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
        case 30: //repairList
            return REPL.IsLoaded() ? &REPL.value : NULL;
        case 31: //equipmentType
            return ETYP.IsLoaded() ? &ETYP.value : NULL;
        case 32: //modelList
            return BIPL.IsLoaded() ? &BIPL.value : NULL;
        case 33: //pickupSound
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 34: //dropSound
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 35: //shell_modPath
            return MOD2.IsLoaded() ? MOD2->MODL.value : NULL;
        case 36: //shell_modt_p
            *FieldValues = MOD2.IsLoaded() ? MOD2->MODT.value : NULL;
            return NULL;
        case 37: //shell_altTextures
            if(!MOD2.IsLoaded())
                return NULL;

            if(ListIndex >= MOD2->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MOD2->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MOD2->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MOD2->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 38: //scope_modPath
            return MOD2.IsLoaded() ? MOD2->MODL.value : NULL;
        case 39: //scope_modt_p
            *FieldValues = MOD2.IsLoaded() ? MOD2->MODT.value : NULL;
            return NULL;
        case 40: //scope_altTextures
            if(!MOD2.IsLoaded())
                return NULL;

            if(ListIndex >= MOD2->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MOD2->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MOD2->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MOD2->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 41: //scopeEffect
            return EFSD.IsLoaded() ? &EFSD.value : NULL;
        case 42: //world_modPath
            return MOD2.IsLoaded() ? MOD2->MODL.value : NULL;
        case 43: //world_modt_p
            *FieldValues = MOD2.IsLoaded() ? MOD2->MODT.value : NULL;
            return NULL;
        case 44: //world_altTextures
            if(!MOD2.IsLoaded())
                return NULL;

            if(ListIndex >= MOD2->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MOD2->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MOD2->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MOD2->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 45: //vatsName
            return VANM.value;
        case 46: //weaponNode
            return NNAM.value;
        case 47: //mod1Path
            return MWD1.value;
        case 48: //mod2Path
            return MWD2.value;
        case 49: //mod12Path
            return MWD3.value;
        case 50: //mod3Path
            return MWD4.value;
        case 51: //mod13Path
            return MWD5.value;
        case 52: //mod23Path
            return MWD6.value;
        case 53: //mod123Path
            return MWD7.value;
        case 54: //impact
            return INAM.IsLoaded() ? &INAM.value : NULL;
        case 55: //model
            return WNAM.IsLoaded() ? &WNAM.value : NULL;
        case 56: //model1
            return WNM1.IsLoaded() ? &WNM1.value : NULL;
        case 57: //model2
            return WNM2.IsLoaded() ? &WNM2.value : NULL;
        case 58: //model12
            return WNM3.IsLoaded() ? &WNM3.value : NULL;
        case 59: //model3
            return WNM4.IsLoaded() ? &WNM4.value : NULL;
        case 60: //model13
            return WNM5.IsLoaded() ? &WNM5.value : NULL;
        case 61: //model23
            return WNM6.IsLoaded() ? &WNM6.value : NULL;
        case 62: //model123
            return WNM7.IsLoaded() ? &WNM7.value : NULL;
        case 63: //mod1
            return WMI1.IsLoaded() ? &WMI1.value : NULL;
        case 64: //mod2
            return WMI2.IsLoaded() ? &WMI2.value : NULL;
        case 65: //mod3
            return WMI3.IsLoaded() ? &WMI3.value : NULL;
        case 66: //sound3D
            return SNAM1.IsLoaded() ? &SNAM1.value : NULL;
        case 67: //soundDist
            return SNAM2.IsLoaded() ? &SNAM2.value : NULL;
        case 68: //sound2D
            return XNAM.IsLoaded() ? &XNAM.value : NULL;
        case 69: //sound3DLoop
            return NAM7.IsLoaded() ? &NAM7.value : NULL;
        case 70: //soundMelee
            return TNAM.IsLoaded() ? &TNAM.value : NULL;
        case 71: //soundBlock
            return NAM6.IsLoaded() ? &NAM6.value : NULL;
        case 72: //soundIdle
            return UNAM.IsLoaded() ? &UNAM.value : NULL;
        case 73: //soundEquip
            return NAM9.IsLoaded() ? &NAM9.value : NULL;
        case 74: //soundUnequip
            return NAM8.IsLoaded() ? &NAM8.value : NULL;
        case 75: //soundMod3D
            return WMS11.IsLoaded() ? &WMS11.value : NULL;
        case 76: //soundModDist
            return WMS12.IsLoaded() ? &WMS12.value : NULL;
        case 77: //soundMod2D
            return WMS2.IsLoaded() ? &WMS2.value : NULL;
        case 78: //value
            return &DATA.value.value;
        case 79: //health
            return &DATA.value.health;
        case 80: //weight
            return &DATA.value.weight;
        case 81: //damage
            return &DATA.value.damage;
        case 82: //clipSize
            return &DATA.value.clipSize;
        case 83: //animType
            return &DNAM.value.animType;
        case 84: //animMult
            return &DNAM.value.animMult;
        case 85: //reach
            return &DNAM.value.reach;
        case 86: //flags
            return &DNAM.value.flags1;
        case 87: //gripAnim
            return &DNAM.value.gripAnim;
        case 88: //ammoUse
            return &DNAM.value.ammoUse;
        case 89: //reloadAnim
            return &DNAM.value.reloadAnim;
        case 90: //minSpread
            return &DNAM.value.minSpread;
        case 91: //spread
            return &DNAM.value.spread;
        case 92: //unknown1
            return &DNAM.value.unknown1;
        case 93: //sightFOV
            return &DNAM.value.sightFOV;
        case 94: //unknown2
            return &DNAM.value.unknown2;
        case 95: //projectile
            return &DNAM.value.projectile;
        case 96: //VATSHitChance
            return &DNAM.value.VATSHitChance;
        case 97: //attackAnim
            return &DNAM.value.attackAnim;
        case 98: //projectileCount
            return &DNAM.value.projectileCount;
        case 99: //weaponAV
            return &DNAM.value.weaponAV;
        case 100: //minRange
            return &DNAM.value.minRange;
        case 101: //maxRange
            return &DNAM.value.maxRange;
        case 102: //onHit
            return &DNAM.value.onHit;
        case 103: //extraFlags
            return &DNAM.value.flags2;
        case 104: //animAttackMult
            return &DNAM.value.animAttackMult;
        case 105: //fireRate
            return &DNAM.value.fireRate;
        case 106: //overrideAP
            return &DNAM.value.overrideAP;
        case 107: //leftRumble
            return &DNAM.value.leftRumble;
        case 108: //timeRumble
            return &DNAM.value.timeRumble;
        case 109: //overrideDamageToWeapon
            return &DNAM.value.overrideDamageToWeapon;
        case 110: //reloadTime
            return &DNAM.value.reloadTime;
        case 111: //jamTime
            return &DNAM.value.jamTime;
        case 112: //aimArc
            return &DNAM.value.aimArc;
        case 113: //skill
            return &DNAM.value.skill;
        case 114: //rumbleType
            return &DNAM.value.rumbleType;
        case 115: //rumbleWavelength
            return &DNAM.value.rumbleWavelength;
        case 116: //limbDamageMult
            return &DNAM.value.limbDamageMult;
        case 117: //resistType
            return &DNAM.value.resistType;
        case 118: //sightUsage
            return &DNAM.value.sightUsage;
        case 119: //semiFireDelayMin
            return &DNAM.value.semiFireDelayMin;
        case 120: //semiFireDelayMax
            return &DNAM.value.semiFireDelayMax;
        case 121: //unknown3
            return &DNAM.value.unknown3;
        case 122: //effectMod1
            return &DNAM.value.effectMod1;
        case 123: //effectMod2
            return &DNAM.value.effectMod2;
        case 124: //effectMod3
            return &DNAM.value.effectMod3;
        case 125: //valueAMod1
            return &DNAM.value.valueAMod1;
        case 126: //valueAMod2
            return &DNAM.value.valueAMod2;
        case 127: //valueAMod3
            return &DNAM.value.valueAMod3;
        case 128: //overridePwrAtkAnim
            return &DNAM.value.overridePwrAtkAnim;
        case 129: //strengthReq
            return &DNAM.value.strengthReq;
        case 130: //unknown4
            return &DNAM.value.unknown4;
        case 131: //reloadAnimMod
            return &DNAM.value.reloadAnimMod;
        case 132: //unknown5
            *FieldValues = &DNAM.value.unknown5[0];
            return NULL;
        case 133: //regenRate
            return &DNAM.value.regenRate;
        case 134: //killImpulse
            return &DNAM.value.killImpulse;
        case 135: //valueBMod1
            return &DNAM.value.valueBMod1;
        case 136: //valueBMod2
            return &DNAM.value.valueBMod2;
        case 137: //valueBMod3
            return &DNAM.value.valueBMod3;
        case 138: //skillReq
            return &DNAM.value.skillReq;
        case 139: //critDamage
            return &CRDT.value.critDamage;
        case 140: //unused1
            *FieldValues = &CRDT.value.unused1[0];
            return NULL;
        case 141: //critMult
            return &CRDT.value.critMult;
        case 142: //critFlags
            return &CRDT.value.flags;
        case 143: //unused2
            *FieldValues = &CRDT.value.unused2[0];
            return NULL;
        case 144: //critEffect
            return &CRDT.value.effect;
        case 145: //vatsEffect
            return &VATS.value.effect;
        case 146: //vatsSkill
            return &VATS.value.skill;
        case 147: //vatsDamageMult
            return &VATS.value.damageMult;
        case 148: //AP
            return &VATS.value.AP;
        case 149: //silenceType
            return &VATS.value.silenceType;
        case 150: //modRequiredType
            return &VATS.value.modRequiredType;
        case 151: //unused3
            *FieldValues = &VATS.value.unused1[0];
            return NULL;
        case 152: //soundLevelType
            return &VNAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool WEAPRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags
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
        case 19: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 20: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 21: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 22: //effect
            EITM.value = *(FORMID *)FieldValue;
            return true;
        case 23: //chargeAmount
            EAMT.value = *(int16_t *)FieldValue;
            break;
        case 24: //ammo
            NAM0.value = *(FORMID *)FieldValue;
            return true;
        case 25: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(int32_t *)FieldValue;
            break;
        case 26: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(uint8_t *)FieldValue;
            break;
        case 27: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 28: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 29: //destructableStages
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
        case 30: //repairList
            REPL.value = *(FORMID *)FieldValue;
            return true;
        case 31: //equipmentType
            ETYP.value = *(int32_t *)FieldValue;
            break;
        case 32: //modelList
            BIPL.value = *(FORMID *)FieldValue;
            return true;
        case 33: //pickupSound
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 34: //dropSound
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 35: //shell_modPath
            MOD2.Load();
            MOD2->MODL.Copy((char *)FieldValue);
            break;
        case 36: //shell_modt_p
            MOD2.Load();
            MOD2->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 37: //shell_altTextures
            MOD2.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MOD2->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MOD2->Textures.MODS[ListIndex]->name;
                    MOD2->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MOD2->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MOD2->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MOD2->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MOD2->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 38: //scope_modPath
            MOD2.Load();
            MOD2->MODL.Copy((char *)FieldValue);
            break;
        case 39: //scope_modt_p
            MOD2.Load();
            MOD2->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 40: //scope_altTextures
            MOD2.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MOD2->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MOD2->Textures.MODS[ListIndex]->name;
                    MOD2->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MOD2->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MOD2->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MOD2->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MOD2->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 41: //scopeEffect
            EFSD.value = *(FORMID *)FieldValue;
            return true;
        case 42: //world_modPath
            MOD2.Load();
            MOD2->MODL.Copy((char *)FieldValue);
            break;
        case 43: //world_modt_p
            MOD2.Load();
            MOD2->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 44: //world_altTextures
            MOD2.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MOD2->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MOD2->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MOD2->Textures.MODS[ListIndex]->name;
                    MOD2->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MOD2->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MOD2->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MOD2->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MOD2->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 45: //vatsName
            VANM.Copy((char *)FieldValue);
            break;
        case 46: //weaponNode
            NNAM.Copy((char *)FieldValue);
            break;
        case 47: //mod1Path
            MWD1.Copy((char *)FieldValue);
            break;
        case 48: //mod2Path
            MWD2.Copy((char *)FieldValue);
            break;
        case 49: //mod12Path
            MWD3.Copy((char *)FieldValue);
            break;
        case 50: //mod3Path
            MWD4.Copy((char *)FieldValue);
            break;
        case 51: //mod13Path
            MWD5.Copy((char *)FieldValue);
            break;
        case 52: //mod23Path
            MWD6.Copy((char *)FieldValue);
            break;
        case 53: //mod123Path
            MWD7.Copy((char *)FieldValue);
            break;
        case 54: //impact
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 55: //model
            WNAM.value = *(FORMID *)FieldValue;
            return true;
        case 56: //model1
            WNM1.value = *(FORMID *)FieldValue;
            return true;
        case 57: //model2
            WNM2.value = *(FORMID *)FieldValue;
            return true;
        case 58: //model12
            WNM3.value = *(FORMID *)FieldValue;
            return true;
        case 59: //model3
            WNM4.value = *(FORMID *)FieldValue;
            return true;
        case 60: //model13
            WNM5.value = *(FORMID *)FieldValue;
            return true;
        case 61: //model23
            WNM6.value = *(FORMID *)FieldValue;
            return true;
        case 62: //model123
            WNM7.value = *(FORMID *)FieldValue;
            return true;
        case 63: //mod1
            WMI1.value = *(FORMID *)FieldValue;
            return true;
        case 64: //mod2
            WMI2.value = *(FORMID *)FieldValue;
            return true;
        case 65: //mod3
            WMI3.value = *(FORMID *)FieldValue;
            return true;
        case 66: //sound3D
            SNAM1.value = *(FORMID *)FieldValue;
            return true;
        case 67: //soundDist
            SNAM2.value = *(FORMID *)FieldValue;
            return true;
        case 68: //sound2D
            XNAM.value = *(FORMID *)FieldValue;
            return true;
        case 69: //sound3DLoop
            NAM7.value = *(FORMID *)FieldValue;
            return true;
        case 70: //soundMelee
            TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 71: //soundBlock
            NAM6.value = *(FORMID *)FieldValue;
            return true;
        case 72: //soundIdle
            UNAM.value = *(FORMID *)FieldValue;
            return true;
        case 73: //soundEquip
            NAM9.value = *(FORMID *)FieldValue;
            return true;
        case 74: //soundUnequip
            NAM8.value = *(FORMID *)FieldValue;
            return true;
        case 75: //soundMod3D
            WMS11.value = *(FORMID *)FieldValue;
            return true;
        case 76: //soundModDist
            WMS12.value = *(FORMID *)FieldValue;
            return true;
        case 77: //soundMod2D
            WMS2.value = *(FORMID *)FieldValue;
            return true;
        case 78: //value
            DATA.value.value = *(int32_t *)FieldValue;
            break;
        case 79: //health
            DATA.value.health = *(int32_t *)FieldValue;
            break;
        case 80: //weight
            DATA.value.weight = *(float *)FieldValue;
            break;
        case 81: //damage
            DATA.value.damage = *(int16_t *)FieldValue;
            break;
        case 82: //clipSize
            DATA.value.clipSize = *(uint8_t *)FieldValue;
            break;
        case 83: //animType
            SetType(*(uint32_t *)FieldValue);
            break;
        case 84: //animMult
            DNAM.value.animMult = *(float *)FieldValue;
            break;
        case 85: //reach
            DNAM.value.reach = *(float *)FieldValue;
            break;
        case 86: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 87: //gripAnim
            SetGripType(*(uint8_t *)FieldValue);
            break;
        case 88: //ammoUse
            DNAM.value.ammoUse = *(uint8_t *)FieldValue;
            break;
        case 89: //reloadAnim
            SetReloadType(*(uint8_t *)FieldValue);
            break;
        case 90: //minSpread
            DNAM.value.minSpread = *(float *)FieldValue;
            break;
        case 91: //spread
            DNAM.value.spread = *(float *)FieldValue;
            break;
        case 92: //unknown1
            DNAM.value.unknown1 = *(float *)FieldValue;
            break;
        case 93: //sightFOV
            DNAM.value.sightFOV = *(float *)FieldValue;
            break;
        case 94: //unknown2
            DNAM.value.unknown2 = *(float *)FieldValue;
            break;
        case 95: //projectile
            DNAM.value.projectile = *(FORMID *)FieldValue;
            return true;
        case 96: //VATSHitChance
            DNAM.value.VATSHitChance = *(uint8_t *)FieldValue;
            break;
        case 97: //attackAnim
            SetAttackType(*(uint8_t *)FieldValue);
            break;
        case 98: //projectileCount
            DNAM.value.projectileCount = *(uint8_t *)FieldValue;
            break;
        case 99: //weaponAV
            SetEmbeddedAVType(*(uint8_t *)FieldValue);
            break;
        case 100: //minRange
            DNAM.value.minRange = *(float *)FieldValue;
            break;
        case 101: //maxRange
            DNAM.value.maxRange = *(float *)FieldValue;
            break;
        case 102: //onHit
            SetOnHitType(*(uint32_t *)FieldValue);
            break;
        case 103: //extraFlags
            SetAdvFlagMask(*(uint32_t *)FieldValue);
            break;
        case 104: //animAttackMult
            DNAM.value.animAttackMult = *(float *)FieldValue;
            break;
        case 105: //fireRate
            DNAM.value.fireRate = *(float *)FieldValue;
            break;
        case 106: //overrideAP
            DNAM.value.overrideAP = *(float *)FieldValue;
            break;
        case 107: //leftRumble
            DNAM.value.leftRumble = *(float *)FieldValue;
            break;
        case 108: //timeRumble
            DNAM.value.timeRumble = *(float *)FieldValue;
            break;
        case 109: //overrideDamageToWeapon
            DNAM.value.overrideDamageToWeapon = *(float *)FieldValue;
            break;
        case 110: //reloadTime
            DNAM.value.reloadTime = *(float *)FieldValue;
            break;
        case 111: //jamTime
            DNAM.value.jamTime = *(float *)FieldValue;
            break;
        case 112: //aimArc
            DNAM.value.aimArc = *(float *)FieldValue;
            break;
        case 113: //skill
            DNAM.value.skill = *(int32_t *)FieldValue;
            break;
        case 114: //rumbleType
            SetRumbleType(*(uint32_t *)FieldValue);
            break;
        case 115: //rumbleWavelength
            DNAM.value.rumbleWavelength = *(float *)FieldValue;
            break;
        case 116: //limbDamageMult
            DNAM.value.limbDamageMult = *(float *)FieldValue;
            break;
        case 117: //resistType
            DNAM.value.resistType = *(int32_t *)FieldValue;
            break;
        case 118: //sightUsage
            DNAM.value.sightUsage = *(float *)FieldValue;
            break;
        case 119: //semiFireDelayMin
            DNAM.value.semiFireDelayMin = *(float *)FieldValue;
            break;
        case 120: //semiFireDelayMax
            DNAM.value.semiFireDelayMax = *(float *)FieldValue;
            break;
        case 121: //unknown3
            DNAM.value.unknown3 = *(float *)FieldValue;
            break;
        case 122: //effectMod1
            DNAM.value.effectMod1 = *(uint32_t *)FieldValue;
            break;
        case 123: //effectMod2
            DNAM.value.effectMod2 = *(uint32_t *)FieldValue;
            break;
        case 124: //effectMod3
            DNAM.value.effectMod3 = *(uint32_t *)FieldValue;
            break;
        case 125: //valueAMod1
            DNAM.value.valueAMod1 = *(float *)FieldValue;
            break;
        case 126: //valueAMod2
            DNAM.value.valueAMod2 = *(float *)FieldValue;
            break;
        case 127: //valueAMod3
            DNAM.value.valueAMod3 = *(float *)FieldValue;
            break;
        case 128: //overridePwrAtkAnim
            SetPowerAttackAnimOverrideType(*(uint32_t *)FieldValue);
            break;
        case 129: //strengthReq
            DNAM.value.strengthReq = *(uint32_t *)FieldValue;
            break;
        case 130: //unknown4
            DNAM.value.unknown4 = *(uint8_t *)FieldValue;
            break;
        case 131: //reloadAnimMod
            SetModType(*(uint8_t *)FieldValue);
            break;
        case 132: //unknown5
            if(ArraySize != 2)
                break;
            DNAM.value.unknown5[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM.value.unknown5[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 133: //regenRate
            DNAM.value.regenRate = *(float *)FieldValue;
            break;
        case 134: //killImpulse
            DNAM.value.killImpulse = *(float *)FieldValue;
            break;
        case 135: //valueBMod1
            DNAM.value.valueBMod1 = *(float *)FieldValue;
            break;
        case 136: //valueBMod2
            DNAM.value.valueBMod2 = *(float *)FieldValue;
            break;
        case 137: //valueBMod3
            DNAM.value.valueBMod3 = *(float *)FieldValue;
            break;
        case 138: //skillReq
            DNAM.value.skillReq = *(uint32_t *)FieldValue;
            break;
        case 139: //critDamage
            CRDT.value.critDamage = *(uint16_t *)FieldValue;
            break;
        case 140: //unused1
            if(ArraySize != 2)
                break;
            CRDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CRDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 141: //critMult
            CRDT.value.critMult = *(float *)FieldValue;
            break;
        case 142: //critFlags
            SetCritFlagMask(*(uint8_t *)FieldValue);
            break;
        case 143: //unused2
            if(ArraySize != 3)
                break;
            CRDT.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            CRDT.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            CRDT.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 144: //critEffect
            CRDT.value.effect = *(FORMID *)FieldValue;
            return true;
        case 145: //vatsEffect
            VATS.value.effect = *(FORMID *)FieldValue;
            return true;
        case 146: //vatsSkill
            VATS.value.skill = *(float *)FieldValue;
            break;
        case 147: //vatsDamageMult
            VATS.value.damageMult = *(float *)FieldValue;
            break;
        case 148: //AP
            VATS.value.AP = *(float *)FieldValue;
            break;
        case 149: //silenceType
            SetVATSSilenceType(*(uint8_t *)FieldValue);
            break;
        case 150: //modRequiredType
            SetVATSModType(*(uint8_t *)FieldValue);
            break;
        case 151: //unused3
            if(ArraySize != 2)
                break;
            VATS.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            VATS.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 152: //soundLevelType
            SetSoundLevelType(*(uint32_t *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void WEAPRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    WEAPDATA defaultDATA;
    WEAPDNAM defaultDNAM;
    WEAPCRDT defaultCRDT;
    WEAPVATS defaultVATS;
    switch(FieldID)
        {
        case 1: //flags
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
        case 19: //iconPath
            ICON.Unload();
            return;
        case 20: //smallIconPath
            MICO.Unload();
            return;
        case 21: //script
            SCRI.Unload();
            return;
        case 22: //effect
            EITM.Unload();
            return;
        case 23: //chargeAmount
            EAMT.Unload();
            return;
        case 24: //ammo
            NAM0.Unload();
            return;
        case 25: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 26: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 27: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 28: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 29: //destructableStages
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
        case 30: //repairList
            REPL.Unload();
            return;
        case 31: //equipmentType
            ETYP.Unload();
            return;
        case 32: //modelList
            BIPL.Unload();
            return;
        case 33: //pickupSound
            YNAM.Unload();
            return;
        case 34: //dropSound
            ZNAM.Unload();
            return;
        case 35: //shell_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            return;
        case 36: //shell_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            return;
        case 37: //shell_altTextures
            if(MOD2.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MOD2->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MOD2->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MOD2->Textures.MODS[ListIndex]->name;
                        MOD2->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MOD2->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MOD2->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 38: //scope_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            return;
        case 39: //scope_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            return;
        case 40: //scope_altTextures
            if(MOD2.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MOD2->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MOD2->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MOD2->Textures.MODS[ListIndex]->name;
                        MOD2->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MOD2->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MOD2->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 41: //scopeEffect
            EFSD.Unload();
            return;
        case 42: //world_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            return;
        case 43: //world_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            return;
        case 44: //world_altTextures
            if(MOD2.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MOD2->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MOD2->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MOD2->Textures.MODS[ListIndex]->name;
                        MOD2->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MOD2->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MOD2->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 45: //vatsName
            VANM.Unload();
            return;
        case 46: //weaponNode
            NNAM.Unload();
            return;
        case 47: //mod1Path
            MWD1.Unload();
            return;
        case 48: //mod2Path
            MWD2.Unload();
            return;
        case 49: //mod12Path
            MWD3.Unload();
            return;
        case 50: //mod3Path
            MWD4.Unload();
            return;
        case 51: //mod13Path
            MWD5.Unload();
            return;
        case 52: //mod23Path
            MWD6.Unload();
            return;
        case 53: //mod123Path
            MWD7.Unload();
            return;
        case 54: //impact
            INAM.Unload();
            return;
        case 55: //model
            WNAM.Unload();
            return;
        case 56: //model1
            WNM1.Unload();
            return;
        case 57: //model2
            WNM2.Unload();
            return;
        case 58: //model12
            WNM3.Unload();
            return;
        case 59: //model3
            WNM4.Unload();
            return;
        case 60: //model13
            WNM5.Unload();
            return;
        case 61: //model23
            WNM6.Unload();
            return;
        case 62: //model123
            WNM7.Unload();
            return;
        case 63: //mod1
            WMI1.Unload();
            return;
        case 64: //mod2
            WMI2.Unload();
            return;
        case 65: //mod3
            WMI3.Unload();
            return;
        case 66: //sound3D
            SNAM1.Unload();
            return;
        case 67: //soundDist
            SNAM2.Unload();
            return;
        case 68: //sound2D
            XNAM.Unload();
            return;
        case 69: //sound3DLoop
            NAM7.Unload();
            return;
        case 70: //soundMelee
            TNAM.Unload();
            return;
        case 71: //soundBlock
            NAM6.Unload();
            return;
        case 72: //soundIdle
            UNAM.Unload();
            return;
        case 73: //soundEquip
            NAM9.Unload();
            return;
        case 74: //soundUnequip
            NAM8.Unload();
            return;
        case 75: //soundMod3D
            WMS11.Unload();
            return;
        case 76: //soundModDist
            WMS12.Unload();
            return;
        case 77: //soundMod2D
            WMS2.Unload();
            return;
        case 78: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 79: //health
            DATA.value.health = defaultDATA.health;
            return;
        case 80: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        case 81: //damage
            DATA.value.damage = defaultDATA.damage;
            return;
        case 82: //clipSize
            DATA.value.clipSize = defaultDATA.clipSize;
            return;
        case 83: //animType
            SetType(defaultDNAM.animType);
            return;
        case 84: //animMult
            DNAM.value.animMult = defaultDNAM.animMult;
            return;
        case 85: //reach
            DNAM.value.reach = defaultDNAM.reach;
            return;
        case 86: //flags
            SetFlagMask(defaultDNAM.flags1);
            return;
        case 87: //gripAnim
            SetGripType(defaultDNAM.gripAnim);
            return;
        case 88: //ammoUse
            DNAM.value.ammoUse = defaultDNAM.ammoUse;
            return;
        case 89: //reloadAnim
            SetReloadType(defaultDNAM.reloadAnim);
            return;
        case 90: //minSpread
            DNAM.value.minSpread = defaultDNAM.minSpread;
            return;
        case 91: //spread
            DNAM.value.spread = defaultDNAM.spread;
            return;
        case 92: //unknown1
            DNAM.value.unknown1 = defaultDNAM.unknown1;
            return;
        case 93: //sightFOV
            DNAM.value.sightFOV = defaultDNAM.sightFOV;
            return;
        case 94: //unknown2
            DNAM.value.unknown2 = defaultDNAM.unknown2;
            return;
        case 95: //projectile
            DNAM.value.projectile = defaultDNAM.projectile;
            return;
        case 96: //VATSHitChance
            DNAM.value.VATSHitChance = defaultDNAM.VATSHitChance;
            return;
        case 97: //attackAnim
            SetAttackType(defaultDNAM.attackAnim);
            return;
        case 98: //projectileCount
            DNAM.value.projectileCount = defaultDNAM.projectileCount;
            return;
        case 99: //weaponAV
            SetEmbeddedAVType(defaultDNAM.weaponAV);
            return;
        case 100: //minRange
            DNAM.value.minRange = defaultDNAM.minRange;
            return;
        case 101: //maxRange
            DNAM.value.maxRange = defaultDNAM.maxRange;
            return;
        case 102: //onHit
            SetOnHitType(defaultDNAM.onHit);
            return;
        case 103: //extraFlags
            SetAdvFlagMask(defaultDNAM.flags2);
            return;
        case 104: //animAttackMult
            DNAM.value.animAttackMult = defaultDNAM.animAttackMult;
            return;
        case 105: //fireRate
            DNAM.value.fireRate = defaultDNAM.fireRate;
            return;
        case 106: //overrideAP
            DNAM.value.overrideAP = defaultDNAM.overrideAP;
            return;
        case 107: //leftRumble
            DNAM.value.leftRumble = defaultDNAM.leftRumble;
            return;
        case 108: //timeRumble
            DNAM.value.timeRumble = defaultDNAM.timeRumble;
            return;
        case 109: //overrideDamageToWeapon
            DNAM.value.overrideDamageToWeapon = defaultDNAM.overrideDamageToWeapon;
            return;
        case 110: //reloadTime
            DNAM.value.reloadTime = defaultDNAM.reloadTime;
            return;
        case 111: //jamTime
            DNAM.value.jamTime = defaultDNAM.jamTime;
            return;
        case 112: //aimArc
            DNAM.value.aimArc = defaultDNAM.aimArc;
            return;
        case 113: //skill
            DNAM.value.skill = defaultDNAM.skill;
            return;
        case 114: //rumbleType
            SetRumbleType(defaultDNAM.rumbleType);
            return;
        case 115: //rumbleWavelength
            DNAM.value.rumbleWavelength = defaultDNAM.rumbleWavelength;
            return;
        case 116: //limbDamageMult
            DNAM.value.limbDamageMult = defaultDNAM.limbDamageMult;
            return;
        case 117: //resistType
            DNAM.value.resistType = defaultDNAM.resistType;
            return;
        case 118: //sightUsage
            DNAM.value.sightUsage = defaultDNAM.sightUsage;
            return;
        case 119: //semiFireDelayMin
            DNAM.value.semiFireDelayMin = defaultDNAM.semiFireDelayMin;
            return;
        case 120: //semiFireDelayMax
            DNAM.value.semiFireDelayMax = defaultDNAM.semiFireDelayMax;
            return;
        case 121: //unknown3
            DNAM.value.unknown3 = defaultDNAM.unknown3;
            return;
        case 122: //effectMod1
            DNAM.value.effectMod1 = defaultDNAM.effectMod1;
            return;
        case 123: //effectMod2
            DNAM.value.effectMod2 = defaultDNAM.effectMod2;
            return;
        case 124: //effectMod3
            DNAM.value.effectMod3 = defaultDNAM.effectMod3;
            return;
        case 125: //valueAMod1
            DNAM.value.valueAMod1 = defaultDNAM.valueAMod1;
            return;
        case 126: //valueAMod2
            DNAM.value.valueAMod2 = defaultDNAM.valueAMod2;
            return;
        case 127: //valueAMod3
            DNAM.value.valueAMod3 = defaultDNAM.valueAMod3;
            return;
        case 128: //overridePwrAtkAnim
            SetPowerAttackAnimOverrideType(defaultDNAM.overridePwrAtkAnim);
            return;
        case 129: //strengthReq
            DNAM.value.strengthReq = defaultDNAM.strengthReq;
            return;
        case 130: //unknown4
            DNAM.value.unknown4 = defaultDNAM.unknown4;
            return;
        case 131: //reloadAnimMod
            SetModType(defaultDNAM.reloadAnimMod);
            return;
        case 132: //unknown5
            DNAM.value.unknown5[0] = defaultDNAM.unknown5[0];
            DNAM.value.unknown5[1] = defaultDNAM.unknown5[1];
            return;
        case 133: //regenRate
            DNAM.value.regenRate = defaultDNAM.regenRate;
            return;
        case 134: //killImpulse
            DNAM.value.killImpulse = defaultDNAM.killImpulse;
            return;
        case 135: //valueBMod1
            DNAM.value.valueBMod1 = defaultDNAM.valueBMod1;
            return;
        case 136: //valueBMod2
            DNAM.value.valueBMod2 = defaultDNAM.valueBMod2;
            return;
        case 137: //valueBMod3
            DNAM.value.valueBMod3 = defaultDNAM.valueBMod3;
            return;
        case 138: //skillReq
            DNAM.value.skillReq = defaultDNAM.skillReq;
            return;
        case 139: //critDamage
            CRDT.value.critDamage = defaultCRDT.critDamage;
            return;
        case 140: //unused1
            CRDT.value.unused1[0] = defaultCRDT.unused1[0];
            CRDT.value.unused1[1] = defaultCRDT.unused1[1];
            return;
        case 141: //critMult
            CRDT.value.critMult = defaultCRDT.critMult;
            return;
        case 142: //critFlags
            SetCritFlagMask(defaultCRDT.flags);
            return;
        case 143: //unused2
            CRDT.value.unused2[0] = defaultCRDT.unused2[0];
            CRDT.value.unused2[1] = defaultCRDT.unused2[1];
            CRDT.value.unused2[2] = defaultCRDT.unused2[2];
            return;
        case 144: //critEffect
            CRDT.value.effect = defaultCRDT.effect;
            return;
        case 145: //vatsEffect
            VATS.value.effect = defaultVATS.effect;
            return;
        case 146: //vatsSkill
            VATS.value.skill = defaultVATS.skill;
            return;
        case 147: //vatsDamageMult
            VATS.value.damageMult = defaultVATS.damageMult;
            return;
        case 148: //AP
            VATS.value.AP = defaultVATS.AP;
            return;
        case 149: //silenceType
            SetVATSSilenceType(defaultVATS.silenceType);
            return;
        case 150: //modRequiredType
            SetVATSModType(defaultVATS.modRequiredType);
            return;
        case 151: //unused3
            VATS.value.unused1[0] = defaultVATS.unused1[0];
            VATS.value.unused1[1] = defaultVATS.unused1[1];
            return;
        case 152: //soundLevelType
            VNAM.Unload();
            break;
        default:
            return;
        }
    }
}