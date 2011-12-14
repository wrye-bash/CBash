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
#include "..\IMADRecord.h"

namespace FNV
{
UINT32 IMADRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //dnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 8: //bnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return BNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 9: //vnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //tnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return TNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 11: //nam3_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM3.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 12: //rnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return RNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 13: //snam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //unam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return UNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 15: //nam1_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM1.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 16: //nam2_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM2.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 17: //wnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return WNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 18: //xnam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 19: //ynam_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return YNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 20: //nam4_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NAM4.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 21: //_00__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _00_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 22: //_40__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _40_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 23: //_01__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _01_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 24: //_41__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _41_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 25: //_02__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _02_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 26: //_42__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _42_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 27: //_03__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _03_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 28: //_43__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _43_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 29: //_04__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _04_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 30: //_44__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _44_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 31: //_05__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _05_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 32: //_45__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _45_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 33: //_06__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _06_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 34: //_46__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _46_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 35: //_07__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _07_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 36: //_47__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _47_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 37: //_08__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _08_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 38: //_48__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _48_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 39: //_09__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _09_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 40: //_49__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _49_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 41: //_0a__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0A_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 42: //_4a__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4A_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 43: //_0b__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0B_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 44: //_4b__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4B_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 45: //_0c__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0C_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 46: //_4c__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4C_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 47: //_0d__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0D_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 48: //_4d__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4D_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 49: //_0e__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0E_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 50: //_4e__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4E_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 51: //_0f__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _0F_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 52: //_4f__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _4F_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 53: //_10__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _10_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 54: //_50__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _50_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 55: //_11__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _11_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 56: //_51__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _51_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 57: //_12__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _12_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 58: //_52__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _52_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 59: //_13__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _13_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 60: //_53__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _53_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 61: //_14__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _14_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 62: //_54__p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return _54_.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 63: //rdsd Sound - Intro
            return FORMID_FIELD;
        case 64: //rdsi Sound - Outro
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
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
            *FieldValues = _00_IAD.value;
            return NULL;
        case 22: //_40__p Unknown
            *FieldValues = _40_IAD.value;
            return NULL;
        case 23: //_01__p Unknown
            *FieldValues = _01_IAD.value;
            return NULL;
        case 24: //_41__p Unknown
            *FieldValues = _41_IAD.value;
            return NULL;
        case 25: //_02__p Unknown
            *FieldValues = _02_IAD.value;
            return NULL;
        case 26: //_42__p Unknown
            *FieldValues = _42_IAD.value;
            return NULL;
        case 27: //_03__p Unknown
            *FieldValues = _03_IAD.value;
            return NULL;
        case 28: //_43__p Unknown
            *FieldValues = _43_IAD.value;
            return NULL;
        case 29: //_04__p Unknown
            *FieldValues = _04_IAD.value;
            return NULL;
        case 30: //_44__p Unknown
            *FieldValues = _44_IAD.value;
            return NULL;
        case 31: //_05__p Unknown
            *FieldValues = _05_IAD.value;
            return NULL;
        case 32: //_45__p Unknown
            *FieldValues = _45_IAD.value;
            return NULL;
        case 33: //_06__p Unknown
            *FieldValues = _06_IAD.value;
            return NULL;
        case 34: //_46__p Unknown
            *FieldValues = _46_IAD.value;
            return NULL;
        case 35: //_07__p Unknown
            *FieldValues = _07_IAD.value;
            return NULL;
        case 36: //_47__p Unknown
            *FieldValues = _47_IAD.value;
            return NULL;
        case 37: //_08__p Unknown
            *FieldValues = _08_IAD.value;
            return NULL;
        case 38: //_48__p Unknown
            *FieldValues = _48_IAD.value;
            return NULL;
        case 39: //_09__p Unknown
            *FieldValues = _09_IAD.value;
            return NULL;
        case 40: //_49__p Unknown
            *FieldValues = _49_IAD.value;
            return NULL;
        case 41: //_0a__p Unknown
            *FieldValues = _0A_IAD.value;
            return NULL;
        case 42: //_4a__p Unknown
            *FieldValues = _4A_IAD.value;
            return NULL;
        case 43: //_0b__p Unknown
            *FieldValues = _0B_IAD.value;
            return NULL;
        case 44: //_4b__p Unknown
            *FieldValues = _4B_IAD.value;
            return NULL;
        case 45: //_0c__p Unknown
            *FieldValues = _0C_IAD.value;
            return NULL;
        case 46: //_4c__p Unknown
            *FieldValues = _4C_IAD.value;
            return NULL;
        case 47: //_0d__p Unknown
            *FieldValues = _0D_IAD.value;
            return NULL;
        case 48: //_4d__p Unknown
            *FieldValues = _4D_IAD.value;
            return NULL;
        case 49: //_0e__p Unknown
            *FieldValues = _0E_IAD.value;
            return NULL;
        case 50: //_4e__p Unknown
            *FieldValues = _4E_IAD.value;
            return NULL;
        case 51: //_0f__p Unknown
            *FieldValues = _0F_IAD.value;
            return NULL;
        case 52: //_4f__p Unknown
            *FieldValues = _4F_IAD.value;
            return NULL;
        case 53: //_10__p Unknown
            *FieldValues = _10_IAD.value;
            return NULL;
        case 54: //_50__p Unknown
            *FieldValues = _50_IAD.value;
            return NULL;
        case 55: //_11__p Unknown
            *FieldValues = _11_IAD.value;
            return NULL;
        case 56: //_51__p Unknown
            *FieldValues = _51_IAD.value;
            return NULL;
        case 57: //_12__p Unknown
            *FieldValues = _12_IAD.value;
            return NULL;
        case 58: //_52__p Unknown
            *FieldValues = _52_IAD.value;
            return NULL;
        case 59: //_13__p Unknown
            *FieldValues = _13_IAD.value;
            return NULL;
        case 60: //_53__p Unknown
            *FieldValues = _53_IAD.value;
            return NULL;
        case 61: //_14__p Unknown
            *FieldValues = _14_IAD.value;
            return NULL;
        case 62: //_54__p Unknown
            *FieldValues = _54_IAD.value;
            return NULL;
        case 63: //rdsd Sound - Intro
            return RDSD.IsLoaded() ? &RDSD->value63 : NULL;
        case 64: //rdsi Sound - Outro
            return RDSI.IsLoaded() ? &RDSI->value64 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IMADRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
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
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
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
            _00_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 22: //_40__p Unknown
            _40_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 23: //_01__p Unknown
            _01_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 24: //_41__p Unknown
            _41_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 25: //_02__p Unknown
            _02_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 26: //_42__p Unknown
            _42_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 27: //_03__p Unknown
            _03_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 28: //_43__p Unknown
            _43_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 29: //_04__p Unknown
            _04_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 30: //_44__p Unknown
            _44_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 31: //_05__p Unknown
            _05_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 32: //_45__p Unknown
            _45_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 33: //_06__p Unknown
            _06_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 34: //_46__p Unknown
            _46_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 35: //_07__p Unknown
            _07_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 36: //_47__p Unknown
            _47_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 37: //_08__p Unknown
            _08_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 38: //_48__p Unknown
            _48_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 39: //_09__p Unknown
            _09_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 40: //_49__p Unknown
            _49_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 41: //_0a__p Unknown
            _0A_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 42: //_4a__p Unknown
            _4A_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 43: //_0b__p Unknown
            _0B_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 44: //_4b__p Unknown
            _4B_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 45: //_0c__p Unknown
            _0C_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 46: //_4c__p Unknown
            _4C_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 47: //_0d__p Unknown
            _0D_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 48: //_4d__p Unknown
            _4D_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 49: //_0e__p Unknown
            _0E_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 50: //_4e__p Unknown
            _4E_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 51: //_0f__p Unknown
            _0F_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 52: //_4f__p Unknown
            _4F_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 53: //_10__p Unknown
            _10_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 54: //_50__p Unknown
            _50_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 55: //_11__p Unknown
            _11_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 56: //_51__p Unknown
            _51_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 57: //_12__p Unknown
            _12_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 58: //_52__p Unknown
            _52_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 59: //_13__p Unknown
            _13_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 60: //_53__p Unknown
            _53_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 61: //_14__p Unknown
            _14_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 62: //_54__p Unknown
            _54_IAD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 63: //rdsd Sound - Intro
            RDSD.Load();
            RDSD->value63 = *(FORMID *)FieldValue;
            return true;
        case 64: //rdsi Sound - Outro
            RDSI.Load();
            RDSI->value64 = *(FORMID *)FieldValue;
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
            _00_IAD.Unload();
            return;
        case 22: //_40__p Unknown
            _40_IAD.Unload();
            return;
        case 23: //_01__p Unknown
            _01_IAD.Unload();
            return;
        case 24: //_41__p Unknown
            _41_IAD.Unload();
            return;
        case 25: //_02__p Unknown
            _02_IAD.Unload();
            return;
        case 26: //_42__p Unknown
            _42_IAD.Unload();
            return;
        case 27: //_03__p Unknown
            _03_IAD.Unload();
            return;
        case 28: //_43__p Unknown
            _43_IAD.Unload();
            return;
        case 29: //_04__p Unknown
            _04_IAD.Unload();
            return;
        case 30: //_44__p Unknown
            _44_IAD.Unload();
            return;
        case 31: //_05__p Unknown
            _05_IAD.Unload();
            return;
        case 32: //_45__p Unknown
            _45_IAD.Unload();
            return;
        case 33: //_06__p Unknown
            _06_IAD.Unload();
            return;
        case 34: //_46__p Unknown
            _46_IAD.Unload();
            return;
        case 35: //_07__p Unknown
            _07_IAD.Unload();
            return;
        case 36: //_47__p Unknown
            _47_IAD.Unload();
            return;
        case 37: //_08__p Unknown
            _08_IAD.Unload();
            return;
        case 38: //_48__p Unknown
            _48_IAD.Unload();
            return;
        case 39: //_09__p Unknown
            _09_IAD.Unload();
            return;
        case 40: //_49__p Unknown
            _49_IAD.Unload();
            return;
        case 41: //_0a__p Unknown
            _0A_IAD.Unload();
            return;
        case 42: //_4a__p Unknown
            _4A_IAD.Unload();
            return;
        case 43: //_0b__p Unknown
            _0B_IAD.Unload();
            return;
        case 44: //_4b__p Unknown
            _4B_IAD.Unload();
            return;
        case 45: //_0c__p Unknown
            _0C_IAD.Unload();
            return;
        case 46: //_4c__p Unknown
            _4C_IAD.Unload();
            return;
        case 47: //_0d__p Unknown
            _0D_IAD.Unload();
            return;
        case 48: //_4d__p Unknown
            _4D_IAD.Unload();
            return;
        case 49: //_0e__p Unknown
            _0E_IAD.Unload();
            return;
        case 50: //_4e__p Unknown
            _4E_IAD.Unload();
            return;
        case 51: //_0f__p Unknown
            _0F_IAD.Unload();
            return;
        case 52: //_4f__p Unknown
            _4F_IAD.Unload();
            return;
        case 53: //_10__p Unknown
            _10_IAD.Unload();
            return;
        case 54: //_50__p Unknown
            _50_IAD.Unload();
            return;
        case 55: //_11__p Unknown
            _11_IAD.Unload();
            return;
        case 56: //_51__p Unknown
            _51_IAD.Unload();
            return;
        case 57: //_12__p Unknown
            _12_IAD.Unload();
            return;
        case 58: //_52__p Unknown
            _52_IAD.Unload();
            return;
        case 59: //_13__p Unknown
            _13_IAD.Unload();
            return;
        case 60: //_53__p Unknown
            _53_IAD.Unload();
            return;
        case 61: //_14__p Unknown
            _14_IAD.Unload();
            return;
        case 62: //_54__p Unknown
            _54_IAD.Unload();
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