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
class INFORecord : public FNVRecord //Dialog response
    {
    private:
        struct INFODATA
            {
            uint8_t   dialType; //Type
            uint8_t   nextSpeaker; //Next Speaker
            uint16_t  flags;

            INFODATA();
            ~INFODATA();

            bool operator ==(const INFODATA &other) const;
            bool operator !=(const INFODATA &other) const;
            };

        struct INFOTRDT //Response Data
            {
            uint32_t  emotionType; //Emotion Type
            int32_t  emotionValue; //Emotion Value
            uint8_t   unused1[4], responseNum, unused2[3]; //Unused, Response Number, Unused
            FORMID  sound; //Sound
            uint8_t   flags, unused3[3]; //Flags, Unused

            INFOTRDT();
            ~INFOTRDT();

            bool operator ==(const INFOTRDT &other) const;
            bool operator !=(const INFOTRDT &other) const;
            };

        struct INFOResponse
            {
            ReqSubRecord<INFOTRDT> TRDT; //Response Data
            StringRecord NAM1; //Response Text (REQ)
            StringRecord NAM2; //Script Notes (REQ)
            StringRecord NAM3; //Edits (REQ)
            OptSimpleSubRecord<FORMID> SNAM; //Speaker Animation
            OptSimpleSubRecord<FORMID> LNAM; //Listener Animation

            enum eEmotionType
                {
                eNeutral  = 0,
                eAnger    = 1,
                eDisgust  = 2,
                eFear     = 3,
                eSad      = 4,
                eHappy    = 5,
                eSurprise = 6,
                ePained   = 7
                };

            enum flagsFlags
                {
                fIsUseEmotionAnim = 0x01
                };

            bool   IsNeutral();
            void   IsNeutral(bool value);
            bool   IsAnger();
            void   IsAnger(bool value);
            bool   IsDisgust();
            void   IsDisgust(bool value);
            bool   IsFear();
            void   IsFear(bool value);
            bool   IsSad();
            void   IsSad(bool value);
            bool   IsHappy();
            void   IsHappy(bool value);
            bool   IsSurprise();
            void   IsSurprise(bool value);
            bool   IsPained();
            void   IsPained(bool value);
            bool   IsType(uint32_t Type);
            void   SetType(uint32_t Type);

            bool   IsUseEmotionAnim();
            void   IsUseEmotionAnim(bool value);
            bool   IsFlagMask(uint8_t Mask, bool Exact=false);
            void   SetFlagMask(uint8_t Mask);

            void Write(FileWriter &writer);

            bool operator ==(const INFOResponse &other) const;
            bool operator !=(const INFOResponse &other) const;
            };

        enum eDialogType
            {
            eTopic        = 0,
            eConversation = 1,
            eCombat       = 2,
            ePersuasion   = 3,
            eDetection    = 4,
            eService      = 5,
            eMisc         = 6,
            eRadio        = 7
            };

        enum eSpeakerType
            {
            eTarget = 0,
            eSelf   = 1,
            eEither = 2
            };

        enum flagsFlags
            {
            fIsGoodbye         = 0x0001,
            fIsRandom          = 0x0002,
            fIsSayOnce         = 0x0004,
            fIsRunImmediately  = 0x0008,
            fIsInfoRefusal     = 0x0010,
            fIsRandomEnd       = 0x0020,
            fIsRunForRumors    = 0x0040,
            fIsSpeechChallenge = 0x0080,
            fIsSayOnceADay     = 0x0100,
            fIsAlwaysDarken    = 0x0200
            };

        enum eChallengeLevelType
            {
            eNone = 0,
            eVeryEasy,
            eEasy,
            eAverage,
            eHard,
            eVeryHard
            };

        enum schrFlags
            {
            fIsEnabled = 0x0001
            };

        enum scriptTypeTypes
            {
            eObject = 0x0000,
            eQuest  = 0x0001,
            eEffect = 0x0100
            };

    public:
        ReqSubRecord<INFODATA> DATA; //INFO Data
        ReqSimpleSubRecord<FORMID> QSTI; //Quest
        OptSimpleSubRecord<FORMID> TPIC; //Topic
        OptSimpleSubRecord<FORMID> PNAM; //Previous INFO
        UnorderedSparseArray<FORMID> NAME; //Topics
        UnorderedSparseArray<INFOResponse *> Responses; //Responses
        OrderedSparseArray<FNVCTDA *> CTDA; //Conditions

        UnorderedSparseArray<FORMID> TCLT; //Choices
        UnorderedSparseArray<FORMID> TCLF; //Link From
        UnorderedSparseArray<FORMID> TCFU; //Unknown
        ReqSubRecord<FNVSCHR> BeginSCHR; //Basic Script Data
        RawRecord BeginSCDA; //Unknown (Script Header?)
        NonNullStringRecord BeginSCTX; //Script Source
        OrderedSparseArray<GENVARS *, sortVARS> BeginVARS; //Local Variables
        OrderedSparseArray<GENSCR_ *> BeginSCR_; //References
        //NEXT empty marker (REQ)
        ReqSubRecord<FNVSCHR> EndSCHR; //Basic Script Data
        RawRecord EndSCDA; //Unknown (Script Header?)
        NonNullStringRecord EndSCTX; //Script Source
        OrderedSparseArray<GENVARS *, sortVARS> EndVARS; //Local Variables
        OrderedSparseArray<GENSCR_ *> EndSCR_; //References

        OptSimpleSubRecord<FORMID> SNDD; //Unused
        StringRecord RNAM; //Prompt
        OptSimpleSubRecord<FORMID> ANAM; //Speaker
        OptSimpleSubRecord<FORMID> KNAM; //ActorValue/Perk
        OptSimpleSubRecord<uint32_t> DNAM; //Speech Challenge

        INFORecord(unsigned char *_recData=NULL);
        INFORecord(INFORecord *srcRecord);
        ~INFORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsGoodbye();
        void   IsGoodbye(bool value);
        bool   IsRandom();
        void   IsRandom(bool value);
        bool   IsSayOnce();
        void   IsSayOnce(bool value);
        bool   IsRunImmediately();
        void   IsRunImmediately(bool value);
        bool   IsInfoRefusal();
        void   IsInfoRefusal(bool value);
        bool   IsRandomEnd();
        void   IsRandomEnd(bool value);
        bool   IsRunForRumors();
        void   IsRunForRumors(bool value);
        bool   IsSpeechChallenge();
        void   IsSpeechChallenge(bool value);
        bool   IsSayOnceADay();
        void   IsSayOnceADay(bool value);
        bool   IsAlwaysDarken();
        void   IsAlwaysDarken(bool value);
        bool   IsFlagMask(uint16_t Mask, bool Exact=false);
        void   SetFlagMask(uint16_t Mask);

        bool   IsBeginScriptEnabled();
        void   IsBeginScriptEnabled(bool value);
        bool   IsBeginScriptFlagMask(uint16_t Mask, bool Exact=false);
        void   SetBeginScriptFlagMask(uint16_t Mask);

        bool   IsEndScriptEnabled();
        void   IsEndScriptEnabled(bool value);
        bool   IsEndScriptFlagMask(uint16_t Mask, bool Exact=false);
        void   SetEndScriptFlagMask(uint16_t Mask);

        bool   IsTopic();
        void   IsTopic(bool value);
        bool   IsConversation();
        void   IsConversation(bool value);
        bool   IsCombat();
        void   IsCombat(bool value);
        bool   IsPersuasion();
        void   IsPersuasion(bool value);
        bool   IsDetection();
        void   IsDetection(bool value);
        bool   IsService();
        void   IsService(bool value);
        bool   IsMisc();
        void   IsMisc(bool value);
        bool   IsRadio();
        void   IsRadio(bool value);
        bool   IsDialogType(uint8_t Type);
        void   SetDialogType(uint8_t Type);

        bool   IsTarget();
        void   IsTarget(bool value);
        bool   IsSelf();
        void   IsSelf(bool value);
        bool   IsEither();
        void   IsEither(bool value);
        bool   IsSpeakerType(uint8_t Type);
        void   SetSpeakerType(uint8_t Type);

        bool   IsNone();
        void   IsNone(bool value);
        bool   IsVeryEasy();
        void   IsVeryEasy(bool value);
        bool   IsEasy();
        void   IsEasy(bool value);
        bool   IsAverage();
        void   IsAverage(bool value);
        bool   IsHard();
        void   IsHard(bool value);
        bool   IsVeryHard();
        void   IsVeryHard(bool value);
        bool   IsDifficultyType(uint8_t Type);
        void   SetDifficultyType(uint8_t Type);

        bool   IsBeginObject();
        void   IsBeginObject(bool value);
        bool   IsBeginQuest();
        void   IsBeginQuest(bool value);
        bool   IsBeginEffect();
        void   IsBeginEffect(bool value);
        bool   IsBeginType(uint16_t Type);
        void   SetBeginType(uint16_t Type);

        bool   IsEndObject();
        void   IsEndObject(bool value);
        bool   IsEndQuest();
        void   IsEndQuest(bool value);
        bool   IsEndEffect();
        void   IsEndEffect(bool value);
        bool   IsEndType(uint16_t Type);
        void   SetEndType(uint16_t Type);

        uint32_t GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, uint32_t WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, uint32_t ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        uint32_t GetType();
        char * GetStrType();

        int32_t ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        int32_t Unload();
        int32_t WriteRecord(FileWriter &writer);

        bool operator ==(const INFORecord &other) const;
        bool operator !=(const INFORecord &other) const;
        bool equals(Record *other);
        bool deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records);
    };
}