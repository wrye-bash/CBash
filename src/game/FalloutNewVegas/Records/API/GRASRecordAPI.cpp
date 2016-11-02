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
#include "..\GRASRecord.h"

namespace FNV
{
uint32_t GRASRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 13: //modPath
            return CB_ISTRING_FIELD;
        case 14: //modb
            return CB_FLOAT32_FIELD;
        case 15: //modt_p
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
        case 16: //altTextures
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
        case 17: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 18: //density
            return CB_UINT8_FIELD;
        case 19: //minSlope
            return CB_UINT8_FIELD;
        case 20: //maxSlope
            return CB_UINT8_FIELD;
        case 21: //unused1
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
        case 22: //waterDistance
            return CB_UINT16_FIELD;
        case 23: //unused2
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
        case 24: //waterOp
            return CB_UINT32_FIELD;
        case 25: //posRange
            return CB_FLOAT32_FIELD;
        case 26: //heightRange
            return CB_FLOAT32_FIELD;
        case 27: //colorRange
            return CB_FLOAT32_FIELD;
        case 28: //wavePeriod
            return CB_FLOAT32_FIELD;
        case 29: //flags
            return CB_UINT8_FLAG_FIELD;
        case 30: //unused3
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
    }

void * GRASRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 13: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 14: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 15: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 16: //altTextures
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
        case 17: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 18: //density
            return &DATA.value.density;
        case 19: //minSlope
            return &DATA.value.minSlope;
        case 20: //maxSlope
            return &DATA.value.maxSlope;
        case 21: //unused1
            *FieldValues = &DATA.value.unused1;
            return NULL;
        case 22: //waterDistance
            return &DATA.value.waterDistance;
        case 23: //unused2
            *FieldValues = &DATA.value.unused2[0];
            return NULL;
        case 24: //waterOp
            return &DATA.value.waterOp;
        case 25: //posRange
            return &DATA.value.posRange;
        case 26: //heightRange
            return &DATA.value.heightRange;
        case 27: //colorRange
            return &DATA.value.colorRange;
        case 28: //wavePeriod
            return &DATA.value.wavePeriod;
        case 29: //flags
            return &DATA.value.flags;
        case 30: //unused3
            *FieldValues = &DATA.value.unused3[0];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool GRASRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 13: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 14: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 15: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 16: //altTextures
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
        case 17: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 18: //density
            DATA.value.density = *(uint8_t *)FieldValue;
            break;
        case 19: //minSlope
            DATA.value.minSlope = *(uint8_t *)FieldValue;
            break;
        case 20: //maxSlope
            DATA.value.maxSlope = *(uint8_t *)FieldValue;
            break;
        case 21: //unused1
            if(ArraySize != 1)
                break;
            DATA.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 22: //waterDistance
            DATA.value.waterDistance = *(uint16_t *)FieldValue;
            break;
        case 23: //unused2
            if(ArraySize != 2)
                break;
            DATA.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 24: //waterOp
            DATA.value.waterOp = *(uint32_t *)FieldValue;
            break;
        case 25: //posRange
            DATA.value.posRange = *(float *)FieldValue;
            break;
        case 26: //heightRange
            DATA.value.heightRange = *(float *)FieldValue;
            break;
        case 27: //colorRange
            DATA.value.colorRange = *(float *)FieldValue;
            break;
        case 28: //wavePeriod
            DATA.value.wavePeriod = *(float *)FieldValue;
            break;
        case 29: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 30: //unused3
            if(ArraySize != 3)
                break;
            DATA.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        default:
            break;
        }
    return false;
    }

void GRASRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GRASDATA defaultDATA;
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
        case 13: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 14: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 15: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 16: //altTextures
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
        case 17: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 18: //density
            DATA.value.density = defaultDATA.density;
            return;
        case 19: //minSlope
            DATA.value.minSlope = defaultDATA.minSlope;
            return;
        case 20: //maxSlope
            DATA.value.maxSlope = defaultDATA.maxSlope;
            return;
        case 21: //unused1
            DATA.value.unused1 = defaultDATA.unused1;
            return;
        case 22: //waterDistance
            DATA.value.waterDistance = defaultDATA.waterDistance;
            return;
        case 23: //unused2
            DATA.value.unused2[0] = defaultDATA.unused2[0];
            DATA.value.unused2[1] = defaultDATA.unused2[1];
            return;
        case 24: //waterOp
            DATA.value.waterOp = defaultDATA.waterOp;
            return;
        case 25: //posRange
            DATA.value.posRange = defaultDATA.posRange;
            return;
        case 26: //heightRange
            DATA.value.heightRange = defaultDATA.heightRange;
            return;
        case 27: //colorRange
            DATA.value.colorRange = defaultDATA.colorRange;
            return;
        case 28: //wavePeriod
            DATA.value.wavePeriod = defaultDATA.wavePeriod;
            return;
        case 29: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 30: //unused3
            DATA.value.unused3[0] = defaultDATA.unused3[0];
            DATA.value.unused3[1] = defaultDATA.unused3[1];
            DATA.value.unused3[2] = defaultDATA.unused3[2];
            return;
        default:
            return;
        }
    return;
    }
}