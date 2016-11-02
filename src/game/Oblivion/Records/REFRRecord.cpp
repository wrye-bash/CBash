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
#include "REFRRecord.h"
#include "CELLRecord.h"

namespace Ob
{
REFRRecord::REFRXTEL::REFRXTEL():
    destinationFid(0)
    {
    //
    }

REFRRecord::REFRXTEL::~REFRXTEL()
    {
    //
    }

bool REFRRecord::REFRXTEL::operator ==(const REFRXTEL &other) const
    {
    return (destinationFid == other.destinationFid &&
            destination == other.destination);
    }

bool REFRRecord::REFRXTEL::operator !=(const REFRXTEL &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRXLOC::REFRXLOC():
    level(0xFF), //Level actually defaults to 0, but this makes it write out if set to 0
    key(0),
    flags(0)
    {
    memset(&unused1[0], 0x00, sizeof(unused1));
    memset(&unused2[0], 0x00, sizeof(unused2));
    memset(&unused3[0], 0x00, sizeof(unused3));
    }

REFRRecord::REFRXLOC::~REFRXLOC()
    {
    //
    }

bool REFRRecord::REFRXLOC::operator ==(const REFRXLOC &other) const
    {
    return (level == other.level &&
            key == other.key &&
            flags == other.flags);
    }

bool REFRRecord::REFRXLOC::operator !=(const REFRXLOC &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRXSED::REFRXSED():
    seed(0),
    isOffset(true)
    {
    //
    }

REFRRecord::REFRXSED::~REFRXSED()
    {
    //
    }

void REFRRecord::REFRXSED::Write(FileWriter &writer)
    {
    if(isOffset)
        writer.record_write_subrecord(REV32(XSED), &offset, 1);
    else
        writer.record_write_subrecord(REV32(XSED), &seed, 4);
    }

bool REFRRecord::REFRXSED::operator ==(const REFRXSED &other) const
    {
    if(!isOffset)
        {
        if(!other.isOffset)
            return (seed == other.seed);
        }
    else if(other.isOffset)
        return offset == other.offset;
    return false;
    }

bool REFRRecord::REFRXSED::operator !=(const REFRXSED &other) const
    {
    return !(*this == other);
    }

void REFRRecord::REFRMAPMARKER::Write(FileWriter &writer)
    {
    WRITEEMPTY(XMRK);
    WRITE(FNAM);
    WRITE(FULL);
    WRITE(TNAM);
    }

bool REFRRecord::REFRMAPMARKER::operator ==(const REFRMAPMARKER &other) const
    {
    return (FNAM == other.FNAM &&
            FULL.equals(other.FULL) &&
            TNAM == other.TNAM);
    }

bool REFRRecord::REFRMAPMARKER::operator !=(const REFRMAPMARKER &other) const
    {
    return !(*this == other);
    }

bool REFRRecord::REFRData::IsOpenByDefault()
    {
    return (XACT.value & fOpenByDefault) != 0;
    }

void REFRRecord::REFRData::Write(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(NAME);
    WRITE(XTEL);
    WRITE(XLOC);
    Ownership.Write(writer);
    WRITE(XESP);
    WRITE(XTRG);
    XSED.Write(writer);
    WRITE(XLOD);
    WRITE(XCHG);
    WRITE(XHLT);
    XPCI.Write(writer);
    WRITE(XLCM);
    WRITE(XRTM);
    WRITE(XACT);
    WRITE(XCNT);
    Marker.Write(writer);
    if(IsOpenByDefault())
        WRITEEMPTY(ONAM);
    WRITE(XSCL);
    WRITE(XSOL);
    WRITE(DATA);
    }

bool REFRRecord::REFRData::operator ==(const REFRData &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            NAME == other.NAME &&
            XTEL == other.XTEL &&
            XLOC == other.XLOC &&
            Ownership == other.Ownership &&
            XESP == other.XESP &&
            XTRG == other.XTRG &&
            XSED == other.XSED &&
            XLOD == other.XLOD &&
            XCHG == other.XCHG &&
            XHLT == other.XHLT &&
            XPCI == other.XPCI &&
            XLCM == other.XLCM &&
            XRTM == other.XRTM &&
            XACT == other.XACT &&
            XCNT == other.XCNT &&
            Marker == other.Marker &&
            XSCL == other.XSCL &&
            XSOL == other.XSOL &&
            DATA == other.DATA);
    }

bool REFRRecord::REFRData::operator !=(const REFRData &other) const
    {
    return !(*this == other);
    }

REFRRecord::REFRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

REFRRecord::REFRRecord(REFRRecord *srcRecord):
    Record()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    if(srcRecord->Data.IsLoaded())
        {
        Data.Load();
        Data->EDID = srcRecord->Data->EDID;
        Data->NAME = srcRecord->Data->NAME;
        Data->XTEL = srcRecord->Data->XTEL;
        Data->XLOC = srcRecord->Data->XLOC;
        Data->Ownership = srcRecord->Data->Ownership;
        Data->XESP = srcRecord->Data->XESP;
        Data->XTRG = srcRecord->Data->XTRG;
        Data->XSED = srcRecord->Data->XSED;
        Data->XLOD = srcRecord->Data->XLOD;
        Data->XCHG = srcRecord->Data->XCHG;
        Data->XHLT = srcRecord->Data->XHLT;
        Data->XPCI = srcRecord->Data->XPCI;
        Data->XLCM = srcRecord->Data->XLCM;
        Data->XRTM = srcRecord->Data->XRTM;
        Data->XACT = srcRecord->Data->XACT;
        Data->XCNT = srcRecord->Data->XCNT;
        Data->Marker = srcRecord->Data->Marker;
        if(srcRecord->IsOpenByDefault())//bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
            IsOpenByDefault(true);
        Data->XSCL = srcRecord->Data->XSCL;
        Data->XSOL = srcRecord->Data->XSOL;
        Data->DATA = srcRecord->Data->DATA;
        }
    }

REFRRecord::~REFRRecord()
    {
    //Parent is a shared pointer that's deleted when the CELL group is deleted
    }

bool REFRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(Data.IsLoaded())
        {
        op.Accept(Data->NAME.value);
        if(Data->XTEL.IsLoaded())
            op.Accept(Data->XTEL->destinationFid);
        if(Data->XLOC.IsLoaded())
            op.Accept(Data->XLOC->key);
        if(Data->Ownership.IsLoaded())
            {
            if(Data->Ownership->XOWN.IsLoaded())
                op.Accept(Data->Ownership->XOWN.value);
            if(Data->Ownership->XGLB.IsLoaded())
                op.Accept(Data->Ownership->XGLB.value);
            }
        if(Data->XESP.IsLoaded())
            op.Accept(Data->XESP->parent);
        if(Data->XTRG.IsLoaded())
            op.Accept(Data->XTRG.value);
        if(Data->XPCI.IsLoaded() && Data->XPCI->XPCI.IsLoaded())
            op.Accept(Data->XPCI->XPCI.value);
        if(Data->XRTM.IsLoaded())
            op.Accept(Data->XRTM.value);
        }

