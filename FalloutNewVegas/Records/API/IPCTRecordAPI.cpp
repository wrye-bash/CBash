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
#include "..\IPCTRecord.h"

namespace FNV
{
UINT32 IPCTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //versionControl1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //formVersion
            return UINT16_FIELD;
        case 6: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 7: //modPath
            return ISTRING_FIELD;
        case 8: //modb
            return FLOAT32_FIELD;
        case 9: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 10: //altTextures
            if(!MODL.IsLoaded())
                return UNKNOWN_FIELD;

            if(ListFieldID == 0) //altTextures
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return LIST_FIELD;
                    case 1: //fieldSize
                        return MODL->Textures.size();
                    default:
                        return UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= MODL->Textures.size())
                return UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name
                    return STRING_FIELD;
                case 2: //texture
                    return FORMID_FIELD;
                case 3: //index
                    return SINT32_FIELD;
                default:
                    return UNKNOWN_FIELD;
                }

        case 13: //modelFlags
            return UINT8_FIELD;
        case 14: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 15: //data DATA ,, Struct
            return UINT32_FIELD;
        case 16: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 17: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 18: //data DATA ,, Struct
            return UINT32_FIELD;
        case 19: //data DATA ,, Struct
            return UINT32_FIELD;
        case 20: //decalMinWidth
            return FLOAT32_FIELD;
        case 21: //decalMaxWidth
            return FLOAT32_FIELD;
        case 22: //decalMinHeight
            return FLOAT32_FIELD;
        case 23: //decalMaxHeight
            return FLOAT32_FIELD;
        case 24: //decalDepth
            return FLOAT32_FIELD;
        case 25: //decalShininess
            return FLOAT32_FIELD;
        case 26: //decalScale
            return FLOAT32_FIELD;
        case 27: //decalPasses
            return UINT8_FIELD;
        case 28: //decalFlags
            return UINT8_FLAG_FIELD;
        case 29: //decalUnused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DODT.IsLoaded() ? 2 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 30: //decalRed
            return UINT8_FIELD;
        case 31: //decalGreen
            return UINT8_FIELD;
        case 32: //decalBlue
            return UINT8_FIELD;
        case 33: //decalUnused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DODT.IsLoaded() ? 1 : 0;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 34: //dnam Texture Set
            return FORMID_FIELD;
        case 35: //snam Sound 1
            return FORMID_FIELD;
        case 36: //nam1 Sound 2
            return FORMID_FIELD;
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
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
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 11: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value11 : NULL;
        case 12: //mods Alternate Textures
            return MODL.IsLoaded() ? &MODL->MODS->value12 : NULL;
        case 13: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value13 : NULL;
        case 14: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value14 : NULL;
        case 15: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value15 : NULL;
        case 16: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value16 : NULL;
        case 17: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value17 : NULL;
        case 18: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value18 : NULL;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value19 : NULL;
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
            return DNAM.IsLoaded() ? &DNAM->value34 : NULL;
        case 35: //snam Sound 1
            return SNAM.IsLoaded() ? &SNAM->value35 : NULL;
        case 36: //nam1 Sound 2
            return NAM1.IsLoaded() ? &NAM1->value36 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool IPCTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
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
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //formVersion
            formVersion = *(UINT16 *)FieldValue;
            break;
        case 6: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 7: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 8: //modb
            MODL.Load();
            MODL->MODB.value = *(FLOAT32 *)FieldValue;
            break;
        case 9: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 11: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value11 = *(FORMID *)FieldValue;
            return true;
        case 12: //mods Alternate Textures
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value12 = *(SINT32 *)FieldValue;
            break;
        case 13: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value13 = *(UINT8 *)FieldValue;
            break;
        case 14: //data DATA ,, Struct
            DATA.Load();
            DATA->value14 = *(FLOAT32 *)FieldValue;
            break;
        case 15: //data DATA ,, Struct
            DATA.Load();
            DATA->value15 = *(UINT32 *)FieldValue;
            break;
        case 16: //data DATA ,, Struct
            DATA.Load();
            DATA->value16 = *(FLOAT32 *)FieldValue;
            break;
        case 17: //data DATA ,, Struct
            DATA.Load();
            DATA->value17 = *(FLOAT32 *)FieldValue;
            break;
        case 18: //data DATA ,, Struct
            DATA.Load();
            DATA->value18 = *(UINT32 *)FieldValue;
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->value19 = *(UINT32 *)FieldValue;
            break;
        case 20: //decalMinWidth
            DODT.Load();
            DODT->minWidth = *(FLOAT32 *)FieldValue;
            break;
        case 21: //decalMaxWidth
            DODT.Load();
            DODT->maxWidth = *(FLOAT32 *)FieldValue;
            break;
        case 22: //decalMinHeight
            DODT.Load();
            DODT->minHeight = *(FLOAT32 *)FieldValue;
            break;
        case 23: //decalMaxHeight
            DODT.Load();
            DODT->maxHeight = *(FLOAT32 *)FieldValue;
            break;
        case 24: //decalDepth
            DODT.Load();
            DODT->depth = *(FLOAT32 *)FieldValue;
            break;
        case 25: //decalShininess
            DODT.Load();
            DODT->shininess = *(FLOAT32 *)FieldValue;
            break;
        case 26: //decalScale
            DODT.Load();
            DODT->scale = *(FLOAT32 *)FieldValue;
            break;
        case 27: //decalPasses
            DODT.Load();
            DODT->passes = *(UINT8 *)FieldValue;
            break;
        case 28: //decalFlags
            DODT.Load();
            DODT->flags = *(UINT8 *)FieldValue;
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
            DODT->red = *(UINT8 *)FieldValue;
            break;
        case 31: //decalGreen
            DODT.Load();
            DODT->green = *(UINT8 *)FieldValue;
            break;
        case 32: //decalBlue
            DODT.Load();
            DODT->blue = *(UINT8 *)FieldValue;
            break;
        case 33: //decalUnused2
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->unused2 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 34: //dnam Texture Set
            DNAM.Load();
            DNAM->value34 = *(FORMID *)FieldValue;
            return true;
        case 35: //snam Sound 1
            SNAM.Load();
            SNAM->value35 = *(FORMID *)FieldValue;
            return true;
        case 36: //nam1 Sound 2
            NAM1.Load();
            NAM1->value36 = *(FORMID *)FieldValue;
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
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 11: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 12: //mods Alternate Textures
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
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
            if(DODT.IsLoaded())
                DODT->minWidth = defaultDODT.minWidth;
            return;
        case 21: //decalMaxWidth
            if(DODT.IsLoaded())
                DODT->maxWidth = defaultDODT.maxWidth;
            return;
        case 22: //decalMinHeight
            if(DODT.IsLoaded())
                DODT->minHeight = defaultDODT.minHeight;
            return;
        case 23: //decalMaxHeight
            if(DODT.IsLoaded())
                DODT->maxHeight = defaultDODT.maxHeight;
            return;
        case 24: //decalDepth
            if(DODT.IsLoaded())
                DODT->depth = defaultDODT.depth;
            return;
        case 25: //decalShininess
            if(DODT.IsLoaded())
                DODT->shininess = defaultDODT.shininess;
            return;
        case 26: //decalScale
            if(DODT.IsLoaded())
                DODT->scale = defaultDODT.scale;
            return;
        case 27: //decalPasses
            if(DODT.IsLoaded())
                DODT->passes = defaultDODT.passes;
            return;
        case 28: //decalFlags
            if(DODT.IsLoaded())
                DODT->flags = defaultDODT.flags;
            return;
        case 29: //decalUnused1
            if(DODT.IsLoaded())
                {
                DODT->unused1[0] = defaultDODT.unused1[0];
                DODT->unused1[1] = defaultDODT.unused1[1];
                }
            return;
        case 30: //decalRed
            if(DODT.IsLoaded())
                DODT->red = defaultDODT.red;
            return;
        case 31: //decalGreen
            if(DODT.IsLoaded())
                DODT->green = defaultDODT.green;
            return;
        case 32: //decalBlue
            if(DODT.IsLoaded())
                DODT->blue = defaultDODT.blue;
            return;
        case 33: //decalUnused2
            if(DODT.IsLoaded())
                DODT->unused2 = defaultDODT.unused2;
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