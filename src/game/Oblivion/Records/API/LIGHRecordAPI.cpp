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
#include "..\LIGHRecord.h"

namespace Ob
{
uint32_t LIGHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //script
            return CB_FORMID_FIELD;
        case 9: //full
            return CB_STRING_FIELD;
        case 10: //iconPath
            return CB_ISTRING_FIELD;
        case 11: //duration
            return CB_SINT32_FIELD;
        case 12: //radius
            return CB_UINT32_FIELD;
        case 13: //red
            return CB_UINT8_FIELD;
        case 14: //green
            return CB_UINT8_FIELD;
        case 15: //blue
            return CB_UINT8_FIELD;
        case 16: //unused1
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
        case 17: //flags
            return CB_UINT32_FLAG_FIELD;
        case 18: //falloff
            return CB_FLOAT32_FIELD;
        case 19: //fov
            return CB_FLOAT32_FIELD;
        case 20: //value
            return CB_UINT32_FIELD;
        case 21: //weight
            return CB_FLOAT32_FIELD;
        case 22: //fade
            return CB_FLOAT32_FIELD;
        case 23: //sound
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LIGHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 9: //full
            return FULL.value;
        case 10: //iconPath
            return ICON.value;
        case 11: //duration
            return &DATA.value.duration;
        case 12: //radius
            return &DATA.value.radius;
        case 13: //red
            return &DATA.value.color.red;
        case 14: //green
            return &DATA.value.color.green;
        case 15: //blue
            return &DATA.value.color.blue;
        case 16: //unused1
            *FieldValues = &DATA.value.color.unused1;
            return NULL;
        case 17: //flags
            return &DATA.value.flags;
        case 18: //falloff
            return &DATA.value.falloff;
        case 19: //fov
            return &DATA.value.fov;
        case 20: //value
            return &DATA.value.value;
        case 21: //weight
            return &DATA.value.weight;
        case 22: //fade
            return FNAM.IsLoaded() ? &FNAM.value : NULL;
        case 23: //sound
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LIGHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 9: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 10: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 11: //duration
            DATA.value.duration = *(int32_t *)FieldValue;
            break;
        case 12: //radius
            DATA.value.radius = *(uint32_t *)FieldValue;
            break;
        case 13: //red
            DATA.value.color.red = *(uint8_t *)FieldValue;
            break;
        case 14: //green
            DATA.value.color.green = *(uint8_t *)FieldValue;
            break;
        case 15: //blue
            DATA.value.color.blue = *(uint8_t *)FieldValue;
            break;
        case 16: //unused1
            if(ArraySize != 1)
                break;
            DATA.value.color.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 17: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 18: //falloff
            DATA.value.falloff = *(float *)FieldValue;
            break;
        case 19: //fov
            DATA.value.fov = *(float *)FieldValue;
            break;
        case 20: //value
            DATA.value.value = *(uint32_t *)FieldValue;
            break;
        case 21: //weight
            DATA.value.weight = *(float *)FieldValue;
            break;
        case 22: //fade
            FNAM.value = *(float *)FieldValue;
            break;
        case 23: //sound.
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void LIGHRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LIGHDATA defaultDATA;

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
        case 8: //script
            SCRI.Unload();
            return;
        case 9: //full
            FULL.Unload();
            return;
        case 10: //iconPath
            ICON.Unload();
            return;
        case 11: //duration
            DATA.value.duration = defaultDATA.duration;
            return;
        case 12: //radius
            DATA.value.radius = defaultDATA.radius;
            return;
        case 13: //red
            DATA.value.color.red = defaultDATA.color.red;
            return;
        case 14: //green
            DATA.value.color.green = defaultDATA.color.green;
            return;
        case 15: //blue
            DATA.value.color.blue = defaultDATA.color.blue;
            return;
        case 16: //unused1
            DATA.value.color.unused1 = defaultDATA.color.unused1;
            return;
        case 17: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 18: //falloff
            DATA.value.falloff = defaultDATA.falloff;
            return;
        case 19: //fov
            DATA.value.fov = defaultDATA.fov;
            return;
        case 20: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 21: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        case 22: //fade
            FNAM.Unload();
            return;
        case 23: //sound
            SNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}