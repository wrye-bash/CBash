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
#include "..\DEBRRecord.h"

namespace FNV
{
uint32_t DEBRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //models
            if(ListFieldID == 0) //models
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Models.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Models.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //percentage
                    return CB_UINT8_FIELD;
                case 2: //modPath
                    return CB_ISTRING_FIELD;
                case 3: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 4: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Models.MODS[ListIndex]->MODT.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * DEBRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //models
            if(ListIndex >= Models.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //percentage
                    return &Models.MODS[ListIndex]->percentage;
                case 2: //modPath
                    return Models.MODS[ListIndex]->modPath;
                case 3: //flags
                    return &Models.MODS[ListIndex]->flags;
                case 4: //modt_p
                    *FieldValues = Models.MODS[ListIndex]->MODT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool DEBRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //models
            if(ListFieldID == 0) //modelsSize
                {
                Models.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Models.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //percentage
                    Models.MODS[ListIndex]->percentage = *(uint8_t *)FieldValue;
                    break;
                case 2: //modPath
                    delete []Models.MODS[ListIndex]->modPath;
                    Models.MODS[ListIndex]->modPath = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        Models.MODS[ListIndex]->modPath = new char[ArraySize];
                        strcpy_s(Models.MODS[ListIndex]->modPath, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 3: //flags
                    Models.MODS[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //modt_p
                    Models.MODS[ListIndex]->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
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

void DEBRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    DEBRModel defaultModel;
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
        case 7: //models
            if(ListFieldID == 0) //modelsSize
                {
                Models.Unload();
                return;
                }

            if(ListIndex >= Models.MODS.size())
                return;

            switch(ListFieldID)
                {
                case 1: //percentage
                    Models.MODS[ListIndex]->percentage = defaultModel.percentage;
                    return;
                case 2: //modPath
                    delete []Models.MODS[ListIndex]->modPath;
                    Models.MODS[ListIndex]->modPath = NULL;
                    return;
                case 3: //flags
                    Models.MODS[ListIndex]->SetFlagMask(defaultModel.flags);
                    return;
                case 4: //modt_p
                    Models.MODS[ListIndex]->MODT.Unload();
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    }
}