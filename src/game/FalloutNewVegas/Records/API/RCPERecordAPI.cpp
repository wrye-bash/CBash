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
#include "..\RCPERecord.h"

namespace FNV
{
uint32_t RCPERecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //ctda Conditions
            return CB_UINT8_FIELD;
        case 9: //ctda_p Conditions
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
        case 10: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 11: //ctda Conditions
            return CB_UINT32_FIELD;
        case 12: //ctda_p Conditions
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
        case 13: //ctda_p Conditions
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
        case 14: //ctda Conditions
            return CB_UINT32_FIELD;
        case 15: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 16: //data DATA ,, Struct
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 17: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 18: //data DATA ,, Struct
            return CB_FORMID_FIELD;
        case 19: //data DATA ,, Struct
            return CB_FORMID_FIELD;
        case 20: //rcil Item
            return CB_FORMID_FIELD;
        case 21: //rcqy Quantity
            return CB_UINT32_FIELD;
        case 22: //rcod Item
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * RCPERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value8 : NULL;
        case 9: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value9[0] : NULL;
            return NULL;
        case 10: //ctda Conditions
            return NULL; // UNPARSED
        case 11: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value11 : NULL;
        case 12: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value12[0] : NULL;
            return NULL;
        case 13: //ctda_p Conditions
            //*FieldValues = CTDAs.IsLoaded() ? &CTDAs->value13[0] : NULL;
            return NULL;
        case 14: //ctda Conditions
            return NULL;
            //return CTDAs.IsLoaded() ? &CTDAs->value14 : NULL;
        case 15: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD15;
        case 16: //data DATA ,, Struct
            return NULL; // UNPARSEDGET_FIELD16;
        case 17: //data DATA ,, Struct
            return NULL;
            //return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data DATA ,, Struct
            return NULL;
            //return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //data DATA ,, Struct
            return NULL;
            //return DATA.IsLoaded() ? &DATA->value19 : NULL;
        case 20: //rcil Item
            return NULL;
            //return RCIL.IsLoaded() ? &RCIL->value20 : NULL;
        case 21: //rcqy Quantity
            return NULL;
            //return RCQY.IsLoaded() ? &RCQY->value21 : NULL;
        case 22: //rcod Item
            return NULL;
            //return RCOD.IsLoaded() ? &RCOD->value22 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool RCPERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value8 = *(uint8_t *)FieldValue;
            break;
        case 9: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            //CTDAs.Load();
            //CTDAs->value9[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value9[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value9[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 10: //ctda Conditions
            //return UNPARSEDGET_FIELD10;
        case 11: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value11 = *(uint32_t *)FieldValue;
            break;
        case 12: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDAs.Load();
            //CTDAs->value12[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value12[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value12[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAs->value12[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 13: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDAs.Load();
            //CTDAs->value13[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAs->value13[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAs->value13[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAs->value13[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 14: //ctda Conditions
            //CTDAs.Load();
            //CTDAs->value14 = *(uint32_t *)FieldValue;
            break;
        case 15: //ctda Conditions
            //return UNPARSEDGET_FIELD15;
        case 16: //data DATA ,, Struct
            //return UNPARSEDGET_FIELD16;
        case 17: //data DATA ,, Struct
            //DATA.Load();
            //DATA->value17 = *(uint32_t *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            //DATA.Load();
            //DATA->value18 = *(FORMID *)FieldValue;
            return true;
        case 19: //data DATA ,, Struct
            //DATA.Load();
            //DATA->value19 = *(FORMID *)FieldValue;
            return true;
        case 20: //rcil Item
            //RCIL.Load();
            //RCIL->value20 = *(FORMID *)FieldValue;
            return true;
        case 21: //rcqy Quantity
            //RCQY.Load();
            //RCQY->value21 = *(uint32_t *)FieldValue;
            break;
        case 22: //rcod Item
            //RCOD.Load();
            //RCOD->value22 = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void RCPERecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 9: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 10: //ctda Conditions
            //return UNPARSEDDEL_FIELD10;
        case 11: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 12: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 13: //ctda_p Conditions
            //CTDAs.Unload();
            return;
        case 14: //ctda Conditions
            //CTDAs.Unload();
            return;
        case 15: //ctda Conditions
            //return UNPARSEDDEL_FIELD15;
        case 16: //data DATA ,, Struct
            //return UNPARSEDDEL_FIELD16;
        case 17: //data DATA ,, Struct
            //DATA.Unload();
            return;
        case 18: //data DATA ,, Struct
            //DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            //DATA.Unload();
            return;
        case 20: //rcil Item
            //RCIL.Unload();
            return;
        case 21: //rcqy Quantity
            //RCQY.Unload();
            return;
        case 22: //rcod Item
            //RCOD.Unload();
            return;
        default:
            return;
        }
    }
}