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
#include "Common.h"
#include "TES4Record.h"
#include "Skyrim\SkyrimCommon.h" // StringLookups
#include "zlib.h"

TES4Record::TES4HEDR::TES4HEDR(float _version, uint32_t _numRecords, uint32_t _nextObject):
    version(_version),
    numRecords(_numRecords),
    nextObject(_nextObject)
{
    //
}

TES4Record::TES4HEDR::~TES4HEDR()
{
    //
}

bool TES4Record::TES4HEDR::operator == (const TES4HEDR &other) const
{
    return (AlmostEqual(version, other.version, 2) &&
            numRecords == other.numRecords &&
            nextObject == other.nextObject
            );
}

bool TES4Record::TES4HEDR::operator != (const TES4HEDR &other) const
{
    return !(*this == other);
}

TES4Record::TES4Record(unsigned char *_recData):
    Record(_recData),
    formVersion(0),
    LookupStrings(NULL)
{
    memset(&versionControl2[0], 0x00, 2);
}

TES4Record::TES4Record(TES4Record *srcRecord):
    Record(),
    LookupStrings(NULL)
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

    HEDR = srcRecord->HEDR;
    OFST = srcRecord->OFST;
    DELE = srcRecord->DELE;
    CNAM = srcRecord->CNAM;
    SNAM = srcRecord->SNAM;
    MAST.resize(srcRecord->MAST.size());
    for(uint32_t x = 0; x < srcRecord->MAST.size();++x)
    {
        uint32_t size = (uint32_t)strlen(srcRecord->MAST[x]) + 1;
        MAST[x] = new char[size];
        memcpy(MAST[x], srcRecord->MAST[x], size);
    }
    ONAM = srcRecord->ONAM;
    SCRN = srcRecord->SCRN;
    INTV = srcRecord->INTV;
    INCC = srcRecord->INCC;
}

TES4Record::~TES4Record()
{
    delete LookupStrings;
}

bool TES4Record::VisitFormIDs(FormIDOp &op)
{
    if(!IsLoaded())
        return false;

    for(uint32_t x = 0; x < ONAM.value.size(); x++)
        op.Accept(ONAM.value[x]);

    return op.Stop();
}

bool TES4Record::IsESM() const
{
    return IsLoaded() ? (flags & fIsESM) != 0 : false;
}

void TES4Record::IsESM(bool value)
{
    if (!IsLoaded())
        return;
    SETBIT(flags, fIsESM, value);
}

bool TES4Record::IsLookupStrings() const
{
    // fIsTurnOffFire = LookupStrings
    return IsLoaded() ? (flags & fIsTurnOffFire) != 0 : false;
}

void TES4Record::IsLookupStrings(bool value)
{
    SETBIT(flags, fIsTurnOffFire, value);
}

void TES4Record::LoadStringLookups(char * FileName)
{
    if (LookupStrings != NULL)
        return;

    LookupStrings = new StringLookups;
    LookupStrings->Open(FileName);
}

uint32_t TES4Record::GetType()
{
    return REV32(TES4);
}

char * TES4Record::GetStrType()
{
    return "TES4";
}

int32_t TES4Record::ParseRecord(unsigned char *buffer, unsigned char *end_buffer, bool CompressedOnDisk)
{
    uint32_t subType = 0;
    uint32_t subSize = 0;
    while(buffer < end_buffer)
    {
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
        case REV32(HEDR):
            HEDR.Read(buffer, subSize);
            break;
        case REV32(CNAM):
            CNAM.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(SNAM):
            SNAM.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(MAST):
            MAST.push_back(new char[subSize]);
            memcpy(MAST.back(), buffer, subSize);
            buffer += subSize;
            break;
        case REV32(DATA):
            // Ignore
            buffer += subSize;
            break;
        case REV32(OFST):
            OFST.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(DELE):
            DELE.Read(buffer, subSize, CompressedOnDisk);
            break;
        /* Fallout: New Vegas---------------------------- */
        case REV32(ONAM):
            ONAM.Read(buffer, subSize);
            break;
        case REV32(SCRN):
            SCRN.Read(buffer, subSize, CompressedOnDisk);
            break;
        /* Skyrim --------------------------------------- */
        case REV32(INTV): // 4 bytes
            INTV.Read(buffer, subSize, CompressedOnDisk);
            break;
        case REV32(INCC):
            INCC.Read(buffer, subSize, CompressedOnDisk);
            break;
        default:
            //printer("FileName = %s\n", FileName);
            printer("  TES4: %08X - Unknown subType = %04x [%c%c%c%c]\n", formID, subType, (subType >> 0) & 0xFF, (subType >> 8) & 0xFF, (subType >> 16) & 0xFF, (subType >> 24) & 0xFF);
            printer("  Size = %i\n", subSize);
            printer("  CurPos = %04x\n\n", buffer - 6);
            buffer = end_buffer;
            break;
        }
    };
    return 0;
}

