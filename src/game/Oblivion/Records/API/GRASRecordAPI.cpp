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
#include "..\GRASRecord.h"

namespace Ob
{
uint32_t GRASRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //modPath
            return CB_ISTRING_FIELD;
        case 6: //modb
            return CB_FLOAT32_FIELD;
        case 7: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //density
            return CB_UINT8_FIELD;
        case 9: //minSlope
            return CB_UINT8_FIELD;
        case 10: //maxSlope
            return CB_UINT8_FIELD;
        case 11: //unused1
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
        case 12: //waterDistance
            return CB_UINT16_FIELD;
        case 13: //unused2
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
        case 14: //waterOp
            return CB_UINT32_FIELD;
        case 15: //posRange
            return CB_FLOAT32_FIELD;
        case 16: //heightRange
            return CB_FLOAT32_FIELD;
        case 17: //colorRange
            return CB_FLOAT32_FIELD;
        case 18: //wavePeriod
            return CB_FLOAT32_FIELD;
        case 19: //flags
            return CB_UINT8_FLAG_FIELD;
        case 20: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * GRASRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 6: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 7: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 8: //density
            return &DATA.value.density;
        case 9: //minSlope
            return &DATA.value.minSlope;
        case 10: //maxSlope
            return &DATA.value.maxSlope;
        case 11: //unused1
            *FieldValues = &DATA.value.unused1;
            return NULL;
        case 12: //waterDistance
            return &DATA.value.waterDistance;
        case 13: //unused2
            *FieldValues = &DATA.value.unused2[0];
            return NULL;
        case 14: //waterOp
            return &DATA.value.waterOp;
        case 15: //posRange
            return &DATA.value.posRange;
        case 16: //heightRange
            return &DATA.value.heightRange;
        case 17: //colorRange
            return &DATA.value.colorRange;
        case 18: //wavePeriod
            return &DATA.value.wavePeriod;
        case 19: //flags
            return &DATA.value.flags;
        case 20: //unused3
            *FieldValues = &DATA.value.unused3[0];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool GRASRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 6: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 7: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //density
            DATA.value.density = *(uint8_t *)FieldValue;
            break;
        case 9: //minSlope
            DATA.value.minSlope = *(uint8_t *)FieldValue;
            break;
        case 10: //maxSlope
            DATA.value.maxSlope = *(uint8_t *)FieldValue;
            break;
        case 11: //unused1
            if(ArraySize != 1)
                break;
            DATA.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 12: //waterDistance
            DATA.value.waterDistance = *(uint16_t *)FieldValue;
            break;
        case 13: //unused2
            if(ArraySize != 2)
                break;
            DATA.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 14: //waterOp
            DATA.value.waterOp = *(uint32_t *)FieldValue;
            break;
        case 15: //posRange
            DATA.value.posRange = *(float *)FieldValue;
            break;
        case 16: //heightRange
            DATA.value.heightRange = *(float *)FieldValue;
            break;
        case 17: //colorRange
            DATA.value.colorRange = *(float *)FieldValue;
            break;
        case 18: //wavePeriod
            DATA.value.wavePeriod = *(float *)FieldValue;
            break;
        case 19: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 20: //unused3
            if(ArraySize != 3)
                break;
            DATA.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        default:
            break;
        }
    return false;
    }

void GRASRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GRASDATA defaultDATA;

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
        case 5: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 6: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 7: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 8: //density
            DATA.value.density = defaultDATA.density;
            return;
        case 9: //minSlope
            DATA.value.minSlope = defaultDATA.minSlope;
            return;
        case 10: //maxSlope
            DATA.value.maxSlope = defaultDATA.maxSlope;
            return;
        case 11: //unused1
            DATA.value.unused1 = defaultDATA.unused1;
            return;
        case 12: //waterDistance
            DATA.value.waterDistance = defaultDATA.waterDistance;
            return;
        case 13: //unused2
            DATA.value.unused2[0] = defaultDATA.unused2[0];
            DATA.value.unused2[1] = defaultDATA.unused2[1];
            return;
        case 14: //waterOp
            DATA.value.waterOp = defaultDATA.waterOp;
            return;
        case 15: //posRange
            DATA.value.posRange = defaultDATA.posRange;
            return;
        case 16: //heightRange
            DATA.value.heightRange = defaultDATA.heightRange;
            return;
        case 17: //colorRange
            DATA.value.colorRange = defaultDATA.colorRange;
            return;
        case 18: //wavePeriod
            DATA.value.wavePeriod = defaultDATA.wavePeriod;
            return;
        case 19: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 20: //unused3
            DATA.value.unused3[0] = defaultDATA.unused3[0];
            DATA.value.unused3[1] = defaultDATA.unused3[1];
            DATA.value.unused3[2] = defaultDATA.unused3[2];
            return;
        default:
            return;
        }
    return;
    }
}