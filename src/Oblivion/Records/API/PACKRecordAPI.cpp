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
#include "..\PACKRecord.h"

namespace Ob
{
uint32_t PACKRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    Function_Arguments_Iterator curCTDAFunction;

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
        case 5: //flags
            return CB_UINT32_FLAG_FIELD;
        case 6: //aiType
            return CB_UINT8_TYPE_FIELD;
        case 7: //unused1
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
        case 8: //locType
            return CB_SINT32_TYPE_FIELD;
        case 9: //locId
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return (PLDT.IsLoaded() && (PLDT->locType < 2 || PLDT->locType == 4)) ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //locRadius
            return CB_SINT32_FIELD;
        case 11: //month
            return CB_SINT8_FIELD;
        case 12: //day
            return CB_SINT8_FIELD;
        case 13: //date
            return CB_UINT8_FIELD;
        case 14: //time
            return CB_SINT8_FIELD;
        case 15: //duration
            return CB_SINT32_FIELD;
        case 16: //targetType
            return CB_SINT32_TYPE_FIELD;
        case 17: //targetId
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return (PTDT.IsLoaded() && PTDT->targetType != 2) ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //targetCount
            return CB_SINT32_FIELD;
        case 19: //conditions
            if(ListFieldID == 0) //conditions
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)CTDA.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= CTDA.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //operType
                    return CB_UINT8_FLAG_TYPE_FIELD;
                case 2: //unused1
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
                case 3: //compValue
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_FLOAT32_FIELD;
                        case 2: //WhichType
                            return CTDA.value[ListIndex]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                case 4: //ifunc
                    return CB_UINT32_TYPE_FIELD;
                case 5: //param1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            {
                            Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(CTDA.value[ListIndex]->ifunc);
                            if(curCTDAFunction != Function_Arguments.end())
                                {
                                const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                switch(CTDAFunction.first)
                                    {
                                    case eFORMID:
                                        return CB_FORMID_FIELD;
                                    case eUINT32:
                                        return CB_UINT32_FIELD;
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                }
                            }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 6: //param2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            {
                            Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(CTDA.value[ListIndex]->ifunc);
                            if(curCTDAFunction != Function_Arguments.end())
                                {
                                const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                switch(CTDAFunction.second)
                                    {
                                    case eFORMID:
                                        return CB_FORMID_FIELD;
                                    case eUINT32:
                                        return CB_UINT32_FIELD;
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                }
                            }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 7: //unused2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 4;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * PACKRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //flags
            return &PKDT.value.flags;
        case 6: //aiType
            return &PKDT.value.aiType;
        case 7: //unused1
            *FieldValues = &PKDT.value.unused1[0];
            return NULL;
        case 8: //locType
            return PLDT.IsLoaded() ? &PLDT->locType : NULL;
        case 9: //locId
            return PLDT.IsLoaded() ? &PLDT->locId : NULL;
        case 10: //locRadius
            return PLDT.IsLoaded() ? &PLDT->locRadius : NULL;
        case 11: //month
            return &PSDT.value.month;
        case 12: //day
            return &PSDT.value.day;
        case 13: //date
            return &PSDT.value.date;
        case 14: //time
            return &PSDT.value.time;
        case 15: //duration
            return &PSDT.value.duration;
        case 16: //targetType
            return PTDT.IsLoaded() ? &PTDT->targetType : NULL;
        case 17: //targetId
            return PTDT.IsLoaded() ? &PTDT->targetId : NULL;
        case 18: //targetCount
            return PTDT.IsLoaded() ? &PTDT->targetCount : NULL;
        case 19: //conditions
            if(ListIndex >= CTDA.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //operType
                    return &CTDA.value[ListIndex]->operType;
                case 2: //unused1
                    *FieldValues = &CTDA.value[ListIndex]->unused1[0];
                    return NULL;
                case 3: //compValue
                    return &CTDA.value[ListIndex]->compValue;
                case 4: //ifunc
                    return &CTDA.value[ListIndex]->ifunc;
                case 5: //param1
                    return &CTDA.value[ListIndex]->param1;
                case 6: //param2
                    return &CTDA.value[ListIndex]->param2;
                case 7: //unused2
                    *FieldValues = &CTDA.value[ListIndex]->unused2[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool PACKRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 6: //aiType
            SetAIType(*(uint8_t *)FieldValue);
            break;
        case 7: //unused1
            if(ArraySize != 3)
                break;
            PKDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            PKDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            PKDT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 8: //locType
            SetLocType(*(int32_t *)FieldValue);
            return true;
        case 9: //locId
            PLDT.Load();
            PLDT->locId = *(FORMID_OR_UINT32 *)FieldValue;
            return true;
        case 10: //locRadius
            PLDT.Load();
            PLDT->locRadius = *(int32_t *)FieldValue;
            break;
        case 11: //month
            PSDT.value.month = *(int8_t *)FieldValue;
            break;
        case 12: //day
            PSDT.value.day = *(int8_t *)FieldValue;
            break;
        case 13: //date
            PSDT.value.date = *(uint8_t *)FieldValue;
            break;
        case 14: //time
            PSDT.value.time = *(int8_t *)FieldValue;
            break;
        case 15: //duration
            PSDT.value.duration = *(int32_t *)FieldValue;
            break;
        case 16: //targetType
            SetTargetType(*(int32_t *)FieldValue);
            return true;
        case 17: //targetId
            PTDT.Load();
            PTDT->targetId = *(uint32_t *)FieldValue;
            return true;
        case 18: //targetCount
            PTDT.Load();
            PTDT->targetCount = *(int32_t *)FieldValue;
            break;
        case 19: //conditions
            if(ListFieldID == 0) //conditionsSize
                {
                CTDA.resize(ArraySize);
                return false;
                }

            if(ListIndex >= CTDA.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //operType
                    CTDA.value[ListIndex]->operType = *(uint8_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 3)
                        break;
                    CTDA.value[ListIndex]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    CTDA.value[ListIndex]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    CTDA.value[ListIndex]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 3: //compValue
                    CTDA.value[ListIndex]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                    return true;
                case 4: //ifunc
                    CTDA.value[ListIndex]->ifunc = *(uint32_t *)FieldValue;
                    return true;
                case 5: //param1
                    CTDA.value[ListIndex]->param1 = *(uint32_t *)FieldValue;
                    return true;
                case 6: //param2
                    CTDA.value[ListIndex]->param2 = *(uint32_t *)FieldValue;
                    return true;
                case 7: //unused2
                    if(ArraySize != 4)
                        break;
                    CTDA.value[ListIndex]->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    CTDA.value[ListIndex]->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    CTDA.value[ListIndex]->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    CTDA.value[ListIndex]->unused2[3] = ((UINT8ARRAY)FieldValue)[3];
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

void PACKRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    PACKPKDT defaultPKDT;
    PACKPLDT defaultPLDT;
    PACKPSDT defaultPSDT;
    PACKPTDT defaultPTDT;

    GENCTDA defaultCTDA;

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
        case 5: //flags
            SetFlagMask(defaultPKDT.flags);
            return;
        case 6: //aiType
            SetAIType(defaultPKDT.aiType);
            return;
        case 7: //unused1
            PKDT.value.unused1[0] = defaultPKDT.unused1[0];
            PKDT.value.unused1[1] = defaultPKDT.unused1[1];
            PKDT.value.unused1[2] = defaultPKDT.unused1[2];
            return;
        case 8: //locType
            if(PLDT.IsLoaded())
                SetLocType(defaultPLDT.locType);
            return;
        case 9: //locId
            if(PLDT.IsLoaded())
                PLDT->locId = defaultPLDT.locId;
            return;
        case 10: //locRadius
            if(PLDT.IsLoaded())
                PLDT->locRadius = defaultPLDT.locRadius;
            return;
        case 11: //month
            PSDT.value.month = defaultPSDT.month;
            return;
        case 12: //day
            PSDT.value.day = defaultPSDT.day;
            return;
        case 13: //date
            PSDT.value.date = defaultPSDT.date;
            return;
        case 14: //time
            PSDT.value.time = defaultPSDT.time;
            return;
        case 15: //duration
            PSDT.value.duration = defaultPSDT.duration;
            return;
        case 16: //targetType
            if(PTDT.IsLoaded())
                SetTargetType(defaultPTDT.targetType);
            return;
        case 17: //targetId
            if(PTDT.IsLoaded())
                PTDT->targetId = defaultPTDT.targetId;
            return;
        case 18: //targetCount
            if(PTDT.IsLoaded())
                PTDT->targetCount = defaultPTDT.targetCount;
            return;
        case 19: //conditions
            if(ListFieldID == 0) //conditions
                {
                CTDA.Unload();
                return;
                }

            if(ListIndex >= CTDA.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //operType
                    CTDA.value[ListIndex]->operType = defaultCTDA.operType;
                    return;
                case 2: //unused1
                    CTDA.value[ListIndex]->unused1[0] = defaultCTDA.unused1[0];
                    CTDA.value[ListIndex]->unused1[1] = defaultCTDA.unused1[1];
                    CTDA.value[ListIndex]->unused1[2] = defaultCTDA.unused1[2];
                    return;
                case 3: //compValue
                    CTDA.value[ListIndex]->compValue = defaultCTDA.compValue;
                    return;
                case 4: //ifunc
                    CTDA.value[ListIndex]->ifunc = defaultCTDA.ifunc;
                    return;
                case 5: //param1
                    CTDA.value[ListIndex]->param1 = defaultCTDA.param1;
                    return;
                case 6: //param2
                    CTDA.value[ListIndex]->param2 = defaultCTDA.param2;
                    return;
                case 7: //unused2
                    CTDA.value[ListIndex]->unused2[0] = defaultCTDA.unused2[0];
                    CTDA.value[ListIndex]->unused2[1] = defaultCTDA.unused2[1];
                    CTDA.value[ListIndex]->unused2[2] = defaultCTDA.unused2[2];
                    CTDA.value[ListIndex]->unused2[3] = defaultCTDA.unused2[3];
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    return;
    }
}