int32_t TES4Record::Unload()
{
    //TES4 should never be unloaded, so do nothing
    return 1;
}

int32_t TES4Record::WriteRecord(FileWriter &writer)
{
    uint8_t DATA[8] = {0};
    switch(whichGame)
    {
    case CB_OBLIVION:
        WRITE(HEDR);
        WRITE(OFST);
        WRITE(DELE);
        WRITE(CNAM);
        WRITE(SNAM);
        for(uint32_t p = 0; p < MAST.size(); p++)
        {
            writer.record_write_subrecord(REV32(MAST), MAST[p], (uint32_t)strlen(MAST[p]) + 1);
            writer.record_write_subrecord(REV32(DATA), &DATA[0], sizeof(DATA));
        }
        break;
    case CB_FALLOUT3:
        printer("TES4Record::WriteRecord: Error - Unable to write TES4 record. Fallout 3 support not yet implemented.\n");
        return -1;
    case CB_FALLOUT_NEW_VEGAS:
        WRITE(HEDR);
        WRITE(OFST);
        WRITE(DELE);
        WRITE(CNAM);
        WRITE(SNAM);
        for(uint32_t p = 0; p < MAST.size(); p++)
        {
            writer.record_write_subrecord(REV32(MAST), MAST[p], (uint32_t)strlen(MAST[p]) + 1);
            writer.record_write_subrecord(REV32(DATA), &DATA[0], sizeof(DATA));
        }
        WRITE(ONAM);
        WRITE(SCRN);
        break;
    case CB_SKYRIM:
        WRITE(HEDR);
        WRITE(OFST);
        WRITE(DELE);
        WRITE(CNAM);
        WRITE(SNAM);
        for(uint32_t p = 0; p < MAST.size(); p++)
        {
            writer.record_write_subrecord(REV32(MAST), MAST[p], (uint32_t)strlen(MAST[p]) + 1);
            writer.record_write_subrecord(REV32(DATA), &DATA[0], sizeof(DATA));
        }
        WRITE(ONAM);
        WRITE(SCRN);
        WRITE(INTV);
        WRITE(INCC);
        break;
    }

    return -1;
}

uint32_t TES4Record::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
{
    IsCompressed(false);
    uint32_t recSize = 0;
    uint32_t recType = GetType();

    collapser.Accept(formID);

    VisitFormIDs(collapser);
    WriteRecord(writer);
    recSize = writer.record_size();

    writer.file_write(&recType, 4);
    writer.file_write(&recSize, 4);
    writer.file_write(&flags, 4);
    writer.file_write(&formID, 4);
    writer.file_write(&flagsUnk, 4);

    if(whichGame == CB_FALLOUT_NEW_VEGAS)
    {
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
    }
    else if(whichGame == CB_SKYRIM)
    {
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
    }

    writer.record_flush();

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();

    if(whichGame == CB_FALLOUT_NEW_VEGAS)
        return recSize + 24;
    else if(whichGame == CB_SKYRIM)
        return recSize + 24;
    else
        return recSize + 20;
}

bool TES4Record::operator ==(const TES4Record &other) const
{
    if (OFST == other.OFST &&
        DELE == other.DELE &&
        CNAM.equals(other.CNAM) &&
        SNAM.equals(other.SNAM) &&
        formVersion == other.formVersion &&
        versionControl2[0] == other.versionControl2[0] &&
        versionControl2[1] == other.versionControl2[1] &&
        SCRN == other.SCRN &&
        MAST.size() == other.MAST.size() &&
        ONAM == other.ONAM &&
        INTV == other.INTV &&
        INCC == other.INCC)
    {
        //Record order kinda sorta but doesn't really matter on masters, so equality testing is easy
        //The order determines the mod index of all formIDs in the mod file
        //If both records have the same masters in the same orders, the formIDs will have the same master indexing
        //If both records have the same masters in different orders, the formIDs will have different indexing but be logically equivalent
        //The ordering has no effect on load order in game or in the editor
        for(uint32_t x = 0; x < MAST.size(); ++x)
            if(icmps(MAST[x], other.MAST[x]) != 0)
                return false;
        return true;
    }

    return false;
}

bool TES4Record::operator !=(const TES4Record &other) const
{
    return !(*this == other);
}

bool TES4Record::equals(Record *other)
{
    return *this == *(TES4Record *)other;
}
