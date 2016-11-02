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
#include "..\SPELRecord.h"

namespace Ob
{
uint32_t SPELRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 5: //full
            return CB_STRING_FIELD;
        case 6: //spellType
            return CB_UINT32_TYPE_FIELD;
        case 7: //cost
            return CB_UINT32_FIELD;
        case 8: //levelType
            return CB_UINT32_FIELD;
        case 9: //flags
            return CB_UINT8_FLAG_FIELD;
        case 10: //unused1
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
        case 11: //effects
            if(ListFieldID == 0) //effects
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Effects.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= Effects.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_MGEFCODE_OR_CHAR4_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded())
                                return Effects.value[ListIndex]->EFID.value >= 0x80000000 ? CB_RESOLVED_MGEFCODE_FIELD : CB_STATIC_MGEFCODE_FIELD;
                            else
                                return CB_CHAR4_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 3: //magnitude
                    return CB_UINT32_FIELD;
                case 4: //area
                    return CB_UINT32_FIELD;
                case 5: //duration
                    return CB_UINT32_FIELD;
                case 6: //rangeType
                    return CB_UINT32_FIELD;
                case 7: //actorValue
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded())
                                {
                                switch(Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo)
                                    {
                                    case 1: //It's a regular formID, so nothing fancy.
                                        return CB_FORMID_FIELD;
                                    case 2: //It's a mgefCode, and not a formID at all.
                                        //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                        //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                        return Effects.value[ListIndex]->EFIT.value.actorValue >= 0x80000000 ? CB_RESOLVED_MGEFCODE_FIELD : CB_STATIC_MGEFCODE_FIELD;
                                    case 3: //It's an actor value, and not a formID at all.
                                        //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                        //It's resolved just like a formID
                                        return Effects.value[ListIndex]->EFIT.value.actorValue >= 0x800 ? CB_RESOLVED_ACTORVALUE_FIELD : CB_STATIC_ACTORVALUE_FIELD;
                                    default: //It's not a formID, mgefCode, or fancied up actor value
                                        //so do nothing
                                        return CB_UINT32_FIELD;
                                    }
                                }
                            else
                                return CB_STATIC_ACTORVALUE_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 8: //script
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->SCIT.IsLoaded())
                                {
                                switch(Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo)
                                    {
                                    case 1: //It's a regular formID, so nothing fancy.
                                        return CB_FORMID_FIELD;
                                    case 2: //It's a mgefCode, and not a formID at all.
                                        //Conditional resolution of mgefCode's based on JRoush's OBME mod
                                        //It's resolved just like a formID, except it uses the lower byte instead of the upper
                                        return Effects.value[ListIndex]->SCIT->script >= 0x80000000 ? CB_RESOLVED_MGEFCODE_FIELD : CB_STATIC_MGEFCODE_FIELD;
                                    case 3: //It's an actor value, and not a formID at all.
                                        //Conditional resolution of av's based on JRoush's OBME/AV mod(s)
                                        //It's resolved just like a formID
                                        return Effects.value[ListIndex]->SCIT->script >= 0x800 ? CB_RESOLVED_ACTORVALUE_FIELD : CB_STATIC_ACTORVALUE_FIELD;
                                    default: //It's not a formID, mgefCode, or fancied up actor value
                                        //so do nothing
                                        return CB_UINT32_FIELD;
                                    }
                                }
                            else
                                return CB_FORMID_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 9: //school
                    return CB_UINT32_TYPE_FIELD;
                case 10: //visual
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_MGEFCODE_OR_CHAR4_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->SCIT.IsLoaded())
                                return ((Effects.value[ListIndex]->SCIT->visual >= 0x80000000) ? CB_RESOLVED_MGEFCODE_FIELD : CB_STATIC_MGEFCODE_FIELD);
                            else
                                return CB_CHAR4_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 11: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 12: //unused1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Effects.value[ListIndex]->SCIT.IsLoaded() ? 3 : 0;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 13: //full
                    return CB_STRING_FIELD;
                //OBME Fields
                case 14: //recordVersion
                    return CB_UINT8_FIELD;
                case 15: //betaVersion
                    return CB_UINT8_FIELD;
                case 16: //minorVersion
                    return CB_UINT8_FIELD;
                case 17: //majorVersion
                    return CB_UINT8_FIELD;
                case 18: //efitParamInfo
                    return CB_UINT8_FIELD;
                case 19: //efixParamInfo
                    return CB_UINT8_FIELD;
                case 20: //reserved1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Effects.value[ListIndex]->OBME.IsLoaded() ? 0xA : 0;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 21: //iconPath
                    return CB_ISTRING_FIELD;
                case 22: //efixOverrides
                    return CB_UINT32_FLAG_FIELD;
                case 23: //efixFlags
                    return CB_UINT32_FLAG_FIELD;
                case 24: //baseCost
                    return CB_FLOAT32_FIELD;
                case 25: //resistAV
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_ACTORVALUE_FIELD;
                        case 2: //WhichType
                            if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                                return Effects.value[ListIndex]->OBME->EFIX->resistAV >= 0x800 ? CB_RESOLVED_ACTORVALUE_FIELD : CB_STATIC_ACTORVALUE_FIELD;
                            else
                                return CB_UNKNOWN_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                case 26: //reserved2
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded() ? 0x10 : 0;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                default:
                    return CB_UNKNOWN_FIELD;
                }
        //OBME Fields
        case 12: //recordVersion
            return CB_UINT8_FIELD;
        case 13: //betaVersion
            return CB_UINT8_FIELD;
        case 14: //minorVersion
            return CB_UINT8_FIELD;
        case 15: //majorVersion
            return CB_UINT8_FIELD;
        case 16: //reserved
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OBME.IsLoaded() ? 0x1C : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //datx_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return (OBME.IsLoaded() && OBME->DATX.IsLoaded()) ? 0x20 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * SPELRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 5: //full
            return FULL.value;
        case 6: //spellType
            return &SPIT.value.spellType;
        case 7: //cost
            return &SPIT.value.cost;
        case 8: //levelType
            return &SPIT.value.levelType;
        case 9: //flags
            return &SPIT.value.flags;
        case 10: //unused1
            *FieldValues = &SPIT.value.unused1[0];
            return NULL;
        case 11: //effects
            if(ListIndex >= Effects.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    return &Effects.value[ListIndex]->EFID.value;
                case 3: //magnitude
                    return &Effects.value[ListIndex]->EFIT.value.magnitude;
                case 4: //area
                    return &Effects.value[ListIndex]->EFIT.value.area;
                case 5: //duration
                    return &Effects.value[ListIndex]->EFIT.value.duration;
                case 6: //rangeType
                    return &Effects.value[ListIndex]->EFIT.value.rangeType;
                case 7: //actorValue
                    return &Effects.value[ListIndex]->EFIT.value.actorValue;
                case 8: //script
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->script : NULL;
                case 9: //school
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->schoolType : NULL;
                case 10: //visual
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->visual : NULL;
                case 11: //flags
                    return Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->flags : NULL;
                case 12: //unused1
                    *FieldValues = Effects.value[ListIndex]->SCIT.IsLoaded() ? &Effects.value[ListIndex]->SCIT->unused1[0] : NULL;
                    return NULL;
                case 13: //full
                    return Effects.value[ListIndex]->FULL.value;
                //OBME Fields
                case 14: //recordVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.recordVersion : NULL;
                case 15: //betaVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.betaVersion : NULL;
                case 16: //minorVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.minorVersion : NULL;
                case 17: //majorVersion
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.majorVersion : NULL;
                case 18: //efitParamInfo
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo : NULL;
                case 19: //efixParamInfo
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo : NULL;
                case 20: //reserved1
                    *FieldValues = Effects.value[ListIndex]->OBME.IsLoaded() ? &Effects.value[ListIndex]->OBME->EFME.value.reserved[0] : NULL;
                    return NULL;
                case 21: //iconPath
                    return Effects.value[ListIndex]->OBME.IsLoaded() ? Effects.value[ListIndex]->OBME->EFII.value : NULL;
                case 22: //efixOverrides
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->efixOverrides : NULL;
                case 23: //efixFlags
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->efixFlags : NULL;
                case 24: //baseCost
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->baseCost : NULL;
                case 25: //resistAV
                    return (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->resistAV : NULL;
                case 26: //reserved2
                    *FieldValues = (Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded()) ? &Effects.value[ListIndex]->OBME->EFIX->reserved[0] : NULL;
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        //OBME Fields
        case 12: //recordVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.recordVersion : NULL;
        case 13: //betaVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.betaVersion : NULL;
        case 14: //minorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.minorVersion : NULL;
        case 15: //majorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.majorVersion : NULL;
        case 16: //reserved
            *FieldValues = OBME.IsLoaded() ? &OBME->OBME.value.reserved[0] : NULL;
            return NULL;
        case 17: //datx_p
            *FieldValues = OBME.IsLoaded() ? OBME->DATX.value : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool SPELRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 6: //spellType
            SetType(*(uint32_t *)FieldValue);
            break;
        case 7: //cost
            SPIT.value.cost = *(uint32_t *)FieldValue;
            break;
        case 8: //levelType
            SPIT.value.levelType = *(uint32_t *)FieldValue;
            break;
        case 9: //flags
            SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 10: //unused1
            if(ArraySize != 3)
                break;
            SPIT.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            SPIT.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            SPIT.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 11: //effects
            if(ListFieldID == 0) //effectsSize
                {
                Effects.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Effects.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects.value[ListIndex]->EFID.value = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    Effects.value[ListIndex]->EFIT.value.name = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    return true;
                case 3: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = *(uint32_t *)FieldValue;
                    break;
                case 4: //area
                    Effects.value[ListIndex]->EFIT.value.area = *(uint32_t *)FieldValue;
                    break;
                case 5: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = *(uint32_t *)FieldValue;
                    break;
                case 6: //rangeType
                    Effects.value[ListIndex]->SetRange(*(uint32_t *)FieldValue);
                    break;
                case 7: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
                    return true;
                case 8: //script
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->script = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
                    return true;
                case 9: //school
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->schoolType = *(uint32_t *)FieldValue;
                    break;
                case 10: //visual
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->visual = *(MGEFCODE_OR_UINT32 *)FieldValue;
                    return true;
                case 11: //flags
                    Effects.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 12: //unused1
                    if(ArraySize != 3)
                        break;
                    Effects.value[ListIndex]->SCIT.Load();
                    Effects.value[ListIndex]->SCIT->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Effects.value[ListIndex]->SCIT->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Effects.value[ListIndex]->SCIT->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    break;
                case 13: //full
                    Effects.value[ListIndex]->FULL.Copy((char *)FieldValue);
                    break;
                //OBME Fields
                case 14: //recordVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.recordVersion = *(uint8_t *)FieldValue;
                    break;
                case 15: //betaVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.betaVersion = *(uint8_t *)FieldValue;
                    break;
                case 16: //minorVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.minorVersion = *(uint8_t *)FieldValue;
                    break;
                case 17: //majorVersion
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.majorVersion = *(uint8_t *)FieldValue;
                    break;
                case 18: //efitParamInfo
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo = *(uint8_t *)FieldValue;
                    return true;
                case 19: //efixParamInfo
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo = *(uint8_t *)FieldValue;
                    return true;
                case 20: //reserved1
                    if(ArraySize != 0xA)
                        break;
                    Effects.value[ListIndex]->OBME.Load();
                    memcpy(&Effects.value[ListIndex]->OBME->EFME.value.reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(Effects.value[ListIndex]->OBME->EFME.value.reserved));
                    break;
                case 21: //iconPath
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFII.Copy((char *)FieldValue);
                    break;
                case 22: //efixOverrides
                    Effects.value[ListIndex]->OBME_SetOverrideFlagMask(*(uint32_t *)FieldValue);
                    return true;
                case 23: //efixFlags
                    Effects.value[ListIndex]->OBME_SetFlagMask(*(uint32_t *)FieldValue);
                    return true;
                case 24: //baseCost
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    Effects.value[ListIndex]->OBME->EFIX->baseCost = *(float *)FieldValue;
                    break;
                case 25: //resistAV
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    Effects.value[ListIndex]->OBME->EFIX->resistAV = *(ACTORVALUE *)FieldValue;
                    return true;
                case 26: //reserved2
                    if(ArraySize != 0x10)
                        break;
                    Effects.value[ListIndex]->OBME.Load();
                    Effects.value[ListIndex]->OBME->EFIX.Load();
                    memcpy(&Effects.value[ListIndex]->OBME->EFIX->reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(Effects.value[ListIndex]->OBME->EFIX->reserved));
                    break;
                default:
                    break;
                }
            break;
        //OBME Fields
        case 12: //recordVersion
            OBME.Load();
            OBME->OBME.value.recordVersion = *(uint8_t *)FieldValue;
            break;
        case 13: //betaVersion
            OBME.Load();
            OBME->OBME.value.betaVersion = *(uint8_t *)FieldValue;
            break;
        case 14: //minorVersion
            OBME.Load();
            OBME->OBME.value.minorVersion = *(uint8_t *)FieldValue;
            break;
        case 15: //majorVersion
            OBME.Load();
            OBME->OBME.value.majorVersion = *(uint8_t *)FieldValue;
            break;
        case 16: //reserved
            if(ArraySize != 0x1C)
                break;
            OBME.Load();
            memcpy(&OBME->OBME.value.reserved[0], &((UINT8ARRAY)FieldValue)[0], sizeof(OBME->OBME.value.reserved));
            break;
        case 17: //datx_p
            if(ArraySize != 0x20)
                break;
            OBME.Load();
            OBME->DATX.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        default:
            break;
        }
    return false;
    }

void SPELRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    SPELSPIT defaultSPIT;
    MAGICOBME defaultOBME;

    GENEFIT defaultEFIT;
    GENSCIT defaultSCIT;
    OBMEEFME defaultEFME;
    OBMEEFIX defaultEFIX;

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
        case 5: //full
            FULL.Unload();
            return;
        case 6: //spellType
            SPIT.value.spellType = defaultSPIT.spellType;
            return;
        case 7: //cost
            SPIT.value.cost = defaultSPIT.cost;
            return;
        case 8: //levelType
            SPIT.value.levelType = defaultSPIT.levelType;
            return;
        case 9: //flags
            SPIT.value.flags = defaultSPIT.flags;
            return;
        case 10: //unused1
            SPIT.value.unused1[0] = defaultSPIT.unused1[0];
            SPIT.value.unused1[1] = defaultSPIT.unused1[1];
            SPIT.value.unused1[2] = defaultSPIT.unused1[2];
            return;
        case 11: //effects
            if(ListFieldID == 0) //effects
                {
                Effects.Unload();
                return;
                }

            if(ListIndex >= Effects.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //name0, both are always the same value, so return one and set both
                case 2: //name
                    Effects.value[ListIndex]->EFID.Unload();
                    Effects.value[ListIndex]->EFIT.value.name = defaultEFIT.name;
                    return;
                case 3: //magnitude
                    Effects.value[ListIndex]->EFIT.value.magnitude = defaultEFIT.magnitude;
                    return;
                case 4: //area
                    Effects.value[ListIndex]->EFIT.value.area = defaultEFIT.area;
                    return;
                case 5: //duration
                    Effects.value[ListIndex]->EFIT.value.duration = defaultEFIT.duration;
                    return;
                case 6: //rangeType
                    Effects.value[ListIndex]->EFIT.value.rangeType = defaultEFIT.rangeType;
                    return;
                case 7: //actorValue
                    Effects.value[ListIndex]->EFIT.value.actorValue = defaultEFIT.actorValue;
                    return;
                case 8: //script
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->script = defaultSCIT.script;
                    return;
                case 9: //school
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->schoolType = defaultSCIT.schoolType;
                    return;
                case 10: //visual
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->visual = defaultSCIT.visual;
                    return;
                case 11: //flags
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        Effects.value[ListIndex]->SCIT->flags = defaultSCIT.flags;
                    return;
                case 12: //unused1
                    if(Effects.value[ListIndex]->SCIT.IsLoaded())
                        {
                        Effects.value[ListIndex]->SCIT->unused1[0] = defaultSCIT.unused1[0];
                        Effects.value[ListIndex]->SCIT->unused1[1] = defaultSCIT.unused1[1];
                        Effects.value[ListIndex]->SCIT->unused1[2] = defaultSCIT.unused1[2];
                        }
                    return;
                case 13: //full
                    Effects.value[ListIndex]->FULL.Unload();
                    return;
                //OBME Fields
                case 14: //recordVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.recordVersion = defaultEFME.recordVersion;
                    return;
                case 15: //betaVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.betaVersion = defaultEFME.betaVersion;
                    return;
                case 16: //minorVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.minorVersion = defaultEFME.minorVersion;
                    return;
                case 17: //majorVersion
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.majorVersion = defaultEFME.majorVersion;
                    return;
                case 18: //efitParamInfo
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.efitParamInfo = defaultEFME.efitParamInfo;
                    return;
                case 19: //efixParamInfo
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFME.value.efixParamInfo = defaultEFME.efixParamInfo;
                    return;
                case 20: //reserved1
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        memcpy(&Effects.value[ListIndex]->OBME->EFME.value.reserved[0],&defaultEFME.reserved[0], sizeof(Effects.value[ListIndex]->OBME->EFME.value.reserved));
                    return;
                case 21: //iconPath
                    if(Effects.value[ListIndex]->OBME.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFII.Unload();
                    return;
                case 22: //efixOverrides
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->efixOverrides = defaultEFIX.efixOverrides;
                    return;
                case 23: //efixFlags
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->efixFlags = defaultEFIX.efixFlags;
                    return;
                case 24: //baseCost
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->baseCost = defaultEFIX.baseCost;
                    return;
                case 25: //resistAV
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        Effects.value[ListIndex]->OBME->EFIX->resistAV = defaultEFIX.resistAV;
                    return;
                case 26: //reserved2
                    if(Effects.value[ListIndex]->OBME.IsLoaded() && Effects.value[ListIndex]->OBME->EFIX.IsLoaded())
                        memcpy(&Effects.value[ListIndex]->OBME->EFIX->reserved[0],&defaultEFIX.reserved[0], sizeof(Effects.value[ListIndex]->OBME->EFIX->reserved));
                    return;
                default:
                    return;
                }
            return;
        //OBME Fields
        case 12: //recordVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.recordVersion = defaultOBME.recordVersion;
            return;
        case 13: //betaVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.betaVersion = defaultOBME.betaVersion;
            return;
        case 14: //minorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.minorVersion = defaultOBME.minorVersion;
            return;
        case 15: //majorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.majorVersion = defaultOBME.majorVersion;
            return;
        case 16: //reserved
            if(OBME.IsLoaded())
                memcpy(&OBME->OBME.value.reserved[0], &defaultOBME.reserved[0], sizeof(OBME->OBME.value.reserved));
            return;
        case 17: //datx_p
            if(OBME.IsLoaded())
                OBME->DATX.Unload();
            return;
        default:
            return;
        }
    return;
    }
}