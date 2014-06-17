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
#include "..\LTEXRecord.h"

namespace Ob
{
UINT32 LTEXRecord::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    switch(FieldID)
        {
        case 0: //recType
            return GetType();
        case 1: //flags1
            return UINT32_FLAG_FIELD;
        case 2: //fid
            return FORMID_FIELD;
        case 3: //flags2
            return UINT32_FLAG_FIELD;
        case 4: //eid
            return ISTRING_FIELD;
        case 5: //iconPath
            return ISTRING_FIELD;
        case 6: //types
            return UINT8_TYPE_FIELD;
        case 7: //friction
            return UINT8_FIELD;
        case 8: //restitution
            return UINT8_FIELD;
        case 9: //specular
            return UINT8_FIELD;
        case 10: //grass
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (UINT32)GNAM.value.size();
                default:
                    return UNKNOWN_FIELD;
                }
        default:
            return UNKNOWN_FIELD;
        }
    return UNKNOWN_FIELD;
    }

void * LTEXRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //iconPath
            return ICON.value;
        case 6: //types
            return HNAM.IsLoaded() ? &HNAM->types : NULL;
        case 7: //friction
            return HNAM.IsLoaded() ? &HNAM->friction : NULL;
        case 8: //restitution
            return HNAM.IsLoaded() ? &HNAM->restitution : NULL;
        case 9: //specular
            return SNAM.IsLoaded() ? SNAM.value : NULL;
        case 10: //grass
            *FieldValues = GNAM.value.size() ? &GNAM.value[0] : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool LTEXRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(UINT32 *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(UINT32 *)FieldValue);
            break;
        case 4: //eid
            EDID.Copy((STRING)FieldValue);
            break;
        case 5: //iconPath
            ICON.Copy((STRING)FieldValue);
            break;
        case 6: //types
            SetType(*(UINT8 *)FieldValue);
            break;
        case 7: //friction
            HNAM.Load();
            HNAM->friction = *(UINT8 *)FieldValue;
            break;
        case 8: //restitution
            HNAM.Load();
            HNAM->restitution = *(UINT8 *)FieldValue;
            break;
        case 9: //specular
            SNAM.Load();
            *SNAM.value = *(UINT8 *)FieldValue;
            break;
        case 10: //grass
            GNAM.resize(ArraySize);
            for(UINT32 x = 0; x < ArraySize; x++)
                GNAM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        default:
            break;
        }
    return false;
    }

void LTEXRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    LTEXHNAM defaultHNAM;

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
        case 5: //iconPath
            ICON.Unload();
            return;
        case 6: //types
            if(HNAM.IsLoaded())
                HNAM->types = defaultHNAM.types;
            return;
        case 7: //friction
            if(HNAM.IsLoaded())
                HNAM->friction = defaultHNAM.friction;
            return;
        case 8: //restitution
            if(HNAM.IsLoaded())
                HNAM->restitution = defaultHNAM.restitution;
            return;
        case 9: //specular
            SNAM.Unload();
            return;
        case 10: //grass
            GNAM.Unload();
            return;
        default:
            return;
        }
    return;
    }
}