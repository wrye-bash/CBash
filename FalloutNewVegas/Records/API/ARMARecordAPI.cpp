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
#include "..\ARMARecord.h"

namespace FNV
{
UINT32 ARMARecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
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
        case 7: //boundX
            return SINT16_FIELD;
        case 8: //boundY
            return SINT16_FIELD;
        case 9: //boundZ
            return SINT16_FIELD;
        case 10: //full
            return STRING_FIELD;
        case 11: //bmdt Biped Data
            return UINT32_FIELD;
        case 12: //bmdt Biped Data
            return UINT8_FIELD;
        case 13: //bmdt_p Biped Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 3;
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 14: //modPath
            return ISTRING_FIELD;
        case 15: //modt_p
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
        case 16: //mods Alternate Texture
            return ISTRING_FIELD;
        case 17: //mods Alternate Texture
            return FORMID_FIELD;
        case 18: //mods Alternate Texture
            return SINT32_FIELD;
        case 19: //modelFlags
            return UINT8_FIELD;
        case 20: //mod2 Model Filename
            return ISTRING_FIELD;
        case 21: //mo2t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO2T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 22: //mo2s Alternate Texture
            return ISTRING_FIELD;
        case 23: //mo2s Alternate Texture
            return FORMID_FIELD;
        case 24: //mo2s Alternate Texture
            return SINT32_FIELD;
        case 25: //icon Male icon filename
            return ISTRING_FIELD;
        case 26: //mico Male mico filename
            return ISTRING_FIELD;
        case 27: //mod3 Model Filename
            return ISTRING_FIELD;
        case 28: //mo3t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO3T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 29: //mo3s Alternate Texture
            return ISTRING_FIELD;
        case 30: //mo3s Alternate Texture
            return FORMID_FIELD;
        case 31: //mo3s Alternate Texture
            return SINT32_FIELD;
        case 32: //mosd FaceGen Model Flags
            return UINT8_FIELD;
        case 33: //mod4 Model Filename
            return ISTRING_FIELD;
        case 34: //mo4t_p Texture Files Hashes
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MO4T.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
            return UNKNOWN_FIELD;
        case 35: //mo4s Alternate Texture
            return ISTRING_FIELD;
        case 36: //mo4s Alternate Texture
            return FORMID_FIELD;
        case 37: //mo4s Alternate Texture
            return SINT32_FIELD;
        case 38: //ico2 Female icon filename
            return ISTRING_FIELD;
        case 39: //mic2 Female mico filename
            return ISTRING_FIELD;
        case 40: //etyp Equipment Type
            return SINT32_FIELD;
        case 41: //data DATA ,, Struct
            return SINT32_FIELD;
        case 42: //data DATA ,, Struct
            return SINT32_FIELD;
        case 43: //data DATA ,, Struct
            return FLOAT32_FIELD;
        case 44: //dnam DNAM ,, Struct
            return SINT16_FIELD;
        case 45: //dnam DNAM ,, Struct
            return UINT16_FIELD;
        case 46: //dnam_p DNAM ,, Struct
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DNAM.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * ARMARecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //boundX
            return OBND.IsLoaded() ? &OBND->x : NULL;
        case 8: //boundY
            return OBND.IsLoaded() ? &OBND->y : NULL;
        case 9: //boundZ
            return OBND.IsLoaded() ? &OBND->z : NULL;
        case 10: //full
            return FULL.value;
        case 11: //bmdt Biped Data
            return BMDT.IsLoaded() ? &BMDT->value11 : NULL;
        case 12: //bmdt Biped Data
            return BMDT.IsLoaded() ? &BMDT->value12 : NULL;
        case 13: //bmdt_p Biped Data
            *FieldValues = BMDT.IsLoaded() ? &BMDT->value13[0] : NULL;
            return NULL;
        case 14: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 15: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 16: //mods Alternate Texture
            return MODL.IsLoaded() ? MODL->MODS.value : NULL;
        case 17: //mods Alternate Texture
            return MODL.IsLoaded() ? &MODL->MODS->value17 : NULL;
        case 18: //mods Alternate Texture
            return MODL.IsLoaded() ? &MODL->MODS->value18 : NULL;
        case 19: //modelFlags
            return MODL.IsLoaded() ? &MODL->MODD->value19 : NULL;
        case 20: //mod2 Model Filename
            return MOD2.IsLoaded() ? MOD2->MOD2.value : NULL;
        case 21: //mo2t_p Texture Files Hashes
            *FieldValues = (MOD2.IsLoaded()) ? MOD2->MO2T.value : NULL;
            return NULL;
        case 22: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? MOD2->MO2S.value : NULL;
        case 23: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value23 : NULL;
        case 24: //mo2s Alternate Texture
            return MOD2.IsLoaded() ? &MOD2->MO2S->value24 : NULL;
        case 25: //icon Male icon filename
            return ICON.value;
        case 26: //mico Male mico filename
            return MICO.value;
        case 27: //mod3 Model Filename
            return MOD3.IsLoaded() ? MOD3->MOD3.value : NULL;
        case 28: //mo3t_p Texture Files Hashes
            *FieldValues = (MOD3.IsLoaded()) ? MOD3->MO3T.value : NULL;
            return NULL;
        case 29: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? MOD3->MO3S.value : NULL;
        case 30: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value30 : NULL;
        case 31: //mo3s Alternate Texture
            return MOD3.IsLoaded() ? &MOD3->MO3S->value31 : NULL;
        case 32: //mosd FaceGen Model Flags
            return MOD3.IsLoaded() ? &MOD3->MOSD->value32 : NULL;
        case 33: //mod4 Model Filename
            return MOD4.IsLoaded() ? MOD4->MOD4.value : NULL;
        case 34: //mo4t_p Texture Files Hashes
            *FieldValues = (MOD4.IsLoaded()) ? MOD4->MO4T.value : NULL;
            return NULL;
        case 35: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? MOD4->MO4S.value : NULL;
        case 36: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value36 : NULL;
        case 37: //mo4s Alternate Texture
            return MOD4.IsLoaded() ? &MOD4->MO4S->value37 : NULL;
        case 38: //ico2 Female icon filename
            return ICO2.value;
        case 39: //mic2 Female mico filename
            return MIC2.value;
        case 40: //etyp Equipment Type
            return ETYP.IsLoaded() ? &ETYPReq->value40 : NULL;
        case 41: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value41 : NULL;
        case 42: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value42 : NULL;
        case 43: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->value43 : NULL;
        case 44: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value44 : NULL;
        case 45: //dnam DNAM ,, Struct
            return DNAM.IsLoaded() ? &DNAM->value45 : NULL;
        case 46: //dnam_p DNAM ,, Struct
            *FieldValues = DNAM.value;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool ARMARecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
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
        case 7: //boundX
            OBND.Load();
            OBND->x = *(SINT16 *)FieldValue;
            break;
        case 8: //boundY
            OBND.Load();
            OBND->y = *(SINT16 *)FieldValue;
            break;
        case 9: //boundZ
            OBND.Load();
            OBND->z = *(SINT16 *)FieldValue;
            break;
        case 10: //full
            FULL.Copy((STRING)FieldValue);
            break;
        case 11: //bmdt Biped Data
            BMDT.Load();
            BMDT->value11 = *(UINT32 *)FieldValue;
            break;
        case 12: //bmdt Biped Data
            BMDT.Load();
            BMDT->value12 = *(UINT8 *)FieldValue;
            break;
        case 13: //bmdt_p Biped Data
            if(ArraySize != 3)
                break;
            BMDT.Load();
            BMDT->value13[0] = ((UINT8ARRAY)FieldValue)[0];
            BMDT->value13[1] = ((UINT8ARRAY)FieldValue)[1];
            BMDT->value13[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 14: //modPath
            MODL.Load();
            MODL->MODL.Copy((STRING)FieldValue);
            break;
        case 15: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 16: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Copy((STRING)FieldValue);
            break;
        case 17: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value17 = *(FORMID *)FieldValue;
            return true;
        case 18: //mods Alternate Texture
            MODL.Load();
            MODL->MODS.Load();
            MODL->MODS->value18 = *(SINT32 *)FieldValue;
            break;
        case 19: //modelFlags
            MODL.Load();
            MODL->MODD.Load();
            MODL->MODD->value19 = *(UINT8 *)FieldValue;
            break;
        case 20: //mod2 Model Filename
            MOD2.Load();
            MOD2->MOD2.Copy((STRING)FieldValue);
            break;
        case 21: //mo2t_p Texture Files Hashes
            MOD2.Load();
            MOD2->MO2T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 22: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Copy((STRING)FieldValue);
            break;
        case 23: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value23 = *(FORMID *)FieldValue;
            return true;
        case 24: //mo2s Alternate Texture
            MOD2.Load();
            MOD2->MO2S.Load();
            MOD2->MO2S->value24 = *(SINT32 *)FieldValue;
            break;
        case 25: //icon Male icon filename
            ICON.Copy((STRING)FieldValue);
            break;
        case 26: //mico Male mico filename
            MICO.Copy((STRING)FieldValue);
            break;
        case 27: //mod3 Model Filename
            MOD3.Load();
            MOD3->MOD3.Copy((STRING)FieldValue);
            break;
        case 28: //mo3t_p Texture Files Hashes
            MOD3.Load();
            MOD3->MO3T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 29: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Copy((STRING)FieldValue);
            break;
        case 30: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value30 = *(FORMID *)FieldValue;
            return true;
        case 31: //mo3s Alternate Texture
            MOD3.Load();
            MOD3->MO3S.Load();
            MOD3->MO3S->value31 = *(SINT32 *)FieldValue;
            break;
        case 32: //mosd FaceGen Model Flags
            MOD3.Load();
            MOD3->MOSD.Load();
            MOD3->MOSD->value32 = *(UINT8 *)FieldValue;
            break;
        case 33: //mod4 Model Filename
            MOD4.Load();
            MOD4->MOD4.Copy((STRING)FieldValue);
            break;
        case 34: //mo4t_p Texture Files Hashes
            MOD4.Load();
            MOD4->MO4T.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 35: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Copy((STRING)FieldValue);
            break;
        case 36: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value36 = *(FORMID *)FieldValue;
            return true;
        case 37: //mo4s Alternate Texture
            MOD4.Load();
            MOD4->MO4S.Load();
            MOD4->MO4S->value37 = *(SINT32 *)FieldValue;
            break;
        case 38: //ico2 Female icon filename
            ICO2.Copy((STRING)FieldValue);
            break;
        case 39: //mic2 Female mico filename
            MIC2.Copy((STRING)FieldValue);
            break;
        case 40: //etyp Equipment Type
            ETYP.Load();
            ETYPReq->value40 = *(SINT32 *)FieldValue;
            break;
        case 41: //data DATA ,, Struct
            DATA.Load();
            DATA->value41 = *(SINT32 *)FieldValue;
            break;
        case 42: //data DATA ,, Struct
            DATA.Load();
            DATA->value42 = *(SINT32 *)FieldValue;
            break;
        case 43: //data DATA ,, Struct
            DATA.Load();
            DATA->value43 = *(FLOAT32 *)FieldValue;
            break;
        case 44: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value44 = *(SINT16 *)FieldValue;
            break;
        case 45: //dnam DNAM ,, Struct
            DNAM.Load();
            DNAM->value45 = *(UINT16 *)FieldValue;
            break;
        case 46: //dnam_p DNAM ,, Struct
            DNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void ARMARecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //boundX
            if(OBND.IsLoaded())
                OBND->x = defaultOBND.x;
            return;
        case 8: //boundY
            if(OBND.IsLoaded())
                OBND->y = defaultOBND.y;
            return;
        case 9: //boundZ
            if(OBND.IsLoaded())
                OBND->z = defaultOBND.z;
            return;
        case 10: //full
            FULL.Unload();
            return;
        case 11: //bmdt Biped Data
            BMDT.Unload();
            return;
        case 12: //bmdt Biped Data
            BMDT.Unload();
            return;
        case 13: //bmdt_p Biped Data
            BMDT.Unload();
            return;
        case 14: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 15: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 16: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 17: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 18: //mods Alternate Texture
            if(MODL.IsLoaded())
                MODL->MODS.Unload();
            return;
        case 19: //modelFlags
            if(MODL.IsLoaded())
                MODL->MODD.Unload();
            return;
        case 20: //mod2 Model Filename
            if(MOD2.IsLoaded())
                MOD2->MOD2.Unload();
            return;
        case 21: //mo2t_p Texture Files Hashes
            if(MOD2.IsLoaded())
                MOD2->MO2T.Unload();
            return;
        case 22: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 23: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 24: //mo2s Alternate Texture
            if(MOD2.IsLoaded())
                MOD2->MO2S.Unload();
            return;
        case 25: //icon Male icon filename
            ICON.Unload();
            return;
        case 26: //mico Male mico filename
            MICO.Unload();
            return;
        case 27: //mod3 Model Filename
            if(MOD3.IsLoaded())
                MOD3->MOD3.Unload();
            return;
        case 28: //mo3t_p Texture Files Hashes
            if(MOD3.IsLoaded())
                MOD3->MO3T.Unload();
            return;
        case 29: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 30: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 31: //mo3s Alternate Texture
            if(MOD3.IsLoaded())
                MOD3->MO3S.Unload();
            return;
        case 32: //mosd FaceGen Model Flags
            if(MOD3.IsLoaded())
                MOD3->MOSD.Unload();
            return;
        case 33: //mod4 Model Filename
            if(MOD4.IsLoaded())
                MOD4->MOD4.Unload();
            return;
        case 34: //mo4t_p Texture Files Hashes
            if(MOD4.IsLoaded())
                MOD4->MO4T.Unload();
            return;
        case 35: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 36: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 37: //mo4s Alternate Texture
            if(MOD4.IsLoaded())
                MOD4->MO4S.Unload();
            return;
        case 38: //ico2 Female icon filename
            ICO2.Unload();
            return;
        case 39: //mic2 Female mico filename
            MIC2.Unload();
            return;
        case 40: //etyp Equipment Type
            ETYP.Unload();
            return;
        case 41: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 42: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 43: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 44: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 45: //dnam DNAM ,, Struct
            DNAM.Unload();
            return;
        case 46: //dnam_p DNAM ,, Struct
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}