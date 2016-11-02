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
class EXPLRecord : public FNVRecord //Explosion
    {
    private:
        struct EXPLDATA
            {
            float force, damage, radius;
            FORMID  light, sound1;
            uint32_t  flags;
            float ISRadius;
            FORMID  impactDataSet, sound2;
            float radLevel, radTime, radRadius;
            uint32_t  soundLevel;

            EXPLDATA();
            ~EXPLDATA();

            bool operator ==(const EXPLDATA &other) const;
            bool operator !=(const EXPLDATA &other) const;
            };

        enum flagsFlags
            {
            fIsUnknown1                   = 0x00000001,
            fIsAlwaysUsesWorldOrientation = 0x00000002,
            fIsAlwaysKnockDown            = 0x00000004,
            fIsFormulaKnockDown           = 0x00000008,
            fIsIgnoreLOS                  = 0x00000010,
            fIsPushExplosionSourceRefOnly = 0x00000020,
            fIsIgnoreImageSpaceSwap       = 0x00000040
            };

        enum soundLevelTypes
            {
            eLoud = 0,
            eNormal,
            eSilent
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<GENOBND> OBND; //Object Bounds
        StringRecord FULL; //Name
        OptSubRecord<FNVMODEL> MODL; //Model
        OptSimpleSubRecord<FORMID> EITM; //Object Effect
        OptSimpleSubRecord<FORMID> MNAM; //Image Space Modifier
        ReqSubRecord<EXPLDATA> DATA; //Data
        OptSimpleSubRecord<FORMID> INAM; //Placed Impact Object

        EXPLRecord(unsigned char *_recData=NULL);
        EXPLRecord(EXPLRecord *srcRecord);
        ~EXPLRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsUnknown1();
        void   IsUnknown1(bool value);
        bool   IsAlwaysUsesWorldOrientation();
        void   IsAlwaysUsesWorldOrientation(bool value);
        bool   IsAlwaysKnockDown();
        void   IsAlwaysKnockDown(bool value);
        bool   IsFormulaKnockDown();
        void   IsFormulaKnockDown(bool value);
        bool   IsIgnoreLOS();
        void   IsIgnoreLOS(bool value);
        bool   IsPushExplosionSourceRefOnly();
        void   IsPushExplosionSourceRefOnly(bool value);
        bool   IsIgnoreImageSpaceSwap();
        void   IsIgnoreImageSpaceSwap(bool value);
        bool   IsFlagMask(uint32_t Mask, bool Exact=false);
        void   SetFlagMask(uint32_t Mask);

        bool   IsLoud();
        void   IsLoud(bool value);
        bool   IsNormal();
        void   IsNormal(bool value);
        bool   IsSilent();
        void   IsSilent(bool value);
        bool   IsSoundLevelType(uint8_t Type);
        void   SetSoundLevelType(uint8_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const EXPLRecord &other) const;
        bool operator !=(const EXPLRecord &other) const;
        bool equals(Record *other);
    };
}