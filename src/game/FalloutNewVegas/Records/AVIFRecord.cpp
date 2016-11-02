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
#include "..\..\Common.h"
#include "AVIFRecord.h"

namespace FNV
{
AVIFRecord::AVIFRecord(unsigned char *_recData):
    FNVRecord(_recData)
    {
    //
    }

AVIFRecord::AVIFRecord(AVIFRecord *srcRecord):
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
    DESC = srcRecord->DESC;
    ICON = srcRecord->ICON;
    MICO = srcRecord->MICO;
    ANAM = srcRecord->ANAM;
    return;
    }

AVIFRecord::~AVIFRecord()
    {
    //
    }

bool AVIFRecord::VisitFormIDs(FormIDOp &op)
    {
    if(!IsLoaded())
        return false;

    return op.Stop();
    }

uint32_t AVIFRecord::GetType()
    {
    return REV32(AVIF);
    }

char * AVIFRecord::GetStrType()
    {
    return "AVIF";
    }

int32_t AVIFRecord::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
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
            case REV32(DESC):
                DESC.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ICON):
                ICON.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(MICO):
                MICO.Read(buffer, subSize, CompressedOnDisk);
                break;
            case REV32(ANAM):
                ANAM.Read(buffer, subSize, CompressedOnDisk);
                break;
            default:
                UnrecognizedSubRecord(formID, subType, subSize, buffer, end_buffer);
                break;
            }
        };
    return 0;
    }

int32_t AVIFRecord::Unload()
    {
    IsChanged(false);
    IsLoaded(false);
    EDID.Unload();
    FULL.Unload();
    DESC.Unload();
    ICON.Unload();
    MICO.Unload();
    ANAM.Unload();
    return 1;
    }

int32_t AVIFRecord::WriteRecord(FileWriter &writer)
    {
    WRITE(EDID);
    WRITE(FULL);
    WRITE(DESC);
    WRITE(ICON);
    WRITE(MICO);
    WRITE(ANAM);

    return -1;
    }

bool AVIFRecord::operator ==(const AVIFRecord &other) const
    {
    return (EDID.equalsi(other.EDID) &&
            FULL.equals(other.FULL) &&
            DESC.equals(other.DESC) &&
            ICON.equalsi(other.ICON) &&
            MICO.equalsi(other.MICO) &&
            ANAM.equalsi(other.ANAM));
    }

bool AVIFRecord::operator !=(const AVIFRecord &other) const
    {
    return !(*this == other);
    }

bool AVIFRecord::equals(Record *other)
    {
    return *this == *(AVIFRecord *)other;
    }
}