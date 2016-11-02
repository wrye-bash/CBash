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

namespace FNV
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
        case 7: //fillPath
            return CB_ISTRING_FIELD;
        case 8: //particlePath
            return CB_ISTRING_FIELD;
        case 9: //holesPath
            return CB_ISTRING_FIELD;
        case 10: //flags
            return CB_UINT8_FLAG_FIELD;
        case 11: //unused1
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
        case 12: //memSBlend
            return CB_UINT32_FIELD;
        case 13: //memBlendOp
            return CB_UINT32_FIELD;
        case 14: //memZFunc
            return CB_UINT32_FIELD;
        case 15: //fill.red
            return CB_UINT8_FIELD;
        case 16: //fill.green
            return CB_UINT8_FIELD;
        case 17: //fill.blue
            return CB_UINT8_FIELD;
        case 18: //unused2
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
        case 19: //fillAIn
            return CB_FLOAT32_FIELD;
        case 20: //fillAFull
            return CB_FLOAT32_FIELD;
        case 21: //fillAOut
            return CB_FLOAT32_FIELD;
        case 22: //fillAPRatio
            return CB_FLOAT32_FIELD;
        case 23: //fillAAmp
            return CB_FLOAT32_FIELD;
        case 24: //fillAFreq
            return CB_FLOAT32_FIELD;
        case 25: //fillAnimSpdU
            return CB_FLOAT32_FIELD;
        case 26: //fillAnimSpdV
            return CB_FLOAT32_FIELD;
        case 27: //edgeEffOff
            return CB_FLOAT32_FIELD;
        case 28: //edgeEff.red
            return CB_UINT8_FIELD;
        case 29: //edgeEff.green
            return CB_UINT8_FIELD;
        case 30: //edgeEff.blue
            return CB_UINT8_FIELD;
        case 31: //unused3
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
        case 32: //edgeEffAIn
            return CB_FLOAT32_FIELD;
        case 33: //edgeEffAFull
            return CB_FLOAT32_FIELD;
        case 34: //edgeEffAOut
            return CB_FLOAT32_FIELD;
        case 35: //edgeEffAPRatio
            return CB_FLOAT32_FIELD;
        case 36: //edgeEffAAmp
            return CB_FLOAT32_FIELD;
        case 37: //edgeEffAFreq
            return CB_FLOAT32_FIELD;
        case 38: //fillAFRatio
            return CB_FLOAT32_FIELD;
        case 39: //edgeEffAFRatio
            return CB_FLOAT32_FIELD;
        case 40: //memDBlend
            return CB_UINT32_FIELD;
        case 41: //partSBlend
            return CB_UINT32_FIELD;
        case 42: //partBlendOp
            return CB_UINT32_FIELD;
        case 43: //partZFunc
            return CB_UINT32_FIELD;
        case 44: //partDBlend
            return CB_UINT32_FIELD;
        case 45: //partBUp
            return CB_FLOAT32_FIELD;
        case 46: //partBFull
            return CB_FLOAT32_FIELD;
        case 47: //partBDown
            return CB_FLOAT32_FIELD;
        case 48: //partBFRatio
            return CB_FLOAT32_FIELD;
        case 49: //partBPRatio
            return CB_FLOAT32_FIELD;
        case 50: //partLTime
            return CB_FLOAT32_FIELD;
        case 51: //partLDelta
            return CB_FLOAT32_FIELD;
        case 52: //partNSpd
            return CB_FLOAT32_FIELD;
        case 53: //partNAcc
            return CB_FLOAT32_FIELD;
        case 54: //partVel1
            return CB_FLOAT32_FIELD;
        case 55: //partVel2
            return CB_FLOAT32_FIELD;
        case 56: //partVel3
            return CB_FLOAT32_FIELD;
        case 57: //partAcc1
            return CB_FLOAT32_FIELD;
        case 58: //partAcc2
            return CB_FLOAT32_FIELD;
        case 59: //partAcc3
            return CB_FLOAT32_FIELD;
        case 60: //partKey1
            return CB_FLOAT32_FIELD;
        case 61: //partKey2
            return CB_FLOAT32_FIELD;
        case 62: //partKey1Time
            return CB_FLOAT32_FIELD;
        case 63: //partKey2Time
            return CB_FLOAT32_FIELD;
        case 64: //key1.red
            return CB_UINT8_FIELD;
        case 65: //key1.green
            return CB_UINT8_FIELD;
        case 66: //key1.blue
            return CB_UINT8_FIELD;
        case 67: //unused4
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
        case 68: //key2.red
            return CB_UINT8_FIELD;
        case 69: //key2.green
            return CB_UINT8_FIELD;
        case 70: //key2.blue
            return CB_UINT8_FIELD;
        case 71: //unused5
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
        case 72: //key3.red
            return CB_UINT8_FIELD;
        case 73: //key3.green
            return CB_UINT8_FIELD;
        case 74: //key3.blue
            return CB_UINT8_FIELD;
        case 75: //unused6
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
        case 76: //key1A
            return CB_FLOAT32_FIELD;
        case 77: //key2A
            return CB_FLOAT32_FIELD;
        case 78: //key3A
            return CB_FLOAT32_FIELD;
        case 79: //key1Time
            return CB_FLOAT32_FIELD;
        case 80: //key2Time
            return CB_FLOAT32_FIELD;
        case 81: //key3Time
            return CB_FLOAT32_FIELD;
        case 82: //partInitSpd
            return CB_FLOAT32_FIELD;
        case 83: //partInitRot
            return CB_FLOAT32_FIELD;
        case 84: //partInitRotDelta
            return CB_FLOAT32_FIELD;
        case 85: //partRotSpd
            return CB_FLOAT32_FIELD;
        case 86: //partRotDelta
            return CB_FLOAT32_FIELD;
        case 87: //addon
            return CB_FORMID_FIELD;
        case 88: //holesSTime
            return CB_FLOAT32_FIELD;
        case 89: //holesETime
            return CB_FLOAT32_FIELD;
        case 90: //holesSValue
            return CB_FLOAT32_FIELD;
        case 91: //holesEValue
            return CB_FLOAT32_FIELD;
        case 92: //edgeWidth
            return CB_FLOAT32_FIELD;
        case 93: //edge.red
            return CB_UINT8_FIELD;
        case 94: //edge.green
            return CB_UINT8_FIELD;
        case 95: //edge.blue
            return CB_UINT8_FIELD;
        case 96: //unused7
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
        case 97: //explWindSpd
            return CB_FLOAT32_FIELD;
        case 98: //textCountU
            return CB_UINT32_FIELD;
        case 99: //textCountV
            return CB_UINT32_FIELD;
        case 100: //addonFITime
            return CB_FLOAT32_FIELD;
        case 101: //addonFOTime
            return CB_FLOAT32_FIELD;
        case 102: //addonScaleStart
            return CB_FLOAT32_FIELD;
        case 103: //addonScaleEnd
            return CB_FLOAT32_FIELD;
        case 104: //addonScaleInTime
            return CB_FLOAT32_FIELD;
        case 105: //addonScaleOutTime
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
        case 7: //fillPath
            return ICON.value;
        case 8: //particlePath
            return ICO2.value;
        case 9: //holesPath
            return NAM7.value;
        case 10: //flags
            return &DATA.value.flags;
        case 11: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 12: //memSBlend
            return &DATA.value.memSBlend;
        case 13: //memBlendOp
            return &DATA.value.memBlendOp;
        case 14: //memZFunc
            return &DATA.value.memZFunc;
        case 15: //fill.red
            return &DATA.value.fill.red;
        case 16: //fill.green
            return &DATA.value.fill.green;
        case 17: //fill.blue
            return &DATA.value.fill.blue;
        case 18: //unused2
            *FieldValues = &DATA.value.fill.unused1;
            return NULL;
        case 19: //fillAIn
            return &DATA.value.fillAIn;
        case 20: //fillAFull
            return &DATA.value.fillAFull;
        case 21: //fillAOut
            return &DATA.value.fillAOut;
        case 22: //fillAPRatio
            return &DATA.value.fillAPRatio;
        case 23: //fillAAmp
            return &DATA.value.fillAAmp;
        case 24: //fillAFreq
            return &DATA.value.fillAFreq;
        case 25: //fillAnimSpdU
            return &DATA.value.fillAnimSpdU;
        case 26: //fillAnimSpdV
            return &DATA.value.fillAnimSpdV;
        case 27: //edgeEffOff
            return &DATA.value.edgeEffOff;
        case 28: //edgeEff.red
            return &DATA.value.edgeEff.red;
        case 29: //edgeEff.green
            return &DATA.value.edgeEff.green;
        case 30: //edgeEff.blue
            return &DATA.value.edgeEff.blue;
        case 31: //unused3
            *FieldValues = &DATA.value.edgeEff.unused1;
            return NULL;
        case 32: //edgeEffAIn
            return &DATA.value.edgeEffAIn;
        case 33: //edgeEffAFull
            return &DATA.value.edgeEffAFull;
        case 34: //edgeEffAOut
            return &DATA.value.edgeEffAOut;
        case 35: //edgeEffAPRatio
            return &DATA.value.edgeEffAPRatio;
        case 36: //edgeEffAAmp
            return &DATA.value.edgeEffAAmp;
        case 37: //edgeEffAFreq
            return &DATA.value.edgeEffAFreq;
        case 38: //fillAFRatio
            return &DATA.value.fillAFRatio;
        case 39: //edgeEffAFRatio
            return &DATA.value.edgeEffAFRatio;
        case 40: //memDBlend
            return &DATA.value.memDBlend;
        case 41: //partSBlend
            return &DATA.value.partSBlend;
        case 42: //partBlendOp
            return &DATA.value.partBlendOp;
        case 43: //partZFunc
            return &DATA.value.partZFunc;
        case 44: //partDBlend
            return &DATA.value.partDBlend;
        case 45: //partBUp
            return &DATA.value.partBUp;
        case 46: //partBFull
            return &DATA.value.partBFull;
        case 47: //partBDown
            return &DATA.value.partBDown;
        case 48: //partBFRatio
            return &DATA.value.partBFRatio;
        case 49: //partBPRatio
            return &DATA.value.partBPRatio;
        case 50: //partLTime
            return &DATA.value.partLTime;
        case 51: //partLDelta
            return &DATA.value.partLDelta;
        case 52: //partNSpd
            return &DATA.value.partNSpd;
        case 53: //partNAcc
            return &DATA.value.partNAcc;
        case 54: //partVel1
            return &DATA.value.partVel1;
        case 55: //partVel2
            return &DATA.value.partVel2;
        case 56: //partVel3
            return &DATA.value.partVel3;
        case 57: //partAcc1
            return &DATA.value.partAcc1;
        case 58: //partAcc2
            return &DATA.value.partAcc2;
        case 59: //partAcc3
            return &DATA.value.partAcc3;
        case 60: //partKey1
            return &DATA.value.partKey1;
        case 61: //partKey2
            return &DATA.value.partKey2;
        case 62: //partKey1Time
            return &DATA.value.partKey1Time;
        case 63: //partKey2Time
            return &DATA.value.partKey2Time;
        case 64: //key1.red
            return &DATA.value.key1.red;
        case 65: //key1.green
            return &DATA.value.key1.green;
        case 66: //key1.blue
            return &DATA.value.key1.blue;
        case 67: //unused4
            *FieldValues = &DATA.value.key1.unused1;
            return NULL;
        case 68: //key2.red
            return &DATA.value.key2.red;
        case 69: //key2.green
            return &DATA.value.key2.green;
        case 70: //key2.blue
            return &DATA.value.key2.blue;
        case 71: //unused5
            *FieldValues = &DATA.value.key2.unused1;
            return NULL;
        case 72: //key3.red
            return &DATA.value.key3.red;
        case 73: //key3.green
            return &DATA.value.key3.green;
        case 74: //key3.blue
            return &DATA.value.key3.blue;
        case 75: //unused6
            *FieldValues = &DATA.value.key3.unused1;
            return NULL;
        case 76: //key1A
            return &DATA.value.key1A;
        case 77: //key2A
            return &DATA.value.key2A;
        case 78: //key3A
            return &DATA.value.key3A;
        case 79: //key1Time
            return &DATA.value.key1Time;
        case 80: //key2Time
            return &DATA.value.key2Time;
        case 81: //key3Time
            return &DATA.value.key3Time;
        case 82: //partInitSpd
            return &DATA.value.partInitSpd;
        case 83: //partInitRot
            return &DATA.value.partInitRot;
        case 84: //partInitRotDelta
            return &DATA.value.partInitRotDelta;
        case 85: //partRotSpd
            return &DATA.value.partRotSpd;
        case 86: //partRotDelta
            return &DATA.value.partRotDelta;
        case 87: //addon
            return &DATA.value.addon;
        case 88: //holesSTime
            return &DATA.value.holesSTime;
        case 89: //holesETime
            return &DATA.value.holesETime;
        case 90: //holesSValue
            return &DATA.value.holesSValue;
        case 91: //holesEValue
            return &DATA.value.holesEValue;
        case 92: //edgeWidth
            return &DATA.value.edgeWidth;
        case 93: //edge.red
            return &DATA.value.edge.red;
        case 94: //edge.green
            return &DATA.value.edge.green;
        case 95: //edge.blue
            return &DATA.value.edge.blue;
        case 96: //unused7
            *FieldValues = &DATA.value.edge.unused1;
            return NULL;
        case 97: //explWindSpd
            return &DATA.value.explWindSpd;
        case 98: //textCountU
            return &DATA.value.textCountU;
        case 99: //textCountV
            return &DATA.value.textCountV;
        case 100: //addonFITime
            return &DATA.value.addonFITime;
        case 101: //addonFOTime
            return &DATA.value.addonFOTime;
        case 102: //addonScaleStart
            return &DATA.value.addonScaleStart;
        case 103: //addonScaleEnd
            return &DATA.value.addonScaleEnd;
        case 104: //addonScaleInTime
            return &DATA.value.addonScaleInTime;
        case 105: //addonScaleOutTime
            return &DATA.value.addonScaleOutTime;
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
        case 7: //fillPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //particlePath
            ICO2.Copy((char *)FieldValue);
            break;
        case 9: //holesPath
            NAM7.Copy((char *)FieldValue);
            break;
        case 10: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 11: //unused1
            if(ArraySize != 3)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 12: //memSBlend
            DATA.value.memSBlend = *(uint32_t *)FieldValue;
            break;
        case 13: //memBlendOp
            DATA.value.memBlendOp = *(uint32_t *)FieldValue;
            break;
        case 14: //memZFunc
            DATA.value.memZFunc = *(uint32_t *)FieldValue;
            break;
        case 15: //fill.red
            DATA.value.fill.red = *(uint8_t *)FieldValue;
            break;
        case 16: //fill.green
            DATA.value.fill.green = *(uint8_t *)FieldValue;
            break;
        case 17: //fill.blue
            DATA.value.fill.blue = *(uint8_t *)FieldValue;
            break;
        case 18: //unused2
            if(ArraySize != 1)
                break;
            DATA.value.fill.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 19: //fillAIn
            DATA.value.fillAIn = *(float *)FieldValue;
            break;
        case 20: //fillAFull
            DATA.value.fillAFull = *(float *)FieldValue;
            break;
        case 21: //fillAOut
            DATA.value.fillAOut = *(float *)FieldValue;
            break;
        case 22: //fillAPRatio
            DATA.value.fillAPRatio = *(float *)FieldValue;
            break;
        case 23: //fillAAmp
            DATA.value.fillAAmp = *(float *)FieldValue;
            break;
        case 24: //fillAFreq
            DATA.value.fillAFreq = *(float *)FieldValue;
            break;
        case 25: //fillAnimSpdU
            DATA.value.fillAnimSpdU = *(float *)FieldValue;
            break;
        case 26: //fillAnimSpdV
            DATA.value.fillAnimSpdV = *(float *)FieldValue;
            break;
        case 27: //edgeEffOff
            DATA.value.edgeEffOff = *(float *)FieldValue;
            break;
        case 28: //edgeEff.red
            DATA.value.edgeEff.red = *(uint8_t *)FieldValue;
            break;
        case 29: //edgeEff.green
            DATA.value.edgeEff.green = *(uint8_t *)FieldValue;
            break;
        case 30: //edgeEff.blue
            DATA.value.edgeEff.blue = *(uint8_t *)FieldValue;
            break;
        case 31: //unused3
            if(ArraySize != 1)
                break;
            DATA.value.edgeEff.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 32: //edgeEffAIn
            DATA.value.edgeEffAIn = *(float *)FieldValue;
            break;
        case 33: //edgeEffAFull
            DATA.value.edgeEffAFull = *(float *)FieldValue;
            break;
        case 34: //edgeEffAOut
            DATA.value.edgeEffAOut = *(float *)FieldValue;
            break;
        case 35: //edgeEffAPRatio
            DATA.value.edgeEffAPRatio = *(float *)FieldValue;
            break;
        case 36: //edgeEffAAmp
            DATA.value.edgeEffAAmp = *(float *)FieldValue;
            break;
        case 37: //edgeEffAFreq
            DATA.value.edgeEffAFreq = *(float *)FieldValue;
            break;
        case 38: //fillAFRatio
            DATA.value.fillAFRatio = *(float *)FieldValue;
            break;
        case 39: //edgeEffAFRatio
            DATA.value.edgeEffAFRatio = *(float *)FieldValue;
            break;
        case 40: //memDBlend
            DATA.value.memDBlend = *(uint32_t *)FieldValue;
            break;
        case 41: //partSBlend
            DATA.value.partSBlend = *(uint32_t *)FieldValue;
            break;
        case 42: //partBlendOp
            DATA.value.partBlendOp = *(uint32_t *)FieldValue;
            break;
        case 43: //partZFunc
            DATA.value.partZFunc = *(uint32_t *)FieldValue;
            break;
        case 44: //partDBlend
            DATA.value.partDBlend = *(uint32_t *)FieldValue;
            break;
        case 45: //partBUp
            DATA.value.partBUp = *(float *)FieldValue;
            break;
        case 46: //partBFull
            DATA.value.partBFull = *(float *)FieldValue;
            break;
        case 47: //partBDown
            DATA.value.partBDown = *(float *)FieldValue;
            break;
        case 48: //partBFRatio
            DATA.value.partBFRatio = *(float *)FieldValue;
            break;
        case 49: //partBPRatio
            DATA.value.partBPRatio = *(float *)FieldValue;
            break;
        case 50: //partLTime
            DATA.value.partLTime = *(float *)FieldValue;
            break;
        case 51: //partLDelta
            DATA.value.partLDelta = *(float *)FieldValue;
            break;
        case 52: //partNSpd
            DATA.value.partNSpd = *(float *)FieldValue;
            break;
        case 53: //partNAcc
            DATA.value.partNAcc = *(float *)FieldValue;
            break;
        case 54: //partVel1
            DATA.value.partVel1 = *(float *)FieldValue;
            break;
        case 55: //partVel2
            DATA.value.partVel2 = *(float *)FieldValue;
            break;
        case 56: //partVel3
            DATA.value.partVel3 = *(float *)FieldValue;
            break;
        case 57: //partAcc1
            DATA.value.partAcc1 = *(float *)FieldValue;
            break;
        case 58: //partAcc2
            DATA.value.partAcc2 = *(float *)FieldValue;
            break;
        case 59: //partAcc3
            DATA.value.partAcc3 = *(float *)FieldValue;
            break;
        case 60: //partKey1
            DATA.value.partKey1 = *(float *)FieldValue;
            break;
        case 61: //partKey2
            DATA.value.partKey2 = *(float *)FieldValue;
            break;
        case 62: //partKey1Time
            DATA.value.partKey1Time = *(float *)FieldValue;
            break;
        case 63: //partKey2Time
            DATA.value.partKey2Time = *(float *)FieldValue;
            break;
        case 64: //key1.red
            DATA.value.key1.red = *(uint8_t *)FieldValue;
            break;
        case 65: //key1.green
            DATA.value.key1.green = *(uint8_t *)FieldValue;
            break;
        case 66: //key1.blue
            DATA.value.key1.blue = *(uint8_t *)FieldValue;
            break;
        case 67: //unused4
            if(ArraySize != 1)
                break;
            DATA.value.key1.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 68: //key2.red
            DATA.value.key2.red = *(uint8_t *)FieldValue;
            break;
        case 69: //key2.green
            DATA.value.key2.green = *(uint8_t *)FieldValue;
            break;
        case 70: //key2.blue
            DATA.value.key2.blue = *(uint8_t *)FieldValue;
            break;
        case 71: //unused5
            if(ArraySize != 1)
                break;
            DATA.value.key2.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 72: //key3.red
            DATA.value.key3.red = *(uint8_t *)FieldValue;
            break;
        case 73: //key3.green
            DATA.value.key3.green = *(uint8_t *)FieldValue;
            break;
        case 74: //key3.blue
            DATA.value.key3.blue = *(uint8_t *)FieldValue;
            break;
        case 75: //unused6
            if(ArraySize != 1)
                break;
            DATA.value.key3.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 76: //key1A
            DATA.value.key1A = *(float *)FieldValue;
            break;
        case 77: //key2A
            DATA.value.key2A = *(float *)FieldValue;
            break;
        case 78: //key3A
            DATA.value.key3A = *(float *)FieldValue;
            break;
        case 79: //key1Time
            DATA.value.key1Time = *(float *)FieldValue;
            break;
        case 80: //key2Time
            DATA.value.key2Time = *(float *)FieldValue;
            break;
        case 81: //key3Time
            DATA.value.key3Time = *(float *)FieldValue;
            break;
        case 82: //partInitSpd
            DATA.value.partInitSpd = *(float *)FieldValue;
            break;
        case 83: //partInitRot
            DATA.value.partInitRot = *(float *)FieldValue;
            break;
        case 84: //partInitRotDelta
            DATA.value.partInitRotDelta = *(float *)FieldValue;
            break;
        case 85: //partRotSpd
            DATA.value.partRotSpd = *(float *)FieldValue;
            break;
        case 86: //partRotDelta
            DATA.value.partRotDelta = *(float *)FieldValue;
            break;
        case 87: //addon
            DATA.value.addon = *(FORMID *)FieldValue;
            return true;
        case 88: //holesSTime
            DATA.value.holesSTime = *(float *)FieldValue;
            break;
        case 89: //holesETime
            DATA.value.holesETime = *(float *)FieldValue;
            break;
        case 90: //holesSValue
            DATA.value.holesSValue = *(float *)FieldValue;
            break;
        case 91: //holesEValue
            DATA.value.holesEValue = *(float *)FieldValue;
            break;
        case 92: //edgeWidth
            DATA.value.edgeWidth = *(float *)FieldValue;
            break;
        case 93: //edge.red
            DATA.value.edge.red = *(uint8_t *)FieldValue;
            break;
        case 94: //edge.green
            DATA.value.edge.green = *(uint8_t *)FieldValue;
            break;
        case 95: //edge.blue
            DATA.value.edge.blue = *(uint8_t *)FieldValue;
            break;
        case 96: //unused7
            if(ArraySize != 1)
                break;
            DATA.value.edge.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 97: //explWindSpd
            DATA.value.explWindSpd = *(float *)FieldValue;
            break;
        case 98: //textCountU
            DATA.value.textCountU = *(uint32_t *)FieldValue;
            break;
        case 99: //textCountV
            DATA.value.textCountV = *(uint32_t *)FieldValue;
            break;
        case 100: //addonFITime
            DATA.value.addonFITime = *(float *)FieldValue;
            break;
        case 101: //addonFOTime
            DATA.value.addonFOTime = *(float *)FieldValue;
            break;
        case 102: //addonScaleStart
            DATA.value.addonScaleStart = *(float *)FieldValue;
            break;
        case 103: //addonScaleEnd
            DATA.value.addonScaleEnd = *(float *)FieldValue;
            break;
        case 104: //addonScaleInTime
            DATA.value.addonScaleInTime = *(float *)FieldValue;
            break;
        case 105: //addonScaleOutTime
            DATA.value.addonScaleOutTime = *(float *)FieldValue;
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
        case 7: //fillPath
            ICON.Unload();
            return;
        case 8: //particlePath
            ICO2.Unload();
            return;
        case 9: //holesPath
            NAM7.Unload();
            return;
        case 10: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 11: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            DATA.value.unused1[2] = defaultDATA.unused1[2];
            return;
        case 12: //memSBlend
            DATA.value.memSBlend = defaultDATA.memSBlend;
            return;
        case 13: //memBlendOp
            DATA.value.memBlendOp = defaultDATA.memBlendOp;
            return;
        case 14: //memZFunc
            DATA.value.memZFunc = defaultDATA.memZFunc;
            return;
        case 15: //fill.red
            DATA.value.fill.red = defaultDATA.fill.red;
            return;
        case 16: //fill.green
            DATA.value.fill.green = defaultDATA.fill.green;
            return;
        case 17: //fill.blue
            DATA.value.fill.blue = defaultDATA.fill.blue;
            return;
        case 18: //unused2
            DATA.value.fill.unused1 = defaultDATA.fill.unused1;
            return;
        case 19: //fillAIn
            DATA.value.fillAIn = defaultDATA.fillAIn;
            return;
        case 20: //fillAFull
            DATA.value.fillAFull = defaultDATA.fillAFull;
            return;
        case 21: //fillAOut
            DATA.value.fillAOut = defaultDATA.fillAOut;
            return;
        case 22: //fillAPRatio
            DATA.value.fillAPRatio = defaultDATA.fillAPRatio;
            return;
        case 23: //fillAAmp
            DATA.value.fillAAmp = defaultDATA.fillAAmp;
            return;
        case 24: //fillAFreq
            DATA.value.fillAFreq = defaultDATA.fillAFreq;
            return;
        case 25: //fillAnimSpdU
            DATA.value.fillAnimSpdU = defaultDATA.fillAnimSpdU;
            return;
        case 26: //fillAnimSpdV
            DATA.value.fillAnimSpdV = defaultDATA.fillAnimSpdV;
            return;
        case 27: //edgeEffOff
            DATA.value.edgeEffOff = defaultDATA.edgeEffOff;
            return;
        case 28: //edgeEff.red
            DATA.value.edgeEff.red = defaultDATA.edgeEff.red;
            return;
        case 29: //edgeEff.green
            DATA.value.edgeEff.green = defaultDATA.edgeEff.green;
            return;
        case 30: //edgeEff.blue
            DATA.value.edgeEff.blue = defaultDATA.edgeEff.blue;
            return;
        case 31: //unused3
            DATA.value.edgeEff.unused1 = defaultDATA.edgeEff.unused1;
            return;
        case 32: //edgeEffAIn
            DATA.value.edgeEffAIn = defaultDATA.edgeEffAIn;
            return;
        case 33: //edgeEffAFull
            DATA.value.edgeEffAFull = defaultDATA.edgeEffAFull;
            return;
        case 34: //edgeEffAOut
            DATA.value.edgeEffAOut = defaultDATA.edgeEffAOut;
            return;
        case 35: //edgeEffAPRatio
            DATA.value.edgeEffAPRatio = defaultDATA.edgeEffAPRatio;
            return;
        case 36: //edgeEffAAmp
            DATA.value.edgeEffAAmp = defaultDATA.edgeEffAAmp;
            return;
        case 37: //edgeEffAFreq
            DATA.value.edgeEffAFreq = defaultDATA.edgeEffAFreq;
            return;
        case 38: //fillAFRatio
            DATA.value.fillAFRatio = defaultDATA.fillAFRatio;
            return;
        case 39: //edgeEffAFRatio
            DATA.value.edgeEffAFRatio = defaultDATA.edgeEffAFRatio;
            return;
        case 40: //memDBlend
            DATA.value.memDBlend = defaultDATA.memDBlend;
            return;
        case 41: //partSBlend
            DATA.value.partSBlend = defaultDATA.partSBlend;
            return;
        case 42: //partBlendOp
            DATA.value.partBlendOp = defaultDATA.partBlendOp;
            return;
        case 43: //partZFunc
            DATA.value.partZFunc = defaultDATA.partZFunc;
            return;
        case 44: //partDBlend
            DATA.value.partDBlend = defaultDATA.partDBlend;
            return;
        case 45: //partBUp
            DATA.value.partBUp = defaultDATA.partBUp;
            return;
        case 46: //partBFull
            DATA.value.partBFull = defaultDATA.partBFull;
            return;
        case 47: //partBDown
            DATA.value.partBDown = defaultDATA.partBDown;
            return;
        case 48: //partBFRatio
            DATA.value.partBFRatio = defaultDATA.partBFRatio;
            return;
        case 49: //partBPRatio
            DATA.value.partBPRatio = defaultDATA.partBPRatio;
            return;
        case 50: //partLTime
            DATA.value.partLTime = defaultDATA.partLTime;
            return;
        case 51: //partLDelta
            DATA.value.partLDelta = defaultDATA.partLDelta;
            return;
        case 52: //partNSpd
            DATA.value.partNSpd = defaultDATA.partNSpd;
            return;
        case 53: //partNAcc
            DATA.value.partNAcc = defaultDATA.partNAcc;
            return;
        case 54: //partVel1
            DATA.value.partVel1 = defaultDATA.partVel1;
            return;
        case 55: //partVel2
            DATA.value.partVel2 = defaultDATA.partVel2;
            return;
        case 56: //partVel3
            DATA.value.partVel3 = defaultDATA.partVel3;
            return;
        case 57: //partAcc1
            DATA.value.partAcc1 = defaultDATA.partAcc1;
            return;
        case 58: //partAcc2
            DATA.value.partAcc2 = defaultDATA.partAcc2;
            return;
        case 59: //partAcc3
            DATA.value.partAcc3 = defaultDATA.partAcc3;
            return;
        case 60: //partKey1
            DATA.value.partKey1 = defaultDATA.partKey1;
            return;
        case 61: //partKey2
            DATA.value.partKey2 = defaultDATA.partKey2;
            return;
        case 62: //partKey1Time
            DATA.value.partKey1Time = defaultDATA.partKey1Time;
            return;
        case 63: //partKey2Time
            DATA.value.partKey2Time = defaultDATA.partKey2Time;
            return;
        case 64: //key1.red
            DATA.value.key1.red = defaultDATA.key1.red;
            return;
        case 65: //key1.green
            DATA.value.key1.green = defaultDATA.key1.green;
            return;
        case 66: //key1.blue
            DATA.value.key1.blue = defaultDATA.key1.blue;
            return;
        case 67: //unused4
            DATA.value.key1.unused1 = defaultDATA.key1.unused1;
            return;
        case 68: //key2.red
            DATA.value.key2.red = defaultDATA.key2.red;
            return;
        case 69: //key2.green
            DATA.value.key2.green = defaultDATA.key2.green;
            return;
        case 70: //key2.blue
            DATA.value.key2.blue = defaultDATA.key2.blue;
            return;
        case 71: //unused5
            DATA.value.key2.unused1 = defaultDATA.key2.unused1;
            return;
        case 72: //key3.red
            DATA.value.key3.red = defaultDATA.key3.red;
            return;
        case 73: //key3.green
            DATA.value.key3.green = defaultDATA.key3.green;
            return;
        case 74: //key3.blue
            DATA.value.key3.blue = defaultDATA.key3.blue;
            return;
        case 75: //unused6
            DATA.value.key3.unused1 = defaultDATA.key3.unused1;
            return;
        case 76: //key1A
            DATA.value.key1A = defaultDATA.key1A;
            return;
        case 77: //key2A
            DATA.value.key2A = defaultDATA.key2A;
            return;
        case 78: //key3A
            DATA.value.key3A = defaultDATA.key3A;
            return;
        case 79: //key1Time
            DATA.value.key1Time = defaultDATA.key1Time;
            return;
        case 80: //key2Time
            DATA.value.key2Time = defaultDATA.key2Time;
            return;
        case 81: //key3Time
            DATA.value.key3Time = defaultDATA.key3Time;
            return;
        case 82: //partInitSpd
            DATA.value.partInitSpd = defaultDATA.partInitSpd;
            return;
        case 83: //partInitRot
            DATA.value.partInitRot = defaultDATA.partInitRot;
            return;
        case 84: //partInitRotDelta
            DATA.value.partInitRotDelta = defaultDATA.partInitRotDelta;
            return;
        case 85: //partRotSpd
            DATA.value.partRotSpd = defaultDATA.partRotSpd;
            return;
        case 86: //partRotDelta
            DATA.value.partRotDelta = defaultDATA.partRotDelta;
            return;
        case 87: //addon
            DATA.value.addon = defaultDATA.addon;
            return;
        case 88: //holesSTime
            DATA.value.holesSTime = defaultDATA.holesSTime;
            return;
        case 89: //holesETime
            DATA.value.holesETime = defaultDATA.holesETime;
            return;
        case 90: //holesSValue
            DATA.value.holesSValue = defaultDATA.holesSValue;
            return;
        case 91: //holesEValue
            DATA.value.holesEValue = defaultDATA.holesEValue;
            return;
        case 92: //edgeWidth
            DATA.value.edgeWidth = defaultDATA.edgeWidth;
            return;
        case 93: //edge.red
            DATA.value.edge.red = defaultDATA.edge.red;
            return;
        case 94: //edge.green
            DATA.value.edge.green = defaultDATA.edge.green;
            return;
        case 95: //edge.blue
            DATA.value.edge.blue = defaultDATA.edge.blue;
            return;
        case 96: //unused7
            DATA.value.edge.unused1 = defaultDATA.edge.unused1;
            return;
        case 97: //explWindSpd
            DATA.value.explWindSpd = defaultDATA.explWindSpd;
            return;
        case 98: //textCountU
            DATA.value.textCountU = defaultDATA.textCountU;
            return;
        case 99: //textCountV
            DATA.value.textCountV = defaultDATA.textCountV;
            return;
        case 100: //addonFITime
            DATA.value.addonFITime = defaultDATA.addonFITime;
            return;
        case 101: //addonFOTime
            DATA.value.addonFOTime = defaultDATA.addonFOTime;
            return;
        case 102: //addonScaleStart
            DATA.value.addonScaleStart = defaultDATA.addonScaleStart;
            return;
        case 103: //addonScaleEnd
            DATA.value.addonScaleEnd = defaultDATA.addonScaleEnd;
            return;
        case 104: //addonScaleInTime
            DATA.value.addonScaleInTime = defaultDATA.addonScaleInTime;
            return;
        case 105: //addonScaleOutTime
            DATA.value.addonScaleOutTime = defaultDATA.addonScaleOutTime;
            return;
        default:
            return;
        }
    }
}