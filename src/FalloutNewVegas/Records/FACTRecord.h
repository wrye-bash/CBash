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
struct sortRNAM;

class FACTRecord : public FNVRecord //Faction
    {
    private:
        struct FACTDATA //older format is a single UINT8 flag. It updates itself without any special action
            {
            UINT16  flags;
            UINT8   unused1[2];

            FACTDATA();
            ~FACTDATA();

            bool operator ==(const FACTDATA &other) const;
            bool operator !=(const FACTDATA &other) const;
            };

        struct FACTRNAM //Rank
            {
            ReqSimpleSubRecord<SINT32> RNAM; //Rank#
            StringRecord MNAM, FNAM, INAM; //Male, Female, Insignia (Unused)

            void Write(FileWriter &writer);

            bool operator ==(const FACTRNAM &other) const;
            bool operator !=(const FACTRNAM &other) const;
            };

        enum flagsFlags
            {
            fIsHiddenFromPC  = 0x0001,
            fIsEvil          = 0x0002,
            fIsSpecialCombat = 0x0004,
            fIsTrackCrime    = 0x0100,
            fIsAllowSell     = 0x0200
            };

        friend sortRNAM;

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OrderedSparseArray<FNVXNAM *> XNAM; //Relations, not sure if record order matters
        ReqSubRecord<FACTDATA> DATA; //Data
        SemiOptSimpleFloatSubRecord<flt_1> CNAM; //Unused
        OrderedSparseArray<FACTRNAM *, sortRNAM> RNAM; //Ranks
        OptSimpleSubRecord<FORMID> WMI1; //Reputation

        FACTRecord(unsigned char *_recData=NULL);
        FACTRecord(FACTRecord *srcRecord);
        ~FACTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsHiddenFromPC();
        void   IsHiddenFromPC(bool value);
        bool   IsEvil();
        void   IsEvil(bool value);
        bool   IsSpecialCombat();
        void   IsSpecialCombat(bool value);
        bool   IsTrackCrime();
        void   IsTrackCrime(bool value);
        bool   IsAllowSell();
        void   IsAllowSell(bool value);
        bool   IsFlagMask(UINT16 Mask, bool Exact=false);
        void   SetFlagMask(UINT16 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const FACTRecord &other) const;
        bool operator !=(const FACTRecord &other) const;
        bool equals(Record *other);
    };

struct sortRNAM
    {
    bool operator()(const FACTRecord::FACTRNAM *lhs, const FACTRecord::FACTRNAM *rhs) const;
    };
}