    return op.Stop();
    }

bool REFRRecord::IsOppositeParent()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->XESP.IsLoaded()) return false;
    return (Data->XESP->flags & fIsOppositeParent) != 0;
    }

void REFRRecord::IsOppositeParent(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->XESP.IsLoaded()) return;
    Data->XESP->flags = value ? (Data->XESP->flags | fIsOppositeParent) : (Data->XESP->flags & ~fIsOppositeParent);
    }

bool REFRRecord::IsParentFlagMask(uint8_t Mask, bool Exact)
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->XESP.IsLoaded()) return false;
    return Exact ? ((Data->XESP->flags & Mask) == Mask) : ((Data->XESP->flags & Mask) != 0);
    }

void REFRRecord::SetParentFlagMask(uint8_t Mask)
    {
    Data.Load();
    Data->XESP.Load();
    Data->XESP->flags = Mask;
    }

bool REFRRecord::IsVisible()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->FNAM.value & fVisible) != 0;
    }

void REFRRecord::IsVisible(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    Data->Marker->FNAM.value = value ? (Data->Marker->FNAM.value | fVisible) : (Data->Marker->FNAM.value & ~fVisible);
    }

bool REFRRecord::IsCanTravelTo()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->FNAM.value & fCanTravelTo) != 0;
    }

void REFRRecord::IsCanTravelTo(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    Data->Marker->FNAM.value = value ? (Data->Marker->FNAM.value | fCanTravelTo) : (Data->Marker->FNAM.value & ~fCanTravelTo);
    }

bool REFRRecord::IsMapFlagMask(uint8_t Mask, bool Exact)
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return Exact ? ((Data->Marker->FNAM.value & Mask) == Mask) : ((Data->Marker->FNAM.value & Mask) != 0);
    }

void REFRRecord::SetMapFlagMask(uint8_t Mask)
    {
    Data.Load();
    Data->Marker.Load();
    Data->Marker->FNAM.value = Mask;
    }

