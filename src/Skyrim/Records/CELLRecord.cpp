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
#include "..\..\Common.h"
#include "CELLRecord.h"

namespace Sk
{
CELLRecord::CELLXCLC::CELLXCLC():
    posX(0),
    posY(0),
    flags(0)
    {
    //
    }

CELLRecord::CELLXCLC::~CELLXCLC()
    {
    //
    }

bool CELLRecord::CELLXCLC::operator ==(const CELLXCLC &other) const
    {
    return (posX == other.posX &&
            posY == other.posY &&
            flags == other.flags);
    }

bool CELLRecord::CELLXCLC::operator !=(const CELLXCLC &other) const
    {
    return !(*this == other);
    }

CELLRecord::CELLRecord(unsigned char *_recData):
    TES5Record(_recData),
    LAND(NULL)
    {
    //
    }

CELLRecord::CELLRecord(CELLRecord *srcRecord):
    TES5Record((TES5Record *)srcRecord),
    LAND(NULL)
    {
    if(srcRecord == NULL || !srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    XCLC = srcRecord->XCLC;
/*  XCLL = srcRecord->XCLL;*/
    IMPS = srcRecord->IMPS;
    IMPF = srcRecord->IMPF;
    LTMP = srcRecord->LTMP;
    LNAM = srcRecord->LNAM;
    XCLW = srcRecord->XCLW;
    XNAM = srcRecord->XNAM;
    XCLR = srcRecord->XCLR;
    XCIM = srcRecord->XCIM;
    XCET = srcRecord->XCET;
    XEZN = srcRecord->XEZN;
    XCCM = srcRecord->XCCM;
    XCWT = srcRecord->XCWT;
/*  Ownership = srcRecord->Ownership;*/
    XCAS = srcRecord->XCAS;
    XCMT = srcRecord->XCMT;
    XCMO = srcRecord->XCMO;
    TVDT = srcRecord->TVDT;
    MHDT = srcRecord->MHDT;
    XLCN = srcRecord->XLCN;
    XWCN = srcRecord->XWCN;
    XWCU = srcRecord->XWCU;
    }

CELLRecord::~CELLRecord()
    {
    //
    //ACHRs are owned at the mod level, so must be destroyed there
    //ACREs are owned at the mod level, so must be destroyed there
    //REFRs are owned at the mod level, so must be destroyed there
    //PGRD is owned at the mod level, so must be destroyed there
    //LAND is owned at the mod level, so must be destroyed there
    //Parent is a shared pointer that's deleted when the WRLD group is deleted

    /*
    for(uint32_t x = 0; x < ACHR.size(); ++x)
        delete ACHR[x];
    for(uint32_t x = 0; x < ACRE.size(); ++x)
        delete ACRE[x];
    for(uint32_t x = 0; x < REFR.size(); ++x)
        delete REFR[x];
    for(uint32_t x = 0; x < PGRE.size(); ++x)
        delete PGRE[x];
    for(uint32_t x = 0; x < PMIS.size(); ++x)
        delete PMIS[x];
    for(uint32_t x = 0; x < PBEA.size(); ++x)
        delete PBEA[x];
    for(uint32_t x = 0; x < PFLA.size(); ++x)
        delete PFLA[x];
    for(uint32_t x = 0; x < PCBE.size(); ++x)
        delete PCBE[x];
    for(uint32_t x = 0; x < NAVM.size(); ++x)
        delete NAVM[x];

    delete LAND;
    */
    }

bool CELLRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    for(uint32_t ListIndex = 0; ListIndex < IMPS.value.size(); ListIndex++)
        {
        op.Accept(IMPS.value[ListIndex]->oldImpact);
        op.Accept(IMPS.value[ListIndex]->newImpact);
        }
    op.Accept(LTMP.value);
    for(uint32_t x = 0; x < XCLR.value.size(); x++)
        op.Accept(XCLR.value[x]);
    if(XCIM.IsLoaded())
        op.Accept(XCIM.value);
    if(XEZN.IsLoaded())
        op.Accept(XEZN.value);
    if(XCCM.IsLoaded())
        op.Accept(XCCM.value);
    if(XCWT.IsLoaded())
        op.Accept(XCWT.value);
/*  if(Ownership.IsLoaded())
        op.Accept(Ownership->XOWN.value);*/
    if(XCAS.IsLoaded())
        op.Accept(XCAS.value);
    if(XCMO.IsLoaded())
        op.Accept(XCMO.value);
    return op.Stop();
    }

bool CELLRecord::IsInterior()
    {
    return (DATA.value & fIsInterior) != 0;
    }

void CELLRecord::IsInterior(bool value)
    {
    SETBIT(DATA.value, fIsInterior, value);
    }

bool CELLRecord::IsHasWater()
    {
    return (DATA.value & fHasWater) != 0;
    }

void CELLRecord::IsHasWater(bool value)
    {
    SETBIT(DATA.value, fHasWater, value);
    }

bool CELLRecord::IsInvertFastTravel()
    {
    return (DATA.value & fInvertFastTravel) != 0;
    }

void CELLRecord::IsInvertFastTravel(bool value)
    {
    SETBIT(DATA.value, fInvertFastTravel, value);
    }

bool CELLRecord::IsForceHideLand()
    {
    if(IsInterior()) return false;
    return (DATA.value & fForceHideLand) != 0;
    }

void CELLRecord::IsForceHideLand(bool value)
    {
    if(IsInterior()) return;
    SETBIT(DATA.value, fForceHideLand, value);
    }

bool CELLRecord::IsOblivionInterior()
    {
    if(!IsInterior()) return false;
    return (DATA.value & fIsOblivionInterior) != 0;
    }

void CELLRecord::IsOblivionInterior(bool value)
    {
    if(!IsInterior()) return;
    SETBIT(DATA.value, fIsOblivionInterior, value);
    }

bool CELLRecord::IsPublicPlace()
    {
    return (DATA.value & fPublicPlace) != 0;
    }

void CELLRecord::IsPublicPlace(bool value)
    {
    SETBIT(DATA.value, fPublicPlace, value);
    }

bool CELLRecord::IsHandChanged()
    {
    return (DATA.value & fHandChanged) != 0;
    }

void CELLRecord::IsHandChanged(bool value)
    {
    SETBIT(DATA.value, fHandChanged, value);
    }

bool CELLRecord::IsBehaveLikeExterior()
    {
    return (DATA.value & fBehaveLikeExterior) != 0;
    }

void CELLRecord::IsBehaveLikeExterior(bool value)
    {
    SETBIT(DATA.value, fBehaveLikeExterior, value);
    }

bool CELLRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value & Mask) == Mask) : ((DATA.value & Mask) != 0);
    }

void CELLRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value = Mask;
    }

bool CELLRecord::IsQuad1ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad1ForceHidden) != 0;
    }

void CELLRecord::IsQuad1ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad1ForceHidden) : (XCLC->flags & ~fIsQuad1ForceHidden);
    }

bool CELLRecord::IsQuad2ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad2ForceHidden) != 0;
    }

void CELLRecord::IsQuad2ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad2ForceHidden) : (XCLC->flags & ~fIsQuad2ForceHidden);
    }

bool CELLRecord::IsQuad3ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad3ForceHidden) != 0;
    }

void CELLRecord::IsQuad3ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad3ForceHidden) : (XCLC->flags & ~fIsQuad3ForceHidden);
    }

bool CELLRecord::IsQuad4ForceHidden()
    {
    if(!XCLC.IsLoaded()) return false;
    return (XCLC->flags & fIsQuad4ForceHidden) != 0;
    }

void CELLRecord::IsQuad4ForceHidden(bool value)
    {
    if(!XCLC.IsLoaded()) return;
    XCLC->flags = value ? (XCLC->flags | fIsQuad4ForceHidden) : (XCLC->flags & ~fIsQuad4ForceHidden);
    }

bool CELLRecord::IsQuadFlagMask(uint32_t Mask, bool Exact)
    {
    if(!XCLC.IsLoaded()) return false;
    return Exact ? ((XCLC->flags & Mask) == Mask) : ((XCLC->flags & Mask) != 0);
    }

void CELLRecord::SetQuadFlagMask(uint32_t Mask)
    {
    XCLC.Load();
    XCLC->flags = Mask;
    }

bool CELLRecord::IsLightAmbientInherited()
    {
    return (LNAM.value & fIsAmbientInherited) != 0;
    }

void CELLRecord::IsLightAmbientInherited(bool value)
    {
    SETBIT(LNAM.value, fIsAmbientInherited, value);
    }

bool CELLRecord::IsLightDirectionalColorInherited()
    {
    return (LNAM.value & fIsDirectionalColorInherited) != 0;
    }

void CELLRecord::IsLightDirectionalColorInherited(bool value)
    {
    SETBIT(LNAM.value, fIsDirectionalColorInherited, value);
    }

bool CELLRecord::IsLightFogColorInherited()
    {
    return (LNAM.value & fIsFogColorInherited) != 0;
    }

void CELLRecord::IsLightFogColorInherited(bool value)
    {
    SETBIT(LNAM.value, fIsFogColorInherited, value);
    }

