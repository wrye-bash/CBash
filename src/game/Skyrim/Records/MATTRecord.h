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
 * Ethatron
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

namespace Sk
{
class MATTRecord : public TES5Record //Material Type
    {
    struct MATTCNAM // Havok display color
    {
        float red, green, blue;

        MATTCNAM();
        ~MATTCNAM();

        bool operator == (const MATTCNAM &other) const;
        bool operator != (const MATTCNAM &other) const;
    };
    SIZE_CHECK(MATTCNAM, 12);

    public:
        StringRecord EDID; // Editor ID
        ReqSimpleSubRecord<FORMID> PNAM; // Material Parent
        StringRecord MNAM; // Material Name
        ReqSubRecord<MATTCNAM> CNAM; // Havok Display Color
        ReqSimpleFloatSubRecord<flt_0> BNAM; // Bouyancy
        ReqSimpleSubRecord<uint32_t> FNAM; // Flags
        ReqSimpleSubRecord<FORMID> HNAM; //Havok Impact Data Set (IPDS)

        enum flagFlags
        {
            fIsStairMaterial = 0x01,
            fIsArrowsStick = 0x02
        };

        bool IsStairMaterial() const;
        void IsStairMaterial(bool value);
        bool IsArrowsStick() const;
        void IsArrowsStick(bool value);
        bool IsFlagMask(uint32_t Mask, bool Exact=false);
        void SetFlagMask(uint32_t Mask);

        MATTRecord(unsigned char *_recData=NULL);
        MATTRecord(MATTRecord *srcRecord);
        ~MATTRecord();

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const MATTRecord &other) const;
        bool operator !=(const MATTRecord &other) const;
        bool equals(Record *other);
    };
}