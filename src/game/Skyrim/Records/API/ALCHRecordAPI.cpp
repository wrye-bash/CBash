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
#include "..\ALCHRecord.h"

namespace Sk {

uint32_t ALCHRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
{
    switch (FieldID)
    {
    case 0: //recType
        return GetType();
    case 1: //flags1
        return CB_UINT32_FLAG_FIELD;
    case 2: //fid
        return CB_FORMID_FIELD;
    case 3: //versionControl1
        switch (WhichAttribute)
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
        switch (WhichAttribute)
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
    case 14: //keywords
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return CB_FORMID_ARRAY_FIELD;
        case 1: //fieldSize
            return KWDA.value.size();
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 15: //description
        return CB_STRING_FIELD;
    case 16: //modPath
        return CB_ISTRING_FIELD;
    case 17: //modt_p
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return CB_UINT8_ARRAY_FIELD;
        case 1: //fieldSize
            return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 18: //altTextures
        if (!MODL.IsLoaded())
            return CB_UNKNOWN_FIELD;

        if (ListFieldID == 0) //altTextures
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return CB_LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)MODL->Textures.MODS.size();
            default:
                return CB_UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= MODL->Textures.MODS.size())
            return CB_UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: //name
            return CB_STRING_FIELD;
        case 2: //textures
            return CB_FORMID_FIELD;
        case 3: //index
            return CB_SINT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 19: //destructableHealth
        return CB_SINT32_FIELD;
    case 20: //destructableCount
        return CB_UINT8_FIELD;
    case 21: //destructableFlags
        return CB_UINT8_FLAG_FIELD;
    case 22: //destructableUnused1
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return CB_UINT8_ARRAY_FIELD;
        case 1: //fieldSize
            return Destructable.IsLoaded() ? sizeof(Destructable->DEST->unused1) : 0;
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 23: //destructableStages
        if (!Destructable.IsLoaded())
            return CB_UNKNOWN_FIELD;

