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
#pragma once
#include "..\..\Common.h"
#include "..\..\GenericRecord.h"

namespace FNV
{
class IMGSRecord : public FNVRecord //Image Space
    {
    private:
        struct IMGSDNAM
            {
            //HDR
            FLOAT32 hdrEyeAdaptSpeed, hdrBlurRadius, hdrBlurPasses,
                    hdrEmissiveMult, hdrTargetLUM, hdrUpperLUMClamp,
                    hdrBrightScale, hdrBrightClamp, hdrLUMRampNoTex,
                    hdrLUMRampMin, hdrLUMRampMax, hdrSunlightDimmer,
                    hdrGrassDimmer, hdrTreeDimmer, hdrSkinDimmer;

            //Bloom
            FLOAT32 bloomBlurRadius, bloomAlphaMultInterior, bloomAlphaMultExterior;

            //Get Hit
            FLOAT32 hitBlurRadius, hitBlurDampingConstant, hitDampingConstant;

            //Night Eye
            FLOAT32 neRed, neGreen, neBlue, neBrightness;

            //Cinematic
            FLOAT32 saturation, contrastAvgLUMValue, contrastValue,
                    brightnessValue, cineRed, cineGreen, cineBlue,
                    cineValue;

            UINT8   unused1[4], unused2[4], unused3[4], unused4[4];
            UINT8   flags, unused5[3];

            IMGSDNAM();
            ~IMGSDNAM();

            bool operator ==(const IMGSDNAM &other) const;
            bool operator !=(const IMGSDNAM &other) const;
            };

        enum flagsFlags
            {
            fIsSaturation = 0x00000001,
            fIsContrast   = 0x00000002,
            fIsTint       = 0x00000004,
            fIsBrightness = 0x00000008
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<IMGSDNAM> DNAM; //IMGS Data

        IMGSRecord(unsigned char *_recData=NULL);
        IMGSRecord(IMGSRecord *srcRecord);
        ~IMGSRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsSaturation();
        void   IsSaturation(bool value);
        bool   IsContrast();
        void   IsContrast(bool value);
        bool   IsTint();
        void   IsTint(bool value);
        bool   IsBrightness();
        void   IsBrightness(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const IMGSRecord &other) const;
        bool operator !=(const IMGSRecord &other) const;
        bool equals(Record *other);
    };
}