bool CELLRecord::IsLightFogNearInherited()
    {
    return (LNAM.value & fIsFogNearInherited) != 0;
    }

void CELLRecord::IsLightFogNearInherited(bool value)
    {
    SETBIT(LNAM.value, fIsFogNearInherited, value);
    }

bool CELLRecord::IsLightFogFarInherited()
    {
    return (LNAM.value & fIsFogFarInherited) != 0;
    }

void CELLRecord::IsLightFogFarInherited(bool value)
    {
    SETBIT(LNAM.value, fIsFogFarInherited, value);
    }

bool CELLRecord::IsLightDirectionalRotationInherited()
    {
    return (LNAM.value & fIsDirectionalRotationInherited) != 0;
    }

void CELLRecord::IsLightDirectionalRotationInherited(bool value)
    {
    SETBIT(LNAM.value, fIsDirectionalRotationInherited, value);
    }

bool CELLRecord::IsLightDirectionalFadeInherited()
    {
    return (LNAM.value & fIsDirectionalFadeInherited) != 0;
    }

void CELLRecord::IsLightDirectionalFadeInherited(bool value)
    {
    SETBIT(LNAM.value, fIsDirectionalFadeInherited, value);
    }

bool CELLRecord::IsLightFogClipInherited()
    {
    return (LNAM.value & fIsFogClipInherited) != 0;
    }

void CELLRecord::IsLightFogClipInherited(bool value)
    {
    SETBIT(LNAM.value, fIsFogClipInherited, value);
    }

bool CELLRecord::IsLightFogPowerInherited()
    {
    return (LNAM.value & fIsFogPowerInherited) != 0;
    }

void CELLRecord::IsLightFogPowerInherited(bool value)
    {
    SETBIT(LNAM.value, fIsFogPowerInherited, value);
    }

bool CELLRecord::IsLightFlagMask(uint32_t Mask, bool Exact)
    {
    return Exact ? ((LNAM.value & Mask) == Mask) : ((LNAM.value & Mask) != 0);
    }

void CELLRecord::SetLightFlagMask(uint32_t Mask)
    {
    LNAM.value = Mask;
    }

uint32_t CELLRecord::GetType()
    {
    return REV32(CELL);
    }

char * CELLRecord::GetStrType()
    {
    return "CELL";
    }

int32_t CELLRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
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
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(XCLC):
                XCLC.Read(buffer, subSize);
                break;
/*          case REV32(XCLL):
                XCLL.Read(buffer, subSize);
                break;*/
            case REV32(IMPS):
                IMPS.Read(buffer, subSize);
                break;
            case REV32(IMPF):
                IMPF.Read(buffer, subSize);
                break;
            case REV32(LTMP):
                LTMP.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(XCLW):
                XCLW.Read(buffer, subSize);
                break;
            case REV32(XNAM):
                XNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XCLR):
                XCLR.Read(buffer, subSize);
                break;
            case REV32(XCIM):
                XCIM.Read(buffer, subSize);
                break;
            case REV32(XCET):
                XCET.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XEZN):
                XEZN.Read(buffer, subSize);
                break;
            case REV32(XCCM):
                XCCM.Read(buffer, subSize);
                break;
            case REV32(XCWT):
                XCWT.Read(buffer, subSize);
                break;
/*          case REV32(XOWN):
                Ownership.Load();
                Ownership->XOWN.Read(buffer, subSize);
                break;
            case REV32(XRNK):
                Ownership.Load();
                Ownership->XRNK.Read(buffer, subSize);
                break;*/
            case REV32(XCAS):
                XCAS.Read(buffer, subSize);
                break;
            case REV32(XCMT):
                XCMT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XCMO):
                XCMO.Read(buffer, subSize);
                break;
            /* Skyrim --------------------------------------- */
            case REV32(TVDT): // 54445654 bytes
                TVDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MHDT): // 1028 bytes (seems contant size)
                MHDT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XLCN): // 4 bytes
                XLCN.Read(buffer, subSize);
                break;
            case REV32(XWCN): // 4 bytes
                XWCN.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(XWCU): // 64 bytes
                XWCU.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  CELL: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t CELLRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    XCLC.Unload();
/*  XCLL.Unload();*/
    IMPS.Unload();
    IMPF.Unload();
    LTMP.Unload();
    LNAM.Unload();
    XCLW.Unload();
    XNAM.Unload();
    XCLR.Unload();
    XCIM.Unload();
    XCET.Unload();
    XEZN.Unload();
    XCCM.Unload();
    XCWT.Unload();
