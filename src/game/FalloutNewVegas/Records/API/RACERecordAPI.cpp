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
#include "..\RACERecord.h"

namespace FNV
{
uint32_t RACERecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //description
            return CB_STRING_FIELD;
        case 9: //relations
            if(ListFieldID == 0) //relations
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)XNAM.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= XNAM.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //faction
                    return CB_FORMID_FIELD;
                case 2: //mod
                    return CB_SINT32_FIELD;
                case 3: //groupReactionType
                    return CB_UINT32_TYPE_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //skill1
            return CB_SINT8_FIELD;
        case 11: //skill1Boost
            return CB_SINT8_FIELD;
        case 12: //skill2
            return CB_SINT8_FIELD;
        case 13: //skill2Boost
            return CB_SINT8_FIELD;
        case 14: //skill3
            return CB_SINT8_FIELD;
        case 15: //skill3Boost
            return CB_SINT8_FIELD;
        case 16: //skill4
            return CB_SINT8_FIELD;
        case 17: //skill4Boost
            return CB_SINT8_FIELD;
        case 18: //skill5
            return CB_SINT8_FIELD;
        case 19: //skill5Boost
            return CB_SINT8_FIELD;
        case 20: //skill6
            return CB_SINT8_FIELD;
        case 21: //skill6Boost
            return CB_SINT8_FIELD;
        case 22: //skill7
            return CB_SINT8_FIELD;
        case 23: //skill7Boost
            return CB_SINT8_FIELD;
        case 24: //unused1
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
        case 25: //maleHeight
            return CB_FLOAT32_FIELD;
        case 26: //femaleHeight
            return CB_FLOAT32_FIELD;
        case 27: //maleWeight
            return CB_FLOAT32_FIELD;
        case 28: //femaleWeight
            return CB_FLOAT32_FIELD;
        case 29: //flags
            return CB_UINT32_FLAG_FIELD;
        case 30: //older
            return CB_FORMID_FIELD;
        case 31: //younger
            return CB_FORMID_FIELD;
        case 32: //maleVoice
            return CB_FORMID_FIELD;
        case 33: //femaleVoice
            return CB_FORMID_FIELD;
        case 34: //defaultHairMale
            return CB_FORMID_FIELD;
        case 35: //defaultHairFemale
            return CB_FORMID_FIELD;
        case 36: //defaultHairMaleColor
            return CB_UINT8_FIELD;
        case 37: //defaultHairFemaleColor
            return CB_UINT8_FIELD;
        case 38: //mainClamp
            return CB_FLOAT32_FIELD;
        case 39: //faceClamp
            return CB_FLOAT32_FIELD;
        case 40: //attr_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return ATTR.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 41: //maleHead_modPath
            return CB_ISTRING_FIELD;
        case 42: //maleHead_modb
            return CB_FLOAT32_FIELD;
        case 43: //maleHead_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD0.MODL.IsLoaded() ? MHMOD0.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 44: //maleHead_altTextures
            if(!MHMOD0.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD0.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD0.MODL->Textures.MODS.size())
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
        case 45: //maleHead_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 46: //maleHead_iconPath
            return CB_ISTRING_FIELD;
        case 47: //maleHead_smallIconPath
            return CB_ISTRING_FIELD;
        case 48: //maleEars_modPath
            return CB_ISTRING_FIELD;
        case 49: //maleEars_modb
            return CB_FLOAT32_FIELD;
        case 50: //maleEars_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD1.MODL.IsLoaded() ? MHMOD1.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 51: //maleEars_altTextures
            if(!MHMOD1.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD1.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD1.MODL->Textures.MODS.size())
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
        case 52: //maleEars_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 53: //maleEars_iconPath
            return CB_ISTRING_FIELD;
        case 54: //maleEars_smallIconPath
            return CB_ISTRING_FIELD;
        case 55: //maleMouth_modPath
            return CB_ISTRING_FIELD;
        case 56: //maleMouth_modb
            return CB_FLOAT32_FIELD;
        case 57: //maleMouth_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD2.MODL.IsLoaded() ? MHMOD2.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 58: //maleMouth_altTextures
            if(!MHMOD2.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD2.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD2.MODL->Textures.MODS.size())
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
        case 59: //maleMouth_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 60: //maleMouth_iconPath
            return CB_ISTRING_FIELD;
        case 61: //maleMouth_smallIconPath
            return CB_ISTRING_FIELD;
        case 62: //maleTeethLower_modPath
            return CB_ISTRING_FIELD;
        case 63: //maleTeethLower_modb
            return CB_FLOAT32_FIELD;
        case 64: //maleTeethLower_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD3.MODL.IsLoaded() ? MHMOD3.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 65: //maleTeethLower_altTextures
            if(!MHMOD3.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD3.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD3.MODL->Textures.MODS.size())
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
        case 66: //maleTeethLower_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 67: //maleTeethLower_iconPath
            return CB_ISTRING_FIELD;
        case 68: //maleTeethLower_smallIconPath
            return CB_ISTRING_FIELD;
        case 69: //maleTeethUpper_modPath
            return CB_ISTRING_FIELD;
        case 70: //maleTeethUpper_modb
            return CB_FLOAT32_FIELD;
        case 71: //maleTeethUpper_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD4.MODL.IsLoaded() ? MHMOD4.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 72: //maleTeethUpper_altTextures
            if(!MHMOD4.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD4.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD4.MODL->Textures.MODS.size())
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
        case 73: //maleTeethUpper_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 74: //maleTeethUpper_iconPath
            return CB_ISTRING_FIELD;
        case 75: //maleTeethUpper_smallIconPath
            return CB_ISTRING_FIELD;
        case 76: //maleTongue_modPath
            return CB_ISTRING_FIELD;
        case 77: //maleTongue_modb
            return CB_FLOAT32_FIELD;
        case 78: //maleTongue_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD5.MODL.IsLoaded() ? MHMOD5.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 79: //maleTongue_altTextures
            if(!MHMOD5.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD5.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD5.MODL->Textures.MODS.size())
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
        case 80: //maleTongue_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 81: //maleTongue_iconPath
            return CB_ISTRING_FIELD;
        case 82: //maleTongue_smallIconPath
            return CB_ISTRING_FIELD;
        case 83: //maleLeftEye_modPath
            return CB_ISTRING_FIELD;
        case 84: //maleLeftEye_modb
            return CB_FLOAT32_FIELD;
        case 85: //maleLeftEye_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD6.MODL.IsLoaded() ? MHMOD6.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 86: //maleLeftEye_altTextures
            if(!MHMOD6.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD6.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD6.MODL->Textures.MODS.size())
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
        case 87: //maleLeftEye_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 88: //maleLeftEye_iconPath
            return CB_ISTRING_FIELD;
        case 89: //maleLeftEye_smallIconPath
            return CB_ISTRING_FIELD;
        case 90: //maleRightEye_modPath
            return CB_ISTRING_FIELD;
        case 91: //maleRightEye_modb
            return CB_FLOAT32_FIELD;
        case 92: //maleRightEye_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MHMOD7.MODL.IsLoaded() ? MHMOD7.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 93: //maleRightEye_altTextures
            if(!MHMOD7.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MHMOD7.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MHMOD7.MODL->Textures.MODS.size())
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
        case 94: //maleRightEye_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 95: //maleRightEye_iconPath
            return CB_ISTRING_FIELD;
        case 96: //maleRightEye_smallIconPath
            return CB_ISTRING_FIELD;
        case 97: //femaleHead_modPath
            return CB_ISTRING_FIELD;
        case 98: //femaleHead_modb
            return CB_FLOAT32_FIELD;
        case 99: //femaleHead_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD0.MODL.IsLoaded() ? FHMOD0.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 100: //femaleHead_altTextures
            if(!FHMOD0.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD0.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD0.MODL->Textures.MODS.size())
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
        case 101: //femaleHead_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 102: //femaleHead_iconPath
            return CB_ISTRING_FIELD;
        case 103: //femaleHead_smallIconPath
            return CB_ISTRING_FIELD;
        case 104: //femaleEars_modPath
            return CB_ISTRING_FIELD;
        case 105: //femaleEars_modb
            return CB_FLOAT32_FIELD;
        case 106: //femaleEars_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD1.MODL.IsLoaded() ? FHMOD1.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 107: //femaleEars_altTextures
            if(!FHMOD1.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD1.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD1.MODL->Textures.MODS.size())
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
        case 108: //femaleEars_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 109: //femaleEars_iconPath
            return CB_ISTRING_FIELD;
        case 110: //femaleEars_smallIconPath
            return CB_ISTRING_FIELD;
        case 111: //femaleMouth_modPath
            return CB_ISTRING_FIELD;
        case 112: //femaleMouth_modb
            return CB_FLOAT32_FIELD;
        case 113: //femaleMouth_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD2.MODL.IsLoaded() ? FHMOD2.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 114: //femaleMouth_altTextures
            if(!FHMOD2.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD2.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD2.MODL->Textures.MODS.size())
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
        case 115: //femaleMouth_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 116: //femaleMouth_iconPath
            return CB_ISTRING_FIELD;
        case 117: //femaleMouth_smallIconPath
            return CB_ISTRING_FIELD;
        case 118: //femaleTeethLower_modPath
            return CB_ISTRING_FIELD;
        case 119: //femaleTeethLower_modb
            return CB_FLOAT32_FIELD;
        case 120: //femaleTeethLower_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD3.MODL.IsLoaded() ? FHMOD3.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 121: //femaleTeethLower_altTextures
            if(!FHMOD3.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD3.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD3.MODL->Textures.MODS.size())
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
        case 122: //femaleTeethLower_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 123: //femaleTeethLower_iconPath
            return CB_ISTRING_FIELD;
        case 124: //femaleTeethLower_smallIconPath
            return CB_ISTRING_FIELD;
        case 125: //femaleTeethUpper_modPath
            return CB_ISTRING_FIELD;
        case 126: //femaleTeethUpper_modb
            return CB_FLOAT32_FIELD;
        case 127: //femaleTeethUpper_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD4.MODL.IsLoaded() ? FHMOD4.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 128: //femaleTeethUpper_altTextures
            if(!FHMOD4.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD4.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD4.MODL->Textures.MODS.size())
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
        case 129: //femaleTeethUpper_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 130: //femaleTeethUpper_iconPath
            return CB_ISTRING_FIELD;
        case 131: //femaleTeethUpper_smallIconPath
            return CB_ISTRING_FIELD;
        case 132: //femaleTongue_modPath
            return CB_ISTRING_FIELD;
        case 133: //femaleTongue_modb
            return CB_FLOAT32_FIELD;
        case 134: //femaleTongue_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD5.MODL.IsLoaded() ? FHMOD5.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 135: //femaleTongue_altTextures
            if(!FHMOD5.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD5.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD5.MODL->Textures.MODS.size())
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
        case 136: //femaleTongue_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 137: //femaleTongue_iconPath
            return CB_ISTRING_FIELD;
        case 138: //femaleTongue_smallIconPath
            return CB_ISTRING_FIELD;
        case 139: //femaleLeftEye_modPath
            return CB_ISTRING_FIELD;
        case 140: //femaleLeftEye_modb
            return CB_FLOAT32_FIELD;
        case 141: //femaleLeftEye_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD6.MODL.IsLoaded() ? FHMOD6.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 142: //femaleLeftEye_altTextures
            if(!FHMOD6.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD6.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD6.MODL->Textures.MODS.size())
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
        case 143: //femaleLeftEye_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 144: //femaleLeftEye_iconPath
            return CB_ISTRING_FIELD;
        case 145: //femaleLeftEye_smallIconPath
            return CB_ISTRING_FIELD;
        case 146: //femaleRightEye_modPath
            return CB_ISTRING_FIELD;
        case 147: //femaleRightEye_modb
            return CB_FLOAT32_FIELD;
        case 148: //femaleRightEye_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FHMOD7.MODL.IsLoaded() ? FHMOD7.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 149: //femaleRightEye_altTextures
            if(!FHMOD7.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FHMOD7.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FHMOD7.MODL->Textures.MODS.size())
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
        case 150: //femaleRightEye_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 151: //femaleRightEye_iconPath
            return CB_ISTRING_FIELD;
        case 152: //femaleRightEye_smallIconPath
            return CB_ISTRING_FIELD;
        case 153: //maleUpperBody_modPath
            return CB_ISTRING_FIELD;
        case 154: //maleUpperBody_modb
            return CB_FLOAT32_FIELD;
        case 155: //maleUpperBody_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MBMOD0.MODL.IsLoaded() ? MBMOD0.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 156: //maleUpperBody_altTextures
            if(!MBMOD0.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MBMOD0.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MBMOD0.MODL->Textures.MODS.size())
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
        case 157: //maleUpperBody_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 158: //maleUpperBody_iconPath
            return CB_ISTRING_FIELD;
        case 159: //maleUpperBody_smallIconPath
            return CB_ISTRING_FIELD;
        case 160: //maleLeftHand_modPath
            return CB_ISTRING_FIELD;
        case 161: //maleLeftHand_modb
            return CB_FLOAT32_FIELD;
        case 162: //maleLeftHand_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MBMOD1.MODL.IsLoaded() ? MBMOD1.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 163: //maleLeftHand_altTextures
            if(!MBMOD1.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MBMOD1.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MBMOD1.MODL->Textures.MODS.size())
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
        case 164: //maleLeftHand_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 165: //maleLeftHand_iconPath
            return CB_ISTRING_FIELD;
        case 166: //maleLeftHand_smallIconPath
            return CB_ISTRING_FIELD;
        case 167: //maleRightHand_modPath
            return CB_ISTRING_FIELD;
        case 168: //maleRightHand_modb
            return CB_FLOAT32_FIELD;
        case 169: //maleRightHand_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MBMOD2.MODL.IsLoaded() ? MBMOD2.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 170: //maleRightHand_altTextures
            if(!MBMOD2.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MBMOD2.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MBMOD2.MODL->Textures.MODS.size())
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
        case 171: //maleRightHand_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 172: //maleRightHand_iconPath
            return CB_ISTRING_FIELD;
        case 173: //maleRightHand_smallIconPath
            return CB_ISTRING_FIELD;
        case 174: //maleUpperBodyTexture_modPath
            return CB_ISTRING_FIELD;
        case 175: //maleUpperBodyTexture_modb
            return CB_FLOAT32_FIELD;
        case 176: //maleUpperBodyTexture_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MBMOD3.MODL.IsLoaded() ? MBMOD3.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 177: //maleUpperBodyTexture_altTextures
            if(!MBMOD3.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MBMOD3.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MBMOD3.MODL->Textures.MODS.size())
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
        case 178: //maleUpperBodyTexture_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 179: //maleUpperBodyTexture_iconPath
            return CB_ISTRING_FIELD;
        case 180: //maleUpperBodyTexture_smallIconPath
            return CB_ISTRING_FIELD;
        case 181: //femaleUpperBody_modPath
            return CB_ISTRING_FIELD;
        case 182: //femaleUpperBody_modb
            return CB_FLOAT32_FIELD;
        case 183: //femaleUpperBody_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FBMOD0.MODL.IsLoaded() ? FBMOD0.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 184: //femaleUpperBody_altTextures
            if(!FBMOD0.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FBMOD0.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FBMOD0.MODL->Textures.MODS.size())
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
        case 185: //femaleUpperBody_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 186: //femaleUpperBody_iconPath
            return CB_ISTRING_FIELD;
        case 187: //femaleUpperBody_smallIconPath
            return CB_ISTRING_FIELD;
        case 188: //femaleLeftHand_modPath
            return CB_ISTRING_FIELD;
        case 189: //femaleLeftHand_modb
            return CB_FLOAT32_FIELD;
        case 190: //femaleLeftHand_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FBMOD1.MODL.IsLoaded() ? FBMOD1.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 191: //femaleLeftHand_altTextures
            if(!FBMOD1.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FBMOD1.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FBMOD1.MODL->Textures.MODS.size())
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
        case 192: //femaleLeftHand_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 193: //femaleLeftHand_iconPath
            return CB_ISTRING_FIELD;
        case 194: //femaleLeftHand_smallIconPath
            return CB_ISTRING_FIELD;
        case 195: //femaleRightHand_modPath
            return CB_ISTRING_FIELD;
        case 196: //femaleRightHand_modb
            return CB_FLOAT32_FIELD;
        case 197: //femaleRightHand_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FBMOD2.MODL.IsLoaded() ? FBMOD2.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 198: //femaleRightHand_altTextures
            if(!FBMOD2.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FBMOD2.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FBMOD2.MODL->Textures.MODS.size())
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
        case 199: //femaleRightHand_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 200: //femaleRightHand_iconPath
            return CB_ISTRING_FIELD;
        case 201: //femaleRightHand_smallIconPath
            return CB_ISTRING_FIELD;
        case 202: //femaleUpperBodyTexture_modPath
            return CB_ISTRING_FIELD;
        case 203: //femaleUpperBodyTexture_modb
            return CB_FLOAT32_FIELD;
        case 204: //femaleUpperBodyTexture_modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FBMOD3.MODL.IsLoaded() ? FBMOD3.MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 205: //femaleUpperBodyTexture_altTextures
            if(!FBMOD3.MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)FBMOD3.MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= FBMOD3.MODL->Textures.MODS.size())
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
        case 206: //femaleUpperBodyTexture_modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 207: //femaleUpperBodyTexture_iconPath
            return CB_ISTRING_FIELD;
        case 208: //femaleUpperBodyTexture_smallIconPath
            return CB_ISTRING_FIELD;
        case 209: //hairs
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)HNAM.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 210: //eyes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)ENAM.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 211: //maleFggs_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MaleFGGS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 212: //maleFgga_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MaleFGGA.IsLoaded() ? 120 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 213: //maleFgts_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MaleFGTS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 214: //maleSnam_p
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
        case 215: //femaleFggs_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FemaleFGGS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 216: //femaleFgga_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FemaleFGGA.IsLoaded() ? 120 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 217: //femaleFgts_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return FemaleFGTS.IsLoaded() ? 200 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 218: //femaleSnam_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * RACERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //description
            return DESC.value;
        case 9: //relations
            if(ListIndex >= XNAM.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //faction
                    return &XNAM.value[ListIndex]->faction;
                case 2: //mod
                    return &XNAM.value[ListIndex]->mod;
                case 3: //groupReactionType
                    return &XNAM.value[ListIndex]->groupReactionType;
                default:
                    return NULL;
                }
            return NULL;
        case 10: //skill1
            return &DATA.value.skills[0].value;
        case 11: //skill1Boost
            return &DATA.value.skills[0].boost;
        case 12: //skill2
            return &DATA.value.skills[1].value;
        case 13: //skill2Boost
            return &DATA.value.skills[1].boost;
        case 14: //skill3
            return &DATA.value.skills[2].value;
        case 15: //skill3Boost
            return &DATA.value.skills[2].boost;
        case 16: //skill4
            return &DATA.value.skills[3].value;
        case 17: //skill4Boost
            return &DATA.value.skills[3].boost;
        case 18: //skill5
            return &DATA.value.skills[4].value;
        case 19: //skill5Boost
            return &DATA.value.skills[4].boost;
        case 20: //skill6
            return &DATA.value.skills[5].value;
        case 21: //skill6Boost
            return &DATA.value.skills[5].boost;
        case 22: //skill7
            return &DATA.value.skills[6].value;
        case 23: //skill7Boost
            return &DATA.value.skills[6].boost;
        case 24: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 25: //maleHeight
            return &DATA.value.maleHeight;
        case 26: //femaleHeight
            return &DATA.value.femaleHeight;
        case 27: //maleWeight
            return &DATA.value.maleWeight;
        case 28: //femaleWeight
            return &DATA.value.femaleWeight;
        case 29: //flags
            return &DATA.value.flags;
        case 30: //older
            return ONAM.IsLoaded() ? &ONAM.value : NULL;
        case 31: //younger
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 32: //maleVoice
            return VTCK.IsLoaded() ? &VTCK.value.maleVoice : NULL;
        case 33: //femaleVoice
            return VTCK.IsLoaded() ? &VTCK.value.femaleVoice : NULL;
        case 34: //defaultHairMale
            return DNAM.IsLoaded() ? &DNAM.value.defaultHairMale : NULL;
        case 35: //defaultHairFemale
            return DNAM.IsLoaded() ? &DNAM.value.defaultHairFemale : NULL;
        case 36: //defaultHairMaleColor
            return CNAM.IsLoaded() ? &CNAM.value.defaultHairMale : NULL;
        case 37: //defaultHairFemaleColor
            return CNAM.IsLoaded() ? &CNAM.value.defaultHairFemale : NULL;
        case 38: //mainClamp
            return PNAM.IsLoaded() ? &PNAM.value : NULL;
        case 39: //faceClamp
            return UNAM.IsLoaded() ? &UNAM.value : NULL;
        case 40: //attr_p
            *FieldValues = ATTR.value;
            return NULL;
        case 41: //maleHead_modPath
            return MHMOD0.MODL.IsLoaded() ? MHMOD0.MODL->MODL.value : NULL;
        case 42: //maleHead_modb
            return MHMOD0.MODL.IsLoaded() ? (MHMOD0.MODL->MODB.IsLoaded() ? &MHMOD0.MODL->MODB.value : NULL) : NULL;
        case 43: //maleHead_modt_p
            *FieldValues = MHMOD0.MODL.IsLoaded() ? MHMOD0.MODL->MODT.value : NULL;
            return NULL;
        case 44: //maleHead_altTextures
            if(!MHMOD0.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD0.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD0.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD0.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD0.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 45: //maleHead_modelFlags
            return MHMOD0.MODL.IsLoaded() ? (MHMOD0.MODL->MODD.IsLoaded() ? &MHMOD0.MODL->MODD.value : NULL) : NULL;
        case 46: //maleHead_iconPath
            return MHMOD0.ICON.value;
        case 47: //maleHead_smallIconPath
            return MHMOD0.MICO.value;
        case 48: //maleEars_modPath
            return MHMOD1.MODL.IsLoaded() ? MHMOD1.MODL->MODL.value : NULL;
        case 49: //maleEars_modb
            return MHMOD1.MODL.IsLoaded() ? (MHMOD1.MODL->MODB.IsLoaded() ? &MHMOD1.MODL->MODB.value : NULL) : NULL;
        case 50: //maleEars_modt_p
            *FieldValues = MHMOD1.MODL.IsLoaded() ? MHMOD1.MODL->MODT.value : NULL;
            return NULL;
        case 51: //maleEars_altTextures
            if(!MHMOD1.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD1.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD1.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD1.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD1.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 52: //maleEars_modelFlags
            return MHMOD1.MODL.IsLoaded() ? (MHMOD1.MODL->MODD.IsLoaded() ? &MHMOD1.MODL->MODD.value : NULL) : NULL;
        case 53: //maleEars_iconPath
            return MHMOD1.ICON.value;
        case 54: //maleEars_smallIconPath
            return MHMOD1.MICO.value;
        case 55: //maleMouth_modPath
            return MHMOD2.MODL.IsLoaded() ? MHMOD2.MODL->MODL.value : NULL;
        case 56: //maleMouth_modb
            return MHMOD2.MODL.IsLoaded() ? (MHMOD2.MODL->MODB.IsLoaded() ? &MHMOD2.MODL->MODB.value : NULL) : NULL;
        case 57: //maleMouth_modt_p
            *FieldValues = MHMOD2.MODL.IsLoaded() ? MHMOD2.MODL->MODT.value : NULL;
            return NULL;
        case 58: //maleMouth_altTextures
            if(!MHMOD2.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD2.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD2.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD2.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD2.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 59: //maleMouth_modelFlags
            return MHMOD2.MODL.IsLoaded() ? (MHMOD2.MODL->MODD.IsLoaded() ? &MHMOD2.MODL->MODD.value : NULL) : NULL;
        case 60: //maleMouth_iconPath
            return MHMOD2.ICON.value;
        case 61: //maleMouth_smallIconPath
            return MHMOD2.MICO.value;
        case 62: //maleTeethLower_modPath
            return MHMOD3.MODL.IsLoaded() ? MHMOD3.MODL->MODL.value : NULL;
        case 63: //maleTeethLower_modb
            return MHMOD3.MODL.IsLoaded() ? (MHMOD3.MODL->MODB.IsLoaded() ? &MHMOD3.MODL->MODB.value : NULL) : NULL;
        case 64: //maleTeethLower_modt_p
            *FieldValues = MHMOD3.MODL.IsLoaded() ? MHMOD3.MODL->MODT.value : NULL;
            return NULL;
        case 65: //maleTeethLower_altTextures
            if(!MHMOD3.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD3.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD3.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD3.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD3.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 66: //maleTeethLower_modelFlags
            return MHMOD3.MODL.IsLoaded() ? (MHMOD3.MODL->MODD.IsLoaded() ? &MHMOD3.MODL->MODD.value : NULL) : NULL;
        case 67: //maleTeethLower_iconPath
            return MHMOD3.ICON.value;
        case 68: //maleTeethLower_smallIconPath
            return MHMOD3.MICO.value;
        case 69: //maleTeethUpper_modPath
            return MHMOD4.MODL.IsLoaded() ? MHMOD4.MODL->MODL.value : NULL;
        case 70: //maleTeethUpper_modb
            return MHMOD4.MODL.IsLoaded() ? (MHMOD4.MODL->MODB.IsLoaded() ? &MHMOD4.MODL->MODB.value : NULL) : NULL;
        case 71: //maleTeethUpper_modt_p
            *FieldValues = MHMOD4.MODL.IsLoaded() ? MHMOD4.MODL->MODT.value : NULL;
            return NULL;
        case 72: //maleTeethUpper_altTextures
            if(!MHMOD4.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD4.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD4.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD4.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD4.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 73: //maleTeethUpper_modelFlags
            return MHMOD4.MODL.IsLoaded() ? (MHMOD4.MODL->MODD.IsLoaded() ? &MHMOD4.MODL->MODD.value : NULL) : NULL;
        case 74: //maleTeethUpper_iconPath
            return MHMOD4.ICON.value;
        case 75: //maleTeethUpper_smallIconPath
            return MHMOD4.MICO.value;
        case 76: //maleTongue_modPath
            return MHMOD5.MODL.IsLoaded() ? MHMOD5.MODL->MODL.value : NULL;
        case 77: //maleTongue_modb
            return MHMOD5.MODL.IsLoaded() ? (MHMOD5.MODL->MODB.IsLoaded() ? &MHMOD5.MODL->MODB.value : NULL) : NULL;
        case 78: //maleTongue_modt_p
            *FieldValues = MHMOD5.MODL.IsLoaded() ? MHMOD5.MODL->MODT.value : NULL;
            return NULL;
        case 79: //maleTongue_altTextures
            if(!MHMOD5.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD5.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD5.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD5.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD5.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 80: //maleTongue_modelFlags
            return MHMOD5.MODL.IsLoaded() ? (MHMOD5.MODL->MODD.IsLoaded() ? &MHMOD5.MODL->MODD.value : NULL) : NULL;
        case 81: //maleTongue_iconPath
            return MHMOD5.ICON.value;
        case 82: //maleTongue_smallIconPath
            return MHMOD5.MICO.value;
        case 83: //maleLeftEye_modPath
            return MHMOD6.MODL.IsLoaded() ? MHMOD6.MODL->MODL.value : NULL;
        case 84: //maleLeftEye_modb
            return MHMOD6.MODL.IsLoaded() ? (MHMOD6.MODL->MODB.IsLoaded() ? &MHMOD6.MODL->MODB.value : NULL) : NULL;
        case 85: //maleLeftEye_modt_p
            *FieldValues = MHMOD6.MODL.IsLoaded() ? MHMOD6.MODL->MODT.value : NULL;
            return NULL;
        case 86: //maleLeftEye_altTextures
            if(!MHMOD6.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD6.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD6.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD6.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD6.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 87: //maleLeftEye_modelFlags
            return MHMOD6.MODL.IsLoaded() ? (MHMOD6.MODL->MODD.IsLoaded() ? &MHMOD6.MODL->MODD.value : NULL) : NULL;
        case 88: //maleLeftEye_iconPath
            return MHMOD6.ICON.value;
        case 89: //maleLeftEye_smallIconPath
            return MHMOD6.MICO.value;
        case 90: //maleRightEye_modPath
            return MHMOD7.MODL.IsLoaded() ? MHMOD7.MODL->MODL.value : NULL;
        case 91: //maleRightEye_modb
            return MHMOD7.MODL.IsLoaded() ? (MHMOD7.MODL->MODB.IsLoaded() ? &MHMOD7.MODL->MODB.value : NULL) : NULL;
        case 92: //maleRightEye_modt_p
            *FieldValues = MHMOD7.MODL.IsLoaded() ? MHMOD7.MODL->MODT.value : NULL;
            return NULL;
        case 93: //maleRightEye_altTextures
            if(!MHMOD7.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MHMOD7.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MHMOD7.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MHMOD7.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MHMOD7.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 94: //maleRightEye_modelFlags
            return MHMOD7.MODL.IsLoaded() ? (MHMOD7.MODL->MODD.IsLoaded() ? &MHMOD7.MODL->MODD.value : NULL) : NULL;
        case 95: //maleRightEye_iconPath
            return MHMOD7.ICON.value;
        case 96: //maleRightEye_smallIconPath
            return MHMOD7.MICO.value;
        case 97: //femaleHead_modPath
            return FHMOD0.MODL.IsLoaded() ? FHMOD0.MODL->MODL.value : NULL;
        case 98: //femaleHead_modb
            return FHMOD0.MODL.IsLoaded() ? (FHMOD0.MODL->MODB.IsLoaded() ? &FHMOD0.MODL->MODB.value : NULL) : NULL;
        case 99: //femaleHead_modt_p
            *FieldValues = FHMOD0.MODL.IsLoaded() ? FHMOD0.MODL->MODT.value : NULL;
            return NULL;
        case 100: //femaleHead_altTextures
            if(!FHMOD0.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD0.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD0.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD0.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD0.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 101: //femaleHead_modelFlags
            return FHMOD0.MODL.IsLoaded() ? (FHMOD0.MODL->MODD.IsLoaded() ? &FHMOD0.MODL->MODD.value : NULL) : NULL;
        case 102: //femaleHead_iconPath
            return FHMOD0.ICON.value;
        case 103: //femaleHead_smallIconPath
            return FHMOD0.MICO.value;
        case 104: //femaleEars_modPath
            return FHMOD1.MODL.IsLoaded() ? FHMOD1.MODL->MODL.value : NULL;
        case 105: //femaleEars_modb
            return FHMOD1.MODL.IsLoaded() ? (FHMOD1.MODL->MODB.IsLoaded() ? &FHMOD1.MODL->MODB.value : NULL) : NULL;
        case 106: //femaleEars_modt_p
            *FieldValues = FHMOD1.MODL.IsLoaded() ? FHMOD1.MODL->MODT.value : NULL;
            return NULL;
        case 107: //femaleEars_altTextures
            if(!FHMOD1.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD1.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD1.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD1.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD1.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 108: //femaleEars_modelFlags
            return FHMOD1.MODL.IsLoaded() ? (FHMOD1.MODL->MODD.IsLoaded() ? &FHMOD1.MODL->MODD.value : NULL) : NULL;
        case 109: //femaleEars_iconPath
            return FHMOD1.ICON.value;
        case 110: //femaleEars_smallIconPath
            return FHMOD1.MICO.value;
        case 111: //femaleMouth_modPath
            return FHMOD2.MODL.IsLoaded() ? FHMOD2.MODL->MODL.value : NULL;
        case 112: //femaleMouth_modb
            return FHMOD2.MODL.IsLoaded() ? (FHMOD2.MODL->MODB.IsLoaded() ? &FHMOD2.MODL->MODB.value : NULL) : NULL;
        case 113: //femaleMouth_modt_p
            *FieldValues = FHMOD2.MODL.IsLoaded() ? FHMOD2.MODL->MODT.value : NULL;
            return NULL;
        case 114: //femaleMouth_altTextures
            if(!FHMOD2.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD2.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD2.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD2.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD2.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 115: //femaleMouth_modelFlags
            return FHMOD2.MODL.IsLoaded() ? (FHMOD2.MODL->MODD.IsLoaded() ? &FHMOD2.MODL->MODD.value : NULL) : NULL;
        case 116: //femaleMouth_iconPath
            return FHMOD2.ICON.value;
        case 117: //femaleMouth_smallIconPath
            return FHMOD2.MICO.value;
        case 118: //femaleTeethLower_modPath
            return FHMOD3.MODL.IsLoaded() ? FHMOD3.MODL->MODL.value : NULL;
        case 119: //femaleTeethLower_modb
            return FHMOD3.MODL.IsLoaded() ? (FHMOD3.MODL->MODB.IsLoaded() ? &FHMOD3.MODL->MODB.value : NULL) : NULL;
        case 120: //femaleTeethLower_modt_p
            *FieldValues = FHMOD3.MODL.IsLoaded() ? FHMOD3.MODL->MODT.value : NULL;
            return NULL;
        case 121: //femaleTeethLower_altTextures
            if(!FHMOD3.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD3.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD3.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD3.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD3.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 122: //femaleTeethLower_modelFlags
            return FHMOD3.MODL.IsLoaded() ? (FHMOD3.MODL->MODD.IsLoaded() ? &FHMOD3.MODL->MODD.value : NULL) : NULL;
        case 123: //femaleTeethLower_iconPath
            return FHMOD3.ICON.value;
        case 124: //femaleTeethLower_smallIconPath
            return FHMOD3.MICO.value;
        case 125: //femaleTeethUpper_modPath
            return FHMOD4.MODL.IsLoaded() ? FHMOD4.MODL->MODL.value : NULL;
        case 126: //femaleTeethUpper_modb
            return FHMOD4.MODL.IsLoaded() ? (FHMOD4.MODL->MODB.IsLoaded() ? &FHMOD4.MODL->MODB.value : NULL) : NULL;
        case 127: //femaleTeethUpper_modt_p
            *FieldValues = FHMOD4.MODL.IsLoaded() ? FHMOD4.MODL->MODT.value : NULL;
            return NULL;
        case 128: //femaleTeethUpper_altTextures
            if(!FHMOD4.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD4.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD4.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD4.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD4.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 129: //femaleTeethUpper_modelFlags
            return FHMOD4.MODL.IsLoaded() ? (FHMOD4.MODL->MODD.IsLoaded() ? &FHMOD4.MODL->MODD.value : NULL) : NULL;
        case 130: //femaleTeethUpper_iconPath
            return FHMOD4.ICON.value;
        case 131: //femaleTeethUpper_smallIconPath
            return FHMOD4.MICO.value;
        case 132: //femaleTongue_modPath
            return FHMOD5.MODL.IsLoaded() ? FHMOD5.MODL->MODL.value : NULL;
        case 133: //femaleTongue_modb
            return FHMOD5.MODL.IsLoaded() ? (FHMOD5.MODL->MODB.IsLoaded() ? &FHMOD5.MODL->MODB.value : NULL) : NULL;
        case 134: //femaleTongue_modt_p
            *FieldValues = FHMOD5.MODL.IsLoaded() ? FHMOD5.MODL->MODT.value : NULL;
            return NULL;
        case 135: //femaleTongue_altTextures
            if(!FHMOD5.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD5.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD5.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD5.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD5.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 136: //femaleTongue_modelFlags
            return FHMOD5.MODL.IsLoaded() ? (FHMOD5.MODL->MODD.IsLoaded() ? &FHMOD5.MODL->MODD.value : NULL) : NULL;
        case 137: //femaleTongue_iconPath
            return FHMOD5.ICON.value;
        case 138: //femaleTongue_smallIconPath
            return FHMOD5.MICO.value;
        case 139: //femaleLeftEye_modPath
            return FHMOD6.MODL.IsLoaded() ? FHMOD6.MODL->MODL.value : NULL;
        case 140: //femaleLeftEye_modb
            return FHMOD6.MODL.IsLoaded() ? (FHMOD6.MODL->MODB.IsLoaded() ? &FHMOD6.MODL->MODB.value : NULL) : NULL;
        case 141: //femaleLeftEye_modt_p
            *FieldValues = FHMOD6.MODL.IsLoaded() ? FHMOD6.MODL->MODT.value : NULL;
            return NULL;
        case 142: //femaleLeftEye_altTextures
            if(!FHMOD6.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD6.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD6.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD6.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD6.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 143: //femaleLeftEye_modelFlags
            return FHMOD6.MODL.IsLoaded() ? (FHMOD6.MODL->MODD.IsLoaded() ? &FHMOD6.MODL->MODD.value : NULL) : NULL;
        case 144: //femaleLeftEye_iconPath
            return FHMOD6.ICON.value;
        case 145: //femaleLeftEye_smallIconPath
            return FHMOD6.MICO.value;
        case 146: //femaleRightEye_modPath
            return FHMOD7.MODL.IsLoaded() ? FHMOD7.MODL->MODL.value : NULL;
        case 147: //femaleRightEye_modb
            return FHMOD7.MODL.IsLoaded() ? (FHMOD7.MODL->MODB.IsLoaded() ? &FHMOD7.MODL->MODB.value : NULL) : NULL;
        case 148: //femaleRightEye_modt_p
            *FieldValues = FHMOD7.MODL.IsLoaded() ? FHMOD7.MODL->MODT.value : NULL;
            return NULL;
        case 149: //femaleRightEye_altTextures
            if(!FHMOD7.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FHMOD7.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FHMOD7.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FHMOD7.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FHMOD7.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 150: //femaleRightEye_modelFlags
            return FHMOD7.MODL.IsLoaded() ? (FHMOD7.MODL->MODD.IsLoaded() ? &FHMOD7.MODL->MODD.value : NULL) : NULL;
        case 151: //femaleRightEye_iconPath
            return FHMOD7.ICON.value;
        case 152: //femaleRightEye_smallIconPath
            return FHMOD7.MICO.value;
        case 153: //maleUpperBody_modPath
            return MBMOD0.MODL.IsLoaded() ? MBMOD0.MODL->MODL.value : NULL;
        case 154: //maleUpperBody_modb
            return MBMOD0.MODL.IsLoaded() ? (MBMOD0.MODL->MODB.IsLoaded() ? &MBMOD0.MODL->MODB.value : NULL) : NULL;
        case 155: //maleUpperBody_modt_p
            *FieldValues = MBMOD0.MODL.IsLoaded() ? MBMOD0.MODL->MODT.value : NULL;
            return NULL;
        case 156: //maleUpperBody_altTextures
            if(!MBMOD0.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MBMOD0.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MBMOD0.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MBMOD0.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MBMOD0.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 157: //maleUpperBody_modelFlags
            return MBMOD0.MODL.IsLoaded() ? (MBMOD0.MODL->MODD.IsLoaded() ? &MBMOD0.MODL->MODD.value : NULL) : NULL;
        case 158: //maleUpperBody_iconPath
            return MBMOD0.ICON.value;
        case 159: //maleUpperBody_smallIconPath
            return MBMOD0.MICO.value;
        case 160: //maleLeftHand_modPath
            return MBMOD1.MODL.IsLoaded() ? MBMOD1.MODL->MODL.value : NULL;
        case 161: //maleLeftHand_modb
            return MBMOD1.MODL.IsLoaded() ? (MBMOD1.MODL->MODB.IsLoaded() ? &MBMOD1.MODL->MODB.value : NULL) : NULL;
        case 162: //maleLeftHand_modt_p
            *FieldValues = MBMOD1.MODL.IsLoaded() ? MBMOD1.MODL->MODT.value : NULL;
            return NULL;
        case 163: //maleLeftHand_altTextures
            if(!MBMOD1.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MBMOD1.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MBMOD1.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MBMOD1.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MBMOD1.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 164: //maleLeftHand_modelFlags
            return MBMOD1.MODL.IsLoaded() ? (MBMOD1.MODL->MODD.IsLoaded() ? &MBMOD1.MODL->MODD.value : NULL) : NULL;
        case 165: //maleLeftHand_iconPath
            return MBMOD1.ICON.value;
        case 166: //maleLeftHand_smallIconPath
            return MBMOD1.MICO.value;
        case 167: //maleRightHand_modPath
            return MBMOD2.MODL.IsLoaded() ? MBMOD2.MODL->MODL.value : NULL;
        case 168: //maleRightHand_modb
            return MBMOD2.MODL.IsLoaded() ? (MBMOD2.MODL->MODB.IsLoaded() ? &MBMOD2.MODL->MODB.value : NULL) : NULL;
        case 169: //maleRightHand_modt_p
            *FieldValues = MBMOD2.MODL.IsLoaded() ? MBMOD2.MODL->MODT.value : NULL;
            return NULL;
        case 170: //maleRightHand_altTextures
            if(!MBMOD2.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MBMOD2.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MBMOD2.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MBMOD2.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MBMOD2.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 171: //maleRightHand_modelFlags
            return MBMOD2.MODL.IsLoaded() ? (MBMOD2.MODL->MODD.IsLoaded() ? &MBMOD2.MODL->MODD.value : NULL) : NULL;
        case 172: //maleRightHand_iconPath
            return MBMOD2.ICON.value;
        case 173: //maleRightHand_smallIconPath
            return MBMOD2.MICO.value;
        case 174: //maleUpperBodyTexture_modPath
            return MBMOD3.MODL.IsLoaded() ? MBMOD3.MODL->MODL.value : NULL;
        case 175: //maleUpperBodyTexture_modb
            return MBMOD3.MODL.IsLoaded() ? (MBMOD3.MODL->MODB.IsLoaded() ? &MBMOD3.MODL->MODB.value : NULL) : NULL;
        case 176: //maleUpperBodyTexture_modt_p
            *FieldValues = MBMOD3.MODL.IsLoaded() ? MBMOD3.MODL->MODT.value : NULL;
            return NULL;
        case 177: //maleUpperBodyTexture_altTextures
            if(!MBMOD3.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MBMOD3.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MBMOD3.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MBMOD3.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MBMOD3.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 178: //maleUpperBodyTexture_modelFlags
            return MBMOD3.MODL.IsLoaded() ? (MBMOD3.MODL->MODD.IsLoaded() ? &MBMOD3.MODL->MODD.value : NULL) : NULL;
        case 179: //maleUpperBodyTexture_iconPath
            return MBMOD3.ICON.value;
        case 180: //maleUpperBodyTexture_smallIconPath
            return MBMOD3.MICO.value;
        case 181: //femaleUpperBody_modPath
            return FBMOD0.MODL.IsLoaded() ? FBMOD0.MODL->MODL.value : NULL;
        case 182: //femaleUpperBody_modb
            return FBMOD0.MODL.IsLoaded() ? (FBMOD0.MODL->MODB.IsLoaded() ? &FBMOD0.MODL->MODB.value : NULL) : NULL;
        case 183: //femaleUpperBody_modt_p
            *FieldValues = FBMOD0.MODL.IsLoaded() ? FBMOD0.MODL->MODT.value : NULL;
            return NULL;
        case 184: //femaleUpperBody_altTextures
            if(!FBMOD0.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FBMOD0.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FBMOD0.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FBMOD0.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FBMOD0.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 185: //femaleUpperBody_modelFlags
            return FBMOD0.MODL.IsLoaded() ? (FBMOD0.MODL->MODD.IsLoaded() ? &FBMOD0.MODL->MODD.value : NULL) : NULL;
        case 186: //femaleUpperBody_iconPath
            return FBMOD0.ICON.value;
        case 187: //femaleUpperBody_smallIconPath
            return FBMOD0.MICO.value;
        case 188: //femaleLeftHand_modPath
            return FBMOD1.MODL.IsLoaded() ? FBMOD1.MODL->MODL.value : NULL;
        case 189: //femaleLeftHand_modb
            return FBMOD1.MODL.IsLoaded() ? (FBMOD1.MODL->MODB.IsLoaded() ? &FBMOD1.MODL->MODB.value : NULL) : NULL;
        case 190: //femaleLeftHand_modt_p
            *FieldValues = FBMOD1.MODL.IsLoaded() ? FBMOD1.MODL->MODT.value : NULL;
            return NULL;
        case 191: //femaleLeftHand_altTextures
            if(!FBMOD1.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FBMOD1.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FBMOD1.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FBMOD1.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FBMOD1.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 192: //femaleLeftHand_modelFlags
            return FBMOD1.MODL.IsLoaded() ? (FBMOD1.MODL->MODD.IsLoaded() ? &FBMOD1.MODL->MODD.value : NULL) : NULL;
        case 193: //femaleLeftHand_iconPath
            return FBMOD1.ICON.value;
        case 194: //femaleLeftHand_smallIconPath
            return FBMOD1.MICO.value;
        case 195: //femaleRightHand_modPath
            return FBMOD2.MODL.IsLoaded() ? FBMOD2.MODL->MODL.value : NULL;
        case 196: //femaleRightHand_modb
            return FBMOD2.MODL.IsLoaded() ? (FBMOD2.MODL->MODB.IsLoaded() ? &FBMOD2.MODL->MODB.value : NULL) : NULL;
        case 197: //femaleRightHand_modt_p
            *FieldValues = FBMOD2.MODL.IsLoaded() ? FBMOD2.MODL->MODT.value : NULL;
            return NULL;
        case 198: //femaleRightHand_altTextures
            if(!FBMOD2.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FBMOD2.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FBMOD2.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FBMOD2.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FBMOD2.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 199: //femaleRightHand_modelFlags
            return FBMOD2.MODL.IsLoaded() ? (FBMOD2.MODL->MODD.IsLoaded() ? &FBMOD2.MODL->MODD.value : NULL) : NULL;
        case 200: //femaleRightHand_iconPath
            return FBMOD2.ICON.value;
        case 201: //femaleRightHand_smallIconPath
            return FBMOD2.MICO.value;
        case 202: //femaleUpperBodyTexture_modPath
            return FBMOD3.MODL.IsLoaded() ? FBMOD3.MODL->MODL.value : NULL;
        case 203: //femaleUpperBodyTexture_modb
            return FBMOD3.MODL.IsLoaded() ? (FBMOD3.MODL->MODB.IsLoaded() ? &FBMOD3.MODL->MODB.value : NULL) : NULL;
        case 204: //femaleUpperBodyTexture_modt_p
            *FieldValues = FBMOD3.MODL.IsLoaded() ? FBMOD3.MODL->MODT.value : NULL;
            return NULL;
        case 205: //femaleUpperBodyTexture_altTextures
            if(!FBMOD3.MODL.IsLoaded())
                return NULL;

            if(ListIndex >= FBMOD3.MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return FBMOD3.MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &FBMOD3.MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &FBMOD3.MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 206: //femaleUpperBodyTexture_modelFlags
            return FBMOD3.MODL.IsLoaded() ? (FBMOD3.MODL->MODD.IsLoaded() ? &FBMOD3.MODL->MODD.value : NULL) : NULL;
        case 207: //femaleUpperBodyTexture_iconPath
            return FBMOD3.ICON.value;
        case 208: //femaleUpperBodyTexture_smallIconPath
            return FBMOD3.MICO.value;
        case 209: //hairs
            *FieldValues = HNAM.value.size() ? &HNAM.value[0] : NULL;
            return NULL;
        case 210: //eyes
            *FieldValues = ENAM.value.size() ? &ENAM.value[0] : NULL;
            return NULL;
        case 211: //maleFggs_p
            *FieldValues = MaleFGGS.value;
            return NULL;
        case 212: //maleFgga_p
            *FieldValues = MaleFGGA.value;
            return NULL;
        case 213: //maleFgts_p
            *FieldValues = MaleFGTS.value;
            return NULL;
        case 214: //maleSnam_p
            *FieldValues = &MaleSNAM.value.SNAM[0];
            return NULL;
        case 215: //femaleFggs_p
            *FieldValues = FemaleFGGS.value;
            return NULL;
        case 216: //femaleFgga_p
            *FieldValues = FemaleFGGA.value;
            return NULL;
        case 217: //femaleFgts_p
            *FieldValues = FemaleFGTS.value;
            return NULL;
        case 218: //femaleSnam_p
            *FieldValues = &FemaleSNAM.value.SNAM[0];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool RACERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 9: //relations
            if(ListFieldID == 0) //relationsSize
                {
                XNAM.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XNAM.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = *(FORMID *)FieldValue;
                    return true;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = *(int32_t *)FieldValue;
                    break;
                case 3: //groupReactionType
                    XNAM.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 10: //skill1
            DATA.value.skills[0].value = *(int8_t *)FieldValue;
            break;
        case 11: //skill1Boost
            DATA.value.skills[0].boost = *(int8_t *)FieldValue;
            break;
        case 12: //skill2
            DATA.value.skills[1].value = *(int8_t *)FieldValue;
            break;
        case 13: //skill2Boost
            DATA.value.skills[1].boost = *(int8_t *)FieldValue;
            break;
        case 14: //skill3
            DATA.value.skills[2].value = *(int8_t *)FieldValue;
            break;
        case 15: //skill3Boost
            DATA.value.skills[2].boost = *(int8_t *)FieldValue;
            break;
        case 16: //skill4
            DATA.value.skills[3].value = *(int8_t *)FieldValue;
            break;
        case 17: //skill4Boost
            DATA.value.skills[3].boost = *(int8_t *)FieldValue;
            break;
        case 18: //skill5
            DATA.value.skills[4].value = *(int8_t *)FieldValue;
            break;
        case 19: //skill5Boost
            DATA.value.skills[4].boost = *(int8_t *)FieldValue;
            break;
        case 20: //skill6
            DATA.value.skills[5].value = *(int8_t *)FieldValue;
            break;
        case 21: //skill6Boost
            DATA.value.skills[5].boost = *(int8_t *)FieldValue;
            break;
        case 22: //skill7
            DATA.value.skills[6].value = *(int8_t *)FieldValue;
            break;
        case 23: //skill7Boost
            DATA.value.skills[6].boost = *(int8_t *)FieldValue;
            break;
        case 24: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 25: //maleHeight
            DATA.value.maleHeight = *(float *)FieldValue;
            break;
        case 26: //femaleHeight
            DATA.value.femaleHeight = *(float *)FieldValue;
            break;
        case 27: //maleWeight
            DATA.value.maleWeight = *(float *)FieldValue;
            break;
        case 28: //femaleWeight
            DATA.value.femaleWeight = *(float *)FieldValue;
            break;
        case 29: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 30: //older
            ONAM.value = *(FORMID *)FieldValue;
            return true;
        case 31: //younger
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 32: //maleVoice
            VTCK.Load();
            VTCK.value.maleVoice = *(FORMID *)FieldValue;
            return true;
        case 33: //femaleVoice
            VTCK.Load();
            VTCK.value.femaleVoice = *(FORMID *)FieldValue;
            return true;
        case 34: //defaultHairMale
            DNAM.Load();
            DNAM.value.defaultHairMale = *(FORMID *)FieldValue;
            return true;
        case 35: //defaultHairFemale
            DNAM.Load();
            DNAM.value.defaultHairFemale = *(FORMID *)FieldValue;
            return true;
        case 36: //defaultHairMaleColor
            CNAM.Load();
            CNAM.value.defaultHairMale = *(uint8_t *)FieldValue;
            break;
        case 37: //defaultHairFemaleColor
            CNAM.Load();
            CNAM.value.defaultHairFemale = *(uint8_t *)FieldValue;
            break;
        case 38: //mainClamp
            PNAM.value = *(float *)FieldValue;
            break;
        case 39: //faceClamp
            UNAM.value = *(float *)FieldValue;
            break;
        case 40: //attr_p
            ATTR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 41: //maleHead_modPath
            MHMOD0.MODL.Load();
            MHMOD0.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 42: //maleHead_modb
            MHMOD0.MODL.Load();
            MHMOD0.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 43: //maleHead_modt_p
            MHMOD0.MODL.Load();
            MHMOD0.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 44: //maleHead_altTextures
            MHMOD0.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD0.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD0.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD0.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD0.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD0.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD0.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD0.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 45: //maleHead_modelFlags
            MHMOD0.MODL.Load();
            MHMOD0.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 46: //maleHead_iconPath
            MHMOD0.ICON.Copy((char *)FieldValue);
            break;
        case 47: //maleHead_smallIconPath
            MHMOD0.MICO.Copy((char *)FieldValue);
            break;
        case 48: //maleEars_modPath
            MHMOD1.MODL.Load();
            MHMOD1.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 49: //maleEars_modb
            MHMOD1.MODL.Load();
            MHMOD1.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 50: //maleEars_modt_p
            MHMOD1.MODL.Load();
            MHMOD1.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 51: //maleEars_altTextures
            MHMOD1.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD1.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD1.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD1.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD1.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD1.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD1.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD1.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 52: //maleEars_modelFlags
            MHMOD1.MODL.Load();
            MHMOD1.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 53: //maleEars_iconPath
            MHMOD1.ICON.Copy((char *)FieldValue);
            break;
        case 54: //maleEars_smallIconPath
            MHMOD1.MICO.Copy((char *)FieldValue);
            break;
        case 55: //maleMouth_modPath
            MHMOD2.MODL.Load();
            MHMOD2.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 56: //maleMouth_modb
            MHMOD2.MODL.Load();
            MHMOD2.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 57: //maleMouth_modt_p
            MHMOD2.MODL.Load();
            MHMOD2.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 58: //maleMouth_altTextures
            MHMOD2.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD2.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD2.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD2.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD2.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD2.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD2.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD2.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 59: //maleMouth_modelFlags
            MHMOD2.MODL.Load();
            MHMOD2.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 60: //maleMouth_iconPath
            MHMOD2.ICON.Copy((char *)FieldValue);
            break;
        case 61: //maleMouth_smallIconPath
            MHMOD2.MICO.Copy((char *)FieldValue);
            break;
        case 62: //maleTeethLower_modPath
            MHMOD3.MODL.Load();
            MHMOD3.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 63: //maleTeethLower_modb
            MHMOD3.MODL.Load();
            MHMOD3.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 64: //maleTeethLower_modt_p
            MHMOD3.MODL.Load();
            MHMOD3.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 65: //maleTeethLower_altTextures
            MHMOD3.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD3.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD3.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD3.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD3.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD3.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD3.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD3.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 66: //maleTeethLower_modelFlags
            MHMOD3.MODL.Load();
            MHMOD3.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 67: //maleTeethLower_iconPath
            MHMOD3.ICON.Copy((char *)FieldValue);
            break;
        case 68: //maleTeethLower_smallIconPath
            MHMOD3.MICO.Copy((char *)FieldValue);
            break;
        case 69: //maleTeethUpper_modPath
            MHMOD4.MODL.Load();
            MHMOD4.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 70: //maleTeethUpper_modb
            MHMOD4.MODL.Load();
            MHMOD4.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 71: //maleTeethUpper_modt_p
            MHMOD4.MODL.Load();
            MHMOD4.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 72: //maleTeethUpper_altTextures
            MHMOD4.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD4.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD4.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD4.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD4.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD4.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD4.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD4.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD4.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 73: //maleTeethUpper_modelFlags
            MHMOD4.MODL.Load();
            MHMOD4.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 74: //maleTeethUpper_iconPath
            MHMOD4.ICON.Copy((char *)FieldValue);
            break;
        case 75: //maleTeethUpper_smallIconPath
            MHMOD4.MICO.Copy((char *)FieldValue);
            break;
        case 76: //maleTongue_modPath
            MHMOD5.MODL.Load();
            MHMOD5.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 77: //maleTongue_modb
            MHMOD5.MODL.Load();
            MHMOD5.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 78: //maleTongue_modt_p
            MHMOD5.MODL.Load();
            MHMOD5.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 79: //maleTongue_altTextures
            MHMOD5.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD5.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD5.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD5.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD5.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD5.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD5.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD5.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD5.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 80: //maleTongue_modelFlags
            MHMOD5.MODL.Load();
            MHMOD5.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 81: //maleTongue_iconPath
            MHMOD5.ICON.Copy((char *)FieldValue);
            break;
        case 82: //maleTongue_smallIconPath
            MHMOD5.MICO.Copy((char *)FieldValue);
            break;
        case 83: //maleLeftEye_modPath
            MHMOD6.MODL.Load();
            MHMOD6.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 84: //maleLeftEye_modb
            MHMOD6.MODL.Load();
            MHMOD6.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 85: //maleLeftEye_modt_p
            MHMOD6.MODL.Load();
            MHMOD6.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 86: //maleLeftEye_altTextures
            MHMOD6.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD6.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD6.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD6.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD6.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD6.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD6.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD6.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD6.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 87: //maleLeftEye_modelFlags
            MHMOD6.MODL.Load();
            MHMOD6.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 88: //maleLeftEye_iconPath
            MHMOD6.ICON.Copy((char *)FieldValue);
            break;
        case 89: //maleLeftEye_smallIconPath
            MHMOD6.MICO.Copy((char *)FieldValue);
            break;
        case 90: //maleRightEye_modPath
            MHMOD7.MODL.Load();
            MHMOD7.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 91: //maleRightEye_modb
            MHMOD7.MODL.Load();
            MHMOD7.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 92: //maleRightEye_modt_p
            MHMOD7.MODL.Load();
            MHMOD7.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 93: //maleRightEye_altTextures
            MHMOD7.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MHMOD7.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MHMOD7.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MHMOD7.MODL->Textures.MODS[ListIndex]->name;
                    MHMOD7.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MHMOD7.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MHMOD7.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MHMOD7.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MHMOD7.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 94: //maleRightEye_modelFlags
            MHMOD7.MODL.Load();
            MHMOD7.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 95: //maleRightEye_iconPath
            MHMOD7.ICON.Copy((char *)FieldValue);
            break;
        case 96: //maleRightEye_smallIconPath
            MHMOD7.MICO.Copy((char *)FieldValue);
            break;
        case 97: //femaleHead_modPath
            FHMOD0.MODL.Load();
            FHMOD0.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 98: //femaleHead_modb
            FHMOD0.MODL.Load();
            FHMOD0.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 99: //femaleHead_modt_p
            FHMOD0.MODL.Load();
            FHMOD0.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 100: //femaleHead_altTextures
            FHMOD0.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD0.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD0.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD0.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD0.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD0.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD0.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD0.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 101: //femaleHead_modelFlags
            FHMOD0.MODL.Load();
            FHMOD0.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 102: //femaleHead_iconPath
            FHMOD0.ICON.Copy((char *)FieldValue);
            break;
        case 103: //femaleHead_smallIconPath
            FHMOD0.MICO.Copy((char *)FieldValue);
            break;
        case 104: //femaleEars_modPath
            FHMOD1.MODL.Load();
            FHMOD1.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 105: //femaleEars_modb
            FHMOD1.MODL.Load();
            FHMOD1.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 106: //femaleEars_modt_p
            FHMOD1.MODL.Load();
            FHMOD1.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 107: //femaleEars_altTextures
            FHMOD1.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD1.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD1.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD1.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD1.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD1.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD1.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD1.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 108: //femaleEars_modelFlags
            FHMOD1.MODL.Load();
            FHMOD1.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 109: //femaleEars_iconPath
            FHMOD1.ICON.Copy((char *)FieldValue);
            break;
        case 110: //femaleEars_smallIconPath
            FHMOD1.MICO.Copy((char *)FieldValue);
            break;
        case 111: //femaleMouth_modPath
            FHMOD2.MODL.Load();
            FHMOD2.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 112: //femaleMouth_modb
            FHMOD2.MODL.Load();
            FHMOD2.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 113: //femaleMouth_modt_p
            FHMOD2.MODL.Load();
            FHMOD2.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 114: //femaleMouth_altTextures
            FHMOD2.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD2.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD2.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD2.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD2.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD2.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD2.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD2.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 115: //femaleMouth_modelFlags
            FHMOD2.MODL.Load();
            FHMOD2.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 116: //femaleMouth_iconPath
            FHMOD2.ICON.Copy((char *)FieldValue);
            break;
        case 117: //femaleMouth_smallIconPath
            FHMOD2.MICO.Copy((char *)FieldValue);
            break;
        case 118: //femaleTeethLower_modPath
            FHMOD3.MODL.Load();
            FHMOD3.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 119: //femaleTeethLower_modb
            FHMOD3.MODL.Load();
            FHMOD3.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 120: //femaleTeethLower_modt_p
            FHMOD3.MODL.Load();
            FHMOD3.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 121: //femaleTeethLower_altTextures
            FHMOD3.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD3.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD3.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD3.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD3.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD3.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD3.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD3.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 122: //femaleTeethLower_modelFlags
            FHMOD3.MODL.Load();
            FHMOD3.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 123: //femaleTeethLower_iconPath
            FHMOD3.ICON.Copy((char *)FieldValue);
            break;
        case 124: //femaleTeethLower_smallIconPath
            FHMOD3.MICO.Copy((char *)FieldValue);
            break;
        case 125: //femaleTeethUpper_modPath
            FHMOD4.MODL.Load();
            FHMOD4.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 126: //femaleTeethUpper_modb
            FHMOD4.MODL.Load();
            FHMOD4.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 127: //femaleTeethUpper_modt_p
            FHMOD4.MODL.Load();
            FHMOD4.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 128: //femaleTeethUpper_altTextures
            FHMOD4.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD4.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD4.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD4.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD4.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD4.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD4.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD4.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD4.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 129: //femaleTeethUpper_modelFlags
            FHMOD4.MODL.Load();
            FHMOD4.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 130: //femaleTeethUpper_iconPath
            FHMOD4.ICON.Copy((char *)FieldValue);
            break;
        case 131: //femaleTeethUpper_smallIconPath
            FHMOD4.MICO.Copy((char *)FieldValue);
            break;
        case 132: //femaleTongue_modPath
            FHMOD5.MODL.Load();
            FHMOD5.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 133: //femaleTongue_modb
            FHMOD5.MODL.Load();
            FHMOD5.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 134: //femaleTongue_modt_p
            FHMOD5.MODL.Load();
            FHMOD5.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 135: //femaleTongue_altTextures
            FHMOD5.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD5.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD5.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD5.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD5.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD5.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD5.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD5.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD5.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 136: //femaleTongue_modelFlags
            FHMOD5.MODL.Load();
            FHMOD5.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 137: //femaleTongue_iconPath
            FHMOD5.ICON.Copy((char *)FieldValue);
            break;
        case 138: //femaleTongue_smallIconPath
            FHMOD5.MICO.Copy((char *)FieldValue);
            break;
        case 139: //femaleLeftEye_modPath
            FHMOD6.MODL.Load();
            FHMOD6.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 140: //femaleLeftEye_modb
            FHMOD6.MODL.Load();
            FHMOD6.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 141: //femaleLeftEye_modt_p
            FHMOD6.MODL.Load();
            FHMOD6.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 142: //femaleLeftEye_altTextures
            FHMOD6.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD6.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD6.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD6.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD6.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD6.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD6.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD6.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD6.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 143: //femaleLeftEye_modelFlags
            FHMOD6.MODL.Load();
            FHMOD6.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 144: //femaleLeftEye_iconPath
            FHMOD6.ICON.Copy((char *)FieldValue);
            break;
        case 145: //femaleLeftEye_smallIconPath
            FHMOD6.MICO.Copy((char *)FieldValue);
            break;
        case 146: //femaleRightEye_modPath
            FHMOD7.MODL.Load();
            FHMOD7.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 147: //femaleRightEye_modb
            FHMOD7.MODL.Load();
            FHMOD7.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 148: //femaleRightEye_modt_p
            FHMOD7.MODL.Load();
            FHMOD7.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 149: //femaleRightEye_altTextures
            FHMOD7.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FHMOD7.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FHMOD7.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FHMOD7.MODL->Textures.MODS[ListIndex]->name;
                    FHMOD7.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FHMOD7.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FHMOD7.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FHMOD7.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FHMOD7.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 150: //femaleRightEye_modelFlags
            FHMOD7.MODL.Load();
            FHMOD7.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 151: //femaleRightEye_iconPath
            FHMOD7.ICON.Copy((char *)FieldValue);
            break;
        case 152: //femaleRightEye_smallIconPath
            FHMOD7.MICO.Copy((char *)FieldValue);
            break;
        case 153: //maleUpperBody_modPath
            MBMOD0.MODL.Load();
            MBMOD0.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 154: //maleUpperBody_modb
            MBMOD0.MODL.Load();
            MBMOD0.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 155: //maleUpperBody_modt_p
            MBMOD0.MODL.Load();
            MBMOD0.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 156: //maleUpperBody_altTextures
            MBMOD0.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MBMOD0.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MBMOD0.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MBMOD0.MODL->Textures.MODS[ListIndex]->name;
                    MBMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MBMOD0.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MBMOD0.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MBMOD0.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MBMOD0.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 157: //maleUpperBody_modelFlags
            MBMOD0.MODL.Load();
            MBMOD0.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 158: //maleUpperBody_iconPath
            MBMOD0.ICON.Copy((char *)FieldValue);
            break;
        case 159: //maleUpperBody_smallIconPath
            MBMOD0.MICO.Copy((char *)FieldValue);
            break;
        case 160: //maleLeftHand_modPath
            MBMOD1.MODL.Load();
            MBMOD1.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 161: //maleLeftHand_modb
            MBMOD1.MODL.Load();
            MBMOD1.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 162: //maleLeftHand_modt_p
            MBMOD1.MODL.Load();
            MBMOD1.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 163: //maleLeftHand_altTextures
            MBMOD1.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MBMOD1.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MBMOD1.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MBMOD1.MODL->Textures.MODS[ListIndex]->name;
                    MBMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MBMOD1.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MBMOD1.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MBMOD1.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MBMOD1.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 164: //maleLeftHand_modelFlags
            MBMOD1.MODL.Load();
            MBMOD1.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 165: //maleLeftHand_iconPath
            MBMOD1.ICON.Copy((char *)FieldValue);
            break;
        case 166: //maleLeftHand_smallIconPath
            MBMOD1.MICO.Copy((char *)FieldValue);
            break;
        case 167: //maleRightHand_modPath
            MBMOD2.MODL.Load();
            MBMOD2.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 168: //maleRightHand_modb
            MBMOD2.MODL.Load();
            MBMOD2.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 169: //maleRightHand_modt_p
            MBMOD2.MODL.Load();
            MBMOD2.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 170: //maleRightHand_altTextures
            MBMOD2.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MBMOD2.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MBMOD2.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MBMOD2.MODL->Textures.MODS[ListIndex]->name;
                    MBMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MBMOD2.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MBMOD2.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MBMOD2.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MBMOD2.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 171: //maleRightHand_modelFlags
            MBMOD2.MODL.Load();
            MBMOD2.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 172: //maleRightHand_iconPath
            MBMOD2.ICON.Copy((char *)FieldValue);
            break;
        case 173: //maleRightHand_smallIconPath
            MBMOD2.MICO.Copy((char *)FieldValue);
            break;
        case 174: //maleUpperBodyTexture_modPath
            MBMOD3.MODL.Load();
            MBMOD3.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 175: //maleUpperBodyTexture_modb
            MBMOD3.MODL.Load();
            MBMOD3.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 176: //maleUpperBodyTexture_modt_p
            MBMOD3.MODL.Load();
            MBMOD3.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 177: //maleUpperBodyTexture_altTextures
            MBMOD3.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MBMOD3.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MBMOD3.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MBMOD3.MODL->Textures.MODS[ListIndex]->name;
                    MBMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MBMOD3.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MBMOD3.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MBMOD3.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MBMOD3.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 178: //maleUpperBodyTexture_modelFlags
            MBMOD3.MODL.Load();
            MBMOD3.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 179: //maleUpperBodyTexture_iconPath
            MBMOD3.ICON.Copy((char *)FieldValue);
            break;
        case 180: //maleUpperBodyTexture_smallIconPath
            MBMOD3.MICO.Copy((char *)FieldValue);
            break;
        case 181: //femaleUpperBody_modPath
            FBMOD0.MODL.Load();
            FBMOD0.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 182: //femaleUpperBody_modb
            FBMOD0.MODL.Load();
            FBMOD0.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 183: //femaleUpperBody_modt_p
            FBMOD0.MODL.Load();
            FBMOD0.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 184: //femaleUpperBody_altTextures
            FBMOD0.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FBMOD0.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FBMOD0.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FBMOD0.MODL->Textures.MODS[ListIndex]->name;
                    FBMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FBMOD0.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FBMOD0.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FBMOD0.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FBMOD0.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 185: //femaleUpperBody_modelFlags
            FBMOD0.MODL.Load();
            FBMOD0.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 186: //femaleUpperBody_iconPath
            FBMOD0.ICON.Copy((char *)FieldValue);
            break;
        case 187: //femaleUpperBody_smallIconPath
            FBMOD0.MICO.Copy((char *)FieldValue);
            break;
        case 188: //femaleLeftHand_modPath
            FBMOD1.MODL.Load();
            FBMOD1.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 189: //femaleLeftHand_modb
            FBMOD1.MODL.Load();
            FBMOD1.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 190: //femaleLeftHand_modt_p
            FBMOD1.MODL.Load();
            FBMOD1.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 191: //femaleLeftHand_altTextures
            FBMOD1.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FBMOD1.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FBMOD1.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FBMOD1.MODL->Textures.MODS[ListIndex]->name;
                    FBMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FBMOD1.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FBMOD1.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FBMOD1.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FBMOD1.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 192: //femaleLeftHand_modelFlags
            FBMOD1.MODL.Load();
            FBMOD1.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 193: //femaleLeftHand_iconPath
            FBMOD1.ICON.Copy((char *)FieldValue);
            break;
        case 194: //femaleLeftHand_smallIconPath
            FBMOD1.MICO.Copy((char *)FieldValue);
            break;
        case 195: //femaleRightHand_modPath
            FBMOD2.MODL.Load();
            FBMOD2.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 196: //femaleRightHand_modb
            FBMOD2.MODL.Load();
            FBMOD2.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 197: //femaleRightHand_modt_p
            FBMOD2.MODL.Load();
            FBMOD2.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 198: //femaleRightHand_altTextures
            FBMOD2.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FBMOD2.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FBMOD2.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FBMOD2.MODL->Textures.MODS[ListIndex]->name;
                    FBMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FBMOD2.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FBMOD2.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FBMOD2.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FBMOD2.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 199: //femaleRightHand_modelFlags
            FBMOD2.MODL.Load();
            FBMOD2.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 200: //femaleRightHand_iconPath
            FBMOD2.ICON.Copy((char *)FieldValue);
            break;
        case 201: //femaleRightHand_smallIconPath
            FBMOD2.MICO.Copy((char *)FieldValue);
            break;
        case 202: //femaleUpperBodyTexture_modPath
            FBMOD3.MODL.Load();
            FBMOD3.MODL->MODL.Copy((char *)FieldValue);
            break;
        case 203: //femaleUpperBodyTexture_modb
            FBMOD3.MODL.Load();
            FBMOD3.MODL->MODB.value = *(float *)FieldValue;
            break;
        case 204: //femaleUpperBodyTexture_modt_p
            FBMOD3.MODL.Load();
            FBMOD3.MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 205: //femaleUpperBodyTexture_altTextures
            FBMOD3.MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                FBMOD3.MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= FBMOD3.MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []FBMOD3.MODL->Textures.MODS[ListIndex]->name;
                    FBMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        FBMOD3.MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(FBMOD3.MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    FBMOD3.MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    FBMOD3.MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 206: //femaleUpperBodyTexture_modelFlags
            FBMOD3.MODL.Load();
            FBMOD3.MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 207: //femaleUpperBodyTexture_iconPath
            FBMOD3.ICON.Copy((char *)FieldValue);
            break;
        case 208: //femaleUpperBodyTexture_smallIconPath
            FBMOD3.MICO.Copy((char *)FieldValue);
            break;
        case 209: //hairs
            HNAM.value.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                HNAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 210: //eyes
            ENAM.value.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                ENAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 211: //maleFggs_p
            if(ArraySize != 200)
                break;
            MaleFGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 212: //maleFgga_p
            if(ArraySize != 120)
                break;
            MaleFGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 213: //maleFgts_p
            if(ArraySize != 200)
                break;
            MaleFGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 214: //maleSnam_p
            if(ArraySize != 2)
                break;
            MaleSNAM.value.SNAM[0] = ((UINT8ARRAY)FieldValue)[0];
            MaleSNAM.value.SNAM[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 215: //femaleFggs_p
            if(ArraySize != 200)
                break;
            FemaleFGGS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 216: //femaleFgga_p
            if(ArraySize != 120)
                break;
            FemaleFGGA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 217: //femaleFgts_p
            if(ArraySize != 200)
                break;
            FemaleFGTS.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 218: //femaleSnam_p
            if(ArraySize != 2)
                break;
            FemaleSNAM.value.SNAM[0] = ((UINT8ARRAY)FieldValue)[0];
            FemaleSNAM.value.SNAM[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        default:
            break;
        }
    return false;
    }

void RACERecord::DeleteField(FIELD_IDENTIFIERS)
    {
    RACEVNAM defaultVNAM;
    RACEDNAM defaultDNAM;
    RACECNAM defaultCNAM;
    FNVXNAM defaultXNAM;
    RACEDATA defaultDATA;
    FNVMODS defaultMODS;

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
        case 8: //description
            DESC.Unload();
            return;
        case 9: //relations
            if(ListFieldID == 0) //relations
                {
                XNAM.Unload();
                return;
                }

            if(ListIndex >= XNAM.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //faction
                    XNAM.value[ListIndex]->faction = defaultXNAM.faction;
                    return;
                case 2: //mod
                    XNAM.value[ListIndex]->mod = defaultXNAM.mod;
                    return;
                case 3: //groupReactionType
                    XNAM.value[ListIndex]->groupReactionType = defaultXNAM.groupReactionType;
                    return;
                default:
                    return;
                }
            return;
        case 10: //skill1
            DATA.value.skills[0].value = defaultDATA.skills[0].value;
            return;
        case 11: //skill1Boost
            DATA.value.skills[0].boost = defaultDATA.skills[0].boost;
            return;
        case 12: //skill2
            DATA.value.skills[1].value = defaultDATA.skills[1].value;
            return;
        case 13: //skill2Boost
            DATA.value.skills[1].boost = defaultDATA.skills[1].boost;
            return;
        case 14: //skill3
            DATA.value.skills[2].value = defaultDATA.skills[2].value;
            return;
        case 15: //skill3Boost
            DATA.value.skills[2].boost = defaultDATA.skills[2].boost;
            return;
        case 16: //skill4
            DATA.value.skills[3].value = defaultDATA.skills[3].value;
            return;
        case 17: //skill4Boost
            DATA.value.skills[3].boost = defaultDATA.skills[3].boost;
            return;
        case 18: //skill5
            DATA.value.skills[4].value = defaultDATA.skills[4].value;
            return;
        case 19: //skill5Boost
            DATA.value.skills[4].boost = defaultDATA.skills[4].boost;
            return;
        case 20: //skill6
            DATA.value.skills[5].value = defaultDATA.skills[5].value;
            return;
        case 21: //skill6Boost
            DATA.value.skills[5].boost = defaultDATA.skills[5].boost;
            return;
        case 22: //skill7
            DATA.value.skills[6].value = defaultDATA.skills[6].value;
            return;
        case 23: //skill7Boost
            DATA.value.skills[6].boost = defaultDATA.skills[6].boost;
            return;
        case 24: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 25: //maleHeight
            DATA.value.maleHeight = defaultDATA.maleHeight;
            return;
        case 26: //femaleHeight
            DATA.value.femaleHeight = defaultDATA.femaleHeight;
            return;
        case 27: //maleWeight
            DATA.value.maleWeight = defaultDATA.maleWeight;
            return;
        case 28: //femaleWeight
            DATA.value.femaleWeight = defaultDATA.femaleWeight;
            return;
        case 29: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 30: //older
            ONAM.Unload();
            return;
        case 31: //younger
            YNAM.Unload();
            return;
        case 32: //maleVoice
            if(VTCK.IsLoaded())
                VTCK.value.maleVoice = defaultVNAM.maleVoice;
            return;
        case 33: //femaleVoice
            if(VTCK.IsLoaded())
                VTCK.value.femaleVoice = defaultVNAM.femaleVoice;
            return;
        case 34: //defaultHairMale
            if(DNAM.IsLoaded())
                DNAM.value.defaultHairMale = defaultDNAM.defaultHairMale;
            return;
        case 35: //defaultHairFemale
            if(DNAM.IsLoaded())
                DNAM.value.defaultHairFemale = defaultDNAM.defaultHairFemale;
            return;
        case 36: //defaultHairMaleColor
            if(CNAM.IsLoaded())
                CNAM.value.defaultHairMale = defaultCNAM.defaultHairMale;
            return;
        case 37: //defaultHairFemaleColor
            if(CNAM.IsLoaded())
                CNAM.value.defaultHairFemale = defaultCNAM.defaultHairFemale;
            return;
        case 38: //mainClamp
            PNAM.Unload();
            return;
        case 39: //faceClamp
            UNAM.Unload();
            return;
        case 40: //attr_p
            ATTR.Unload();
            return;
        case 41: //maleHead_modPath
            if(MHMOD0.MODL.IsLoaded())
                MHMOD0.MODL->MODL.Unload();
            return;
        case 42: //maleHead_modb
            if(MHMOD0.MODL.IsLoaded())
                MHMOD0.MODL->MODB.Unload();
            return;
        case 43: //maleHead_modt_p
            if(MHMOD0.MODL.IsLoaded())
                MHMOD0.MODL->MODT.Unload();
            return;
        case 44: //maleHead_altTextures
            if(MHMOD0.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD0.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD0.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD0.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD0.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD0.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 45: //maleHead_modelFlags
            if(MHMOD0.MODL.IsLoaded())
                MHMOD0.MODL->MODD.Unload();
            return;
        case 46: //maleHead_iconPath
            MHMOD0.ICON.Unload();
            return;
        case 47: //maleHead_smallIconPath
            MHMOD0.MICO.Unload();
            return;
        case 48: //maleEars_modPath
            if(MHMOD1.MODL.IsLoaded())
                MHMOD1.MODL->MODL.Unload();
            return;
        case 49: //maleEars_modb
            if(MHMOD1.MODL.IsLoaded())
                MHMOD1.MODL->MODB.Unload();
            return;
        case 50: //maleEars_modt_p
            if(MHMOD1.MODL.IsLoaded())
                MHMOD1.MODL->MODT.Unload();
            return;
        case 51: //maleEars_altTextures
            if(MHMOD1.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD1.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD1.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD1.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD1.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD1.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 52: //maleEars_modelFlags
            if(MHMOD1.MODL.IsLoaded())
                MHMOD1.MODL->MODD.Unload();
            return;
        case 53: //maleEars_iconPath
            MHMOD1.ICON.Unload();
            return;
        case 54: //maleEars_smallIconPath
            MHMOD1.MICO.Unload();
            return;
        case 55: //maleMouth_modPath
            if(MHMOD2.MODL.IsLoaded())
                MHMOD2.MODL->MODL.Unload();
            return;
        case 56: //maleMouth_modb
            if(MHMOD2.MODL.IsLoaded())
                MHMOD2.MODL->MODB.Unload();
            return;
        case 57: //maleMouth_modt_p
            if(MHMOD2.MODL.IsLoaded())
                MHMOD2.MODL->MODT.Unload();
            return;
        case 58: //maleMouth_altTextures
            if(MHMOD2.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD2.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD2.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD2.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD2.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD2.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 59: //maleMouth_modelFlags
            if(MHMOD2.MODL.IsLoaded())
                MHMOD2.MODL->MODD.Unload();
            return;
        case 60: //maleMouth_iconPath
            MHMOD2.ICON.Unload();
            return;
        case 61: //maleMouth_smallIconPath
            MHMOD2.MICO.Unload();
            return;
        case 62: //maleTeethLower_modPath
            if(MHMOD3.MODL.IsLoaded())
                MHMOD3.MODL->MODL.Unload();
            return;
        case 63: //maleTeethLower_modb
            if(MHMOD3.MODL.IsLoaded())
                MHMOD3.MODL->MODB.Unload();
            return;
        case 64: //maleTeethLower_modt_p
            if(MHMOD3.MODL.IsLoaded())
                MHMOD3.MODL->MODT.Unload();
            return;
        case 65: //maleTeethLower_altTextures
            if(MHMOD3.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD3.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD3.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD3.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD3.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD3.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 66: //maleTeethLower_modelFlags
            if(MHMOD3.MODL.IsLoaded())
                MHMOD3.MODL->MODD.Unload();
            return;
        case 67: //maleTeethLower_iconPath
            MHMOD3.ICON.Unload();
            return;
        case 68: //maleTeethLower_smallIconPath
            MHMOD3.MICO.Unload();
            return;
        case 69: //maleTeethUpper_modPath
            if(MHMOD4.MODL.IsLoaded())
                MHMOD4.MODL->MODL.Unload();
            return;
        case 70: //maleTeethUpper_modb
            if(MHMOD4.MODL.IsLoaded())
                MHMOD4.MODL->MODB.Unload();
            return;
        case 71: //maleTeethUpper_modt_p
            if(MHMOD4.MODL.IsLoaded())
                MHMOD4.MODL->MODT.Unload();
            return;
        case 72: //maleTeethUpper_altTextures
            if(MHMOD4.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD4.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD4.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD4.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD4.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD4.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD4.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 73: //maleTeethUpper_modelFlags
            if(MHMOD4.MODL.IsLoaded())
                MHMOD4.MODL->MODD.Unload();
            return;
        case 74: //maleTeethUpper_iconPath
            MHMOD4.ICON.Unload();
            return;
        case 75: //maleTeethUpper_smallIconPath
            MHMOD4.MICO.Unload();
            return;
        case 76: //maleTongue_modPath
            if(MHMOD5.MODL.IsLoaded())
                MHMOD5.MODL->MODL.Unload();
            return;
        case 77: //maleTongue_modb
            if(MHMOD5.MODL.IsLoaded())
                MHMOD5.MODL->MODB.Unload();
            return;
        case 78: //maleTongue_modt_p
            if(MHMOD5.MODL.IsLoaded())
                MHMOD5.MODL->MODT.Unload();
            return;
        case 79: //maleTongue_altTextures
            if(MHMOD5.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD5.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD5.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD5.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD5.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD5.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD5.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 80: //maleTongue_modelFlags
            if(MHMOD5.MODL.IsLoaded())
                MHMOD5.MODL->MODD.Unload();
            return;
        case 81: //maleTongue_iconPath
            MHMOD5.ICON.Unload();
            return;
        case 82: //maleTongue_smallIconPath
            MHMOD5.MICO.Unload();
            return;
        case 83: //maleLeftEye_modPath
            if(MHMOD6.MODL.IsLoaded())
                MHMOD6.MODL->MODL.Unload();
            return;
        case 84: //maleLeftEye_modb
            if(MHMOD6.MODL.IsLoaded())
                MHMOD6.MODL->MODB.Unload();
            return;
        case 85: //maleLeftEye_modt_p
            if(MHMOD6.MODL.IsLoaded())
                MHMOD6.MODL->MODT.Unload();
            return;
        case 86: //maleLeftEye_altTextures
            if(MHMOD6.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD6.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD6.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD6.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD6.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD6.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD6.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 87: //maleLeftEye_modelFlags
            if(MHMOD6.MODL.IsLoaded())
                MHMOD6.MODL->MODD.Unload();
            return;
        case 88: //maleLeftEye_iconPath
            MHMOD6.ICON.Unload();
            return;
        case 89: //maleLeftEye_smallIconPath
            MHMOD6.MICO.Unload();
            return;
        case 90: //maleRightEye_modPath
            if(MHMOD7.MODL.IsLoaded())
                MHMOD7.MODL->MODL.Unload();
            return;
        case 91: //maleRightEye_modb
            if(MHMOD7.MODL.IsLoaded())
                MHMOD7.MODL->MODB.Unload();
            return;
        case 92: //maleRightEye_modt_p
            if(MHMOD7.MODL.IsLoaded())
                MHMOD7.MODL->MODT.Unload();
            return;
        case 93: //maleRightEye_altTextures
            if(MHMOD7.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MHMOD7.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MHMOD7.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MHMOD7.MODL->Textures.MODS[ListIndex]->name;
                        MHMOD7.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MHMOD7.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MHMOD7.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 94: //maleRightEye_modelFlags
            if(MHMOD7.MODL.IsLoaded())
                MHMOD7.MODL->MODD.Unload();
            return;
        case 95: //maleRightEye_iconPath
            MHMOD7.ICON.Unload();
            return;
        case 96: //maleRightEye_smallIconPath
            MHMOD7.MICO.Unload();
            return;
        case 97: //femaleHead_modPath
            if(FHMOD0.MODL.IsLoaded())
                FHMOD0.MODL->MODL.Unload();
            return;
        case 98: //femaleHead_modb
            if(FHMOD0.MODL.IsLoaded())
                FHMOD0.MODL->MODB.Unload();
            return;
        case 99: //femaleHead_modt_p
            if(FHMOD0.MODL.IsLoaded())
                FHMOD0.MODL->MODT.Unload();
            return;
        case 100: //femaleHead_altTextures
            if(FHMOD0.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD0.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD0.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD0.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD0.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD0.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 101: //femaleHead_modelFlags
            if(FHMOD0.MODL.IsLoaded())
                FHMOD0.MODL->MODD.Unload();
            return;
        case 102: //femaleHead_iconPath
            FHMOD0.ICON.Unload();
            return;
        case 103: //femaleHead_smallIconPath
            FHMOD0.MICO.Unload();
            return;
        case 104: //femaleEars_modPath
            if(FHMOD1.MODL.IsLoaded())
                FHMOD1.MODL->MODL.Unload();
            return;
        case 105: //femaleEars_modb
            if(FHMOD1.MODL.IsLoaded())
                FHMOD1.MODL->MODB.Unload();
            return;
        case 106: //femaleEars_modt_p
            if(FHMOD1.MODL.IsLoaded())
                FHMOD1.MODL->MODT.Unload();
            return;
        case 107: //femaleEars_altTextures
            if(FHMOD1.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD1.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD1.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD1.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD1.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD1.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 108: //femaleEars_modelFlags
            if(FHMOD1.MODL.IsLoaded())
                FHMOD1.MODL->MODD.Unload();
            return;
        case 109: //femaleEars_iconPath
            FHMOD1.ICON.Unload();
            return;
        case 110: //femaleEars_smallIconPath
            FHMOD1.MICO.Unload();
            return;
        case 111: //femaleMouth_modPath
            if(FHMOD2.MODL.IsLoaded())
                FHMOD2.MODL->MODL.Unload();
            return;
        case 112: //femaleMouth_modb
            if(FHMOD2.MODL.IsLoaded())
                FHMOD2.MODL->MODB.Unload();
            return;
        case 113: //femaleMouth_modt_p
            if(FHMOD2.MODL.IsLoaded())
                FHMOD2.MODL->MODT.Unload();
            return;
        case 114: //femaleMouth_altTextures
            if(FHMOD2.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD2.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD2.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD2.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD2.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD2.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 115: //femaleMouth_modelFlags
            if(FHMOD2.MODL.IsLoaded())
                FHMOD2.MODL->MODD.Unload();
            return;
        case 116: //femaleMouth_iconPath
            FHMOD2.ICON.Unload();
            return;
        case 117: //femaleMouth_smallIconPath
            FHMOD2.MICO.Unload();
            return;
        case 118: //femaleTeethLower_modPath
            if(FHMOD3.MODL.IsLoaded())
                FHMOD3.MODL->MODL.Unload();
            return;
        case 119: //femaleTeethLower_modb
            if(FHMOD3.MODL.IsLoaded())
                FHMOD3.MODL->MODB.Unload();
            return;
        case 120: //femaleTeethLower_modt_p
            if(FHMOD3.MODL.IsLoaded())
                FHMOD3.MODL->MODT.Unload();
            return;
        case 121: //femaleTeethLower_altTextures
            if(FHMOD3.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD3.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD3.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD3.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD3.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD3.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 122: //femaleTeethLower_modelFlags
            if(FHMOD3.MODL.IsLoaded())
                FHMOD3.MODL->MODD.Unload();
            return;
        case 123: //femaleTeethLower_iconPath
            FHMOD3.ICON.Unload();
            return;
        case 124: //femaleTeethLower_smallIconPath
            FHMOD3.MICO.Unload();
            return;
        case 125: //femaleTeethUpper_modPath
            if(FHMOD4.MODL.IsLoaded())
                FHMOD4.MODL->MODL.Unload();
            return;
        case 126: //femaleTeethUpper_modb
            if(FHMOD4.MODL.IsLoaded())
                FHMOD4.MODL->MODB.Unload();
            return;
        case 127: //femaleTeethUpper_modt_p
            if(FHMOD4.MODL.IsLoaded())
                FHMOD4.MODL->MODT.Unload();
            return;
        case 128: //femaleTeethUpper_altTextures
            if(FHMOD4.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD4.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD4.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD4.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD4.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD4.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD4.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 129: //femaleTeethUpper_modelFlags
            if(FHMOD4.MODL.IsLoaded())
                FHMOD4.MODL->MODD.Unload();
            return;
        case 130: //femaleTeethUpper_iconPath
            FHMOD4.ICON.Unload();
            return;
        case 131: //femaleTeethUpper_smallIconPath
            FHMOD4.MICO.Unload();
            return;
        case 132: //femaleTongue_modPath
            if(FHMOD5.MODL.IsLoaded())
                FHMOD5.MODL->MODL.Unload();
            return;
        case 133: //femaleTongue_modb
            if(FHMOD5.MODL.IsLoaded())
                FHMOD5.MODL->MODB.Unload();
            return;
        case 134: //femaleTongue_modt_p
            if(FHMOD5.MODL.IsLoaded())
                FHMOD5.MODL->MODT.Unload();
            return;
        case 135: //femaleTongue_altTextures
            if(FHMOD5.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD5.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD5.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD5.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD5.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD5.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD5.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 136: //femaleTongue_modelFlags
            if(FHMOD5.MODL.IsLoaded())
                FHMOD5.MODL->MODD.Unload();
            return;
        case 137: //femaleTongue_iconPath
            FHMOD5.ICON.Unload();
            return;
        case 138: //femaleTongue_smallIconPath
            FHMOD5.MICO.Unload();
            return;
        case 139: //femaleLeftEye_modPath
            if(FHMOD6.MODL.IsLoaded())
                FHMOD6.MODL->MODL.Unload();
            return;
        case 140: //femaleLeftEye_modb
            if(FHMOD6.MODL.IsLoaded())
                FHMOD6.MODL->MODB.Unload();
            return;
        case 141: //femaleLeftEye_modt_p
            if(FHMOD6.MODL.IsLoaded())
                FHMOD6.MODL->MODT.Unload();
            return;
        case 142: //femaleLeftEye_altTextures
            if(FHMOD6.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD6.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD6.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD6.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD6.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD6.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD6.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 143: //femaleLeftEye_modelFlags
            if(FHMOD6.MODL.IsLoaded())
                FHMOD6.MODL->MODD.Unload();
            return;
        case 144: //femaleLeftEye_iconPath
            FHMOD6.ICON.Unload();
            return;
        case 145: //femaleLeftEye_smallIconPath
            FHMOD6.MICO.Unload();
            return;
        case 146: //femaleRightEye_modPath
            if(FHMOD7.MODL.IsLoaded())
                FHMOD7.MODL->MODL.Unload();
            return;
        case 147: //femaleRightEye_modb
            if(FHMOD7.MODL.IsLoaded())
                FHMOD7.MODL->MODB.Unload();
            return;
        case 148: //femaleRightEye_modt_p
            if(FHMOD7.MODL.IsLoaded())
                FHMOD7.MODL->MODT.Unload();
            return;
        case 149: //femaleRightEye_altTextures
            if(FHMOD7.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FHMOD7.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FHMOD7.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FHMOD7.MODL->Textures.MODS[ListIndex]->name;
                        FHMOD7.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FHMOD7.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FHMOD7.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 150: //femaleRightEye_modelFlags
            if(FHMOD7.MODL.IsLoaded())
                FHMOD7.MODL->MODD.Unload();
            return;
        case 151: //femaleRightEye_iconPath
            FHMOD7.ICON.Unload();
            return;
        case 152: //femaleRightEye_smallIconPath
            FHMOD7.MICO.Unload();
            return;
        case 153: //maleUpperBody_modPath
            if(MBMOD0.MODL.IsLoaded())
                MBMOD0.MODL->MODL.Unload();
            return;
        case 154: //maleUpperBody_modb
            if(MBMOD0.MODL.IsLoaded())
                MBMOD0.MODL->MODB.Unload();
            return;
        case 155: //maleUpperBody_modt_p
            if(MBMOD0.MODL.IsLoaded())
                MBMOD0.MODL->MODT.Unload();
            return;
        case 156: //maleUpperBody_altTextures
            if(MBMOD0.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MBMOD0.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MBMOD0.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MBMOD0.MODL->Textures.MODS[ListIndex]->name;
                        MBMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MBMOD0.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MBMOD0.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 157: //maleUpperBody_modelFlags
            if(MBMOD0.MODL.IsLoaded())
                MBMOD0.MODL->MODD.Unload();
            return;
        case 158: //maleUpperBody_iconPath
            MBMOD0.ICON.Unload();
            return;
        case 159: //maleUpperBody_smallIconPath
            MBMOD0.MICO.Unload();
            return;
        case 160: //maleLeftHand_modPath
            if(MBMOD1.MODL.IsLoaded())
                MBMOD1.MODL->MODL.Unload();
            return;
        case 161: //maleLeftHand_modb
            if(MBMOD1.MODL.IsLoaded())
                MBMOD1.MODL->MODB.Unload();
            return;
        case 162: //maleLeftHand_modt_p
            if(MBMOD1.MODL.IsLoaded())
                MBMOD1.MODL->MODT.Unload();
            return;
        case 163: //maleLeftHand_altTextures
            if(MBMOD1.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MBMOD1.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MBMOD1.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MBMOD1.MODL->Textures.MODS[ListIndex]->name;
                        MBMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MBMOD1.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MBMOD1.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 164: //maleLeftHand_modelFlags
            if(MBMOD1.MODL.IsLoaded())
                MBMOD1.MODL->MODD.Unload();
            return;
        case 165: //maleLeftHand_iconPath
            MBMOD1.ICON.Unload();
            return;
        case 166: //maleLeftHand_smallIconPath
            MBMOD1.MICO.Unload();
            return;
        case 167: //maleRightHand_modPath
            if(MBMOD2.MODL.IsLoaded())
                MBMOD2.MODL->MODL.Unload();
            return;
        case 168: //maleRightHand_modb
            if(MBMOD2.MODL.IsLoaded())
                MBMOD2.MODL->MODB.Unload();
            return;
        case 169: //maleRightHand_modt_p
            if(MBMOD2.MODL.IsLoaded())
                MBMOD2.MODL->MODT.Unload();
            return;
        case 170: //maleRightHand_altTextures
            if(MBMOD2.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MBMOD2.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MBMOD2.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MBMOD2.MODL->Textures.MODS[ListIndex]->name;
                        MBMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MBMOD2.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MBMOD2.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 171: //maleRightHand_modelFlags
            if(MBMOD2.MODL.IsLoaded())
                MBMOD2.MODL->MODD.Unload();
            return;
        case 172: //maleRightHand_iconPath
            MBMOD2.ICON.Unload();
            return;
        case 173: //maleRightHand_smallIconPath
            MBMOD2.MICO.Unload();
            return;
        case 174: //maleUpperBodyTexture_modPath
            if(MBMOD3.MODL.IsLoaded())
                MBMOD3.MODL->MODL.Unload();
            return;
        case 175: //maleUpperBodyTexture_modb
            if(MBMOD3.MODL.IsLoaded())
                MBMOD3.MODL->MODB.Unload();
            return;
        case 176: //maleUpperBodyTexture_modt_p
            if(MBMOD3.MODL.IsLoaded())
                MBMOD3.MODL->MODT.Unload();
            return;
        case 177: //maleUpperBodyTexture_altTextures
            if(MBMOD3.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MBMOD3.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MBMOD3.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MBMOD3.MODL->Textures.MODS[ListIndex]->name;
                        MBMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MBMOD3.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MBMOD3.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 178: //maleUpperBodyTexture_modelFlags
            if(MBMOD3.MODL.IsLoaded())
                MBMOD3.MODL->MODD.Unload();
            return;
        case 179: //maleUpperBodyTexture_iconPath
            MBMOD3.ICON.Unload();
            return;
        case 180: //maleUpperBodyTexture_smallIconPath
            MBMOD3.MICO.Unload();
            return;
        case 181: //femaleUpperBody_modPath
            if(FBMOD0.MODL.IsLoaded())
                FBMOD0.MODL->MODL.Unload();
            return;
        case 182: //femaleUpperBody_modb
            if(FBMOD0.MODL.IsLoaded())
                FBMOD0.MODL->MODB.Unload();
            return;
        case 183: //femaleUpperBody_modt_p
            if(FBMOD0.MODL.IsLoaded())
                FBMOD0.MODL->MODT.Unload();
            return;
        case 184: //femaleUpperBody_altTextures
            if(FBMOD0.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FBMOD0.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FBMOD0.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FBMOD0.MODL->Textures.MODS[ListIndex]->name;
                        FBMOD0.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FBMOD0.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FBMOD0.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 185: //femaleUpperBody_modelFlags
            if(FBMOD0.MODL.IsLoaded())
                FBMOD0.MODL->MODD.Unload();
            return;
        case 186: //femaleUpperBody_iconPath
            FBMOD0.ICON.Unload();
            return;
        case 187: //femaleUpperBody_smallIconPath
            FBMOD0.MICO.Unload();
            return;
        case 188: //femaleLeftHand_modPath
            if(FBMOD1.MODL.IsLoaded())
                FBMOD1.MODL->MODL.Unload();
            return;
        case 189: //femaleLeftHand_modb
            if(FBMOD1.MODL.IsLoaded())
                FBMOD1.MODL->MODB.Unload();
            return;
        case 190: //femaleLeftHand_modt_p
            if(FBMOD1.MODL.IsLoaded())
                FBMOD1.MODL->MODT.Unload();
            return;
        case 191: //femaleLeftHand_altTextures
            if(FBMOD1.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FBMOD1.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FBMOD1.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FBMOD1.MODL->Textures.MODS[ListIndex]->name;
                        FBMOD1.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FBMOD1.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FBMOD1.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 192: //femaleLeftHand_modelFlags
            if(FBMOD1.MODL.IsLoaded())
                FBMOD1.MODL->MODD.Unload();
            return;
        case 193: //femaleLeftHand_iconPath
            FBMOD1.ICON.Unload();
            return;
        case 194: //femaleLeftHand_smallIconPath
            FBMOD1.MICO.Unload();
            return;
        case 195: //femaleRightHand_modPath
            if(FBMOD2.MODL.IsLoaded())
                FBMOD2.MODL->MODL.Unload();
            return;
        case 196: //femaleRightHand_modb
            if(FBMOD2.MODL.IsLoaded())
                FBMOD2.MODL->MODB.Unload();
            return;
        case 197: //femaleRightHand_modt_p
            if(FBMOD2.MODL.IsLoaded())
                FBMOD2.MODL->MODT.Unload();
            return;
        case 198: //femaleRightHand_altTextures
            if(FBMOD2.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FBMOD2.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FBMOD2.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FBMOD2.MODL->Textures.MODS[ListIndex]->name;
                        FBMOD2.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FBMOD2.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FBMOD2.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 199: //femaleRightHand_modelFlags
            if(FBMOD2.MODL.IsLoaded())
                FBMOD2.MODL->MODD.Unload();
            return;
        case 200: //femaleRightHand_iconPath
            FBMOD2.ICON.Unload();
            return;
        case 201: //femaleRightHand_smallIconPath
            FBMOD2.MICO.Unload();
            return;
        case 202: //femaleUpperBodyTexture_modPath
            if(FBMOD3.MODL.IsLoaded())
                FBMOD3.MODL->MODL.Unload();
            return;
        case 203: //femaleUpperBodyTexture_modb
            if(FBMOD3.MODL.IsLoaded())
                FBMOD3.MODL->MODB.Unload();
            return;
        case 204: //femaleUpperBodyTexture_modt_p
            if(FBMOD3.MODL.IsLoaded())
                FBMOD3.MODL->MODT.Unload();
            return;
        case 205: //femaleUpperBodyTexture_altTextures
            if(FBMOD3.MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    FBMOD3.MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= FBMOD3.MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []FBMOD3.MODL->Textures.MODS[ListIndex]->name;
                        FBMOD3.MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        FBMOD3.MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        FBMOD3.MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 206: //femaleUpperBodyTexture_modelFlags
            if(FBMOD3.MODL.IsLoaded())
                FBMOD3.MODL->MODD.Unload();
            return;
        case 207: //femaleUpperBodyTexture_iconPath
            FBMOD3.ICON.Unload();
            return;
        case 208: //femaleUpperBodyTexture_smallIconPath
            FBMOD3.MICO.Unload();
            return;
        case 209: //hairs
            HNAM.Unload();
            return;
        case 210: //eyes
            ENAM.Unload();
            return;
        case 211: //maleFggs_p
            MaleFGGS.Unload();
            return;
        case 212: //maleFgga_p
            MaleFGGA.Unload();
            return;
        case 213: //maleFgts_p
            MaleFGTS.Unload();
            return;
        case 214: //maleSnam_p
            MaleSNAM.Unload();
            return;
        case 215: //femaleFggs_p
            FemaleFGGS.Unload();
            return;
        case 216: //femaleFgga_p
            FemaleFGGA.Unload();
            return;
        case 217: //femaleFgts_p
            FemaleFGTS.Unload();
            return;
        case 218: //femaleSnam_p
            FemaleSNAM.Unload();
            return;
        default:
            return;
        }
    }
}