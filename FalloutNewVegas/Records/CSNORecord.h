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
class CSNORecord : public FNVRecord //Casino
    {
    private:
        struct CSNODATA
            {
            FLOAT32 shufflePercent; //Decks % Before Shuffle
            FLOAT32 bjPayoutRatio; //BlackJack Payout Ratio
            UINT32  symbol1Stop, symbol2Stop,
                    symbol3Stop, symbol4Stop,
                    symbol5Stop, symbol6Stop,
                    symbolWStop; //Slot Reel Stops
            UINT32  numDecks; //Number of Decks
            UINT32  maxWinnings; //Max Winnings
            FORMID  currency; //Currency
            FORMID  winningsQuest; //Casino Winnings Quest
            UINT32  flags;

            CSNODATA();
            ~CSNODATA();

            bool operator ==(const CSNODATA &other) const;
            bool operator !=(const CSNODATA &other) const;
            };

        enum csnoFlags
            {
            fIsDealerStayOnSoft17 = 0x00000001
            };
    public:
        StringRecord EDID; //Editor ID
        StringRecord FULL; //Name
        OptSubRecord<CSNODATA> DATA; //Data
        StringRecord MODL1; //$1 Chip Model
        StringRecord MODL5; //$5 Chip Model
        StringRecord MODL10; //$10 Chip Model
        StringRecord MODL25; //$25 Chip Model
        StringRecord MODL100; //$100 Chip Model
        StringRecord MODL500; //$500 Chip Model
        StringRecord MODLRoulette; //Roulette Chip
        StringRecord MODL; //Slot Machine Model
        StringRecord MOD2; //Slot Machine Model (again?)
        StringRecord MOD3; //BlackJack Table Model
        StringRecord MOD4; //Roulette Table Model
        StringRecord ICON1; //Symbol 1 Slot Reel Texture
        StringRecord ICON2; //Symbol 2 Slot Reel Texture
        StringRecord ICON3; //Symbol 3 Slot Reel Texture
        StringRecord ICON4; //Symbol 4 Slot Reel Texture
        StringRecord ICON5; //Symbol 5 Slot Reel Texture
        StringRecord ICON6; //Symbol 6 Slot Reel Texture
        StringRecord ICONW; //Symbol W Slot Reel Texture
        StringRecord ICO21; //BlackJack Deck 1
        StringRecord ICO22; //BlackJack Deck 2
        StringRecord ICO23; //BlackJack Deck 3
        StringRecord ICO24; //BlackJack Deck 4

        CSNORecord(unsigned char *_recData=NULL);
        CSNORecord(CSNORecord *srcRecord);
        ~CSNORecord();

        bool   VisitFormIDs(FormIDOp &op);

        bool   IsDealerStayOnSoft17();
        void   IsDealerStayOnSoft17(bool value);
        bool   IsFlagMask(UINT32 Mask, bool Exact=false);
        void   SetFlagMask(UINT32 Mask);

        UINT32 GetFieldAttribute(DEFAULTED_FIELD_IDENTIFIERS, UINT32 WhichAttribute=0);
        void * GetField(DEFAULTED_FIELD_IDENTIFIERS, void **FieldValues=NULL);
        bool   SetField(DEFAULTED_FIELD_IDENTIFIERS, void *FieldValue=NULL, UINT32 ArraySize=0);
        void   DeleteField(DEFAULTED_FIELD_IDENTIFIERS);

        UINT32 GetType();
        STRING GetStrType();

        SINT32 ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk=false);
        SINT32 Unload();
        SINT32 WriteRecord(FileWriter &writer);

        bool operator ==(const CSNORecord &other) const;
        bool operator !=(const CSNORecord &other) const;
        bool equals(Record *other);
    };
}