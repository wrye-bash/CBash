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
#include "..\WRLDRecord.h"

namespace Ob
{
uint32_t WRLDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 6: //parent
            return CB_FORMID_FIELD;
        case 7: //climate
            return CB_FORMID_FIELD;
        case 8: //water
            return CB_FORMID_FIELD;
        case 9: //mapPath
            return CB_ISTRING_FIELD;
        case 10: //dimX
            return CB_SINT32_FIELD;
        case 11: //dimY
            return CB_SINT32_FIELD;
        case 12: //NWCellX
            return CB_SINT16_FIELD;
        case 13: //NWCellY
            return CB_SINT16_FIELD;
        case 14: //SECellX
            return CB_SINT16_FIELD;
        case 15: //SECellY
            return CB_SINT16_FIELD;
        case 16: //flags
            return CB_UINT8_FLAG_FIELD;
        case 17: //xMinObjBounds
            return CB_FLOAT32_FIELD;
        case 18: //yMinObjBounds
            return CB_FLOAT32_FIELD;
        case 19: //xMaxObjBounds
            return CB_FLOAT32_FIELD;
        case 20: //yMaxObjBounds
            return CB_FLOAT32_FIELD;
        case 21: //soundType
            return CB_UINT32_FIELD;
        case 22: //ofst_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OFST.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 23: //ROAD
            return CB_SUBRECORD_FIELD;
        case 24: //CELL
            return CB_SUBRECORD_FIELD;
        case 25: //CELLS
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)CELLS.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * WRLDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //parent
            return WNAM.IsLoaded() ? &WNAM.value : NULL;
        case 7: //climate
            return CNAM.IsLoaded() ? &CNAM.value : NULL;
        case 8: //water
            return NAM2.IsLoaded() ? &NAM2.value : NULL;
        case 9: //mapPath
            return ICON.value;
        case 10: //dimX
            return MNAM.IsLoaded() ? &MNAM->dimX : NULL;
        case 11: //dimY
            return MNAM.IsLoaded() ? &MNAM->dimY : NULL;
        case 12: //NWCellX
            return MNAM.IsLoaded() ? &MNAM->NWCellX : NULL;
        case 13: //NWCellY
            return MNAM.IsLoaded() ? &MNAM->NWCellY : NULL;
        case 14: //SECellX
            return MNAM.IsLoaded() ? &MNAM->SECellX : NULL;
        case 15: //SECellY
            return MNAM.IsLoaded() ? &MNAM->SECellY : NULL;
        case 16: //flags
            return &DATA.value;
        case 17: //xMinObjBounds
            return &NAM0.value.x;
        case 18: //yMinObjBounds
            return &NAM0.value.y;
        case 19: //xMaxObjBounds
            return &NAM9.value.x;
        case 20: //yMaxObjBounds
            return &NAM9.value.y;
        case 21: //soundType
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        case 22: //ofst_p
            *FieldValues = OFST.value;
            return NULL;
        case 23: //ROAD
            return ROAD;
        case 24: //CELL
            return CELL;
        case 25: //CELLS
            for(uint32_t p = 0;p < (uint32_t)CELLS.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = CELLS[p];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool WRLDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 6: //parent
            WNAM.value = *(FORMID *)FieldValue;
            return true;
        case 7: //climate
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 8: //water
            NAM2.value = *(FORMID *)FieldValue;
            return true;
        case 9: //mapPath
            ICON.Copy((char *)FieldValue);
            break;
        case 10: //dimX
            MNAM.Load();
            MNAM->dimX = *(int32_t *)FieldValue;
            break;
        case 11: //dimY
            MNAM.Load();
            MNAM->dimY = *(int32_t *)FieldValue;
            break;
        case 12: //NWCellX
            MNAM.Load();
            MNAM->NWCellX = *(int16_t *)FieldValue;
            break;
        case 13: //NWCellY
            MNAM.Load();
            MNAM->NWCellY = *(int16_t *)FieldValue;
            break;
        case 14: //SECellX
            MNAM.Load();
            MNAM->SECellX = *(int16_t *)FieldValue;
            break;
        case 15: //SECellY
            MNAM.Load();
            MNAM->SECellY = *(int16_t *)FieldValue;
            break;
        case 16: //flags
            DATA.value = *(uint8_t *)FieldValue;
            break;
        case 17: //xMinObjBounds
            NAM0.value.x = *(float *)FieldValue;
            break;
        case 18: //yMinObjBounds
            NAM0.value.y = *(float *)FieldValue;
            break;
        case 19: //xMaxObjBounds
            NAM9.value.x = *(float *)FieldValue;
            break;
        case 20: //yMaxObjBounds
            NAM9.value.y = *(float *)FieldValue;
            break;
        case 21: //musicType
            SetMusicType(*(uint32_t *)FieldValue);
            break;
        case 22: //ofst_p
            OFST.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void WRLDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENMNAM defaultMNAM;
    GENNAM0 defaultNAM0;
    GENNAM9 defaultNAM9;

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
        case 6: //parent
            WNAM.Unload();
            return;
        case 7: //climate
            CNAM.Unload();
            return;
        case 8: //water
            NAM2.Unload();
            return;
        case 9: //mapPath
            ICON.Unload();
            return;
        case 10: //dimX
            if(MNAM.IsLoaded())
                MNAM->dimX = defaultMNAM.dimX;
            return;
        case 11: //dimY
            if(MNAM.IsLoaded())
                MNAM->dimY = defaultMNAM.dimY;
            return;
        case 12: //NWCellX
            if(MNAM.IsLoaded())
                MNAM->NWCellX = defaultMNAM.NWCellX;
            return;
        case 13: //NWCellY
            if(MNAM.IsLoaded())
                MNAM->NWCellY = defaultMNAM.NWCellY;
            return;
        case 14: //SECellX
            if(MNAM.IsLoaded())
                MNAM->SECellX = defaultMNAM.SECellX;
            return;
        case 15: //SECellY
            if(MNAM.IsLoaded())
                MNAM->SECellY = defaultMNAM.SECellY;
            return;
        case 16: //flags
            DATA.Unload();
            return;
        case 17: //xMinObjBounds
            NAM0.value.x = defaultNAM0.x;
            return;
        case 18: //yMinObjBounds
            NAM0.value.y = defaultNAM0.y;
            return;
        case 19: //xMaxObjBounds
            NAM9.value.x = defaultNAM9.x;
            return;
        case 20: //yMaxObjBounds
            NAM9.value.y = defaultNAM9.y;
            return;
        case 21: //soundType
            SNAM.Unload();
            return;
        case 22: //ofst_p
            OFST.Unload();
            return;
        default:
            return;
        }
    return;
    }
}