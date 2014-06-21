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
#include "..\ACTIRecord.h"

namespace Sk
{

// VMAD not accessible via API

uint32_t ACTIRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
    case 14: //modPath
        return CB_ISTRING_FIELD;
    case 15: //modt_p
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
    case 16: //altTextures
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
        case 2: //texture
            return CB_FORMID_FIELD;
        case 3: //index
            return CB_SINT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 17: //destructableHealth
        return CB_SINT32_FIELD;
    case 18: //destructableCount
        return CB_UINT8_FIELD;
    case 19: //destructableFlags
        return CB_UINT8_FLAG_FIELD;
    case 20: //destructableUnused1
        switch (WhichAttribute)
        {
        case 0: //fieldType
            return CB_UINT8_ARRAY_FIELD;
        case 1: //fieldSize
            return Destructable.IsLoaded() ? 2 : 0;
        default:
            return CB_UNKNOWN_FIELD;
        }
        return CB_UNKNOWN_FIELD;
    case 21: //destructableStages
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
            return CB_UNKNOWN_FIELD;
        case 11: //altTextures
            if (ListX2FieldID == 0) //altTextures
            {
                switch (WhichAttribute)
                {
                case 1: //fieldType
                    return CB_LIST_FIELD;
                case 2: //fieldSize
                    return Destructable->Stages.value[ListIndex]->DMDS.MODS.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
                return CB_UNKNOWN_FIELD;
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
    case 22: //keywords
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
    case 23: //colorRed
        return CB_UINT8_FIELD;
    case 24: //colorGreen
        return CB_UINT8_FIELD;
    case 25: //colorBlue
        return CB_UINT8_FIELD;
    case 26: //colorUnk1
        return CB_UINT8_FIELD;
    case 27: //loopSound
        return CB_FORMID_FIELD;
    case 28: //actSound
        return CB_FORMID_FIELD;
    case 29: //water
        return CB_FORMID_FIELD;
    case 30: //textOverride
        return CB_STRING_FIELD;
    case 31: //flags
        return CB_UINT16_FLAG_FIELD;
    case 32: //interactKywd
        return CB_FORMID_FIELD;
    default:
        return CB_UNKNOWN_FIELD;
    }
    return CB_UNKNOWN_FIELD;
}

void * ACTIRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
{
    switch (FieldID)
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
    case 15: //modt_p
        *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
        return NULL;
    case 16: //altTextures
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
    case 17: //destructableHealth
        return Destructable.IsLoaded() ? &Destructable->DEST.value.health : NULL;
    case 18: //destructableCount
        return Destructable.IsLoaded() ? &Destructable->DEST.value.count : NULL;
    case 19: //destructableFlags
        return Destructable.IsLoaded() ? &Destructable->DEST.value.flags : NULL;
    case 20: //destructableUnused1
        *FieldValues = Destructable.IsLoaded() ? &Destructable->DEST.value.unused1[0] : NULL;
        return NULL;
    case 21: //destructableStages
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
    case 22: //keywords
        *FieldValues = KWDA.IsLoaded() ? &KWDA.value[0] : NULL;
        return NULL;
    case 23: //colorRed
        return &PNAM->red;
    case 24: //colorGreen
        return &PNAM->green;
    case 25: //colorBlue
        return &PNAM->blue;
    case 26: //colorUnk
        return &PNAM->unk1;
    case 27: //loopSound
        return SNAM.IsLoaded() ? &SNAM.value : NULL;
    case 28: //actSound
        return VNAM.IsLoaded() ? &VNAM.value : NULL;
    case 29: //water
        return WNAM.IsLoaded() ? &WNAM.value : NULL;
    case 30: //textOverride
        return RNAM.value;
    case 31: //flags
        return &FNAM.value;
    case 32: //interactionKywd
        return KNAM.IsLoaded() ? &KNAM.value : NULL;
    default:
        return NULL;
    }
    return NULL;
}

