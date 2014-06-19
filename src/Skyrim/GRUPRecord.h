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

#include "Records/CELLRecord.h"
#include "Records/LANDRecord.h"
#include "Records/WRLDRecord.h"

template<uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID>
class TES5GRUPRecords<Sk::CELLRecord, RecType, AllocUnit, IsKeyedByEditorID>
    {
    public:
        RecordPoolAllocator<Sk::CELLRecord, RecType, AllocUnit> cell_pool;
        /*
        RecordPoolAllocator<Sk::ACHRRecord, REV32(ACHR), 5> achr_pool;
        RecordPoolAllocator<Sk::ACRERecord, REV32(ACRE), 5> acre_pool;
        RecordPoolAllocator<Sk::REFRRecord, REV32(REFR), 5> refr_pool;
        RecordPoolAllocator<Sk::PGRERecord, REV32(PGRE), 5> pgre_pool;
        RecordPoolAllocator<Sk::PMISRecord, REV32(PMIS), 5> pmis_pool;
        RecordPoolAllocator<Sk::PBEARecord, REV32(PBEA), 5> pbea_pool;
        RecordPoolAllocator<Sk::PFLARecord, REV32(PFLA), 5> pfla_pool;
        RecordPoolAllocator<Sk::PCBERecord, REV32(PCBE), 5> pcbe_pool;
        RecordPoolAllocator<Sk::NAVMRecord, REV32(NAVM), 5> navm_pool;
        */
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
                printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            Sk::CELLRecord *last_record = NULL, *orphaned_records = NULL;
            uint32_t numCELL = 0/*, numACHR = 0, numACRE = 0, numREFR = 0, numPGRE = 0,
                   numPMIS = 0, numPBEA = 0, numPFLA = 0, numPCBE = 0, numNAVM = 0*/;

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(Sk::CELLRecord)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(REV32(CELL)) > 0/* &&
                    processor.NewTypes.count(REV32(ACHR)) > 0 &&
                    processor.NewTypes.count(REV32(ACRE)) > 0 &&
                    processor.NewTypes.count(REV32(REFR)) > 0 &&
                    processor.NewTypes.count(REV32(PGRE)) > 0 &&
                    processor.NewTypes.count(REV32(PMIS)) > 0 &&
                    processor.NewTypes.count(REV32(PBEA)) > 0 &&
                    processor.NewTypes.count(REV32(PFLA)) > 0 &&
                    processor.NewTypes.count(REV32(PCBE)) > 0 &&
                    processor.NewTypes.count(REV32(NAVM)) > 0*/)
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
                    buffer_position += 16;
                    continue;
                    }

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

                    switch(header.type)
                        {
                        case REV32(CELL):
                            numCELL++;
                            break;

                        /*
                        case REV32(ACHR):
                            numACHR++;
                            break;
                        case REV32(ACRE):
                            numACRE++;
                            break;
                        case REV32(REFR):
                            numREFR++;
                            break;
                        case REV32(PGRE):
                            numPGRE++;
                            break;
                        case REV32(PMIS):
                            numPMIS++;
                            break;
                        case REV32(PBEA):
                            numPBEA++;
                            break;
                        case REV32(PFLA):
                            numPFLA++;
                            break;
                        case REV32(PCBE):
                            numPCBE++;
                            break;
                        case REV32(NAVM):
                            numNAVM++;
                            break;
                        */

                        default:
                            printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
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
                    cell_buffer = (unsigned char *)malloc(sizeof(Sk::CELLRecord) * numCELL);
                    if(cell_buffer == 0)
                        throw std::bad_alloc();
                    cell_pool.add_buffer(cell_buffer);
                    }

                /*
                unsigned char *achr_buffer = NULL;
                if(numACHR)
                    {
                    achr_buffer = (unsigned char *)malloc(sizeof(Sk::ACHRRecord) * numACHR);
                    if(achr_buffer == 0)
                        throw std::bad_alloc();
                    achr_pool.add_buffer(achr_buffer);
                    }

                unsigned char *acre_buffer = NULL;
                if(numACRE)
                    {
                    acre_buffer = (unsigned char *)malloc(sizeof(Sk::ACRERecord) * numACRE);
                    if(acre_buffer == 0)
                        throw std::bad_alloc();
                    acre_pool.add_buffer(acre_buffer);
                    }

                unsigned char *refr_buffer = NULL;
                if(numREFR)
                    {
                    refr_buffer = (unsigned char *)malloc(sizeof(Sk::REFRRecord) * numREFR);
                    if(refr_buffer == 0)
                        throw std::bad_alloc();
                    refr_pool.add_buffer(refr_buffer);
                    }

                unsigned char *pgre_buffer = NULL;
                if(numPGRE)
                    {
                    pgre_buffer = (unsigned char *)malloc(sizeof(Sk::PGRERecord) * numPGRE);
                    if(pgre_buffer == 0)
                        throw std::bad_alloc();
                    pgre_pool.add_buffer(pgre_buffer);
                    }

                unsigned char *pmis_buffer = NULL;
                if(numPMIS)
                    {
                    pmis_buffer = (unsigned char *)malloc(sizeof(Sk::PMISRecord) * numPMIS);
                    if(pmis_buffer == 0)
                        throw std::bad_alloc();
                    pmis_pool.add_buffer(pmis_buffer);
                    }

                unsigned char *pbea_buffer = NULL;
                if(numPBEA)
                    {
                    pbea_buffer = (unsigned char *)malloc(sizeof(Sk::PBEARecord) * numPBEA);
                    if(pbea_buffer == 0)
                        throw std::bad_alloc();
                    pbea_pool.add_buffer(pbea_buffer);
                    }

                unsigned char *pfla_buffer = NULL;
                if(numPFLA)
                    {
                    pfla_buffer = (unsigned char *)malloc(sizeof(Sk::PFLARecord) * numPFLA);
                    if(pfla_buffer == 0)
                        throw std::bad_alloc();
                    pfla_pool.add_buffer(pfla_buffer);
                    }

                unsigned char *pcbe_buffer = NULL;
                if(numPCBE)
                    {
                    pcbe_buffer = (unsigned char *)malloc(sizeof(Sk::PCBERecord) * numPCBE);
                    if(pcbe_buffer == 0)
                        throw std::bad_alloc();
                    pcbe_pool.add_buffer(pcbe_buffer);
                    }

                unsigned char *navm_buffer = NULL;
                if(numNAVM)
                    {
                    navm_buffer = (unsigned char *)malloc(sizeof(Sk::NAVMRecord) * numNAVM);
                    if(navm_buffer == 0)
                        throw std::bad_alloc();
                    navm_pool.add_buffer(navm_buffer);
                    }
                */

                last_record = orphaned_records = new Sk::CELLRecord();

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];

                    switch(header.type)
                        {
                        case REV32(CELL):
                            curRecord = last_record = new(cell_buffer) Sk::CELLRecord(header.data);
                            cell_buffer += sizeof(Sk::CELLRecord);
                            curRecord->SetParent(processor.curModFile, true);
                            break;

                        /*
                        case REV32(ACHR):
                            curRecord = new(achr_buffer) Sk::ACHRRecord(header.data);
                            achr_buffer += sizeof(Sk::ACHRRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->ACHR.push_back(curRecord);
                            break;
                        case REV32(ACRE):
                            curRecord = new(acre_buffer) Sk::ACRERecord(header.data);
                            acre_buffer += sizeof(Sk::ACRERecord);
                            curRecord->SetParent(last_record, false);
                            last_record->ACRE.push_back(curRecord);
                            break;
                        case REV32(REFR):
                            curRecord = new(refr_buffer) Sk::REFRRecord(header.data);
                            refr_buffer += sizeof(Sk::REFRRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->REFR.push_back(curRecord);
                            break;
                        case REV32(PGRE):
                            curRecord = new(pgre_buffer) Sk::PGRERecord(header.data);
                            pgre_buffer += sizeof(Sk::PGRERecord);
                            curRecord->SetParent(last_record, false);
                            last_record->PGRE.push_back(curRecord);
                            break;
                        case REV32(PMIS):
                            curRecord = new(pmis_buffer) Sk::PMISRecord(header.data);
                            pmis_buffer += sizeof(Sk::PMISRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->PMIS.push_back(curRecord);
                            break;
                        case REV32(PBEA):
                            curRecord = new(pbea_buffer) Sk::PBEARecord(header.data);
                            pbea_buffer += sizeof(Sk::PBEARecord);
                            curRecord->SetParent(last_record, false);
                            last_record->PBEA.push_back(curRecord);
                            break;
                        case REV32(PFLA):
                            curRecord = new(pfla_buffer) Sk::PFLARecord(header.data);
                            pfla_buffer += sizeof(Sk::PFLARecord);
                            curRecord->SetParent(last_record, false);
                            last_record->PFLA.push_back(curRecord);
                            break;
                        case REV32(PCBE):
                            curRecord = new(pcbe_buffer) Sk::PCBERecord(header.data);
                            pcbe_buffer += sizeof(Sk::PCBERecord);
                            curRecord->SetParent(last_record, false);
                            last_record->PCBE.push_back(curRecord);
                            break;
                        case REV32(NAVM):
                            curRecord = new(navm_buffer) Sk::NAVMRecord(header.data);
                            navm_buffer += sizeof(Sk::NAVMRecord);
                            curRecord->SetParent(last_record, false);
                            last_record->NAVM.push_back(curRecord);
                            break;
                        */

                        default:
                            printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(header.data, PEEK_SIZE);
                            #endif
                            continue;
                            break;
                        }

                    curRecord->flags = header.flags;
                    curRecord->formID = header.formID;
                    curRecord->flagsUnk = header.flagsUnk; //VersionControl1
                    ((TES5Record *)curRecord)->formVersion = header.formVersion;
                    ((TES5Record *)curRecord)->versionControl2[0] = header.versionControl2[0];
                    ((TES5Record *)curRecord)->versionControl2[1] = header.versionControl2[1];

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

                /*
                for(uint32_t x = 0; x < orphaned_records->ACHR.size(); ++x)
                    {
                    curRecord = orphaned_records->ACHR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    achr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->ACRE.size(); ++x)
                    {
                    curRecord = orphaned_records->ACRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    acre_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->REFR.size(); ++x)
                    {
                    curRecord = orphaned_records->REFR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->PGRE.size(); ++x)
                    {
                    curRecord = orphaned_records->PGRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PGRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->PMIS.size(); ++x)
                    {
                    curRecord = orphaned_records->PMIS[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PMIS (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->PBEA.size(); ++x)
                    {
                    curRecord = orphaned_records->PBEA[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PBEA (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->PFLA.size(); ++x)
                    {
                    curRecord = orphaned_records->PFLA[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PFLA (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->PCBE.size(); ++x)
                    {
                    curRecord = orphaned_records->PCBE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PCBE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_records->NAVM.size(); ++x)
                    {
                    curRecord = orphaned_records->NAVM[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan NAVM (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    refr_pool.destroy(curRecord);
                    }
                */

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
            Sk::CELLRecord *curRecord = NULL;
            int ObjectID, BlockIndex, SubBlockIndex;

            std::vector< std::vector< std::vector<Sk::CELLRecord *> > > BlockedRecords(10, std::vector< std::vector<Sk::CELLRecord *> > (10, std::vector<Sk::CELLRecord *>()));
            std::vector<Record *> Persistent;
            std::vector<Record *> Temporary;
            std::vector<Record *> VWD;
            BlockedRecords.reserve(numCELLRecords);
            for(uint32_t p = 0; p < numCELLRecords; ++p)
                {
                curRecord = (Sk::CELLRecord *)Records[p];

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
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

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
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            blockSize = 24;
                            }
                        gType = eInteriorSubBlock;
                        writer.file_write(&type, 4);
                        subBlockSizePos = writer.file_tell();
                        writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curSubBlock, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        writer.file_write(&unknown, 4);
                        ++formCount;
                        subBlockSize = 24;
                        for(uint32_t p = 0; p < numSubBlocks; ++p)
                            {
                            curRecord = BlockedRecords[curBlock][curSubBlock][p];
                            parentFormID = curRecord->formID;
                            collapser.Accept(parentFormID);
                            subBlockSize += curRecord->Write(writer, bMastersChanged, expander, collapser, Expanders);
                            //Place the ACHR, ACRE, REFR, PGRE, PMIS, PBEA, PFLA, PCBE, NAVM records into their proper GRUP

                            /*
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

                            for(uint32_t y = 0; y < curRecord->PGRE.size(); ++y)
                                {
                                if(curRecord->PGRE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PGRE[y]);
                                else if(curRecord->PGRE[y]->IsVWD())
                                    VWD.push_back(curRecord->PGRE[y]);
                                else
                                    Temporary.push_back(curRecord->PGRE[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->PMIS.size(); ++y)
                                {
                                if(curRecord->PMIS[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PMIS[y]);
                                else if(curRecord->PMIS[y]->IsVWD())
                                    VWD.push_back(curRecord->PMIS[y]);
                                else
                                    Temporary.push_back(curRecord->PMIS[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->PBEA.size(); ++y)
                                {
                                if(curRecord->PBEA[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PBEA[y]);
                                else if(curRecord->PBEA[y]->IsVWD())
                                    VWD.push_back(curRecord->PBEA[y]);
                                else
                                    Temporary.push_back(curRecord->PBEA[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->PFLA.size(); ++y)
                                {
                                if(curRecord->PFLA[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PFLA[y]);
                                else if(curRecord->PFLA[y]->IsVWD())
                                    VWD.push_back(curRecord->PFLA[y]);
                                else
                                    Temporary.push_back(curRecord->PFLA[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->PCBE.size(); ++y)
                                {
                                if(curRecord->PCBE[y]->IsPersistent())
                                    Persistent.push_back(curRecord->PCBE[y]);
                                else if(curRecord->PCBE[y]->IsVWD())
                                    VWD.push_back(curRecord->PCBE[y]);
                                else
                                    Temporary.push_back(curRecord->PCBE[y]);
                                }

                            for(uint32_t y = 0; y < curRecord->NAVM.size(); ++y)
                                 Temporary.push_back(curRecord->NAVM[y]);
                            */

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
                                writer.file_write(&unknown, 4);
                                ++formCount;
                                childrenSize = 24;

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
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

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
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

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
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childSize = 24;

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
                                /*
                                for(uint32_t x = 0; x < curRecord->ACHR.size(); ++x)
                                    achr_pool.destroy(curRecord->ACHR[x]);

                                for(uint32_t x = 0; x < curRecord->ACRE.size(); ++x)
                                    acre_pool.destroy(curRecord->ACRE[x]);

                                for(uint32_t x = 0; x < curRecord->REFR.size(); ++x)
                                    refr_pool.destroy(curRecord->REFR[x]);

                                for(uint32_t x = 0; x < curRecord->PGRE.size(); ++x)
                                    pgre_pool.destroy(curRecord->PGRE[x]);

                                for(uint32_t x = 0; x < curRecord->PMIS.size(); ++x)
                                    pmis_pool.destroy(curRecord->PMIS[x]);

                                for(uint32_t x = 0; x < curRecord->PBEA.size(); ++x)
                                    pbea_pool.destroy(curRecord->PBEA[x]);

                                for(uint32_t x = 0; x < curRecord->PFLA.size(); ++x)
                                    pfla_pool.destroy(curRecord->PFLA[x]);

                                for(uint32_t x = 0; x < curRecord->PCBE.size(); ++x)
                                    pcbe_pool.destroy(curRecord->PCBE[x]);

                                for(uint32_t x = 0; x < curRecord->NAVM.size(); ++x)
                                    navm_pool.destroy(curRecord->NAVM[x]);
                                */

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
                //pgre_pool.purge_no_destructors();
                //pmis_pool.purge_no_destructors();
                //pbea_pool.purge_no_destructors();
                //pfla_pool.purge_no_destructors();
                //pcbe_pool.purge_no_destructors();
                //navm_pool.purge_no_destructors();
                cell_pool.purge_no_destructors();
                }
            return formCount;
            }
    };

