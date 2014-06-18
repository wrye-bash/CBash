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
#include "WATRRecord.h"

namespace Ob
{
WATRRecord::WATRDATA::WATRDATA():
    windVelocity(0.1f),
    windDirection(90.0f),
    waveAmp(0.5f),
    waveFreq(1.0f),
    sunPower(50.0f),
    reflectAmt(0.5f),
    fresnelAmt(0.025f),
    xSpeed(0.0f),
    ySpeed(0.0f),
    fogNear(27852.801f),
    fogFar(163840.0f),
    shallow(0, 128, 128, 0),
    deep(0, 0, 25, 0),
    refl(255, 255, 255, 0),
    blend(50),
    rainForce(0.1f),
    rainVelocity(0.6f),
    rainFalloff(0.985f),
    rainDampner(2.0f),
    rainSize(0.01f),
    dispForce(0.4f),
    dispVelocity(0.6f),
    dispFalloff(0.985f),
    dispDampner(10.0f),
    dispSize(0.05f),
    damage(0)
    {
    memset(&unused1[0], 0xCD, sizeof(unused1));
    }

WATRRecord::WATRDATA::~WATRDATA()
    {
    //
    }

bool WATRRecord::WATRDATA::operator ==(const WATRDATA &other) const
    {
    return (damage == other.damage &&
            blend == other.blend &&
            AlmostEqual(windVelocity,other.windVelocity,2) &&
            AlmostEqual(windDirection,other.windDirection,2) &&
            AlmostEqual(waveAmp,other.waveAmp,2) &&
            AlmostEqual(waveFreq,other.waveFreq,2) &&
            AlmostEqual(sunPower,other.sunPower,2) &&
            AlmostEqual(reflectAmt,other.reflectAmt,2) &&
            AlmostEqual(fresnelAmt,other.fresnelAmt,2) &&
            AlmostEqual(xSpeed,other.xSpeed,2) &&
            AlmostEqual(ySpeed,other.ySpeed,2) &&
            AlmostEqual(fogNear,other.fogNear,2) &&
            AlmostEqual(fogFar,other.fogFar,2) &&
            AlmostEqual(rainForce,other.rainForce,2) &&
            AlmostEqual(rainVelocity,other.rainVelocity,2) &&
            AlmostEqual(rainFalloff,other.rainFalloff,2) &&
            AlmostEqual(rainDampner,other.rainDampner,2) &&
            AlmostEqual(rainSize,other.rainSize,2) &&
            AlmostEqual(dispForce,other.dispForce,2) &&
            AlmostEqual(dispVelocity,other.dispVelocity,2) &&
            AlmostEqual(dispFalloff,other.dispFalloff,2) &&
            AlmostEqual(dispDampner,other.dispDampner,2) &&
            AlmostEqual(dispSize,other.dispSize,2) &&
            shallow == other.shallow &&
            deep == other.deep &&
            refl == other.refl);
    }

bool WATRRecord::WATRDATA::operator !=(const WATRDATA &other) const
    {
    return !(*this == other);
    }

WATRRecord::WATRGNAM::WATRGNAM():
    dayWater(0),
    nightWater(0),
    underWater(0)
    {
    //
    }

WATRRecord::WATRGNAM::~WATRGNAM()
    {
    //
    }

bool WATRRecord::WATRGNAM::operator ==(const WATRGNAM &other) const
    {
    return (dayWater == other.dayWater &&
            nightWater == other.nightWater &&
            underWater == other.underWater);
    }

bool WATRRecord::WATRGNAM::operator !=(const WATRGNAM &other) const
    {
    return !(*this == other);
    }

WATRRecord::WATRRecord(unsigned char *_recData):
    Record(_recData)
    {
    //
    }

WATRRecord::WATRRecord(WATRRecord *srcRecord):
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

    EDID = srcRecord->EDID;
    TNAM = srcRecord->TNAM;
    ANAM = srcRecord->ANAM;
    FNAM = srcRecord->FNAM;
    MNAM = srcRecord->MNAM;
    SNAM = srcRecord->SNAM;
    DATA = srcRecord->DATA;
    GNAM = srcRecord->GNAM;
    }

WATRRecord::~WATRRecord()
    {
    //
    }

bool WATRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(SNAM.IsLoaded())
        op.Accept(SNAM.value);
    if(GNAM.IsLoaded())
        {
        op.Accept(GNAM->dayWater);
        op.Accept(GNAM->nightWater);
        op.Accept(GNAM->underWater);
        }

    return op.Stop();
    }

bool WATRRecord::IsCausesDmg()
    {
    return (FNAM.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDmg(bool value)
    {
    SETBIT(FNAM.value, fIsCausesDamage, value);
    }

bool WATRRecord::IsCausesDamage()
    {
    return (FNAM.value & fIsCausesDamage) != 0;
    }

void WATRRecord::IsCausesDamage(bool value)
    {
    SETBIT(FNAM.value, fIsCausesDamage, value);
    }

bool WATRRecord::IsReflective()
    {
    return (FNAM.value & fIsReflective) != 0;
    }

void WATRRecord::IsReflective(bool value)
    {
    SETBIT(FNAM.value, fIsReflective, value);
    }

bool WATRRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((FNAM.value & Mask) == Mask) : ((FNAM.value & Mask) != 0);
    }

void WATRRecord::SetFlagMask(uint8_t Mask)
    {
    FNAM.value = Mask;
    }

uint32_t WATRRecord::GetType()
    {
    return REV32(WATR);
    }

char * WATRRecord::GetStrType()
    {
    return "WATR";
    }

int32_t WATRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(TNAM):
                TNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize);
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(MNAM):
                MNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(SNAM):
                SNAM.Read(buffer, subSize);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(GNAM):
                GNAM.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WATR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t WATRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    TNAM.Unload();
    ANAM.Unload();
    FNAM.Unload();
    MNAM.Unload();
    SNAM.Unload();
    DATA.Unload();
    GNAM.Unload();
    return 1;
    }

int32_t WATRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(TNAM);
    WRITE(ANAM);
    WRITE(FNAM);
    WRITE(MNAM);
    WRITE(SNAM);
    WRITE(DATA);
    WRITE(GNAM);
    return -1;
    }

bool WATRRecord::operator ==(const WATRRecord &other) const
    {
    return (ANAM == other.ANAM &&
            FNAM == other.FNAM &&
            SNAM == other.SNAM &&
            GNAM == other.GNAM &&
            EDID.equalsi(other.EDID) &&
            TNAM.equalsi(other.TNAM) &&
            MNAM.equalsi(other.MNAM) &&
            DATA == other.DATA);
    }

bool WATRRecord::operator !=(const WATRRecord &other) const
    {
    return !(*this == other);
    }

bool WATRRecord::equals(Record *other)
    {
    return *this == *(WATRRecord *)other;
    }
}