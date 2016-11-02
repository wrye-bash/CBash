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
#include "..\LIGHRecord.h"

namespace FNV
{
uint32_t LIGHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 19: //iconPath
            return CB_ISTRING_FIELD;
        case 20: //smallIconPath
            return CB_ISTRING_FIELD;
        case 21: //script
            return CB_FORMID_FIELD;
        case 22: //duration
            return CB_SINT32_FIELD;
        case 23: //radius
            return CB_UINT32_FIELD;
        case 24: //red
            return CB_UINT8_FIELD;
        case 25: //green
            return CB_UINT8_FIELD;
        case 26: //blue
            return CB_UINT8_FIELD;
        case 27: //unused1
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
        case 28: //flags
            return CB_UINT32_FLAG_FIELD;
        case 29: //falloff
            return CB_FLOAT32_FIELD;
        case 30: //fov
            return CB_FLOAT32_FIELD;
        case 31: //value
            return CB_UINT32_FIELD;
        case 32: //weight
            return CB_FLOAT32_FIELD;
        case 33: //fade
            return CB_FLOAT32_FIELD;
        case 34: //sound
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LIGHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 19: //iconPath
            return ICON.value;
        case 20: //smallIconPath
            return MICO.value;
        case 21: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 22: //duration
            return &DATA.value.duration;
        case 23: //radius
            return &DATA.value.radius;
        case 24: //red
            return &DATA.value.color.red;
        case 25: //green
            return &DATA.value.color.green;
        case 26: //blue
            return &DATA.value.color.blue;
        case 27: //unused1
            *FieldValues = &DATA.value.color.unused1;
            return NULL;
        case 28: //flags
            return &DATA.value.flags;
        case 29: //falloff
            return &DATA.value.falloff;
        case 30: //fov
            return &DATA.value.fov;
        case 31: //value
            return &DATA.value.value;
        case 32: //weight
            return &DATA.value.weight;
        case 33: //fade
            return FNAM.IsLoaded() ? &FNAM.value : NULL;
        case 34: //sound
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LIGHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 19: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 20: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 21: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 22: //duration
            DATA.value.duration = *(int32_t *)FieldValue;
            break;
        case 23: //radius
            DATA.value.radius = *(uint32_t *)FieldValue;
            break;
        case 24: //red
            DATA.value.color.red = *(uint8_t *)FieldValue;
            break;
        case 25: //green
            DATA.value.color.green = *(uint8_t *)FieldValue;
            break;
        case 26: //blue
            DATA.value.color.blue = *(uint8_t *)FieldValue;
            break;
        case 27: //unused1
            if(ArraySize != 1)
                break;
            DATA.value.color.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 28: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 29: //falloff
            DATA.value.falloff = *(float *)FieldValue;
            break;
        case 30: //fov
            DATA.value.fov = *(float *)FieldValue;
            break;
        case 31: //value
            DATA.value.value = *(uint32_t *)FieldValue;
            break;
        case 32: //weight
            DATA.value.weight = *(float *)FieldValue;
            break;
        case 33: //fade
            FNAM.value = *(float *)FieldValue;
            break;
        case 34: //sound.
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LIGHRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    LIGHDATA defaultDATA;
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
        case 19: //iconPath
            ICON.Unload();
            return;
        case 20: //smallIconPath
            MICO.Unload();
            return;
        case 21: //script
            SCRI.Unload();
            return;
        case 22: //duration
            DATA.value.duration = defaultDATA.duration;
            return;
        case 23: //radius
            DATA.value.radius = defaultDATA.radius;
            return;
        case 24: //red
            DATA.value.color.red = defaultDATA.color.red;
            return;
        case 25: //green
            DATA.value.color.green = defaultDATA.color.green;
            return;
        case 26: //blue
            DATA.value.color.blue = defaultDATA.color.blue;
            return;
        case 27: //unused1
            DATA.value.color.unused1 = defaultDATA.color.unused1;
            return;
        case 28: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 29: //falloff
            DATA.value.falloff = defaultDATA.falloff;
            return;
        case 30: //fov
            DATA.value.fov = defaultDATA.fov;
            return;
        case 31: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 32: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        case 33: //fade
            FNAM.Unload();
            return;
        case 34: //sound
            SNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}