bool ACTIRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
{
    switch (FieldID)
    {
    case 1: //flags1
        SetHeaderFlagMask(*(uint32_t *)FieldValue);
        break;
    case 3: //versionControl1
        if (ArraySize != 4)
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
        if (ArraySize != 2)
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
    case 15: //modt_p
        MODL.Load();
        MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
        break;
    case 16: //altTextures
        MODL.Load();
        if (ListFieldID == 0) //altTexturesSize
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
    case 17: //destructableHealth
        Destructable.Load();
        Destructable->DEST.value.health = *(int32_t *)FieldValue;
        break;
    case 18: //destructableCount
        Destructable.Load();
        Destructable->DEST.value.count = *(uint8_t *)FieldValue;
        break;
    case 19: //destructableFlags
        Destructable.Load();
        Destructable->DEST->flags = *(uint8_t *)FieldValue;
        break;
    case 20: //destructableUnused1
        if (ArraySize != 2)
            break;
        Destructable.Load();
        Destructable->DEST.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
        Destructable->DEST.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
        break;
    case 21: //destructableStages
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
            Destructable->Stages.value[ListIndex]->DSTD.value.health = *(uint8_t *)FieldValue;
            break;
        case 2: //index
            Destructable->Stages.value[ListIndex]->DSTD.value.index = *(uint8_t *)FieldValue;
            break;
        case 3: //stage
            Destructable->Stages.value[ListIndex]->DSTD.value.stage = *(uint8_t *)FieldValue;
            break;
        case 4: //flags
            Destructable->Stages.value[ListIndex]->DSTD.value.flags = *(uint8_t *)FieldValue;
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
        case 11: //altTextures
            if (ListX2FieldID == 0) //altTexturesSize
            {
                Destructable->Stages.value[ListIndex]->DMDS.resize(ArraySize);
                return false;
            }

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
    case 22: //keywords
        KWDA.resize(ArraySize);
        for (uint32_t x = 0; x < ArraySize; ++x)
            KWDA.value[x] = ((FORMIDARRAY)FieldValue)[x];
        return true;
    case 23: //colorRed
        PNAM->red = *(uint8_t *)FieldValue;
        break;
    case 24: //colorGreen
        PNAM->green = *(uint8_t *)FieldValue;
        break;
    case 25: //colorBlue
        PNAM->blue = *(uint8_t *)FieldValue;
        break;
    case 26: //colorUnk
        PNAM->unk1 = *(uint8_t *)FieldValue;
        break;
    case 27: //loopSound
        SNAM.value = *(FORMID *)FieldValue;
        return true;
    case 28: //actSound
        VNAM.value = *(FORMID *)FieldValue;
        return true;
    case 29: //water
        WNAM.value = *(FORMID *)FieldValue;
        return true;
    case 30: //textOverride
        RNAM.Copy((char *)FieldValue);
        break;
    case 31: //flags
        FNAM.value = *(uint16_t *)FieldValue;
        break;
    case 32: //interactionKywd
        KNAM.value = *(FORMID *)FieldValue;
        return true;
    default:
        break;
    }

    return false;
}

void ACTIRecord::DeleteField(FIELD_IDENTIFIERS)
{
    GENOBND defaultOBND;
    FNVMODS defaultMODS;
    GENDEST defaultDEST;
    DESTDSTD defaultDSTD;
    GENCNAM defaultCNAM;
    switch (FieldID)
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
        if (MODL.IsLoaded())
            MODL->MODL.Unload();
        return;
    case 15: //modt_p
        if (MODL.IsLoaded())
            MODL->MODT.Unload();
        return;
    case 16: //altTextures
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
                delete[]MODL->Textures.MODS[ListIndex]->name;
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
    case 17: //destructableHealth
        if (Destructable.IsLoaded())
            Destructable->DEST.value.health = defaultDEST.health;
        return;
    case 18: //destructableCount
        if (Destructable.IsLoaded())
            Destructable->DEST.value.count = defaultDEST.count;
        return;
    case 19: //destructableFlags
        if (Destructable.IsLoaded())
            Destructable->DEST->flags = defaultDEST.flags;
        return;
    case 20: //destructableUnused1
        if (Destructable.IsLoaded())
        {
            Destructable->DEST.value.unused1[0] = defaultDSTD.health;
        }
        return;
    case 21: //destructableStages
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
                Destructable->Stages.value[ListIndex]->DSTD.value.health = defaultDSTD.health;
                return;
            case 2: //index
                Destructable->Stages.value[ListIndex]->DSTD.value.index = defaultDSTD.index;
                return;
            case 3: //stage
                Destructable->Stages.value[ListIndex]->DSTD.value.stage = defaultDSTD.stage;
                return;
            case 4: //flags
                Destructable->Stages.value[ListIndex]->DSTD.value.flags = defaultDSTD.flags;
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
    case 22: //keywords
        KWDA.Unload();
        return;
    case 23: //colorRed
        PNAM->red = defaultCNAM.red;
        return;
    case 24: //colorGreen
        PNAM->green = defaultCNAM.green;
        return;
    case 25: //colorBlue
        PNAM->blue = defaultCNAM.blue;
        return;
    case 26: //colorUnk
        PNAM->unk1 = defaultCNAM.unk1;
        return;
    case 27: //loopSound
        SNAM.Unload();
        return;
    case 28: //actSound
        VNAM.Unload();
        return;
    case 29: //water
        WNAM.Unload();
        return;
    case 30: //textOverride
        RNAM.Unload();
        return;
    case 31: //flags
        FNAM.Unload();
        return;
    case 32: //interactionKywd
        KNAM.Unload();
        return;
    default:
        return;
    }
}

} // namespace Sk
