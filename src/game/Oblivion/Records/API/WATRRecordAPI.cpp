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
#include "..\WATRRecord.h"

namespace Ob
{
uint32_t WATRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //texturePath
            return CB_ISTRING_FIELD;
        case 6: //opacity
            return CB_UINT8_FIELD;
        case 7: //flags
            return CB_UINT8_FLAG_FIELD;
        case 8: //materialPath
            return CB_ISTRING_FIELD;
        case 9: //sound
            return CB_FORMID_FIELD;
        case 10: //windVelocity
            return CB_FLOAT32_FIELD;
        case 11: //windDirection
            return CB_FLOAT32_FIELD;
        case 12: //waveAmp
            return CB_FLOAT32_FIELD;
        case 13: //waveFreq
            return CB_FLOAT32_FIELD;
        case 14: //sunPower
            return CB_FLOAT32_FIELD;
        case 15: //reflectAmt
            return CB_FLOAT32_FIELD;
        case 16: //fresnelAmt
            return CB_FLOAT32_FIELD;
        case 17: //xSpeed
            return CB_FLOAT32_FIELD;
        case 18: //ySpeed
            return CB_FLOAT32_FIELD;
        case 19: //fogNear
            return CB_FLOAT32_FIELD;
        case 20: //fogFar
            return CB_FLOAT32_FIELD;
        case 21: //shallowRed
            return CB_UINT8_FIELD;
        case 22: //shallowGreen
            return CB_UINT8_FIELD;
        case 23: //shallowBlue
            return CB_UINT8_FIELD;
        case 24: //unused1
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
        case 25: //deepRed
            return CB_UINT8_FIELD;
        case 26: //deepGreen
            return CB_UINT8_FIELD;
        case 27: //deepBlue
            return CB_UINT8_FIELD;
        case 28: //unused2
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
        case 29: //reflRed
            return CB_UINT8_FIELD;
        case 30: //reflGreen
            return CB_UINT8_FIELD;
        case 31: //reflBlue
            return CB_UINT8_FIELD;
        case 32: //unused3
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
        case 33: //blend
            return CB_UINT8_FIELD;
        case 34: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 35: //rainForce
            return CB_FLOAT32_FIELD;
        case 36: //rainVelocity
            return CB_FLOAT32_FIELD;
        case 37: //rainFalloff
            return CB_FLOAT32_FIELD;
        case 38: //rainDampner
            return CB_FLOAT32_FIELD;
        case 39: //rainSize
            return CB_FLOAT32_FIELD;
        case 40: //dispForce
            return CB_FLOAT32_FIELD;
        case 41: //dispVelocity
            return CB_FLOAT32_FIELD;
        case 42: //dispFalloff
            return CB_FLOAT32_FIELD;
        case 43: //dispDampner
            return CB_FLOAT32_FIELD;
        case 44: //dispSize
            return CB_FLOAT32_FIELD;
        case 45: //damage
            return CB_UINT16_FIELD;
        case 46: //dayWater
            return CB_FORMID_FIELD;
        case 47: //nightWater
            return CB_FORMID_FIELD;
        case 48: //underWater
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * WATRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //texturePath
            return TNAM.value;
        case 6: //opacity
            return &ANAM.value;
        case 7: //flags
            return &FNAM.value;
        case 8: //materialPath
            return MNAM.value;
        case 9: //sound
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        case 10: //windVelocity
            return DATA.IsLoaded() ? &DATA->windVelocity : NULL;
        case 11: //windDirection
            return DATA.IsLoaded() ? &DATA->windDirection : NULL;
        case 12: //waveAmp
            return DATA.IsLoaded() ? &DATA->waveAmp : NULL;
        case 13: //waveFreq
            return DATA.IsLoaded() ? &DATA->waveFreq : NULL;
        case 14: //sunPower
            return DATA.IsLoaded() ? &DATA->sunPower : NULL;
        case 15: //reflectAmt
            return DATA.IsLoaded() ? &DATA->reflectAmt : NULL;
        case 16: //fresnelAmt
            return DATA.IsLoaded() ? &DATA->fresnelAmt : NULL;
        case 17: //xSpeed
            return DATA.IsLoaded() ? &DATA->xSpeed : NULL;
        case 18: //ySpeed
            return DATA.IsLoaded() ? &DATA->ySpeed : NULL;
        case 19: //fogNear
            return DATA.IsLoaded() ? &DATA->fogNear : NULL;
        case 20: //fogFar
            return DATA.IsLoaded() ? &DATA->fogFar : NULL;
        case 21: //shallowRed
            return DATA.IsLoaded() ? &DATA->shallow.red : NULL;
        case 22: //shallowGreen
            return DATA.IsLoaded() ? &DATA->shallow.green : NULL;
        case 23: //shallowBlue
            return DATA.IsLoaded() ? &DATA->shallow.blue : NULL;
        case 24: //unused1
            *FieldValues = DATA.IsLoaded() ? &DATA->shallow.unused1 : NULL;
            return NULL;
        case 25: //deepRed
            return DATA.IsLoaded() ? &DATA->deep.red : NULL;
        case 26: //deepGreen
            return DATA.IsLoaded() ? &DATA->deep.green : NULL;
        case 27: //deepBlue
            return DATA.IsLoaded() ? &DATA->deep.blue : NULL;
        case 28: //unused2
            *FieldValues = DATA.IsLoaded() ? &DATA->deep.unused1 : NULL;
            return NULL;
        case 29: //reflRed
            return DATA.IsLoaded() ? &DATA->refl.red : NULL;
        case 30: //reflGreen
            return DATA.IsLoaded() ? &DATA->refl.green : NULL;
        case 31: //reflBlue
            return DATA.IsLoaded() ? &DATA->refl.blue : NULL;
        case 32: //unused3
            *FieldValues = DATA.IsLoaded() ? &DATA->refl.unused1 : NULL;
            return NULL;
        case 33: //blend
            return DATA.IsLoaded() ? &DATA->blend : NULL;
        case 34: //unused4
            *FieldValues = DATA.IsLoaded() ? &DATA->unused1[0] : NULL;
            return NULL;
        case 35: //rainForce
            return DATA.IsLoaded() ? &DATA->rainForce : NULL;
        case 36: //rainVelocity
            return DATA.IsLoaded() ? &DATA->rainVelocity : NULL;
        case 37: //rainFalloff
            return DATA.IsLoaded() ? &DATA->rainFalloff : NULL;
        case 38: //rainDampner
            return DATA.IsLoaded() ? &DATA->rainDampner : NULL;
        case 39: //rainSize
            return DATA.IsLoaded() ? &DATA->rainSize : NULL;
        case 40: //dispForce
            return DATA.IsLoaded() ? &DATA->dispForce : NULL;
        case 41: //dispVelocity
            return DATA.IsLoaded() ? &DATA->dispVelocity : NULL;
        case 42: //dispFalloff
            return DATA.IsLoaded() ? &DATA->dispFalloff : NULL;
        case 43: //dispDampner
            return DATA.IsLoaded() ? &DATA->dispDampner : NULL;
        case 44: //dispSize
            return DATA.IsLoaded() ? &DATA->dispSize : NULL;
        case 45: //damage
            return DATA.IsLoaded() ? &DATA->damage : NULL;
        case 46: //dayWater
            return GNAM.IsLoaded() ? &GNAM->dayWater : NULL;
        case 47: //nightWater
            return GNAM.IsLoaded() ? &GNAM->nightWater : NULL;
        case 48: //underWater
            return GNAM.IsLoaded() ? &GNAM->underWater : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool WATRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //texturePath
            TNAM.Copy((char *)FieldValue);
            break;
        case 6: //opacity
            ANAM.value = *(uint8_t *)FieldValue;
            break;
        case 7: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 8: //materialPath
            MNAM.Copy((char *)FieldValue);
            break;
        case 9: //sound
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        case 10: //windVelocity
            DATA.Load();
            DATA->windVelocity = *(float *)FieldValue;
            break;
        case 11: //windDirection
            DATA.Load();
            DATA->windDirection = *(float *)FieldValue;
            break;
        case 12: //waveAmp
            DATA.Load();
            DATA->waveAmp = *(float *)FieldValue;
            break;
        case 13: //waveFreq
            DATA.Load();
            DATA->waveFreq = *(float *)FieldValue;
            break;
        case 14: //sunPower
            DATA.Load();
            DATA->sunPower = *(float *)FieldValue;
            break;
        case 15: //reflectAmt
            DATA.Load();
            DATA->reflectAmt = *(float *)FieldValue;
            break;
        case 16: //fresnelAmt
            DATA.Load();
            DATA->fresnelAmt = *(float *)FieldValue;
            break;
        case 17: //xSpeed
            DATA.Load();
            DATA->xSpeed = *(float *)FieldValue;
            break;
        case 18: //ySpeed
            DATA.Load();
            DATA->ySpeed = *(float *)FieldValue;
            break;
        case 19: //fogNear
            DATA.Load();
            DATA->fogNear = *(float *)FieldValue;
            break;
        case 20: //fogFar
            DATA.Load();
            DATA->fogFar = *(float *)FieldValue;
            break;
        case 21: //shallowRed
            DATA.Load();
            DATA->shallow.red = *(uint8_t *)FieldValue;
            break;
        case 22: //shallowGreen
            DATA.Load();
            DATA->shallow.green = *(uint8_t *)FieldValue;
            break;
        case 23: //shallowBlue
            DATA.Load();
            DATA->shallow.blue = *(uint8_t *)FieldValue;
            break;
        case 24: //unused1
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->shallow.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 25: //deepRed
            DATA.Load();
            DATA->deep.red = *(uint8_t *)FieldValue;
            break;
        case 26: //deepGreen
            DATA.Load();
            DATA->deep.green = *(uint8_t *)FieldValue;
            break;
        case 27: //deepBlue
            DATA.Load();
            DATA->deep.blue = *(uint8_t *)FieldValue;
            break;
        case 28: //unused2
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->deep.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 29: //reflRed
            DATA.Load();
            DATA->refl.red = *(uint8_t *)FieldValue;
            break;
        case 30: //reflGreen
            DATA.Load();
            DATA->refl.green = *(uint8_t *)FieldValue;
            break;
        case 31: //reflBlue
            DATA.Load();
            DATA->refl.blue = *(uint8_t *)FieldValue;
            break;
        case 32: //unused3
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->refl.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 33: //blend
            DATA.Load();
            DATA->blend = *(uint8_t *)FieldValue;
            break;
        case 34: //unused4
            if(ArraySize != 3)
                break;
            DATA.Load();
            DATA->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 35: //rainForce
            DATA.Load();
            DATA->rainForce = *(float *)FieldValue;
            break;
        case 36: //rainVelocity
            DATA.Load();
            DATA->rainVelocity = *(float *)FieldValue;
            break;
        case 37: //rainFalloff
            DATA.Load();
            DATA->rainFalloff = *(float *)FieldValue;
            break;
        case 38: //rainDampner
            DATA.Load();
            DATA->rainDampner = *(float *)FieldValue;
            break;
        case 39: //rainSize
            DATA.Load();
            DATA->rainSize = *(float *)FieldValue;
            break;
        case 40: //dispForce
            DATA.Load();
            DATA->dispForce = *(float *)FieldValue;
            break;
        case 41: //dispVelocity
            DATA.Load();
            DATA->dispVelocity = *(float *)FieldValue;
            break;
        case 42: //dispFalloff
            DATA.Load();
            DATA->dispFalloff = *(float *)FieldValue;
            break;
        case 43: //dispDampner
            DATA.Load();
            DATA->dispDampner = *(float *)FieldValue;
            break;
        case 44: //dispSize
            DATA.Load();
            DATA->dispSize = *(float *)FieldValue;
            break;
        case 45: //damage
            DATA.Load();
            DATA->damage = *(uint16_t *)FieldValue;
            break;
        case 46: //dayWater
            GNAM.Load();
            GNAM->dayWater = *(FORMID *)FieldValue;
            return true;
        case 47: //nightWater
            GNAM.Load();
            GNAM->nightWater = *(FORMID *)FieldValue;
            return true;
        case 48: //underWater
            GNAM.Load();
            GNAM->underWater = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void WATRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    WATRDATA defaultDATA;
    WATRGNAM defaultGNAM;

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
        case 5: //texturePath
            TNAM.Unload();
            return;
        case 6: //opacity
            ANAM.Unload();
            return;
        case 7: //flags
            FNAM.Unload();
            return;
        case 8: //materialPath
            MNAM.Unload();
            return;
        case 9: //sound
            SNAM.Unload();
            return;
        case 10: //windVelocity
            if(DATA.IsLoaded())
                DATA->windVelocity = defaultDATA.windVelocity;
            return;
        case 11: //windDirection
            if(DATA.IsLoaded())
                DATA->windDirection = defaultDATA.windDirection;
            return;
        case 12: //waveAmp
            if(DATA.IsLoaded())
                DATA->waveAmp = defaultDATA.waveAmp;
            return;
        case 13: //waveFreq
            if(DATA.IsLoaded())
                DATA->waveFreq = defaultDATA.waveFreq;
            return;
        case 14: //sunPower
            if(DATA.IsLoaded())
                DATA->sunPower = defaultDATA.sunPower;
            return;
        case 15: //reflectAmt
            if(DATA.IsLoaded())
                DATA->reflectAmt = defaultDATA.reflectAmt;
            return;
        case 16: //fresnelAmt
            if(DATA.IsLoaded())
                DATA->fresnelAmt = defaultDATA.fresnelAmt;
            return;
        case 17: //xSpeed
            if(DATA.IsLoaded())
                DATA->xSpeed = defaultDATA.xSpeed;
            return;
        case 18: //ySpeed
            if(DATA.IsLoaded())
                DATA->ySpeed = defaultDATA.ySpeed;
            return;
        case 19: //fogNear
            if(DATA.IsLoaded())
                DATA->fogNear = defaultDATA.fogNear;
            return;
        case 20: //fogFar
            if(DATA.IsLoaded())
                DATA->fogFar = defaultDATA.fogFar;
            return;
        case 21: //shallowRed
            if(DATA.IsLoaded())
                DATA->shallow.red = defaultDATA.shallow.red;
            return;
        case 22: //shallowGreen
            if(DATA.IsLoaded())
                DATA->shallow.green = defaultDATA.shallow.green;
            return;
        case 23: //shallowBlue
            if(DATA.IsLoaded())
                DATA->shallow.blue = defaultDATA.shallow.blue;
            return;
        case 24: //unused1
            if(DATA.IsLoaded())
                DATA->shallow.unused1 = defaultDATA.shallow.unused1;
            return;
        case 25: //deepRed
            if(DATA.IsLoaded())
                DATA->deep.red = defaultDATA.deep.red;
            return;
        case 26: //deepGreen
            if(DATA.IsLoaded())
                DATA->deep.green = defaultDATA.deep.green;
            return;
        case 27: //deepBlue
            if(DATA.IsLoaded())
                DATA->deep.blue = defaultDATA.deep.blue;
            return;
        case 28: //unused2
            if(DATA.IsLoaded())
                DATA->deep.unused1 = defaultDATA.deep.unused1;
            return;
        case 29: //reflRed
            if(DATA.IsLoaded())
                DATA->refl.red = defaultDATA.refl.red;
            return;
        case 30: //reflGreen
            if(DATA.IsLoaded())
                DATA->refl.green = defaultDATA.refl.green;
            return;
        case 31: //reflBlue
            if(DATA.IsLoaded())
                DATA->refl.blue = defaultDATA.refl.blue;
            return;
        case 32: //unused3
            if(DATA.IsLoaded())
                DATA->refl.unused1 = defaultDATA.refl.unused1;
            return;
        case 33: //blend
            if(DATA.IsLoaded())
                DATA->blend = defaultDATA.blend;
            return;
        case 34: //unused4
            if(DATA.IsLoaded())
                {
                DATA->unused1[0] = defaultDATA.unused1[0];
                DATA->unused1[1] = defaultDATA.unused1[1];
                DATA->unused1[2] = defaultDATA.unused1[2];
                }
            return;
        case 35: //rainForce
            if(DATA.IsLoaded())
                DATA->rainForce = defaultDATA.rainForce;
            return;
        case 36: //rainVelocity
            if(DATA.IsLoaded())
                DATA->rainVelocity = defaultDATA.rainVelocity;
            return;
        case 37: //rainFalloff
            if(DATA.IsLoaded())
                DATA->rainFalloff = defaultDATA.rainFalloff;
            return;
        case 38: //rainDampner
            if(DATA.IsLoaded())
                DATA->rainDampner = defaultDATA.rainDampner;
            return;
        case 39: //rainSize
            if(DATA.IsLoaded())
                DATA->rainSize = defaultDATA.rainSize;
            return;
        case 40: //dispForce
            if(DATA.IsLoaded())
                DATA->dispForce = defaultDATA.dispForce;
            return;
        case 41: //dispVelocity
            if(DATA.IsLoaded())
                DATA->dispVelocity = defaultDATA.dispVelocity;
            return;
        case 42: //dispFalloff
            if(DATA.IsLoaded())
                DATA->dispFalloff = defaultDATA.dispFalloff;
            return;
        case 43: //dispDampner
            if(DATA.IsLoaded())
                DATA->dispDampner = defaultDATA.dispDampner;
            return;
        case 44: //dispSize
            if(DATA.IsLoaded())
                DATA->dispSize = defaultDATA.dispSize;
            return;
        case 45: //damage
            if(DATA.IsLoaded())
                DATA->damage = defaultDATA.damage;
            return;
        case 46: //dayWater
            if(GNAM.IsLoaded())
                GNAM->dayWater = defaultGNAM.dayWater;
            return;
        case 47: //nightWater
            if(GNAM.IsLoaded())
                GNAM->nightWater = defaultGNAM.nightWater;
            return;
        case 48: //underWater
            if(GNAM.IsLoaded())
                GNAM->underWater = defaultGNAM.underWater;
            return;
        default:
            return;
        }
    return;
    }
}