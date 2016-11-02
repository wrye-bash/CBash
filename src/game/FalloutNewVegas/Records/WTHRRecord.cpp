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
#include "WTHRRecord.h"

namespace FNV
{
WTHRRecord::WTHRONAM::WTHRONAM():
    layer0Speed(0),
    layer1Speed(0),
    layer2Speed(0),
    layer3Speed(0)
    {
    //
    }

WTHRRecord::WTHRONAM::~WTHRONAM()
    {
    //
    }

bool WTHRRecord::WTHRONAM::operator ==(const WTHRONAM &other) const
    {
    return (layer0Speed == other.layer0Speed &&
            layer1Speed == other.layer1Speed &&
            layer2Speed == other.layer2Speed &&
            layer3Speed == other.layer3Speed);
    }

bool WTHRRecord::WTHRONAM::operator !=(const WTHRONAM &other) const
    {
    return !(*this == other);
    }

bool WTHRRecord::WTHRColors::operator ==(const WTHRColors &other) const
    {
    return (rise == other.rise &&
            day == other.day &&
            set == other.set &&
            night == other.night &&
            noon == other.noon &&
            midnight == other.midnight);
    }

bool WTHRRecord::WTHRColors::operator !=(const WTHRColors &other) const
    {
    return !(*this == other);
    }

bool WTHRRecord::WTHRNAM0::operator ==(const WTHRNAM0 &other) const
    {
    return (upperSky == other.upperSky &&
            fog == other.fog &&
            lowerClouds == other.lowerClouds &&
            ambient == other.ambient &&
            sunlight == other.sunlight &&
            sun == other.sun &&
            stars == other.stars &&
            lowerSky == other.lowerSky &&
            horizon == other.horizon &&
            upperClouds == other.upperClouds);
    }

bool WTHRRecord::WTHRNAM0::operator !=(const WTHRNAM0 &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRFNAM::WTHRFNAM():
    fogDayNear(0.0f),
    fogDayFar(0.0f),
    fogNightNear(0.0f),
    fogNightFar(0.0f),
    fogDayPower(0.0f),
    fogNightPower(0.0f)
    {
    //
    }

WTHRRecord::WTHRFNAM::~WTHRFNAM()
    {
    //
    }

bool WTHRRecord::WTHRFNAM::operator ==(const WTHRFNAM &other) const
    {
    return (AlmostEqual(fogDayNear,other.fogDayNear,2) &&
            AlmostEqual(fogDayFar,other.fogDayFar,2) &&
            AlmostEqual(fogNightNear,other.fogNightNear,2) &&
            AlmostEqual(fogNightFar,other.fogNightFar,2) &&
            AlmostEqual(fogDayPower,other.fogDayPower,2) &&
            AlmostEqual(fogNightPower,other.fogNightPower,2));
    }

bool WTHRRecord::WTHRFNAM::operator !=(const WTHRFNAM &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRDATA::WTHRDATA():
    windSpeed(0),
    lowerCloudSpeed(0),
    upperCloudSpeed(0),
    transDelta(0),
    sunGlare(0),
    sunDamage(0),
    rainFadeIn(0),
    rainFadeOut(0),
    boltFadeIn(0),
    boltFadeOut(0),
    boltFrequency(0),
    weatherType(0),
    boltRed(0),
    boltGreen(0),
    boltBlue(0)
    {
    //
    }

WTHRRecord::WTHRDATA::~WTHRDATA()
    {
    //
    }

bool WTHRRecord::WTHRDATA::operator ==(const WTHRDATA &other) const
    {
    return (windSpeed == other.windSpeed &&
            lowerCloudSpeed == other.lowerCloudSpeed &&
            upperCloudSpeed == other.upperCloudSpeed &&
            transDelta == other.transDelta &&
            sunGlare == other.sunGlare &&
            sunDamage == other.sunDamage &&
            rainFadeIn == other.rainFadeIn &&
            rainFadeOut == other.rainFadeOut &&
            boltFadeIn == other.boltFadeIn &&
            boltFadeOut == other.boltFadeOut &&
            boltFrequency == other.boltFrequency &&
            weatherType == other.weatherType &&
            boltRed == other.boltRed &&
            boltGreen == other.boltGreen &&
            boltBlue == other.boltBlue);
    }

bool WTHRRecord::WTHRDATA::operator !=(const WTHRDATA &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRSNAM::WTHRSNAM():
    sound(0),
    type(0)
    {
    //
    }

WTHRRecord::WTHRSNAM::~WTHRSNAM()
    {
    //
    }

bool WTHRRecord::WTHRSNAM::IsDefault()
    {
    return (type == eDefault);
    }

void WTHRRecord::WTHRSNAM::IsDefault(bool value)
    {
    if(value)
        type = eDefault;
    else if(IsDefault())
        type = ePrecip;
    }

bool WTHRRecord::WTHRSNAM::IsPrecip()
    {
    return (type == ePrecip);
    }

void WTHRRecord::WTHRSNAM::IsPrecip(bool value)
    {
    if(value)
        type = ePrecip;
    else if(IsPrecip())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsPrecipitation()
    {
    return (type == ePrecip);
    }

void WTHRRecord::WTHRSNAM::IsPrecipitation(bool value)
    {
    if(value)
        type = ePrecip;
    else if(IsPrecipitation())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsWind()
    {
    return (type == eWind);
    }

void WTHRRecord::WTHRSNAM::IsWind(bool value)
    {
    if(value)
        type = eWind;
    else if(IsWind())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsThunder()
    {
    return (type == eThunder);
    }

void WTHRRecord::WTHRSNAM::IsThunder(bool value)
    {
    if(value)
        type = eThunder;
    else if(IsThunder())
        type = eDefault;
    }

bool WTHRRecord::WTHRSNAM::IsType(uint32_t Type)
    {
    return (type == Type);
    }

void WTHRRecord::WTHRSNAM::SetType(uint32_t Type)
    {
    type = Type;
    }

bool WTHRRecord::WTHRSNAM::operator ==(const WTHRSNAM &other) const
    {
    return (sound == other.sound &&
            type == other.type);
    }
bool WTHRRecord::WTHRSNAM::operator !=(const WTHRSNAM &other) const
    {
    return !(*this == other);
    }

WTHRRecord::WTHRRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

WTHRRecord::WTHRRecord(WTHRRecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    _0IAD = srcRecord->_0IAD;
    _1IAD = srcRecord->_1IAD;
    _2IAD = srcRecord->_2IAD;
    _3IAD = srcRecord->_3IAD;
    _4IAD = srcRecord->_4IAD;
    _5IAD = srcRecord->_5IAD;
    DNAM = srcRecord->DNAM;
    CNAM = srcRecord->CNAM;
    ANAM = srcRecord->ANAM;
    BNAM = srcRecord->BNAM;
    MODL = srcRecord->MODL;
    LNAM = srcRecord->LNAM;
    ONAM = srcRecord->ONAM;
    PNAM = srcRecord->PNAM;
    NAM0 = srcRecord->NAM0;
    FNAM = srcRecord->FNAM;
    INAM = srcRecord->INAM;
    DATA = srcRecord->DATA;
    Sounds = srcRecord->Sounds;
    return;
    }

WTHRRecord::~WTHRRecord()
    {
    //
    }

bool WTHRRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(_0IAD.IsLoaded())
        op.Accept(_0IAD.value);
    if(_1IAD.IsLoaded())
        op.Accept(_1IAD.value);
    if(_2IAD.IsLoaded())
        op.Accept(_2IAD.value);
    if(_3IAD.IsLoaded())
        op.Accept(_3IAD.value);
    if(_4IAD.IsLoaded())
        op.Accept(_4IAD.value);
    if(_5IAD.IsLoaded())
        op.Accept(_5IAD.value);
    if(MODL.IsLoaded())
        {
        for(uint32_t x = 0; x < MODL->Textures.MODS.size(); x++)
            op.Accept(MODL->Textures.MODS[x]->texture);
        }
    for(uint32_t x = 0; x < Sounds.value.size(); x++)
        op.Accept(Sounds.value[x]->sound);

    return op.Stop();
    }

bool WTHRRecord::IsPleasant()
    {
    return (DATA.value.weatherType & ePleasant) != 0;
    }

void WTHRRecord::IsPleasant(bool value)
    {
    if(value)
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsPleasant())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsCloudy()
    {
    return (DATA.value.weatherType & eCloudy) != 0;
    }

void WTHRRecord::IsCloudy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType |= eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsCloudy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsRainy()
    {
    return (DATA.value.weatherType & eRainy) != 0;
    }

void WTHRRecord::IsRainy(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType |= eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsRainy())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsSnow()
    {
    return (DATA.value.weatherType & eSnow) != 0;
    }

void WTHRRecord::IsSnow(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType |= eSnow;
        }
    else if(IsSnow())
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsNone()
    {
    return IsPleasant() == false && IsCloudy() == false && IsRainy() == false && IsSnow() == false;
    }

void WTHRRecord::IsNone(bool value)
    {
    if(value)
        {
        DATA.value.weatherType &= ~ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    else if(IsNone())
        {
        DATA.value.weatherType |= ePleasant;
        DATA.value.weatherType &= ~eCloudy;
        DATA.value.weatherType &= ~eRainy;
        DATA.value.weatherType &= ~eSnow;
        }
    }

bool WTHRRecord::IsUnk1()
    {
    return (DATA.value.weatherType & fUnk1) != 0;
    }

void WTHRRecord::IsUnk1(bool value)
    {
    SETBIT(DATA.value.weatherType, fUnk1, value);
    }

bool WTHRRecord::IsUnk2()
    {
    return (DATA.value.weatherType & fUnk2) != 0;
    }

void WTHRRecord::IsUnk2(bool value)
    {
    SETBIT(DATA.value.weatherType, fUnk2, value);
    }

bool WTHRRecord::IsType(uint8_t Type)
    {
    return (DATA.value.weatherType == Type);
    }

void WTHRRecord::SetType(uint8_t Type)
    {
    DATA.value.weatherType = Type;
    }

bool WTHRRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    return Exact ? ((DATA.value.weatherType & Mask) == Mask) : ((DATA.value.weatherType & Mask) != 0);
    }

void WTHRRecord::SetFlagMask(uint8_t Mask)
    {
    DATA.value.weatherType = Mask;
    }

uint32_t WTHRRecord::GetType()
    {
    return REV32(WTHR);
    }

char * WTHRRecord::GetStrType()
    {
    return "WTHR";
    }

int32_t WTHRRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(_IAD) & 0xFFFFFF00 | 0x00:
                //Unlike all other sigs, IAD's use 0x00, 0x01, etc instead of the character 0, 1, etc
                //So this oddity has to be compensated for
                //The above nonsense gets optimized away, so there's no runtime cost
                _0IAD.Read(buffer, subSize);
                break;
            case REV32(_IAD) & 0xFFFFFF00 | 0x01:
                _1IAD.Read(buffer, subSize);
                break;
            case REV32(_IAD) & 0xFFFFFF00 | 0x02:
                _2IAD.Read(buffer, subSize);
                break;
            case REV32(_IAD) & 0xFFFFFF00 | 0x03:
                _3IAD.Read(buffer, subSize);
                break;
            case REV32(_IAD) & 0xFFFFFF00 | 0x04:
                _4IAD.Read(buffer, subSize);
                break;
            case REV32(_IAD) & 0xFFFFFF00 | 0x05:
                _5IAD.Read(buffer, subSize);
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(CNAM):
                CNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(BNAM):
                BNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL->MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODB):
                MODL.Load();
                MODL->MODB.Read(buffer, subSize);
                break;
            case REV32(MODT):
                MODL.Load();
                MODL->MODT.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MODS):
                MODL.Load();
                MODL->Textures.Read(buffer, subSize);
                break;
            case REV32(MODD):
                MODL.Load();
                MODL->MODD.Read(buffer, subSize);
                break;
            case REV32(LNAM):
                LNAM.Read(buffer, subSize);
                break;
            case REV32(ONAM):
                ONAM.Read(buffer, subSize);
                break;
            case REV32(PNAM):
                PNAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(NAM0):
                switch(subSize)
                    {
                    case 160:
                        //old format is missing the noon and midnight colors
                        memcpy(&NAM0.value.upperSky, buffer, sizeof(NAM0.value.upperSky));
                        buffer += sizeof(NAM0.value.upperSky);
                        memcpy(&NAM0.value.fog, buffer, sizeof(NAM0.value.fog));
                        buffer += sizeof(NAM0.value.fog);
                        memcpy(&NAM0.value.lowerClouds, buffer, sizeof(NAM0.value.lowerClouds));
                        buffer += sizeof(NAM0.value.lowerClouds);
                        memcpy(&NAM0.value.ambient, buffer, sizeof(NAM0.value.ambient));
                        buffer += sizeof(NAM0.value.ambient);
                        memcpy(&NAM0.value.sunlight, buffer, sizeof(NAM0.value.sunlight));
                        buffer += sizeof(NAM0.value.sunlight);
                        memcpy(&NAM0.value.sun, buffer, sizeof(NAM0.value.sun));
                        buffer += sizeof(NAM0.value.sun);
                        memcpy(&NAM0.value.stars, buffer, sizeof(NAM0.value.stars));
                        buffer += sizeof(NAM0.value.stars);
                        memcpy(&NAM0.value.lowerSky, buffer, sizeof(NAM0.value.lowerSky));
                        buffer += sizeof(NAM0.value.lowerSky);
                        memcpy(&NAM0.value.horizon, buffer, sizeof(NAM0.value.horizon));
                        buffer += sizeof(NAM0.value.horizon);
                        memcpy(&NAM0.value.upperClouds, buffer, sizeof(NAM0.value.upperClouds));
                        buffer += sizeof(NAM0.value.upperClouds);
                        break;
                    default:
                        NAM0.Read(buffer, subSize);
                        break;
                    }
                break;
            case REV32(FNAM):
                FNAM.Read(buffer, subSize);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(SNAM):
                Sounds.Read(buffer, subSize);
                break;
            default:
                //printer("FileName = %s\n", FileName);
                printer("  WTHR: %08X - Unknown subType = %04x\n", formID, subType);
                CBASH_CHUNK_DEBUG
                printer("  Size = %i\n", subSize);
                printer("  CurPos = %04x\n\n", buffer - 6);
                buffer = end_buffer;
                break;
            }
        };
    return 0;
    }

int32_t WTHRRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    _0IAD.Unload();
    _1IAD.Unload();
    _2IAD.Unload();
    _3IAD.Unload();
    _4IAD.Unload();
    _5IAD.Unload();
    DNAM.Unload();
    CNAM.Unload();
    ANAM.Unload();
    BNAM.Unload();
    MODL.Unload();
    LNAM.Unload();
    ONAM.Unload();
    PNAM.Unload();
    NAM0.Unload();
    FNAM.Unload();
    INAM.Unload();
    DATA.Unload();
    Sounds.Unload();
    return 1;
    }

