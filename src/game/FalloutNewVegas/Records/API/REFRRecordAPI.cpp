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
#include "..\REFRRecord.h"

namespace FNV
{
uint32_t REFRRecord::GetFieldAttribute(FIELD_IDENTIFIERS, uint32_t WhichAttribute)
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
        case 7: //base
            return CB_FORMID_FIELD;
        case 8: //encounterZone
            return CB_FORMID_FIELD;
        case 9: //xrgd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGD.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 10: //xrgb_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XRGB.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 11: //idleTime
            return CB_FLOAT32_FIELD;
        case 12: //idle
            return CB_FORMID_FIELD;
        case 13: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? 4 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 14: //numRefs
            return CB_UINT32_FIELD;
        case 15: //compiledSize
            return CB_UINT32_FIELD;
        case 16: //lastIndex
            return CB_UINT32_FIELD;
        case 17: //scriptType
            return CB_UINT16_TYPE_FIELD;
        case 18: //scriptFlags
            return CB_UINT16_FLAG_FIELD;
        case 19: //compiled_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Patrol.IsLoaded() ? Patrol->SCDA.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 20: //scriptText
            return CB_ISTRING_FIELD;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //vars
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Patrol->VARS.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //index
                    return CB_UINT32_FIELD;
                case 2: //unused1
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
                case 3: //flags
                    return CB_UINT8_FLAG_FIELD;
                case 4: //unused2
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
                case 5: //name
                    return CB_ISTRING_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 22: //references
            if(!Patrol.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //references
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_FORMID_OR_UINT32_ARRAY_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)Patrol->SCR_.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_FORMID_OR_UINT32_FIELD;
                        case 2: //WhichType
                            return Patrol->SCR_.value[ListIndex]->isSCRO ? CB_FORMID_FIELD : CB_UINT32_FIELD;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 23: //topic
            return CB_FORMID_FIELD;
        case 24: //levelMod
            return CB_SINT32_FIELD;
        case 25: //owner
            return CB_FORMID_FIELD;
        case 26: //rank
            return CB_SINT32_FIELD;
        case 27: //count
            return CB_SINT32_FIELD;
        case 28: //radius
            return CB_FLOAT32_FIELD;
        case 29: //health
            return CB_FLOAT32_FIELD;
        case 30: //radiation
            return CB_FLOAT32_FIELD;
        case 31: //charge
            return CB_FLOAT32_FIELD;
        case 32: //decals
            if(ListFieldID == 0) //decals
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)XDCR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= XDCR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return CB_FORMID_FIELD;
                case 2: //unknown1
                    switch(WhichAttribute)
                        {
                        case 0: //fieldType
                            return CB_UINT8_ARRAY_FIELD;
                        case 1: //fieldSize
                            return 24;
                        default:
                            return CB_UNKNOWN_FIELD;
                        }
                    return CB_UNKNOWN_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 33: //linkedReference
            return CB_FORMID_FIELD;
        case 34: //startRed
            return CB_UINT8_FIELD;
        case 35: //startRed
            return CB_UINT8_FIELD;
        case 36: //startBlue
            return CB_UINT8_FIELD;
        case 37: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 38: //endRed
            return CB_UINT8_FIELD;
        case 39: //endGreen
            return CB_UINT8_FIELD;
        case 40: //endBlue
            return CB_UINT8_FIELD;
        case 41: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XCLP.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 42: //rclr_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return RCLR.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 43: //activateParentFlags
            return CB_UINT8_FLAG_FIELD;
        case 44: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return CB_UNKNOWN_FIELD;

            if(ListFieldID == 0) //activateParentRefs
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)ActivateParents->XAPR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return CB_FORMID_FIELD;
                case 2: //delay
                    return CB_FLOAT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 45: //prompt
            return CB_STRING_FIELD;
        case 46: //parent
            return CB_FORMID_FIELD;
        case 47: //parentFlags
            return CB_UINT8_FLAG_FIELD;
        case 48: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XESP.IsLoaded() ? 3 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 49: //emittance
            return CB_FORMID_FIELD;
        case 50: //boundRef
            return CB_FORMID_FIELD;
        case 51: //primitiveX
            return CB_FLOAT32_FIELD;
        case 52: //primitiveY
            return CB_FLOAT32_FIELD;
        case 53: //primitiveZ
            return CB_FLOAT32_FIELD;
        case 54: //primitiveRed
            return CB_FLOAT32_FIELD;
        case 55: //primitiveGreen
            return CB_FLOAT32_FIELD;
        case 56: //primitiveBlue
            return CB_FLOAT32_FIELD;
        case 57: //primitiveUnknown
            return CB_FLOAT32_FIELD;
        case 58: //primitiveType
            return CB_UINT32_TYPE_FIELD;
        case 59: //collisionType
            return CB_UINT32_TYPE_FIELD;
        case 60: //extentX
            return CB_FLOAT32_FIELD;
        case 61: //extentY
            return CB_FLOAT32_FIELD;
        case 62: //extentZ
            return CB_FLOAT32_FIELD;
        case 63: //destinationFid
            return CB_FORMID_FIELD;
        case 64: //destinationPosX
            return CB_FLOAT32_FIELD;
        case 65: //destinationPosY
            return CB_FLOAT32_FIELD;
        case 66: //destinationPosZ
            return CB_FLOAT32_FIELD;
        case 67: //destinationRotX
            return CB_RADIAN_FIELD;
        case 68: //destinationRotY
            return CB_RADIAN_FIELD;
        case 69: //destinationRotZ
            return CB_RADIAN_FIELD;
        case 70: //destinationFlags
            return CB_UINT32_FLAG_FIELD;
        case 71: //markerFlags
            return CB_UINT8_FLAG_FIELD;
        case 72: //markerFull
            return CB_STRING_FIELD;
        case 73: //markerType
            return CB_UINT8_TYPE_FIELD;
        case 74: //unused5
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return MapData.IsLoaded() ? 1 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 75: //markerReputation
            return CB_FORMID_FIELD;
        case 76: //audioFull_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return AudioData.IsLoaded() ? AudioData->FULL.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 77: //audioLocation
            return CB_FORMID_FIELD;
        case 78: //audioBnam_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return AudioData.IsLoaded() ? AudioData->BNAM.GetSize() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 79: //audioUnknown1
            return CB_FLOAT32_FIELD;
        case 80: //audioUnknown2
            return CB_FLOAT32_FIELD;
        case 81: //xsrf_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XSRF.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 82: //xsrd_p
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XSRD.GetSize();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 83: //target
            return CB_FORMID_FIELD;
        case 84: //rangeRadius
            return CB_FLOAT32_FIELD;
        case 85: //rangeType
            return CB_UINT32_TYPE_FIELD;
        case 86: //staticPercentage
            return CB_FLOAT32_FIELD;
        case 87: //positionReference
            return CB_FORMID_FIELD;
        case 88: //lockLevel
            return CB_UINT8_FIELD;
        case 89: //unused6
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XLOC.IsLoaded() ? 3 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 90: //lockKey
            return CB_FORMID_FIELD;
        case 91: //lockFlags
            return CB_UINT8_FLAG_FIELD;
        case 92: //unused7
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XLOC.IsLoaded() ? 3 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 93: //lockUnknown1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XLOC.IsLoaded() ? 8 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 94: //ammo
            return CB_FORMID_FIELD;
        case 95: //ammoCount
            return CB_SINT32_FIELD;
        case 96: //reflrefrs
            if(ListFieldID == 0) //reflrefrs
                {
                switch(WhichAttribute)
                    {
                    case 0: //fieldType
                        return CB_LIST_FIELD;
                    case 1: //fieldSize
                        return (uint32_t)XPWR.value.size();
                    default:
                        return CB_UNKNOWN_FIELD;
                    }
                return CB_UNKNOWN_FIELD;
                }

            if(ListIndex >= XPWR.value.size())
                return CB_UNKNOWN_FIELD;

            switch(ListFieldID)
                {
                case 1: //reference
                    return CB_FORMID_FIELD;
                case 2: //type
                    return CB_UINT32_TYPE_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 97: //litWaters
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return (uint32_t)XLTW.value.size();
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 98: //actionFlags
            return CB_UINT32_FLAG_FIELD;
        case 99: //navMesh
            return CB_FORMID_FIELD;
        case 100: //navUnknown1
            return CB_UINT16_FIELD;
        case 101: //unused8
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return XNDP.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 102: //portalLinkedRoom1
            return CB_FORMID_FIELD;
        case 103: //portalLinkedRoom2
            return CB_FORMID_FIELD;
        case 104: //portalWidth
            return CB_FLOAT32_FIELD;
        case 105: //portalHeight
            return CB_FLOAT32_FIELD;
        case 106: //portalPosX
            return CB_FLOAT32_FIELD;
        case 107: //portalPosY
            return CB_FLOAT32_FIELD;
        case 108: //portalPosZ
            return CB_FLOAT32_FIELD;
        case 109: //portalQ1
            return CB_FLOAT32_FIELD;
        case 110: //portalQ2
            return CB_FLOAT32_FIELD;
        case 111: //portalQ3
            return CB_FLOAT32_FIELD;
        case 112: //portalQ4
            return CB_FLOAT32_FIELD;
        case 113: //seed
            return CB_UINT8_FIELD;
        case 114: //roomCount
            return CB_UINT16_FIELD;
        case 115: //roomUnknown1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Room.IsLoaded() && Room->XRMR.IsLoaded() ? 2 : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 116: //rooms
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_FORMID_ARRAY_FIELD;
                case 1: //fieldSize
                    return Room.IsLoaded() ? (uint32_t)Room->XLRM.value.size() : 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 117: //occPlaneWidth
            return CB_FLOAT32_FIELD;
        case 118: //occPlaneHeight
            return CB_FLOAT32_FIELD;
        case 119: //occPlanePosX
            return CB_FLOAT32_FIELD;
        case 120: //occPlanePosY
            return CB_FLOAT32_FIELD;
        case 121: //occPlanePosZ
            return CB_FLOAT32_FIELD;
        case 122: //occPlaneQ1
            return CB_FLOAT32_FIELD;
        case 123: //occPlaneQ2
            return CB_FLOAT32_FIELD;
        case 124: //occPlaneQ3
            return CB_FLOAT32_FIELD;
        case 125: //occPlaneQ4
            return CB_FLOAT32_FIELD;
        case 126: //occPlaneRight
            return CB_FORMID_FIELD;
        case 127: //occPlaneLeft
            return CB_FORMID_FIELD;
        case 128: //occPlaneBottom
            return CB_FORMID_FIELD;
        case 129: //occPlaneTop
            return CB_FORMID_FIELD;
        case 130: //lod1
            return CB_FLOAT32_FIELD;
        case 131: //lod2
            return CB_FLOAT32_FIELD;
        case 132: //lod3
            return CB_FLOAT32_FIELD;
        case 133: //ignoredBySandbox
            return CB_BOOL_FIELD;
        case 134: //scale
            return CB_FLOAT32_FIELD;
        case 135: //posX
            return CB_FLOAT32_FIELD;
        case 136: //posY
            return CB_FLOAT32_FIELD;
        case 137: //posZ
            return CB_FLOAT32_FIELD;
        case 138: //rotX
            return CB_RADIAN_FIELD;
        case 139: //rotY
            return CB_RADIAN_FIELD;
        case 140: //rotZ
            return CB_RADIAN_FIELD;
        case 141: //Parent
            return CB_PARENTRECORD_FIELD;
        default:
            return CB_UNKNOWN_FIELD;
        }
    return CB_UNKNOWN_FIELD;
    }

