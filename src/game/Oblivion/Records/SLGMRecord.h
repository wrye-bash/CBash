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
class SLGMRecord : public Record
    {
    private:
        enum eSoulType
            {
            eNone    = 0,
            ePetty   = 1,
            eLesser  = 2,
            eCommon  = 3,
            eGreater = 4,
            eGrand   = 5
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<GENMODEL> MODL; //Model
        StringRecord ICON; //Icon filename
        OptSimpleSubRecord<FORMID> SCRI; //Script
        ReqSubRecord<GENVALUEWEIGHT> DATA; //Data
        ReqSimpleSubRecord<uint8_t> SOUL; //Contained Soul
        ReqSimpleSubRecord<uint8_t, 1> SLCP; //Maximum Capacity

        SLGMRecord(unsigned char *_recData=NULL);
        SLGMRecord(SLGMRecord *srcRecord);
        ~SLGMRecord();

        bool   VisitFormIDs(FormIDOp &op);

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

        bool   IsNoCapacity();
        void   IsNoCapacity(bool value);
        bool   IsPettyCapacity();
        void   IsPettyCapacity(bool value);
        bool   IsLesserCapacity();
        void   IsLesserCapacity(bool value);
        bool   IsCommonCapacity();
        void   IsCommonCapacity(bool value);
        bool   IsGreaterCapacity();
        void   IsGreaterCapacity(bool value);
        bool   IsGrandCapacity();
        void   IsGrandCapacity(bool value);
        bool   IsCapacity(uint8_t Type);
        void   SetCapacity(uint8_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const SLGMRecord &other) const;
        bool operator !=(const SLGMRecord &other) const;
        bool equals(Record *other);
    };
}