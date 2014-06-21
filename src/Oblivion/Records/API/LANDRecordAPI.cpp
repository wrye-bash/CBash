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
#include "..\LANDRecord.h"

namespace Ob
{
uint32_t LANDRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    //normals, heights, and colors are accessed as if they were a list of lists
    //They aren't true lists, but rather 33x33 arrays
    //So there are some inconsistencies when compared to true lists of lists
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
        case 5: //data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DATA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 6: //normals
            if(ListFieldID == 0) //normals
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListX2FieldID == 0) //normals
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= 33)
                return CB_UNKNOWN_FIELD;

            if(ListX2Index >= 33)
                return CB_UNKNOWN_FIELD;

            switch(ListX2FieldID)
                {
                case 1: //x
                    return CB_UINT8_FIELD;
                case 2: //y
                    return CB_UINT8_FIELD;
                case 3: //z
                    return CB_UINT8_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 7: //heightOffset
            return CB_FLOAT32_FIELD;
        case 8: //heights
            if(ListFieldID == 0) //heights
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListX2FieldID == 0) //heights
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= 33)
                return CB_UNKNOWN_FIELD;

            if(ListX2Index >= 33)
                return CB_UNKNOWN_FIELD;

            switch(ListX2FieldID)
                {
                case 1: //height
                    return CB_SINT8_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 9: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return VHGT.IsLoaded() ? 3 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //colors
            if(ListFieldID == 0) //colors
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListX2FieldID == 0) //colors
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= 33)
                return CB_UNKNOWN_FIELD;

            if(ListX2Index >= 33)
                return CB_UNKNOWN_FIELD;

            switch(ListX2FieldID)
                {
                case 1: //red
                    return CB_UINT8_FIELD;
                case 2: //green
                    return CB_UINT8_FIELD;
                case 3: //blue
                    return CB_UINT8_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //baseTextures
            if(ListFieldID == 0) //baseTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)BTXT.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= BTXT.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //texture
                    return CB_FORMID_FIELD;
                case 2: //quadrant
                    return CB_SINT8_FIELD;
                case 3: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 1;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 4: //layer
                    return CB_SINT16_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 12: //alphaLayers
            if(ListFieldID == 0) //alphaLayers
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Layers.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Layers.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //texture
                    return CB_FORMID_FIELD;
                case 2: //quadrant
                    return CB_SINT8_FIELD;
                case 3: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 1;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 4: //layer
                    return CB_SINT16_FIELD;
                case 5: //opacities
                    if(ListX2FieldID == 0) //opacities
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Layers.value[ListIndex]->VTXT.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }

                    if(ListX2Index >= Layers.value[ListIndex]->VTXT.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
                        {
                        case 1: //position
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
                        case 3: //opacity
                            return CB_FLOAT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 13: //vertexTextures
            if(ListFieldID == 0) //vertexTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)VTEX.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= VTEX.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //texture
                    return CB_FORMID_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //Position
            if(ListFieldID == 0) //Position
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListX2FieldID == 0) //Position
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return ListIndex < 33 ? 33 : 0;
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= 33)
                return CB_UNKNOWN_FIELD;

            if(ListX2Index >= 33)
                return CB_UNKNOWN_FIELD;

            switch(ListX2FieldID)
                {
                case 1: //height
                    return CB_FLOAT32_FIELD;
                case 2: //normalX
                    return CB_UINT8_FIELD;
                case 3: //normalY
                    return CB_UINT8_FIELD;
                case 4: //normalZ
                    return CB_UINT8_FIELD;
                case 5: //red
                    return CB_UINT8_FIELD;
                case 6: //green
                    return CB_UINT8_FIELD;
                case 7: //blue
                    return CB_UINT8_FIELD;
                case 8: //baseTexture
                    return CB_FORMID_FIELD;
                case 9: //alphaLayer1Texture
                    return CB_FORMID_FIELD;
                case 10: //alphaLayer1Opacity
                    return CB_FLOAT32_FIELD;
                case 11: //alphaLayer2Texture
                    return CB_FORMID_FIELD;
                case 12: //alphaLayer2Opacity
                    return CB_FLOAT32_FIELD;
                case 13: //alphaLayer3Texture
                    return CB_FORMID_FIELD;
                case 14: //alphaLayer3Opacity
                    return CB_FLOAT32_FIELD;
                case 15: //alphaLayer4Texture
                    return CB_FORMID_FIELD;
                case 16: //alphaLayer4Opacity
                    return CB_FLOAT32_FIELD;
                case 17: //alphaLayer5Texture
                    return CB_FORMID_FIELD;
                case 18: //alphaLayer5Opacity
                    return CB_FLOAT32_FIELD;
                case 19: //alphaLayer6Texture
                    return CB_FORMID_FIELD;
                case 20: //alphaLayer6Opacity
                    return CB_FLOAT32_FIELD;
                case 21: //alphaLayer7Texture
                    return CB_FORMID_FIELD;
                case 22: //alphaLayer7Opacity
                    return CB_FLOAT32_FIELD;
                case 23: //alphaLayer8Texture
                    return CB_FORMID_FIELD;
                case 24: //alphaLayer8Opacity
                    return CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        case 15: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * LANDRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    uint8_t  curQuadrant;
    uint16_t curPosition;
    static float fRetValue;

    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 5: //data
            *FieldValues = DATA.value;
            return NULL;
        case 6: //normals
            if(ListIndex >= 33)
                return NULL;

            if(ListX2Index >= 33)
                return NULL;

            switch(ListX2FieldID)
                {
                case 1: //x
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].x : NULL;
                case 2: //y
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].y : NULL;
                case 3: //z
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].z : NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 7: //heightOffset
            return VHGT.IsLoaded() ? &VHGT->offset : NULL;
        case 8: //heights
            if(ListIndex >= 33)
                return NULL;

            if(ListX2Index >= 33)
                return NULL;

            switch(ListX2FieldID)
                {
                case 1: //height
                    return VHGT.IsLoaded() ? &VHGT->VHGT[ListIndex][ListX2Index] : NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 9: //unused1
            *FieldValues = VHGT.IsLoaded() ? &VHGT->unused1[0] : NULL;
            return NULL;
        case 10: //colors
            if(ListIndex >= 33)
                return NULL;

            if(ListX2Index >= 33)
                return NULL;

            switch(ListX2FieldID)
                {
                case 1: //red
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].red : NULL;
                case 2: //green
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].green : NULL;
                case 3: //blue
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].blue : NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 11: //baseTextures
            if(ListIndex >= BTXT.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //texture
                    return &BTXT.value[ListIndex]->texture;
                case 2: //quadrant
                    return &BTXT.value[ListIndex]->quadrant;
                case 3: //unused1
                    *FieldValues = &BTXT.value[ListIndex]->unused1;
                    return NULL;
                case 4: //layer
                    return &BTXT.value[ListIndex]->layer;
                default:
                    return NULL;
                }
            return NULL;
        case 12: //alphaLayers
            if(ListIndex >= Layers.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //texture
                    return &Layers.value[ListIndex]->ATXT.value.texture;
                case 2: //quadrant
                    return &Layers.value[ListIndex]->ATXT.value.quadrant;
                case 3: //unused1
                    *FieldValues = &Layers.value[ListIndex]->ATXT.value.unused1;
                    return NULL;
                case 4: //layer
                    return &Layers.value[ListIndex]->ATXT.value.layer;
                case 5: //opacities
                    if(ListX2Index >= Layers.value[ListIndex]->VTXT.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //position
                            return &Layers.value[ListIndex]->VTXT.value[ListX2Index].position;
                        case 2: //unused1
                            *FieldValues = &Layers.value[ListIndex]->VTXT.value[ListX2Index].unused1[0];
                            return NULL;
                        case 3: //opacity
                            return &Layers.value[ListIndex]->VTXT.value[ListX2Index].opacity;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 13: //vertexTextures
            if(ListIndex >= VTEX.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //texture
                    return &VTEX.value[ListFieldID];
                default:
                    return NULL;
                }
            return NULL;
        case 14: //Position
            if(ListIndex >= 33)
                return NULL;

            if(ListX2Index >= 33)
                return NULL;

            switch(ListX2FieldID)
                {
                case 1: //height
                    if(VHGT.IsLoaded())
                        {
                        fRetValue = CalcHeight(ListIndex, ListX2Index);
                        return &fRetValue;
                        }
                    return NULL;
                case 2: //normalX
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].x : NULL;
                case 3: //normalY
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].y : NULL;
                case 4: //normalZ
                    return VNML.IsLoaded() ? &VNML->VNML[ListIndex][ListX2Index].z : NULL;
                case 5: //red
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].red : NULL;
                case 6: //green
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].green : NULL;
                case 7: //blue
                    return VCLR.IsLoaded() ? &VCLR->VCLR[ListIndex][ListX2Index].blue : NULL;
                case 8: //baseTexture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < BTXT.value.size(); ++x)
                        if(BTXT.value[x]->quadrant == curQuadrant)
                            return &BTXT.value[x]->texture;
                    return NULL;
                case 9: //alphaLayer1Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 10: //alphaLayer1Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 11: //alphaLayer2Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 12: //alphaLayer2Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 13: //alphaLayer3Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 14: //alphaLayer3Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 15: //alphaLayer4Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 16: //alphaLayer4Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 17: //alphaLayer5Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 18: //alphaLayer5Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 19: //alphaLayer6Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 20: //alphaLayer6Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 21: //alphaLayer7Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 22: //alphaLayer7Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                case 23: //alphaLayer8Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            return &Layers.value[x]->ATXT.value.texture;
                    return NULL;
                case 24: //alphaLayer8Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    return &Layers.value[x]->VTXT.value[y].opacity;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 15: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool LANDRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    int8_t    newOffset;
    uint8_t    curQuadrant;
    uint16_t   curPosition;
    LANDVTXT curVTXT;
    LANDGENTXT *curTexture;
    LANDLAYERS *curLayer;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 5: //data
            DATA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 6: //normals
            if(ListFieldID == 0) //normalsSize, not really a list so it can't be resized
                break;

            if(ListIndex >= 33)
                break;

            if(ListX2Index >= 33)
                break;

            switch(ListX2FieldID)
                {
                case 1: //x
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].x = *(uint8_t *)FieldValue;
                    break;
                case 2: //y
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].y = *(uint8_t *)FieldValue;
                    break;
                case 3: //z
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].z = *(uint8_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 7: //heightOffset
            VHGT.Load();
            VHGT->offset = *(float *)FieldValue;
            break;
        case 8: //heights
            if(ListFieldID == 0) //heightsSize, not really a list so it can't be resized
                break;

            if(ListIndex >= 33)
                break;

            if(ListX2Index >= 33)
                break;

            switch(ListX2FieldID)
                {
                case 1: //height
                    VHGT.Load();
                    VHGT->VHGT[ListIndex][ListX2Index] = *(int8_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 9: //unused1
            if(ArraySize != 3)
                break;
            VHGT.Load();
            VHGT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            VHGT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            VHGT->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 10: //colors
            if(ListFieldID == 0) //colorsSize, not really a list so it can't be resized
                break;

            if(ListIndex >= 33)
                break;

            if(ListX2Index >= 33)
                break;

            switch(ListX2FieldID)
                {
                case 1: //red
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].red = *(uint8_t *)FieldValue;
                    break;
                case 2: //green
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].green = *(uint8_t *)FieldValue;
                    break;
                case 3: //blue
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].blue = *(uint8_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 11: //baseTextures
            if(ListFieldID == 0) //baseTexturesSize
                {
                BTXT.resize(ArraySize);
                return false;
                }

            if(ListIndex >= BTXT.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //texture
                    BTXT.value[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 2: //quadrant
                    BTXT.value[ListIndex]->quadrant = *(uint8_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 1)
                        break;
                    BTXT.value[ListIndex]->unused1 = ((UINT8ARRAY)FieldValue)[0];
                    break;
                case 4: //layer
                    BTXT.value[ListIndex]->layer = *(int16_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 12: //alphaLayers
            if(ListFieldID == 0) //alphaLayersSize
                {
                Layers.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Layers.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //texture
                    Layers.value[ListIndex]->ATXT.value.texture = *(FORMID *)FieldValue;
                    return true;
                case 2: //quadrant
                    Layers.value[ListIndex]->ATXT.value.quadrant = *(uint8_t *)FieldValue;
                    break;
                case 3: //unused1
                    if(ArraySize != 1)
                        break;
                    Layers.value[ListIndex]->ATXT.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
                    break;
                case 4: //layer
                    Layers.value[ListIndex]->ATXT.value.layer = *(int16_t *)FieldValue;
                    break;
                case 5: //opacities
                    if(ListX2Index >= Layers.value[ListIndex]->VTXT.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //position
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].position = *(uint16_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 2)
                                break;
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            break;
                        case 3: //opacity
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].opacity = *(float *)FieldValue;
                            break;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 13: //vertexTextures
            if(ListFieldID == 0) //vertexTexturesSize
                {
                VTEX.resize(ArraySize);
                return false;
                }

            if(ListIndex >= VTEX.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //texture
                    VTEX.value[ListIndex] = *(FORMID *)FieldValue;
                    return true;
                default:
                    break;
                }
            break;
        case 14: //Position
            if(ListFieldID == 0) //PositionSize, not really a list so can't resize
                break;

            if(ListIndex >= 33)
                break;

            if(ListX2Index >= 33)
                break;

            switch(ListX2FieldID)
                {
                case 1: //height
                    //Changing height is tricky because the co-ords to the east and possibly north have to be updated as well
                    //These other co-ords may be in other cells.  Example: the corners of the cell must update four different VHGT records
                    //If any of the cells happen to be 0,0, then the baseHeight offset of that cell must be changed instead
                    //The borders of the cells must match the height of the surrounding cells or there will be visual tearing
                    VHGT.Load();
                    newOffset = (int8_t)((*(float *)FieldValue - CalcHeight(ListIndex, ListX2Index)) / 8.0f);

                    //Set the co-ords to the proper offset.  If the co-ords are 0,0, then change the baseHeight offset instead
                    if(ListIndex == 0 && ListX2Index == 0)
                        {
                        VHGT->VHGT[0][0] = 0;
                        VHGT->offset = *(float *)FieldValue;
                        }
                    else
                        VHGT->VHGT[ListIndex][ListX2Index] += newOffset;

                    //Update the co-ords to the east
                    if(ListX2Index == 32) //the co-ords to update are in the next cell to the east
                        {
                        if(ListIndex == 0)
                            {
                            //At a corner, so update the three overlapped cells
                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->VHGT->offset) / 8.0f);
                                EastLand->VHGT->VHGT[0][0] = 0;
                                EastLand->VHGT->offset = *(float *)FieldValue;
                                EastLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(EastLand != NULL && EastLand->SouthLand != NULL)
                                {
                                EastLand->SouthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->SouthLand->CalcHeight(32, 0)) / 8.0f);
                                EastLand->SouthLand->VHGT->VHGT[32][0] += newOffset;
                                EastLand->SouthLand->VHGT->VHGT[32][1] -= newOffset;
                                }
                            else if(SouthLand != NULL && SouthLand->EastLand != NULL)
                                {
                                SouthLand->EastLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - SouthLand->EastLand->CalcHeight(32, 0)) / 8.0f);
                                SouthLand->EastLand->VHGT->VHGT[32][0] += newOffset;
                                SouthLand->EastLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            if(SouthLand != NULL)
                                {
                                SouthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - SouthLand->CalcHeight(32, 32)) / 8.0f);
                                SouthLand->VHGT->VHGT[32][32] += newOffset;
                                }
                            }
                        else if(ListIndex == 32)
                            {
                            //At a corner, so update the three overlapped cells
                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->CalcHeight(32, 0)) / 8.0f);
                                EastLand->VHGT->VHGT[32][0] += newOffset;
                                EastLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            //Two ways of getting to the same cell
                            if(EastLand != NULL && EastLand->NorthLand != NULL)
                                {
                                EastLand->NorthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->NorthLand->VHGT->offset) / 8.0f);
                                EastLand->NorthLand->VHGT->VHGT[0][0] = 0;
                                EastLand->NorthLand->VHGT->offset = *(float *)FieldValue;
                                EastLand->NorthLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->NorthLand->VHGT->VHGT[1][0] -= newOffset;
                                }
                            else if(NorthLand != NULL && NorthLand->EastLand != NULL)
                                {
                                NorthLand->EastLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - NorthLand->EastLand->VHGT->offset) / 8.0f);
                                NorthLand->EastLand->VHGT->VHGT[0][0] = 0;
                                NorthLand->EastLand->VHGT->offset = *(float *)FieldValue;
                                NorthLand->EastLand->VHGT->VHGT[0][1] -= newOffset;
                                NorthLand->EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(NorthLand != NULL)
                                {
                                NorthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - NorthLand->CalcHeight(0, 32)) / 8.0f);
                                NorthLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            }
                        else
                            {
                            //In between the corners of the eastern edge, so update overlapped cell
                            if(EastLand != NULL)
                                {
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->CalcHeight(ListIndex, 0)) / 8.0f);
                                EastLand->VHGT->VHGT[ListIndex][0] += newOffset;

                                //Then, update the co-ords to the east and north.
                                EastLand->VHGT->VHGT[ListIndex][1] -= newOffset;
                                EastLand->VHGT->VHGT[ListIndex + 1][0] -= newOffset;
                                }
                            }
                        }
                    //Update the co-ords to the north, if needed
                    else if(ListX2Index == 0) //first column is offset by the values to the south
                        {
                        if(ListIndex == 0)
                            {
                            VHGT->VHGT[0][1] -= newOffset;
                            VHGT->VHGT[1][0] -= newOffset;

                            //At a corner, so update the three overlapped cells
                            if(SouthLand != NULL)
                                {
                                SouthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - SouthLand->CalcHeight(32, 0)) / 8.0f);
                                SouthLand->VHGT->VHGT[32][0] += newOffset;
                                SouthLand->VHGT->VHGT[32][1] -= newOffset;
                                }

                            if(SouthLand != NULL && SouthLand->WestLand != NULL)
                                {
                                SouthLand->WestLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - SouthLand->WestLand->CalcHeight(32, 32)) / 8.0f);
                                SouthLand->WestLand->VHGT->VHGT[32][32] += newOffset;
                                }
                            else if(WestLand != NULL && WestLand->SouthLand != NULL)
                                {
                                WestLand->SouthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - WestLand->SouthLand->CalcHeight(32, 32)) / 8.0f);
                                WestLand->SouthLand->VHGT->VHGT[32][32] += newOffset;
                                }

                            if(WestLand != NULL)
                                {
                                WestLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - WestLand->CalcHeight(0, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[0][32] += newOffset;
                                }

                            if(EastLand != NULL)
                                {
                                EastLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - EastLand->VHGT->offset) / 8.0f);
                                EastLand->VHGT->VHGT[0][0] = 0;
                                EastLand->VHGT->offset = *(float *)FieldValue;
                                EastLand->VHGT->VHGT[0][1] -= newOffset;
                                EastLand->VHGT->VHGT[1][0] -= newOffset;
                                }
                            }
                        else if(ListIndex == 32)
                            {
                            VHGT->VHGT[32][1] -= newOffset;

                            //At a corner, so update the three overlapped cells
                            if(WestLand != NULL)
                                {
                                WestLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - WestLand->CalcHeight(32, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[32][32] += newOffset;
                                }

                            if(NorthLand != NULL)
                                {
                                NorthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - NorthLand->VHGT->offset) / 8.0f);
                                NorthLand->VHGT->VHGT[0][0] = 0;
                                NorthLand->VHGT->offset = *(float *)FieldValue;
                                NorthLand->VHGT->VHGT[0][1] -= newOffset;
                                NorthLand->VHGT->VHGT[1][0] -= newOffset;
                                }

                            if(NorthLand != NULL && NorthLand->WestLand != NULL)
                                {
                                NorthLand->WestLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - NorthLand->WestLand->CalcHeight(0, 32)) / 8.0f);
                                NorthLand->WestLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            else if(WestLand != NULL && WestLand->NorthLand != NULL)
                                {
                                WestLand->NorthLand->VHGT.Load();
                                newOffset = (int8_t)((*(float *)FieldValue - WestLand->NorthLand->CalcHeight(0, 32)) / 8.0f);
                                WestLand->NorthLand->VHGT->VHGT[0][32] += newOffset;
                                }
                            }
                        else
                            {
                            VHGT->VHGT[ListIndex][1] -= newOffset;
                            VHGT->VHGT[ListIndex + 1][0] -= newOffset;
                            //In between the corners of the western edge, so update overlapped cell
                            if(WestLand != NULL)
                                {
                                newOffset = (int8_t)((*(float *)FieldValue - WestLand->CalcHeight(ListIndex, 32)) / 8.0f);
                                WestLand->VHGT->VHGT[ListIndex][32] += newOffset;
                                }
                            }
                        }
                    //Update the co-ords to the south, if needed
                    else if(ListIndex == 0)
                        {
                        VHGT->VHGT[0][ListX2Index + 1] -= newOffset;
                        //In between the corners of the western edge, so update overlapped cell
                        if(SouthLand != NULL)
                            {
                            newOffset = (int8_t)((*(float *)FieldValue - SouthLand->CalcHeight(32, ListX2Index)) / 8.0f);
                            SouthLand->VHGT->VHGT[32][ListX2Index] += newOffset;
                            SouthLand->VHGT->VHGT[32][ListX2Index + 1] -= newOffset;
                            }
                        }
                    //Update the co-ords to the north, if needed
                    else if(ListIndex == 32)
                        {
                        VHGT->VHGT[0][ListX2Index + 1] -= newOffset;
                        //In between the corners of the western edge, so update overlapped cell
                        if(NorthLand != NULL)
                            {
                            newOffset = (int8_t)((*(float *)FieldValue - NorthLand->CalcHeight(0, ListX2Index)) / 8.0f);
                            NorthLand->VHGT->VHGT[0][ListX2Index] += newOffset;
                            NorthLand->VHGT->VHGT[0][ListX2Index + 1] -= newOffset;
                            }
                        }
                    else //the co-ords are contained within the cell
                        VHGT->VHGT[ListIndex][ListX2Index + 1] -= newOffset;
                    break;
                case 2: //normalX
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].x = *(uint8_t *)FieldValue;
                    break;
                case 3: //normalY
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].y = *(uint8_t *)FieldValue;
                    break;
                case 4: //normalZ
                    VNML.Load();
                    VNML->VNML[ListIndex][ListX2Index].z = *(uint8_t *)FieldValue;
                    break;
                case 5: //red
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].red = *(uint8_t *)FieldValue;
                    break;
                case 6: //green
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].green = *(uint8_t *)FieldValue;
                    break;
                case 7: //blue
                    VCLR.Load();
                    VCLR->VCLR[ListIndex][ListX2Index].blue = *(uint8_t *)FieldValue;
                    break;
                case 8: //baseTexture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < BTXT.value.size(); ++x)
                        if(BTXT.value[x]->quadrant == curQuadrant)
                            {
                            BTXT.value[x]->texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    //No existing BTXT, so make one if able
                    if(BTXT.value.size() > 3)
                        break;
                    curTexture = new LANDGENTXT;
                    curTexture->layer = -1;
                    curTexture->quadrant = curQuadrant;
                    curTexture->texture = *(FORMID *)FieldValue;
                    BTXT.value.push_back(curTexture);
                    return true;
                case 9: //alphaLayer1Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 0;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 10: //alphaLayer1Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    break;
                case 11: //alphaLayer2Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 1;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 12: //alphaLayer2Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 13: //alphaLayer3Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 2;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 14: //alphaLayer3Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 15: //alphaLayer4Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 3;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 16: //alphaLayer4Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 17: //alphaLayer5Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 4;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 18: //alphaLayer5Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 19: //alphaLayer6Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 5;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 20: //alphaLayer6Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 21: //alphaLayer7Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 6;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 22: //alphaLayer7Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                case 23: //alphaLayer8Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            {
                            Layers.value[x]->ATXT.value.texture = *(FORMID *)FieldValue;
                            return true;
                            }
                    curLayer = new LANDLAYERS;
                    curLayer->ATXT.value.layer = 7;
                    curLayer->ATXT.value.quadrant = curQuadrant;
                    curLayer->ATXT.value.texture = *(FORMID *)FieldValue;
                    Layers.value.push_back(curLayer);
                    return true;
                case 24: //alphaLayer8Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = *(float *)FieldValue;
                                    return false;
                                    }
                    //No existing VTXT, so make one
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            {
                            curVTXT.position = curPosition;
                            curVTXT.opacity = *(float *)FieldValue;
                            Layers.value[x]->VTXT.value.push_back(curVTXT);
                            return false;
                            }
                    //No existing ATXT, so do nothing
                    return false;
                default:
                    break;
                }
            break;
        default:
            break;
        }
    return false;
    }

void LANDRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LANDNORMALS defaultVNML;
    LANDVHGT defaultVHGT;
    LANDVCLR defaultVCLR;
    LANDGENTXT defaultGENTXT;
    LANDVTXT defaultVTXT;

    uint8_t  curQuadrant;
    uint16_t curPosition;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 5: //data
            DATA.Unload();
            return;
        case 6: //normals
            if(ListFieldID == 0) //normalsSize
                {
                VNML.Unload();
                return;
                }

            if(ListIndex >= 33)
                return;

            if(ListX2FieldID == 0) //normalsSize
                {
                if(VNML.IsLoaded())
                    {
                    for(uint32_t x = 0; x < 33; ++x)
                        {
                        VNML->VNML[ListIndex][x].x = defaultVNML.x;
                        VNML->VNML[ListIndex][x].y = defaultVNML.y;
                        VNML->VNML[ListIndex][x].z = defaultVNML.z;
                        }
                    }
                return;
                }

            if(ListX2Index >= 33)
                return;

            switch(ListX2FieldID)
                {
                case 1: //x
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].x = defaultVNML.x;
                    return;
                case 2: //y
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].y = defaultVNML.y;
                    return;
                case 3: //z
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].z = defaultVNML.z;
                    return;
                default:
                    return;
                }
            return;
        case 7: //heightOffset
            if(VHGT.IsLoaded())
                VHGT->offset = defaultVHGT.offset;
            return;
        case 8: //heights
            if(ListFieldID == 0) //heightsSize
                {
                VHGT.Unload();
                return;
                }

            if(ListIndex >= 33)
                return;

            if(ListX2FieldID == 0) //heightsSize
                {
                if(VHGT.IsLoaded())
                    for(uint32_t x = 0; x < 33; ++x)
                        VHGT->VHGT[ListIndex][x] = defaultVHGT.VHGT[ListIndex][x];
                return;
                }

            if(ListX2Index >= 33)
                return;

            switch(ListX2FieldID)
                {
                case 1: //height
                    if(VHGT.IsLoaded())
                        VHGT->VHGT[ListIndex][ListX2Index] = defaultVHGT.VHGT[ListIndex][ListX2Index];
                    return;
                default:
                    return;
                }
            return;
        case 9: //unused1
            if(VHGT.IsLoaded())
                {
                VHGT->unused1[0] = defaultVHGT.unused1[0];
                VHGT->unused1[1] = defaultVHGT.unused1[1];
                VHGT->unused1[2] = defaultVHGT.unused1[2];
                }
            return;
        case 10: //colors
            if(ListFieldID == 0) //colorsSize, not really a list so it can't be resized
                {
                VCLR.Unload();
                return;
                }

            if(ListIndex >= 33)
                return;

            if(ListX2FieldID == 0) //heightsSize
                {
                if(VCLR.IsLoaded())
                    for(uint32_t x = 0; x < 33; ++x)
                        {
                        VCLR->VCLR[ListIndex][x].red = defaultVCLR.VCLR[ListIndex][x].red;
                        VCLR->VCLR[ListIndex][x].green = defaultVCLR.VCLR[ListIndex][x].green;
                        VCLR->VCLR[ListIndex][x].blue = defaultVCLR.VCLR[ListIndex][x].blue;
                        }
                return;
                }

            if(ListX2Index >= 33)
                return;

            switch(ListX2FieldID)
                {
                case 1: //red
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].red = defaultVCLR.VCLR[ListIndex][ListX2Index].red;
                    return;
                case 2: //green
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].green = defaultVCLR.VCLR[ListIndex][ListX2Index].green;
                    return;
                case 3: //blue
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].blue = defaultVCLR.VCLR[ListIndex][ListX2Index].blue;
                    return;
                default:
                    return;
                }
            return;
        case 11: //baseTextures
            if(ListFieldID == 0) //baseTexturesSize
                {
                BTXT.Unload();
                return;
                }

            if(ListIndex >= BTXT.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //texture
                    BTXT.value[ListIndex]->texture = defaultGENTXT.texture;
                    return;
                case 2: //quadrant
                    BTXT.value[ListIndex]->quadrant = defaultGENTXT.quadrant;
                    return;
                case 3: //unused1
                    BTXT.value[ListIndex]->unused1 = defaultGENTXT.unused1;
                    return;
                case 4: //layer
                    BTXT.value[ListIndex]->layer = defaultGENTXT.layer;
                    return;
                default:
                    return;
                }
            return;
        case 12: //alphaLayers
            if(ListFieldID == 0) //alphaLayersSize
                {
                Layers.Unload();
                return;
                }

            if(ListIndex >= Layers.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //texture
                    if(Layers.value[ListIndex]->ATXT.IsLoaded())
                        Layers.value[ListIndex]->ATXT.value.texture = defaultGENTXT.texture;
                    return;
                case 2: //quadrant
                    if(Layers.value[ListIndex]->ATXT.IsLoaded())
                        Layers.value[ListIndex]->ATXT.value.quadrant = defaultGENTXT.quadrant;
                    return;
                case 3: //unused1
                    if(Layers.value[ListIndex]->ATXT.IsLoaded())
                        Layers.value[ListIndex]->ATXT.value.unused1 = defaultGENTXT.unused1;
                    return;
                case 4: //layer
                    if(Layers.value[ListIndex]->ATXT.IsLoaded())
                        Layers.value[ListIndex]->ATXT.value.layer = defaultGENTXT.layer;
                    return;
                case 5: //opacities
                    if(ListFieldID == 0) //opacitiesSize
                        {
                        Layers.value[ListIndex]->VTXT.Unload();
                        return;
                        }

                    if(ListX2Index >= Layers.value[ListIndex]->VTXT.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //position
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].position = defaultVTXT.position;
                            return;
                        case 2: //unused1
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].unused1[0] = defaultVTXT.unused1[0];
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].unused1[1] = defaultVTXT.unused1[1];
                            return;
                        case 3: //opacity
                            Layers.value[ListIndex]->VTXT.value[ListX2Index].opacity = defaultVTXT.opacity;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 13: //vertexTextures
            if(ListFieldID == 0) //vertexTexturesSize
                {
                VTEX.Unload();
                return;
                }

            if(ListIndex >= VTEX.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //texture
                    VTEX.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 14: //Position

            if(ListIndex >= 33)
                return;

            if(ListX2Index >= 33)
                return;

            if(ListX2FieldID == 0) //PositionSize
                {
                for(uint32_t x = 1; x <= 24; ++x)
                    DeleteField(FieldID, ListIndex, ListFieldID, ListX2Index, x, ListX3Index, ListX3FieldID);
                return;
                }

            switch(ListX2FieldID)
                {
                case 1: //height
                    SetField(FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID, &defaultVHGT.VHGT[ListIndex][ListX2Index], 0);
                    return;
                case 2: //normalX
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].x = defaultVNML.x;
                    return;
                case 3: //normalY
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].y = defaultVNML.y;
                    return;
                case 4: //normalZ
                    if(VNML.IsLoaded())
                        VNML->VNML[ListIndex][ListX2Index].z = defaultVNML.z;
                    return;
                case 5: //red
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].red = defaultVCLR.VCLR[ListIndex][ListX2Index].red;
                    return;
                case 6: //green
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].green = defaultVCLR.VCLR[ListIndex][ListX2Index].green;
                    return;
                case 7: //blue
                    if(VCLR.IsLoaded())
                        VCLR->VCLR[ListIndex][ListX2Index].blue = defaultVCLR.VCLR[ListIndex][ListX2Index].blue;
                    return;
                case 8: //baseTexture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < BTXT.value.size(); ++x)
                        if(BTXT.value[x]->quadrant == curQuadrant)
                            {
                            BTXT.value[x]->texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing BTXT, so nothing to do
                    return;
                case 9: //alphaLayer1Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 10: //alphaLayer1Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 0)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 11: //alphaLayer2Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 12: //alphaLayer2Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 1)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 13: //alphaLayer3Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 14: //alphaLayer3Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 2)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 15: //alphaLayer4Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 16: //alphaLayer4Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 3)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 17: //alphaLayer5Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 18: //alphaLayer5Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 4)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 19: //alphaLayer6Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 20: //alphaLayer6Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 5)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 21: //alphaLayer7Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 22: //alphaLayer7Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 6)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
                    return;
                case 23: //alphaLayer8Texture
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            {
                            Layers.value[x]->ATXT.value.texture = defaultGENTXT.texture;
                            return;
                            }
                    //No existing alpha layer, so nothing to do
                    return;
                case 24: //alphaLayer8Opacity
                    curQuadrant = CalcQuadrant(ListIndex, ListX2Index);
                    curPosition = CalcPosition(curQuadrant, ListIndex, ListX2Index);
                    for(uint32_t x = 0; x < Layers.value.size(); ++x)
                        if(Layers.value[x]->ATXT.value.quadrant == curQuadrant && Layers.value[x]->ATXT.value.layer == 7)
                            for(uint32_t y = 0; y < Layers.value[x]->VTXT.value.size(); ++y)
                                if(Layers.value[x]->VTXT.value[y].position == curPosition)
                                    {
                                    Layers.value[x]->VTXT.value[y].opacity = defaultVTXT.opacity;
                                    return;
                                    }
                    //No existing VTXT, so nothing to do
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