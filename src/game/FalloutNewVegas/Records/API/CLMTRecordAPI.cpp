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
#include "..\CLMTRecord.h"

namespace FNV
{
uint32_t CLMTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //weathers
            if(ListFieldID == 0) //weathers
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Weathers.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Weathers.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //weather
                    return CB_FORMID_FIELD;
                case 2: //chance
                    return CB_SINT32_FIELD;
                case 3: //globalId
                    return CB_FORMID_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //sunPath
            return CB_ISTRING_FIELD;
        case 9: //glarePath
            return CB_ISTRING_FIELD;
        case 10: //modPath
            return CB_ISTRING_FIELD;
        case 11: //modb
            return CB_FLOAT32_FIELD;
        case 12: //modt_p
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
        case 13: //altTextures
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
        case 14: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 15: //riseBegin
            return CB_UINT8_FIELD;
        case 16: //riseEnd
            return CB_UINT8_FIELD;
        case 17: //setBegin
            return CB_UINT8_FIELD;
        case 18: //setEnd
            return CB_UINT8_FIELD;
        case 19: //volatility
            return CB_UINT8_FIELD;
        case 20: //phaseLength
            return CB_UINT8_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CLMTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //weathers
            if(ListIndex >= Weathers.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //weather
                    return &Weathers.value[ListIndex].weather;
                case 2: //chance
                    return &Weathers.value[ListIndex].chance;
                case 3: //globalId
                    return &Weathers.value[ListIndex].globalId;
                default:
                    return NULL;
                }
            return NULL;
        case 8: //sunPath
            return FNAM.value;
        case 9: //glarePath
            return GNAM.value;
        case 10: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 11: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 12: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 13: //altTextures
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
        case 14: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 15: //riseBegin
            return &TNAM.value.riseBegin;
        case 16: //riseEnd
            return &TNAM.value.riseEnd;
        case 17: //setBegin
            return &TNAM.value.setBegin;
        case 18: //setEnd
            return &TNAM.value.setEnd;
        case 19: //volatility
            return &TNAM.value.volatility;
        case 20: //phaseLength
            return &TNAM.value.phaseLength;
        default:
            return NULL;
        }
    return NULL;
    }

bool CLMTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //weathers
            if(ListFieldID == 0) //weathersSize
                {
                Weathers.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Weathers.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //weather
                    Weathers.value[ListIndex].weather = *(FORMID *)FieldValue;
                    return true;
                case 2: //chance
                    Weathers.value[ListIndex].chance = *(int32_t *)FieldValue;
                    break;
                case 3: //globalId
                    Weathers.value[ListIndex].globalId = *(FORMID *)FieldValue;
                    return true;
                default:
                    break;
                }
            break;
        case 8: //sunPath
            FNAM.Copy((char *)FieldValue);
            break;
        case 9: //glarePath
            GNAM.Copy((char *)FieldValue);
            break;
        case 10: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 11: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 12: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //altTextures
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
        case 14: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 15: //riseBegin
            TNAM.value.riseBegin = *(uint8_t *)FieldValue;
            break;
        case 16: //riseEnd
            TNAM.value.riseEnd = *(uint8_t *)FieldValue;
            break;
        case 17: //setBegin
            TNAM.value.setBegin = *(uint8_t *)FieldValue;
            break;
        case 18: //setEnd
            TNAM.value.setEnd = *(uint8_t *)FieldValue;
            break;
        case 19: //volatility
            TNAM.value.volatility = *(uint8_t *)FieldValue;
            break;
        case 20: //phaseLength
            TNAM.value.phaseLength = *(uint8_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CLMTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CLMTTNAM defaultTNAM;
    CLMTWLST defaultWLST;
    FNVMODS defaultMODS;

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
        case 7: //weathers
            if(ListFieldID == 0) //weathers
                {
                Weathers.Unload();
                return;
                }

            if(ListIndex >= Weathers.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //weather
                    Weathers.value[ListIndex].weather = defaultWLST.weather;
                    return;
                case 2: //chance
                    Weathers.value[ListIndex].chance = defaultWLST.chance;
                    return;
                case 3: //globalId
                    Weathers.value[ListIndex].globalId = defaultWLST.globalId;
                    return;
                default:
                    return;
                }
            return;
        case 8: //sunPath
            FNAM.Unload();
            return;
        case 9: //glarePath
            GNAM.Unload();
            return;
        case 10: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 11: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 12: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 13: //altTextures
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
        case 14: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 15: //riseBegin
            TNAM.value.riseBegin = defaultTNAM.riseBegin;
            return;
        case 16: //riseEnd
            TNAM.value.riseEnd = defaultTNAM.riseEnd;
            return;
        case 17: //setBegin
            TNAM.value.setBegin = defaultTNAM.setBegin;
            return;
        case 18: //setEnd
            TNAM.value.setEnd = defaultTNAM.setEnd;
            return;
        case 19: //volatility
            TNAM.value.volatility = defaultTNAM.volatility;
            return;
        case 20: //phaseLength
            TNAM.value.phaseLength = defaultTNAM.phaseLength;
            return;
        default:
            return;
        }
    return;
    }
}