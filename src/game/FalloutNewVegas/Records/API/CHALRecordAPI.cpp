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
#include "..\CHALRecord.h"

namespace FNV
{
uint32_t CHALRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //script
            return CB_FORMID_FIELD;
        case 9: //description
            return CB_STRING_FIELD;
        case 10: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 11: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 12: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 13: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 14: //data_p DATA ,, Struct
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
        case 15: //data_p DATA ,, Struct
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
        case 16: //data_p DATA ,, Struct
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
        case 17: //snam (depends on type)
            return CB_FORMID_FIELD;
        case 18: //xnam (depends on type)
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CHALRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 9: //description
            return DESC.value;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->challengeType : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->threshold : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->flags : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->interval : NULL;
        case 14: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->var1[0] : NULL;
            return NULL;
        case 15: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->var2[0] : NULL;
            return NULL;
        case 16: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->var3[0] : NULL;
            return NULL;
        case 17: //snam (depends on type)
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        case 18: //xnam (depends on type)
            return XNAM.IsLoaded() ? &XNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool CHALRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //script
            SCRI.Load();
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 9: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->challengeType = *(uint32_t *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->threshold = *(uint32_t *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->flags = *(uint32_t *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->interval = *(uint32_t *)FieldValue;
            break;
        case 14: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->var1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->var1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 15: //data_p DATA ,, Struct
            if(ArraySize != 2)
                break;
            DATA.Load();
            DATA->var2[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->var2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 16: //data_p DATA ,, Struct
            if(ArraySize != 4)
                break;
            DATA.Load();
            DATA->var3[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->var3[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA->var3[2] = ((UINT8ARRAY)FieldValue)[2];
            DATA->var3[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 17: //snam (depends on type)
            SNAM.Load();
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        case 18: //xnam (depends on type)
            XNAM.Load();
            XNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CHALRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 8: //script
            SCRI.Unload();
            return;
        case 9: //description
            DESC.Unload();
            return;
        case 10: //data DATA ,, Struct
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
        case 15: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //snam (depends on type)
            SNAM.Unload();
            return;
        case 18: //xnam (depends on type)
            XNAM.Unload();
            return;
        default:
            return;
        }
    }
}