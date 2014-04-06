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
#include "GenericRecord.h"
#include "zlib/zlib.h"

RecordOp::RecordOp():
    count(0),
    stop(false),
    result(false)
    {
    //
    }

RecordOp::~RecordOp()
    {
    //
    }

bool RecordOp::Accept(Record *&curRecord)
    {
    return false;
    }

UINT32 RecordOp::GetCount()
    {
    return count;
    }

void RecordOp::ResetCount()
    {
    count = 0;
    }

bool RecordOp::Stop()
    {
    return stop;
    }

RecordProcessor::RecordProcessor(ModFile *_curModFile, FormIDHandlerClass &_FormIDHandler, const ModFlags &_Flags, boost::unordered_set<UINT32> &_UsedFormIDs):
    curModFile(_curModFile),
    filter_records(),
    filter_wspaces(),
    filter_inclusive(false),
    NewTypes(_FormIDHandler.NewTypes),
    ExpandedIndex(_FormIDHandler.ExpandedIndex),
    expander(_FormIDHandler.ExpandTable, _FormIDHandler.FileStart, _FormIDHandler.FileEnd),
    Flags(_Flags),
    UsedFormIDs(_UsedFormIDs),
    EmptyGRUPs(_FormIDHandler.EmptyGRUPs),
    OrphanedRecords(_FormIDHandler.OrphanedRecords),
    IsSkipNewRecords(_Flags.IsSkipNewRecords),
    IsSkipAllRecords(_Flags.IsSkipAllRecords),
    IsKeepRecords(!_Flags.IsSkipAllRecords),
    IsTrackNewTypes(_Flags.IsTrackNewTypes),
    IsAddMasters(_Flags.IsAddMasters)
    {
    //
    }

RecordProcessor::~RecordProcessor()
    {
    //
    }

Record::Record(unsigned char *_recData):
    flags(0),
    formID(0),
    flagsUnk(0),
    recData(_recData),
    Parent(NULL),
    CBash_Flags(0)
    {
    //If a buffer is provided, the record isn't loaded
    // until the record is read
    //Otherwise, it's a new record and is considered loaded
    IsLoaded(_recData == NULL);
    }

Record::~Record()
    {
    //
    }

void * Record::GetParent() const
    {
    return Parent;
    }

bool Record::SetParent(void *_Parent, bool IsMod)
    {
    if(Parent != NULL)
        return false;

    SETBIT(CBash_Flags, _fIsParentMod, IsMod);
    Parent = _Parent;
    return true;
    }

bool Record::IsParentMod() const
    {
    return (CBash_Flags & _fIsParentMod) != 0;
    }

Record * Record::GetParentRecord() const
    {
    if(IsParentMod())
        return NULL;
    return (Record *)GetParent();
    }

ModFile * Record::GetParentMod() const
    {
    Record *parent_record = GetParentRecord();

    if(parent_record)
        return parent_record->GetParentMod();

    return (ModFile *)GetParent();
    }

bool Record::IsWinningDetermined() const
    {
    return (CBash_Flags & _fIsWinningDetermined) != 0;
    }

void Record::IsWinningDetermined(bool value)
    {
    SETBIT(CBash_Flags, _fIsWinningDetermined, value);
    }

bool Record::IsWinning() const
    {
    return (CBash_Flags & _fIsWinning) != 0;
    }

void Record::IsWinning(bool value)
    {
    IsWinningDetermined(true);
    SETBIT(CBash_Flags, _fIsWinning, value);
    }

bool Record::IsExtendedWinning() const
    {
    return (CBash_Flags & _fIsExtendedWinning) != 0;
    }

void Record::IsExtendedWinning(bool value)
    {
    IsWinningDetermined(true);
    SETBIT(CBash_Flags, _fIsExtendedWinning, value);
    }

//bool Record::HasInvalidFormIDs() const
//    {
//    return (CBash_Flags & _fHasInvalidFormIDs) != 0;
//    }
//
//void Record::HasInvalidFormIDs(bool value)
//    {
//    CBash_Flags = value ? (CBash_Flags | _fHasInvalidFormIDs) : (CBash_Flags & ~_fHasInvalidFormIDs);
//    }

UINT32 Record::GetFieldAttribute(FIELD_IDENTIFIERS, UINT32 WhichAttribute)
    {
    return UNKNOWN_FIELD;
    }

