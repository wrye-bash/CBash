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
 *  Jacob "Lojack" Lojewski
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
#include "..\SkyrimCommon.h"
#include "common/GenericRecord.h"
#include "..\SkyrimChunks.h"

namespace Sk {

class ALCHRecord : public TES5Record // Ingestible
    {
        struct ALCHENIT //Effect Data
        {
            int32_t  value; //Value
            uint32_t  flags; //Flags
            FORMID  withdrawalEffect; //Withdrawal Effect
            float addictionChance; //Addiction Chance
            FORMID  consumeSound; //Sound - Consume

            ALCHENIT();
            ~ALCHENIT();

            bool operator ==(const ALCHENIT &other) const;
            bool operator !=(const ALCHENIT &other) const;
        };
        SIZE_CHECK(ALCHENIT, 20);

        enum flagsFlags
        {
            fIsNoAutoCalc = 0x00000001,
            fIsFood =       0x00000002,
            fIsMedicine =   0x00010000,
            fIsPoison =     0x00020000
        };

    public:
        StringRecord EDID; // Editor ID
        ReqSubRecord<GENOBND> OBND; // Object Bounds
        LStringRecord FULL; // Name
        OptCounted<OrderedPackedArray<FORMID>, uint32_t, REV32(KSIZ)> KWDA; // Keywords
        LStringRecord DESC; // Description
        OptSubRecord<FNVWORLDMODEL> MODL; // Model
        OptSubRecord<SKDESTRUCT> Destructable; // Destruction Data
        StringRecord ICON; // Large Icon
        StringRecord MICO; // Menu Icon
        OptSimpleSubRecord<FORMID> YNAM; // Pickup Sound
        OptSimpleSubRecord<FORMID> ZNAM; // Drop Sound
        OptSimpleSubRecord<FORMID> ETYP; // Equipment Type
        ReqSimpleFloatSubRecord<> DATA; // Weight
        ReqSubRecord<ALCHENIT> ENIT; // Effect Data
        UnorderedSparseArray<SKEffect *> Effects; //Effects

        ALCHRecord(unsigned char *_recData=NULL);
        ALCHRecord(ALCHRecord *srcRecord);
        ~ALCHRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoAutoCalc() const;
        void   IsNoAutoCalc(bool value);
        bool   IsFood() const;
        void   IsFood(bool value);
        bool   IsMedicine() const;
        void   IsMedicine(bool value);
        bool   IsPoison() const;
        void   IsPoison(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact = false) const;
        void   SetFlagMask(uint8_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const ALCHRecord &other) const;
        bool operator !=(const ALCHRecord &other) const;
        bool equals(Record *other);
    };

} // namespace Sk
