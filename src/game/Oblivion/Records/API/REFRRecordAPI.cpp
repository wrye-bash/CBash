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
#include "..\REFRRecord.h"

namespace Ob
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
        case 3: //flags2
            return CB_UINT32_FLAG_FIELD;
        case 4: //eid
            return CB_ISTRING_FIELD;
        case 5: //base
            return CB_FORMID_FIELD;
        case 6: //destination
            return CB_FORMID_FIELD;
        case 7: //destinationPosX
            return CB_FLOAT32_FIELD;
        case 8: //destinationPosY
            return CB_FLOAT32_FIELD;
        case 9: //destinationPosZ
            return CB_FLOAT32_FIELD;
        case 10: //destinationRotX
            return CB_RADIAN_FIELD;
        case 11: //destinationRotY
            return CB_RADIAN_FIELD;
        case 12: //destinationRotZ
            return CB_RADIAN_FIELD;
        case 13: //lockLevel
            return CB_UINT8_FIELD;
        case 14: //unused1
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Data.IsLoaded() && Data->XLOC.IsLoaded() ? 3: 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 15: //lockKey
            return CB_FORMID_FIELD;
        case 16: //unused2
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Data.IsLoaded() && Data->XLOC.IsLoaded() ? 4: 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 17: //lockFlags
            return CB_UINT8_FLAG_FIELD;
        case 18: //unused3
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Data.IsLoaded() && Data->XLOC.IsLoaded() ? 3: 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 19: //owner
            return CB_FORMID_FIELD;
        case 20: //rank
            return CB_SINT32_FIELD;
        case 21: //globalVariable
            return CB_FORMID_FIELD;
        case 22: //parent
            return CB_FORMID_FIELD;
        case 23: //parentFlags
            return CB_UINT8_FLAG_FIELD;
        case 24: //unused4
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Data.IsLoaded() && Data->XESP.IsLoaded() ? 3: 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 25: //target
            return CB_FORMID_FIELD;
        case 26: //seed
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_OR_UINT32_FIELD;
                case 2: //WhichType
                    if(Data.IsLoaded() && Data->XSED.IsLoaded())
                        return Data->XSED->isOffset ? CB_UINT8_FIELD : CB_UINT32_FIELD;
                    return CB_UINT32_FIELD;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 27: //lod1
            return CB_FLOAT32_FIELD;
        case 28: //lod2
            return CB_FLOAT32_FIELD;
        case 29: //lod3
            return CB_FLOAT32_FIELD;
        case 30: //charge
            return CB_FLOAT32_FIELD;
        case 31: //health
            return CB_SINT32_FIELD;
        case 32: //unknownXPCIFormID
            return CB_FORMID_FIELD;
        case 33: //unknownXPCIString
            return CB_ISTRING_FIELD;
        case 34: //levelMod
            return CB_SINT32_FIELD;
        case 35: //unknownXRTMFormID
            return CB_FORMID_FIELD;
        case 36: //actionFlags
            return CB_UINT32_FLAG_FIELD;
        case 37: //count
            return CB_SINT32_FIELD;
        case 38: //markerFlags
            return CB_UINT8_FLAG_FIELD;
        case 39: //markerName
            return CB_STRING_FIELD;
        case 40: //markerType
            return CB_UINT8_TYPE_FIELD;
        case 41: //markerUnused
            switch(WhichAttribute)
                {
                case 0: //fieldType
                    return CB_UINT8_ARRAY_FIELD;
                case 1: //fieldSize
                    return Data.IsLoaded() && Data->Marker.IsLoaded() ? 1: 0;
                default:
                    return CB_UNKNOWN_FIELD;
                }
            return CB_UNKNOWN_FIELD;
        case 42: //scale
            return CB_FLOAT32_FIELD;
        case 43: //soulType
            return CB_UINT8_TYPE_FIELD;
        case 44: //posX
            return CB_FLOAT32_FIELD;
        case 45: //posY
            return CB_FLOAT32_FIELD;
        case 46: //posZ
            return CB_FLOAT32_FIELD;
        case 47: //rotX
            return CB_RADIAN_FIELD;
        case 48: //rotY
            return CB_RADIAN_FIELD;
        case 49: //rotZ
            return CB_RADIAN_FIELD;
        case 50: //Parent
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
        case 3: //flags2
            return &flagsUnk;
        case 50: //Parent
            return GetParentRecord();
        default:
            break;
        }
    if(!Data.IsLoaded())
        return NULL;
    switch(FieldID)
        {
        case 4: //eid
            return Data->EDID.value;
        case 5: //base
            return &Data->NAME.value;
        case 6: //destination
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destinationFid : NULL;
        case 7: //destinationPosX
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.posX : NULL;
        case 8: //destinationPosY
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.posY : NULL;
        case 9: //destinationPosZ
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.posZ : NULL;
        case 10: //destinationRotX
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.rotX : NULL;
        case 11: //destinationRotY
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.rotY : NULL;
        case 12: //destinationRotZ
            return Data->XTEL.IsLoaded() ? &Data->XTEL->destination.rotZ : NULL;
        case 13: //lockLevel
            return Data->XLOC.IsLoaded() ? &Data->XLOC->level : NULL;
        case 14: //unused1
            *FieldValues = Data->XLOC.IsLoaded() ? &Data->XLOC->unused1[0] : NULL;
            return NULL;
        case 15: //lockKey
            return Data->XLOC.IsLoaded() ? &Data->XLOC->key : NULL;
        case 16: //unused2
            *FieldValues = Data->XLOC.IsLoaded() ? &Data->XLOC->unused2[0] : NULL;
            return NULL;
        case 17: //lockFlags
            return Data->XLOC.IsLoaded() ? &Data->XLOC->flags : NULL;
        case 18: //unused3
            *FieldValues = Data->XLOC.IsLoaded() ? &Data->XLOC->unused3[0] : NULL;
            return NULL;
        case 19: //owner
            return Data->Ownership.IsLoaded() ? &Data->Ownership->XOWN.value : NULL;
        case 20: //rank
            return Data->Ownership.IsLoaded() ? Data->Ownership->XRNK.value : NULL;
        case 21: //globalVariable
            return (Data->Ownership.IsLoaded() && Data->Ownership->XGLB.IsLoaded()) ? &Data->Ownership->XGLB.value : NULL;
        case 22: //parent
            return Data->XESP.IsLoaded() ? &Data->XESP->parent : NULL;
        case 23: //parentFlags
            return Data->XESP.IsLoaded() ? &Data->XESP->flags : NULL;
        case 24: //unused4
            *FieldValues = Data->XESP.IsLoaded() ? &Data->XESP->unused1[0] : NULL;
            return NULL;
        case 25: //target
            return Data->XTRG.IsLoaded() ? &Data->XTRG.value : NULL;
        case 26: //seed
            if(Data->XSED.IsLoaded())
                {
                if(Data->XSED->isOffset)
                    return &Data->XSED->offset;
                return &Data->XSED->seed;
                }
            return NULL;
        case 27: //lod1
            return Data->XLOD.IsLoaded() ? &Data->XLOD->lod1 : NULL;
        case 28: //lod2
            return Data->XLOD.IsLoaded() ? &Data->XLOD->lod2 : NULL;
        case 29: //lod3
            return Data->XLOD.IsLoaded() ? &Data->XLOD->lod3 : NULL;
        case 30: //charge
            return Data->XCHG.IsLoaded() ? &Data->XCHG.value : NULL;
        case 31: //health
            return Data->XHLT.IsLoaded() ? &Data->XHLT.value : NULL;
        case 32: //unknownXPCIFormID
            return (Data->XPCI.IsLoaded() && Data->XPCI->XPCI.IsLoaded()) ? &Data->XPCI->XPCI.value : NULL;
        case 33: //unknownXPCIString
            return Data->XPCI.IsLoaded() ? Data->XPCI->FULL.value : NULL;
        case 34: //levelMod
            return Data->XLCM.IsLoaded() ? &Data->XLCM.value : NULL;
        case 35: //unknownXRTMFormID
            return Data->XRTM.IsLoaded() ? &Data->XRTM.value : NULL;
        case 36: //actionFlags
            return Data->XACT.IsLoaded() ? &Data->XACT.value : NULL;
        case 37: //count
            return Data->XCNT.IsLoaded() ? &Data->XCNT.value : NULL;
        case 38: //markerFlags
            return Data->Marker.IsLoaded() ? &Data->Marker->FNAM.value : NULL;
        case 39: //markerName
            return Data->Marker.IsLoaded() ? Data->Marker->FULL.value : NULL;
        case 40: //markerType
            return Data->Marker.IsLoaded() ? &Data->Marker->TNAM.value.markerType : NULL;
        case 41: //markerUnused
            *FieldValues = Data->Marker.IsLoaded() ? &Data->Marker->TNAM.value.unused1 : NULL;
            return NULL;
        case 42: //scale
            return Data->XSCL.IsLoaded() ? &Data->XSCL.value : NULL;
        case 43: //soulType
            return Data->XSOL.IsLoaded() ? &Data->XSOL.value : NULL;
        case 44: //posX
            return &Data->DATA.value.posX;
        case 45: //posY
            return &Data->DATA.value.posY;
        case 46: //posZ
            return &Data->DATA.value.posZ;
        case 47: //rotX
            return &Data->DATA.value.rotX;
        case 48: //rotY
            return &Data->DATA.value.rotY;
        case 49: //rotZ
            return &Data->DATA.value.rotZ;
        default:
            return NULL;
        }
    return NULL;
    }

