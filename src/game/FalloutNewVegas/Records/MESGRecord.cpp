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
#include "MESGRecord.h"

namespace FNV
{
bool MESGRecord::MESGButton::operator ==(const MESGButton &other) const
    {
    return (ITXT.equals(other.ITXT) &&
            CTDA == other.CTDA
            );
    }

bool MESGRecord::MESGButton::operator !=(const MESGButton &other) const
    {
    return !(*this == other);
    }

MESGRecord::MESGRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

MESGRecord::MESGRecord(MESGRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    FULL = srcRecord->FULL;
    INAM = srcRecord->INAM;
    //NAM0 = srcRecord->NAM0;
    //NAM1 = srcRecord->NAM1;
    //NAM2 = srcRecord->NAM2;
    //NAM3 = srcRecord->NAM3;
    //NAM4 = srcRecord->NAM4;
    //NAM5 = srcRecord->NAM5;
    //NAM6 = srcRecord->NAM6;
    //NAM7 = srcRecord->NAM7;
    //NAM8 = srcRecord->NAM8;
    //NAM9 = srcRecord->NAM9;
    DNAM = srcRecord->DNAM;
    TNAM = srcRecord->TNAM;
    Buttons = srcRecord->Buttons;

    return;
    }

MESGRecord::~MESGRecord()
    {
    //
    }

bool MESGRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    if(INAM.IsLoaded())
        op.Accept(INAM.value);
    for(uint32_t ButtonIndex = 0; ButtonIndex < Buttons.size(); ButtonIndex++)
        {
        for (uint32_t ConditionIndex = 0; ConditionIndex < Buttons[ButtonIndex].CTDA.value.size(); ConditionIndex++)
            Buttons[ButtonIndex].CTDA.value[ConditionIndex].VisitFormIDs(op);
        }

    return op.Stop();
    }

uint32_t MESGRecord::GetType()
    {
    return REV32(MESG);
    }

char * MESGRecord::GetStrType()
    {
    return "MESG";
    }

int32_t MESGRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(FULL):
                FULL.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(INAM):
                INAM.Read(buffer, subSize);
                break;
            case REV32(NAM0):
                //NAM0.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM1):
                //NAM1.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM2):
                //NAM2.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM3):
                //NAM3.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM4):
                //NAM4.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM5):
                //NAM5.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM6):
                //NAM6.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM7):
                //NAM7.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM8):
                //NAM8.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(NAM9):
                //NAM9.Read(buffer, subSize); //FILL IN MANUALLY
                break;
            case REV32(DNAM):
                DNAM.Read(buffer, subSize);
                break;
            case REV32(TNAM):
                TNAM.Read(buffer, subSize);
                break;
            case REV32(ITXT):
                {
                MESGButton button;
                button.ITXT.Read(buffer, subSize, CompressedOnDisk);
                Buttons.push_back(button);
                break;
                }
            case REV32(CTDA):
                if (Buttons.size() > 0)
                    Buttons[Buttons.size() - 1].CTDA.Read(buffer, subSize);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t MESGRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    DESC.Unload();
    FULL.Unload();
    INAM.Unload();
    //NAM0.Unload(); //FILL IN MANUALLY
    //NAM1.Unload(); //FILL IN MANUALLY
    //NAM2.Unload(); //FILL IN MANUALLY
    //NAM3.Unload(); //FILL IN MANUALLY
    //NAM4.Unload(); //FILL IN MANUALLY
    //NAM5.Unload(); //FILL IN MANUALLY
    //NAM6.Unload(); //FILL IN MANUALLY
    //NAM7.Unload(); //FILL IN MANUALLY
    //NAM8.Unload(); //FILL IN MANUALLY
    //NAM9.Unload(); //FILL IN MANUALLY
    DNAM.Unload();
    TNAM.Unload();
    Buttons.clear();
    return 1;
    }

int32_t MESGRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(DESC);
    WRITE(FULL);
    WRITE(INAM);

    //if(NAM0.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM0), NAM0.value, NAM0.GetSize());

    //if(NAM1.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM1), NAM1.value, NAM1.GetSize());

    //if(NAM2.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM2), NAM2.value, NAM2.GetSize());

    //if(NAM3.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM3), NAM3.value, NAM3.GetSize());

    //if(NAM4.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM4), NAM4.value, NAM4.GetSize());

    //if(NAM5.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM5), NAM5.value, NAM5.GetSize());

    //if(NAM6.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM6), NAM6.value, NAM6.GetSize());

    //if(NAM7.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM7), NAM7.value, NAM7.GetSize());

    //if(NAM8.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM8), NAM8.value, NAM8.GetSize());

    //if(NAM9.IsLoaded()) //FILL IN MANUALLY
        //SaveHandler.writeSubRecord(REV32(NAM9), NAM9.value, NAM9.GetSize());
    WRITE(DNAM);
    WRITE(TNAM);
    for(uint32_t ListIndex = 0; ListIndex < Buttons.size(); ListIndex++)
    {
        Buttons[ListIndex].ITXT.Write(REV32(ITXT), writer);
        Buttons[ListIndex].CTDA.Write(REV32(CTDA), writer);
    }

    return -1;
    }

bool MESGRecord::operator ==(const MESGRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            DESC.equals(other.DESC) &&
            FULL.equals(other.FULL) &&
            INAM == other.INAM &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            //Empty &&
            DNAM == other.DNAM &&
            TNAM == other.TNAM &&
            Buttons == other.Buttons);
    }

bool MESGRecord::operator !=(const MESGRecord &other) const
    {
    return !(*this == other);
    }

bool MESGRecord::equals(Record *other)
    {
    return *this == *(MESGRecord *)other;
    }
}