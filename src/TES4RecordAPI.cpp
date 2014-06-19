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
#include "Common.h"
#include "TES4Record.h"

uint32_t TES4Record::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return MISSING_FIELD;
        case 3: //flags2 or versionControl1 for FNV
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;// UINT32_FLAG_FIELD; for Ob
                case 1: //fieldSize
                    return 4;
                default:
                    return UNKNOWN_FIELD;
                }
        case 4: //eid
            return MISSING_FIELD;
        case 5: //version
            return FLOAT32_FIELD;
        case 6: //numRecords
            return UINT32_FIELD;
        case 7: //nextObject
            return UINT32_FIELD;
        case 8: //ofst_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OFST.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 9: //dele_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return DELE.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        case 10: //author
            return STRING_FIELD;
        case 11: //description
            return STRING_FIELD;
        case 12: //masters
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return ISTRING_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)MAST.size();
                default:
                    return UNKNOWN_FIELD;
                }
        case 13: //DATA
            return JUNK_FIELD;
        //FNV Specific
        case 14: //formVersion
            return UINT16_FIELD;
        case 15: //versionControl2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return 2;
                default:
                    return UNKNOWN_FIELD;
                }
        case 16: //overrides
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)ONAM.value.size();
                default:
                    return UNKNOWN_FIELD;
                }
        case 17: //screenshot_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return SCRN.GetSize();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    }

void * TES4Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 3: //flags2
            if(whichGame == eIsOblivion)
                return &flagsUnk;
            else
                {
                *FieldValues = &flagsUnk;
                return NULL;
                }
        case 5: //version
            return &HEDR.value.version;
        case 6: //numRecords
            return &HEDR.value.numRecords;
        case 7: //nextObject
            return &HEDR.value.nextObject;
        case 8: //ofst_p
            *FieldValues = OFST.value;
            return NULL;
        case 9: //dele_p
            *FieldValues = DELE.value;
            return NULL;
        case 10: //author
            return CNAM.value;
        case 11: //description
            return SNAM.value;
        case 12: //masters
            for(uint32_t p = 0;p < MAST.size();p++)
                FieldValues[p] = MAST[p];
            return NULL;
        case 13: //DATA
            return NULL;
        //FNV Specific
        case 14: //formVersion
            return &formVersion;
        case 15: //versionControl2
            *FieldValues = &versionControl2[0];
            return NULL;
        case 16: //overrides
            *FieldValues = ONAM.value.size() ? &ONAM.value[0] : NULL;
            return NULL;
        case 17: //screenshot_p
            *FieldValues = SCRN.value;
            return NULL;
        default:
            return NULL;
        }
    }

bool TES4Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 5: //version
            HEDR.value.version = *(float *)FieldValue;
            break;
        case 6: //numRecords
            HEDR.value.numRecords = *(uint32_t *)FieldValue;
            break;
        case 7: //nextObject
            HEDR.value.nextObject = *(uint32_t *)FieldValue;
            break;
        case 8: //ofst_p
            OFST.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 9: //dele_p
            DELE.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //author
            CNAM.Copy((char *)FieldValue);
            break;
        case 11: //description
            SNAM.TruncateCopy((char *)FieldValue, 512);
            break;
        case 12: //masters
            //Good chance of breaking the plugin if called. Might be better to disallow.
            //Or atleast try and fix things up on this side.
            for(uint32_t x = 0; x < MAST.size(); x++)
                delete []MAST[x];

            MAST.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                {
                uint32_t size = (uint32_t)strlen(((STRINGARRAY)FieldValue)[x]) + 1;
                MAST[x] = new char[size];
                memcpy(MAST[x], ((STRINGARRAY)FieldValue)[x], size);
                }
            break;
        //FNV Specific
        case 14: //formVersion
            formVersion = *(uint16_t *)FieldValue;
            break;
        case 15: //versionControl2
            if(ArraySize != 2)
                break;
            versionControl2[0] = ((UINT8ARRAY)FieldValue)[0];
            versionControl2[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 16: //overrides
            ONAM.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                ONAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 17: //screenshot_p
            SCRN.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void TES4Record::DeleteField(FIELD_IDENTIFIERS)
    {
    TES4HEDR defaultHEDR;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 5: //version
            HEDR.value.version = defaultHEDR.version;
            return;
        case 6: //numRecords
            HEDR.value.numRecords = defaultHEDR.numRecords;
            return;
        case 7: //nextObject
            HEDR.value.nextObject = defaultHEDR.nextObject;
            return;
        case 8: //ofst_p
            OFST.Unload();
            return;
        case 9: //dele_p
            DELE.Unload();
            return;
        case 10: //author
            CNAM.Unload();
            return;
        case 11: //description
            SNAM.Unload();
            return;
        case 12: //masters
            //Good chance of breaking the plugin if called. Might be better to disallow.
            //Or atleast try and fix things up on this side.
            for(uint32_t x = 0; x < MAST.size(); x++)
                delete []MAST[x];
            MAST.clear();
            return;
        //FNV Specific
        case 14: //formVersion
            formVersion = 0;
            return;
        case 15: //versionControl2
            versionControl2[0] = 0;
            versionControl2[1] = 0;
            return;
        case 16: //overrides
            ONAM.Unload();
            return;
        case 17: //screenshot_p
            SCRN.Unload();
            return;
        default:
            return;
        }
    }