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
#include "..\CELLRecord.h"

namespace Ob
{
uint32_t CELLRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 6: //flags
            return CB_UINT8_FLAG_FIELD;
        case 7: //ambientRed
            return CB_UINT8_FIELD;
        case 8: //ambientGreen
            return CB_UINT8_FIELD;
        case 9: //ambientBlue
            return CB_UINT8_FIELD;
        case 10: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLL.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //directionalRed
            return CB_UINT8_FIELD;
        case 12: //directionalGreen
            return CB_UINT8_FIELD;
        case 13: //directionalBlue
            return CB_UINT8_FIELD;
        case 14: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLL.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 15: //fogRed
            return CB_UINT8_FIELD;
        case 16: //fogGreen
            return CB_UINT8_FIELD;
        case 17: //fogBlue
            return CB_UINT8_FIELD;
        case 18: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLL.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //fogNear
            return CB_FLOAT32_FIELD;
        case 20: //fogFar
            return CB_FLOAT32_FIELD;
        case 21: //directionalXY
            return CB_SINT32_FIELD;
        case 22: //directionalZ
            return CB_SINT32_FIELD;
        case 23: //directionalFade
            return CB_FLOAT32_FIELD;
        case 24: //fogClip
            return CB_FLOAT32_FIELD;
        case 25: //musicType
            return CB_UINT8_TYPE_FIELD;
        case 26: //owner
            return CB_FORMID_FIELD;
        case 27: //rank
            return CB_SINT32_FIELD;
        case 28: //globalVariable
            return CB_FORMID_FIELD;
        case 29: //climate
            return CB_FORMID_FIELD;
        case 30: //waterHeight
            return CB_FLOAT32_FIELD;
        case 31: //regions
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)XCLR.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 32: //posX
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UNKNOWN_OR_SINT32_FIELD;
                case 2: //WhichType
                    if(!IsInterior())
                        return CB_SINT32_FIELD;
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 33: //posY
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UNKNOWN_OR_SINT32_FIELD;
                case 2: //WhichType
                    if(!IsInterior())
                        return CB_SINT32_FIELD;
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 34: //water
            return CB_FORMID_FIELD;
        case 35: //ACHR
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)ACHR.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 36: //ACRE
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)ACRE.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 37: //REFR
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)REFR.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 38: //PGRD
            return CB_SUBRECORD_FIELD;
        case 39: //LAND
            return CB_SUBRECORD_FIELD;
        case 40: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CELLRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //flags
            return &DATA.value;
        case 7: //ambientRed
            return XCLL.IsLoaded() ? &XCLL->ambient.red : NULL;
        case 8: //ambientGreen
            return XCLL.IsLoaded() ? &XCLL->ambient.green : NULL;
        case 9: //ambientBlue
            return XCLL.IsLoaded() ? &XCLL->ambient.blue : NULL;
        case 10: //unused1
            *FieldValues = XCLL.IsLoaded() ? &XCLL->ambient.unused1 : NULL;
            return NULL;
        case 11: //directionalRed
            return XCLL.IsLoaded() ? &XCLL->directional.red : NULL;
        case 12: //directionalGreen
            return XCLL.IsLoaded() ? &XCLL->directional.green : NULL;
        case 13: //directionalBlue
            return XCLL.IsLoaded() ? &XCLL->directional.blue : NULL;
        case 14: //unused2
            *FieldValues = XCLL.IsLoaded() ? &XCLL->directional.unused1 : NULL;
            return NULL;
        case 15: //fogRed
            return XCLL.IsLoaded() ? &XCLL->fog.red : NULL;
        case 16: //fogGreen
            return XCLL.IsLoaded() ? &XCLL->fog.green : NULL;
        case 17: //fogBlue
            return XCLL.IsLoaded() ? &XCLL->fog.blue : NULL;
        case 18: //unused3
            *FieldValues = XCLL.IsLoaded() ? &XCLL->fog.unused1 : NULL;
            return NULL;
        case 19: //fogNear
            return XCLL.IsLoaded() ? &XCLL->fogNear : NULL;
        case 20: //fogFar
            return XCLL.IsLoaded() ? &XCLL->fogFar : NULL;
        case 21: //directionalXY
            return XCLL.IsLoaded() ? &XCLL->directionalXY : NULL;
        case 22: //directionalZ
            return XCLL.IsLoaded() ? &XCLL->directionalZ : NULL;
        case 23: //directionalFade
            return XCLL.IsLoaded() ? &XCLL->directionalFade : NULL;
        case 24: //fogClip
            return XCLL.IsLoaded() ? &XCLL->fogClip : NULL;
        case 25: //musicType
            return XCMT.IsLoaded() ? &XCMT.value : NULL;
        case 26: //owner
            return Ownership.IsLoaded() ? &Ownership->XOWN.value : NULL;
        case 27: //rank
            return Ownership.IsLoaded() ? Ownership->XRNK.value : NULL;
        case 28: //globalVariable
            return (Ownership.IsLoaded() && Ownership->XGLB.IsLoaded()) ? &Ownership->XGLB.value : NULL;
        case 29: //climate
            return XCCM.IsLoaded() ? &XCCM.value : NULL;
        case 30: //waterHeight
            return XCLW.IsLoaded() ? &XCLW.value : NULL;
        case 31: //regions
            *FieldValues = XCLR.value.size() ? &XCLR.value[0]: NULL;
            return NULL;
        case 32: //posX
            return (!IsInterior() & XCLC.IsLoaded()) ? &XCLC->posX : NULL;
        case 33: //posY
            return (!IsInterior() & XCLC.IsLoaded()) ? &XCLC->posY : NULL;
        case 34: //water
            return XCWT.IsLoaded() ? &XCWT.value : NULL;
        case 35: //ACHR
            for(uint32_t p = 0;p < (uint32_t)ACHR.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = ACHR[p];
            return NULL;
        case 36: //ACRE
            for(uint32_t p = 0;p < (uint32_t)ACRE.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = ACRE[p];
            return NULL;
        case 37: //REFR
            for(uint32_t p = 0;p < (uint32_t)REFR.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = REFR[p];
            return NULL;
        case 38: //PGRD
            return PGRD;
        case 39: //LAND
            return LAND;
        case 40: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool CELLRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 6: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 7: //ambientRed
            XCLL.Load();
            XCLL->ambient.red = *(uint8_t *)FieldValue;
            break;
        case 8: //ambientGreen
            XCLL.Load();
            XCLL->ambient.green = *(uint8_t *)FieldValue;
            break;
        case 9: //ambientBlue
            XCLL.Load();
            XCLL->ambient.blue = *(uint8_t *)FieldValue;
            break;
        case 10: //unused1
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->ambient.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 11: //directionalRed
            XCLL.Load();
            XCLL->directional.red = *(uint8_t *)FieldValue;
            break;
        case 12: //directionalGreen
            XCLL.Load();
            XCLL->directional.green = *(uint8_t *)FieldValue;
            break;
        case 13: //directionalBlue
            XCLL.Load();
            XCLL->directional.blue = *(uint8_t *)FieldValue;
            break;
        case 14: //unused2
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->directional.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 15: //fogRed
            XCLL.Load();
            XCLL->fog.red = *(uint8_t *)FieldValue;
            break;
        case 16: //fogGreen
            XCLL.Load();
            XCLL->fog.green = *(uint8_t *)FieldValue;
            break;
        case 17: //fogBlue
            XCLL.Load();
            XCLL->fog.blue = *(uint8_t *)FieldValue;
            break;
        case 18: //unused3
            if(ArraySize != 1)
                break;
            XCLL.Load();
            XCLL->fog.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 19: //fogNear
            XCLL.Load();
            XCLL->fogNear = *(float *)FieldValue;
            break;
        case 20: //fogFar
            XCLL.Load();
            XCLL->fogFar = *(float *)FieldValue;
            break;
        case 21: //directionalXY
            XCLL.Load();
            XCLL->directionalXY = *(int32_t *)FieldValue;
            break;
        case 22: //directionalZ
            XCLL.Load();
            XCLL->directionalZ = *(int32_t *)FieldValue;
            break;
        case 23: //directionalFade
            XCLL.Load();
            XCLL->directionalFade = *(float *)FieldValue;
            break;
        case 24: //fogClip
            XCLL.Load();
            XCLL->fogClip = *(float *)FieldValue;
            break;
        case 25: //musicType
            SetMusicType(*(uint8_t *)FieldValue);
            break;
        case 26: //owner
            Ownership.Load();
            Ownership->XOWN.value = *(FORMID *)FieldValue;
            return true;
        case 27: //rank
            Ownership.Load();
            Ownership->XRNK.Load();
            *Ownership->XRNK.value = *(int32_t *)FieldValue;
            break;
        case 28: //globalVariable
            Ownership.Load();
            Ownership->XGLB.value = *(FORMID *)FieldValue;
            return true;
        case 29: //climate
            XCCM.Load();
            XCCM.value = *(FORMID *)FieldValue;
            return true;
        case 30: //waterHeight
            XCLW.Load();
            XCLW.value = *(float *)FieldValue;
            break;
        case 31: //regions
            XCLR.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; ++x)
                XCLR.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 32: //posX
            if(IsInterior())
                break;
            XCLC.Load();
            XCLC->posX = *(int32_t *)FieldValue;
            break;
        case 33: //posY
            if(IsInterior())
                break;
            XCLC.Load();
            XCLC->posY = *(int32_t *)FieldValue;
            break;
        case 34: //water
            XCWT.Load();
            XCWT.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void CELLRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CELLXCLL defaultXCLL;
    CELLXCLC defaultXCLC;

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
        case 6: //flags
            DATA.Unload();
            return;
        case 7: //ambientRed
            if(XCLL.IsLoaded())
                XCLL->ambient.red = defaultXCLL.ambient.red;
            return;
        case 8: //ambientGreen
            if(XCLL.IsLoaded())
                XCLL->ambient.green = defaultXCLL.ambient.green;
            return;
        case 9: //ambientBlue
            if(XCLL.IsLoaded())
                XCLL->ambient.blue = defaultXCLL.ambient.blue;
            return;
        case 10: //unused1
            if(XCLL.IsLoaded())
                XCLL->ambient.unused1 = defaultXCLL.ambient.unused1;
            return;
        case 11: //directionalRed
            if(XCLL.IsLoaded())
                XCLL->directional.red = defaultXCLL.directional.red;
            return;
        case 12: //directionalGreen
            if(XCLL.IsLoaded())
                XCLL->directional.green = defaultXCLL.directional.green;
            return;
        case 13: //directionalBlue
            if(XCLL.IsLoaded())
                XCLL->directional.blue = defaultXCLL.directional.blue;
            return;
        case 14: //unused2
            if(XCLL.IsLoaded())
                XCLL->directional.unused1 = defaultXCLL.directional.unused1;
            return;
        case 15: //fogRed
            if(XCLL.IsLoaded())
                XCLL->fog.red = defaultXCLL.fog.red;
            return;
        case 16: //fogGreen
            if(XCLL.IsLoaded())
                XCLL->fog.green = defaultXCLL.fog.green;
            return;
        case 17: //fogBlue
            if(XCLL.IsLoaded())
                XCLL->fog.blue = defaultXCLL.fog.blue;
            return;
        case 18: //unused3
            if(XCLL.IsLoaded())
                XCLL->fog.unused1 = defaultXCLL.fog.unused1;
            return;
        case 19: //fogNear
            if(XCLL.IsLoaded())
                XCLL->fogNear = defaultXCLL.fogNear;
            return;
        case 20: //fogFar
            if(XCLL.IsLoaded())
                XCLL->fogFar = defaultXCLL.fogFar;
            return;
        case 21: //directionalXY
            if(XCLL.IsLoaded())
                XCLL->directionalXY = defaultXCLL.directionalXY;
            return;
        case 22: //directionalZ
            if(XCLL.IsLoaded())
                XCLL->directionalZ = defaultXCLL.directionalZ;
            return;
        case 23: //directionalFade
            if(XCLL.IsLoaded())
                XCLL->directionalFade = defaultXCLL.directionalFade;
            return;
        case 24: //fogClip
            if(XCLL.IsLoaded())
                XCLL->fogClip = defaultXCLL.fogClip;
            return;
        case 25: //musicType
            XCMT.Unload();
            return;
        case 26: //owner
            if(Ownership.IsLoaded())
                Ownership->XOWN.Unload();
            return;
        case 27: //rank
            if(Ownership.IsLoaded())
                Ownership->XRNK.Unload();
            return;
        case 28: //globalVariable
            if(Ownership.IsLoaded())
                Ownership->XGLB.Unload();
            return;
        case 29: //climate
            XCCM.Unload();
            return;
        case 30: //waterHeight
            XCLW.Unload();
            return;
        case 31: //regions
            XCLR.Unload();
            return;
        case 32: //posX
            if(!IsInterior() && XCLC.IsLoaded())
                XCLC->posX = defaultXCLC.posX;
            return;
        case 33: //posY
            if(!IsInterior() && XCLC.IsLoaded())
                XCLC->posY = defaultXCLC.posY;
            return;
        case 34: //water
            XCWT.Unload();
            return;
        default:
            return;
        }
    return;
    }
}