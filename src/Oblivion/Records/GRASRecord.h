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
class GRASRecord : public Record //Grass
    {
    private:
        struct GRASDATA
            {
            UINT8   density, minSlope, maxSlope, unused1;
            UINT16  waterDistance;
            UINT8   unused2[2];
            UINT32  waterOp;
            FLOAT32 posRange, heightRange, colorRange, wavePeriod;
            UINT8   flags, unused3[3];

            GRASDATA();
            ~GRASDATA();

            bool operator ==(const GRASDATA &other) const;
            bool operator !=(const GRASDATA &other) const;
            };

        enum flagsFlags
            {
            fIsVLighting = 0x00000001,
            fIsUScaling  = 0x00000002,
            fIsFitSlope  = 0x00000004
            };

    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<GENMODEL> MODL; //Model
        ReqSubRecord<GRASDATA> DATA; //Data

        GRASRecord(unsigned char *_recData=NULL);
        GRASRecord(GRASRecord *srcRecord);
        ~GRASRecord();

        bool   IsVLighting();
        void   IsVLighting(bool value);
        bool   IsUScaling();
        void   IsUScaling(bool value);
        bool   IsFitSlope();
        void   IsFitSlope(bool value);
        bool   IsFlagMask(UINT8 Mask, bool Exact=false);
        void   SetFlagMask(UINT8 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const GRASRecord &other) const;
        bool operator !=(const GRASRecord &other) const;
        bool equals(Record *other);
    };
}