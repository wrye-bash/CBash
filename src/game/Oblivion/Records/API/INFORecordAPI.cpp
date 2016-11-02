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
#include "..\INFORecord.h"

namespace Ob
{
uint32_t INFORecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //dialType
            return CB_UINT16_TYPE_FIELD;
        case 6: //flags
            return CB_UINT8_FLAG_FIELD;
        case 7: //quest
            return CB_FORMID_FIELD;
        case 8: //topic
            return CB_FORMID_FIELD;
        case 9: //prevInfo
            return CB_FORMID_FIELD;
        case 10: //addTopics
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)NAME.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //responses
            if(ListFieldID == 0) //responses
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Responses.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Responses.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //emotionType
                    return CB_UINT32_TYPE_FIELD;
                case 2: //emotionValue
                    return CB_SINT32_FIELD;
                case 3: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 4;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 4: //responseNum
                    return CB_UINT8_FIELD;
                case 5: //unused2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 3;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 6: //responseText
                    return CB_STRING_FIELD;
                case 7: //actorNotes
                    return CB_ISTRING_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 12: //conditions
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
        case 13: //choices
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)TCLT.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //linksFrom
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)TCLF.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 15: //unused1
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
        case 16: //numRefs
            return CB_UINT32_FIELD;
        case 17: //compiledSize
            return CB_UINT32_FIELD;
        case 18: //lastIndex
            return CB_UINT32_FIELD;
        case 19: //scriptType
            return CB_UINT32_FIELD;
        case 20: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCDA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 21: //scriptText
            return CB_ISTRING_FIELD;
        case 22: //references
            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)SCR_.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= SCR_.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return (SCR_.value[ListIndex]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        case 23: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * INFORecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //dialType
            return &DATA.value.dialType;
        case 6: //flags
            return &DATA.value.flags;
        case 7: //quest
            return &QSTI.value;
        case 8: //topic
            return TPIC.IsLoaded() ? &TPIC.value : NULL;
        case 9: //prevInfo
            return PNAM.value;
        case 10: //addTopics
            *FieldValues = NAME.value.size() ? &NAME.value[0] : NULL;
            return NULL;
        case 11: //responses
            if(ListIndex >= Responses.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //emotionType
                    return &Responses.value[ListIndex]->TRDT.value.emotionType;
                case 2: //emotionValue
                    return &Responses.value[ListIndex]->TRDT.value.emotionValue;
                case 3: //unused1
                    *FieldValues = &Responses.value[ListIndex]->TRDT.value.unused1[0];
                    return NULL;
                case 4: //responseNum
                    return &Responses.value[ListIndex]->TRDT.value.responseNum;
                case 5: //unused2
                    *FieldValues = &Responses.value[ListIndex]->TRDT.value.unused2[0];
                    return NULL;
                case 6: //responseText
                    return Responses.value[ListIndex]->NAM1.value;
                case 7: //actorNotes
                    return Responses.value[ListIndex]->NAM2.value;
                default:
                    return NULL;
                }
            return NULL;
        case 12: //conditions
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
        case 13: //choices
            *FieldValues = TCLT.value.size() ? &TCLT.value[0] : NULL;
            return NULL;
        case 14: //linksFrom
            *FieldValues = TCLF.value.size() ? &TCLF.value[0] : NULL;
            return NULL;
        case 15: //unused1
            *FieldValues = &SCHR.value.unused1[0];
            return NULL;
        case 16: //numRefs
            return &SCHR.value.numRefs;
        case 17: //compiledSize
            return &SCHR.value.compiledSize;
        case 18: //lastIndex
            return &SCHR.value.lastIndex;
        case 19: //scriptType
            return &SCHR.value.scriptType;
        case 20: //compiled_p
            *FieldValues = SCDA.value;
            return NULL;
        case 21: //scriptText
            return SCTX.value;
        case 22: //references
            for(uint32_t x = 0; x < SCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = SCR_.value[x]->reference;
            return NULL;
        case 23: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool INFORecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //dialType
            SetDialogType(*(uint16_t *)FieldValue);
            break;
        case 6: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 7: //quest
            QSTI.value = *(FORMID *)FieldValue;
            return true;
        case 8: //topic
            TPIC.value = *(FORMID *)FieldValue;
            return true;
        case 9: //prevInfo
            PNAM.Load();
            *PNAM.value = *(FORMID *)FieldValue;
            return true;
        case 10: //addTopics
            NAME.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                NAME.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 11: //responses
            if(ListFieldID == 0) //responsesSize
                {
                Responses.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Responses.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //emotionType
                    Responses.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    break;
                case 2: //emotionValue
                    Responses.value[ListIndex]->TRDT.value.emotionValue = *(int32_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 4)
                        break;
                    Responses.value[ListIndex]->TRDT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Responses.value[ListIndex]->TRDT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Responses.value[ListIndex]->TRDT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    Responses.value[ListIndex]->TRDT.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    break;
                case 4: //responseNum
                    Responses.value[ListIndex]->TRDT.value.responseNum = *(uint8_t *)FieldValue;
                    break;
                case 5: //unused2
                    if(ArraySize != 3)
                        break;
                    Responses.value[ListIndex]->TRDT.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Responses.value[ListIndex]->TRDT.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    Responses.value[ListIndex]->TRDT.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 6: //responseText
                    Responses.value[ListIndex]->NAM1.Copy((char *)FieldValue);
                    break;
                case 7: //actorNotes
                    Responses.value[ListIndex]->NAM2.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 12: //conditions
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
        case 13: //choices
            TCLT.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                TCLT.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 14: //linksFrom
            TCLF.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                TCLF.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 15: //unused1
            if(ArraySize != 4)
                break;
            SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 16: //numRefs
            SCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 17: //compiledSize
            SCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 18: //lastIndex
            SCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 19: //scriptType
            SetScriptType(*(uint32_t *)FieldValue);
            break;
        case 20: //compiled_p
            SCDA.Copy(((UINT8ARRAY)FieldValue), ArraySize);
            break;
        case 21: //scriptText
            SCTX.Copy((char *)FieldValue);
            break;
        case 22: //references
            if(ListFieldID == 0) //referencesSize
                {
                SCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= SCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    SCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    SCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void INFORecord::DeleteField(FIELD_IDENTIFIERS)
    {
    INFODATA defaultDATA;
    GENSCHR defaultSCHR;

    INFOTRDT defaultTRDT;
    GENCTDA defaultCTDA;
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
        case 5: //dialType
            SetDialogType(defaultDATA.dialType);
            return;
        case 6: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 7: //quest
            QSTI.Unload();
            return;
        case 8: //topic
            TPIC.Unload();
            return;
        case 9: //prevInfo
            PNAM.Unload();
            return;
        case 10: //addTopics
            NAME.Unload();
            return;
        case 11: //responses
            if(ListFieldID == 0) //responses
                {
                Responses.Unload();
                return;
                }

            if(ListIndex >= Responses.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //emotionType
                    Responses.value[ListIndex]->SetType(defaultTRDT.emotionType);
                    return;
                case 2: //emotionValue
                    Responses.value[ListIndex]->TRDT.value.emotionValue = defaultTRDT.emotionValue;
                    return;
                case 3: //unused1
                    Responses.value[ListIndex]->TRDT.value.unused1[0] = defaultTRDT.unused1[0];
                    Responses.value[ListIndex]->TRDT.value.unused1[1] = defaultTRDT.unused1[1];
                    Responses.value[ListIndex]->TRDT.value.unused1[2] = defaultTRDT.unused1[2];
                    Responses.value[ListIndex]->TRDT.value.unused1[3] = defaultTRDT.unused1[3];
                    return;
                case 4: //responseNum
                    Responses.value[ListIndex]->TRDT.value.responseNum = defaultTRDT.responseNum;
                    return;
                case 5: //unused2
                    Responses.value[ListIndex]->TRDT.value.unused2[0] = defaultTRDT.unused2[0];
                    Responses.value[ListIndex]->TRDT.value.unused2[1] = defaultTRDT.unused2[1];
                    Responses.value[ListIndex]->TRDT.value.unused2[2] = defaultTRDT.unused2[2];
                    return;
                case 6: //responseText
                    Responses.value[ListIndex]->NAM1.Unload();
                    return;
                case 7: //actorNotes
                    Responses.value[ListIndex]->NAM2.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 12: //conditions
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
        case 13: //choices
            TCLT.Unload();
            return;
        case 14: //linksFrom
            TCLF.Unload();
            return;
        case 15: //unused1
            SCHR.value.unused1[0] = defaultSCHR.unused1[0];
            SCHR.value.unused1[1] = defaultSCHR.unused1[1];
            SCHR.value.unused1[2] = defaultSCHR.unused1[2];
            SCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 16: //numRefs
            SCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 17: //compiledSize
            SCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 18: //lastIndex
            SCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 19: //scriptType
            SetScriptType(defaultSCHR.scriptType);
            return;
        case 20: //compiled_p
            SCDA.Unload();
            return;
        case 21: //scriptText
            SCTX.Unload();
            return;
        case 22: //references
            if(ListFieldID == 0) //references
                {
                SCR_.Unload();
                return;
                }

            if(ListIndex >= SCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    SCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    SCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
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