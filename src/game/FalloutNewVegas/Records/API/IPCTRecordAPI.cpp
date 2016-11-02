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
#include "..\IPCTRecord.h"

namespace FNV
{
uint32_t IPCTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //modPath
            return CB_ISTRING_FIELD;
        case 8: //modb
            return CB_FLOAT32_FIELD;
        case 9: //modt_p
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
        case 10: //altTextures
            if(!MODL.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.MODS.size();
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

        case 13: //modelFlags
            return CB_UINT8_FIELD;
        case 14: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 15: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 16: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 17: //data DATA ,, Struct
            return CB_FLOAT32_FIELD;
        case 18: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 19: //data DATA ,, Struct
            return CB_UINT32_FIELD;
        case 20: //decalMinWidth
            return CB_FLOAT32_FIELD;
        case 21: //decalMaxWidth
            return CB_FLOAT32_FIELD;
        case 22: //decalMinHeight
            return CB_FLOAT32_FIELD;
        case 23: //decalMaxHeight
            return CB_FLOAT32_FIELD;
        case 24: //decalDepth
            return CB_FLOAT32_FIELD;
        case 25: //decalShininess
            return CB_FLOAT32_FIELD;
        case 26: //decalScale
            return CB_FLOAT32_FIELD;
        case 27: //decalPasses
            return CB_UINT8_FIELD;
        case 28: //decalFlags
            return CB_UINT8_FLAG_FIELD;
        case 29: //decalUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DODT.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 30: //decalRed
            return CB_UINT8_FIELD;
        case 31: //decalGreen
            return CB_UINT8_FIELD;
        case 32: //decalBlue
            return CB_UINT8_FIELD;
        case 33: //decalUnused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DODT.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 34: //dnam Texture Set
            return CB_FORMID_FIELD;
        case 35: //snam Sound 1
            return CB_FORMID_FIELD;
        case 36: //nam1 Sound 2
            return CB_FORMID_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * IPCTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 8: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 9: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 10: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? MODL->Textures.MODS.value : NULL;
        case 11: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->MODS->value11 : NULL;
        case 12: //mods Alternate Textures
            return NULL;
            //return MODL.IsLoaded() ? &MODL->MODS->value12 : NULL;
        case 13: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD.value : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->duration : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->orientation : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->angleThreshold : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->placementRadius : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->soundLevel : NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->flags : NULL;
        case 20: //decalMinWidth
            return DODT.IsLoaded() ? &DODT->minWidth : NULL;
        case 21: //decalMaxWidth
            return DODT.IsLoaded() ? &DODT->maxWidth : NULL;
        case 22: //decalMinHeight
            return DODT.IsLoaded() ? &DODT->minHeight : NULL;
        case 23: //decalMaxHeight
            return DODT.IsLoaded() ? &DODT->maxHeight : NULL;
        case 24: //decalDepth
            return DODT.IsLoaded() ? &DODT->depth : NULL;
        case 25: //decalShininess
            return DODT.IsLoaded() ? &DODT->shininess : NULL;
        case 26: //decalScale
            return DODT.IsLoaded() ? &DODT->scale : NULL;
        case 27: //decalPasses
            return DODT.IsLoaded() ? &DODT->passes : NULL;
        case 28: //decalFlags
            return DODT.IsLoaded() ? &DODT->flags : NULL;
        case 29: //decalUnused1
            *FieldValues = DODT.IsLoaded() ? &DODT->unused1[0] : NULL;
            return NULL;
        case 30: //decalRed
            return DODT.IsLoaded() ? &DODT->red : NULL;
        case 31: //decalGreen
            return DODT.IsLoaded() ? &DODT->green : NULL;
        case 32: //decalBlue
            return DODT.IsLoaded() ? &DODT->blue : NULL;
        case 33: //decalUnused2
            *FieldValues = DODT.IsLoaded() ? &DODT->unused2 : NULL;
            return NULL;
        case 34: //dnam Texture Set
            return DNAM.IsLoaded() ? &DNAM.value : NULL;
        case 35: //snam Sound 1
            return SNAM.IsLoaded() ? &SNAM.value : NULL;
        case 36: //nam1 Sound 2
            return NAM1.IsLoaded() ? &NAM1.value : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IPCTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 8: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //mods Alternate Textures
            MODL.Load();
            //MODL->MODS.Copy((char *)FieldValue);
            break;
        case 11: //mods Alternate Textures
            MODL.Load();
            MODL->Textures.Load();
            //MODL->MODS->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //mods Alternate Textures
            MODL.Load();
            MODL->Textures.Load();
            //MODL->MODS->value12 = *(int32_t *)FieldValue;
            break;
        case 13: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD.value = *(uint8_t *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->duration = *(float *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->orientation = *(uint32_t *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->angleThreshold = *(float *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->placementRadius = *(float *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->soundLevel = *(uint32_t *)FieldValue;
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->flags = *(uint32_t *)FieldValue;
            break;
        case 20: //decalMinWidth
            DODT.Load();
            DODT->minWidth = *(float *)FieldValue;
            break;
        case 21: //decalMaxWidth
            DODT.Load();
            DODT->maxWidth = *(float *)FieldValue;
            break;
        case 22: //decalMinHeight
            DODT.Load();
            DODT->minHeight = *(float *)FieldValue;
            break;
        case 23: //decalMaxHeight
            DODT.Load();
            DODT->maxHeight = *(float *)FieldValue;
            break;
        case 24: //decalDepth
            DODT.Load();
            DODT->depth = *(float *)FieldValue;
            break;
        case 25: //decalShininess
            DODT.Load();
            DODT->shininess = *(float *)FieldValue;
            break;
        case 26: //decalScale
            DODT.Load();
            DODT->scale = *(float *)FieldValue;
            break;
        case 27: //decalPasses
            DODT.Load();
            DODT->passes = *(uint8_t *)FieldValue;
            break;
        case 28: //decalFlags
            DODT.Load();
            DODT->flags = *(uint8_t *)FieldValue;
            break;
        case 29: //decalUnused1
            if(ArraySize != 2)
                break;
            DODT.Load();
            DODT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DODT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 30: //decalRed
            DODT.Load();
            DODT->red = *(uint8_t *)FieldValue;
            break;
        case 31: //decalGreen
            DODT.Load();
            DODT->green = *(uint8_t *)FieldValue;
            break;
        case 32: //decalBlue
            DODT.Load();
            DODT->blue = *(uint8_t *)FieldValue;
            break;
        case 33: //decalUnused2
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->unused2 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 34: //dnam Texture Set
            DNAM.Load();
            DNAM.value = *(FORMID *)FieldValue;
            return true;
        case 35: //snam Sound 1
            SNAM.Load();
            SNAM.value = *(FORMID *)FieldValue;
            return true;
        case 36: //nam1 Sound 2
            NAM1.Load();
            NAM1.value = *(FORMID *)FieldValue;
            return true;
        default:
            break;
        }
    return false;
    }

void IPCTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
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
        case 7: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 8: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 9: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 10: //mods Alternate Textures
            if (MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 11: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 12: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->Textures.Unload();
            return;
        case 13: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 14: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 15: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 16: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 17: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 18: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //decalMinWidth
            if (DODT.IsLoaded())
                DODT->minWidth = 0.0; // defaultDODT.minWidth;
            return;
        case 21: //decalMaxWidth
            if (DODT.IsLoaded())
                DODT->maxWidth = 0.0; // defaultDODT.maxWidth;
            return;
        case 22: //decalMinHeight
            if (DODT.IsLoaded())
                DODT->minHeight = 0.0; // defaultDODT.minHeight;
            return;
        case 23: //decalMaxHeight
            if (DODT.IsLoaded())
                DODT->maxHeight = 0.0; // defaultDODT.maxHeight;
            return;
        case 24: //decalDepth
            if (DODT.IsLoaded())
                DODT->depth = 0.0; // defaultDODT.depth;
            return;
        case 25: //decalShininess
            if (DODT.IsLoaded())
                DODT->shininess = 0.0; // defaultDODT.shininess;
            return;
        case 26: //decalScale
            if (DODT.IsLoaded())
                DODT->scale = 0.0; // defaultDODT.scale;
            return;
        case 27: //decalPasses
            if (DODT.IsLoaded())
                DODT->passes = 0; // defaultDODT.passes;
            return;
        case 28: //decalFlags
            if (DODT.IsLoaded())
                DODT->flags = 0; // defaultDODT.flags;
            return;
        case 29: //decalUnused1
            if(DODT.IsLoaded())
                {
                DODT->unused1[0] = 0; // defaultDODT.unused1[0];
                DODT->unused1[1] = 0; // defaultDODT.unused1[1];
                }
            return;
        case 30: //decalRed
            if (DODT.IsLoaded())
                DODT->red = 0; // defaultDODT.red;
            return;
        case 31: //decalGreen
            if (DODT.IsLoaded())
                DODT->green = 0; // defaultDODT.green;
            return;
        case 32: //decalBlue
            if (DODT.IsLoaded())
                DODT->blue = 0; // defaultDODT.blue;
            return;
        case 33: //decalUnused2
            if (DODT.IsLoaded())
                DODT->unused2 = 0; // defaultDODT.unused2;
            return;
        case 34: //dnam Texture Set
            DNAM.Unload();
            return;
        case 35: //snam Sound 1
            SNAM.Unload();
            return;
        case 36: //nam1 Sound 2
            NAM1.Unload();
            return;
        default:
            return;
        }
    }
}