void * REFRRecord::GetField(FIELD_IDENTIFIERS, void **FieldValues)
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
        case 7: //base
            return &NAME.value;
        case 8: //encounterZone
            return &XEZN.value;
        case 9: //XRGD
            *FieldValues = XRGD.value;
            return NULL;
        case 10: //XRGB
            *FieldValues = XRGB.value;
            return NULL;
        case 11: //idleTime
            return Patrol.IsLoaded() ? &Patrol->XPRD.value : NULL;
        case 12: //idle
            return Patrol.IsLoaded() ? &Patrol->INAM.value : NULL;
        case 13: //unused1
            *FieldValues = Patrol.IsLoaded() ? &Patrol->SCHR.value.unused1[0] : NULL;
            return NULL;
        case 14: //numRefs
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.numRefs : NULL;
        case 15: //compiledSize
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.compiledSize : NULL;
        case 16: //lastIndex
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.lastIndex : NULL;
        case 17: //scriptType
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.scriptType : NULL;
        case 18: //scriptFlags
            return Patrol.IsLoaded() ? &Patrol->SCHR.value.flags : NULL;
        case 19: //compiled_p
            *FieldValues = Patrol.IsLoaded() ? Patrol->SCDA.value : NULL;
            return NULL;
        case 20: //scriptText
            return Patrol.IsLoaded() ? Patrol->SCTX.value : NULL;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return NULL;

            if(ListIndex >= Patrol->VARS.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //index
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.index;
                case 2: //unused1
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0];
                    return NULL;
                case 3: //flags
                    return &Patrol->VARS.value[ListIndex]->SLSD.value.flags;
                case 4: //unused2
                    *FieldValues = &Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0];
                    return NULL;
                case 5: //name
                    return Patrol->VARS.value[ListIndex]->SCVR.value;
                default:
                    return NULL;
                }
            return NULL;
        case 22: //references
            if(!Patrol.IsLoaded())
                {
                *FieldValues = NULL;
                return NULL;
                }
            for(uint32_t x = 0; x < Patrol->SCR_.value.size(); ++x)
                ((FORMIDARRAY)FieldValues)[x] = Patrol->SCR_.value[x]->reference;
            return NULL;
        case 23: //topic
            return Patrol.IsLoaded() ? &Patrol->TNAM.value : NULL;
        case 24: //levelMod
            return &XLCM.value;
        case 25: //owner
            return Ownership.IsLoaded() ? &Ownership->XOWN.value : NULL;
        case 26: //rank
            return Ownership.IsLoaded() ? Ownership->XRNK.value : NULL;
        case 27: //count
            return &XCNT.value;
        case 28: //radius
            return &XRDS.value;
        case 29: //health
            return &XHLP.value;
        case 30: //radiation
            return &XRAD.value;
        case 31: //charge
            return &XCHG.value;
        case 32: //decals
            if(ListIndex >= XDCR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &XDCR.value[ListIndex]->reference;
                case 2: //unknown1
                    *FieldValues = &XDCR.value[ListIndex]->unknown1[0];
                    return NULL;
                default:
                    return NULL;
                }
            return NULL;
        case 33: //linkedReference
            return &XLKR.value;
        case 34: //startRed
            return XCLP.IsLoaded() ? &XCLP->start.red : NULL;
        case 35: //startRed
            return XCLP.IsLoaded() ? &XCLP->start.green : NULL;
        case 36: //startBlue
            return XCLP.IsLoaded() ? &XCLP->start.blue : NULL;
        case 37: //unused2
            *FieldValues = XCLP.IsLoaded() ? &XCLP->start.unused1 : NULL;
            return NULL;
        case 38: //endRed
            return XCLP.IsLoaded() ? &XCLP->end.red : NULL;
        case 39: //endGreen
            return XCLP.IsLoaded() ? &XCLP->end.green : NULL;
        case 40: //endBlue
            return XCLP.IsLoaded() ? &XCLP->end.blue : NULL;
        case 41: //unused3
            *FieldValues = XCLP.IsLoaded() ? &XCLP->end.unused1 : NULL;
            return NULL;
        case 42: //rclr_p
            *FieldValues = RCLR.value;
            return NULL;
        case 43: //activateParentFlags
            return ActivateParents.IsLoaded() ? &ActivateParents->XAPD.value : NULL;
        case 44: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return NULL;

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &ActivateParents->XAPR.value[ListIndex]->reference;
                case 2: //delay
                    return &ActivateParents->XAPR.value[ListIndex]->delay;
                default:
                    return NULL;
                }
            return NULL;
        case 45: //prompt
            return XATO.value;
        case 46: //parent
            return XESP.IsLoaded() ? &XESP->parent : NULL;
        case 47: //parentFlags
            return XESP.IsLoaded() ? &XESP->flags : NULL;
        case 48: //unused4
            *FieldValues = XESP.IsLoaded() ? &XESP->unused1[0] : NULL;
            return NULL;
        case 49: //emittance
            return &XEMI.value;
        case 50: //boundRef
            return &XMBR.value;
        case 51: //primitiveX
            return XPRM.IsLoaded() ? &XPRM->xBound : NULL;
        case 52: //primitiveY
            return XPRM.IsLoaded() ? &XPRM->yBound : NULL;
        case 53: //primitiveZ
            return XPRM.IsLoaded() ? &XPRM->zBound : NULL;
        case 54: //primitiveRed
            return XPRM.IsLoaded() ? &XPRM->red : NULL;
        case 55: //primitiveGreen
            return XPRM.IsLoaded() ? &XPRM->green : NULL;
        case 56: //primitiveBlue
            return XPRM.IsLoaded() ? &XPRM->blue : NULL;
        case 57: //primitiveUnknown
            return XPRM.IsLoaded() ? &XPRM->unknown : NULL;
        case 58: //primitiveType
            return XPRM.IsLoaded() ? &XPRM->type : NULL;
        case 59: //collisionType
            return &XTRI.value;
        case 60: //extentX
            return XMBO.IsLoaded() ? &XMBO->x : NULL;
        case 61: //extentY
            return XMBO.IsLoaded() ? &XMBO->y : NULL;
        case 62: //extentZ
            return XMBO.IsLoaded() ? &XMBO->z : NULL;
        case 63: //destinationFid
            return XTEL.IsLoaded() ? &XTEL->destinationFid : NULL;
        case 64: //destinationPosX
            return XTEL.IsLoaded() ? &XTEL->destination.posX : NULL;
        case 65: //destinationPosY
            return XTEL.IsLoaded() ? &XTEL->destination.posY : NULL;
        case 66: //destinationPosZ
            return XTEL.IsLoaded() ? &XTEL->destination.posZ : NULL;
        case 67: //destinationRotX
            return XTEL.IsLoaded() ? &XTEL->destination.rotX : NULL;
        case 68: //destinationRotY
            return XTEL.IsLoaded() ? &XTEL->destination.rotY : NULL;
        case 69: //destinationRotZ
            return XTEL.IsLoaded() ? &XTEL->destination.rotZ : NULL;
        case 70: //destinationFlags
            return XTEL.IsLoaded() ? &XTEL->flags : NULL;
        case 71: //markerFlags
            return MapData.IsLoaded() ? &MapData->FNAM.value : NULL;
        case 72: //markerFull
            return MapData.IsLoaded() ? MapData->FULL.value : NULL;
        case 73: //markerType
            return MapData.IsLoaded() ? &MapData->TNAM.value.markerType : NULL;
        case 74: //unused5
            *FieldValues = MapData.IsLoaded() ? &MapData->TNAM.value.unused1 : NULL;
            return NULL;
        case 75: //markerReputation
            return MapData.IsLoaded() ? &MapData->WMI1.value : NULL;
        case 76: //audioFull_p
            *FieldValues = AudioData.IsLoaded() ? AudioData->FULL.value : NULL;
            return NULL;
        case 77: //audioLocation
            return AudioData.IsLoaded() ? &AudioData->CNAM.value : NULL;
        case 78: //audioBnam_p
            *FieldValues = AudioData.IsLoaded() ? AudioData->BNAM.value : NULL;
            return NULL;
        case 79: //audioUnknown1
            return AudioData.IsLoaded() ? &AudioData->MNAM.value : NULL;
        case 80: //audioUnknown2
            return AudioData.IsLoaded() ? &AudioData->NNAM.value : NULL;
        case 81: //xsrf_p
            *FieldValues = XSRF.value;
            return NULL;
        case 82: //xsrd_p
            *FieldValues = XSRD.value;
            return NULL;
        case 83: //target
            return &XTRG.value;
        case 84: //rangeRadius
            return XRDO.IsLoaded() ? &XRDO->rangeRadius : NULL;
        case 85: //rangeType
            return XRDO.IsLoaded() ? &XRDO->rangeType : NULL;
        case 86: //staticPercentage
            return XRDO.IsLoaded() ? &XRDO->staticPercentage : NULL;
        case 87: //positionReference
            return XRDO.IsLoaded() ? &XRDO->positionReference : NULL;
        case 88: //lockLevel
            return XLOC.IsLoaded() ? &XLOC->level : NULL;
        case 89: //unused6
            *FieldValues = XLOC.IsLoaded() ? &XLOC->unused1[0] : NULL;
            return NULL;
        case 90: //lockKey
            return XLOC.IsLoaded() ? &XLOC->key : NULL;
        case 91: //lockFlags
            return XLOC.IsLoaded() ? &XLOC->flags : NULL;
        case 92: //unused7
            *FieldValues = XLOC.IsLoaded() ? &XLOC->unused2[0] : NULL;
            return NULL;
        case 93: //lockUnknown1
            *FieldValues = XLOC.IsLoaded() ? &XLOC->unknown[0] : NULL;
            return NULL;
        case 94: //ammo
            return Ammo.IsLoaded() ? &Ammo->XAMT.value : NULL;
        case 95: //ammoCount
            return Ammo.IsLoaded() ? &Ammo->XAMC.value : NULL;
        case 96: //reflrefrs
            if(ListIndex >= XPWR.value.size())
                return NULL;

            switch(ListFieldID)
                {
                case 1: //reference
                    return &XPWR.value[ListIndex]->reference;
                case 2: //type
                    return &XPWR.value[ListIndex]->type;
                default:
                    return NULL;
                }
            return NULL;
        case 97: //litWaters
            *FieldValues = XLTW.IsLoaded() ? &XLTW.value[0] : NULL;
            return NULL;
        case 98: //actionFlags
            return &XACT.value;
        case 99: //navMesh
            return XNDP.IsLoaded() ? &XNDP->navMesh : NULL;
        case 100: //navUnknown1
            return XNDP.IsLoaded() ? &XNDP->unknown1 : NULL;
        case 101: //unused8
            *FieldValues = XNDP.IsLoaded() ? &XNDP->unused1[0] : NULL;
            return NULL;
        case 102: //portalLinkedRoom1
            return XPOD.IsLoaded() ? &XPOD->room1 : NULL;
        case 103: //portalLinkedRoom2
            return XPOD.IsLoaded() ? &XPOD->room2 : NULL;
        case 104: //portalWidth
            return XPTL.IsLoaded() ? &XPTL->width : NULL;
        case 105: //portalHeight
            return XPTL.IsLoaded() ? &XPTL->height : NULL;
        case 106: //portalPosX
            return XPTL.IsLoaded() ? &XPTL->xPos : NULL;
        case 107: //portalPosY
            return XPTL.IsLoaded() ? &XPTL->yPos : NULL;
        case 108: //portalPosZ
            return XPTL.IsLoaded() ? &XPTL->zPos : NULL;
        case 109: //portalQ1
            return XPTL.IsLoaded() ? &XPTL->q1 : NULL;
        case 110: //portalQ2
            return XPTL.IsLoaded() ? &XPTL->q2 : NULL;
        case 111: //portalQ3
            return XPTL.IsLoaded() ? &XPTL->q3 : NULL;
        case 112: //portalQ4
            return XPTL.IsLoaded() ? &XPTL->q4 : NULL;
        case 113: //seed
            return XSED.value;
        case 114: //roomCount
            return Room.IsLoaded() && Room->XRMR.IsLoaded() ? &Room->XRMR->count : NULL;
        case 115: //roomUnknown1
            *FieldValues = Room.IsLoaded() && Room->XRMR.IsLoaded() ? &Room->XRMR->unknown1[0] : NULL;
            return NULL;
        case 116: //rooms
            *FieldValues = Room.IsLoaded() && Room->XLRM.IsLoaded() ? &Room->XLRM.value[0] : NULL;
            return NULL;
        case 117: //occPlaneWidth
            return XOCP.IsLoaded() ? &XOCP->width : NULL;
        case 118: //occPlaneHeight
            return XOCP.IsLoaded() ? &XOCP->height : NULL;
        case 119: //occPlanePosX
            return XOCP.IsLoaded() ? &XOCP->xPos : NULL;
        case 120: //occPlanePosY
            return XOCP.IsLoaded() ? &XOCP->yPos : NULL;
        case 121: //occPlanePosZ
            return XOCP.IsLoaded() ? &XOCP->zPos : NULL;
        case 122: //occPlaneQ1
            return XOCP.IsLoaded() ? &XOCP->q1 : NULL;
        case 123: //occPlaneQ2
            return XOCP.IsLoaded() ? &XOCP->q2 : NULL;
        case 124: //occPlaneQ3
            return XOCP.IsLoaded() ? &XOCP->q3 : NULL;
        case 125: //occPlaneQ4
            return XOCP.IsLoaded() ? &XOCP->q4 : NULL;
        case 126: //occPlaneRight
            return XORD.IsLoaded() ? &XORD->right : NULL;
        case 127: //occPlaneLeft
            return XORD.IsLoaded() ? &XORD->left : NULL;
        case 128: //occPlaneBottom
            return XORD.IsLoaded() ? &XORD->bottom : NULL;
        case 129: //occPlaneTop
            return XORD.IsLoaded() ? &XORD->top : NULL;
        case 130: //lod1
            return XLOD.IsLoaded() ? &XLOD->lod1 : NULL;
        case 131: //lod2
            return XLOD.IsLoaded() ? &XLOD->lod2 : NULL;
        case 132: //lod3
            return XLOD.IsLoaded() ? &XLOD->lod3 : NULL;
        case 133: //ignoredBySandbox
            return &XIBS.value;
        case 134: //scale
            return &XSCL.value;
        case 135: //posX
            return &DATA.value.posX;
        case 136: //posY
            return &DATA.value.posY;
        case 137: //posZ
            return &DATA.value.posZ;
        case 138: //rotX
            return &DATA.value.rotX;
        case 139: //rotY
            return &DATA.value.rotY;
        case 140: //rotZ
            return &DATA.value.rotZ;
        case 141: //Parent
            return GetParentRecord();
        default:
            return NULL;
        }
    return NULL;
    }

