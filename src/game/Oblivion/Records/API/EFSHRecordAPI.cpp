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
#include "..\EFSHRecord.h"

namespace Ob
{
uint32_t EFSHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //fillTexturePath
            return CB_ISTRING_FIELD;
        case 6: //particleTexturePath
            return CB_ISTRING_FIELD;
        case 7: //flags
            return CB_UINT8_FLAG_FIELD;
        case 8: //unused1
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
        case 9: //memSBlend
            return CB_UINT32_FIELD;
        case 10: //memBlendOp
            return CB_UINT32_FIELD;
        case 11: //memZFunc
            return CB_UINT32_FIELD;
        case 12: //fillRed
            return CB_UINT8_FIELD;
        case 13: //fillGreen
            return CB_UINT8_FIELD;
        case 14: //fillBlue
            return CB_UINT8_FIELD;
        case 15: //unused2
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
        case 16: //fillAIn
            return CB_FLOAT32_FIELD;
        case 17: //fillAFull
            return CB_FLOAT32_FIELD;
        case 18: //fillAOut
            return CB_FLOAT32_FIELD;
        case 19: //fillAPRatio
            return CB_FLOAT32_FIELD;
        case 20: //fillAAmp
            return CB_FLOAT32_FIELD;
        case 21: //fillAFreq
            return CB_FLOAT32_FIELD;
        case 22: //fillAnimSpdU
            return CB_FLOAT32_FIELD;
        case 23: //fillAnimSpdV
            return CB_FLOAT32_FIELD;
        case 24: //edgeOff
            return CB_FLOAT32_FIELD;
        case 25: //edgeRed
            return CB_UINT8_FIELD;
        case 26: //edgeGreen
            return CB_UINT8_FIELD;
        case 27: //edgeBlue
            return CB_UINT8_FIELD;
        case 28: //unused3
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
        case 29: //edgeAIn
            return CB_FLOAT32_FIELD;
        case 30: //edgeAFull
            return CB_FLOAT32_FIELD;
        case 31: //edgeAOut
            return CB_FLOAT32_FIELD;
        case 32: //edgeAPRatio
            return CB_FLOAT32_FIELD;
        case 33: //edgeAAmp
            return CB_FLOAT32_FIELD;
        case 34: //edgeAFreq
            return CB_FLOAT32_FIELD;
        case 35: //fillAFRatio
            return CB_FLOAT32_FIELD;
        case 36: //edgeAFRatio
            return CB_FLOAT32_FIELD;
        case 37: //memDBlend
            return CB_UINT8_FIELD;
        case 38: //partSBlend
            return CB_UINT8_FIELD;
        case 39: //partBlendOp
            return CB_UINT8_FIELD;
        case 40: //partZFunc
            return CB_UINT8_FIELD;
        case 41: //partDBlend
            return CB_UINT8_FIELD;
        case 42: //partBUp
            return CB_FLOAT32_FIELD;
        case 43: //partBFull
            return CB_FLOAT32_FIELD;
        case 44: //partBDown
            return CB_FLOAT32_FIELD;
        case 45: //partBFRatio
            return CB_FLOAT32_FIELD;
        case 46: //partBPRatio
            return CB_FLOAT32_FIELD;
        case 47: //partLTime
            return CB_FLOAT32_FIELD;
        case 48: //partLDelta
            return CB_FLOAT32_FIELD;
        case 49: //partNSpd
            return CB_FLOAT32_FIELD;
        case 50: //partNAcc
            return CB_FLOAT32_FIELD;
        case 51: //partVel1
            return CB_FLOAT32_FIELD;
        case 52: //partVel2
            return CB_FLOAT32_FIELD;
        case 53: //partVel3
            return CB_FLOAT32_FIELD;
        case 54: //partAcc1
            return CB_FLOAT32_FIELD;
        case 55: //partAcc2
            return CB_FLOAT32_FIELD;
        case 56: //partAcc3
            return CB_FLOAT32_FIELD;
        case 57: //partKey1
            return CB_FLOAT32_FIELD;
        case 58: //partKey2
            return CB_FLOAT32_FIELD;
        case 59: //partKey1Time
            return CB_FLOAT32_FIELD;
        case 60: //partKey2Time
            return CB_FLOAT32_FIELD;
        case 61: //key1Red
            return CB_UINT8_FIELD;
        case 62: //key1Green
            return CB_UINT8_FIELD;
        case 63: //key1Blue
            return CB_UINT8_FIELD;
        case 64: //unused4
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
        case 65: //key2Red
            return CB_UINT8_FIELD;
        case 66: //key2Green
            return CB_UINT8_FIELD;
        case 67: //key2Blue
            return CB_UINT8_FIELD;
        case 68: //unused5
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
        case 69: //key3Red
            return CB_UINT8_FIELD;
        case 70: //key3Green
            return CB_UINT8_FIELD;
        case 71: //key3Blue
            return CB_UINT8_FIELD;
        case 72: //unused6
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
        case 73: //key1A
            return CB_FLOAT32_FIELD;
        case 74: //key2A
            return CB_FLOAT32_FIELD;
        case 75: //key3A
            return CB_FLOAT32_FIELD;
        case 76: //key1Time
            return CB_FLOAT32_FIELD;
        case 77: //key2Time
            return CB_FLOAT32_FIELD;
        case 78: //key3Time
            return CB_FLOAT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * EFSHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //fillTexturePath
            return ICON.value;
        case 6: //particleTexturePath
            return ICO2.value;
        case 7: //flags
            return &DATA.value.flags;
        case 8: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 9: //memSBlend
            return &DATA.value.memSBlend;
        case 10: //memBlendOp
            return &DATA.value.memBlendOp;
        case 11: //memZFunc
            return &DATA.value.memZFunc;
        case 12: //fillRed
            return &DATA.value.fill.red;
        case 13: //fillGreen
            return &DATA.value.fill.green;
        case 14: //fillBlue
            return &DATA.value.fill.blue;
        case 15: //unused2
            *FieldValues = &DATA.value.fill.unused1;
            return NULL;
        case 16: //fillAIn
            return &DATA.value.fillAIn;
        case 17: //fillAFull
            return &DATA.value.fillAFull;
        case 18: //fillAOut
            return &DATA.value.fillAOut;
        case 19: //fillAPRatio
            return &DATA.value.fillAPRatio;
        case 20: //fillAAmp
            return &DATA.value.fillAAmp;
        case 21: //fillAFreq
            return &DATA.value.fillAFreq;
        case 22: //fillAnimSpdU
            return &DATA.value.fillAnimSpdU;
        case 23: //fillAnimSpdV
            return &DATA.value.fillAnimSpdV;
        case 24: //edgeOff
            return &DATA.value.edgeOff;
        case 25: //edgeRed
            return &DATA.value.edge.red;
        case 26: //edgeGreen
            return &DATA.value.edge.green;
        case 27: //edgeBlue
            return &DATA.value.edge.blue;
        case 28: //unused3
            *FieldValues = &DATA.value.edge.unused1;
            return NULL;
        case 29: //edgeAIn
            return &DATA.value.edgeAIn;
        case 30: //edgeAFull
            return &DATA.value.edgeAFull;
        case 31: //edgeAOut
            return &DATA.value.edgeAOut;
        case 32: //edgeAPRatio
            return &DATA.value.edgeAPRatio;
        case 33: //edgeAAmp
            return &DATA.value.edgeAAmp;
        case 34: //edgeAFreq
            return &DATA.value.edgeAFreq;
        case 35: //fillAFRatio
            return &DATA.value.fillAFRatio;
        case 36: //edgeAFRatio
            return &DATA.value.edgeAFRatio;
        case 37: //memDBlend
            return &DATA.value.memDBlend;
        case 38: //partSBlend
            return &DATA.value.partSBlend;
        case 39: //partBlendOp
            return &DATA.value.partBlendOp;
        case 40: //partZFunc
            return &DATA.value.partZFunc;
        case 41: //partDBlend
            return &DATA.value.partDBlend;
        case 42: //partBUp
            return &DATA.value.partBUp;
        case 43: //partBFull
            return &DATA.value.partBFull;
        case 44: //partBDown
            return &DATA.value.partBDown;
        case 45: //partBFRatio
            return &DATA.value.partBFRatio;
        case 46: //partBPRatio
            return &DATA.value.partBPRatio;
        case 47: //partLTime
            return &DATA.value.partLTime;
        case 48: //partLDelta
            return &DATA.value.partLDelta;
        case 49: //partNSpd
            return &DATA.value.partNSpd;
        case 50: //partNAcc
            return &DATA.value.partNAcc;
        case 51: //partVel1
            return &DATA.value.partVel1;
        case 52: //partVel2
            return &DATA.value.partVel2;
        case 53: //partVel3
            return &DATA.value.partVel3;
        case 54: //partAcc1
            return &DATA.value.partAcc1;
        case 55: //partAcc2
            return &DATA.value.partAcc2;
        case 56: //partAcc3
            return &DATA.value.partAcc3;
        case 57: //partKey1
            return &DATA.value.partKey1;
        case 58: //partKey2
            return &DATA.value.partKey2;
        case 59: //partKey1Time
            return &DATA.value.partKey1Time;
        case 60: //partKey2Time
            return &DATA.value.partKey2Time;
        case 61: //key1Red
            return &DATA.value.key1.red;
        case 62: //key1Green
            return &DATA.value.key1.green;
        case 63: //key1Blue
            return &DATA.value.key1.blue;
        case 64: //unused4
            *FieldValues = &DATA.value.key1.unused1;
            return NULL;
        case 65: //key2Red
            return &DATA.value.key2.red;
        case 66: //key2Green
            return &DATA.value.key2.green;
        case 67: //key2Blue
            return &DATA.value.key2.blue;
        case 68: //unused5
            *FieldValues = &DATA.value.key2.unused1;
            return NULL;
        case 69: //key3Red
            return &DATA.value.key3.red;
        case 70: //key3Green
            return &DATA.value.key3.green;
        case 71: //key3Blue
            return &DATA.value.key3.blue;
        case 72: //unused6
            *FieldValues = &DATA.value.key3.unused1;
            return NULL;
        case 73: //key1A
            return &DATA.value.key1A;
        case 74: //key2A
            return &DATA.value.key2A;
        case 75: //key3A
            return &DATA.value.key3A;
        case 76: //key1Time
            return &DATA.value.key1Time;
        case 77: //key2Time
            return &DATA.value.key2Time;
        case 78: //key3Time
            return &DATA.value.key3Time;
        default:
            return NULL;
        }
    return NULL;
    }

