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
#include "..\IMADRecord.h"

namespace FNV
{
uint32_t IMADRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //dnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //bnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return BNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 9: //vnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //tnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return TNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //nam3_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM3.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 12: //rnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return RNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 13: //snam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //unam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return UNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 15: //nam1_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM1.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 16: //nam2_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM2.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //wnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return WNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //xnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //ynam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return YNAM.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 20: //nam4_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM4.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 21: //_00__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _00_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 22: //_40__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _40_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 23: //_01__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _01_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 24: //_41__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _41_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 25: //_02__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _02_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 26: //_42__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _42_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 27: //_03__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _03_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 28: //_43__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _43_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 29: //_04__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _04_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 30: //_44__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _44_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 31: //_05__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _05_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 32: //_45__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _45_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 33: //_06__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _06_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 34: //_46__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _46_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 35: //_07__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _07_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 36: //_47__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _47_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 37: //_08__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _08_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 38: //_48__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _48_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 39: //_09__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _09_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 40: //_49__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _49_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 41: //_0a__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0A_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 42: //_4a__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4A_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 43: //_0b__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0B_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 44: //_4b__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4B_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 45: //_0c__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0C_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 46: //_4c__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4C_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 47: //_0d__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0D_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 48: //_4d__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4D_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 49: //_0e__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0E_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 50: //_4e__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4E_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 51: //_0f__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0F_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 52: //_4f__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4F_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 53: //_10__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _10_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 54: //_50__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _50_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 55: //_11__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _11_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 56: //_51__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _51_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 57: //_12__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _12_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 58: //_52__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _52_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 59: //_13__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _13_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 60: //_53__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _53_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 61: //_14__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _14_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 62: //_54__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _54_.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 63: //rdsd Sound - Intro
            return CB_FORMID_FIELD;
        case 64: //rdsi Sound - Outro
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * IMADRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //dnam_p Unknown
            *FieldValues = DNAM.value;
            return NULL;
        case 8: //bnam_p Unknown
            *FieldValues = BNAM.value;
            return NULL;
        case 9: //vnam_p Unknown
            *FieldValues = VNAM.value;
            return NULL;
        case 10: //tnam_p Unknown
            *FieldValues = TNAM.value;
            return NULL;
        case 11: //nam3_p Unknown
            *FieldValues = NAM3.value;
            return NULL;
        case 12: //rnam_p Unknown
            *FieldValues = RNAM.value;
            return NULL;
        case 13: //snam_p Unknown
            *FieldValues = SNAM.value;
            return NULL;
        case 14: //unam_p Unknown
            *FieldValues = UNAM.value;
            return NULL;
        case 15: //nam1_p Unknown
            *FieldValues = NAM1.value;
            return NULL;
        case 16: //nam2_p Unknown
            *FieldValues = NAM2.value;
            return NULL;
        case 17: //wnam_p Unknown
            *FieldValues = WNAM.value;
            return NULL;
        case 18: //xnam_p Unknown
            *FieldValues = XNAM.value;
            return NULL;
        case 19: //ynam_p Unknown
            *FieldValues = YNAM.value;
            return NULL;
        case 20: //nam4_p Unknown
            *FieldValues = NAM4.value;
            return NULL;
        case 21: //_00__p Unknown
            *FieldValues = _00_.value;
            return NULL;
        case 22: //_40__p Unknown
            *FieldValues = _40_.value;
            return NULL;
        case 23: //_01__p Unknown
            *FieldValues = _01_.value;
            return NULL;
        case 24: //_41__p Unknown
            *FieldValues = _41_.value;
            return NULL;
        case 25: //_02__p Unknown
            *FieldValues = _02_.value;
            return NULL;
        case 26: //_42__p Unknown
            *FieldValues = _42_.value;
            return NULL;
        case 27: //_03__p Unknown
            *FieldValues = _03_.value;
            return NULL;
        case 28: //_43__p Unknown
            *FieldValues = _43_.value;
            return NULL;
        case 29: //_04__p Unknown
            *FieldValues = _04_.value;
            return NULL;
        case 30: //_44__p Unknown
            *FieldValues = _44_.value;
            return NULL;
        case 31: //_05__p Unknown
            *FieldValues = _05_.value;
            return NULL;
        case 32: //_45__p Unknown
            *FieldValues = _45_.value;
            return NULL;
        case 33: //_06__p Unknown
            *FieldValues = _06_.value;
            return NULL;
        case 34: //_46__p Unknown
            *FieldValues = _46_.value;
            return NULL;
        case 35: //_07__p Unknown
            *FieldValues = _07_.value;
            return NULL;
        case 36: //_47__p Unknown
            *FieldValues = _47_.value;
            return NULL;
        case 37: //_08__p Unknown
            *FieldValues = _08_.value;
            return NULL;
        case 38: //_48__p Unknown
            *FieldValues = _48_.value;
            return NULL;
        case 39: //_09__p Unknown
            *FieldValues = _09_.value;
            return NULL;
        case 40: //_49__p Unknown
            *FieldValues = _49_.value;
            return NULL;
        case 41: //_0a__p Unknown
            *FieldValues = _0A_.value;
            return NULL;
        case 42: //_4a__p Unknown
            *FieldValues = _4A_.value;
            return NULL;
        case 43: //_0b__p Unknown
            *FieldValues = _0B_.value;
            return NULL;
        case 44: //_4b__p Unknown
            *FieldValues = _4B_.value;
            return NULL;
        case 45: //_0c__p Unknown
            *FieldValues = _0C_.value;
            return NULL;
        case 46: //_4c__p Unknown
            *FieldValues = _4C_.value;
            return NULL;
        case 47: //_0d__p Unknown
            *FieldValues = _0D_.value;
            return NULL;
        case 48: //_4d__p Unknown
            *FieldValues = _4D_.value;
            return NULL;
        case 49: //_0e__p Unknown
            *FieldValues = _0E_.value;
            return NULL;
        case 50: //_4e__p Unknown
            *FieldValues = _4E_.value;
            return NULL;
        case 51: //_0f__p Unknown
            *FieldValues = _0F_.value;
            return NULL;
        case 52: //_4f__p Unknown
            *FieldValues = _4F_.value;
            return NULL;
        case 53: //_10__p Unknown
            *FieldValues = _10_.value;
            return NULL;
        case 54: //_50__p Unknown
            *FieldValues = _50_.value;
            return NULL;
        case 55: //_11__p Unknown
            *FieldValues = _11_.value;
            return NULL;
        case 56: //_51__p Unknown
            *FieldValues = _51_.value;
            return NULL;
        case 57: //_12__p Unknown
            *FieldValues = _12_.value;
            return NULL;
        case 58: //_52__p Unknown
            *FieldValues = _52_.value;
            return NULL;
        case 59: //_13__p Unknown
            *FieldValues = _13_.value;
            return NULL;
        case 60: //_53__p Unknown
            *FieldValues = _53_.value;
            return NULL;
        case 61: //_14__p Unknown
            *FieldValues = _14_.value;
            return NULL;
        case 62: //_54__p Unknown
            *FieldValues = _54_.value;
            return NULL;
        case 63: //rdsd Sound - Intro
            return RDSD.IsLoaded() ? &RDSD.value : NULL;
        case 64: //rdsi Sound - Outro
            return RDSI.IsLoaded() ? &RDSI.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IMADRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //dnam_p Unknown
            DNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //bnam_p Unknown
            BNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //vnam_p Unknown
            VNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //tnam_p Unknown
            TNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //nam3_p Unknown
            NAM3.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 12: //rnam_p Unknown
            RNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 13: //snam_p Unknown
            SNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 14: //unam_p Unknown
            UNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 15: //nam1_p Unknown
            NAM1.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 16: //nam2_p Unknown
            NAM2.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //wnam_p Unknown
            WNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 18: //xnam_p Unknown
            XNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 19: //ynam_p Unknown
            YNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //nam4_p Unknown
            NAM4.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 21: //_00__p Unknown
            _00_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 22: //_40__p Unknown
            _40_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 23: //_01__p Unknown
            _01_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 24: //_41__p Unknown
            _41_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 25: //_02__p Unknown
            _02_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 26: //_42__p Unknown
            _42_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 27: //_03__p Unknown
            _03_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 28: //_43__p Unknown
            _43_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 29: //_04__p Unknown
            _04_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 30: //_44__p Unknown
            _44_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 31: //_05__p Unknown
            _05_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 32: //_45__p Unknown
            _45_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 33: //_06__p Unknown
            _06_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 34: //_46__p Unknown
            _46_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 35: //_07__p Unknown
            _07_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 36: //_47__p Unknown
            _47_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 37: //_08__p Unknown
            _08_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 38: //_48__p Unknown
            _48_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 39: //_09__p Unknown
            _09_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 40: //_49__p Unknown
            _49_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 41: //_0a__p Unknown
            _0A_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 42: //_4a__p Unknown
            _4A_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 43: //_0b__p Unknown
            _0B_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 44: //_4b__p Unknown
            _4B_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 45: //_0c__p Unknown
            _0C_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 46: //_4c__p Unknown
            _4C_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 47: //_0d__p Unknown
            _0D_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 48: //_4d__p Unknown
            _4D_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 49: //_0e__p Unknown
            _0E_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 50: //_4e__p Unknown
            _4E_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 51: //_0f__p Unknown
            _0F_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 52: //_4f__p Unknown
            _4F_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 53: //_10__p Unknown
            _10_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 54: //_50__p Unknown
            _50_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 55: //_11__p Unknown
            _11_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 56: //_51__p Unknown
            _51_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 57: //_12__p Unknown
            _12_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 58: //_52__p Unknown
            _52_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 59: //_13__p Unknown
            _13_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 60: //_53__p Unknown
            _53_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 61: //_14__p Unknown
            _14_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 62: //_54__p Unknown
            _54_.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 63: //rdsd Sound - Intro
            RDSD.Load();
            RDSD.value = *(FORMID *)FieldValue;
            return true;
        case 64: //rdsi Sound - Outro
            RDSI.Load();
            RDSI.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void IMADRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //dnam_p Unknown
            DNAM.Unload();
            return;
        case 8: //bnam_p Unknown
            BNAM.Unload();
            return;
        case 9: //vnam_p Unknown
            VNAM.Unload();
            return;
        case 10: //tnam_p Unknown
            TNAM.Unload();
            return;
        case 11: //nam3_p Unknown
            NAM3.Unload();
            return;
        case 12: //rnam_p Unknown
            RNAM.Unload();
            return;
        case 13: //snam_p Unknown
            SNAM.Unload();
            return;
        case 14: //unam_p Unknown
            UNAM.Unload();
            return;
        case 15: //nam1_p Unknown
            NAM1.Unload();
            return;
        case 16: //nam2_p Unknown
            NAM2.Unload();
            return;
        case 17: //wnam_p Unknown
            WNAM.Unload();
            return;
        case 18: //xnam_p Unknown
            XNAM.Unload();
            return;
        case 19: //ynam_p Unknown
            YNAM.Unload();
            return;
        case 20: //nam4_p Unknown
            NAM4.Unload();
            return;
        case 21: //_00__p Unknown
            _00_.Unload();
            return;
        case 22: //_40__p Unknown
            _40_.Unload();
            return;
        case 23: //_01__p Unknown
            _01_.Unload();
            return;
        case 24: //_41__p Unknown
            _41_.Unload();
            return;
        case 25: //_02__p Unknown
            _02_.Unload();
            return;
        case 26: //_42__p Unknown
            _42_.Unload();
            return;
        case 27: //_03__p Unknown
            _03_.Unload();
            return;
        case 28: //_43__p Unknown
            _43_.Unload();
            return;
        case 29: //_04__p Unknown
            _04_.Unload();
            return;
        case 30: //_44__p Unknown
            _44_.Unload();
            return;
        case 31: //_05__p Unknown
            _05_.Unload();
            return;
        case 32: //_45__p Unknown
            _45_.Unload();
            return;
        case 33: //_06__p Unknown
            _06_.Unload();
            return;
        case 34: //_46__p Unknown
            _46_.Unload();
            return;
        case 35: //_07__p Unknown
            _07_.Unload();
            return;
        case 36: //_47__p Unknown
            _47_.Unload();
            return;
        case 37: //_08__p Unknown
            _08_.Unload();
            return;
        case 38: //_48__p Unknown
            _48_.Unload();
            return;
        case 39: //_09__p Unknown
            _09_.Unload();
            return;
        case 40: //_49__p Unknown
            _49_.Unload();
            return;
        case 41: //_0a__p Unknown
            _0A_.Unload();
            return;
        case 42: //_4a__p Unknown
            _4A_.Unload();
            return;
        case 43: //_0b__p Unknown
            _0B_.Unload();
            return;
        case 44: //_4b__p Unknown
            _4B_.Unload();
            return;
        case 45: //_0c__p Unknown
            _0C_.Unload();
            return;
        case 46: //_4c__p Unknown
            _4C_.Unload();
            return;
        case 47: //_0d__p Unknown
            _0D_.Unload();
            return;
        case 48: //_4d__p Unknown
            _4D_.Unload();
            return;
        case 49: //_0e__p Unknown
            _0E_.Unload();
            return;
        case 50: //_4e__p Unknown
            _4E_.Unload();
            return;
        case 51: //_0f__p Unknown
            _0F_.Unload();
            return;
        case 52: //_4f__p Unknown
            _4F_.Unload();
            return;
        case 53: //_10__p Unknown
            _10_.Unload();
            return;
        case 54: //_50__p Unknown
            _50_.Unload();
            return;
        case 55: //_11__p Unknown
            _11_.Unload();
            return;
        case 56: //_51__p Unknown
            _51_.Unload();
            return;
        case 57: //_12__p Unknown
            _12_.Unload();
            return;
        case 58: //_52__p Unknown
            _52_.Unload();
            return;
        case 59: //_13__p Unknown
            _13_.Unload();
            return;
        case 60: //_53__p Unknown
            _53_.Unload();
            return;
        case 61: //_14__p Unknown
            _14_.Unload();
            return;
        case 62: //_54__p Unknown
            _54_.Unload();
            return;
        case 63: //rdsd Sound - Intro
            RDSD.Unload();
            return;
        case 64: //rdsi Sound - Outro
            RDSI.Unload();
            return;
        default:
            return;
        }
    }
}