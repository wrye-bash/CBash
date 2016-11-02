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
#include "..\PGRDRecord.h"

namespace Ob
{
uint32_t PGRDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //count
            return CB_UINT16_FIELD;
        case 6: //pgrp
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
        case 7: //pgag_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PGAG.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 8: //pgrr_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return PGRR.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 9: //pgri
            if(ListFieldID == 0) //pgri
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)PGRI.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= PGRI.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //point
                    return CB_UINT16_FIELD;
                case 2: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 2;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 3: //x
                    return CB_FLOAT32_FIELD;
                case 4: //y
                    return CB_FLOAT32_FIELD;
                case 5: //z
                    return CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //pgrl
            if(ListFieldID == 0) //pgrl
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)PGRL.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= PGRL.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return CB_FORMID_FIELD;
                case 2: //points
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT32_ARRAY_FIELD;
                        case 1: //fieldSize
                            //The first entry in the points array is actually the reference
                            return (uint32_t)PGRL.value[ListIndex]->points.value.size() - 1;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        case 11: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * PGRDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 5: //count
            return &DATA.value;
        case 6: //pgrp
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
        case 7: //pgag_p
            *FieldValues = PGAG.value;
            return NULL;
        case 8: //pgrr_p
            *FieldValues = PGRR.value;
            return NULL;
        case 9: //pgri
            if(ListIndex >= PGRI.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //point
                    return &PGRI.value[ListIndex].point;
                case 2: //unused1
                    *FieldValues = &PGRI.value[ListIndex].unused1[0];
                    return NULL;
                case 3: //x
                    return &PGRI.value[ListIndex].x;
                case 4: //y
                    return &PGRI.value[ListIndex].y;
                case 5: //z
                    return &PGRI.value[ListIndex].z;
                default:
                    return NULL;
                }
            return NULL;
        case 10: //pgrl
            if(ListIndex >= PGRL.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return PGRL.value[ListIndex]->points.value.size() ? &PGRL.value[ListIndex]->points.value[0] : NULL;
                case 2: //points
                    *FieldValues = (PGRL.value[ListIndex]->points.value.size() > 1) ? &PGRL.value[ListIndex]->points.value[1] : NULL;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 11: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool PGRDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    uint32_t reference = 0;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 5: //count
            DATA.value = *(uint16_t *)FieldValue;
            break;
        case 6: //pgrp
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
        case 7: //pgag_p
            PGAG.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 8: //pgrr_p
            PGRR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //pgri
            if(ListFieldID == 0) //pgriSize
                {
                PGRI.resize(ArraySize);
                return false;
                }

            if(ListIndex >= PGRI.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //point
                    PGRI.value[ListIndex].point = *(uint16_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 2)
                        break;
                    PGRI.value[ListIndex].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    PGRI.value[ListIndex].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 3: //x
                    PGRI.value[ListIndex].x = *(float *)FieldValue;
                    break;
                case 4: //y
                    PGRI.value[ListIndex].y = *(float *)FieldValue;
                    break;
                case 5: //z
                    PGRI.value[ListIndex].z = *(float *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 10: //pgrl
            if(ListFieldID == 0) //pgrlSize
                {
                PGRL.resize(ArraySize);
                return false;
                }

            if(ListIndex >= PGRL.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    if(PGRL.value[ListIndex]->points.value.size() == 0) //Sanity check, should already have a minimum of 1
                        PGRL.value[ListIndex]->points.value.resize(1);
                    PGRL.value[ListIndex]->points.value[0] = *(FORMID *)FieldValue;
                    return true;
                case 2: //points
                    reference = PGRL.value[ListIndex]->points.value.size() ? PGRL.value[ListIndex]->points.value[0] : 0;

                    PGRL.value[ListIndex]->points.value.resize(ArraySize + 1);
                    PGRL.value[ListIndex]->points.value[0] = reference;

                    for(uint32_t x = 0; x < ArraySize; x++)
                        PGRL.value[ListIndex]->points.value[x + 1] = ((UINT32ARRAY)FieldValue)[x];
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

void PGRDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENPGRP defaultPGRP;
    PGRDPGRI defaultPGRI;
    PGRDPGRL defaultPGRL;
    uint32_t reference;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 5: //count
            DATA.Unload();
            return;
        case 6: //pgrp
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
        case 7: //pgag_p
            PGAG.Unload();
            return;
        case 8: //pgrr_p
            PGRR.Unload();
            return;
        case 9: //pgri
            if(ListFieldID == 0) //pgri
                {
                PGRI.Unload();
                return;
                }

            if(ListIndex >= PGRI.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //point
                    PGRI.value[ListIndex].point = defaultPGRI.point;
                    return;
                case 2: //unused1
                    PGRI.value[ListIndex].unused1[0] = defaultPGRI.unused1[0];
                    PGRI.value[ListIndex].unused1[1] = defaultPGRI.unused1[1];
                    return;
                case 3: //x
                    PGRI.value[ListIndex].x = defaultPGRI.x;
                    return;
                case 4: //y
                    PGRI.value[ListIndex].y = defaultPGRI.y;
                    return;
                case 5: //z
                    PGRI.value[ListIndex].z = defaultPGRI.z;
                    return;
                default:
                    return;
                }
            return;
        case 10: //pgrl
            if(ListFieldID == 0) //pgrl
                {
                PGRL.Unload();
                return;
                }

            if(ListIndex >= PGRL.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    PGRL.value[ListIndex]->points.value[0] = defaultPGRL.points.value[0];
                    return;
                case 2: //points
                    reference = PGRL.value[ListIndex]->points.value[0];
                    PGRL.value[ListIndex]->points.Unload();
                    PGRL.value[ListIndex]->points.value.push_back(reference);
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