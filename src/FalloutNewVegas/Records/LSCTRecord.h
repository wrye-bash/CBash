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
class LSCTRecord : public FNVRecord //Load Screen Type
    {
    private:
        struct LSCTDATA
            {
            UINT32  screenType; //Type
            //Data 1
            UINT32  x, y, width, height;
            FLOAT32 orientation;
            UINT32  font1;
            FLOAT32 font1Red, font1Green, font1Blue;
            UINT32  alignmentType;
            UINT8   unknown1[20];
            //Data 2
            UINT32  font2;
            FLOAT32 font2Red, font2Green, font2Blue;
            UINT8   unknown2[4];
            UINT32  stats;

            LSCTDATA();
            ~LSCTDATA();

            bool operator ==(const LSCTDATA &other) const;
            bool operator !=(const LSCTDATA &other) const;
            };

        enum eScreenTypeTypes
            {
            eNone       = 0,
            eXPProgress = 1,
            eObjective  = 2,
            eTip        = 3,
            eStats      = 4
            };
    public:
        StringRecord EDID; //Editor ID
        OptSubRecord<LSCTDATA> DATA; //Data

        LSCTRecord(unsigned char *_recData=NULL);
        LSCTRecord(LSCTRecord *srcRecord);
        ~LSCTRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsNone();
        bool   IsXPProgress();
        bool   IsObjective();
        bool   IsTip();
        bool   IsStats();
        bool   IsType(UINT32 Type);
        void   SetType(UINT32 Type);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const LSCTRecord &other) const;
        bool operator !=(const LSCTRecord &other) const;
        bool equals(Record *other);
    };
}