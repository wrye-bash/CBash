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
#include "common/Common.h"
#include "CSNORecord.h"

namespace FNV
{
CSNORecord::CSNODATA::CSNODATA():
    shufflePercent(0.0),
    bjPayoutRatio(0.0),
    symbol1Stop(0),
    symbol2Stop(0),
    symbol3Stop(0),
    symbol4Stop(0),
    symbol5Stop(0),
    symbol6Stop(0),
    symbolWStop(0),
    numDecks(0),
    maxWinnings(0),
    currency(0),
    winningsQuest(0),
    flags(0)
    {
    //
    }

CSNORecord::CSNODATA::~CSNODATA()
    {
    //
    }

bool CSNORecord::CSNODATA::operator ==(const CSNODATA &other) const
    {
    return (AlmostEqual(shufflePercent, other.shufflePercent, 2) &&
            AlmostEqual(bjPayoutRatio, other.bjPayoutRatio, 2) &&
            symbol1Stop == other.symbol1Stop &&
            symbol2Stop == other.symbol2Stop &&
            symbol3Stop == other.symbol3Stop &&
            symbol4Stop == other.symbol4Stop &&
            symbol5Stop == other.symbol5Stop &&
            symbol6Stop == other.symbol6Stop &&
            symbolWStop == other.symbolWStop &&
            numDecks == other.numDecks &&
            maxWinnings == other.maxWinnings &&
            currency == other.currency &&
            winningsQuest == other.winningsQuest &&
            flags == other.flags
            );
    }

bool CSNORecord::CSNODATA::operator !=(const CSNODATA &other) const
    {
    return !(*this == other);
    }

CSNORecord::CSNORecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

CSNORecord::CSNORecord(CSNORecord *srcRecord):
    FNVRecord()
    {
    if(srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    if(!srcRecord->IsChanged())
        return;

    EDID = srcRecord->EDID;
    FULL = srcRecord->FULL;
    DATA = srcRecord->DATA;
    MODL1 = srcRecord->MODL1;
    MODL5 = srcRecord->MODL5;
    MODL10 = srcRecord->MODL10;
    MODL25 = srcRecord->MODL25;
    MODL100 = srcRecord->MODL100;
    MODL500 = srcRecord->MODL500;
    MODL = srcRecord->MODL;
    MOD2 = srcRecord->MOD2;
    MOD3 = srcRecord->MOD3;
    MOD4 = srcRecord->MOD4;
    ICON1 = srcRecord->ICON1;
    ICON2 = srcRecord->ICON2;
    ICON3 = srcRecord->ICON3;
    ICON4 = srcRecord->ICON4;
    ICON5 = srcRecord->ICON5;
    ICON6 = srcRecord->ICON6;
    ICONW = srcRecord->ICONW;
    ICO21 = srcRecord->ICO21;
    ICO22 = srcRecord->ICO22;
    ICO23 = srcRecord->ICO23;
    ICO24 = srcRecord->ICO24;

    return;
    }

CSNORecord::~CSNORecord()
    {
    //
    }

bool CSNORecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if (DATA.IsLoaded())
        {
        op.Accept(DATA->currency);
        op.Accept(DATA->winningsQuest);
        }

    return op.Stop();
    }

bool CSNORecord::IsDealerStayOnSoft17()
    {
    if (!DATA.IsLoaded()) return false;
    return (DATA->flags & fIsDealerStayOnSoft17) != 0;
    }

void CSNORecord::IsDealerStayOnSoft17(bool value)
    {
    if (!DATA.IsLoaded()) return;
    SETBIT(DATA->flags, fIsDealerStayOnSoft17, value);
    }

bool CSNORecord::IsFlagMask(uint32_t Mask, bool Exact)
    {
    if (!DATA.IsLoaded()) return false;
    return Exact ? ((DATA->flags & Mask) == Mask) : (DATA->flags & Mask) != 0;
    }

void CSNORecord::SetFlagMask(uint32_t Mask)
    {
    DATA.Load();
    DATA->flags = Mask;
    }

uint32_t CSNORecord::GetType()
    {
    return REV32(CSNO);
    }

char * CSNORecord::GetStrType()
    {
    return "CSNO";
    }

int32_t CSNORecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
    {
    uint32_t subType = 0;
    uint32_t subSize = 0;
    while(buffer < end_buffer){
        subType = *(uint32_t *)buffer;
        buffer += 4;
        switch(subType)
            {
            case REV32(XXXX):
                buffer += 2;
                subSize = *(uint32_t *)buffer;
                buffer += 4;
                subType = *(uint32_t *)buffer;
                buffer += 6;
                break;
            default:
                subSize = *(uint16_t *)buffer;
                buffer += 2;
                break;
            }
        switch(subType)
            {
            case REV32(EDID):
                EDID.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(DATA):
                DATA.Read(buffer, subSize);
                break;
            case REV32(MODL):
                MODL.Load();
                MODL.Read(buffer, subSize, CompressedOnDisk);
                break;
            // TODO: handle MODL records better
            //case REV32(MODL):
            //    MODL.Read(buffer, subSize);
            //    break;
            case REV32(MOD2):
                MOD2.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD3):
                MOD3.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MOD4):
                MOD4.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON1.Load();
                ICON1.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICO2):
                ICON2.Load();
                ICON2.Read(buffer, subSize, CompressedOnDisk);
                break;
            // TODO: The rest of the ICO* subrecords
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t CSNORecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DATA.Unload();
    MODL1.Unload();
    MODL5.Unload();
    MODL10.Unload();
    MODL25.Unload();
    MODL100.Unload();
    MODL500.Unload();
    MODL.Unload();
    MOD2.Unload();
    MOD3.Unload();
    MOD4.Unload();
    ICON1.Unload();
    ICON2.Unload();
    ICON3.Unload();
    ICON4.Unload();
    ICON5.Unload();
    ICON6.Unload();
    ICONW.Unload();
    ICO21.Unload();
    ICO22.Unload();
    ICO23.Unload();
    ICO24.Unload();
    return 1;
    }

int32_t CSNORecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DATA);

    WRITE(MODL);
    WRITE(MOD2);
    WRITE(MOD3);
    WRITE(MOD4);

    // TODO: Fix this!  Much more needs writing

    return -1;
    }

bool CSNORecord::operator ==(const CSNORecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DATA == other.DATA &&
            MODL.equalsi(other.MODL) &&
            MOD2.equalsi(other.MOD2) &&
            MOD3.equalsi(other.MOD3) &&
            MOD4.equalsi(other.MOD4) &&
            ICON1.equals(other.ICON1) &&
            ICON2.equals(other.ICON2));
    // TODO: Rest of subrecords need checks too!
    }

bool CSNORecord::operator !=(const CSNORecord &other) const
    {
    return !(*this == other);
    }

bool CSNORecord::equals(Record *other)
    {
    return *this == *(CSNORecord *)other;
    }
}