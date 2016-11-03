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
#include "Common.h"
//#include "GenericRecord.h"
#include <vector>
#include <malloc.h>

template<class T, uint32_t RecType, uint32_t AllocUnit>
class RecordPoolAllocator
    {
    private:
        unsigned char *freed_position;
        std::vector<unsigned char *> buffers;

    public:
        RecordPoolAllocator():
            freed_position(NULL)
            {
            //reserve(AllocUnit);
            }

        ~RecordPoolAllocator()
            {
            purge_with_destructors();
            }

        //uint32_t try_to_free()
        //    {
        //    //attempts to free any unused buffers. Will mostly fail to free any memory unless a large number of records have been destroyed.
        //    //this is a relatively slow function. Don't call it unless necessary.
        //    uint32_t freed_bytes = 0;
        //    if(freed_position)
        //        {
        //        boost::unordered_set<unsigned char *> free_set;
        //        MakeFreeSet(free_set);
        //        for(int32_t p = (int32_t)buffers.size() - 1;p >= 0; --p)
        //            {
        //            unsigned char *buffer = buffers[p];
        //            uint32_t buffer_size = (uint32_t)_msize(buffer);
        //            //in case malloc returned more than the requested amount
        //            buffer_size -= buffer_size % sizeof(T);

        //            unsigned char *end_of_buffer = buffer + buffer_size;
        //            bool buffer_in_use = false;

        //            for(unsigned char *last_position = buffer;last_position < end_of_buffer; last_position += sizeof(T))
        //                {
        //                if(free_set.find(last_position) == free_set.end())
        //                    {
        //                    buffer_in_use = true;
        //                    break;
        //                    }
        //                }

        //            if(!buffer_in_use)
        //                {
        //                uint32_t max_count = buffer_size / sizeof(T);
        //                uint32_t removed_count = 0;

        //                //Remove any freed entries at the head of the list
        //                while(removed_count < max_count && (freed_position >= buffer && freed_position < end_of_buffer))
        //                    {
        //                    removed_count++;
        //                    freed_position = *(unsigned char **)freed_position;
        //                    };


        //                for(unsigned char *last_position = freed_position, *next_position = NULL; removed_count < max_count && (last_position != NULL);last_position = next_position)
        //                    {
        //                    next_position = *(unsigned char **)last_position;
        //                    while(next_position >= buffer && next_position < end_of_buffer)
        //                        {
        //                        removed_count++;
        //                        next_position = *(unsigned char **)next_position;
        //                        *(unsigned char **)last_position = next_position;
        //                        };
        //                    }

        //                freed_bytes += (uint32_t)_msize(buffer);
        //                free(buffer);
        //                buffers.erase(buffers.begin() + p);
        //                }
        //            }
        //        }
        //    return freed_bytes;
        //    }

        void purge_no_destructors()
            {
            for(uint32_t p = 0;p < buffers.size(); p++)
                free(buffers[p]);
            buffers.clear();
            //_heapmin();
            freed_position = NULL;
            }

        void purge_with_destructors()
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            for(uint32_t p = 0;p < buffers.size(); p++)
                {
                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        {
                        //printer("Destroying: %08X\n", ((Record *)last_position)->formID);
                        ((Record *)last_position)->~Record();
                        }
                    }
                free(buffers[p]);
                }
            buffers.clear();
            freed_position = NULL;
            }

        void reserve(uint32_t elements)
            {
            //Allocate memory
            unsigned char *buffer = (unsigned char *)malloc(sizeof(T) * elements);
            if(buffer == 0)
                throw std::bad_alloc();
            buffers.push_back(buffer);
            //memset(buffer, 0x00, buffer_size);

            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
            for(unsigned char *last_position = buffer + (sizeof(T) * elements) - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
                {
                *(unsigned char **)last_position = freed_position;
                freed_position = last_position;
                }
            }

        Record *construct(unsigned char *recData, void *Parent, bool IsMod)
            {
            if(freed_position == NULL)
                reserve(AllocUnit);
            unsigned char *next_position = *(unsigned char **)freed_position;
            Record * curRecord = new (freed_position) T(recData);
            curRecord->SetParent(Parent, IsMod);
            freed_position = next_position;
            return curRecord;
            }

        Record *construct(Record *SourceRecord, void *Parent, bool IsMod)
            {
            if(freed_position == NULL)
                reserve(AllocUnit);
            unsigned char *next_position = *(unsigned char **)freed_position;
            Record * curRecord = new (freed_position) T((T *)SourceRecord);
            curRecord->SetParent(Parent, IsMod);
            freed_position = next_position;
            return curRecord;
            }

        void destroy(Record *curRecord)
            {
            if(curRecord == NULL)
                return;
            curRecord->~Record();
            *(unsigned char **)curRecord = freed_position;
            freed_position = (unsigned char *)curRecord;
            }

        void deallocate(Record *curRecord)
            {
            if(curRecord == NULL)
                return;
            *(unsigned char **)curRecord = freed_position;
            freed_position = (unsigned char *)curRecord;
            }

        uint32_t object_capacity()
            {
            uint32_t size = 0;
            for(uint32_t p = 0;p < buffers.size(); p++)
                {
                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                size += buffer_size / sizeof(T);
                }

            return size;
            }

        uint32_t free_object_capacity()
            {
            uint32_t size = 0;

            if(freed_position)
                {
                size++;
                for(unsigned char *next_position = *(unsigned char **)freed_position; next_position != NULL; next_position = *(unsigned char **)next_position)
                    {
                    size++;
                    }
                }

            return size;
            }

        uint32_t used_object_capacity()
            {
            return object_capacity() - free_object_capacity();
            }

        uint32_t bytes_capacity()
            {
            return object_capacity() * sizeof(T);
            }

        uint32_t free_bytes_capacity()
            {
            return free_object_capacity() * sizeof(T);
            }

        uint32_t used_bytes_capacity()
            {
            return used_object_capacity() * sizeof(T);
            }

        bool VisitRecords(RecordOp &op)
            {
            boost::unordered_set<unsigned char *> free_set;

            MakeFreeSet(free_set);
            for(uint32_t p = 0;p < buffers.size(); p++)
                {
                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        {
                        if(op.Accept((Record *&)last_position))
                            return true;
                        }
                    }
                }
            return false;
            }

        void MakeFreeSet(boost::unordered_set<unsigned char *> &free_set)
            {
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                free_set.insert(freed_position);
                while(next_position != NULL)
                    {
                    free_set.insert(next_position);
                    next_position = *(unsigned char **)next_position;
                    };
                }
            }

        void MakeFreeVector(std::vector<unsigned char *> &free_vector)
            {
            if(freed_position)
                {
                unsigned char *next_position = *(unsigned char **)freed_position;
                free_vector.push_back(freed_position);
                while(next_position != NULL)
                    {
                    free_vector.push_back(next_position);
                    next_position = *(unsigned char **)next_position;
                    };
                std::sort(free_vector.begin(), free_vector.end());
                }
            }

        void MakeRecordsVector(std::vector<Record *> &Records)
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            Records.reserve(object_capacity() - free_set.size());
            for(uint32_t p = 0;p < buffers.size(); p++)
                {
                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        Records.push_back((Record *)last_position);
                    }
                }
            }

        void MakeRecordsArray(RECORDIDARRAY Records)
            {
            boost::unordered_set<unsigned char *> free_set;
            MakeFreeSet(free_set);
            uint32_t pos = 0;
            for(uint32_t p = 0;p < buffers.size(); p++)
                {
                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
                //in case malloc returned more than the requested amount
                buffer_size -= buffer_size % sizeof(T);
                unsigned char *end_of_buffer = buffers[p] + buffer_size;
                for(unsigned char *last_position = buffers[p];last_position < end_of_buffer; last_position += sizeof(T))
                    {
                    if(free_set.find(last_position) == free_set.end())
                        ((RECORDIDARRAY)Records)[pos++] = (Record *)last_position;
                    }
                }
            }

        void add_buffer(unsigned char *buffer)
            {
            buffers.push_back(buffer);
            return;
            }
    };

