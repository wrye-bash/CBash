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
#include "..\MGEFRecord.h"

namespace FNV
{
uint32_t MGEFRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //full
            return CB_STRING_FIELD;
        case 8: //description
            return CB_STRING_FIELD;
        case 9: //iconPath
            return CB_ISTRING_FIELD;
        case 10: //smallIconPath
            return CB_ISTRING_FIELD;
        case 11: //modPath
            return CB_ISTRING_FIELD;
        case 12: //modb
            return CB_FLOAT32_FIELD;
        case 13: //modt_p
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
        case 14: //altTextures
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
        case 15: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 16: //flags
            return CB_UINT32_FLAG_FIELD;
        case 17: //baseCostUnused
            return CB_FLOAT32_FIELD;
        case 18: //associated
            return CB_FORMID_FIELD;
        case 19: //schoolUnused
            return CB_UINT32_TYPE_FIELD;
        case 20: //resistType
            return CB_SINT32_TYPE_FIELD;
        case 21: //numCounters
            return CB_UINT16_FIELD;
        case 22: //unused1
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
        case 23: //light
            return CB_FORMID_FIELD;
        case 24: //projectileSpeed
            return CB_FLOAT32_FIELD;
        case 25: //effectShader
            return CB_FORMID_FIELD;
        case 26: //displayShader
            return CB_FORMID_FIELD;
        case 27: //effectSound
            return CB_FORMID_FIELD;
        case 28: //boltSound
            return CB_FORMID_FIELD;
        case 29: //hitSound
            return CB_FORMID_FIELD;
        case 30: //areaSound
            return CB_FORMID_FIELD;
        case 31: //cefEnchantmentUnused
            return CB_FLOAT32_FIELD;
        case 32: //cefBarterUnused
            return CB_FLOAT32_FIELD;
        case 33: //archType
            return CB_UINT32_TYPE_FIELD;
        case 34: //actorValue
            return CB_SINT32_TYPE_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * MGEFRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full
            return FULL.value;
        case 8: //description
            return DESC.value;
        case 9: //iconPath
            return ICON.value;
        case 10: //smallIconPath
            return MICO.value;
        case 11: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 12: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 13: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 14: //altTextures
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
        case 15: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 16: //flags
            return &DATA.value.flags;
        case 17: //baseCostUnused
            return &DATA.value.baseCost;
        case 18: //associated
            return &DATA.value.associated;
        case 19: //schoolUnused
            return &DATA.value.schoolType;
        case 20: //resistType
            return &DATA.value.resistType;
        case 21: //numCounters
            return &DATA.value.numCounters;
        case 22: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 23: //light
            return &DATA.value.light;
        case 24: //projectileSpeed
            return &DATA.value.projectileSpeed;
        case 25: //effectShader
            return &DATA.value.effectShader;
        case 26: //displayShader
            return &DATA.value.displayShader;
        case 27: //effectSound
            return &DATA.value.effectSound;
        case 28: //boltSound
            return &DATA.value.boltSound;
        case 29: //hitSound
            return &DATA.value.hitSound;
        case 30: //areaSound
            return &DATA.value.areaSound;
        case 31: //cefEnchantmentUnused
            return &DATA.value.cefEnchantment;
        case 32: //cefBarterUnused
            return &DATA.value.cefBarter;
        case 33: //archType
            return &DATA.value.archType;
        case 34: //actorValue
            return &DATA.value.actorValue;
        default:
            return NULL;
        }
    return NULL;
    }

bool MGEFRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 8: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 9: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 10: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 11: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 12: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 13: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //altTextures
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
        case 15: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 16: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 17: //baseCostUnused
            DATA.value.baseCost = *(float *)FieldValue;
            break;
        case 18: //associated
            DATA.value.associated = *(FORMID *)FieldValue;
            return true;
        case 19: //schoolUnused
            DATA.value.schoolType = *(uint32_t *)FieldValue;
            break;
        case 20: //resistType
            DATA.value.resistType = *(int32_t *)FieldValue;
            break;
        case 21: //numCounters
            DATA.value.numCounters = *(uint16_t *)FieldValue;
            break;
        case 22: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 23: //light
            DATA.value.light = *(FORMID *)FieldValue;
            return true;
        case 24: //projectileSpeed
            DATA.value.projectileSpeed = *(float *)FieldValue;
            break;
        case 25: //effectShader
            DATA.value.effectShader = *(FORMID *)FieldValue;
            return true;
        case 26: //displayShader
            DATA.value.displayShader = *(FORMID *)FieldValue;
            return true;
        case 27: //effectSound
            DATA.value.effectSound = *(FORMID *)FieldValue;
            return true;
        case 28: //boltSound
            DATA.value.boltSound = *(FORMID *)FieldValue;
            return true;
        case 29: //hitSound
            DATA.value.hitSound = *(FORMID *)FieldValue;
            return true;
        case 30: //areaSound
            DATA.value.areaSound = *(FORMID *)FieldValue;
            return true;
        case 31: //cefEnchantmentUnused
            DATA.value.cefEnchantment = *(float *)FieldValue;
            break;
        case 32: //cefBarterUnused
            DATA.value.cefBarter = *(float *)FieldValue;
            break;
        case 33: //archType
            SetType(*(uint32_t *)FieldValue);
            break;
        case 34: //actorValue
            DATA.value.actorValue = *(int32_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void MGEFRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FNVMODS defaultMODS;
    MGEFDATA defaultDATA;
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //description
            DESC.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //smallIconPath
            MICO.Unload();
            return;
        case 11: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 12: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 13: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 14: //altTextures
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
        case 15: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 16: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 17: //baseCostUnused
            DATA.value.baseCost = defaultDATA.baseCost;
            return;
        case 18: //associated
            DATA.value.associated = defaultDATA.associated;
            return;
        case 19: //schoolUnused
            DATA.value.schoolType = defaultDATA.schoolType;
            return;
        case 20: //resistType
            DATA.value.resistType = defaultDATA.resistType;
            return;
        case 21: //numCounters
            DATA.value.numCounters = defaultDATA.numCounters;
            return;
        case 22: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 23: //light
            DATA.value.light = defaultDATA.light ;
            return;
        case 24: //projectileSpeed
            DATA.value.projectileSpeed = defaultDATA.projectileSpeed;
            return;
        case 25: //effectShader
            DATA.value.effectShader = defaultDATA.effectShader;
            return;
        case 26: //displayShader
            DATA.value.displayShader = defaultDATA.displayShader;
            return;
        case 27: //effectSound
            DATA.value.effectSound = defaultDATA.effectSound;
            return;
        case 28: //boltSound
            DATA.value.boltSound = defaultDATA.boltSound;
            return;
        case 29: //hitSound
            DATA.value.hitSound = defaultDATA.hitSound;
            return;
        case 30: //areaSound
            DATA.value.areaSound = defaultDATA.areaSound;
            return;
        case 31: //cefEnchantmentUnused
            DATA.value.cefEnchantment = defaultDATA.cefEnchantment;
            return;
        case 32: //cefBarterUnused
            DATA.value.cefBarter = defaultDATA.cefBarter;
            return;
        case 33: //archType
            SetType(defaultDATA.archType);
            return;
        case 34: //actorValue
            DATA.value.actorValue = defaultDATA.actorValue;
            return;
        default:
            return;
        }
    }
}