bool REFRRecord::IsUseDefault()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XACT.value & fUseDefault) != 0;
    }

void REFRRecord::IsUseDefault(bool value)
    {
    if(!Data.IsLoaded()) return;
    Data->XACT.value = value ? (Data->XACT.value | fUseDefault) : (Data->XACT.value & ~fUseDefault);
    }

bool REFRRecord::IsActivate()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XACT.value & fActivate) != 0;
    }

void REFRRecord::IsActivate(bool value)
    {
    if(!Data.IsLoaded()) return;
    Data->XACT.value = value ? (Data->XACT.value | fActivate) : (Data->XACT.value & ~fActivate);
    }

bool REFRRecord::IsOpen()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XACT.value & fOpen) != 0;
    }

void REFRRecord::IsOpen(bool value)
    {
    if(!Data.IsLoaded()) return;
    Data->XACT.value = value ? (Data->XACT.value | fOpen) : (Data->XACT.value & ~fOpen);
    }

bool REFRRecord::IsOpenByDefault()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XACT.value & fOpenByDefault) != 0;
    }

void REFRRecord::IsOpenByDefault(bool value)
    {
    if(!Data.IsLoaded()) return;
    Data->XACT.value = value ? (Data->XACT.value | fOpenByDefault) : (Data->XACT.value & ~fOpenByDefault);
    }

bool REFRRecord::IsActionFlagMask(uint32_t Mask, bool Exact)
    {
    if(!Data.IsLoaded()) return false;
    return Exact ? ((Data->XACT.value & Mask) == Mask) : ((Data->XACT.value & Mask) != 0);
    }

void REFRRecord::SetActionFlagMask(uint32_t Mask)
    {
    Data.Load();
    Data->XACT.value = Mask;
    }

bool REFRRecord::IsLeveledLock()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->XLOC.IsLoaded()) return false;
    return (Data->XLOC->flags & fLeveledLock) != 0;
    }

void REFRRecord::IsLeveledLock(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->XLOC.IsLoaded()) return;
    Data->XLOC->flags = value ? (Data->XLOC->flags | fLeveledLock) : (Data->XLOC->flags & ~fLeveledLock);
    }

bool REFRRecord::IsLockFlagMask(uint8_t Mask, bool Exact)
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->XLOC.IsLoaded()) return false;
    return Exact ? ((Data->XLOC->flags & Mask) == Mask) : ((Data->XLOC->flags & Mask) != 0);
    }

void REFRRecord::SetLockFlagMask(uint8_t Mask)
    {
    Data.Load();
    Data->XLOC.Load();
    Data->XLOC->flags = Mask;
    }

bool REFRRecord::IsNoMarker()
    {
    if(!Data.IsLoaded()) return true;
    if(!Data->Marker.IsLoaded()) return true;
    return (Data->Marker->TNAM.value.markerType == eMarkerNone);
    }

void REFRRecord::IsNoMarker(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    else if(IsNoMarker())
        Data->Marker->TNAM.value.markerType = eCamp;
    }

bool REFRRecord::IsCamp()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eCamp);
    }

void REFRRecord::IsCamp(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eCamp;
    else if(IsCamp())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsCave()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eCave);
    }

void REFRRecord::IsCave(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eCave;
    else if(IsCave())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsCity()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eCity);
    }

void REFRRecord::IsCity(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eCity;
    else if(IsCity())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsElvenRuin()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eElvenRuin);
    }

void REFRRecord::IsElvenRuin(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eElvenRuin;
    else if(IsElvenRuin())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsFortRuin()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eFortRuin);
    }

void REFRRecord::IsFortRuin(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eFortRuin;
    else if(IsFortRuin())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsMine()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eMine);
    }

void REFRRecord::IsMine(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eMine;
    else if(IsMine())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsLandmark()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eLandmark);
    }

void REFRRecord::IsLandmark(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eLandmark;
    else if(IsLandmark())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsTavern()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eTavern);
    }

void REFRRecord::IsTavern(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eTavern;
    else if(IsTavern())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsSettlement()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eSettlement);
    }

void REFRRecord::IsSettlement(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eSettlement;
    else if(IsSettlement())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsDaedricShrine()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eDaedricShrine);
    }

void REFRRecord::IsDaedricShrine(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eDaedricShrine;
    else if(IsDaedricShrine())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsOblivionGate()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eOblivionGate);
    }

