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
#include "..\CSTYRecord.h"

namespace FNV
{
uint32_t CSTYRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //dodgeChance
            return CB_UINT8_FIELD;
        case 8: //lrChance
            return CB_UINT8_FIELD;
        case 9: //unused1
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
        case 10: //lrTimerMin
            return CB_FLOAT32_FIELD;
        case 11: //lrTimerMax
            return CB_FLOAT32_FIELD;
        case 12: //forTimerMin
            return CB_FLOAT32_FIELD;
        case 13: //forTimerMax
            return CB_FLOAT32_FIELD;
        case 14: //backTimerMin
            return CB_FLOAT32_FIELD;
        case 15: //backTimerMax
            return CB_FLOAT32_FIELD;
        case 16: //idleTimerMin
            return CB_FLOAT32_FIELD;
        case 17: //idleTimerMax
            return CB_FLOAT32_FIELD;
        case 18: //blkChance
            return CB_UINT8_FIELD;
        case 19: //atkChance
            return CB_UINT8_FIELD;
        case 20: //unused2
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
        case 21: //atkBRecoil
            return CB_FLOAT32_FIELD;
        case 22: //atkBUnc
            return CB_FLOAT32_FIELD;
        case 23: //atkBh2h
            return CB_FLOAT32_FIELD;
        case 24: //pAtkChance
            return CB_UINT8_FIELD;
        case 25: //unused3
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
        case 26: //pAtkBRecoil
            return CB_FLOAT32_FIELD;
        case 27: //pAtkBUnc
            return CB_FLOAT32_FIELD;
        case 28: //pAtkNormal
            return CB_UINT8_FIELD;
        case 29: //pAtkFor
            return CB_UINT8_FIELD;
        case 30: //pAtkBack
            return CB_UINT8_FIELD;
        case 31: //pAtkL
            return CB_UINT8_FIELD;
        case 32: //pAtkR
            return CB_UINT8_FIELD;
        case 33: //unused4
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
        case 34: //holdTimerMin
            return CB_FLOAT32_FIELD;
        case 35: //holdTimerMax
            return CB_FLOAT32_FIELD;
        case 36: //flags
            return CB_UINT16_FLAG_FIELD;
        case 37: //unused5
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
        case 38: //acroDodge
            return CB_UINT8_FIELD;
        case 39: //rushChance
            return CB_UINT8_FIELD;
        case 40: //unused6
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
        case 41: //rushMult
            return CB_FLOAT32_FIELD;
        case 42: //dodgeFMult
            return CB_FLOAT32_FIELD;
        case 43: //dodgeFBase
            return CB_FLOAT32_FIELD;
        case 44: //encSBase
            return CB_FLOAT32_FIELD;
        case 45: //encSMult
            return CB_FLOAT32_FIELD;
        case 46: //dodgeAtkMult
            return CB_FLOAT32_FIELD;
        case 47: //dodgeNAtkMult
            return CB_FLOAT32_FIELD;
        case 48: //dodgeBAtkMult
            return CB_FLOAT32_FIELD;
        case 49: //dodgeBNAtkMult
            return CB_FLOAT32_FIELD;
        case 50: //dodgeFAtkMult
            return CB_FLOAT32_FIELD;
        case 51: //dodgeFNAtkMult
            return CB_FLOAT32_FIELD;
        case 52: //blockMult
            return CB_FLOAT32_FIELD;
        case 53: //blockBase
            return CB_FLOAT32_FIELD;
        case 54: //blockAtkMult
            return CB_FLOAT32_FIELD;
        case 55: //blockNAtkMult
            return CB_FLOAT32_FIELD;
        case 56: //atkMult
            return CB_FLOAT32_FIELD;
        case 57: //atkBase
            return CB_FLOAT32_FIELD;
        case 58: //atkAtkMult
            return CB_FLOAT32_FIELD;
        case 59: //atkNAtkMult
            return CB_FLOAT32_FIELD;
        case 60: //atkBlockMult
            return CB_FLOAT32_FIELD;
        case 61: //pAtkFBase
            return CB_FLOAT32_FIELD;
        case 62: //pAtkFMult
            return CB_FLOAT32_FIELD;
        case 63: //coverRadius
            return CB_FLOAT32_FIELD;
        case 64: //coverChance
            return CB_FLOAT32_FIELD;
        case 65: //waitTimerMin
            return CB_FLOAT32_FIELD;
        case 66: //waitFireTimerMin
            return CB_FLOAT32_FIELD;
        case 67: //waitFireTimerMax
            return CB_FLOAT32_FIELD;
        case 68: //waitTimerMax
            return CB_FLOAT32_FIELD;
        case 69: //fireTimerMin
            return CB_FLOAT32_FIELD;
        case 70: //fireTimerMax
            return CB_FLOAT32_FIELD;
        case 71: //rangedRangeMultMin
            return CB_FLOAT32_FIELD;
        case 72: //unused7
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
        case 73: //weaponRestrictions
            return CB_UINT32_TYPE_FIELD;
        case 74: //rangedRangeMultMax
            return CB_FLOAT32_FIELD;
        case 75: //targetMaxFOV
            return CB_FLOAT32_FIELD;
        case 76: //combatRadius
            return CB_FLOAT32_FIELD;
        case 77: //semiAutoFireDelayMultMin
            return CB_FLOAT32_FIELD;
        case 78: //semiAutoFireDelayMultMax
            return CB_FLOAT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * CSTYRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //dodgeChance
            return &CSTD.value.dodgeChance;
        case 8: //lrChance
            return &CSTD.value.lrChance;
        case 9: //unused1
            *FieldValues = &CSTD.value.unused1[0];
            return NULL;
        case 10: //lrTimerMin
            return &CSTD.value.lrTimerMin;
        case 11: //lrTimerMax
            return &CSTD.value.lrTimerMax;
        case 12: //forTimerMin
            return &CSTD.value.forTimerMin;
        case 13: //forTimerMax
            return &CSTD.value.forTimerMax;
        case 14: //backTimerMin
            return &CSTD.value.backTimerMin;
        case 15: //backTimerMax
            return &CSTD.value.backTimerMax;
        case 16: //idleTimerMin
            return &CSTD.value.idleTimerMin;
        case 17: //idleTimerMax
            return &CSTD.value.idleTimerMax;
        case 18: //blkChance
            return &CSTD.value.blkChance;
        case 19: //atkChance
            return &CSTD.value.atkChance;
        case 20: //unused2
            *FieldValues = &CSTD.value.unused2[0];
            return NULL;
        case 21: //atkBRecoil
            return &CSTD.value.atkBRecoil;
        case 22: //atkBUnc
            return &CSTD.value.atkBUnc;
        case 23: //atkBh2h
            return &CSTD.value.atkBh2h;
        case 24: //pAtkChance
            return &CSTD.value.pAtkChance;
        case 25: //unused3
            *FieldValues = &CSTD.value.unused3[0];
            return NULL;
        case 26: //pAtkBRecoil
            return &CSTD.value.pAtkBRecoil;
        case 27: //pAtkBUnc
            return &CSTD.value.pAtkBUnc;
        case 28: //pAtkNormal
            return &CSTD.value.pAtkNormal;
        case 29: //pAtkFor
            return &CSTD.value.pAtkFor;
        case 30: //pAtkBack
            return &CSTD.value.pAtkBack;
        case 31: //pAtkL
            return &CSTD.value.pAtkL;
        case 32: //pAtkR
            return &CSTD.value.pAtkR;
        case 33: //unused4
            *FieldValues = &CSTD.value.unused4[0];
            return NULL;
        case 34: //holdTimerMin
            return &CSTD.value.holdTimerMin;
        case 35: //holdTimerMax
            return &CSTD.value.holdTimerMax;
        case 36: //flags
            return &CSTD.value.flags;
        case 37: //unused5
            *FieldValues = &CSTD.value.unused5[0];
            return NULL;
        case 38: //acroDodge
            return &CSTD.value.acroDodge;
        case 39: //rushChance
            return &CSTD.value.rushChance;
        case 40: //unused6
            *FieldValues = &CSTD.value.unused6[0];
            return NULL;
        case 41: //rushMult
            return &CSTD.value.rushMult;
        case 42: //dodgeFMult
            return &CSAD.value.dodgeFMult;
        case 43: //dodgeFBase
            return &CSAD.value.dodgeFBase;
        case 44: //encSBase
            return &CSAD.value.encSBase;
        case 45: //encSMult
            return &CSAD.value.encSMult;
        case 46: //dodgeAtkMult
            return &CSAD.value.dodgeAtkMult;
        case 47: //dodgeNAtkMult
            return &CSAD.value.dodgeNAtkMult;
        case 48: //dodgeBAtkMult
            return &CSAD.value.dodgeBAtkMult;
        case 49: //dodgeBNAtkMult
            return &CSAD.value.dodgeBNAtkMult;
        case 50: //dodgeFAtkMult
            return &CSAD.value.dodgeFAtkMult;
        case 51: //dodgeFNAtkMult
            return &CSAD.value.dodgeFNAtkMult;
        case 52: //blockMult
            return &CSAD.value.blockMult;
        case 53: //blockBase
            return &CSAD.value.blockBase;
        case 54: //blockAtkMult
            return &CSAD.value.blockAtkMult;
        case 55: //blockNAtkMult
            return &CSAD.value.blockNAtkMult;
        case 56: //atkMult
            return &CSAD.value.atkMult;
        case 57: //atkBase
            return &CSAD.value.atkBase;
        case 58: //atkAtkMult
            return &CSAD.value.atkAtkMult;
        case 59: //atkNAtkMult
            return &CSAD.value.atkNAtkMult;
        case 60: //atkBlockMult
            return &CSAD.value.atkBlockMult;
        case 61: //pAtkFBase
            return &CSAD.value.pAtkFBase;
        case 62: //pAtkFMult
            return &CSAD.value.pAtkFMult;
        case 63: //coverRadius
            return &CSSD.value.coverRadius;
        case 64: //coverChance
            return &CSSD.value.coverChance;
        case 65: //waitTimerMin
            return &CSSD.value.waitTimerMin;
        case 66: //waitTimerMax
            return &CSSD.value.waitTimerMax;
        case 67: //waitFireTimerMin
            return &CSSD.value.waitFireTimerMin;
        case 68: //waitFireTimerMax
            return &CSSD.value.waitFireTimerMax;
        case 69: //fireTimerMin
            return &CSSD.value.fireTimerMin;
        case 70: //fireTimerMax
            return &CSSD.value.fireTimerMax;
        case 71: //rangedRangeMultMin
            return &CSSD.value.rangedRangeMultMin;
        case 72: //unused7
            *FieldValues = &CSSD.value.unused1[0];
            return NULL;
        case 73: //weaponRestrictions
            return &CSSD.value.weaponRestrictions;
        case 74: //rangedRangeMultMax
            return &CSSD.value.rangedRangeMultMax;
        case 75: //targetMaxFOV
            return &CSSD.value.targetMaxFOV;
        case 76: //combatRadius
            return &CSSD.value.combatRadius;
        case 77: //semiAutoFireDelayMultMin
            return &CSSD.value.semiAutoFireDelayMultMin;
        case 78: //semiAutoFireDelayMultMax
            return &CSSD.value.semiAutoFireDelayMultMax;
        default:
            return NULL;
        }
    return NULL;
    }

