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
#include "..\ROADRecord.h"

namespace Ob
{
uint32_t ROADRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
            return CB_MISSING_FIELD;
        case 5: //pgrp
            if(ListFieldID == 0) //pgrp
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)PGRP.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= PGRP.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //x
                    return CB_FLOAT32_FIELD;
                case 2: //y
                    return CB_FLOAT32_FIELD;
                case 3: //z
                    return CB_FLOAT32_FIELD;
                case 4: //connections
                    return CB_UINT8_FIELD;
                case 5: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 3;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 6: //pgrr
            if(ListFieldID == 0) //pgrr
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)PGRR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= PGRR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //x
                    return CB_FLOAT32_FIELD;
                case 2: //y
                    return CB_FLOAT32_FIELD;
                case 3: //z
                    return CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        case 7: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * ROADRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 5: //pgrp
            if(ListIndex >= PGRP.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //x
                    return &PGRP.value[ListIndex].x;
                case 2: //y
                    return &PGRP.value[ListIndex].y;
                case 3: //z
                    return &PGRP.value[ListIndex].z;
                case 4: //connections
                    return &PGRP.value[ListIndex].connections;
                case 5: //unused1
                    *FieldValues = &PGRP.value[ListIndex].unused1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 6: //pgrr
            if(ListIndex >= PGRR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //x
                    return &PGRR.value[ListIndex].x;
                case 2: //y
                    return &PGRR.value[ListIndex].y;
                case 3: //z
                    return &PGRR.value[ListIndex].z;
                default:
                    return NULL;
                }
            return NULL;
        case 7: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool ROADRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 5: //pgrp
            if(ListFieldID == 0) //pgrpSize
                {
                PGRP.resize(ArraySize);
                return false;
                }

            if(ListIndex >= PGRP.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //x
                    PGRP.value[ListIndex].x = *(float *)FieldValue;
                    break;
                case 2: //y
                    PGRP.value[ListIndex].y = *(float *)FieldValue;
                    break;
                case 3: //z
                    PGRP.value[ListIndex].z = *(float *)FieldValue;
                    break;
                case 4: //connections
                    PGRP.value[ListIndex].connections = *(uint8_t *)FieldValue;
                    break;
                case 5: //unused1
                    if(ArraySize != 3)
                        break;
                    PGRP.value[ListIndex].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    PGRP.value[ListIndex].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    PGRP.value[ListIndex].unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                default:
                    break;
                }
            break;
        case 6: //pgrr
            if(ListFieldID == 0) //pgrrSize
                {
                PGRR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= PGRR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //x
                    PGRR.value[ListIndex].x = *(float *)FieldValue;
                    break;
                case 2: //y
                    PGRR.value[ListIndex].y = *(float *)FieldValue;
                    break;
                case 3: //z
                    PGRR.value[ListIndex].z = *(float *)FieldValue;
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

void ROADRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENPGRP defaultPGRP;
    ROADPGRR defaultPGRR;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 5: //pgrp
            if(ListFieldID == 0) //pgrp
                {
                PGRP.Unload();
                return;
                }

            if(ListIndex >= PGRP.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //x
                    PGRP.value[ListIndex].x = defaultPGRP.x;
                    return;
                case 2: //y
                    PGRP.value[ListIndex].y = defaultPGRP.y;
                    return;
                case 3: //z
                    PGRP.value[ListIndex].z = defaultPGRP.z;
                    return;
                case 4: //connections
                    PGRP.value[ListIndex].connections = defaultPGRP.connections;
                    return;
                case 5: //unused1
                    PGRP.value[ListIndex].unused1[0] = defaultPGRP.unused1[0];
                    PGRP.value[ListIndex].unused1[1] = defaultPGRP.unused1[1];
                    PGRP.value[ListIndex].unused1[2] = defaultPGRP.unused1[2];
                    return;
                default:
                    return;
                }
            return;
        case 6: //pgrr
            if(ListFieldID == 0) //pgrr
                {
                PGRR.Unload();
                return;
                }

            if(ListIndex >= PGRR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //x
                    PGRR.value[ListIndex].x = defaultPGRP.x;
                    return;
                case 2: //y
                    PGRR.value[ListIndex].y = defaultPGRP.y;
                    return;
                case 3: //z
                    PGRR.value[ListIndex].z = defaultPGRP.z;
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