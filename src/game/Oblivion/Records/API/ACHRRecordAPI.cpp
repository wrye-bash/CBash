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
#include "..\ACHRRecord.h"

namespace Ob
{
uint32_t ACHRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //base
            return CB_FORMID_FIELD;
        case 6: //unknownXPCIFormID
            return CB_FORMID_FIELD;
        case 7: //unknownXPCIString
            return CB_ISTRING_FIELD;
        case 8: //lod1
            return CB_FLOAT32_FIELD;
        case 9: //lod2
            return CB_FLOAT32_FIELD;
        case 10: //lod3
            return CB_FLOAT32_FIELD;
        case 11: //parent
            return CB_FORMID_FIELD;
        case 12: //parentFlags
            return CB_UINT8_FLAG_FIELD;
        case 13: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XESP.IsLoaded() ? 3 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //merchantContainer
            return CB_FORMID_FIELD;
        case 15: //horse
            return CB_FORMID_FIELD;
        case 16: //xrgd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //scale
            return CB_FLOAT32_FIELD;
        case 18: //posX
            return CB_FLOAT32_FIELD;
        case 19: //posY
            return CB_FLOAT32_FIELD;
        case 20: //posZ
            return CB_FLOAT32_FIELD;
        case 21: //rotX
            return CB_RADIAN_FIELD;
        case 22: //rotY
            return CB_RADIAN_FIELD;
        case 23: //rotZ
            return CB_RADIAN_FIELD;
        case 24: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * ACHRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //base
            return &NAME.value;
        case 6: //unknownXPCIFormID
            return (XPCI.IsLoaded() && XPCI->XPCI.IsLoaded()) ? &XPCI->XPCI.value : NULL;
        case 7: //unknownXPCIString
            return XPCI.IsLoaded() ? XPCI->FULL.value : NULL;
        case 8: //lod1
            return XLOD.IsLoaded() ? &XLOD->lod1 : NULL;
        case 9: //lod2
            return XLOD.IsLoaded() ? &XLOD->lod2 : NULL;
        case 10: //lod3
            return XLOD.IsLoaded() ? &XLOD->lod3 : NULL;
        case 11: //parent
            return XESP.IsLoaded() ? &XESP->parent : NULL;
        case 12: //parentFlags
            return XESP.IsLoaded() ? &XESP->flags : NULL;
        case 13: //unused1
            *FieldValues = XESP.IsLoaded() ? &XESP->unused1[0] : NULL;
            return NULL;
        case 14: //merchantContainer
            return XMRC.IsLoaded() ? &XMRC.value : NULL;
        case 15: //horse
            return XHRS.IsLoaded() ? &XHRS.value : NULL;
        case 16: //xrgd_p
            *FieldValues = XRGD.value;
            return NULL;
        case 17: //scale
            return XSCL.IsLoaded() ? &XSCL.value : NULL;
        case 18: //posX
            return &DATA.value.posX;
        case 19: //posY
            return &DATA.value.posY;
        case 20: //posZ
            return &DATA.value.posZ;
        case 21: //rotX
            return &DATA.value.rotX;
        case 22: //rotY
            return &DATA.value.rotY;
        case 23: //rotZ
            return &DATA.value.rotZ;
        case 24: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool ACHRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //base
            NAME.value = *(FORMID *)FieldValue;
            return true;
        case 6: //unknownXPCIFormID
            XPCI.Load();
            XPCI->XPCI.value = *(FORMID *)FieldValue;
            return true;
        case 7: //unknownXPCIString
            XPCI.Load();
            XPCI->FULL.Copy((char *)FieldValue);
            break;
        case 8: //lod1
            XLOD.Load();
            XLOD->lod1 = *(float *)FieldValue;
            break;
        case 9: //lod2
            XLOD.Load();
            XLOD->lod2 = *(float *)FieldValue;
            break;
        case 10: //lod3
            XLOD.Load();
            XLOD->lod3 = *(float *)FieldValue;
            break;
        case 11: //parent
            XESP.Load();
            XESP->parent = *(FORMID *)FieldValue;
            return true;
        case 12: //parentFlags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 13: //unused1
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XESP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            XESP->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 14: //merchantContainer
            XMRC.value = *(FORMID *)FieldValue;
            return true;
        case 15: //horse
            XHRS.Load();
            XHRS.value = *(FORMID *)FieldValue;
            return true;
        case 16: //xrgd_p
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //scale
            XSCL.Load();
            XSCL.value = *(float *)FieldValue;
            break;
        case 18: //posX
            DATA.value.posX = *(float *)FieldValue;
            break;
        case 19: //posY
            DATA.value.posY = *(float *)FieldValue;
            break;
        case 20: //posZ
            DATA.value.posZ = *(float *)FieldValue;
            break;
        case 21: //rotX
            DATA.value.rotX = *(float *)FieldValue;
            break;
        case 22: //rotY
            DATA.value.rotY = *(float *)FieldValue;
            break;
        case 23: //rotZ
            DATA.value.rotZ = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void ACHRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENXESP defaultXESP;
    GENXLOD defaultXLOD;
    GENPOSDATA defaultDATA;

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
        case 5: //base
            NAME.Unload();
            return;
        case 6: //unknownXPCIFormID
            if(XPCI.IsLoaded())
                XPCI->XPCI.Unload();
            return;
        case 7: //unknownXPCIString
            if(XPCI.IsLoaded())
                XPCI->FULL.Unload();
            return;
        case 8: //lod1
            if(XLOD.IsLoaded())
                XLOD->lod1 = defaultXLOD.lod1;
            return;
        case 9: //lod2
            if(XLOD.IsLoaded())
                XLOD->lod2 = defaultXLOD.lod2;
            return;
        case 10: //lod3
            if(XLOD.IsLoaded())
                XLOD->lod3 = defaultXLOD.lod3;
            return;
        case 11: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            return;
        case 12: //parentFlags
            if(XESP.IsLoaded())
                XESP->flags = defaultXESP.flags;
            return;
        case 13: //unused1
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            return;
        case 14: //merchantContainer
            XMRC.Unload();
            return;
        case 15: //horse
            XHRS.Unload();
            return;
        case 16: //xrgd_p
            XRGD.Unload();
            return;
        case 17: //scale
            XSCL.Unload();
            return;
        case 18: //posX
            DATA.value.posX = defaultDATA.posX;
            return;
        case 19: //posY
            DATA.value.posY = defaultDATA.posY;
            return;
        case 20: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            return;
        case 21: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            return;
        case 22: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            return;
        case 23: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            return;
        default:
            return;
        }
    return;
    }
}