        if (ListFieldID == 0) //destructableStages
        {
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return CB_LIST_FIELD;
            case 1: //fieldSize
                return (uint32_t)Destructable->Stages.value.size();
            default:
                return CB_UNKNOWN_FIELD;
            }
        }

        if (ListIndex >= Destructable->Stages.value.size())
            return CB_UNKNOWN_FIELD;

        switch (ListFieldID)
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
            switch (WhichAttribute)
            {
            case 0: //fieldType
                return CB_UINT8_ARRAY_FIELD;
            case 1: //fieldSize
                return Destructable->Stages.value[ListIndex]->DMDT.GetSize();
            default:
                return CB_UNKNOWN_FIELD;
            }
        case 11: //altTextures
            if (!Destructable->Stages.value[ListIndex]->DMDS.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if (ListX2FieldID == 0) //altTextures
            {
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_LIST_FIELD;
                case 1: //fieldSize
                    return (uint32_t)Destructable->Stages.value[ListIndex]->DMDS.MODS.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            }

            if (ListX2Index >= Destructable->Stages.value[ListIndex]->DMDS.MODS.size())
                return CB_UNKNOWN_FIELD;

            switch (ListX2FieldID)
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
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 24: //iconPath
        return CB_ISTRING_FIELD;
    case 25: //smallIconPath
        return CB_ISTRING_FIELD;
    case 26: //pickupSound
        return CB_FORMID_FIELD;
    case 27: //dropSound
        return CB_FORMID_FIELD;
    case 28: //equipmentType
        return CB_FORMID_FIELD;
    case 29: //weight
        return CB_FLOAT32_FIELD;
    case 30: //value
        return CB_SINT32_FIELD;
    case 31: //flags
        return CB_UINT32_FLAG_FIELD;
    case 32: //withdrawalEffect
        return CB_FORMID_FIELD;
    case 33: //addictionChance
        return CB_FLOAT32_FIELD;
    case 34: //consumeSound
        return CB_FORMID_FIELD;
    case 35: //effects
        if (ListFieldID == 0) //effects
        {
            switch (WhichAttribute)
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

        if (ListIndex >= Effects.value.size())
            return CB_UNKNOWN_FIELD;

        switch (ListFieldID)
        {
        case 1: //effect
            return CB_FORMID_FIELD;
        case 2: //magnitude
            return CB_FLOAT32_FIELD;
        case 3: //area
            return CB_UINT32_FIELD;
        case 4: //duration
            return CB_UINT32_FIELD;
        case 5: //conditions
            if (ListX2FieldID == 0) //conditions
            {
                switch (WhichAttribute)
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

            if (ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                return CB_UNKNOWN_FIELD;

            switch (ListX2FieldID)
            {
            case 1: //operType
                return CB_UINT8_FLAG_TYPE_FIELD;
            case 2: //unused1
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            case 3: //compValue
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_OR_FLOAT32_FIELD;
                case 2: //WhichType
                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->IsUseGlobal() ? CB_FORMID_FIELD : CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
                return CB_UNKNOWN_FIELD;
            case 4: //ifunc
                return CB_UINT16_TYPE_FIELD;
            case 5: //unused2
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return CB_UNKNOWN_FIELD;
                }
                return CB_UNKNOWN_FIELD;
            case 6: //param1
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                {
                            Function_Arguments_Iterator curCTDAFunction = SKFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->ifunc);
                            if (curCTDAFunction != SKFunction_Arguments.end())
                            {
                                const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                switch (CTDAFunction.first)
                                {
                                case eFORMID:
                                    return CB_FORMID_FIELD;
                                case eUINT32:
                                case eEVENTDATA:
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
            case 7: //param2
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                {
                            Function_Arguments_Iterator curCTDAFunction = SKFunction_Arguments.find(Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->ifunc);
                            if (curCTDAFunction != SKFunction_Arguments.end())
                            {
                                const FunctionArguments &CTDAFunction = curCTDAFunction->second;
                                switch (CTDAFunction.second)
                                {
                                case eFORMID:
                                    return CB_FORMID_FIELD;
                                case eUINT32:
                                    return CB_UINT32_FIELD;
                                default:
                                    return CB_UNKNOWN_FIELD;
                                }
                                return CB_UNKNOWN_FIELD;
                            }
                            return CB_UNKNOWN_FIELD;
                }
                default:
                    return CB_UNKNOWN_FIELD;
                }
                return CB_UNKNOWN_FIELD;
            case 8: //runOnType
                return CB_UINT32_TYPE_FIELD;
            case 9: //reference
                switch (WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UNKNOWN_OR_FORMID_OR_UINT32_FIELD;
                case 2: //WhichType
                    return Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->IsResultOnReference() ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
                return CB_UNKNOWN_FIELD;
            case 10: //param3
                return CB_SINT32_FIELD;
            case 11: //cis1
                return CB_STRING_FIELD;
            case 12: //cis2
                return CB_STRING_FIELD;
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
    case 14: //keywords
        *FieldValues = KWDA.IsLoaded() ? &KWDA.value[0] : NULL;
        return NULL;
    case 15: //description
        return DESC.value;
    case 16: //modPath
        return MODL.IsLoaded() ? MODL->MODL.value : NULL;
    case 17: //modt_p
        return MODL.IsLoaded() ? MODL->MODT.value : NULL;
    case 18: //altTextures
        if (!MODL.IsLoaded())
            return NULL;

        if (ListIndex >= MODL->Textures.MODS.size())
            return NULL;

        switch (ListFieldID)
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
    case 19: //destructableHealth
        return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
    case 20: //destructableCount
        return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
    case 21: //destructableFlags
        return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
    case 22: //destructableUnused1
        *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
        return NULL;
    case 23: //destructableStages
        if (!Destructable.IsLoaded())
            return NULL;

        if (ListIndex >= Destructable->Stages.value.size())
            return NULL;

        switch (ListFieldID)
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
        case 11: //altTextures
            if (ListX2Index >= Destructable->Stages.value[ListIndex]->DMDS.MODS.size())
                return NULL;

            switch (ListX2FieldID)
            {
            case 1: //name
                return Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name;
            case 2: //texture
                return &Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->texture;
            case 3: //index
                return &Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->index;
            default:
                return NULL;
            }
            return NULL;
        default:
            return NULL;
        }
        return NULL;
    case 24: //iconPath
        return ICON.value;
    case 25: //smallIconPath
        return MICO.value;
    case 26: //pickupSound
        return YNAM.IsLoaded() ? &YNAM.value : NULL;
    case 27: //dropSound
        return ZNAM.IsLoaded() ? &ZNAM.value : NULL;
    case 28: //equipmentType
        return ETYP.IsLoaded() ? &ETYP.value : NULL;
    case 29: //weigth
        return &DATA.value;
    case 30: //value
        return &ENIT->value;
    case 31: //flags
        return &ENIT->flags;
    case 32: //withdrawalEffect
        return &ENIT->withdrawalEffect;
    case 33: //addictionChance
        return &ENIT->addictionChance;
    case 34: //consumeSound
        return &ENIT->consumeSound;
    case 35: //effects
        if (ListIndex >= Effects.value.size())
            return NULL;

        switch (ListFieldID)
        {
        case 1: //effect
            return &Effects.value[ListIndex]->EFID.value;
        case 2: //magnitude
            return &Effects.value[ListIndex]->EFIT->magnitude;
        case 3: //area
            return &Effects.value[ListIndex]->EFIT->area;
        case 4: //duration
            return &Effects.value[ListIndex]->EFIT->duration;
        case 5: //conditions
            if (ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                return NULL;

            switch (ListX2FieldID)
            {
            case 1: //operType
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->operType;
            case 2: //unused1
                *FieldValues = &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[0];
                return NULL;
            case 3: //compValue
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->compValue;
            case 4: //ifunc
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->ifunc;
            case 5: //unused2
                *FieldValues = &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused2[0];
                return NULL;
            case 6: //param1
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param1;
            case 7: //param2
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param2;
            case 8: //runOnType
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->runOnType;
            case 9: // reference
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->reference;
            case 10: //param3
                return &Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param3;
            case 11: //cis2
                return Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS1.value;
            case 12: //cis3
                return Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS2.value;
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
            OBND->x1 = *(int16_t *)FieldValue;
            break;
        case 8: //boundY1
            OBND->y1 = *(int16_t *)FieldValue;
            break;
        case 9: //boundZ1
            OBND->z1 = *(int16_t *)FieldValue;
            break;
        case 10: //boundX2
            OBND->x2 = *(int16_t *)FieldValue;
            break;
        case 11: //boundY2
            OBND->y2 = *(int16_t *)FieldValue;
            break;
        case 12: //boundZ2
            OBND->z2 = *(int16_t *)FieldValue;
            break;
        case 13: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 14: //keywords
            KWDA.resize(ArraySize);
            for (uint32_t i = 0; i < ArraySize; ++i)
                KWDA.value[i] = ((FORMIDARRAY)FieldValue)[i];
            return true;
        case 15: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 16: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 17: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 18: //altTextures
            MODL.Load();
            if (ListFieldID == 0) // altTextures
            {
                MODL->Textures.resize(ArraySize);
                return false;
            }

            if (ListIndex >= MODL->Textures.MODS.size())
                break;

            switch (ListFieldID)
            {
            case 1: //name
                delete[]MODL->Textures.MODS[ListIndex]->name;
                MODL->Textures.MODS[ListIndex]->name = NULL;
                if (FieldValue != NULL)
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
        case 19: //destructableHealth
            Destructable.Load();
            Destructable->DEST->health = *(int32_t *)FieldValue;
            break;
        case 20: //destructableCount
            Destructable.Load();
            Destructable->DEST->count = *(uint8_t *)FieldValue;
            break;
        case 21: //destructableFlags
            Destructable.Load();
            Destructable->DEST->flags = *(uint8_t *)FieldValue;
            break;
        case 22: //destructableUnused1
            if (ArraySize != 2)
                break;
            Destructable.Load();
            Destructable->DEST->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Destructable->DEST->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 23: //destructableStages
            Destructable.Load();
            if (ListFieldID == 0) //destructableStagesSize
            {
                Destructable->Stages.resize(ArraySize);
                return false;
            }

            if (ListIndex >= Destructable->Stages.value.size())
                break;

            switch (ListFieldID)
            {
            case 1: //health
                Destructable->Stages.value[ListIndex]->DSTD->health = *(uint8_t *)FieldValue;
                break;
            case 2: //index
                Destructable->Stages.value[ListIndex]->DSTD->index = *(uint8_t *)FieldValue;
                break;
            case 3: //stage
                Destructable->Stages.value[ListIndex]->DSTD->stage = *(uint8_t *)FieldValue;
                break;
            case 4: //flags
                Destructable->Stages.value[ListIndex]->DSTD->flags = *(uint8_t *)FieldValue;
                break;
            case 5: //dps
                Destructable->Stages.value[ListIndex]->DSTD->dps = *(int32_t *)FieldValue;
                break;
            case 6: //explosion
                Destructable->Stages.value[ListIndex]->DSTD->explosion = *(FORMID *)FieldValue;
                return true;
            case 7: //debris
                Destructable->Stages.value[ListIndex]->DSTD->debris = *(FORMID *)FieldValue;
                return true;
            case 8: //debrisCount
                Destructable->Stages.value[ListIndex]->DSTD->debrisCount = *(int32_t *)FieldValue;
                break;
            case 9: //modPath
                Destructable->Stages.value[ListIndex]->DMDL.Copy((char *)FieldValue);
                break;
            case 10: //modt_p
                Destructable->Stages.value[ListIndex]->DMDT.Copy((UINT8ARRAY)FieldValue, ArraySize);
                break;
            case 11: //altTextures
                if (ListX2FieldID == 0) //altTexturesSize
                {
                    Destructable->Stages.value[ListIndex]->DMDS.resize(ArraySize);
                    return false;
                }

                if (ListX2Index >= Destructable->Stages.value[ListIndex]->DMDS.MODS.size())
                    break;

                switch (ListX2FieldID)
                {
                case 1: //name
                    delete[] Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name;
                    Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name = NULL;
                    if (FieldValue != NULL)
                    {
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name = new char[ArraySize];
                        strcpy_s(Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name, ArraySize, (char *)FieldValue);
                    }
                    break;
                case 2: //texture
                    Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->texture = *(FORMID *)FieldValue;
                    return true;
                case 3: //index
                    Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->index = *(int32_t *)FieldValue;
                    break;
                default:
                    break;
                }
                break;
            default:
                break;
            }
            break;
        case 24: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 25: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 26: //pickupSound
            YNAM.value = *(FORMID *)FieldValue;
            return true;
        case 27: //drop Sound
            ZNAM.value = *(FORMID *)FieldValue;
            return true;
        case 28: //equipmentType
            ETYP.value = *(FORMID *)FieldValue;
            return true;
        case 29: //wieght
            DATA.value = *(float *)FieldValue;
            break;
        case 30: //value
            ENIT->value = *(int32_t *)FieldValue;
            break;
        case 31: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 32: //withdrawalEffect
            ENIT->withdrawalEffect = *(FORMID *)FieldValue;
            return true;
        case 33: //addictionChance
            ENIT->addictionChance = *(float *)FieldValue;
            break;
        case 34: //consumeSound
            ENIT->consumeSound = *(FORMID *)FieldValue;
            return true;
        case 35: //effects
            if (ListFieldID == 0) //effectsSize
            {
                Effects.resize(ArraySize);
                return false;
            }

            if (ListIndex >= Effects.value.size())
                break;

            switch (ListFieldID)
            {
            case 1: //effect
                Effects.value[ListIndex]->EFID.value = *(FORMID *)FieldValue;
                return true;
            case 2: //magnitude
                Effects.value[ListIndex]->EFIT->magnitude = *(float *)FieldValue;
                break;
            case 3: //area
                Effects.value[ListIndex]->EFIT->area = *(uint32_t *)FieldValue;
                break;
            case 4: //duration
                Effects.value[ListIndex]->EFIT->duration = *(uint32_t *)FieldValue;
                break;
            case 5: //conditions
                if (ListX2FieldID == 0) //conditionsSize
                {
                    Effects.value[ListIndex]->CTDA.resize(ArraySize);
                    return false;
                }

                if (ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                    break;

                switch (ListX2FieldID)
                {
                case 1: //operType
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->operType = *(uint8_t *)FieldValue;
                    break;
                case 2: //unused1
                    if (ArraySize != 3)
                        break;
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 3: //compValue
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->compValue = *(FORMID_OR_FLOAT32 *)FieldValue;
                    return true;
                case 4: //ifunc
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->ifunc = *(uint16_t *)FieldValue;
                    return true;
                case 5: //unused2
                    if (ArraySize != 2)
                        break;
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    break;
                case 6: //param1
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param1 = *(FORMID_OR_UINT32 *)FieldValue;
                    return true;
                case 7: //param2
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param2 = *(FORMID_OR_UINT32 *)FieldValue;
                    return true;
                case 8: //runOnType
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->runOnType = *(uint32_t *)FieldValue;
                    true;
                case 9: //reference
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->reference = *(FORMID_OR_UINT32 *)FieldValue;
                    return true;
                case 10: //param3
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param3 = *(int32_t *)FieldValue;
                    break;
                case 11: //cis1
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS1.Copy((char *)FieldValue);
                    return true; // affects how param1 is interpreted
                case 12: //cis2
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS2.Copy((char *)FieldValue);
                    return true; // affects how param2 is interpreted
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

void ALCHRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    ALCHENIT defaultENIT;
    SKEffect defaultEffect;
    SKCTDA defaultCTDA;

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
            OBND->x1 = defaultOBND.x1;
            return;
        case 8: //boundY1
            OBND->y1 = defaultOBND.y1;
            return;
        case 9: //boundZ1
            OBND->z1 = defaultOBND.z1;
            return;
        case 10: //boundX2
            OBND->x2 = defaultOBND.x2;
            return;
        case 11: //boundY2
            OBND->y2 = defaultOBND.y2;
            return;
        case 12: //boundZ2
            OBND->z2 = defaultOBND.z2;
            return;
        case 13: //full
            FULL.Unload();
            return;
        case 14: //keywords
            KWDA.Unload();
            return;
        case 15: //description
            DESC.Unload();
            return;
        case 16: //modPath
            if (MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 17: //modt_p
            if (MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 18: //altTextures
            if (MODL.IsLoaded())
            {
                if (ListFieldID == 0) //altTextures
                {
                    MODL->Textures.Unload();
                    return;
                }

                if (ListIndex >= MODL->Textures.MODS.size())
                    return;

                switch (ListFieldID)
                {
                case 1: //name
                    delete[] MODL->Textures.MODS[ListIndex]->name;
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
        case 19: //destructableHealth
            if (Destructable.IsLoaded())
                Destructable->DEST->health = defaultDEST.health;
            return;
        case 20: //destructableCount
            if (Destructable.IsLoaded())
                Destructable->DEST->count = defaultDEST.count;
            return;
        case 21: //destructableFlags
            if (Destructable.IsLoaded())
                Destructable->DEST->flags = defaultDEST.flags;
            return;
        case 22: //destructableUnused1
            if (Destructable.IsLoaded())
            {
                Destructable->DEST->unused1[0] = defaultDEST.unused1[0];
                Destructable->DEST->unused1[1] = defaultDEST.unused1[1];
            }
            return;
        case 23: //destructableStages
            if (Destructable.IsLoaded())
            {
                if (ListFieldID == 0) //destructableStages
                {
                    Destructable->Stages.Unload();
                    return;
                }

                if (ListIndex >= Destructable->Stages.value.size())
                    return;

                switch (ListFieldID)
                {
                case 1: //health
                    Destructable->Stages.value[ListIndex]->DSTD->health = defaultDSTD.health;
                    return;
                case 2: //index
                    Destructable->Stages.value[ListIndex]->DSTD->index = defaultDSTD.index;
                    return;
                case 3: //stage
                    Destructable->Stages.value[ListIndex]->DSTD->stage = defaultDSTD.stage;
                    return;
                case 4: //flags
                    Destructable->Stages.value[ListIndex]->DSTD->flags = defaultDSTD.flags;
                    return;
                case 5: //dps
                    Destructable->Stages.value[ListIndex]->DSTD->dps = defaultDSTD.dps;
                    return;
                case 6: //explosion
                    Destructable->Stages.value[ListIndex]->DSTD->explosion = defaultDSTD.explosion;
                    return;
                case 7: //debris
                    Destructable->Stages.value[ListIndex]->DSTD->debris = defaultDSTD.debris;
                    return;
                case 8: //debrisCount
                    Destructable->Stages.value[ListIndex]->DSTD->debrisCount = defaultDSTD.debrisCount;
                    return;
                case 9: //modPath
                    Destructable->Stages.value[ListIndex]->DMDL.Unload();
                    return;
                case 10: //modt_p
                    Destructable->Stages.value[ListIndex]->DMDT.Unload();
                    return;
                case 11: //altTextures
                    if (ListX2FieldID == 0) //altTextures
                    {
                        Destructable->Stages.value[ListIndex]->DMDS.Unload();
                        return;
                    }

                    if (ListX2Index >= Destructable->Stages.value[ListIndex]->DMDS.MODS.size())
                        return;

                    switch (ListX2FieldID)
                    {
                    case 1: //name
                        delete[] Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name;
                        Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->name = NULL;
                        return;
                    case 2: //texture
                        Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->texture = defaultMODS.texture;
                        return;
                    case 3: //index
                        Destructable->Stages.value[ListIndex]->DMDS.MODS[ListX2Index]->index = defaultMODS.index;
                        return;
                    default:
                        return;
                    }
                    return;
                default:
                    return;
                }
            }
            return;
        case 24: //iconPath
            ICON.Unload();
            return;
        case 25: //smallIconPath
            MICO.Unload();
            return;
        case 26: //pickupSound
            YNAM.Unload();
            return;
        case 27: //dropSound
            ZNAM.Unload();
            return;
        case 28: //equipmentType
            ETYP.Unload();
            return;
        case 29: //wieght
            DATA.Unload();
            return;
        case 30: //value
            ENIT->value = defaultENIT.value;
            return;
        case 31: //flags
            ENIT->flags = defaultENIT.flags;
            return;
        case 32: //withdrawalEffect
            ENIT->withdrawalEffect = defaultENIT.withdrawalEffect;
            return;
        case 33: //addictionChance
            ENIT->addictionChance = defaultENIT.addictionChance;
            return;
        case 34: //consumeSound
            ENIT->consumeSound = defaultENIT.consumeSound;
            return;
        case 35: //effects
            if (ListFieldID == 0) //effects
            {
                Effects.Unload();
                return;
            }

            if (ListIndex >= Effects.value.size())
                return;

            switch (ListFieldID)
            {
            case 1: //effect
                Effects.value[ListIndex]->EFID = defaultEffect.EFID;
                return;
            case 2: //magnitude
                Effects.value[ListIndex]->EFIT->magnitude = defaultEffect.EFIT->magnitude;
                return;
            case 3: //area
                Effects.value[ListIndex]->EFIT->area = defaultEffect.EFIT->area;
                return;
            case 4: //duration
                Effects.value[ListIndex]->EFIT->duration = defaultEffect.EFIT->duration;
            case 5: //conditions
                if (ListX2FieldID == 0) //conditions
                {
                    Effects.value[ListIndex]->CTDA.Unload();
                    return;
                }

                if (ListX2Index >= Effects.value[ListIndex]->CTDA.value.size())
                    return;

                switch (ListX2FieldID)
                {
                case 1:  //operType
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->operType = defaultCTDA.operType;
                    return;
                case 2: //unused1
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[0] = defaultCTDA.unused1[0];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[1] = defaultCTDA.unused1[1];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused1[2] = defaultCTDA.unused1[2];
                    return;
                case 3: //compValue
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->compValue = defaultCTDA.compValue;
                    return;
                case 4: //ifunc
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->ifunc = defaultCTDA.ifunc;
                    return;
                case 5: //unused2
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused2[0] = defaultCTDA.unused2[0];
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->unused2[1] = defaultCTDA.unused2[1];
                    return;
                case 6: //param1
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param1 = defaultCTDA.param1;
                    return;
                case 7: //param2
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param2 = defaultCTDA.param2;
                    return;
                case 8: //runOnType
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->runOnType = defaultCTDA.runOnType;
                    return;
                case 9: //reference
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->reference = defaultCTDA.reference;
                    return;
                case 10: //param3
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CTDA->param3 = defaultCTDA.param3;
                    return;
                case 11: //cis1
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS1.Unload();
                    return;
                case 12: //cis2
                    Effects.value[ListIndex]->CTDA.value[ListX2Index]->CIS2.Unload();
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
    }
}
