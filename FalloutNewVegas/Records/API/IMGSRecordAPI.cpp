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
#include "..\IMGSRecord.h"

namespace FNV
{
UINT32 IMGSRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 8: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 9: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 10: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 11: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 12: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 13: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 14: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 15: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 16: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 17: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 18: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 19: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 20: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 21: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 22: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 23: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 24: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 25: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 26: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 27: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 28: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 29: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 30: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 31: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 32: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 33: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 34: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 35: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 36: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 37: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 38: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 39: //dnam DNAM ,, Struct
            return FLOAT32_FIELD;
        case 40: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 41: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 42: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 43: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 44: //dnam DNAM ,, Struct
            return UINT8_FIELD;
        case 45: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * IMGSRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value7 : NULL;
        case 8: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value8 : NULL;
        case 9: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value9 : NULL;
        case 10: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value10 : NULL;
        case 11: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value11 : NULL;
        case 12: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value12 : NULL;
        case 13: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value13 : NULL;
        case 14: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value14 : NULL;
        case 15: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value15 : NULL;
        case 16: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value16 : NULL;
        case 17: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value17 : NULL;
        case 18: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value18 : NULL;
        case 19: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value19 : NULL;
        case 20: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value20 : NULL;
        case 21: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value21 : NULL;
        case 22: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value22 : NULL;
        case 23: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value23 : NULL;
        case 24: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value24 : NULL;
        case 25: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value25 : NULL;
        case 26: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value26 : NULL;
        case 27: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value27 : NULL;
        case 28: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value28 : NULL;
        case 29: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value29 : NULL;
        case 30: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value30 : NULL;
        case 31: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value31 : NULL;
        case 32: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value32 : NULL;
        case 33: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value33 : NULL;
        case 34: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value34 : NULL;
        case 35: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value35 : NULL;
        case 36: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value36 : NULL;
        case 37: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value37 : NULL;
        case 38: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value38 : NULL;
        case 39: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value39 : NULL;
        case 40: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value40[0] : NULL;
            return NULL;
        case 41: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value41[0] : NULL;
            return NULL;
        case 42: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value42[0] : NULL;
            return NULL;
        case 43: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value43[0] : NULL;
            return NULL;
        case 44: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value44 : NULL;
        case 45: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->value45[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IMGSRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
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
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value7 = *(FLOAT32 *)FieldValue;
            break;
        case 8: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value8 = *(FLOAT32 *)FieldValue;
            break;
        case 9: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value9 = *(FLOAT32 *)FieldValue;
            break;
        case 10: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value10 = *(FLOAT32 *)FieldValue;
            break;
        case 11: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value11 = *(FLOAT32 *)FieldValue;
            break;
        case 12: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value12 = *(FLOAT32 *)FieldValue;
            break;
        case 13: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value13 = *(FLOAT32 *)FieldValue;
            break;
        case 14: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value15 = *(FLOAT32 *)FieldValue;
            break;
        case 16: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value31 = *(FLOAT32 *)FieldValue;
            break;
        case 32: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value32 = *(FLOAT32 *)FieldValue;
            break;
        case 33: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value33 = *(FLOAT32 *)FieldValue;
            break;
        case 34: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value34 = *(FLOAT32 *)FieldValue;
            break;
        case 35: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value35 = *(FLOAT32 *)FieldValue;
            break;
        case 36: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value36 = *(FLOAT32 *)FieldValue;
            break;
        case 37: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value37 = *(FLOAT32 *)FieldValue;
            break;
        case 38: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value40[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value40[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->value40[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->value40[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 41: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value41[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value41[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->value41[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->value41[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 42: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value42[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value42[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->value42[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->value42[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 43: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->value43[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value43[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->value43[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->value43[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 44: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value44 = *(UINT8 *)FieldValue;
            break;
        case 45: //dnam_p DNAM ,, Struct
            if(ArraySize != 3)
                break;
            DNAM.Load();
            DNAM->value45[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->value45[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->value45[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        default:
            break;
        }
    return false;
    }

void IMGSRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 8: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 9: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 10: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 11: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 12: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 13: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 14: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 15: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 16: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 17: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 18: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 19: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 20: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 21: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 22: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 23: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 24: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 25: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 26: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 27: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 28: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 29: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 30: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 31: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 32: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 33: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 34: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 35: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 36: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 37: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 38: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 39: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 40: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 41: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 42: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 43: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 44: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 45: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}