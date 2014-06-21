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
#include "..\MGEFRecord.h"

namespace Ob
{
uint32_t MGEFRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 6: //text
            return CB_STRING_FIELD;
        case 7: //iconPath
            return CB_ISTRING_FIELD;
        case 8: //modPath
            return CB_ISTRING_FIELD;
        case 9: //modb
            return CB_FLOAT32_FIELD;
        case 10: //modt_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MODL.IsLoaded() ? MODL->MODT.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //flags
            return CB_UINT32_FLAG_FIELD;
        case 12: //baseCost
            return CB_FLOAT32_FIELD;
        case 13: //associated
            return CB_FORMID_FIELD;
        case 14: //school
            return CB_UINT32_TYPE_FIELD;
        case 15: //resistValue
            return CB_UINT32_FIELD;
        case 16: //numCounters
            return CB_UINT16_FIELD;
        case 17: //unused1
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
        case 18: //light
            return CB_FORMID_FIELD;
        case 19: //projectileSpeed
            return CB_FLOAT32_FIELD;
        case 20: //effectShader
            return CB_FORMID_FIELD;
        case 21: //enchantEffect
            return CB_FORMID_FIELD;
        case 22: //castingSound
            return CB_FORMID_FIELD;
        case 23: //boltSound
            return CB_FORMID_FIELD;
        case 24: //hitSound
            return CB_FORMID_FIELD;
        case 25: //areaSound
            return CB_FORMID_FIELD;
        case 26: //cefEnchantment
            return CB_FLOAT32_FIELD;
        case 27: //cefBarter
            return CB_FLOAT32_FIELD;
        case 28: //counterEffects
            if(ListFieldID == 0) //counterEffects
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_MGEFCODE_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)ESCE.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                }

            if(ListIndex >= ESCE.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //counterEffect
                    if(OBME.IsLoaded())
                        {
                        switch(WhichAttribute)
                            {
                            case 0: //fieldType
                                return CB_MGEFCODE_OR_CHAR4_FIELD;
                            case 2: //WhichType
                                return ((ESCE.value[ListIndex] >= 0x80000000) ? CB_RESOLVED_MGEFCODE_FIELD : CB_STATIC_MGEFCODE_FIELD);
                            default:
                                return CB_UNKNOWN_FIELD;
                            }
                        }
                    else
                        return CB_CHAR4_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
        //OBME Fields
        case 29: //recordVersion
            return CB_UINT8_FIELD;
        case 30: //betaVersion
            return CB_UINT8_FIELD;
        case 31: //minorVersion
            return CB_UINT8_FIELD;
        case 32: //majorVersion
            return CB_UINT8_FIELD;
        case 33: //mgefParamAInfo
            return CB_UINT8_FIELD;
        case 34: //mgefParamBInfo
            return CB_UINT8_FIELD;
        case 35: //reserved1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return OBME.IsLoaded() ? 0x2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 36: //handlerCode
            return CB_UINT32_FIELD;
        case 37: //OBMEFlags
            return CB_UINT32_FLAG_FIELD;
        case 38: //mgefParamB
            return CB_UINT32_FIELD;
        case 39: //reserved2
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
        case 40: //mgefCode
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_MGEFCODE_FIELD;
                case 2: //WhichType
                    if(OBME.IsLoaded())
                        {
                        if(*(MGEFCODE *)&OBME->EDDX.value.mgefCode[0] >= 0x80000000)
                            return CB_RESOLVED_MGEFCODE_FIELD;
                        return CB_STATIC_MGEFCODE_FIELD;
                        }
                    else
                        return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 41: //datx_p
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

void * MGEFRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 6: //text
            return DESC.value;
        case 7: //iconPath
            return ICON.value;
        case 8: //modPath
            return MODL.IsLoaded() ? MODL->MODL.value : NULL;
        case 9: //modb
            return MODL.IsLoaded() ? &MODL->MODB.value : NULL;
        case 10: //modt_p
            *FieldValues = MODL.IsLoaded() ? MODL->MODT.value : NULL;
            return NULL;
        case 11: //flags
            return &DATA.value.flags;
        case 12: //baseCost
            return &DATA.value.baseCost;
        case 13: //associated
            return &DATA.value.associated;
        case 14: //school
            return &DATA.value.schoolType;
        case 15: //resistValue
            return &DATA.value.resistValue;
        case 16: //numCounters
            return &DATA.value.numCounters;
        case 17: //unused1
            *FieldValues = &DATA.value.unused1[0];
            return NULL;
        case 18: //light
            return &DATA.value.light;
        case 19: //projectileSpeed
            return &DATA.value.projectileSpeed;
        case 20: //effectShader
            return &DATA.value.effectShader;
        case 21: //enchantEffect
            return &DATA.value.enchantEffect;
        case 22: //castingSound
            return &DATA.value.castingSound;
        case 23: //boltSound
            return &DATA.value.boltSound;
        case 24: //hitSound
            return &DATA.value.hitSound;
        case 25: //areaSound
            return &DATA.value.areaSound;
        case 26: //cefEnchantment
            return &DATA.value.cefEnchantment;
        case 27: //cefBarter
            return &DATA.value.cefBarter;
        case 28: //counterEffects
            *FieldValues = ESCE.value.size() ? &ESCE.value[0] : NULL;
            return NULL;
        //OBME Fields
        case 29: //recordVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.recordVersion : NULL;
        case 30: //betaVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.betaVersion : NULL;
        case 31: //minorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.minorVersion : NULL;
        case 32: //majorVersion
            return OBME.IsLoaded() ? &OBME->OBME.value.majorVersion : NULL;
        case 33: //mgefParamAInfo
            return OBME.IsLoaded() ? &OBME->OBME.value.mgefParamAInfo : NULL;
        case 34: //mgefParamBInfo
            return OBME.IsLoaded() ? &OBME->OBME.value.mgefParamBInfo : NULL;
        case 35: //reserved1
            *FieldValues = OBME.IsLoaded() ? &OBME->OBME.value.reserved1[0] : NULL;
            return NULL;
        case 36: //handlerCode
            return OBME.IsLoaded() ? &OBME->OBME.value.handlerCode : NULL;
        case 37: //OBMEFlags
            return OBME.IsLoaded() ? &OBME->OBME.value.flags : NULL;
        case 38: //mgefParamB
            return OBME.IsLoaded() ? &OBME->OBME.value.mgefParamB : NULL;
        case 39: //reserved2
            *FieldValues = OBME.IsLoaded() ? &OBME->OBME.value.reserved2[0] : NULL;
            return NULL;
        case 40: //mgefCode
            return OBME.IsLoaded() ? &OBME->EDDX.value.mgefCode[0] : NULL;
        case 41: //datx_p
            *FieldValues = (OBME.IsLoaded() && OBME->DATX.IsLoaded()) ? OBME->DATX.value : NULL;
            return NULL;
        default:
            return NULL;
        }
    return NULL;
    }

