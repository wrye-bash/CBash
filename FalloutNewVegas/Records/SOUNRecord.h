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
class SOUNRecord : public FNVRecord //Sound
    {
    private:
        struct SOUNSNDD
            {
            UINT8   minDistance, maxDistance;
            SINT8   freqAdjustment;
            UINT8   unused1;
            UINT32  flags;
            SINT16  staticAtten;
            UINT8   stopTime, startTime;
            //Below are only on SNDD, and not SNDX
            SINT16  attenCurve[5], reverb;
            SINT32  priority, x, y;

            SOUNSNDD();
            ~SOUNSNDD();

            bool operator ==(const SOUNSNDD &other) const;
            bool operator !=(const SOUNSNDD &other) const;
            };

        enum flagsFlags
            {
            fIsRandomFrequencyShift = 0x00000001,
            fIsPlayAtRandom         = 0x00000002,
            fIsEnvironmentIgnored   = 0x00000004,
            fIsRandomLocation       = 0x00000008,
            fIsLoop                 = 0x00000010,
            fIsMenuSound            = 0x00000020,
            fIs2D                   = 0x00000040,
            fIs360LFE               = 0x00000080,
            fIsDialogueSound        = 0x00000100,
            fIsEnvelopeFast         = 0x00000200,
            fIsEnvelopeSlow         = 0x00000400,
            fIs2DRadius             = 0x00000800,
            fIsMuteWhenSubmerged    = 0x00001000
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FNAM; //Sound Filename
        SemiOptSimpleSubRecord<UINT8> RNAM; //Random Chance %
        ReqSubRecord<SOUNSNDD> SNDD; //Sound Data (May be SNDX format, so auto-update on read)

        //OptSubRecord<GENANAM> ANAM; //Attenuation Curve (Read into SNDD)
        //OptSimpleSubRecord<SINT16> GNAM; //Reverb Attenuation Control (Read into SNDD)
        //OptSimpleSubRecord<SINT32> HNAM; //Priority (Read into SNDD)

        SOUNRecord(unsigned char *_recData=NULL);
        SOUNRecord(SOUNRecord *srcRecord);
        ~SOUNRecord();

        bool   IsRandomFrequencyShift();
        void   IsRandomFrequencyShift(bool value);
        bool   IsPlayAtRandom();
        void   IsPlayAtRandom(bool value);
        bool   IsEnvironmentIgnored();
        void   IsEnvironmentIgnored(bool value);
        bool   IsRandomLocation();
        void   IsRandomLocation(bool value);
        bool   IsLoop();
        void   IsLoop(bool value);
        bool   IsMenuSound();
        void   IsMenuSound(bool value);
        bool   Is2D();
        void   Is2D(bool value);
        bool   Is360LFE();
        void   Is360LFE(bool value);
        bool   IsDialogueSound();
        void   IsDialogueSound(bool value);
        bool   IsEnvelopeFast();
        void   IsEnvelopeFast(bool value);
        bool   IsEnvelopeSlow();
        void   IsEnvelopeSlow(bool value);
        bool   Is2DRadius();
        void   Is2DRadius(bool value);
        bool   IsMuteWhenSubmerged();
        void   IsMuteWhenSubmerged(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const SOUNRecord &other) const;
        bool operator !=(const SOUNRecord &other) const;
        bool equals(Record *other);
    };
}