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
// GRUPRecord.h
#include "Common.h"
#include "GenericRecord.h"
#include "Allocator.h"
#include "Visitors.h"
#include <vector>
#include <math.h>
//#include <boost/threadpool.hpp>

//#include "mmgr.h"

template<class T, uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID=false>
class GRUPRecords
    {
    public:
        RecordPoolAllocator<T, RecType, AllocUnit> pool;
        uint32_t stamp;

        GRUPRecords():
            stamp(134671)
            {
            //
            }

        ~GRUPRecords()
            {
            //
            }

        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, char * &FileName)
            {
            stamp = *(uint32_t *)buffer_position;
            buffer_position += 4;
            if(group_buffer_end <= buffer_position)
                {
                printer("GRUPRecords::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(RecType) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.flags = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.formID = *(FORMID *)buffer_position;
                buffer_position += 4;
                header.flagsUnk = *(uint32_t *)buffer_position;
                buffer_position += 4;

                if(processor.Accept(header))
                    {
                    header.data = buffer_position;
                    records.push_back(header);
                    }

                buffer_position += recordSize;
                };

            if(records.size())
                {
                //Allocates many records at once in a contiguous space
                //Allocate memory
                unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (uint32_t)records.size());
                if(buffer == 0)
                    throw std::bad_alloc();
                pool.add_buffer(buffer);

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];
                    curRecord = new(buffer) T(header.data);
                    buffer += sizeof(T);
                    curRecord->SetParent(processor.curModFile, true);
                    curRecord->flags = header.flags;
                    curRecord->formID = header.formID;
                    curRecord->flagsUnk = header.flagsUnk;
                    //Testing Messages
                    //if((flags & 0x4000) != 0)
                    //    printer("0x4000 used: %08X!!!!\n", curRecord->formID);

                    //Read (if FullLoad), no-op otherwise
                    parser.Accept(curRecord);
                    //Save any deleted records for post-processing
                    if(curRecord->IsDeleted())
                        DeletedRecords.push_back(curRecord);
                    //Index it for fast, random lookup
                    indexer.Accept(curRecord);
                    }

                records.clear();
                }

            return true;
            }

        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            pool.MakeRecordsVector(Records);
            uint32_t numRecords = (uint32_t)Records.size();
            if(numRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t TopSize = 0;
            uint32_t TopLabel = RecType;
            uint32_t formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            uint32_t TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numRecords;
            for(uint32_t p = 0; p < numRecords; p++)
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                pool.purge_with_destructors();

            return formCount;
            }
    };

#include "Oblivion/GRUPRecord.h"

template<class T, uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID=false>
class FNVGRUPRecords
    {
    public:
        RecordPoolAllocator<T, RecType, AllocUnit> pool;
        uint32_t stamp, unknown;

        FNVGRUPRecords():
            stamp(134671),
            unknown(0)
            {
            //
            }

        ~FNVGRUPRecords()
            {
            //
            }

        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, char * &FileName)
            {
            stamp = *(uint32_t *)buffer_position;
            buffer_position += 4;
            unknown = *(uint32_t *)buffer_position;
            buffer_position += 4;
            if(group_buffer_end <= buffer_position)
                {
                printer("FNVGRUPRecords::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(RecType) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.flags = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.formID = *(FORMID *)buffer_position;
                buffer_position += 4;
                header.flagsUnk = *(uint32_t *)buffer_position; //VersionControl1
                buffer_position += 4;
                header.formVersion = *(uint16_t *)buffer_position;
                buffer_position += 2;
                header.versionControl2[0] = *(uint8_t *)buffer_position;
                buffer_position++;
                header.versionControl2[1] = *(uint8_t *)buffer_position;
                buffer_position++;

                if(processor.Accept(header))
                    {
                    header.data = buffer_position;
                    records.push_back(header);
                    }

                buffer_position += recordSize;
                };

            if(records.size())
                {
                //Allocates many records at once in a contiguous space
                //Allocate memory
                unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (uint32_t)records.size());
                if(buffer == 0)
                    throw std::bad_alloc();
                pool.add_buffer(buffer);

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];
                    curRecord = new(buffer) T(header.data);
                    buffer += sizeof(T);
                    curRecord->SetParent(processor.curModFile, true);
                    curRecord->flags = header.flags;
                    curRecord->formID = header.formID;
                    curRecord->flagsUnk = header.flagsUnk; //VersionControl1
                    ((FNVRecord *)curRecord)->formVersion = header.formVersion;
                    ((FNVRecord *)curRecord)->versionControl2[0] = header.versionControl2[0];
                    ((FNVRecord *)curRecord)->versionControl2[1] = header.versionControl2[1];

                    //Testing Messages
                    //if((flags & 0x4000) != 0)
                    //    printer("0x4000 used: %08X!!!!\n", curRecord->formID);

                    //Read (if FullLoad), no-op otherwise
                    parser.Accept(curRecord);
                    //Save any deleted records for post-processing
                    if(curRecord->IsDeleted())
                        DeletedRecords.push_back(curRecord);
                    //Index it for fast, random lookup
                    indexer.Accept(curRecord);
                    }

                records.clear();
                }

            return true;
            }

        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            pool.MakeRecordsVector(Records);
            uint32_t numRecords = (uint32_t)Records.size();
            if(numRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t TopSize = 0;
            uint32_t TopLabel = RecType;
            uint32_t formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            uint32_t TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numRecords;
            for(uint32_t p = 0; p < numRecords; p++)
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                pool.purge_with_destructors();

            return formCount;
            }
    };

