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
#include "..\IMGSRecord.h"

namespace FNV
{
uint32_t IMGSRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 8: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 9: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 10: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 11: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 12: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 13: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 14: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 15: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 16: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 17: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 18: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 19: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 20: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 21: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 22: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 23: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 24: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 25: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 26: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 27: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 28: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 29: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 30: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 31: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 32: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 33: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 34: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 35: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 36: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 37: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 38: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 39: //dnam DNAM ,, Struct
            return CB_FLOAT32_FIELD;
        case 40: //dnam_p DNAM ,, Struct
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
        case 41: //dnam_p DNAM ,, Struct
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
        case 42: //dnam_p DNAM ,, Struct
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
        case 43: //dnam_p DNAM ,, Struct
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
        case 44: //dnam DNAM ,, Struct
            return CB_UINT8_FIELD;
        case 45: //dnam_p DNAM ,, Struct
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

void * IMGSRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrEyeAdaptSpeed : NULL;
        case 8: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrBlurRadius : NULL;
        case 9: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrBlurPasses : NULL;
        case 10: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrEmissiveMult : NULL;
        case 11: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrTargetLUM : NULL;
        case 12: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrUpperLUMClamp : NULL;
        case 13: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrBrightScale : NULL;
        case 14: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrBrightClamp : NULL;
        case 15: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrLUMRampNoTex : NULL;
        case 16: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrLUMRampMin : NULL;
        case 17: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrLUMRampMax : NULL;
        case 18: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrSunlightDimmer : NULL;
        case 19: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrGrassDimmer : NULL;
        case 20: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrTreeDimmer : NULL;
        case 21: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hdrSkinDimmer : NULL;
        case 22: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->bloomBlurRadius : NULL;
        case 23: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->bloomAlphaMultInterior : NULL;
        case 24: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->bloomAlphaMultExterior : NULL;
        case 25: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hitBlurRadius : NULL;
        case 26: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hitBlurDampingConstant : NULL;
        case 27: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->hitDampingConstant : NULL;
        case 28: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->neRed : NULL;
        case 29: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->neGreen : NULL;
        case 30: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->neBlue : NULL;
        case 31: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->neBrightness : NULL;
        case 32: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->saturation : NULL;
        case 33: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->contrastAvgLUMValue : NULL;
        case 34: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->contrastValue : NULL;
        case 35: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->brightnessValue : NULL;
        case 36: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->cineRed : NULL;
        case 37: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->cineGreen : NULL;
        case 38: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->cineBlue : NULL;
        case 39: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->cineValue : NULL;
        case 40: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->unused1[0] : NULL;
            return NULL;
        case 41: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->unused2[0] : NULL;
            return NULL;
        case 42: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->unused3[0] : NULL;
            return NULL;
        case 43: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->unused4[0] : NULL;
            return NULL;
        case 44: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->flags : NULL;
        case 45: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.IsLoaded() ? &DNAM->unused5[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IMGSRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrEyeAdaptSpeed = *(float *)FieldValue;
            break;
        case 8: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrBlurRadius = *(float *)FieldValue;
            break;
        case 9: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrBlurPasses = *(float *)FieldValue;
            break;
        case 10: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrEmissiveMult = *(float *)FieldValue;
            break;
        case 11: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrTargetLUM = *(float *)FieldValue;
            break;
        case 12: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrUpperLUMClamp = *(float *)FieldValue;
            break;
        case 13: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrBrightScale = *(float *)FieldValue;
            break;
        case 14: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrBrightClamp = *(float *)FieldValue;
            break;
        case 15: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrLUMRampNoTex = *(float *)FieldValue;
            break;
        case 16: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrLUMRampMin = *(float *)FieldValue;
            break;
        case 17: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrLUMRampMax = *(float *)FieldValue;
            break;
        case 18: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrSunlightDimmer = *(float *)FieldValue;
            break;
        case 19: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrGrassDimmer = *(float *)FieldValue;
            break;
        case 20: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrTreeDimmer = *(float *)FieldValue;
            break;
        case 21: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hdrSkinDimmer = *(float *)FieldValue;
            break;
        case 22: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->bloomBlurRadius = *(float *)FieldValue;
            break;
        case 23: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->bloomAlphaMultInterior = *(float *)FieldValue;
            break;
        case 24: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->bloomAlphaMultExterior = *(float *)FieldValue;
            break;
        case 25: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hitBlurRadius = *(float *)FieldValue;
            break;
        case 26: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hitBlurDampingConstant = *(float *)FieldValue;
            break;
        case 27: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->hitDampingConstant = *(float *)FieldValue;
            break;
        case 28: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->neRed = *(float *)FieldValue;
            break;
        case 29: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->neGreen = *(float *)FieldValue;
            break;
        case 30: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->neBlue = *(float *)FieldValue;
            break;
        case 31: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->neBrightness = *(float *)FieldValue;
            break;
        case 32: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->saturation = *(float *)FieldValue;
            break;
        case 33: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->contrastAvgLUMValue = *(float *)FieldValue;
            break;
        case 34: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->contrastValue = *(float *)FieldValue;
            break;
        case 35: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->brightnessValue = *(float *)FieldValue;
            break;
        case 36: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->cineRed = *(float *)FieldValue;
            break;
        case 37: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->cineGreen = *(float *)FieldValue;
            break;
        case 38: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->cineBlue = *(float *)FieldValue;
            break;
        case 39: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->cineValue = *(float *)FieldValue;
            break;
        case 40: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 41: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->unused2[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 42: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->unused3[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 43: //dnam_p DNAM ,, Struct
            if(ArraySize != 4)
                break;
            DNAM.Load();
            DNAM->unused4[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->unused4[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->unused4[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM->unused4[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 44: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->flags = *(uint8_t *)FieldValue;
            break;
        case 45: //dnam_p DNAM ,, Struct
            if(ArraySize != 3)
                break;
            DNAM.Load();
            DNAM->unused5[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM->unused5[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM->unused5[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        default:
            break;
        }
    return false;
    }

void IMGSRecord::DeleteField(FIELD_IDENTIFIERS)
    {
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
        case 7: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 8: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 9: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 10: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 11: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 12: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 13: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 14: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 15: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 16: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 17: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 18: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 19: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 20: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 21: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 22: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 23: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 24: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 25: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 26: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 27: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 28: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 29: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 30: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 31: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 32: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 33: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 34: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 35: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 36: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 37: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 38: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 39: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 40: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 41: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 42: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 43: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        case 44: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 45: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}