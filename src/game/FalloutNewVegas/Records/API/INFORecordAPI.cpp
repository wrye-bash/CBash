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

namespace FNV
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
            return CB_MISSING_FIELD;
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
        case 7: //dialType
            return CB_UINT8_TYPE_FIELD;
        case 8: //nextSpeaker
            return CB_UINT8_TYPE_FIELD;
        case 9: //flags
            return CB_UINT16_FLAG_FIELD;
        case 10: //quest
            return CB_FORMID_FIELD;
        case 11: //topic
            return CB_FORMID_FIELD;
        case 12: //prevInfo
            return CB_FORMID_FIELD;
        case 13: //addTopics
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
        case 14: //responses
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
                return CB_UNKNOWN_FIELD;
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
                    return CB_UNKNOWN_FIELD;
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
                    return CB_UNKNOWN_FIELD;
                case 6: //sound
                    return CB_FORMID_FIELD;
                case 7: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 8: //unused3
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
                case 9: //responseText
                    return CB_STRING_FIELD;
                case 10: //actorNotes
                    return CB_ISTRING_FIELD;
                case 11: //editNotes
                    return CB_ISTRING_FIELD;
                case 12: //speakerAnim
                    return CB_FORMID_FIELD;
                case 13: //listenerAnim
                    return CB_FORMID_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
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
        case 16: //choices
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
        case 17: //linksFrom
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
        case 18: //unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)TCFU.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //unused1
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
        case 20: //numRefs
            return CB_UINT32_FIELD;
        case 21: //compiledSize
            return CB_UINT32_FIELD;
        case 22: //lastIndex
            return CB_UINT32_FIELD;
        case 23: //scriptType
            return CB_UINT16_TYPE_FIELD;
        case 24: //scriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 25: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return BeginSCDA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 26: //scriptText
            return CB_ISTRING_FIELD;
        case 27: //vars
            if(ListFieldID == 0) //vars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)BeginVARS.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= BeginVARS.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
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
                    return CB_UNKNOWN_FIELD;
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
                    return CB_UNKNOWN_FIELD;
                case 5: //name
                    return CB_ISTRING_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 28: //references
            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)BeginSCR_.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= BeginSCR_.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return (BeginSCR_.value[ListIndex]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 29: //unused2
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
        case 30: //endNumRefs
            return CB_UINT32_FIELD;
        case 31: //endCompiledSize
            return CB_UINT32_FIELD;
        case 32: //endLastIndex
            return CB_UINT32_FIELD;
        case 33: //endScriptType
            return CB_UINT16_TYPE_FIELD;
        case 34: //endScriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 35: //endCompiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return EndSCDA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 36: //endScriptText
            return CB_ISTRING_FIELD;
        case 37: //endVars
            if(ListFieldID == 0) //endVars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)EndVARS.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= EndVARS.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
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
                    return CB_UNKNOWN_FIELD;
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
                    return CB_UNKNOWN_FIELD;
                case 5: //name
                    return CB_ISTRING_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 38: //endReferences
            if(ListFieldID == 0) //endReferences
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)EndSCR_.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= EndSCR_.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return (EndSCR_.value[ListIndex]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 39: //unusedSound
            return CB_FORMID_FIELD;
        case 40: //prompt
            return CB_STRING_FIELD;
        case 41: //speaker
            return CB_FORMID_FIELD;
        case 42: //actorValueOrPerk
            return CB_FORMID_FIELD;
        case 43: //challengeType
            return CB_UINT32_TYPE_FIELD;
        case 44: //Parent
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
        case 3: //versionControl1
            *FieldValues = &flagsUnk;
            return NULL;
        case 5: //formVersion
            return &formVersion;
        case 6: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 7: //dialType
            return &DATA.value.dialType;
        case 8: //nextSpeaker
            return &DATA.value.nextSpeaker;
        case 9: //flags
            return &DATA.value.flags;
        case 10: //quest
            return &QSTI.value;
        case 11: //topic
            return &TPIC.value;
        case 12: //prevInfo
            return &PNAM.value;
        case 13: //addTopics
            *FieldValues = NAME.value.size() ? &NAME.value[0] : NULL;
            return NULL;
        case 14: //responses
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
                case 6: //sound
                    return &Responses.value[ListIndex]->TRDT.value.sound;
                case 7: //flags
                    return &Responses.value[ListIndex]->TRDT.value.flags;
                case 8: //unused3
                    *FieldValues = &Responses.value[ListIndex]->TRDT.value.unused3[0];
                    return NULL;
                case 9: //responseText
                    return Responses.value[ListIndex]->NAM1.value;
                case 10: //actorNotes
                    return Responses.value[ListIndex]->NAM2.value;
                case 11: //editNotes
                    return Responses.value[ListIndex]->NAM3.value;
                case 12: //speakerAnim
                    return &Responses.value[ListIndex]->SNAM.value;
                case 13: //listenerAnim
                    return &Responses.value[ListIndex]->LNAM.value;
                default:
                    return NULL;
                }
            return NULL;
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
        case 16: //choices
            *FieldValues = TCLT.value.size() ? &TCLT.value[0] : NULL;
            return NULL;
        case 17: //linksFrom
            *FieldValues = TCLF.value.size() ? &TCLF.value[0] : NULL;
            return NULL;
        case 18: //unknown
            *FieldValues = TCFU.value.size() ? &TCFU.value[0] : NULL;
            return NULL;
        case 19: //unused1
            *FieldValues = &BeginSCHR.value.unused1[0];
            return NULL;
        case 20: //numRefs
            return &BeginSCHR.value.numRefs;
        case 21: //compiledSize
            return &BeginSCHR.value.compiledSize;
        case 22: //lastIndex
            return &BeginSCHR.value.lastIndex;
        case 23: //scriptType
            return &BeginSCHR.value.scriptType;
        case 24: //scriptFlags
            return &BeginSCHR.value.flags;
        case 25: //compiled_p
            *FieldValues = BeginSCDA.value;
            return NULL;
        case 26: //scriptText
            return BeginSCTX.value;
        case 27: //vars
            if(ListIndex >= BeginVARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &BeginVARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &BeginVARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &BeginVARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &BeginVARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return BeginVARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 28: //references
            for(uint32_t x = 0; x < BeginSCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = BeginSCR_.value[x]->reference;
            return NULL;
        case 29: //unused2
            *FieldValues = &EndSCHR.value.unused1[0];
            return NULL;
        case 30: //endNumRefs
            return &EndSCHR.value.numRefs;
        case 31: //endCompiledSize
            return &EndSCHR.value.compiledSize;
        case 32: //endLastIndex
            return &EndSCHR.value.lastIndex;
        case 33: //endScriptType
            return &EndSCHR.value.scriptType;
        case 34: //endScriptFlags
            return &EndSCHR.value.flags;
        case 35: //endCompiled_p
            *FieldValues = EndSCDA.value;
            return NULL;
        case 36: //endScriptText
            return EndSCTX.value;
        case 37: //endVars
            if(ListIndex >= EndVARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &EndVARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &EndVARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &EndVARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &EndVARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return EndVARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 38: //endReferences
            for(uint32_t x = 0; x < EndSCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = EndSCR_.value[x]->reference;
            return NULL;
        case 39: //unusedSound
            return &SNDD.value;
        case 40: //prompt
            return RNAM.value;
        case 41: //speaker
            return &ANAM.value;
        case 42: //actorValueOrPerk
            return &KNAM.value;
        case 43: //challengeType
            return &DNAM.value;
        case 44: //Parent
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
        case 3: //versionControl1
            if(ArraySize != 4)
                break;
            ((UINT8ARRAY)&flagsUnk)[0] = ((UINT8ARRAY)FieldValue)[0];
            ((UINT8ARRAY)&flagsUnk)[1] = ((UINT8ARRAY)FieldValue)[1];
            ((UINT8ARRAY)&flagsUnk)[2] = ((UINT8ARRAY)FieldValue)[2];
            ((UINT8ARRAY)&flagsUnk)[3] = ((UINT8ARRAY)FieldValue)[3];
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
        case 7: //dialType
            SetDialogType(*(uint8_t *)FieldValue);
            break;
        case 8: //nextSpeaker
            SetSpeakerType(*(uint8_t *)FieldValue);
            break;
        case 9: //flags
            SetFlagMask(*(uint16_t *)FieldValue);
            break;
        case 10: //quest
            QSTI.value = *(FORMID *)FieldValue;
            return true;
        case 11: //topic
            TPIC.value = *(FORMID *)FieldValue;
            return true;
        case 12: //prevInfo
            PNAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //addTopics
            NAME.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                NAME.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 14: //responses
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
                case 6: //sound
                    Responses.value[ListIndex]->TRDT.value.sound = *(FORMID *)FieldValue;
                    return true;
                case 7: //flags
                    Responses.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 8: //unused3
                    if(ArraySize != 3)
                        break;
                    Responses.value[ListIndex]->TRDT.value.unused3[0] = ((UINT8ARRAY)FieldValue)[0];
                    Responses.value[ListIndex]->TRDT.value.unused3[1] = ((UINT8ARRAY)FieldValue)[1];
                    Responses.value[ListIndex]->TRDT.value.unused3[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 9: //responseText
                    Responses.value[ListIndex]->NAM1.Copy((char *)FieldValue);
                    break;
                case 10: //actorNotes
                    Responses.value[ListIndex]->NAM2.Copy((char *)FieldValue);
                    break;
                case 11: //editNotes
                    Responses.value[ListIndex]->NAM3.Copy((char *)FieldValue);
                    break;
                case 12: //speakerAnim
                    Responses.value[ListIndex]->SNAM.value = *(FORMID *)FieldValue;
                    return true;
                case 13: //listenerAnim
                    Responses.value[ListIndex]->LNAM.value = *(FORMID *)FieldValue;
                    return true;
                default:
                    break;
                }
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
        case 16: //choices
            TCLT.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                TCLT.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 17: //linksFrom
            TCLF.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                TCLF.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 18: //unknown
            TCFU.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                TCFU.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 19: //unused1
            if(ArraySize != 4)
                break;
            BeginSCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            BeginSCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            BeginSCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            BeginSCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 20: //numRefs
            BeginSCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 21: //compiledSize
            BeginSCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 22: //lastIndex
            BeginSCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 23: //scriptType
            SetBeginType(*(uint16_t *)FieldValue);
            break;
        case 24: //scriptFlags
            SetBeginScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 25: //compiled_p
            BeginSCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            BeginSCHR.value.compiledSize = ArraySize;
            break;
        case 26: //scriptText
            BeginSCTX.Copy((char *)FieldValue);
            break;
        case 27: //vars
            if(ListFieldID == 0) //varsSize
                {
                BeginVARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= BeginVARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    BeginVARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    BeginVARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    BeginVARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 28: //references
            if(ListFieldID == 0) //referencesSize
                {
                BeginSCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= BeginSCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    BeginSCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    BeginSCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 29: //unused2
            if(ArraySize != 4)
                break;
            EndSCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            EndSCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            EndSCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            EndSCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 30: //endNumRefs
            EndSCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 31: //endCompiledSize
            EndSCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 32: //endLastIndex
            EndSCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 33: //endScriptType
            SetEndType(*(uint16_t *)FieldValue);
            break;
        case 34: //endScriptFlags
            SetEndScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 35: //endCompiled_p
            EndSCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            BeginSCHR.value.compiledSize = ArraySize;
            break;
        case 36: //endScriptText
            EndSCTX.Copy((char *)FieldValue);
            break;
        case 37: //endVars
            if(ListFieldID == 0) //endVarsSize
                {
                EndVARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= EndVARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    EndVARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    EndVARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    EndVARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    EndVARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    EndVARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 38: //endReferences
            if(ListFieldID == 0) //endReferencesSize
                {
                EndSCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= EndSCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    EndSCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    EndSCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 39: //unusedSound
            SNDD.value = *(FORMID *)FieldValue;
            return true;
        case 40: //prompt
            RNAM.Copy((char *)FieldValue);
            break;
        case 41: //speaker
            ANAM.value = *(FORMID *)FieldValue;
            return true;
        case 42: //actorValueOrPerk
            KNAM.value = *(FORMID *)FieldValue;
            return true;
        case 43: //challengeType
            DNAM.value = *(uint32_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void INFORecord::DeleteField(FIELD_IDENTIFIERS)
    {
    INFODATA defaultDATA;
    FNVSCHR defaultSCHR;

    INFOTRDT defaultTRDT;
    FNVCTDA defaultCTDA;
    GENSCR_ defaultSCR_;
    GENVARS defaultVARS;
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //versionControl1
            flagsUnk = 0;
            return;
        case 5: //formVersion
            formVersion = 0;
            return;
        case 6: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 7: //dialType
            SetDialogType(defaultDATA.dialType);
            return;
        case 8: //nextSpeaker
            SetSpeakerType(defaultDATA.nextSpeaker);
            return;
        case 9: //flags
            SetFlagMask(defaultDATA.flags);
            return;
        case 10: //quest
            QSTI.Unload();
            return;
        case 11: //topic
            TPIC.Unload();
            return;
        case 12: //prevInfo
            PNAM.Unload();
            return;
        case 13: //addTopics
            NAME.Unload();
            return;
        case 14: //responses
            if(ListFieldID == 0) //responsesSize
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
                case 6: //sound
                    Responses.value[ListIndex]->TRDT.value.sound = defaultTRDT.sound;
                    return;
                case 7: //flags
                    Responses.value[ListIndex]->SetFlagMask(defaultTRDT.flags);
                    return;
                case 8: //unused3
                    Responses.value[ListIndex]->TRDT.value.unused3[0] = defaultTRDT.unused3[0];
                    Responses.value[ListIndex]->TRDT.value.unused3[1] = defaultTRDT.unused3[1];
                    Responses.value[ListIndex]->TRDT.value.unused3[2] = defaultTRDT.unused3[2];
                    return;
                case 9: //responseText
                    Responses.value[ListIndex]->NAM1.Unload();
                    return;
                case 10: //actorNotes
                    Responses.value[ListIndex]->NAM2.Unload();
                    return;
                case 11: //editNotes
                    Responses.value[ListIndex]->NAM3.Unload();
                    return;
                case 12: //speakerAnim
                    Responses.value[ListIndex]->SNAM.Unload();
                    return;
                case 13: //listenerAnim
                    Responses.value[ListIndex]->LNAM.Unload();
                    return;
                default:
                    return;
                }
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
        case 16: //choices
            TCLT.Unload();
            return;
        case 17: //linksFrom
            TCLF.Unload();
            return;
        case 18: //unknown
            TCFU.Unload();
            return;
        case 19: //unused1
            BeginSCHR.value.unused1[0] = defaultSCHR.unused1[0];
            BeginSCHR.value.unused1[1] = defaultSCHR.unused1[1];
            BeginSCHR.value.unused1[2] = defaultSCHR.unused1[2];
            BeginSCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 20: //numRefs
            BeginSCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 21: //compiledSize
            BeginSCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 22: //lastIndex
            BeginSCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 23: //scriptType
            SetBeginType(defaultSCHR.scriptType);
            return;
        case 24: //scriptFlags
            SetBeginScriptFlagMask(defaultSCHR.flags);
            return;
        case 25: //compiled_p
            BeginSCDA.Unload();
            return;
        case 26: //scriptText
            BeginSCTX.Unload();
            return;
        case 27: //vars
            if(ListFieldID == 0) //varsSize
                {
                BeginVARS.Unload();
                return;
                }

            if(ListIndex >= BeginVARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    BeginVARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    BeginVARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    BeginVARS.value[ListIndex]->SetFlagMask(defaultVARS.SLSD.value.flags);
                    return;
                case 4: //unused2
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    BeginVARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    BeginVARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 28: //references
            if(ListFieldID == 0) //referencesSize
                {
                BeginSCR_.Unload();
                return;
                }

            if(ListIndex >= BeginSCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    BeginSCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    BeginSCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 29: //unused2
            EndSCHR.value.unused1[0] = defaultSCHR.unused1[0];
            EndSCHR.value.unused1[1] = defaultSCHR.unused1[1];
            EndSCHR.value.unused1[2] = defaultSCHR.unused1[2];
            EndSCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 30: //endNumRefs
            EndSCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 31: //endCompiledSize
            EndSCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 32: //endLastIndex
            EndSCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 33: //endScriptType
            SetEndType(defaultSCHR.scriptType);
            return;
        case 34: //endScriptFlags
            SetEndScriptFlagMask(defaultSCHR.flags);
            return;
        case 35: //endCompiled_p
            EndSCDA.Unload();
            return;
        case 36: //endScriptText
            EndSCTX.Unload();
            return;
        case 37: //endVars
            if(ListFieldID == 0) //endVarsSize
                {
                EndVARS.Unload();
                return;
                }

            if(ListIndex >= EndVARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    EndVARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    EndVARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    EndVARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    EndVARS.value[ListIndex]->SetFlagMask(defaultVARS.SLSD.value.flags);
                    return;
                case 4: //unused2
                    EndVARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    EndVARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    EndVARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 38: //endReferences
            if(ListFieldID == 0) //endReferencesSize
                {
                EndSCR_.Unload();
                return;
                }

            if(ListIndex >= EndSCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    EndSCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    EndSCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 39: //unusedSound
            SNDD.Unload();
            return;
        case 40: //prompt
            RNAM.Unload();
            return;
        case 41: //speaker
            ANAM.Unload();
            return;
        case 42: //actorValueOrPerk
            KNAM.Unload();
            return;
        case 43: //challengeType
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}