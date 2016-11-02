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
#include "..\REGNRecord.h"

namespace Ob
{
uint32_t REGNRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //iconPath
            return CB_ISTRING_FIELD;
        case 6: //mapRed
            return CB_UINT8_FIELD;
        case 7: //mapGreen
            return CB_UINT8_FIELD;
        case 8: //mapBlue
            return CB_UINT8_FIELD;
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
        case 10: //worldspace
            return CB_FORMID_FIELD;
        case 11: //areas
            if(ListFieldID == 0) //areas
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Areas.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Areas.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    return CB_FORMID_FIELD;
                case 2: //points
                    if(ListX2FieldID == 0) //points
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Areas.value[ListIndex]->RPLD.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return CB_FLOAT32_FIELD;
                        case 2: //posY
                            return CB_FLOAT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 12: //entries
            if(ListFieldID == 0) //entries
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Entries.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Entries.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //entryType
                    return CB_UINT32_TYPE_FIELD;
                case 2: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 3: //priority
                    return CB_UINT8_FIELD;
                case 4: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 2;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 5: //objects
                    if(ListX2FieldID == 0) //points
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Entries.value[ListIndex]->RDOT.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            return CB_FORMID_FIELD;
                        case 2: //parentIndex
                            return CB_UINT16_FIELD;
                        case 3: //unused1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 2;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 4: //density
                            return CB_FLOAT32_FIELD;
                        case 5: //clustering
                            return CB_UINT8_FIELD;
                        case 6: //minSlope
                            return CB_UINT8_FIELD;
                        case 7: //maxSlope
                            return CB_UINT8_FIELD;
                        case 8: //flags
                            return CB_UINT8_FLAG_FIELD;
                        case 9: //radiusWRTParent
                            return CB_UINT16_FIELD;
                        case 10: //radius
                            return CB_UINT16_FIELD;
                        case 11: //unk1
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 4;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 12: //maxHeight
                            return CB_FLOAT32_FIELD;
                        case 13: //sink
                            return CB_FLOAT32_FIELD;
                        case 14: //sinkVar
                            return CB_FLOAT32_FIELD;
                        case 15: //sizeVar
                            return CB_FLOAT32_FIELD;
                        case 16: //angleVarX
                            return CB_UINT16_FIELD;
                        case 17: //angleVarY
                            return CB_UINT16_FIELD;
                        case 18: //angleVarZ
                            return CB_UINT16_FIELD;
                        case 19: //unused2
                            switch(WhichAttribute)
                                {
                                case 0: //fieldType
                                    return CB_UINT8_ARRAY_FIELD;
                                case 1: //fieldSize
                                    return 2;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                        case 20: //unk2
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
                case 6: //mapName
                    return CB_STRING_FIELD;
                case 7: //iconPath
                    return CB_ISTRING_FIELD;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grasses
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Entries.value[ListIndex]->RDGS.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            return CB_FORMID_FIELD;
                        case 2: //unk1
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
                case 9: //musicType
                    return CB_UINT32_TYPE_FIELD;
                case 10: //sounds
                    if(ListX2FieldID == 0) //sounds
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Entries.value[ListIndex]->RDSD.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return CB_FORMID_FIELD;
                        case 2: //flags
                            return CB_UINT32_FLAG_FIELD;
                        case 3: //chance
                            return CB_UINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 11: //weathers
                    if(ListX2FieldID == 0) //weathers
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Entries.value[ListIndex]->RDWT.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            return CB_FORMID_FIELD;
                        case 2: //chance
                            return CB_UINT32_FIELD;
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

void * REGNRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //iconPath
            return ICON.value;
        case 6: //mapRed
            return &RCLR.value.red;
        case 7: //mapGreen
            return &RCLR.value.green;
        case 8: //mapBlue
            return &RCLR.value.blue;
        case 9: //unused1
            *FieldValues = &RCLR.value.unused1;
            return NULL;
        case 10: //worldspace
            return WNAM.IsLoaded() ? &WNAM.value : NULL;
        case 11: //areas
            if(ListIndex >= Areas.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    return &Areas.value[ListIndex]->RPLI.value;
                case 2: //points
                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            return &Areas.value[ListIndex]->RPLD.value[ListX2Index].posX;
                        case 2: //posY
                            return &Areas.value[ListIndex]->RPLD.value[ListX2Index].posY;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 12: //entries
            if(ListIndex >= Entries.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //entryType
                    return &Entries.value[ListIndex]->RDAT.value.entryType;
                case 2: //flags
                    return &Entries.value[ListIndex]->RDAT.value.flags;
                case 3: //priority
                    return &Entries.value[ListIndex]->RDAT.value.priority;
                case 4: //unused1
                    *FieldValues = &Entries.value[ListIndex]->RDAT.value.unused1[0];
                    return NULL;
                case 5: //objects
                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId;
                        case 2: //parentIndex
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex;
                        case 3: //unused1
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0];
                            return NULL;
                        case 4: //density
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].density;
                        case 5: //clustering
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering;
                        case 6: //minSlope
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope;
                        case 7: //maxSlope
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope;
                        case 8: //flags
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].flags;
                        case 9: //radiusWRTParent
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent;
                        case 10: //radius
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].radius;
                        case 11: //unk1
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0];
                            return NULL;
                        case 12: //maxHeight
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight;
                        case 13: //sink
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sink;
                        case 14: //sinkVar
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar;
                        case 15: //sizeVar
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar;
                        case 16: //angleVarX
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX;
                        case 17: //angleVarY
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY;
                        case 18: //angleVarZ
                            return &Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ;
                        case 19: //unused2
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0];
                            return NULL;
                        case 20: //unk2
                            *FieldValues = &Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0];
                            return NULL;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 6: //mapName
                    return Entries.value[ListIndex]->RDMP.value;
                case 7: //iconPath
                    return Entries.value[ListIndex]->ICON.value;
                case 8: //grasses
                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            return &Entries.value[ListIndex]->RDGS.value[ListX2Index].grass;
                        case 2: //unused1
                            *FieldValues = &Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[0];
                            return NULL;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 9: //musicType
                    return Entries.value[ListIndex]->RDMD.value;
                case 10: //sounds
                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].sound;
                        case 2: //flags
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].flags;
                        case 3: //chance
                            return &Entries.value[ListIndex]->RDSD.value[ListX2Index].chance;
                        default:
                            return NULL;
                        }
                    return NULL;
                case 11: //weathers
                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            return &Entries.value[ListIndex]->RDWT.value[ListX2Index].weather;
                        case 2: //chance
                            return &Entries.value[ListIndex]->RDWT.value[ListX2Index].chance;
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

