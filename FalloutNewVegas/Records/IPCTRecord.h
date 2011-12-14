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
class IPCTRecord : public FNVRecord //Impact
    {
    private:
        struct IPCTDATA
            {
            FLOAT32 duration; //Effect - Duration
            UINT32  orientation; //Effect - Orientation
            FLOAT32 angleThreshold, placementRadius; //Angle Threshold, Placement Radius
            UINT32  soundLevel, flags; //Sound Level, Flags

            IPCTDATA();
            ~IPCTDATA();

            bool operator ==(const IPCTDATA &other) const;
            bool operator !=(const IPCTDATA &other) const;
            };

        enum flagsFlags
            {
            fIsNoDecalData = 0x00000001
            };

        enum DODTFlags
            {
            fIsParallax      = 0x00000001,
            fIsAlphaBlending = 0x00000002,
            fIsAlphaTesting  = 0x00000004
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSubRecord<IPCTDATA> DATA; //Data
        OptSubRecord<GENDODT> DODT; //Decal Data
        OptSimpleSubRecord<FORMID> DNAM; //Texture Set
        OptSimpleSubRecord<FORMID> SNAM; //Sound 1
        OptSimpleSubRecord<FORMID> NAM1; //Sound 2

        IPCTRecord(unsigned char *_recData=NULL);
        IPCTRecord(IPCTRecord *srcRecord);
        ~IPCTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNoDecalData();
        void   IsNoDecalData(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        bool   IsObjectParallax();
        void   IsObjectParallax(bool value);
        bool   IsObjectAlphaBlending();
        void   IsObjectAlphaBlending(bool value);
        bool   IsObjectAlphaTesting();
        void   IsObjectAlphaTesting(bool value);
        bool   IsObjectFlagMask(UINT8 Mask, bool Exact=false);
        void   SetObjectFlagMask(UINT8 Mask);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(UINT8 Type);
        void   SetSoundLevelType(UINT8 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const IPCTRecord &other) const;
        bool operator !=(const IPCTRecord &other) const;
        bool equals(Record *other);
    };
}