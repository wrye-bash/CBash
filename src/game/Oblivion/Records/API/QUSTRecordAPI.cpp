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

namespace Ob
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
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //script
            return CB_FORMID_FIELD;
        case 6: //full
            return CB_STRING_FIELD;
        case 7: //iconPath
            return CB_ISTRING_FIELD;
        case 8: //flags
            return CB_UINT8_FLAG_FIELD;
        case 9: //priority
            return CB_UINT8_FIELD;
        case 10: //conditions
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
        case 11: //stages
            if(ListFieldID == 0) //conditions
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
                }

            if(ListIndex >= Stages.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //stage
                    return CB_UINT16_FIELD;
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
                        }

                    if(ListX2Index >= Stages.value[ListIndex]->Entries.value.size())
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
                                            Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                                            Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->ifunc);
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
                        case 5: //numRefs
                            return CB_UINT32_FIELD;
                        case 6: //compiledSize
                            return CB_UINT32_FIELD;
                        case 7: //lastIndex
                            return CB_UINT32_FIELD;
                        case 8: //scriptType
                            return CB_UINT32_FIELD;
                        case 9: //compiled_p
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.GetSize();
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 10: //scriptText
                            return CB_ISTRING_FIELD;
                        case 11: //references
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
        case 12: //targets
            if(ListFieldID == 0) //targets
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Targets.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Targets.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
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
                case 4: //conditions
                    if(ListX2FieldID == 0) //conditions
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Targets.value[ListIndex]->CTDA.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= Targets.value[ListIndex]->CTDA.value.size())
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
                            return CB_UNKNOWN_FIELD;
                        case 3: //compValue
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_FORMID_OR_FLOAT32_FIELD;
                                case 2: //WhichType
                                    return Targets.value[ListIndex]->CTDA.value[ListX2Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
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
                                    Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(Targets.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
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
                                    Function_Arguments_Iterator curCTDAFunction = Function_Arguments.find(Targets.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
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
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 6: //full
            return FULL.value;
        case 7: //iconPath
            return ICON.value;
        case 8: //flags
            return &DATA.value.flags;
        case 9: //priority
            return &DATA.value.priority;
        case 10: //conditions
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
        case 11: //stages
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
                            if(ListX3Index >= Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
                                return NULL;

                            switch(ListX3FieldID)
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
                                case 7: //unused2
                                    *FieldValues = &Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[0];
                                    return NULL;
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
                        case 9: //compiled_p
                            *FieldValues = Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.value;
                            return NULL;
                        case 10: //scriptText
                            return Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.value;
                        case 11: //references
                            for(uint32_t x = 0; x < Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value.size(); ++x)
                                ((FORMIDARRAY)FieldValues)[x] = Stages.value[ListIndex]->Entries.value[ListX2Index]->SCR_.value[x]->reference;
                            return NULL;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 12: //targets
            if(ListIndex >= Targets.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //targetId
                    return &Targets.value[ListIndex]->QSTA.value.targetId;
                case 2: //flags
                    return &Targets.value[ListIndex]->QSTA.value.flags;
                case 3: //unused1
                    *FieldValues = &Targets.value[ListIndex]->QSTA.value.unused1[0];
                    return NULL;
                case 4: //conditions
                    if(ListX2Index >= Targets.value[ListIndex]->CTDA.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            return &Targets.value[ListIndex]->CTDA.value[ListX2Index]->operType;
                        case 2: //unused1
                            *FieldValues = &Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0];
                            return NULL;
                        case 3: //compValue
                            return &Targets.value[ListIndex]->CTDA.value[ListX2Index]->compValue;
                        case 4: //ifunc
                            return &Targets.value[ListIndex]->CTDA.value[ListX2Index]->ifunc;
                        case 5: //param1
                            return &Targets.value[ListIndex]->CTDA.value[ListX2Index]->param1;
                        case 6: //param2
                            return &Targets.value[ListIndex]->CTDA.value[ListX2Index]->param2;
                        case 7: //unused2
                            *FieldValues = &Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[0];
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
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 6: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 7: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 9: //priority
            DATA.value.priority = *(uint8_t *)FieldValue;
            break;
        case 10: //conditions
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
        case 11: //stages
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
                    Stages.value[ListIndex]->INDX.value = *(uint16_t *)FieldValue;
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
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SetFlagMask(*(uint8_t *)FieldValue);
                            break;
                        case 2: //conditions
                            if(ListX3FieldID == 0) //conditionsSize
                                {
                                Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.resize(ArraySize);
                                return false;
                                }

                            if(ListX3Index >= (uint32_t)Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value.size())
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
                                case 7: //unused2
                                    if(ArraySize != 4)
                                        break;
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                                    break;
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
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCHR.value.scriptType = *(uint32_t *)FieldValue;
                            break;
                        case 9: //compiled_p
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
                            break;
                        case 10: //scriptText
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.Copy((char *)FieldValue);
                            break;
                        case 11: //references
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
        case 12: //targets
            if(ListFieldID == 0) //targetsSize
                {
                Targets.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Targets.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //targetId
                    Targets.value[ListIndex]->QSTA.value.targetId = *(FORMID *)FieldValue;
                    return true;
                case 2: //flags
                    Targets.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 3: //unused1
                    if(ArraySize != 3)
                        break;
                    Targets.value[ListIndex]->QSTA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Targets.value[ListIndex]->QSTA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Targets.value[ListIndex]->QSTA.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 4: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Targets.value[ListIndex]->CTDA.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= (uint32_t)Targets.value[ListIndex]->CTDA.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->operType = *(uint8_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 3)
                                break;
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            break;
                        case 3: //compValue
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                            return true;
                        case 4: //ifunc
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = *(uint32_t *)FieldValue;
                            return true;
                        case 5: //param1
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->param1 = *(uint32_t *)FieldValue;
                            return true;
                        case 6: //param2
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->param2 = *(uint32_t *)FieldValue;
                            return true;
                        case 7: //unused2
                            if(ArraySize != 4)
                                break;
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[3] = ((UINT8ARRAY)FieldValue)[3];
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

    GENCTDA defaultCTDA;
    QUSTQSTA defaultQSTA;

    GENSCHR defaultSCHR;

    GENSCR_ defaultSCR_;

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
        case 5: //script
            SCRI.Unload();
            return;
        case 6: //full
            FULL.Unload();
            return;
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 9: //priority
            DATA.value.priority = defaultDATA.priority;
            return;
        case 10: //conditions
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
        case 11: //stages
            if(ListFieldID == 0) //stages
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

                    if(ListX2Index >= Stages.value[ListIndex]->Entries.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //flags
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->QSDT.Unload();
                            return;
                        case 2: //conditions
                            if(ListX3FieldID == 0) //conditions
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
                                case 7: //unused2
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[0] = defaultCTDA.unused2[0];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[1] = defaultCTDA.unused2[1];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[2] = defaultCTDA.unused2[2];
                                    Stages.value[ListIndex]->Entries.value[ListX2Index]->CTDA.value[ListX3Index]->unused2[3] = defaultCTDA.unused2[3];
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
                        case 9: //compiled_p
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCDA.Unload();
                            return;
                        case 10: //scriptText
                            Stages.value[ListIndex]->Entries.value[ListX2Index]->SCTX.Unload();
                            return;
                        case 11: //references
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
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 12: //targets
            if(ListFieldID == 0) //stages
                {
                Targets.Unload();
                return;
                }

            if(ListIndex >= Targets.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //targetId
                    Targets.value[ListIndex]->QSTA.value.targetId = defaultQSTA.targetId;
                    return;
                case 2: //flags
                    Targets.value[ListIndex]->QSTA.value.flags = defaultQSTA.flags;
                    return;
                case 3: //unused1
                    Targets.value[ListIndex]->QSTA.value.unused1[0] = defaultQSTA.unused1[0];
                    Targets.value[ListIndex]->QSTA.value.unused1[1] = defaultQSTA.unused1[1];
                    Targets.value[ListIndex]->QSTA.value.unused1[2] = defaultQSTA.unused1[2];
                    return;
                case 4: //conditions
                    if(ListX2FieldID == 0) //conditions
                        {
                        Targets.value[ListIndex]->CTDA.Unload();
                        return;
                        }

                    if(ListX2Index >= Targets.value[ListIndex]->CTDA.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->operType = defaultCTDA.operType;
                            return;
                        case 2: //unused1
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = defaultCTDA.unused1[0];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = defaultCTDA.unused1[1];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = defaultCTDA.unused1[2];
                            return;
                        case 3: //compValue
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->compValue = defaultCTDA.compValue;
                            return;
                        case 4: //ifunc
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = defaultCTDA.ifunc;
                            return;
                        case 5: //param1
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->param1 = defaultCTDA.param1;
                            return;
                        case 6: //param2
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->param2 = defaultCTDA.param2;
                            return;
                        case 7: //unused2
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[0] = defaultCTDA.unused2[0];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[1] = defaultCTDA.unused2[1];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[2] = defaultCTDA.unused2[2];
                            Targets.value[ListIndex]->CTDA.value[ListX2Index]->unused2[3] = defaultCTDA.unused2[3];
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
    }
}