bool REGNRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 6: //mapRed
            RCLR.value.red = *(uint8_t *)FieldValue;
            break;
        case 7: //mapGreen
            RCLR.value.green = *(uint8_t *)FieldValue;
            break;
        case 8: //mapBlue
            RCLR.value.blue = *(uint8_t *)FieldValue;
            break;
        case 9: //unused1
            if(ArraySize != 1)
                break;
            RCLR.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 10: //worldspace
            WNAM.Load();
            WNAM.value = *(FORMID *)FieldValue;
            return true;
        case 11: //areas
            if(ListFieldID == 0) //areasSize
                {
                Areas.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Areas.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    Areas.value[ListIndex]->RPLI.value = *(uint32_t *)FieldValue;
                    break;
                case 2: //points
                    if(ListX2FieldID == 0) //pointsSize
                        {
                        Areas.value[ListIndex]->RPLD.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posX = *(float *)FieldValue;
                            break;
                        case 2: //posY
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posY = *(float *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 12: //entries
            if(ListFieldID == 0) //areasSize
                {
                Entries.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Entries.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //entryType
                    Entries.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    return true;
                case 2: //flags
                    Entries.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 3: //priority
                    Entries.value[ListIndex]->RDAT.value.priority = *(uint8_t *)FieldValue;
                    break;
                case 4: //unused1
                    if(ArraySize != 2)
                        break;
                    Entries.value[ListIndex]->RDAT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Entries.value[ListIndex]->RDAT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 5: //objects
                    if(ListX2FieldID == 0) //objectsSize
                        {
                        Entries.value[ListIndex]->RDOT.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId = *(FORMID *)FieldValue;
                            return true;
                        case 2: //parentIndex
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex = *(uint16_t *)FieldValue;
                            break;
                        case 3: //unused1
                            if(ArraySize != 2)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            break;
                        case 4: //density
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].density = *(float *)FieldValue;
                            break;
                        case 5: //clustering
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering = *(uint8_t *)FieldValue;
                            break;
                        case 6: //minSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope = *(uint8_t *)FieldValue;
                            break;
                        case 7: //maxSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope = *(uint8_t *)FieldValue;
                            break;
                        case 8: //flags
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].SetFlagMask(*(uint8_t *)FieldValue);
                            break;
                        case 9: //radiusWRTParent
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent = *(uint16_t *)FieldValue;
                            break;
                        case 10: //radius
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radius = *(uint16_t *)FieldValue;
                            break;
                        case 11: //unk1
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        case 12: //maxHeight
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight = *(float *)FieldValue;
                            break;
                        case 13: //sink
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sink = *(float *)FieldValue;
                            break;
                        case 14: //sinkVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar = *(float *)FieldValue;
                            break;
                        case 15: //sizeVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar = *(float *)FieldValue;
                            break;
                        case 16: //angleVarX
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX = *(uint16_t *)FieldValue;
                            break;
                        case 17: //angleVarY
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY = *(uint16_t *)FieldValue;
                            break;
                        case 18: //angleVarZ
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ = *(uint16_t *)FieldValue;
                            break;
                        case 19: //unused2
                            if(ArraySize != 2)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                            break;
                        case 20: //unk2
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        default:
                            break;
                        }
                    break;
                case 6: //mapName
                    Entries.value[ListIndex]->RDMP.Copy((char *)FieldValue);
                    break;
                case 7: //iconPath
                    Entries.value[ListIndex]->ICON.Copy((char *)FieldValue);
                    break;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grassesSize
                        {
                        Entries.value[ListIndex]->RDGS.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].grass = *(FORMID *)FieldValue;
                            return true;
                        case 2: //unused1
                            if(ArraySize != 4)
                                break;
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                            break;
                        default:
                            break;
                        }
                    break;
                case 9: //musicType
                    Entries.value[ListIndex]->SetMusicType(*(uint32_t *)FieldValue);
                    break;
                case 10: //sounds
                    if(ListX2FieldID == 0) //soundsSize
                        {
                        Entries.value[ListIndex]->RDSD.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].sound = *(FORMID *)FieldValue;
                            return true;
                        case 2: //flags
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].SetFlagMask(*(uint32_t *)FieldValue);
                            break;
                        case 3: //chance
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].chance = *(uint32_t *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                case 11: //weathers
                    if(ListX2FieldID == 0) //weathersSize
                        {
                        Entries.value[ListIndex]->RDWT.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].weather = *(FORMID *)FieldValue;
                            return true;
                        case 2: //chance
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].chance = *(uint32_t *)FieldValue;
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

void REGNRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENCLR defaultCLR;

    REGNRDAT defaultRDAT;

    REGNRPLD defaultRPLD;
    REGNRDOT defaultRDOT;
    REGNRDGS defaultRDGS;
    REGNRDSD defaultRDSD;
    REGNRDWT defaultRDWT;

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
        case 5: //iconPath
            ICON.Unload();
            return;
        case 6: //mapRed
            RCLR.value.red = defaultCLR.red;
            return;
        case 7: //mapGreen
            RCLR.value.green = defaultCLR.green;
            return;
        case 8: //mapBlue
            RCLR.value.blue = defaultCLR.blue;
            return;
        case 9: //unused1
            RCLR.value.unused1 = defaultCLR.unused1;
            return;
        case 10: //worldspace
            WNAM.Unload();
            return;
        case 11: //areas
            if(ListFieldID == 0) //areas
                {
                Areas.Unload();
                return;
                }

            if(ListIndex >= Areas.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //edgeFalloff
                    Areas.value[ListIndex]->RPLI.Unload();
                    return;
                case 2: //points
                    if(ListX2FieldID == 0) //points
                        {
                        Areas.value[ListIndex]->RPLD.Unload();
                        return;
                        }

                    if(ListX2Index >= Areas.value[ListIndex]->RPLD.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //posX
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posX = defaultRPLD.posX;
                            return;
                        case 2: //posY
                            Areas.value[ListIndex]->RPLD.value[ListX2Index].posY = defaultRPLD.posY;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 12: //entries
            if(ListFieldID == 0) //entries
                {
                Entries.Unload();
                return;
                }

            if(ListIndex >= Entries.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //entryType
                    Entries.value[ListIndex]->RDAT.value.entryType = defaultRDAT.entryType;
                    return;
                case 2: //flags
                    Entries.value[ListIndex]->RDAT.value.flags = defaultRDAT.flags;
                    return;
                case 3: //priority
                    Entries.value[ListIndex]->RDAT.value.priority = defaultRDAT.priority;
                    return;
                case 4: //unused1
                    Entries.value[ListIndex]->RDAT.value.unused1[0] = defaultRDAT.unused1[0];
                    Entries.value[ListIndex]->RDAT.value.unused1[1] = defaultRDAT.unused1[1];
                    return;
                case 5: //objects
                    if(ListX2FieldID == 0) //objects
                        {
                        Entries.value[ListIndex]->RDOT.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDOT.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //objectId
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].objectId = defaultRDOT.objectId;
                            return;
                        case 2: //parentIndex
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].parentIndex = defaultRDOT.parentIndex;
                            return;
                        case 3: //unused1
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[0] = defaultRDOT.unused1[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused1[1] = defaultRDOT.unused1[1];
                            return;
                        case 4: //density
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].density = defaultRDOT.density;
                            return;
                        case 5: //clustering
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].clustering = defaultRDOT.clustering;
                            return;
                        case 6: //minSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].minSlope = defaultRDOT.minSlope;
                            return;
                        case 7: //maxSlope
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxSlope = defaultRDOT.maxSlope;
                            return;
                        case 8: //flags
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].flags = defaultRDOT.flags;
                            return;
                        case 9: //radiusWRTParent
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radiusWRTParent = defaultRDOT.radiusWRTParent;
                            return;
                        case 10: //radius
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].radius = defaultRDOT.radius;
                            return;
                        case 11: //unk1
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[0] = defaultRDOT.unk1[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[1] = defaultRDOT.unk1[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[2] = defaultRDOT.unk1[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk1[3] = defaultRDOT.unk1[3];
                            return;
                        case 12: //maxHeight
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].maxHeight = defaultRDOT.maxHeight;
                            return;
                        case 13: //sink
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sink = defaultRDOT.sink;
                            return;
                        case 14: //sinkVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sinkVar = defaultRDOT.sinkVar;
                            return;
                        case 15: //sizeVar
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].sizeVar = defaultRDOT.sizeVar;
                            return;
                        case 16: //angleVarX
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarX = defaultRDOT.angleVarX;
                            return;
                        case 17: //angleVarY
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarY = defaultRDOT.angleVarY;
                            return;
                        case 18: //angleVarZ
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].angleVarZ = defaultRDOT.angleVarZ;
                            return;
                        case 19: //unused2
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[0] = defaultRDOT.unused2[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unused2[1] = defaultRDOT.unused2[1];
                            return;
                        case 20: //unk2
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[0] = defaultRDOT.unk2[0];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[1] = defaultRDOT.unk2[1];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[2] = defaultRDOT.unk2[2];
                            Entries.value[ListIndex]->RDOT.value[ListX2Index].unk2[3] = defaultRDOT.unk2[3];
                            return;
                        default:
                            return;
                        }
                    return;
                case 6: //mapName
                    Entries.value[ListIndex]->RDMP.Unload();
                    return;
                case 7: //iconPath
                    Entries.value[ListIndex]->ICON.Unload();
                    return;
                case 8: //grasses
                    if(ListX2FieldID == 0) //grasses
                        {
                        Entries.value[ListIndex]->RDGS.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDGS.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //grass
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].grass = defaultRDGS.grass;
                            return;
                        case 2: //unused1
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[0] = defaultRDGS.unused1[0];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[1] = defaultRDGS.unused1[1];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[2] = defaultRDGS.unused1[2];
                            Entries.value[ListIndex]->RDGS.value[ListX2Index].unused1[3] = defaultRDGS.unused1[3];
                            return;
                        default:
                            return;
                        }
                    return;
                case 9: //musicType
                    Entries.value[ListIndex]->RDMD.Unload();
                    return;
                case 10: //sounds
                    if(ListX2FieldID == 0) //sounds
                        {
                        Entries.value[ListIndex]->RDSD.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDSD.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //sound
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].sound = defaultRDSD.sound;
                            return;
                        case 2: //flags
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].flags = defaultRDSD.flags;
                            return;
                        case 3: //chance
                            Entries.value[ListIndex]->RDSD.value[ListX2Index].chance = defaultRDSD.chance;
                            return;
                        default:
                            return;
                        }
                    return;
                case 11: //weathers
                    if(ListX2FieldID == 0) //weathers
                        {
                        Entries.value[ListIndex]->RDWT.Unload();
                        return;
                        }

                    if(ListX2Index >= Entries.value[ListIndex]->RDWT.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //weather
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].weather = defaultRDWT.weather;
                            return;
                        case 2: //chance
                            Entries.value[ListIndex]->RDWT.value[ListX2Index].chance = defaultRDWT.chance;
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