//template<class T, uint32_t AllocUnit>
//class PODPoolAllocator
//    {
//    private:
//        unsigned char *freed_position;
//        std::vector<unsigned char *> buffers;
//
//    public:
//        PODPoolAllocator():
//            freed_position(NULL)
//            {
//            //reserve(AllocUnit);
//            }
//
//        ~PODPoolAllocator()
//            {
//            purge_no_destructors();
//            }
//
//        void purge_no_destructors()
//            {
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                free(buffers[p]);
//            buffers.clear();
//            //_heapmin();
//            freed_position = NULL;
//            }
//
//        void reserve(uint32_t elements)
//            {
//            //Allocate memory
//            uint32_t buffer_size = sizeof(T) * elements;
//            unsigned char *buffer = (unsigned char *)malloc(buffer_size);
//            if(buffer == 0)
//                throw std::bad_alloc();
//            //memset(buffer, 0x00, buffer_size);
//
//            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
//            //unsigned char *end_of_buffer = buffer + buffer_size;
//            for(unsigned char *last_position = buffer + buffer_size - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
//                {
//                *(unsigned char **)last_position = freed_position;
//                freed_position = last_position;
//                }
//
//            //Save the buffer so it can be deallocated later
//            buffers.push_back(buffer);
//            }
//
//        Record *construct()
//            {
//            //See if any memory is free
//            if(freed_position)
//                {
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                Record * curRecord = new (freed_position) T();
//                freed_position = next_position;
//                return curRecord;
//                }
//            //Otherwise, allocate more memory
//            else
//                {
//                reserve(AllocUnit);
//                return construct(recData);
//                }
//            throw std::bad_alloc();
//            return NULL;
//            }
//
//        void deallocate(T *curPOD)
//            {
//            if(curPOD == NULL)
//                return;
//            *(unsigned char **)curPOD = freed_position;
//            freed_position = (unsigned char *)curPOD;
//            }
//
//        uint32_t object_capacity()
//            {
//            uint32_t size = 0;
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                {
//                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size / sizeof(T);
//                }
//
//            return size;
//            }
//
//        uint32_t free_object_capacity()
//            {
//            uint32_t size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size;
//            }
//
//        uint32_t used_object_capacity()
//            {
//            return object_capacity() - free_object_capacity();
//            }
//
//        uint32_t bytes_capacity()
//            {
//            uint32_t size = 0;
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                {
//                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size;
//                }
//
//            return size;
//            }
//
//        uint32_t free_bytes_capacity()
//            {
//            uint32_t size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size * sizeof(T);
//            }
//
//        uint32_t used_bytes_capacity()
//            {
//            return bytes_capacity() - free_bytes_capacity();
//            }
//    };

//class StringPoolAllocator
//    {
//    private:
//        static char null_term;
//        PODPoolAllocator<4, 1024>   pool4;
//        PODPoolAllocator<6, 1024>   pool6;
//        PODPoolAllocator<8, 1024>   pool8;
//        PODPoolAllocator<10, 1024>  pool10;
//        PODPoolAllocator<12, 1024>  pool12;
//        PODPoolAllocator<14, 1024>  pool14;
//        PODPoolAllocator<16, 1024>  pool16;
//        PODPoolAllocator<18, 1024>  pool18;
//        PODPoolAllocator<20, 1024>  pool20;
//        PODPoolAllocator<22, 1024>  pool22;
//        PODPoolAllocator<24, 1024>  pool24;
//        PODPoolAllocator<26, 1024>  pool26;
//        PODPoolAllocator<28, 1024>  pool28;
//        PODPoolAllocator<30, 1024>  pool30;
//        PODPoolAllocator<32, 1024>  pool32;
//        PODPoolAllocator<34, 1024>  pool34;
//        PODPoolAllocator<36, 1024>  pool36;
//        PODPoolAllocator<38, 1024>  pool38;
//        PODPoolAllocator<40, 1024>  pool40;
//        PODPoolAllocator<48, 1024>  pool48;
//        PODPoolAllocator<56, 1024>  pool56;
//        PODPoolAllocator<64, 1024>  pool64;
//        PODPoolAllocator<128, 1024>  pool128;
//        PODPoolAllocator<256, 1024>  pool256;
//        unsigned char *freed_position;
//        std::vector<char *> buffers;
//
//    public:
//        StringPoolAllocator():
//            freed_position(NULL),
//            null_term(0x00)
//            {
//            //reserve(AllocUnit);
//            }
//
//        ~StringPoolAllocator()
//            {
//            purge_no_destructors();
//            }
//
//        void purge_no_destructors()
//            {
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                free(buffers[p]);
//            buffers.clear();
//            //_heapmin();
//            freed_position = NULL;
//            }
//
//        void reserve(uint32_t elements)
//            {
//            //Allocate memory
//            uint32_t buffer_size = sizeof(T) * elements;
//            unsigned char *buffer = (unsigned char *)malloc(buffer_size);
//            if(buffer == 0)
//                throw std::bad_alloc();
//            //memset(buffer, 0x00, buffer_size);
//
//            //Populate the free linked list in reverse so that the first freed_position is at the beginning of the buffer
//            //unsigned char *end_of_buffer = buffer + buffer_size;
//            for(unsigned char *last_position = buffer + buffer_size - sizeof(T);last_position >= buffer; last_position -= sizeof(T))
//                {
//                *(unsigned char **)last_position = freed_position;
//                freed_position = last_position;
//                }
//
//            //Save the buffer so it can be deallocated later
//            buffers.push_back(buffer);
//            }
//
//        Record *construct()
//            {
//            //See if any memory is free
//            if(freed_position)
//                {
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                Record * curRecord = new (freed_position) T();
//                freed_position = next_position;
//                return curRecord;
//                }
//            //Otherwise, allocate more memory
//            else
//                {
//                reserve(AllocUnit);
//                return construct(recData);
//                }
//            throw std::bad_alloc();
//            return NULL;
//            }
//
//        void deallocate(T *curPOD)
//            {
//            if(curPOD == NULL)
//                return;
//            *(unsigned char **)curPOD = freed_position;
//            freed_position = (unsigned char *)curPOD;
//            }
//
//        uint32_t object_capacity()
//            {
//            uint32_t size = 0;
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                {
//                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size / sizeof(T);
//                }
//
//            return size;
//            }
//
//        uint32_t free_object_capacity()
//            {
//            uint32_t size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size;
//            }
//
//        uint32_t used_object_capacity()
//            {
//            return object_capacity() - free_object_capacity();
//            }
//
//        uint32_t bytes_capacity()
//            {
//            uint32_t size = 0;
//            for(uint32_t p = 0;p < buffers.size(); p++)
//                {
//                uint32_t buffer_size = (uint32_t)_msize(buffers[p]);
//                //in case malloc returned more than the requested amount
//                buffer_size -= buffer_size % sizeof(T);
//                size += buffer_size;
//                }
//
//            return size;
//            }
//
//        uint32_t free_bytes_capacity()
//            {
//            uint32_t size = 0;
//
//            if(freed_position)
//                {
//                size++;
//                unsigned char *next_position = *(unsigned char **)freed_position;
//                while(next_position != NULL)
//                    {
//                    size++;
//                    next_position = *(unsigned char **)next_position;
//                    };
//                }
//
//            return size * sizeof(T);
//            }
//
//        uint32_t used_bytes_capacity()
//            {
//            return bytes_capacity() - free_bytes_capacity();
//            }
//    };