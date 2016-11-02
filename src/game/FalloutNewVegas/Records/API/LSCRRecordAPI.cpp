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
#include "..\LSCRRecord.h"

namespace FNV
{
uint32_t LSCRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //iconPath
            return CB_ISTRING_FIELD;
        case 8: //smallIconPath
            return CB_ISTRING_FIELD;
        case 9: //text
            return CB_STRING_FIELD;
        case 10: //locations
            if(ListFieldID == 0) //locations
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)LNAM.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= LNAM.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //direct
                    return CB_FORMID_FIELD;
                case 2: //indirect
                    return CB_FORMID_FIELD;
                case 3: //gridY
                    return CB_SINT16_FIELD;
                case 4: //gridX
                    return CB_SINT16_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //screentype
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LSCRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //iconPath
            return ICON.value;
        case 8: //smallIconPath
            return MICO.value;
        case 9: //text
            return DESC.value;
        case 10: //locations
            if(ListIndex >= LNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //direct
                    return &LNAM.value[ListIndex]->direct;
                case 2: //indirect
                    return &LNAM.value[ListIndex]->indirect;
                case 3: //gridY
                    return &LNAM.value[ListIndex]->gridY;
                case 4: //gridX
                    return &LNAM.value[ListIndex]->gridX;
                default:
                    return NULL;
                }
            return NULL;
        case 11: //screentype
            return &WMI1.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool LSCRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 9: //text
            DESC.Copy((char *)FieldValue);
            break;
        case 10: //locations
            if(ListFieldID == 0) //locationsSize
                {
                LNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= LNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //direct
                    LNAM.value[ListIndex]->direct = *(FORMID *)FieldValue;
                    return true;
                case 2: //indirect
                    LNAM.value[ListIndex]->indirect = *(FORMID *)FieldValue;
                    return true;
                case 3: //gridY
                    LNAM.value[ListIndex]->gridY = *(int16_t *)FieldValue;
                    break;
                case 4: //gridX
                    LNAM.value[ListIndex]->gridX = *(int16_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 11: //screentype
            WMI1.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LSCRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LSCRLNAM defaultLNAM;
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
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //smallIconPath
            MICO.Unload();
            return;
        case 9: //text
            DESC.Unload();
            return;
        case 10: //locations
            if(ListFieldID == 0) //locationsSize
                {
                LNAM.Unload();
                return;
                }

            if(ListIndex >= LNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //direct
                    LNAM.value[ListIndex]->direct = defaultLNAM.direct;
                    return;
                case 2: //indirect
                    LNAM.value[ListIndex]->indirect = defaultLNAM.indirect;
                    return;
                case 3: //gridY
                    LNAM.value[ListIndex]->gridY = defaultLNAM.gridY;
                    return;
                case 4: //gridX
                    LNAM.value[ListIndex]->gridX = defaultLNAM.gridX;
                    return;
                default:
                    return;
                }
            return;
        case 11: //screentype
            WMI1.Unload();
            return;
        default:
            return;
        }
    }
}