template<uint32_t RecType, uint32_t AllocUnit, bool IsKeyedByEditorID>
class TES5GRUPRecords<Sk::WRLDRecord, RecType, AllocUnit, IsKeyedByEditorID>
    {
    public:
        RecordPoolAllocator<Sk::WRLDRecord, RecType, AllocUnit> wrld_pool;
        RecordPoolAllocator<Sk::CELLRecord, REV32(CELL), 5> cell_pool;
        RecordPoolAllocator<Sk::LANDRecord, REV32(LAND), 5> land_pool;
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

        template<typename U>
        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, char * &FileName, RecordOp &read_parser, U &CELL)
            {
            stamp = *(uint32_t *)buffer_position;
            buffer_position += 4;
            unknown = *(uint32_t *)buffer_position;
            buffer_position += 4;
            if(group_buffer_end <= buffer_position)
                {
                printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Error - Unable to load group in file \"%s\". The group has a size of 0.\n", FileName);
                #ifdef CBASH_DEBUG_CHUNK
                    peek_around(buffer_position, PEEK_SIZE);
                #endif
                return false;
                }

            Record * curRecord = NULL;
            uint32_t recordSize = 0;
            RecordHeader header;

            Sk::WRLDRecord *last_wrld_record = NULL, *orphaned_wrld_records = NULL;
            Sk::CELLRecord *last_cell_record = NULL, *orphaned_cell_records = NULL;
            uint32_t numWRLD = 0, numCELL = 0, numLAND = 0/*, numACHR = 0, numACRE = 0, numREFR = 0,
                   numPGRE = 0, numPMIS = 0, numPBEA = 0, numPFLA = 0, numPCBE = 0, numNAVM = 0*/;

            std::map<int32_t, std::map<int32_t, Sk::LANDRecord *> > GridXY_LAND;
            std::vector<std::pair<uint32_t, unsigned char *> > GRUPs;
            std::pair<uint32_t, unsigned char *> GRUP_End;
            GRUP_End.first = eTop;
            GRUP_End.second = group_buffer_end;
            GRUPs.push_back(GRUP_End);

            std::vector<RecordHeader> records;
            records.reserve((uint32_t)(group_buffer_end - buffer_position) / sizeof(Sk::WRLDRecord)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(REV32(WRLD)) > 0 &&
                    processor.NewTypes.count(REV32(CELL)) > 0 &&
                    processor.NewTypes.count(REV32(LAND)) > 0/* &&
                    processor.NewTypes.count(REV32(ACHR)) > 0 &&
                    processor.NewTypes.count(REV32(ACRE)) > 0 &&
                    processor.NewTypes.count(REV32(REFR)) > 0 &&
                    processor.NewTypes.count(REV32(PGRE)) > 0 &&
                    processor.NewTypes.count(REV32(PMIS)) > 0 &&
                    processor.NewTypes.count(REV32(PBEA)) > 0 &&
                    processor.NewTypes.count(REV32(PFLA)) > 0 &&
                    processor.NewTypes.count(REV32(PCBE)) > 0 &&
                    processor.NewTypes.count(REV32(NAVM)) > 0*/)
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
                    buffer_position += 12; //header.flagsUnk, header.formVersion ,header.versionControl2[0]
                    GRUP_End.first = header.formID; //GRUP Type
                    GRUP_End.second = buffer_position + recordSize - 24;
                    GRUPs.push_back(GRUP_End);
                    continue;
                    }

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

                    switch(header.type)
                        {
                        case REV32(WRLD):
                            numWRLD++;
                            break;
                        case REV32(CELL):
                            //Uniquely mark world cells for later
                            if(GRUP_End.first == eWorld)
                                records.back().type = REV32(WCEL);
                            numCELL++;
                            break;

                        case REV32(LAND):
                            numLAND++;
                            break;
                            /*
                        case REV32(ACHR):
                            numACHR++;
                            break;
                        case REV32(ACRE):
                            numACRE++;
                            break;
                        case REV32(REFR):
                            numREFR++;
                            break;
                        case REV32(PGRE):
                            numPGRE++;
                            break;
                        case REV32(PMIS):
                            numPMIS++;
                            break;
                        case REV32(PBEA):
                            numPBEA++;
                            break;
                        case REV32(PFLA):
                            numPFLA++;
                            break;
                        case REV32(PCBE):
                            numPCBE++;
                            break;
                        case REV32(NAVM):
                            numNAVM++;
                            break;
                            */

                        default:
                            printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
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
                    wrld_buffer = (unsigned char *)malloc(sizeof(Sk::WRLDRecord) * numWRLD);
                    if(wrld_buffer == 0)
                        throw std::bad_alloc();
                    wrld_pool.add_buffer(wrld_buffer);
                    }

                unsigned char *cell_buffer = NULL;
                if(numCELL)
                    {
                    cell_buffer = (unsigned char *)malloc(sizeof(Sk::CELLRecord) * numCELL);
                    if(cell_buffer == 0)
                        throw std::bad_alloc();
                    cell_pool.add_buffer(cell_buffer);
                    }

                unsigned char *land_buffer = NULL;
                if(numLAND)
                    {
                    land_buffer = (unsigned char *)malloc(sizeof(Sk::LANDRecord) * numLAND);
                    if(land_buffer == 0)
                        throw std::bad_alloc();
                    land_pool.add_buffer(land_buffer);
                    }
