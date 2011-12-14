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
#include "..\WTHRRecord.h"

namespace Ob
{
UINT32 WTHRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //lowerLayerPath
            return ISTRING_FIELD;
        case 6: //upperLayerPath
            return ISTRING_FIELD;
        case 7: //modPath
            return ISTRING_FIELD;
        case 8: //modb
            return FLOAT32_FIELD;
        case 9: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //upperSky.rise.red
            return UINT8_FIELD;
        case 11: //upperSky.rise.green
            return UINT8_FIELD;
        case 12: //upperSky.rise.blue
            return UINT8_FIELD;
        case 13: //upperSky.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //upperSky.day.red
            return UINT8_FIELD;
        case 15: //upperSky.day.green
            return UINT8_FIELD;
        case 16: //upperSky.day.blue
            return UINT8_FIELD;
        case 17: //upperSky.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 18: //upperSky.set.red
            return UINT8_FIELD;
        case 19: //upperSky.set.green
            return UINT8_FIELD;
        case 20: //upperSky.set.blue
            return UINT8_FIELD;
        case 21: //upperSky.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 22: //upperSky.night.red
            return UINT8_FIELD;
        case 23: //upperSky.night.green
            return UINT8_FIELD;
        case 24: //upperSky.night.blue
            return UINT8_FIELD;
        case 25: //upperSky.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //fog.rise.red
            return UINT8_FIELD;
        case 27: //fog.rise.green
            return UINT8_FIELD;
        case 28: //fog.rise.blue
            return UINT8_FIELD;
        case 29: //fog.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 30: //fog.day.red
            return UINT8_FIELD;
        case 31: //fog.day.green
            return UINT8_FIELD;
        case 32: //fog.day.blue
            return UINT8_FIELD;
        case 33: //fog.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 34: //fog.set.red
            return UINT8_FIELD;
        case 35: //fog.set.green
            return UINT8_FIELD;
        case 36: //fog.set.blue
            return UINT8_FIELD;
        case 37: //fog.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 38: //fog.night.red
            return UINT8_FIELD;
        case 39: //fog.night.green
            return UINT8_FIELD;
        case 40: //fog.night.blue
            return UINT8_FIELD;
        case 41: //fog.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 42: //lowerClouds.rise.red
            return UINT8_FIELD;
        case 43: //lowerClouds.rise.green
            return UINT8_FIELD;
        case 44: //lowerClouds.rise.blue
            return UINT8_FIELD;
        case 45: //lowerClouds.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 46: //lowerClouds.day.red
            return UINT8_FIELD;
        case 47: //lowerClouds.day.green
            return UINT8_FIELD;
        case 48: //lowerClouds.day.blue
            return UINT8_FIELD;
        case 49: //lowerClouds.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 50: //lowerClouds.set.red
            return UINT8_FIELD;
        case 51: //lowerClouds.set.green
            return UINT8_FIELD;
        case 52: //lowerClouds.set.blue
            return UINT8_FIELD;
        case 53: //lowerClouds.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 54: //lowerClouds.night.red
            return UINT8_FIELD;
        case 55: //lowerClouds.night.green
            return UINT8_FIELD;
        case 56: //lowerClouds.night.blue
            return UINT8_FIELD;
        case 57: //lowerClouds.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 58: //ambient.rise.red
            return UINT8_FIELD;
        case 59: //ambient.rise.green
            return UINT8_FIELD;
        case 60: //ambient.rise.blue
            return UINT8_FIELD;
        case 61: //ambient.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 62: //ambient.day.red
            return UINT8_FIELD;
        case 63: //ambient.day.green
            return UINT8_FIELD;
        case 64: //ambient.day.blue
            return UINT8_FIELD;
        case 65: //ambient.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 66: //ambient.set.red
            return UINT8_FIELD;
        case 67: //ambient.set.green
            return UINT8_FIELD;
        case 68: //ambient.set.blue
            return UINT8_FIELD;
        case 69: //ambient.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 70: //ambient.night.red
            return UINT8_FIELD;
        case 71: //ambient.night.green
            return UINT8_FIELD;
        case 72: //ambient.night.blue
            return UINT8_FIELD;
        case 73: //ambient.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 74: //sunlight.rise.red
            return UINT8_FIELD;
        case 75: //sunlight.rise.green
            return UINT8_FIELD;
        case 76: //sunlight.rise.blue
            return UINT8_FIELD;
        case 77: //sunlight.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 78: //sunlight.day.red
            return UINT8_FIELD;
        case 79: //sunlight.day.green
            return UINT8_FIELD;
        case 80: //sunlight.day.blue
            return UINT8_FIELD;
        case 81: //sunlight.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 82: //sunlight.set.red
            return UINT8_FIELD;
        case 83: //sunlight.set.green
            return UINT8_FIELD;
        case 84: //sunlight.set.blue
            return UINT8_FIELD;
        case 85: //sunlight.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 86: //sunlight.night.red
            return UINT8_FIELD;
        case 87: //sunlight.night.green
            return UINT8_FIELD;
        case 88: //sunlight.night.blue
            return UINT8_FIELD;
        case 89: //sunlight.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 90: //sun.rise.red
            return UINT8_FIELD;
        case 91: //sun.rise.green
            return UINT8_FIELD;
        case 92: //sun.rise.blue
            return UINT8_FIELD;
        case 93: //sun.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 94: //sun.day.red
            return UINT8_FIELD;
        case 95: //sun.day.green
            return UINT8_FIELD;
        case 96: //sun.day.blue
            return UINT8_FIELD;
        case 97: //sun.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 98: //sun.set.red
            return UINT8_FIELD;
        case 99: //sun.set.green
            return UINT8_FIELD;
        case 100: //sun.set.blue
            return UINT8_FIELD;
        case 101: //sun.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 102: //sun.night.red
            return UINT8_FIELD;
        case 103: //sun.night.green
            return UINT8_FIELD;
        case 104: //sun.night.blue
            return UINT8_FIELD;
        case 105: //sun.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 106: //stars.rise.red
            return UINT8_FIELD;
        case 107: //stars.rise.green
            return UINT8_FIELD;
        case 108: //stars.rise.blue
            return UINT8_FIELD;
        case 109: //stars.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 110: //stars.day.red
            return UINT8_FIELD;
        case 111: //stars.day.green
            return UINT8_FIELD;
        case 112: //stars.day.blue
            return UINT8_FIELD;
        case 113: //stars.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 114: //stars.set.red
            return UINT8_FIELD;
        case 115: //stars.set.green
            return UINT8_FIELD;
        case 116: //stars.set.blue
            return UINT8_FIELD;
        case 117: //stars.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 118: //stars.night.red
            return UINT8_FIELD;
        case 119: //stars.night.green
            return UINT8_FIELD;
        case 120: //stars.night.blue
            return UINT8_FIELD;
        case 121: //stars.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 122: //lowerSky.rise.red
            return UINT8_FIELD;
        case 123: //lowerSky.rise.green
            return UINT8_FIELD;
        case 124: //lowerSky.rise.blue
            return UINT8_FIELD;
        case 125: //lowerSky.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 126: //lowerSky.day.red
            return UINT8_FIELD;
        case 127: //lowerSky.day.green
            return UINT8_FIELD;
        case 128: //lowerSky.day.blue
            return UINT8_FIELD;
        case 129: //lowerSky.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 130: //lowerSky.set.red
            return UINT8_FIELD;
        case 131: //lowerSky.set.green
            return UINT8_FIELD;
        case 132: //lowerSky.set.blue
            return UINT8_FIELD;
        case 133: //lowerSky.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 134: //lowerSky.night.red
            return UINT8_FIELD;
        case 135: //lowerSky.night.green
            return UINT8_FIELD;
        case 136: //lowerSky.night.blue
            return UINT8_FIELD;
        case 137: //lowerSky.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 138: //horizon.rise.red
            return UINT8_FIELD;
        case 139: //horizon.rise.green
            return UINT8_FIELD;
        case 140: //horizon.rise.blue
            return UINT8_FIELD;
        case 141: //horizon.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 142: //horizon.day.red
            return UINT8_FIELD;
        case 143: //horizon.day.green
            return UINT8_FIELD;
        case 144: //horizon.day.blue
            return UINT8_FIELD;
        case 145: //horizon.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 146: //horizon.set.red
            return UINT8_FIELD;
        case 147: //horizon.set.green
            return UINT8_FIELD;
        case 148: //horizon.set.blue
            return UINT8_FIELD;
        case 149: //horizon.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 150: //horizon.night.red
            return UINT8_FIELD;
        case 151: //horizon.night.green
            return UINT8_FIELD;
        case 152: //horizon.night.blue
            return UINT8_FIELD;
        case 153: //horizon.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 154: //upperClouds.rise.red
            return UINT8_FIELD;
        case 155: //upperClouds.rise.green
            return UINT8_FIELD;
        case 156: //upperClouds.rise.blue
            return UINT8_FIELD;
        case 157: //upperClouds.rise.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 158: //upperClouds.day.red
            return UINT8_FIELD;
        case 159: //upperClouds.day.green
            return UINT8_FIELD;
        case 160: //upperClouds.day.blue
            return UINT8_FIELD;
        case 161: //upperClouds.day.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 162: //upperClouds.set.red
            return UINT8_FIELD;
        case 163: //upperClouds.set.green
            return UINT8_FIELD;
        case 164: //upperClouds.set.blue
            return UINT8_FIELD;
        case 165: //upperClouds.set.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 166: //upperClouds.night.red
            return UINT8_FIELD;
        case 167: //upperClouds.night.green
            return UINT8_FIELD;
        case 168: //upperClouds.night.blue
            return UINT8_FIELD;
        case 169: //upperClouds.night.unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 1;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 170: //fogDayNear
            return FLOAT32_FIELD;
        case 171: //fogDayFar
            return FLOAT32_FIELD;
        case 172: //fogNightNear
            return FLOAT32_FIELD;
        case 173: //fogNightFar
            return FLOAT32_FIELD;
        case 174: //eyeAdaptSpeed
            return FLOAT32_FIELD;
        case 175: //blurRadius
            return FLOAT32_FIELD;
        case 176: //blurPasses
            return FLOAT32_FIELD;
        case 177: //emissiveMult
            return FLOAT32_FIELD;
        case 178: //targetLum
            return FLOAT32_FIELD;
        case 179: //upperLumClamp
            return FLOAT32_FIELD;
        case 180: //brightScale
            return FLOAT32_FIELD;
        case 181: //brightClamp
            return FLOAT32_FIELD;
        case 182: //lumRampNoTex
            return FLOAT32_FIELD;
        case 183: //lumRampMin
            return FLOAT32_FIELD;
        case 184: //lumRampMax
            return FLOAT32_FIELD;
        case 185: //sunlightDimmer
            return FLOAT32_FIELD;
        case 186: //grassDimmer
            return FLOAT32_FIELD;
        case 187: //treeDimmer
            return FLOAT32_FIELD;
        case 188: //windSpeed
            return UINT8_FIELD;
        case 189: //lowerCloudSpeed
            return UINT8_FIELD;
        case 190: //upperCloudSpeed
            return UINT8_FIELD;
        case 191: //transDelta
            return UINT8_FIELD;
        case 192: //sunGlare
            return UINT8_FIELD;
        case 193: //sunDamage
            return UINT8_FIELD;
        case 194: //rainFadeIn
            return UINT8_FIELD;
        case 195: //rainFadeOut
            return UINT8_FIELD;
        case 196: //boltFadeIn
            return UINT8_FIELD;
        case 197: //boltFadeOut
            return UINT8_FIELD;
        case 198: //boltFrequency
            return UINT8_FIELD;
        case 199: //weatherType
            return UINT8_TYPE_FIELD;
        case 200: //boltRed
            return UINT8_FIELD;
        case 201: //boltGreen
            return UINT8_FIELD;
        case 202: //boltBlue
            return UINT8_FIELD;
        case 203: //sounds
            if(ListFieldID == 0) //sounds
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return (UINT32)Sounds.value.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Sounds.value.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //sound
                    return FORMID_FIELD;
                case 2: //type
                    return UINT32_TYPE_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * WTHRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //lowerLayerPath
            return CNAM.value;
        case 6: //upperLayerPath
            return DNAM.value;
        case 7: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 8: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 9: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 10: //upperSky.rise.red
            return &NAM0.value.upperSky.rise.red;
        case 11: //upperSky.rise.green
            return &NAM0.value.upperSky.rise.green;
        case 12: //upperSky.rise.blue
            return &NAM0.value.upperSky.rise.blue;
        case 13: //upperSky.rise.unused1
            *FieldValues = &NAM0.value.upperSky.rise.unused1;
            return NULL;
        case 14: //upperSky.day.red
            return &NAM0.value.upperSky.day.red;
        case 15: //upperSky.day.green
            return &NAM0.value.upperSky.day.green;
        case 16: //upperSky.day.blue
            return &NAM0.value.upperSky.day.blue;
        case 17: //upperSky.day.unused1
            *FieldValues = &NAM0.value.upperSky.day.unused1;
            return NULL;
        case 18: //upperSky.set.red
            return &NAM0.value.upperSky.set.red;
        case 19: //upperSky.set.green
            return &NAM0.value.upperSky.set.green;
        case 20: //upperSky.set.blue
            return &NAM0.value.upperSky.set.blue;
        case 21: //upperSky.set.unused1
            *FieldValues = &NAM0.value.upperSky.set.unused1;
            return NULL;
        case 22: //upperSky.night.red
            return &NAM0.value.upperSky.night.red;
        case 23: //upperSky.night.green
            return &NAM0.value.upperSky.night.green;
        case 24: //upperSky.night.blue
            return &NAM0.value.upperSky.night.blue;
        case 25: //upperSky.night.unused1
            *FieldValues = &NAM0.value.upperSky.night.unused1;
            return NULL;
        case 26: //fog.rise.red
            return &NAM0.value.fog.rise.red;
        case 27: //fog.rise.green
            return &NAM0.value.fog.rise.green;
        case 28: //fog.rise.blue
            return &NAM0.value.fog.rise.blue;
        case 29: //fog.rise.unused1
            *FieldValues = &NAM0.value.fog.rise.unused1;
            return NULL;
        case 30: //fog.day.red
            return &NAM0.value.fog.day.red;
        case 31: //fog.day.green
            return &NAM0.value.fog.day.green;
        case 32: //fog.day.blue
            return &NAM0.value.fog.day.blue;
        case 33: //fog.day.unused1
            *FieldValues = &NAM0.value.fog.day.unused1;
            return NULL;
        case 34: //fog.set.red
            return &NAM0.value.fog.set.red;
        case 35: //fog.set.green
            return &NAM0.value.fog.set.green;
        case 36: //fog.set.blue
            return &NAM0.value.fog.set.blue;
        case 37: //fog.set.unused1
            *FieldValues = &NAM0.value.fog.set.unused1;
            return NULL;
        case 38: //fog.night.red
            return &NAM0.value.fog.night.red;
        case 39: //fog.night.green
            return &NAM0.value.fog.night.green;
        case 40: //fog.night.blue
            return &NAM0.value.fog.night.blue;
        case 41: //fog.night.unused1
            *FieldValues = &NAM0.value.fog.night.unused1;
            return NULL;
        case 42: //lowerClouds.rise.red
            return &NAM0.value.lowerClouds.rise.red;
        case 43: //lowerClouds.rise.green
            return &NAM0.value.lowerClouds.rise.green;
        case 44: //lowerClouds.rise.blue
            return &NAM0.value.lowerClouds.rise.blue;
        case 45: //lowerClouds.rise.unused1
            *FieldValues = &NAM0.value.lowerClouds.rise.unused1;
            return NULL;
        case 46: //lowerClouds.day.red
            return &NAM0.value.lowerClouds.day.red;
        case 47: //lowerClouds.day.green
            return &NAM0.value.lowerClouds.day.green;
        case 48: //lowerClouds.day.blue
            return &NAM0.value.lowerClouds.day.blue;
        case 49: //lowerClouds.day.unused1
            *FieldValues = &NAM0.value.lowerClouds.day.unused1;
            return NULL;
        case 50: //lowerClouds.set.red
            return &NAM0.value.lowerClouds.set.red;
        case 51: //lowerClouds.set.green
            return &NAM0.value.lowerClouds.set.green;
        case 52: //lowerClouds.set.blue
            return &NAM0.value.lowerClouds.set.blue;
        case 53: //lowerClouds.set.unused1
            *FieldValues = &NAM0.value.lowerClouds.set.unused1;
            return NULL;
        case 54: //lowerClouds.night.red
            return &NAM0.value.lowerClouds.night.red;
        case 55: //lowerClouds.night.green
            return &NAM0.value.lowerClouds.night.green;
        case 56: //lowerClouds.night.blue
            return &NAM0.value.lowerClouds.night.blue;
        case 57: //lowerClouds.night.unused1
            *FieldValues = &NAM0.value.lowerClouds.night.unused1;
            return NULL;
        case 58: //ambient.rise.red
            return &NAM0.value.ambient.rise.red;
        case 59: //ambient.rise.green
            return &NAM0.value.ambient.rise.green;
        case 60: //ambient.rise.blue
            return &NAM0.value.ambient.rise.blue;
        case 61: //ambient.rise.unused1
            *FieldValues = &NAM0.value.ambient.rise.unused1;
            return NULL;
        case 62: //ambient.day.red
            return &NAM0.value.ambient.day.red;
        case 63: //ambient.day.green
            return &NAM0.value.ambient.day.green;
        case 64: //ambient.day.blue
            return &NAM0.value.ambient.day.blue;
        case 65: //ambient.day.unused1
            *FieldValues = &NAM0.value.ambient.day.unused1;
            return NULL;
        case 66: //ambient.set.red
            return &NAM0.value.ambient.set.red;
        case 67: //ambient.set.green
            return &NAM0.value.ambient.set.green;
        case 68: //ambient.set.blue
            return &NAM0.value.ambient.set.blue;
        case 69: //ambient.set.unused1
            *FieldValues = &NAM0.value.ambient.set.unused1;
            return NULL;
        case 70: //ambient.night.red
            return &NAM0.value.ambient.night.red;
        case 71: //ambient.night.green
            return &NAM0.value.ambient.night.green;
        case 72: //ambient.night.blue
            return &NAM0.value.ambient.night.blue;
        case 73: //ambient.night.unused1
            *FieldValues = &NAM0.value.ambient.night.unused1;
            return NULL;
        case 74: //sunlight.rise.red
            return &NAM0.value.sunlight.rise.red;
        case 75: //sunlight.rise.green
            return &NAM0.value.sunlight.rise.green;
        case 76: //sunlight.rise.blue
            return &NAM0.value.sunlight.rise.blue;
        case 77: //sunlight.rise.unused1
            *FieldValues = &NAM0.value.sunlight.rise.unused1;
            return NULL;
        case 78: //sunlight.day.red
            return &NAM0.value.sunlight.day.red;
        case 79: //sunlight.day.green
            return &NAM0.value.sunlight.day.green;
        case 80: //sunlight.day.blue
            return &NAM0.value.sunlight.day.blue;
        case 81: //sunlight.day.unused1
            *FieldValues = &NAM0.value.sunlight.day.unused1;
            return NULL;
        case 82: //sunlight.set.red
            return &NAM0.value.sunlight.set.red;
        case 83: //sunlight.set.green
            return &NAM0.value.sunlight.set.green;
        case 84: //sunlight.set.blue
            return &NAM0.value.sunlight.set.blue;
        case 85: //sunlight.set.unused1
            *FieldValues = &NAM0.value.sunlight.set.unused1;
            return NULL;
        case 86: //sunlight.night.red
            return &NAM0.value.sunlight.night.red;
        case 87: //sunlight.night.green
            return &NAM0.value.sunlight.night.green;
        case 88: //sunlight.night.blue
            return &NAM0.value.sunlight.night.blue;
        case 89: //sunlight.night.unused1
            *FieldValues = &NAM0.value.sunlight.night.unused1;
            return NULL;
        case 90: //sun.rise.red
            return &NAM0.value.sun.rise.red;
        case 91: //sun.rise.green
            return &NAM0.value.sun.rise.green;
        case 92: //sun.rise.blue
            return &NAM0.value.sun.rise.blue;
        case 93: //sun.rise.unused1
            *FieldValues = &NAM0.value.sun.rise.unused1;
            return NULL;
        case 94: //sun.day.red
            return &NAM0.value.sun.day.red;
        case 95: //sun.day.green
            return &NAM0.value.sun.day.green;
        case 96: //sun.day.blue
            return &NAM0.value.sun.day.blue;
        case 97: //sun.day.unused1
            *FieldValues = &NAM0.value.sun.day.unused1;
            return NULL;
        case 98: //sun.set.red
            return &NAM0.value.sun.set.red;
        case 99: //sun.set.green
            return &NAM0.value.sun.set.green;
        case 100: //sun.set.blue
            return &NAM0.value.sun.set.blue;
        case 101: //sun.set.unused1
            *FieldValues = &NAM0.value.sun.set.unused1;
            return NULL;
        case 102: //sun.night.red
            return &NAM0.value.sun.night.red;
        case 103: //sun.night.green
            return &NAM0.value.sun.night.green;
        case 104: //sun.night.blue
            return &NAM0.value.sun.night.blue;
        case 105: //sun.night.unused1
            *FieldValues = &NAM0.value.sun.night.unused1;
            return NULL;
        case 106: //stars.rise.red
            return &NAM0.value.stars.rise.red;
        case 107: //stars.rise.green
            return &NAM0.value.stars.rise.green;
        case 108: //stars.rise.blue
            return &NAM0.value.stars.rise.blue;
        case 109: //stars.rise.unused1
            *FieldValues = &NAM0.value.stars.rise.unused1;
            return NULL;
        case 110: //stars.day.red
            return &NAM0.value.stars.day.red;
        case 111: //stars.day.green
            return &NAM0.value.stars.day.green;
        case 112: //stars.day.blue
            return &NAM0.value.stars.day.blue;
        case 113: //stars.day.unused1
            *FieldValues = &NAM0.value.stars.day.unused1;
            return NULL;
        case 114: //stars.set.red
            return &NAM0.value.stars.set.red;
        case 115: //stars.set.green
            return &NAM0.value.stars.set.green;
        case 116: //stars.set.blue
            return &NAM0.value.stars.set.blue;
        case 117: //stars.set.unused1
            *FieldValues = &NAM0.value.stars.set.unused1;
            return NULL;
        case 118: //stars.night.red
            return &NAM0.value.stars.night.red;
        case 119: //stars.night.green
            return &NAM0.value.stars.night.green;
        case 120: //stars.night.blue
            return &NAM0.value.stars.night.blue;
        case 121: //stars.night.unused1
            *FieldValues = &NAM0.value.stars.night.unused1;
            return NULL;
        case 122: //lowerSky.rise.red
            return &NAM0.value.lowerSky.rise.red;
        case 123: //lowerSky.rise.green
            return &NAM0.value.lowerSky.rise.green;
        case 124: //lowerSky.rise.blue
            return &NAM0.value.lowerSky.rise.blue;
        case 125: //lowerSky.rise.unused1
            *FieldValues = &NAM0.value.lowerSky.rise.unused1;
            return NULL;
        case 126: //lowerSky.day.red
            return &NAM0.value.lowerSky.day.red;
        case 127: //lowerSky.day.green
            return &NAM0.value.lowerSky.day.green;
        case 128: //lowerSky.day.blue
            return &NAM0.value.lowerSky.day.blue;
        case 129: //lowerSky.day.unused1
            *FieldValues = &NAM0.value.lowerSky.day.unused1;
            return NULL;
        case 130: //lowerSky.set.red
            return &NAM0.value.lowerSky.set.red;
        case 131: //lowerSky.set.green
            return &NAM0.value.lowerSky.set.green;
        case 132: //lowerSky.set.blue
            return &NAM0.value.lowerSky.set.blue;
        case 133: //lowerSky.set.unused1
            *FieldValues = &NAM0.value.lowerSky.set.unused1;
            return NULL;
        case 134: //lowerSky.night.red
            return &NAM0.value.lowerSky.night.red;
        case 135: //lowerSky.night.green
            return &NAM0.value.lowerSky.night.green;
        case 136: //lowerSky.night.blue
            return &NAM0.value.lowerSky.night.blue;
        case 137: //lowerSky.night.unused1
            *FieldValues = &NAM0.value.lowerSky.night.unused1;
            return NULL;
        case 138: //horizon.rise.red
            return &NAM0.value.horizon.rise.red;
        case 139: //horizon.rise.green
            return &NAM0.value.horizon.rise.green;
        case 140: //horizon.rise.blue
            return &NAM0.value.horizon.rise.blue;
        case 141: //horizon.rise.unused1
            *FieldValues = &NAM0.value.horizon.rise.unused1;
            return NULL;
        case 142: //horizon.day.red
            return &NAM0.value.horizon.day.red;
        case 143: //horizon.day.green
            return &NAM0.value.horizon.day.green;
        case 144: //horizon.day.blue
            return &NAM0.value.horizon.day.blue;
        case 145: //horizon.day.unused1
            *FieldValues = &NAM0.value.horizon.day.unused1;
            return NULL;
        case 146: //horizon.set.red
            return &NAM0.value.horizon.set.red;
        case 147: //horizon.set.green
            return &NAM0.value.horizon.set.green;
        case 148: //horizon.set.blue
            return &NAM0.value.horizon.set.blue;
        case 149: //horizon.set.unused1
            *FieldValues = &NAM0.value.horizon.set.unused1;
            return NULL;
        case 150: //horizon.night.red
            return &NAM0.value.horizon.night.red;
        case 151: //horizon.night.green
            return &NAM0.value.horizon.night.green;
        case 152: //horizon.night.blue
            return &NAM0.value.horizon.night.blue;
        case 153: //horizon.night.unused1
            *FieldValues = &NAM0.value.horizon.night.unused1;
            return NULL;
        case 154: //upperClouds.rise.red
            return &NAM0.value.upperClouds.rise.red;
        case 155: //upperClouds.rise.green
            return &NAM0.value.upperClouds.rise.green;
        case 156: //upperClouds.rise.blue
            return &NAM0.value.upperClouds.rise.blue;
        case 157: //upperClouds.rise.unused1
            *FieldValues = &NAM0.value.upperClouds.rise.unused1;
            return NULL;
        case 158: //upperClouds.day.red
            return &NAM0.value.upperClouds.day.red;
        case 159: //upperClouds.day.green
            return &NAM0.value.upperClouds.day.green;
        case 160: //upperClouds.day.blue
            return &NAM0.value.upperClouds.day.blue;
        case 161: //upperClouds.day.unused1
            *FieldValues = &NAM0.value.upperClouds.day.unused1;
            return NULL;
        case 162: //upperClouds.set.red
            return &NAM0.value.upperClouds.set.red;
        case 163: //upperClouds.set.green
            return &NAM0.value.upperClouds.set.green;
        case 164: //upperClouds.set.blue
            return &NAM0.value.upperClouds.set.blue;
        case 165: //upperClouds.set.unused1
            *FieldValues = &NAM0.value.upperClouds.set.unused1;
            return NULL;
        case 166: //upperClouds.night.red
            return &NAM0.value.upperClouds.night.red;
        case 167: //upperClouds.night.green
            return &NAM0.value.upperClouds.night.green;
        case 168: //upperClouds.night.blue
            return &NAM0.value.upperClouds.night.blue;
        case 169: //upperClouds.night.unused1
            *FieldValues = &NAM0.value.upperClouds.night.unused1;
            return NULL;
        case 170: //fogDayNear
            return &FNAM.value.fogDayNear;
        case 171: //fogDayFar
            return &FNAM.value.fogDayFar;
        case 172: //fogNightNear
            return &FNAM.value.fogNightNear;
        case 173: //fogNightFar
            return &FNAM.value.fogNightFar;
        case 174: //eyeAdaptSpeed
            return &HNAM.value.eyeAdaptSpeed;
        case 175: //blurRadius
            return &HNAM.value.blurRadius;
        case 176: //blurPasses
            return &HNAM.value.blurPasses;
        case 177: //emissiveMult
            return &HNAM.value.emissiveMult;
        case 178: //targetLum
            return &HNAM.value.targetLum;
        case 179: //upperLumClamp
            return &HNAM.value.upperLumClamp;
        case 180: //brightScale
            return &HNAM.value.brightScale;
        case 181: //brightClamp
            return &HNAM.value.brightClamp;
        case 182: //lumRampNoTex
            return &HNAM.value.lumRampNoTex;
        case 183: //lumRampMin
            return &HNAM.value.lumRampMin;
        case 184: //lumRampMax
            return &HNAM.value.lumRampMax;
        case 185: //sunlightDimmer
            return &HNAM.value.sunlightDimmer;
        case 186: //grassDimmer
            return &HNAM.value.grassDimmer;
        case 187: //treeDimmer
            return &HNAM.value.treeDimmer;
        case 188: //windSpeed
            return &DATA.value.windSpeed;
        case 189: //lowerCloudSpeed
            return &DATA.value.lowerCloudSpeed;
        case 190: //upperCloudSpeed
            return &DATA.value.upperCloudSpeed;
        case 191: //transDelta
            return &DATA.value.transDelta;
        case 192: //sunGlare
            return &DATA.value.sunGlare;
        case 193: //sunDamage
            return &DATA.value.sunDamage;
        case 194: //rainFadeIn
            return &DATA.value.rainFadeIn;
        case 195: //rainFadeOut
            return &DATA.value.rainFadeOut;
        case 196: //boltFadeIn
            return &DATA.value.boltFadeIn;
        case 197: //boltFadeOut
            return &DATA.value.boltFadeOut;
        case 198: //boltFrequency
            return &DATA.value.boltFrequency;
        case 199: //weatherType
            return &DATA.value.weatherType;
        case 200: //boltRed
            return &DATA.value.boltRed;
        case 201: //boltGreen
            return &DATA.value.boltGreen;
        case 202: //boltBlue
            return &DATA.value.boltBlue;
        case 203: //sounds
            if(ListIndex >= Sounds.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //sound
                    return &Sounds.value[ListIndex]->sound;
                case 2: //type
                    return &Sounds.value[ListIndex]->type;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool WTHRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //lowerLayerPath
            CNAM.Copy((STRING)FieldValue);
            break;
        case 6: //upperLayerPath
            DNAM.Copy((STRING)FieldValue);
            break;
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 8: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //upperSky.rise.red
            NAM0.value.upperSky.rise.red = *(UINT8 *)FieldValue;
            break;
        case 11: //upperSky.rise.green
            NAM0.value.upperSky.rise.green = *(UINT8 *)FieldValue;
            break;
        case 12: //upperSky.rise.blue
            NAM0.value.upperSky.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 13: //upperSky.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 14: //upperSky.day.red
            NAM0.value.upperSky.day.red = *(UINT8 *)FieldValue;
            break;
        case 15: //upperSky.day.green
            NAM0.value.upperSky.day.green = *(UINT8 *)FieldValue;
            break;
        case 16: //upperSky.day.blue
            NAM0.value.upperSky.day.blue = *(UINT8 *)FieldValue;
            break;
        case 17: //upperSky.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 18: //upperSky.set.red
            NAM0.value.upperSky.set.red = *(UINT8 *)FieldValue;
            break;
        case 19: //upperSky.set.green
            NAM0.value.upperSky.set.green = *(UINT8 *)FieldValue;
            break;
        case 20: //upperSky.set.blue
            NAM0.value.upperSky.set.blue = *(UINT8 *)FieldValue;
            break;
        case 21: //upperSky.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 22: //upperSky.night.red
            NAM0.value.upperSky.night.red = *(UINT8 *)FieldValue;
            break;
        case 23: //upperSky.night.green
            NAM0.value.upperSky.night.green = *(UINT8 *)FieldValue;
            break;
        case 24: //upperSky.night.blue
            NAM0.value.upperSky.night.blue = *(UINT8 *)FieldValue;
            break;
        case 25: //upperSky.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 26: //fog.rise.red
            NAM0.value.fog.rise.red = *(UINT8 *)FieldValue;
            break;
        case 27: //fog.rise.green
            NAM0.value.fog.rise.green = *(UINT8 *)FieldValue;
            break;
        case 28: //fog.rise.blue
            NAM0.value.fog.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 29: //fog.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 30: //fog.day.red
            NAM0.value.fog.day.red = *(UINT8 *)FieldValue;
            break;
        case 31: //fog.day.green
            NAM0.value.fog.day.green = *(UINT8 *)FieldValue;
            break;
        case 32: //fog.day.blue
            NAM0.value.fog.day.blue = *(UINT8 *)FieldValue;
            break;
        case 33: //fog.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 34: //fog.set.red
            NAM0.value.fog.set.red = *(UINT8 *)FieldValue;
            break;
        case 35: //fog.set.green
            NAM0.value.fog.set.green = *(UINT8 *)FieldValue;
            break;
        case 36: //fog.set.blue
            NAM0.value.fog.set.blue = *(UINT8 *)FieldValue;
            break;
        case 37: //fog.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 38: //fog.night.red
            NAM0.value.fog.night.red = *(UINT8 *)FieldValue;
            break;
        case 39: //fog.night.green
            NAM0.value.fog.night.green = *(UINT8 *)FieldValue;
            break;
        case 40: //fog.night.blue
            NAM0.value.fog.night.blue = *(UINT8 *)FieldValue;
            break;
        case 41: //fog.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 42: //lowerClouds.rise.red
            NAM0.value.lowerClouds.rise.red = *(UINT8 *)FieldValue;
            break;
        case 43: //lowerClouds.rise.green
            NAM0.value.lowerClouds.rise.green = *(UINT8 *)FieldValue;
            break;
        case 44: //lowerClouds.rise.blue
            NAM0.value.lowerClouds.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 45: //lowerClouds.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 46: //lowerClouds.day.red
            NAM0.value.lowerClouds.day.red = *(UINT8 *)FieldValue;
            break;
        case 47: //lowerClouds.day.green
            NAM0.value.lowerClouds.day.green = *(UINT8 *)FieldValue;
            break;
        case 48: //lowerClouds.day.blue
            NAM0.value.lowerClouds.day.blue = *(UINT8 *)FieldValue;
            break;
        case 49: //lowerClouds.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 50: //lowerClouds.set.red
            NAM0.value.lowerClouds.set.red = *(UINT8 *)FieldValue;
            break;
        case 51: //lowerClouds.set.green
            NAM0.value.lowerClouds.set.green = *(UINT8 *)FieldValue;
            break;
        case 52: //lowerClouds.set.blue
            NAM0.value.lowerClouds.set.blue = *(UINT8 *)FieldValue;
            break;
        case 53: //lowerClouds.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 54: //lowerClouds.night.red
            NAM0.value.lowerClouds.night.red = *(UINT8 *)FieldValue;
            break;
        case 55: //lowerClouds.night.green
            NAM0.value.lowerClouds.night.green = *(UINT8 *)FieldValue;
            break;
        case 56: //lowerClouds.night.blue
            NAM0.value.lowerClouds.night.blue = *(UINT8 *)FieldValue;
            break;
        case 57: //lowerClouds.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 58: //ambient.rise.red
            NAM0.value.ambient.rise.red = *(UINT8 *)FieldValue;
            break;
        case 59: //ambient.rise.green
            NAM0.value.ambient.rise.green = *(UINT8 *)FieldValue;
            break;
        case 60: //ambient.rise.blue
            NAM0.value.ambient.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 61: //ambient.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 62: //ambient.day.red
            NAM0.value.ambient.day.red = *(UINT8 *)FieldValue;
            break;
        case 63: //ambient.day.green
            NAM0.value.ambient.day.green = *(UINT8 *)FieldValue;
            break;
        case 64: //ambient.day.blue
            NAM0.value.ambient.day.blue = *(UINT8 *)FieldValue;
            break;
        case 65: //ambient.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 66: //ambient.set.red
            NAM0.value.ambient.set.red = *(UINT8 *)FieldValue;
            break;
        case 67: //ambient.set.green
            NAM0.value.ambient.set.green = *(UINT8 *)FieldValue;
            break;
        case 68: //ambient.set.blue
            NAM0.value.ambient.set.blue = *(UINT8 *)FieldValue;
            break;
        case 69: //ambient.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 70: //ambient.night.red
            NAM0.value.ambient.night.red = *(UINT8 *)FieldValue;
            break;
        case 71: //ambient.night.green
            NAM0.value.ambient.night.green = *(UINT8 *)FieldValue;
            break;
        case 72: //ambient.night.blue
            NAM0.value.ambient.night.blue = *(UINT8 *)FieldValue;
            break;
        case 73: //ambient.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 74: //sunlight.rise.red
            NAM0.value.sunlight.rise.red = *(UINT8 *)FieldValue;
            break;
        case 75: //sunlight.rise.green
            NAM0.value.sunlight.rise.green = *(UINT8 *)FieldValue;
            break;
        case 76: //sunlight.rise.blue
            NAM0.value.sunlight.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 77: //sunlight.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 78: //sunlight.day.red
            NAM0.value.sunlight.day.red = *(UINT8 *)FieldValue;
            break;
        case 79: //sunlight.day.green
            NAM0.value.sunlight.day.green = *(UINT8 *)FieldValue;
            break;
        case 80: //sunlight.day.blue
            NAM0.value.sunlight.day.blue = *(UINT8 *)FieldValue;
            break;
        case 81: //sunlight.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 82: //sunlight.set.red
            NAM0.value.sunlight.set.red = *(UINT8 *)FieldValue;
            break;
        case 83: //sunlight.set.green
            NAM0.value.sunlight.set.green = *(UINT8 *)FieldValue;
            break;
        case 84: //sunlight.set.blue
            NAM0.value.sunlight.set.blue = *(UINT8 *)FieldValue;
            break;
        case 85: //sunlight.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 86: //sunlight.night.red
            NAM0.value.sunlight.night.red = *(UINT8 *)FieldValue;
            break;
        case 87: //sunlight.night.green
            NAM0.value.sunlight.night.green = *(UINT8 *)FieldValue;
            break;
        case 88: //sunlight.night.blue
            NAM0.value.sunlight.night.blue = *(UINT8 *)FieldValue;
            break;
        case 89: //sunlight.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 90: //sun.rise.red
            NAM0.value.sun.rise.red = *(UINT8 *)FieldValue;
            break;
        case 91: //sun.rise.green
            NAM0.value.sun.rise.green = *(UINT8 *)FieldValue;
            break;
        case 92: //sun.rise.blue
            NAM0.value.sun.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 93: //sun.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 94: //sun.day.red
            NAM0.value.sun.day.red = *(UINT8 *)FieldValue;
            break;
        case 95: //sun.day.green
            NAM0.value.sun.day.green = *(UINT8 *)FieldValue;
            break;
        case 96: //sun.day.blue
            NAM0.value.sun.day.blue = *(UINT8 *)FieldValue;
            break;
        case 97: //sun.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 98: //sun.set.red
            NAM0.value.sun.set.red = *(UINT8 *)FieldValue;
            break;
        case 99: //sun.set.green
            NAM0.value.sun.set.green = *(UINT8 *)FieldValue;
            break;
        case 100: //sun.set.blue
            NAM0.value.sun.set.blue = *(UINT8 *)FieldValue;
            break;
        case 101: //sun.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 102: //sun.night.red
            NAM0.value.sun.night.red = *(UINT8 *)FieldValue;
            break;
        case 103: //sun.night.green
            NAM0.value.sun.night.green = *(UINT8 *)FieldValue;
            break;
        case 104: //sun.night.blue
            NAM0.value.sun.night.blue = *(UINT8 *)FieldValue;
            break;
        case 105: //sun.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 106: //stars.rise.red
            NAM0.value.stars.rise.red = *(UINT8 *)FieldValue;
            break;
        case 107: //stars.rise.green
            NAM0.value.stars.rise.green = *(UINT8 *)FieldValue;
            break;
        case 108: //stars.rise.blue
            NAM0.value.stars.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 109: //stars.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 110: //stars.day.red
            NAM0.value.stars.day.red = *(UINT8 *)FieldValue;
            break;
        case 111: //stars.day.green
            NAM0.value.stars.day.green = *(UINT8 *)FieldValue;
            break;
        case 112: //stars.day.blue
            NAM0.value.stars.day.blue = *(UINT8 *)FieldValue;
            break;
        case 113: //stars.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 114: //stars.set.red
            NAM0.value.stars.set.red = *(UINT8 *)FieldValue;
            break;
        case 115: //stars.set.green
            NAM0.value.stars.set.green = *(UINT8 *)FieldValue;
            break;
        case 116: //stars.set.blue
            NAM0.value.stars.set.blue = *(UINT8 *)FieldValue;
            break;
        case 117: //stars.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 118: //stars.night.red
            NAM0.value.stars.night.red = *(UINT8 *)FieldValue;
            break;
        case 119: //stars.night.green
            NAM0.value.stars.night.green = *(UINT8 *)FieldValue;
            break;
        case 120: //stars.night.blue
            NAM0.value.stars.night.blue = *(UINT8 *)FieldValue;
            break;
        case 121: //stars.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 122: //lowerSky.rise.red
            NAM0.value.lowerSky.rise.red = *(UINT8 *)FieldValue;
            break;
        case 123: //lowerSky.rise.green
            NAM0.value.lowerSky.rise.green = *(UINT8 *)FieldValue;
            break;
        case 124: //lowerSky.rise.blue
            NAM0.value.lowerSky.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 125: //lowerSky.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 126: //lowerSky.day.red
            NAM0.value.lowerSky.day.red = *(UINT8 *)FieldValue;
            break;
        case 127: //lowerSky.day.green
            NAM0.value.lowerSky.day.green = *(UINT8 *)FieldValue;
            break;
        case 128: //lowerSky.day.blue
            NAM0.value.lowerSky.day.blue = *(UINT8 *)FieldValue;
            break;
        case 129: //lowerSky.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 130: //lowerSky.set.red
            NAM0.value.lowerSky.set.red = *(UINT8 *)FieldValue;
            break;
        case 131: //lowerSky.set.green
            NAM0.value.lowerSky.set.green = *(UINT8 *)FieldValue;
            break;
        case 132: //lowerSky.set.blue
            NAM0.value.lowerSky.set.blue = *(UINT8 *)FieldValue;
            break;
        case 133: //lowerSky.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 134: //lowerSky.night.red
            NAM0.value.lowerSky.night.red = *(UINT8 *)FieldValue;
            break;
        case 135: //lowerSky.night.green
            NAM0.value.lowerSky.night.green = *(UINT8 *)FieldValue;
            break;
        case 136: //lowerSky.night.blue
            NAM0.value.lowerSky.night.blue = *(UINT8 *)FieldValue;
            break;
        case 137: //lowerSky.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 138: //horizon.rise.red
            NAM0.value.horizon.rise.red = *(UINT8 *)FieldValue;
            break;
        case 139: //horizon.rise.green
            NAM0.value.horizon.rise.green = *(UINT8 *)FieldValue;
            break;
        case 140: //horizon.rise.blue
            NAM0.value.horizon.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 141: //horizon.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 142: //horizon.day.red
            NAM0.value.horizon.day.red = *(UINT8 *)FieldValue;
            break;
        case 143: //horizon.day.green
            NAM0.value.horizon.day.green = *(UINT8 *)FieldValue;
            break;
        case 144: //horizon.day.blue
            NAM0.value.horizon.day.blue = *(UINT8 *)FieldValue;
            break;
        case 145: //horizon.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 146: //horizon.set.red
            NAM0.value.horizon.set.red = *(UINT8 *)FieldValue;
            break;
        case 147: //horizon.set.green
            NAM0.value.horizon.set.green = *(UINT8 *)FieldValue;
            break;
        case 148: //horizon.set.blue
            NAM0.value.horizon.set.blue = *(UINT8 *)FieldValue;
            break;
        case 149: //horizon.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 150: //horizon.night.red
            NAM0.value.horizon.night.red = *(UINT8 *)FieldValue;
            break;
        case 151: //horizon.night.green
            NAM0.value.horizon.night.green = *(UINT8 *)FieldValue;
            break;
        case 152: //horizon.night.blue
            NAM0.value.horizon.night.blue = *(UINT8 *)FieldValue;
            break;
        case 153: //horizon.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 154: //upperClouds.rise.red
            NAM0.value.upperClouds.rise.red = *(UINT8 *)FieldValue;
            break;
        case 155: //upperClouds.rise.green
            NAM0.value.upperClouds.rise.green = *(UINT8 *)FieldValue;
            break;
        case 156: //upperClouds.rise.blue
            NAM0.value.upperClouds.rise.blue = *(UINT8 *)FieldValue;
            break;
        case 157: //upperClouds.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 158: //upperClouds.day.red
            NAM0.value.upperClouds.day.red = *(UINT8 *)FieldValue;
            break;
        case 159: //upperClouds.day.green
            NAM0.value.upperClouds.day.green = *(UINT8 *)FieldValue;
            break;
        case 160: //upperClouds.day.blue
            NAM0.value.upperClouds.day.blue = *(UINT8 *)FieldValue;
            break;
        case 161: //upperClouds.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 162: //upperClouds.set.red
            NAM0.value.upperClouds.set.red = *(UINT8 *)FieldValue;
            break;
        case 163: //upperClouds.set.green
            NAM0.value.upperClouds.set.green = *(UINT8 *)FieldValue;
            break;
        case 164: //upperClouds.set.blue
            NAM0.value.upperClouds.set.blue = *(UINT8 *)FieldValue;
            break;
        case 165: //upperClouds.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 166: //upperClouds.night.red
            NAM0.value.upperClouds.night.red = *(UINT8 *)FieldValue;
            break;
        case 167: //upperClouds.night.green
            NAM0.value.upperClouds.night.green = *(UINT8 *)FieldValue;
            break;
        case 168: //upperClouds.night.blue
            NAM0.value.upperClouds.night.blue = *(UINT8 *)FieldValue;
            break;
        case 169: //upperClouds.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 170: //fogDayNear
            FNAM.value.fogDayNear = *(FLOAT32 *)FieldValue;
            break;
        case 171: //fogDayFar
            FNAM.value.fogDayFar = *(FLOAT32 *)FieldValue;
            break;
        case 172: //fogNightNear
            FNAM.value.fogNightNear = *(FLOAT32 *)FieldValue;
            break;
        case 173: //fogNightFar
            FNAM.value.fogNightFar = *(FLOAT32 *)FieldValue;
            break;
        case 174: //eyeAdaptSpeed
            HNAM.value.eyeAdaptSpeed = *(FLOAT32 *)FieldValue;
            break;
        case 175: //blurRadius
            HNAM.value.blurRadius = *(FLOAT32 *)FieldValue;
            break;
        case 176: //blurPasses
            HNAM.value.blurPasses = *(FLOAT32 *)FieldValue;
            break;
        case 177: //emissiveMult
            HNAM.value.emissiveMult = *(FLOAT32 *)FieldValue;
            break;
        case 178: //targetLum
            HNAM.value.targetLum = *(FLOAT32 *)FieldValue;
            break;
        case 179: //upperLumClamp
            HNAM.value.upperLumClamp = *(FLOAT32 *)FieldValue;
            break;
        case 180: //brightScale
            HNAM.value.brightScale = *(FLOAT32 *)FieldValue;
            break;
        case 181: //brightClamp
            HNAM.value.brightClamp = *(FLOAT32 *)FieldValue;
            break;
        case 182: //lumRampNoTex
            HNAM.value.lumRampNoTex = *(FLOAT32 *)FieldValue;
            break;
        case 183: //lumRampMin
            HNAM.value.lumRampMin = *(FLOAT32 *)FieldValue;
            break;
        case 184: //lumRampMax
            HNAM.value.lumRampMax = *(FLOAT32 *)FieldValue;
            break;
        case 185: //sunlightDimmer
            HNAM.value.sunlightDimmer = *(FLOAT32 *)FieldValue;
            break;
        case 186: //grassDimmer
            HNAM.value.grassDimmer = *(FLOAT32 *)FieldValue;
            break;
        case 187: //treeDimmer
            HNAM.value.treeDimmer = *(FLOAT32 *)FieldValue;
            break;
        case 188: //windSpeed
            DATA.value.windSpeed = *(UINT8 *)FieldValue;
            break;
        case 189: //lowerCloudSpeed
            DATA.value.lowerCloudSpeed = *(UINT8 *)FieldValue;
            break;
        case 190: //upperCloudSpeed
            DATA.value.upperCloudSpeed = *(UINT8 *)FieldValue;
            break;
        case 191: //transDelta
            DATA.value.transDelta = *(UINT8 *)FieldValue;
            break;
        case 192: //sunGlare
            DATA.value.sunGlare = *(UINT8 *)FieldValue;
            break;
        case 193: //sunDamage
            DATA.value.sunDamage = *(UINT8 *)FieldValue;
            break;
        case 194: //rainFadeIn
            DATA.value.rainFadeIn = *(UINT8 *)FieldValue;
            break;
        case 195: //rainFadeOut
            DATA.value.rainFadeOut = *(UINT8 *)FieldValue;
            break;
        case 196: //boltFadeIn
            DATA.value.boltFadeIn = *(UINT8 *)FieldValue;
            break;
        case 197: //boltFadeOut
            DATA.value.boltFadeOut = *(UINT8 *)FieldValue;
            break;
        case 198: //boltFrequency
            DATA.value.boltFrequency = *(UINT8 *)FieldValue;
            break;
        case 199: //weatherType
            SetType(*(UINT8 *)FieldValue);
            break;
        case 200: //boltRed
            DATA.value.boltRed = *(UINT8 *)FieldValue;
            break;
        case 201: //boltGreen
            DATA.value.boltGreen = *(UINT8 *)FieldValue;
            break;
        case 202: //boltBlue
            DATA.value.boltBlue = *(UINT8 *)FieldValue;
            break;
        case 203: //sounds
            if(ListFieldID == 0) //soundsSize
                {
                Sounds.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Sounds.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //sound
                    Sounds.value[ListIndex]->sound = *(FORMID *)FieldValue;
                    return true;
                case 2: //type
                    Sounds.value[ListIndex]->SetType(*(UINT32 *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void WTHRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENCLR defaultCLR;
    WTHRFNAM defaultFNAM;
    WTHRHNAM defaultHNAM;
    WTHRDATA defaultDATA;
    WTHRColors defaultColors;

    WTHRSNAM defaultSNAM;

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
        case 5: //lowerLayerPath
            CNAM.Unload();
            return;
        case 6: //upperLayerPath
            DNAM.Unload();
            return;
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 10: //upperSky.rise.red
            NAM0.value.upperSky.rise.red = defaultCLR.red;
            return;
        case 11: //upperSky.rise.green
            NAM0.value.upperSky.rise.green = defaultCLR.green;
            return;
        case 12: //upperSky.rise.blue
            NAM0.value.upperSky.rise.blue = defaultCLR.blue;
            return;
        case 13: //upperSky.rise.unused1
            NAM0.value.upperSky.rise.unused1 = defaultCLR.unused1;
            return;
        case 14: //upperSky.day.red
            NAM0.value.upperSky.day.red = defaultCLR.red;
            return;
        case 15: //upperSky.day.green
            NAM0.value.upperSky.day.green = defaultCLR.green;
            return;
        case 16: //upperSky.day.blue
            NAM0.value.upperSky.day.blue = defaultCLR.blue;
            return;
        case 17: //upperSky.day.unused1
            NAM0.value.upperSky.day.unused1 = defaultCLR.unused1;
            return;
        case 18: //upperSky.set.red
            NAM0.value.upperSky.set.red = defaultCLR.red;
            return;
        case 19: //upperSky.set.green
            NAM0.value.upperSky.set.green = defaultCLR.green;
            return;
        case 20: //upperSky.set.blue
            NAM0.value.upperSky.set.blue = defaultCLR.blue;
            return;
        case 21: //upperSky.set.unused1
            NAM0.value.upperSky.set.unused1 = defaultCLR.unused1;
            return;
        case 22: //upperSky.night.red
            NAM0.value.upperSky.night.red = defaultCLR.red;
            return;
        case 23: //upperSky.night.green
            NAM0.value.upperSky.night.green = defaultCLR.green;
            return;
        case 24: //upperSky.night.blue
            NAM0.value.upperSky.night.blue = defaultCLR.blue;
            return;
        case 25: //upperSky.night.unused1
            NAM0.value.upperSky.night.unused1 = defaultCLR.unused1;
            return;
        case 26: //fog.rise.red
            NAM0.value.fog.rise.red = defaultCLR.red;
            return;
        case 27: //fog.rise.green
            NAM0.value.fog.rise.green = defaultCLR.green;
            return;
        case 28: //fog.rise.blue
            NAM0.value.fog.rise.blue = defaultCLR.blue;
            return;
        case 29: //fog.rise.unused1
            NAM0.value.fog.rise.unused1 = defaultCLR.unused1;
            return;
        case 30: //fog.day.red
            NAM0.value.fog.day.red = defaultCLR.red;
            return;
        case 31: //fog.day.green
            NAM0.value.fog.day.green = defaultCLR.green;
            return;
        case 32: //fog.day.blue
            NAM0.value.fog.day.blue = defaultCLR.blue;
            return;
        case 33: //fog.day.unused1
            NAM0.value.fog.day.unused1 = defaultCLR.unused1;
            return;
        case 34: //fog.set.red
            NAM0.value.fog.set.red = defaultCLR.red;
            return;
        case 35: //fog.set.green
            NAM0.value.fog.set.green = defaultCLR.green;
            return;
        case 36: //fog.set.blue
            NAM0.value.fog.set.blue = defaultCLR.blue;
            return;
        case 37: //fog.set.unused1
            NAM0.value.fog.set.unused1 = defaultCLR.unused1;
            return;
        case 38: //fog.night.red
            NAM0.value.fog.night.red = defaultCLR.red;
            return;
        case 39: //fog.night.green
            NAM0.value.fog.night.green = defaultCLR.green;
            return;
        case 40: //fog.night.blue
            NAM0.value.fog.night.blue = defaultCLR.blue;
            return;
        case 41: //fog.night.unused1
            NAM0.value.fog.night.unused1 = defaultCLR.unused1;
            return;
        case 42: //lowerClouds.rise.red
            NAM0.value.lowerClouds.rise.red = defaultCLR.red;
            return;
        case 43: //lowerClouds.rise.green
            NAM0.value.lowerClouds.rise.green = defaultCLR.green;
            return;
        case 44: //lowerClouds.rise.blue
            NAM0.value.lowerClouds.rise.blue = defaultCLR.blue;
            return;
        case 45: //lowerClouds.rise.unused1
            NAM0.value.lowerClouds.rise.unused1 = defaultCLR.unused1;
            return;
        case 46: //lowerClouds.day.red
            NAM0.value.lowerClouds.day.red = defaultCLR.red;
            return;
        case 47: //lowerClouds.day.green
            NAM0.value.lowerClouds.day.green = defaultCLR.green;
            return;
        case 48: //lowerClouds.day.blue
            NAM0.value.lowerClouds.day.blue = defaultCLR.blue;
            return;
        case 49: //lowerClouds.day.unused1
            NAM0.value.lowerClouds.day.unused1 = defaultCLR.unused1;
            return;
        case 50: //lowerClouds.set.red
            NAM0.value.lowerClouds.set.red = defaultCLR.red;
            return;
        case 51: //lowerClouds.set.green
            NAM0.value.lowerClouds.set.green = defaultCLR.green;
            return;
        case 52: //lowerClouds.set.blue
            NAM0.value.lowerClouds.set.blue = defaultCLR.blue;
            return;
        case 53: //lowerClouds.set.unused1
            NAM0.value.lowerClouds.set.unused1 = defaultCLR.unused1;
            return;
        case 54: //lowerClouds.night.red
            NAM0.value.lowerClouds.night.red = defaultCLR.red;
            return;
        case 55: //lowerClouds.night.green
            NAM0.value.lowerClouds.night.green = defaultCLR.green;
            return;
        case 56: //lowerClouds.night.blue
            NAM0.value.lowerClouds.night.blue = defaultCLR.blue;
            return;
        case 57: //lowerClouds.night.unused1
            NAM0.value.lowerClouds.night.unused1 = defaultCLR.unused1;
            return;
        case 58: //ambient.rise.red
            NAM0.value.ambient.rise.red = defaultCLR.red;
            return;
        case 59: //ambient.rise.green
            NAM0.value.ambient.rise.green = defaultCLR.green;
            return;
        case 60: //ambient.rise.blue
            NAM0.value.ambient.rise.blue = defaultCLR.blue;
            return;
        case 61: //ambient.rise.unused1
            NAM0.value.ambient.rise.unused1 = defaultCLR.unused1;
            return;
        case 62: //ambient.day.red
            NAM0.value.ambient.day.red = defaultCLR.red;
            return;
        case 63: //ambient.day.green
            NAM0.value.ambient.day.green = defaultCLR.green;
            return;
        case 64: //ambient.day.blue
            NAM0.value.ambient.day.blue = defaultCLR.blue;
            return;
        case 65: //ambient.day.unused1
            NAM0.value.ambient.day.unused1 = defaultCLR.unused1;
            return;
        case 66: //ambient.set.red
            NAM0.value.ambient.set.red = defaultCLR.red;
            return;
        case 67: //ambient.set.green
            NAM0.value.ambient.set.green = defaultCLR.green;
            return;
        case 68: //ambient.set.blue
            NAM0.value.ambient.set.blue = defaultCLR.blue;
            return;
        case 69: //ambient.set.unused1
            NAM0.value.ambient.set.unused1 = defaultCLR.unused1;
            return;
        case 70: //ambient.night.red
            NAM0.value.ambient.night.red = defaultCLR.red;
            return;
        case 71: //ambient.night.green
            NAM0.value.ambient.night.green = defaultCLR.green;
            return;
        case 72: //ambient.night.blue
            NAM0.value.ambient.night.blue = defaultCLR.blue;
            return;
        case 73: //ambient.night.unused1
            NAM0.value.ambient.night.unused1 = defaultCLR.unused1;
            return;
        case 74: //sunlight.rise.red
            NAM0.value.sunlight.rise.red = defaultCLR.red;
            return;
        case 75: //sunlight.rise.green
            NAM0.value.sunlight.rise.green = defaultCLR.green;
            return;
        case 76: //sunlight.rise.blue
            NAM0.value.sunlight.rise.blue = defaultCLR.blue;
            return;
        case 77: //sunlight.rise.unused1
            NAM0.value.sunlight.rise.unused1 = defaultCLR.unused1;
            return;
        case 78: //sunlight.day.red
            NAM0.value.sunlight.day.red = defaultCLR.red;
            return;
        case 79: //sunlight.day.green
            NAM0.value.sunlight.day.green = defaultCLR.green;
            return;
        case 80: //sunlight.day.blue
            NAM0.value.sunlight.day.blue = defaultCLR.blue;
            return;
        case 81: //sunlight.day.unused1
            NAM0.value.sunlight.day.unused1 = defaultCLR.unused1;
            return;
        case 82: //sunlight.set.red
            NAM0.value.sunlight.set.red = defaultCLR.red;
            return;
        case 83: //sunlight.set.green
            NAM0.value.sunlight.set.green = defaultCLR.green;
            return;
        case 84: //sunlight.set.blue
            NAM0.value.sunlight.set.blue = defaultCLR.blue;
            return;
        case 85: //sunlight.set.unused1
            NAM0.value.sunlight.set.unused1 = defaultCLR.unused1;
            return;
        case 86: //sunlight.night.red
            NAM0.value.sunlight.night.red = defaultCLR.red;
            return;
        case 87: //sunlight.night.green
            NAM0.value.sunlight.night.green = defaultCLR.green;
            return;
        case 88: //sunlight.night.blue
            NAM0.value.sunlight.night.blue = defaultCLR.blue;
            return;
        case 89: //sunlight.night.unused1
            NAM0.value.sunlight.night.unused1 = defaultCLR.unused1;
            return;
        case 90: //sun.rise.red
            NAM0.value.sun.rise.red = defaultCLR.red;
            return;
        case 91: //sun.rise.green
            NAM0.value.sun.rise.green = defaultCLR.green;
            return;
        case 92: //sun.rise.blue
            NAM0.value.sun.rise.blue = defaultCLR.blue;
            return;
        case 93: //sun.rise.unused1
            NAM0.value.sun.rise.unused1 = defaultCLR.unused1;
            return;
        case 94: //sun.day.red
            NAM0.value.sun.day.red = defaultCLR.red;
            return;
        case 95: //sun.day.green
            NAM0.value.sun.day.green = defaultCLR.green;
            return;
        case 96: //sun.day.blue
            NAM0.value.sun.day.blue = defaultCLR.blue;
            return;
        case 97: //sun.day.unused1
            NAM0.value.sun.day.unused1 = defaultCLR.unused1;
            return;
        case 98: //sun.set.red
            NAM0.value.sun.set.red = defaultCLR.red;
            return;
        case 99: //sun.set.green
            NAM0.value.sun.set.green = defaultCLR.green;
            return;
        case 100: //sun.set.blue
            NAM0.value.sun.set.blue = defaultCLR.blue;
            return;
        case 101: //sun.set.unused1
            NAM0.value.sun.set.unused1 = defaultCLR.unused1;
            return;
        case 102: //sun.night.red
            NAM0.value.sun.night.red = defaultCLR.red;
            return;
        case 103: //sun.night.green
            NAM0.value.sun.night.green = defaultCLR.green;
            return;
        case 104: //sun.night.blue
            NAM0.value.sun.night.blue = defaultCLR.blue;
            return;
        case 105: //sun.night.unused1
            NAM0.value.sun.night.unused1 = defaultCLR.unused1;
            return;
        case 106: //stars.rise.red
            NAM0.value.stars.rise.red = defaultCLR.red;
            return;
        case 107: //stars.rise.green
            NAM0.value.stars.rise.green = defaultCLR.green;
            return;
        case 108: //stars.rise.blue
            NAM0.value.stars.rise.blue = defaultCLR.blue;
            return;
        case 109: //stars.rise.unused1
            NAM0.value.stars.rise.unused1 = defaultCLR.unused1;
            return;
        case 110: //stars.day.red
            NAM0.value.stars.day.red = defaultCLR.red;
            return;
        case 111: //stars.day.green
            NAM0.value.stars.day.green = defaultCLR.green;
            return;
        case 112: //stars.day.blue
            NAM0.value.stars.day.blue = defaultCLR.blue;
            return;
        case 113: //stars.day.unused1
            NAM0.value.stars.day.unused1 = defaultCLR.unused1;
            return;
        case 114: //stars.set.red
            NAM0.value.stars.set.red = defaultCLR.red;
            return;
        case 115: //stars.set.green
            NAM0.value.stars.set.green = defaultCLR.green;
            return;
        case 116: //stars.set.blue
            NAM0.value.stars.set.blue = defaultCLR.blue;
            return;
        case 117: //stars.set.unused1
            NAM0.value.stars.set.unused1 = defaultCLR.unused1;
            return;
        case 118: //stars.night.red
            NAM0.value.stars.night.red = defaultCLR.red;
            return;
        case 119: //stars.night.green
            NAM0.value.stars.night.green = defaultCLR.green;
            return;
        case 120: //stars.night.blue
            NAM0.value.stars.night.blue = defaultCLR.blue;
            return;
        case 121: //stars.night.unused1
            NAM0.value.stars.night.unused1 = defaultCLR.unused1;
            return;
        case 122: //lowerSky.rise.red
            NAM0.value.lowerSky.rise.red = defaultCLR.red;
            return;
        case 123: //lowerSky.rise.green
            NAM0.value.lowerSky.rise.green = defaultCLR.green;
            return;
        case 124: //lowerSky.rise.blue
            NAM0.value.lowerSky.rise.blue = defaultCLR.blue;
            return;
        case 125: //lowerSky.rise.unused1
            NAM0.value.lowerSky.rise.unused1 = defaultCLR.unused1;
            return;
        case 126: //lowerSky.day.red
            NAM0.value.lowerSky.day.red = defaultCLR.red;
            return;
        case 127: //lowerSky.day.green
            NAM0.value.lowerSky.day.green = defaultCLR.green;
            return;
        case 128: //lowerSky.day.blue
            NAM0.value.lowerSky.day.blue = defaultCLR.blue;
            return;
        case 129: //lowerSky.day.unused1
            NAM0.value.lowerSky.day.unused1 = defaultCLR.unused1;
            return;
        case 130: //lowerSky.set.red
            NAM0.value.lowerSky.set.red = defaultCLR.red;
            return;
        case 131: //lowerSky.set.green
            NAM0.value.lowerSky.set.green = defaultCLR.green;
            return;
        case 132: //lowerSky.set.blue
            NAM0.value.lowerSky.set.blue = defaultCLR.blue;
            return;
        case 133: //lowerSky.set.unused1
            NAM0.value.lowerSky.set.unused1 = defaultCLR.unused1;
            return;
        case 134: //lowerSky.night.red
            NAM0.value.lowerSky.night.red = defaultCLR.red;
            return;
        case 135: //lowerSky.night.green
            NAM0.value.lowerSky.night.green = defaultCLR.green;
            return;
        case 136: //lowerSky.night.blue
            NAM0.value.lowerSky.night.blue = defaultCLR.blue;
            return;
        case 137: //lowerSky.night.unused1
            NAM0.value.lowerSky.night.unused1 = defaultCLR.unused1;
            return;
        case 138: //horizon.rise.red
            NAM0.value.horizon.rise.red = defaultCLR.red;
            return;
        case 139: //horizon.rise.green
            NAM0.value.horizon.rise.green = defaultCLR.green;
            return;
        case 140: //horizon.rise.blue
            NAM0.value.horizon.rise.blue = defaultCLR.blue;
            return;
        case 141: //horizon.rise.unused1
            NAM0.value.horizon.rise.unused1 = defaultCLR.unused1;
            return;
        case 142: //horizon.day.red
            NAM0.value.horizon.day.red = defaultCLR.red;
            return;
        case 143: //horizon.day.green
            NAM0.value.horizon.day.green = defaultCLR.green;
            return;
        case 144: //horizon.day.blue
            NAM0.value.horizon.day.blue = defaultCLR.blue;
            return;
        case 145: //horizon.day.unused1
            NAM0.value.horizon.day.unused1 = defaultCLR.unused1;
            return;
        case 146: //horizon.set.red
            NAM0.value.horizon.set.red = defaultCLR.red;
            return;
        case 147: //horizon.set.green
            NAM0.value.horizon.set.green = defaultCLR.green;
            return;
        case 148: //horizon.set.blue
            NAM0.value.horizon.set.blue = defaultCLR.blue;
            return;
        case 149: //horizon.set.unused1
            NAM0.value.horizon.set.unused1 = defaultCLR.unused1;
            return;
        case 150: //horizon.night.red
            NAM0.value.horizon.night.red = defaultCLR.red;
            return;
        case 151: //horizon.night.green
            NAM0.value.horizon.night.green = defaultCLR.green;
            return;
        case 152: //horizon.night.blue
            NAM0.value.horizon.night.blue = defaultCLR.blue;
            return;
        case 153: //horizon.night.unused1
            NAM0.value.horizon.night.unused1 = defaultCLR.unused1;
            return;
        case 154: //upperClouds.rise.red
            NAM0.value.upperClouds.rise.red = defaultCLR.red;
            return;
        case 155: //upperClouds.rise.green
            NAM0.value.upperClouds.rise.green = defaultCLR.green;
            return;
        case 156: //upperClouds.rise.blue
            NAM0.value.upperClouds.rise.blue = defaultCLR.blue;
            return;
        case 157: //upperClouds.rise.unused1
            NAM0.value.upperClouds.rise.unused1 = defaultCLR.unused1;
            return;
        case 158: //upperClouds.day.red
            NAM0.value.upperClouds.day.red = defaultCLR.red;
            return;
        case 159: //upperClouds.day.green
            NAM0.value.upperClouds.day.green = defaultCLR.green;
            return;
        case 160: //upperClouds.day.blue
            NAM0.value.upperClouds.day.blue = defaultCLR.blue;
            return;
        case 161: //upperClouds.day.unused1
            NAM0.value.upperClouds.day.unused1 = defaultCLR.unused1;
            return;
        case 162: //upperClouds.set.red
            NAM0.value.upperClouds.set.red = defaultCLR.red;
            return;
        case 163: //upperClouds.set.green
            NAM0.value.upperClouds.set.green = defaultCLR.green;
            return;
        case 164: //upperClouds.set.blue
            NAM0.value.upperClouds.set.blue = defaultCLR.blue;
            return;
        case 165: //upperClouds.set.unused1
            NAM0.value.upperClouds.set.unused1 = defaultCLR.unused1;
            return;
        case 166: //upperClouds.night.red
            NAM0.value.upperClouds.night.red = defaultCLR.red;
            return;
        case 167: //upperClouds.night.green
            NAM0.value.upperClouds.night.green = defaultCLR.green;
            return;
        case 168: //upperClouds.night.blue
            NAM0.value.upperClouds.night.blue = defaultCLR.blue;
            return;
        case 169: //upperClouds.night.unused1
            NAM0.value.upperClouds.night.unused1 = defaultCLR.unused1;
            return;
        case 170: //fogDayNear
            FNAM.value.fogDayNear = defaultFNAM.fogDayNear;
            return;
        case 171: //fogDayFar
            FNAM.value.fogDayFar = defaultFNAM.fogDayFar;
            return;
        case 172: //fogNightNear
            FNAM.value.fogNightNear = defaultFNAM.fogNightNear;
            return;
        case 173: //fogNightFar
            FNAM.value.fogNightFar = defaultFNAM.fogNightFar;
            return;
        case 174: //eyeAdaptSpeed
            HNAM.value.eyeAdaptSpeed = defaultHNAM.eyeAdaptSpeed;
            return;
        case 175: //blurRadius
            HNAM.value.blurRadius = defaultHNAM.blurRadius;
            return;
        case 176: //blurPasses
            HNAM.value.blurPasses = defaultHNAM.blurPasses;
            return;
        case 177: //emissiveMult
            HNAM.value.emissiveMult = defaultHNAM.emissiveMult;
            return;
        case 178: //targetLum
            HNAM.value.targetLum = defaultHNAM.targetLum;
            return;
        case 179: //upperLumClamp
            HNAM.value.upperLumClamp = defaultHNAM.upperLumClamp;
            return;
        case 180: //brightScale
            HNAM.value.brightScale = defaultHNAM.brightScale;
            return;
        case 181: //brightClamp
            HNAM.value.brightClamp = defaultHNAM.brightClamp;
            return;
        case 182: //lumRampNoTex
            HNAM.value.lumRampNoTex = defaultHNAM.lumRampNoTex;
            return;
        case 183: //lumRampMin
            HNAM.value.lumRampMin = defaultHNAM.lumRampMin;
            return;
        case 184: //lumRampMax
            HNAM.value.lumRampMax = defaultHNAM.lumRampMax;
            return;
        case 185: //sunlightDimmer
            HNAM.value.sunlightDimmer = defaultHNAM.sunlightDimmer;
            return;
        case 186: //grassDimmer
            HNAM.value.grassDimmer = defaultHNAM.grassDimmer;
            return;
        case 187: //treeDimmer
            HNAM.value.treeDimmer = defaultHNAM.treeDimmer;
            return;
        case 188: //windSpeed
            DATA.value.windSpeed = defaultDATA.windSpeed;
            return;
        case 189: //lowerCloudSpeed
            DATA.value.lowerCloudSpeed = defaultDATA.lowerCloudSpeed;
            return;
        case 190: //upperCloudSpeed
            DATA.value.upperCloudSpeed = defaultDATA.upperCloudSpeed;
            return;
        case 191: //transDelta
            DATA.value.transDelta = defaultDATA.transDelta;
            return;
        case 192: //sunGlare
            DATA.value.sunGlare = defaultDATA.sunGlare;
            return;
        case 193: //sunDamage
            DATA.value.sunDamage = defaultDATA.sunDamage;
            return;
        case 194: //rainFadeIn
            DATA.value.rainFadeIn = defaultDATA.rainFadeIn;
            return;
        case 195: //rainFadeOut
            DATA.value.rainFadeOut = defaultDATA.rainFadeOut;
            return;
        case 196: //boltFadeIn
            DATA.value.boltFadeIn = defaultDATA.boltFadeIn;
            return;
        case 197: //boltFadeOut
            DATA.value.boltFadeOut = defaultDATA.boltFadeOut;
            return;
        case 198: //boltFrequency
            DATA.value.boltFrequency = defaultDATA.boltFrequency;
            return;
        case 199: //weatherType
            DATA.value.weatherType = defaultDATA.weatherType;
            return;
        case 200: //boltRed
            DATA.value.boltRed = defaultDATA.boltRed;
            return;
        case 201: //boltGreen
            DATA.value.boltGreen = defaultDATA.boltGreen;
            return;
        case 202: //boltBlue
            DATA.value.boltBlue = defaultDATA.boltBlue;
            return;
        case 203: //sounds
            if(ListFieldID == 0) //sounds
                {
                Sounds.Unload();
                return;
                }

            if(ListIndex >= Sounds.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //sound
                    Sounds.value[ListIndex]->sound = defaultSNAM.sound;
                    return;
                case 2: //type
                    Sounds.value[ListIndex]->type = defaultSNAM.type;
                    return;
                default:
                    return;
                }
            return;
        case 204: //convenience deleter
            NAM0.value.upperSky = defaultColors;
            return;
        case 205: //convenience deleter
            NAM0.value.fog = defaultColors;
            return;
        case 206: //convenience deleter
            NAM0.value.lowerClouds = defaultColors;
            return;
        case 207: //convenience deleter
            NAM0.value.ambient = defaultColors;
            return;
        case 208: //convenience deleter
            NAM0.value.sunlight = defaultColors;
            return;
        case 209: //convenience deleter
            NAM0.value.sun = defaultColors;
            return;
        case 210: //convenience deleter
            NAM0.value.stars = defaultColors;
            return;
        case 211: //convenience deleter
            NAM0.value.lowerSky = defaultColors;
            return;
        case 212: //convenience deleter
            NAM0.value.horizon = defaultColors;
            return;
        case 213: //convenience deleter
            NAM0.value.upperClouds = defaultColors;
            return;
        default:
            return;
        }
    return;
    }
}