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
#include "..\WTHRRecord.h"

namespace FNV
{
uint32_t WTHRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //sunriseImageSpace
            return CB_FORMID_FIELD;
        case 8: //dayImageSpace
            return CB_FORMID_FIELD;
        case 9: //sunsetImageSpace
            return CB_FORMID_FIELD;
        case 10: //nightImageSpace
            return CB_FORMID_FIELD;
        case 11: //unknown1ImageSpace
            return CB_FORMID_FIELD;
        case 12: //unknown2ImageSpace
            return CB_FORMID_FIELD;
        case 13: //cloudLayer0Path
            return CB_ISTRING_FIELD;
        case 14: //cloudLayer1Path
            return CB_ISTRING_FIELD;
        case 15: //cloudLayer2Path
            return CB_ISTRING_FIELD;
        case 16: //cloudLayer3Path
            return CB_ISTRING_FIELD;
        case 17: //modPath
            return CB_ISTRING_FIELD;
        case 18: //modb
            return CB_FLOAT32_FIELD;
        case 19: //modt_p
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
        case 20: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_STRING_FIELD;
                case 2: //texture
                    return CB_FORMID_FIELD;
                case 3: //index
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 21: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 22: //unknown1
            return CB_UINT32_FIELD;
        case 23: //layer0Speed
            return CB_UINT8_FIELD;
        case 24: //layer1Speed
            return CB_UINT8_FIELD;
        case 25: //layer2Speed
            return CB_UINT8_FIELD;
        case 26: //layer3Speed
            return CB_UINT8_FIELD;
        case 27: //pnam_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 28: //upperSky.rise.red
            return CB_UINT8_FIELD;
        case 29: //upperSky.rise.green
            return CB_UINT8_FIELD;
        case 30: //upperSky.rise.blue
            return CB_UINT8_FIELD;
        case 31: //upperSky.rise.unused1
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
        case 32: //upperSky.day.red
            return CB_UINT8_FIELD;
        case 33: //upperSky.day.green
            return CB_UINT8_FIELD;
        case 34: //upperSky.day.blue
            return CB_UINT8_FIELD;
        case 35: //upperSky.day.unused1
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
        case 36: //upperSky.set.red
            return CB_UINT8_FIELD;
        case 37: //upperSky.set.green
            return CB_UINT8_FIELD;
        case 38: //upperSky.set.blue
            return CB_UINT8_FIELD;
        case 39: //upperSky.set.unused1
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
        case 40: //upperSky.night.red
            return CB_UINT8_FIELD;
        case 41: //upperSky.night.green
            return CB_UINT8_FIELD;
        case 42: //upperSky.night.blue
            return CB_UINT8_FIELD;
        case 43: //upperSky.night.unused1
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
        case 44: //upperSky.noon.red
            return CB_UINT8_FIELD;
        case 45: //upperSky.noon.green
            return CB_UINT8_FIELD;
        case 46: //upperSky.noon.blue
            return CB_UINT8_FIELD;
        case 47: //upperSky.noon.unused1
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
        case 48: //upperSky.midnight.red
            return CB_UINT8_FIELD;
        case 49: //upperSky.midnight.green
            return CB_UINT8_FIELD;
        case 50: //upperSky.midnight.blue
            return CB_UINT8_FIELD;
        case 51: //upperSky.midnight.unused1
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
        case 52: //fog.rise.red
            return CB_UINT8_FIELD;
        case 53: //fog.rise.green
            return CB_UINT8_FIELD;
        case 54: //fog.rise.blue
            return CB_UINT8_FIELD;
        case 55: //fog.rise.unused1
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
        case 56: //fog.day.red
            return CB_UINT8_FIELD;
        case 57: //fog.day.green
            return CB_UINT8_FIELD;
        case 58: //fog.day.blue
            return CB_UINT8_FIELD;
        case 59: //fog.day.unused1
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
        case 60: //fog.set.red
            return CB_UINT8_FIELD;
        case 61: //fog.set.green
            return CB_UINT8_FIELD;
        case 62: //fog.set.blue
            return CB_UINT8_FIELD;
        case 63: //fog.set.unused1
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
        case 64: //fog.night.red
            return CB_UINT8_FIELD;
        case 65: //fog.night.green
            return CB_UINT8_FIELD;
        case 66: //fog.night.blue
            return CB_UINT8_FIELD;
        case 67: //fog.night.unused1
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
        case 68: //fog.noon.red
            return CB_UINT8_FIELD;
        case 69: //fog.noon.green
            return CB_UINT8_FIELD;
        case 70: //fog.noon.blue
            return CB_UINT8_FIELD;
        case 71: //fog.noon.unused1
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
        case 72: //fog.midnight.red
            return CB_UINT8_FIELD;
        case 73: //fog.midnight.green
            return CB_UINT8_FIELD;
        case 74: //fog.midnight.blue
            return CB_UINT8_FIELD;
        case 75: //fog.midnight.unused1
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
        case 76: //lowerClouds.rise.red
            return CB_UINT8_FIELD;
        case 77: //lowerClouds.rise.green
            return CB_UINT8_FIELD;
        case 78: //lowerClouds.rise.blue
            return CB_UINT8_FIELD;
        case 79: //lowerClouds.rise.unused1
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
        case 80: //lowerClouds.day.red
            return CB_UINT8_FIELD;
        case 81: //lowerClouds.day.green
            return CB_UINT8_FIELD;
        case 82: //lowerClouds.day.blue
            return CB_UINT8_FIELD;
        case 83: //lowerClouds.day.unused1
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
        case 84: //lowerClouds.set.red
            return CB_UINT8_FIELD;
        case 85: //lowerClouds.set.green
            return CB_UINT8_FIELD;
        case 86: //lowerClouds.set.blue
            return CB_UINT8_FIELD;
        case 87: //lowerClouds.set.unused1
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
        case 88: //lowerClouds.night.red
            return CB_UINT8_FIELD;
        case 89: //lowerClouds.night.green
            return CB_UINT8_FIELD;
        case 90: //lowerClouds.night.blue
            return CB_UINT8_FIELD;
        case 91: //lowerClouds.night.unused1
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
        case 92: //lowerClouds.noon.red
            return CB_UINT8_FIELD;
        case 93: //lowerClouds.noon.green
            return CB_UINT8_FIELD;
        case 94: //lowerClouds.noon.blue
            return CB_UINT8_FIELD;
        case 95: //lowerClouds.noon.unused1
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

        case 96: //lowerClouds.midnight.red
            return CB_UINT8_FIELD;
        case 97: //lowerClouds.midnight.green
            return CB_UINT8_FIELD;
        case 98: //lowerClouds.midnight.blue
            return CB_UINT8_FIELD;
        case 99: //lowerClouds.midnight.unused1
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
        case 100: //ambient.rise.red
            return CB_UINT8_FIELD;
        case 101: //ambient.rise.green
            return CB_UINT8_FIELD;
        case 102: //ambient.rise.blue
            return CB_UINT8_FIELD;
        case 103: //ambient.rise.unused1
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
        case 104: //ambient.day.red
            return CB_UINT8_FIELD;
        case 105: //ambient.day.green
            return CB_UINT8_FIELD;
        case 106: //ambient.day.blue
            return CB_UINT8_FIELD;
        case 107: //ambient.day.unused1
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
        case 108: //ambient.set.red
            return CB_UINT8_FIELD;
        case 109: //ambient.set.green
            return CB_UINT8_FIELD;
        case 110: //ambient.set.blue
            return CB_UINT8_FIELD;
        case 111: //ambient.set.unused1
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
        case 112: //ambient.night.red
            return CB_UINT8_FIELD;
        case 113: //ambient.night.green
            return CB_UINT8_FIELD;
        case 114: //ambient.night.blue
            return CB_UINT8_FIELD;
        case 115: //ambient.night.unused1
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
        case 116: //ambient.noon.red
            return CB_UINT8_FIELD;
        case 117: //ambient.noon.green
            return CB_UINT8_FIELD;
        case 118: //ambient.noon.blue
            return CB_UINT8_FIELD;
        case 119: //ambient.noon.unused1
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

        case 120: //ambient.midnight.red
            return CB_UINT8_FIELD;
        case 121: //ambient.midnight.green
            return CB_UINT8_FIELD;
        case 122: //ambient.midnight.blue
            return CB_UINT8_FIELD;
        case 123: //ambient.midnight.unused1
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
        case 124: //sunlight.rise.red
            return CB_UINT8_FIELD;
        case 125: //sunlight.rise.green
            return CB_UINT8_FIELD;
        case 126: //sunlight.rise.blue
            return CB_UINT8_FIELD;
        case 127: //sunlight.rise.unused1
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
        case 128: //sunlight.day.red
            return CB_UINT8_FIELD;
        case 129: //sunlight.day.green
            return CB_UINT8_FIELD;
        case 130: //sunlight.day.blue
            return CB_UINT8_FIELD;
        case 131: //sunlight.day.unused1
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
        case 132: //sunlight.set.red
            return CB_UINT8_FIELD;
        case 133: //sunlight.set.green
            return CB_UINT8_FIELD;
        case 134: //sunlight.set.blue
            return CB_UINT8_FIELD;
        case 135: //sunlight.set.unused1
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
        case 136: //sunlight.night.red
            return CB_UINT8_FIELD;
        case 137: //sunlight.night.green
            return CB_UINT8_FIELD;
        case 138: //sunlight.night.blue
            return CB_UINT8_FIELD;
        case 139: //sunlight.night.unused1
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
        case 140: //sunlight.noon.red
            return CB_UINT8_FIELD;
        case 141: //sunlight.noon.green
            return CB_UINT8_FIELD;
        case 142: //sunlight.noon.blue
            return CB_UINT8_FIELD;
        case 143: //sunlight.noon.unused1
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

        case 144: //sunlight.midnight.red
            return CB_UINT8_FIELD;
        case 145: //sunlight.midnight.green
            return CB_UINT8_FIELD;
        case 146: //sunlight.midnight.blue
            return CB_UINT8_FIELD;
        case 147: //sunlight.midnight.unused1
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
        case 148: //sun.rise.red
            return CB_UINT8_FIELD;
        case 149: //sun.rise.green
            return CB_UINT8_FIELD;
        case 150: //sun.rise.blue
            return CB_UINT8_FIELD;
        case 151: //sun.rise.unused1
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
        case 152: //sun.day.red
            return CB_UINT8_FIELD;
        case 153: //sun.day.green
            return CB_UINT8_FIELD;
        case 154: //sun.day.blue
            return CB_UINT8_FIELD;
        case 155: //sun.day.unused1
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
        case 156: //sun.set.red
            return CB_UINT8_FIELD;
        case 157: //sun.set.green
            return CB_UINT8_FIELD;
        case 158: //sun.set.blue
            return CB_UINT8_FIELD;
        case 159: //sun.set.unused1
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
        case 160: //sun.night.red
            return CB_UINT8_FIELD;
        case 161: //sun.night.green
            return CB_UINT8_FIELD;
        case 162: //sun.night.blue
            return CB_UINT8_FIELD;
        case 163: //sun.night.unused1
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
        case 164: //sun.noon.red
            return CB_UINT8_FIELD;
        case 165: //sun.noon.green
            return CB_UINT8_FIELD;
        case 166: //sun.noon.blue
            return CB_UINT8_FIELD;
        case 167: //sun.noon.unused1
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

        case 168: //sun.midnight.red
            return CB_UINT8_FIELD;
        case 169: //sun.midnight.green
            return CB_UINT8_FIELD;
        case 170: //sun.midnight.blue
            return CB_UINT8_FIELD;
        case 171: //sun.midnight.unused1
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
        case 172: //stars.rise.red
            return CB_UINT8_FIELD;
        case 173: //stars.rise.green
            return CB_UINT8_FIELD;
        case 174: //stars.rise.blue
            return CB_UINT8_FIELD;
        case 175: //stars.rise.unused1
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
        case 176: //stars.day.red
            return CB_UINT8_FIELD;
        case 177: //stars.day.green
            return CB_UINT8_FIELD;
        case 178: //stars.day.blue
            return CB_UINT8_FIELD;
        case 179: //stars.day.unused1
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
        case 180: //stars.set.red
            return CB_UINT8_FIELD;
        case 181: //stars.set.green
            return CB_UINT8_FIELD;
        case 182: //stars.set.blue
            return CB_UINT8_FIELD;
        case 183: //stars.set.unused1
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
        case 184: //stars.night.red
            return CB_UINT8_FIELD;
        case 185: //stars.night.green
            return CB_UINT8_FIELD;
        case 186: //stars.night.blue
            return CB_UINT8_FIELD;
        case 187: //stars.night.unused1
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
        case 188: //stars.noon.red
            return CB_UINT8_FIELD;
        case 189: //stars.noon.green
            return CB_UINT8_FIELD;
        case 190: //stars.noon.blue
            return CB_UINT8_FIELD;
        case 191: //stars.noon.unused1
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