void * Record::GetField(FIELD_IDENTIFIERS, void **FieldValues)
    {
    return NULL;
    }

bool Record::SetField(FIELD_IDENTIFIERS, void *FieldValue, UINT32 ArraySize)
    {
    return false;
    }

void Record::DeleteField(FIELD_IDENTIFIERS)
    {
    return;
    }

bool Record::IsKeyedByEditorID()
    {
    return false;
    }

STRING Record::GetEditorIDKey()
    {
    return (STRING)GetField(4);
    }

bool Record::SetEditorIDKey(STRING EditorID)
    {
    SetField(4, 0, 0, 0, 0, 0, 0, (void *)EditorID, 0);
    return false;
    }

bool Record::VisitFormIDs(FormIDOp &op)
    {
    return false;
    }

bool Record::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;
    UINT32 recSize = *(UINT32*)&recData[-16];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(UINT32*)&recData[-12] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        UINT32 expandedRecSize = *(UINT32*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, buffer + expandedRecSize, true);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recData + recSize);

    IsLoaded(true);
    return true;
    }

UINT32 Record::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();
    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged || flags != *(UINT32*)&recData[-12])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            if(Read())
                {
                //if(expander.IsValid(data)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, data, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, data, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(UINT32 z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(UINT32*)&recData[-16];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&flags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 20;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        }

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 20;
    }

bool Record::IsValid(FormIDResolver &expander)
    {
    return (recData <= expander.FileEnd && recData >= expander.FileStart);
    }

bool Record::master_equality(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    if(!shallow_equals(master))
        return false;

    //If neither is changed, and both use the same base data, they're equal. Don't need any expensive equality tests.
    if(!IsChanged() && !master->IsChanged() && recData == master->recData)
        return deep_equals(master, read_self, read_master, identical_records);

    Record *temp = (Record *)this;
    read_self.Accept(temp);
    read_master.Accept(master);

    if(equals(master))
        return deep_equals(master, read_self, read_master, identical_records);
    return false;
    }

bool Record::shallow_equals(Record *other)
    {
    if(GetType() != other->GetType())
        return false;
    if(flags != other->flags)
        return false;
    if(formID != other->formID)
        return false;
    return true;
    }

bool Record::deep_equals(Record *master, RecordOp &read_self, RecordOp &read_master, boost::unordered_set<Record *> &identical_records)
    {
    return true;
    }

bool Record::IsDeleted() const
    {
    return (flags & fIsDeleted) != 0;
    }

void Record::IsDeleted(bool value)
    {
    SETBIT(flags, fIsDeleted, value);
    }

bool Record::IsBorderRegion()
    {
    return (flags & fIsBorderRegion) != 0;
    }

void Record::IsBorderRegion(bool value)
    {
    SETBIT(flags, fIsBorderRegion, value);
    }

bool Record::IsTurnOffFire()
    {
    return (flags & fIsTurnOffFire) != 0;
    }

void Record::IsTurnOffFire(bool value)
    {
    SETBIT(flags, fIsTurnOffFire, value);
    }

bool Record::IsCastsShadows()
    {
    return (flags & fIsCastsShadows) != 0;
    }

void Record::IsCastsShadows(bool value)
    {
    SETBIT(flags, fIsCastsShadows, value);
    }

bool Record::IsQuestOrPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuestOrPersistent(bool value)
    {
    SETBIT(flags, fIsQuestOrPersistent, value);
    }

bool Record::IsQuest()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsQuest(bool value)
    {
    SETBIT(flags, fIsQuestOrPersistent, value);
    }

bool Record::IsPersistent()
    {
    return (flags & fIsQuestOrPersistent) != 0;
    }

void Record::IsPersistent(bool value)
    {
    SETBIT(flags, fIsQuestOrPersistent, value);
    }

bool Record::IsInitiallyDisabled()
    {
    return (flags & fIsInitiallyDisabled) != 0;
    }

void Record::IsInitiallyDisabled(bool value)
    {
    SETBIT(flags, fIsInitiallyDisabled, value);
    }

bool Record::IsIgnored()
    {
    return (flags & fIsIgnored) != 0;
    }

void Record::IsIgnored(bool value)
    {
    SETBIT(flags, fIsIgnored, value);
    }

