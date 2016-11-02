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
#include "..\LGTMRecord.h"

namespace FNV
{
uint32_t LGTMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 8: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 9: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 10: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 12: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 13: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 14: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 15: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 16: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 17: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 18: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 20: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 21: //data DATA ,, Struct
            return CB_SINT32_FIELD;
        case 22: //data DATA ,, Struct
            return CB_SINT32_FIELD;
        case 23: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 24: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 25: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LGTMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->ambient.red : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->ambient.green : NULL;
        case 9: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->ambient.blue : NULL;
        case 10: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->ambient.unused1 : NULL;
            return NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directional.red : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directional.blue : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directional.green : NULL;
        case 14: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->directional.unused1 : NULL;
            return NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fog.red : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fog.green : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fog.blue : NULL;
        case 18: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->fog.unused1 : NULL;
            return NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fogNear : NULL;
        case 20: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fogFar : NULL;
        case 21: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directionalXY : NULL;
        case 22: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directionalZ : NULL;
        case 23: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->directionalFade : NULL;
        case 24: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fogClip : NULL;
        case 25: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->fogPower : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LGTMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //data DATA ,, Struct
            DATA.Load();
            DATA->ambient.red = *(uint8_t *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->ambient.green = *(uint8_t *)FieldValue;
            break;
        case 9: //data DATA ,, Struct
            DATA.Load();
            DATA->ambient.blue = *(uint8_t *)FieldValue;
            break;
        case 10: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->ambient.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->directional.red = *(uint8_t *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->directional.green = *(uint8_t *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->directional.blue = *(uint8_t *)FieldValue;
            break;
        case 14: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->directional.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->fog.red = *(uint8_t *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->fog.green = *(uint8_t *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->fog.blue = *(uint8_t *)FieldValue;
            break;
        case 18: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->fog.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->fogNear = *(float *)FieldValue;
            break;
        case 20: //data DATA ,, Struct
            DATA.Load();
            DATA->fogFar = *(float *)FieldValue;
            break;
        case 21: //data DATA ,, Struct
            DATA.Load();
            DATA->directionalXY = *(int32_t *)FieldValue;
            break;
        case 22: //data DATA ,, Struct
            DATA.Load();
            DATA->directionalZ = *(int32_t *)FieldValue;
            break;
        case 23: //data DATA ,, Struct
            DATA.Load();
            DATA->directionalFade = *(float *)FieldValue;
            break;
        case 24: //data DATA ,, Struct
            DATA.Load();
            DATA->fogClip = *(float *)FieldValue;
            break;
        case 25: //data DATA ,, Struct
            DATA.Load();
            DATA->fogPower = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void LGTMRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 21: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 22: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 23: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 25: //data DATA ,, Struct
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}