        case 192: //stars.midnight.red
            return CB_UINT8_FIELD;
        case 193: //stars.midnight.green
            return CB_UINT8_FIELD;
        case 194: //stars.midnight.blue
            return CB_UINT8_FIELD;
        case 195: //stars.midnight.unused1
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
        case 196: //lowerSky.rise.red
            return CB_UINT8_FIELD;
        case 197: //lowerSky.rise.green
            return CB_UINT8_FIELD;
        case 198: //lowerSky.rise.blue
            return CB_UINT8_FIELD;
        case 199: //lowerSky.rise.unused1
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
        case 200: //lowerSky.day.red
            return CB_UINT8_FIELD;
        case 201: //lowerSky.day.green
            return CB_UINT8_FIELD;
        case 202: //lowerSky.day.blue
            return CB_UINT8_FIELD;
        case 203: //lowerSky.day.unused1
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
        case 204: //lowerSky.set.red
            return CB_UINT8_FIELD;
        case 205: //lowerSky.set.green
            return CB_UINT8_FIELD;
        case 206: //lowerSky.set.blue
            return CB_UINT8_FIELD;
        case 207: //lowerSky.set.unused1
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
        case 208: //lowerSky.night.red
            return CB_UINT8_FIELD;
        case 209: //lowerSky.night.green
            return CB_UINT8_FIELD;
        case 210: //lowerSky.night.blue
            return CB_UINT8_FIELD;
        case 211: //lowerSky.night.unused1
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
        case 212: //lowerSky.noon.red
            return CB_UINT8_FIELD;
        case 213: //lowerSky.noon.green
            return CB_UINT8_FIELD;
        case 214: //lowerSky.noon.blue
            return CB_UINT8_FIELD;
        case 215: //lowerSky.noon.unused1
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

        case 216: //lowerSky.midnight.red
            return CB_UINT8_FIELD;
        case 217: //lowerSky.midnight.green
            return CB_UINT8_FIELD;
        case 218: //lowerSky.midnight.blue
            return CB_UINT8_FIELD;
        case 219: //lowerSky.midnight.unused1
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
        case 220: //horizon.rise.red
            return CB_UINT8_FIELD;
        case 221: //horizon.rise.green
            return CB_UINT8_FIELD;
        case 222: //horizon.rise.blue
            return CB_UINT8_FIELD;
        case 223: //horizon.rise.unused1
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
        case 224: //horizon.day.red
            return CB_UINT8_FIELD;
        case 225: //horizon.day.green
            return CB_UINT8_FIELD;
        case 226: //horizon.day.blue
            return CB_UINT8_FIELD;
        case 227: //horizon.day.unused1
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
        case 228: //horizon.set.red
            return CB_UINT8_FIELD;
        case 229: //horizon.set.green
            return CB_UINT8_FIELD;
        case 230: //horizon.set.blue
            return CB_UINT8_FIELD;
        case 231: //horizon.set.unused1
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
        case 232: //horizon.night.red
            return CB_UINT8_FIELD;
        case 233: //horizon.night.green
            return CB_UINT8_FIELD;
        case 234: //horizon.night.blue
            return CB_UINT8_FIELD;
        case 235: //horizon.night.unused1
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
        case 236: //horizon.noon.red
            return CB_UINT8_FIELD;
        case 237: //horizon.noon.green
            return CB_UINT8_FIELD;
        case 238: //horizon.noon.blue
            return CB_UINT8_FIELD;
        case 239: //horizon.noon.unused1
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