bool Record::IsVisibleWhenDistant()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVisibleWhenDistant(bool value)
    {
    SETBIT(flags, fIsVisibleWhenDistant, value);
    }

bool Record::IsVWD()
    {
    return (flags & fIsVisibleWhenDistant) != 0;
    }

void Record::IsVWD(bool value)
    {
    SETBIT(flags, fIsVisibleWhenDistant, value);
    }

bool Record::IsTemporary()
    {
    return (flags & (fIsVisibleWhenDistant | fIsQuestOrPersistent)) != 0;
    }

void Record::IsTemporary(bool value)
    {
    flags = value ? (flags & ~(fIsVisibleWhenDistant | fIsQuestOrPersistent)) : (flags | fIsQuestOrPersistent);
    }

bool Record::IsDangerousOrOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerousOrOffLimits(bool value)
    {
    SETBIT(flags, fIsDangerousOrOffLimits, value);
    }

bool Record::IsDangerous()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsDangerous(bool value)
    {
    SETBIT(flags, fIsDangerousOrOffLimits, value);
    }

bool Record::IsOffLimits()
    {
    return (flags & fIsDangerousOrOffLimits) != 0;
    }

void Record::IsOffLimits(bool value)
    {
    SETBIT(flags, fIsDangerousOrOffLimits, value);
    }

bool Record::IsCompressed()
    {
    return (flags & fIsCompressed) != 0;
    }

void Record::IsCompressed(bool value)
    {
    SETBIT(flags, fIsCompressed, value);
    }

bool Record::IsCantWait()
    {
    return (flags & fIsCantWait) != 0;
    }

void Record::IsCantWait(bool value)
    {
    SETBIT(flags, fIsCantWait, value);
    }

bool Record::IsHeaderFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? (flags & Mask) == Mask : (flags & Mask) != 0;
    }

void Record::SetHeaderFlagMask(UINT32 Mask)
    {
    flags = Mask;
    }

bool Record::IsHeaderUnknownFlagMask(UINT32 Mask, bool Exact)
    {
    return Exact ? (flagsUnk & Mask) == Mask : (flagsUnk & Mask) != 0;
    }

void Record::SetHeaderUnknownFlagMask(UINT32 Mask)
    {
    flagsUnk = Mask;
    }

bool Record::IsLoaded() const
    {
    return (CBash_Flags & _fIsLoaded) != 0;
    }

void Record::IsLoaded(bool value)
    {
    SETBIT(CBash_Flags, _fIsLoaded, value);
    }

bool Record::IsChanged()
    {
    return recData == NULL || (CBash_Flags & _fIsChanged) != 0;
    }

void Record::IsChanged(bool value)
    {
    SETBIT(CBash_Flags, _fIsChanged, value);
    }

FNVRecord::FNVRecord(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

FNVRecord::~FNVRecord()
    {
    //
    }

bool FNVRecord::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;
    UINT32 recSize = *(UINT32*)&recData[-20];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(UINT32*)&recData[-16] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        UINT32 expandedRecSize = *(UINT32*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, buffer + expandedRecSize, true);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recData + recSize);

    IsLoaded(true);
    return true;
    }

UINT32 FNVRecord::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();

    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged || flags != *(UINT32*)&recData[-16])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            //so the record can't just be written as is.
            if(Read())
                {
                //if(expander.IsValid(data)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, data, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, data, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(UINT32 z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(UINT32*)&recData[-20];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&flags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(&formVersion, 2);
            writer.file_write(&versionControl2[0], 2);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 24;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        }

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 24;
    }

TES5Record::TES5Record(unsigned char *_recData):
    Record(_recData),
    formVersion(0)
    {
    memset(&versionControl2[0], 0x00, 2);
    }

TES5Record::TES5Record(TES5Record *srcRecord)
    {
    if (srcRecord == NULL)
        return;

    flags = srcRecord->flags;
    formID = srcRecord->formID;
    flagsUnk = srcRecord->flagsUnk;
    formVersion = srcRecord->formVersion;
    versionControl2[0] = srcRecord->versionControl2[0];
    versionControl2[1] = srcRecord->versionControl2[1];

    recData = srcRecord->recData;
    }

TES5Record::~TES5Record()
    {
    //
    }

