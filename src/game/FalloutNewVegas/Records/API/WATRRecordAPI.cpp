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
#include "..\WATRRecord.h"

namespace FNV
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
        case 8: //noisePath
            return CB_ISTRING_FIELD;
        case 9: //opacity
            return CB_UINT8_FIELD;
        case 10: //flags
            return CB_UINT8_FIELD;
        case 11: //material
            return CB_ISTRING_FIELD;
        case 12: //sound
            return CB_FORMID_FIELD;
        case 13: //effect
            return CB_FORMID_FIELD;
        case 14: //damage
            return CB_UINT16_FIELD;
        case 15: //unknown1
            return CB_FLOAT32_FIELD;
        case 16: //unknown2
            return CB_FLOAT32_FIELD;
        case 17: //unknown3
            return CB_FLOAT32_FIELD;
        case 18: //unknown4
            return CB_FLOAT32_FIELD;
        case 19: //sunPower
            return CB_FLOAT32_FIELD;
        case 20: //reflectAmt
            return CB_FLOAT32_FIELD;
        case 21: //fresnelAmt
            return CB_FLOAT32_FIELD;
        case 22: //unused1
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
        case 23: //fogNear
            return CB_FLOAT32_FIELD;
        case 24: //fogFar
            return CB_FLOAT32_FIELD;
        case 25: //shallow.red
            return CB_UINT8_FIELD;
        case 26: //shallow.green
            return CB_UINT8_FIELD;
        case 27: //shallow.blue
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
        case 29: //deep.red
            return CB_UINT8_FIELD;
        case 30: //deep.green
            return CB_UINT8_FIELD;
        case 31: //deep.blue
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
        case 33: //refl.red
            return CB_UINT8_FIELD;
        case 34: //refl.green
            return CB_UINT8_FIELD;
        case 35: //refl.blue
            return CB_UINT8_FIELD;
        case 36: //unused4
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
        case 37: //unused5
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
        case 38: //rainForce
            return CB_FLOAT32_FIELD;
        case 39: //rainVelocity
            return CB_FLOAT32_FIELD;
        case 40: //rainFalloff
            return CB_FLOAT32_FIELD;
        case 41: //rainDampner
            return CB_FLOAT32_FIELD;
        case 42: //dispSize
            return CB_FLOAT32_FIELD;
        case 43: //dispForce
            return CB_FLOAT32_FIELD;
        case 44: //dispVelocity
            return CB_FLOAT32_FIELD;
        case 45: //dispFalloff
            return CB_FLOAT32_FIELD;
        case 46: //dispDampner
            return CB_FLOAT32_FIELD;
        case 47: //rainSize
            return CB_FLOAT32_FIELD;
        case 48: //normalsNoiseScale
            return CB_FLOAT32_FIELD;
        case 49: //noise1Direction
            return CB_FLOAT32_FIELD;
        case 50: //noise2Direction
            return CB_FLOAT32_FIELD;
        case 51: //noise3Direction
            return CB_FLOAT32_FIELD;
        case 52: //noise1Speed
            return CB_FLOAT32_FIELD;
        case 53: //noise2Speed
            return CB_FLOAT32_FIELD;
        case 54: //noise3Speed
            return CB_FLOAT32_FIELD;
        case 55: //normalsFalloffStart
            return CB_FLOAT32_FIELD;
        case 56: //normalsFalloffEnd
            return CB_FLOAT32_FIELD;
        case 57: //fogAmt
            return CB_FLOAT32_FIELD;
        case 58: //normalsUVScale
            return CB_FLOAT32_FIELD;
        case 59: //underFogAmt
            return CB_FLOAT32_FIELD;
        case 60: //underFogNear
            return CB_FLOAT32_FIELD;
        case 61: //underFogFar
            return CB_FLOAT32_FIELD;
        case 62: //distAmt
            return CB_FLOAT32_FIELD;
        case 63: //shininess
            return CB_FLOAT32_FIELD;
        case 64: //hdrMult
            return CB_FLOAT32_FIELD;
        case 65: //lightRadius
            return CB_FLOAT32_FIELD;
        case 66: //lightBright
            return CB_FLOAT32_FIELD;
        case 67: //noise1UVScale
            return CB_FLOAT32_FIELD;
        case 68: //noise2UVScale
            return CB_FLOAT32_FIELD;
        case 69: //noise3UVScale
            return CB_FLOAT32_FIELD;
        case 70: //noise1AmpScale
            return CB_FLOAT32_FIELD;
        case 71: //noise2AmpScale
            return CB_FLOAT32_FIELD;
        case 72: //noise3AmpScale
            return CB_FLOAT32_FIELD;
        case 73: //dayWater
            return CB_FORMID_FIELD;
        case 74: //nightWater
            return CB_FORMID_FIELD;
        case 75: //underWater
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
        case 8: //noisePath
            return NNAM.value;
        case 9: //opacity
            return &ANAM.value;
        case 10: //flags
            return &FNAM.value;
        case 11: //material
            return MNAM.value;
        case 12: //sound
            return &SNAM.value;
        case 13: //effect
            return &XNAM.value;
        case 14: //damage
            return &DATA.value;
        case 15: //unknown1
            return &DNAM.value.unknown1;
        case 16: //unknown2
            return &DNAM.value.unknown2;
        case 17: //unknown3
            return &DNAM.value.unknown3;
        case 18: //unknown4
            return &DNAM.value.unknown4;
        case 19: //sunPower
            return &DNAM.value.sunPower;
        case 20: //reflectAmt
            return &DNAM.value.reflectAmt;
        case 21: //fresnelAmt
            return &DNAM.value.fresnelAmt;
        case 22: //unused1
            *FieldValues = &DNAM.value.unused1[0];
            return NULL;
        case 23: //fogNear
            return &DNAM.value.fogNear;
        case 24: //fogFar
            return &DNAM.value.fogFar;
        case 25: //shallow.red
            return &DNAM.value.shallow.red;
        case 26: //shallow.green
            return &DNAM.value.shallow.green;
        case 27: //shallow.blue
            return &DNAM.value.shallow.blue;
        case 28: //unused2
            *FieldValues = &DNAM.value.shallow.unused1;
            return NULL;
        case 29: //deep.red
            return &DNAM.value.deep.red;
        case 30: //deep.green
            return &DNAM.value.deep.green;
        case 31: //deep.blue
            return &DNAM.value.deep.blue;
        case 32: //unused3
            *FieldValues = &DNAM.value.deep.unused1;
            return NULL;
        case 33: //refl.red
            return &DNAM.value.refl.red;
        case 34: //refl.green
            return &DNAM.value.refl.green;
        case 35: //refl.blue
            return &DNAM.value.refl.blue;
        case 36: //unused4
            *FieldValues = &DNAM.value.refl.unused1;
            return NULL;
        case 37: //unused5
            *FieldValues = &DNAM.value.unused2[0];
            return NULL;
        case 38: //rainForce
            return &DNAM.value.rainForce;
        case 39: //rainVelocity
            return &DNAM.value.rainVelocity;
        case 40: //rainFalloff
            return &DNAM.value.rainFalloff;
        case 41: //rainDampner
            return &DNAM.value.rainDampner;
        case 42: //dispSize
            return &DNAM.value.dispSize;
        case 43: //dispForce
            return &DNAM.value.dispForce;
        case 44: //dispVelocity
            return &DNAM.value.dispVelocity;
        case 45: //dispFalloff
            return &DNAM.value.dispFalloff;
        case 46: //dispDampner
            return &DNAM.value.dispDampner;
        case 47: //rainSize
            return &DNAM.value.rainSize;
        case 48: //normalsNoiseScale
            return &DNAM.value.normalsNoiseScale;
        case 49: //noise1Direction
            return &DNAM.value.noise1Direction;
        case 50: //noise2Direction
            return &DNAM.value.noise2Direction;
        case 51: //noise3Direction
            return &DNAM.value.noise3Direction;
        case 52: //noise1Speed
            return &DNAM.value.noise1Speed;
        case 53: //noise2Speed
            return &DNAM.value.noise2Speed;
        case 54: //noise3Speed
            return &DNAM.value.noise3Speed;
        case 55: //normalsFalloffStart
            return &DNAM.value.normalsFalloffStart;
        case 56: //normalsFalloffEnd
            return &DNAM.value.normalsFalloffEnd;
        case 57: //fogAmt
            return &DNAM.value.fogAmt;
        case 58: //normalsUVScale
            return &DNAM.value.normalsUVScale;
        case 59: //underFogAmt
            return &DNAM.value.underFogAmt;
        case 60: //underFogNear
            return &DNAM.value.underFogNear;
        case 61: //underFogFar
            return &DNAM.value.underFogFar;
        case 62: //distAmt
            return &DNAM.value.distAmt;
        case 63: //shininess
            return &DNAM.value.shininess;
        case 64: //hdrMult
            return &DNAM.value.hdrMult;
        case 65: //lightRadius
            return &DNAM.value.lightRadius;
        case 66: //lightBright
            return &DNAM.value.lightBright;
        case 67: //noise1UVScale
            return &DNAM.value.noise1UVScale;
        case 68: //noise2UVScale
            return &DNAM.value.noise2UVScale;
        case 69: //noise3UVScale
            return &DNAM.value.noise3UVScale;
        case 70: //noise1AmpScale
            return &DNAM.value.noise1AmpScale;
        case 71: //noise2AmpScale
            return &DNAM.value.noise2AmpScale;
        case 72: //noise3AmpScale
            return &DNAM.value.noise3AmpScale;
        case 73: //dayWater
            return &GNAM.value.dayWater;
        case 74: //nightWater
            return &GNAM.value.nightWater;
        case 75: //underWater
            return &GNAM.value.underWater;
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
        case 8: //noisePath
            NNAM.Copy((char *)FieldValue);
            break;
        case 9: //opacity
            ANAM.value = *(uint8_t *)FieldValue;
            break;
        case 10: //flags
            FNAM.value = *(uint8_t *)FieldValue;
            break;
        case 11: //material
            MNAM.Copy((char *)FieldValue);
            break;
        case 12: //sound
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //effect
            XNAM.value = *(FORMID *)FieldValue;
            return true;
        case 14: //damage
            DATA.value = *(uint16_t *)FieldValue;
            break;
        case 15: //unknown1
            DNAM.value.unknown1 = *(float *)FieldValue;
            break;
        case 16: //unknown2
            DNAM.value.unknown2 = *(float *)FieldValue;
            break;
        case 17: //unknown3
            DNAM.value.unknown3 = *(float *)FieldValue;
            break;
        case 18: //unknown4
            DNAM.value.unknown4 = *(float *)FieldValue;
            break;
        case 19: //sunPower
            DNAM.value.sunPower = *(float *)FieldValue;
            break;
        case 20: //reflectAmt
            DNAM.value.reflectAmt = *(float *)FieldValue;
            break;
        case 21: //fresnelAmt
            DNAM.value.fresnelAmt = *(float *)FieldValue;
            break;
        case 22: //unused1
            if(ArraySize != 4)
                break;
            DNAM.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 23: //fogNear
            DNAM.value.fogNear = *(float *)FieldValue;
            break;
        case 24: //fogFar
            DNAM.value.fogFar = *(float *)FieldValue;
            break;
        case 25: //shallow.red
            DNAM.value.shallow.red = *(uint8_t *)FieldValue;
            break;
        case 26: //shallow.green
            DNAM.value.shallow.green = *(uint8_t *)FieldValue;
            break;
        case 27: //shallow.blue
            DNAM.value.shallow.blue = *(uint8_t *)FieldValue;
            break;
        case 28: //unused2
            if(ArraySize != 1)
                break;
            DNAM.value.shallow.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 29: //deep.red
            DNAM.value.deep.red = *(uint8_t *)FieldValue;
            break;
        case 30: //deep.green
            DNAM.value.deep.green = *(uint8_t *)FieldValue;
            break;
        case 31: //deep.blue
            DNAM.value.deep.blue = *(uint8_t *)FieldValue;
            break;
        case 32: //unused3
            if(ArraySize != 1)
                break;
            DNAM.value.deep.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 33: //refl.red
            DNAM.value.refl.red = *(uint8_t *)FieldValue;
            break;
        case 34: //refl.green
            DNAM.value.refl.green = *(uint8_t *)FieldValue;
            break;
        case 35: //refl.blue
            DNAM.value.refl.blue = *(uint8_t *)FieldValue;
            break;
        case 36: //unused4
            if(ArraySize != 1)
                break;
            DNAM.value.refl.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 37: //unused5
            if(ArraySize != 4)
                break;
            DNAM.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            DNAM.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            DNAM.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
            DNAM.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 38: //rainForce
            DNAM.value.rainForce = *(float *)FieldValue;
            break;
        case 39: //rainVelocity
            DNAM.value.rainVelocity = *(float *)FieldValue;
            break;
        case 40: //rainFalloff
            DNAM.value.rainFalloff = *(float *)FieldValue;
            break;
        case 41: //rainDampner
            DNAM.value.rainDampner = *(float *)FieldValue;
            break;
        case 42: //dispSize
            DNAM.value.dispSize = *(float *)FieldValue;
            break;
        case 43: //dispForce
            DNAM.value.dispForce = *(float *)FieldValue;
            break;
        case 44: //dispVelocity
            DNAM.value.dispVelocity = *(float *)FieldValue;
            break;
        case 45: //dispFalloff
            DNAM.value.dispFalloff = *(float *)FieldValue;
            break;
        case 46: //dispDampner
            DNAM.value.dispDampner = *(float *)FieldValue;
            break;
        case 47: //rainSize
            DNAM.value.rainSize = *(float *)FieldValue;
            break;
        case 48: //normalsNoiseScale
            DNAM.value.normalsNoiseScale = *(float *)FieldValue;
            break;
        case 49: //noise1Direction
            DNAM.value.noise1Direction = *(float *)FieldValue;
            break;
        case 50: //noise2Direction
            DNAM.value.noise2Direction = *(float *)FieldValue;
            break;
        case 51: //noise3Direction
            DNAM.value.noise3Direction = *(float *)FieldValue;
            break;
        case 52: //noise1Speed
            DNAM.value.noise1Speed = *(float *)FieldValue;
            break;
        case 53: //noise2Speed
            DNAM.value.noise2Speed = *(float *)FieldValue;
            break;
        case 54: //noise3Speed
            DNAM.value.noise3Speed = *(float *)FieldValue;
            break;
        case 55: //normalsFalloffStart
            DNAM.value.normalsFalloffStart = *(float *)FieldValue;
            break;
        case 56: //normalsFalloffEnd
            DNAM.value.normalsFalloffEnd = *(float *)FieldValue;
            break;
        case 57: //fogAmt
            DNAM.value.fogAmt = *(float *)FieldValue;
            break;
        case 58: //normalsUVScale
            DNAM.value.normalsUVScale = *(float *)FieldValue;
            break;
        case 59: //underFogAmt
            DNAM.value.underFogAmt = *(float *)FieldValue;
            break;
        case 60: //underFogNear
            DNAM.value.underFogNear = *(float *)FieldValue;
            break;
        case 61: //underFogFar
            DNAM.value.underFogFar = *(float *)FieldValue;
            break;
        case 62: //distAmt
            DNAM.value.distAmt = *(float *)FieldValue;
            break;
        case 63: //shininess
            DNAM.value.shininess = *(float *)FieldValue;
            break;
        case 64: //hdrMult
            DNAM.value.hdrMult = *(float *)FieldValue;
            break;
        case 65: //lightRadius
            DNAM.value.lightRadius = *(float *)FieldValue;
            break;
        case 66: //lightBright
            DNAM.value.lightBright = *(float *)FieldValue;
            break;
        case 67: //noise1UVScale
            DNAM.value.noise1UVScale = *(float *)FieldValue;
            break;
        case 68: //noise2UVScale
            DNAM.value.noise2UVScale = *(float *)FieldValue;
            break;
        case 69: //noise3UVScale
            DNAM.value.noise3UVScale = *(float *)FieldValue;
            break;
        case 70: //noise1AmpScale
            DNAM.value.noise1AmpScale = *(float *)FieldValue;
            break;
        case 71: //noise2AmpScale
            DNAM.value.noise2AmpScale = *(float *)FieldValue;
            break;
        case 72: //noise3AmpScale
            DNAM.value.noise3AmpScale = *(float *)FieldValue;
            break;
        case 73: //dayWater
            GNAM.value.dayWater = *(FORMID *)FieldValue;
            return true;
        case 74: //nightWater
            GNAM.value.nightWater = *(FORMID *)FieldValue;
            return true;
        case 75: //underWater
            GNAM.value.underWater = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void WATRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    WATRDNAM defaultDNAM;
    WATRGNAM defaultGNAM;
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
        case 8: //noisePath
            NNAM.Unload();
            return;
        case 9: //opacity
            ANAM.Unload();
            return;
        case 10: //flags
            FNAM.Unload();
            return;
        case 11: //material
            MNAM.Unload();
            return;
        case 12: //sound
            SNAM.Unload();
            return;
        case 13: //effect
            XNAM.Unload();
            return;
        case 14: //damage
            DATA.Unload();
            return;
        case 15: //unknown1
            DNAM.value.unknown1 = defaultDNAM.unknown1;
            return;
        case 16: //unknown2
            DNAM.value.unknown2 = defaultDNAM.unknown2;
            return;
        case 17: //unknown3
            DNAM.value.unknown3 = defaultDNAM.unknown3;
            return;
        case 18: //unknown4
            DNAM.value.unknown4 = defaultDNAM.unknown4;
            return;
        case 19: //sunPower
            DNAM.value.sunPower = defaultDNAM.sunPower;
            return;
        case 20: //reflectAmt
            DNAM.value.reflectAmt = defaultDNAM.reflectAmt;
            return;
        case 21: //fresnelAmt
            DNAM.value.fresnelAmt = defaultDNAM.fresnelAmt;
            return;
        case 22: //unused1
            DNAM.value.unused1[0] = defaultDNAM.unused1[0];
            DNAM.value.unused1[1] = defaultDNAM.unused1[1];
            DNAM.value.unused1[2] = defaultDNAM.unused1[2];
            DNAM.value.unused1[3] = defaultDNAM.unused1[3];
            return;
        case 23: //fogNear
            DNAM.value.fogNear = defaultDNAM.fogNear;
            return;
        case 24: //fogFar
            DNAM.value.fogFar = defaultDNAM.fogFar;
            return;
        case 25: //shallow.red
            DNAM.value.shallow.red = defaultDNAM.shallow.red;
            return;
        case 26: //shallow.green
            DNAM.value.shallow.green = defaultDNAM.shallow.green;
            return;
        case 27: //shallow.blue
            DNAM.value.shallow.blue = defaultDNAM.shallow.blue;
            return;
        case 28: //unused2
            DNAM.value.shallow.unused1 = defaultDNAM.shallow.unused1;
            return;
        case 29: //deep.red
            DNAM.value.deep.red = defaultDNAM.deep.red;
            return;
        case 30: //deep.green
            DNAM.value.deep.green = defaultDNAM.deep.green;
            return;
        case 31: //deep.blue
            DNAM.value.deep.blue = defaultDNAM.deep.blue;
            return;
        case 32: //unused3
            DNAM.value.deep.unused1 = defaultDNAM.deep.unused1;
            return;
        case 33: //refl.red
            DNAM.value.refl.red = defaultDNAM.refl.red;
            return;
        case 34: //refl.green
            DNAM.value.refl.green = defaultDNAM.refl.green;
            return;
        case 35: //refl.blue
            DNAM.value.refl.blue = defaultDNAM.refl.blue;
            return;
        case 36: //unused4
            DNAM.value.refl.unused1 = defaultDNAM.refl.unused1;
            return;
        case 37: //unused5
            DNAM.value.unused2[0] = defaultDNAM.unused2[0];
            DNAM.value.unused2[1] = defaultDNAM.unused2[1];
            DNAM.value.unused2[2] = defaultDNAM.unused2[2];
            DNAM.value.unused2[3] = defaultDNAM.unused2[3];
            return;
        case 38: //rainForce
            DNAM.value.rainForce = defaultDNAM.rainForce;
            return;
        case 39: //rainVelocity
            DNAM.value.rainVelocity = defaultDNAM.rainVelocity;
            return;
        case 40: //rainFalloff
            DNAM.value.rainFalloff = defaultDNAM.rainFalloff;
            return;
        case 41: //rainDampner
            DNAM.value.rainDampner = defaultDNAM.rainDampner;
            return;
        case 42: //dispSize
            DNAM.value.dispSize = defaultDNAM.dispSize;
            return;
        case 43: //dispForce
            DNAM.value.dispForce = defaultDNAM.dispForce;
            return;
        case 44: //dispVelocity
            DNAM.value.dispVelocity = defaultDNAM.dispVelocity;
            return;
        case 45: //dispFalloff
            DNAM.value.dispFalloff = defaultDNAM.dispFalloff;
            return;
        case 46: //dispDampner
            DNAM.value.dispDampner = defaultDNAM.dispDampner;
            return;
        case 47: //rainSize
            DNAM.value.rainSize = defaultDNAM.rainSize;
            return;
        case 48: //normalsNoiseScale
            DNAM.value.normalsNoiseScale = defaultDNAM.normalsNoiseScale;
            return;
        case 49: //noise1Direction
            DNAM.value.noise1Direction = defaultDNAM.noise1Direction;
            return;
        case 50: //noise2Direction
            DNAM.value.noise2Direction = defaultDNAM.noise2Direction;
            return;
        case 51: //noise3Direction
            DNAM.value.noise3Direction = defaultDNAM.noise3Direction;
            return;
        case 52: //noise1Speed
            DNAM.value.noise1Speed = defaultDNAM.noise1Speed;
            return;
        case 53: //noise2Speed
            DNAM.value.noise2Speed = defaultDNAM.noise2Speed;
            return;
        case 54: //noise3Speed
            DNAM.value.noise3Speed = defaultDNAM.noise3Speed;
            return;
        case 55: //normalsFalloffStart
            DNAM.value.normalsFalloffStart = defaultDNAM.normalsFalloffStart;
            return;
        case 56: //normalsFalloffEnd
            DNAM.value.normalsFalloffEnd = defaultDNAM.normalsFalloffEnd;
            return;
        case 57: //fogAmt
            DNAM.value.fogAmt = defaultDNAM.fogAmt;
            return;
        case 58: //normalsUVScale
            DNAM.value.normalsUVScale = defaultDNAM.normalsUVScale;
            return;
        case 59: //underFogAmt
            DNAM.value.underFogAmt = defaultDNAM.underFogAmt;
            return;
        case 60: //underFogNear
            DNAM.value.underFogNear = defaultDNAM.underFogNear;
            return;
        case 61: //underFogFar
            DNAM.value.underFogFar = defaultDNAM.underFogFar;
            return;
        case 62: //distAmt
            DNAM.value.distAmt = defaultDNAM.distAmt;
            return;
        case 63: //shininess
            DNAM.value.shininess = defaultDNAM.shininess;
            return;
        case 64: //hdrMult
            DNAM.value.hdrMult = defaultDNAM.hdrMult;
            return;
        case 65: //lightRadius
            DNAM.value.lightRadius = defaultDNAM.lightRadius;
            return;
        case 66: //lightBright
            DNAM.value.lightBright = defaultDNAM.lightBright;
            return;
        case 67: //noise1UVScale
            DNAM.value.noise1UVScale = defaultDNAM.noise1UVScale;
            return;
        case 68: //noise2UVScale
            DNAM.value.noise2UVScale = defaultDNAM.noise2UVScale;
            return;
        case 69: //noise3UVScale
            DNAM.value.noise3UVScale = defaultDNAM.noise3UVScale;
            return;
        case 70: //noise1AmpScale
            DNAM.value.noise1AmpScale = defaultDNAM.noise1AmpScale;
            return;
        case 71: //noise2AmpScale
            DNAM.value.noise2AmpScale = defaultDNAM.noise2AmpScale;
            return;
        case 72: //noise3AmpScale
            DNAM.value.noise3AmpScale = defaultDNAM.noise3AmpScale;
            return;
        case 73: //dayWater
            GNAM.value.dayWater = defaultGNAM.dayWater;
            return;
        case 74: //nightWater
            GNAM.value.nightWater = defaultGNAM.nightWater;
            return;
        case 75: //underWater
            GNAM.value.underWater = defaultGNAM.underWater;
            return;
        default:
            return;
        }
    }
}