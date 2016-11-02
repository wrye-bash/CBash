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
#include "..\BPTDRecord.h"

namespace FNV
{
uint32_t BPTDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //modPath
            return CB_ISTRING_FIELD;
        case 8: //modb
            return CB_FLOAT32_FIELD;
        case 9: //modt_p
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
        case 10: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.MODS.size();
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
        case 11: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 12: //parts
            if(ListFieldID == 0) //parts
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Parts.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Parts.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_ISTRING_FIELD;
                case 2: //node
                    return CB_ISTRING_FIELD;
                case 3: //vats
                    return CB_ISTRING_FIELD;
                case 4: //IKData
                    return CB_ISTRING_FIELD;
                case 5: //damageMult
                    return CB_FLOAT32_FIELD;
                case 6: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 7: //partType
                    return CB_UINT8_TYPE_FIELD;
                case 8: //healthPercent
                    return CB_UINT8_FIELD;
                case 9: //actorValue
                    return CB_SINT8_FIELD;
                case 10: //hitChance
                    return CB_UINT8_FIELD;
                case 11: //explodableExplosionChance
                    return CB_UINT8_FIELD;
                case 12: //explodableDebrisCount
                    return CB_UINT16_FIELD;
                case 13: //explodableDebris
                    return CB_FORMID_FIELD;
                case 14: //explodableExplosion
                    return CB_FORMID_FIELD;
                case 15: //maxTrackAngle
                    return CB_FLOAT32_FIELD;
                case 16: //explodableDebrisScale
                    return CB_FLOAT32_FIELD;
                case 17: //severableDebrisCount
                    return CB_SINT32_FIELD;
                case 18: //severableDebris
                    return CB_FORMID_FIELD;
                case 19: //severableExplosion
                    return CB_FORMID_FIELD;
                case 20: //severableDebrisScale
                    return CB_FLOAT32_FIELD;
                case 21: //transX
                    return CB_FLOAT32_FIELD;
                case 22: //transY
                    return CB_FLOAT32_FIELD;
                case 23: //transZ
                    return CB_FLOAT32_FIELD;
                case 24: //rotX
                    return CB_RADIAN_FIELD;
                case 25: //rotY
                    return CB_RADIAN_FIELD;
                case 26: //rotZ
                    return CB_RADIAN_FIELD;
                case 27: //severableImpact
                    return CB_FORMID_FIELD;
                case 28: //explodableImpact
                    return CB_FORMID_FIELD;
                case 29: //severableDecalCount
                    return CB_UINT8_FIELD;
                case 30: //explodableDecalCount
                    return CB_UINT8_FIELD;
                case 31: //unused1
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
                case 32: //limbReplaceScale
                    return CB_FLOAT32_FIELD;
                case 33: //limbReplaceModPath
                    return CB_STRING_FIELD;
                case 34: //goreBone
                    return CB_STRING_FIELD;
                case 35: //nam5_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Parts.value[0]->NAM5.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 13: //ragdoll
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * BPTDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 8: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 9: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 10: //altTextures
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
        case 11: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 12: //parts
            if(ListIndex >= Parts.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return Parts.value[ListIndex]->BPTN.value;
                case 2: //node
                    return Parts.value[ListIndex]->BPNN.value;
                case 3: //vats
                    return Parts.value[ListIndex]->BPNT.value;
                case 4: //IKData
                    return Parts.value[ListIndex]->BPNI.value;
                case 5: //damageMult
                    return &Parts.value[ListIndex]->BPND.value.damageMult;
                case 6: //flags
                    return &Parts.value[ListIndex]->BPND.value.flags;
                case 7: //partType
                    return &Parts.value[ListIndex]->BPND.value.partType;
                case 8: //healthPercent
                    return &Parts.value[ListIndex]->BPND.value.healthPercent;
                case 9: //actorValue
                    return &Parts.value[ListIndex]->BPND.value.actorValue;
                case 10: //hitChance
                    return &Parts.value[ListIndex]->BPND.value.hitChance;
                case 11: //explodableExplosionChance
                    return &Parts.value[ListIndex]->BPND.value.explodableExplosionChance;
                case 12: //explodableDebrisCount
                    return &Parts.value[ListIndex]->BPND.value.explodableDebrisCount;
                case 13: //explodableDebris
                    return &Parts.value[ListIndex]->BPND.value.explodableDebris;
                case 14: //explodableExplosion
                    return &Parts.value[ListIndex]->BPND.value.explodableExplosion;
                case 15: //maxTrackAngle
                    return &Parts.value[ListIndex]->BPND.value.maxTrackAngle;
                case 16: //explodableDebrisScale
                    return &Parts.value[ListIndex]->BPND.value.explodableDebrisScale;
                case 17: //severableDebrisCount
                    return &Parts.value[ListIndex]->BPND.value.severableDebrisCount;
                case 18: //severableDebris
                    return &Parts.value[ListIndex]->BPND.value.severableDebris;
                case 19: //severableExplosion
                    return &Parts.value[ListIndex]->BPND.value.severableExplosion;
                case 20: //severableDebrisScale
                    return &Parts.value[ListIndex]->BPND.value.severableDebrisScale;
                case 21: //transX
                    return &Parts.value[ListIndex]->BPND.value.transX;
                case 22: //transY
                    return &Parts.value[ListIndex]->BPND.value.transY;
                case 23: //transZ
                    return &Parts.value[ListIndex]->BPND.value.transZ;
                case 24: //rotX
                    return &Parts.value[ListIndex]->BPND.value.rotX;
                case 25: //rotY
                    return &Parts.value[ListIndex]->BPND.value.rotY;
                case 26: //rotZ
                    return &Parts.value[ListIndex]->BPND.value.rotZ;
                case 27: //severableImpact
                    return &Parts.value[ListIndex]->BPND.value.severableImpact;
                case 28: //explodableImpact
                    return &Parts.value[ListIndex]->BPND.value.explodableImpact;
                case 29: //severableDecalCount
                    return &Parts.value[ListIndex]->BPND.value.severableDecalCount;
                case 30: //explodableDecalCount
                    return &Parts.value[ListIndex]->BPND.value.explodableDecalCount;
                case 31: //unused1
                    *FieldValues = &Parts.value[ListIndex]->BPND.value.unused1[0];
                    return NULL;
                case 32: //limbReplaceScale
                    return &Parts.value[ListIndex]->BPND.value.limbReplaceScale;
                case 33: //limbReplaceModPath
                    return Parts.value[ListIndex]->NAM1.value;
                case 34: //goreBone
                    return Parts.value[ListIndex]->NAM4.value;
                case 35: //nam5_p
                    *FieldValues = Parts.value[ListIndex]->NAM5.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 13: //ragdoll
            return &RAGA.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool BPTDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 8: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //altTextures
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
        case 11: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 12: //parts
            if(ListFieldID == 0) //partsSize
                {
                Parts.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Parts.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    Parts.value[ListIndex]->BPTN.Copy((char *)FieldValue);
                    break;
                case 2: //node
                    Parts.value[ListIndex]->BPNN.Copy((char *)FieldValue);
                    break;
                case 3: //vats
                    Parts.value[ListIndex]->BPNT.Copy((char *)FieldValue);
                    break;
                case 4: //IKData
                    Parts.value[ListIndex]->BPNI.Copy((char *)FieldValue);
                    break;
                case 5: //damageMult
                    Parts.value[ListIndex]->BPND.value.damageMult = *(float *)FieldValue;
                    break;
                case 6: //flags
                    Parts.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 7: //partType
                    Parts.value[ListIndex]->SetType(*(uint8_t *)FieldValue);
                    break;
                case 8: //healthPercent
                    Parts.value[ListIndex]->BPND.value.healthPercent = *(uint8_t *)FieldValue;
                    break;
                case 9: //actorValue
                    Parts.value[ListIndex]->BPND.value.actorValue = *(int8_t *)FieldValue;
                    break;
                case 10: //hitChance
                    Parts.value[ListIndex]->BPND.value.hitChance = *(uint8_t *)FieldValue;
                    break;
                case 11: //explodableExplosionChance
                    Parts.value[ListIndex]->BPND.value.explodableExplosionChance = *(uint8_t *)FieldValue;
                    break;
                case 12: //explodableDebrisCount
                    Parts.value[ListIndex]->BPND.value.explodableDebrisCount = *(uint16_t *)FieldValue;
                    break;
                case 13: //explodableDebris
                    Parts.value[ListIndex]->BPND.value.explodableDebris = *(FORMID *)FieldValue;
                    return true;
                case 14: //explodableExplosion
                    Parts.value[ListIndex]->BPND.value.explodableExplosion = *(FORMID *)FieldValue;
                    return true;
                case 15: //maxTrackAngle
                    Parts.value[ListIndex]->BPND.value.maxTrackAngle = *(float *)FieldValue;
                    break;
                case 16: //explodableDebrisScale
                    Parts.value[ListIndex]->BPND.value.explodableDebrisScale = *(float *)FieldValue;
                    break;
                case 17: //severableDebrisCount
                    Parts.value[ListIndex]->BPND.value.severableDebrisCount = *(int32_t *)FieldValue;
                    break;
                case 18: //severableDebris
                    Parts.value[ListIndex]->BPND.value.severableDebris = *(FORMID *)FieldValue;
                    return true;
                case 19: //severableExplosion
                    Parts.value[ListIndex]->BPND.value.severableExplosion = *(FORMID *)FieldValue;
                    return true;
                case 20: //severableDebrisScale
                    Parts.value[ListIndex]->BPND.value.severableDebrisScale = *(float *)FieldValue;
                    break;
                case 21: //transX
                    Parts.value[ListIndex]->BPND.value.transX = *(float *)FieldValue;
                    break;
                case 22: //transY
                    Parts.value[ListIndex]->BPND.value.transY = *(float *)FieldValue;
                    break;
                case 23: //transZ
                    Parts.value[ListIndex]->BPND.value.transZ = *(float *)FieldValue;
                    break;
                case 24: //rotX
                    Parts.value[ListIndex]->BPND.value.rotX = *(float *)FieldValue;
                    break;
                case 25: //rotY
                    Parts.value[ListIndex]->BPND.value.rotY = *(float *)FieldValue;
                    break;
                case 26: //rotZ
                    Parts.value[ListIndex]->BPND.value.rotZ = *(float *)FieldValue;
                    break;
                case 27: //severableImpact
                    Parts.value[ListIndex]->BPND.value.severableImpact = *(FORMID *)FieldValue;
                    return true;
                case 28: //explodableImpact
                    Parts.value[ListIndex]->BPND.value.explodableImpact = *(FORMID *)FieldValue;
                    return true;
                case 29: //severableDecalCount
                    Parts.value[ListIndex]->BPND.value.severableDecalCount = *(uint8_t *)FieldValue;
                    break;
                case 30: //explodableDecalCount
                    Parts.value[ListIndex]->BPND.value.explodableDecalCount = *(uint8_t *)FieldValue;
                    break;
                case 31: //unused1
                    if(ArraySize != 2)
                        break;
                    Parts.value[ListIndex]->BPND.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Parts.value[ListIndex]->BPND.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 32: //limbReplaceScale
                    Parts.value[ListIndex]->BPND.value.limbReplaceScale = *(float *)FieldValue;
                    break;
                case 33: //limbReplaceModPath
                    Parts.value[ListIndex]->NAM1.Copy((char *)FieldValue);
                    break;
                case 34: //goreBone
                    Parts.value[ListIndex]->NAM4.Copy((char *)FieldValue);
                    break;
                case 35: //nam5_p
                    Parts.value[ListIndex]->NAM5.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 13: //ragdoll
            RAGA.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void BPTDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
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
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 10: //altTextures
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
                        MODL->Textures.MODS[ListIndex]->texture = 0; // defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = 0; // defaultMODS.index;
                        return;
                    default:
                        return;
                }
                }
            return;
        case 11: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 12: //parts
            if(ListFieldID == 0) //partsSize
                {
                Parts.Unload();
                return;
                }

