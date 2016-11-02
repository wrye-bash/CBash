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
#include "..\QUSTRecord.h"

namespace FNV
{
uint32_t QUSTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //script
            return CB_FORMID_FIELD;
        case 8: //full
            return CB_STRING_FIELD;
        case 9: //iconPath
            return CB_ISTRING_FIELD;
        case 10: //smallIconPath
            return CB_ISTRING_FIELD;
        case 11: //flags
            return CB_UINT8_FLAG_FIELD;
        case 12: //priority
            return CB_UINT8_FIELD;
        case 13: //unused1
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
        case 14: //delay
            return CB_FLOAT32_FIELD;
        case 15: //conditions
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
                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(CTDA.value[ListIndex]->ifunc);
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
                    return CB_UNKNOWN_FIELD;
                case 6: //param2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            {
                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(CTDA.value[ListIndex]->ifunc);
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
                                        if(CTDA.value[ListIndex]->param1 < VATSFUNCTIONSIZE)
                                            {
                                            switch(VATSFunction_Argument[CTDA.value[ListIndex]->param1])
                                                {
                                                case eFORMID:
                                                    return CB_FORMID_FIELD;
                                                case eUINT32:
                                                    return CB_UINT32_FIELD;
                                                default:
                                                    return CB_UNKNOWN_FIELD;
                                                }

                                            }
                                        return CB_UNKNOWN_FIELD;
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                }
                            }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                case 7: //runOnType
                    return CB_UINT32_TYPE_FIELD;
                case 8: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return CTDA.value[ListIndex]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 16: //stages
            if(ListFieldID == 0) //stages
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Stages.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Stages.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //stage
                    return CB_SINT16_FIELD;
                case 2: //entries
                    if(ListX2FieldID == 0) //entries
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Stages.value[ListIndex]->Entries.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListIndex >= Stages.value[ListIndex]->Entries.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //flags
                            return CB_UINT8_FLAG_FIELD;
                        case 2: //conditions
                            if(ListX3FieldID == 0) //conditions
                                {
                                switch(WhichAttribute)
                                    {
                                    case 0: //fieldType
                                        return CB_LIST_FIELD;
                                    case 1: //fieldSize
                                        return (uint32_t)Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size();
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                return CB_UNKNOWN_FIELD;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
                                return CB_UNKNOWN_FIELD;

                            switch(ListX3FieldID)
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
                                            return Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
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
                                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                                    return CB_UNKNOWN_FIELD;
                                case 6: //param2
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                        case 2: //WhichType
                                            {
                                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                                                        if(Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param1 < VATSFUNCTIONSIZE)
                                                            {
                                                            switch(VATSFunction_Argument[Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param1])
                                                                {
                                                                case eFORMID:
                                                                    return CB_FORMID_FIELD;
                                                                case eUINT32:
                                                                    return CB_UINT32_FIELD;
                                                                default:
                                                                    return CB_UNKNOWN_FIELD;
                                                                }

                                                            }
                                                        return CB_UNKNOWN_FIELD;
                                                    default:
                                                        return CB_UNKNOWN_FIELD;
                                                    }
                                                }
                                            }
                                            return CB_UNKNOWN_FIELD;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                    return CB_UNKNOWN_FIELD;
                                case 7: //runOnType
                                    return CB_UINT32_TYPE_FIELD;
                                case 8: //reference
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                        case 2: //WhichType
                                            return Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 3: //text
                            return CB_STRING_FIELD;
                        case 4: //unused1
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
                        case 5: //numRefs
                            return CB_UINT32_FIELD;
                        case 6: //compiledSize
                            return CB_UINT32_FIELD;
                        case 7: //lastIndex
                            return CB_UINT32_FIELD;
                        case 8: //scriptType
                            return CB_UINT16_FIELD;
                        case 9: //scriptFlags
                            return CB_UINT16_FLAG_FIELD;
                        case 10: //compiled_p
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.GetSize();
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 11: //scriptText
                            return CB_ISTRING_FIELD;
                        case 12: //vars
                            if(ListX3FieldID == 0) //vars
                                {
                                switch(WhichAttribute)
                                    {
                                    case 0: //fieldType
                                        return CB_LIST_FIELD;
                                    case 1: //fieldSize
                                        return (uint32_t)Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value.size();
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value.size())
                                return CB_UNKNOWN_FIELD;

                            switch(ListX3FieldID)
                                {
                                case 1: //index
                                    return CB_UINT32_FIELD;
                                case 2: //unused1
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UINT8_ARRAY_FIELD;
                                        case 1: //fieldSize
                                            return 12;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                case 3: //flags
                                    return CB_UINT8_FLAG_FIELD;
                                case 4: //unused2
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UINT8_ARRAY_FIELD;
                                        case 1: //fieldSize
                                            return 7;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                case 5: //name
                                    return CB_ISTRING_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 13: //references
                            if(ListX3FieldID == 0) //references
                                {
                                switch(WhichAttribute)
                                    {
                                    case 0: //fieldType
                                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                                    case 1: //fieldSize
                                        return (uint32_t)Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size();
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                return CB_UNKNOWN_FIELD;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size())
                                return CB_UNKNOWN_FIELD;

                            switch(ListX3FieldID)
                                {
                                case 1: //reference
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_FORMID_OR_UINT32_FIELD;
                                        case 2: //WhichType
                                            return (Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        case 14: //nextQuest
                            return CB_FORMID_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //objectives
            if(ListFieldID == 0) //objectives
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Objectives.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Objectives.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //objective
                    return CB_SINT32_FIELD;
                case 2: //text
                    return CB_STRING_FIELD;
                case 3: //targets
                    if(ListX2FieldID == 0) //targets
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Objectives.value[ListIndex]->Targets.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= Objectives.value[ListIndex]->Targets.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //targetId
                            return CB_FORMID_FIELD;
                        case 2: //flags
                            return CB_UINT8_FLAG_FIELD;
                        case 3: //unused1
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
                        case 4: //conditions
                            if(ListX3FieldID == 0) //conditions
                                {
                                switch(WhichAttribute)
                                    {
                                    case 0: //fieldType
                                        return CB_LIST_FIELD;
                                    case 1: //fieldSize
                                        return (uint32_t)Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value.size();
                                    default:
                                        return CB_UNKNOWN_FIELD;
                                    }
                                return CB_UNKNOWN_FIELD;
                                }

                            if(ListX3Index >= Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value.size())
                                return CB_UNKNOWN_FIELD;

                            switch(ListX3FieldID)
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
                                            return Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
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
                                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                                    return CB_UNKNOWN_FIELD;
                                case 6: //param2
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                        case 2: //WhichType
                                            {
                                            Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                                                        if(Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param1 < VATSFUNCTIONSIZE)
                                                            {
                                                            switch(VATSFunction_Argument[Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param1])
                                                                {
                                                                case eFORMID:
                                                                    return CB_FORMID_FIELD;
                                                                case eUINT32:
                                                                    return CB_UINT32_FIELD;
                                                                default:
                                                                    return CB_UNKNOWN_FIELD;
                                                                }

                                                            }
                                                        return CB_UNKNOWN_FIELD;
                                                    default:
                                                        return CB_UNKNOWN_FIELD;
                                                    }
                                                }
                                            }
                                            return CB_UNKNOWN_FIELD;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                    return CB_UNKNOWN_FIELD;
                                case 7: //runOnType
                                    return CB_UINT32_TYPE_FIELD;
                                case 8: //reference
                                    switch(WhichAttribute)
                                        {
                                        case 0: //fieldType
                                            return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                                        case 2: //WhichType
                                            return Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                                        default:
                                            return CB_UNKNOWN_FIELD;
                                        }
                                    return CB_UNKNOWN_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * QUSTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //script
            return &SCRI.value;
        case 8: //full
            return FULL.value;
        case 9: //iconPath
            return ICON.value;
        case 10: //smallIconPath
            return MICO.value;
        case 11: //flags
            return &DATA.value.flags;
        case 12: //priority
            return &DATA.value.priority;
        case 13: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 14: //delay
            return &DATA.value.delay;
        case 15: //conditions
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
                case 7: //runOnType
                    return &CTDA.value[ListIndex]->runOnType;
                case 8: //reference
                    return &CTDA.value[ListIndex]->reference;
                default:
                    return NULL;
                }
            return NULL;
        case 16: //stages
            if(ListIndex >= Stages.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //stage
                    return &Stages.value[ListIndex]->INDX.value;
                case 2: //entries
                    if(ListX2Index >= Stages.value[ListIndex]->Entries.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //flags
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->QSDT.value;
                        case 2: //conditions
                            if(ListX2Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
                                return NULL;

                            switch(ListFieldID)
                                {
                                case 1: //operType
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->operType;
                                case 2: //unused1
                                    *FieldValues = &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0];
                                    return NULL;
                                case 3: //compValue
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->compValue;
                                case 4: //ifunc
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc;
                                case 5: //param1
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param1;
                                case 6: //param2
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param2;
                                case 7: //runOnType
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType;
                                case 8: //reference
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->reference;
                                default:
                                    return NULL;
                                }
                            return NULL;
                        case 3: //text
                            return Stages.value[ListIndex]->Entries.value[ListX2Index]->CNAM.value;
                        case 4: //unused1
                            *FieldValues = &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[0];
                            return NULL;
                        case 5: //numRefs
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.numRefs;
                        case 6: //compiledSize
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.compiledSize;
                        case 7: //lastIndex
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.lastIndex;
                        case 8: //scriptType
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.scriptType;
                        case 9: //scriptFlags
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.flags;
                        case 10: //compiled_p
                            *FieldValues = Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.value;
                            return NULL;
                        case 11: //scriptText
                            return Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.value;
                        case 12: //vars
                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value.size())
                                return NULL;

                            switch(ListX3FieldID)
                                {
                                case 1: //index
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.index;
                                case 2: //unused1
                                    *FieldValues = &Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[0];
                                    return NULL;
                                case 3: //flags
                                    return &Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.flags;
                                case 4: //unused2
                                    *FieldValues = &Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[0];
                                    return NULL;
                                case 5: //name
                                    return Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SCVR.value;
                                default:
                                    return NULL;
                                }
                            return NULL;
                        case 13: //references
                            for(uint32_t x = 0; x < Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size(); ++x)
                                ((FORMIDARRAY)FieldValues)[x] = Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[x]->reference;
                            return NULL;
                        case 14: //nextQuest
                            return &Stages.value[ListIndex]->Entries.value[ListX2Index]->NAM0.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 17: //objectives
            if(ListIndex >= Objectives.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //objective
                    return &Objectives.value[ListIndex]->QOBJ.value;
                case 2: //text
                    return Objectives.value[ListIndex]->NNAM.value;
                case 3: //targets
                    if(ListX2Index >= Objectives.value[ListIndex]->Targets.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //targetId
                            return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.targetId;
                        case 2: //flags
                            return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.flags;
                        case 3: //unused1
                            *FieldValues = &Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[0];
                            return NULL;
                        case 4: //conditions
                            if(ListX3Index >= Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value.size())
                                return NULL;

                            switch(ListX3FieldID)
                                {
                                case 1: //operType
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->operType;
                                case 2: //unused1
                                    *FieldValues = &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0];
                                    return NULL;
                                case 3: //compValue
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->compValue;
                                case 4: //ifunc
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc;
                                case 5: //param1
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param1;
                                case 6: //param2
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param2;
                                case 7: //runOnType
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType;
                                case 8: //reference
                                    return &Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->reference;
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
        default:
            return NULL;
        }
    return NULL;
    }

bool QUSTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 8: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 9: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 10: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 11: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 12: //priority
            DATA.value.priority = *(uint8_t *)FieldValue;
            break;
        case 13: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 14: //delay
            DATA.value.delay = *(float *)FieldValue;
            break;
        case 15: //conditions
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
                case 7: //runOnType
                    CTDA.value[ListIndex]->runOnType = *(uint32_t *)FieldValue;
                    return true;
                case 8: //reference
                    CTDA.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    return true;
                default:
                    break;
                }
            break;
        case 16: //stages
            if(ListFieldID == 0) //stagesSize
                {
                Stages.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Stages.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //stage
                    Stages.value[ListIndex]->INDX.value = *(int16_t *)FieldValue;
                    break;
                case 2: //entries
                    if(ListX2FieldID == 0) //entriesSize
                        {
                        Stages.value[ListIndex]->Entries.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Stages.value[ListIndex]->Entries.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //flags
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->QSDT.value = *(uint8_t *)FieldValue;
                            break;
                        case 2: //conditions
                            if(ListX3FieldID == 0) //conditionsSize
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.resize(ArraySize);
                                return false;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
                                break;

                            switch(ListX3FieldID)
                                {
                                case 1: //operType
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->operType = *(uint8_t *)FieldValue;
                                    break;
                                case 2: //unused1
                                    if(ArraySize != 3)
                                        break;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                                    break;
                                case 3: //compValue
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                                    return true;
                                case 4: //ifunc
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc = *(uint32_t *)FieldValue;
                                    return true;
                                case 5: //param1
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param1 = *(uint32_t *)FieldValue;
                                    return true;
                                case 6: //param2
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param2 = *(uint32_t *)FieldValue;
                                    return true;
                                case 7: //runOnType
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType = *(uint32_t *)FieldValue;
                                    return true;
                                case 8: //reference
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->reference = *(uint32_t *)FieldValue;
                                    return true;
                                default:
                                    break;
                                }
                            break;
                        case 3: //text
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->CNAM.Copy((char *)FieldValue);
                            break;
                        case 4: //unused1
                            if(ArraySize != 4)
                                break;
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        case 5: //numRefs
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.numRefs = *(uint32_t *)FieldValue;
                            break;
                        case 6: //compiledSize
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.compiledSize = *(uint32_t *)FieldValue;
                            break;
                        case 7: //lastIndex
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.lastIndex = *(uint32_t *)FieldValue;
                            break;
                        case 8: //scriptType
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.scriptType = *(uint16_t *)FieldValue;
                            break;
                        case 9: //scriptFlags
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.flags = *(uint16_t *)FieldValue;
                            break;
                        case 10: //compiled_p
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
                            break;
                        case 11: //scriptText
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.Copy((char *)FieldValue);
                            break;
                        case 12: //vars
                            if(ListX3FieldID == 0) //varsSize
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.resize(ArraySize);
                                return false;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value.size())
                                break;

                            switch(ListX3FieldID)
                                {
                                case 1: //index
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.index = *(uint32_t *)FieldValue;
                                    break;
                                case 2: //unused1
                                    if(ArraySize != 12)
                                        break;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                                    break;
                                case 3: //flags
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SetFlagMask(*(uint8_t *)FieldValue);
                                    break;
                                case 4: //unused2
                                    if(ArraySize != 7)
                                        break;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                                    break;
                                case 5: //name
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SCVR.Copy((char *)FieldValue);
                                    break;
                                default:
                                    break;
                                }
                            break;
                        case 13: //references
                            if(ListX3FieldID == 0) //referencesSize
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.resize(ArraySize);
                                return false;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size())
                                break;

                            switch(ListX3FieldID)
                                {
                                case 1: //reference
                                    //Borrowing ArraySize to flag if the new value is a formID
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->reference = *(uint32_t *)FieldValue;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->isSCRO = ArraySize ? true : false;
                                    return ArraySize != 0;
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
            break;
        case 17: //objectives
            if(ListFieldID == 0) //objectivesSize
                {
                Objectives.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Objectives.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //objective
                    Objectives.value[ListIndex]->QOBJ.value = *(int32_t *)FieldValue;
                    break;
                case 2: //text
                    Objectives.value[ListIndex]->NNAM.Copy((char *)FieldValue);
                    break;
                case 3: //targets
                    if(ListX2FieldID == 0) //targetsSize
                        {
                        Objectives.value[ListIndex]->Targets.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Objectives.value[ListIndex]->Targets.value.size())
                        break;

                    switch(ListFieldID)
                        {
                        case 1: //targetId
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.targetId = *(FORMID *)FieldValue;
                            return true;
                        case 2: //flags
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->SetFlagMask(*(uint8_t *)FieldValue);
                            break;
                        case 3: //unused1
                            if(ArraySize != 3)
                                break;
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            break;
                        case 4: //conditions
                            if(ListX3FieldID == 0) //conditionsSize
                                {
                                Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.resize(ArraySize);
                                return false;
                                }

                            if(ListX3Index >= Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value.size())
                                break;

                            switch(ListX3FieldID)
                                {
                                case 1: //operType
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->operType = *(uint8_t *)FieldValue;
                                    break;
                                case 2: //unused1
                                    if(ArraySize != 3)
                                        break;
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                                    break;
                                case 3: //compValue
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                                    return true;
                                case 4: //ifunc
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc = *(uint32_t *)FieldValue;
                                    return true;
                                case 5: //param1
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param1 = *(uint32_t *)FieldValue;
                                    return true;
                                case 6: //param2
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param2 = *(uint32_t *)FieldValue;
                                    return true;
                                case 7: //runOnType
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType = *(uint32_t *)FieldValue;
                                    return true;
                                case 8: //reference
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->reference = *(uint32_t *)FieldValue;
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
            break;
        default:
            break;
        }
    return false;
    }

void QUSTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    QUSTDATA defaultDATA;
    FNVCTDA defaultCTDA;
    QUSTQSTA defaultQSTA;
    FNVSCHR defaultSCHR;
    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;
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
        case 7: //script
            SCRI.Unload();
            return;
        case 8: //full
            FULL.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //smallIconPath
            MICO.Unload();
            return;
        case 11: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 12: //priority
            DATA.value.priority = defaultDATA.priority;
            return;
        case 13: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 14: //delay
            DATA.value.delay = defaultDATA.delay;
            return;
        case 15: //conditions
            if(ListFieldID == 0) //conditionsSize
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
                case 7: //runOnType
                    CTDA.value[ListIndex]->runOnType = defaultCTDA.runOnType;
                    return;
                case 8: //reference
                    CTDA.value[ListIndex]->reference = defaultCTDA.reference;
                    return;
                default:
                    return;
                }
            return;
        case 16: //stages
            if(ListFieldID == 0) //stagesSize
                {
                Stages.Unload();
                return;
                }

            if(ListIndex >= Stages.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //stage
                    Stages.value[ListIndex]->INDX.Unload();
                    return;
                case 2: //entries
                    if(ListX2FieldID == 0) //entries
                        {
                        Stages.value[ListIndex]->Entries.Unload();
                        return;
                        }

                    if(ListIndex >= Stages.value[ListIndex]->Entries.value.size())
                        return;

                    switch(ListFieldID)
                        {
                        case 1: //flags
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->QSDT.Unload();
                            return;
                        case 2: //conditions
                            if(ListX3FieldID == 0) //conditionsSize
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.Unload();
                                return;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
                                return;

                            switch(ListX3FieldID)
                                {
                                case 1: //operType
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->operType = defaultCTDA.operType;
                                    return;
                                case 2: //unused1
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0] = defaultCTDA.unused1[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[1] = defaultCTDA.unused1[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[2] = defaultCTDA.unused1[2];
                                    return;
                                case 3: //compValue
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->compValue = defaultCTDA.compValue;
                                    return;
                                case 4: //ifunc
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc = defaultCTDA.ifunc;
                                    return;
                                case 5: //param1
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param1 = defaultCTDA.param1;
                                    return;
                                case 6: //param2
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->param2 = defaultCTDA.param2;
                                    return;
                                case 7: //runOnType
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType = defaultCTDA.runOnType;
                                    return;
                                case 8: //reference
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->reference = defaultCTDA.reference;
                                    return;
                                default:
                                    return;
                                }
                            return;
                        case 3: //text
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->CNAM.Unload();
                            return;
                        case 4: //unused1
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[0] = defaultSCHR.unused1[0];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[1] = defaultSCHR.unused1[1];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[2] = defaultSCHR.unused1[2];
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.unused1[3] = defaultSCHR.unused1[3];
                            return;
                        case 5: //numRefs
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.numRefs = defaultSCHR.numRefs;
                            return;
                        case 6: //compiledSize
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.compiledSize = defaultSCHR.compiledSize;
                            return;
                        case 7: //lastIndex
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.lastIndex = defaultSCHR.lastIndex;
                            return;
                        case 8: //scriptType
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.scriptType = defaultSCHR.scriptType;
                            return;
                        case 9: //scriptFlags
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.flags = defaultSCHR.flags;
                            return;
                        case 10: //compiled_p
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.Unload();
                            return;
                        case 11: //scriptText
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.Unload();
                            return;
                        case 12: //vars
                            if(ListX3FieldID == 0) //vars
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.Unload();
                                return;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value.size())
                                return;

                            switch(ListX3FieldID)
                                {
                                case 1: //index
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.index = defaultVARS.SLSD.value.index;
                                    return;
                                case 2: //unused1
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                                    return;
                                case 3: //flags
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SetFlagMask(defaultVARS.SLSD.value.flags);
                                    return;
                                case 4: //unused2
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                                    return;
                                case 5: //name
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->VARS.value[ListX3Index]->SCVR.Unload();
                                    return;
                                default:
                                    return;
                                }
                            return;
                        case 13: //references
                            if(ListX3FieldID == 0) //references
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.Unload();
                                return;
                                }

                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size())
                                return;

                            switch(ListX3FieldID)
                                {
                                case 1: //reference
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->reference = defaultSCR_.reference;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[ListX3Index]->isSCRO = defaultSCR_.isSCRO;
                                    return;
                                default:
                                    return;
                                }
                            return;
                        case 14: //nextQuest
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->NAM0.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 17: //objectives
            if(ListFieldID == 0) //objectivesSize
                {
                Objectives.Unload();
                return;
                }

            if(ListIndex >= Objectives.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //objective
                    Objectives.value[ListIndex]->QOBJ.Unload();
                    return;
                case 2: //text
                    Objectives.value[ListIndex]->NNAM.Unload();
                    return;
                case 3: //targets
                    if(ListX2FieldID == 0) //stages
                        {
                        Objectives.value[ListIndex]->Targets.Unload();
                        return;
                        }

                    if(ListX2Index >= Objectives.value[ListIndex]->Targets.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //targetId
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.targetId = defaultQSTA.targetId;
                            return;
                        case 2: //flags
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.flags = defaultQSTA.flags;
                            return;
                        case 3: //unused1
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[0] = defaultQSTA.unused1[0];
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[1] = defaultQSTA.unused1[1];
                            Objectives.value[ListIndex]->Targets.value[ListX2Index]->QSTA.value.unused1[2] = defaultQSTA.unused1[2];
                            return;
                        case 4: //conditions
                            if(ListX3FieldID == 0) //conditionsSize
                                {
                                Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.Unload();
                                return;
                                }

                            if(ListX3Index >= Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value.size())
                                return;

                            switch(ListX3FieldID)
                                {
                                case 1: //operType
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->operType = defaultCTDA.operType;
                                    return;
                                case 2: //unused1
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[0] = defaultCTDA.unused1[0];
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[1] = defaultCTDA.unused1[1];
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->unused1[2] = defaultCTDA.unused1[2];
                                    return;
                                case 3: //compValue
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->compValue = defaultCTDA.compValue;
                                    return;
                                case 4: //ifunc
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc = defaultCTDA.ifunc;
                                    return;
                                case 5: //param1
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param1 = defaultCTDA.param1;
                                    return;
                                case 6: //param2
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->param2 = defaultCTDA.param2;
                                    return;
                                case 7: //runOnType
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->runOnType = defaultCTDA.runOnType;
                                    return;
                                case 8: //reference
                                    Objectives.value[ListIndex]->Targets.value[ListX2Index]->CTDA.value[ListX3Index]->reference = defaultCTDA.reference;
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
            return;
        default:
            return;
        }
    }
}