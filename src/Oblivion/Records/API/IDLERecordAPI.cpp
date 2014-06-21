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
#include "..\IDLERecord.h"

namespace Ob
{
uint32_t IDLERecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //modPath
            return CB_ISTRING_FIELD;
        case 6: //modb
            return CB_FLOAT32_FIELD;
        case 7: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //conditions
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
        case 9: //group
            return CB_UINT8_FLAG_TYPE_FIELD;
        case 10: //parent
            return CB_FORMID_FIELD;
        case 11: //prevId
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * IDLERecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 6: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 7: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 8: //conditions
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
        case 9: //group
            return &ANAM.value;
        case 10: //parent
            return &DATA.value.parent;
        case 11: //prevId
            return &DATA.value.prevId;
        default:
            return NULL;
        }
    return NULL;
    }

bool IDLERecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 6: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 7: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //conditions
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
        case 9: //group
            ANAM.value = *(uint8_t *)FieldValue;
            break;
        case 10: //parent
            DATA.value.parent = *(FORMID *)FieldValue;
            return true;
        case 11: //prevId
            DATA.value.prevId = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void IDLERecord::DeleteField(FIELD_IDENTIFIERS)
    {
    IDLEDATA defaultDATA;
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
        case 5: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 6: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 7: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 8: //conditions
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
        case 9: //group
            ANAM.Unload();
            return;
        case 10: //parent
            DATA.value.parent = defaultDATA.parent;
            return;
        case 11: //prevId
            DATA.value.prevId = defaultDATA.prevId;
            return;
        default:
            return;
        }
    return;
    }
}