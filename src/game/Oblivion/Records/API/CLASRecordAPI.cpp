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
#include "..\CLASRecord.h"

namespace Ob
{
uint32_t CLASRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return CB_UINT32_FLAG_FIELD;
        case 2: //fid
            return CB_FORMID_FIELD;
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //full
            return CB_STRING_FIELD;
        case 6: //description
            return CB_STRING_FIELD;
        case 7: //iconPath
            return CB_ISTRING_FIELD;
        case 8: //primary1
            return CB_SINT32_FIELD;
        case 9: //primary2
            return CB_SINT32_FIELD;
        case 10: //specialization
            return CB_UINT32_FIELD;
        case 11: //major1
            return CB_SINT32_FIELD;
        case 12: //major2
            return CB_SINT32_FIELD;
        case 13: //major3
            return CB_SINT32_FIELD;
        case 14: //major4
            return CB_SINT32_FIELD;
        case 15: //major5
            return CB_SINT32_FIELD;
        case 16: //major6
            return CB_SINT32_FIELD;
        case 17: //major7
            return CB_SINT32_FIELD;
        case 18: //flags
            return CB_UINT32_FLAG_FIELD;
        case 19: //services
            return CB_UINT32_FLAG_FIELD;
        case 20: //trainSkill
            return CB_SINT8_FIELD;
        case 21: //trainLevel
            return CB_UINT8_FIELD;
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
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CLASRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //full
            return FULL.value;
        case 6: //description
            return DESC.value;
        case 7: //iconPath
            return ICON.value;
        case 8: //primary1
            return &DATA.value.primary[0];
        case 9: //primary2
            return &DATA.value.primary[1];
        case 10: //specialization
            return &DATA.value.specialization;
        case 11: //major1
            return &DATA.value.major[0];
        case 12: //major2
            return &DATA.value.major[1];
        case 13: //major3
            return &DATA.value.major[2];
        case 14: //major4
            return &DATA.value.major[3];
        case 15: //major5
            return &DATA.value.major[4];
        case 16: //major6
            return &DATA.value.major[5];
        case 17: //major7
            return &DATA.value.major[6];
        case 18: //flags
            return &DATA.value.flags;
        case 19: //services
            return &DATA.value.services;
        case 20: //trainSkill
            return &DATA.value.trainSkill;
        case 21: //trainLevel
            return &DATA.value.trainLevel;
        case 22: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CLASRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 6: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 7: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //primary1
            DATA.value.primary[0] = *(int32_t *)FieldValue;
            break;
        case 9: //primary2
            DATA.value.primary[1] = *(int32_t *)FieldValue;
            break;
        case 10: //specialization
            DATA.value.specialization = *(uint32_t *)FieldValue;
            break;
        case 11: //major1
            DATA.value.major[0] = *(int32_t *)FieldValue;
            break;
        case 12: //major2
            DATA.value.major[1] = *(int32_t *)FieldValue;
            break;
        case 13: //major3
            DATA.value.major[2] = *(int32_t *)FieldValue;
            break;
        case 14: //major4
            DATA.value.major[3] = *(int32_t *)FieldValue;
            break;
        case 15: //major5
            DATA.value.major[4] = *(int32_t *)FieldValue;
            break;
        case 16: //major6
            DATA.value.major[5] = *(int32_t *)FieldValue;
            break;
        case 17: //major7
            DATA.value.major[6] = *(int32_t *)FieldValue;
            break;
        case 18: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 19: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 20: //trainSkill
            DATA.value.trainSkill = *(int8_t *)FieldValue;
            break;
        case 21: //trainLevel
            DATA.value.trainLevel = *(uint8_t *)FieldValue;
            break;
        case 22: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        default:
            break;
        }
    return false;
    }

void CLASRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CLASDATA defaultDATA;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //full
            FULL.Unload();
            return;
        case 6: //description
            DESC.Unload();
            return;
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //primary1
            DATA.value.primary[0] = defaultDATA.primary[0];
            return;
        case 9: //primary2
            DATA.value.primary[1] = defaultDATA.primary[1];
            return;
        case 10: //specialization
            DATA.value.specialization = defaultDATA.specialization;
            return;
        case 11: //major1
            DATA.value.major[0] = defaultDATA.major[0];
            return;
        case 12: //major2
            DATA.value.major[1] = defaultDATA.major[1];
            return;
        case 13: //major3
            DATA.value.major[2] = defaultDATA.major[2];
            return;
        case 14: //major4
            DATA.value.major[3] = defaultDATA.major[3];
            return;
        case 15: //major5
            DATA.value.major[4] = defaultDATA.major[4];
            return;
        case 16: //major6
            DATA.value.major[5] = defaultDATA.major[5];
            return;
        case 17: //major7
            DATA.value.major[6] = defaultDATA.major[6];
            return;
        case 18: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 19: //services
            DATA.value.services = defaultDATA.services;
            return;
        case 20: //trainSkill
            DATA.value.trainSkill = defaultDATA.trainSkill;
            return;
        case 21: //trainLevel
            DATA.value.trainLevel = defaultDATA.trainLevel;
            return;
        case 22: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        default:
            return;
        }
    return;
    }
}