void REFRRecord::IsOblivionGate(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eOblivionGate;
    else if(IsOblivionGate())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsUnknownDoorIcon()
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == eUnknownDoorIcon);
    }

void REFRRecord::IsUnknownDoorIcon(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(!Data->Marker.IsLoaded()) return;
    if(value)
        Data->Marker->TNAM.value.markerType = eUnknownDoorIcon;
    else if(IsUnknownDoorIcon())
        Data->Marker->TNAM.value.markerType = eMarkerNone;
    }

bool REFRRecord::IsMarkerType(uint8_t Type)
    {
    if(!Data.IsLoaded()) return false;
    if(!Data->Marker.IsLoaded()) return false;
    return (Data->Marker->TNAM.value.markerType == Type);
    }

void REFRRecord::SetMarkerType(uint8_t Type)
    {
    Data.Load();
    Data->Marker.Load();
    Data->Marker->TNAM.value.markerType = Type;
    }

bool REFRRecord::IsNoSoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == eNone);
    }

void REFRRecord::IsNoSoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = eNone;
    else if(IsNoSoul())
        Data->XSOL.value = ePetty;
    }

bool REFRRecord::IsPettySoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == ePetty);
    }

void REFRRecord::IsPettySoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = ePetty;
    else if(IsPettySoul())
        Data->XSOL.value = eNone;
    }

bool REFRRecord::IsLesserSoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == eLesser);
    }

void REFRRecord::IsLesserSoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = eLesser;
    else if(IsLesserSoul())
        Data->XSOL.value = eNone;
    }

bool REFRRecord::IsCommonSoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == eCommon);
    }

void REFRRecord::IsCommonSoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = eCommon;
    else if(IsCommonSoul())
        Data->XSOL.value = eNone;
    }

bool REFRRecord::IsGreaterSoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == eGreater);
    }

void REFRRecord::IsGreaterSoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = eGreater;
    else if(IsGreaterSoul())
        Data->XSOL.value = eNone;
    }

bool REFRRecord::IsGrandSoul()
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == eGrand);
    }

void REFRRecord::IsGrandSoul(bool value)
    {
    if(!Data.IsLoaded()) return;
    if(value)
        Data->XSOL.value = eGrand;
    else if(IsGrandSoul())
        Data->XSOL.value = eNone;
    }

bool REFRRecord::IsSoul(uint8_t Type)
    {
    if(!Data.IsLoaded()) return false;
    return (Data->XSOL.value == Type);
    }

void REFRRecord::SetSoul(uint8_t Type)
    {
    Data.Load();
    Data->XSOL.value = Type;
    }

uint32_t REFRRecord::GetType()
    {
    return REV32(REFR);
    }

char * REFRRecord::GetStrType()
    {
    return "REFR";
    }

