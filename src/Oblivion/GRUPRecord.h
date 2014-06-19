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

#include "Records/DIALRecord.h"
#include "Records/CELLRecord.h"
#include "Records/ACRERecord.h"
#include "Records/ACHRRecord.h"
#include "Records/REFRRecord.h"
#include "Records/PGRDRecord.h"
#include "Records/WRLDRecord.h"
#include "Records/ROADRecord.h"
#include "Records/LANDRecord.h"

template<uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID>
class GRUPRecords<Ob::DIALRecord, RecType, AllocUnit, IsKeyedByEditorID>
    {
    public:
        RecordPoolAllocator<Ob::DIALRecord, RecType, AllocUnit> dial_pool;
        RecordPoolAllocator<Ob::INFORecord, REV32(INFO), 20> info_pool;
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
                printer("GRUPRecords<Ob::DIALRecord>::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            Ob::DIALRecord *last_record = NULL, *orphaned_records = NULL;
            uint32_t numDIAL = 0, numINFO = 0;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(Ob::DIALRecord)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(REV32(DIAL)) > 0 &&
                    processor.NewTypes.count(REV32(INFO)) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;

                if(header.type == REV32(GRUP)) //All GRUPs will be recreated from scratch on write (saves memory)
                    {
                    if(recordSize == 20)
                        processor.EmptyGRUPs++;
                    buffer_position += 12;
                    continue;
                    }

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

                    switch(header.type)
                        {
                        case REV32(DIAL):
                            numDIAL++;
                            break;
                        case REV32(INFO):
                            numINFO++;
                            break;
                        default:
                            printer("GRUPRecords<Ob::DIALRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(buffer_position, PEEK_SIZE);
                            #endif
                            records.pop_back();
                            break;
                        }
                    }

                buffer_position += recordSize;
                };

            if(records.size())
                {
                //Allocates many records at once in a contiguous space
                //Allocate memory
                unsigned char *dial_buffer = NULL;
                if(numDIAL)
                    {
                    dial_buffer = (unsigned char *)malloc(sizeof(Ob::DIALRecord) * numDIAL);
                    if(dial_buffer == 0)
                        throw std::bad_alloc();
                    dial_pool.add_buffer(dial_buffer);
                    }

                unsigned char *info_buffer = NULL;
                if(numINFO)
                    {
                    info_buffer = (unsigned char *)malloc(sizeof(Ob::INFORecord) * numINFO);
                    if(info_buffer == 0)
                        throw std::bad_alloc();
                    info_pool.add_buffer(info_buffer);
                    }

                last_record = orphaned_records = new Ob::DIALRecord();

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];

                    switch(header.type)
                        {
                        case REV32(DIAL):
                            curRecord = last_record = new(dial_buffer) Ob::DIALRecord(header.data);
                            dial_buffer += sizeof(Ob::DIALRecord);
                            curRecord->SetParent(processor.curModFile, true);
                            break;
                        case REV32(INFO):
                            curRecord = new(info_buffer) Ob::INFORecord(header.data);
                            info_buffer += sizeof(Ob::INFORecord);
                            curRecord->SetParent(last_record, false);
                            last_record->INFO.push_back(curRecord);
                            break;
                        default:
                            printer("GRUPRecords<Ob::DIALRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(header.data, PEEK_SIZE);
                            #endif
                            continue;
                            break;
                        }

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

                for(uint32_t x = 0; x < orphaned_records->INFO.size(); ++x)
                    {
                    curRecord = orphaned_records->INFO[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Ob::DIALRecord>::Read: Warning - Parsing error. Skipped orphan INFO (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    info_pool.destroy(curRecord);
                    }
                delete orphaned_records;
                }

            return true;
            }

        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            dial_pool.MakeRecordsVector(Records);
            uint32_t numDIALRecords = (uint32_t)Records.size(); //Parent Records
            if(numDIALRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t TopSize =0;
            uint32_t ChildrenSize =0;
            uint32_t formCount = 0;
            uint32_t TopLabel = REV32(DIAL);
            uint32_t numINFORecords = 0;
            uint32_t parentFormID = 0;
            Ob::DIALRecord *curRecord = NULL;

            //Top GRUP Header
            writer.file_write(&type, 4);
            uint32_t TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            gType = eTopicChildren;
            formCount += numDIALRecords;
            for(uint32_t p = 0; p < numDIALRecords; ++p)
                {
                curRecord = (Ob::DIALRecord *)Records[p];
                parentFormID = curRecord->formID;
                collapser.Accept(parentFormID);
                TopSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);

                numINFORecords = (uint32_t)curRecord->INFO.size();
                if(numINFORecords)
                    {
                    writer.file_write(&type, 4);
                    uint32_t ChildrenSizePos = writer.file_tell();
                    writer.file_write(&ChildrenSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&parentFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    ++formCount;
                    ChildrenSize = 20;

                    formCount += numINFORecords;
                    for(uint32_t y = 0; y < numINFORecords; ++y)
                        ChildrenSize += curRecord->INFO[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);
                    writer.file_write(ChildrenSizePos, &ChildrenSize, 4);
                    TopSize += ChildrenSize;
                    }
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                {
                info_pool.purge_with_destructors();
                dial_pool.purge_with_destructors();
                }
            return formCount;
            }

    };

template<uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID>
class GRUPRecords<Ob::CELLRecord, RecType, AllocUnit, IsKeyedByEditorID>
    {
    public:
        RecordPoolAllocator<Ob::CELLRecord, RecType, AllocUnit> cell_pool;
        RecordPoolAllocator<Ob::ACHRRecord, REV32(ACHR), 20> achr_pool;
        RecordPoolAllocator<Ob::ACRERecord, REV32(ACRE), 20> acre_pool;
        RecordPoolAllocator<Ob::REFRRecord, REV32(REFR), 20> refr_pool;
        RecordPoolAllocator<Ob::PGRDRecord, REV32(PGRD), 20> pgrd_pool;
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
                printer("GRUPRecords<Ob::CELLRecord>::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            Ob::CELLRecord *last_record = NULL, *orphaned_records = NULL;
            uint32_t numCELL = 0, numACHR = 0, numACRE = 0, numREFR = 0, numPGRD = 0;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(Ob::CELLRecord)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(REV32(CELL)) > 0 &&
                    processor.NewTypes.count(REV32(ACHR)) > 0 &&
                    processor.NewTypes.count(REV32(ACRE)) > 0 &&
                    processor.NewTypes.count(REV32(REFR)) > 0 &&
                    processor.NewTypes.count(REV32(PGRD)) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;

                if(header.type == REV32(GRUP)) //All GRUPs will be recreated from scratch on write (saves memory)
                    {
                    if(recordSize == 20)
                        processor.EmptyGRUPs++;
                    buffer_position += 12;
                    continue;
                    }

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

                    switch(header.type)
                        {
                        case REV32(CELL):
                            numCELL++;
                            break;
                        case REV32(ACHR):
                            numACHR++;
                            break;
                        case REV32(ACRE):
                            numACRE++;
                            break;
                        case REV32(REFR):
                            numREFR++;
                            break;
                        case REV32(PGRD):
                            numPGRD++;
                            break;
                        default:
                            printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(buffer_position, PEEK_SIZE);
                            #endif
                            records.pop_back();
                            break;
                        }
                    }

                buffer_position += recordSize;
                };

            if(records.size())
                {
                //Allocates many records at once in a contiguous space
                //Allocate memory

                unsigned char *cell_buffer = NULL;
                if(numCELL)
                    {
                    cell_buffer = (unsigned char *)malloc(sizeof(Ob::CELLRecord) * numCELL);
                    if(cell_buffer == 0)
                        throw std::bad_alloc();
                    cell_pool.add_buffer(cell_buffer);
                    }

                unsigned char *achr_buffer = NULL;
                if(numACHR)
                    {
                    achr_buffer = (unsigned char *)malloc(sizeof(Ob::ACHRRecord) * numACHR);
                    if(achr_buffer == 0)
                        throw std::bad_alloc();
                    achr_pool.add_buffer(achr_buffer);
                    }

                unsigned char *acre_buffer = NULL;
                if(numACRE)
                    {
                    acre_buffer = (unsigned char *)malloc(sizeof(Ob::ACRERecord) * numACRE);
                    if(acre_buffer == 0)
                        throw std::bad_alloc();
                    acre_pool.add_buffer(acre_buffer);
                    }

                unsigned char *refr_buffer = NULL;
                if(numREFR)
                    {
                    refr_buffer = (unsigned char *)malloc(sizeof(Ob::REFRRecord) * numREFR);
                    if(refr_buffer == 0)
                        throw std::bad_alloc();
                    refr_pool.add_buffer(refr_buffer);
                    }

                unsigned char *pgrd_buffer = NULL;
                if(numPGRD)
                    {
                    pgrd_buffer = (unsigned char *)malloc(sizeof(Ob::PGRDRecord) * numPGRD);
                    if(pgrd_buffer == 0)
                        throw std::bad_alloc();
                    pgrd_pool.add_buffer(pgrd_buffer);
                    }

                last_record = orphaned_records = new Ob::CELLRecord();

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];

                    switch(header.type)
                        {
                        case REV32(CELL):
                            curRecord = last_record = new(cell_buffer) Ob::CELLRecord(header.data);
                            cell_buffer += sizeof(Ob::CELLRecord);
                            curRecord->SetParent(processor.curModFile, true);
                            break;
                        case REV32(ACHR):
                            curRecord = new(achr_buffer) Ob::ACHRRecord(header.data);
                            achr_buffer += sizeof(Ob::ACHRRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->ACHR.push_back(curRecord);
                            break;
                        case REV32(ACRE):
                            curRecord = new(acre_buffer) Ob::ACRERecord(header.data);
                            acre_buffer += sizeof(Ob::ACRERecord);
                            curRecord->SetParent(last_record, false);
                            last_record->ACRE.push_back(curRecord);
                            break;
                        case REV32(REFR):
                            curRecord = new(refr_buffer) Ob::REFRRecord(header.data);
                            refr_buffer += sizeof(Ob::REFRRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->REFR.push_back(curRecord);
                            break;
                        case REV32(PGRD):
                            if(last_record == orphaned_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PGRD (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                pgrd_pool.deallocate((Record *)pgrd_buffer);
                                pgrd_buffer += sizeof(Ob::PGRDRecord);
                                continue;
                                break;
                                }
                            else if(last_record->PGRD != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Skipped extra PGRD (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", header.formID, header.data - buffer_start, FileName, last_record->formID, last_record->PGRD->formID);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                pgrd_pool.deallocate((Record *)pgrd_buffer);
                                pgrd_buffer += sizeof(Ob::PGRDRecord);
                                continue;
                                break;
                                }
                            curRecord = last_record->PGRD = new(pgrd_buffer) Ob::PGRDRecord(header.data);
                            pgrd_buffer += sizeof(Ob::PGRDRecord);
                            curRecord->SetParent(last_record, false);
                            break;
                        default:
                            printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(header.data, PEEK_SIZE);
                            #endif
                            continue;
                            break;
                        }

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

                for(uint32_t x = 0; x < orphaned_records->ACHR.size(); ++x)
                    {
                    curRecord = orphaned_records->ACHR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    achr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->ACRE.size(); ++x)
                    {
                    curRecord = orphaned_records->ACRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    acre_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->REFR.size(); ++x)
                    {
                    curRecord = orphaned_records->REFR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }
                delete orphaned_records;
                }
            return true;
            }

        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            cell_pool.MakeRecordsVector(Records);
            uint32_t numCELLRecords = (uint32_t)Records.size();
            if(numCELLRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t TopSize = 0;
            uint32_t TopSizePos = 0;
            uint32_t blockSize = 0;
            uint32_t blockSizePos = 0;
            uint32_t subBlockSize = 0;
            uint32_t subBlockSizePos = 0;
            uint32_t childrenSize = 0;
            uint32_t childrenSizePos = 0;
            uint32_t childSize = 0;
            uint32_t childSizePos = 0;

            uint32_t formCount = 0;

            uint32_t gLabel = RecType;
            uint32_t numSubBlocks = 0;
            uint32_t numChildren = 0;
            uint32_t numChild = 0;

            uint32_t parentFormID = 0;
            Ob::CELLRecord *curRecord = NULL;
            int ObjectID, BlockIndex, SubBlockIndex;

            std::vector< std::vector< std::vector<Ob::CELLRecord *> > > BlockedRecords(10, std::vector< std::vector<Ob::CELLRecord *> > (10, std::vector<Ob::CELLRecord *>()));
            std::vector<Record *> Persistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;
            BlockedRecords.reserve(numCELLRecords);
            for(uint32_t p = 0; p < numCELLRecords; ++p)
                {
                curRecord = (Ob::CELLRecord *)Records[p];

                ObjectID = curRecord->formID & 0x00FFFFFF;
                BlockIndex = ObjectID % 10;
                SubBlockIndex = (ObjectID / 10) % 10;

                BlockedRecords[BlockIndex][SubBlockIndex].push_back(curRecord);
                }

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numCELLRecords;
            for(uint32_t curBlock = 0; curBlock < 10; ++curBlock)
                {
                gType = eInteriorBlock;
                for(uint32_t curSubBlock = 0; curSubBlock < 10; ++curSubBlock)
                    {
                    numSubBlocks = (uint32_t)BlockedRecords[curBlock][curSubBlock].size();
                    if(numSubBlocks != 0)
                        {
                        if(gType == eInteriorBlock)
                            {
                            writer.file_write(&type, 4);
                            blockSizePos = writer.file_tell();
                            writer.file_write(&blockSizePos, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curBlock, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            blockSize = 20;
                            }
                        gType = eInteriorSubBlock;
                        writer.file_write(&type, 4);
                        subBlockSizePos = writer.file_tell();
                        writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curSubBlock, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        ++formCount;
                        subBlockSize = 20;
                        for(uint32_t p = 0; p < numSubBlocks; ++p)
                            {
                            curRecord = BlockedRecords[curBlock][curSubBlock][p];
                            parentFormID = curRecord->formID;
                            collapser.Accept(parentFormID);
                            subBlockSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);
                            //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP
                            if(curRecord->PGRD != NULL)
                                Temporary.push_back(curRecord->PGRD);

                            for(uint32_t y = 0; y < curRecord->ACHR.size(); ++y)
                                {
                                if(curRecord->ACHR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACHR[y]);
                                else if(curRecord->ACHR[y]->IsVWD())
                                    VWD.push_back(curRecord->ACHR[y]);
                                else
                                    Temporary.push_back(curRecord->ACHR[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->ACRE.size(); ++y)
                                {
                                if(curRecord->ACRE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->ACRE[y]);
                                else if(curRecord->ACRE[y]->IsVWD())
                                    VWD.push_back(curRecord->ACRE[y]);
                                else
                                    Temporary.push_back(curRecord->ACRE[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->REFR.size(); ++y)
                                {
                                if(curRecord->REFR[y]->IsPersistent())
                                    Persistent.push_back(curRecord->REFR[y]);
                                else if(curRecord->REFR[y]->IsVWD())
                                    VWD.push_back(curRecord->REFR[y]);
                                else
                                    Temporary.push_back(curRecord->REFR[y]);
                                }

                            numChildren = (uint32_t)Persistent.size() + (uint32_t)VWD.size() + (uint32_t)Temporary.size();
                            if(numChildren)
                                {
                                formCount += numChildren;
                                gType = eCellChildren;
                                writer.file_write(&type, 4);
                                childrenSizePos = writer.file_tell();
                                writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                writer.file_write(&parentFormID, 4);
                                writer.file_write(&gType, 4);
                                writer.file_write(&stamp, 4);
                                ++formCount;
                                childrenSize = 20;

                                numChild = (uint32_t)Persistent.size();
                                if(numChild)
                                    {
                                    gType = eCellPersistent;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(uint32_t x = 0; x < numChild; ++x)
                                        childSize += Persistent[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Persistent.clear();
                                    }

                                numChild = (uint32_t)VWD.size();
                                if(numChild)
                                    {
                                    gType = eCellVWD;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(uint32_t x = 0; x < numChild; ++x)
                                        childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    VWD.clear();
                                    }

                                numChild = (uint32_t)Temporary.size();
                                if(numChild)
                                    {
                                    gType = eCellTemporary;
                                    writer.file_write(&type, 4);
                                    childSizePos = writer.file_tell();
                                    writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&parentFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childSize = 20;

                                    for(uint32_t x = 0; x < numChild; ++x)
                                        childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                                    childrenSize += childSize;
                                    writer.file_write(childSizePos, &childSize, 4);
                                    Temporary.clear();
                                    }
                                subBlockSize += childrenSize;
                                writer.file_write(childrenSizePos, &childrenSize, 4);
                                }
                            if(CloseMod)
                                {
                                for(uint32_t x = 0; x < curRecord->ACHR.size(); ++x)
                                    achr_pool.destroy(curRecord->ACHR[x]);

                                for(uint32_t x = 0; x < curRecord->ACRE.size(); ++x)
                                    acre_pool.destroy(curRecord->ACRE[x]);

                                for(uint32_t x = 0; x < curRecord->REFR.size(); ++x)
                                    refr_pool.destroy(curRecord->REFR[x]);

                                pgrd_pool.destroy(curRecord->PGRD);
                                cell_pool.destroy(curRecord);
                                }
                            }
                        blockSize += subBlockSize;
                        writer.file_write(subBlockSizePos, &subBlockSize, 4);
                        BlockedRecords[curBlock][curSubBlock].clear();
                        }
                    }
                if(gType != eInteriorBlock)
                    {
                    TopSize += blockSize;
                    writer.file_write(blockSizePos, &blockSize, 4);
                    }
                BlockedRecords[curBlock].clear();
                }
            writer.file_write(TopSizePos, &TopSize, 4);
            BlockedRecords.clear();
            if(CloseMod)
                {
                //Can't release the pools entirely since the WRLD group may have entries still
                //achr_pool.purge_no_destructors();
                //acre_pool.purge_no_destructors();
                //refr_pool.purge_no_destructors();
                //pgrd_pool.purge_no_destructors();
                //uint32_t freed_achr = achr_pool.try_to_free();
                //uint32_t freed_acre = acre_pool.try_to_free();
                //uint32_t freed_refr = refr_pool.try_to_free();
                //uint32_t freed_pgrd = pgrd_pool.try_to_free();
                //DPRINT("freed_achr = %d, freed_acre = %d, freed_refr = %d, freed_pgrd = %d, total = %d", freed_achr, freed_acre, freed_refr, freed_pgrd, freed_achr + freed_acre + freed_refr + freed_pgrd);
                cell_pool.purge_no_destructors();
                }
            return formCount;
            }
    };

template<uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID>
class GRUPRecords<Ob::WRLDRecord, RecType, AllocUnit, IsKeyedByEditorID>
    {
    public:
        RecordPoolAllocator<Ob::WRLDRecord, RecType, AllocUnit> wrld_pool;
        RecordPoolAllocator<Ob::CELLRecord, REV32(CELL), 20> cell_pool;
        RecordPoolAllocator<Ob::LANDRecord, REV32(LAND), 20> land_pool;
        RecordPoolAllocator<Ob::ROADRecord, REV32(ROAD), 20> road_pool;

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

        template<typename U>
        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, char * &FileName, RecordOp &read_parser, U &CELL)
            {
            stamp = *(uint32_t *)buffer_position;
            buffer_position += 4;
            if(group_buffer_end <= buffer_position)
                {
                printer("GRUPRecords<Ob::WRLDRecord>::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            Ob::WRLDRecord *last_wrld_record = NULL, *orphaned_wrld_records = NULL;
            Ob::CELLRecord *last_cell_record = NULL, *orphaned_cell_records = NULL;
            uint32_t numWRLD = 0, numCELL = 0, numACHR = 0, numACRE = 0, numREFR = 0, numPGRD = 0, numLAND = 0, numROAD = 0;

            std::map<int32_t, std::map<int32_t, Ob::LANDRecord *> > GridXY_LAND;
            std::vector<std::pair<uint32_t, unsigned char *> > GRUPs;
            std::pair<uint32_t, unsigned char *> GRUP_End;
            GRUP_End.first = eTop;
            GRUP_End.second = group_buffer_end;
            GRUPs.push_back(GRUP_End);

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(Ob::WRLDRecord)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(REV32(WRLD)) > 0 &&
                    processor.NewTypes.count(REV32(ROAD)) > 0 &&
                    processor.NewTypes.count(REV32(CELL)) > 0 &&
                    processor.NewTypes.count(REV32(ACHR)) > 0 &&
                    processor.NewTypes.count(REV32(ACRE)) > 0 &&
                    processor.NewTypes.count(REV32(REFR)) > 0 &&
                    processor.NewTypes.count(REV32(PGRD)) > 0 &&
                    processor.NewTypes.count(REV32(LAND)) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                while(buffer_position >= GRUP_End.second)
                    {
                    //Better tracking of the last GRUP
                    //Mainly fixes cases where the world cell isn't located before the cell blocks
                    //One example of this is Windfall.esp
                    GRUPs.pop_back();
                    GRUP_End = GRUPs.back();
                    };

                //Assumes that all records in a generic group are of the same type
                header.type = *(uint32_t *)buffer_position;
                buffer_position += 4;
                recordSize = *(uint32_t *)buffer_position;
                buffer_position += 4;

                if(header.type == REV32(GRUP)) //All GRUPs will be recreated from scratch on write (saves memory)
                    {
                    if(recordSize == 20)
                        processor.EmptyGRUPs++;
                    buffer_position += 4; //header.flags
                    header.formID = *(FORMID *)buffer_position;
                    buffer_position += 8; //header.flagsUnk
                    GRUP_End.first = header.formID; //GRUP Type
                    GRUP_End.second = buffer_position + recordSize - 20;
                    GRUPs.push_back(GRUP_End);
                    continue;
                    }

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

                    switch(header.type)
                        {
                        case REV32(WRLD):
                            numWRLD++;
                            break;
                        case REV32(ROAD):
                            numROAD++;
                            break;
                        case REV32(CELL):
                            //Uniquely mark world cells for later
                            if(GRUP_End.first == eWorld)
                                records.back().type = REV32(WCEL);
                            numCELL++;
                            break;
                        case REV32(ACHR):
                            numACHR++;
                            break;
                        case REV32(ACRE):
                            numACRE++;
                            break;
                        case REV32(REFR):
                            numREFR++;
                            break;
                        case REV32(PGRD):
                            numPGRD++;
                            break;
                        case REV32(LAND):
                            numLAND++;
                            break;
                        default:
                            printer("GRUPRecords<Ob::CELLRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(buffer_position, PEEK_SIZE);
                            #endif
                            records.pop_back();
                            break;
                        }
                    }

                buffer_position += recordSize;
                };

            if(records.size())
                {
                //Allocates many records at once in a contiguous space
                //Allocate memory
                unsigned char *wrld_buffer = NULL;
                if(numWRLD)
                    {
                    wrld_buffer = (unsigned char *)malloc(sizeof(Ob::WRLDRecord) * numWRLD);
                    if(wrld_buffer == 0)
                        throw std::bad_alloc();
                    wrld_pool.add_buffer(wrld_buffer);
                    }

                unsigned char *road_buffer = NULL;
                if(numROAD)
                    {
                    road_buffer = (unsigned char *)malloc(sizeof(Ob::ROADRecord) * numROAD);
                    if(road_buffer == 0)
                        throw std::bad_alloc();
                    road_pool.add_buffer(road_buffer);
                    }

                unsigned char *cell_buffer = NULL;
                if(numCELL)
                    {
                    cell_buffer = (unsigned char *)malloc(sizeof(Ob::CELLRecord) * numCELL);
                    if(cell_buffer == 0)
                        throw std::bad_alloc();
                    cell_pool.add_buffer(cell_buffer);
                    }

                unsigned char *achr_buffer = NULL;
                if(numACHR)
                    {
                    achr_buffer = (unsigned char *)malloc(sizeof(Ob::ACHRRecord) * numACHR);
                    if(achr_buffer == 0)
                        throw std::bad_alloc();
                    CELL.achr_pool.add_buffer(achr_buffer);
                    }

                unsigned char *acre_buffer = NULL;
                if(numACRE)
                    {
                    acre_buffer = (unsigned char *)malloc(sizeof(Ob::ACRERecord) * numACRE);
                    if(acre_buffer == 0)
                        throw std::bad_alloc();
                    CELL.acre_pool.add_buffer(acre_buffer);
                    }

                unsigned char *refr_buffer = NULL;
                if(numREFR)
                    {
                    refr_buffer = (unsigned char *)malloc(sizeof(Ob::REFRRecord) * numREFR);
                    if(refr_buffer == 0)
                        throw std::bad_alloc();
                    CELL.refr_pool.add_buffer(refr_buffer);
                    }

                unsigned char *pgrd_buffer = NULL;
                if(numPGRD)
                    {
                    pgrd_buffer = (unsigned char *)malloc(sizeof(Ob::PGRDRecord) * numPGRD);
                    if(pgrd_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pgrd_pool.add_buffer(pgrd_buffer);
                    }

                unsigned char *land_buffer = NULL;
                if(numLAND)
                    {
                    land_buffer = (unsigned char *)malloc(sizeof(Ob::LANDRecord) * numLAND);
                    if(land_buffer == 0)
                        throw std::bad_alloc();
                    land_pool.add_buffer(land_buffer);
                    }

                last_wrld_record = orphaned_wrld_records = new Ob::WRLDRecord();
                last_cell_record = orphaned_cell_records = new Ob::CELLRecord();

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];

                    switch(header.type)
                        {
                        case REV32(WRLD):
                            curRecord = last_wrld_record = new(wrld_buffer) Ob::WRLDRecord(header.data);
                            wrld_buffer += sizeof(Ob::WRLDRecord);
                            curRecord->SetParent(processor.curModFile, true);
                            break;
                        case REV32(ROAD):
                            if(last_wrld_record == orphaned_wrld_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan ROAD (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                road_pool.deallocate((Record *)road_buffer);
                                road_buffer += sizeof(Ob::ROADRecord);
                                continue;
                                break;
                                }
                            else if(last_wrld_record->ROAD != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped extra ROAD (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", header.formID, header.data - buffer_start, FileName, last_wrld_record->formID, last_wrld_record->ROAD->formID);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                road_pool.deallocate((Record *)road_buffer);
                                road_buffer += sizeof(Ob::ROADRecord);
                                continue;
                                break;
                                }
                            curRecord = last_wrld_record->ROAD = new(road_buffer) Ob::ROADRecord(header.data);
                            road_buffer += sizeof(Ob::ROADRecord);
                            curRecord->SetParent(last_wrld_record, false);
                            break;
                        case REV32(WCEL):
                            if(last_wrld_record == orphaned_wrld_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan World CELL (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                cell_pool.deallocate((Record *)cell_buffer);
                                cell_buffer += sizeof(Ob::CELLRecord);
                                continue;
                                break;
                                }
                            else if(last_wrld_record->CELL != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped extra World CELL (%08X) at %08X in file \"%s\"\n  WRLD (%08X) already has CELL (%08X)\n", header.formID, header.data - buffer_start, FileName, last_wrld_record->formID, last_wrld_record->CELL->formID);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                cell_pool.deallocate((Record *)cell_buffer);
                                cell_buffer += sizeof(Ob::CELLRecord);
                                continue;
                                break;
                                }
                            curRecord = last_cell_record = new(cell_buffer) Ob::CELLRecord(header.data);
                            cell_buffer += sizeof(Ob::CELLRecord);
                            last_cell_record->SetParent(last_wrld_record, false);
                            last_wrld_record->CELL = last_cell_record;
                            break;
                        case REV32(CELL):
                            curRecord = last_cell_record = new(cell_buffer) Ob::CELLRecord(header.data);
                            cell_buffer += sizeof(Ob::CELLRecord);
                            last_cell_record->SetParent(last_wrld_record, false);
                            last_wrld_record->CELLS.push_back(curRecord);
                            break;
                        case REV32(ACHR):
                            curRecord = new(achr_buffer) Ob::ACHRRecord(header.data);
                            achr_buffer += sizeof(Ob::ACHRRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->ACHR.push_back(curRecord);
                            break;
                        case REV32(ACRE):
                            curRecord = new(acre_buffer) Ob::ACRERecord(header.data);
                            acre_buffer += sizeof(Ob::ACRERecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->ACRE.push_back(curRecord);
                            break;
                        case REV32(REFR):
                            curRecord = new(refr_buffer) Ob::REFRRecord(header.data);
                            refr_buffer += sizeof(Ob::REFRRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->REFR.push_back(curRecord);
                            break;
                        case REV32(PGRD):
                            if(last_cell_record == orphaned_cell_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan PGRD (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                CELL.pgrd_pool.deallocate((Record *)pgrd_buffer);
                                pgrd_buffer += sizeof(Ob::PGRDRecord);
                                continue;
                                break;
                                }
                            else if(last_cell_record->PGRD != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped extra PGRD (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", header.formID, header.data - buffer_start, FileName, last_cell_record->formID, last_cell_record->PGRD->formID);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                CELL.pgrd_pool.deallocate((Record *)pgrd_buffer);
                                pgrd_buffer += sizeof(Ob::PGRDRecord);
                                continue;
                                break;
                                }
                            curRecord = last_cell_record->PGRD = new(pgrd_buffer) Ob::PGRDRecord(header.data);
                            pgrd_buffer += sizeof(Ob::PGRDRecord);
                            curRecord->SetParent(last_cell_record, false);
                            break;
                        case REV32(LAND):
                            if(last_cell_record == orphaned_cell_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan LAND (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                land_pool.deallocate((Record *)land_buffer);
                                land_buffer += sizeof(Ob::LANDRecord);
                                continue;
                                break;
                                }
                            else if(last_cell_record->LAND != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped extra LAND (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", header.formID, header.data - buffer_start, FileName, last_cell_record->formID, last_cell_record->LAND->formID);
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                land_pool.deallocate((Record *)land_buffer);
                                land_buffer += sizeof(Ob::LANDRecord);
                                continue;
                                break;
                                }
                            curRecord = last_cell_record->LAND = new(land_buffer) Ob::LANDRecord(header.data);
                            land_buffer += sizeof(Ob::LANDRecord);
                            curRecord->SetParent(last_cell_record, false);
                            if(processor.Flags.IsIndexLANDs)
                                {
                                read_parser.Accept((Record *&)last_cell_record); //may already be loaded, but just to be sure.
                                //CELL will be unloaded if needed after a second round of indexing when all records are loaded
                                last_cell_record->XCLC.Load(); //in-case no XCLC chunk is specified
                                GridXY_LAND[last_cell_record->XCLC->posX][last_cell_record->XCLC->posY] = (Ob::LANDRecord *)curRecord;
                                }
                            break;
                        default:
                            printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(header.data, PEEK_SIZE);
                            #endif
                            continue;
                            break;
                        }

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

                //Index LAND records by grid
                //There might be ACHR, ACRE, or REFR records in the World CELL
                if(processor.Flags.IsIndexLANDs || processor.Flags.IsFixupPlaceables)
                    {
                    int32_t posX = 0, posY = 0;
                    int32_t gridX = 0, gridY = 0;

                    Ob::CELLRecord *last_wcel_record = NULL;
                    Ob::LANDRecord *last_land_record = NULL;
                    std::vector<Record *> Records;
                    wrld_pool.MakeRecordsVector(Records);
                    for(uint32_t x = 0; x < Records.size(); ++x)
                        {
                        last_wrld_record = (Ob::WRLDRecord *)Records[x];
                        last_wcel_record = (Ob::CELLRecord *)last_wrld_record->CELL;
                        for(uint32_t y = 0; y < last_wrld_record->CELLS.size(); ++y)
                            {
                            last_cell_record = (Ob::CELLRecord *)last_wrld_record->CELLS[y];
                            read_parser.Accept((Record *&)last_cell_record);
                            last_cell_record->XCLC.Load(); //in-case no XCLC chunk is specified

                            // "Oblivion.esm"->"TestRender" has no XCLC
                            posX = 0;
                            posY = 0;
                            if (last_cell_record->XCLC.IsLoaded()) {
                                posX = last_cell_record->XCLC->posX;
                                posY = last_cell_record->XCLC->posY;
                            }

                            if(processor.Flags.IsFixupPlaceables && last_wcel_record != NULL)
                                {
                                for(uint32_t x = 0; x < last_wcel_record->ACHR.size();)
                                    {
                                    //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                    curRecord = last_wcel_record->ACHR[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Ob::ACHRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Ob::ACHRRecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        //For easier use later on, go ahead and move it to the parent cell.
                                        //It will get moved back later during the save process if need be.
                                        last_cell_record->ACHR.push_back(curRecord);
                                        last_wcel_record->ACHR.erase(last_wcel_record->ACHR.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->ACRE.size();)
                                    {
                                    //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                    curRecord = last_wcel_record->ACRE[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Ob::ACRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Ob::ACRERecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        //For easier use later on, go ahead and move it to the parent cell.
                                        //It will get moved back later during the save process if need be.
                                        last_cell_record->ACRE.push_back(curRecord);
                                        last_wcel_record->ACRE.erase(last_wcel_record->ACRE.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->REFR.size();)
                                    {
                                    //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                    curRecord = last_wcel_record->REFR[x];
                                    read_parser.Accept(curRecord);

                                    ((Ob::REFRRecord *)curRecord)->Data.Load();
                                    gridX = (int32_t)floor(((Ob::REFRRecord *)curRecord)->Data->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Ob::REFRRecord *)curRecord)->Data->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        //For easier use later on, go ahead and move it to the parent cell.
                                        //It will get moved back later during the save process if need be.
                                        last_cell_record->REFR.push_back(curRecord);
                                        last_wcel_record->REFR.erase(last_wcel_record->REFR.begin() + x);
                                        }
                                    else ++x;
                                    }
                                }

                            if(processor.Flags.IsIndexLANDs)
                                {
                                last_land_record = (Ob::LANDRecord *)last_cell_record->LAND;
                                if(last_land_record != NULL)
                                    {
                                    last_land_record->NorthLand = GridXY_LAND[posX][posY + 1];
                                    last_land_record->SouthLand = GridXY_LAND[posX][posY - 1];
                                    last_land_record->EastLand = GridXY_LAND[posX + 1][posY];
                                    last_land_record->WestLand = GridXY_LAND[posX - 1][posY];
                                    }
                                }

                            if(processor.Flags.IsMinLoad)
                                last_cell_record->Unload();
                            }
                        }
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->ACHR.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->ACHR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.achr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->ACRE.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->ACRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.acre_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->REFR.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->REFR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    #ifdef CBASH_DEBUG_CHUNK
                        printer("GRUPRecords<Ob::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.refr_pool.destroy(curRecord);
                    }
                delete orphaned_cell_records;
                delete orphaned_wrld_records;
                }
            return true;
            }

        template<typename U>
        uint32_t Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod, FormIDHandlerClass &FormIDHandler, U &CELL, RecordOp &indexer)
            {
            std::vector<Record *> Records;
            wrld_pool.MakeRecordsVector(Records);
            uint32_t numWRLDRecords = (uint32_t)Records.size();
            if(numWRLDRecords == 0)
                return 0;

            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t gLabel = RecType;
            uint32_t TopSize = 0;
            uint32_t TopSizePos = 0;
            uint32_t worldSize = 0;
            uint32_t worldSizePos = 0;
            uint32_t blockSize = 0;
            uint32_t blockSizePos = 0;
            uint32_t subBlockSize = 0;
            uint32_t subBlockSizePos = 0;
            uint32_t childrenSize = 0;
            uint32_t childrenSizePos = 0;
            uint32_t childSize = 0;
            uint32_t childSizePos = 0;

            uint32_t formCount = 0;

            uint32_t numCELLRecords = 0;
            uint32_t numSubBlocks = 0;
            uint32_t numChildren = 0;
            uint32_t numChild = 0;

            Ob::WRLDRecord *curWorld = NULL;
            Ob::CELLRecord *curCell = NULL;
            Ob::CELLRecord *curWorldCell = NULL;
            uint32_t worldFormID = 0;
            uint32_t cellFormID = 0;
            int gridX, gridY;
            uint32_t BlockIndex, SubBlockIndex;

            std::map<uint32_t, std::map<uint32_t, std::vector<Ob::CELLRecord *> > > BlockedRecords;
            std::vector<Record *> Persistent;
            std::vector<Record *> FixedPersistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;

            //Top GRUP Header
            writer.file_write(&type, 4);
            TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&gLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;
            formCount += numWRLDRecords;
            for(uint32_t x = 0; x < numWRLDRecords; ++x)
                {
                curWorld = (Ob::WRLDRecord *)Records[x];
                worldFormID = curWorld->formID;
                collapser.Accept(worldFormID);
                TopSize += curWorld->Write(writer, bMastersChanged, expander, collapser, Expanders);

                curWorldCell = (Ob::CELLRecord *)curWorld->CELL;

                numCELLRecords = (uint32_t)curWorld->CELLS.size();
                formCount += numCELLRecords;
                for(uint32_t p = 0; p < numCELLRecords; ++p)
                    {
                    curCell = (Ob::CELLRecord *)curWorld->CELLS[p];

                    //All persistent references must be moved to the world cell
                    for(uint32_t y = 0; y < curCell->ACRE.size(); ++y)
                        if(curCell->ACRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACRE[y]);

                    for(uint32_t y = 0; y < curCell->ACHR.size(); ++y)
                        if(curCell->ACHR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->ACHR[y]);

                    for(uint32_t y = 0; y < curCell->REFR.size(); ++y)
                        if(curCell->REFR[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->REFR[y]);

                    if(curCell->Read())
                        curCell->VisitFormIDs(expander);
                    curCell->XCLC.Load();
                    gridX = (int)floor(curCell->XCLC->posX / 8.0);
                    gridY = (int)floor(curCell->XCLC->posY / 8.0);
                    if(!curCell->IsChanged())
                        curCell->Unload();
                    SubBlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);
                    gridX = (int)floor(gridX / 4.0);
                    gridY = (int)floor(gridY / 4.0);
                    BlockIndex = (gridX << 16 & 0xFFFF0000) | (gridY & 0x0000FFFF);

                    BlockedRecords[BlockIndex][SubBlockIndex].push_back(curCell);
                    }

                if(curWorldCell == NULL && FixedPersistent.size()) //create a default dummy cell for persistents
                    {
                    curWorldCell = (Ob::CELLRecord *)cell_pool.construct((unsigned char *)NULL, curWorld, false);
                    curWorldCell->formID = FormIDHandler.NextExpandedFormID();
                    curWorld->CELL = curWorldCell;
                    curWorldCell->SetParent(curWorld, false);
                    curWorldCell->IsInterior(false);
                    curWorldCell->IsHasWater(true);
                    curWorldCell->IsPersistent(true);
                    curWorldCell->XCLC.Load();
                    if(!CloseMod)
                        indexer.Accept((Record *&)curWorldCell);
                    }

                if(curWorld->ROAD != NULL || curWorldCell != NULL || numCELLRecords > 0)
                    {
                    gType = eWorld;
                    writer.file_write(&type, 4);
                    worldSizePos = writer.file_tell();
                    writer.file_write(&worldSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&worldFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    ++formCount;
                    worldSize = 20;

                    if(curWorld->ROAD != NULL)
                        {
                        worldSize += curWorld->ROAD->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;
                        if(CloseMod)
                            road_pool.destroy(curWorld->ROAD);
                        }

                    if(curWorldCell != NULL)
                        {
                        curCell = curWorldCell;
                        cellFormID = curCell->formID;
                        collapser.Accept(cellFormID);
                        worldSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;

                        if(curCell->LAND != NULL)
                            Temporary.push_back(curCell->LAND);

                        if(curCell->PGRD != NULL)
                            Temporary.push_back(curCell->PGRD);

                        uint32_t ignored_count = 0;
                        for(uint32_t y = 0; y < curCell->ACRE.size(); ++y)
                            {
                            if(curCell->ACRE[y]->IsPersistent())
                                Persistent.push_back(curCell->ACRE[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->ACHR.size(); ++y)
                            {
                            if(curCell->ACHR[y]->IsPersistent())
                                Persistent.push_back(curCell->ACHR[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->REFR.size(); ++y)
                            {
                            if(curCell->REFR[y]->IsPersistent())
                                Persistent.push_back(curCell->REFR[y]);
                            else
                                ignored_count++;
                            }

                        if(ignored_count)
                            printer("GRUPRecords<Ob::WRLDRecord>::Write: Warning - Information lost. Ignored %u VWD and Temporary records in the world cell: %08X", ignored_count, worldFormID);

                        numChildren = (uint32_t)Persistent.size() + (uint32_t)FixedPersistent.size();
                        if(numChildren)
                            {
                            formCount += numChildren;
                            gType = eCellChildren;
                            writer.file_write(&type, 4);
                            childrenSizePos = writer.file_tell();
                            writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            childrenSize = 20;

                            //World CELL should only have persistent objects in it
                            gType = eCellPersistent;
                            writer.file_write(&type, 4);
                            childSizePos = writer.file_tell();
                            writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            childSize = 20;

                            numChild = (uint32_t)Persistent.size();
                            for(uint32_t y = 0; y < numChild; ++y)
                                childSize += Persistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                            numChild = (uint32_t)FixedPersistent.size();
                            for(uint32_t y = 0; y < numChild; ++y)
                                childSize += FixedPersistent[y]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                            childrenSize += childSize;
                            writer.file_write(childSizePos, &childSize, 4);
                            Persistent.clear();
                            FixedPersistent.clear();
                            worldSize += childrenSize;
                            writer.file_write(childrenSizePos, &childrenSize, 4);
                            }
                        if(CloseMod)
                            {
                            for(uint32_t x = 0; x < curCell->ACHR.size(); ++x)
                                CELL.achr_pool.destroy(curCell->ACHR[x]);

                            for(uint32_t x = 0; x < curCell->ACRE.size(); ++x)
                                CELL.acre_pool.destroy(curCell->ACRE[x]);

                            for(uint32_t x = 0; x < curCell->REFR.size(); ++x)
                                CELL.refr_pool.destroy(curCell->REFR[x]);

                            CELL.pgrd_pool.destroy(curCell->PGRD);
                            land_pool.destroy(curCell->LAND);

                            cell_pool.destroy(curCell);
                            }
                        }

                    for(std::map<uint32_t, std::map<uint32_t, std::vector<Ob::CELLRecord *> > >::iterator curBlock = BlockedRecords.begin(); curBlock != BlockedRecords.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        writer.file_write(&type, 4);
                        blockSizePos = writer.file_tell();
                        writer.file_write(&blockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curBlock->first, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        ++formCount;
                        blockSize = 20;

                        for(std::map<uint32_t, std::vector<Ob::CELLRecord *> >::iterator curSubBlock = curBlock->second.begin(); curSubBlock != curBlock->second.end(); ++curSubBlock)
                            {
                            gType = eExteriorSubBlock;
                            writer.file_write(&type, 4);
                            subBlockSizePos = writer.file_tell();
                            writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curSubBlock->first, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            ++formCount;
                            subBlockSize = 20;

                            numSubBlocks = (uint32_t)curSubBlock->second.size();
                            for(uint32_t p = 0; p < numSubBlocks; ++p)
                                {
                                curCell = curSubBlock->second[p];
                                cellFormID = curCell->formID;
                                collapser.Accept(cellFormID);
                                subBlockSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                                //Place the PGRD, ACHR, ACRE, and REFR records into their proper GRUP

                                if(curCell->LAND != NULL)
                                    Temporary.push_back(curCell->LAND);

                                if(curCell->PGRD != NULL)
                                    Temporary.push_back(curCell->PGRD);

                                for(uint32_t y = 0; y < curCell->ACRE.size(); ++y)
                                    {
                                    if(curCell->ACRE[y]->IsVWD())
                                        VWD.push_back(curCell->ACRE[y]);
                                    else if(!curCell->ACRE[y]->IsPersistent())
                                        Temporary.push_back(curCell->ACRE[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->ACHR.size(); ++y)
                                    {
                                    if(curCell->ACHR[y]->IsVWD())
                                        VWD.push_back(curCell->ACHR[y]);
                                    else if(!curCell->ACHR[y]->IsPersistent())
                                        Temporary.push_back(curCell->ACHR[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->REFR.size(); ++y)
                                    {
                                    if(curCell->REFR[y]->IsVWD())
                                        VWD.push_back(curCell->REFR[y]);
                                    else if(!curCell->REFR[y]->IsPersistent())
                                        Temporary.push_back(curCell->REFR[y]);
                                    }

                                numChildren = (uint32_t)VWD.size() + (uint32_t)Temporary.size();
                                if(numChildren)
                                    {
                                    formCount += numChildren;
                                    gType = eCellChildren;
                                    writer.file_write(&type, 4);
                                    childrenSizePos = writer.file_tell();
                                    writer.file_write(&childrenSize, 4); //Placeholder: will be overwritten with correct value later.
                                    writer.file_write(&cellFormID, 4);
                                    writer.file_write(&gType, 4);
                                    writer.file_write(&stamp, 4);
                                    ++formCount;
                                    childrenSize = 20;

                                    numChild = (uint32_t)VWD.size();
                                    if(numChild)
                                        {
                                        gType = eCellVWD;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(uint32_t x = 0; x < numChild; ++x)
                                            childSize += VWD[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        VWD.clear();
                                        }

                                    numChild = (uint32_t)Temporary.size();
                                    if(numChild)
                                        {
                                        gType = eCellTemporary;
                                        writer.file_write(&type, 4);
                                        childSizePos = writer.file_tell();
                                        writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                                        writer.file_write(&cellFormID, 4);
                                        writer.file_write(&gType, 4);
                                        writer.file_write(&stamp, 4);
                                        ++formCount;
                                        childSize = 20;

                                        for(uint32_t x = 0; x < numChild; ++x)
                                            childSize += Temporary[x]->Write(writer, bMastersChanged, expander, collapser, Expanders);

                                        childrenSize += childSize;
                                        writer.file_write(childSizePos, &childSize, 4);
                                        Temporary.clear();
                                        }
                                    subBlockSize += childrenSize;
                                    writer.file_write(childrenSizePos, &childrenSize, 4);
                                    }
                                if(CloseMod)
                                    {
                                    for(uint32_t x = 0; x < curCell->ACHR.size(); ++x)
                                        CELL.achr_pool.destroy(curCell->ACHR[x]);

                                    for(uint32_t x = 0; x < curCell->ACRE.size(); ++x)
                                        CELL.acre_pool.destroy(curCell->ACRE[x]);

                                    for(uint32_t x = 0; x < curCell->REFR.size(); ++x)
                                        CELL.refr_pool.destroy(curCell->REFR[x]);

                                    CELL.pgrd_pool.destroy(curCell->PGRD);
                                    land_pool.destroy(curCell->LAND);

                                    cell_pool.destroy(curCell);
                                    }
                                }
                            blockSize += subBlockSize;
                            writer.file_write(subBlockSizePos, &subBlockSize, 4);
                            curSubBlock->second.clear();
                            }
                        worldSize += blockSize;
                        writer.file_write(blockSizePos, &blockSize, 4);
                        curBlock->second.clear();
                        }
                    TopSize += worldSize;
                    writer.file_write(worldSizePos, &worldSize, 4);
                    }
                if(CloseMod)
                    wrld_pool.destroy(curWorld);
                BlockedRecords.clear();
                }

            if(CloseMod)
                {
                //All destructors ran earlier, pools are entirely free
                CELL.achr_pool.purge_no_destructors();
                CELL.acre_pool.purge_no_destructors();
                CELL.refr_pool.purge_no_destructors();
                CELL.pgrd_pool.purge_no_destructors();
                cell_pool.purge_no_destructors();
                land_pool.purge_no_destructors();
                road_pool.purge_no_destructors();
                wrld_pool.purge_no_destructors();
                }

            writer.file_write(TopSizePos, &TopSize, 4);

            return formCount;
            }
    };
