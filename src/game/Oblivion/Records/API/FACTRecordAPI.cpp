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
#include "..\FACTRecord.h"

namespace Ob
{
uint32_t FACTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 6: //relations
            if(ListFieldID == 0) //relations
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)XNAM.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= XNAM.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //faction
                    return CB_FORMID_FIELD;
                case 2: //mod
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 7: //flags
            return CB_UINT8_FLAG_FIELD;
        case 8: //crimeGoldMultiplier
            return CB_FLOAT32_FIELD;
        case 9: //ranks
            if(ListFieldID == 0) //ranks
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)RNAM.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= RNAM.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //rank
                    return CB_SINT32_FIELD;
                case 2: //male
                    return CB_STRING_FIELD;
                case 3: //female
                    return CB_STRING_FIELD;
                case 4: //insigniaPath
                    return CB_ISTRING_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * FACTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //relations
            if(ListIndex >= XNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    return &XNAM.value[ListIndex]->faction;
                case 2: //mod
                    return &XNAM.value[ListIndex]->mod;
                default:
                    return NULL;
                }
            return NULL;
        case 7: //flags
            return &DATA.value;
        case 8: //crimeGoldMultiplier
            return CNAM.value;
        case 9: //ranks
            if(ListIndex >= RNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //rank
                    return &RNAM.value[ListIndex]->RNAM.value;
                case 2: //male
                    return RNAM.value[ListIndex]->MNAM.value;
                case 3: //female
                    return RNAM.value[ListIndex]->FNAM.value;
                case 4: //insigniaPath
                    return RNAM.value[ListIndex]->INAM.value;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool FACTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 6: //relations
            if(ListFieldID == 0) //relationsSize
                {
                XNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = *(FORMID *)FieldValue;
                    return true;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 7: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 8: //crimeGoldMultiplier
            CNAM.Load();
            *CNAM.value = *(float *)FieldValue;
            break;
        case 9: //ranks
            if(ListFieldID == 0) //ranksSize
                {
                RNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= RNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //rank
                    RNAM.value[ListIndex]->RNAM.value = *(int32_t *)FieldValue;
                    break;
                case 2: //male
                    RNAM.value[ListIndex]->MNAM.Copy((char *)FieldValue);
                    break;
                case 3: //female
                    RNAM.value[ListIndex]->FNAM.Copy((char *)FieldValue);
                    break;
                case 4: //insigniaPath
                    RNAM.value[ListIndex]->INAM.Copy((char *)FieldValue);
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

void FACTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENXNAM defaultXNAM;
    FACTRNAM defaultRNAM;

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
        case 6: //relations
            if(ListFieldID == 0) //relations
                {
                XNAM.Unload();
                return;
                }

            if(ListIndex >= XNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = defaultXNAM.faction;
                    return;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = defaultXNAM.mod;
                    return;
                default:
                    return;
                }
            return;
        case 7: //flags
            DATA.Unload();
            return;
        case 8: //crimeGoldMultiplier
            CNAM.Unload();
            return;
        case 9: //ranks
            if(ListFieldID == 0) //ranks
                {
                RNAM.Unload();
                return;
                }

            if(ListIndex >= RNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //rank
                    RNAM.value[ListIndex]->RNAM.value = defaultRNAM.RNAM.value;
                    return;
                case 2: //male
                    RNAM.value[ListIndex]->MNAM.Unload();
                    return;
                case 3: //female
                    RNAM.value[ListIndex]->FNAM.Unload();
                    return;
                case 4: //insigniaPath
                    RNAM.value[ListIndex]->INAM.Unload();
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