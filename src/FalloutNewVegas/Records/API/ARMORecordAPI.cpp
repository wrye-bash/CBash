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
#include "..\ARMORecord.h"

namespace FNV
{
uint32_t ARMORecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 14: //script
            return CB_FORMID_FIELD;
        case 15: //effect
            return CB_FORMID_FIELD;
        case 16: //flags
            return CB_UINT32_FLAG_FIELD;
        case 17: //extraFlags
            return CB_UINT8_FLAG_FIELD;
        case 18: //unused1
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
        case 19: //male_modPath
            return CB_ISTRING_FIELD;
        case 20: //male_modt_p
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
        case 21: //male_altTextures
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
                return CB_UNKNOWN_FIELD;
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
        case 22: //male_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 23: //maleWorld_modPath
            return CB_ISTRING_FIELD;
        case 24: //maleWorld_modt_p
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
        case 25: //maleWorld_altTextures
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
        case 26: //maleIconPath
            return CB_ISTRING_FIELD;
        case 27: //maleSmallIconPath
            return CB_ISTRING_FIELD;
        case 28: //female_modPath
            return CB_ISTRING_FIELD;
        case 29: //female_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD3.IsLoaded() ? MOD3->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 30: //female_altTextures
            if(!MOD3.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MOD3->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MOD3->Textures.MODS.size())
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
        case 31: //female_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 32: //femaleWorld_modPath
            return CB_ISTRING_FIELD;
        case 33: //femaleWorld_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD4.IsLoaded() ? MOD4->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 34: //femaleWorld_altTextures
            if(!MOD4.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MOD4->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MOD4->Textures.MODS.size())
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
        case 35: //femaleIconPath
            return CB_ISTRING_FIELD;
        case 36: //femaleSmallIconPath
            return CB_ISTRING_FIELD;
        case 37: //ragdollTemplatePath
            return CB_ISTRING_FIELD;
        case 38: //repairList
            return CB_FORMID_FIELD;
        case 39: //modelList
            return CB_FORMID_FIELD;
        case 40: //equipmentType
            return CB_SINT32_TYPE_FIELD;
        case 41: //pickupSound
            return CB_FORMID_FIELD;
        case 42: //dropSound
            return CB_FORMID_FIELD;
        case 43: //value
            return CB_SINT32_FIELD;
        case 44: //health
            return CB_SINT32_FIELD;
        case 45: //weight
            return CB_FLOAT32_FIELD;
        case 46: //AR
            return CB_SINT16_FIELD;
        case 47: //voiceFlags
            return CB_UINT16_FLAG_FIELD;
        case 48: //DT
            return CB_FLOAT32_FIELD;
        case 49: //unknown1
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
        case 50: //overrideSounds
            return CB_UINT32_TYPE_FIELD;
        case 51: //sounds
            if(ListFieldID == 0) //altTextures
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
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Sounds.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //sound
                    return CB_FORMID_FIELD;
                case 2: //chance
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
                case 4: //type
                    return CB_UINT32_TYPE_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 52: //soundsTemplate
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * ARMORecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 14: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 15: //effect
            return EITM.IsLoaded() ? &EITM.value : NULL;
        case 16: //flags
            return &BMDT.value.bipedFlags;
        case 17: //extraFlags
            return &BMDT.value.generalFlags;
        case 18: //unused1
            *FieldValues = &BMDT.value.unused1[0];
            return NULL;
        case 19: //male_modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 20: //male_modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 21: //male_altTextures
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
        case 22: //male_modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 23: //maleWorld_modPath
            return MOD2.IsLoaded() ? MOD2->MODL.value : NULL;
        case 24: //maleWorld_modt_p
            *FieldValues = MOD2.IsLoaded() ? MOD2->MODT.value : NULL;
            return NULL;
        case 25: //maleWorld_altTextures
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
        case 26: //maleIconPath
            return ICON.value;
        case 27: //maleSmallIconPath
            return MICO.value;
        case 28: //female_modPath
            return MOD3.IsLoaded() ? MOD3->MODL.value : NULL;
        case 29: //female_modt_p
            *FieldValues = MOD3.IsLoaded() ? MOD3->MODT.value : NULL;
            return NULL;
        case 30: //female_altTextures
            if(!MOD3.IsLoaded())
                return NULL;

