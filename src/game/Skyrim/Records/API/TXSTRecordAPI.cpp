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
#include "..\TXSTRecord.h"

namespace Sk
{
uint32_t TXSTRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 13: //baseImageOrTransparency
            return CB_ISTRING_FIELD;
        case 14: //normalMapOrSpecular
            return CB_ISTRING_FIELD;
        case 15: //envMapMaskOrUnk
            return CB_ISTRING_FIELD;
        case 16: //glowMapOrUnused
            return CB_ISTRING_FIELD;
        case 17: //parallaxMapOrUnused
            return CB_ISTRING_FIELD;
        case 18: //envMapOrUnused
            return CB_ISTRING_FIELD;
        case 19: //decalMinWidth
            return CB_FLOAT32_FIELD;
        case 20: //decalMaxWidth
            return CB_FLOAT32_FIELD;
        case 21: //decalMinHeight
            return CB_FLOAT32_FIELD;
        case 22: //decalMaxHeight
            return CB_FLOAT32_FIELD;
        case 23: //decalDepth
            return CB_FLOAT32_FIELD;
        case 24: //decalShininess
            return CB_FLOAT32_FIELD;
        case 25: //decalScale
            return CB_FLOAT32_FIELD;
        case 26: //decalPasses
            return CB_UINT8_FIELD;
        case 27: //decalFlags
            return CB_UINT8_FLAG_FIELD;
        case 28: //decalUnused1
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
        case 29: //decalRed
            return CB_UINT8_FIELD;
        case 30: //decalGreen
            return CB_UINT8_FIELD;
        case 31: //decalBlue
            return CB_UINT8_FIELD;
        case 32: //decalUnused2
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
        case 33: //flags
            return CB_UINT16_FLAG_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * TXSTRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 13: //baseImageOrTransparency
            return TX00.value;
        case 14: //normalMapOrSpecular
            return TX01.value;
        case 15: //envMapMaskOrUnk
            return TX02.value;
        case 16: //glowMapOrUnused
            return TX03.value;
        case 17: //parallaxMapOrUnused
            return TX04.value;
        case 18: //envMapOrUnused
            return TX05.value;
        case 19: //decalMinWidth
            return DODT.IsLoaded() ? &DODT->minWidth : NULL;
        case 20: //decalMaxWidth
            return DODT.IsLoaded() ? &DODT->maxWidth : NULL;
        case 21: //decalMinHeight
            return DODT.IsLoaded() ? &DODT->minHeight : NULL;
        case 22: //decalMaxHeight
            return DODT.IsLoaded() ? &DODT->maxHeight : NULL;
        case 23: //decalDepth
            return DODT.IsLoaded() ? &DODT->depth : NULL;
        case 24: //decalShininess
            return DODT.IsLoaded() ? &DODT->shininess : NULL;
        case 25: //decalScale
            return DODT.IsLoaded() ? &DODT->scale : NULL;
        case 26: //decalPasses
            return DODT.IsLoaded() ? &DODT->passes : NULL;
        case 27: //decalFlags
            return DODT.IsLoaded() ? &DODT->flags : NULL;
        case 28: //decalUnused1
            *FieldValues = DODT.IsLoaded() ? &DODT->unused1[0] : NULL;
            return NULL;
        case 29: //decalRed
            return DODT.IsLoaded() ? &DODT->red : NULL;
        case 30: //decalGreen
            return DODT.IsLoaded() ? &DODT->green : NULL;
        case 31: //decalBlue
            return DODT.IsLoaded() ? &DODT->blue : NULL;
        case 32: //decalUnused2
            *FieldValues = DODT.IsLoaded() ? &DODT->unused2 : NULL;
            return NULL;
        case 33: //flags
            return DNAM.value;
        default:
            return NULL;
        }
    return NULL;
    }

