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
#include "..\PERKRecord.h"

namespace FNV
{
uint32_t PERKRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 8: //description
            return CB_STRING_FIELD;
        case 9: //iconPath
            return CB_ISTRING_FIELD;
        case 10: //smallIconPath
            return CB_ISTRING_FIELD;
        case 11: //ctda Conditions
            return CB_UINT8_FIELD;
        case 12: //ctda_p Conditions
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
        case 13: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 14: //ctda Conditions
            return CB_UINT32_FIELD;
        case 15: //ctda_p Conditions
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
        case 16: //ctda_p Conditions
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
        case 17: //ctda Conditions
            return CB_UINT32_FIELD;
        case 18: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 19: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 20: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 21: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 22: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 23: //data DATA ,, Struct
            return CB_UINT8_FIELD;
        case 24: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 25: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 26: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 27: //prke PRKE ,, Struct
            return CB_FORMID_FIELD;
        case 28: //prke PRKE ,, Struct
            return CB_FORMID_FIELD;
        case 29: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 30: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 31: //prke PRKE ,, Struct
            return CB_UINT8_FIELD;
        case 32: //prkc Run On
            return CB_SINT8_FIELD;
        case 33: //ctda Conditions
            return CB_UINT8_FIELD;
        case 34: //ctda_p Conditions
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
        case 35: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 36: //ctda Conditions
            return CB_UINT32_FIELD;
        case 37: //ctda_p Conditions
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
        case 38: //ctda_p Conditions
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
        case 39: //ctda Conditions
            return CB_UINT32_FIELD;
        case 40: //ctda Conditions
            return CB_UNKNOWN_FIELD; // UNPARSED_FIELD;
        case 41: //epft Type
            return CB_UINT8_FIELD;
        case 42: //data Leveled Item
            return CB_FORMID_FIELD;
        case 43: //epf2 Button Label
            return CB_ISTRING_FIELD;
        case 44: //epf3 Script Flags
            return CB_UINT16_FIELD;
        case 45: //schr_p Basic Script Data
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
        case 46: //schr Basic Script Data
            return CB_UINT32_FIELD;
        case 47: //schr Basic Script Data
            return CB_UINT32_FIELD;
        case 48: //schr Basic Script Data
            return CB_UINT32_FIELD;
        case 49: //schr Basic Script Data
            return CB_UINT16_FIELD;
        case 50: //schr Basic Script Data
            return CB_UINT16_FIELD;
        case 51: //scda_p Compiled Embedded Script
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 0; // SCDA.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 52: //sctx Embedded Script Source
            return CB_ISTRING_FIELD;
        case 53: //slsd Local Variable Data
            return CB_UINT32_FIELD;
        case 54: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 12;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 55: //slsd Local Variable Data
            return CB_UINT8_FIELD;
        case 56: //slsd_p Local Variable Data
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 7;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 57: //scvr Name
            return CB_ISTRING_FIELD;
        case 58: //scro Global Reference
            return CB_FORMID_FIELD;
        case 59: //scrv Local Variable
            return CB_UINT32_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * PERKRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 8: //description
            return DESC.value;
        case 9: //iconPath
            return ICON.value;
        case 10: //smallIconPath
            return MICO.value;
        case 11: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value11 : NULL;
        case 12: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value12[0] : NULL;
            return NULL;
        case 13: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD13;
        case 14: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value14 : NULL;
        case 15: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value15[0] : NULL;
            return NULL;
        case 16: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDA->value16[0] : NULL;
            return NULL;
        case 17: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDA->value17 : NULL;
        case 18: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD18;
        case 19: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->trait : NULL;
        case 20: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->minLevel : NULL;
        case 21: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->ranks : NULL;
        case 22: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->playable : NULL;
        case 23: //data DATA ,, Struct
            return DATA.IsLoaded() ? &DATA->hidden : NULL;
        case 24: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value24 : NULL;
        case 25: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value25 : NULL;
        case 26: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value26 : NULL;
        case 27: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value27 : NULL;
        case 28: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value28 : NULL;
        case 29: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value29 : NULL;
        case 30: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value30 : NULL;
        case 31: //prke PRKE ,, Struct
            return NULL;
            //return PRKE.IsLoaded() ? &PRKE->value31 : NULL;
        case 32: //prkc Run On
            return NULL;
            //return PRKC.IsLoaded() ? &PRKC->value32 : NULL;
        case 33: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDAsReq->value33 : NULL;
        case 34: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDAsReq->value34[0] : NULL;
            return NULL;
        case 35: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD35;
        case 36: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDAsReq->value36 : NULL;
        case 37: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDAsReq->value37[0] : NULL;
            return NULL;
        case 38: //ctda_p Conditions
            //*FieldValues = CTDA.IsLoaded() ? &CTDAsReq->value38[0] : NULL;
            return NULL;
        case 39: //ctda Conditions
            return NULL;
            //return CTDA.IsLoaded() ? &CTDAsReq->value39 : NULL;
        case 40: //ctda Conditions
            return NULL; // UNPARSEDGET_FIELD40;
        case 41: //epft Type
            return NULL;
            //return EPFT.IsLoaded() ? &EPFT->EPFT->value41 : NULL;
        case 42: //data Leveled Item
            return NULL;
            //return EPFT.IsLoaded() ? &EPFT->DATA->value42 : NULL;
        case 43: //epf2 Button Label
            return NULL;
            //return EPF2.value;
        case 44: //epf3 Script Flags
            return NULL;
            //return EPF3.IsLoaded() ? &EPF3->value44 : NULL;
        case 45: //schr_p Basic Script Data
            //*FieldValues = SCHR.IsLoaded() ? &SCHR->SCHR->value45[0] : NULL;
            return NULL;
        case 46: //schr Basic Script Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCHR->value46 : NULL;
        case 47: //schr Basic Script Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCHR->value47 : NULL;
        case 48: //schr Basic Script Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCHR->value48 : NULL;
        case 49: //schr Basic Script Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCHR->value49 : NULL;
        case 50: //schr Basic Script Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCHR->value50 : NULL;
        case 51: //scda_p Compiled Embedded Script
            //*FieldValues = (SCHR.IsLoaded()) ? SCHR->SCDA.value : NULL;
            return NULL;
        case 52: //sctx Embedded Script Source
            return NULL;
            //return SCHR.IsLoaded() ? SCHR->SCTX.value : NULL;
        case 53: //slsd Local Variable Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SLSD->value53 : NULL;
        case 54: //slsd_p Local Variable Data
            //*FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value54[0] : NULL;
            return NULL;
        case 55: //slsd Local Variable Data
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SLSD->value55 : NULL;
        case 56: //slsd_p Local Variable Data
            //*FieldValues = SCHR.IsLoaded() ? &SCHR->SLSD->value56[0] : NULL;
            return NULL;
        case 57: //scvr Name
            return NULL;
            //return SCHR.IsLoaded() ? SCHR->SCVR.value : NULL;
        case 58: //scro Global Reference
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCRO->value58 : NULL;
        case 59: //scrv Local Variable
            return NULL;
            //return SCHR.IsLoaded() ? &SCHR->SCRV->value59 : NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool PERKRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 8: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 9: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 10: //smallIconPath
            MICO.Copy((char *)FieldValue);
            break;
        case 11: //ctda Conditions
            //CTDA.Load();
            //CTDA->value11 = *(uint8_t *)FieldValue;
            break;
        case 12: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            //CTDA.Load();
            //CTDA->value12[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value12[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value12[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 13: //ctda Conditions
            //return UNPARSEDGET_FIELD13;
        case 14: //ctda Conditions
            //CTDA.Load();
            //CTDA->value14 = *(uint32_t *)FieldValue;
            break;
        case 15: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDA->value15[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value15[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value15[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDA->value15[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 16: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDA->value16[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDA->value16[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDA->value16[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDA->value16[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 17: //ctda Conditions
            //CTDA.Load();
            //CTDA->value17 = *(uint32_t *)FieldValue;
            break;
        case 18: //ctda Conditions
            //return UNPARSEDGET_FIELD18;
            break;
        case 19: //data DATA ,, Struct
            DATA.Load();
            DATA->trait = *(uint8_t *)FieldValue;
            break;
        case 20: //data DATA ,, Struct
            DATA.Load();
            DATA->minLevel = *(uint8_t *)FieldValue;
            break;
        case 21: //data DATA ,, Struct
            DATA.Load();
            DATA->ranks = *(uint8_t *)FieldValue;
            break;
        case 22: //data DATA ,, Struct
            DATA.Load();
            DATA->playable = *(uint8_t *)FieldValue;
            break;
        case 23: //data DATA ,, Struct
            DATA.Load();
            DATA->hidden = *(uint8_t *)FieldValue;
            break;
        case 24: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value24 = *(uint8_t *)FieldValue;
            break;
        case 25: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value25 = *(uint8_t *)FieldValue;
            break;
        case 26: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value26 = *(uint8_t *)FieldValue;
            break;
        case 27: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value27 = *(FORMID *)FieldValue;
            return true;
        case 28: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value28 = *(FORMID *)FieldValue;
            return true;
        case 29: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value29 = *(uint8_t *)FieldValue;
            break;
        case 30: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value30 = *(uint8_t *)FieldValue;
            break;
        case 31: //prke PRKE ,, Struct
            //PRKE.Load();
            //PRKE->value31 = *(uint8_t *)FieldValue;
            break;
        case 32: //prkc Run On
            //PRKC.Load();
            //PRKC->value32 = *(int8_t *)FieldValue;
            break;
        case 33: //ctda Conditions
            //CTDA.Load();
            //CTDAsReq->value33 = *(uint8_t *)FieldValue;
            break;
        case 34: //ctda_p Conditions
            if(ArraySize != 3)
                break;
            //CTDA.Load();
            //CTDAsReq->value34[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAsReq->value34[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAsReq->value34[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 35: //ctda Conditions
            //return UNPARSEDGET_FIELD35;
        case 36: //ctda Conditions
            //CTDA.Load();
            //CTDAsReq->value36 = *(uint32_t *)FieldValue;
            break;
        case 37: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDAsReq->value37[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAsReq->value37[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAsReq->value37[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAsReq->value37[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 38: //ctda_p Conditions
            if(ArraySize != 4)
                break;
            //CTDA.Load();
            //CTDAsReq->value38[0] = ((UINT8ARRAY)FieldValue)[0];
            //CTDAsReq->value38[1] = ((UINT8ARRAY)FieldValue)[1];
            //CTDAsReq->value38[2] = ((UINT8ARRAY)FieldValue)[2];
            //CTDAsReq->value38[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 39: //ctda Conditions
            //CTDA.Load();
            //CTDAsReq->value39 = *(uint32_t *)FieldValue;
            break;
        case 40: //ctda Conditions
            //return UNPARSEDGET_FIELD40;
        case 41: //epft Type
            //EPFT.Load();
            //EPFT->EPFT.Load();
            //EPFT->EPFT->value41 = *(uint8_t *)FieldValue;
            break;
        case 42: //data Leveled Item
            //EPFT.Load();
            //EPFT->DATA.Load();
            //EPFT->DATA->value42 = *(FORMID *)FieldValue;
            return true;
        case 43: //epf2 Button Label
            //EPF2.Copy((char *)FieldValue);
            break;
        case 44: //epf3 Script Flags
            //EPF3.Load();
            //EPF3->value44 = *(uint16_t *)FieldValue;
            break;
        case 45: //schr_p Basic Script Data
            if(ArraySize != 4)
                break;
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value45[0] = ((UINT8ARRAY)FieldValue)[0];
            //SCHR->SCHR->value45[1] = ((UINT8ARRAY)FieldValue)[1];
            //SCHR->SCHR->value45[2] = ((UINT8ARRAY)FieldValue)[2];
            //SCHR->SCHR->value45[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 46: //schr Basic Script Data
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value46 = *(uint32_t *)FieldValue;
            break;
        case 47: //schr Basic Script Data
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value47 = *(uint32_t *)FieldValue;
            break;
        case 48: //schr Basic Script Data
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value48 = *(uint32_t *)FieldValue;
            break;
        case 49: //schr Basic Script Data
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value49 = *(uint16_t *)FieldValue;
            break;
        case 50: //schr Basic Script Data
            //SCHR.Load();
            //SCHR->SCHR.Load();
            //SCHR->SCHR->value50 = *(uint16_t *)FieldValue;
            break;
        case 51: //scda_p Compiled Embedded Script
            //SCHR.Load();
            //SCHR->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 52: //sctx Embedded Script Source
            //SCHR.Load();
            //SCHR->SCTX.Copy((char *)FieldValue);
            break;
        case 53: //slsd Local Variable Data
            //SCHR.Load();
            //SCHR->SLSD.Load();
            //SCHR->SLSD->value53 = *(uint32_t *)FieldValue;
            break;
        case 54: //slsd_p Local Variable Data
            if(ArraySize != 12)
                break;
            //SCHR.Load();
            //SCHR->SLSD.Load();
            //SCHR->SLSD->value54[0] = ((UINT8ARRAY)FieldValue)[0];
            //SCHR->SLSD->value54[1] = ((UINT8ARRAY)FieldValue)[1];
            //SCHR->SLSD->value54[2] = ((UINT8ARRAY)FieldValue)[2];
            //SCHR->SLSD->value54[3] = ((UINT8ARRAY)FieldValue)[3];
            //SCHR->SLSD->value54[4] = ((UINT8ARRAY)FieldValue)[4];
            //SCHR->SLSD->value54[5] = ((UINT8ARRAY)FieldValue)[5];
            //SCHR->SLSD->value54[6] = ((UINT8ARRAY)FieldValue)[6];
            //SCHR->SLSD->value54[7] = ((UINT8ARRAY)FieldValue)[7];
            //SCHR->SLSD->value54[8] = ((UINT8ARRAY)FieldValue)[8];
            //SCHR->SLSD->value54[9] = ((UINT8ARRAY)FieldValue)[9];
            //SCHR->SLSD->value54[10] = ((UINT8ARRAY)FieldValue)[10];
            //SCHR->SLSD->value54[11] = ((UINT8ARRAY)FieldValue)[11];
            break;
        case 55: //slsd Local Variable Data
            //SCHR.Load();
            //SCHR->SLSD.Load();
            //SCHR->SLSD->value55 = *(uint8_t *)FieldValue;
            break;
        case 56: //slsd_p Local Variable Data
            if(ArraySize != 7)
                break;
            //SCHR.Load();
            //SCHR->SLSD.Load();
            //SCHR->SLSD->value56[0] = ((UINT8ARRAY)FieldValue)[0];
            //SCHR->SLSD->value56[1] = ((UINT8ARRAY)FieldValue)[1];
            //SCHR->SLSD->value56[2] = ((UINT8ARRAY)FieldValue)[2];
            //SCHR->SLSD->value56[3] = ((UINT8ARRAY)FieldValue)[3];
            //SCHR->SLSD->value56[4] = ((UINT8ARRAY)FieldValue)[4];
            //SCHR->SLSD->value56[5] = ((UINT8ARRAY)FieldValue)[5];
            //SCHR->SLSD->value56[6] = ((UINT8ARRAY)FieldValue)[6];
            break;
        case 57: //scvr Name
            //SCHR.Load();
            //SCHR->SCVR.Copy((char *)FieldValue);
            break;
        case 58: //scro Global Reference
            //SCHR.Load();
            //SCHR->SCRO.Load();
            //SCHR->SCRO->value58 = *(FORMID *)FieldValue;
            return true;
        case 59: //scrv Local Variable
            //SCHR.Load();
            //SCHR->SCRV.Load();
            //SCHR->SCRV->value59 = *(uint32_t *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void PERKRecord::DeleteField(FIELD_IDENTIFIERS)
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
        case 8: //description
            DESC.Unload();
            return;
        case 9: //iconPath
            ICON.Unload();
            return;
        case 10: //smallIconPath
            MICO.Unload();
            return;
        case 11: //ctda Conditions
            CTDA.Unload();
            return;
        case 12: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 13: //ctda Conditions
            return; // UNPARSEDDEL_FIELD13;
        case 14: //ctda Conditions
            CTDA.Unload();
            return;
        case 15: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 16: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 17: //ctda Conditions
            CTDA.Unload();
            return;
        case 18: //ctda Conditions
            return; // UNPARSEDDEL_FIELD18;
        case 19: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 20: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 21: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 22: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 23: //data DATA ,, Struct
            DATA.Unload();
            return;
        case 24: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 25: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 26: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 27: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 28: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 29: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 30: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 31: //prke PRKE ,, Struct
            PRKE.Unload();
            return;
        case 32: //prkc Run On
            //PRKC.Unload();
            return;
        case 33: //ctda Conditions
            CTDA.Unload();
            return;
        case 34: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 35: //ctda Conditions
            return; // UNPARSEDDEL_FIELD35;
        case 36: //ctda Conditions
            CTDA.Unload();
            return;
        case 37: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 38: //ctda_p Conditions
            CTDA.Unload();
            return;
        case 39: //ctda Conditions
            CTDA.Unload();
            return;
        case 40: //ctda Conditions
            return; // UNPARSEDDEL_FIELD40;
        case 41: //epft Type
            //if(EPFT.IsLoaded())
            //    EPFT->EPFT.Unload();
            return;
        case 42: //data Leveled Item
            //if(EPFT.IsLoaded())
            //    EPFT->DATA.Unload();
            return;
        case 43: //epf2 Button Label
            //EPF2.Unload();
            return;
        case 44: //epf3 Script Flags
            //EPF3.Unload();
            return;
        case 45: //schr_p Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 46: //schr Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 47: //schr Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 48: //schr Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 49: //schr Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 50: //schr Basic Script Data
            //if(SCHR.IsLoaded())
            //    SCHR->SCHR.Unload();
            return;
        case 51: //scda_p Compiled Embedded Script
            //if(SCHR.IsLoaded())
            //    SCHR->SCDA.Unload();
            return;
        case 52: //sctx Embedded Script Source
            //if(SCHR.IsLoaded())
            //    SCHR->SCTX.Unload();
            return;
        case 53: //slsd Local Variable Data
            //if(SCHR.IsLoaded())
            //    SCHR->SLSD.Unload();
            return;
        case 54: //slsd_p Local Variable Data
            //if(SCHR.IsLoaded())
            //    SCHR->SLSD.Unload();
            return;
        case 55: //slsd Local Variable Data
            //if(SCHR.IsLoaded())
            //    SCHR->SLSD.Unload();
            return;
        case 56: //slsd_p Local Variable Data
            //if(SCHR.IsLoaded())
            //    SCHR->SLSD.Unload();
            return;
        case 57: //scvr Name
            //if(SCHR.IsLoaded())
            //    SCHR->SCVR.Unload();
            return;
        case 58: //scro Global Reference
            //if(SCHR.IsLoaded())
            //    SCHR->SCRO.Unload();
            return;
        case 59: //scrv Local Variable
            //if(SCHR.IsLoaded())
            //    SCHR->SCRV.Unload();
            return;
        default:
            return;
        }
    }
}