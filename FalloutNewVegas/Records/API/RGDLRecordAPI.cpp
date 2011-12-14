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
#include "..\RGDLRecord.h"

namespace FNV
{
UINT32 RGDLRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //nver Version
            return UINT32_FIELD;
        case 8: //data DATA ,, Struct
            return UINT32_FIELD;
        case 9: //data_p DATA ,, Struct
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
        case 10: //data DATA ,, Struct
            return UINT8_FIELD;
        case 11: //data DATA ,, Struct
            return UINT8_FIELD;
        case 12: //data DATA ,, Struct
            return UINT8_FIELD;
        case 13: //data DATA ,, Struct
            return UINT8_FIELD;
        case 14: //data DATA ,, Struct
            return UINT8_FIELD;
        case 15: //data_p DATA ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 16: //xnam Actor Base
            return FORMID_FIELD;
        case 17: //tnam Body Part Data
            return FORMID_FIELD;
        case 18: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 19: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 20: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 21: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 22: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 23: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 24: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 25: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 26: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 27: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 28: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 29: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 30: //rafd RAFD ,, Struct
            return FLOAT32_FIELD;
        case 31: //rafd RAFD ,, Struct
            return SINT32_FIELD;
        case 32: //rafd RAFD ,, Struct
            return SINT32_FIELD;
        case 33: //rafb Feedback Dynamic Bones
            return UNPARSED_FIELD;
        case 34: //raps RAPS ,, Struct
            return UINT16_FIELD;
        case 35: //raps RAPS ,, Struct
            return UINT8_FIELD;
        case 36: //raps_p RAPS ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 37: //raps RAPS ,, Struct
            return FLOAT32_FIELD;
        case 38: //raps RAPS ,, Struct
            return FLOAT32_FIELD;
        case 39: //raps RAPS ,, Struct
            return FLOAT32_FIELD;
        case 40: //raps RAPS ,, Struct
            return FLOAT32_FIELD;
        case 41: //anam Death Pose
            return ISTRING_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * RGDLRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //nver Version
            return NVER.IsLoaded() ? &NVER->value7 : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value8 : NULL;
        case 9: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value9[0] : NULL;
            return NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value10 : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value11 : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value12 : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value13 : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->value15[0] : NULL;
            return NULL;
        case 16: //xnam Actor Base
            return XNAM.IsLoaded() ? &XNAM->value16 : NULL;
        case 17: //tnam Body Part Data
            return TNAM.IsLoaded() ? &TNAM->value17 : NULL;
        case 18: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value18 : NULL;
        case 19: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value19 : NULL;
        case 20: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value20 : NULL;
        case 21: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value21 : NULL;
        case 22: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value22 : NULL;
        case 23: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value23 : NULL;
        case 24: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value24 : NULL;
        case 25: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value25 : NULL;
        case 26: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value26 : NULL;
        case 27: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value27 : NULL;
        case 28: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value28 : NULL;
        case 29: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value29 : NULL;
        case 30: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value30 : NULL;
        case 31: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value31 : NULL;
        case 32: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->value32 : NULL;
        case 33: //rafb Feedback Dynamic Bones
            return UNPARSEDGET_FIELD33;
        case 34: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value34 : NULL;
        case 35: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value35 : NULL;
        case 36: //raps_p RAPS ,, Struct
            *FieldValues = RAPS.IsLoaded() ? &RAPS->value36[0] : NULL;
            return NULL;
        case 37: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value37 : NULL;
        case 38: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value38 : NULL;
        case 39: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value39 : NULL;
        case 40: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->value40 : NULL;
        case 41: //anam Death Pose
            return ANAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool RGDLRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //nver Version
            NVER.Load();
            NVER->value7 = *(UINT32 *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->value8 = *(UINT32 *)FieldValue;
            break;
        case 9: //data_p DATA ,, Struct
            if(ArraySize != 4)
                break;
            DATA.Load();
            DATA->value9[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->value9[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA->value9[2] = ((UINT8ARRAY)FieldValue)[2];
            DATA->value9[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->value10 = *(UINT8 *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->value11 = *(UINT8 *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(UINT8 *)FieldValue;
            break;
        case 15: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->value15[0] = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 16: //xnam Actor Base
            XNAM.Load();
            XNAM->value16 = *(FORMID *)FieldValue;
            return true;
        case 17: //tnam Body Part Data
            TNAM.Load();
            TNAM->value17 = *(FORMID *)FieldValue;
            return true;
        case 18: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value18 = *(FLOAT32 *)FieldValue;
            break;
        case 19: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value19 = *(FLOAT32 *)FieldValue;
            break;
        case 20: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value20 = *(FLOAT32 *)FieldValue;
            break;
        case 21: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value21 = *(FLOAT32 *)FieldValue;
            break;
        case 22: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value22 = *(FLOAT32 *)FieldValue;
            break;
        case 23: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value23 = *(FLOAT32 *)FieldValue;
            break;
        case 24: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value24 = *(FLOAT32 *)FieldValue;
            break;
        case 25: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value25 = *(FLOAT32 *)FieldValue;
            break;
        case 26: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value26 = *(FLOAT32 *)FieldValue;
            break;
        case 27: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value27 = *(FLOAT32 *)FieldValue;
            break;
        case 28: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value28 = *(FLOAT32 *)FieldValue;
            break;
        case 29: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value29 = *(FLOAT32 *)FieldValue;
            break;
        case 30: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value30 = *(FLOAT32 *)FieldValue;
            break;
        case 31: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value31 = *(SINT32 *)FieldValue;
            break;
        case 32: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->value32 = *(SINT32 *)FieldValue;
            break;
        case 33: //rafb Feedback Dynamic Bones
            return UNPARSEDGET_FIELD33;
        case 34: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value34 = *(UINT16 *)FieldValue;
            break;
        case 35: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value35 = *(UINT8 *)FieldValue;
            break;
        case 36: //raps_p RAPS ,, Struct
            if(ArraySize != 1)
                break;
            RAPS.Load();
            RAPS->value36[0] = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 37: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value37 = *(FLOAT32 *)FieldValue;
            break;
        case 38: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value38 = *(FLOAT32 *)FieldValue;
            break;
        case 39: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value39 = *(FLOAT32 *)FieldValue;
            break;
        case 40: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->value40 = *(FLOAT32 *)FieldValue;
            break;
        case 41: //anam Death Pose
            ANAM.Copy((STRING)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void RGDLRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //nver Version
            NVER.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data_p DATA ,, Struct
            DATA.Unload();
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
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //xnam Actor Base
            XNAM.Unload();
            return;
        case 17: //tnam Body Part Data
            TNAM.Unload();
            return;
        case 18: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 19: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 20: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 21: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 22: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 23: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 24: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 25: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 26: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 27: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 28: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 29: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 30: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 31: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 32: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 33: //rafb Feedback Dynamic Bones
            return UNPARSEDDEL_FIELD33;
        case 34: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 35: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 36: //raps_p RAPS ,, Struct
            RAPS.Unload();
            return;
        case 37: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 38: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 39: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 40: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 41: //anam Death Pose
            ANAM.Unload();
            return;
        default:
            return;
        }
    }
}