int32_t REFRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    uint32_t lastChunk = 0;
    Data.Load();
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                Data->EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAME):
                Data->NAME.Read(buffer, subSize);
                break;
            case REV32(XTEL):
                Data->XTEL.Read(buffer, subSize);
                break;
            case REV32(XLOC):
                switch(subSize)
                    {
                    case 12: //unused2 is absent, so shift the values read into it
                        Data->XLOC.Read(buffer, subSize);
                        Data->XLOC->flags = Data->XLOC->unused2[0];
                        Data->XLOC->unused3[0] = Data->XLOC->unused2[1];
                        Data->XLOC->unused3[1] = Data->XLOC->unused2[2];
                        Data->XLOC->unused3[2] = Data->XLOC->unused2[3];
                        memset(&Data->XLOC->unused2[0], 0x00, sizeof(Data->XLOC->unused2));
                        break;
                    default:
                        Data->XLOC.Read(buffer, subSize);
                        break;
                    }
                break;
            case REV32(XOWN):
                Data->Ownership.Load();
                Data->Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Data->Ownership.Load();
                Data->Ownership->XRNK.Read(buffer, subSize);
                break;
            case REV32(XGLB):
                Data->Ownership.Load();
                Data->Ownership->XGLB.Read(buffer, subSize);
                break;
            case REV32(XESP):
                Data->XESP.Read(buffer, subSize);
                break;
            case REV32(XTRG):
                Data->XTRG.Read(buffer, subSize);
                break;
            case REV32(XSED):
                switch(subSize)
                    {
                    case 1:
                        //if it's a single byte then it's an offset into the list of seed values in the TREE record
                        Data->XSED.Load();
                        Data->XSED->isOffset = true;
                        //XSED.size = 1;
                        Data->XSED->offset = *(uint8_t *)buffer;
                        buffer++;
                        break;
                    case 4:
                        //if it's 4 byte it's the seed value directly
                        Data->XSED.Load();
                        Data->XSED->isOffset = false;
                        //XSED.size = 4;
                        Data->XSED->seed = *(uint32_t *)buffer;
                        buffer += 4;
                        break;
                    default:
                        printer("  REFR: %08X - Unknown XSED size = %u\n", formID, subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(XLOD):
                Data->XLOD.Read(buffer, subSize);
                break;
            case REV32(XCHG):
                Data->XCHG.Read(buffer, subSize);
                break;
            case REV32(XHLT):
                Data->XHLT.Read(buffer, subSize);
                break;
            case REV32(XPCI):
                Data->XPCI.Load();
                Data->XPCI->XPCI.Read(buffer, subSize);
                lastChunk = REV32(XPCI);
                break;
            case REV32(FULL):
                switch(lastChunk)
                    {
                    case REV32(XPCI):
                        Data->XPCI.Load();
                        Data->XPCI->FULL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    case REV32(XMRK):
                        Data->Marker->FULL.Read(buffer, subSize, CompressedOnDisk);
                        break;
                    default:
                        printer("  REFR: %08X - Unexpected FULL chunk\n", formID);
                        printer("  Size = %i\n", subSize);
                        printer("  CurPos = %04x\n\n", buffer - 6);
                        buffer += subSize;
                        break;
                    }
                break;
            case REV32(XLCM):
                Data->XLCM.Read(buffer, subSize);
                break;
            case REV32(XRTM):
                Data->XRTM.Read(buffer, subSize);
                break;
            case REV32(XACT):
                Data->XACT.Read(buffer, subSize);
                break;
            case REV32(XCNT):
                Data->XCNT.Read(buffer, subSize);
                break;
            case REV32(XMRK):
                Data->Marker.Load();
                buffer += subSize;
                lastChunk = REV32(XMRK);
                break;
            case REV32(FNAM):
                Data->Marker.Load();
                Data->Marker->FNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                Data->Marker.Load();
                Data->Marker->TNAM.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                IsOpenByDefault(true);
                buffer += subSize;
                break;
            case REV32(XSCL):
                Data->XSCL.Read(buffer, subSize);
                break;
            case REV32(XSOL):
                Data->XSOL.Read(buffer, subSize);
                break;
            case REV32(DATA):
                Data->DATA.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  REFR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t REFRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    Data.Unload();
    //EDID.Unload();
    //NAME.Unload();
    //XTEL.Unload();
    //XLOC.Unload();
    //Ownership.Unload();
    //Data->XESP.Unload();
    //XTRG.Unload();
    //XSED.Unload();
    //XLOD.Unload();
    //XCHG.Unload();
    //XHLT.Unload();
    //XPCI.Unload();
    //XLCM.Unload();
    //XRTM.Unload();
    //XACT.Unload();
    //XCNT.Unload();
    //Marker.Unload();
    //XSCL.Unload();
    //XSOL.Unload();
    //DATA.Unload();
    return 1;
    }

int32_t REFRRecord::WriteRecord(FileWriter &writer)
    {
    if(!Data.IsLoaded())
        return 0;

    Data.Write(writer);
    return -1;
    }

bool REFRRecord::operator ==(const REFRRecord &other) const
    {
    return (Data == other.Data);
    }

bool REFRRecord::operator !=(const REFRRecord &other) const
    {
    return !(*this == other);
    }

bool REFRRecord::equals(Record *other)
    {
    return *this == *(REFRRecord *)other;
    }

bool REFRRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    CELLRecord *parent_cell = (CELLRecord *)GetParentRecord(), *master_cell = (CELLRecord *)master->GetParentRecord();
    Record *parent_wrld = parent_cell->GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the parent cell is attached at the same spot
    if(parent_cell->formID != master_cell->formID)
        return false;
    if(parent_wrld != NULL)
        {
        if(master_wrld != NULL)
            {
            if(parent_wrld->formID != master_wrld->formID)
                return false;
            }
        else
            return false;
        }
    else if(master_wrld != NULL)
        return false;
    if(parent_wrld)
        {
        read_self.Accept((Record *&)parent_cell);
        read_master.Accept((Record *&)master_cell);
        parent_cell->XCLC.Load();
        master_cell->XCLC.Load();
        if(parent_cell->XCLC->posX != master_cell->XCLC->posX)
            return false;
        if(parent_cell->XCLC->posY != master_cell->XCLC->posY)
            return false;
        }
    return true;
    }
}