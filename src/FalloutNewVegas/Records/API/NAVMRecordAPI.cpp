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
#include "..\NAVMRecord.h"

namespace FNV
{
uint32_t NAVMRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //version
            return CB_UINT32_FIELD;
        case 8: //cell
            return CB_FORMID_FIELD;
        case 9: //numVertices
            return CB_UINT32_FIELD;
        case 10: //numTriangles
            return CB_UINT32_FIELD;
        case 11: //numConnections
            return CB_UINT32_FIELD;
        case 12: //numUnknown
            return CB_UINT32_FIELD;
        case 13: //numDoors
            return CB_UINT32_FIELD;
        case 14: //vertices
            if(ListFieldID == 0) //vertices
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)NVVX.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= NVVX.value.size())
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
            return CB_UNKNOWN_FIELD;
        case 15: //triangles
            if(ListFieldID == 0) //triangles
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)NVTR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= NVTR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //vertex1
                    return CB_SINT16_FIELD;
                case 2: //vertex2
                    return CB_SINT16_FIELD;
                case 3: //vertex3
                    return CB_SINT16_FIELD;
                case 4: //edge1
                    return CB_SINT16_FIELD;
                case 5: //edge2
                    return CB_SINT16_FIELD;
                case 6: //edge3
                    return CB_SINT16_FIELD;
                case 7: //flags
                    return CB_UINT32_FLAG_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 16: //unknown1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_SINT16_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)NVCA.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //doors
            if(ListFieldID == 0) //doors
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)NVDP.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= NVDP.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //door
                    return CB_FORMID_FIELD;
                case 2: //unknown1
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
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //nvgd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return NVGD.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //connections
            if(ListFieldID == 0) //connections
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)NVEX.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= NVEX.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //unknown1
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
                case 2: //mesh
                    return CB_FORMID_FIELD;
                case 3: //triangle
                    return CB_UINT16_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 20: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * NAVMRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //version
            return &NVER.value;
        case 8: //cell
            return &DATA.value.cell;
        case 9: //numVertices
            return &DATA.value.numVertices;
        case 10: //numTriangles
            return &DATA.value.numTriangles;
        case 11: //numConnections
            return &DATA.value.numConnections;
        case 12: //numUnknown
            return &DATA.value.numNVCA;
        case 13: //numDoors
            return &DATA.value.numDoors;
        case 14: //vertices
            if(ListIndex >= NVVX.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //x
                    return &NVVX.value[ListIndex].x;
                case 2: //y
                    return &NVVX.value[ListIndex].y;
                case 3: //z
                    return &NVVX.value[ListIndex].z;
                default:
                    return NULL;
                }
            return NULL;
        case 15: //triangles
            if(ListIndex >= NVTR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //vertex1
                    return &NVTR.value[ListIndex].vertex1;
                case 2: //vertex2
                    return &NVTR.value[ListIndex].vertex2;
                case 3: //vertex3
                    return &NVTR.value[ListIndex].vertex3;
                case 4: //edge1
                    return &NVTR.value[ListIndex].edge1;
                case 5: //edge2
                    return &NVTR.value[ListIndex].edge2;
                case 6: //edge3
                    return &NVTR.value[ListIndex].edge3;
                case 7: //flags
                    return &NVTR.value[ListIndex].flags;
                default:
                    return NULL;
                }
            return NULL;
        case 16: //unknown1
            *FieldValues = NVCA.IsLoaded() ? &NVCA.value[0] : NULL;
            return NULL;
        case 17: //doors
            if(ListIndex >= NVDP.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //door
                    return &NVDP.value[ListIndex].door;
                case 2: //unknown1
                    return &NVDP.value[ListIndex].unknown1;
                case 3: //unused1
                    *FieldValues = &NVDP.value[ListIndex].unused1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 18: //nvgd_p
            *FieldValues = NVGD.value;
            return NULL;
        case 19: //connections
            if(ListIndex >= NVEX.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    *FieldValues = &NVEX.value[ListIndex].unknown1[0];
                    return NULL;
                case 2: //mesh
                    return &NVEX.value[ListIndex].mesh;
                case 3: //triangle
                    return &NVEX.value[ListIndex].triangle;
                default:
                    return NULL;
                }
            return NULL;
        case 20: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool NAVMRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //version
            NVER.value = *(uint32_t *)FieldValue;
            break;
        case 8: //cell
            DATA.value.cell = *(FORMID *)FieldValue;
            return true;
        case 9: //numVertices
            DATA.value.numVertices = *(uint32_t *)FieldValue;
            break;
        case 10: //numTriangles
            DATA.value.numTriangles = *(uint32_t *)FieldValue;
            break;
        case 11: //numConnections
            DATA.value.numConnections = *(uint32_t *)FieldValue;
            break;
        case 12: //numUnknown
            DATA.value.numNVCA = *(uint32_t *)FieldValue;
            break;
        case 13: //numDoors
            DATA.value.numDoors = *(uint32_t *)FieldValue;
            break;
        case 14: //vertices
            if(ListFieldID == 0) //verticesSize
                {
                NVVX.resize(ArraySize);
                DATA.value.numVertices = ArraySize;
                return false;
                }

            if(ListIndex >= NVVX.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //x
                    NVVX.value[ListIndex].x = *(float *)FieldValue;
                    break;
                case 2: //y
                    NVVX.value[ListIndex].y = *(float *)FieldValue;
                    break;
                case 3: //z
                    NVVX.value[ListIndex].z = *(float *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 15: //triangles
            if(ListFieldID == 0) //trianglesSize
                {
                NVTR.resize(ArraySize);
                DATA.value.numTriangles = ArraySize;
                return false;
                }

            if(ListIndex >= NVTR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //vertex1
                    NVTR.value[ListIndex].vertex1 = *(int16_t *)FieldValue;
                    break;
                case 2: //vertex2
                    NVTR.value[ListIndex].vertex2 = *(int16_t *)FieldValue;
                    break;
                case 3: //vertex3
                    NVTR.value[ListIndex].vertex3 = *(int16_t *)FieldValue;
                    break;
                case 4: //edge1
                    NVTR.value[ListIndex].edge1 = *(int16_t *)FieldValue;
                    break;
                case 5: //edge2
                    NVTR.value[ListIndex].edge2 = *(int16_t *)FieldValue;
                    break;
                case 6: //edge3
                    NVTR.value[ListIndex].edge3 = *(int16_t *)FieldValue;
                    break;
                case 7: //flags
                    NVTR.value[ListIndex].flags = *(uint32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 16: //unknown1
            NVCA.value.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                NVCA.value[x] = ((SINT16ARRAY)FieldValue)[x];
            DATA.value.numNVCA = ArraySize;
            break;
        case 17: //doors
            if(ListFieldID == 0) //doorsSize
                {
                NVDP.resize(ArraySize);
                DATA.value.numDoors = ArraySize;
                return false;
                }

            if(ListIndex >= NVDP.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //door
                    NVDP.value[ListIndex].door = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown1
                    NVDP.value[ListIndex].unknown1 = *(uint16_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 2)
                        break;
                    NVDP.value[ListIndex].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    NVDP.value[ListIndex].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                default:
                    break;
                }
            break;
        case 18: //nvgd_p
            NVGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 19: //connections
            if(ListFieldID == 0) //connectionsSize
                {
                NVEX.resize(ArraySize);
                DATA.value.numConnections = ArraySize;
                return false;
                }

            if(ListIndex >= NVEX.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    if(ArraySize != 4)
                        break;
                    NVEX.value[ListIndex].unknown1[0] = ((UINT8ARRAY)FieldValue)[0];
                    NVEX.value[ListIndex].unknown1[1] = ((UINT8ARRAY)FieldValue)[1];
                    NVEX.value[ListIndex].unknown1[2] = ((UINT8ARRAY)FieldValue)[2];
                    NVEX.value[ListIndex].unknown1[3] = ((UINT8ARRAY)FieldValue)[3];
                    break;
                case 2: //mesh
                    NVEX.value[ListIndex].mesh = *(FORMID *)FieldValue;
                    return true;
                case 3: //triangle
                    NVEX.value[ListIndex].triangle = *(uint16_t *)FieldValue;
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

void NAVMRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    NAVMDATA defaultDATA;
    NAVMVertex defaultNVVX;
    NAVMNVTR defaultNVTR;
    NAVMNVDP defaultNVDP;
    NAVMNVEX defaultNVEX;
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
        case 7: //version
            NVER.Unload();
            return;
        case 8: //cell
            DATA.value.cell = defaultDATA.cell;
            return;
        case 9: //numVertices
            DATA.value.numVertices = defaultDATA.numVertices;
            return;
        case 10: //numTriangles
            DATA.value.numTriangles = defaultDATA.numTriangles;
            return;
        case 11: //numConnections
            DATA.value.numConnections = defaultDATA.numConnections;
            return;
        case 12: //numUnknown
            DATA.value.numNVCA = defaultDATA.numNVCA;
            return;
        case 13: //numDoors
            DATA.value.numDoors = defaultDATA.numDoors;
            return;
        case 14: //vertices
            if(ListFieldID == 0) //verticesSize
                {
                NVVX.Unload();
                return;
                }

            if(ListIndex >= NVVX.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //x
                    NVVX.value[ListIndex].x = defaultNVVX.x;
                    return;
                case 2: //y
                    NVVX.value[ListIndex].y = defaultNVVX.y;
                    return;
                case 3: //z
                    NVVX.value[ListIndex].z = defaultNVVX.z;
                    return;
                default:
                    return;
                }
            return;
        case 15: //triangles
            if(ListFieldID == 0) //trianglesSize
                {
                NVTR.Unload();
                return;
                }

            if(ListIndex >= NVTR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //vertex1
                    NVTR.value[ListIndex].vertex1 = defaultNVTR.vertex1;
                    return;
                case 2: //vertex2
                    NVTR.value[ListIndex].vertex2 = defaultNVTR.vertex2;
                    return;
                case 3: //vertex3
                    NVTR.value[ListIndex].vertex3 = defaultNVTR.vertex3;
                    return;
                case 4: //edge1
                    NVTR.value[ListIndex].edge1 = defaultNVTR.edge1;
                    return;
                case 5: //edge2
                    NVTR.value[ListIndex].edge2 = defaultNVTR.edge2;
                    return;
                case 6: //edge3
                    NVTR.value[ListIndex].edge3 = defaultNVTR.edge3;
                    return;
                case 7: //flags
                    NVTR.value[ListIndex].flags = defaultNVTR.flags;
                    return;
                default:
                    return;
                }
            return;
        case 16: //unknown1
            NVCA.Unload();
            return;
        case 17: //doors
            if(ListFieldID == 0) //doorsSize
                {
                NVDP.Unload();
                return;
                }

            if(ListIndex >= NVDP.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //door
                    NVDP.value[ListIndex].door = defaultNVDP.door;
                    return;
                case 2: //unknown1
                    NVDP.value[ListIndex].unknown1 = defaultNVDP.unknown1;
                    return;
                case 3: //unused1
                    NVDP.value[ListIndex].unused1[0] = defaultNVDP.unused1[0];
                    NVDP.value[ListIndex].unused1[1] = defaultNVDP.unused1[1];
                    return;
                default:
                    return;
                }
            return;
        case 18: //nvgd_p
            NVGD.Unload();
            return;
        case 19: //connections
            if(ListFieldID == 0) //connectionsSize
                {
                NVEX.Unload();
                return;
                }

            if(ListIndex >= NVEX.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //unknown1
                    NVEX.value[ListIndex].unknown1[0] = defaultNVEX.unknown1[0];
                    NVEX.value[ListIndex].unknown1[1] = defaultNVEX.unknown1[1];
                    NVEX.value[ListIndex].unknown1[2] = defaultNVEX.unknown1[2];
                    NVEX.value[ListIndex].unknown1[3] = defaultNVEX.unknown1[3];
                    return;
                case 2: //mesh
                    NVEX.value[ListIndex].mesh = defaultNVEX.mesh;
                    return;
                case 3: //triangle
                    NVEX.value[ListIndex].triangle = defaultNVEX.triangle;
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