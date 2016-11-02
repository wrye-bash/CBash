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
#include "..\ALCHRecord.h"

namespace FNV
{
uint32_t ALCHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //boundX1
            return CB_SINT16_FIELD;
        case 8: //boundY1
            return CB_SINT16_FIELD;
        case 9: //boundZ1
            return CB_SINT16_FIELD;
        case 10: //boundX2
            return CB_SINT16_FIELD;
        case 11: //boundY2
            return CB_SINT16_FIELD;
        case 12: //boundZ2
            return CB_SINT16_FIELD;
        case 13: //full
            return CB_STRING_FIELD;
        case 14: //modPath
            return CB_ISTRING_FIELD;
        case 15: //modb
            return CB_FLOAT32_FIELD;
        case 16: //modt_p
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
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)MODL->Textures.MODS.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return CB_STRING_FIELD;
                case 2: //texture
                    return CB_FORMID_FIELD;
                case 3: //index
                    return CB_SINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 18: //modelFlags
            return CB_UINT8_FLAG_FIELD;
        case 19: //iconPath
            return CB_ISTRING_FIELD;
        case 20: //smallIconPath
            return CB_ISTRING_FIELD;
        case 21: //script
            return CB_FORMID_FIELD;
        case 22: //equipmentType
            return CB_SINT32_TYPE_FIELD;
        case 23: //weight
            return CB_FLOAT32_FIELD;
        case 24: //value
            return CB_SINT32_FIELD;
        case 25: //flags
            return CB_UINT8_FLAG_FIELD;
        case 26: //unused1
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
        case 27: //withdrawalEffect
            return CB_FORMID_FIELD;
        case 28: //addictionChance
            return CB_FLOAT32_FIELD;
        case 29: //consumeSound
            return CB_FORMID_FIELD;
        case 30: //effects
            if(ListFieldID == 0) //effects
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Effects.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Effects.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //effect
                    return CB_FORMID_FIELD;
                case 2: //magnitude
                    return CB_UINT32_FIELD;
                case 3: //area
                    return CB_UINT32_FIELD;
                case 4: //duration
                    return CB_UINT32_FIELD;
                case 5: //rangeType
                    return CB_UINT32_FIELD;
                case 6: //actorValue
                    return CB_SINT32_FIELD;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditions
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_LIST_FIELD;
                            case 1: //fieldSize
                                return (uint32_t)Effects.value[ListIndex]->CTDA.value.size();
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        return CB_UNKNOWN_FIELD;
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return CB_UNKNOWN_FIELD;

                    switch(ListX2FieldID)
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
                                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->IsUseGlobal() ? CB_FORMID_FIELD :  CB_FLOAT32_FIELD;
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
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
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
                                    Function_Arguments_Iterator curCTDAFunction = FNVFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc);
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
                                                if(Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 < VATSFUNCTIONSIZE)
                                                    {
                                                    switch(VATSFunction_Argument[Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1])
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
                                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                            return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 31: //destructableHealth
            return CB_SINT32_FIELD;
        case 32: //destructableCount
            return CB_UINT8_FIELD;
        case 33: //destructableFlags
            return CB_UINT8_FLAG_FIELD;
        case 34: //destructableUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Destructable.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 35: //destructableStages
            if(!Destructable.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //destructableStages
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Destructable->Stages.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Destructable->Stages.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //health
                    return CB_UINT8_FIELD;
                case 2: //index
                    return CB_UINT8_FIELD;
                case 3: //stage
                    return CB_UINT8_FIELD;
                case 4: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 5: //dps
                    return CB_SINT32_FIELD;
                case 6: //explosion
                    return CB_FORMID_FIELD;
                case 7: //debris
                    return CB_FORMID_FIELD;
                case 8: //debrisCount
                    return CB_SINT32_FIELD;
                case 9: //modPath
                    return CB_ISTRING_FIELD;
                case 10: //modt_p
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 36: //pickupSound
            return CB_FORMID_FIELD;
        case 37: //dropSound
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * ALCHRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX1
            return &OBND.value.x1;
        case 8: //boundY1
            return &OBND.value.y1;
        case 9: //boundZ1
            return &OBND.value.z1;
        case 10: //boundX2
            return &OBND.value.x2;
        case 11: //boundY2
            return &OBND.value.y2;
        case 12: //boundZ2
            return &OBND.value.z2;
        case 13: //full
            return FULL.value;
        case 14: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 15: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 16: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 17: //altTextures
            if(!MODL.IsLoaded())
                return NULL;

            if(ListIndex >= MODL->Textures.MODS.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name
                    return MODL->Textures.MODS[ListIndex]->name;
                case 2: //texture
                    return &MODL->Textures.MODS[ListIndex]->texture;
                case 3: //index
                    return &MODL->Textures.MODS[ListIndex]->index;
                default:
                    return NULL;
                }
            return NULL;
        case 18: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 19: //iconPath
            return ICON.value;
        case 20: //smallIconPath
            return MICO.value;
        case 21: //script
            return SCRI.IsLoaded() ? &SCRI.value : NULL;
        case 22: //equipmentType
            return ETYP.IsLoaded() ? &ETYP.value : NULL;
        case 23: //weight
            return &DATA.value;
        case 24: //value
            return &ENIT.value.value;
        case 25: //flags
            return &ENIT.value.flags;
        case 26: //unused1
            *FieldValues = &ENIT.value.unused1[0];
            return NULL;
        case 27: //withdrawalEffect
            return &ENIT.value.withdrawalEffect;
        case 28: //addictionChance
            return &ENIT.value.addictionChance;
        case 29: //consumeSound
            return &ENIT.value.consumeSound;
        case 30: //effects
            if(ListIndex >= Effects.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //effect
                    return &Effects.value[ListIndex]->EFID.value;
                case 2: //magnitude
                    return &Effects.value[ListIndex]->EFIT.value.magnitude;
                case 3: //area
                    return &Effects.value[ListIndex]->EFIT.value.area;
                case 4: //duration
                    return &Effects.value[ListIndex]->EFIT.value.duration;
                case 5: //rangeType
                    return &Effects.value[ListIndex]->EFIT.value.rangeType;
                case 6: //actorValue
                    return &Effects.value[ListIndex]->EFIT.value.actorValue;
                case 7: //conditions
                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return NULL;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType;
                        case 2: //unused1
                            *FieldValues = &Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0];
                            return NULL;
                        case 3: //compValue
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue;
                        case 4: //ifunc
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc;
                        case 5: //param1
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1;
                        case 6: //param2
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2;
                        case 7: //runOnType
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType;
                        case 8: //reference
                            return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference;
                        default:
                            return NULL;
                        }
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 31: //destructableHealth
            return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
        case 32: //destructableCount
            return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
        case 33: //destructableFlags
            return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
        case 34: //destructableUnused1
            *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
            return NULL;
        case 35: //destructableStages
            if(!Destructable.IsLoaded())
                return NULL;

            if(ListIndex >= Destructable->Stages.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //health
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.health;
                case 2: //index
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.index;
                case 3: //stage
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.stage;
                case 4: //flags
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.flags;
                case 5: //dps
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.dps;
                case 6: //explosion
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.explosion;
                case 7: //debris
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debris;
                case 8: //debrisCount
                    return &Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount;
                case 9: //modPath
                    return Destructable->Stages.value[ListIndex]->DMDL.value;
                case 10: //modt_p
                    *FieldValues = Destructable->Stages.value[ListIndex]->DMDT.value;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 36: //pickupSound
            return YNAM.IsLoaded() ? &YNAM.value : NULL;
        case 37: //dropSound
            return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool ALCHRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //boundX1
            OBND.value.x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND.value.y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND.value.z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND.value.x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND.value.y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND.value.z2 = *(int16_t *)FieldValue;
            break;
        case 13: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 14: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 15: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 16: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 17: //altTextures
            MODL.Load();
            if(ListFieldID == 0) //altTexturesSize
                {
                MODL->Textures.resize(ArraySize);
                return false;
                }

            if(ListIndex >= MODL->Textures.MODS.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name
                    delete []MODL->Textures.MODS[ListIndex]->name;
                    MODL->Textures.MODS[ListIndex]->name = NULL;
                    if(FieldValue != NULL)
                        {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        MODL->Textures.MODS[ListIndex]->name = new char[ArraySize];
                        strcpy_s(MODL->Textures.MODS[ListIndex]->name, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 2: //texture
                    MODL->Textures.MODS[ListIndex]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    MODL->Textures.MODS[ListIndex]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 18: //modelFlags
            MODL.Load();
            MODL->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 19: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 20: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 21: //script
            SCRI.value = *(FORMID *)FieldValue;
            return true;
        case 22: //equipmentType
            SetEquipmentType(*(int32_t *)FieldValue);
            break;
        case 23: //weight
            DATA.value = *(float *)FieldValue;
            break;
        case 24: //value
            ENIT.value.value = *(int32_t *)FieldValue;
            break;
        case 25: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 26: //unused1
            if(ArraySize != 3)
                break;
            ENIT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            ENIT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            ENIT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 27: //withdrawalEffect
            ENIT.value.withdrawalEffect = *(FORMID *)FieldValue;
            return true;
        case 28: //addictionChance
            ENIT.value.addictionChance = *(float *)FieldValue;
            break;
        case 29: //consumeSound
            ENIT.value.consumeSound = *(FORMID *)FieldValue;
            return true;
        case 30: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Effects.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //effect
                    Effects.value[ListIndex]->EFID.value = *(FORMID *)FieldValue;
                    return true;
                case 2: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = *(uint32_t *)FieldValue;
                    break;
                case 3: //area
                    Effects.value[ListIndex]->EFIT.value.area = *(uint32_t *)FieldValue;
                    break;
                case 4: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = *(uint32_t *)FieldValue;
                    break;
                case 5: //rangeType
                    Effects.value[ListIndex]->SetRange(*(uint32_t *)FieldValue);
                    break;
                case 6: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = *(int32_t *)FieldValue;
                    break;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Effects.value[ListIndex]->CTDA.resize(ArraySize);
                        return false;
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        break;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType = *(uint8_t *)FieldValue;
                            break;
                        case 2: //unused1
                            if(ArraySize != 3)
                                break;
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                            break;
                        case 3: //compValue
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                            return true;
                        case 4: //ifunc
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = *(uint32_t *)FieldValue;
                            return true;
                        case 5: //param1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 6: //param2
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2 = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        case 7: //runOnType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = *(uint32_t *)FieldValue;
                            return true;
                        case 8: //reference
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference = *(FORMID_OR_UINT32 *)FieldValue;
                            return true;
                        default:
                            break;
                        }
                    break;
                default:
                    break;
                }
            break;
        case 31: //destructableHealth
            Destructable.Load();
            Destructable->DEST.value.health = *(int32_t *)FieldValue;
            break;
        case 32: //destructableCount
            Destructable.Load();
            Destructable->DEST.value.count = *(uint8_t *)FieldValue;
            break;
        case 33: //destructableFlags
            Destructable.Load();
            Destructable->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 34: //destructableUnused1
            if(ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 35: //destructableStages
            Destructable.Load();
            if(ListFieldID == 0) //destructableStagesSize
                {
                Destructable->Stages.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Destructable->Stages.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //health
                    Destructable->Stages.value[ListIndex]->DSTD.value.health = *(uint8_t *)FieldValue;
                    break;
                case 2: //index
                    Destructable->Stages.value[ListIndex]->DSTD.value.index = *(uint8_t *)FieldValue;
                    break;
                case 3: //stage
                    Destructable->Stages.value[ListIndex]->DSTD.value.stage = *(uint8_t *)FieldValue;
                    break;
                case 4: //flags
                    Destructable->Stages.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 5: //dps
                    Destructable->Stages.value[ListIndex]->DSTD.value.dps = *(int32_t *)FieldValue;
                    break;
                case 6: //explosion
                    Destructable->Stages.value[ListIndex]->DSTD.value.explosion = *(FORMID *)FieldValue;
                    return true;
                case 7: //debris
                    Destructable->Stages.value[ListIndex]->DSTD.value.debris = *(FORMID *)FieldValue;
                    return true;
                case 8: //debrisCount
                    Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = *(int32_t *)FieldValue;
                    break;
                case 9: //modPath
                    Destructable->Stages.value[ListIndex]->DMDL.Copy((char *)FieldValue);
                    break;
                case 10: //modt_p
                    Destructable->Stages.value[ListIndex]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                    break;
                default:
                    break;
                }
            break;
        case 36: //pickupSound
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 37: //dropSound
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void ALCHRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    ALCHENIT defaultENIT;
    FNVCTDA defaultCTDA;
    FNVEffect defaultEffect;

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
        case 7: //boundX1
            OBND.value.x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND.value.y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND.value.z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND.value.x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND.value.y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND.value.z2 = defaultOBND.z2;
            return;
        case 13: //full
            FULL.Unload();
            return;
        case 14: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 15: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 16: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 17: //altTextures
            if(MODL.IsLoaded())
                {
                if(ListFieldID == 0) //altTextures
                    {
                    MODL->Textures.Unload();
                    return;
                    }

                if(ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //name
                        delete []MODL->Textures.MODS[ListIndex]->name;
                        MODL->Textures.MODS[ListIndex]->name = NULL;
                        return;
                    case 2: //texture
                        MODL->Textures.MODS[ListIndex]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        MODL->Textures.MODS[ListIndex]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 18: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 19: //iconPath
            ICON.Unload();
            return;
        case 20: //smallIconPath
            MICO.Unload();
            return;
        case 21: //script
            SCRI.Unload();
            return;
        case 22: //equipmentType
            ETYP.Unload();
            return;
        case 23: //weight
            DATA.Unload();
            return;
        case 24: //value
            ENIT.value.value = defaultENIT.value;
            return;
        case 25: //flags
            ENIT.value.flags = defaultENIT.flags;
            return;
        case 26: //unused1
            ENIT.value.unused1[0] = defaultENIT.unused1[0];
            ENIT.value.unused1[1] = defaultENIT.unused1[1];
            ENIT.value.unused1[2] = defaultENIT.unused1[2];
            return;
        case 27: //withdrawalEffect
            ENIT.value.withdrawalEffect = defaultENIT.withdrawalEffect;
            return;
        case 28: //addictionChance
            ENIT.value.addictionChance = defaultENIT.addictionChance;
            return;
        case 29: //consumeSound
            ENIT.value.consumeSound = defaultENIT.consumeSound;
            return;
        case 30: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.Unload();
                return;
                }

            if(ListIndex >= Effects.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //effect
                    Effects.value[ListIndex]->EFID.value = defaultEffect.EFID.value;
                    return;
                case 2: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = defaultEffect.EFIT.value.magnitude;
                    return;
                case 3: //area
                    Effects.value[ListIndex]->EFIT.value.area = defaultEffect.EFIT.value.area;
                    return;
                case 4: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = defaultEffect.EFIT.value.duration;
                    return;
                case 5: //rangeType
                    Effects.value[ListIndex]->SetRange(defaultEffect.EFIT.value.rangeType);
                    return;
                case 6: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = defaultEffect.EFIT.value.actorValue;
                    return;
                case 7: //conditions
                    if(ListX2FieldID == 0) //conditionsSize
                        {
                        Effects.value[ListIndex]->CTDA.Unload();
                        return;
                        }

                    if(ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                        return;

                    switch(ListX2FieldID)
                        {
                        case 1: //operType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->operType = defaultCTDA.operType;
                            return;
                        case 2: //unused1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[0] = defaultCTDA.unused1[0];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[1] = defaultCTDA.unused1[1];
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->unused1[2] = defaultCTDA.unused1[2];
                            return;
                        case 3: //compValue
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->compValue = defaultCTDA.compValue;
                            return;
                        case 4: //ifunc
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->ifunc = defaultCTDA.ifunc;
                            return;
                        case 5: //param1
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param1 = defaultCTDA.param1;
                            return;
                        case 6: //param2
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->param2 = defaultCTDA.param2;
                            return;
                        case 7: //runOnType
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->runOnType = defaultCTDA.runOnType;
                            return;
                        case 8: //reference
                            Effects.value[ListIndex]->CTDA.value[ListX2Index]->reference = defaultCTDA.reference;
                            return;
                        default:
                            return;
                        }
                    return;
                default:
                    return;
                }
            return;
        case 31: //destructableHealth
            if(Destructable.IsLoaded())
                Destructable->DEST.value.health = defaultDEST.health;
            return;
        case 32: //destructableCount
            if(Destructable.IsLoaded())
                Destructable->DEST.value.count = defaultDEST.count;
            return;
        case 33: //destructableFlags
            if(Destructable.IsLoaded())
                Destructable->SetFlagMask(defaultDEST.flags);
            return;
        case 34: //destructableUnused1
            if(Destructable.IsLoaded())
                {
                Destructable->DEST.value.unused1[0] = defaultDSTD.health;
                }
            return;
        case 35: //destructableStages
            if(Destructable.IsLoaded())
                {
                if(ListFieldID == 0) //destructableStages
                    {
                    Destructable->Stages.Unload();
                    return;
                    }

                if(ListIndex >= Destructable->Stages.value.size())
                    return;

                switch(ListFieldID)
                    {
                    case 1: //health
                        Destructable->Stages.value[ListIndex]->DSTD.value.health = defaultDSTD.health;
                        return;
                    case 2: //index
                        Destructable->Stages.value[ListIndex]->DSTD.value.index = defaultDSTD.index;
                        return;
                    case 3: //stage
                        Destructable->Stages.value[ListIndex]->DSTD.value.stage = defaultDSTD.stage;
                        return;
                    case 4: //flags
                        Destructable->Stages.value[ListIndex]->SetFlagMask(defaultDSTD.flags);
                        return;
                    case 5: //dps
                        Destructable->Stages.value[ListIndex]->DSTD.value.dps = defaultDSTD.dps;
                        return;
                    case 6: //explosion
                        Destructable->Stages.value[ListIndex]->DSTD.value.explosion = defaultDSTD.explosion;
                        return;
                    case 7: //debris
                        Destructable->Stages.value[ListIndex]->DSTD.value.debris = defaultDSTD.debris;
                        return;
                    case 8: //debrisCount
                        Destructable->Stages.value[ListIndex]->DSTD.value.debrisCount = defaultDSTD.debrisCount;
                        return;
                    case 9: //modPath
                        Destructable->Stages.value[ListIndex]->DMDL.Unload();
                        return;
                    case 10: //modt_p
                        Destructable->Stages.value[ListIndex]->DMDT.Unload();
                        return;
                    default:
                        return;
                    }
                }
            return;
        case 36: //pickupSound
            YNAM.Unload();
            return;
        case 37: //dropSound
            ZNAM.Unload();
            return;
        default:
            return;
        }
    }
}