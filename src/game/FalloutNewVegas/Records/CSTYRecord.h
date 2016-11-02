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
class CSTYRecord : public FNVRecord //Combat Style
    {
    private:
        struct CSTYCSTD //Advanced Standard
            {
            uint8_t   dodgeChance, lrChance, unused1[2];
            float lrTimerMin, lrTimerMax, forTimerMin, forTimerMax, backTimerMin,
                    backTimerMax, idleTimerMin, idleTimerMax;
            uint8_t   blkChance, atkChance, unused2[2];
            float atkBRecoil, atkBUnc, atkBh2h;
            uint8_t   pAtkChance, unused3[3];
            float pAtkBRecoil, pAtkBUnc;
            uint8_t   pAtkNormal, pAtkFor, pAtkBack, pAtkL, pAtkR, unused4[3];
            float holdTimerMin, holdTimerMax;
            uint16_t  flags;
            uint8_t   unused5[2], acroDodge, rushChance, unused6[2];
            float rushMult;

            CSTYCSTD();
            ~CSTYCSTD();

            bool operator ==(const CSTYCSTD &other) const;
            bool operator !=(const CSTYCSTD &other) const;
            };

        struct CSTYCSAD //Advanced - Advanced
            {
            float dodgeFMult, dodgeFBase, encSBase, encSMult, dodgeAtkMult,
                    dodgeNAtkMult, dodgeBAtkMult, dodgeBNAtkMult,
                    dodgeFAtkMult, dodgeFNAtkMult, blockMult, blockBase,
                    blockAtkMult, blockNAtkMult, atkMult, atkBase, atkAtkMult,
                    atkNAtkMult, atkBlockMult, pAtkFBase, pAtkFMult;

            CSTYCSAD();
            ~CSTYCSAD();

            bool operator ==(const CSTYCSAD &other) const;
            bool operator !=(const CSTYCSAD &other) const;
            };

        struct CSTYCSSD //Simple
            {
            float coverRadius, coverChance, waitTimerMin, waitTimerMax,
                    waitFireTimerMin, waitFireTimerMax, fireTimerMin,
                    fireTimerMax, rangedRangeMultMin;
            uint8_t   unused1[4];
            uint32_t  weaponRestrictions;
            float rangedRangeMultMax, targetMaxFOV, combatRadius,
                    semiAutoFireDelayMultMin, semiAutoFireDelayMultMax;

            CSTYCSSD();
            ~CSTYCSSD();

            bool operator ==(const CSTYCSSD &other) const;
            bool operator !=(const CSTYCSSD &other) const;
            };

        enum flagsFlags
            {
            fIsUseChanceForAttack      = 0x00000001,
            fIsMeleeAlertOK            = 0x00000002,
            fIsFleeForSurvival         = 0x00000004,
            fIsIgnoreThreats           = 0x00000010,
            fIsIgnoreDamagingSelf      = 0x00000020,
            fIsIgnoreDamagingGroup     = 0x00000040,
            fIsIgnoreDamagingSpectator = 0x00000080,
            fIsNoUseStealthboy         = 0x00000100
            };

        enum restrictionTypes
            {
            eNone       = 0,
            eMeleeOnly  = 1,
            eRangedOnly = 2
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<CSTYCSTD> CSTD; //Advanced Standard
        ReqSubRecord<CSTYCSAD> CSAD; //Advanced - Advanced
        ReqSubRecord<CSTYCSSD> CSSD; //Simple

        CSTYRecord(unsigned char *_recData=NULL);
        CSTYRecord(CSTYRecord *srcRecord);
        ~CSTYRecord();

        bool   IsUseChanceForAttack();
        void   IsUseChanceForAttack(bool value);
        bool   IsMeleeAlertOK();
        void   IsMeleeAlertOK(bool value);
        bool   IsFleeForSurvival();
        void   IsFleeForSurvival(bool value);
        bool   IsIgnoreThreats();
        void   IsIgnoreThreats(bool value);
        bool   IsIgnoreDamagingSelf();
        void   IsIgnoreDamagingSelf(bool value);
        bool   IsIgnoreDamagingGroup();
        void   IsIgnoreDamagingGroup(bool value);
        bool   IsIgnoreDamagingSpectator();
        void   IsIgnoreDamagingSpectator(bool value);
        bool   IsNoUseStealthboy();
        void   IsNoUseStealthboy(bool value);
        bool   IsFlagMask(uint16_t Mask, bool Exact=false);
        void   SetFlagMask(uint16_t Mask);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsMeleeOnly();
        void   IsMeleeOnly(bool value);
        bool   IsRangedOnly();
        void   IsRangedOnly(bool value);
        bool   IsType(uint32_t Type);
        void   SetType(uint32_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const CSTYRecord &other) const;
        bool operator !=(const CSTYRecord &other) const;
        bool equals(Record *other);
    };
}