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
#include "..\DIALRecord.h"

namespace FNV
{
uint32_t DIALRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //quests
            if(ListFieldID == 0) //quests
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)QSTI.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= QSTI.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //quest
                    return CB_FORMID_FIELD;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //quests
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)QSTI.value[ListIndex]->Unknown.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return CB_FORMID_FIELD;
                        case 2: //unknown
                            return CB_SINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuests
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)QSTR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= QSTR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //quest
                    return CB_FORMID_FIELD;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknowns
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)QSTR.value[ListIndex]->Unknown.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return CB_FORMID_FIELD;
                        case 2: //unknown
                            return CB_SINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 9: //full
            return CB_STRING_FIELD;
        case 10: //priority
            return CB_FLOAT32_FIELD;
        case 11: //unknown
            return CB_STRING_FIELD;
        case 12: //dialType
            return CB_UINT8_TYPE_FIELD;
        case 13: //flags
            return CB_UINT8_FLAG_FIELD;
        case 14: //INFO
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SUBRECORD_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)INFO.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * DIALRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //quests
            if(ListIndex >= QSTI.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //quest
                    return &QSTI.value[ListIndex]->QSTI.value;
                case 2: //unknown
                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return &QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value;
                        case 2: //unknown
                            return QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 8: //removedQuests
            if(ListIndex >= QSTR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //quest
                    return &QSTR.value[ListIndex]->QSTR.value;
                case 2: //unknown
                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            return &QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value;
                        case 2: //unknown
                            return QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 9: //full
            return FULL.value;
        case 10: //priority
            return &PNAM.value;
        case 11: //unknown
            return TDUM.value;
        case 12: //dialType
            return &DATA.value.dialType;
        case 13: //flags
            return &DATA.value.flags;
        case 14: //INFO
            for(uint32_t p = 0;p < (uint32_t)INFO.size();++p)
                ((RECORDIDARRAY)FieldValues)[p] = INFO[p];
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool DIALRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //quests
            if(ListFieldID == 0) //questsSize
                {
                QSTI.resize(ArraySize);
                return false;
                }

            if(ListIndex >= QSTI.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTI.value[ListIndex]->QSTI.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTI.value[ListIndex]->Unknown.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unknown
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Load();
                            *QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value = *(int32_t *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuestsSize
                {
                QSTR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= QSTR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTR.value[ListIndex]->QSTR.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTR.value[ListIndex]->Unknown.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.value = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unknown
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Load();
                            *QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.value = *(int32_t *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 9: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 10: //priority
            PNAM.value = *(float *)FieldValue;
            break;
        case 11: //unknown
            TDUM.Copy((char *)FieldValue);
            break;
        case 12: //dialType
            SetType(*(uint8_t *)FieldValue);
            break;
        case 13: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void DIALRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    DIALDATA defaultDATA;
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
        case 7: //quests
            if(ListFieldID == 0) //questsSize
                {
                QSTI.Unload();
                return;
                }

            if(ListIndex >= QSTI.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTI.value[ListIndex]->QSTI.Unload();
                    return;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTI.value[ListIndex]->Unknown.Unload();
                        return;
                        }

                    if(ListX2Index >= QSTI.value[ListIndex]->Unknown.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFC.Unload();
                            return;
                        case 2: //unknown
                            QSTI.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 8: //removedQuests
            if(ListFieldID == 0) //removedQuestsSize
                {
                QSTR.Unload();
                return;
                }

            if(ListIndex >= QSTR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //quest
                    QSTR.value[ListIndex]->QSTR.Unload();
                    return;
                case 2: //unknowns
                    if(ListX2FieldID == 0) //unknownsSize
                        {
                        QSTR.value[ListIndex]->Unknown.Unload();
                        return;
                        }

                    if(ListX2Index >= QSTR.value[ListIndex]->Unknown.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //unknownId
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFC.Unload();
                            return;
                        case 2: //unknown
                            QSTR.value[ListIndex]->Unknown.value[ListX2Index]->INFX.Unload();
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 9: //full
            FULL.Unload();
            return;
        case 10: //priority
            PNAM.Unload();
            return;
        case 11: //unknown
            TDUM.Unload();
            return;
        case 12: //dialType
            SetType(defaultDATA.dialType);
            return;
        case 13: //flags
            SetType(defaultDATA.flags);
            return;
        default:
            return;
        }
    }
}