#include "FalloutNewVegas/GRUPRecord.h"

template<class T, uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID=false>
class TES5GRUPRecords
    {
    public:
        RecordPoolAllocator<T, RecType, AllocUnit> pool;
        uint32_t stamp, unknown;

        TES5GRUPRecords():
            stamp(134671),
            unknown(0)
        {
        //
        }

        ~TES5GRUPRecords()
        {
        //
        }

        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, char * &FileName)
        {
            stamp = *(uint32_t *)buffer_position;
            buffer_position += 4;
            unknown = *(uint32_t *)buffer_position;
            buffer_position += 4;
            if(group_buffer_end <= buffer_position)
            {
                printer("TES5GRUPRecords::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
#ifdef CBASH_DEBUG_CHUNK
                peek_around(buffer_position, PEEK_SIZE);
#endif
                return false;
            }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end)
            {
                if ((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(RecType) > 0)
                {
                    buffer_position = group_buffer_end;
                    break;
                }

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.flags = *(uint32_t *)buffer_position;
                buffer_position += 4;
                header.formID = *(FORMID *)buffer_position;
                buffer_position += 4;
                header.flagsUnk = *(uint32_t *)buffer_position; //VersionControl1
                buffer_position += 4;
                header.formVersion = *(uint16_t *)buffer_position;
                buffer_position += 2;
                header.versionControl2[0] = *(uint8_t *)buffer_position;
                buffer_position++;
                header.versionControl2[1] = *(uint8_t *)buffer_position;
                buffer_position++;

                if (processor.Accept(header))
                {
                    header.data = buffer_position;
                    records.push_back(header);
                }

                buffer_position += recordSize;
            };

            if (records.size())
            {
                //Allocates many records at once in a contiguous space
                //Allocate memory
                unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (uint32_t)records.size());
                if (buffer == 0)
                    throw std::bad_alloc();
                pool.add_buffer(buffer);

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                {
                    header = records[x];
                    curRecord = new(buffer) T(header.data);
                    buffer += sizeof(T);
                    curRecord->SetParent(processor.curModFile, true);
                    curRecord->flags = header.flags;
                    curRecord->formID = header.formID;
                    curRecord->flagsUnk = header.flagsUnk; //VersionControl1
                    ((TES5Record *)curRecord)->formVersion = header.formVersion;
                    ((TES5Record *)curRecord)->versionControl2[0] = header.versionControl2[0];
                    ((TES5Record *)curRecord)->versionControl2[1] = header.versionControl2[1];

                    //Testing Messages
                    //if((flags & 0x4000) != 0)
                    //    printer("0x4000 used: %08X!!!!\n", curRecord->formID);
                    curRecord->IsLoaded(false); //just incase the chosen flags were in use, clear them

                    //Read (if FullLoad), no-op otherwise
                    parser.Accept(curRecord);
                    //Save any deleted records for post-processing
                    if (curRecord->IsDeleted())
                        DeletedRecords.push_back(curRecord);
                    //Index it for fast, random lookup
                    indexer.Accept(curRecord);
                }

                records.clear();
            }

            return true;
        }

        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
        {
            std::vector<Record *> Records;
            pool.MakeRecordsVector(Records);
            uint32_t numRecords = (uint32_t)Records.size();
            if (numRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t TopSize = 0;
            uint32_t TopLabel = RecType;
            uint32_t formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            uint32_t TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numRecords;
            for(uint32_t p = 0; p < numRecords; p++)
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

            writer.file_write(TopSizePos, &TopSize, 4);
            if (CloseMod)
                pool.purge_with_destructors();

            return formCount;
        }
    };

#include "Skyrim/GRUPRecord.h"
