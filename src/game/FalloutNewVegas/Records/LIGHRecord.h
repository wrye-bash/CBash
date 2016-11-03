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
#include "../FNVRecord.h"

namespace FNV
{
class LIGHRecord : public FNVRecord //Light
    {
    private:
        struct LIGHDATA
            {
            int32_t  duration;
            uint32_t  radius;
            GENCLR  color;
            uint32_t  flags;
            float falloff, fov;
            uint32_t  value;
            float weight;

            LIGHDATA();
            ~LIGHDATA();

            bool operator ==(const LIGHDATA &other) const;
            bool operator !=(const LIGHDATA &other) const;
            };

        enum flagsFlags
            {
            fIsDynamic      = 0x00000001,
            fIsCanTake      = 0x00000002,
            fIsNegative     = 0x00000004,
            fIsFlickers     = 0x00000008,
            fIsOffByDefault = 0x00000020,
            fIsFlickerSlow  = 0x00000040,
            fIsPulse        = 0x00000080,
            fIsPulseSlow    = 0x00000100,
            fIsSpotLight    = 0x00000200,
            fIsSpotShadow   = 0x00000400
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        StringRecord ICON; //Large Icon Filename
        StringRecord MICO; //Small Icon Filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        ReqSubRecord<LIGHDATA> DATA; //Data
        OptSimpleFloatSubRecord<flt_0> FNAM; //Fade value
        OptSimpleSubRecord<FORMID> SNAM; //Sound

        LIGHRecord(unsigned char *_recData=NULL);
        LIGHRecord(LIGHRecord *srcRecord);
        ~LIGHRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDynamic();
        void   IsDynamic(bool value);
        bool   IsCanTake();
        void   IsCanTake(bool value);
        bool   IsTakeable();
        void   IsTakeable(bool value);
        bool   IsNegative();
        void   IsNegative(bool value);
        bool   IsFlickers();
        void   IsFlickers(bool value);
        bool   IsOffByDefault();
        void   IsOffByDefault(bool value);
        bool   IsFlickerSlow();
        void   IsFlickerSlow(bool value);
        bool   IsPulse();
        void   IsPulse(bool value);
        bool   IsPulseSlow();
        void   IsPulseSlow(bool value);
        bool   IsSpotLight();
        void   IsSpotLight(bool value);
        bool   IsSpotShadow();
        void   IsSpotShadow(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const LIGHRecord &other) const;
        bool operator !=(const LIGHRecord &other) const;
        bool equals(Record *other);
    };
}