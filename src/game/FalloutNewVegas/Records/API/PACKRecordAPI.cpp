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
#include "..\PACKRecord.h"

namespace FNV
{
uint32_t PACKRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //flags
            return CB_UINT32_FLAG_FIELD;
        case 8: //aiType
            return CB_UINT8_TYPE_FIELD;
        case 9: //unused1
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
        case 10: //behaviorFlags
            return CB_UINT16_FLAG_FIELD;
        case 11: //specificFlags
            return CB_UINT16_FLAG_FIELD;
        case 12: //unused2
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
        case 13: //loc1Type
            return CB_SINT32_TYPE_FIELD;
        case 14: //loc1Id
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
        case 15: //loc1Radius
            return CB_SINT32_FIELD;
        case 16: //loc2Type
            return CB_SINT32_TYPE_FIELD;
        case 17: //loc2Id
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return (PLD2.IsLoaded() && (PLD2->locType < 2 || PLD2->locType == 4)) ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //loc2Radius
            return CB_SINT32_FIELD;
        case 19: //month
            return CB_SINT8_FIELD;
        case 20: //day
            return CB_SINT8_FIELD;
        case 21: //date
            return CB_UINT8_FIELD;
        case 22: //time
            return CB_SINT8_FIELD;
        case 23: //duration
            return CB_SINT32_FIELD;
        case 24: //target1Type
            return CB_SINT32_TYPE_FIELD;
        case 25: //target1Id
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return (PTDT.IsLoaded() && PTDT->targetType < 2) ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 26: //target1CountOrDistance
            return CB_SINT32_FIELD;
        case 27: //target1Unknown
            return CB_FLOAT32_FIELD;
        case 28: //conditions
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
        case 29: //idleAnimFlags
            return CB_UINT8_FLAG_FIELD;
        case 30: //idleAnimCount
            return CB_UINT8_FIELD;
        case 31: //idleTimer
            return CB_FLOAT32_FIELD;
        case 32: //animations
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)IDLA.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 33: //unusedIDLB_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return IDLB.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 34: //escortDistance
            return CB_UINT32_FIELD;
        case 35: //combatStyle
            return CB_FORMID_FIELD;
        case 36: //followTriggerRadius
            return CB_FLOAT32_FIELD;
        case 37: //patrolType
            return CB_UINT16_TYPE_FIELD;
        case 38: //weaponFlags
            return CB_UINT32_FLAG_FIELD;
        case 39: //fireRate
            return CB_UINT8_TYPE_FIELD;
        case 40: //fireType
            return CB_UINT8_TYPE_FIELD;
        case 41: //burstNum
            return CB_UINT16_FIELD;
        case 42: //minShots
            return CB_UINT16_FIELD;
        case 43: //maxShots
            return CB_UINT16_FIELD;
        case 44: //minPause
            return CB_FLOAT32_FIELD;
        case 45: //maxPause
            return CB_FLOAT32_FIELD;
        case 46: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PKW3.IsLoaded() ? 4 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 47: //target2Type
            return CB_SINT32_TYPE_FIELD;
        case 48: //target2Id
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return (PTD2.IsLoaded() && PTD2->targetType != 2) ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 49: //target2CountOrDistance
            return CB_SINT32_FIELD;
        case 50: //target2Unknown
            return CB_FLOAT32_FIELD;
        case 51: //FOV
            return CB_FLOAT32_FIELD;
        case 52: //topic
            return CB_FORMID_FIELD;
        case 53: //dialFlags
            return CB_UINT32_FLAG_FIELD;
        case 54: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PKDD.IsLoaded() ? 4 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 55: //dialType
            return CB_UINT32_TYPE_FIELD;
        case 56: //dialUnknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PKDD.IsLoaded() ? 4 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 57: //beginIdle
            return CB_FORMID_FIELD;
        case 58: //unused5
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
        case 59: //beginNumRefs
            return CB_UINT32_FIELD;
        case 60: //beginCompiledSize
            return CB_UINT32_FIELD;
        case 61: //beginLastIndex
            return CB_UINT32_FIELD;
        case 62: //beginScriptType
            return CB_UINT16_TYPE_FIELD;
        case 63: //beginScriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 64: //beginCompiled_p
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
        case 65: //beginScriptText
            return CB_ISTRING_FIELD;
        case 66: //beginVars
            if(ListFieldID == 0) //beginVars
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
        case 67: //beginReferences
            if(ListFieldID == 0) //beginReferences
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
        case 68: //beginTopic
            return CB_FORMID_FIELD;
        case 69: //endIdle
            return CB_FORMID_FIELD;
        case 70: //unused6
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
        case 71: //endNumRefs
            return CB_UINT32_FIELD;
        case 72: //endCompiledSize
            return CB_UINT32_FIELD;
        case 73: //endLastIndex
            return CB_UINT32_FIELD;
        case 74: //endScriptType
            return CB_UINT16_TYPE_FIELD;
        case 75: //endScriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 76: //endCompiled_p
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
        case 77: //endScriptText
            return CB_ISTRING_FIELD;
        case 78: //endVars
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
        case 79: //endReferences
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
        case 80: //endTopic
            return CB_FORMID_FIELD;
        case 81: //changeIdle
            return CB_FORMID_FIELD;
        case 82: //unused7
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
        case 83: //changeNumRefs
            return CB_UINT32_FIELD;
        case 84: //changeCompiledSize
            return CB_UINT32_FIELD;
        case 85: //changeLastIndex
            return CB_UINT32_FIELD;
        case 86: //changeScriptType
            return CB_UINT16_TYPE_FIELD;
        case 87: //changeScriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 88: //changeCompiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return ChangeSCDA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 89: //changeScriptText
            return CB_ISTRING_FIELD;
        case 90: //changeVars
            if(ListFieldID == 0) //changeVars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)ChangeVARS.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= ChangeVARS.value.size())
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
        case 91: //changeReferences
            if(ListFieldID == 0) //changeReferences
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)ChangeSCR_.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= ChangeSCR_.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return (ChangeSCR_.value[ListIndex]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD);
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 92: //changeTopic
            return CB_FORMID_FIELD;
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
        case 7: //flags
            return &PKDT.value.flags;
        case 8: //aiType
            return &PKDT.value.aiType;
        case 9: //unused1
            *FieldValues = &PKDT.value.unused1;
            return NULL;
        case 10: //behaviorFlags
            return &PKDT.value.behaviorFlags;
        case 11: //specificFlags
            return &PKDT.value.specificFlags;
        case 12: //unused2
            *FieldValues = &PKDT.value.unused2[0];
            return NULL;
        case 13: //loc1Type
            return PLDT.IsLoaded() ? &PLDT->locType : NULL;
        case 14: //loc1Id
            return PLDT.IsLoaded() ? &PLDT->locId : NULL;
        case 15: //loc1Radius
            return PLDT.IsLoaded() ? &PLDT->locRadius : NULL;
        case 16: //loc2Type
            return PLD2.IsLoaded() ? &PLD2->locType : NULL;
        case 17: //loc2Id
            return PLD2.IsLoaded() ? &PLD2->locId : NULL;
        case 18: //loc2Radius
            return PLD2.IsLoaded() ? &PLD2->locRadius : NULL;
        case 19: //month
            return &PSDT.value.month;
        case 20: //day
            return &PSDT.value.day;
        case 21: //date
            return &PSDT.value.date;
        case 22: //time
            return &PSDT.value.time;
        case 23: //duration
            return &PSDT.value.duration;
        case 24: //target1Type
            return PTDT.IsLoaded() ? &PTDT->targetType : NULL;
        case 25: //target1Id
            return PTDT.IsLoaded() ? &PTDT->targetId : NULL;
        case 26: //target1CountOrDistance
            return PTDT.IsLoaded() ? &PTDT->targetCountOrDistance : NULL;
        case 27: //target1Unknown
            return PTDT.IsLoaded() ? &PTDT->unknown : NULL;
        case 28: //conditions
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
        case 29: //idleAnimFlags
            return &IDLF.value;
        case 30: //idleAnimCount
            return &IDLC.value;
        case 31: //idleTimer
            return &IDLT.value;
        case 32: //animations
            *FieldValues = IDLA.value.size() ? &IDLA.value[0] : NULL;
            return NULL;
        case 33: //idlb_p
            *FieldValues = IDLB.value;
            return NULL;
        case 34: //escortDistance
            return &PKE2.value;
        case 35: //combatStyle
            return &CNAM.value;
        case 36: //followTriggerRadius
            return &PKFD.value;
        case 37: //patrolType
            return &PKPT.value;
        case 38: //weaponFlags
            return PKW3.IsLoaded() ? &PKW3->flags : NULL;
        case 39: //fireRate
            return PKW3.IsLoaded() ? &PKW3->fireRate : NULL;
        case 40: //fireType
            return PKW3.IsLoaded() ? &PKW3->fireType : NULL;
        case 41: //burstNum
            return PKW3.IsLoaded() ? &PKW3->burstNum : NULL;
        case 42: //minShots
            return PKW3.IsLoaded() ? &PKW3->minShots : NULL;
        case 43: //maxShots
            return PKW3.IsLoaded() ? &PKW3->maxShots : NULL;
        case 44: //minPause
            return PKW3.IsLoaded() ? &PKW3->minPause : NULL;
        case 45: //maxPause
            return PKW3.IsLoaded() ? &PKW3->maxPause : NULL;
        case 46: //unused3
            *FieldValues = PKW3.IsLoaded() ? &PKW3->unused[0] : NULL;
            return NULL;
        case 47: //target2Type
            return PTD2.IsLoaded() ? &PTD2->targetType : NULL;
        case 48: //target2Id
            return PTD2.IsLoaded() ? &PTD2->targetId : NULL;
        case 49: //target2CountOrDistance
            return PTD2.IsLoaded() ? &PTD2->targetCountOrDistance : NULL;
        case 50: //target2Unknown
            return PTD2.IsLoaded() ? &PTD2->unknown : NULL;
        case 51: //FOV
            return PKDD.IsLoaded() ? &PKDD->FOV : NULL;
        case 52: //topic
            return PKDD.IsLoaded() ? &PKDD->topic : NULL;
        case 53: //dialFlags
            return PKDD.IsLoaded() ? &PKDD->flags : NULL;
        case 54: //unused4
            *FieldValues = PKDD.IsLoaded() ? &PKDD->unused1[0] : NULL;
            return NULL;
        case 55: //dialType
            return PKDD.IsLoaded() ? &PKDD->dialType : NULL;
        case 56: //dialUnknown
            *FieldValues = PKDD.IsLoaded() ? &PKDD->unknown[0] : NULL;
            return NULL;
        case 57: //beginIdle
            return &BeginINAM.value;
        case 58: //unused5
            *FieldValues = &BeginSCHR.value.unused1[0];
            return NULL;
        case 59: //beginNumRefs
            return &BeginSCHR.value.numRefs;
        case 60: //beginCompiledSize
            return &BeginSCHR.value.compiledSize;
        case 61: //beginLastIndex
            return &BeginSCHR.value.lastIndex;
        case 62: //beginScriptType
            return &BeginSCHR.value.scriptType;
        case 63: //beginScriptFlags
            return &BeginSCHR.value.flags;
        case 64: //beginCompiled_p
            *FieldValues = BeginSCDA.value;
            return NULL;
        case 65: //beginScriptText
            return BeginSCTX.value;
        case 66: //beginVars
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
        case 67: //beginReferences
            for(uint32_t x = 0; x < BeginSCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = BeginSCR_.value[x]->reference;
            return NULL;
        case 68: //beginTopic
            return &BeginTNAM.value;
        case 69: //endIdle
            return &EndINAM.value;
        case 70: //unused6
            *FieldValues = &EndSCHR.value.unused1[0];
            return NULL;
        case 71: //endNumRefs
            return &EndSCHR.value.numRefs;
        case 72: //endCompiledSize
            return &EndSCHR.value.compiledSize;
        case 73: //endLastIndex
            return &EndSCHR.value.lastIndex;
        case 74: //endScriptType
            return &EndSCHR.value.scriptType;
        case 75: //endScriptFlags
            return &EndSCHR.value.flags;
        case 76: //endCompiled_p
            *FieldValues = EndSCDA.value;
            return NULL;
        case 77: //endScriptText
            return EndSCTX.value;
        case 78: //endVars
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
        case 79: //endReferences
            for(uint32_t x = 0; x < EndSCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = EndSCR_.value[x]->reference;
            return NULL;
        case 80: //endTopic
            return &EndTNAM.value;
        case 81: //changeIdle
            return &ChangeINAM.value;
        case 82: //unused7
            *FieldValues = &ChangeSCHR.value.unused1[0];
            return NULL;
        case 83: //changeNumRefs
            return &ChangeSCHR.value.numRefs;
        case 84: //changeCompiledSize
            return &ChangeSCHR.value.compiledSize;
        case 85: //changeLastIndex
            return &ChangeSCHR.value.lastIndex;
        case 86: //changeScriptType
            return &ChangeSCHR.value.scriptType;
        case 87: //changeScriptFlags
            return &ChangeSCHR.value.flags;
        case 88: //changeCompiled_p
            *FieldValues = ChangeSCDA.value;
            return NULL;
        case 89: //changeScriptText
            return ChangeSCTX.value;
        case 90: //changeVars
            if(ListIndex >= ChangeVARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &ChangeVARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &ChangeVARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &ChangeVARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &ChangeVARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return ChangeVARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 91: //changeReferences
            for(uint32_t x = 0; x < ChangeSCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = ChangeSCR_.value[x]->reference;
            return NULL;
        case 92: //changeTopic
            return &ChangeTNAM.value;
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
        case 7: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 8: //aiType
            SetAIType(*(uint8_t *)FieldValue);
            break;
        case 9: //unused1
            if(ArraySize != 1)
                break;
            PKDT.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 10: //behaviorFlags
            SetBehaviorFlagMask(*(uint16_t *)FieldValue);
            break;
        case 11: //specificFlags
            SetSpecificFlagMask(*(uint16_t *)FieldValue);
            break;
        case 12: //unused2
            if(ArraySize != 2)
                break;
            PKDT.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            PKDT.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 13: //loc1Type
            SetLoc1Type(*(int32_t *)FieldValue);
            break;
        case 14: //loc1Id
            PLDT.Load();
            PLDT->locId = *(FORMID_OR_UINT32 *)FieldValue;
            break;
        case 15: //loc1Radius
            PLDT.Load();
            PLDT->locRadius = *(int32_t *)FieldValue;
            break;
        case 16: //loc2Type
            SetLoc2Type(*(int32_t *)FieldValue);
            break;
        case 17: //loc2Id
            PLD2.Load();
            PLD2->locId = *(FORMID_OR_UINT32 *)FieldValue;
            break;
        case 18: //loc2Radius
            PLD2.Load();
            PLD2->locRadius = *(int32_t *)FieldValue;
            break;
        case 19: //month
            PSDT.value.month = *(int8_t *)FieldValue;
            break;
        case 20: //day
            SetDayType(*(int8_t *)FieldValue);
            break;
        case 21: //date
            PSDT.value.date = *(uint8_t *)FieldValue;
            break;
        case 22: //time
            PSDT.value.time = *(int8_t *)FieldValue;
            break;
        case 23: //duration
            PSDT.value.duration = *(int32_t *)FieldValue;
            break;
        case 24: //target1Type
            SetTarget1Type(*(int32_t *)FieldValue);
            return true;
        case 25: //target1Id
            PTDT.Load();
            PTDT->targetId = *(FORMID_OR_UINT32 *)FieldValue;
            return true;
        case 26: //target1CountOrDistance
            PTDT.Load();
            PTDT->targetCountOrDistance = *(int32_t *)FieldValue;
            break;
        case 27: //target1Unknown
            PTDT.Load();
            PTDT->unknown = *(float *)FieldValue;
            break;
        case 28: //conditions
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
        case 29: //idleAnimFlags
            SetIdleFlagMask(*(uint8_t *)FieldValue);
            break;
        case 30: //idleAnimCount
            IDLC.value = *(uint8_t *)FieldValue;
            break;
        case 31: //idleTimer
            IDLT.value = *(float *)FieldValue;
            break;
        case 32: //animations
            IDLA.value.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                IDLA.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 33: //idlb_p
            IDLB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 34: //escortDistance
            PKE2.value = *(uint32_t *)FieldValue;
            break;
        case 35: //combatStyle
            CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 36: //followTriggerRadius
            PKFD.value = *(float *)FieldValue;
            break;
        case 37: //patrolType
            SetRepeatType(*(uint16_t *)FieldValue);
            break;
        case 38: //weaponFlags
            SetWeaponFlagMask(*(uint32_t *)FieldValue);
            break;
        case 39: //fireRate
            SetFireType(*(uint8_t *)FieldValue);
            break;
        case 40: //fireType
            SetFireCountType(*(uint8_t *)FieldValue);
            break;
        case 41: //burstNum
            PKW3.Load();
            PKW3->burstNum = *(uint16_t *)FieldValue;
            break;
        case 42: //minShots
            PKW3.Load();
            PKW3->minShots = *(uint16_t *)FieldValue;
            break;
        case 43: //maxShots
            PKW3.Load();
            PKW3->maxShots = *(uint16_t *)FieldValue;
            break;
        case 44: //minPause
            PKW3.Load();
            PKW3->minPause = *(float *)FieldValue;
            break;
        case 45: //maxPause
            PKW3.Load();
            PKW3->maxPause = *(float *)FieldValue;
            break;
        case 46: //unused3
            if(ArraySize != 4)
                break;
            PKW3.Load();
            PKW3->unused[0] = ((UINT8ARRAY)FieldValue)[0];
            PKW3->unused[1] = ((UINT8ARRAY)FieldValue)[1];
            PKW3->unused[2] = ((UINT8ARRAY)FieldValue)[2];
            PKW3->unused[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 47: //target2Type
            SetTarget2Type(*(int32_t *)FieldValue);
            return true;
        case 48: //target2Id
            PTD2.Load();
            PTD2->targetId = *(uint32_t *)FieldValue;
            return true;
        case 49: //target2CountOrDistance
            PTD2.Load();
            PTD2->targetCountOrDistance = *(int32_t *)FieldValue;
            break;
        case 50: //target2Unknown
            PTD2.Load();
            PTD2->unknown = *(float *)FieldValue;
            break;
        case 51: //FOV
            PKDD.Load();
            PKDD->FOV = *(float *)FieldValue;
            break;
        case 52: //topic
            PKDD.Load();
            PKDD->topic = *(FORMID *)FieldValue;
            return true;
        case 53: //dialFlags
            SetDialogueFlagMask(*(uint32_t *)FieldValue);
            break;
        case 54: //unused4
            if(ArraySize != 4)
                break;
            PKDD.Load();
            PKDD->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            PKDD->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            PKDD->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            PKDD->unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 55: //dialType
            SetDialogueType(*(uint32_t *)FieldValue);
            break;
        case 56: //dialUnknown
            if(ArraySize != 4)
                break;
            PKDD.Load();
            PKDD->unknown[0] = ((UINT8ARRAY)FieldValue)[0];
            PKDD->unknown[1] = ((UINT8ARRAY)FieldValue)[1];
            PKDD->unknown[2] = ((UINT8ARRAY)FieldValue)[2];
            PKDD->unknown[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 57: //beginIdle
            BeginINAM.value = *(FORMID *)FieldValue;
            return true;
        case 58: //unused5
            if(ArraySize != 4)
                break;
            BeginSCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            BeginSCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            BeginSCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            BeginSCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 59: //beginNumRefs
            BeginSCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 60: //beginCompiledSize
            BeginSCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 61: //beginLastIndex
            BeginSCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 62: //beginScriptType
            SetBeginType(*(uint16_t *)FieldValue);
            break;
        case 63: //beginScriptFlags
            SetBeginScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 64: //beginCompiled_p
            BeginSCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            BeginSCHR.value.compiledSize = ArraySize;
            break;
        case 65: //beginScriptText
            BeginSCTX.Copy((char *)FieldValue);
            break;
        case 66: //beginVars
            if(ListFieldID == 0) //beginVarsSize
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
        case 67: //beginReferences
            if(ListFieldID == 0) //beginReferencesSize
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
        case 68: //beginTopic
            BeginTNAM.value = *(FORMID *)FieldValue;
            return true;
        case 69: //endIdle
            EndINAM.value = *(FORMID *)FieldValue;
            return true;
        case 70: //unused6
            if(ArraySize != 4)
                break;
            EndSCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            EndSCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            EndSCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            EndSCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 71: //endNumRefs
            EndSCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 72: //endCompiledSize
            EndSCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 73: //endLastIndex
            EndSCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 74: //endScriptType
            SetEndType(*(uint16_t *)FieldValue);
            break;
        case 75: //endScriptFlags
            SetEndScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 76: //endCompiled_p
            EndSCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            EndSCHR.value.compiledSize = ArraySize;
            break;
        case 77: //endScriptText
            EndSCTX.Copy((char *)FieldValue);
            break;
        case 78: //endVars
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
        case 79: //endReferences
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
        case 80: //endTopic
            EndTNAM.value = *(FORMID *)FieldValue;
            return true;
        case 81: //changeIdle
            ChangeINAM.value = *(FORMID *)FieldValue;
            return true;
        case 82: //unused7
            if(ArraySize != 4)
                break;
            ChangeSCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            ChangeSCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            ChangeSCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            ChangeSCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 83: //changeNumRefs
            ChangeSCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 84: //changeCompiledSize
            ChangeSCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 85: //changeLastIndex
            ChangeSCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 86: //changeScriptType
            SetChangeType(*(uint16_t *)FieldValue);
            break;
        case 87: //changeScriptFlags
            SetChangeScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 88: //changeCompiled_p
            ChangeSCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            ChangeSCHR.value.compiledSize = ArraySize;
            break;
        case 89: //changeScriptText
            ChangeSCTX.Copy((char *)FieldValue);
            break;
        case 90: //changeVars
            if(ListFieldID == 0) //changeVarsSize
                {
                ChangeVARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= ChangeVARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    ChangeVARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    ChangeVARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    ChangeVARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 91: //changeReferences
            if(ListFieldID == 0) //changeReferencesSize
                {
                ChangeSCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= ChangeSCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    ChangeSCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    ChangeSCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 92: //changeTopic
            ChangeTNAM.value = *(FORMID *)FieldValue;
            return true;
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

    FNVCTDA defaultCTDA;
    PACKPKW3 defaultPKW3;
    PACKPKDD defaultPKDD;
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
        case 7: //flags
            SetFlagMask(defaultPKDT.flags);
            return;
        case 8: //aiType
            SetAIType(defaultPKDT.aiType);
            return;
        case 9: //unused1
            PKDT.value.unused1 = defaultPKDT.unused1;
            return;
        case 10: //behaviorFlags
            SetBehaviorFlagMask(defaultPKDT.behaviorFlags);
            return;
        case 11: //specificFlags
            SetSpecificFlagMask(defaultPKDT.specificFlags);
            return;
        case 12: //unused2
            PKDT.value.unused2[0] = defaultPKDT.unused2[0];
            PKDT.value.unused2[1] = defaultPKDT.unused2[1];
            return;
        case 13: //loc1Type
            if(PLDT.IsLoaded())
                SetLoc1Type(defaultPLDT.locType);
            return;
        case 14: //loc1Id
            if(PLDT.IsLoaded())
                PLDT->locId = defaultPLDT.locId;
            return;
        case 15: //loc1Radius
            if(PLDT.IsLoaded())
                PLDT->locRadius = defaultPLDT.locRadius;
            return;
        case 16: //loc2Type
            if(PLD2.IsLoaded())
                SetLoc2Type(defaultPLDT.locType);
            return;
        case 17: //loc2Id
            if(PLD2.IsLoaded())
                PLD2->locId = defaultPLDT.locId;
            return;
        case 18: //loc2Radius
            if(PLD2.IsLoaded())
                PLD2->locRadius = defaultPLDT.locRadius;
            return;
        case 19: //month
            PSDT.value.month = defaultPSDT.month;
            return;
        case 20: //day
            SetDayType(defaultPSDT.day);
            return;
        case 21: //date
            PSDT.value.date = defaultPSDT.date;
            return;
        case 22: //time
            PSDT.value.time = defaultPSDT.time;
            return;
        case 23: //duration
            PSDT.value.duration = defaultPSDT.duration;
            return;
        case 24: //target1Type
            if(PTDT.IsLoaded())
                SetTarget1Type(defaultPTDT.targetType);
            return;
        case 25: //target1Id
            if(PTDT.IsLoaded())
                PTDT->targetId = defaultPTDT.targetId;
            return;
        case 26: //target1CountOrDistance
            if(PTDT.IsLoaded())
                PTDT->targetCountOrDistance = defaultPTDT.targetCountOrDistance;
            return;
        case 27: //target1Unknown
            if(PTDT.IsLoaded())
                PTDT->unknown = defaultPTDT.unknown;
            return;
        case 28: //conditions
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
        case 29: //idleAnimFlags
            IDLF.Unload();
            return;
        case 30: //idleAnimCount
            IDLC.Unload();
            return;
        case 31: //idleTimer
            IDLT.Unload();
            return;
        case 32: //animations
            IDLA.Unload();
            return;
        case 33: //idlb_p
            IDLB.Unload();
            return;
        case 34: //escortDistance
            PKE2.Unload();
            return;
        case 35: //combatStyle
            CNAM.Unload();
            return;
        case 36: //followTriggerRadius
            PKFD.Unload();
            return;
        case 37: //patrolType
            PKPT.Unload();
            return;
        case 38: //weaponFlags
            if(PKW3.IsLoaded())
                SetWeaponFlagMask(defaultPKW3.flags);
            return;
        case 39: //fireRate
            if(PKW3.IsLoaded())
                SetFireType(defaultPKW3.fireRate);
            return;
        case 40: //fireType
            if(PKW3.IsLoaded())
                SetFireCountType(defaultPKW3.fireType);
            return;
        case 41: //burstNum
            if(PKW3.IsLoaded())
                PKW3->burstNum = defaultPKW3.burstNum;
            return;
        case 42: //minShots
            if(PKW3.IsLoaded())
                PKW3->minShots = defaultPKW3.minShots;
            return;
        case 43: //maxShots
            if(PKW3.IsLoaded())
                PKW3->maxShots = defaultPKW3.maxShots;
            return;
        case 44: //minPause
            if(PKW3.IsLoaded())
                PKW3->minPause = defaultPKW3.minPause;
            return;
        case 45: //maxPause
            if(PKW3.IsLoaded())
                PKW3->maxPause = defaultPKW3.maxPause;
            return;
        case 46: //unused3
            if(PKW3.IsLoaded())
                {
                PKW3->unused[0] = defaultPKW3.unused[0];
                PKW3->unused[1] = defaultPKW3.unused[1];
                PKW3->unused[2] = defaultPKW3.unused[2];
                PKW3->unused[3] = defaultPKW3.unused[3];
                }
            return;
        case 47: //target2Type
            if(PTD2.IsLoaded())
                SetTarget2Type(defaultPTDT.targetType);
            return;
        case 48: //target2Id
            if(PTD2.IsLoaded())
                PTD2->targetId = defaultPTDT.targetId;
            return;
        case 49: //target2CountOrDistance
            if(PTD2.IsLoaded())
                PTD2->targetCountOrDistance = defaultPTDT.targetCountOrDistance;
            return;
        case 50: //target2Unknown
            if(PTD2.IsLoaded())
                PTD2->unknown = defaultPTDT.unknown;
            return;
        case 51: //FOV
            if(PKDD.IsLoaded())
                PKDD->FOV = defaultPKDD.FOV;
            return;
        case 52: //topic
            if(PKDD.IsLoaded())
                PKDD->topic = defaultPKDD.topic;
            return;
        case 53: //dialFlags
            if(PKDD.IsLoaded())
                SetDialogueFlagMask(defaultPKDD.flags);
            return;
        case 54: //unused4
            if(PKDD.IsLoaded())
                {
                PKDD->unused1[0] = defaultPKDD.unused1[0];
                PKDD->unused1[1] = defaultPKDD.unused1[1];
                PKDD->unused1[2] = defaultPKDD.unused1[2];
                PKDD->unused1[3] = defaultPKDD.unused1[3];
                }
            return;
        case 55: //dialType
            if(PKDD.IsLoaded())
                SetDialogueType(defaultPKDD.dialType);
            return;
        case 56: //dialUnknown
            if(PKDD.IsLoaded())
                {
                PKDD->unknown[0] = defaultPKDD.unknown[0];
                PKDD->unknown[1] = defaultPKDD.unknown[1];
                PKDD->unknown[2] = defaultPKDD.unknown[2];
                PKDD->unknown[3] = defaultPKDD.unknown[3];
                }
            return;
        case 57: //beginIdle
            BeginINAM.Unload();
            return;
        case 58: //unused5
            BeginSCHR.value.unused1[0] = defaultSCHR.unused1[0];
            BeginSCHR.value.unused1[1] = defaultSCHR.unused1[1];
            BeginSCHR.value.unused1[2] = defaultSCHR.unused1[2];
            BeginSCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 59: //beginNumRefs
            BeginSCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 60: //beginCompiledSize
            BeginSCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 61: //beginLastIndex
            BeginSCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 62: //beginScriptType
            SetBeginType(defaultSCHR.scriptType);
            return;
        case 63: //beginScriptFlags
            SetBeginScriptFlagMask(defaultSCHR.flags);
            return;
        case 64: //beginCompiled_p
            BeginSCDA.Unload();
            return;
        case 65: //beginScriptText
            BeginSCTX.Unload();
            return;
        case 66: //beginVars
            if(ListFieldID == 0) //beginVarsSize
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
        case 67: //beginReferences
            if(ListFieldID == 0) //beginReferencesSize
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
        case 68: //beginTopic
            BeginTNAM.Unload();
            return;
        case 69: //endIdle
            EndINAM.Unload();
            return;
        case 70: //unused6
            EndSCHR.value.unused1[0] = defaultSCHR.unused1[0];
            EndSCHR.value.unused1[1] = defaultSCHR.unused1[1];
            EndSCHR.value.unused1[2] = defaultSCHR.unused1[2];
            EndSCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 71: //endNumRefs
            EndSCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 72: //endCompiledSize
            EndSCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 73: //endLastIndex
            EndSCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 74: //endScriptType
            SetEndType(defaultSCHR.scriptType);
            return;
        case 75: //endScriptFlags
            SetEndScriptFlagMask(defaultSCHR.flags);
            return;
        case 76: //endCompiled_p
            EndSCDA.Unload();
            return;
        case 77: //endScriptText
            EndSCTX.Unload();
            return;
        case 78: //endVars
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
        case 79: //endReferences
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
        case 80: //endTopic
            EndTNAM.Unload();
            return;
        case 81: //changeIdle
            ChangeINAM.Unload();
            return;
        case 82: //unused7
            ChangeSCHR.value.unused1[0] = defaultSCHR.unused1[0];
            ChangeSCHR.value.unused1[1] = defaultSCHR.unused1[1];
            ChangeSCHR.value.unused1[2] = defaultSCHR.unused1[2];
            ChangeSCHR.value.unused1[3] = defaultSCHR.unused1[3];
            return;
        case 83: //changeNumRefs
            ChangeSCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 84: //changeCompiledSize
            ChangeSCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 85: //changeLastIndex
            ChangeSCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 86: //changeScriptType
            SetChangeType(defaultSCHR.scriptType);
            return;
        case 87: //changeScriptFlags
            SetChangeScriptFlagMask(defaultSCHR.flags);
            return;
        case 88: //changeCompiled_p
            ChangeSCDA.Unload();
            return;
        case 89: //changeScriptText
            ChangeSCTX.Unload();
            return;
        case 90: //changeVars
            if(ListFieldID == 0) //changeVarsSize
                {
                ChangeVARS.Unload();
                return;
                }

            if(ListIndex >= ChangeVARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    ChangeVARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    ChangeVARS.value[ListIndex]->SetFlagMask(defaultVARS.SLSD.value.flags);
                    return;
                case 4: //unused2
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    ChangeVARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    ChangeVARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 91: //changeReferences
            if(ListFieldID == 0) //changeReferencesSize
                {
                ChangeSCR_.Unload();
                return;
                }

            if(ListIndex >= ChangeSCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    ChangeSCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    ChangeSCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 92: //changeTopic
            ChangeTNAM.Unload();
            return;
        default:
            return;
        }
    }
}