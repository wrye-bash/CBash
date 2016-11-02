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
#include "..\LVLIRecord.h"

namespace Ob
{
uint32_t LVLIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //chanceNone
            return CB_UINT8_FIELD;
        case 6: //flags
            return CB_UINT8_FLAG_FIELD;
        case 7: //script
            //This field and the template field do not exist on LVLI or LVSP records
            //Otherwise, they are identical
            //This is simply a placeholder so that LVLC, LVLI, and LVSP may be read using the same FieldID's
            return CB_MISSING_FIELD;
        case 8: //template
            //This field and the script field do not exist on LVLI or LVSP records
            //Otherwise, they are identical
            //This is simply a placeholder so that LVLC, LVLI, and LVSP may be read using the same FieldID's
            return CB_MISSING_FIELD;
        case 9: //entries
            if(ListFieldID == 0) //entries
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Entries.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Entries.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //level
                    return CB_SINT16_FIELD;
                case 2: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 2;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 3: //listId
                    return CB_FORMID_FIELD;
                case 4: //count
                    return CB_SINT16_FIELD;
                case 5: //unused2
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
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LVLIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //chanceNone
            return &LVLD.value;
        case 6: //flags
            return LVLF.IsLoaded() ? LVLF.value : NULL;
        case 9: //entries
            if(ListIndex >= Entries.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //level
                    return &Entries.value[ListIndex]->level;
                case 2: //unused1
                    *FieldValues = &Entries.value[ListIndex]->unused1[0];
                    return NULL;
                case 3: //listId
                    return &Entries.value[ListIndex]->listId;
                case 4: //count
                    return &Entries.value[ListIndex]->count;
                case 5: //unused2
                    *FieldValues = &Entries.value[ListIndex]->unused2[0];
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

bool LVLIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //chanceNone
            LVLD.value = *(uint8_t *)FieldValue;
            if((LVLD.value & fAltCalcFromAllLevels) != 0)
                {
                LVLD.value &= ~fAltCalcFromAllLevels;
                IsCalcFromAllLevels(true);
                }
            break;
        case 6: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 9: //entries
            if(ListFieldID == 0) //entriesSize
                {
                Entries.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Entries.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //level
                    Entries.value[ListIndex]->level = *(int16_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 3: //listId
                    Entries.value[ListIndex]->listId = *(FORMID *)FieldValue;
                    return true;
                case 4: //count
                    Entries.value[ListIndex]->count = *(int16_t *)FieldValue;
                    break;
                case 5: //unused2
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
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

void LVLIRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LVLLVLO defaultLVLO;

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
        case 5: //chanceNone
            LVLD.Unload();
            return;
        case 6: //flags
            LVLF.Unload();
            return;
        case 9: //entries
            if(ListFieldID == 0) //entries
                {
                Entries.Unload();
                return;
                }

            if(ListIndex >= Entries.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //level
                    Entries.value[ListIndex]->level = defaultLVLO.level;
                    return;
                case 2: //unused1
                    Entries.value[ListIndex]->unused1[0] = defaultLVLO.unused1[0];
                    Entries.value[ListIndex]->unused1[1] = defaultLVLO.unused1[1];
                    return;
                case 3: //listId
                    Entries.value[ListIndex]->listId = defaultLVLO.listId;
                    return;
                case 4: //count
                    Entries.value[ListIndex]->count = defaultLVLO.count;
                    return;
                case 5: //unused2
                    Entries.value[ListIndex]->unused2[0] = defaultLVLO.unused2[0];
                    Entries.value[ListIndex]->unused2[1] = defaultLVLO.unused2[1];
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}