bool CSTYRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //dodgeChance
            CSTD.value.dodgeChance = *(uint8_t *)FieldValue;
            break;
        case 8: //lrChance
            CSTD.value.lrChance = *(uint8_t *)FieldValue;
            break;
        case 9: //unused1
            if(ArraySize != 2)
                break;
            CSTD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 10: //lrTimerMin
            CSTD.value.lrTimerMin = *(float *)FieldValue;
            break;
        case 11: //lrTimerMax
            CSTD.value.lrTimerMax = *(float *)FieldValue;
            break;
        case 12: //forTimerMin
            CSTD.value.forTimerMin = *(float *)FieldValue;
            break;
        case 13: //forTimerMax
            CSTD.value.forTimerMax = *(float *)FieldValue;
            break;
        case 14: //backTimerMin
            CSTD.value.backTimerMin = *(float *)FieldValue;
            break;
        case 15: //backTimerMax
            CSTD.value.backTimerMax = *(float *)FieldValue;
            break;
        case 16: //idleTimerMin
            CSTD.value.idleTimerMin = *(float *)FieldValue;
            break;
        case 17: //idleTimerMax
            CSTD.value.idleTimerMax = *(float *)FieldValue;
            break;
        case 18: //blkChance
            CSTD.value.blkChance = *(uint8_t *)FieldValue;
            break;
        case 19: //atkChance
            CSTD.value.atkChance = *(uint8_t *)FieldValue;
            break;
        case 20: //unused2
            if(ArraySize != 2)
                break;
            CSTD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 21: //atkBRecoil
            CSTD.value.atkBRecoil = *(float *)FieldValue;
            break;
        case 22: //atkBUnc
            CSTD.value.atkBUnc = *(float *)FieldValue;
            break;
        case 23: //atkBh2h
            CSTD.value.atkBh2h = *(float *)FieldValue;
            break;
        case 24: //pAtkChance
            CSTD.value.pAtkChance = *(uint8_t *)FieldValue;
            break;
        case 25: //unused3
            if(ArraySize != 3)
                break;
            CSTD.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 26: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = *(float *)FieldValue;
            break;
        case 27: //pAtkBUnc
            CSTD.value.pAtkBUnc = *(float *)FieldValue;
            break;
        case 28: //pAtkNormal
            CSTD.value.pAtkNormal = *(uint8_t *)FieldValue;
            break;
        case 29: //pAtkFor
            CSTD.value.pAtkFor = *(uint8_t *)FieldValue;
            break;
        case 30: //pAtkBack
            CSTD.value.pAtkBack = *(uint8_t *)FieldValue;
            break;
        case 31: //pAtkL
            CSTD.value.pAtkL = *(uint8_t *)FieldValue;
            break;
        case 32: //pAtkR
            CSTD.value.pAtkR = *(uint8_t *)FieldValue;
            break;
        case 33: //unused4
            if(ArraySize != 3)
                break;
            CSTD.value.unused4[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused4[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused4[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 34: //holdTimerMin
            CSTD.value.holdTimerMin = *(float *)FieldValue;
            break;
        case 35: //holdTimerMax
            CSTD.value.holdTimerMax = *(float *)FieldValue;
            break;
        case 36: //flags
            SetFlagMask(*(uint16_t *)FieldValue);
            break;
        case 37: //unused5
            if(ArraySize != 2)
                break;
            CSTD.value.unused5[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused5[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 38: //acroDodge
            CSTD.value.acroDodge = *(uint8_t *)FieldValue;
            break;
        case 39: //rushChance
            CSTD.value.rushChance = *(uint8_t *)FieldValue;
            break;
        case 40: //unused6
            if(ArraySize != 2)
                break;
            CSTD.value.unused6[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused6[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 41: //rushMult
            CSTD.value.rushMult = *(float *)FieldValue;
            break;
        case 42: //dodgeFMult
            CSAD.value.dodgeFMult = *(float *)FieldValue;
            break;
        case 43: //dodgeFBase
            CSAD.value.dodgeFBase = *(float *)FieldValue;
            break;
        case 44: //encSBase
            CSAD.value.encSBase = *(float *)FieldValue;
            break;
        case 45: //encSMult
            CSAD.value.encSMult = *(float *)FieldValue;
            break;
        case 46: //dodgeAtkMult
            CSAD.value.dodgeAtkMult = *(float *)FieldValue;
            break;
        case 47: //dodgeNAtkMult
            CSAD.value.dodgeNAtkMult = *(float *)FieldValue;
            break;
        case 48: //dodgeBAtkMult
            CSAD.value.dodgeBAtkMult = *(float *)FieldValue;
            break;
        case 49: //dodgeBNAtkMult
            CSAD.value.dodgeBNAtkMult = *(float *)FieldValue;
            break;
        case 50: //dodgeFAtkMult
            CSAD.value.dodgeFAtkMult = *(float *)FieldValue;
            break;
        case 51: //dodgeFNAtkMult
            CSAD.value.dodgeFNAtkMult = *(float *)FieldValue;
            break;
        case 52: //blockMult
            CSAD.value.blockMult = *(float *)FieldValue;
            break;
        case 53: //blockBase
            CSAD.value.blockBase = *(float *)FieldValue;
            break;
        case 54: //blockAtkMult
            CSAD.value.blockAtkMult = *(float *)FieldValue;
            break;
        case 55: //blockNAtkMult
            CSAD.value.blockNAtkMult = *(float *)FieldValue;
            break;
        case 56: //atkMult
            CSAD.value.atkMult = *(float *)FieldValue;
            break;
        case 57: //atkBase
            CSAD.value.atkBase = *(float *)FieldValue;
            break;
        case 58: //atkAtkMult
            CSAD.value.atkAtkMult = *(float *)FieldValue;
            break;
        case 59: //atkNAtkMult
            CSAD.value.atkNAtkMult = *(float *)FieldValue;
            break;
        case 60: //atkBlockMult
            CSAD.value.atkBlockMult = *(float *)FieldValue;
            break;
        case 61: //pAtkFBase
            CSAD.value.pAtkFBase = *(float *)FieldValue;
            break;
        case 62: //pAtkFMult
            CSAD.value.pAtkFMult = *(float *)FieldValue;
            break;
        case 63: //coverRadius
            CSSD.value.coverRadius = *(float *)FieldValue;
            break;
        case 64: //coverChance
            CSSD.value.coverChance = *(float *)FieldValue;
            break;
        case 65: //waitTimerMin
            CSSD.value.waitTimerMin = *(float *)FieldValue;
            break;
        case 66: //waitTimerMax
            CSSD.value.waitTimerMax = *(float *)FieldValue;
            break;
        case 67: //waitFireTimerMin
            CSSD.value.waitFireTimerMin = *(float *)FieldValue;
            break;
        case 68: //waitFireTimerMax
            CSSD.value.waitFireTimerMax = *(float *)FieldValue;
            break;
        case 69: //fireTimerMin
            CSSD.value.fireTimerMin = *(float *)FieldValue;
            break;
        case 70: //fireTimerMax
            CSSD.value.fireTimerMax = *(float *)FieldValue;
            break;
        case 71: //rangedRangeMultMin
            CSSD.value.rangedRangeMultMin = *(float *)FieldValue;
            break;
        case 72: //unused7
            if(ArraySize != 4)
                break;
            CSSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CSSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            CSSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            CSSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 73: //weaponRestrictions
            SetType(*(uint32_t *)FieldValue);
            break;
        case 74: //rangedRangeMultMax
            CSSD.value.rangedRangeMultMax = *(float *)FieldValue;
            break;
        case 75: //targetMaxFOV
            CSSD.value.targetMaxFOV = *(float *)FieldValue;
            break;
        case 76: //combatRadius
            CSSD.value.combatRadius = *(float *)FieldValue;
            break;
        case 77: //semiAutoFireDelayMultMin
            CSSD.value.semiAutoFireDelayMultMin = *(float *)FieldValue;
            break;
        case 78: //semiAutoFireDelayMultMax
            CSSD.value.semiAutoFireDelayMultMax = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void CSTYRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    CSTYCSTD defaultCSTD;
    CSTYCSAD defaultCSAD;
    CSTYCSSD defaultCSSD;
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
        case 7: //dodgeChance
            CSTD.value.dodgeChance = defaultCSTD.dodgeChance;
            return;
        case 8: //lrChance
            CSTD.value.lrChance = defaultCSTD.lrChance;
            return;
        case 9: //unused1
            CSTD.value.unused1[0] = defaultCSTD.unused1[0];
            CSTD.value.unused1[1] = defaultCSTD.unused1[1];
            return;
        case 10: //lrTimerMin
            CSTD.value.lrTimerMin = defaultCSTD.lrTimerMin;
            return;
        case 11: //lrTimerMax
            CSTD.value.lrTimerMax = defaultCSTD.lrTimerMax;
            return;
        case 12: //forTimerMin
            CSTD.value.forTimerMin = defaultCSTD.forTimerMin;
            return;
        case 13: //forTimerMax
            CSTD.value.forTimerMax = defaultCSTD.forTimerMax;
            return;
        case 14: //backTimerMin
            CSTD.value.backTimerMin = defaultCSTD.backTimerMin;
            return;
        case 15: //backTimerMax
            CSTD.value.backTimerMax = defaultCSTD.backTimerMax;
            return;
        case 16: //idleTimerMin
            CSTD.value.idleTimerMin = defaultCSTD.idleTimerMin;
            return;
        case 17: //idleTimerMax
            CSTD.value.idleTimerMax = defaultCSTD.idleTimerMax;
            return;
        case 18: //blkChance
            CSTD.value.blkChance = defaultCSTD.blkChance;
            return;
        case 19: //atkChance
            CSTD.value.atkChance = defaultCSTD.atkChance;
            return;
        case 20: //unused2
            CSTD.value.unused2[0] = defaultCSTD.unused2[0];
            CSTD.value.unused2[1] = defaultCSTD.unused2[1];
            return;
        case 21: //atkBRecoil
            CSTD.value.atkBRecoil = defaultCSTD.atkBRecoil;
            return;
        case 22: //atkBUnc
            CSTD.value.atkBUnc = defaultCSTD.atkBUnc;
            return;
        case 23: //atkBh2h
            CSTD.value.atkBh2h = defaultCSTD.atkBh2h;
            return;
        case 24: //pAtkChance
            CSTD.value.pAtkChance = defaultCSTD.pAtkChance;
            return;
        case 25: //unused3
            CSTD.value.unused3[0] = defaultCSTD.unused3[0];
            CSTD.value.unused3[1] = defaultCSTD.unused3[1];
            CSTD.value.unused3[2] = defaultCSTD.unused3[2];
            return;
        case 26: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = defaultCSTD.pAtkBRecoil;
            return;
        case 27: //pAtkBUnc
            CSTD.value.pAtkBUnc = defaultCSTD.pAtkBUnc;
            return;
        case 28: //pAtkNormal
            CSTD.value.pAtkNormal = defaultCSTD.pAtkNormal;
            return;
        case 29: //pAtkFor
            CSTD.value.pAtkFor = defaultCSTD.pAtkFor;
            return;
        case 30: //pAtkBack
            CSTD.value.pAtkBack = defaultCSTD.pAtkBack;
            return;
        case 31: //pAtkL
            CSTD.value.pAtkL = defaultCSTD.pAtkL;
            return;
        case 32: //pAtkR
            CSTD.value.pAtkR = defaultCSTD.pAtkR;
            return;
        case 33: //unused4
            CSTD.value.unused4[0] = defaultCSTD.unused4[0];
            CSTD.value.unused4[1] = defaultCSTD.unused4[1];
            CSTD.value.unused4[2] = defaultCSTD.unused4[2];
            return;
        case 34: //holdTimerMin
            CSTD.value.holdTimerMin = defaultCSTD.holdTimerMin;
            return;
        case 35: //holdTimerMax
            CSTD.value.holdTimerMax = defaultCSTD.holdTimerMax;
            return;
        case 36: //flags
            SetFlagMask(defaultCSTD.flags);
            return;
        case 37: //unused5
            CSTD.value.unused5[0] = defaultCSTD.unused5[0];
            CSTD.value.unused5[1] = defaultCSTD.unused5[1];
            return;
        case 38: //acroDodge
            CSTD.value.acroDodge = defaultCSTD.acroDodge;
            return;
        case 39: //rushChance
            CSTD.value.rushChance = defaultCSTD.rushChance;
            return;
        case 40: //unused6
            CSTD.value.unused6[0] = defaultCSTD.unused6[0];
            CSTD.value.unused6[1] = defaultCSTD.unused6[1];
            return;
        case 41: //rushMult
            CSTD.value.rushMult = defaultCSTD.rushMult;
            return;
        case 42: //dodgeFMult
            CSAD.value.dodgeFMult = defaultCSAD.dodgeFMult;
            return;
        case 43: //dodgeFBase
            CSAD.value.dodgeFBase = defaultCSAD.dodgeFBase;
            return;
        case 44: //encSBase
            CSAD.value.encSBase = defaultCSAD.encSBase;
            return;
        case 45: //encSMult
            CSAD.value.encSMult = defaultCSAD.encSMult;
            return;
        case 46: //dodgeAtkMult
            CSAD.value.dodgeAtkMult = defaultCSAD.dodgeAtkMult;
            return;
        case 47: //dodgeNAtkMult
            CSAD.value.dodgeNAtkMult = defaultCSAD.dodgeNAtkMult;
            return;
        case 48: //dodgeBAtkMult
            CSAD.value.dodgeBAtkMult = defaultCSAD.dodgeBAtkMult;
            return;
        case 49: //dodgeBNAtkMult
            CSAD.value.dodgeBNAtkMult = defaultCSAD.dodgeBNAtkMult;
            return;
        case 50: //dodgeFAtkMult
            CSAD.value.dodgeFAtkMult = defaultCSAD.dodgeFAtkMult;
            return;
        case 51: //dodgeFNAtkMult
            CSAD.value.dodgeFNAtkMult = defaultCSAD.dodgeFNAtkMult;
            return;
        case 52: //blockMult
            CSAD.value.blockMult = defaultCSAD.blockMult;
            return;
        case 53: //blockBase
            CSAD.value.blockBase = defaultCSAD.blockBase;
            return;
        case 54: //blockAtkMult
            CSAD.value.blockAtkMult = defaultCSAD.blockAtkMult;
            return;
        case 55: //blockNAtkMult
            CSAD.value.blockNAtkMult = defaultCSAD.blockNAtkMult;
            return;
        case 56: //atkMult
            CSAD.value.atkMult = defaultCSAD.atkMult;
            return;
        case 57: //atkBase
            CSAD.value.atkBase = defaultCSAD.atkBase;
            return;
        case 58: //atkAtkMult
            CSAD.value.atkAtkMult = defaultCSAD.atkAtkMult;
            return;
        case 59: //atkNAtkMult
            CSAD.value.atkNAtkMult = defaultCSAD.atkNAtkMult;
            return;
        case 60: //atkBlockMult
            CSAD.value.atkBlockMult = defaultCSAD.atkBlockMult;
            return;
        case 61: //pAtkFBase
            CSAD.value.pAtkFBase = defaultCSAD.pAtkFBase;
            return;
        case 62: //pAtkFMult
            CSAD.value.pAtkFMult = defaultCSAD.pAtkFMult;
            return;
        case 63: //coverRadius
            CSSD.value.coverRadius = defaultCSSD.coverRadius;
            return;
        case 64: //coverChance
            CSSD.value.coverChance = defaultCSSD.coverChance;
            return;
        case 65: //waitTimerMin
            CSSD.value.waitTimerMin = defaultCSSD.waitTimerMin;
            return;
        case 66: //waitTimerMax
            CSSD.value.waitTimerMax = defaultCSSD.waitTimerMax;
            return;
        case 67: //waitFireTimerMin
            CSSD.value.waitFireTimerMin =defaultCSSD.waitFireTimerMin;
            break;
        case 68: //waitFireTimerMax
            CSSD.value.waitFireTimerMax = defaultCSSD.waitFireTimerMax;
            break;
        case 69: //fireTimerMin
            CSSD.value.fireTimerMin = defaultCSSD.fireTimerMin;
            return;
        case 70: //fireTimerMax
            CSSD.value.fireTimerMax = defaultCSSD.fireTimerMax;
            return;
        case 71: //rangedRangeMultMin
            CSSD.value.rangedRangeMultMin = defaultCSSD.rangedRangeMultMin;
            return;
        case 72: //unused7
            CSSD.value.unused1[0] = defaultCSSD.unused1[0];
            CSSD.value.unused1[1] = defaultCSSD.unused1[1];
            CSSD.value.unused1[2] = defaultCSSD.unused1[2];
            CSSD.value.unused1[3] = defaultCSSD.unused1[3];
            return;
        case 73: //weaponRestrictions
            SetType(defaultCSSD.weaponRestrictions);
            return;
        case 74: //rangedRangeMultMax
            CSSD.value.rangedRangeMultMax = defaultCSSD.rangedRangeMultMax;
            return;
        case 75: //targetMaxFOV
            CSSD.value.targetMaxFOV = defaultCSSD.targetMaxFOV;
            return;
        case 76: //combatRadius
            CSSD.value.combatRadius = defaultCSSD.combatRadius;
            return;
        case 77: //semiAutoFireDelayMultMin
            CSSD.value.semiAutoFireDelayMultMin = defaultCSSD.semiAutoFireDelayMultMin;
            return;
        case 78: //semiAutoFireDelayMultMax
            CSSD.value.semiAutoFireDelayMultMax = defaultCSSD.semiAutoFireDelayMultMax;
            return;
        default:
            return;
        }
    }
}