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
#include "..\CLOTRecord.h"

namespace Ob
{
uint32_t CLOTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 6: //script
            return CB_FORMID_FIELD;
        case 7: //enchantment
            return CB_FORMID_FIELD;
        case 8: //enchantPoints
            return CB_UINT16_FIELD;
        case 9: //flags
            return CB_UINT32_FLAG_FIELD;
        case 10: //maleBody_modPath
            return CB_STRING_FIELD;
        case 11: //maleBody_modb
            return CB_FLOAT32_FIELD;
        case 12: //maleBody_modt_p
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
        case 13: //maleWorld_modPath
            return CB_STRING_FIELD;
        case 14: //maleWorld_modb
            return CB_FLOAT32_FIELD;
        case 15: //maleWorld_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD2.IsLoaded() ? MOD2->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 16: //maleIconPath
            return CB_ISTRING_FIELD;
        case 17: //femaleBody_modPath
            return CB_STRING_FIELD;
        case 18: //femaleBody_modb
            return CB_FLOAT32_FIELD;
        case 19: //femaleBody_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD3.IsLoaded() ? MOD3->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 20: //femaleWorld_modPath
            return CB_STRING_FIELD;
        case 21: //femaleWorld_modb
            return CB_FLOAT32_FIELD;
        case 22: //femaleWorld_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MOD4.IsLoaded() ? MOD4->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 23: //femaleIconPath
            return CB_ISTRING_FIELD;
        case 24: //value
            return CB_UINT32_FIELD;
        case 25: //weight
            return CB_FLOAT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CLOTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 7: //enchantment
            return ENAM.IsLoaded() ? &ENAM.value : NULL;
        case 8: //enchantPoints
            return ANAM.IsLoaded() ? &ANAM.value : NULL;
        case 9: //flags
            return &BMDT.value;
        case 10: //maleBody_modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 11: //maleBody_modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 12: //maleBody_modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 13: //maleWorld_modPath
            return MOD2.IsLoaded() ? MOD2->MODL.value : NULL;
        case 14: //maleWorld_modb
            return MOD2.IsLoaded() ? &MOD2->MODB.value : NULL;
        case 15: //maleWorld_modt_p
            *FieldValues = MOD2.IsLoaded() ? MOD2->MODT.value : NULL;
            return NULL;
        case 16: //maleIconPath
            return ICON.value;
        case 17: //femaleBody_modPath
            return MOD3.IsLoaded() ? MOD3->MODL.value : NULL;
        case 18: //femaleBody_modb
            return MOD3.IsLoaded() ? &MOD3->MODB.value : NULL;
        case 19: //femaleBody_modt_p
            *FieldValues = MOD3.IsLoaded() ? MOD3->MODT.value : NULL;
            return NULL;
        case 20: //femaleWorld_modPath
            return MOD4.IsLoaded() ? MOD4->MODL.value : NULL;
        case 21: //femaleWorld_modb
            return MOD4.IsLoaded() ? &MOD4->MODB.value : NULL;
        case 22: //femaleWorld_modt_p
            *FieldValues = MOD4.IsLoaded() ? MOD4->MODT.value : NULL;
            return NULL;
        case 23: //femaleIconPath
            return ICO2.value;
        case 24: //value
            return &DATA.value.value;
        case 25: //weight
            return &DATA.value.weight;
        default:
            return NULL;
        }
    return NULL;
    }

bool CLOTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 6: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 7: //enchantment
            ENAM.value = *(FORMID *)FieldValue;
            return true;
        case 8: //enchantPoints
            ANAM.value = *(uint16_t *)FieldValue;
            break;
        case 9: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 10: //maleBody_modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 11: //maleBody_modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 12: //maleBody_modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //maleWorld_modPath
            MOD2.Load();
            MOD2->MODL.Copy((char *)FieldValue);
            break;
        case 14: //maleWorld_modb
            MOD2.Load();
            MOD2->MODB.value = *(float *)FieldValue;
            break;
        case 15: //maleWorld_modt_p
            MOD2.Load();
            MOD2->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 16: //maleIconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 17: //femaleBody_modPath
            MOD3.Load();
            MOD3->MODL.Copy((char *)FieldValue);
            break;
        case 18: //femaleBody_modb
            MOD3.Load();
            MOD3->MODB.value = *(float *)FieldValue;
            break;
        case 19: //femaleBody_modt_p
            MOD3.Load();
            MOD3->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //femaleWorld_modPath
            MOD4.Load();
            MOD4->MODL.Copy((char *)FieldValue);
            break;
        case 21: //femaleWorld_modb
            MOD4.Load();
            MOD4->MODB.value = *(float *)FieldValue;
            break;
        case 22: //femaleWorld_modt_p
            MOD4.Load();
            MOD4->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 23: //femaleIconPath
            ICO2.Copy((char *)FieldValue);
            break;
        case 24: //value
            DATA.value.value = *(uint32_t *)FieldValue;
            break;
        case 25: //weight
            DATA.value.weight = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CLOTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENVALUEWEIGHT defaultDATA;

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
        case 6: //script
            SCRI.Unload();
            return;
        case 7: //enchantment
            ENAM.Unload();
            return;
        case 8: //enchantPoints
            ANAM.Unload();
            return;
        case 9: //flags
            BMDT.Unload();
            return;
        case 10: //maleBody_modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 11: //maleBody_modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 12: //maleBody_modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 13: //maleWorld_modPath
            if(MOD2.IsLoaded())
                MOD2->MODL.Unload();
            return;
        case 14: //maleWorld_modb
            if(MOD2.IsLoaded())
                MOD2->MODB.Unload();
            return;
        case 15: //maleWorld_modt_p
            if(MOD2.IsLoaded())
                MOD2->MODT.Unload();
            return;
        case 16: //maleIconPath
            ICON.Unload();
            return;
        case 17: //femaleBody_modPath
            if(MOD3.IsLoaded())
                MOD3->MODL.Unload();
            return;
        case 18: //femaleBody_modb
            if(MOD3.IsLoaded())
                MOD3->MODB.Unload();
            return;
        case 19: //femaleBody_modt_p
            if(MOD3.IsLoaded())
                MOD3->MODT.Unload();
            return;
        case 20: //femaleWorld_modPath
            if(MOD4.IsLoaded())
                MOD4->MODL.Unload();
            return;
        case 21: //femaleWorld_modb
            if(MOD4.IsLoaded())
                MOD4->MODB.Unload();
            return;
        case 22: //femaleWorld_modt_p
            if(MOD4.IsLoaded())
                MOD4->MODT.Unload();
            return;
        case 23: //femaleIconPath
            ICO2.Unload();
            return;
        case 24: //value
            DATA.value.value = defaultDATA.value;
            return;
        case 25: //weight
            DATA.value.weight = defaultDATA.weight;
            return;
        default:
            return;
        }
    return;
    }
}