        case 240: //horizon.midnight.red
            return CB_UINT8_FIELD;
        case 241: //horizon.midnight.green
            return CB_UINT8_FIELD;
        case 242: //horizon.midnight.blue
            return CB_UINT8_FIELD;
        case 243: //horizon.midnight.unused1
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
        case 244: //upperClouds.rise.red
            return CB_UINT8_FIELD;
        case 245: //upperClouds.rise.green
            return CB_UINT8_FIELD;
        case 246: //upperClouds.rise.blue
            return CB_UINT8_FIELD;
        case 247: //upperClouds.rise.unused1
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
        case 248: //upperClouds.day.red
            return CB_UINT8_FIELD;
        case 249: //upperClouds.day.green
            return CB_UINT8_FIELD;
        case 250: //upperClouds.day.blue
            return CB_UINT8_FIELD;
        case 251: //upperClouds.day.unused1
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
        case 252: //upperClouds.set.red
            return CB_UINT8_FIELD;
        case 253: //upperClouds.set.green
            return CB_UINT8_FIELD;
        case 254: //upperClouds.set.blue
            return CB_UINT8_FIELD;
        case 255: //upperClouds.set.unused1
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
        case 256: //upperClouds.night.red
            return CB_UINT8_FIELD;
        case 257: //upperClouds.night.green
            return CB_UINT8_FIELD;
        case 258: //upperClouds.night.blue
            return CB_UINT8_FIELD;
        case 259: //upperClouds.night.unused1
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
        case 260: //upperClouds.noon.red
            return CB_UINT8_FIELD;
        case 261: //upperClouds.noon.green
            return CB_UINT8_FIELD;
        case 262: //upperClouds.noon.blue
            return CB_UINT8_FIELD;
        case 263: //upperClouds.noon.unused1
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
        case 264: //upperClouds.midnight.red
            return CB_UINT8_FIELD;
        case 265: //upperClouds.midnight.green
            return CB_UINT8_FIELD;
        case 266: //upperClouds.midnight.blue
            return CB_UINT8_FIELD;
        case 267: //upperClouds.midnight.unused1
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
        case 268: //fogDayNear
            return CB_FLOAT32_FIELD;
        case 269: //fogDayFar
            return CB_FLOAT32_FIELD;
        case 270: //fogNightNear
            return CB_FLOAT32_FIELD;
        case 271: //fogNightFar
            return CB_FLOAT32_FIELD;
        case 272: //fogDayPower
            return CB_FLOAT32_FIELD;
        case 273: //fogNightPower
            return CB_FLOAT32_FIELD;
        case 274: //inam_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return INAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 275: //windSpeed
            return CB_UINT8_FIELD;
        case 276: //lowerCloudSpeed
            return CB_UINT8_FIELD;
        case 277: //upperCloudSpeed
            return CB_UINT8_FIELD;
        case 278: //transDelta
            return CB_UINT8_FIELD;
        case 279: //sunGlare
            return CB_UINT8_FIELD;
        case 280: //sunDamage
            return CB_UINT8_FIELD;
        case 281: //rainFadeIn
            return CB_UINT8_FIELD;
        case 282: //rainFadeOut
            return CB_UINT8_FIELD;
        case 283: //boltFadeIn
            return CB_UINT8_FIELD;
        case 284: //boltFadeOut
            return CB_UINT8_FIELD;
        case 285: //boltFrequency
            return CB_UINT8_FIELD;
        case 286: //weatherType
            return CB_UINT8_TYPE_FIELD;
        case 287: //boltRed
            return CB_UINT8_FIELD;
        case 288: //boltGreen
            return CB_UINT8_FIELD;
        case 289: //boltBlue
            return CB_UINT8_FIELD;
        case 290: //sounds
            if(ListFieldID == 0) //sounds
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Sounds.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Sounds.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //sound
                    return CB_FORMID_FIELD;
                case 2: //type
                    return CB_UINT32_TYPE_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * WTHRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //sunriseImageSpace
            return &_0IAD.value;
        case 8: //dayImageSpace
            return &_1IAD.value;
        case 9: //sunsetImageSpace
            return &_2IAD.value;
        case 10: //nightImageSpace
            return &_3IAD.value;
        case 11: //unknown1ImageSpace
            return &_4IAD.value;
        case 12: //unknown2ImageSpace
            return &_5IAD.value;
        case 13: //cloudLayer0Path
            return DNAM.value;
        case 14: //cloudLayer1Path
            return CNAM.value;
        case 15: //cloudLayer2Path
            return ANAM.value;
        case 16: //cloudLayer3Path
            return BNAM.value;
        case 17: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 18: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 19: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 20: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 21: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 22: //unknown1
            return &LNAM.value;
        case 23: //layer0Speed
            return ONAM.IsLoaded() ? &ONAM->layer0Speed : NULL;
        case 24: //layer1Speed
            return ONAM.IsLoaded() ? &ONAM->layer1Speed : NULL;
        case 25: //layer2Speed
            return ONAM.IsLoaded() ? &ONAM->layer2Speed : NULL;
        case 26: //layer3Speed
            return ONAM.IsLoaded() ? &ONAM->layer3Speed : NULL;
        case 27: //pnam_p
            *FieldValues = PNAM.value;
            return NULL;
        case 28: //upperSky.rise.red
            return &NAM0.value.upperSky.rise.red;
        case 29: //upperSky.rise.green
            return &NAM0.value.upperSky.rise.green;
        case 30: //upperSky.rise.blue
            return &NAM0.value.upperSky.rise.blue;
        case 31: //upperSky.rise.unused1
            *FieldValues = &NAM0.value.upperSky.rise.unused1;
            return NULL;
        case 32: //upperSky.day.red
            return &NAM0.value.upperSky.day.red;
        case 33: //upperSky.day.green
            return &NAM0.value.upperSky.day.green;
        case 34: //upperSky.day.blue
            return &NAM0.value.upperSky.day.blue;
        case 35: //upperSky.day.unused1
            *FieldValues = &NAM0.value.upperSky.day.unused1;
            return NULL;
        case 36: //upperSky.set.red
            return &NAM0.value.upperSky.set.red;
        case 37: //upperSky.set.green
            return &NAM0.value.upperSky.set.green;
        case 38: //upperSky.set.blue
            return &NAM0.value.upperSky.set.blue;
        case 39: //upperSky.set.unused1
            *FieldValues = &NAM0.value.upperSky.set.unused1;
            return NULL;
        case 40: //upperSky.night.red
            return &NAM0.value.upperSky.night.red;
        case 41: //upperSky.night.green
            return &NAM0.value.upperSky.night.green;
        case 42: //upperSky.night.blue
            return &NAM0.value.upperSky.night.blue;
        case 43: //upperSky.night.unused1
            *FieldValues = &NAM0.value.upperSky.night.unused1;
            return NULL;
        case 44: //upperSky.noon.red
            return &NAM0.value.upperSky.noon.red;
        case 45: //upperSky.noon.green
            return &NAM0.value.upperSky.noon.green;
        case 46: //upperSky.noon.blue
            return &NAM0.value.upperSky.noon.blue;
        case 47: //upperSky.noon.unused1
            *FieldValues = &NAM0.value.upperSky.noon.unused1;
            return NULL;
        case 48: //upperSky.midnight.red
            return &NAM0.value.upperSky.midnight.red;
        case 49: //upperSky.midnight.green
            return &NAM0.value.upperSky.midnight.green;
        case 50: //upperSky.midnight.blue
            return &NAM0.value.upperSky.midnight.blue;
        case 51: //upperSky.midnight.unused1
            *FieldValues = &NAM0.value.upperSky.midnight.unused1;
            return NULL;
        case 52: //fog.rise.red
            return &NAM0.value.fog.rise.red;
        case 53: //fog.rise.green
            return &NAM0.value.fog.rise.green;
        case 54: //fog.rise.blue
            return &NAM0.value.fog.rise.blue;
        case 55: //fog.rise.unused1
            *FieldValues = &NAM0.value.fog.rise.unused1;
            return NULL;
        case 56: //fog.day.red
            return &NAM0.value.fog.day.red;
        case 57: //fog.day.green
            return &NAM0.value.fog.day.green;
        case 58: //fog.day.blue
            return &NAM0.value.fog.day.blue;
        case 59: //fog.day.unused1
            *FieldValues = &NAM0.value.fog.day.unused1;
            return NULL;
        case 60: //fog.set.red
            return &NAM0.value.fog.set.red;
        case 61: //fog.set.green
            return &NAM0.value.fog.set.green;
        case 62: //fog.set.blue
            return &NAM0.value.fog.set.blue;
        case 63: //fog.set.unused1
            *FieldValues = &NAM0.value.fog.set.unused1;
            return NULL;
        case 64: //fog.night.red
            return &NAM0.value.fog.night.red;
        case 65: //fog.night.green
            return &NAM0.value.fog.night.green;
        case 66: //fog.night.blue
            return &NAM0.value.fog.night.blue;
        case 67: //fog.night.unused1
            *FieldValues = &NAM0.value.fog.night.unused1;
            return NULL;
        case 68: //fog.noon.red
            return &NAM0.value.fog.noon.red;
        case 69: //fog.noon.green
            return &NAM0.value.fog.noon.green;
        case 70: //fog.noon.blue
            return &NAM0.value.fog.noon.blue;
        case 71: //fog.noon.unused1
            *FieldValues = &NAM0.value.fog.noon.unused1;
            return NULL;
        case 72: //fog.midnight.red
            return &NAM0.value.fog.midnight.red;
        case 73: //fog.midnight.green
            return &NAM0.value.fog.midnight.green;
        case 74: //fog.midnight.blue
            return &NAM0.value.fog.midnight.blue;
        case 75: //fog.midnight.unused1
            *FieldValues = &NAM0.value.fog.midnight.unused1;
            return NULL;
        case 76: //lowerClouds.rise.red
            return &NAM0.value.lowerClouds.rise.red;
        case 77: //lowerClouds.rise.green
            return &NAM0.value.lowerClouds.rise.green;
        case 78: //lowerClouds.rise.blue
            return &NAM0.value.lowerClouds.rise.blue;
        case 79: //lowerClouds.rise.unused1
            *FieldValues = &NAM0.value.lowerClouds.rise.unused1;
            return NULL;
        case 80: //lowerClouds.day.red
            return &NAM0.value.lowerClouds.day.red;
        case 81: //lowerClouds.day.green
            return &NAM0.value.lowerClouds.day.green;
        case 82: //lowerClouds.day.blue
            return &NAM0.value.lowerClouds.day.blue;
        case 83: //lowerClouds.day.unused1
            *FieldValues = &NAM0.value.lowerClouds.day.unused1;
            return NULL;
        case 84: //lowerClouds.set.red
            return &NAM0.value.lowerClouds.set.red;
        case 85: //lowerClouds.set.green
            return &NAM0.value.lowerClouds.set.green;
        case 86: //lowerClouds.set.blue
            return &NAM0.value.lowerClouds.set.blue;
        case 87: //lowerClouds.set.unused1
            *FieldValues = &NAM0.value.lowerClouds.set.unused1;
            return NULL;
        case 88: //lowerClouds.night.red
            return &NAM0.value.lowerClouds.night.red;
        case 89: //lowerClouds.night.green
            return &NAM0.value.lowerClouds.night.green;
        case 90: //lowerClouds.night.blue
            return &NAM0.value.lowerClouds.night.blue;
        case 91: //lowerClouds.night.unused1
            *FieldValues = &NAM0.value.lowerClouds.night.unused1;
            return NULL;
        case 92: //lowerClouds.noon.red
            return &NAM0.value.lowerClouds.noon.red;
        case 93: //lowerClouds.noon.green
            return &NAM0.value.lowerClouds.noon.green;
        case 94: //lowerClouds.noon.blue
            return &NAM0.value.lowerClouds.noon.blue;
        case 95: //lowerClouds.noon.unused1
            *FieldValues = &NAM0.value.lowerClouds.noon.unused1;
            return NULL;
        case 96: //lowerClouds.midnight.red
            return &NAM0.value.lowerClouds.midnight.red;
        case 97: //lowerClouds.midnight.green
            return &NAM0.value.lowerClouds.midnight.green;
        case 98: //lowerClouds.midnight.blue
            return &NAM0.value.lowerClouds.midnight.blue;
        case 99: //lowerClouds.midnight.unused1
            *FieldValues = &NAM0.value.lowerClouds.midnight.unused1;
            return NULL;
        case 100: //ambient.rise.red
            return &NAM0.value.ambient.rise.red;
        case 101: //ambient.rise.green
            return &NAM0.value.ambient.rise.green;
        case 102: //ambient.rise.blue
            return &NAM0.value.ambient.rise.blue;
        case 103: //ambient.rise.unused1
            *FieldValues = &NAM0.value.ambient.rise.unused1;
            return NULL;
        case 104: //ambient.day.red
            return &NAM0.value.ambient.day.red;
        case 105: //ambient.day.green
            return &NAM0.value.ambient.day.green;
        case 106: //ambient.day.blue
            return &NAM0.value.ambient.day.blue;
        case 107: //ambient.day.unused1
            *FieldValues = &NAM0.value.ambient.day.unused1;
            return NULL;
        case 108: //ambient.set.red
            return &NAM0.value.ambient.set.red;
        case 109: //ambient.set.green
            return &NAM0.value.ambient.set.green;
        case 110: //ambient.set.blue
            return &NAM0.value.ambient.set.blue;
        case 111: //ambient.set.unused1
            *FieldValues = &NAM0.value.ambient.set.unused1;
            return NULL;
        case 112: //ambient.night.red
            return &NAM0.value.ambient.night.red;
        case 113: //ambient.night.green
            return &NAM0.value.ambient.night.green;
        case 114: //ambient.night.blue
            return &NAM0.value.ambient.night.blue;
        case 115: //ambient.night.unused1
            *FieldValues = &NAM0.value.ambient.night.unused1;
            return NULL;
        case 116: //ambient.noon.red
            return &NAM0.value.ambient.noon.red;
        case 117: //ambient.noon.green
            return &NAM0.value.ambient.noon.green;
        case 118: //ambient.noon.blue
            return &NAM0.value.ambient.noon.blue;
        case 119: //ambient.noon.unused1
            *FieldValues = &NAM0.value.ambient.noon.unused1;
            return NULL;
        case 120: //ambient.midnight.red
            return &NAM0.value.ambient.midnight.red;
        case 121: //ambient.midnight.green
            return &NAM0.value.ambient.midnight.green;
        case 122: //ambient.midnight.blue
            return &NAM0.value.ambient.midnight.blue;
        case 123: //ambient.midnight.unused1
            *FieldValues = &NAM0.value.ambient.midnight.unused1;
            return NULL;
        case 124: //sunlight.rise.red
            return &NAM0.value.sunlight.rise.red;
        case 125: //sunlight.rise.green
            return &NAM0.value.sunlight.rise.green;
        case 126: //sunlight.rise.blue
            return &NAM0.value.sunlight.rise.blue;
        case 127: //sunlight.rise.unused1
            *FieldValues = &NAM0.value.sunlight.rise.unused1;
            return NULL;
        case 128: //sunlight.day.red
            return &NAM0.value.sunlight.day.red;
        case 129: //sunlight.day.green
            return &NAM0.value.sunlight.day.green;
        case 130: //sunlight.day.blue
            return &NAM0.value.sunlight.day.blue;
        case 131: //sunlight.day.unused1
            *FieldValues = &NAM0.value.sunlight.day.unused1;
            return NULL;
        case 132: //sunlight.set.red
            return &NAM0.value.sunlight.set.red;
        case 133: //sunlight.set.green
            return &NAM0.value.sunlight.set.green;
        case 134: //sunlight.set.blue
            return &NAM0.value.sunlight.set.blue;
        case 135: //sunlight.set.unused1
            *FieldValues = &NAM0.value.sunlight.set.unused1;
            return NULL;
        case 136: //sunlight.night.red
            return &NAM0.value.sunlight.night.red;
        case 137: //sunlight.night.green
            return &NAM0.value.sunlight.night.green;
        case 138: //sunlight.night.blue
            return &NAM0.value.sunlight.night.blue;
        case 139: //sunlight.night.unused1
            *FieldValues = &NAM0.value.sunlight.night.unused1;
            return NULL;
        case 140: //sunlight.noon.red
            return &NAM0.value.sunlight.noon.red;
        case 141: //sunlight.noon.green
            return &NAM0.value.sunlight.noon.green;
        case 142: //sunlight.noon.blue
            return &NAM0.value.sunlight.noon.blue;
        case 143: //sunlight.noon.unused1
            *FieldValues = &NAM0.value.sunlight.noon.unused1;
            return NULL;
        case 144: //sunlight.midnight.red
            return &NAM0.value.sunlight.midnight.red;
        case 145: //sunlight.midnight.green
            return &NAM0.value.sunlight.midnight.green;
        case 146: //sunlight.midnight.blue
            return &NAM0.value.sunlight.midnight.blue;
        case 147: //sunlight.midnight.unused1
            *FieldValues = &NAM0.value.sunlight.midnight.unused1;
            return NULL;
        case 148: //sun.rise.red
            return &NAM0.value.sun.rise.red;
        case 149: //sun.rise.green
            return &NAM0.value.sun.rise.green;
        case 150: //sun.rise.blue
            return &NAM0.value.sun.rise.blue;
        case 151: //sun.rise.unused1
            *FieldValues = &NAM0.value.sun.rise.unused1;
            return NULL;
        case 152: //sun.day.red
            return &NAM0.value.sun.day.red;
        case 153: //sun.day.green
            return &NAM0.value.sun.day.green;
        case 154: //sun.day.blue
            return &NAM0.value.sun.day.blue;
        case 155: //sun.day.unused1
            *FieldValues = &NAM0.value.sun.day.unused1;
            return NULL;
        case 156: //sun.set.red
            return &NAM0.value.sun.set.red;
        case 157: //sun.set.green
            return &NAM0.value.sun.set.green;
        case 158: //sun.set.blue
            return &NAM0.value.sun.set.blue;
        case 159: //sun.set.unused1
            *FieldValues = &NAM0.value.sun.set.unused1;
            return NULL;
        case 160: //sun.night.red
            return &NAM0.value.sun.night.red;
        case 161: //sun.night.green
            return &NAM0.value.sun.night.green;
        case 162: //sun.night.blue
            return &NAM0.value.sun.night.blue;
        case 163: //sun.night.unused1
            *FieldValues = &NAM0.value.sun.night.unused1;
            return NULL;
        case 164: //sun.noon.red
            return &NAM0.value.sun.noon.red;
        case 165: //sun.noon.green
            return &NAM0.value.sun.noon.green;
        case 166: //sun.noon.blue
            return &NAM0.value.sun.noon.blue;
        case 167: //sun.noon.unused1
            *FieldValues = &NAM0.value.sun.noon.unused1;
            return NULL;
        case 168: //sun.midnight.red
            return &NAM0.value.sun.midnight.red;
        case 169: //sun.midnight.green
            return &NAM0.value.sun.midnight.green;
        case 170: //sun.midnight.blue
            return &NAM0.value.sun.midnight.blue;
        case 171: //sun.midnight.unused1
            *FieldValues = &NAM0.value.sun.midnight.unused1;
            return NULL;
        case 172: //stars.rise.red
            return &NAM0.value.stars.rise.red;
        case 173: //stars.rise.green
            return &NAM0.value.stars.rise.green;
        case 174: //stars.rise.blue
            return &NAM0.value.stars.rise.blue;
        case 175: //stars.rise.unused1
            *FieldValues = &NAM0.value.stars.rise.unused1;
            return NULL;
        case 176: //stars.day.red
            return &NAM0.value.stars.day.red;
        case 177: //stars.day.green
            return &NAM0.value.stars.day.green;
        case 178: //stars.day.blue
            return &NAM0.value.stars.day.blue;
        case 179: //stars.day.unused1
            *FieldValues = &NAM0.value.stars.day.unused1;
            return NULL;
        case 180: //stars.set.red
            return &NAM0.value.stars.set.red;
        case 181: //stars.set.green
            return &NAM0.value.stars.set.green;
        case 182: //stars.set.blue
            return &NAM0.value.stars.set.blue;
        case 183: //stars.set.unused1
            *FieldValues = &NAM0.value.stars.set.unused1;
            return NULL;
        case 184: //stars.night.red
            return &NAM0.value.stars.night.red;
        case 185: //stars.night.green
            return &NAM0.value.stars.night.green;
        case 186: //stars.night.blue
            return &NAM0.value.stars.night.blue;
        case 187: //stars.night.unused1
            *FieldValues = &NAM0.value.stars.night.unused1;
            return NULL;
        case 188: //stars.noon.red
            return &NAM0.value.stars.noon.red;
        case 189: //stars.noon.green
            return &NAM0.value.stars.noon.green;
        case 190: //stars.noon.blue
            return &NAM0.value.stars.noon.blue;
        case 191: //stars.noon.unused1
            *FieldValues = &NAM0.value.stars.noon.unused1;
            return NULL;
        case 192: //stars.midnight.red
            return &NAM0.value.stars.midnight.red;
        case 193: //stars.midnight.green
            return &NAM0.value.stars.midnight.green;
        case 194: //stars.midnight.blue
            return &NAM0.value.stars.midnight.blue;
        case 195: //stars.midnight.unused1
            *FieldValues = &NAM0.value.stars.midnight.unused1;
            return NULL;
        case 196: //lowerSky.rise.red
            return &NAM0.value.lowerSky.rise.red;
        case 197: //lowerSky.rise.green
            return &NAM0.value.lowerSky.rise.green;
        case 198: //lowerSky.rise.blue
            return &NAM0.value.lowerSky.rise.blue;
        case 199: //lowerSky.rise.unused1
            *FieldValues = &NAM0.value.lowerSky.rise.unused1;
            return NULL;
        case 200: //lowerSky.day.red
            return &NAM0.value.lowerSky.day.red;
        case 201: //lowerSky.day.green
            return &NAM0.value.lowerSky.day.green;
        case 202: //lowerSky.day.blue
            return &NAM0.value.lowerSky.day.blue;
        case 203: //lowerSky.day.unused1
            *FieldValues = &NAM0.value.lowerSky.day.unused1;
            return NULL;
        case 204: //lowerSky.set.red
            return &NAM0.value.lowerSky.set.red;
        case 205: //lowerSky.set.green
            return &NAM0.value.lowerSky.set.green;
        case 206: //lowerSky.set.blue
            return &NAM0.value.lowerSky.set.blue;
        case 207: //lowerSky.set.unused1
            *FieldValues = &NAM0.value.lowerSky.set.unused1;
            return NULL;
        case 208: //lowerSky.night.red
            return &NAM0.value.lowerSky.night.red;
        case 209: //lowerSky.night.green
            return &NAM0.value.lowerSky.night.green;
        case 210: //lowerSky.night.blue
            return &NAM0.value.lowerSky.night.blue;
        case 211: //lowerSky.night.unused1
            *FieldValues = &NAM0.value.lowerSky.night.unused1;
            return NULL;
        case 212: //lowerSky.noon.red
            return &NAM0.value.lowerSky.noon.red;
        case 213: //lowerSky.noon.green
            return &NAM0.value.lowerSky.noon.green;
        case 214: //lowerSky.noon.blue
            return &NAM0.value.lowerSky.noon.blue;
        case 215: //lowerSky.noon.unused1
            *FieldValues = &NAM0.value.lowerSky.noon.unused1;
            return NULL;
        case 216: //lowerSky.midnight.red
            return &NAM0.value.lowerSky.midnight.red;
        case 217: //lowerSky.midnight.green
            return &NAM0.value.lowerSky.midnight.green;
        case 218: //lowerSky.midnight.blue
            return &NAM0.value.lowerSky.midnight.blue;
        case 219: //lowerSky.midnight.unused1
            *FieldValues = &NAM0.value.lowerSky.midnight.unused1;
            return NULL;
        case 220: //horizon.rise.red
            return &NAM0.value.horizon.rise.red;
        case 221: //horizon.rise.green
            return &NAM0.value.horizon.rise.green;
        case 222: //horizon.rise.blue
            return &NAM0.value.horizon.rise.blue;
        case 223: //horizon.rise.unused1
            *FieldValues = &NAM0.value.horizon.rise.unused1;
            return NULL;
        case 224: //horizon.day.red
            return &NAM0.value.horizon.day.red;
        case 225: //horizon.day.green
            return &NAM0.value.horizon.day.green;
        case 226: //horizon.day.blue
            return &NAM0.value.horizon.day.blue;
        case 227: //horizon.day.unused1
            *FieldValues = &NAM0.value.horizon.day.unused1;
            return NULL;
        case 228: //horizon.set.red
            return &NAM0.value.horizon.set.red;
        case 229: //horizon.set.green
            return &NAM0.value.horizon.set.green;
        case 230: //horizon.set.blue
            return &NAM0.value.horizon.set.blue;
        case 231: //horizon.set.unused1
            *FieldValues = &NAM0.value.horizon.set.unused1;
            return NULL;
        case 232: //horizon.night.red
            return &NAM0.value.horizon.night.red;
        case 233: //horizon.night.green
            return &NAM0.value.horizon.night.green;
        case 234: //horizon.night.blue
            return &NAM0.value.horizon.night.blue;
        case 235: //horizon.night.unused1
            *FieldValues = &NAM0.value.horizon.night.unused1;
            return NULL;
        case 236: //horizon.noon.red
            return &NAM0.value.horizon.noon.red;
        case 237: //horizon.noon.green
            return &NAM0.value.horizon.noon.green;
        case 238: //horizon.noon.blue
            return &NAM0.value.horizon.noon.blue;
        case 239: //horizon.noon.unused1
            *FieldValues = &NAM0.value.horizon.noon.unused1;
            return NULL;
        case 240: //horizon.midnight.red
            return &NAM0.value.horizon.midnight.red;
        case 241: //horizon.midnight.green
            return &NAM0.value.horizon.midnight.green;
        case 242: //horizon.midnight.blue
            return &NAM0.value.horizon.midnight.blue;
        case 243: //horizon.midnight.unused1
            *FieldValues = &NAM0.value.horizon.midnight.unused1;
            return NULL;
        case 244: //upperClouds.rise.red
            return &NAM0.value.upperClouds.rise.red;
        case 245: //upperClouds.rise.green
            return &NAM0.value.upperClouds.rise.green;
        case 246: //upperClouds.rise.blue
            return &NAM0.value.upperClouds.rise.blue;
        case 247: //upperClouds.rise.unused1
            *FieldValues = &NAM0.value.upperClouds.rise.unused1;
            return NULL;
        case 248: //upperClouds.day.red
            return &NAM0.value.upperClouds.day.red;
        case 249: //upperClouds.day.green
            return &NAM0.value.upperClouds.day.green;
        case 250: //upperClouds.day.blue
            return &NAM0.value.upperClouds.day.blue;
        case 251: //upperClouds.day.unused1
            *FieldValues = &NAM0.value.upperClouds.day.unused1;
            return NULL;
        case 252: //upperClouds.set.red
            return &NAM0.value.upperClouds.set.red;
        case 253: //upperClouds.set.green
            return &NAM0.value.upperClouds.set.green;
        case 254: //upperClouds.set.blue
            return &NAM0.value.upperClouds.set.blue;
        case 255: //upperClouds.set.unused1
            *FieldValues = &NAM0.value.upperClouds.set.unused1;
            return NULL;
        case 256: //upperClouds.night.red
            return &NAM0.value.upperClouds.night.red;
        case 257: //upperClouds.night.green
            return &NAM0.value.upperClouds.night.green;
        case 258: //upperClouds.night.blue
            return &NAM0.value.upperClouds.night.blue;
        case 259: //upperClouds.night.unused1
            *FieldValues = &NAM0.value.upperClouds.night.unused1;
            return NULL;
        case 260: //upperClouds.noon.red
            return &NAM0.value.upperClouds.noon.red;
        case 261: //upperClouds.noon.green
            return &NAM0.value.upperClouds.noon.green;
        case 262: //upperClouds.noon.blue
            return &NAM0.value.upperClouds.noon.blue;
        case 263: //upperClouds.noon.unused1
            *FieldValues = &NAM0.value.upperClouds.noon.unused1;
            return NULL;
        case 264: //upperClouds.midnight.red
            return &NAM0.value.upperClouds.midnight.red;
        case 265: //upperClouds.midnight.green
            return &NAM0.value.upperClouds.midnight.green;
        case 266: //upperClouds.midnight.blue
            return &NAM0.value.upperClouds.midnight.blue;
        case 267: //upperClouds.midnight.unused1
            *FieldValues = &NAM0.value.upperClouds.midnight.unused1;
            return NULL;
        case 268: //fogDayNear
            return &FNAM.value.fogDayNear;
        case 269: //fogDayFar
            return &FNAM.value.fogDayFar;
        case 270: //fogNightNear
            return &FNAM.value.fogNightNear;
        case 271: //fogNightFar
            return &FNAM.value.fogNightFar;
        case 272: //fogDayPower
            return &FNAM.value.fogDayPower;
        case 273: //fogNightPower
            return &FNAM.value.fogNightPower;
        case 274: //inam_p
            *FieldValues = INAM.value;
            return NULL;
        case 275: //windSpeed
            return &DATA.value.windSpeed;
        case 276: //lowerCloudSpeed
            return &DATA.value.lowerCloudSpeed;
        case 277: //upperCloudSpeed
            return &DATA.value.upperCloudSpeed;
        case 278: //transDelta
            return &DATA.value.transDelta;
        case 279: //sunGlare
            return &DATA.value.sunGlare;
        case 280: //sunDamage
            return &DATA.value.sunDamage;
        case 281: //rainFadeIn
            return &DATA.value.rainFadeIn;
        case 282: //rainFadeOut
            return &DATA.value.rainFadeOut;
        case 283: //boltFadeIn
            return &DATA.value.boltFadeIn;
        case 284: //boltFadeOut
            return &DATA.value.boltFadeOut;
        case 285: //boltFrequency
            return &DATA.value.boltFrequency;
        case 286: //weatherType
            return &DATA.value.weatherType;
        case 287: //boltRed
            return &DATA.value.boltRed;
        case 288: //boltGreen
            return &DATA.value.boltGreen;
        case 289: //boltBlue
            return &DATA.value.boltBlue;
        case 290: //sounds
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

bool WTHRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //sunriseImageSpace
            _0IAD.value = *(FORMID *)FieldValue;
            return true;
        case 8: //dayImageSpace
            _1IAD.value = *(FORMID *)FieldValue;
            return true;
        case 9: //sunsetImageSpace
            _2IAD.value = *(FORMID *)FieldValue;
            return true;
        case 10: //nightImageSpace
            _3IAD.value = *(FORMID *)FieldValue;
            return true;
        case 11: //unknown1ImageSpace
            _4IAD.value = *(FORMID *)FieldValue;
            return true;
        case 12: //unknown2ImageSpace
            _5IAD.value = *(FORMID *)FieldValue;
            return true;
        case 13: //cloudLayer0Path
            DNAM.Copy((char *)FieldValue);
            break;
        case 14: //cloudLayer1Path
            CNAM.Copy((char *)FieldValue);
            break;
        case 15: //cloudLayer2Path
            ANAM.Copy((char *)FieldValue);
            break;
        case 16: //cloudLayer3Path
            BNAM.Copy((char *)FieldValue);
            break;
        case 17: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 18: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 19: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 21: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 22: //unknown1
            LNAM.value = *(uint32_t *)FieldValue;
            break;
        case 23: //layer0Speed
            ONAM.Load();
            ONAM->layer0Speed = *(uint8_t *)FieldValue;
            break;
        case 24: //layer1Speed
            ONAM.Load();
            ONAM->layer1Speed = *(uint8_t *)FieldValue;
            break;
        case 25: //layer2Speed
            ONAM.Load();
            ONAM->layer2Speed = *(uint8_t *)FieldValue;
            break;
        case 26: //layer3Speed
            ONAM.Load();
            ONAM->layer3Speed = *(uint8_t *)FieldValue;
            break;
        case 27: //PNAM
            PNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 28: //upperSky.rise.red
            NAM0.value.upperSky.rise.red = *(uint8_t *)FieldValue;
            break;
        case 29: //upperSky.rise.green
            NAM0.value.upperSky.rise.green = *(uint8_t *)FieldValue;
            break;
        case 30: //upperSky.rise.blue
            NAM0.value.upperSky.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 31: //upperSky.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 32: //upperSky.day.red
            NAM0.value.upperSky.day.red = *(uint8_t *)FieldValue;
            break;
        case 33: //upperSky.day.green
            NAM0.value.upperSky.day.green = *(uint8_t *)FieldValue;
            break;
        case 34: //upperSky.day.blue
            NAM0.value.upperSky.day.blue = *(uint8_t *)FieldValue;
            break;
        case 35: //upperSky.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 36: //upperSky.set.red
            NAM0.value.upperSky.set.red = *(uint8_t *)FieldValue;
            break;
        case 37: //upperSky.set.green
            NAM0.value.upperSky.set.green = *(uint8_t *)FieldValue;
            break;
        case 38: //upperSky.set.blue
            NAM0.value.upperSky.set.blue = *(uint8_t *)FieldValue;
            break;
        case 39: //upperSky.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 40: //upperSky.night.red
            NAM0.value.upperSky.night.red = *(uint8_t *)FieldValue;
            break;
        case 41: //upperSky.night.green
            NAM0.value.upperSky.night.green = *(uint8_t *)FieldValue;
            break;
        case 42: //upperSky.night.blue
            NAM0.value.upperSky.night.blue = *(uint8_t *)FieldValue;
            break;
        case 43: //upperSky.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 44: //upperSky.noon.red
            NAM0.value.upperSky.noon.red = *(uint8_t *)FieldValue;
            break;
        case 45: //upperSky.noon.green
            NAM0.value.upperSky.noon.green = *(uint8_t *)FieldValue;
            break;
        case 46: //upperSky.noon.blue
            NAM0.value.upperSky.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 47: //upperSky.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 48: //upperSky.midnight.red
            NAM0.value.upperSky.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 49: //upperSky.midnight.green
            NAM0.value.upperSky.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 50: //upperSky.midnight.blue
            NAM0.value.upperSky.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 51: //upperSky.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperSky.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 52: //fog.rise.red
            NAM0.value.fog.rise.red = *(uint8_t *)FieldValue;
            break;
        case 53: //fog.rise.green
            NAM0.value.fog.rise.green = *(uint8_t *)FieldValue;
            break;
        case 54: //fog.rise.blue
            NAM0.value.fog.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 55: //fog.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 56: //fog.day.red
            NAM0.value.fog.day.red = *(uint8_t *)FieldValue;
            break;
        case 57: //fog.day.green
            NAM0.value.fog.day.green = *(uint8_t *)FieldValue;
            break;
        case 58: //fog.day.blue
            NAM0.value.fog.day.blue = *(uint8_t *)FieldValue;
            break;
        case 59: //fog.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 60: //fog.set.red
            NAM0.value.fog.set.red = *(uint8_t *)FieldValue;
            break;
        case 61: //fog.set.green
            NAM0.value.fog.set.green = *(uint8_t *)FieldValue;
            break;
        case 62: //fog.set.blue
            NAM0.value.fog.set.blue = *(uint8_t *)FieldValue;
            break;
        case 63: //fog.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 64: //fog.night.red
            NAM0.value.fog.night.red = *(uint8_t *)FieldValue;
            break;
        case 65: //fog.night.green
            NAM0.value.fog.night.green = *(uint8_t *)FieldValue;
            break;
        case 66: //fog.night.blue
            NAM0.value.fog.night.blue = *(uint8_t *)FieldValue;
            break;
        case 67: //fog.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 68: //fog.noon.red
            NAM0.value.fog.noon.red = *(uint8_t *)FieldValue;
            break;
        case 69: //fog.noon.green
            NAM0.value.fog.noon.green = *(uint8_t *)FieldValue;
            break;
        case 70: //fog.noon.blue
            NAM0.value.fog.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 71: //fog.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 72: //fog.midnight.red
            NAM0.value.fog.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 73: //fog.midnight.green
            NAM0.value.fog.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 74: //fog.midnight.blue
            NAM0.value.fog.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 75: //fog.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.fog.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 76: //lowerClouds.rise.red
            NAM0.value.lowerClouds.rise.red = *(uint8_t *)FieldValue;
            break;
        case 77: //lowerClouds.rise.green
            NAM0.value.lowerClouds.rise.green = *(uint8_t *)FieldValue;
            break;
        case 78: //lowerClouds.rise.blue
            NAM0.value.lowerClouds.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 79: //lowerClouds.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 80: //lowerClouds.day.red
            NAM0.value.lowerClouds.day.red = *(uint8_t *)FieldValue;
            break;
        case 81: //lowerClouds.day.green
            NAM0.value.lowerClouds.day.green = *(uint8_t *)FieldValue;
            break;
        case 82: //lowerClouds.day.blue
            NAM0.value.lowerClouds.day.blue = *(uint8_t *)FieldValue;
            break;
        case 83: //lowerClouds.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 84: //lowerClouds.set.red
            NAM0.value.lowerClouds.set.red = *(uint8_t *)FieldValue;
            break;
        case 85: //lowerClouds.set.green
            NAM0.value.lowerClouds.set.green = *(uint8_t *)FieldValue;
            break;
        case 86: //lowerClouds.set.blue
            NAM0.value.lowerClouds.set.blue = *(uint8_t *)FieldValue;
            break;
        case 87: //lowerClouds.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 88: //lowerClouds.night.red
            NAM0.value.lowerClouds.night.red = *(uint8_t *)FieldValue;
            break;
        case 89: //lowerClouds.night.green
            NAM0.value.lowerClouds.night.green = *(uint8_t *)FieldValue;
            break;
        case 90: //lowerClouds.night.blue
            NAM0.value.lowerClouds.night.blue = *(uint8_t *)FieldValue;
            break;
        case 91: //lowerClouds.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 92: //lowerClouds.noon.red
            NAM0.value.lowerClouds.noon.red = *(uint8_t *)FieldValue;
            break;
        case 93: //lowerClouds.noon.green
            NAM0.value.lowerClouds.noon.green = *(uint8_t *)FieldValue;
            break;
        case 94: //lowerClouds.noon.blue
            NAM0.value.lowerClouds.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 95: //lowerClouds.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 96: //lowerClouds.midnight.red
            NAM0.value.lowerClouds.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 97: //lowerClouds.midnight.green
            NAM0.value.lowerClouds.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 98: //lowerClouds.midnight.blue
            NAM0.value.lowerClouds.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 99: //lowerClouds.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerClouds.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 100: //ambient.rise.red
            NAM0.value.ambient.rise.red = *(uint8_t *)FieldValue;
            break;
        case 101: //ambient.rise.green
            NAM0.value.ambient.rise.green = *(uint8_t *)FieldValue;
            break;
        case 102: //ambient.rise.blue
            NAM0.value.ambient.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 103: //ambient.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 104: //ambient.day.red
            NAM0.value.ambient.day.red = *(uint8_t *)FieldValue;
            break;
        case 105: //ambient.day.green
            NAM0.value.ambient.day.green = *(uint8_t *)FieldValue;
            break;
        case 106: //ambient.day.blue
            NAM0.value.ambient.day.blue = *(uint8_t *)FieldValue;
            break;
        case 107: //ambient.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 108: //ambient.set.red
            NAM0.value.ambient.set.red = *(uint8_t *)FieldValue;
            break;
        case 109: //ambient.set.green
            NAM0.value.ambient.set.green = *(uint8_t *)FieldValue;
            break;
        case 110: //ambient.set.blue
            NAM0.value.ambient.set.blue = *(uint8_t *)FieldValue;
            break;
        case 111: //ambient.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 112: //ambient.night.red
            NAM0.value.ambient.night.red = *(uint8_t *)FieldValue;
            break;
        case 113: //ambient.night.green
            NAM0.value.ambient.night.green = *(uint8_t *)FieldValue;
            break;
        case 114: //ambient.night.blue
            NAM0.value.ambient.night.blue = *(uint8_t *)FieldValue;
            break;
        case 115: //ambient.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 116: //ambient.noon.red
            NAM0.value.ambient.noon.red = *(uint8_t *)FieldValue;
            break;
        case 117: //ambient.noon.green
            NAM0.value.ambient.noon.green = *(uint8_t *)FieldValue;
            break;
        case 118: //ambient.noon.blue
            NAM0.value.ambient.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 119: //ambient.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 120: //ambient.midnight.red
            NAM0.value.ambient.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 121: //ambient.midnight.green
            NAM0.value.ambient.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 122: //ambient.midnight.blue
            NAM0.value.ambient.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 123: //ambient.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.ambient.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 124: //sunlight.rise.red
            NAM0.value.sunlight.rise.red = *(uint8_t *)FieldValue;
            break;
        case 125: //sunlight.rise.green
            NAM0.value.sunlight.rise.green = *(uint8_t *)FieldValue;
            break;
        case 126: //sunlight.rise.blue
            NAM0.value.sunlight.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 127: //sunlight.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 128: //sunlight.day.red
            NAM0.value.sunlight.day.red = *(uint8_t *)FieldValue;
            break;
        case 129: //sunlight.day.green
            NAM0.value.sunlight.day.green = *(uint8_t *)FieldValue;
            break;
        case 130: //sunlight.day.blue
            NAM0.value.sunlight.day.blue = *(uint8_t *)FieldValue;
            break;
        case 131: //sunlight.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 132: //sunlight.set.red
            NAM0.value.sunlight.set.red = *(uint8_t *)FieldValue;
            break;
        case 133: //sunlight.set.green
            NAM0.value.sunlight.set.green = *(uint8_t *)FieldValue;
            break;
        case 134: //sunlight.set.blue
            NAM0.value.sunlight.set.blue = *(uint8_t *)FieldValue;
            break;
        case 135: //sunlight.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 136: //sunlight.night.red
            NAM0.value.sunlight.night.red = *(uint8_t *)FieldValue;
            break;
        case 137: //sunlight.night.green
            NAM0.value.sunlight.night.green = *(uint8_t *)FieldValue;
            break;
        case 138: //sunlight.night.blue
            NAM0.value.sunlight.night.blue = *(uint8_t *)FieldValue;
            break;
        case 139: //sunlight.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 140: //sunlight.noon.red
            NAM0.value.sunlight.noon.red = *(uint8_t *)FieldValue;
            break;
        case 141: //sunlight.noon.green
            NAM0.value.sunlight.noon.green = *(uint8_t *)FieldValue;
            break;
        case 142: //sunlight.noon.blue
            NAM0.value.sunlight.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 143: //sunlight.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 144: //sunlight.midnight.red
            NAM0.value.sunlight.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 145: //sunlight.midnight.green
            NAM0.value.sunlight.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 146: //sunlight.midnight.blue
            NAM0.value.sunlight.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 147: //sunlight.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sunlight.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 148: //sun.rise.red
            NAM0.value.sun.rise.red = *(uint8_t *)FieldValue;
            break;
        case 149: //sun.rise.green
            NAM0.value.sun.rise.green = *(uint8_t *)FieldValue;
            break;
        case 150: //sun.rise.blue
            NAM0.value.sun.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 151: //sun.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 152: //sun.day.red
            NAM0.value.sun.day.red = *(uint8_t *)FieldValue;
            break;
        case 153: //sun.day.green
            NAM0.value.sun.day.green = *(uint8_t *)FieldValue;
            break;
        case 154: //sun.day.blue
            NAM0.value.sun.day.blue = *(uint8_t *)FieldValue;
            break;
        case 155: //sun.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 156: //sun.set.red
            NAM0.value.sun.set.red = *(uint8_t *)FieldValue;
            break;
        case 157: //sun.set.green
            NAM0.value.sun.set.green = *(uint8_t *)FieldValue;
            break;
        case 158: //sun.set.blue
            NAM0.value.sun.set.blue = *(uint8_t *)FieldValue;
            break;
        case 159: //sun.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 160: //sun.night.red
            NAM0.value.sun.night.red = *(uint8_t *)FieldValue;
            break;
        case 161: //sun.night.green
            NAM0.value.sun.night.green = *(uint8_t *)FieldValue;
            break;
        case 162: //sun.night.blue
            NAM0.value.sun.night.blue = *(uint8_t *)FieldValue;
            break;
        case 163: //sun.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 164: //sun.noon.red
            NAM0.value.sun.noon.red = *(uint8_t *)FieldValue;
            break;
        case 165: //sun.noon.green
            NAM0.value.sun.noon.green = *(uint8_t *)FieldValue;
            break;
        case 166: //sun.noon.blue
            NAM0.value.sun.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 167: //sun.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 168: //sun.midnight.red
            NAM0.value.sun.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 169: //sun.midnight.green
            NAM0.value.sun.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 170: //sun.midnight.blue
            NAM0.value.sun.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 171: //sun.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.sun.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 172: //stars.rise.red
            NAM0.value.stars.rise.red = *(uint8_t *)FieldValue;
            break;
        case 173: //stars.rise.green
            NAM0.value.stars.rise.green = *(uint8_t *)FieldValue;
            break;
        case 174: //stars.rise.blue
            NAM0.value.stars.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 175: //stars.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 176: //stars.day.red
            NAM0.value.stars.day.red = *(uint8_t *)FieldValue;
            break;
        case 177: //stars.day.green
            NAM0.value.stars.day.green = *(uint8_t *)FieldValue;
            break;
        case 178: //stars.day.blue
            NAM0.value.stars.day.blue = *(uint8_t *)FieldValue;
            break;
        case 179: //stars.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 180: //stars.set.red
            NAM0.value.stars.set.red = *(uint8_t *)FieldValue;
            break;
        case 181: //stars.set.green
            NAM0.value.stars.set.green = *(uint8_t *)FieldValue;
            break;
        case 182: //stars.set.blue
            NAM0.value.stars.set.blue = *(uint8_t *)FieldValue;
            break;
        case 183: //stars.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 184: //stars.night.red
            NAM0.value.stars.night.red = *(uint8_t *)FieldValue;
            break;
        case 185: //stars.night.green
            NAM0.value.stars.night.green = *(uint8_t *)FieldValue;
            break;
        case 186: //stars.night.blue
            NAM0.value.stars.night.blue = *(uint8_t *)FieldValue;
            break;
        case 187: //stars.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 188: //stars.noon.red
            NAM0.value.stars.noon.red = *(uint8_t *)FieldValue;
            break;
        case 189: //stars.noon.green
            NAM0.value.stars.noon.green = *(uint8_t *)FieldValue;
            break;
        case 190: //stars.noon.blue
            NAM0.value.stars.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 191: //stars.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 192: //stars.midnight.red
            NAM0.value.stars.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 193: //stars.midnight.green
            NAM0.value.stars.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 194: //stars.midnight.blue
            NAM0.value.stars.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 195: //stars.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.stars.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 196: //lowerSky.rise.red
            NAM0.value.lowerSky.rise.red = *(uint8_t *)FieldValue;
            break;
        case 197: //lowerSky.rise.green
            NAM0.value.lowerSky.rise.green = *(uint8_t *)FieldValue;
            break;
        case 198: //lowerSky.rise.blue
            NAM0.value.lowerSky.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 199: //lowerSky.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 200: //lowerSky.day.red
            NAM0.value.lowerSky.day.red = *(uint8_t *)FieldValue;
            break;
        case 201: //lowerSky.day.green
            NAM0.value.lowerSky.day.green = *(uint8_t *)FieldValue;
            break;
        case 202: //lowerSky.day.blue
            NAM0.value.lowerSky.day.blue = *(uint8_t *)FieldValue;
            break;
        case 203: //lowerSky.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 204: //lowerSky.set.red
            NAM0.value.lowerSky.set.red = *(uint8_t *)FieldValue;
            break;
        case 205: //lowerSky.set.green
            NAM0.value.lowerSky.set.green = *(uint8_t *)FieldValue;
            break;
        case 206: //lowerSky.set.blue
            NAM0.value.lowerSky.set.blue = *(uint8_t *)FieldValue;
            break;
        case 207: //lowerSky.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 208: //lowerSky.night.red
            NAM0.value.lowerSky.night.red = *(uint8_t *)FieldValue;
            break;
        case 209: //lowerSky.night.green
            NAM0.value.lowerSky.night.green = *(uint8_t *)FieldValue;
            break;
        case 210: //lowerSky.night.blue
            NAM0.value.lowerSky.night.blue = *(uint8_t *)FieldValue;
            break;
        case 211: //lowerSky.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 212: //lowerSky.noon.red
            NAM0.value.lowerSky.noon.red = *(uint8_t *)FieldValue;
            break;
        case 213: //lowerSky.noon.green
            NAM0.value.lowerSky.noon.green = *(uint8_t *)FieldValue;
            break;
        case 214: //lowerSky.noon.blue
            NAM0.value.lowerSky.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 215: //lowerSky.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 216: //lowerSky.midnight.red
            NAM0.value.lowerSky.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 217: //lowerSky.midnight.green
            NAM0.value.lowerSky.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 218: //lowerSky.midnight.blue
            NAM0.value.lowerSky.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 219: //lowerSky.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.lowerSky.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 220: //horizon.rise.red
            NAM0.value.horizon.rise.red = *(uint8_t *)FieldValue;
            break;
        case 221: //horizon.rise.green
            NAM0.value.horizon.rise.green = *(uint8_t *)FieldValue;
            break;
        case 222: //horizon.rise.blue
            NAM0.value.horizon.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 223: //horizon.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 224: //horizon.day.red
            NAM0.value.horizon.day.red = *(uint8_t *)FieldValue;
            break;
        case 225: //horizon.day.green
            NAM0.value.horizon.day.green = *(uint8_t *)FieldValue;
            break;
        case 226: //horizon.day.blue
            NAM0.value.horizon.day.blue = *(uint8_t *)FieldValue;
            break;
        case 227: //horizon.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 228: //horizon.set.red
            NAM0.value.horizon.set.red = *(uint8_t *)FieldValue;
            break;
        case 229: //horizon.set.green
            NAM0.value.horizon.set.green = *(uint8_t *)FieldValue;
            break;
        case 230: //horizon.set.blue
            NAM0.value.horizon.set.blue = *(uint8_t *)FieldValue;
            break;
        case 231: //horizon.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 232: //horizon.night.red
            NAM0.value.horizon.night.red = *(uint8_t *)FieldValue;
            break;
        case 233: //horizon.night.green
            NAM0.value.horizon.night.green = *(uint8_t *)FieldValue;
            break;
        case 234: //horizon.night.blue
            NAM0.value.horizon.night.blue = *(uint8_t *)FieldValue;
            break;
        case 235: //horizon.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 236: //horizon.noon.red
            NAM0.value.horizon.noon.red = *(uint8_t *)FieldValue;
            break;
        case 237: //horizon.noon.green
            NAM0.value.horizon.noon.green = *(uint8_t *)FieldValue;
            break;
        case 238: //horizon.noon.blue
            NAM0.value.horizon.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 239: //horizon.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 240: //horizon.midnight.red
            NAM0.value.horizon.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 241: //horizon.midnight.green
            NAM0.value.horizon.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 242: //horizon.midnight.blue
            NAM0.value.horizon.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 243: //horizon.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.horizon.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 244: //upperClouds.rise.red
            NAM0.value.upperClouds.rise.red = *(uint8_t *)FieldValue;
            break;
        case 245: //upperClouds.rise.green
            NAM0.value.upperClouds.rise.green = *(uint8_t *)FieldValue;
            break;
        case 246: //upperClouds.rise.blue
            NAM0.value.upperClouds.rise.blue = *(uint8_t *)FieldValue;
            break;
        case 247: //upperClouds.rise.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.rise.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 248: //upperClouds.day.red
            NAM0.value.upperClouds.day.red = *(uint8_t *)FieldValue;
            break;
        case 249: //upperClouds.day.green
            NAM0.value.upperClouds.day.green = *(uint8_t *)FieldValue;
            break;
        case 250: //upperClouds.day.blue
            NAM0.value.upperClouds.day.blue = *(uint8_t *)FieldValue;
            break;
        case 251: //upperClouds.day.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.day.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 252: //upperClouds.set.red
            NAM0.value.upperClouds.set.red = *(uint8_t *)FieldValue;
            break;
        case 253: //upperClouds.set.green
            NAM0.value.upperClouds.set.green = *(uint8_t *)FieldValue;
            break;
        case 254: //upperClouds.set.blue
            NAM0.value.upperClouds.set.blue = *(uint8_t *)FieldValue;
            break;
        case 255: //upperClouds.set.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.set.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 256: //upperClouds.night.red
            NAM0.value.upperClouds.night.red = *(uint8_t *)FieldValue;
            break;
        case 257: //upperClouds.night.green
            NAM0.value.upperClouds.night.green = *(uint8_t *)FieldValue;
            break;
        case 258: //upperClouds.night.blue
            NAM0.value.upperClouds.night.blue = *(uint8_t *)FieldValue;
            break;
        case 259: //upperClouds.night.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.night.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 260: //upperClouds.noon.red
            NAM0.value.upperClouds.noon.red = *(uint8_t *)FieldValue;
            break;
        case 261: //upperClouds.noon.green
            NAM0.value.upperClouds.noon.green = *(uint8_t *)FieldValue;
            break;
        case 262: //upperClouds.noon.blue
            NAM0.value.upperClouds.noon.blue = *(uint8_t *)FieldValue;
            break;
        case 263: //upperClouds.noon.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.noon.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 264: //upperClouds.midnight.red
            NAM0.value.upperClouds.midnight.red = *(uint8_t *)FieldValue;
            break;
        case 265: //upperClouds.midnight.green
            NAM0.value.upperClouds.midnight.green = *(uint8_t *)FieldValue;
            break;
        case 266: //upperClouds.midnight.blue
            NAM0.value.upperClouds.midnight.blue = *(uint8_t *)FieldValue;
            break;
        case 267: //upperClouds.midnight.unused1
            if(ArraySize != 1)
                break;
            NAM0.value.upperClouds.midnight.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 268: //fogDayNear
            FNAM.value.fogDayNear = *(float *)FieldValue;
            break;
        case 269: //fogDayFar
            FNAM.value.fogDayFar = *(float *)FieldValue;
            break;
        case 270: //fogNightNear
            FNAM.value.fogNightNear = *(float *)FieldValue;
            break;
        case 271: //fogNightFar
            FNAM.value.fogNightFar = *(float *)FieldValue;
            break;
        case 272: //fogDayPower
            FNAM.value.fogDayPower = *(float *)FieldValue;
            break;
        case 273: //fogNightPower
            FNAM.value.fogNightPower = *(float *)FieldValue;
            break;
        case 274: //INAM
            INAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 275: //windSpeed
            DATA.value.windSpeed = *(uint8_t *)FieldValue;
            break;
        case 276: //lowerCloudSpeed
            DATA.value.lowerCloudSpeed = *(uint8_t *)FieldValue;
            break;
        case 277: //upperCloudSpeed
            DATA.value.upperCloudSpeed = *(uint8_t *)FieldValue;
            break;
        case 278: //transDelta
            DATA.value.transDelta = *(uint8_t *)FieldValue;
            break;
        case 279: //sunGlare
            DATA.value.sunGlare = *(uint8_t *)FieldValue;
            break;
        case 280: //sunDamage
            DATA.value.sunDamage = *(uint8_t *)FieldValue;
            break;
        case 281: //rainFadeIn
            DATA.value.rainFadeIn = *(uint8_t *)FieldValue;
            break;
        case 282: //rainFadeOut
            DATA.value.rainFadeOut = *(uint8_t *)FieldValue;
            break;
        case 283: //boltFadeIn
            DATA.value.boltFadeIn = *(uint8_t *)FieldValue;
            break;
        case 284: //boltFadeOut
            DATA.value.boltFadeOut = *(uint8_t *)FieldValue;
            break;
        case 285: //boltFrequency
            DATA.value.boltFrequency = *(uint8_t *)FieldValue;
            break;
        case 286: //weatherType
            DATA.value.weatherType = *(uint8_t *)FieldValue;
            break;
        case 287: //boltRed
            DATA.value.boltRed = *(uint8_t *)FieldValue;
            break;
        case 288: //boltGreen
            DATA.value.boltGreen = *(uint8_t *)FieldValue;
            break;
        case 289: //boltBlue
            DATA.value.boltBlue = *(uint8_t *)FieldValue;
            break;
        case 290: //sounds
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
                    Sounds.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
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
    WTHRDATA defaultDATA;
    WTHRColors defaultColors;
    WTHRSNAM defaultSNAM;
    FNVMODS defaultMODS;
    WTHRONAM defaultONAM;
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
        case 7: //sunriseImageSpace
            _0IAD.Unload();
            return;
        case 8: //dayImageSpace
            _1IAD.Unload();
            return;
        case 9: //sunsetImageSpace
            _2IAD.Unload();
            return;
        case 10: //nightImageSpace
            _3IAD.Unload();
            return;
        case 11: //unknown1ImageSpace
            _4IAD.Unload();
            return;
        case 12: //unknown2ImageSpace
            _5IAD.Unload();
            return;
        case 13: //cloudLayer0Path
            DNAM.Unload();
            return;
        case 14: //cloudLayer1Path
            CNAM.Unload();
            return;
        case 15: //cloudLayer2Path
            ANAM.Unload();
            return;
        case 16: //cloudLayer3Path
            BNAM.Unload();
            return;
        case 17: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 18: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 19: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 20: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 21: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 22: //unknown1
            LNAM.Unload();
            return;
        case 23: //layer0Speed
            if(ONAM.IsLoaded())
                ONAM->layer0Speed = defaultONAM.layer0Speed;
            return;
        case 24: //layer1Speed
            if(ONAM.IsLoaded())
                ONAM->layer1Speed = defaultONAM.layer1Speed;
            return;
        case 25: //layer2Speed
            if(ONAM.IsLoaded())
                ONAM->layer2Speed = defaultONAM.layer2Speed;
            return;
        case 26: //layer3Speed
            if(ONAM.IsLoaded())
                ONAM->layer3Speed = defaultONAM.layer3Speed;
            return;
        case 27: //PNAM
            PNAM.Unload();
            return;
        case 28: //upperSky.rise.red
            NAM0.value.upperSky.rise.red = defaultCLR.red;
            return;
        case 29: //upperSky.rise.green
            NAM0.value.upperSky.rise.green = defaultCLR.green;
            return;
        case 30: //upperSky.rise.blue
            NAM0.value.upperSky.rise.blue = defaultCLR.blue;
            return;
        case 31: //upperSky.rise.unused1
            NAM0.value.upperSky.rise.unused1 = defaultCLR.unused1;
            return;
        case 32: //upperSky.day.red
            NAM0.value.upperSky.day.red = defaultCLR.red;
            return;
        case 33: //upperSky.day.green
            NAM0.value.upperSky.day.green = defaultCLR.green;
            return;
        case 34: //upperSky.day.blue
            NAM0.value.upperSky.day.blue = defaultCLR.blue;
            return;
        case 35: //upperSky.day.unused1
            NAM0.value.upperSky.day.unused1 = defaultCLR.unused1;
            return;
        case 36: //upperSky.set.red
            NAM0.value.upperSky.set.red = defaultCLR.red;
            return;
        case 37: //upperSky.set.green
            NAM0.value.upperSky.set.green = defaultCLR.green;
            return;
        case 38: //upperSky.set.blue
            NAM0.value.upperSky.set.blue = defaultCLR.blue;
            return;
        case 39: //upperSky.set.unused1
            NAM0.value.upperSky.set.unused1 = defaultCLR.unused1;
            return;
        case 40: //upperSky.night.red
            NAM0.value.upperSky.night.red = defaultCLR.red;
            return;
        case 41: //upperSky.night.green
            NAM0.value.upperSky.night.green = defaultCLR.green;
            return;
        case 42: //upperSky.night.blue
            NAM0.value.upperSky.night.blue = defaultCLR.blue;
            return;
        case 43: //upperSky.night.unused1
            NAM0.value.upperSky.night.unused1 = defaultCLR.unused1;
            return;
        case 44: //upperSky.noon.red
            NAM0.value.upperSky.noon.red = defaultCLR.red;
            return;
        case 45: //upperSky.noon.green
            NAM0.value.upperSky.noon.green = defaultCLR.green;
            return;
        case 46: //upperSky.noon.blue
            NAM0.value.upperSky.noon.blue = defaultCLR.blue;
            return;
        case 47: //upperSky.noon.unused1
            NAM0.value.upperSky.noon.unused1 = defaultCLR.unused1;
            return;
        case 48: //upperSky.midnight.red
            NAM0.value.upperSky.midnight.red = defaultCLR.red;
            return;
        case 49: //upperSky.midnight.green
            NAM0.value.upperSky.midnight.green = defaultCLR.green;
            return;
        case 50: //upperSky.midnight.blue
            NAM0.value.upperSky.midnight.blue = defaultCLR.blue;
            return;
        case 51: //upperSky.midnight.unused1
            NAM0.value.upperSky.midnight.unused1 = defaultCLR.unused1;
            return;
        case 52: //fog.rise.red
            NAM0.value.fog.rise.red = defaultCLR.red;
            return;
        case 53: //fog.rise.green
            NAM0.value.fog.rise.green = defaultCLR.green;
            return;
        case 54: //fog.rise.blue
            NAM0.value.fog.rise.blue = defaultCLR.blue;
            return;
        case 55: //fog.rise.unused1
            NAM0.value.fog.rise.unused1 = defaultCLR.unused1;
            return;
        case 56: //fog.day.red
            NAM0.value.fog.day.red = defaultCLR.red;
            return;
        case 57: //fog.day.green
            NAM0.value.fog.day.green = defaultCLR.green;
            return;
        case 58: //fog.day.blue
            NAM0.value.fog.day.blue = defaultCLR.blue;
            return;
        case 59: //fog.day.unused1
            NAM0.value.fog.day.unused1 = defaultCLR.unused1;
            return;
        case 60: //fog.set.red
            NAM0.value.fog.set.red = defaultCLR.red;
            return;
        case 61: //fog.set.green
            NAM0.value.fog.set.green = defaultCLR.green;
            return;
        case 62: //fog.set.blue
            NAM0.value.fog.set.blue = defaultCLR.blue;
            return;
        case 63: //fog.set.unused1
            NAM0.value.fog.set.unused1 = defaultCLR.unused1;
            return;
        case 64: //fog.night.red
            NAM0.value.fog.night.red = defaultCLR.red;
            return;
        case 65: //fog.night.green
            NAM0.value.fog.night.green = defaultCLR.green;
            return;
        case 66: //fog.night.blue
            NAM0.value.fog.night.blue = defaultCLR.blue;
            return;
        case 67: //fog.night.unused1
            NAM0.value.fog.night.unused1 = defaultCLR.unused1;
            return;
        case 68: //fog.noon.red
            NAM0.value.fog.noon.red = defaultCLR.red;
            return;
        case 69: //fog.noon.green
            NAM0.value.fog.noon.green = defaultCLR.green;
            return;
        case 70: //fog.noon.blue
            NAM0.value.fog.noon.blue = defaultCLR.blue;
            return;
        case 71: //fog.noon.unused1
            NAM0.value.fog.noon.unused1 = defaultCLR.unused1;
            return;
        case 72: //fog.midnight.red
            NAM0.value.fog.midnight.red = defaultCLR.red;
            return;
        case 73: //fog.midnight.green
            NAM0.value.fog.midnight.green = defaultCLR.green;
            return;
        case 74: //fog.midnight.blue
            NAM0.value.fog.midnight.blue = defaultCLR.blue;
            return;
        case 75: //fog.midnight.unused1
            NAM0.value.fog.midnight.unused1 = defaultCLR.unused1;
            return;
        case 76: //lowerClouds.rise.red
            NAM0.value.lowerClouds.rise.red = defaultCLR.red;
            return;
        case 77: //lowerClouds.rise.green
            NAM0.value.lowerClouds.rise.green = defaultCLR.green;
            return;
        case 78: //lowerClouds.rise.blue
            NAM0.value.lowerClouds.rise.blue = defaultCLR.blue;
            return;
        case 79: //lowerClouds.rise.unused1
            NAM0.value.lowerClouds.rise.unused1 = defaultCLR.unused1;
            return;
        case 80: //lowerClouds.day.red
            NAM0.value.lowerClouds.day.red = defaultCLR.red;
            return;
        case 81: //lowerClouds.day.green
            NAM0.value.lowerClouds.day.green = defaultCLR.green;
            return;
        case 82: //lowerClouds.day.blue
            NAM0.value.lowerClouds.day.blue = defaultCLR.blue;
            return;
        case 83: //lowerClouds.day.unused1
            NAM0.value.lowerClouds.day.unused1 = defaultCLR.unused1;
            return;
        case 84: //lowerClouds.set.red
            NAM0.value.lowerClouds.set.red = defaultCLR.red;
            return;
        case 85: //lowerClouds.set.green
            NAM0.value.lowerClouds.set.green = defaultCLR.green;
            return;
        case 86: //lowerClouds.set.blue
            NAM0.value.lowerClouds.set.blue = defaultCLR.blue;
            return;
        case 87: //lowerClouds.set.unused1
            NAM0.value.lowerClouds.set.unused1 = defaultCLR.unused1;
            return;
        case 88: //lowerClouds.night.red
            NAM0.value.lowerClouds.night.red = defaultCLR.red;
            return;
        case 89: //lowerClouds.night.green
            NAM0.value.lowerClouds.night.green = defaultCLR.green;
            return;
        case 90: //lowerClouds.night.blue
            NAM0.value.lowerClouds.night.blue = defaultCLR.blue;
            return;
        case 91: //lowerClouds.night.unused1
            NAM0.value.lowerClouds.night.unused1 = defaultCLR.unused1;
            return;
        case 92: //lowerClouds.noon.red
            NAM0.value.lowerClouds.noon.red = defaultCLR.red;
            return;
        case 93: //lowerClouds.noon.green
            NAM0.value.lowerClouds.noon.green = defaultCLR.green;
            return;
        case 94: //lowerClouds.noon.blue
            NAM0.value.lowerClouds.noon.blue = defaultCLR.blue;
            return;
        case 95: //lowerClouds.noon.unused1
            NAM0.value.lowerClouds.noon.unused1 = defaultCLR.unused1;
            return;
        case 96: //lowerClouds.midnight.red
            NAM0.value.lowerClouds.midnight.red = defaultCLR.red;
            return;
        case 97: //lowerClouds.midnight.green
            NAM0.value.lowerClouds.midnight.green = defaultCLR.green;
            return;
        case 98: //lowerClouds.midnight.blue
            NAM0.value.lowerClouds.midnight.blue = defaultCLR.blue;
            return;
        case 99: //lowerClouds.midnight.unused1
            NAM0.value.lowerClouds.midnight.unused1 = defaultCLR.unused1;
            return;
        case 100: //ambient.rise.red
            NAM0.value.ambient.rise.red = defaultCLR.red;
            return;
        case 101: //ambient.rise.green
            NAM0.value.ambient.rise.green = defaultCLR.green;
            return;
        case 102: //ambient.rise.blue
            NAM0.value.ambient.rise.blue = defaultCLR.blue;
            return;
        case 103: //ambient.rise.unused1
            NAM0.value.ambient.rise.unused1 = defaultCLR.unused1;
            return;
        case 104: //ambient.day.red
            NAM0.value.ambient.day.red = defaultCLR.red;
            return;
        case 105: //ambient.day.green
            NAM0.value.ambient.day.green = defaultCLR.green;
            return;
        case 106: //ambient.day.blue
            NAM0.value.ambient.day.blue = defaultCLR.blue;
            return;
        case 107: //ambient.day.unused1
            NAM0.value.ambient.day.unused1 = defaultCLR.unused1;
            return;
        case 108: //ambient.set.red
            NAM0.value.ambient.set.red = defaultCLR.red;
            return;
        case 109: //ambient.set.green
            NAM0.value.ambient.set.green = defaultCLR.green;
            return;
        case 110: //ambient.set.blue
            NAM0.value.ambient.set.blue = defaultCLR.blue;
            return;
        case 111: //ambient.set.unused1
            NAM0.value.ambient.set.unused1 = defaultCLR.unused1;
            return;
        case 112: //ambient.night.red
            NAM0.value.ambient.night.red = defaultCLR.red;
            return;
        case 113: //ambient.night.green
            NAM0.value.ambient.night.green = defaultCLR.green;
            return;
        case 114: //ambient.night.blue
            NAM0.value.ambient.night.blue = defaultCLR.blue;
            return;
        case 115: //ambient.night.unused1
            NAM0.value.ambient.night.unused1 = defaultCLR.unused1;
            return;
        case 116: //ambient.noon.red
            NAM0.value.ambient.noon.red = defaultCLR.red;
            return;
        case 117: //ambient.noon.green
            NAM0.value.ambient.noon.green = defaultCLR.green;
            return;
        case 118: //ambient.noon.blue
            NAM0.value.ambient.noon.blue = defaultCLR.blue;
            return;
        case 119: //ambient.noon.unused1
            NAM0.value.ambient.noon.unused1 = defaultCLR.unused1;
            return;
        case 120: //ambient.midnight.red
            NAM0.value.ambient.midnight.red = defaultCLR.red;
            return;
        case 121: //ambient.midnight.green
            NAM0.value.ambient.midnight.green = defaultCLR.green;
            return;
        case 122: //ambient.midnight.blue
            NAM0.value.ambient.midnight.blue = defaultCLR.blue;
            return;
        case 123: //ambient.midnight.unused1
            NAM0.value.ambient.midnight.unused1 = defaultCLR.unused1;
            return;
        case 124: //sunlight.rise.red
            NAM0.value.sunlight.rise.red = defaultCLR.red;
            return;
        case 125: //sunlight.rise.green
            NAM0.value.sunlight.rise.green = defaultCLR.green;
            return;
        case 126: //sunlight.rise.blue
            NAM0.value.sunlight.rise.blue = defaultCLR.blue;
            return;
        case 127: //sunlight.rise.unused1
            NAM0.value.sunlight.rise.unused1 = defaultCLR.unused1;
            return;
        case 128: //sunlight.day.red
            NAM0.value.sunlight.day.red = defaultCLR.red;
            return;
        case 129: //sunlight.day.green
            NAM0.value.sunlight.day.green = defaultCLR.green;
            return;
        case 130: //sunlight.day.blue
            NAM0.value.sunlight.day.blue = defaultCLR.blue;
            return;
        case 131: //sunlight.day.unused1
            NAM0.value.sunlight.day.unused1 = defaultCLR.unused1;
            return;
        case 132: //sunlight.set.red
            NAM0.value.sunlight.set.red = defaultCLR.red;
            return;
        case 133: //sunlight.set.green
            NAM0.value.sunlight.set.green = defaultCLR.green;
            return;
        case 134: //sunlight.set.blue
            NAM0.value.sunlight.set.blue = defaultCLR.blue;
            return;
        case 135: //sunlight.set.unused1
            NAM0.value.sunlight.set.unused1 = defaultCLR.unused1;
            return;
        case 136: //sunlight.night.red
            NAM0.value.sunlight.night.red = defaultCLR.red;
            return;
        case 137: //sunlight.night.green
            NAM0.value.sunlight.night.green = defaultCLR.green;
            return;
        case 138: //sunlight.night.blue
            NAM0.value.sunlight.night.blue = defaultCLR.blue;
            return;
        case 139: //sunlight.night.unused1
            NAM0.value.sunlight.night.unused1 = defaultCLR.unused1;
            return;
        case 140: //sunlight.noon.red
            NAM0.value.sunlight.noon.red = defaultCLR.red;
            return;
        case 141: //sunlight.noon.green
            NAM0.value.sunlight.noon.green = defaultCLR.green;
            return;
        case 142: //sunlight.noon.blue
            NAM0.value.sunlight.noon.blue = defaultCLR.blue;
            return;
        case 143: //sunlight.noon.unused1
            NAM0.value.sunlight.noon.unused1 = defaultCLR.unused1;
            return;
        case 144: //sunlight.midnight.red
            NAM0.value.sunlight.midnight.red = defaultCLR.red;
            return;
        case 145: //sunlight.midnight.green
            NAM0.value.sunlight.midnight.green = defaultCLR.green;
            return;
        case 146: //sunlight.midnight.blue
            NAM0.value.sunlight.midnight.blue = defaultCLR.blue;
            return;
        case 147: //sunlight.midnight.unused1
            NAM0.value.sunlight.midnight.unused1 = defaultCLR.unused1;
            return;
        case 148: //sun.rise.red
            NAM0.value.sun.rise.red = defaultCLR.red;
            return;
        case 149: //sun.rise.green
            NAM0.value.sun.rise.green = defaultCLR.green;
            return;
        case 150: //sun.rise.blue
            NAM0.value.sun.rise.blue = defaultCLR.blue;
            return;
        case 151: //sun.rise.unused1
            NAM0.value.sun.rise.unused1 = defaultCLR.unused1;
            return;
        case 152: //sun.day.red
            NAM0.value.sun.day.red = defaultCLR.red;
            return;
        case 153: //sun.day.green
            NAM0.value.sun.day.green = defaultCLR.green;
            return;
        case 154: //sun.day.blue
            NAM0.value.sun.day.blue = defaultCLR.blue;
            return;
        case 155: //sun.day.unused1
            NAM0.value.sun.day.unused1 = defaultCLR.unused1;
            return;
        case 156: //sun.set.red
            NAM0.value.sun.set.red = defaultCLR.red;
            return;
        case 157: //sun.set.green
            NAM0.value.sun.set.green = defaultCLR.green;
            return;
        case 158: //sun.set.blue
            NAM0.value.sun.set.blue = defaultCLR.blue;
            return;
        case 159: //sun.set.unused1
            NAM0.value.sun.set.unused1 = defaultCLR.unused1;
            return;
        case 160: //sun.night.red
            NAM0.value.sun.night.red = defaultCLR.red;
            return;
        case 161: //sun.night.green
            NAM0.value.sun.night.green = defaultCLR.green;
            return;
        case 162: //sun.night.blue
            NAM0.value.sun.night.blue = defaultCLR.blue;
            return;
        case 163: //sun.night.unused1
            NAM0.value.sun.night.unused1 = defaultCLR.unused1;
            return;
        case 164: //sun.noon.red
            NAM0.value.sun.noon.red = defaultCLR.red;
            return;
        case 165: //sun.noon.green
            NAM0.value.sun.noon.green = defaultCLR.green;
            return;
        case 166: //sun.noon.blue
            NAM0.value.sun.noon.blue = defaultCLR.blue;
            return;
        case 167: //sun.noon.unused1
            NAM0.value.sun.noon.unused1 = defaultCLR.unused1;
            return;
        case 168: //sun.midnight.red
            NAM0.value.sun.midnight.red = defaultCLR.red;
            return;
        case 169: //sun.midnight.green
            NAM0.value.sun.midnight.green = defaultCLR.green;
            return;
        case 170: //sun.midnight.blue
            NAM0.value.sun.midnight.blue = defaultCLR.blue;
            return;
        case 171: //sun.midnight.unused1
            NAM0.value.sun.midnight.unused1 = defaultCLR.unused1;
            return;
        case 172: //stars.rise.red
            NAM0.value.stars.rise.red = defaultCLR.red;
            return;
        case 173: //stars.rise.green
            NAM0.value.stars.rise.green = defaultCLR.green;
            return;
        case 174: //stars.rise.blue
            NAM0.value.stars.rise.blue = defaultCLR.blue;
            return;
        case 175: //stars.rise.unused1
            NAM0.value.stars.rise.unused1 = defaultCLR.unused1;
            return;
        case 176: //stars.day.red
            NAM0.value.stars.day.red = defaultCLR.red;
            return;
        case 177: //stars.day.green
            NAM0.value.stars.day.green = defaultCLR.green;
            return;
        case 178: //stars.day.blue
            NAM0.value.stars.day.blue = defaultCLR.blue;
            return;
        case 179: //stars.day.unused1
            NAM0.value.stars.day.unused1 = defaultCLR.unused1;
            return;
        case 180: //stars.set.red
            NAM0.value.stars.set.red = defaultCLR.red;
            return;
        case 181: //stars.set.green
            NAM0.value.stars.set.green = defaultCLR.green;
            return;
        case 182: //stars.set.blue
            NAM0.value.stars.set.blue = defaultCLR.blue;
            return;
        case 183: //stars.set.unused1
            NAM0.value.stars.set.unused1 = defaultCLR.unused1;
            return;
        case 184: //stars.night.red
            NAM0.value.stars.night.red = defaultCLR.red;
            return;
        case 185: //stars.night.green
            NAM0.value.stars.night.green = defaultCLR.green;
            return;
        case 186: //stars.night.blue
            NAM0.value.stars.night.blue = defaultCLR.blue;
            return;
        case 187: //stars.night.unused1
            NAM0.value.stars.night.unused1 = defaultCLR.unused1;
            return;
        case 188: //stars.noon.red
            NAM0.value.stars.noon.red = defaultCLR.red;
            return;
        case 189: //stars.noon.green
            NAM0.value.stars.noon.green = defaultCLR.green;
            return;
        case 190: //stars.noon.blue
            NAM0.value.stars.noon.blue = defaultCLR.blue;
            return;
        case 191: //stars.noon.unused1
            NAM0.value.stars.noon.unused1 = defaultCLR.unused1;
            return;
        case 192: //stars.midnight.red
            NAM0.value.stars.midnight.red = defaultCLR.red;
            return;
        case 193: //stars.midnight.green
            NAM0.value.stars.midnight.green = defaultCLR.green;
            return;
        case 194: //stars.midnight.blue
            NAM0.value.stars.midnight.blue = defaultCLR.blue;
            return;
        case 195: //stars.midnight.unused1
            NAM0.value.stars.midnight.unused1 = defaultCLR.unused1;
            return;
        case 196: //lowerSky.rise.red
            NAM0.value.lowerSky.rise.red = defaultCLR.red;
            return;
        case 197: //lowerSky.rise.green
            NAM0.value.lowerSky.rise.green = defaultCLR.green;
            return;
        case 198: //lowerSky.rise.blue
            NAM0.value.lowerSky.rise.blue = defaultCLR.blue;
            return;
        case 199: //lowerSky.rise.unused1
            NAM0.value.lowerSky.rise.unused1 = defaultCLR.unused1;
            return;
        case 200: //lowerSky.day.red
            NAM0.value.lowerSky.day.red = defaultCLR.red;
            return;
        case 201: //lowerSky.day.green
            NAM0.value.lowerSky.day.green = defaultCLR.green;
            return;
        case 202: //lowerSky.day.blue
            NAM0.value.lowerSky.day.blue = defaultCLR.blue;
            return;
        case 203: //lowerSky.day.unused1
            NAM0.value.lowerSky.day.unused1 = defaultCLR.unused1;
            return;
        case 204: //lowerSky.set.red
            NAM0.value.lowerSky.set.red = defaultCLR.red;
            return;
        case 205: //lowerSky.set.green
            NAM0.value.lowerSky.set.green = defaultCLR.green;
            return;
        case 206: //lowerSky.set.blue
            NAM0.value.lowerSky.set.blue = defaultCLR.blue;
            return;
        case 207: //lowerSky.set.unused1
            NAM0.value.lowerSky.set.unused1 = defaultCLR.unused1;
            return;
        case 208: //lowerSky.night.red
            NAM0.value.lowerSky.night.red = defaultCLR.red;
            return;
        case 209: //lowerSky.night.green
            NAM0.value.lowerSky.night.green = defaultCLR.green;
            return;
        case 210: //lowerSky.night.blue
            NAM0.value.lowerSky.night.blue = defaultCLR.blue;
            return;
        case 211: //lowerSky.night.unused1
            NAM0.value.lowerSky.night.unused1 = defaultCLR.unused1;
            return;
        case 212: //lowerSky.noon.red
            NAM0.value.lowerSky.noon.red = defaultCLR.red;
            return;
        case 213: //lowerSky.noon.green
            NAM0.value.lowerSky.noon.green = defaultCLR.green;
            return;
        case 214: //lowerSky.noon.blue
            NAM0.value.lowerSky.noon.blue = defaultCLR.blue;
            return;
        case 215: //lowerSky.noon.unused1
            NAM0.value.lowerSky.noon.unused1 = defaultCLR.unused1;
            return;
        case 216: //lowerSky.midnight.red
            NAM0.value.lowerSky.midnight.red = defaultCLR.red;
            return;
        case 217: //lowerSky.midnight.green
            NAM0.value.lowerSky.midnight.green = defaultCLR.green;
            return;
        case 218: //lowerSky.midnight.blue
            NAM0.value.lowerSky.midnight.blue = defaultCLR.blue;
            return;
        case 219: //lowerSky.midnight.unused1
            NAM0.value.lowerSky.midnight.unused1 = defaultCLR.unused1;
            return;
        case 220: //horizon.rise.red
            NAM0.value.horizon.rise.red = defaultCLR.red;
            return;
        case 221: //horizon.rise.green
            NAM0.value.horizon.rise.green = defaultCLR.green;
            return;
        case 222: //horizon.rise.blue
            NAM0.value.horizon.rise.blue = defaultCLR.blue;
            return;
        case 223: //horizon.rise.unused1
            NAM0.value.horizon.rise.unused1 = defaultCLR.unused1;
            return;
        case 224: //horizon.day.red
            NAM0.value.horizon.day.red = defaultCLR.red;
            return;
        case 225: //horizon.day.green
            NAM0.value.horizon.day.green = defaultCLR.green;
            return;
        case 226: //horizon.day.blue
            NAM0.value.horizon.day.blue = defaultCLR.blue;
            return;
        case 227: //horizon.day.unused1
            NAM0.value.horizon.day.unused1 = defaultCLR.unused1;
            return;
        case 228: //horizon.set.red
            NAM0.value.horizon.set.red = defaultCLR.red;
            return;
        case 229: //horizon.set.green
            NAM0.value.horizon.set.green = defaultCLR.green;
            return;
        case 230: //horizon.set.blue
            NAM0.value.horizon.set.blue = defaultCLR.blue;
            return;
        case 231: //horizon.set.unused1
            NAM0.value.horizon.set.unused1 = defaultCLR.unused1;
            return;
        case 232: //horizon.night.red
            NAM0.value.horizon.night.red = defaultCLR.red;
            return;
        case 233: //horizon.night.green
            NAM0.value.horizon.night.green = defaultCLR.green;
            return;
        case 234: //horizon.night.blue
            NAM0.value.horizon.night.blue = defaultCLR.blue;
            return;
        case 235: //horizon.night.unused1
            NAM0.value.horizon.night.unused1 = defaultCLR.unused1;
            return;
        case 236: //horizon.noon.red
            NAM0.value.horizon.noon.red = defaultCLR.red;
            return;
        case 237: //horizon.noon.green
            NAM0.value.horizon.noon.green = defaultCLR.green;
            return;
        case 238: //horizon.noon.blue
            NAM0.value.horizon.noon.blue = defaultCLR.blue;
            return;
        case 239: //horizon.noon.unused1
            NAM0.value.horizon.noon.unused1 = defaultCLR.unused1;
            return;
        case 240: //horizon.midnight.red
            NAM0.value.horizon.midnight.red = defaultCLR.red;
            return;
        case 241: //horizon.midnight.green
            NAM0.value.horizon.midnight.green = defaultCLR.green;
            return;
        case 242: //horizon.midnight.blue
            NAM0.value.horizon.midnight.blue = defaultCLR.blue;
            return;
        case 243: //horizon.midnight.unused1
            NAM0.value.horizon.midnight.unused1 = defaultCLR.unused1;
            return;
        case 244: //upperClouds.rise.red
            NAM0.value.upperClouds.rise.red = defaultCLR.red;
            return;
        case 245: //upperClouds.rise.green
            NAM0.value.upperClouds.rise.green = defaultCLR.green;
            return;
        case 246: //upperClouds.rise.blue
            NAM0.value.upperClouds.rise.blue = defaultCLR.blue;
            return;
        case 247: //upperClouds.rise.unused1
            NAM0.value.upperClouds.rise.unused1 = defaultCLR.unused1;
            return;
        case 248: //upperClouds.day.red
            NAM0.value.upperClouds.day.red = defaultCLR.red;
            return;
        case 249: //upperClouds.day.green
            NAM0.value.upperClouds.day.green = defaultCLR.green;
            return;
        case 250: //upperClouds.day.blue
            NAM0.value.upperClouds.day.blue = defaultCLR.blue;
            return;
        case 251: //upperClouds.day.unused1
            NAM0.value.upperClouds.day.unused1 = defaultCLR.unused1;
            return;
        case 252: //upperClouds.set.red
            NAM0.value.upperClouds.set.red = defaultCLR.red;
            return;
        case 253: //upperClouds.set.green
            NAM0.value.upperClouds.set.green = defaultCLR.green;
            return;
        case 254: //upperClouds.set.blue
            NAM0.value.upperClouds.set.blue = defaultCLR.blue;
            return;
        case 255: //upperClouds.set.unused1
            NAM0.value.upperClouds.set.unused1 = defaultCLR.unused1;
            return;
        case 256: //upperClouds.night.red
            NAM0.value.upperClouds.night.red = defaultCLR.red;
            return;
        case 257: //upperClouds.night.green
            NAM0.value.upperClouds.night.green = defaultCLR.green;
            return;
        case 258: //upperClouds.night.blue
            NAM0.value.upperClouds.night.blue = defaultCLR.blue;
            return;
        case 259: //upperClouds.night.unused1
            NAM0.value.upperClouds.night.unused1 = defaultCLR.unused1;
            return;
        case 260: //upperClouds.noon.red
            NAM0.value.upperClouds.noon.red = defaultCLR.red;
            return;
        case 261: //upperClouds.noon.green
            NAM0.value.upperClouds.noon.green = defaultCLR.green;
            return;
        case 262: //upperClouds.noon.blue
            NAM0.value.upperClouds.noon.blue = defaultCLR.blue;
            return;
        case 263: //upperClouds.noon.unused1
            NAM0.value.upperClouds.noon.unused1 = defaultCLR.unused1;
            return;
        case 264: //upperClouds.midnight.red
            NAM0.value.upperClouds.midnight.red = defaultCLR.red;
            return;
        case 265: //upperClouds.midnight.green
            NAM0.value.upperClouds.midnight.green = defaultCLR.green;
            return;
        case 266: //upperClouds.midnight.blue
            NAM0.value.upperClouds.midnight.blue = defaultCLR.blue;
            return;
        case 267: //upperClouds.midnight.unused1
            NAM0.value.upperClouds.midnight.unused1 = defaultCLR.unused1;
            return;
        case 268: //fogDayNear
            FNAM.value.fogDayNear = defaultFNAM.fogDayNear;
            return;
        case 269: //fogDayFar
            FNAM.value.fogDayFar = defaultFNAM.fogDayFar;
            return;
        case 270: //fogNightNear
            FNAM.value.fogNightNear = defaultFNAM.fogNightNear;
            return;
        case 271: //fogNightFar
            FNAM.value.fogNightFar = defaultFNAM.fogNightFar;
            return;
        case 272: //fogDayPower
            FNAM.value.fogDayPower = defaultFNAM.fogDayPower;
            return;
        case 273: //fogNightPower
            FNAM.value.fogNightPower = defaultFNAM.fogNightPower;
            return;
        case 274: //INAM
            INAM.Unload();
            return;
        case 275: //windSpeed
            DATA.value.windSpeed = defaultDATA.windSpeed;
            return;
        case 276: //lowerCloudSpeed
            DATA.value.lowerCloudSpeed = defaultDATA.lowerCloudSpeed;
            return;
        case 277: //upperCloudSpeed
            DATA.value.upperCloudSpeed = defaultDATA.upperCloudSpeed;
            return;
        case 278: //transDelta
            DATA.value.transDelta = defaultDATA.transDelta;
            return;
        case 279: //sunGlare
            DATA.value.sunGlare = defaultDATA.sunGlare;
            return;
        case 280: //sunDamage
            DATA.value.sunDamage = defaultDATA.sunDamage;
            return;
        case 281: //rainFadeIn
            DATA.value.rainFadeIn = defaultDATA.rainFadeIn;
            return;
        case 282: //rainFadeOut
            DATA.value.rainFadeOut = defaultDATA.rainFadeOut;
            return;
        case 283: //boltFadeIn
            DATA.value.boltFadeIn = defaultDATA.boltFadeIn;
            return;
        case 284: //boltFadeOut
            DATA.value.boltFadeOut = defaultDATA.boltFadeOut;
            return;
        case 285: //boltFrequency
            DATA.value.boltFrequency = defaultDATA.boltFrequency;
            return;
        case 286: //weatherType
            DATA.value.weatherType = defaultDATA.weatherType;
            return;
        case 287: //boltRed
            DATA.value.boltRed = defaultDATA.boltRed;
            return;
        case 288: //boltGreen
            DATA.value.boltGreen = defaultDATA.boltGreen;
            return;
        case 289: //boltBlue
            DATA.value.boltBlue = defaultDATA.boltBlue;
            return;
        case 290: //sounds
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
        case 291: //convenience deleter
            NAM0.value.upperSky = defaultColors;
            return;
        case 292: //convenience deleter
            NAM0.value.fog = defaultColors;
            return;
        case 293: //convenience deleter
            NAM0.value.lowerClouds = defaultColors;
            return;
        case 294: //convenience deleter
            NAM0.value.ambient = defaultColors;
            return;
        case 295: //convenience deleter
            NAM0.value.sunlight = defaultColors;
            return;
        case 296: //convenience deleter
            NAM0.value.sun = defaultColors;
            return;
        case 297: //convenience deleter
            NAM0.value.stars = defaultColors;
            return;
        case 298: //convenience deleter
            NAM0.value.lowerSky = defaultColors;
            return;
        case 299: //convenience deleter
            NAM0.value.horizon = defaultColors;
            return;
        case 300: //convenience deleter
            NAM0.value.upperClouds = defaultColors;
            return;
        default:
            return;
        }
    }
}