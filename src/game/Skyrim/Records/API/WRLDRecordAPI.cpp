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
#include "..\WRLDRecord.h"

namespace Sk
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
        case 7: //full
            return CB_STRING_FIELD;
        case 8: //encounterZone
            return CB_FORMID_FIELD;
        case 9: //parent
            return CB_FORMID_FIELD;
        case 10: //parentFlags
            return CB_UINT16_FLAG_FIELD;
        case 11: //climate
            return CB_FORMID_FIELD;
        case 12: //water
            return CB_FORMID_FIELD;
        case 13: //lodWater
            return CB_FORMID_FIELD;
        case 14: //lodWaterHeight
            return CB_FLOAT32_FIELD;
        case 15: //defaultLandHeight
            return CB_FLOAT32_FIELD;
        case 16: //defaultWaterHeight
            return CB_FLOAT32_FIELD;
        case 17: //iconPath
            return CB_ISTRING_FIELD;
        case 18: //smallIconPath
            return CB_ISTRING_FIELD;
        case 19: //dimX
            return CB_SINT32_FIELD;
        case 20: //dimY
            return CB_SINT32_FIELD;
        case 21: //NWCellX
            return CB_SINT16_FIELD;
        case 22: //NWCellY
            return CB_SINT16_FIELD;
        case 23: //SECellX
            return CB_SINT16_FIELD;
        case 24: //SECellY
            return CB_SINT16_FIELD;
        case 25: //mapScale
            return CB_FLOAT32_FIELD;
        case 26: //xCellOffset
            return CB_FLOAT32_FIELD;
        case 27: //yCellOffset
            return CB_FLOAT32_FIELD;
        case 28: //imageSpace
            return CB_FORMID_FIELD;
        case 29: //flags
            return CB_UINT8_FLAG_FIELD;
        case 30: //xMinObjBounds
            return CB_FLOAT32_FIELD;
        case 31: //yMinObjBounds
            return CB_FLOAT32_FIELD;
        case 32: //xMaxObjBounds
            return CB_FLOAT32_FIELD;
        case 33: //yMaxObjBounds
            return CB_FLOAT32_FIELD;
        case 34: //music
            return CB_FORMID_FIELD;
        case 35: //canopyShadowPath
            return CB_ISTRING_FIELD;
        case 36: //waterNoisePath
            return CB_ISTRING_FIELD;
        case 37: //swappedImpacts
            if(ListFieldID == 0) //swappedImpacts
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)IMPS.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= IMPS.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //material
                    return CB_UINT32_TYPE_FIELD;
                case 2: //oldImpact
                    return CB_FORMID_FIELD;
                case 3: //newImpact
                    return CB_FORMID_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 38: //concSolid
            return CB_STRING_FIELD;
        case 39: //concBroken
            return CB_STRING_FIELD;
        case 40: //metalSolid
            return CB_STRING_FIELD;
        case 41: //metalHollow
            return CB_STRING_FIELD;
        case 42: //metalSheet
            return CB_STRING_FIELD;
        case 43: //wood
            return CB_STRING_FIELD;
        case 44: //sand
            return CB_STRING_FIELD;
        case 45: //dirt
            return CB_STRING_FIELD;
        case 46: //grass
            return CB_STRING_FIELD;
        case 47: //water
            return CB_STRING_FIELD;
        case 48: //ofst_p
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
        case 49: //CELL
            return CB_SUBRECORD_FIELD;
        case 50: //CELLS
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
        case 7: //full
            return FULL.value;
        case 8: //encounterZone
            return &XEZN.value;
        case 9: //parent
            return &WNAM.value;
        case 10: //parentFlags
            return &PNAM.value;
        case 11: //climate
            return &CNAM.value;
        case 12: //water
            return &NAM2.value;
        case 13: //lodWater
            return &NAM3.value;
        case 14: //lodWaterHeight
            return NAM4.value;
        case 15: //defaultLandHeight
            return &DNAM.value.defaultLandHeight;
        case 16: //defaultWaterHeight
            return &DNAM.value.defaultWaterHeight;
        case 17: //iconPath
            return ICON.value;
        case 18: //smallIconPath
            return MICO.value;
        case 19: //dimX
            return MNAM.IsLoaded() ? &MNAM->dimX : NULL;
        case 20: //dimY
            return MNAM.IsLoaded() ? &MNAM->dimY : NULL;
        case 21: //NWCellX
            return MNAM.IsLoaded() ? &MNAM->NWCellX : NULL;
        case 22: //NWCellY
            return MNAM.IsLoaded() ? &MNAM->NWCellY : NULL;
        case 23: //SECellX
            return MNAM.IsLoaded() ? &MNAM->SECellX : NULL;
        case 24: //SECellY
            return MNAM.IsLoaded() ? &MNAM->SECellY : NULL;
        case 25: //mapScale
            return &ONAM.value.mapScale;
        case 26: //xCellOffset
            return &ONAM.value.xCellOffset;
        case 27: //yCellOffset
            return &ONAM.value.yCellOffset;
        case 28: //imageSpace
            return &INAM.value;
        case 29: //flags
            return &DATA.value;
        case 30: //xMinObjBounds
            return &NAM0.value.x;
        case 31: //yMinObjBounds
            return &NAM0.value.y;
        case 32: //xMaxObjBounds
            return &NAM9.value.x;
        case 33: //yMaxObjBounds
            return &NAM9.value.y;
        case 34: //music
            return &ZNAM.value;
        case 35: //canopyShadowPath
            return NNAM.value;
        case 36: //waterNoisePath
            return XNAM.value;
        case 37: //swappedImpacts
            if(ListIndex >= IMPS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //material
                    return &IMPS.value[ListIndex]->material;
                case 2: //oldImpact
                    return &IMPS.value[ListIndex]->oldImpact;
                case 3: //newImpact
                    return &IMPS.value[ListIndex]->newImpact;
                default:
                    return NULL;
                }
            return NULL;
        case 38: //concSolid
            return IMPF.IsLoaded() ? &IMPF->concSolid[0] : NULL;
        case 39: //concBroken
            return IMPF.IsLoaded() ? &IMPF->concBroken[0] : NULL;
        case 40: //metalSolid
            return IMPF.IsLoaded() ? &IMPF->metalSolid[0] : NULL;
        case 41: //metalHollow
            return IMPF.IsLoaded() ? &IMPF->metalHollow[0] : NULL;
        case 42: //metalSheet
            return IMPF.IsLoaded() ? &IMPF->metalSheet[0] : NULL;
        case 43: //wood
            return IMPF.IsLoaded() ? &IMPF->wood[0] : NULL;
        case 44: //sand
            return IMPF.IsLoaded() ? &IMPF->sand[0] : NULL;
        case 45: //dirt
            return IMPF.IsLoaded() ? &IMPF->dirt[0] : NULL;
        case 46: //grass
            return IMPF.IsLoaded() ? &IMPF->grass[0] : NULL;
        case 47: //water
            return IMPF.IsLoaded() ? &IMPF->water[0] : NULL;
        case 48: //ofst_p
            *FieldValues = OFST.value;
            return NULL;
        case 49: //CELL
            return CELL;
        case 50: //CELLS
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
        case 7: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 8: //encounterZone
            XEZN.value = *(FORMID *)FieldValue;
            return true;
        case 9: //parent
            WNAM.value = *(FORMID *)FieldValue;
            return true;
        case 10: //parentFlags
            PNAM.value = *(uint16_t *)FieldValue;
            break;
        case 11: //climate
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 12: //water
            NAM2.value = *(FORMID *)FieldValue;
            return true;
        case 13: //lodWater
            NAM3.value = *(FORMID *)FieldValue;
            return true;
        case 14: //lodWaterHeight
            NAM4.Load();
            *NAM4.value = *(float *)FieldValue;
            break;
        case 15: //defaultLandHeight
            DNAM.value.defaultLandHeight = *(float *)FieldValue;
            break;
        case 16: //defaultWaterHeight
            DNAM.value.defaultWaterHeight = *(float *)FieldValue;
            break;
        case 17: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 18: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 19: //dimX
            MNAM.Load();
            MNAM->dimX = *(int32_t *)FieldValue;
            break;
        case 20: //dimY
            MNAM.Load();
            MNAM->dimY = *(int32_t *)FieldValue;
            break;
        case 21: //NWCellX
            MNAM.Load();
            MNAM->NWCellX = *(int16_t *)FieldValue;
            break;
        case 22: //NWCellY
            MNAM.Load();
            MNAM->NWCellY = *(int16_t *)FieldValue;
            break;
        case 23: //SECellX
            MNAM.Load();
            MNAM->SECellX = *(int16_t *)FieldValue;
            break;
        case 24: //SECellY
            MNAM.Load();
            MNAM->SECellY = *(int16_t *)FieldValue;
            break;
        case 25: //mapScale
            ONAM.value.mapScale = *(float *)FieldValue;
            break;
        case 26: //xCellOffset
            ONAM.value.xCellOffset = *(float *)FieldValue;
            break;
        case 27: //yCellOffset
            ONAM.value.yCellOffset = *(float *)FieldValue;
            break;
        case 28: //imageSpace
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 29: //flags
            DATA.value = *(uint8_t *)FieldValue;
            break;
        case 30: //xMinObjBounds
            NAM0.value.x = *(float *)FieldValue;
            break;
        case 31: //yMinObjBounds
            NAM0.value.y = *(float *)FieldValue;
            break;
        case 32: //xMaxObjBounds
            NAM9.value.x = *(float *)FieldValue;
            break;
        case 33: //yMaxObjBounds
            NAM9.value.y = *(float *)FieldValue;
            break;
        case 34: //music
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 35: //canopyShadowPath
            NNAM.Copy((char *)FieldValue);
            break;
        case 36: //waterNoisePath
            XNAM.Copy((char *)FieldValue);
            break;
        case 37: //swappedImpacts
            if(ListFieldID == 0) //swappedImpactsSize
                {
                IMPS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= IMPS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //material
                    IMPS.value[ListIndex]->material = *(uint32_t *)FieldValue;
                    break;
                case 2: //oldImpact
                    IMPS.value[ListIndex]->oldImpact = *(FORMID *)FieldValue;
                    return true;
                case 3: //newImpact
                    IMPS.value[ListIndex]->newImpact = *(FORMID *)FieldValue;
                    return true;
                default:
                    break;
                }
            break;
        case 38: //concSolid
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->concSolid[0], 0x00, sizeof(IMPF->concSolid));
            memcpy(&IMPF->concSolid[0], FieldValue, ArraySize);
            break;
        case 39: //concBroken
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->concBroken[0], 0x00, sizeof(IMPF->concBroken));
            memcpy(&IMPF->concBroken[0], FieldValue, ArraySize);
            break;
        case 40: //metalSolid
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->metalSolid[0], 0x00, sizeof(IMPF->metalSolid));
            memcpy(&IMPF->metalSolid[0], FieldValue, ArraySize);
            break;
        case 41: //metalHollow
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->metalHollow[0], 0x00, sizeof(IMPF->metalHollow));
            memcpy(&IMPF->metalHollow[0], FieldValue, ArraySize);
            break;
        case 42: //metalSheet
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->metalSheet[0], 0x00, sizeof(IMPF->metalSheet));
            memcpy(&IMPF->metalSheet[0], FieldValue, ArraySize);
            break;
        case 43: //wood
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->wood[0], 0x00, sizeof(IMPF->wood));
            memcpy(&IMPF->wood[0], FieldValue, ArraySize);
            break;
        case 44: //sand
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->sand[0], 0x00, sizeof(IMPF->sand));
            memcpy(&IMPF->sand[0], FieldValue, ArraySize);
            break;
        case 45: //dirt
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->dirt[0], 0x00, sizeof(IMPF->dirt));
            memcpy(&IMPF->dirt[0], FieldValue, ArraySize);
            break;
        case 46: //grass
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->grass[0], 0x00, sizeof(IMPF->grass));
            memcpy(&IMPF->grass[0], FieldValue, ArraySize);
            break;
        case 47: //water
            if(FieldValue == NULL)
                break;
            ArraySize = (uint32_t)strlen((char *)FieldValue);
            if(ArraySize > 29)
                break;
            IMPF.Load();
            memset(&IMPF->water[0], 0x00, sizeof(IMPF->water));
            memcpy(&IMPF->water[0], FieldValue, ArraySize);
            break;
        case 48: //ofst_p
            OFST.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void WRLDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENDNAM defaultDNAM;
    GENMNAM defaultMNAM;
    GENONAM defaultONAM;
    GENNAM0 defaultNAM0;
    GENNAM9 defaultNAM9;
    GENIMPS defaultIMPS;
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //encounterZone
            XEZN.Unload();
            return;
        case 9: //parent
            WNAM.Unload();
            return;
        case 10: //parentFlags
            PNAM.Unload();
            return;
        case 11: //climate
            CNAM.Unload();
            return;
        case 12: //water
            NAM2.Unload();
            return;
        case 13: //lodWater
            NAM3.Unload();
            return;
        case 14: //lodWaterHeight
            NAM4.Unload();
            return;
        case 15: //defaultLandHeight
            DNAM.value.defaultLandHeight = defaultDNAM.defaultLandHeight;
            return;
        case 16: //defaultWaterHeight
            DNAM.value.defaultWaterHeight = defaultDNAM.defaultWaterHeight;
            return;
        case 17: //iconPath
            ICON.Unload();
            return;
        case 18: //smallIconPath
            MICO.Unload();
            return;
        case 19: //dimX
            if(MNAM.IsLoaded())
                MNAM->dimX = defaultMNAM.dimX;
            return;
        case 20: //dimY
            if(MNAM.IsLoaded())
                MNAM->dimY = defaultMNAM.dimY;
            return;
        case 21: //NWCellX
            if(MNAM.IsLoaded())
                MNAM->NWCellX = defaultMNAM.NWCellX;
            return;
        case 22: //NWCellY
            if(MNAM.IsLoaded())
                MNAM->NWCellY = defaultMNAM.NWCellY;
            return;
        case 23: //SECellX
            if(MNAM.IsLoaded())
                MNAM->SECellX = defaultMNAM.SECellX;
            return;
        case 24: //SECellY
            if(MNAM.IsLoaded())
                MNAM->SECellY = defaultMNAM.SECellY;
            return;
        case 25: //mapScale
            ONAM.value.mapScale = defaultONAM.mapScale;
            return;
        case 26: //xCellOffset
            ONAM.value.xCellOffset = defaultONAM.xCellOffset;
            return;
        case 27: //yCellOffset
            ONAM.value.yCellOffset = defaultONAM.yCellOffset;
            return;
        case 28: //imageSpace
            INAM.Unload();
            return;
        case 29: //flags
            DATA.Unload();
            return;
        case 30: //xMinObjBounds
            NAM0.value.x = defaultNAM0.x;
            return;
        case 31: //yMinObjBounds
            NAM0.value.y = defaultNAM0.y;
            return;
        case 32: //xMaxObjBounds
            NAM9.value.x = defaultNAM9.x;
            return;
        case 33: //yMaxObjBounds
            NAM9.value.y = defaultNAM9.y;
            return;
        case 34: //music
            ZNAM.Unload();
            return;
        case 35: //canopyShadowPath
            NNAM.Unload();
            return;
        case 36: //waterNoisePath
            XNAM.Unload();
            return;
        case 37: //swappedImpacts
            if(ListFieldID == 0) //swappedImpactsSize
                {
                IMPS.Unload();
                return;
                }

            if(ListIndex >= IMPS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //material
                    IMPS.value[ListIndex]->material = defaultIMPS.material;
                    return;
                case 2: //oldImpact
                    IMPS.value[ListIndex]->oldImpact = defaultIMPS.oldImpact;
                    return;
                case 3: //newImpact
                    IMPS.value[ListIndex]->newImpact = defaultIMPS.newImpact;
                    return;
                default:
                    return;
                }
            return;
        case 38: //concSolid
            if(IMPF.IsLoaded())
                memset(&IMPF->concSolid[0], 0x00, sizeof(IMPF->concSolid));
            return;
        case 39: //concBroken
            if(IMPF.IsLoaded())
                memset(&IMPF->concBroken[0], 0x00, sizeof(IMPF->concBroken));
            return;
        case 40: //metalSolid
            if(IMPF.IsLoaded())
                memset(&IMPF->metalSolid[0], 0x00, sizeof(IMPF->metalSolid));
            return;
        case 41: //metalHollow
            if(IMPF.IsLoaded())
                memset(&IMPF->metalHollow[0], 0x00, sizeof(IMPF->metalHollow));
            return;
        case 42: //metalSheet
            if(IMPF.IsLoaded())
                memset(&IMPF->metalSheet[0], 0x00, sizeof(IMPF->metalSheet));
            return;
        case 43: //wood
            if(IMPF.IsLoaded())
                memset(&IMPF->wood[0], 0x00, sizeof(IMPF->wood));
            return;
        case 44: //sand
            if(IMPF.IsLoaded())
                memset(&IMPF->sand[0], 0x00, sizeof(IMPF->sand));
            return;
        case 45: //dirt
            if(IMPF.IsLoaded())
                memset(&IMPF->dirt[0], 0x00, sizeof(IMPF->dirt));
            return;
        case 46: //grass
            if(IMPF.IsLoaded())
                memset(&IMPF->grass[0], 0x00, sizeof(IMPF->grass));
            return;
        case 47: //water
            if(IMPF.IsLoaded())
                memset(&IMPF->water[0], 0x00, sizeof(IMPF->water));
            return;
        case 48: //ofst_p
            OFST.Unload();
            return;
        default:
            return;
        }
    }
}