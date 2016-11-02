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
#include "..\SKILRecord.h"

namespace Ob
{
uint32_t SKILRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //skill
            return CB_SINT32_FIELD;
        case 6: //description
            return CB_STRING_FIELD;
        case 7: //iconPath
            return CB_ISTRING_FIELD;
        case 8: //action
            return CB_SINT32_FIELD;
        case 9: //attribute
            return CB_SINT32_FIELD;
        case 10: //specialization
            return CB_UINT32_FIELD;
        case 11: //use0
            return CB_FLOAT32_FIELD;
        case 12: //use1
            return CB_FLOAT32_FIELD;
        case 13: //apprentice
            return CB_STRING_FIELD;
        case 14: //journeyman
            return CB_STRING_FIELD;
        case 15: //expert
            return CB_STRING_FIELD;
        case 16: //master
            return CB_STRING_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * SKILRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //skill
            return &INDX.value;
        case 6: //description
            return DESC.value;
        case 7: //iconPath
            return ICON.value;
        case 8: //action
            return &DATA.value.action;
        case 9: //attribute
            return &DATA.value.attribute;
        case 10: //specialization
            return &DATA.value.specialization;
        case 11: //use0
            return &DATA.value.use0;
        case 12: //use1
            return &DATA.value.use1;
        case 13: //apprentice
            return ANAM.value;
        case 14: //journeyman
            return JNAM.value;
        case 15: //expert
            return ENAM.value;
        case 16: //master
            return MNAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool SKILRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((char *)FieldValue);
            break;
        case 5: //skill
            INDX.value = *(int32_t *)FieldValue;
            break;
        case 6: //description
            DESC.Copy((char *)FieldValue);
            break;
        case 7: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //action
            DATA.value.action = *(int32_t *)FieldValue;
            break;
        case 9: //attribute
            DATA.value.attribute = *(int32_t *)FieldValue;
            break;
        case 10: //specialization
            DATA.value.specialization = *(uint32_t *)FieldValue;
            break;
        case 11: //use0
            DATA.value.use0 = *(float *)FieldValue;
            break;
        case 12: //use1
            DATA.value.use1 = *(float *)FieldValue;
            break;
        case 13: //apprentice
            ANAM.Copy((char *)FieldValue);
            break;
        case 14: //journeyman
            JNAM.Copy((char *)FieldValue);
            break;
        case 15: //expert
            ENAM.Copy((char *)FieldValue);
            break;
        case 16: //master
            MNAM.Copy((char *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void SKILRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    SKILDATA defaultDATA;

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
        case 5: //skill
            INDX.Unload();
            return;
        case 6: //description
            DESC.Unload();
            return;
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //action
            ICON.Unload();
            return;
        case 9: //attribute
            DATA.value.attribute = defaultDATA.attribute;
            return;
        case 10: //specialization
            DATA.value.specialization = defaultDATA.specialization;
            return;
        case 11: //use0
            DATA.value.use0 = defaultDATA.use0;
            return;
        case 12: //use1
            DATA.value.use1 = defaultDATA.use1;
            return;
        case 13: //apprentice
            ANAM.Unload();
            return;
        case 14: //journeyman
            JNAM.Unload();
            return;
        case 15: //expert
            ENAM.Unload();
            return;
        case 16: //master
            MNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}