bool MGEFRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 5: //full
            FULL.Copy((char *)FieldValue);
            break;
        case 6: //text
            DESC.Copy((char *)FieldValue);
            break;
        case 7: //iconPath
            ICON.Copy((char *)FieldValue);
            break;
        case 8: //modPath
            MODL.Load();
            MODL->MODL.Copy((char *)FieldValue);
            break;
        case 9: //modb
            MODL.Load();
            MODL->MODB.value = *(float *)FieldValue;
            break;
        case 10: //modt_p
            MODL.Load();
            MODL->MODT.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //flags
            SetFlagMask(*(uint32_t *)FieldValue);
            break;
        case 12: //baseCost
            DATA.value.baseCost = *(float *)FieldValue;
            break;
        case 13: //associated
            DATA.value.associated = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
            return true;
        case 14: //school
            DATA.value.schoolType = *(uint32_t *)FieldValue;
            break;
        case 15: //resistValue
            DATA.value.resistValue = *(FORMID *)FieldValue;
            return true;
        case 16: //numCounters
            DATA.value.numCounters = *(uint16_t *)FieldValue;
            ESCE.value.resize(*(uint16_t *)FieldValue);
            break;
        case 17: //unused1
            if(ArraySize != 2)
                break;
            DATA.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            DATA.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 18: //light
            DATA.value.light = *(FORMID *)FieldValue;
            return true;
        case 19: //projectileSpeed
            DATA.value.projectileSpeed = *(float *)FieldValue;
            break;
        case 20: //effectShader
            DATA.value.effectShader = *(FORMID *)FieldValue;
            return true;
        case 21: //enchantEffect
            DATA.value.enchantEffect = *(FORMID *)FieldValue;
            return true;
        case 22: //castingSound
            DATA.value.castingSound = *(FORMID *)FieldValue;
            return true;
        case 23: //boltSound
            DATA.value.boltSound = *(FORMID *)FieldValue;
            return true;
        case 24: //hitSound
            DATA.value.hitSound = *(FORMID *)FieldValue;
            return true;
        case 25: //areaSound
            DATA.value.areaSound = *(FORMID *)FieldValue;
            return true;
        case 26: //cefEnchantment
            DATA.value.cefEnchantment = *(float *)FieldValue;
            break;
        case 27: //cefBarter
            DATA.value.cefBarter = *(float *)FieldValue;
            break;
        case 28: //counterEffects
            ESCE.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                ESCE.value[x] = ((MGEFCODEARRAY)FieldValue)[x];
            return true;
        //OBME Fields
        case 29: //recordVersion
            OBME.Load();
            OBME->OBME.value.recordVersion = *(uint8_t *)FieldValue;
            break;
        case 30: //betaVersion
            OBME.Load();
            OBME->OBME.value.betaVersion = *(uint8_t *)FieldValue;
            break;
        case 31: //minorVersion
            OBME.Load();
            OBME->OBME.value.minorVersion = *(uint8_t *)FieldValue;
            break;
        case 32: //majorVersion
            OBME.Load();
            OBME->OBME.value.majorVersion = *(uint8_t *)FieldValue;
            break;
        case 33: //mgefParamAInfo
            OBME.Load();
            OBME->OBME.value.mgefParamAInfo = *(uint8_t *)FieldValue;
            return true;
        case 34: //mgefParamBInfo
            OBME.Load();
            OBME->OBME.value.mgefParamBInfo = *(uint8_t *)FieldValue;
            return true;
        case 35: //reserved1
            if(ArraySize != 0x2)
                break;
            OBME.Load();
            OBME->OBME.value.reserved1[0] = ((UINT8ARRAY)FieldValue)[0];
            OBME->OBME.value.reserved1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 36: //handlerCode
            OBME.Load();
            OBME->OBME.value.handlerCode = *(uint32_t *)FieldValue;
            break;
        case 37: //OBMEFlags
            SetOBMEFlagMask(*(uint32_t *)FieldValue);
            break;
        case 38: //mgefParamB
            OBME.Load();
            OBME->OBME.value.mgefParamB = *(FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32 *)FieldValue;
            return true;
        case 39: //reserved2
            if(ArraySize != 0x1C)
                break;
            OBME.Load();
            memcpy(&OBME->OBME.value.reserved2[0], &((UINT8ARRAY)FieldValue)[0], sizeof(OBME->OBME.value.reserved2));
            break;
        case 40: //mgefCode
            OBME.Load();
            OBME->EDDX.Load();
            memcpy(&OBME->EDDX.value.mgefCode[0], FieldValue, sizeof(OBME->EDDX.value.mgefCode) - 1);
            OBME->EDDX.value.mgefCode[4] = 0;
            return true;
        case 41: //datx_p
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

void MGEFRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    MGEFDATA defaultDATA;
    MGEFOBME defaultOBME;

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
        case 6: //text
            DESC.Unload();
            return;
        case 7: //iconPath
            ICON.Unload();
            return;
        case 8: //modPath
            if(MODL.IsLoaded())
                MODL->MODL.Unload();
            return;
        case 9: //modb
            if(MODL.IsLoaded())
                MODL->MODB.Unload();
            return;
        case 10: //modt_p
            if(MODL.IsLoaded())
                MODL->MODT.Unload();
            return;
        case 11: //flags
            DATA.value.flags = defaultDATA.flags;
            return;
        case 12: //baseCost
            DATA.value.baseCost = defaultDATA.baseCost;
            return;
        case 13: //associated
            DATA.value.associated = defaultDATA.associated;
            return;
        case 14: //school
            DATA.value.schoolType = defaultDATA.schoolType;
            return;
        case 15: //resistValue
            DATA.value.resistValue = defaultDATA.resistValue;
            return;
        case 16: //numCounters
            DATA.value.numCounters = defaultDATA.numCounters;
            ESCE.resize(defaultDATA.numCounters);
            return;
        case 17: //unused1
            DATA.value.unused1[0] = defaultDATA.unused1[0];
            DATA.value.unused1[1] = defaultDATA.unused1[1];
            return;
        case 18: //light
            DATA.value.light = defaultDATA.light;
            return;
        case 19: //projectileSpeed
            DATA.value.projectileSpeed = defaultDATA.projectileSpeed;
            return;
        case 20: //effectShader
            DATA.value.effectShader = defaultDATA.effectShader;
            return;
        case 21: //enchantEffect
            DATA.value.enchantEffect = defaultDATA.enchantEffect;
            return;
        case 22: //castingSound
            DATA.value.castingSound = defaultDATA.castingSound;
            return;
        case 23: //boltSound
            DATA.value.boltSound = defaultDATA.boltSound;
            return;
        case 24: //hitSound
            DATA.value.hitSound = defaultDATA.hitSound;
            return;
        case 25: //areaSound
            DATA.value.areaSound = defaultDATA.areaSound;
            return;
        case 26: //cefEnchantment
            DATA.value.cefEnchantment = defaultDATA.cefEnchantment;
            return;
        case 27: //cefBarter
            DATA.value.cefBarter = defaultDATA.cefBarter;
            return;
        case 28: //counterEffects
            DATA.value.numCounters = 0;
            ESCE.Unload();
            return;
        //OBME Fields
        case 29: //recordVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.recordVersion = defaultOBME.recordVersion;
            return;
        case 30: //betaVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.betaVersion = defaultOBME.betaVersion;
            return;
        case 31: //minorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.minorVersion = defaultOBME.minorVersion;
            return;
        case 32: //majorVersion
            if(OBME.IsLoaded())
                OBME->OBME.value.majorVersion = defaultOBME.majorVersion;
            return;
        case 33: //mgefParamAInfo
            if(OBME.IsLoaded())
                OBME->OBME.value.mgefParamAInfo = defaultOBME.mgefParamAInfo;
            return;
        case 34: //mgefParamBInfo
            if(OBME.IsLoaded())
                OBME->OBME.value.mgefParamBInfo = defaultOBME.mgefParamBInfo;
            return;
        case 35: //reserved1
            if(OBME.IsLoaded())
                {
                OBME->OBME.value.reserved1[0] = defaultOBME.reserved1[0];
                OBME->OBME.value.reserved1[1] = defaultOBME.reserved1[1];
                }
            return;
        case 36: //handlerCode
            if(OBME.IsLoaded())
                OBME->OBME.value.handlerCode = defaultOBME.handlerCode;
            return;
        case 37: //OBMEFlags
            if(OBME.IsLoaded())
                OBME->OBME.value.flags = defaultOBME.flags;
            return;
        case 38: //mgefParamB
            if(OBME.IsLoaded())
                OBME->OBME.value.mgefParamB = defaultOBME.mgefParamB;
            return;
        case 39: //reserved2
            if(OBME.IsLoaded())
                memcpy(&OBME->OBME.value.reserved2[0], &defaultOBME.reserved2[0], sizeof(OBME->OBME.value.reserved2));
            return;
        case 40: //mgefCode
            if(OBME.IsLoaded())
                OBME->EDDX.Unload();
            return;
        case 41: //datx_p
            if(OBME.IsLoaded())
                OBME->DATX.Unload();
            return;
        default:
            return;
        }
    return;
    }
}