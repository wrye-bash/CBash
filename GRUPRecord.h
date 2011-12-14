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

template<class T, UINT32 RecType, UINT32 AllocUnit, bool IsKeyedByEditorID=false>
class GRUPRecords
    {
    public:
        RecordPoolAllocator<T, RecType, AllocUnit> pool;
        UINT32 stamp;

        GRUPRecords():
            stamp(134671)
            {
            //
            }

        ~GRUPRecords()
            {
            //
            }

        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, STRING &FileName)
            {
            stamp = *(UINT32 *)buffer_position;
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
            UINT32 recordSize = 0;
            RecordHeader header;

            std::vector<RecordHeader> records;
            records.reserve((UINT32)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(RecType) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(UINT32 *)buffer_position;
                buffer_position += 4;
                recordSize = *(UINT32 *)buffer_position;
                buffer_position += 4;
                header.flags = *(UINT32 *)buffer_position;
                buffer_position += 4;
                header.formID = *(FORMID *)buffer_position;
                buffer_position += 4;
                header.flagsUnk = *(UINT32 *)buffer_position;
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
                unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (UINT32)records.size());
                if(buffer == 0)
                    throw std::bad_alloc();
                pool.add_buffer(buffer);

                //Construct the records
                for(UINT32 x = 0; x < records.size();++x)
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

        UINT32 Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            pool.MakeRecordsVector(Records);
            UINT32 numRecords = (UINT32)Records.size();
            if(numRecords == 0)
                return 0;

            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 TopLabel = RecType;
            UINT32 formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            ++formCount;
            TopSize = 20;

            formCount += numRecords;
            for(UINT32 p = 0; p < numRecords; p++)
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                pool.purge_with_destructors();

            return formCount;
            }
    };

#include "Oblivion/GRUPRecord.h"

template<class T, UINT32 RecType, UINT32 AllocUnit, bool IsKeyedByEditorID=false>
class FNVGRUPRecords
    {
    public:
        RecordPoolAllocator<T, RecType, AllocUnit> pool;
        UINT32 stamp, unknown;

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

        bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, STRING &FileName)
            {
            stamp = *(UINT32 *)buffer_position;
            buffer_position += 4;
            unknown = *(UINT32 *)buffer_position;
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
            UINT32 recordSize = 0;
            RecordHeader header;

            std::vector<RecordHeader> records;
            records.reserve((UINT32)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
            while(buffer_position < group_buffer_end){
                if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
                    processor.NewTypes.count(RecType) > 0)
                    {
                    buffer_position = group_buffer_end;
                    break;
                    }

                //Assumes that all records in a generic group are of the same type
                header.type = *(UINT32 *)buffer_position;
                buffer_position += 4;
                recordSize = *(UINT32 *)buffer_position;
                buffer_position += 4;
                header.flags = *(UINT32 *)buffer_position;
                buffer_position += 4;
                header.formID = *(FORMID *)buffer_position;
                buffer_position += 4;
                header.flagsUnk = *(UINT32 *)buffer_position; //VersionControl1
                buffer_position += 4;
                header.formVersion = *(UINT16 *)buffer_position;
                buffer_position += 2;
                header.versionControl2[0] = *(UINT8 *)buffer_position;
                buffer_position++;
                header.versionControl2[1] = *(UINT8 *)buffer_position;
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
                unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (UINT32)records.size());
                if(buffer == 0)
                    throw std::bad_alloc();
                pool.add_buffer(buffer);

                //Construct the records
                for(UINT32 x = 0; x < records.size();++x)
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

        UINT32 Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
            {
            std::vector<Record *> Records;
            pool.MakeRecordsVector(Records);
            UINT32 numRecords = (UINT32)Records.size();
            if(numRecords == 0)
                return 0;

            UINT32 type = REV32(GRUP);
            UINT32 gType = eTop;
            UINT32 TopSize = 0;
            UINT32 TopLabel = RecType;
            UINT32 formCount = 0;

            //Top GRUP Header
            writer.file_write(&type, 4);
            UINT32 TopSizePos = writer.file_tell();
            writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
            writer.file_write(&TopLabel, 4);
            writer.file_write(&gType, 4);
            writer.file_write(&stamp, 4);
            writer.file_write(&unknown, 4);
            ++formCount;
            TopSize = 24;

            formCount += numRecords;
            for(UINT32 p = 0; p < numRecords; p++)
                TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

            writer.file_write(TopSizePos, &TopSize, 4);
            if(CloseMod)
                pool.purge_with_destructors();

            return formCount;
            }
    };