bool TES5Record::Read()
    {
    if(IsLoaded() || IsChanged())
        return false;
    UINT32 recSize = *(UINT32*)&recData[-20];

    //Check against the original record flags to see if it is compressed since the current flags may have changed
    if ((*(UINT32*)&recData[-16] & fIsCompressed) != 0)
        {
        unsigned char localBuffer[BUFFERSIZE];
        UINT32 expandedRecSize = *(UINT32*)recData;
        unsigned char *buffer = (expandedRecSize >= BUFFERSIZE) ? new unsigned char[expandedRecSize] : &localBuffer[0];
        uncompress(buffer, (uLongf*)&expandedRecSize, &recData[4], recSize - 4);
        ParseRecord(buffer, buffer + expandedRecSize, true);
        if(buffer != &localBuffer[0])
            delete [] buffer;
        }
    else
        ParseRecord(recData, recData + recSize);

    IsLoaded(true);
    return true;
    }

UINT32 TES5Record::Write(FileWriter &writer, const bool &bMastersChanged, FormIDResolver &expander, FormIDResolver &collapser, std::vector<FormIDResolver *> &Expanders)
    {
    UINT32 recSize = 0;
    UINT32 recType = GetType();

    collapser.Accept(formID);

    if(!IsChanged())
        {
        if(bMastersChanged || flags != *(UINT32*)&recData[-16])
            {
            //if masters have changed, all formIDs have to be updated...
            //or if the flags have changed internally (notably fIsDeleted or fIsCompressed, possibly others)
            //so the record can't just be written as is.
            if(Read())
                {
                //if(expander.IsValid(data)) //optimization disabled for testing
                //    VisitFormIDs(expander);
                //printer("Looking for correct expander\n");
                SINT32 index = -1;
                for(UINT32 x = 0; x < Expanders.size(); ++x)
                    if(IsValid(*Expanders[x]))
                        {
                        //if(index != -1)
                        //    {
                        //    printer("Multiple 'Correct' expanders found (%08X)! Using last one found (likely incorrect unless lucky)\n", formID);
                        //    printer("  %i:   %08X, %08X, %08X\n", index, Expanders[index]->FileStart, data, Expanders[index]->FileEnd);
                        //    printer("  %i:   %08X, %08X, %08X\n", x, Expanders[x]->FileStart, data, Expanders[x]->FileEnd);
                        //    printer("Expanders:\n");
                        //    for(UINT32 z = 0; z < Expanders.size(); ++z)
                        //        printer("  %i of %i:   %08X, %08X\n", z, Expanders.size(), Expanders[z]->FileStart, Expanders[z]->FileEnd);
                        //    }
                        index = x;
                        break;
                        }
                if(index == -1)
                    {
                    printer("Unable to find the correct expander!\n");
                    VisitFormIDs(expander);
                    }
                else
                    VisitFormIDs(*Expanders[index]);
                }
            }
        else
            {
            //if masters have not changed, the record can just be written from the read buffer
            recSize = *(UINT32*)&recData[-20];

            writer.file_write(&recType, 4);
            writer.file_write(&recSize, 4);
            writer.file_write(&flags, 4);
            writer.file_write(&formID, 4);
            writer.file_write(&flagsUnk, 4);
            writer.file_write(&formVersion, 2);
            writer.file_write(&versionControl2[0], 2);
            writer.file_write(recData, recSize);
            Unload();
            return recSize + 24;
            }
        }

    VisitFormIDs(collapser);

    if(!IsDeleted())
        {
        //IsCompressed(true); //Test code
        WriteRecord(writer);
        recSize = IsCompressed() ? writer.record_compress() : writer.record_size();
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        //if(IsCompressed())
        //    {
        //    printer("Compressed: %08X\n", formID);
        //    }
        writer.record_flush();
        }
    else
        {
        writer.file_write(&recType, 4);
        writer.file_write(&recSize, 4);
        writer.file_write(&flags, 4);
        writer.file_write(&formID, 4);
        writer.file_write(&flagsUnk, 4);
        writer.file_write(&formVersion, 2);
        writer.file_write(&versionControl2[0], 2);
        }

    expander.Accept(formID);
    if(IsChanged())
        VisitFormIDs(expander);
    else
        Unload();
    return recSize + 24;
    }