/*
                unsigned char *achr_buffer = NULL;
                if(numACHR)
                    {
                    achr_buffer = (unsigned char *)malloc(sizeof(Sk::ACHRRecord) * numACHR);
                    if(achr_buffer == 0)
                        throw std::bad_alloc();
                    CELL.achr_pool.add_buffer(achr_buffer);
                    }

                unsigned char *acre_buffer = NULL;
                if(numACRE)
                    {
                    acre_buffer = (unsigned char *)malloc(sizeof(Sk::ACRERecord) * numACRE);
                    if(acre_buffer == 0)
                        throw std::bad_alloc();
                    CELL.acre_pool.add_buffer(acre_buffer);
                    }

                unsigned char *refr_buffer = NULL;
                if(numREFR)
                    {
                    refr_buffer = (unsigned char *)malloc(sizeof(Sk::REFRRecord) * numREFR);
                    if(refr_buffer == 0)
                        throw std::bad_alloc();
                    CELL.refr_pool.add_buffer(refr_buffer);
                    }

                unsigned char *pgre_buffer = NULL;
                if(numPGRE)
                    {
                    pgre_buffer = (unsigned char *)malloc(sizeof(Sk::PGRERecord) * numPGRE);
                    if(pgre_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pgre_pool.add_buffer(pgre_buffer);
                    }

                unsigned char *pmis_buffer = NULL;
                if(numPMIS)
                    {
                    pmis_buffer = (unsigned char *)malloc(sizeof(Sk::PMISRecord) * numPMIS);
                    if(pmis_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pmis_pool.add_buffer(pmis_buffer);
                    }

                unsigned char *pbea_buffer = NULL;
                if(numPBEA)
                    {
                    pbea_buffer = (unsigned char *)malloc(sizeof(Sk::PBEARecord) * numPBEA);
                    if(pbea_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pbea_pool.add_buffer(pbea_buffer);
                    }

                unsigned char *pfla_buffer = NULL;
                if(numPFLA)
                    {
                    pfla_buffer = (unsigned char *)malloc(sizeof(Sk::PFLARecord) * numPFLA);
                    if(pfla_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pfla_pool.add_buffer(pfla_buffer);
                    }

                unsigned char *pcbe_buffer = NULL;
                if(numPCBE)
                    {
                    pcbe_buffer = (unsigned char *)malloc(sizeof(Sk::PCBERecord) * numPCBE);
                    if(pcbe_buffer == 0)
                        throw std::bad_alloc();
                    CELL.pcbe_pool.add_buffer(pcbe_buffer);
                    }

                unsigned char *navm_buffer = NULL;
                if(numNAVM)
                    {
                    navm_buffer = (unsigned char *)malloc(sizeof(Sk::NAVMRecord) * numNAVM);
                    if(navm_buffer == 0)
                        throw std::bad_alloc();
                    CELL.navm_pool.add_buffer(navm_buffer);
                    }
*/
                last_wrld_record = orphaned_wrld_records = new Sk::WRLDRecord();
                last_cell_record = orphaned_cell_records = new Sk::CELLRecord();

                //Construct the records
                for(uint32_t x = 0; x < records.size();++x)
                    {
                    header = records[x];

                    switch(header.type)
                        {
                        case REV32(WRLD):
                            curRecord = last_wrld_record = new(wrld_buffer) Sk::WRLDRecord(header.data);
                            wrld_buffer += sizeof(Sk::WRLDRecord);
                            curRecord->SetParent(processor.curModFile, true);
                            break;
                        case REV32(WCEL):
                            if(last_wrld_record == orphaned_wrld_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                //printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan World CELL (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                #ifdef CBASH_DEBUG_CHUNK
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                cell_pool.deallocate((Record *)cell_buffer);
                                cell_buffer += sizeof(Sk::CELLRecord);
                                continue;
                                break;
                                }
                            else if(last_wrld_record->CELL != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                //printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Skipped extra World CELL (%08X) at %08X in file \"%s\"\n  WRLD (%08X) already has CELL (%08X)\n", header.formID, header.data - buffer_start, FileName, last_wrld_record->formID, last_wrld_record->CELL->formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                cell_pool.deallocate((Record *)cell_buffer);
                                cell_buffer += sizeof(Sk::CELLRecord);
                                continue;
                                break;
                                }
                            curRecord = last_cell_record = new(cell_buffer) Sk::CELLRecord(header.data);
                            cell_buffer += sizeof(Sk::CELLRecord);
                            last_cell_record->SetParent(last_wrld_record, false);
                            last_wrld_record->CELL = last_cell_record;
                            break;
                        case REV32(CELL):
                            curRecord = last_cell_record = new(cell_buffer) Sk::CELLRecord(header.data);
                            cell_buffer += sizeof(Sk::CELLRecord);
                            last_cell_record->SetParent(last_wrld_record, false);
                            last_wrld_record->CELLS.push_back(curRecord);
                            break;
                        case REV32(LAND):
                            if(last_cell_record == orphaned_cell_records)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                //printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Skipped orphan LAND (%08X) at %08X in file \"%s\"\n", header.formID, header.data - buffer_start, FileName);
                                #ifdef CBASH_DEBUG_CHUNK
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                land_pool.deallocate((Record *)land_buffer);
                                land_buffer += sizeof(Sk::LANDRecord);
                                continue;
                                break;
                                }
                            else if(last_cell_record->LAND != NULL)
                                {
                                processor.OrphanedRecords.push_back(header.formID);
                                //printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Skipped extra LAND (%08X) at %08X in file \"%s\"\n  CELL (%08X) already has PGRD (%08X)\n", header.formID, header.data - buffer_start, FileName, last_cell_record->formID, last_cell_record->LAND->formID);
                                #ifdef CBASH_DEBUG_CHUNK
                                    peek_around(header.data, PEEK_SIZE);
                                #endif
                                land_pool.deallocate((Record *)land_buffer);
                                land_buffer += sizeof(Sk::LANDRecord);
                                continue;
                                break;
                                }
                            curRecord = last_cell_record->LAND = new(land_buffer) Sk::LANDRecord(header.data);
                            land_buffer += sizeof(Sk::LANDRecord);
                            curRecord->SetParent(last_cell_record, false);
                            if(processor.Flags.IsIndexLANDs)
                                {
                                read_parser.Accept((Record *&)last_cell_record); //may already be loaded, but just to be sure.
                                //CELL will be unloaded if needed after a second round of indexing when all records are loaded
                                last_cell_record->XCLC.Load(); //in-case no XCLC chunk is specified
                                GridXY_LAND[last_cell_record->XCLC->posX][last_cell_record->XCLC->posY] = (Sk::LANDRecord *)curRecord;
                                }
                            break;
                            /*
                        case REV32(ACHR):
                            curRecord = new(achr_buffer) Sk::ACHRRecord(header.data);
                            achr_buffer += sizeof(Sk::ACHRRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->ACHR.push_back(curRecord);
                            break;
                        case REV32(ACRE):
                            curRecord = new(acre_buffer) Sk::ACRERecord(header.data);
                            acre_buffer += sizeof(Sk::ACRERecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->ACRE.push_back(curRecord);
                            break;
                        case REV32(REFR):
                            curRecord = new(refr_buffer) Sk::REFRRecord(header.data);
                            refr_buffer += sizeof(Sk::REFRRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->REFR.push_back(curRecord);
                            break;
                        case REV32(PGRE):
                            curRecord = new(pgre_buffer) Sk::PGRERecord(header.data);
                            pgre_buffer += sizeof(Sk::PGRERecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->PGRE.push_back(curRecord);
                            break;
                        case REV32(PMIS):
                            curRecord = new(pmis_buffer) Sk::PMISRecord(header.data);
                            pmis_buffer += sizeof(Sk::PMISRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->PMIS.push_back(curRecord);
                            break;
                        case REV32(PBEA):
                            curRecord = new(pbea_buffer) Sk::PBEARecord(header.data);
                            pbea_buffer += sizeof(Sk::PBEARecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->PBEA.push_back(curRecord);
                            break;
                        case REV32(PFLA):
                            curRecord = new(pfla_buffer) Sk::PFLARecord(header.data);
                            pfla_buffer += sizeof(Sk::PFLARecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->PFLA.push_back(curRecord);
                            break;
                        case REV32(PCBE):
                            curRecord = new(pcbe_buffer) Sk::PCBERecord(header.data);
                            pcbe_buffer += sizeof(Sk::PCBERecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->PCBE.push_back(curRecord);
                            break;
                        case REV32(NAVM):
                            curRecord = new(navm_buffer) Sk::NAVMRecord(header.data);
                            navm_buffer += sizeof(Sk::NAVMRecord);
                            curRecord->SetParent(last_cell_record, false);
                            last_cell_record->NAVM.push_back(curRecord);
                            break;
                            */
                        default:
                            printer("TES5GRUPRecords<Sk::WRLDRecord>::Read: Warning - Parsing error. Unexpected record type (%c%c%c%c) in file \"%s\".\n", ((char *)&header.type)[0], ((char *)&header.type)[1], ((char *)&header.type)[2], ((char *)&header.type)[3], FileName);
                            #ifdef CBASH_DEBUG_CHUNK
                                peek_around(header.data, PEEK_SIZE);
                            #endif
                            continue;
                            break;
                        }

                    curRecord->flags = header.flags;
                    curRecord->formID = header.formID;
                    curRecord->flagsUnk = header.flagsUnk; //VersionControl1
                    ((TES5Record *)curRecord)->formVersion = header.formVersion;
                    ((TES5Record *)curRecord)->versionControl2[0] = header.versionControl2[0];
                    ((TES5Record *)curRecord)->versionControl2[1] = header.versionControl2[1];

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

                    Sk::CELLRecord *last_wcel_record = NULL;
                    Sk::LANDRecord *last_land_record = NULL;
                    std::vector<Record *> Records;
                    wrld_pool.MakeRecordsVector(Records);
                    for(uint32_t x = 0; x < Records.size(); ++x)
                        {
                        last_wrld_record = (Sk::WRLDRecord *)Records[x];
                        last_wcel_record = (Sk::CELLRecord *)last_wrld_record->CELL;
                        for(uint32_t y = 0; y < last_wrld_record->CELLS.size(); ++y)
                            {
                            last_cell_record = (Sk::CELLRecord *)last_wrld_record->CELLS[y];
                            read_parser.Accept((Record *&)last_cell_record);
                            last_cell_record->XCLC.Load(); //in-case no XCLC chunk is specified
                            posX = last_cell_record->XCLC->posX;
                            posY = last_cell_record->XCLC->posY;

                            if(processor.Flags.IsFixupPlaceables && last_wcel_record != NULL)
                                {
/*
                                for(uint32_t x = 0; x < last_wcel_record->ACHR.size();)
                                    {
                                    //Have to test each record to see if it belongs to the cell. This is determined by its positioning.
                                    curRecord = last_wcel_record->ACHR[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::ACHRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::ACHRRecord *)curRecord)->DATA.value.posY / 4096.0);

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

                                    gridX = (int32_t)floor(((Sk::ACRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::ACRERecord *)curRecord)->DATA.value.posY / 4096.0);

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

                                    //((Sk::REFRRecord *)curRecord)->Data.Load();
                                    gridX = (int32_t)floor(((Sk::REFRRecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::REFRRecord *)curRecord)->DATA.value.posY / 4096.0);

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
                                for(uint32_t x = 0; x < last_wcel_record->PGRE.size();)
                                    {
                                    curRecord = last_wcel_record->PGRE[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::PGRERecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::PGRERecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        last_cell_record->PGRE.push_back(curRecord);
                                        last_wcel_record->PGRE.erase(last_wcel_record->PGRE.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->PMIS.size();)
                                    {
                                    curRecord = last_wcel_record->PMIS[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::PMISRecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::PMISRecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        last_cell_record->PMIS.push_back(curRecord);
                                        last_wcel_record->PMIS.erase(last_wcel_record->PMIS.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->PBEA.size();)
                                    {
                                    curRecord = last_wcel_record->PBEA[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::PBEARecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::PBEARecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        last_cell_record->PBEA.push_back(curRecord);
                                        last_wcel_record->PBEA.erase(last_wcel_record->PBEA.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->PFLA.size();)
                                    {
                                    curRecord = last_wcel_record->PFLA[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::PFLARecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::PFLARecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        last_cell_record->PFLA.push_back(curRecord);
                                        last_wcel_record->PFLA.erase(last_wcel_record->PFLA.begin() + x);
                                        }
                                    else ++x;
                                    }

                                for(uint32_t x = 0; x < last_wcel_record->PCBE.size();)
                                    {
                                    curRecord = last_wcel_record->PCBE[x];
                                    read_parser.Accept(curRecord);

                                    gridX = (int32_t)floor(((Sk::PCBERecord *)curRecord)->DATA.value.posX / 4096.0);
                                    gridY = (int32_t)floor(((Sk::PCBERecord *)curRecord)->DATA.value.posY / 4096.0);

                                    if(processor.Flags.IsMinLoad)
                                        curRecord->Unload();

                                    if(gridX == posX && gridY == posY)
                                        {
                                        last_cell_record->PCBE.push_back(curRecord);
                                        last_wcel_record->PCBE.erase(last_wcel_record->PCBE.begin() + x);
                                        }
                                    else ++x;
                                    }
*/
                                //NAVM's probably shouldn't ever show up in the world cell since they aren't persistent
                                //for(uint32_t x = 0; x < last_wcel_record->NAVM.size();)
                                //    {
                                //    curRecord = last_wcel_record->NAVM[x];
                                //    read_parser.Accept(curRecord);

                                //    gridX = (int32_t)floor(((Sk::NAVMRecord *)curRecord)->DATA.value.posX / 4096.0);
                                //    gridY = (int32_t)floor(((Sk::NAVMRecord *)curRecord)->DATA.value.posY / 4096.0);

                                //    if(processor.Flags.IsMinLoad)
                                //        curRecord->Unload();

                                //    if(gridX == posX && gridY == posY)
                                //        {
                                //        last_cell_record->NAVM.push_back(curRecord);
                                //        last_wcel_record->NAVM.erase(last_wcel_record->NAVM.begin() + x);
                                //        }
                                //    else ++x;
                                //    }
                                }

                            if(processor.Flags.IsIndexLANDs)
                                {
                                last_land_record = (Sk::LANDRecord *)last_cell_record->LAND;
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
/*
                for(uint32_t x = 0; x < orphaned_cell_records->ACHR.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->ACHR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACHR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.achr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->ACRE.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->ACRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan ACRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.acre_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->REFR.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->REFR[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan REFR (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.refr_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->PGRE.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->PGRE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PGRE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.pgre_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->PMIS.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->PMIS[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PMIS (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.pmis_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->PBEA.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->PBEA[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PBEA (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.pbea_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->PFLA.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->PFLA[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PFLA (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.pfla_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->PCBE.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->PCBE[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan PCBE (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.pcbe_pool.destroy(curRecord);
                    }

                for(uint32_t x = 0; x < orphaned_cell_records->NAVM.size(); ++x)
                    {
                    curRecord = orphaned_cell_records->NAVM[x];
                    processor.OrphanedRecords.push_back(curRecord->formID);
                    //printer("TES5GRUPRecords<Sk::CELLRecord>::Read: Warning - Parsing error. Skipped orphan NAVM (%08X) at %08X in file \"%s\"\n", curRecord->formID, curRecord->recData - buffer_start, FileName);
                    #ifdef CBASH_DEBUG_CHUNK
                        peek_around(curRecord->recData, PEEK_SIZE);
                    #endif
                    CELL.navm_pool.destroy(curRecord);
                    }
                    */

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
            uint32_t numWrldRecords = (uint32_t)Records.size();
            if(numWrldRecords == 0)
                return 0;
            uint32_t type = REV32(GRUP);
            uint32_t gType = eTop;
            uint32_t gLabel = REV32(WRLD);
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

            uint32_t numCellRecords = 0;
            uint32_t numSubBlocks = 0;
            uint32_t numChildren = 0;
            uint32_t numChild = 0;

            Sk::WRLDRecord *curWorld = NULL;
            Sk::CELLRecord *curCell = NULL;
            Sk::CELLRecord *curWorldCell = NULL;
            uint32_t worldFormID = 0;
            uint32_t cellFormID = 0;
            int gridX, gridY;
            uint32_t BlockIndex, SubBlockIndex;

            std::map<uint32_t, std::map<uint32_t, std::vector<Sk::CELLRecord *> > > BlockedRecords;
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
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numWrldRecords;
            for(uint32_t x = 0; x < numWrldRecords; ++x)
                {
                curWorld = (Sk::WRLDRecord *)Records[x];
                worldFormID = curWorld->formID;
                collapser.Accept(worldFormID);
                TopSize += curWorld->Write(writer, bMastersChanged, expander, collapser, Expanders);

                curWorldCell = (Sk::CELLRecord *)curWorld->CELL;

                numCellRecords = (uint32_t)curWorld->CELLS.size();
                formCount += numCellRecords;
                for(uint32_t p = 0; p < numCellRecords; ++p)
                    {
                    curCell = (Sk::CELLRecord *)curWorld->CELLS[p];
/*
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

                    for(uint32_t y = 0; y < curCell->PGRE.size(); ++y)
                        if(curCell->PGRE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PGRE[y]);

                    for(uint32_t y = 0; y < curCell->PMIS.size(); ++y)
                        if(curCell->PMIS[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PMIS[y]);

                    for(uint32_t y = 0; y < curCell->PBEA.size(); ++y)
                        if(curCell->PBEA[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PBEA[y]);

                    for(uint32_t y = 0; y < curCell->PFLA.size(); ++y)
                        if(curCell->PFLA[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PFLA[y]);

                    for(uint32_t y = 0; y < curCell->PCBE.size(); ++y)
                        if(curCell->PCBE[y]->IsPersistent())
                            FixedPersistent.push_back(curCell->PCBE[y]);

                    //for(uint32_t y = 0; y < curCell->NAVM.size(); ++y)
                    //    if(curCell->NAVM[y]->IsPersistent())
                    //        FixedPersistent.push_back(curCell->NAVM[y]);
*/
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
                    curWorldCell = (Sk::CELLRecord *)cell_pool.construct((unsigned char *)NULL, curWorld, false);
                    curWorldCell->formID = FormIDHandler.NextExpandedFormID();
                    curWorld->CELL = curWorldCell;
                    curWorldCell->IsInterior(false);
                    curWorldCell->IsHasWater(true);
                    curWorldCell->IsPersistent(true);
                    curWorldCell->XCLC.Load();
                    if(!CloseMod)
                        indexer.Accept((Record *&)curWorldCell);
                    }

                if(curWorldCell != NULL || curWorld->CELLS.size() > 0)
                    {
                    gType = eWorld;
                    writer.file_write(&type, 4);
                    worldSizePos = writer.file_tell();
                    writer.file_write(&worldSize, 4); //Placeholder: will be overwritten with correct value later.
                    writer.file_write(&worldFormID, 4);
                    writer.file_write(&gType, 4);
                    writer.file_write(&stamp, 4);
                    writer.file_write(&unknown, 4);
                    ++formCount;
                    worldSize = 24;

                    if(curWorldCell != NULL)
                        {
                        curCell = curWorldCell;
                        cellFormID = curCell->formID;
                        collapser.Accept(cellFormID);
                        worldSize += curCell->Write(writer, bMastersChanged, expander, collapser, Expanders);
                        ++formCount;

                        if(curCell->LAND != NULL)
                            Temporary.push_back(curCell->LAND);
                        if(CloseMod)
                            curCell->LAND = NULL;

                        uint32_t ignored_count = 0;
/*
                        for(uint32_t y = 0; y < curCell->ACHR.size(); ++y)
                            {
                            if(curCell->ACHR[y]->IsPersistent())
                                Persistent.push_back(curCell->ACHR[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->ACRE.size(); ++y)
                            {
                            if(curCell->ACRE[y]->IsPersistent())
                                Persistent.push_back(curCell->ACRE[y]);
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

                        for(uint32_t y = 0; y < curCell->PGRE.size(); ++y)
                            {
                            if(curCell->PGRE[y]->IsPersistent())
                                Persistent.push_back(curCell->PGRE[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->PMIS.size(); ++y)
                            {
                            if(curCell->PMIS[y]->IsPersistent())
                                Persistent.push_back(curCell->PMIS[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->PBEA.size(); ++y)
                            {
                            if(curCell->PBEA[y]->IsPersistent())
                                Persistent.push_back(curCell->PBEA[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->PFLA.size(); ++y)
                            {
                            if(curCell->PFLA[y]->IsPersistent())
                                Persistent.push_back(curCell->PFLA[y]);
                            else
                                ignored_count++;
                            }

                        for(uint32_t y = 0; y < curCell->PCBE.size(); ++y)
                            {
                            if(curCell->PCBE[y]->IsPersistent())
                                Persistent.push_back(curCell->PCBE[y]);
                            else
                                ignored_count++;
                            }
                        ignored_count += curCell->NAVM.size();
*/
                        if(ignored_count)
                            printer("TES5GRUPRecords<Sk::WRLDRecord>::Write: Warning - Information lost. Ignored %u VWD or Temporary records in the world cell: %08X", ignored_count, worldFormID);

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
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            childrenSize = 24;

                            //World CELL should only have persistent objects in it
                            gType = eCellPersistent;
                            writer.file_write(&type, 4);
                            childSizePos = writer.file_tell();
                            writer.file_write(&childSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&cellFormID, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            childSize = 24;

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
                            /*
                            for(uint32_t x = 0; x < curCell->ACHR.size(); ++x)
                                CELL.achr_pool.destroy(curCell->ACHR[x]);

                            for(uint32_t x = 0; x < curCell->ACRE.size(); ++x)
                                CELL.acre_pool.destroy(curCell->ACRE[x]);

                            for(uint32_t x = 0; x < curCell->REFR.size(); ++x)
                                CELL.refr_pool.destroy(curCell->REFR[x]);

                            for(uint32_t x = 0; x < curCell->PGRE.size(); ++x)
                                CELL.pgre_pool.destroy(curCell->PGRE[x]);

                            for(uint32_t x = 0; x < curCell->PMIS.size(); ++x)
                                CELL.pmis_pool.destroy(curCell->PMIS[x]);

                            for(uint32_t x = 0; x < curCell->PBEA.size(); ++x)
                                CELL.pbea_pool.destroy(curCell->PBEA[x]);

                            for(uint32_t x = 0; x < curCell->PFLA.size(); ++x)
                                CELL.pfla_pool.destroy(curCell->PFLA[x]);

                            for(uint32_t x = 0; x < curCell->PCBE.size(); ++x)
                                CELL.pcbe_pool.destroy(curCell->PCBE[x]);

                            for(uint32_t x = 0; x < curCell->NAVM.size(); ++x)
                                CELL.navm_pool.destroy(curCell->NAVM[x]);
                            */

                            land_pool.destroy(curCell->LAND);
                            cell_pool.destroy(curCell);
                            }
                        }

                    for(std::map<uint32_t, std::map<uint32_t, std::vector<Sk::CELLRecord *> > >::iterator curBlock = BlockedRecords.begin(); curBlock != BlockedRecords.end(); ++curBlock)
                        {
                        gType = eExteriorBlock;
                        writer.file_write(&type, 4);
                        blockSizePos = writer.file_tell();
                        writer.file_write(&blockSize, 4); //Placeholder: will be overwritten with correct value later.
                        writer.file_write(&curBlock->first, 4);
                        writer.file_write(&gType, 4);
                        writer.file_write(&stamp, 4);
                        writer.file_write(&unknown, 4);
                        ++formCount;
                        blockSize = 24;

                        for(std::map<uint32_t, std::vector<Sk::CELLRecord *> >::iterator curSubBlock = curBlock->second.begin(); curSubBlock != curBlock->second.end(); ++curSubBlock)
                            {
                            gType = eExteriorSubBlock;
                            writer.file_write(&type, 4);
                            subBlockSizePos = writer.file_tell();
                            writer.file_write(&subBlockSize, 4); //Placeholder: will be overwritten with correct value later.
                            writer.file_write(&curSubBlock->first, 4);
                            writer.file_write(&gType, 4);
                            writer.file_write(&stamp, 4);
                            writer.file_write(&unknown, 4);
                            ++formCount;
                            subBlockSize = 24;

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
/*
                                for(uint32_t y = 0; y < curCell->ACHR.size(); ++y)
                                    {
                                    if(curCell->ACHR[y]->IsVWD())
                                        VWD.push_back(curCell->ACHR[y]);
                                    else
                                        Temporary.push_back(curCell->ACHR[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->ACRE.size(); ++y)
                                    {
                                    if(curCell->ACRE[y]->IsVWD())
                                        VWD.push_back(curCell->ACRE[y]);
                                    else
                                        Temporary.push_back(curCell->ACRE[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->REFR.size(); ++y)
                                    {
                                    if(curCell->REFR[y]->IsVWD())
                                        VWD.push_back(curCell->REFR[y]);
                                    else
                                        Temporary.push_back(curCell->REFR[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->PGRE.size(); ++y)
                                    {
                                    if(curCell->PGRE[y]->IsVWD())
                                        VWD.push_back(curCell->PGRE[y]);
                                    else
                                        Temporary.push_back(curCell->PGRE[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->PMIS.size(); ++y)
                                    {
                                    if(curCell->PMIS[y]->IsVWD())
                                        VWD.push_back(curCell->PMIS[y]);
                                    else
                                        Temporary.push_back(curCell->PMIS[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->PBEA.size(); ++y)
                                    {
                                    if(curCell->PBEA[y]->IsVWD())
                                        VWD.push_back(curCell->PBEA[y]);
                                    else
                                        Temporary.push_back(curCell->PBEA[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->PFLA.size(); ++y)
                                    {
                                    if(curCell->PFLA[y]->IsVWD())
                                        VWD.push_back(curCell->PFLA[y]);
                                    else
                                        Temporary.push_back(curCell->PFLA[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->PCBE.size(); ++y)
                                    {
                                    if(curCell->PCBE[y]->IsVWD())
                                        VWD.push_back(curCell->PCBE[y]);
                                    else
                                        Temporary.push_back(curCell->PCBE[y]);
                                    }

                                for(uint32_t y = 0; y < curCell->NAVM.size(); ++y)
                                    Temporary.push_back(curCell->NAVM[y]);
*/
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
                                    writer.file_write(&unknown, 4);
                                    ++formCount;
                                    childrenSize = 24;

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
                                        writer.file_write(&unknown, 4);
                                        ++formCount;
                                        childSize = 24;

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
                                        writer.file_write(&unknown, 4);
                                        ++formCount;
                                        childSize = 24;

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
                                    /*
                                    for(uint32_t x = 0; x < curCell->ACHR.size(); ++x)
                                        CELL.achr_pool.destroy(curCell->ACHR[x]);

                                    for(uint32_t x = 0; x < curCell->ACRE.size(); ++x)
                                        CELL.acre_pool.destroy(curCell->ACRE[x]);

                                    for(uint32_t x = 0; x < curCell->REFR.size(); ++x)
                                        CELL.refr_pool.destroy(curCell->REFR[x]);

                                    for(uint32_t x = 0; x < curCell->PGRE.size(); ++x)
                                        CELL.pgre_pool.destroy(curCell->PGRE[x]);

                                    for(uint32_t x = 0; x < curCell->PMIS.size(); ++x)
                                        CELL.pmis_pool.destroy(curCell->PMIS[x]);

                                    for(uint32_t x = 0; x < curCell->PBEA.size(); ++x)
                                        CELL.pbea_pool.destroy(curCell->PBEA[x]);

                                    for(uint32_t x = 0; x < curCell->PFLA.size(); ++x)
                                        CELL.pfla_pool.destroy(curCell->PFLA[x]);

                                    for(uint32_t x = 0; x < curCell->PCBE.size(); ++x)
                                        CELL.pcbe_pool.destroy(curCell->PCBE[x]);

                                    for(uint32_t x = 0; x < curCell->NAVM.size(); ++x)
                                        CELL.navm_pool.destroy(curCell->NAVM[x]);
                                    */

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
                /*
                //All destructors ran earlier, pools are entirely free
                CELL.achr_pool.purge_no_destructors();
                CELL.acre_pool.purge_no_destructors();
                CELL.refr_pool.purge_no_destructors();
                CELL.pgre_pool.purge_no_destructors();
                CELL.pmis_pool.purge_no_destructors();
                CELL.pbea_pool.purge_no_destructors();
                CELL.pfla_pool.purge_no_destructors();
                CELL.pcbe_pool.purge_no_destructors();
                CELL.navm_pool.purge_no_destructors();
                */
                cell_pool.purge_no_destructors();
                land_pool.purge_no_destructors();
                wrld_pool.purge_no_destructors();
                }
            writer.file_write(TopSizePos, &TopSize, 4);

            return formCount;
            }
    };
