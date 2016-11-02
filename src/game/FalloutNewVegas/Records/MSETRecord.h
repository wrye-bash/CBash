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

namespace FNV
{
class MSETRecord : public FNVRecord //Media Set
    {
    private:
        enum typeTypes
            {
            eNone   = -1,
            eBattle = 0,
            eLocation,
            eDungeon,
            eIncidential
            };

        enum flagsFlags
            {
            fIsDayOuter    = 0x01,
            fIsDayMiddle   = 0x02,
            fIsDayInner    = 0x04,
            fIsNightOuter  = 0x08,
            fIsNightMiddle = 0x10,
            fIsNightInner  = 0x20
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSimpleSubRecord<uint32_t> NAM1; //Type
        StringRecord NAM2; //Loop (B) / Battle (D) / Day Outer (L)
        StringRecord NAM3; //Explore (D) / Day Middle (L)
        StringRecord NAM4; //Suspense (D) / Day Inner (L)
        StringRecord NAM5; //Night Outer (L)
        StringRecord NAM6; //Night Middle (L)
        StringRecord NAM7; //Night Inner (L)
        OptSimpleFloatSubRecord<flt_0> NAM8; //Loop dB (B) / Battle dB (D) / Day Outer dB (L)
        OptSimpleFloatSubRecord<flt_0> NAM9; //Explore dB (D) / Day Middle dB (L)
        OptSimpleFloatSubRecord<flt_0> NAM0; //Suspense dB (D) / Day Inner dB (L)
        OptSimpleFloatSubRecord<flt_0> ANAM; //Night Outer dB (L)
        OptSimpleFloatSubRecord<flt_0> BNAM; //Night Middle dB (L)
        OptSimpleFloatSubRecord<flt_0> CNAM; //Night Inner dB (L)
        OptSimpleFloatSubRecord<flt_0> JNAM; //Day Outer Boundary % (L)
        OptSimpleFloatSubRecord<flt_0> KNAM; //Day Middle Boundary % (L)
        OptSimpleFloatSubRecord<flt_0> LNAM; //Day Inner Boundary % (L)
        OptSimpleFloatSubRecord<flt_0> MNAM; //Night Outer Boundary % (L)
        OptSimpleFloatSubRecord<flt_0> NNAM; //Night Middle Boundary % (L)
        OptSimpleFloatSubRecord<flt_0> ONAM; //Night Inner Boundary % (L)
        OptSimpleSubRecord<uint8_t> PNAM; //Enable Flags
        OptSimpleFloatSubRecord<flt_0> DNAM; //Wait Time (B) / Minimum Time On (D,L) / Daytime Min (I)
        OptSimpleFloatSubRecord<flt_0> ENAM; //Loop Fade Out (B) / Looping/Random Crossfade Overlap (D,L) / Nighttime Min (I)
        OptSimpleFloatSubRecord<flt_0> FNAM; //Recovery Time (B) / Layer Crossfade Time (D,L) / Daytime Max (I)
        OptSimpleFloatSubRecord<flt_0> GNAM; //Nighttime Max (I)
        OptSimpleSubRecord<FORMID> HNAM; //Intro (B,D) / Daytime (I)
        OptSimpleSubRecord<FORMID> INAM; //Outro (B,D) / Nighttime (I)
        RawRecord DATA; //Unknown

        MSETRecord(unsigned char *_recData=NULL);
        MSETRecord(MSETRecord *srcRecord);
        ~MSETRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDayOuter();
        void   IsDayOuter(bool value);
        bool   IsDayMiddle();
        void   IsDayMiddle(bool value);
        bool   IsDayInner();
        void   IsDayInner(bool value);
        bool   IsNightOuter();
        void   IsNightOuter(bool value);
        bool   IsNightMiddle();
        void   IsNightMiddle(bool value);
        bool   IsNightInner();
        void   IsNightInner(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsBattle();
        void   IsBattle(bool value);
        bool   IsLocation();
        void   IsLocation(bool value);
        bool   IsDungeon();
        void   IsDungeon(bool value);
        bool   IsIncidential();
        void   IsIncidential(bool value);
        bool   IsType(uint32_t Type);
        void   SetType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk = false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const MSETRecord &other) const;
        bool operator !=(const MSETRecord &other) const;
        bool equals(Record *other);
    };
}