bool REFRRecord::SetField(FIELD_IDENTIFIERS, void *FieldValue, uint32_t ArraySize)
    {
    Data.Load();
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(*(uint32_t *)FieldValue);
            break;
        case 3: //flags2
            SetHeaderUnknownFlagMask(*(uint32_t *)FieldValue);
            break;
        case 4: //eid
            Data->EDID.Copy((char *)FieldValue);
            break;
        case 5: //base
            Data->NAME.value = *(FORMID *)FieldValue;
            return true;
        case 6: //destination
            Data->XTEL.Load();
            Data->XTEL->destinationFid = *(FORMID *)FieldValue;
            return true;
        case 7: //destinationPosX
            Data->XTEL.Load();
            Data->XTEL->destination.posX = *(float *)FieldValue;
            break;
        case 8: //destinationPosY
            Data->XTEL.Load();
            Data->XTEL->destination.posY = *(float *)FieldValue;
            break;
        case 9: //destinationPosZ
            Data->XTEL.Load();
            Data->XTEL->destination.posZ = *(float *)FieldValue;
            break;
        case 10: //destinationRotX
            Data->XTEL.Load();
            Data->XTEL->destination.rotX = *(float *)FieldValue;
            break;
        case 11: //destinationRotY
            Data->XTEL.Load();
            Data->XTEL->destination.rotY = *(float *)FieldValue;
            break;
        case 12: //destinationRotZ
            Data->XTEL.Load();
            Data->XTEL->destination.rotZ = *(float *)FieldValue;
            break;
        case 13: //lockLevel
            Data->XLOC.Load();
            Data->XLOC->level = *(uint8_t *)FieldValue;
            break;
        case 14: //unused1
            if(ArraySize != 3)
                break;
            Data->XLOC.Load();
            Data->XLOC->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Data->XLOC->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            Data->XLOC->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 15: //lockKey
            Data->XLOC.Load();
            Data->XLOC->key = *(FORMID *)FieldValue;
            return true;
        case 16: //unused2
            if(ArraySize != 4)
                break;
            Data->XLOC.Load();
            Data->XLOC->unused2[0] = ((UINT8ARRAY)FieldValue)[0];
            Data->XLOC->unused2[1] = ((UINT8ARRAY)FieldValue)[1];
            Data->XLOC->unused2[2] = ((UINT8ARRAY)FieldValue)[2];
            Data->XLOC->unused2[3] = ((UINT8ARRAY)FieldValue)[3];
            break;
        case 17: //lockFlags
            SetLockFlagMask(*(uint8_t *)FieldValue);
            break;
        case 18: //unused3
            if(ArraySize != 3)
                break;
            Data->XLOC.Load();
            Data->XLOC->unused3[0] = ((UINT8ARRAY)FieldValue)[0];
            Data->XLOC->unused3[1] = ((UINT8ARRAY)FieldValue)[1];
            Data->XLOC->unused3[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 19: //owner
            Data->Ownership.Load();
            Data->Ownership->XOWN.value = *(FORMID *)FieldValue;
            return true;
        case 20: //rank
            Data->Ownership.Load();
            Data->Ownership->XRNK.Load();
            *Data->Ownership->XRNK.value = *(int32_t *)FieldValue;
            break;
        case 21: //globalVariable
            Data->Ownership.Load();
            Data->Ownership->XGLB.value = *(FORMID *)FieldValue;
            return true;
        case 22: //parent
            Data->XESP.Load();
            Data->XESP->parent = *(FORMID *)FieldValue;
            return true;
        case 23: //parentFlags
            SetParentFlagMask(*(uint8_t *)FieldValue);
            break;
        case 24: //unused4
            if(ArraySize != 3)
                break;
            Data->XESP.Load();
            Data->XESP->unused1[0] = ((UINT8ARRAY)FieldValue)[0];
            Data->XESP->unused1[1] = ((UINT8ARRAY)FieldValue)[1];
            Data->XESP->unused1[2] = ((UINT8ARRAY)FieldValue)[2];
            break;
        case 25: //target
            Data->XTRG.value = *(FORMID *)FieldValue;
            return true;
        case 26: //seed
            Data->XSED.Load();
            //Borrowing ArraySize to flag if the new value is an offset
            if(ArraySize)
                {
                Data->XSED->isOffset = true;
                Data->XSED->offset = *(uint8_t *)FieldValue;
                }
            else
                {
                Data->XSED->isOffset = false;
                Data->XSED->seed = *(uint32_t *)FieldValue;
                }
            break;
        case 27: //lod1
            Data->XLOD.Load();
            Data->XLOD->lod1 = *(float *)FieldValue;
            break;
        case 28: //lod2
            Data->XLOD.Load();
            Data->XLOD->lod2 = *(float *)FieldValue;
            break;
        case 29: //lod3
            Data->XLOD.Load();
            Data->XLOD->lod3 = *(float *)FieldValue;
            break;
        case 30: //charge
            Data->XCHG.value = *(float *)FieldValue;
            break;
        case 31: //health
            Data->XHLT.value = *(int32_t *)FieldValue;
            break;
        case 32: //unknownXPCIFormID
            Data->XPCI.Load();
            Data->XPCI->XPCI.value = *(FORMID *)FieldValue;
            return true;
        case 33: //unknownXPCIString
            Data->XPCI.Load();
            Data->XPCI->FULL.Copy((char *)FieldValue);
            break;
        case 34: //levelMod
            Data->XLCM.value = *(int32_t *)FieldValue;
            break;
        case 35: //unknownXRTMFormID
            Data->XRTM.value = *(FORMID *)FieldValue;
            return true;
        case 36: //actionFlags
            SetActionFlagMask(*(uint32_t *)FieldValue);
            break;
        case 37: //count
            Data->XCNT.value = *(int32_t *)FieldValue;
            break;
        case 38: //markerFlags
            SetMapFlagMask(*(uint8_t *)FieldValue);
            break;
        case 39: //markerName
            Data->Marker.Load();
            Data->Marker->FULL.Copy((char *)FieldValue);
            break;
        case 40: //markerType
            SetMarkerType(*(uint8_t *)FieldValue);
            break;
        case 41: //markerUnused
            if(ArraySize != 1)
                break;
            Data->Marker.Load();
            Data->Marker->TNAM.value.unused1 = ((UINT8ARRAY)FieldValue)[0];
            break;
        case 42: //scale
            Data->XSCL.Load();
            Data->XSCL.value = *(float *)FieldValue;
            break;
        case 43: //soulType
            SetSoul(*(uint8_t *)FieldValue);
            break;
        case 44: //posX
            Data->DATA.value.posX = *(float *)FieldValue;
            break;
        case 45: //posY
            Data->DATA.value.posY = *(float *)FieldValue;
            break;
        case 46: //posZ
            Data->DATA.value.posZ = *(float *)FieldValue;
            break;
        case 47: //rotX
            Data->DATA.value.rotX = *(float *)FieldValue;
            break;
        case 48: //rotY
            Data->DATA.value.rotY = *(float *)FieldValue;
            break;
        case 49: //rotZ
            Data->DATA.value.rotZ = *(float *)FieldValue;
            break;
        default:
            break;
        }
    return false;
    }

