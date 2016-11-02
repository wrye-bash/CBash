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
#include "..\SOUNRecord.h"

namespace FNV
{
uint32_t SOUNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //boundX1
            return CB_SINT16_FIELD;
        case 8: //boundY1
            return CB_SINT16_FIELD;
        case 9: //boundZ1
            return CB_SINT16_FIELD;
        case 10: //boundX2
            return CB_SINT16_FIELD;
        case 11: //boundY2
            return CB_SINT16_FIELD;
        case 12: //boundZ2
            return CB_SINT16_FIELD;
        case 13: //soundPath
            return CB_ISTRING_FIELD;
        case 14: //chance
            return CB_UINT8_FIELD;
        case 15: //minDistance
            return CB_UINT8_FIELD;
        case 16: //maxDistance
            return CB_UINT8_FIELD;
        case 17: //freqAdjustment
            return CB_SINT8_FIELD;
        case 18: //unused1
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
        case 19: //flags
            return CB_UINT32_FLAG_FIELD;
        case 20: //staticAtten
            return CB_SINT16_FIELD;
        case 21: //stopTime
            return CB_UINT8_FIELD;
        case 22: //startTime
            return CB_UINT8_FIELD;
        case 23: //attenCurve
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SINT16_ARRAY_FIELD;
                case 1: //fieldSize
                    return 5;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 24: //reverb
            return CB_SINT16_FIELD;
        case 25: //priority
            return CB_SINT32_FIELD;
        case 26: //x
            return CB_SINT32_FIELD;
        case 27: //y
            return CB_SINT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * SOUNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //soundPath
            return FNAM.value;
        case 14: //chance
            return RNAM.IsLoaded() ? RNAM.value : NULL;
        case 15: //minDistance
            return &SNDD.value.minDistance;
        case 16: //maxDistance
            return &SNDD.value.maxDistance;
        case 17: //freqAdjustment
            return &SNDD.value.freqAdjustment;
        case 18: //unused1
            *FieldValues = &SNDD.value.unused1;
            return NULL;
        case 19: //flags
            return &SNDD.value.flags;
        case 20: //staticAtten
            return &SNDD.value.staticAtten;
        case 21: //stopTime
            return &SNDD.value.stopTime;
        case 22: //startTime
            return &SNDD.value.startTime;
        case 23: //attenCurve
            *FieldValues = &SNDD.value.attenCurve[0];
            return NULL;
        case 24: //reverb
            return &SNDD.value.reverb;
        case 25: //priority
            return &SNDD.value.priority;
        case 26: //x
            return &SNDD.value.x;
        case 27: //y
            return &SNDD.value.y;
        default:
            return NULL;
        }
    return NULL;
    }

bool SOUNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //boundX1
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(int16_t *)FieldValue;
            break;
        case 13: //soundPath
            FNAM.Copy((char *)FieldValue);
            break;
        case 14: //chance
            RNAM.Load();
            *RNAM.value = *(uint8_t *)FieldValue;
            break;
        case 15: //minDistance
            SNDD.value.minDistance = *(uint8_t *)FieldValue;
            break;
        case 16: //maxDistance
            SNDD.value.maxDistance = *(uint8_t *)FieldValue;
            break;
        case 17: //freqAdjustment
            SNDD.value.freqAdjustment = *(int8_t *)FieldValue;
            break;
        case 18: //unused1
            if(ArraySize != 1)
                break;
            SNDD.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 19: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 20: //staticAtten
            SNDD.value.staticAtten = *(int16_t *)FieldValue;
            break;
        case 21: //stopTime
            SNDD.value.stopTime = *(uint8_t *)FieldValue;
            break;
        case 22: //startTime
            SNDD.value.startTime = *(uint8_t *)FieldValue;
            break;
        case 23: //attenCurve
            if(ArraySize != 5)
                break;
            SNDD.value.attenCurve[0] = ((SINT16ARRAY)FieldValue)[0];
            SNDD.value.attenCurve[1] = ((SINT16ARRAY)FieldValue)[1];
            SNDD.value.attenCurve[2] = ((SINT16ARRAY)FieldValue)[2];
            SNDD.value.attenCurve[3] = ((SINT16ARRAY)FieldValue)[3];
            SNDD.value.attenCurve[4] = ((SINT16ARRAY)FieldValue)[4];
            break;
        case 24: //reverb
            SNDD.value.reverb = *(int16_t *)FieldValue;
            break;
        case 25: //priority
            SNDD.value.priority = *(int32_t *)FieldValue;
            break;
        case 26: //x
            SNDD.value.x = *(int32_t *)FieldValue;
            break;
        case 27: //y
            SNDD.value.y = *(int32_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void SOUNRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    SOUNSNDD defaultSNDD;

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
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //soundPath
            FNAM.Unload();
            return;
        case 14: //chance
            RNAM.Unload();
            return;
        case 15: //minDistance
            SNDD.value.minDistance = defaultSNDD.minDistance;
            return;
        case 16: //maxDistance
            SNDD.value.maxDistance = defaultSNDD.maxDistance;
            return;
        case 17: //freqAdjustment
            SNDD.value.freqAdjustment = defaultSNDD.freqAdjustment;
            return;
        case 18: //unused1
            SNDD.value.unused1 = defaultSNDD.unused1;
            return;
        case 19: //flags
            SetFlagMask(defaultSNDD.flags);
            return;
        case 20: //staticAtten
            SNDD.value.staticAtten = defaultSNDD.staticAtten;
            return;
        case 21: //stopTime
            SNDD.value.stopTime = defaultSNDD.stopTime;
            return;
        case 22: //startTime
            SNDD.value.startTime = defaultSNDD.startTime;
            return;
        case 23: //attenCurve
            SNDD.value.attenCurve[0] = defaultSNDD.attenCurve[0];
            SNDD.value.attenCurve[1] = defaultSNDD.attenCurve[1];
            SNDD.value.attenCurve[2] = defaultSNDD.attenCurve[2];
            SNDD.value.attenCurve[3] = defaultSNDD.attenCurve[3];
            SNDD.value.attenCurve[4] = defaultSNDD.attenCurve[4];
            return;
        case 24: //reverb
            SNDD.value.reverb = defaultSNDD.reverb;
            return;
        case 25: //priority
            SNDD.value.priority = defaultSNDD.priority;
            return;
        case 26: //x
            SNDD.value.x = defaultSNDD.x;
            return;
        case 27: //y
            SNDD.value.y = defaultSNDD.y;
            return;
        default:
            return;
        }
    }
}