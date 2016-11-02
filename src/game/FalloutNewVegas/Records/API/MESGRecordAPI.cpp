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
#include "..\MESGRecord.h"

namespace FNV
{
uint32_t MESGRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //description
            return CB_STRING_FIELD;
        case 8: //full
            return CB_STRING_FIELD;
        case 9: //inam Icon
            return CB_FORMID_FIELD;
        case 10: //dnam Flags
            return CB_UINT32_FIELD;
        case 11: //tnam Display Time
            return CB_UINT32_FIELD;
        case 12: //itxt Button Text
            return CB_ISTRING_FIELD;
        case 13: //ctda Conditions
            return CB_UINT8_FIELD;
        case 14: //ctda_p Conditions
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
        case 15: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 16: //ctda Conditions
            return CB_UINT32_FIELD;
        case 17: //ctda_p Conditions
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
        case 18: //ctda_p Conditions
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
        case 19: //ctda Conditions
            return CB_UINT32_FIELD;
        case 20: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * MESGRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //description
            return DESC.value;
        case 8: //full
            return FULL.value;
        case 9: //inam Icon
            return INAM.IsLoaded() ? &INAM.value : NULL;
        case 10: //dnam Flags
            return DNAM.IsLoaded() ? &DNAM.value : NULL;
        case 11: //tnam Display Time
            return TNAM.IsLoaded() ? &TNAM.value : NULL;
        case 12: //itxt Button Text
            return NULL;
            //return ITXT.value;
        case 13: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value13 : NULL;
        case 14: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value14[0] : NULL;
            return NULL;
        case 15: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD15;
        case 16: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value16 : NULL;
        case 17: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value17[0] : NULL;
            return NULL;
        case 18: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value18[0] : NULL;
            return NULL;
        case 19: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value19 : NULL;
        case 20: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD20;
        default:
            return NULL;
        }
    return NULL;
    }

bool MESGRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 8: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 9: //inam Icon
            INAM.Load();
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 10: //dnam Flags
            DNAM.Load();
            DNAM.value = *(uint32_t *)FieldValue;
            break;
        case 11: //tnam Display Time
            TNAM.Load();
            TNAM.value = *(uint32_t *)FieldValue;
            break;
        case 12: //itxt Button Text
            //ITXT.Copy((char *)FieldValue);
            break;
        case 13: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value13 = *(uint8_t *)FieldValue;
            break;
        case 14: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            //CTDAs.Load();
            //CTDAs->value14[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value14[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value14[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 15: //ctda Conditions
            //return UNPARSEDGET_FIELD15;
        case 16: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value16 = *(uint32_t *)FieldValue;
            break;
        case 17: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDAs.Load();
            //CTDAs->value17[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value17[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value17[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAs->value17[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 18: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDAs.Load();
            //CTDAs->value18[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value18[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value18[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAs->value18[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 19: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value19 = *(uint32_t *)FieldValue;
            break;
        case 20: //ctda Conditions
            //return UNPARSEDGET_FIELD20;
        default:
            break;
        }
    return false;
    }

void MESGRecord::DeleteField(FIELD_IDENTIFIERS)
    {
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
        case 7: //description
            DESC.Unload();
            return;
        case 8: //full
            FULL.Unload();
            return;
        case 9: //inam Icon
            INAM.Unload();
            return;
        case 10: //dnam Flags
            DNAM.Unload();
            return;
        case 11: //tnam Display Time
            TNAM.Unload();
            return;
        case 12: //itxt Button Text
            //ITXT.Unload();
            return;
        case 13: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 14: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 15: //ctda Conditions
            //return UNPARSEDDEL_FIELD15;
        case 16: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 17: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 18: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 19: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 20: //ctda Conditions
            //return UNPARSEDDEL_FIELD20;
        default:
            return;
        }
    }
}