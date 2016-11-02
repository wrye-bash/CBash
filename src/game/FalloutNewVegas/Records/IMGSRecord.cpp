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
#include "IMGSRecord.h"

namespace FNV
{
IMGSRecord::IMGSDNAM::IMGSDNAM():
    hdrEyeAdaptSpeed(0.0), hdrBlurRadius(0.0), hdrBlurPasses(0.0),
    hdrEmissiveMult(0.0), hdrTargetLUM(0.0), hdrUpperLUMClamp(0.0),
    hdrBrightScale(0.0), hdrBrightClamp(0.0), hdrLUMRampNoTex(0.0),
    hdrLUMRampMin(0.0), hdrLUMRampMax(0.0), hdrSunlightDimmer(0.0),
    hdrGrassDimmer(0.0), hdrTreeDimmer(0.0), hdrSkinDimmer(0.0),
    bloomBlurRadius(0.0), bloomAlphaMultInterior(0.0), bloomAlphaMultExterior(0.0),
    hitBlurRadius(0.0), hitBlurDampingConstant(0.0), hitDampingConstant(0.0),
    neRed(0.0), neGreen(0.0), neBlue(0.0), neBrightness(0.0),
    saturation(0.0), contrastAvgLUMValue(0.0), contrastValue(0.0),
    brightnessValue(0.0), cineRed(0.0), cineGreen(0.0), cineBlue(0.0),
    cineValue(0.0),
    flags(0)
    {
    memset(&unused1, 0, sizeof(unused1));
    memset(&unused2, 0, sizeof(unused2));
    memset(&unused3, 0, sizeof(unused3));
    memset(&unused4, 0, sizeof(unused4));
    memset(&unused5, 0, sizeof(unused5));
    }

IMGSRecord::IMGSDNAM::~IMGSDNAM()
    {
    //
    }

bool IMGSRecord::IMGSDNAM::operator ==(const IMGSDNAM &other) const
    {
    return (AlmostEqual(hdrEyeAdaptSpeed, other.hdrEyeAdaptSpeed, 2) &&
            AlmostEqual(hdrBlurRadius, other.hdrBlurRadius, 2) &&
            AlmostEqual(hdrBlurPasses, other.hdrBlurPasses, 2) &&
            AlmostEqual(hdrEmissiveMult, other.hdrEmissiveMult, 2) &&
            AlmostEqual(hdrTargetLUM, other.hdrTargetLUM, 2) &&
            AlmostEqual(hdrUpperLUMClamp, other.hdrUpperLUMClamp, 2) &&
            AlmostEqual(hdrBrightScale, other.hdrBrightScale, 2) &&
            AlmostEqual(hdrBrightClamp, other.hdrBrightClamp, 2) &&
            AlmostEqual(hdrLUMRampNoTex, other.hdrLUMRampNoTex, 2) &&
            AlmostEqual(hdrLUMRampMin, other.hdrLUMRampMin, 2) &&
            AlmostEqual(hdrLUMRampMax, other.hdrLUMRampMax, 2) &&
            AlmostEqual(hdrSunlightDimmer, other.hdrSunlightDimmer, 2) &&
            AlmostEqual(hdrGrassDimmer, other.hdrGrassDimmer, 2) &&
            AlmostEqual(hdrTreeDimmer, other.hdrTreeDimmer, 2) &&
            AlmostEqual(hdrSkinDimmer, other.hdrSkinDimmer, 2) &&
            AlmostEqual(bloomBlurRadius, other.bloomBlurRadius, 2) &&
            AlmostEqual(bloomAlphaMultInterior, other.bloomAlphaMultInterior, 2) &&
            AlmostEqual(bloomAlphaMultExterior, other.bloomAlphaMultExterior, 2) &&
            AlmostEqual(hitBlurRadius, other.hitBlurRadius, 2) &&
            AlmostEqual(hitBlurDampingConstant, other.hitBlurDampingConstant, 2) &&
            AlmostEqual(hitDampingConstant, other.hitDampingConstant, 2) &&
            AlmostEqual(neRed, other.neRed, 2) &&
            AlmostEqual(neGreen, other.neGreen, 2) &&
            AlmostEqual(neBlue, other.neBlue, 2) &&
            AlmostEqual(neBrightness, other.neBrightness, 2) &&
            AlmostEqual(saturation, other.saturation, 2) &&
            AlmostEqual(contrastAvgLUMValue, other.contrastAvgLUMValue, 2) &&
            AlmostEqual(contrastValue, other.contrastValue, 2) &&
            AlmostEqual(brightnessValue, other.brightnessValue, 2) &&
            AlmostEqual(cineRed, other.cineRed, 2) &&
            AlmostEqual(cineGreen, other.cineGreen, 2) &&
            AlmostEqual(cineBlue, other.cineBlue, 2) &&
            AlmostEqual(cineValue, other.cineValue, 2) &&
            flags == other.flags
            // unused1, unused2, unused3, unused4, unused5
            );
    }

bool IMGSRecord::IMGSDNAM::operator !=(const IMGSDNAM &other) const
    {
    return !(*this == other);
    }

IMGSRecord::IMGSRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

IMGSRecord::IMGSRecord(IMGSRecord *srcRecord):
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
    DNAM = srcRecord->DNAM;
    return;
    }

IMGSRecord::~IMGSRecord()
    {
    //
    }

bool IMGSRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

bool IMGSRecord::IsSaturation()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM->flags & fIsSaturation) != 0;
    }

void IMGSRecord::IsSaturation(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM->flags, fIsSaturation, value);
    }

bool IMGSRecord::IsContrast()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM->flags & fIsContrast) != 0;
    }

void IMGSRecord::IsContrast(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM->flags, fIsContrast, value);
    }

bool IMGSRecord::IsTint()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM->flags & fIsTint) != 0;
    }

void IMGSRecord::IsTint(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM->flags, fIsTint, value);
    }

bool IMGSRecord::IsBrightness()
    {
    if (!DNAM.IsLoaded()) return false;
    return (DNAM->flags & fIsBrightness) != 0;
    }

void IMGSRecord::IsBrightness(bool value)
    {
    if (!DNAM.IsLoaded()) return;
    SETBIT(DNAM->flags, fIsBrightness, value);
    }

bool IMGSRecord::IsFlagMask(uint8_t Mask, bool Exact)
    {
    if (!DNAM.IsLoaded()) return false;
    return Exact ? ((DNAM->flags & Mask) == Mask) : ((DNAM->flags & Mask) != 0);
    }

void IMGSRecord::SetFlagMask(uint8_t Mask)
    {
    DNAM.Load();
    DNAM->flags = Mask;
    }

uint32_t IMGSRecord::GetType()
    {
    return REV32(IMGS);
    }

char * IMGSRecord::GetStrType()
    {
    return "IMGS";
    }

int32_t IMGSRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t IMGSRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DNAM.Unload();
    return 1;
    }

int32_t IMGSRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DNAM);

    return -1;
    }

bool IMGSRecord::operator ==(const IMGSRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DNAM == other.DNAM);
    }

bool IMGSRecord::operator !=(const IMGSRecord &other) const
    {
    return !(*this == other);
    }

bool IMGSRecord::equals(Record *other)
    {
    return *this == *(IMGSRecord *)other;
    }
}