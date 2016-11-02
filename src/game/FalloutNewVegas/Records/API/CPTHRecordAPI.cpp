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
#include "..\CPTHRecord.h"

namespace FNV
{
uint32_t CPTHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //ctda Conditions
            return CB_UINT8_FIELD;
        case 8: //ctda_p Conditions
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
        case 9: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 10: //ctda Conditions
            return CB_UINT32_FIELD;
        case 11: //ctda_p Conditions
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
        case 13: //ctda Conditions
            return CB_UINT32_FIELD;
        case 14: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 15: //anam Related Camera Paths
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 16: //data Camera Zoom
            return CB_UINT8_FIELD;
        case 17: //snam Camera Shot
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CPTHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value7 : NULL;
        case 8: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value8[0] : NULL;
            return NULL;
        case 9: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD9;
        case 10: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value10 : NULL;
        case 11: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value11[0] : NULL;
            return NULL;
        case 12: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value12[0] : NULL;
            return NULL;
        case 13: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value13 : NULL;
        case 14: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD14;
        case 15: //anam Related Camera Paths
            return NULL; // UNPARSEDGET_FIELD15;
        case 16: //data Camera Zoom
            return DATA.IsLoaded() ? &DATA.value : NULL;
        case 17: //snam Camera Shot
            return SNAM.IsLoaded() ? &SNAM.value[0] : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CPTHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //ctda Conditions
            //CTDA.Load();
            //CTDA->value7 = *(uint8_t *)FieldValue;
            break;
        case 8: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            //CTDA.Load();
            //CTDA->value8[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value8[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value8[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 9: //ctda Conditions
            //return UNPARSEDGET_FIELD9;
            break;
        case 10: //ctda Conditions
            //CTDA.Load();
            //CTDA->value10 = *(uint32_t *)FieldValue;
            break;
        case 11: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDA->value11[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value11[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value11[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDA->value11[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 12: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDA->value12[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value12[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value12[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDA->value12[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 13: //ctda Conditions
            //CTDA.Load();
            //CTDA->value13 = *(uint32_t *)FieldValue;
            break;
        case 14: //ctda Conditions
            //return UNPARSEDGET_FIELD14;
            break;
        case 15: //anam Related Camera Paths
            //return UNPARSEDGET_FIELD15;
            break;
        case 16: //data Camera Zoom
            DATA.Load();
            DATA.value = *(uint8_t *)FieldValue;
            break;
        case 17: //snam Camera Shot
            //SNAM.Load();
            SNAM.value[0] = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CPTHRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //ctda Conditions
            //CTDA.Unload();
            return;
        case 8: //ctda_p Conditions
            //CTDA.Unload();
            return;
        case 9: //ctda Conditions
            return; // UNPARSEDDEL_FIELD9;
        case 10: //ctda Conditions
            //CTDA.Unload();
            return;
        case 11: //ctda_p Conditions
            //CTDA.Unload();
            return;
        case 12: //ctda_p Conditions
            //CTDA.Unload();
            return;
        case 13: //ctda Conditions
            //CTDA.Unload();
            return;
        case 14: //ctda Conditions
            return; // UNPARSEDDEL_FIELD14;
        case 15: //anam Related Camera Paths
            return; // UNPARSEDDEL_FIELD15;
        case 16: //data Camera Zoom
            DATA.Unload();
            return;
        case 17: //snam Camera Shot
            SNAM.Unload();
            return;
        default:
            return;
        }
    }
}