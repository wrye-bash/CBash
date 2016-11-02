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
#include "..\SPELRecord.h"

namespace FNV
{
uint32_t SPELRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //spellType
            return CB_UINT32_TYPE_FIELD;
        case 9: //costUnused
            return CB_UINT32_FIELD;
        case 10: //levelTypeUnused
            return CB_UINT32_TYPE_FIELD;
        case 11: //flags
            return CB_UINT8_FLAG_FIELD;
        case 12: //unused1
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
        case 13: //effects
            if(ListFieldID == 0) //effects
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Effects.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Effects.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //effect
                    return CB_FORMID_FIELD;
                case 2: //magnitude
                    return CB_UINT32_FIELD;
                case 3: //area
                    return CB_UINT32_FIELD;
                case 4: //duration
                    return CB_UINT32_FIELD;
                case 5: //rangeType
                    return CB_UINT32_FIELD;
                case 6: //actorValue
                    return CB_SINT32_FIELD;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditions
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Effects.value[ListIndex]->CTDA.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
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
                        case 3: //compValue
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_FORMID_OR_FLOAT32_FIELD;
                                case 2: //WhichType
                                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 4: //ifunc
                            return CB_UINT32_TYPE_FIELD;
                        case 5: //param1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    {
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
                                    if(curCTDAFunction != FNVFunction_Arguments.end())
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
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
                                    if(curCTDAFunction != FNVFunction_Arguments.end())
                                        {
                                        const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                        switch(CTDAFunction.second)
                                            {
                                            case eFORMID:
                                                return CB_FORMID_FIELD;
                                            case eUINT32:
                                                return CB_UINT32_FIELD;
                                            case eVATSPARAM:
                                                if(Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 < VATSFUNCTIONSIZE)
                                                    {
                                                    switch(VATSFunction_Argument[Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1])
                                                        {
                                                        case eFORMID:
                                                            return CB_FORMID_FIELD;
                                                        case eUINT32:
                                                            return CB_UINT32_FIELD;
                                                        default:
                                                            return CB_UNKNOWN_FIELD;
                                                        }

                                                    }
                                            default:
                                                return CB_UNKNOWN_FIELD;
                                            }
                                        }
                                    }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 7: //runOnType
                            return CB_UINT32_TYPE_FIELD;
                        case 8: //reference
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                case 2: //WhichType
                                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * SPELRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //spellType
            return &SPIT.value.spellType;
        case 9: //costUnused
            return &SPIT.value.cost;
        case 10: //levelTypeUnused
            return &SPIT.value.levelType;
        case 11: //flags
            return &SPIT.value.flags;
        case 12: //unused1
            *FieldValues = &SPIT.value.unused1[0];
            return NULL;
        case 13: //effects
            if(ListIndex >= Effects.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //effect
                    return &Effects.value[ListIndex]->EFID.value;
                case 2: //magnitude
                    return &Effects.value[ListIndex]->EFIT.value.magnitude;
                case 3: //area
                    return &Effects.value[ListIndex]->EFIT.value.area;
                case 4: //duration
                    return &Effects.value[ListIndex]->EFIT.value.duration;
                case 5: //rangeType
                    return &Effects.value[ListIndex]->EFIT.value.rangeType;
                case 6: //actorValue
                    return &Effects.value[ListIndex]->EFIT.value.actorValue;
                case 7: //conditions
                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType;
                        case 2: //unused1
                            *FieldValues = &Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0];
                            return NULL;
                        case 3: //compValue
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue;
                        case 4: //ifunc
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc;
                        case 5: //param1
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1;
                        case 6: //param2
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2;
                        case 7: //runOnType
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType;
                        case 8: //reference
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference;
                        default:
                            return NULL;
                        }
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

bool SPELRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //spellType
            SetType(*(uint32_t *)FieldValue);
            break;
        case 9: //costUnused
            SPIT.value.cost = *(uint32_t *)FieldValue;
            break;
        case 10: //levelTypeUnused
            SPIT.value.levelType = *(uint32_t *)FieldValue;
            break;
        case 11: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 12: //unused1
            if(ArraySize != 3)
                break;
            SPIT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            SPIT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            SPIT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 13: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Effects.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //effect
                    Effects.value[ListIndex]->EFID.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = *(uint32_t *)FieldValue;
                    break;
                case 3: //area
                    Effects.value[ListIndex]->EFIT.value.area = *(uint32_t *)FieldValue;
                    break;
                case 4: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = *(uint32_t *)FieldValue;
                    break;
                case 5: //rangeType
                    Effects.value[ListIndex]->SetRange(*(uint32_t *)FieldValue);
                    break;
                case 6: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = *(int32_t *)FieldValue;
                    break;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Effects.value[ListIndex]->CTDA.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType = *(uint8_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 3)
                                break;
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            break;
                        case 3: //compValue
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                            return true;
                        case 4: //ifunc
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = *(uint32_t *)FieldValue;
                            return true;
                        case 5: //param1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 6: //param2
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 7: //runOnType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = *(uint32_t *)FieldValue;
                            return true;
                        case 8: //reference
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        default:
                            break;
                        }
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

void SPELRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    SPELSPIT defaultSPIT;
    FNVCTDA defaultCTDA;
    FNVEffect defaultEffect;
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
        case 8: //spellType
            SetType(defaultSPIT.spellType);
            return;
        case 9: //costUnused
            SPIT.value.cost = defaultSPIT.cost;
            return;
        case 10: //levelTypeUnused
            SPIT.value.levelType = defaultSPIT.levelType;
            return;
        case 11: //flags
            SetFlagMask(defaultSPIT.flags);
            return;
        case 12: //unused1
            SPIT.value.unused1[0] = defaultSPIT.unused1[0];
            SPIT.value.unused1[1] = defaultSPIT.unused1[1];
            SPIT.value.unused1[2] = defaultSPIT.unused1[2];
            return;
        case 13: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.Unload();
                return;
                }

            if(ListIndex >= Effects.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //effect
                    Effects.value[ListIndex]->EFID.value = defaultEffect.EFID.value;
                    return;
                case 2: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = defaultEffect.EFIT.value.magnitude;
                    return;
                case 3: //area
                    Effects.value[ListIndex]->EFIT.value.area = defaultEffect.EFIT.value.area;
                    return;
                case 4: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = defaultEffect.EFIT.value.duration;
                    return;
                case 5: //rangeType
                    Effects.value[ListIndex]->SetRange(defaultEffect.EFIT.value.rangeType);
                    return;
                case 6: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = defaultEffect.EFIT.value.actorValue;
                    return;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Effects.value[ListIndex]->CTDA.Unload();
                        return;
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType = defaultCTDA.operType;
                            return;
                        case 2: //unused1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = defaultCTDA.unused1[0];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = defaultCTDA.unused1[1];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = defaultCTDA.unused1[2];
                            return;
                        case 3: //compValue
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue = defaultCTDA.compValue;
                            return;
                        case 4: //ifunc
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = defaultCTDA.ifunc;
                            return;
                        case 5: //param1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 = defaultCTDA.param1;
                            return;
                        case 6: //param2
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2 = defaultCTDA.param2;
                            return;
                        case 7: //runOnType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = defaultCTDA.runOnType;
                            return;
                        case 8: //reference
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference = defaultCTDA.reference;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        default:
            return;
        }
    }
}