#include "FalloutNewVegas/GRUPRecord.h"

template<class T, UINT32 RecType, UINT32 AllocUnit, bool IsKeyedByEditorID=false>
class TES5GRUPRecords
    {
    public:
      RecordPoolAllocator<T, RecType, AllocUnit> pool;
      UINT32 stamp, unknown;

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

      bool Read(unsigned char *&buffer_start, unsigned char *&buffer_position, unsigned char *&group_buffer_end, RecordOp &indexer, RecordOp &parser, std::vector<Record *> &DeletedRecords, RecordProcessor &processor, STRING &FileName)
      {
	stamp = *(UINT32 *)buffer_position;
	buffer_position += 4;
	unknown = *(UINT32 *)buffer_position;
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
	UINT32 recordSize = 0;
	RecordHeader header;

	std::vector<RecordHeader> records;
	records.reserve((UINT32)(group_buffer_end - buffer_position) / sizeof(T)); //gross overestimation, but good enough
	while(buffer_position < group_buffer_end){
	  if((processor.IsSkipAllRecords && processor.IsTrackNewTypes) &&
	    processor.NewTypes.count(RecType) > 0)
	  {
	    buffer_position = group_buffer_end;
	    break;
	  }

	  //Assumes that all records in a generic group are of the same type
	  header.type = *(UINT32 *)buffer_position;
	  buffer_position += 4;
	  recordSize = *(UINT32 *)buffer_position;
	  buffer_position += 4;
	  header.flags = *(UINT32 *)buffer_position;
	  buffer_position += 4;
	  header.formID = *(FORMID *)buffer_position;
	  buffer_position += 4;
	  header.flagsUnk = *(UINT32 *)buffer_position; //VersionControl1
	  buffer_position += 4;
	  header.formVersion = *(UINT16 *)buffer_position;
	  buffer_position += 2;
	  header.versionControl2[0] = *(UINT8 *)buffer_position;
	  buffer_position++;
	  header.versionControl2[1] = *(UINT8 *)buffer_position;
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
	  unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * (UINT32)records.size());
	  if(buffer == 0)
	    throw std::bad_alloc();
	  pool.add_buffer(buffer);

	  //Construct the records
	  for(UINT32 x = 0; x < records.size();++x)
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
	    if(curRecord->IsDeleted())
	      DeletedRecords.push_back(curRecord);
	    //Index it for fast, random lookup
	    indexer.Accept(curRecord);
	  }

	  records.clear();
	}

	return true;
      }

      UINT32 Write(FileWriter &writer, std::vector<FormIDResolver *> &Expanders, FormIDResolver &expander, FormIDResolver &collapser, const bool &bMastersChanged, bool CloseMod)
      {
	std::vector<Record *> Records;
	pool.MakeRecordsVector(Records);
	UINT32 numRecords = (UINT32)Records.size();
	if(numRecords == 0)
	  return 0;

	UINT32 type = REV32(GRUP);
	UINT32 gType = eTop;
	UINT32 TopSize = 0;
	UINT32 TopLabel = RecType;
	UINT32 formCount = 0;

	//Top GRUP Header
	writer.file_write(&type, 4);
	UINT32 TopSizePos = writer.file_tell();
	writer.file_write(&TopSize, 4); //Placeholder: will be overwritten with correct value later.
	writer.file_write(&TopLabel, 4);
	writer.file_write(&gType, 4);
	writer.file_write(&stamp, 4);
	writer.file_write(&unknown, 4);
	++formCount;
	TopSize = 24;

	formCount += numRecords;
	for(UINT32 p = 0; p < numRecords; p++)
	  TopSize += Records[p]->Write(writer, bMastersChanged, expander, collapser, Expanders);

	writer.file_write(TopSizePos, &TopSize, 4);
	if(CloseMod)
	  pool.purge_with_destructors();

	return formCount;
      }
    };

#include "Skyrim/GRUPRecord.h"
