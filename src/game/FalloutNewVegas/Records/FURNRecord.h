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

namespace FNV
{
class FURNRecord : public FNVRecord //Furniture
    {
    private:
        enum flagsFlags
            {
            fIsAnim01    = 0x00000001,
            fIsAnim02    = 0x00000002,
            fIsAnim03    = 0x00000004,
            fIsAnim04    = 0x00000008,
            fIsAnim05    = 0x00000010,
            fIsAnim06    = 0x00000020,
            fIsAnim07    = 0x00000040,
            fIsAnim08    = 0x00000080,
            fIsAnim09    = 0x00000100,
            fIsAnim10    = 0x00000200,
            fIsAnim11    = 0x00000400,
            fIsAnim12    = 0x00000800,
            fIsAnim13    = 0x00001000,
            fIsAnim14    = 0x00002000,
            fIsAnim15    = 0x00004000,
            fIsAnim16    = 0x00008000,
            fIsAnim17    = 0x00010000,
            fIsAnim18    = 0x00020000,
            fIsAnim19    = 0x00040000,
            fIsAnim20    = 0x00080000,
            fIsAnim21    = 0x00100000,
            fIsAnim22    = 0x00200000,
            fIsAnim23    = 0x00400000,
            fIsAnim24    = 0x00800000,
            fIsAnim25    = 0x01000000,
            fIsAnim26    = 0x02000000,
            fIsAnim27    = 0x04000000,
            fIsAnim28    = 0x08000000,
            fIsAnim29    = 0x10000000,
            fIsAnim30    = 0x20000000,
            fIsSitAnim   = 0x40000000,
            fIsSleepAnim = 0x80000000
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSimpleSubRecord<FORMID> SCRI; //Script
        OptSubRecord<GENDESTRUCT> Destructable; //Destructable
        ReqSimpleSubRecord<uint32_t> MNAM; //Marker Flags

        FURNRecord(unsigned char *_recData=NULL);
        FURNRecord(FURNRecord *srcRecord);
        ~FURNRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsAnim01();
        void   IsAnim01(bool value);
        bool   IsAnim02();
        void   IsAnim02(bool value);
        bool   IsAnim03();
        void   IsAnim03(bool value);
        bool   IsAnim04();
        void   IsAnim04(bool value);
        bool   IsAnim05();
        void   IsAnim05(bool value);
        bool   IsAnim06();
        void   IsAnim06(bool value);
        bool   IsAnim07();
        void   IsAnim07(bool value);
        bool   IsAnim08();
        void   IsAnim08(bool value);
        bool   IsAnim09();
        void   IsAnim09(bool value);
        bool   IsAnim10();
        void   IsAnim10(bool value);
        bool   IsAnim11();
        void   IsAnim11(bool value);
        bool   IsAnim12();
        void   IsAnim12(bool value);
        bool   IsAnim13();
        void   IsAnim13(bool value);
        bool   IsAnim14();
        void   IsAnim14(bool value);
        bool   IsAnim15();
        void   IsAnim15(bool value);
        bool   IsAnim16();
        void   IsAnim16(bool value);
        bool   IsAnim17();
        void   IsAnim17(bool value);
        bool   IsAnim18();
        void   IsAnim18(bool value);
        bool   IsAnim19();
        void   IsAnim19(bool value);
        bool   IsAnim20();
        void   IsAnim20(bool value);
        bool   IsAnim21();
        void   IsAnim21(bool value);
        bool   IsAnim22();
        void   IsAnim22(bool value);
        bool   IsAnim23();
        void   IsAnim23(bool value);
        bool   IsAnim24();
        void   IsAnim24(bool value);
        bool   IsAnim25();
        void   IsAnim25(bool value);
        bool   IsAnim26();
        void   IsAnim26(bool value);
        bool   IsAnim27();
        void   IsAnim27(bool value);
        bool   IsAnim28();
        void   IsAnim28(bool value);
        bool   IsAnim29();
        void   IsAnim29(bool value);
        bool   IsAnim30();
        void   IsAnim30(bool value);
        bool   IsSitAnim();
        void   IsSitAnim(bool value);
        bool   IsSleepAnim();
        void   IsSleepAnim(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const FURNRecord &other) const;
        bool operator !=(const FURNRecord &other) const;
        bool equals(Record *other);
    };
}