void REFRRecord::DeleteField(FIELD_IDENTIFIERS)
    {
    REFRXTEL defaultXTEL;
    REFRXLOC defaultXLOC;
    GENXESP defaultXESP;
    GENXLOD defaultXLOD;
    GENTNAM defaultTNAM;
    GENPOSDATA defaultDATA;
    Data.Load();
    switch(FieldID)
        {
        case 1: //flags1
            SetHeaderFlagMask(0);
            return;
        case 3: //flags2
            flagsUnk = 0;
            return;
        case 4: //eid
            Data->EDID.Unload();
            return;
        case 5: //base
            Data->NAME.Unload();
            return;
        case 6: //destination
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destinationFid = defaultXTEL.destinationFid;
            return;
        case 7: //destinationPosX
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.posX = defaultXTEL.destination.posX;
            return;
        case 8: //destinationPosY
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.posY = defaultXTEL.destination.posY;
            return;
        case 9: //destinationPosZ
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.posZ = defaultXTEL.destination.posZ;
            return;
        case 10: //destinationRotX
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.rotX = defaultXTEL.destination.rotX;
            return;
        case 11: //destinationRotY
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.rotY = defaultXTEL.destination.rotY;
            return;
        case 12: //destinationRotZ
            if(Data->XTEL.IsLoaded())
                Data->XTEL->destination.rotZ = defaultXTEL.destination.rotZ;
            return;
        case 13: //lockLevel
            if(Data->XLOC.IsLoaded())
                Data->XLOC->level = defaultXLOC.level;
            return;
        case 14: //unused1
            if(Data->XLOC.IsLoaded())
                {
                Data->XLOC->unused1[0] = defaultXLOC.unused1[0];
                Data->XLOC->unused1[1] = defaultXLOC.unused1[1];
                Data->XLOC->unused1[2] = defaultXLOC.unused1[2];
                }
            return;
        case 15: //lockKey
            if(Data->XLOC.IsLoaded())
                Data->XLOC->key = defaultXLOC.key;
            return;
        case 16: //unused2
            if(Data->XLOC.IsLoaded())
                {
                Data->XLOC->unused2[0] = defaultXLOC.unused2[0];
                Data->XLOC->unused2[1] = defaultXLOC.unused2[1];
                Data->XLOC->unused2[2] = defaultXLOC.unused2[2];
                Data->XLOC->unused2[3] = defaultXLOC.unused2[3];
                }
            return;
        case 17: //lockFlags
            if(Data->XLOC.IsLoaded())
                Data->XLOC->flags = defaultXLOC.flags;
            return;
        case 18: //unused3
            if(Data->XLOC.IsLoaded())
                {
                Data->XLOC->unused3[0] = defaultXLOC.unused3[0];
                Data->XLOC->unused3[1] = defaultXLOC.unused3[1];
                Data->XLOC->unused3[2] = defaultXLOC.unused3[2];
                }
            return;
        case 19: //owner
            if(Data->Ownership.IsLoaded())
                Data->Ownership->XOWN.Unload();
            return;
        case 20: //rank
            if(Data->Ownership.IsLoaded())
                Data->Ownership->XRNK.Unload();
            return;
        case 21: //globalVariable
            if(Data->Ownership.IsLoaded())
                Data->Ownership->XGLB.Unload();
            return;
        case 22: //parent
            if(Data->XESP.IsLoaded())
                Data->XESP->parent = defaultXESP.parent;
            return;
        case 23: //parentFlags
            if(Data->XESP.IsLoaded())
                Data->XESP->flags = defaultXESP.flags;
            return;
        case 24: //unused4
            if(Data->XESP.IsLoaded())
                {
                Data->XESP->unused1[0] = defaultXESP.unused1[0];
                Data->XESP->unused1[1] = defaultXESP.unused1[1];
                Data->XESP->unused1[2] = defaultXESP.unused1[2];
                }
            return;
        case 25: //target
            Data->XTRG.Unload();
            return;
        case 26: //seed
            Data->XSED.Unload();
            return;
        case 27: //lod1
            if(Data->XLOD.IsLoaded())
                Data->XLOD->lod1 = defaultXLOD.lod1;
            return;
        case 28: //lod2
            if(Data->XLOD.IsLoaded())
                Data->XLOD->lod2 = defaultXLOD.lod2;
            return;
        case 29: //lod3
            if(Data->XLOD.IsLoaded())
                Data->XLOD->lod3 = defaultXLOD.lod3;
            return;
        case 30: //charge
            Data->XCHG.Unload();
            return;
        case 31: //health
            Data->XHLT.Unload();
            return;
        case 32: //unknownXPCIFormID
            if(Data->XPCI.IsLoaded())
                Data->XPCI->XPCI.Unload();
            return;
        case 33: //unknownXPCIString
            if(Data->XPCI.IsLoaded())
                Data->XPCI->FULL.Unload();
            return;
        case 34: //levelMod
            Data->XLCM.Unload();
            return;
        case 35: //unknownXRTMFormID
            Data->XRTM.Unload();
            return;
        case 36: //actionFlags
            Data->XACT.Unload();
            return;
        case 37: //count
            Data->XCNT.Unload();
            return;
        case 38: //markerFlags
            if(Data->Marker.IsLoaded())
                Data->Marker->FNAM.Unload();
            return;
        case 39: //markerName
            if(Data->Marker.IsLoaded())
                Data->Marker->FULL.Unload();
            return;
        case 40: //markerType
            if(Data->Marker.IsLoaded())
                Data->Marker->TNAM.value.markerType = defaultTNAM.markerType;
            return;
        case 41: //markerUnused
            if(Data->Marker.IsLoaded())
                Data->Marker->TNAM.value.unused1 = defaultTNAM.unused1;
            return;
        case 42: //scale
            Data->XSCL.Unload();
            return;
        case 43: //soulType
            Data->XSOL.Unload();
            return;
        case 44: //posX
            Data->DATA.value.posX = defaultDATA.posX;
            return;
        case 45: //posY
            Data->DATA.value.posY = defaultDATA.posY;
            return;
        case 46: //posZ
            Data->DATA.value.posZ = defaultDATA.posZ;
            return;
        case 47: //rotX
            Data->DATA.value.rotX = defaultDATA.rotX;
            return;
        case 48: //rotY
            Data->DATA.value.rotY = defaultDATA.rotY;
            return;
        case 49: //rotZ
            Data->DATA.value.rotZ = defaultDATA.rotZ;
            return;
        default:
            return;
        }
    return;
    }
}