bool REFRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
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
        case 7: //base
            NAME.value = *(FORMID *)FieldValue;
            return true;
        case 8: //encounterZone
            XEZN.value = *(FORMID *)FieldValue;
            return true;
        case 9: //XRGD
            XRGD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 10: //XRGB
            XRGB.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 11: //idleTime
            Patrol.Load();
            Patrol->XPRD.value = *(float *)FieldValue;
            break;
        case 12: //idle
            Patrol.Load();
            Patrol->INAM.value = *(FORMID *)FieldValue;
            return true;
        case 13: //unused1
            if(ArraySize != 4)
                break;
            Patrol.Load();
            Patrol->SCHR.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Patrol->SCHR.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            Patrol->SCHR.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            Patrol->SCHR.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 14: //numRefs
            Patrol.Load();
            Patrol->SCHR.value.numRefs = *(uint32_t *)FieldValue;
            break;
        case 15: //compiledSize
            Patrol.Load();
            Patrol->SCHR.value.compiledSize = *(uint32_t *)FieldValue;
            break;
        case 16: //lastIndex
            Patrol.Load();
            Patrol->SCHR.value.lastIndex = *(uint32_t *)FieldValue;
            break;
        case 17: //scriptType
            Patrol.Load();
            Patrol->SetType(*(uint16_t *)FieldValue);
            break;
        case 18: //scriptFlags
            Patrol.Load();
            Patrol->SetScriptFlagMask(*(uint16_t *)FieldValue);
            break;
        case 19: //compiled_p
            Patrol.Load();
            Patrol->SCDA.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 20: //scriptText
            Patrol.Load();
            Patrol->SCTX.Copy((char *)FieldValue);
            break;
        case 21: //vars
            Patrol.Load();
            if(ListFieldID == 0) //varsSize
                {
                Patrol->VARS.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = *(uint32_t *)FieldValue;
                    break;
                case 2: //unused1
                    if(ArraySize != 12)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = ((UINT8ARRAY)FieldValue)[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = ((UINT8ARRAY)FieldValue)[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = ((UINT8ARRAY)FieldValue)[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = ((UINT8ARRAY)FieldValue)[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = ((UINT8ARRAY)FieldValue)[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = ((UINT8ARRAY)FieldValue)[11];
                    break;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SetFlagMask(*(uint8_t *)FieldValue);
                    break;
                case 4: //unused2
                    if(ArraySize != 7)
                        break;
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = ((UINT8ARRAY)FieldValue)[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = ((UINT8ARRAY)FieldValue)[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = ((UINT8ARRAY)FieldValue)[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = ((UINT8ARRAY)FieldValue)[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = ((UINT8ARRAY)FieldValue)[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = ((UINT8ARRAY)FieldValue)[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = ((UINT8ARRAY)FieldValue)[6];
                    break;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Copy((char *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 22: //references
            Patrol.Load();
            if(ListFieldID == 0) //referencesSize
                {
                Patrol->SCR_.resize(ArraySize);
                return false;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    //Borrowing ArraySize to flag if the new value is a formID
                    Patrol->SCR_.value[ListIndex]->reference = *(uint32_t *)FieldValue;
                    Patrol->SCR_.value[ListIndex]->isSCRO = ArraySize ? true : false;
                    return ArraySize != 0;
                default:
                    break;
                }
            break;
        case 23: //topic
            Patrol.Load();
            Patrol->TNAM.value = *(FORMID *)FieldValue;
            return true;
        case 24: //levelMod
            XLCM.value = *(int32_t *)FieldValue;
            break;
        case 25: //owner
            Ownership.Load();
            Ownership->XOWN.value = *(FORMID *)FieldValue;
            return true;
        case 26: //rank
            Ownership.Load();
            *Ownership->XRNK.value = *(int32_t *)FieldValue;
            break;
        case 27: //count
            XCNT.value = *(int32_t *)FieldValue;
            break;
        case 28: //radius
            XRDS.value = *(float *)FieldValue;
            break;
        case 29: //health
            XHLP.value = *(float *)FieldValue;
            break;
        case 30: //radiation
            XRAD.value = *(float *)FieldValue;
            break;
        case 31: //charge
            XCHG.value = *(float *)FieldValue;
            break;
        case 32: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XDCR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //unknown1
                    if(ArraySize != 24)
                        break;
                    XDCR.value[ListIndex]->unknown1[0] = ((UINT8ARRAY)FieldValue)[0];
                    XDCR.value[ListIndex]->unknown1[1] = ((UINT8ARRAY)FieldValue)[1];
                    XDCR.value[ListIndex]->unknown1[2] = ((UINT8ARRAY)FieldValue)[2];
                    XDCR.value[ListIndex]->unknown1[3] = ((UINT8ARRAY)FieldValue)[3];
                    XDCR.value[ListIndex]->unknown1[4] = ((UINT8ARRAY)FieldValue)[4];
                    XDCR.value[ListIndex]->unknown1[5] = ((UINT8ARRAY)FieldValue)[5];
                    XDCR.value[ListIndex]->unknown1[6] = ((UINT8ARRAY)FieldValue)[6];
                    XDCR.value[ListIndex]->unknown1[7] = ((UINT8ARRAY)FieldValue)[7];
                    XDCR.value[ListIndex]->unknown1[8] = ((UINT8ARRAY)FieldValue)[8];
                    XDCR.value[ListIndex]->unknown1[9] = ((UINT8ARRAY)FieldValue)[9];
                    XDCR.value[ListIndex]->unknown1[10] = ((UINT8ARRAY)FieldValue)[10];
                    XDCR.value[ListIndex]->unknown1[11] = ((UINT8ARRAY)FieldValue)[11];
                    XDCR.value[ListIndex]->unknown1[12] = ((UINT8ARRAY)FieldValue)[12];
                    XDCR.value[ListIndex]->unknown1[13] = ((UINT8ARRAY)FieldValue)[13];
                    XDCR.value[ListIndex]->unknown1[14] = ((UINT8ARRAY)FieldValue)[14];
                    XDCR.value[ListIndex]->unknown1[15] = ((UINT8ARRAY)FieldValue)[15];
                    XDCR.value[ListIndex]->unknown1[16] = ((UINT8ARRAY)FieldValue)[16];
                    XDCR.value[ListIndex]->unknown1[17] = ((UINT8ARRAY)FieldValue)[17];
                    XDCR.value[ListIndex]->unknown1[18] = ((UINT8ARRAY)FieldValue)[18];
                    XDCR.value[ListIndex]->unknown1[19] = ((UINT8ARRAY)FieldValue)[19];
                    XDCR.value[ListIndex]->unknown1[20] = ((UINT8ARRAY)FieldValue)[20];
                    XDCR.value[ListIndex]->unknown1[21] = ((UINT8ARRAY)FieldValue)[21];
                    XDCR.value[ListIndex]->unknown1[22] = ((UINT8ARRAY)FieldValue)[22];
                    XDCR.value[ListIndex]->unknown1[23] = ((UINT8ARRAY)FieldValue)[23];
                    break;
                default:
                    break;
                }
            break;
        case 33: //linkedReference
            XLKR.value = *(FORMID *)FieldValue;
            return true;
        case 34: //startRed
            XCLP.Load();
            XCLP->start.red = *(uint8_t *)FieldValue;
            break;
        case 35: //startRed
            XCLP.Load();
            XCLP->start.green = *(uint8_t *)FieldValue;
            break;
        case 36: //startBlue
            XCLP.Load();
            XCLP->start.blue = *(uint8_t *)FieldValue;
            break;
        case 37: //unused2
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->start.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 38: //endRed
            XCLP.Load();
            XCLP->end.red = *(uint8_t *)FieldValue;
            break;
        case 39: //endGreen
            XCLP.Load();
            XCLP->end.green = *(uint8_t *)FieldValue;
            break;
        case 40: //endBlue
            XCLP.Load();
            XCLP->end.blue = *(uint8_t *)FieldValue;
            break;
        case 41: //unused3
            if(ArraySize != 1)
                break;
            XCLP.Load();
            XCLP->end.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 42: //rclr_p
            RCLR.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 43: //activateParentFlags
            ActivateParents.Load();
            ActivateParents->SetFlagMask(*(uint8_t *)FieldValue);
            break;
        case 44: //activateParentRefs
            ActivateParents.Load();
            if(ListFieldID == 0) //activateParentRefsSize
                {
                ActivateParents->XAPR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = *(float *)FieldValue;
                    break;
                default:
                    break;
                }
            break;
        case 45: //prompt
            XATO.Copy((char *)FieldValue);
            break;
        case 46: //parent
            XESP.Load();
            XESP->parent = *(FORMID *)FieldValue;
            return true;
        case 47: //parentFlags
            SetParentFlagMask(*(uint8_t *)FieldValue);
            break;
        case 48: //unused4
            if(ArraySize != 3)
                break;
            XESP.Load();
            XESP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XESP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            XESP->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 49: //emittance
            XEMI.value = *(FORMID *)FieldValue;
            return true;
        case 50: //boundRef
            XMBR.value = *(FORMID *)FieldValue;
            return true;
        case 51: //primitiveX
            XPRM.Load();
            XPRM->xBound = *(float *)FieldValue;
            break;
        case 52: //primitiveY
            XPRM.Load();
            XPRM->yBound = *(float *)FieldValue;
            break;
        case 53: //primitiveZ
            XPRM.Load();
            XPRM->zBound = *(float *)FieldValue;
            break;
        case 54: //primitiveRed
            XPRM.Load();
            XPRM->red = *(float *)FieldValue;
            break;
        case 55: //primitiveGreen
            XPRM.Load();
            XPRM->green = *(float *)FieldValue;
            break;
        case 56: //primitiveBlue
            XPRM.Load();
            XPRM->blue = *(float *)FieldValue;
            break;
        case 57: //primitiveUnknown
            XPRM.Load();
            XPRM->unknown = *(float *)FieldValue;
            break;
        case 58: //primitiveType
            SetPrimitiveType(*(uint32_t *)FieldValue);
            break;
        case 59: //collisionType
            SetCollisionType(*(uint32_t *)FieldValue);
            break;
        case 60: //extentX
            XMBO.Load();
            XMBO->x = *(float *)FieldValue;
            break;
        case 61: //extentY
            XMBO.Load();
            XMBO->y = *(float *)FieldValue;
            break;
        case 62: //extentZ
            XMBO.Load();
            XMBO->z = *(float *)FieldValue;
            break;
        case 63: //destinationFid
            XTEL.Load();
            XTEL->destinationFid = *(FORMID *)FieldValue;
            return true;
        case 64: //destinationPosX
            XTEL.Load();
            XTEL->destination.posX = *(float *)FieldValue;
            break;
        case 65: //destinationPosY
            XTEL.Load();
            XTEL->destination.posY = *(float *)FieldValue;
            break;
        case 66: //destinationPosZ
            XTEL.Load();
            XTEL->destination.posZ = *(float *)FieldValue;
            break;
        case 67: //destinationRotX
            XTEL.Load();
            XTEL->destination.rotX = *(float *)FieldValue;
            break;
        case 68: //destinationRotY
            XTEL.Load();
            XTEL->destination.rotY = *(float *)FieldValue;
            break;
        case 69: //destinationRotZ
            XTEL.Load();
            XTEL->destination.rotZ = *(float *)FieldValue;
            break;
        case 70: //destinationFlags
            SetDestFlagMask(*(uint32_t *)FieldValue);
            break;
        case 71: //markerFlags
            SetMapFlagMask(*(uint8_t *)FieldValue);
            break;
        case 72: //markerFull
            MapData.Load();
            MapData->FULL.Copy((char *)FieldValue);
            break;
        case 73: //markerType
            SetMapType(*(uint8_t *)FieldValue);
            break;
        case 74: //unused5
            if(ArraySize != 1)
                break;
            MapData.Load();
            MapData->TNAM.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 75: //markerReputation
            MapData.Load();
            MapData->WMI1.value = *(FORMID *)FieldValue;
            return true;
        case 76: //audioFull_p
            AudioData.Load();
            AudioData->FULL.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 77: //audioLocation
            AudioData.Load();
            AudioData->CNAM.value = *(FORMID *)FieldValue;
            return true;
        case 78: //audioBnam_p
            AudioData.Load();
            AudioData->BNAM.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 79: //audioUnknown1
            AudioData.Load();
            AudioData->MNAM.value = *(float *)FieldValue;
            break;
        case 80: //audioUnknown2
            AudioData.Load();
            AudioData->NNAM.value = *(float *)FieldValue;
            break;
        case 81: //xsrf_p
            XSRF.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 82: //xsrd_p
            XSRD.Copy((UINT8ARRAY)FieldValue, ArraySize);
            break;
        case 83: //target
            XTRG.value = *(FORMID *)FieldValue;
            return true;
        case 84: //rangeRadius
            XRDO.Load();
            XRDO->rangeRadius = *(float *)FieldValue;
            break;
        case 85: //rangeType
            SetBroadcastType(*(uint32_t *)FieldValue);
            break;
        case 86: //staticPercentage
            XRDO.Load();
            XRDO->staticPercentage = *(float *)FieldValue;
            break;
        case 87: //positionReference
            XRDO.Load();
            XRDO->positionReference = *(FORMID *)FieldValue;
            return true;
        case 88: //lockLevel
            XLOC.Load();
            XLOC->level = *(uint8_t *)FieldValue;
            break;
        case 89: //unused6
            if(ArraySize != 3)
                break;
            XLOC.Load();
            XLOC->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XLOC->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            XLOC->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 90: //lockKey
            XLOC.Load();
            XLOC->key = *(FORMID *)FieldValue;
            return true;
        case 91: //lockFlags
            SetLockFlagMask(*(uint8_t *)FieldValue);
            break;
        case 92: //unused7
            if(ArraySize != 3)
                break;
            XLOC.Load();
            XLOC->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            XLOC->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            XLOC->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 93: //lockUnknown1
            if(ArraySize != 8)
                break;
            XLOC.Load();
            XLOC->unknown[0] = ((UINT8ARRAY)FieldValue)[0];
            XLOC->unknown[1] = ((UINT8ARRAY)FieldValue)[1];
            XLOC->unknown[2] = ((UINT8ARRAY)FieldValue)[2];
            XLOC->unknown[3] = ((UINT8ARRAY)FieldValue)[3];
            XLOC->unknown[4] = ((UINT8ARRAY)FieldValue)[4];
            XLOC->unknown[5] = ((UINT8ARRAY)FieldValue)[5];
            XLOC->unknown[6] = ((UINT8ARRAY)FieldValue)[6];
            XLOC->unknown[7] = ((UINT8ARRAY)FieldValue)[7];
            break;
        case 94: //ammo
            Ammo.Load();
            Ammo->XAMT.value = *(FORMID *)FieldValue;
            return true;
        case 95: //ammoCount
            Ammo.Load();
            Ammo->XAMC.value = *(int32_t *)FieldValue;
            break;
        case 96: //reflrefrs
            if(ListFieldID == 0) //reflrefrsSize
                {
                XPWR.resize(ArraySize);
                return false;
                }

            if(ListIndex >= XPWR.value.size())
                break;

            switch(ListFieldID)
                {
                case 1: //reference
                    XPWR.value[ListIndex]->reference = *(FORMID *)FieldValue;
                    return true;
                case 2: //type
                    XPWR.value[ListIndex]->SetType(*(uint32_t *)FieldValue);
                    break;
                default:
                    break;
                }
            break;
        case 97: //litWaters
            XLTW.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                XLTW.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 98: //actionFlags
            SetActionFlagMask(*(uint32_t *)FieldValue);
            break;
        case 99: //navMesh
            XNDP.Load();
            XNDP->navMesh = *(FORMID *)FieldValue;
            return true;
        case 100: //navUnknown1
            XNDP.Load();
            XNDP->unknown1 = *(uint16_t *)FieldValue;
            break;
        case 101: //unused8
            if(ArraySize != 2)
                break;
            XNDP.Load();
            XNDP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            XNDP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 102: //portalLinkedRoom1
            XPOD.Load();
            XPOD->room1 = *(FORMID *)FieldValue;
            return true;
        case 103: //portalLinkedRoom2
            XPOD.Load();
            XPOD->room2 = *(FORMID *)FieldValue;
            return true;
        case 104: //portalWidth
            XPTL.Load();
            XPTL->width = *(float *)FieldValue;
            break;
        case 105: //portalHeight
            XPTL.Load();
            XPTL->height = *(float *)FieldValue;
            break;
        case 106: //portalPosX
            XPTL.Load();
            XPTL->xPos = *(float *)FieldValue;
            break;
        case 107: //portalPosY
            XPTL.Load();
            XPTL->yPos = *(float *)FieldValue;
            break;
        case 108: //portalPosZ
            XPTL.Load();
            XPTL->zPos = *(float *)FieldValue;
            break;
        case 109: //portalQ1
            XPTL.Load();
            XPTL->q1 = *(float *)FieldValue;
            break;
        case 110: //portalQ2
            XPTL.Load();
            XPTL->q2 = *(float *)FieldValue;
            break;
        case 111: //portalQ3
            XPTL.Load();
            XPTL->q3 = *(float *)FieldValue;
            break;
        case 112: //portalQ4
            XPTL.Load();
            XPTL->q4 = *(float *)FieldValue;
            break;
        case 113: //seed
            *XSED.value = *(uint8_t *)FieldValue;
            break;
        case 114: //roomCount
            Room.Load();
            Room->XRMR.Load();
            Room->XRMR->count = *(uint16_t *)FieldValue;
            break;
        case 115: //roomUnknown1
            if(ArraySize != 2)
                break;
            Room.Load();
            Room->XRMR.Load();
            Room->XRMR->unknown1[0] = ((UINT8ARRAY)FieldValue)[0];
            Room->XRMR->unknown1[1] = ((UINT8ARRAY)FieldValue)[1];
            break;
        case 116: //rooms
            Room.Load();
            Room->XLRM.resize(ArraySize);
            for(uint32_t x = 0; x < ArraySize; x++)
                Room->XLRM.value[x] = ((FORMIDARRAY)FieldValue)[x];
            return true;
        case 117: //occPlaneWidth
            XOCP.Load();
            XOCP->width = *(float *)FieldValue;
            break;
        case 118: //occPlaneHeight
            XOCP.Load();
            XOCP->height = *(float *)FieldValue;
            break;
        case 119: //occPlanePosX
            XOCP.Load();
            XOCP->xPos = *(float *)FieldValue;
            break;
        case 120: //occPlanePosY
            XOCP.Load();
            XOCP->yPos = *(float *)FieldValue;
            break;
        case 121: //occPlanePosZ
            XOCP.Load();
            XOCP->zPos = *(float *)FieldValue;
            break;
        case 122: //occPlaneQ1
            XOCP.Load();
            XOCP->q1 = *(float *)FieldValue;
            break;
        case 123: //occPlaneQ2
            XOCP.Load();
            XOCP->q2 = *(float *)FieldValue;
            break;
        case 124: //occPlaneQ3
            XOCP.Load();
            XOCP->q3 = *(float *)FieldValue;
            break;
        case 125: //occPlaneQ4
            XOCP.Load();
            XOCP->q4 = *(float *)FieldValue;
            break;
        case 126: //occPlaneRight
            XORD.Load();
            XORD->right = *(FORMID *)FieldValue;
            return true;
        case 127: //occPlaneLeft
            XORD.Load();
            XORD->left = *(FORMID *)FieldValue;
            return true;
        case 128: //occPlaneBottom
            XORD.Load();
            XORD->bottom = *(FORMID *)FieldValue;
            return true;
        case 129: //occPlaneTop
            XORD.Load();
            XORD->top = *(FORMID *)FieldValue;
            return true;
        case 130: //lod1
            XLOD.Load();
            XLOD->lod1 = *(float *)FieldValue;
            break;
        case 131: //lod2
            XLOD.Load();
            XLOD->lod2 = *(float *)FieldValue;
            break;
        case 132: //lod3
            XLOD.Load();
            XLOD->lod3 = *(float *)FieldValue;
            break;
        case 133: //ignoredBySandbox
            XIBS.value = *(uint8_t *)FieldValue;
            break;
        case 134: //scale
            XSCL.value = *(float *)FieldValue;
            break;
        case 135: //posX
            DATA.value.posX = *(float *)FieldValue;
            break;
        case 136: //posY
            DATA.value.posY = *(float *)FieldValue;
            break;
        case 137: //posZ
            DATA.value.posZ = *(float *)FieldValue;
            break;
        case 138: //rotX
            DATA.value.rotX = *(float *)FieldValue;
            break;
        case 139: //rotY
            DATA.value.rotY = *(float *)FieldValue;
            break;
        case 140: //rotZ
            DATA.value.rotZ = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void REFRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    FNVSCHR defaultSCHR;

    GENVARS defaultVARS;
    GENSCR_ defaultSCR_;
    GENCLR defaultCLR;
    GENXDCR defaultXDCR;
    GENXAPR defaultXAPR;
    GENXESP defaultXESP;
    GENPOSDATA defaultDATA;

    GENXTEL defaultXTEL;
    GENXPRM defaultXPRM;
    GENXMBO defaultXMBO;
    GENTNAM defaultTNAM;
    GENXRDO defaultXRDO;
    FNVXLOC defaultXLOC;
    GENXLOD defaultXLOD;
    GENXORD defaultXORD;
    GENPOSITION defaultPOS;
    GENXPOD defaultXPOD;
    GENXNDP defaultXNDP;
    GENXPWR defaultXPWR;
    GENXRMR defaultXRMR;
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
        case 7: //base
            NAME.Unload();
            return;
        case 8: //encounterZone
            XEZN.Unload();
            return;
        case 9: //XRGD
            XRGD.Unload();
            return;
        case 10: //XRGB
            XRGB.Unload();
            return;
        case 11: //idleTime
            if(Patrol.IsLoaded())
                Patrol->XPRD.Unload();
            return;
        case 12: //idle
            if(Patrol.IsLoaded())
                Patrol->INAM.Unload();
            return;
        case 13: //unused1
            if(Patrol.IsLoaded())
                {
                Patrol->SCHR.value.unused1[0] = defaultSCHR.unused1[0];
                Patrol->SCHR.value.unused1[1] = defaultSCHR.unused1[1];
                Patrol->SCHR.value.unused1[2] = defaultSCHR.unused1[2];
                Patrol->SCHR.value.unused1[3] = defaultSCHR.unused1[3];
                }
            return;
        case 14: //numRefs
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.numRefs = defaultSCHR.numRefs;
            return;
        case 15: //compiledSize
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.compiledSize = defaultSCHR.compiledSize;
            return;
        case 16: //lastIndex
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.lastIndex = defaultSCHR.lastIndex;
            return;
        case 17: //scriptType
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.scriptType = defaultSCHR.scriptType;
            return;
        case 18: //scriptFlags
            if(Patrol.IsLoaded())
                Patrol->SCHR.value.flags = defaultSCHR.flags;
            return;
        case 19: //compiled_p
            if(Patrol.IsLoaded())
                Patrol->SCDA.Unload();
            return;
        case 20: //scriptText
            if(Patrol.IsLoaded())
                Patrol->SCTX.Unload();
            return;
        case 21: //vars
            if(!Patrol.IsLoaded())
                return;

            if(ListFieldID == 0) //varsSize
                {
                Patrol->VARS.Unload();
                return;
                }

            if(ListIndex >= Patrol->VARS.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //index
                    Patrol->VARS.value[ListIndex]->SLSD.value.index = defaultVARS.SLSD.value.index;
                    return;
                case 2: //unused1
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[0] = defaultVARS.SLSD.value.unused1[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[1] = defaultVARS.SLSD.value.unused1[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[2] = defaultVARS.SLSD.value.unused1[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[3] = defaultVARS.SLSD.value.unused1[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[4] = defaultVARS.SLSD.value.unused1[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[5] = defaultVARS.SLSD.value.unused1[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[6] = defaultVARS.SLSD.value.unused1[6];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[7] = defaultVARS.SLSD.value.unused1[7];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[8] = defaultVARS.SLSD.value.unused1[8];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[9] = defaultVARS.SLSD.value.unused1[9];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[10] = defaultVARS.SLSD.value.unused1[10];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused1[11] = defaultVARS.SLSD.value.unused1[11];
                    return;
                case 3: //flags
                    Patrol->VARS.value[ListIndex]->SLSD.value.flags = defaultVARS.SLSD.value.flags;
                    return;
                case 4: //unused2
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[0] = defaultVARS.SLSD.value.unused2[0];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[1] = defaultVARS.SLSD.value.unused2[1];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[2] = defaultVARS.SLSD.value.unused2[2];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[3] = defaultVARS.SLSD.value.unused2[3];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[4] = defaultVARS.SLSD.value.unused2[4];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[5] = defaultVARS.SLSD.value.unused2[5];
                    Patrol->VARS.value[ListIndex]->SLSD.value.unused2[6] = defaultVARS.SLSD.value.unused2[6];
                    return;
                case 5: //name
                    Patrol->VARS.value[ListIndex]->SCVR.Unload();
                    return;
                default:
                    return;
                }
            return;
        case 22: //references
            if(!Patrol.IsLoaded())
                return;

            if(ListFieldID == 0) //referencesSize
                {
                Patrol->SCR_.Unload();
                return;
                }

            if(ListIndex >= Patrol->SCR_.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    Patrol->SCR_.value[ListIndex]->reference = defaultSCR_.reference;
                    Patrol->SCR_.value[ListIndex]->isSCRO = defaultSCR_.isSCRO;
                    return;
                default:
                    return;
                }
            return;
        case 23: //topic
            if(Patrol.IsLoaded())
                Patrol->TNAM.Unload();
            return;
        case 24: //levelMod
            XLCM.Unload();
            return;
        case 25: //owner
            if(Ownership.IsLoaded())
                Ownership->XOWN.Unload();
            return;
        case 26: //rank
            if(Ownership.IsLoaded())
                Ownership->XRNK.Unload();
            return;
        case 27: //count
            XCNT.Unload();
            return;
        case 28: //radius
            XRDS.Unload();
            return;
        case 29: //health
            XHLP.Unload();
            return;
        case 30: //radiation
            XRAD.Unload();
            return;
        case 31: //charge
            XCHG.Unload();
            return;
        case 32: //decals
            if(ListFieldID == 0) //decalsSize
                {
                XDCR.Unload();
                return;
                }

            if(ListIndex >= XDCR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    XDCR.value[ListIndex]->reference = defaultXDCR.reference;
                    return;
                case 2: //unknown1
                    XDCR.value[ListIndex]->unknown1[0] = defaultXDCR.unknown1[0];
                    XDCR.value[ListIndex]->unknown1[1] = defaultXDCR.unknown1[1];
                    XDCR.value[ListIndex]->unknown1[2] = defaultXDCR.unknown1[2];
                    XDCR.value[ListIndex]->unknown1[3] = defaultXDCR.unknown1[3];
                    XDCR.value[ListIndex]->unknown1[4] = defaultXDCR.unknown1[4];
                    XDCR.value[ListIndex]->unknown1[5] = defaultXDCR.unknown1[5];
                    XDCR.value[ListIndex]->unknown1[6] = defaultXDCR.unknown1[6];
                    XDCR.value[ListIndex]->unknown1[7] = defaultXDCR.unknown1[7];
                    XDCR.value[ListIndex]->unknown1[8] = defaultXDCR.unknown1[8];
                    XDCR.value[ListIndex]->unknown1[9] = defaultXDCR.unknown1[9];
                    XDCR.value[ListIndex]->unknown1[10] = defaultXDCR.unknown1[10];
                    XDCR.value[ListIndex]->unknown1[11] = defaultXDCR.unknown1[11];
                    XDCR.value[ListIndex]->unknown1[12] = defaultXDCR.unknown1[12];
                    XDCR.value[ListIndex]->unknown1[13] = defaultXDCR.unknown1[13];
                    XDCR.value[ListIndex]->unknown1[14] = defaultXDCR.unknown1[14];
                    XDCR.value[ListIndex]->unknown1[15] = defaultXDCR.unknown1[15];
                    XDCR.value[ListIndex]->unknown1[16] = defaultXDCR.unknown1[16];
                    XDCR.value[ListIndex]->unknown1[17] = defaultXDCR.unknown1[17];
                    XDCR.value[ListIndex]->unknown1[18] = defaultXDCR.unknown1[18];
                    XDCR.value[ListIndex]->unknown1[19] = defaultXDCR.unknown1[19];
                    XDCR.value[ListIndex]->unknown1[20] = defaultXDCR.unknown1[20];
                    XDCR.value[ListIndex]->unknown1[21] = defaultXDCR.unknown1[21];
                    XDCR.value[ListIndex]->unknown1[22] = defaultXDCR.unknown1[22];
                    XDCR.value[ListIndex]->unknown1[23] = defaultXDCR.unknown1[23];
                    return;
                default:
                    return;
                }
            return;
        case 33: //linkedReference
            XLKR.Unload();
            return;
        case 34: //startRed
            if(XCLP.IsLoaded())
                XCLP->start.red = defaultCLR.red;
            return;
        case 35: //startRed
            if(XCLP.IsLoaded())
                XCLP->start.green = defaultCLR.green;
            return;
        case 36: //startBlue
            if(XCLP.IsLoaded())
                XCLP->start.blue = defaultCLR.blue;
            return;
        case 37: //unused2
            if(XCLP.IsLoaded())
                XCLP->start.unused1 = defaultCLR.unused1;
            return;
        case 38: //endRed
            if(XCLP.IsLoaded())
                XCLP->end.red = defaultCLR.red;
            return;
        case 39: //endGreen
            if(XCLP.IsLoaded())
                XCLP->end.green = defaultCLR.green;
            return;
        case 40: //endBlue
            if(XCLP.IsLoaded())
                XCLP->end.blue = defaultCLR.blue;
            return;
        case 41: //unused3
            if(XCLP.IsLoaded())
                XCLP->end.unused1 = defaultCLR.unused1;
            return;
        case 42: //rclr_p
            RCLR.Unload();
            return;
        case 43: //activateParentFlags
            if(ActivateParents.IsLoaded())
                ActivateParents->XAPD.Unload();
            return;
        case 44: //activateParentRefs
            if(!ActivateParents.IsLoaded())
                return;

            if(ListFieldID == 0) //activateParentRefsSize
                {
                ActivateParents->XAPR.Unload();
                return;
                }

            if(ListIndex >= ActivateParents->XAPR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    ActivateParents->XAPR.value[ListIndex]->reference = defaultXAPR.reference;
                    return;
                case 2: //delay
                    ActivateParents->XAPR.value[ListIndex]->delay = defaultXAPR.delay;
                    return;
                default:
                    return;
                }
            return;
        case 45: //prompt
            XATO.Unload();
            return;
        case 46: //parent
            if(XESP.IsLoaded())
                XESP->parent = defaultXESP.parent;
            return;
        case 47: //parentFlags
            if(XESP.IsLoaded())
                SetParentFlagMask(defaultXESP.flags);
            return;
        case 48: //unused4
            if(XESP.IsLoaded())
                {
                XESP->unused1[0] = defaultXESP.unused1[0];
                XESP->unused1[1] = defaultXESP.unused1[1];
                XESP->unused1[2] = defaultXESP.unused1[2];
                }
            return;
        case 49: //emittance
            XEMI.Unload();
            return;
        case 50: //boundRef
            XMBR.Unload();
            return;
        case 51: //primitiveX
            if(XPRM.IsLoaded())
                XPRM->xBound = defaultXPRM.xBound;
            return;
        case 52: //primitiveY
            if(XPRM.IsLoaded())
                XPRM->yBound = defaultXPRM.yBound;
            return;
        case 53: //primitiveZ
            if(XPRM.IsLoaded())
                XPRM->zBound = defaultXPRM.zBound;
            return;
        case 54: //primitiveRed
            if(XPRM.IsLoaded())
                XPRM->red = defaultXPRM.red;
            return;
        case 55: //primitiveGreen
            if(XPRM.IsLoaded())
                XPRM->green = defaultXPRM.green;
            return;
        case 56: //primitiveBlue
            if(XPRM.IsLoaded())
                XPRM->blue = defaultXPRM.blue;
            return;
        case 57: //primitiveUnknown
            if(XPRM.IsLoaded())
                XPRM->unknown = defaultXPRM.unknown;
            return;
        case 58: //primitiveType
            if(XPRM.IsLoaded())
                SetPrimitiveType(defaultXPRM.type);
            return;
        case 59: //collisionType
            XTRI.Unload();
            return;
        case 60: //extentX
            if(XMBO.IsLoaded())
                XMBO->x = defaultXMBO.x;
            return;
        case 61: //extentY
            if(XMBO.IsLoaded())
                XMBO->y = defaultXMBO.y;
            return;
        case 62: //extentZ
            if(XMBO.IsLoaded())
                XMBO->z = defaultXMBO.z;
            return;
        case 63: //destinationFid
            if(XTEL.IsLoaded())
                XTEL->destinationFid = defaultXTEL.destinationFid;
            return;
        case 64: //destinationPosX
            if(XTEL.IsLoaded())
                XTEL->destination.posX = defaultXTEL.destination.posX;
            return;
        case 65: //destinationPosY
            if(XTEL.IsLoaded())
                XTEL->destination.posY = defaultXTEL.destination.posY;
            return;
        case 66: //destinationPosZ
            if(XTEL.IsLoaded())
                XTEL->destination.posZ = defaultXTEL.destination.posZ;
            return;
        case 67: //destinationRotX
            if(XTEL.IsLoaded())
                XTEL->destination.rotX = defaultXTEL.destination.rotX;
            return;
        case 68: //destinationRotY
            if(XTEL.IsLoaded())
                XTEL->destination.rotY = defaultXTEL.destination.rotY;
            return;
        case 69: //destinationRotZ
            if(XTEL.IsLoaded())
                XTEL->destination.rotZ = defaultXTEL.destination.rotZ;
            return;
        case 70: //destinationFlags
            if(XTEL.IsLoaded())
                SetDestFlagMask(defaultXTEL.flags);
            return;
        case 71: //markerFlags
            if(MapData.IsLoaded())
                MapData->FNAM.Unload();
            return;
        case 72: //markerFull
            if(MapData.IsLoaded())
                MapData->FULL.Unload();
            return;
        case 73: //markerType
            if(MapData.IsLoaded())
                SetMapType(defaultTNAM.markerType);
            return;
        case 74: //unused5
            if(MapData.IsLoaded())
                MapData->TNAM.value.unused1 = defaultTNAM.unused1;
            return;
        case 75: //markerReputation
            if(MapData.IsLoaded())
                MapData->WMI1.Unload();
            return;
        case 76: //audioFull_p
            if(AudioData.IsLoaded())
                AudioData->FULL.Unload();
            return;
        case 77: //audioLocation
            if(AudioData.IsLoaded())
                AudioData->CNAM.Unload();
            return;
        case 78: //audioBnam_p
            if(AudioData.IsLoaded())
                AudioData->BNAM.Unload();
            return;
        case 79: //audioUnknown1
            if(AudioData.IsLoaded())
                AudioData->MNAM.Unload();
            return;
        case 80: //audioUnknown2
            if(AudioData.IsLoaded())
                AudioData->NNAM.Unload();
            return;
        case 81: //xsrf_p
            XSRF.Unload();
            return;
        case 82: //xsrd_p
            XSRD.Unload();
            return;
        case 83: //target
            XTRG.Unload();
            return;
        case 84: //rangeRadius
            if(XRDO.IsLoaded())
                XRDO->rangeRadius = defaultXRDO.rangeRadius;
            return;
        case 85: //rangeType
            if(XRDO.IsLoaded())
                SetBroadcastType(defaultXRDO.rangeType);
            return;
        case 86: //staticPercentage
            if(XRDO.IsLoaded())
                XRDO->staticPercentage = defaultXRDO.staticPercentage;
            return;
        case 87: //positionReference
            if(XRDO.IsLoaded())
                XRDO->positionReference = defaultXRDO.positionReference;
            return;
        case 88: //lockLevel
            if(XLOC.IsLoaded())
                XLOC->level = defaultXLOC.level;
            return;
        case 89: //unused6
            if(XLOC.IsLoaded())
                {
                XLOC->unused1[0] = defaultXLOC.unused1[0];
                XLOC->unused1[1] = defaultXLOC.unused1[1];
                XLOC->unused1[2] = defaultXLOC.unused1[2];
                }
            return;
        case 90: //lockKey
            if(XLOC.IsLoaded())
                XLOC->key = defaultXLOC.key;
            return;
        case 91: //lockFlags
            if(XLOC.IsLoaded())
                SetLockFlagMask(defaultXLOC.flags);
            return;
        case 92: //unused7
            if(XLOC.IsLoaded())
                {
                XLOC->unused2[0] = defaultXLOC.unused2[0];
                XLOC->unused2[1] = defaultXLOC.unused2[1];
                XLOC->unused2[2] = defaultXLOC.unused2[2];
                }
            return;
        case 93: //lockUnknown1
            if(XLOC.IsLoaded())
                {
                XLOC->unknown[0] = defaultXLOC.unknown[0];
                XLOC->unknown[1] = defaultXLOC.unknown[1];
                XLOC->unknown[2] = defaultXLOC.unknown[2];
                XLOC->unknown[3] = defaultXLOC.unknown[3];
                XLOC->unknown[4] = defaultXLOC.unknown[4];
                XLOC->unknown[5] = defaultXLOC.unknown[5];
                XLOC->unknown[6] = defaultXLOC.unknown[6];
                XLOC->unknown[7] = defaultXLOC.unknown[7];
                }
            return;
        case 94: //ammo
            if(Ammo.IsLoaded())
                Ammo->XAMT.Unload();
            return;
        case 95: //ammoCount
            if(Ammo.IsLoaded())
                Ammo->XAMC.Unload();
            return;
        case 96: //reflrefrs
            if(ListFieldID == 0) //reflrefrsSize
                {
                XPWR.Unload();
                return;
                }

            if(ListIndex >= XPWR.value.size())
                return;

            switch(ListFieldID)
                {
                case 1: //reference
                    XPWR.value[ListIndex]->reference = defaultXPWR.reference;
                    return;
                case 2: //type
                    XPWR.value[ListIndex]->type = defaultXPWR.type;
                    return;
                default:
                    return;
                }
            return;
        case 97: //litWaters
            XLTW.Unload();
            return;
        case 98: //actionFlags
            XACT.Unload();
            return;
        case 99: //navMesh
            if(XNDP.IsLoaded())
                XNDP->navMesh = defaultXNDP.navMesh;
            return;
        case 100: //navUnknown1
            if(XNDP.IsLoaded())
                XNDP->unknown1 = defaultXNDP.unknown1;
            return;
        case 101: //unused8
            if(XNDP.IsLoaded())
                {
                XNDP->unused1[0] = defaultXNDP.unused1[0];
                XNDP->unused1[1] = defaultXNDP.unused1[1];
                }
            return;
        case 102: //portalLinkedRoom1
            if(XPOD.IsLoaded())
                XPOD->room1 = defaultXPOD.room1;
            return;
        case 103: //portalLinkedRoom2
            if(XPOD.IsLoaded())
                XPOD->room2 = defaultXPOD.room2;
            return;
        case 104: //portalWidth
            if(XPTL.IsLoaded())
                XPTL->width = defaultPOS.width;
            return;
        case 105: //portalHeight
            if(XPTL.IsLoaded())
                XPTL->height = defaultPOS.height;
            return;
        case 106: //portalPosX
            if(XPTL.IsLoaded())
                XPTL->xPos = defaultPOS.xPos;
            return;
        case 107: //portalPosY
            if(XPTL.IsLoaded())
                XPTL->yPos = defaultPOS.yPos;
            return;
        case 108: //portalPosZ
            if(XPTL.IsLoaded())
                XPTL->zPos = defaultPOS.zPos;
            return;
        case 109: //portalQ1
            if(XPTL.IsLoaded())
                XPTL->q1 = defaultPOS.q1;
            return;
        case 110: //portalQ2
            if(XPTL.IsLoaded())
                XPTL->q2 = defaultPOS.q2;
            return;
        case 111: //portalQ3
            if(XPTL.IsLoaded())
                XPTL->q3 = defaultPOS.q3;
            return;
        case 112: //portalQ4
            if(XPTL.IsLoaded())
                XPTL->q4 = defaultPOS.q4;
            return;
        case 113: //seed
            XSED.Unload();
            return;
        case 114: //roomCount
            if(Room.IsLoaded() && Room->XRMR.IsLoaded())
                Room->XRMR->count = defaultXRMR.count;
            return;
        case 115: //roomUnknown1
            if(Room.IsLoaded() && Room->XRMR.IsLoaded())
                {
                Room->XRMR->unknown1[0] = defaultXRMR.unknown1[0];
                Room->XRMR->unknown1[1] = defaultXRMR.unknown1[1];
                }
            return;
        case 116: //rooms
            if(Room.IsLoaded())
                Room->XLRM.Unload();
            return;
        case 117: //occPlaneWidth
            if(XOCP.IsLoaded())
                XOCP->width = defaultPOS.width;
            return;
        case 118: //occPlaneHeight
            if(XOCP.IsLoaded())
                XOCP->height = defaultPOS.height;
            return;
        case 119: //occPlanePosX
            if(XOCP.IsLoaded())
                XOCP->xPos = defaultPOS.xPos;
            return;
        case 120: //occPlanePosY
            if(XOCP.IsLoaded())
                XOCP->yPos = defaultPOS.yPos;
            return;
        case 121: //occPlanePosZ
            if(XOCP.IsLoaded())
                XOCP->zPos = defaultPOS.zPos;
            return;
        case 122: //occPlaneQ1
            if(XOCP.IsLoaded())
                XOCP->q1 = defaultPOS.q1;
            return;
        case 123: //occPlaneQ2
            if(XOCP.IsLoaded())
                XOCP->q2 = defaultPOS.q2;
            return;
        case 124: //occPlaneQ3
            if(XOCP.IsLoaded())
                XOCP->q3 = defaultPOS.q3;
            return;
        case 125: //occPlaneQ4
            if(XOCP.IsLoaded())
                XOCP->q4 = defaultPOS.q4;
            return;
        case 126: //occPlaneRight
            if(XORD.IsLoaded())
                XORD->right = defaultXORD.right;
            return;
        case 127: //occPlaneLeft
            if(XORD.IsLoaded())
                XORD->left = defaultXORD.left;
            return;
        case 128: //occPlaneBottom
            if(XORD.IsLoaded())
                XORD->bottom = defaultXORD.bottom;
            return;
        case 129: //occPlaneTop
            if(XORD.IsLoaded())
                XORD->top = defaultXORD.top;
            return;
        case 130: //lod1
            if(XLOD.IsLoaded())
                XLOD->lod1 = defaultXLOD.lod1;
            return;
        case 131: //lod2
            if(XLOD.IsLoaded())
                XLOD->lod2 = defaultXLOD.lod2;
            return;
        case 132: //lod3
            if(XLOD.IsLoaded())
                XLOD->lod3 = defaultXLOD.lod3;
            return;
        case 133: //ignoredBySandbox
            XIBS.Unload();
            return;
        case 134: //scale
            XSCL.Unload();
            return;
        case 135: //posX
            DATA.value.posX = defaultDATA.posX;
            return;
        case 136: //posY
            DATA.value.posY = defaultDATA.posY;
            return;
        case 137: //posZ
            DATA.value.posZ = defaultDATA.posZ;
            return;
        case 138: //rotX
            DATA.value.rotX = defaultDATA.rotX;
            return;
        case 139: //rotY
            DATA.value.rotY = defaultDATA.rotY;
            return;
        case 140: //rotZ
            DATA.value.rotZ = defaultDATA.rotZ;
            return;
        default:
            return;
        }
    }
}