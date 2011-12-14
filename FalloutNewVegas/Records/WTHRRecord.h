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
class WTHRRecord : public FNVRecord //Weather
    {
    private:
        struct WTHRONAM
            {
            UINT8   layer0Speed, layer1Speed, layer2Speed, layer3Speed;

            WTHRONAM();
            ~WTHRONAM();

            bool operator ==(const WTHRONAM &other) const;
            bool operator !=(const WTHRONAM &other) const;
            };

        struct WTHRColors
            {
            GENCLR rise;
            GENCLR day;
            GENCLR set;
            GENCLR night;
            GENCLR noon;
            GENCLR midnight;

            bool operator ==(const WTHRColors &other) const;
            bool operator !=(const WTHRColors &other) const;
            };

        struct WTHRNAM0
            {
            WTHRColors upperSky;
            WTHRColors fog;
            WTHRColors lowerClouds;
            WTHRColors ambient;
            WTHRColors sunlight;
            WTHRColors sun;
            WTHRColors stars;
            WTHRColors lowerSky;
            WTHRColors horizon;
            WTHRColors upperClouds;

            bool operator ==(const WTHRNAM0 &other) const;
            bool operator !=(const WTHRNAM0 &other) const;
            };

        struct WTHRFNAM
            {
            FLOAT32 fogDayNear, fogDayFar, fogNightNear,
                    fogNightFar, fogDayPower, fogNightPower;

            WTHRFNAM();
            ~WTHRFNAM();

            bool operator ==(const WTHRFNAM &other) const;
            bool operator !=(const WTHRFNAM &other) const;
            };

        struct WTHRDATA
            {
            UINT8   windSpeed, lowerCloudSpeed, upperCloudSpeed,
                    transDelta, sunGlare, sunDamage, rainFadeIn,
                    rainFadeOut, boltFadeIn, boltFadeOut, boltFrequency,
                    weatherType, boltRed, boltGreen, boltBlue;

            WTHRDATA();
            ~WTHRDATA();

            bool operator ==(const WTHRDATA &other) const;
            bool operator !=(const WTHRDATA &other) const;
            };

        struct WTHRSNAM
            {
            FORMID  sound;
            UINT32  type;

            enum eSoundType
                {
                eDefault = 0,
                ePrecip  = 1,
                eWind    = 2,
                eThunder = 3
                };

            WTHRSNAM();
            ~WTHRSNAM();

            bool IsDefault();
            void IsDefault(bool value);
            bool IsPrecip();
            void IsPrecip(bool value);
            bool IsPrecipitation();
            void IsPrecipitation(bool value);
            bool IsWind();
            void IsWind(bool value);
            bool IsThunder();
            void IsThunder(bool value);
            bool IsType(UINT32 Type);
            void SetType(UINT32 Type);

            bool operator ==(const WTHRSNAM &other) const;
            bool operator !=(const WTHRSNAM &other) const;
            };

        enum eWeatherType //actually flags, but all are exclusive(except unknowns)...so like a Type
            { //Manual hackery will make the CS think it is multiple types. It isn't known how the game would react.
            eNone     = 0x00,
            ePleasant = 0x01,
            eCloudy   = 0x02,
            eRainy    = 0x04,
            eSnow     = 0x08,
            fUnk1     = 0x40,
            fUnk2     = 0x80
            };

    public:
        StringRecord EDID; //Editor ID
        OptSimpleSubRecord<FORMID> _0IAD; //Sunrise Image Space Modifier
        OptSimpleSubRecord<FORMID> _1IAD; //Day Image Space Modifier
        OptSimpleSubRecord<FORMID> _2IAD; //Sunset Image Space Modifier
        OptSimpleSubRecord<FORMID> _3IAD; //Night Image Space Modifier
        OptSimpleSubRecord<FORMID> _4IAD; //Unknown
        OptSimpleSubRecord<FORMID> _5IAD; //Unknown
        StringRecord DNAM; //Cloud Textures - Layer 0
        StringRecord CNAM; //Cloud Textures - Layer 1
        StringRecord ANAM; //Cloud Textures - Layer 2
        StringRecord BNAM; //Cloud Textures - Layer 3
        OptSubRecord<FNVMODEL> MODL; //Model
        ReqSimpleSubRecord<UINT32, 4> LNAM; //Unknown
        OptSubRecord<WTHRONAM> ONAM; //Cloud Speeds
        RawRecord PNAM; //Unused
        ReqSubRecord<WTHRNAM0> NAM0; //Colors by Types/Times
        ReqSubRecord<WTHRFNAM> FNAM; //Fog Distance
        RawRecord INAM; //Unused
        ReqSubRecord<WTHRDATA> DATA; //Data
        UnorderedSparseArray<WTHRSNAM *> Sounds; //Sounds

        WTHRRecord(unsigned char *_recData=NULL);
        WTHRRecord(WTHRRecord *srcRecord);
        ~WTHRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsPleasant();
        void   IsPleasant(bool value);
        bool   IsCloudy();
        void   IsCloudy(bool value);
        bool   IsRainy();
        void   IsRainy(bool value);
        bool   IsSnow();
        void   IsSnow(bool value);
        bool   IsNone();
        void   IsNone(bool value);
        bool   IsUnk1();
        void   IsUnk1(bool value);
        bool   IsUnk2();
        void   IsUnk2(bool value);
        bool   IsType(UINT8 Type);
        void   SetType(UINT8 Type);
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

        bool operator ==(const WTHRRecord &other) const;
        bool operator !=(const WTHRRecord &other) const;
        bool equals(Record *other);
    };
}