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
#include "common/Common.h"
#include "common/GenericRecord.h"
#include "../FNVRecord.h"

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
        RawRecord _00_; //Unknown
        RawRecord _40_; //Unknown
        RawRecord _01_; //Unknown
        RawRecord _41_; //Unknown
        RawRecord _02_; //Unknown
        RawRecord _42_; //Unknown
        RawRecord _03_; //Unknown
        RawRecord _43_; //Unknown
        RawRecord _04_; //Unknown
        RawRecord _44_; //Unknown
        RawRecord _05_; //Unknown
        RawRecord _45_; //Unknown
        RawRecord _06_; //Unknown
        RawRecord _46_; //Unknown
        RawRecord _07_; //Unknown
        RawRecord _47_; //Unknown
        RawRecord _08_; //Unknown
        RawRecord _48_; //Unknown
        RawRecord _09_; //Unknown
        RawRecord _49_; //Unknown
        RawRecord _0A_; //Unknown
        RawRecord _4A_; //Unknown
        RawRecord _0B_; //Unknown
        RawRecord _4B_; //Unknown
        RawRecord _0C_; //Unknown
        RawRecord _4C_; //Unknown
        RawRecord _0D_; //Unknown
        RawRecord _4D_; //Unknown
        RawRecord _0E_; //Unknown
        RawRecord _4E_; //Unknown
        RawRecord _0F_; //Unknown
        RawRecord _4F_; //Unknown
        RawRecord _10_; //Unknown
        RawRecord _50_; //Unknown
        RawRecord _11_; //Unknown
        RawRecord _51_; //Unknown
        RawRecord _12_; //Unknown
        RawRecord _52_; //Unknown
        RawRecord _13_; //Unknown
        RawRecord _53_; //Unknown
        RawRecord _14_; //Unknown
        RawRecord _54_; //Unknown
        OptSimpleSubRecord<FORMID> RDSD; //Sound - Intro
        OptSimpleSubRecord<FORMID> RDSI; //Sound - Outro

        IMADRecord(unsigned char *_recData=NULL);
        IMADRecord(IMADRecord *srcRecord);
        ~IMADRecord();

        bool   VisitFormIDs(FormIDOp &op);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const IMADRecord &other) const;
        bool operator !=(const IMADRecord &other) const;
        bool equals(Record *other);
    };
}