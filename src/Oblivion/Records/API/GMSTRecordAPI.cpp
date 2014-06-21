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
#include "..\GMSTRecord.h"

namespace Ob
{
uint32_t GMSTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
    {
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
            return CB_ISTRING_FIELD;
        case 5: //value
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_STRING_OR_FLOAT32_OR_SINT32_FIELD;
                case 2: //WhichType
                    switch(DATA.format)
                        {
                        case 's':
                            return CB_STRING_FIELD;
                        case 'i':
                            return CB_SINT32_FIELD;
                        case 'f':
                            return CB_FLOAT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * GMSTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    switch(FieldID)
        {
        case 1: //flags1
            return &flags;
        case 2: //fid
            return &formID;
        case 3: //flags2
            return &flagsUnk;
        case 4: //eid
            return EDID.value;
        case 5: //value
            switch(DATA.format)
                {
                case 's':
                    return DATA.s;
                case 'i':
                    return &DATA.i;
                case 'f':
                    return &DATA.f;
                default:
                    return NULL;
                }
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool GMSTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 2: //fid
            formID = *(FORMID *)FieldValue;
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //value
            switch(DATA.format)
                {
                case 's':
                    if(FieldValue != NULL)
                        {
                        delete []DATA.s;
                        ArraySize = (uint32_t)strlen((char *)FieldValue) + 1;
                        DATA.s = new char[ArraySize];
                        strcpy_s(DATA.s, ArraySize, (char *)FieldValue);
                        }
                    break;
                case 'i':
                    DATA.i = *(int32_t *)FieldValue;
                    break;
                case 'f':
                    DATA.f = *(float *)FieldValue;
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

void GMSTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GMSTDATA defaultDATA;
    uint32_t ArraySize = 0;

    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            EDID.Unload();
            return;
        case 5: //value
            switch(DATA.format)
                {
                case 's':
                    delete []DATA.s;
                    DATA.s = defaultDATA.s;
                    if(defaultDATA.s != NULL)
                        {
                        ArraySize = (uint32_t)strlen(defaultDATA.s) + 1;
                        DATA.s = new char[ArraySize];
                        strcpy_s(DATA.s, ArraySize, defaultDATA.s);
                        }
                    return;
                case 'i':
                    DATA.i = defaultDATA.i;
                    return;
                case 'f':
                    DATA.f = defaultDATA.f;
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