/*  Ownership.Unload();*/
    XCAS.Unload();
    XCMT.Unload();
    XCMO.Unload();
    TVDT.Unload();
    MHDT.Unload();
    XLCN.Unload();
    XWCN.Unload();
    XWCU.Unload();
    return 1;
    }

int32_t CELLRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    //DATA.Unload(); //need to keep IsInterior around
    WRITE(XCLC);
/*  WRITE(XCLL);*/
    WRITE(IMPS);
    WRITE(IMPF);
    if(LNAM.value != 0 || LTMP.value != 0)
        {
        WRITE(LTMP);
        WRITE(LNAM);
        }
    if(XCLW.IsLoaded())
        WRITE(XCLW);
    else if(IsHasWater())
        WRITEREQ(XCLW);
    WRITE(XNAM);
    WRITE(XCLR);
    WRITE(XCIM);
    WRITE(XCET);
    WRITE(XEZN);
    WRITE(XCCM);
    WRITE(XCWT);
/*  Ownership.Write(writer);*/
    WRITE(XCAS);
    WRITE(XCMT);
    WRITE(XCMO);
    WRITE(TVDT);
    WRITE(MHDT);
    WRITE(XLCN);
    WRITE(XWCN);
    WRITE(XWCU);
    return -1;
    }

bool CELLRecord::operator ==(const CELLRecord &other) const
    {
    return (DATA == other.DATA &&
            XCLC == other.XCLC &&
/*          XCLL == other.XCLL &&*/
            IMPF == other.IMPF &&
            LTMP == other.LTMP &&
            LNAM == other.LNAM &&
            XCLW == other.XCLW &&
            XCIM == other.XCIM &&
            XEZN == other.XEZN &&
            XCCM == other.XCCM &&
            XCWT == other.XCWT &&
            XCAS == other.XCAS &&
            XCMO == other.XCMO &&
            IMPS == other.IMPS &&
            XCLR == other.XCLR &&
/*          Ownership == other.Ownership &&*/
            EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            XNAM.equalsi(other.XNAM) &&
            XCET == other.XCET &&
            XCMT == other.XCMT &&
            TVDT == other.TVDT &&
            MHDT == other.MHDT &&
            XLCN == other.XLCN &&
            XWCN == other.XWCN &&
            XWCU == other.XWCU);
    }

bool CELLRecord::operator !=(const CELLRecord &other) const
    {
    return !(*this == other);
    }

bool CELLRecord::equals(Record *other)
    {
    return *this == *(CELLRecord *)other;
    }

bool CELLRecord::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    //Precondition: equals has been run for these records and returned true
    //              all child records have been visited
    CELLRecord *master_cell = (CELLRecord *)master;
    Record *parent_wrld = GetParentRecord(), *master_wrld = master_cell->GetParentRecord();
    //Check to make sure the CELLs are attached at the same spot
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

/*
    if(ACHR.size() > master_cell->ACHR.size())
        return false;
    if(ACRE.size() > master_cell->ACRE.size())
        return false;
    if(REFR.size() > master_cell->REFR.size())
        return false;
    if(PGRE.size() > master_cell->PGRE.size())
        return false;
    if(PMIS.size() > master_cell->PMIS.size())
        return false;
    if(PBEA.size() > master_cell->PBEA.size())
        return false;
    if(PFLA.size() > master_cell->PFLA.size())
        return false;
    if(PCBE.size() > master_cell->PCBE.size())
        return false;
    if(NAVM.size() > master_cell->NAVM.size())
        return false;
*/
    if(LAND != NULL)
        {
        if(master_cell->LAND != NULL)
            {
            if(identical_records.count(LAND) == 0)
                return false;
            }
        else
            return false;
        }
/*
    for(uint32_t ListIndex = 0; ListIndex < ACHR.size(); ++ListIndex)
        if(identical_records.count(ACHR[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < ACRE.size(); ++ListIndex)
        if(identical_records.count(ACRE[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < REFR.size(); ++ListIndex)
        if(identical_records.count(REFR[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < PGRE.size(); ++ListIndex)
        if(identical_records.count(PGRE[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < PMIS.size(); ++ListIndex)
        if(identical_records.count(PMIS[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < PBEA.size(); ++ListIndex)
        if(identical_records.count(PBEA[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < PFLA.size(); ++ListIndex)
        if(identical_records.count(PFLA[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < PCBE.size(); ++ListIndex)
        if(identical_records.count(PCBE[ListIndex]) == 0)
            return false;

    for(uint32_t ListIndex = 0; ListIndex < NAVM.size(); ++ListIndex)
        if(identical_records.count(NAVM[ListIndex]) == 0)
            return false;
*/

    return true;
    }
}