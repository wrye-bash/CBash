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
#include "common/Common.h"
#include "common/GenericRecord.h"

namespace Ob
{
class SOUNRecord : public Record
    {
    private:
        struct SOUNSNDX
            {
            uint8_t   minDistance, maxDistance;
            int8_t   freqAdjustment;
            uint8_t   unused1;
            uint16_t  flags;
            uint8_t   unused2[2];
            int16_t  staticAtten;
            uint8_t   stopTime,startTime;

            SOUNSNDX();
            ~SOUNSNDX();

            bool operator ==(const SOUNSNDX &other) const;
            bool operator !=(const SOUNSNDX &other) const;
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
            fIs360LFE               = 0x00000080
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FNAM; //Sound Filename
        ReqSubRecord<SOUNSNDX> SNDX; //Sound Data

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
        bool   IsFlagMask(unsigned short Mask, bool Exact=false);
        void   SetFlagMask(unsigned short Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const SOUNRecord &other) const;
        bool operator !=(const SOUNRecord &other) const;
        bool equals(Record *other);
    };
}