            if(ListIndex >= MOD3->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MOD3->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MOD3->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MOD3->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 31: //female_modelFlags
            return MOD3.IsLoaded() ? &MOD3->MODD.value : NULL;
        case 32: //femaleWorld_modPath
            return MOD4.IsLoaded() ? MOD4->MODL.value : NULL;
        case 33: //femaleWorld_modt_p
            *FieldValues = MOD4.IsLoaded() ? MOD4->MODT.value : NULL;
            return NULL;
        case 34: //femaleWorld_altTextures
            if(!MOD4.IsLoaded())
                return NULL;

            if(ListIndex >= MOD4->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MOD4->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MOD4->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MOD4->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 35: //femaleIconPath
            return ICO2.value;
        case 36: //femaleSmallIconPath
            return MIC2.value;
        case 37: //ragdollTemplatePath
            return BMCT.value;
        case 38: //repairList
            return REPL.IsLoaded() ? &REPL.value : NULL;
        case 39: //modelList
            return BIPL.IsLoaded() ? &BIPL.value : NULL;
        case 40: //equipmentType
            return ETYP.IsLoaded() ? &ETYP.value : NULL;
        case 41: //pickupSound
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 42: //dropSound
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        case 43: //value
            return &DATA.value.value;
        case 44: //health
            return &DATA.value.health;
        case 45: //weight
            return &DATA.value.weight;
        case 46: //AR
            return &DNAM.value.AR;
        case 47: //voiceFlags
            return &DNAM.value.flags;
        case 48: //DT
            return &DNAM.value.DT;
        case 49: //unknown1
            *FieldValues = &DNAM.value.unknown[0];
            return NULL;
        case 50: //overrideSounds
            return BNAM.IsLoaded() ? &BNAM.value : NULL;
        case 51: //sounds
            if(ListIndex >= Sounds.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //sound
                    return &Sounds.value[ListIndex]->sound;
                case 2: //chance
                    return &Sounds.value[ListIndex]->chance;
                case 3: //unused1
                    *FieldValues = &Sounds.value[ListIndex]->unused1[0];
                    return NULL;
                case 4: //type
                    return &Sounds.value[ListIndex]->type;
                default:
                    return NULL;
                }
            return NULL;
        case 52: //soundsTemplate
            return TNAM.IsLoaded() ? &TNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool ARMORecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 14: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 15: //effect
            EITM.value = *(FORMID *)FieldValue;
            return true;
        case 16: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 17: //extraFlags
            SetExtraFlagMask(*(uint8_t *)FieldValue);
            break;
        case 18: //unused1
            if(ArraySize != 3)
                break;
            BMDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            BMDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            BMDT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 19: //male_modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 20: //male_modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 21: //male_altTextures
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
        case 22: //male_modelFlags
            MODL.Load();
            MODL->MODD.value = *(uint8_t *)FieldValue;
            break;
        case 23: //maleWorld_modPath
            MOD2.Load();
            MOD2->MODL.Copy((char *)FieldValue);
            break;
        case 24: //maleWorld_modt_p
            MOD2.Load();
            MOD2->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 25: //maleWorld_altTextures
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
        case 26: //maleIconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 27: //maleSmallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 28: //female_modPath
            MOD3.Load();
            MOD3->MODL.Copy((char *)FieldValue);
            break;
        case 29: //female_modt_p
            MOD3.Load();
            MOD3->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 30: //female_altTextures
            MOD3.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MOD3->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MOD3->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MOD3->Textures.MODS[ListIndex]->name;
                    MOD3->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MOD3->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MOD3->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MOD3->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MOD3->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 31: //female_modelFlags
            MOD3.Load();
            MOD3->MODD.value = *(uint8_t *)FieldValue;
            break;
        case 32: //femaleWorld_modPath
            MOD4.Load();
            MOD4->MODL.Copy((char *)FieldValue);
            break;
        case 33: //femaleWorld_modt_p
            MOD4.Load();
            MOD4->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 34: //femaleWorld_altTextures
            MOD4.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MOD4->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MOD4->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MOD4->Textures.MODS[ListIndex]->name;
                    MOD4->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MOD4->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MOD4->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MOD4->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MOD4->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 35: //femaleIconPath
            ICO2.Copy((char *)FieldValue);
            break;
        case 36: //femaleSmallIconPath
            MIC2.Copy((char *)FieldValue);
            break;
        case 37: //ragdollTemplatePath
            BMCT.Copy((char *)FieldValue);
            break;
        case 38: //repairList
            REPL.value = *(FORMID *)FieldValue;
            return true;
        case 39: //modelList
            BIPL.value = *(FORMID *)FieldValue;
            return true;
        case 40: //equipmentType
            SetEquipmentType(*(int32_t *)FieldValue);
            break;
        case 41: //pickupSound
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 42: //dropSound
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 43: //value
            DATA.value.value = *(int32_t *)FieldValue;
            break;
        case 44: //health
            DATA.value.health = *(int32_t *)FieldValue;
            break;
        case 45: //weight
            DATA.value.weight = *(float *)FieldValue;
            break;
        case 46: //AR
            DNAM.value.AR = *(int16_t *)FieldValue;
            break;
        case 47: //voiceFlags
            SetVoiceFlagMask(*(uint16_t *)FieldValue);
            break;
        case 48: //DT
            DNAM.value.DT = *(float *)FieldValue;
            break;
        case 49: //unknown1
            if(ArraySize != 4)
                break;
            DNAM.value.unknown[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM.value.unknown[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM.value.unknown[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM.value.unknown[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 50: //overrideSounds
            SetOverrideType(*(uint32_t *)FieldValue);
            break;
        case 51: //sounds
            if(ListFieldID == 0) //soundsSize
                {
                Sounds.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Sounds.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //sound
                    Sounds.value[ListIndex]->sound = *(FORMID *)FieldValue;
                    return true;
                case 2: //chance
                    Sounds.value[ListIndex]->chance = *(uint8_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 3)
                        break;
                    Sounds.value[ListIndex]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Sounds.value[ListIndex]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Sounds.value[ListIndex]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 4: //type
                    Sounds.value[ListIndex]->type = *(uint32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 52: //soundsTemplate
            TNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void ARMORecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    GENBMDT defaultBMDT;
    FNVMODS defaultMODS;
    FNVEQUIPDATA defaultDATA;
    FNVEQUIPDNAM defaultDNAM;
    FNVSNAM defaultSNAM;

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
        case 14: //script
            SCRI.Unload();
            return;
        case 15: //effect
            EITM.Unload();
            return;
        case 16: //flags
            SetFlagMask(defaultBMDT.bipedFlags);
            return;
        case 17: //extraFlags
            SetExtraFlagMask(defaultBMDT.generalFlags);
            return;
        case 18: //unused1
            BMDT.value.unused1[0] = defaultBMDT.unused1[0];
            BMDT.value.unused1[1] = defaultBMDT.unused1[1];
            BMDT.value.unused1[2] = defaultBMDT.unused1[2];
            return;
        case 19: //male_modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 20: //male_modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 21: //male_altTextures
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
        case 22: //male_modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 23: //maleWorld_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            return;
        case 24: //maleWorld_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            return;
        case 25: //maleWorld_altTextures
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
        case 26: //maleIconPath
            ICON.Unload();
            return;
        case 27: //maleSmallIconPath
            MICO.Unload();
            return;
        case 28: //female_modPath
            if(MOD3.IsLoaded())
                MOD3->MODL.Unload();
            return;
        case 29: //female_modt_p
            if(MOD3.IsLoaded())
                MOD3->MODT.Unload();
            return;
        case 30: //female_altTextures
            if(MOD3.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MOD3->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MOD3->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MOD3->Textures.MODS[ListIndex]->name;
                        MOD3->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MOD3->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MOD3->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 31: //female_modelFlags
            if(MOD3.IsLoaded())
                MOD3->MODD.Unload();
            return;
        case 32: //femaleWorld_modPath
            if(MOD4.IsLoaded())
                MOD4->MODL.Unload();
            return;
        case 33: //femaleWorld_modt_p
            if(MOD4.IsLoaded())
                MOD4->MODT.Unload();
            return;
        case 34: //femaleWorld_altTextures
            if(MOD4.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MOD4->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MOD4->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MOD4->Textures.MODS[ListIndex]->name;
                        MOD4->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MOD4->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MOD4->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 35: //femaleIconPath
            ICO2.Unload();
            return;
        case 36: //femaleSmallIconPath
            MIC2.Unload();
            return;
        case 37: //ragdollTemplatePath
            BMCT.Unload();
            return;
        case 38: //repairList
            REPL.Unload();
            return;
        case 39: //modelList
            BIPL.Unload();
            return;
        case 40: //equipmentType
            ETYP.Unload();
            return;
        case 41: //pickupSound
            YNAM.Unload();
            return;
        case 42: //dropSound
            ZNAM.Unload();
            return;
        case 43: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 44: //health
            DATA.value.health = defaultDATA.health;
            return;
        case 45: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        case 46: //AR
            DNAM.value.AR = defaultDNAM.AR;
            return;
        case 47: //voiceFlags
            SetVoiceFlagMask(defaultDNAM.flags);
            return;
        case 48: //DT
            DNAM.value.DT = defaultDNAM.DT;
            return;
        case 49: //unknown1
            DNAM.value.unknown[0] = defaultDNAM.unknown[0];
            DNAM.value.unknown[1] = defaultDNAM.unknown[1];
            DNAM.value.unknown[2] = defaultDNAM.unknown[2];
            DNAM.value.unknown[3] = defaultDNAM.unknown[3];
            return;
        case 50: //overrideSounds
            BNAM.Unload();
            return;
        case 51: //sounds
            if(ListFieldID == 0) //soundsSize
                {
                Sounds.Unload();
                return;
                }

            if(ListIndex >= Sounds.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //sound
                    Sounds.value[ListIndex]->sound = defaultSNAM.sound;
                    return;
                case 2: //chance
                    Sounds.value[ListIndex]->chance = defaultSNAM.chance;
                    return;
                case 3: //unused1
                    Sounds.value[ListIndex]->unused1[0] = defaultSNAM.unused1[0];
                    Sounds.value[ListIndex]->unused1[1] = defaultSNAM.unused1[1];
                    Sounds.value[ListIndex]->unused1[2] = defaultSNAM.unused1[2];
                    return;
                case 4: //type
                    Sounds.value[ListIndex]->type = defaultSNAM.type;
                    return;
                default:
                    return;
                }
            return;
        case 52: //soundsTemplate
            TNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}