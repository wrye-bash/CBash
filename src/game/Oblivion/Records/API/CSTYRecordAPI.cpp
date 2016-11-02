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
#include "..\CSTYRecord.h"

namespace Ob
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
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //dodgeChance
            return CB_UINT8_FIELD;
        case 6: //lrChance
            return CB_UINT8_FIELD;
        case 7: //unused1
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
        case 8: //lrTimerMin
            return CB_FLOAT32_FIELD;
        case 9: //lrTimerMax
            return CB_FLOAT32_FIELD;
        case 10: //forTimerMin
            return CB_FLOAT32_FIELD;
        case 11: //forTimerMax
            return CB_FLOAT32_FIELD;
        case 12: //backTimerMin
            return CB_FLOAT32_FIELD;
        case 13: //backTimerMax
            return CB_FLOAT32_FIELD;
        case 14: //idleTimerMin
            return CB_FLOAT32_FIELD;
        case 15: //idleTimerMax
            return CB_FLOAT32_FIELD;
        case 16: //blkChance
            return CB_UINT8_FIELD;
        case 17: //atkChance
            return CB_UINT8_FIELD;
        case 18: //unused2
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
        case 19: //atkBRecoil
            return CB_FLOAT32_FIELD;
        case 20: //atkBUnc
            return CB_FLOAT32_FIELD;
        case 21: //atkBh2h
            return CB_FLOAT32_FIELD;
        case 22: //pAtkChance
            return CB_UINT8_FIELD;
        case 23: //unused3
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
        case 24: //pAtkBRecoil
            return CB_FLOAT32_FIELD;
        case 25: //pAtkBUnc
            return CB_FLOAT32_FIELD;
        case 26: //pAtkNormal
            return CB_UINT8_FIELD;
        case 27: //pAtkFor
            return CB_UINT8_FIELD;
        case 28: //pAtkBack
            return CB_UINT8_FIELD;
        case 29: //pAtkL
            return CB_UINT8_FIELD;
        case 30: //pAtkR
            return CB_UINT8_FIELD;
        case 31: //unused4
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
        case 32: //holdTimerMin
            return CB_FLOAT32_FIELD;
        case 33: //holdTimerMax
            return CB_FLOAT32_FIELD;
        case 34: //flagsA
            return CB_UINT8_FLAG_FIELD;
        case 35: //acroDodge
            return CB_UINT8_FIELD;
        case 36: //unused5
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
        case 37: //rMultOpt
            return CB_FLOAT32_FIELD;
        case 38: //rMultMax
            return CB_FLOAT32_FIELD;
        case 39: //mDistance
            return CB_FLOAT32_FIELD;
        case 40: //rDistance
            return CB_FLOAT32_FIELD;
        case 41: //buffStand
            return CB_FLOAT32_FIELD;
        case 42: //rStand
            return CB_FLOAT32_FIELD;
        case 43: //groupStand
            return CB_FLOAT32_FIELD;
        case 44: //rushChance
            return CB_UINT8_FIELD;
        case 45: //unused6
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
        case 46: //rushMult
            return CB_FLOAT32_FIELD;
        case 47: //flagsB
            return CB_UINT32_FLAG_FIELD;
        case 48: //dodgeFMult
            return CB_FLOAT32_FIELD;
        case 49: //dodgeFBase
            return CB_FLOAT32_FIELD;
        case 50: //encSBase
            return CB_FLOAT32_FIELD;
        case 51: //encSMult
            return CB_FLOAT32_FIELD;
        case 52: //dodgeAtkMult
            return CB_FLOAT32_FIELD;
        case 53: //dodgeNAtkMult
            return CB_FLOAT32_FIELD;
        case 54: //dodgeBAtkMult
            return CB_FLOAT32_FIELD;
        case 55: //dodgeBNAtkMult
            return CB_FLOAT32_FIELD;
        case 56: //dodgeFAtkMult
            return CB_FLOAT32_FIELD;
        case 57: //dodgeFNAtkMult
            return CB_FLOAT32_FIELD;
        case 58: //blockMult
            return CB_FLOAT32_FIELD;
        case 59: //blockBase
            return CB_FLOAT32_FIELD;
        case 60: //blockAtkMult
            return CB_FLOAT32_FIELD;
        case 61: //blockNAtkMult
            return CB_FLOAT32_FIELD;
        case 62: //atkMult
            return CB_FLOAT32_FIELD;
        case 63: //atkBase
            return CB_FLOAT32_FIELD;
        case 64: //atkAtkMult
            return CB_FLOAT32_FIELD;
        case 65: //atkNAtkMult
            return CB_FLOAT32_FIELD;
        case 66: //atkBlockMult
            return CB_FLOAT32_FIELD;
        case 67: //pAtkFBase
            return CB_FLOAT32_FIELD;
        case 68: //pAtkFMult
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
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //dodgeChance
            return &CSTD.value.dodgeChance;
        case 6: //lrChance
            return &CSTD.value.lrChance;
        case 7: //unused1
            *FieldValues = &CSTD.value.unused1[0];
            return NULL;
        case 8: //lrTimerMin
            return &CSTD.value.lrTimerMin;
        case 9: //lrTimerMax
            return &CSTD.value.lrTimerMax;
        case 10: //forTimerMin
            return &CSTD.value.forTimerMin;
        case 11: //forTimerMax
            return &CSTD.value.forTimerMax;
        case 12: //backTimerMin
            return &CSTD.value.backTimerMin;
        case 13: //backTimerMax
            return &CSTD.value.backTimerMax;
        case 14: //idleTimerMin
            return &CSTD.value.idleTimerMin;
        case 15: //idleTimerMax
            return &CSTD.value.idleTimerMax;
        case 16: //blkChance
            return &CSTD.value.blkChance;
        case 17: //atkChance
            return &CSTD.value.atkChance;
        case 18: //unused2
            *FieldValues = &CSTD.value.unused2[0];
            return NULL;
        case 19: //atkBRecoil
            return &CSTD.value.atkBRecoil;
        case 20: //atkBUnc
            return &CSTD.value.atkBUnc;
        case 21: //atkBh2h
            return &CSTD.value.atkBh2h;
        case 22: //pAtkChance
            return &CSTD.value.pAtkChance;
        case 23: //unused3
            *FieldValues = &CSTD.value.unused3[0];
            return NULL;
        case 24: //pAtkBRecoil
            return &CSTD.value.pAtkBRecoil;
        case 25: //pAtkBUnc
            return &CSTD.value.pAtkBUnc;
        case 26: //pAtkNormal
            return &CSTD.value.pAtkNormal;
        case 27: //pAtkFor
            return &CSTD.value.pAtkFor;
        case 28: //pAtkBack
            return &CSTD.value.pAtkBack;
        case 29: //pAtkL
            return &CSTD.value.pAtkL;
        case 30: //pAtkR
            return &CSTD.value.pAtkR;
        case 31: //unused4
            *FieldValues = &CSTD.value.unused4[0];
            return NULL;
        case 32: //holdTimerMin
            return &CSTD.value.holdTimerMin;
        case 33: //holdTimerMax
            return &CSTD.value.holdTimerMax;
        case 34: //flagsA
            return &CSTD.value.flagsA;
        case 35: //acroDodge
            return &CSTD.value.acroDodge;
        case 36: //unused5
            *FieldValues = &CSTD.value.unused5[0];
            return NULL;
        case 37: //rMultOpt
            return &CSTD.value.rMultOpt;
        case 38: //rMultMax
            return &CSTD.value.rMultMax;
        case 39: //mDistance
            return &CSTD.value.mDistance;
        case 40: //rDistance
            return &CSTD.value.rDistance;
        case 41: //buffStand
            return &CSTD.value.buffStand;
        case 42: //rStand
            return &CSTD.value.rStand;
        case 43: //groupStand
            return &CSTD.value.groupStand;
        case 44: //rushChance
            return &CSTD.value.rushChance;
        case 45: //unused6
            *FieldValues = &CSTD.value.unused6[0];
            return NULL;
        case 46: //rushMult
            return &CSTD.value.rushMult;
        case 47: //flagsB
            return &CSTD.value.flagsB;
        case 48: //dodgeFMult
            return CSAD.IsLoaded() ? &CSAD->dodgeFMult : NULL;
        case 49: //dodgeFBase
            return CSAD.IsLoaded() ? &CSAD->dodgeFBase : NULL;
        case 50: //encSBase
            return CSAD.IsLoaded() ? &CSAD->encSBase : NULL;
        case 51: //encSMult
            return CSAD.IsLoaded() ? &CSAD->encSMult : NULL;
        case 52: //dodgeAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeAtkMult : NULL;
        case 53: //dodgeNAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeNAtkMult : NULL;
        case 54: //dodgeBAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeBAtkMult : NULL;
        case 55: //dodgeBNAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeBNAtkMult : NULL;
        case 56: //dodgeFAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeFAtkMult : NULL;
        case 57: //dodgeFNAtkMult
            return CSAD.IsLoaded() ? &CSAD->dodgeFNAtkMult : NULL;
        case 58: //blockMult
            return CSAD.IsLoaded() ? &CSAD->blockMult : NULL;
        case 59: //blockBase
            return CSAD.IsLoaded() ? &CSAD->blockBase : NULL;
        case 60: //blockAtkMult
            return CSAD.IsLoaded() ? &CSAD->blockAtkMult : NULL;
        case 61: //blockNAtkMult
            return CSAD.IsLoaded() ? &CSAD->blockNAtkMult : NULL;
        case 62: //atkMult
            return CSAD.IsLoaded() ? &CSAD->atkMult : NULL;
        case 63: //atkBase
            return CSAD.IsLoaded() ? &CSAD->atkBase : NULL;
        case 64: //atkAtkMult
            return CSAD.IsLoaded() ? &CSAD->atkAtkMult : NULL;
        case 65: //atkNAtkMult
            return CSAD.IsLoaded() ? &CSAD->atkNAtkMult : NULL;
        case 66: //atkBlockMult
            return CSAD.IsLoaded() ? &CSAD->atkBlockMult : NULL;
        case 67: //pAtkFBase
            return CSAD.IsLoaded() ? &CSAD->pAtkFBase : NULL;
        case 68: //pAtkFMult
            return CSAD.IsLoaded() ? &CSAD->pAtkFMult : NULL;
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
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //dodgeChance
            CSTD.value.dodgeChance = *(uint8_t *)FieldValue;
            break;
        case 6: //lrChance
            CSTD.value.lrChance = *(uint8_t *)FieldValue;
            break;
        case 7: //unused1
            if(ArraySize != 2)
                break;
            CSTD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 8: //lrTimerMin
            CSTD.value.lrTimerMin = *(float *)FieldValue;
            break;
        case 9: //lrTimerMax
            CSTD.value.lrTimerMax = *(float *)FieldValue;
            break;
        case 10: //forTimerMin
            CSTD.value.forTimerMin = *(float *)FieldValue;
            break;
        case 11: //forTimerMax
            CSTD.value.forTimerMax = *(float *)FieldValue;
            break;
        case 12: //backTimerMin
            CSTD.value.backTimerMin = *(float *)FieldValue;
            break;
        case 13: //backTimerMax
            CSTD.value.backTimerMax = *(float *)FieldValue;
            break;
        case 14: //idleTimerMin
            CSTD.value.idleTimerMin = *(float *)FieldValue;
            break;
        case 15: //idleTimerMax
            CSTD.value.idleTimerMax = *(float *)FieldValue;
            break;
        case 16: //blkChance
            CSTD.value.blkChance = *(uint8_t *)FieldValue;
            break;
        case 17: //atkChance
            CSTD.value.atkChance = *(uint8_t *)FieldValue;
            break;
        case 18: //unused2
            if(ArraySize != 2)
                break;
            CSTD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 19: //atkBRecoil
            CSTD.value.atkBRecoil = *(float *)FieldValue;
            break;
        case 20: //atkBUnc
            CSTD.value.atkBUnc = *(float *)FieldValue;
            break;
        case 21: //atkBh2h
            CSTD.value.atkBh2h = *(float *)FieldValue;
            break;
        case 22: //pAtkChance
            CSTD.value.pAtkChance = *(uint8_t *)FieldValue;
            break;
        case 23: //unused3
            if(ArraySize != 3)
                break;
            CSTD.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 24: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = *(float *)FieldValue;
            break;
        case 25: //pAtkBUnc
            CSTD.value.pAtkBUnc = *(float *)FieldValue;
            break;
        case 26: //pAtkNormal
            CSTD.value.pAtkNormal = *(uint8_t *)FieldValue;
            break;
        case 27: //pAtkFor
            CSTD.value.pAtkFor = *(uint8_t *)FieldValue;
            break;
        case 28: //pAtkBack
            CSTD.value.pAtkBack = *(uint8_t *)FieldValue;
            break;
        case 29: //pAtkL
            CSTD.value.pAtkL = *(uint8_t *)FieldValue;
            break;
        case 30: //pAtkR
            CSTD.value.pAtkR = *(uint8_t *)FieldValue;
            break;
        case 31: //unused4
            if(ArraySize != 3)
                break;
            CSTD.value.unused4[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused4[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused4[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 32: //holdTimerMin
            CSTD.value.holdTimerMin = *(float *)FieldValue;
            break;
        case 33: //holdTimerMax
            CSTD.value.holdTimerMax = *(float *)FieldValue;
            break;
        case 34: //flagsA
            SetFlagAMask(*(uint8_t *)FieldValue);
            break;
        case 35: //acroDodge
            CSTD.value.acroDodge = *(uint8_t *)FieldValue;
            break;
        case 36: //unused5
            if(ArraySize != 2)
                break;
            CSTD.value.unused5[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused5[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 37: //rMultOpt
            CSTD.value.rMultOpt = *(float *)FieldValue;
            break;
        case 38: //rMultMax
            CSTD.value.rMultMax = *(float *)FieldValue;
            break;
        case 39: //mDistance
            CSTD.value.mDistance = *(float *)FieldValue;
            break;
        case 40: //rDistance
            CSTD.value.rDistance = *(float *)FieldValue;
            break;
        case 41: //buffStand
            CSTD.value.buffStand = *(float *)FieldValue;
            break;
        case 42: //rStand
            CSTD.value.rStand = *(float *)FieldValue;
            break;
        case 43: //groupStand
            CSTD.value.groupStand = *(float *)FieldValue;
            break;
        case 44: //rushChance
            CSTD.value.rushChance = *(uint8_t *)FieldValue;
            break;
        case 45: //unused6
            if(ArraySize != 3)
                break;
            CSTD.value.unused6[0] = ((UINT8ARRAY)FieldValue)[0];
            CSTD.value.unused6[1] = ((UINT8ARRAY)FieldValue)[1];
            CSTD.value.unused6[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 46: //rushMult
            CSTD.value.rushMult = *(float *)FieldValue;
            break;
        case 47: //flagsB
            SetFlagBMask(*(uint32_t *)FieldValue);
            break;
        case 48: //dodgeFMult
            CSAD.Load();
            CSAD->dodgeFMult = *(float *)FieldValue;
            break;
        case 49: //dodgeFBase
            CSAD.Load();
            CSAD->dodgeFBase = *(float *)FieldValue;
            break;
        case 50: //encSBase
            CSAD.Load();
            CSAD->encSBase = *(float *)FieldValue;
            break;
        case 51: //encSMult
            CSAD.Load();
            CSAD->encSMult = *(float *)FieldValue;
            break;
        case 52: //dodgeAtkMult
            CSAD.Load();
            CSAD->dodgeAtkMult = *(float *)FieldValue;
            break;
        case 53: //dodgeNAtkMult
            CSAD.Load();
            CSAD->dodgeNAtkMult = *(float *)FieldValue;
            break;
        case 54: //dodgeBAtkMult
            CSAD.Load();
            CSAD->dodgeBAtkMult = *(float *)FieldValue;
            break;
        case 55: //dodgeBNAtkMult
            CSAD.Load();
            CSAD->dodgeBNAtkMult = *(float *)FieldValue;
            break;
        case 56: //dodgeFAtkMult
            CSAD.Load();
            CSAD->dodgeFAtkMult = *(float *)FieldValue;
            break;
        case 57: //dodgeFNAtkMult
            CSAD.Load();
            CSAD->dodgeFNAtkMult = *(float *)FieldValue;
            break;
        case 58: //blockMult
            CSAD.Load();
            CSAD->blockMult = *(float *)FieldValue;
            break;
        case 59: //blockBase
            CSAD.Load();
            CSAD->blockBase = *(float *)FieldValue;
            break;
        case 60: //blockAtkMult
            CSAD.Load();
            CSAD->blockAtkMult = *(float *)FieldValue;
            break;
        case 61: //blockNAtkMult
            CSAD.Load();
            CSAD->blockNAtkMult = *(float *)FieldValue;
            break;
        case 62: //atkMult
            CSAD.Load();
            CSAD->atkMult = *(float *)FieldValue;
            break;
        case 63: //atkBase
            CSAD.Load();
            CSAD->atkBase = *(float *)FieldValue;
            break;
        case 64: //atkAtkMult
            CSAD.Load();
            CSAD->atkAtkMult = *(float *)FieldValue;
            break;
        case 65: //atkNAtkMult
            CSAD.Load();
            CSAD->atkNAtkMult = *(float *)FieldValue;
            break;
        case 66: //atkBlockMult
            CSAD.Load();
            CSAD->atkBlockMult = *(float *)FieldValue;
            break;
        case 67: //pAtkFBase
            CSAD.Load();
            CSAD->pAtkFBase = *(float *)FieldValue;
            break;
        case 68: //pAtkFMult
            CSAD.Load();
            CSAD->pAtkFMult = *(float *)FieldValue;
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
        case 5: //dodgeChance
            CSTD.value.dodgeChance = defaultCSTD.dodgeChance;
            return;
        case 6: //lrChance
            CSTD.value.lrChance = defaultCSTD.lrChance;
            return;
        case 7: //unused1
            CSTD.value.unused1[0] = defaultCSTD.unused1[0];
            CSTD.value.unused1[1] = defaultCSTD.unused1[1];
            return;
        case 8: //lrTimerMin
            CSTD.value.lrTimerMin = defaultCSTD.lrTimerMin;
            return;
        case 9: //lrTimerMax
            CSTD.value.lrTimerMax = defaultCSTD.lrTimerMax;
            return;
        case 10: //forTimerMin
            CSTD.value.forTimerMin = defaultCSTD.forTimerMin;
            return;
        case 11: //forTimerMax
            CSTD.value.forTimerMax = defaultCSTD.forTimerMax;
            return;
        case 12: //backTimerMin
            CSTD.value.backTimerMin = defaultCSTD.backTimerMin;
            return;
        case 13: //backTimerMax
            CSTD.value.backTimerMax = defaultCSTD.backTimerMax;
            return;
        case 14: //idleTimerMin
            CSTD.value.idleTimerMin = defaultCSTD.idleTimerMin;
            return;
        case 15: //idleTimerMax
            CSTD.value.idleTimerMax = defaultCSTD.idleTimerMax;
            return;
        case 16: //blkChance
            CSTD.value.blkChance = defaultCSTD.blkChance;
            return;
        case 17: //atkChance
            CSTD.value.atkChance = defaultCSTD.atkChance;
            return;
        case 18: //unused2
            CSTD.value.unused2[0] = defaultCSTD.unused2[0];
            CSTD.value.unused2[1] = defaultCSTD.unused2[1];
            return;
        case 19: //atkBRecoil
            CSTD.value.atkBRecoil = defaultCSTD.atkBRecoil;
            return;
        case 20: //atkBUnc
            CSTD.value.atkBUnc = defaultCSTD.atkBUnc;
            return;
        case 21: //atkBh2h
            CSTD.value.atkBh2h = defaultCSTD.atkBh2h;
            return;
        case 22: //pAtkChance
            CSTD.value.pAtkChance = defaultCSTD.pAtkChance;
            return;
        case 23: //unused3
            CSTD.value.unused3[0] = defaultCSTD.unused3[0];
            CSTD.value.unused3[1] = defaultCSTD.unused3[1];
            CSTD.value.unused3[2] = defaultCSTD.unused3[2];
            return;
        case 24: //pAtkBRecoil
            CSTD.value.pAtkBRecoil = defaultCSTD.pAtkBRecoil;
            return;
        case 25: //pAtkBUnc
            CSTD.value.pAtkBUnc = defaultCSTD.pAtkBUnc;
            return;
        case 26: //pAtkNormal
            CSTD.value.pAtkNormal = defaultCSTD.pAtkNormal;
            return;
        case 27: //pAtkFor
            CSTD.value.pAtkFor = defaultCSTD.pAtkFor;
            return;
        case 28: //pAtkBack
            CSTD.value.pAtkBack = defaultCSTD.pAtkBack;
            return;
        case 29: //pAtkL
            CSTD.value.pAtkL = defaultCSTD.pAtkL;
            return;
        case 30: //pAtkR
            CSTD.value.pAtkR = defaultCSTD.pAtkR;
            return;
        case 31: //unused4
            CSTD.value.unused4[0] = defaultCSTD.unused4[0];
            CSTD.value.unused4[1] = defaultCSTD.unused4[1];
            CSTD.value.unused4[2] = defaultCSTD.unused4[2];
            return;
        case 32: //holdTimerMin
            CSTD.value.holdTimerMin = defaultCSTD.holdTimerMin;
            return;
        case 33: //holdTimerMax
            CSTD.value.holdTimerMax = defaultCSTD.holdTimerMax;
            return;
        case 34: //flagsA
            CSTD.value.flagsA = defaultCSTD.flagsA;
            return;
        case 35: //acroDodge
            CSTD.value.acroDodge = defaultCSTD.acroDodge;
            return;
        case 36: //unused5
            CSTD.value.unused5[0] = defaultCSTD.unused5[0];
            CSTD.value.unused5[1] = defaultCSTD.unused5[1];
            return;
        case 37: //rMultOpt
            CSTD.value.rMultOpt = defaultCSTD.rMultOpt;
            return;
        case 38: //rMultMax
            CSTD.value.rMultMax = defaultCSTD.rMultMax;
            return;
        case 39: //mDistance
            CSTD.value.mDistance = defaultCSTD.mDistance;
            return;
        case 40: //rDistance
            CSTD.value.rDistance = defaultCSTD.rDistance;
            return;
        case 41: //buffStand
            CSTD.value.buffStand = defaultCSTD.buffStand;
            return;
        case 42: //rStand
            CSTD.value.rStand = defaultCSTD.rStand;
            return;
        case 43: //groupStand
            CSTD.value.groupStand = defaultCSTD.groupStand;
            return;
        case 44: //rushChance
            CSTD.value.rushChance = defaultCSTD.rushChance;
            return;
        case 45: //unused6
            CSTD.value.unused6[0] = defaultCSTD.unused6[0];
            CSTD.value.unused6[1] = defaultCSTD.unused6[1];
            CSTD.value.unused6[2] = defaultCSTD.unused6[2];
            return;
        case 46: //rushMult
            CSTD.value.rushMult = defaultCSTD.rushMult;
            return;
        case 47: //flagsB
            CSTD.value.flagsB = defaultCSTD.flagsB;
            return;
        case 48: //dodgeFMult
            if(CSAD.IsLoaded())
                CSAD->dodgeFMult = defaultCSAD.dodgeFMult;
            return;
        case 49: //dodgeFBase
            if(CSAD.IsLoaded())
                CSAD->dodgeFBase = defaultCSAD.dodgeFBase;
            return;
        case 50: //encSBase
            if(CSAD.IsLoaded())
                CSAD->encSBase = defaultCSAD.encSBase;
            return;
        case 51: //encSMult
            if(CSAD.IsLoaded())
                CSAD->encSMult = defaultCSAD.encSMult;
            return;
        case 52: //dodgeAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeAtkMult = defaultCSAD.dodgeAtkMult;
            return;
        case 53: //dodgeNAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeNAtkMult = defaultCSAD.dodgeNAtkMult;
            return;
        case 54: //dodgeBAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeBAtkMult = defaultCSAD.dodgeBAtkMult;
            return;
        case 55: //dodgeBNAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeBNAtkMult = defaultCSAD.dodgeBNAtkMult;
            return;
        case 56: //dodgeFAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeFAtkMult = defaultCSAD.dodgeFAtkMult;
            return;
        case 57: //dodgeFNAtkMult
            if(CSAD.IsLoaded())
                CSAD->dodgeFNAtkMult = defaultCSAD.dodgeFNAtkMult;
            return;
        case 58: //blockMult
            if(CSAD.IsLoaded())
                CSAD->blockMult = defaultCSAD.blockMult;
            return;
        case 59: //blockBase
            if(CSAD.IsLoaded())
                CSAD->blockBase = defaultCSAD.blockBase;
            return;
        case 60: //blockAtkMult
            if(CSAD.IsLoaded())
                CSAD->blockAtkMult = defaultCSAD.blockAtkMult;
            return;
        case 61: //blockNAtkMult
            if(CSAD.IsLoaded())
                CSAD->blockNAtkMult = defaultCSAD.blockNAtkMult;
            return;
        case 62: //atkMult
            if(CSAD.IsLoaded())
                CSAD->atkMult = defaultCSAD.atkMult;
            return;
        case 63: //atkBase
            if(CSAD.IsLoaded())
                CSAD->atkBase = defaultCSAD.atkBase;
            return;
        case 64: //atkAtkMult
            if(CSAD.IsLoaded())
                CSAD->atkAtkMult = defaultCSAD.atkAtkMult;
            return;
        case 65: //atkNAtkMult
            if(CSAD.IsLoaded())
                CSAD->atkNAtkMult = defaultCSAD.atkNAtkMult;
            return;
        case 66: //atkBlockMult
            if(CSAD.IsLoaded())
                CSAD->atkBlockMult = defaultCSAD.atkBlockMult;
            return;
        case 67: //pAtkFBase
            if(CSAD.IsLoaded())
                CSAD->pAtkFBase = defaultCSAD.pAtkFBase;
            return;
        case 68: //pAtkFMult
            if(CSAD.IsLoaded())
                CSAD->pAtkFMult = defaultCSAD.pAtkFMult;
            return;
        default:
            return;
        }
    return;
    }
}