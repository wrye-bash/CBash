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

namespace Ob
{
class REFRRecord : public Record
    {
    private:
        struct REFRXTEL
            {
            FORMID  destinationFid;
            GENPOSDATA destination;

            REFRXTEL();
            ~REFRXTEL();

            bool operator ==(const REFRXTEL &other) const;
            bool operator !=(const REFRXTEL &other) const;
            };

        struct REFRXLOC
            {
            uint8_t   level, unused1[3];
            FORMID  key;
            uint8_t   unused2[4], flags, unused3[3];

            REFRXLOC();
            ~REFRXLOC();

            bool operator ==(const REFRXLOC &other) const;
            bool operator !=(const REFRXLOC &other) const;
            };

        struct REFRXSED
            {
            union
                {
                uint32_t  seed;
                uint8_t   offset;
                };
            bool isOffset;

            REFRXSED();
            ~REFRXSED();

            void Write(FileWriter &writer);

            bool operator ==(const REFRXSED &other) const;
            bool operator !=(const REFRXSED &other) const;
            };

        struct REFRMAPMARKER
            {
            StringRecord FULL;
            ReqSubRecord<GENTNAM> TNAM;
            ReqSimpleSubRecord<uint8_t> FNAM;

            void Write(FileWriter &writer);

            bool operator ==(const REFRMAPMARKER &other) const;
            bool operator !=(const REFRMAPMARKER &other) const;
            };

        enum flagsFlags
            {
            fIsOppositeParent = 0x00000001
            };

        enum fnamFlags
            {
            fVisible     = 0x00000001,
            fCanTravelTo = 0x00000002
            };

        enum xactFlags
            {
            fUseDefault    = 0x00000001,
            fActivate      = 0x00000002,
            fOpen          = 0x00000004,
            fOpenByDefault = 0x00000008
            };

        enum xlocFlags
            {
            fLeveledLock = 0x00000004
            };

        enum markerTypeTypes
            {
            eMarkerNone      = 0,
            eCamp            = 1,
            eCave            = 2,
            eCity            = 3,
            eElvenRuin       = 4,
            eFortRuin        = 5,
            eMine            = 6,
            eLandmark        = 7,
            eTavern          = 8,
            eSettlement      = 9,
            eDaedricShrine   = 10,
            eOblivionGate    = 11,
            eUnknownDoorIcon = 12
            };

        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };

        struct REFRData
            {
            StringRecord EDID; //Editor ID
            ReqSimpleSubRecord<FORMID> NAME; //Base
            OptSubRecord<REFRXTEL> XTEL; //Teleport Destination
            SemiOptSubRecord<REFRXLOC> XLOC; //Lock Data
            OptSubRecord<GENXOWN> Ownership; //Owner
            OptSubRecord<GENXESP> XESP; //Enable Parent
            OptSimpleSubRecord<FORMID> XTRG; //Target
            SemiOptSubRecord<REFRXSED> XSED; //SpeedTree Seed
            OptSubRecord<GENXLOD> XLOD; //Distant LOD Data
            OptSimpleFloatSubRecord<flt_0> XCHG; //Charge
            OptSimpleSubRecord<int32_t> XHLT; //Health
            OptSubRecord<GENXPCI> XPCI; //Unknown
            OptSimpleSubRecord<int32_t> XLCM; //Level Modifier
            OptSimpleSubRecord<FORMID> XRTM; //Unknown
            OptSimpleSubRecord<uint32_t> XACT; //Action Flag
            OptSimpleSubRecord<int32_t> XCNT; //Count
            OptSubRecord<REFRMAPMARKER> Marker; //Map Marker Data
            //bool ONAM; //Open by Default, empty marker, written whenever fOpenByDefault is true
            OptSimpleFloatSubRecord<flt_1> XSCL; //scale
            OptSimpleSubRecord<uint8_t> XSOL; //Soul
            ReqSubRecord<GENPOSDATA> DATA; //Position/Rotation

            bool IsOpenByDefault();

            void Write(FileWriter &writer);

            bool operator ==(const REFRData &other) const;
            bool operator !=(const REFRData &other) const;
            };
    public:
        SemiOptSubRecord<REFRData> Data;

        REFRRecord(unsigned char *_recData=NULL);
        REFRRecord(REFRRecord *srcRecord);
        ~REFRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsOppositeParent();
        void   IsOppositeParent(bool value);
        bool   IsParentFlagMask(uint8_t Mask, bool Exact=false);
        void   SetParentFlagMask(uint8_t Mask);

        bool   IsVisible();
        void   IsVisible(bool value);
        bool   IsCanTravelTo();
        void   IsCanTravelTo(bool value);
        bool   IsMapFlagMask(uint8_t Mask, bool Exact=false);
        void   SetMapFlagMask(uint8_t Mask);

        bool   IsUseDefault();
        void   IsUseDefault(bool value);
        bool   IsActivate();
        void   IsActivate(bool value);
        bool   IsOpen();
        void   IsOpen(bool value);
        bool   IsOpenByDefault();
        void   IsOpenByDefault(bool value);
        bool   IsActionFlagMask(uint32_t Mask, bool Exact=false);
        void   SetActionFlagMask(uint32_t Mask);

        bool   IsLeveledLock();
        void   IsLeveledLock(bool value);
        bool   IsLockFlagMask(uint8_t Mask, bool Exact=false);
        void   SetLockFlagMask(uint8_t Mask);

        bool   IsNoMarker();
        void   IsNoMarker(bool value);
        bool   IsCamp();
        void   IsCamp(bool value);
        bool   IsCave();
        void   IsCave(bool value);
        bool   IsCity();
        void   IsCity(bool value);
        bool   IsElvenRuin();
        void   IsElvenRuin(bool value);
        bool   IsFortRuin();
        void   IsFortRuin(bool value);
        bool   IsMine();
        void   IsMine(bool value);
        bool   IsLandmark();
        void   IsLandmark(bool value);
        bool   IsTavern();
        void   IsTavern(bool value);
        bool   IsSettlement();
        void   IsSettlement(bool value);
        bool   IsDaedricShrine();
        void   IsDaedricShrine(bool value);
        bool   IsOblivionGate();
        void   IsOblivionGate(bool value);
        bool   IsUnknownDoorIcon();
        void   IsUnknownDoorIcon(bool value);
        bool   IsMarkerType(uint8_t Type);
        void   SetMarkerType(uint8_t Type);

        bool   IsNoSoul();
        void   IsNoSoul(bool value);
        bool   IsPettySoul();
        void   IsPettySoul(bool value);
        bool   IsLesserSoul();
        void   IsLesserSoul(bool value);
        bool   IsCommonSoul();
        void   IsCommonSoul(bool value);
        bool   IsGreaterSoul();
        void   IsGreaterSoul(bool value);
        bool   IsGrandSoul();
        void   IsGrandSoul(bool value);
        bool   IsSoul(uint8_t Type);
        void   SetSoul(uint8_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const REFRRecord &other) const;
        bool operator !=(const REFRRecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}