            if(ListIndex >= Parts.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //name
                    Parts.value[ListIndex]->BPTN.Unload();
                    return;
                case 2: //node
                    Parts.value[ListIndex]->BPNN.Unload();
                    return;
                case 3: //vats
                    Parts.value[ListIndex]->BPNT.Unload();
                    return;
                case 4: //IKData
                    Parts.value[ListIndex]->BPNI.Unload();
                    return;
                case 5: //damageMult
                    Parts.value[ListIndex]->BPND.value.damageMult = 0; // defaultBPND.damageMult;
                    return;
                case 6: //flags
                    Parts.value[ListIndex]->SetFlagMask(0);  //defaultBPND.flags
                    return;
                case 7: //partType
                    Parts.value[ListIndex]->SetType(0); //defaultBPND.partType
                    return;
                case 8: //healthPercent
                    Parts.value[ListIndex]->BPND.value.healthPercent = 0; // defaultBPND.healthPercent;
                    return;
                case 9: //actorValue
                    Parts.value[ListIndex]->BPND.value.actorValue = 0; // defaultBPND.actorValue;
                    return;
                case 10: //hitChance
                    Parts.value[ListIndex]->BPND.value.hitChance = 0; // defaultBPND.hitChance;
                    return;
                case 11: //explodableExplosionChance
                    Parts.value[ListIndex]->BPND.value.explodableExplosionChance = 0; // defaultBPND.explodableExplosionChance;
                    return;
                case 12: //explodableDebrisCount
                    Parts.value[ListIndex]->BPND.value.explodableDebrisCount = 0; // defaultBPND.explodableDebrisCount;
                    return;
                case 13: //explodableDebris
                    Parts.value[ListIndex]->BPND.value.explodableDebris = 0; // defaultBPND.explodableDebris;
                    return;
                case 14: //explodableExplosion
                    Parts.value[ListIndex]->BPND.value.explodableExplosion = 0; // defaultBPND.explodableExplosion;
                    return;
                case 15: //maxTrackAngle
                    Parts.value[ListIndex]->BPND.value.maxTrackAngle = 0; //defaultBPND.maxTrackAngle;
                    return;
                case 16: //explodableDebrisScale
                    Parts.value[ListIndex]->BPND.value.explodableDebrisScale = 0; //defaultBPND.explodableDebrisScale;
                    return;
                case 17: //severableDebrisCount
                    Parts.value[ListIndex]->BPND.value.severableDebrisCount = 0; //defaultBPND.severableDebrisCount;
                    return;
                case 18: //severableDebris
                    Parts.value[ListIndex]->BPND.value.severableDebris = 0; //defaultBPND.severableDebris;
                    return;
                case 19: //severableExplosion
                    Parts.value[ListIndex]->BPND.value.severableExplosion = 0; //defaultBPND.severableExplosion;
                    return;
                case 20: //severableDebrisScale
                    Parts.value[ListIndex]->BPND.value.severableDebrisScale = 0; //defaultBPND.severableDebrisScale;
                    return;
                case 21: //transX
                    Parts.value[ListIndex]->BPND.value.transX = 0; //defaultBPND.transX;
                    return;
                case 22: //transY
                    Parts.value[ListIndex]->BPND.value.transY = 0; //defaultBPND.transY;
                    return;
                case 23: //transZ
                    Parts.value[ListIndex]->BPND.value.transZ = 0; //defaultBPND.transZ;
                    return;
                case 24: //rotX
                    Parts.value[ListIndex]->BPND.value.rotX = 0; //defaultBPND.rotX;
                    return;
                case 25: //rotY
                    Parts.value[ListIndex]->BPND.value.rotY = 0; //defaultBPND.rotY;
                    return;
                case 26: //rotZ
                    Parts.value[ListIndex]->BPND.value.rotZ = 0; //defaultBPND.rotZ;
                    return;
                case 27: //severableImpact
                    Parts.value[ListIndex]->BPND.value.severableImpact = 0; //defaultBPND.severableImpact;
                    return;
                case 28: //explodableImpact
                    Parts.value[ListIndex]->BPND.value.explodableImpact = 0; //defaultBPND.explodableImpact;
                    return;
                case 29: //severableDecalCount
                    Parts.value[ListIndex]->BPND.value.severableDecalCount = 0; //defaultBPND.severableDecalCount;
                    return;
                case 30: //explodableDecalCount
                    Parts.value[ListIndex]->BPND.value.explodableDecalCount = 0; //defaultBPND.explodableDecalCount;
                    return;
                case 31: //unused1
                    Parts.value[ListIndex]->BPND.value.unused1[0] = 0; //defaultBPND.unused1[0];
                    Parts.value[ListIndex]->BPND.value.unused1[1] = 0; //defaultBPND.unused1[1];
                    return;
                case 32: //limbReplaceScale
                    Parts.value[ListIndex]->BPND.value.limbReplaceScale = 0; //defaultBPND.limbReplaceScale;
                    return;
                case 33: //limbReplaceModPath
                    Parts.value[ListIndex]->NAM1.Unload();
                    return;
                case 34: //goreBone
                    Parts.value[ListIndex]->NAM4.Unload();
                    return;
                case 35: //nam5_p
                    Parts.value[ListIndex]->NAM5.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 13: //ragdoll
            RAGA.Unload();
            return;
        default:
            return;
        }
    }
}