bool TXSTRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 13: //baseImageOrTransparency
            TX00.Copy((char *)FieldValue);
            break;
        case 14: //normalMapOrSpecular
            TX01.Copy((char *)FieldValue);
            break;
        case 15: //envMapMaskOrUnk
            TX02.Copy((char *)FieldValue);
            break;
        case 16: //glowMapOrUnused
            TX03.Copy((char *)FieldValue);
            break;
        case 17: //parallaxMapOrUnused
            TX04.Copy((char *)FieldValue);
            break;
        case 18: //envMapOrUnused
            TX05.Copy((char *)FieldValue);
            break;
        case 19: //decalMinWidth
            DODT.Load();
            DODT->minWidth = *(float *)FieldValue;
            break;
        case 20: //decalMaxWidth
            DODT.Load();
            DODT->maxWidth = *(float *)FieldValue;
            break;
        case 21: //decalMinHeight
            DODT.Load();
            DODT->minHeight = *(float *)FieldValue;
            break;
        case 22: //decalMaxHeight
            DODT.Load();
            DODT->maxHeight = *(float *)FieldValue;
            break;
        case 23: //decalDepth
            DODT.Load();
            DODT->depth = *(float *)FieldValue;
            break;
        case 24: //decalShininess
            DODT.Load();
            DODT->shininess = *(float *)FieldValue;
            break;
        case 25: //decalScale
            DODT.Load();
            DODT->scale = *(float *)FieldValue;
            break;
        case 26: //decalPasses
            DODT.Load();
            DODT->passes = *(uint8_t *)FieldValue;
            break;
        case 27: //decalFlags
            DODT.Load();
            DODT->flags = *(uint8_t *)FieldValue;
            break;
        case 28: //decalUnused1
            if(ArraySize != 2)
                break;
            DODT.Load();
            DODT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DODT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 29: //decalRed
            DODT.Load();
            DODT->red = *(uint8_t *)FieldValue;
            break;
        case 30: //decalGreen
            DODT.Load();
            DODT->green = *(uint8_t *)FieldValue;
            break;
        case 31: //decalBlue
            DODT.Load();
            DODT->blue = *(uint8_t *)FieldValue;
            break;
        case 32: //decalUnused2
            if(ArraySize != 1)
                break;
            DODT.Load();
            DODT->unused2 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 33: //flags
            SetFlagMask(*(uint16_t *)FieldValue);
            break;
        default:
            break;
        }
    return false;
    }

void TXSTRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    GENOBND defaultOBND;
    GENDODT defaultDODT;

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
        case 13: //baseImageOrTransparency
            TX00.Unload();
            return;
        case 14: //normalMapOrSpecular
            TX01.Unload();
            return;
        case 15: //envMapMaskOrUnk
            TX02.Unload();
            return;
        case 16: //glowMapOrUnused
            TX03.Unload();
            return;
        case 17: //parallaxMapOrUnused
            TX04.Unload();
            return;
        case 18: //envMapOrUnused
            TX05.Unload();
            return;
        case 19: //decalMinWidth
            if(DODT.IsLoaded())
                DODT->minWidth = defaultDODT.minWidth;
            return;
        case 20: //decalMaxWidth
            if(DODT.IsLoaded())
                DODT->maxWidth = defaultDODT.maxWidth;
            return;
        case 21: //decalMinHeight
            if(DODT.IsLoaded())
                DODT->minHeight = defaultDODT.minHeight;
            return;
        case 22: //decalMaxHeight
            if(DODT.IsLoaded())
                DODT->maxHeight = defaultDODT.maxHeight;
            return;
        case 23: //decalDepth
            if(DODT.IsLoaded())
                DODT->depth = defaultDODT.depth;
            return;
        case 24: //decalShininess
            if(DODT.IsLoaded())
                DODT->shininess = defaultDODT.shininess;
            return;
        case 25: //decalScale
            if(DODT.IsLoaded())
                DODT->scale = defaultDODT.scale;
            return;
        case 26: //decalPasses
            if(DODT.IsLoaded())
                DODT->passes = defaultDODT.passes;
            return;
        case 27: //decalFlags
            if(DODT.IsLoaded())
                DODT->flags = defaultDODT.flags;
            return;
        case 28: //decalUnused1
            if(DODT.IsLoaded())
                {
                DODT->unused1[0] = defaultDODT.unused1[0];
                DODT->unused1[1] = defaultDODT.unused1[1];
                }
            return;
        case 29: //decalRed
            if(DODT.IsLoaded())
                DODT->red = defaultDODT.red;
            return;
        case 30: //decalGreen
            if(DODT.IsLoaded())
                DODT->green = defaultDODT.green;
            return;
        case 31: //decalBlue
            if(DODT.IsLoaded())
                DODT->blue = defaultDODT.blue;
            return;
        case 32: //decalUnused2
            if(DODT.IsLoaded())
                DODT->unused2 = defaultDODT.unused2;
            return;
        case 33: //flags
            DNAM.Unload();
            return;
        default:
            return;
        }
    }
}