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
#include "common/GenericRecord.h"
#include "..\SkyrimChunks.h"
#include "..\SkyrimCommon.h"


namespace Sk {

class COLLRecord : public TES5Record // Collision Layer
    {
    public:
        StringRecord EDID; // Editor ID
        LStringRecord DESC; // Description
        ReqSimpleSubRecord<uint32_t> BNAM; // ID
        ReqSubRecord<GENCNAM> FNAM; // Color
        ReqSimpleSubRecord<uint32_t, 0> GNAM; // Flags
        StringRecord MNAM; // Name
        // INTV - handled seperately
        OptCounted<OrderedPackedArray<FORMID>, uint32_t, REV32(INTV)> CNAM; // collidesWidth
        //OrderedPackedArray<FORMID> CNAM; // colliedsWith

        enum flagFlags
        {
            fIsTriggerVolume =   0x00000001,
            fIsSensor =          0x00000002,
            fIsNavmeshObstacle = 0x00000004
        };

        COLLRecord(unsigned char *_recData=NULL);
        COLLRecord(COLLRecord *srcRecord);
        ~COLLRecord();

        bool IsTriggerVolume() const;
        void IsTriggerVolume(bool value);
        bool IsSensor() const;
        void IsSensor(bool value);
        bool IsNavmeshObstacle() const;
        void IsNavmeshObstacle(bool value);
        bool IsFlagMask(uint32_t Mask, bool Exact=false);
        void SetFlagMask(uint32_t Mask);

        bool VisitFormIDs(FormIDOp &op);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const COLLRecord &other) const;
        bool operator !=(const COLLRecord &other) const;
        bool equals(Record *other);
    };

} // namespace Sk
