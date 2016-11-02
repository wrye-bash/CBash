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
#include "..\MSETRecord.h"

namespace FNV
{
uint32_t MSETRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //full
            return CB_STRING_FIELD;
        case 8: //nam1 Type
            return CB_UINT32_FIELD;
        case 9: //nam2 Loop (B) / Battle (D) / Day Outer (L)
            return CB_ISTRING_FIELD;
        case 10: //nam3 Explore (D) / Day Middle (L)
            return CB_ISTRING_FIELD;
        case 11: //nam4 Suspense (D) / Day Inner (L)
            return CB_ISTRING_FIELD;
        case 12: //nam5 Night Outer (L)
            return CB_ISTRING_FIELD;
        case 13: //nam6 Night Middle (L)
            return CB_ISTRING_FIELD;
        case 14: //nam7 Night Inner (L)
            return CB_ISTRING_FIELD;
        case 15: //nam8 Loop dB (B) / Battle dB (D) / Day Outer dB (L)
            return CB_FLOAT32_FIELD;
        case 16: //nam9 Explore dB (D) / Day Middle dB (L)
            return CB_FLOAT32_FIELD;
        case 17: //nam0 Suspense dB (D) / Day Inner dB (L)
            return CB_FLOAT32_FIELD;
        case 18: //anam Night Outer dB (L)
            return CB_FLOAT32_FIELD;
        case 19: //bnam Night Middle dB (L)
            return CB_FLOAT32_FIELD;
        case 20: //cnam Night Inner dB (L)
            return CB_FLOAT32_FIELD;
        case 21: //jnam Day Outer Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 22: //knam Day Middle Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 23: //lnam Day Inner Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 24: //mnam Night Outer Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 25: //nnam Night Middle Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 26: //onam Night Inner Boundary % (L)
            return CB_FLOAT32_FIELD;
        case 27: //pnam Enable Flags
            return CB_UINT8_FIELD;
        case 28: //dnam Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
            return CB_FLOAT32_FIELD;
        case 29: //enam Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
            return CB_FLOAT32_FIELD;
        case 30: //fnam Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
            return CB_FLOAT32_FIELD;
        case 31: //gnam Nighttime Max (I)
            return CB_FLOAT32_FIELD;
        case 32: //hnam Intro (B,D) / Daytime (I)
            return CB_FORMID_FIELD;
        case 33: //inam Outro (B,D) / Nighttime (I)
            return CB_FORMID_FIELD;
        case 34: //data_p Unknown
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DATA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * MSETRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //full
            return FULL.value;
        case 8: //nam1 Type
            return NAM1.IsLoaded() ? &NAM1.value : NULL;
        case 9: //nam2 Loop (B) / Battle (D) / Day Outer (L)
            return NAM2.value;
        case 10: //nam3 Explore (D) / Day Middle (L)
            return NAM3.value;
        case 11: //nam4 Suspense (D) / Day Inner (L)
            return NAM4.value;
        case 12: //nam5 Night Outer (L)
            return NAM5.value;
        case 13: //nam6 Night Middle (L)
            return NAM6.value;
        case 14: //nam7 Night Inner (L)
            return NAM7.value;
        case 15: //nam8 Loop dB (B) / Battle dB (D) / Day Outer dB (L)
            return NAM8.IsLoaded() ? &NAM8.value : NULL;
        case 16: //nam9 Explore dB (D) / Day Middle dB (L)
            return NAM9.IsLoaded() ? &NAM9.value : NULL;
        case 17: //nam0 Suspense dB (D) / Day Inner dB (L)
            return NAM0.IsLoaded() ? &NAM0.value : NULL;
        case 18: //anam Night Outer dB (L)
            return ANAM.IsLoaded() ? &ANAM.value : NULL;
        case 19: //bnam Night Middle dB (L)
            return BNAM.IsLoaded() ? &BNAM.value : NULL;
        case 20: //cnam Night Inner dB (L)
            return CNAM.IsLoaded() ? &CNAM.value : NULL;
        case 21: //jnam Day Outer Boundary % (L)
            return JNAM.IsLoaded() ? &JNAM.value : NULL;
        case 22: //knam Day Middle Boundary % (L)
            return KNAM.IsLoaded() ? &KNAM.value : NULL;
        case 23: //lnam Day Inner Boundary % (L)
            return LNAM.IsLoaded() ? &LNAM.value : NULL;
        case 24: //mnam Night Outer Boundary % (L)
            return MNAM.IsLoaded() ? &MNAM.value : NULL;
        case 25: //nnam Night Middle Boundary % (L)
            return NNAM.IsLoaded() ? &NNAM.value : NULL;
        case 26: //onam Night Inner Boundary % (L)
            return ONAM.IsLoaded() ? &ONAM.value : NULL;
        case 27: //pnam Enable Flags
            return PNAM.IsLoaded() ? &PNAM.value : NULL;
        case 28: //dnam Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
            return DNAM.IsLoaded() ? &DNAM.value : NULL;
        case 29: //enam Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
            return ENAM.IsLoaded() ? &ENAM.value : NULL;
        case 30: //fnam Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
            return FNAM.IsLoaded() ? &FNAM.value : NULL;
        case 31: //gnam Nighttime Max (I)
            return GNAM.IsLoaded() ? &GNAM.value : NULL;
        case 32: //hnam Intro (B,D) / Daytime (I)
            return HNAM.IsLoaded() ? &HNAM.value : NULL;
        case 33: //inam Outro (B,D) / Nighttime (I)
            return INAM.IsLoaded() ? &INAM.value : NULL;
        case 34: //data_p Unknown
            *FieldValues = DATA.value;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool MSETRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 8: //nam1 Type
            NAM1.Load();
            NAM1.value = *(uint32_t *)FieldValue;
            break;
        case 9: //nam2 Loop (B) / Battle (D) / Day Outer (L)
            NAM2.Copy((char *)FieldValue);
            break;
        case 10: //nam3 Explore (D) / Day Middle (L)
            NAM3.Copy((char *)FieldValue);
            break;
        case 11: //nam4 Suspense (D) / Day Inner (L)
            NAM4.Copy((char *)FieldValue);
            break;
        case 12: //nam5 Night Outer (L)
            NAM5.Copy((char *)FieldValue);
            break;
        case 13: //nam6 Night Middle (L)
            NAM6.Copy((char *)FieldValue);
            break;
        case 14: //nam7 Night Inner (L)
            NAM7.Copy((char *)FieldValue);
            break;
        case 15: //nam8 Loop dB (B) / Battle dB (D) / Day Outer dB (L)
            NAM8.Load();
            NAM8.value = *(float *)FieldValue;
            break;
        case 16: //nam9 Explore dB (D) / Day Middle dB (L)
            NAM9.Load();
            NAM9.value = *(float *)FieldValue;
            break;
        case 17: //nam0 Suspense dB (D) / Day Inner dB (L)
            NAM0.Load();
            NAM0.value = *(float *)FieldValue;
            break;
        case 18: //anam Night Outer dB (L)
            ANAM.Load();
            ANAM.value = *(float *)FieldValue;
            break;
        case 19: //bnam Night Middle dB (L)
            BNAM.Load();
            BNAM.value = *(float *)FieldValue;
            break;
        case 20: //cnam Night Inner dB (L)
            CNAM.Load();
            CNAM.value = *(float *)FieldValue;
            break;
        case 21: //jnam Day Outer Boundary % (L)
            JNAM.Load();
            JNAM.value = *(float *)FieldValue;
            break;
        case 22: //knam Day Middle Boundary % (L)
            KNAM.Load();
            KNAM.value = *(float *)FieldValue;
            break;
        case 23: //lnam Day Inner Boundary % (L)
            LNAM.Load();
            LNAM.value = *(float *)FieldValue;
            break;
        case 24: //mnam Night Outer Boundary % (L)
            MNAM.Load();
            MNAM.value = *(float *)FieldValue;
            break;
        case 25: //nnam Night Middle Boundary % (L)
            NNAM.Load();
            NNAM.value = *(float *)FieldValue;
            break;
        case 26: //onam Night Inner Boundary % (L)
            ONAM.Load();
            ONAM.value = *(float *)FieldValue;
            break;
        case 27: //pnam Enable Flags
            PNAM.Load();
            PNAM.value = *(uint8_t *)FieldValue;
            break;
        case 28: //dnam Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
            DNAM.Load();
            DNAM.value = *(float *)FieldValue;
            break;
        case 29: //enam Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
            ENAM.Load();
            ENAM.value = *(float *)FieldValue;
            break;
        case 30: //fnam Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
            FNAM.Load();
            FNAM.value = *(float *)FieldValue;
            break;
        case 31: //gnam Nighttime Max (I)
            GNAM.Load();
            GNAM.value = *(float *)FieldValue;
            break;
        case 32: //hnam Intro (B,D) / Daytime (I)
            HNAM.Load();
            HNAM.value = *(FORMID *)FieldValue;
            return true;
        case 33: //inam Outro (B,D) / Nighttime (I)
            INAM.Load();
            INAM.value = *(FORMID *)FieldValue;
            return true;
        case 34: //data_p Unknown
            DATA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void MSETRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 7: //full
            FULL.Unload();
            return;
        case 8: //nam1 Type
            NAM1.Unload();
            return;
        case 9: //nam2 Loop (B) / Battle (D) / Day Outer (L)
            NAM2.Unload();
            return;
        case 10: //nam3 Explore (D) / Day Middle (L)
            NAM3.Unload();
            return;
        case 11: //nam4 Suspense (D) / Day Inner (L)
            NAM4.Unload();
            return;
        case 12: //nam5 Night Outer (L)
            NAM5.Unload();
            return;
        case 13: //nam6 Night Middle (L)
            NAM6.Unload();
            return;
        case 14: //nam7 Night Inner (L)
            NAM7.Unload();
            return;
        case 15: //nam8 Loop dB (B) / Battle dB (D) / Day Outer dB (L)
            NAM8.Unload();
            return;
        case 16: //nam9 Explore dB (D) / Day Middle dB (L)
            NAM9.Unload();
            return;
        case 17: //nam0 Suspense dB (D) / Day Inner dB (L)
            NAM0.Unload();
            return;
        case 18: //anam Night Outer dB (L)
            ANAM.Unload();
            return;
        case 19: //bnam Night Middle dB (L)
            BNAM.Unload();
            return;
        case 20: //cnam Night Inner dB (L)
            CNAM.Unload();
            return;
        case 21: //jnam Day Outer Boundary % (L)
            JNAM.Unload();
            return;
        case 22: //knam Day Middle Boundary % (L)
            KNAM.Unload();
            return;
        case 23: //lnam Day Inner Boundary % (L)
            LNAM.Unload();
            return;
        case 24: //mnam Night Outer Boundary % (L)
            MNAM.Unload();
            return;
        case 25: //nnam Night Middle Boundary % (L)
            NNAM.Unload();
            return;
        case 26: //onam Night Inner Boundary % (L)
            ONAM.Unload();
            return;
        case 27: //pnam Enable Flags
            PNAM.Unload();
            return;
        case 28: //dnam Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
            DNAM.Unload();
            return;
        case 29: //enam Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
            ENAM.Unload();
            return;
        case 30: //fnam Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
            FNAM.Unload();
            return;
        case 31: //gnam Nighttime Max (I)
            GNAM.Unload();
            return;
        case 32: //hnam Intro (B,D) / Daytime (I)
            HNAM.Unload();
            return;
        case 33: //inam Outro (B,D) / Nighttime (I)
            INAM.Unload();
            return;
        case 34: //data_p Unknown
            DATA.Unload();
            return;
        default:
            return;
        }
    }
}