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
#include "..\TREERecord.h"

namespace Ob
{
uint32_t TREERecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //iconPath
            return CB_ISTRING_FIELD;
        case 9: //speedTree
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT32_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)SNAM.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //curvature
            return CB_FLOAT32_FIELD;
        case 11: //minAngle
            return CB_FLOAT32_FIELD;
        case 12: //maxAngle
            return CB_FLOAT32_FIELD;
        case 13: //branchDim
            return CB_FLOAT32_FIELD;
        case 14: //leafDim
            return CB_FLOAT32_FIELD;
        case 15: //shadowRadius
            return CB_SINT32_FIELD;
        case 16: //rockSpeed
            return CB_FLOAT32_FIELD;
        case 17: //rustleSpeed
            return CB_FLOAT32_FIELD;
        case 18: //widthBill
            return CB_FLOAT32_FIELD;
        case 19: //heightBill
            return CB_FLOAT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * TREERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //iconPath
            return ICON.value;
        case 9: //speedTree
            *FieldValues = SNAM.value.size() != 0 ? &SNAM.value[0] : NULL;
            return NULL;
        case 10: //curvature
            return &CNAM.value.curvature;
        case 11: //minAngle
            return &CNAM.value.minAngle;
        case 12: //maxAngle
            return &CNAM.value.maxAngle;
        case 13: //branchDim
            return &CNAM.value.branchDim;
        case 14: //leafDim
            return &CNAM.value.leafDim;
        case 15: //shadowRadius
            return &CNAM.value.shadowRadius;
        case 16: //rockSpeed
            return &CNAM.value.rockSpeed;
        case 17: //rustleSpeed
            return &CNAM.value.rustleSpeed;
        case 18: //widthBill
            return &BNAM.value.widthBill;
        case 19: //heightBill
            return &BNAM.value.heightBill;
        default:
            return NULL;
        }
    return NULL;
    }

bool TREERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 9: //speedTree
            SNAM.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                SNAM.value[x] = ((UINT32ARRAY)FieldValue)[x];
            break;
        case 10: //curvature
            CNAM.value.curvature = *(float *)FieldValue;
            break;
        case 11: //minAngle
            CNAM.value.minAngle = *(float *)FieldValue;
            break;
        case 12: //maxAngle
            CNAM.value.maxAngle = *(float *)FieldValue;
            break;
        case 13: //branchDim
            CNAM.value.branchDim = *(float *)FieldValue;
            break;
        case 14: //leafDim
            CNAM.value.leafDim = *(float *)FieldValue;
            break;
        case 15: //shadowRadius
            CNAM.value.shadowRadius = *(int32_t *)FieldValue;
            break;
        case 16: //rockSpeed
            CNAM.value.rockSpeed = *(float *)FieldValue;
            break;
        case 17: //rustleSpeed
            CNAM.value.rustleSpeed = *(float *)FieldValue;
            break;
        case 18: //widthBill
            BNAM.value.widthBill = *(float *)FieldValue;
            break;
        case 19: //heightBill
            BNAM.value.heightBill = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void TREERecord::DeleteField(FIELD_IDENTIFIERS)
    {
    TREECNAM defaultCNAM;
    TREEBNAM defaultBNAM;

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
        case 8: //iconPath
            ICON.Unload();
            return;
        case 9: //speedTree
            SNAM.Unload();
            return;
        case 10: //curvature
            CNAM.value.curvature = defaultCNAM.curvature;
            return;
        case 11: //minAngle
            CNAM.value.minAngle = defaultCNAM.minAngle;
            return;
        case 12: //maxAngle
            CNAM.value.maxAngle = defaultCNAM.maxAngle;
            return;
        case 13: //branchDim
            CNAM.value.branchDim = defaultCNAM.branchDim;
            return;
        case 14: //leafDim
            CNAM.value.leafDim = defaultCNAM.leafDim;
            return;
        case 15: //shadowRadius
            CNAM.value.shadowRadius = defaultCNAM.shadowRadius;
            return;
        case 16: //rockSpeed
            CNAM.value.rockSpeed = defaultCNAM.rockSpeed;
            return;
        case 17: //rustleSpeed
            CNAM.value.rustleSpeed = defaultCNAM.rustleSpeed;
            return;
        case 18: //widthBill
            BNAM.value.widthBill = defaultBNAM.widthBill;
            return;
        case 19: //heightBill
            BNAM.value.heightBill = defaultBNAM.heightBill;
            return;
        default:
            return;
        }
    return;
    }
}