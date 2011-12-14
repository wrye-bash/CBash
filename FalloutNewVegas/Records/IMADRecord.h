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
class IMADRecord : public FNVRecord //Image Space Modifier
    {
    public:
        StringRecord EDID; //Editor ID
        RawRecord DNAM; //Unknown
        RawRecord BNAM; //Unknown
        RawRecord VNAM; //Unknown
        RawRecord TNAM; //Unknown
        RawRecord NAM3; //Unknown
        RawRecord RNAM; //Unknown
        RawRecord SNAM; //Unknown
        RawRecord UNAM; //Unknown
        RawRecord NAM1; //Unknown
        RawRecord NAM2; //Unknown
        RawRecord WNAM; //Unknown
        RawRecord XNAM; //Unknown
        RawRecord YNAM; //Unknown
        RawRecord NAM4; //Unknown
        RawRecord _00_IAD; //Unknown
        RawRecord _40_IAD; //Unknown
        RawRecord _01_IAD; //Unknown
        RawRecord _41_IAD; //Unknown
        RawRecord _02_IAD; //Unknown
        RawRecord _42_IAD; //Unknown
        RawRecord _03_IAD; //Unknown
        RawRecord _43_IAD; //Unknown
        RawRecord _04_IAD; //Unknown
        RawRecord _44_IAD; //Unknown
        RawRecord _05_IAD; //Unknown
        RawRecord _45_IAD; //Unknown
        RawRecord _06_IAD; //Unknown
        RawRecord _46_IAD; //Unknown
        RawRecord _07_IAD; //Unknown
        RawRecord _47_IAD; //Unknown
        RawRecord _08_IAD; //Unknown
        RawRecord _48_IAD; //Unknown
        RawRecord _09_IAD; //Unknown
        RawRecord _49_IAD; //Unknown
        RawRecord _0A_IAD; //Unknown
        RawRecord _4A_IAD; //Unknown
        RawRecord _0B_IAD; //Unknown
        RawRecord _4B_IAD; //Unknown
        RawRecord _0C_IAD; //Unknown
        RawRecord _4C_IAD; //Unknown
        RawRecord _0D_IAD; //Unknown
        RawRecord _4D_IAD; //Unknown
        RawRecord _0E_IAD; //Unknown
        RawRecord _4E_IAD; //Unknown
        RawRecord _0F_IAD; //Unknown
        RawRecord _4F_IAD; //Unknown
        RawRecord _10_IAD; //Unknown
        RawRecord _50_IAD; //Unknown
        RawRecord _11_IAD; //Unknown
        RawRecord _51_IAD; //Unknown
        RawRecord _12_IAD; //Unknown
        RawRecord _52_IAD; //Unknown
        RawRecord _13_IAD; //Unknown
        RawRecord _53_IAD; //Unknown
        RawRecord _14_IAD; //Unknown
        RawRecord _54_IAD; //Unknown
        OptSimpleSubRecord<FORMID> RDSD; //Sound - Intro
        OptSimpleSubRecord<FORMID> RDSI; //Sound - Outro

        IMADRecord(unsigned char *_recData=NULL);
        IMADRecord(IMADRecord *srcRecord);
        ~IMADRecord();

        bool   VisitFormIDs(FormIDOp &op);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, const UINT32 &recSize, bool CompressedOnDisk);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const IMADRecord &other) const;
        bool operator !=(const IMADRecord &other) const;
        bool equals(Record *other, RecordOp &read_self, RecordOp &read_other, EqualityOptions &options);
    };
}