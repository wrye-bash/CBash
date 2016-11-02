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
#include "..\RGDLRecord.h"

namespace FNV
{
uint32_t RGDLRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //nver Version
            return CB_UINT32_FIELD;
        case 8: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 9: //data_p DATA ,, Struct
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
        case 10: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 11: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 12: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 13: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 14: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 15: //data_p DATA ,, Struct
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
        case 16: //xnam Actor Base
            return CB_FORMID_FIELD;
        case 17: //tnam Body Part Data
            return CB_FORMID_FIELD;
        case 18: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 19: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 20: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 21: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 22: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 23: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 24: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 25: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 26: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 27: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 28: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 29: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 30: //rafd RAFD ,, Struct
            return CB_FLOAT32_FIELD;
        case 31: //rafd RAFD ,, Struct
            return CB_SINT32_FIELD;
        case 32: //rafd RAFD ,, Struct
            return CB_SINT32_FIELD;
        case 33: //rafb Feedback Dynamic Bones
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD
        case 34: //raps RAPS ,, Struct
            return CB_UINT16_FIELD;
        case 35: //raps RAPS ,, Struct
            return CB_UINT8_FIELD;
        case 36: //raps_p RAPS ,, Struct
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
        case 37: //raps RAPS ,, Struct
            return CB_FLOAT32_FIELD;
        case 38: //raps RAPS ,, Struct
            return CB_FLOAT32_FIELD;
        case 39: //raps RAPS ,, Struct
            return CB_FLOAT32_FIELD;
        case 40: //raps RAPS ,, Struct
            return CB_FLOAT32_FIELD;
        case 41: //anam Death Pose
            return CB_ISTRING_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * RGDLRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //nver Version
            return NVER.IsLoaded() ? &NVER.value : NULL;
        case 8: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->numBones : NULL;
        case 9: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->unused1[0] : NULL;
            return NULL;
        case 10: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->feedbackType : NULL;
        case 11: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->footIKType : NULL;
        case 12: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->lookIKType : NULL;
        case 13: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->grabIKType : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->matchPoseType : NULL;
        case 15: //data_p DATA ,, Struct
            *FieldValues = DATA.IsLoaded() ? &DATA->unused2 : NULL;
            return NULL;
        case 16: //xnam Actor Base
            return XNAM.IsLoaded() ? &XNAM.value : NULL;
        case 17: //tnam Body Part Data
            return TNAM.IsLoaded() ? &TNAM.value : NULL;
        case 18: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->blendAmt : NULL;
        case 19: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->hierachyGain : NULL;
        case 20: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->posGain : NULL;
        case 21: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->velGain : NULL;
        case 22: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->accGain : NULL;
        case 23: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->snapGain : NULL;
        case 24: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->velDamping : NULL;
        case 25: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->snapLinVel : NULL;
        case 26: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->snapAngVel : NULL;
        case 27: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->snapLinDist : NULL;
        case 28: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->snapAngDist : NULL;
        case 29: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->posLinVel : NULL;
        case 30: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->posAngVel : NULL;
        case 31: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->posProjectileVel : NULL;
        case 32: //rafd RAFD ,, Struct
            return RAFD.IsLoaded() ? &RAFD->posMeleeVel : NULL;
        case 33: //rafb Feedback Dynamic Bones
            return NULL; // Unparsed
        case 34: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->matchBones1 : NULL;
        case 35: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->flags : NULL;
        case 36: //raps_p RAPS ,, Struct
            *FieldValues = RAPS.IsLoaded() ? &RAPS->unused : NULL;
            return NULL;
        case 37: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->motorsStrength : NULL;
        case 38: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->poseDelay : NULL;
        case 39: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->errorAllowance : NULL;
        case 40: //raps RAPS ,, Struct
            return RAPS.IsLoaded() ? &RAPS->disableDisplacement : NULL;
        case 41: //anam Death Pose
            return ANAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool RGDLRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //nver Version
            NVER.Load();
            NVER.value = *(uint32_t *)FieldValue;
            break;
        case 8: //data DATA ,, Struct
            DATA.Load();
            DATA->numBones = *(uint32_t *)FieldValue;
            break;
        case 9: //data_p DATA ,, Struct
            if(ArraySize != 4)
                break;
            DATA.Load();
            DATA->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            DATA->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            DATA->unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 10: //data DATA ,, Struct
            DATA.Load();
            DATA->feedbackType = *(uint8_t *)FieldValue;
            break;
        case 11: //data DATA ,, Struct
            DATA.Load();
            DATA->footIKType = *(uint8_t *)FieldValue;
            break;
        case 12: //data DATA ,, Struct
            DATA.Load();
            DATA->lookIKType = *(uint8_t *)FieldValue;
            break;
        case 13: //data DATA ,, Struct
            DATA.Load();
            DATA->grabIKType = *(uint8_t *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->matchPoseType = *(uint8_t *)FieldValue;
            break;
        case 15: //data_p DATA ,, Struct
            if(ArraySize != 1)
                break;
            DATA.Load();
            DATA->unused2 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 16: //xnam Actor Base
            XNAM.Load();
            XNAM.value = *(FORMID *)FieldValue;
            return true;
        case 17: //tnam Body Part Data
            TNAM.Load();
            TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 18: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->blendAmt = *(float *)FieldValue;
            break;
        case 19: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->hierachyGain = *(float *)FieldValue;
            break;
        case 20: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->posGain = *(float *)FieldValue;
            break;
        case 21: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->velGain = *(float *)FieldValue;
            break;
        case 22: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->accGain = *(float *)FieldValue;
            break;
        case 23: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->snapGain = *(float *)FieldValue;
            break;
        case 24: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->velDamping = *(float *)FieldValue;
            break;
        case 25: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->snapLinVel = *(float *)FieldValue;
            break;
        case 26: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->snapAngVel = *(float *)FieldValue;
            break;
        case 27: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->snapLinDist = *(float *)FieldValue;
            break;
        case 28: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->snapAngDist = *(float *)FieldValue;
            break;
        case 29: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->posLinVel = *(float *)FieldValue;
            break;
        case 30: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->posAngVel = *(float *)FieldValue;
            break;
        case 31: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->posProjectileVel = *(int32_t *)FieldValue;
            break;
        case 32: //rafd RAFD ,, Struct
            RAFD.Load();
            RAFD->posMeleeVel = *(int32_t *)FieldValue;
            break;
        case 33: //rafb Feedback Dynamic Bones
            break; //unparsed
        case 34: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->matchBones1 = *(uint16_t *)FieldValue;
            break;
        case 35: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->flags = *(uint8_t *)FieldValue;
            break;
        case 36: //raps_p RAPS ,, Struct
            if(ArraySize != 1)
                break;
            RAPS.Load();
            RAPS->unused = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 37: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->motorsStrength = *(float *)FieldValue;
            break;
        case 38: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->poseDelay = *(float *)FieldValue;
            break;
        case 39: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->errorAllowance = *(float *)FieldValue;
            break;
        case 40: //raps RAPS ,, Struct
            RAPS.Load();
            RAPS->disableDisplacement = *(float *)FieldValue;
            break;
        case 41: //anam Death Pose
            ANAM.Copy((char *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void RGDLRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //nver Version
            NVER.Unload();
            return;
        case 8: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 9: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 10: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 11: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 12: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 13: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data_p DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //xnam Actor Base
            XNAM.Unload();
            return;
        case 17: //tnam Body Part Data
            TNAM.Unload();
            return;
        case 18: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 19: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 20: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 21: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 22: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 23: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 24: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 25: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 26: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 27: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 28: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 29: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 30: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 31: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 32: //rafd RAFD ,, Struct
            RAFD.Unload();
            return;
        case 33: //rafb Feedback Dynamic Bones
            return; // unparsed
        case 34: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 35: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 36: //raps_p RAPS ,, Struct
            RAPS.Unload();
            return;
        case 37: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 38: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 39: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 40: //raps RAPS ,, Struct
            RAPS.Unload();
            return;
        case 41: //anam Death Pose
            ANAM.Unload();
            return;
        default:
            return;
        }
    }
}