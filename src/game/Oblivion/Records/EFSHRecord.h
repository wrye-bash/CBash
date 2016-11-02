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

namespace Ob
{
class EFSHRecord : public Record //Effect Shader
    {
    private:
        struct EFSHDATA
            {
            uint8_t   flags, unused1[3];
            uint32_t  memSBlend, memBlendOp, memZFunc;
            GENCLR  fill;
            float fillAIn, fillAFull, fillAOut, fillAPRatio, fillAAmp,
                    fillAFreq, fillAnimSpdU, fillAnimSpdV, edgeOff;
            GENCLR  edge;
            float edgeAIn, edgeAFull, edgeAOut, edgeAPRatio, edgeAAmp,
                    edgeAFreq,  fillAFRatio, edgeAFRatio;
            uint32_t  memDBlend, partSBlend, partBlendOp, partZFunc, partDBlend;
            float partBUp, partBFull, partBDown, partBFRatio, partBPRatio, partLTime,
                    partLDelta, partNSpd, partNAcc, partVel1, partVel2, partVel3,
                    partAcc1, partAcc2, partAcc3, partKey1, partKey2, partKey1Time,
                    partKey2Time;
            GENCLR  key1;
            GENCLR  key2;
            GENCLR  key3;
            float key1A, key2A, key3A, key1Time, key2Time, key3Time;

            EFSHDATA();
            ~EFSHDATA();

            bool operator ==(const EFSHDATA &other) const;
            bool operator !=(const EFSHDATA &other) const;
            };

        enum flagsFlags
            {
            fIsNoMemShader  = 0x00000001,
            fIsNoPartShader = 0x00000008,
            fIsEdgeInverse  = 0x00000010,
            fIsMemSkinOnly  = 0x00000020
            };

    public:
        StringRecord EDID; //Editor ID
        StringRecord ICON; //Fill Texture
        StringRecord ICO2; //Particle Shader Texture
        ReqSubRecord<EFSHDATA> DATA; //Data

        EFSHRecord(unsigned char *_recData=NULL);
        EFSHRecord(EFSHRecord *srcRecord);
        ~EFSHRecord();

        bool   IsNoMemShader();
        void   IsNoMemShader(bool value);
        bool   IsNoMembraneShader();
        void   IsNoMembraneShader(bool value);
        bool   IsNoPartShader();
        void   IsNoPartShader(bool value);
        bool   IsNoParticleShader();
        void   IsNoParticleShader(bool value);
        bool   IsEdgeInverse();
        void   IsEdgeInverse(bool value);
        bool   IsEdgeEffectInverse();
        void   IsEdgeEffectInverse(bool value);
        bool   IsMemSkinOnly();
        void   IsMemSkinOnly(bool value);
        bool   IsMembraneShaderSkinOnly();
        void   IsMembraneShaderSkinOnly(bool value);
        bool   IsFlagMask(uint8_t Mask, bool Exact=false);
        void   SetFlagMask(uint8_t Mask);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const EFSHRecord &other) const;
        bool operator !=(const EFSHRecord &other) const;
        bool equals(Record *other);
    };
}