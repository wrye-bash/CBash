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
#include "..\FLORRecord.h"

namespace Ob
{
uint32_t FLORRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //full
            return CB_STRING_FIELD;
        case 6: //modPath
            return CB_ISTRING_FIELD;
        case 7: //modb
            return CB_FLOAT32_FIELD;
        case 8: //modt_p
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
        case 9: //script
            return CB_FORMID_FIELD;
        case 10: //ingredient
            return CB_FORMID_FIELD;
        case 11: //spring
            return CB_UINT8_FIELD;
        case 12: //summer
            return CB_UINT8_FIELD;
        case 13: //fall
            return CB_UINT8_FIELD;
        case 14: //winter
            return CB_UINT8_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * FLORRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //full
            return FULL.value;
        case 6: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 7: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 8: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 9: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 10: //ingredient
            return PFIG.IsLoaded() ? &PFIG.value : NULL;
        case 11: //spring
            return &PFPC.value.spring;
        case 12: //summer
            return &PFPC.value.summer;
        case 13: //fall
            return &PFPC.value.fall;
        case 14: //winter
            return &PFPC.value.winter;
        default:
            return NULL;
        }
    return NULL;
    }

bool FLORRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 6: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 7: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 8: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 10: //ingredient
            PFIG.Load();
            PFIG.value = *(FORMID *)FieldValue;
            return true;
        case 11: //spring
            PFPC.value.spring = *(uint8_t *)FieldValue;
            break;
        case 12: //summer
            PFPC.value.summer = *(uint8_t *)FieldValue;
            break;
        case 13: //fall
            PFPC.value.fall = *(uint8_t *)FieldValue;
            break;
        case 14: //winter
            PFPC.value.winter = *(uint8_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void FLORRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FLORPFPC defaultPFPC;

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
        case 5: //full
            FULL.Unload();
            return;
        case 6: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 7: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 8: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 9: //script
            SCRI.Unload();
            return;
        case 10: //ingredient
            PFIG.Unload();
            return;
        case 11: //spring
            PFPC.value.spring = defaultPFPC.spring;
            return;
        case 12: //summer
            PFPC.value.summer = defaultPFPC.summer;
            return;
        case 13: //fall
            PFPC.value.fall = defaultPFPC.fall;
            return;
        case 14: //winter
            PFPC.value.winter = defaultPFPC.winter;
            return;
        default:
            return;
        }
    return;
    }
}