int32_t WTHRRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    _0IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x00, writer);
    _1IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x01, writer);
    _2IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x02, writer);
    _3IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x03, writer);
    _4IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x04, writer);
    _5IAD.Write(REV32(_IAD) & 0xFFFFFF00 | 0x05, writer);
    WRITE(DNAM);
    WRITE(CNAM);
    WRITE(ANAM);
    WRITE(BNAM);
    MODL.Write(writer);
    WRITE(LNAM);
    WRITE(ONAM);
    WRITE(PNAM);
    WRITE(NAM0);
    WRITE(FNAM);
    WRITE(INAM);
    WRITE(DATA);
    WRITEAS(Sounds,SNAM);
    return -1;
    }

bool WTHRRecord::operator ==(const WTHRRecord &other) const
    {
    return (_0IAD == other._0IAD &&
            _1IAD == other._1IAD &&
            _2IAD == other._2IAD &&
            _3IAD == other._3IAD &&
            _4IAD == other._4IAD &&
            _5IAD == other._5IAD &&
            MODL == other.MODL &&
            LNAM == other.LNAM &&
            ONAM == other.ONAM &&
            NAM0 == other.NAM0 &&
            DATA == other.DATA &&
            INAM == other.INAM &&
            PNAM == other.PNAM &&
            EDID.equalsi(other.EDID) &&
            DNAM.equalsi(other.DNAM) &&
            CNAM.equalsi(other.CNAM) &&
            ANAM.equalsi(other.ANAM) &&
            BNAM.equalsi(other.BNAM) &&
            FNAM == other.FNAM &&
            Sounds == other.Sounds);
    }

bool WTHRRecord::operator !=(const WTHRRecord &other) const
    {
    return !(*this == other);
    }

bool WTHRRecord::equals(Record *other)
    {
    return *this == *(WTHRRecord *)other;
    }
}