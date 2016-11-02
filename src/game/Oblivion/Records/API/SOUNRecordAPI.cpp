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
#include "..\SOUNRecord.h"

namespace Ob
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
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //soundPath
            return CB_ISTRING_FIELD;
        case 6: //minDistance
            return CB_UINT8_FIELD;
        case 7: //maxDistance
            return CB_UINT8_FIELD;
        case 8: //freqAdjustment
            return CB_SINT8_FIELD;
        case 9: //unused1
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
        case 10: //flags
            return CB_UINT16_FLAG_FIELD;
        case 11: //unused2
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
        case 12: //staticAtten
            return CB_SINT16_FIELD;
        case 13: //stopTime
            return CB_UINT8_FIELD;
        case 14: //startTime
            return CB_UINT8_FIELD;
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
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //soundPath
            return FNAM.value;
        case 6: //minDistance
            return &SNDX.value.minDistance;
        case 7: //maxDistance
            return &SNDX.value.maxDistance;
        case 8: //freqAdjustment
            return &SNDX.value.freqAdjustment;
        case 9: //unused1
            *FieldValues = &SNDX.value.unused1;
            return NULL;
        case 10: //flags
            return &SNDX.value.flags;
        case 11: //unused2
            *FieldValues = &SNDX.value.unused2[0];
            return NULL;
        case 12: //staticAtten
            return &SNDX.value.staticAtten;
        case 13: //stopTime
            return &SNDX.value.stopTime;
        case 14: //startTime
            return &SNDX.value.startTime;
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
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //soundPath
            FNAM.Copy((char *)FieldValue);
            break;
        case 6: //minDistance
            SNDX.value.minDistance = *(uint8_t *)FieldValue;
            break;
        case 7: //maxDistance
            SNDX.value.maxDistance = *(uint8_t *)FieldValue;
            break;
        case 8: //freqAdjustment
            SNDX.value.freqAdjustment = *(int8_t *)FieldValue;
            break;
        case 9: //unused1
            if(ArraySize != 1)
                break;
            SNDX.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 10: //flags
            SetFlagMask(*(uint16_t *)FieldValue);
            break;
        case 11: //unused2
            if(ArraySize != 2)
                break;
            SNDX.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            SNDX.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 12: //staticAtten
            SNDX.value.staticAtten = *(int16_t *)FieldValue;
            break;
        case 13: //stopTime
            SNDX.value.stopTime = *(uint8_t *)FieldValue;
            break;
        case 14: //startTime
            SNDX.value.startTime = *(uint8_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void SOUNRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    SOUNSNDX defaultSNDX;

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
        case 5: //soundPath
            FNAM.Unload();
            return;
        case 6: //minDistance
            SNDX.value.minDistance = defaultSNDX.minDistance;
            return;
        case 7: //maxDistance
            SNDX.value.maxDistance = defaultSNDX.maxDistance;
            return;
        case 8: //freqAdjustment
            SNDX.value.freqAdjustment = defaultSNDX.freqAdjustment;
            return;
        case 9: //unused1
            SNDX.value.unused1 = defaultSNDX.unused1;
            return;
        case 10: //flags
            SNDX.value.flags = defaultSNDX.flags;
            return;
        case 11: //unused2
            SNDX.value.unused2[0] = defaultSNDX.unused2[0];
            SNDX.value.unused2[1] = defaultSNDX.unused2[1];
            return;
        case 12: //staticAtten
            SNDX.value.staticAtten = defaultSNDX.staticAtten;
            return;
        case 13: //stopTime
            SNDX.value.stopTime = defaultSNDX.stopTime;
            return;
        case 14: //startTime
            SNDX.value.startTime = defaultSNDX.startTime;
            return;
        default:
            return;
        }
    return;
    }
}