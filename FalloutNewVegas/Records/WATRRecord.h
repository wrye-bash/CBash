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
class WATRRecord : public FNVRecord //Water
    {
    private:
        struct WATRDNAM
            {
            FLOAT32 unknown1, unknown2, unknown3, unknown4,
                    sunPower, reflectAmt, fresnelAmt;
            UINT8   unused1[4];
            FLOAT32 fogNear, fogFar;
            GENCLR  shallow;
            GENCLR  deep;
            GENCLR  refl;
            UINT8   unused2[4];
            FLOAT32 rainForce, rainVelocity, rainFalloff, rainDampner,
                    dispSize, dispForce, dispVelocity, dispFalloff,
                    dispDampner, rainSize, normalsNoiseScale, noise1Direction,
                    noise2Direction, noise3Direction, noise1Speed,
                    noise2Speed, noise3Speed, normalsFalloffStart,
                    normalsFalloffEnd, fogAmt, normalsUVScale, underFogAmt,
                    underFogNear, underFogFar, distAmt, shininess,
                    hdrMult, lightRadius, lightBright, noise1UVScale,
                    noise2UVScale, noise3UVScale;

            //Below aren't on older DATA, and also a few DNAM
            FLOAT32 noise1AmpScale, noise2AmpScale, noise3AmpScale;

            WATRDNAM();
            ~WATRDNAM();

            bool operator ==(const WATRDNAM &other) const;
            bool operator !=(const WATRDNAM &other) const;
            };

        struct WATRGNAM
            {
            FORMID  dayWater, nightWater, underWater;

            WATRGNAM();
            ~WATRGNAM();

            bool operator ==(const WATRGNAM &other) const;
            bool operator !=(const WATRGNAM &other) const;
            };

        enum flagsFlags
            {
            fIsCausesDamage = 0x01,
            fIsReflective   = 0x02
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        StringRecord NNAM; //Noise Map
        ReqSimpleSubRecord<UINT8, 75> ANAM; //opacity
        ReqSimpleSubRecord<UINT8> FNAM; //Flags
        StringRecord MNAM; //Material ID
        OptSimpleSubRecord<FORMID> SNAM; //Sound
        OptSimpleSubRecord<FORMID> XNAM; //Actor Effect
        ReqSimpleSubRecord<UINT16> DATA; //Damage (May be 186 size struct (older format))
        ReqSubRecord<WATRDNAM> DNAM; //Visual Data (May be listed as DATA an old format, auto upgrade to DNAM on read)
        ReqSubRecord<WATRGNAM> GNAM; //Related Waters (Unused)

        WATRRecord(unsigned char *_recData=NULL);
        WATRRecord(WATRRecord *srcRecord);
        ~WATRRecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsCausesDmg();
        void   IsCausesDmg(bool value);
        bool   IsCausesDamage();
        void   IsCausesDamage(bool value);
        bool   IsReflective();
        void   IsReflective(bool value);
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

        bool operator ==(const WATRRecord &other) const;
        bool operator !=(const WATRRecord &other) const;
        bool equals(Record *other);
    };
}