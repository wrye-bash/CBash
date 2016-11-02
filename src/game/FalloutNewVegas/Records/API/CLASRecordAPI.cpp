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

namespace FNV
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
        case 11: //tagSkills1
            return CB_SINT32_FIELD;
        case 12: //tagSkills2
            return CB_SINT32_FIELD;
        case 13: //tagSkills3
            return CB_SINT32_FIELD;
        case 14: //tagSkills4
            return CB_SINT32_FIELD;
        case 15: //flags
            return CB_UINT32_FLAG_FIELD;
        case 16: //services
            return CB_UINT32_FLAG_FIELD;
        case 17: //trainSkill
            return CB_SINT8_FIELD;
        case 18: //trainLevel
            return CB_UINT8_FIELD;
        case 19: //unused1
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
        case 20: //strength
            return CB_UINT8_FIELD;
        case 21: //perception
            return CB_UINT8_FIELD;
        case 22: //endurance
            return CB_UINT8_FIELD;
        case 23: //charisma
            return CB_UINT8_FIELD;
        case 24: //intelligence
            return CB_UINT8_FIELD;
        case 25: //agility
            return CB_UINT8_FIELD;
        case 26: //luck
            return CB_UINT8_FIELD;
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
        case 11: //tagSkills1
            return &DATA.value.tagSkills[0];
        case 12: //tagSkills2
            return &DATA.value.tagSkills[1];
        case 13: //tagSkills3
            return &DATA.value.tagSkills[2];
        case 14: //tagSkills4
            return &DATA.value.tagSkills[3];
        case 15: //flags
            return &DATA.value.flags;
        case 16: //services
            return &DATA.value.services;
        case 17: //trainSkill
            return &DATA.value.trainSkill;
        case 18: //trainLevel
            return &DATA.value.trainLevel;
        case 19: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 20: //strength
            return &ATTR.value.strength;
        case 21: //perception
            return &ATTR.value.perception;
        case 22: //endurance
            return &ATTR.value.endurance;
        case 23: //charisma
            return &ATTR.value.charisma;
        case 24: //intelligence
            return &ATTR.value.intelligence;
        case 25: //agility
            return &ATTR.value.agility;
        case 26: //luck
            return &ATTR.value.luck;
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
        case 11: //tagSkills1
            DATA.value.tagSkills[0] = *(int32_t *)FieldValue;
            break;
        case 12: //tagSkills2
            DATA.value.tagSkills[1] = *(int32_t *)FieldValue;
            break;
        case 13: //tagSkills3
            DATA.value.tagSkills[2] = *(int32_t *)FieldValue;
            break;
        case 14: //tagSkills4
            DATA.value.tagSkills[3] = *(int32_t *)FieldValue;
            break;
        case 15: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 16: //services
            SetServicesFlagMask(*(uint32_t *)FieldValue);
            break;
        case 17: //trainSkill
            DATA.value.trainSkill = *(int8_t *)FieldValue;
            break;
        case 18: //trainLevel
            DATA.value.trainLevel = *(uint8_t *)FieldValue;
            break;
        case 19: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 20: //strength
            ATTR.value.strength = *(uint8_t *)FieldValue;
            break;
        case 21: //perception
            ATTR.value.perception = *(uint8_t *)FieldValue;
            break;
        case 22: //endurance
            ATTR.value.endurance = *(uint8_t *)FieldValue;
            break;
        case 23: //charisma
            ATTR.value.charisma = *(uint8_t *)FieldValue;
            break;
        case 24: //intelligence
            ATTR.value.intelligence = *(uint8_t *)FieldValue;
            break;
        case 25: //agility
            ATTR.value.agility = *(uint8_t *)FieldValue;
            break;
        case 26: //luck
            ATTR.value.luck = *(uint8_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CLASRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CLASDATA defaultDATA;
    CLASATTR defaultATTR;

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
        case 11: //tagSkills1
            DATA.value.tagSkills[0] = defaultDATA.tagSkills[0];
            return;
        case 12: //tagSkills2
            DATA.value.tagSkills[1] = defaultDATA.tagSkills[1];
            return;
        case 13: //tagSkills3
            DATA.value.tagSkills[2] = defaultDATA.tagSkills[2];
            return;
        case 14: //tagSkills4
            DATA.value.tagSkills[3] = defaultDATA.tagSkills[3];
            return;
        case 15: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 16: //services
            SetServicesFlagMask(defaultDATA.services);
            return;
        case 17: //trainSkill
            DATA.value.trainSkill = defaultDATA.trainSkill;
            return;
        case 18: //trainLevel
            DATA.value.trainLevel = defaultDATA.trainLevel;
            return;
        case 19: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 20: //strength
            ATTR.value.strength = defaultATTR.strength;
            return;
        case 21: //perception
            ATTR.value.perception = defaultATTR.perception;
            return;
        case 22: //endurance
            ATTR.value.endurance = defaultATTR.endurance;
            return;
        case 23: //charisma
            ATTR.value.charisma = defaultATTR.charisma;
            return;
        case 24: //intelligence
            ATTR.value.intelligence = defaultATTR.intelligence;
            return;
        case 25: //agility
            ATTR.value.agility = defaultATTR.agility;
            return;
        case 26: //luck
            ATTR.value.luck = defaultATTR.luck;
            return;
        default:
            return;
        }
    }
}