bool EFSHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //fillTexturePath
            ICON.Copy((char *)FieldValue);
            break;
        case 6: //particleTexturePath
            ICO2.Copy((char *)FieldValue);
            break;
        case 7: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 8: //unused1
            if(ArraySize != 3)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 9: //memSBlend
            DATA.value.memSBlend = *(uint32_t *)FieldValue;
            break;
        case 10: //memBlendOp
            DATA.value.memBlendOp = *(uint32_t *)FieldValue;
            break;
        case 11: //memZFunc
            DATA.value.memZFunc = *(uint32_t *)FieldValue;
            break;
        case 12: //fillRed
            DATA.value.fill.red = *(uint8_t *)FieldValue;
            break;
        case 13: //fillGreen
            DATA.value.fill.green = *(uint8_t *)FieldValue;
            break;
        case 14: //fillBlue
            DATA.value.fill.blue = *(uint8_t *)FieldValue;
            break;
        case 15: //unused2
            if(ArraySize != 1)
                break;
            DATA.value.fill.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 16: //fillAIn
            DATA.value.fillAIn = *(float *)FieldValue;
            break;
        case 17: //fillAFull
            DATA.value.fillAFull = *(float *)FieldValue;
            break;
        case 18: //fillAOut
            DATA.value.fillAOut = *(float *)FieldValue;
            break;
        case 19: //fillAPRatio
            DATA.value.fillAPRatio = *(float *)FieldValue;
            break;
        case 20: //fillAAmp
            DATA.value.fillAAmp = *(float *)FieldValue;
            break;
        case 21: //fillAFreq
            DATA.value.fillAFreq = *(float *)FieldValue;
            break;
        case 22: //fillAnimSpdU
            DATA.value.fillAnimSpdU = *(float *)FieldValue;
            break;
        case 23: //fillAnimSpdV
            DATA.value.fillAnimSpdV = *(float *)FieldValue;
            break;
        case 24: //edgeOff
            DATA.value.edgeOff = *(float *)FieldValue;
            break;
        case 25: //edgeRed
            DATA.value.edge.red = *(uint8_t *)FieldValue;
            break;
        case 26: //edgeGreen
            DATA.value.edge.green = *(uint8_t *)FieldValue;
            break;
        case 27: //edgeBlue
            DATA.value.edge.blue = *(uint8_t *)FieldValue;
            break;
        case 28: //unused3
            if(ArraySize != 1)
                break;
            DATA.value.edge.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 29: //edgeAIn
            DATA.value.edgeAIn = *(float *)FieldValue;
            break;
        case 30: //edgeAFull
            DATA.value.edgeAFull = *(float *)FieldValue;
            break;
        case 31: //edgeAOut
            DATA.value.edgeAOut = *(float *)FieldValue;
            break;
        case 32: //edgeAPRatio
            DATA.value.edgeAPRatio = *(float *)FieldValue;
            break;
        case 33: //edgeAAmp
            DATA.value.edgeAAmp = *(float *)FieldValue;
            break;
        case 34: //edgeAFreq
            DATA.value.edgeAFreq = *(float *)FieldValue;
            break;
        case 35: //fillAFRatio
            DATA.value.fillAFRatio = *(float *)FieldValue;
            break;
        case 36: //edgeAFRatio
            DATA.value.edgeAFRatio = *(float *)FieldValue;
            break;
        case 37: //memDBlend
            DATA.value.memDBlend = *(uint8_t *)FieldValue;
            break;
        case 38: //partSBlend
            DATA.value.partSBlend = *(uint8_t *)FieldValue;
            break;
        case 39: //partBlendOp
            DATA.value.partBlendOp = *(uint8_t *)FieldValue;
            break;
        case 40: //partZFunc
            DATA.value.partZFunc = *(uint8_t *)FieldValue;
            break;
        case 41: //partDBlend
            DATA.value.partDBlend = *(uint8_t *)FieldValue;
            break;
        case 42: //partBUp
            DATA.value.partBUp = *(float *)FieldValue;
            break;
        case 43: //partBFull
            DATA.value.partBFull = *(float *)FieldValue;
            break;
        case 44: //partBDown
            DATA.value.partBDown = *(float *)FieldValue;
            break;
        case 45: //partBFRatio
            DATA.value.partBFRatio = *(float *)FieldValue;
            break;
        case 46: //partBPRatio
            DATA.value.partBPRatio = *(float *)FieldValue;
            break;
        case 47: //partLTime
            DATA.value.partLTime = *(float *)FieldValue;
            break;
        case 48: //partLDelta
            DATA.value.partLDelta = *(float *)FieldValue;
            break;
        case 49: //partNSpd
            DATA.value.partNSpd = *(float *)FieldValue;
            break;
        case 50: //partNAcc
            DATA.value.partNAcc = *(float *)FieldValue;
            break;
        case 51: //partVel1
            DATA.value.partVel1 = *(float *)FieldValue;
            break;
        case 52: //partVel2
            DATA.value.partVel2 = *(float *)FieldValue;
            break;
        case 53: //partVel3
            DATA.value.partVel3 = *(float *)FieldValue;
            break;
        case 54: //partAcc1
            DATA.value.partAcc1 = *(float *)FieldValue;
            break;
        case 55: //partAcc2
            DATA.value.partAcc2 = *(float *)FieldValue;
            break;
        case 56: //partAcc3
            DATA.value.partAcc3 = *(float *)FieldValue;
            break;
        case 57: //partKey1
            DATA.value.partKey1 = *(float *)FieldValue;
            break;
        case 58: //partKey2
            DATA.value.partKey2 = *(float *)FieldValue;
            break;
        case 59: //partKey1Time
            DATA.value.partKey1Time = *(float *)FieldValue;
            break;
        case 60: //partKey2Time
            DATA.value.partKey2Time = *(float *)FieldValue;
            break;
        case 61: //key1Red
            DATA.value.key1.red = *(uint8_t *)FieldValue;
            break;
        case 62: //key1Green
            DATA.value.key1.green = *(uint8_t *)FieldValue;
            break;
        case 63: //key1Blue
            DATA.value.key1.blue = *(uint8_t *)FieldValue;
            break;
        case 64: //unused4
            if(ArraySize != 1)
                break;
            DATA.value.key1.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 65: //key2Red
            DATA.value.key2.red = *(uint8_t *)FieldValue;
            break;
        case 66: //key2Green
            DATA.value.key2.green = *(uint8_t *)FieldValue;
            break;
        case 67: //key2Blue
            DATA.value.key2.blue = *(uint8_t *)FieldValue;
            break;
        case 68: //unused5
            if(ArraySize != 1)
                break;
            DATA.value.key2.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 69: //key3Red
            DATA.value.key3.red = *(uint8_t *)FieldValue;
            break;
        case 70: //key3Green
            DATA.value.key3.green = *(uint8_t *)FieldValue;
            break;
        case 71: //key3Blue
            DATA.value.key3.blue = *(uint8_t *)FieldValue;
            break;
        case 72: //unused6
            if(ArraySize != 1)
                break;
            DATA.value.key3.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 73: //key1A
            DATA.value.key1A = *(float *)FieldValue;
            break;
        case 74: //key2A
            DATA.value.key2A = *(float *)FieldValue;
            break;
        case 75: //key3A
            DATA.value.key3A = *(float *)FieldValue;
            break;
        case 76: //key1Time
            DATA.value.key1Time = *(float *)FieldValue;
            break;
        case 77: //key2Time
            DATA.value.key2Time = *(float *)FieldValue;
            break;
        case 78: //key3Time
            DATA.value.key3Time = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void EFSHRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    EFSHDATA defaultDATA;

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
        case 5: //fillTexturePath
            ICON.Unload();
            return;
        case 6: //particleTexturePath
            ICO2.Unload();
            return;
        case 7: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 8: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            DATA.value.unused1[2] = defaultDATA.unused1[2];
            return;
        case 9: //memSBlend
            DATA.value.memSBlend = defaultDATA.memSBlend;
            return;
        case 10: //memBlendOp
            DATA.value.memBlendOp = defaultDATA.memBlendOp;
            return;
        case 11: //memZFunc
            DATA.value.memZFunc = defaultDATA.memZFunc;
            return;
        case 12: //fillRed
            DATA.value.fill.red = defaultDATA.fill.red;
            return;
        case 13: //fillGreen
            DATA.value.fill.green = defaultDATA.fill.green;
            return;
        case 14: //fillBlue
            DATA.value.fill.blue = defaultDATA.fill.blue;
            return;
        case 15: //unused2
            DATA.value.fill.unused1 = defaultDATA.fill.unused1;
            return;
        case 16: //fillAIn
            DATA.value.fillAIn = defaultDATA.fillAIn;
            return;
        case 17: //fillAFull
            DATA.value.fillAFull = defaultDATA.fillAFull;
            return;
        case 18: //fillAOut
            DATA.value.fillAOut = defaultDATA.fillAOut;
            return;
        case 19: //fillAPRatio
            DATA.value.fillAPRatio = defaultDATA.fillAPRatio;
            return;
        case 20: //fillAAmp
            DATA.value.fillAAmp = defaultDATA.fillAAmp;
            return;
        case 21: //fillAFreq
            DATA.value.fillAFreq = defaultDATA.fillAFreq;
            return;
        case 22: //fillAnimSpdU
            DATA.value.fillAnimSpdU = defaultDATA.fillAnimSpdU;
            return;
        case 23: //fillAnimSpdV
            DATA.value.fillAnimSpdV = defaultDATA.fillAnimSpdV;
            return;
        case 24: //edgeOff
            DATA.value.edgeOff = defaultDATA.edgeOff;
            return;
        case 25: //edgeRed
            DATA.value.edge.red = defaultDATA.edge.red;
            return;
        case 26: //edgeGreen
            DATA.value.edge.green = defaultDATA.edge.green;
            return;
        case 27: //edgeBlue
            DATA.value.edge.blue = defaultDATA.edge.blue;
            return;
        case 28: //unused3
            DATA.value.edge.unused1 = defaultDATA.edge.unused1;
            return;
        case 29: //edgeAIn
            DATA.value.edgeAIn = defaultDATA.edgeAIn;
            return;
        case 30: //edgeAFull
            DATA.value.edgeAFull = defaultDATA.edgeAFull;
            return;
        case 31: //edgeAOut
            DATA.value.edgeAOut = defaultDATA.edgeAOut;
            return;
        case 32: //edgeAPRatio
            DATA.value.edgeAPRatio = defaultDATA.edgeAPRatio;
            return;
        case 33: //edgeAAmp
            DATA.value.edgeAAmp = defaultDATA.edgeAAmp;
            return;
        case 34: //edgeAFreq
            DATA.value.edgeAFreq = defaultDATA.edgeAFreq;
            return;
        case 35: //fillAFRatio
            DATA.value.fillAFRatio = defaultDATA.fillAFRatio;
            return;
        case 36: //edgeAFRatio
            DATA.value.edgeAFRatio = defaultDATA.edgeAFRatio;
            return;
        case 37: //memDBlend
            DATA.value.memDBlend = defaultDATA.memDBlend;
            return;
        case 38: //partSBlend
            DATA.value.partSBlend = defaultDATA.partSBlend;
            return;
        case 39: //partBlendOp
            DATA.value.partBlendOp = defaultDATA.partBlendOp;
            return;
        case 40: //partZFunc
            DATA.value.partZFunc = defaultDATA.partZFunc;
            return;
        case 41: //partDBlend
            DATA.value.partDBlend = defaultDATA.partDBlend;
            return;
        case 42: //partBUp
            DATA.value.partBUp = defaultDATA.partBUp;
            return;
        case 43: //partBFull
            DATA.value.partBFull = defaultDATA.partBFull;
            return;
        case 44: //partBDown
            DATA.value.partBDown = defaultDATA.partBDown;
            return;
        case 45: //partBFRatio
            DATA.value.partBFRatio = defaultDATA.partBFRatio;
            return;
        case 46: //partBPRatio
            DATA.value.partBPRatio = defaultDATA.partBPRatio;
            return;
        case 47: //partLTime
            DATA.value.partLTime = defaultDATA.partLTime;
            return;
        case 48: //partLDelta
            DATA.value.partLDelta = defaultDATA.partLDelta;
            return;
        case 49: //partNSpd
            DATA.value.partNSpd = defaultDATA.partNSpd;
            return;
        case 50: //partNAcc
            DATA.value.partNAcc = defaultDATA.partNAcc;
            return;
        case 51: //partVel1
            DATA.value.partVel1 = defaultDATA.partVel1;
            return;
        case 52: //partVel2
            DATA.value.partVel2 = defaultDATA.partVel2;
            return;
        case 53: //partVel3
            DATA.value.partVel3 = defaultDATA.partVel3;
            return;
        case 54: //partAcc1
            DATA.value.partAcc1 = defaultDATA.partAcc1;
            return;
        case 55: //partAcc2
            DATA.value.partAcc2 = defaultDATA.partAcc2;
            return;
        case 56: //partAcc3
            DATA.value.partAcc3 = defaultDATA.partAcc3;
            return;
        case 57: //partKey1
            DATA.value.partKey1 = defaultDATA.partKey1;
            return;
        case 58: //partKey2
            DATA.value.partKey2 = defaultDATA.partKey2;
            return;
        case 59: //partKey1Time
            DATA.value.partKey1Time = defaultDATA.partKey1Time;
            return;
        case 60: //partKey2Time
            DATA.value.partKey2Time = defaultDATA.partKey2Time;
            return;
        case 61: //key1Red
            DATA.value.key1.red = defaultDATA.key1.red;
            return;
        case 62: //key1Green
            DATA.value.key1.green = defaultDATA.key1.green;
            return;
        case 63: //key1Blue
            DATA.value.key1.blue = defaultDATA.key1.blue;
            return;
        case 64: //unused4
            DATA.value.key1.unused1 = defaultDATA.key1.unused1;
            return;
        case 65: //key2Red
            DATA.value.key2.red = defaultDATA.key2.red;
            return;
        case 66: //key2Green
            DATA.value.key2.green = defaultDATA.key2.green;
            return;
        case 67: //key2Blue
            DATA.value.key2.blue = defaultDATA.key2.blue;
            return;
        case 68: //unused5
            DATA.value.key2.unused1 = defaultDATA.key2.unused1;
            return;
        case 69: //key3Red
            DATA.value.key3.red = defaultDATA.key3.red;
            return;
        case 70: //key3Green
            DATA.value.key3.green = defaultDATA.key3.green;
            return;
        case 71: //key3Blue
            DATA.value.key3.blue = defaultDATA.key3.blue;
            return;
        case 72: //unused6
            DATA.value.key3.unused1 = defaultDATA.key3.unused1;
            return;
        case 73: //key1A
            DATA.value.key1A = defaultDATA.key1A;
            return;
        case 74: //key2A
            DATA.value.key2A = defaultDATA.key2A;
            return;
        case 75: //key3A
            DATA.value.key3A = defaultDATA.key3A;
            return;
        case 76: //key1Time
            DATA.value.key1Time = defaultDATA.key1Time;
            return;
        case 77: //key2Time
            DATA.value.key2Time = defaultDATA.key2Time;
            return;
        case 78: //key3Time
            DATA.value.key3Time = defaultDATA.key3Time;
            return;
        default:
            return;
        }
    return;
    }
}