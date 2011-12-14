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
class CSTYRecord : public Record //Combat Style
    {
    private:
        struct CSTYCSTD //Standard
            {
            UINT8   dodgeChance, lrChance, unused1[2];
            FLOAT32 lrTimerMin, lrTimerMax, forTimerMin, forTimerMax, backTimerMin,
                    backTimerMax, idleTimerMin, idleTimerMax;
            UINT8   blkChance, atkChance, unused2[2];
            FLOAT32 atkBRecoil, atkBUnc, atkBh2h;
            UINT8   pAtkChance, unused3[3];
            FLOAT32 pAtkBRecoil, pAtkBUnc;
            UINT8   pAtkNormal, pAtkFor, pAtkBack, pAtkL, pAtkR, unused4[3];
            FLOAT32 holdTimerMin, holdTimerMax;
            UINT8   flagsA, acroDodge, unused5[2];
            FLOAT32 rMultOpt, rMultMax, mDistance, rDistance, buffStand, rStand, groupStand;
            UINT8   rushChance, unused6[3];
            FLOAT32 rushMult;
            UINT32  flagsB;

            CSTYCSTD();
            ~CSTYCSTD();

            bool operator ==(const CSTYCSTD &other) const;
            bool operator !=(const CSTYCSTD &other) const;
            };

        struct CSTYCSAD //Advanced
            {
            FLOAT32 dodgeFMult, dodgeFBase, encSBase, encSMult, dodgeAtkMult,
                    dodgeNAtkMult, dodgeBAtkMult, dodgeBNAtkMult,
                    dodgeFAtkMult, dodgeFNAtkMult, blockMult, blockBase,
                    blockAtkMult, blockNAtkMult, atkMult, atkBase, atkAtkMult,
                    atkNAtkMult, atkBlockMult, pAtkFBase, pAtkFMult;

            CSTYCSAD();
            ~CSTYCSAD();

            bool operator ==(const CSTYCSAD &other) const;
            bool operator !=(const CSTYCSAD &other) const;
            };

        enum flagsAFlags
            {
            fIsUseAdvanced        = 0x00000001,
            fIsUseChanceForAttack = 0x00000002,
            fIsIgnoreAllies       = 0x00000004,
            fIsWillYield          = 0x00000008,
            fIsRejectsYields      = 0x00000010,
            fIsFleeingDisabled    = 0x00000020,
            fIsPrefersRanged      = 0x00000040,
            fIsMeleeAlertOK       = 0x00000080
            };

        enum flagsBFlags
            {
            fIsDoNotAcquire = 0x00000001 //OBSE, ignored?
            };

    public:
        StringRecord EDID; //Editor ID
        ReqSubRecord<CSTYCSTD> CSTD; //Standard
        SemiOptSubRecord<CSTYCSAD> CSAD; //Advanced

        CSTYRecord(unsigned char *_recData=NULL);
        CSTYRecord(CSTYRecord *srcRecord);
        ~CSTYRecord();

        bool   IsUseAdvanced();
        void   IsUseAdvanced(bool value);
        bool   IsUseChanceForAttack();
        void   IsUseChanceForAttack(bool value);
        bool   IsIgnoreAllies();
        void   IsIgnoreAllies(bool value);
        bool   IsWillYield();
        void   IsWillYield(bool value);
        bool   IsRejectsYields();
        void   IsRejectsYields(bool value);
        bool   IsFleeingDisabled();
        void   IsFleeingDisabled(bool value);
        bool   IsPrefersRanged();
        void   IsPrefersRanged(bool value);
        bool   IsMeleeAlertOK();
        void   IsMeleeAlertOK(bool value);
        bool   IsFlagAMask(UINT8 Mask, bool Exact=false);
        void   SetFlagAMask(UINT8 Mask);

        bool   IsDoNotAcquire();
        void   IsDoNotAcquire(bool value);
        bool   IsFlagBMask(UINT32 Mask, bool Exact=false);
        void   SetFlagBMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CSTYRecord &other) const;
        bool operator !=(const CSTYRecord &other) const;
        bool equals(Record *other);
    };
}