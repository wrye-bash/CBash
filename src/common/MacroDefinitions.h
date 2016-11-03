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
//don't touch

#include "Types.h"

#ifdef _M_X64
    //#pragma message("Compiling with x64 compatibility")
    #define CBASH_X64_COMPATIBILITY
    //#error "CBASH is untested as a x64 build"
#elif defined(_M_IX86)
    //#pragma message("Compiling with x86 compatibility")
    #define CBASH_X64_COMPATIBILITY
#else
    #error "Unknown platform"
#endif

//#define CBASH_X64_COMPATIBILITY

//define or undef as desired
#undef CBASH_PROFILING
#undef CBASH_CHUNK_WARN
#undef CBASH_CHUNK_LCHECK
#define CBASH_DEBUG_VARS

#define CBASH_DEBUG_CHUNK

//Peek into the data before and after to see what's up
#ifdef CBASH_DEBUG_CHUNK
    #define CBASH_CHUNK_DEBUG   for(int32_t x = 32; x > 0; x--) \
                                    printer("%02X ", buffer[-x]); \
                                for(uint32_t x = 0; x < 32; x++) \
                                    printer("%02X ", buffer[x]); \
                             /* printer("\n\n");*/ \
                             /* for(int32_t x = 32; x > 0; x--)*/ \
                             /*     printer("%c", buffer[-x]);*/ \
                             /* for(uint32_t x = 0; x < 32; x++)*/ \
                             /*     printer("%c", buffer[x]);*/ \
                                printer("\n");
#else
    //don't touch
    #define CBASH_CHUNK_DEBUG
#endif

#ifndef PEEK_SIZE
    #define PEEK_SIZE 32
#endif

//These require CBASH_PROFILING to be defined
#ifdef CBASH_PROFILING
    //define or undef as desired
    #define CBASH_CALLTIMING
    #define CBASH_CALLCOUNT
    #undef CBASH_TRACE
#else
    //don't touch
    #undef CBASH_CALLTIMING
    #undef CBASH_CALLCOUNT
    #undef CBASH_TRACE
#endif

#ifdef CBASH_TRACE
    #define TRACE_FUNC printer("%s\n", __FUNCTION__)
#else
    #define TRACE_FUNC
#endif

#ifdef CBASH_PROFILING
    #define PROFILE_FUNC TRACE_FUNC;COUNT_FUNC;TIME_FUNC;
#else
    #define PROFILE_FUNC
#endif

#ifdef CBASH_CALLTIMING
    #include <windows.h>
    #include <map>

    extern std::map<char *, double> CallTime;

    typedef struct
        {
        LARGE_INTEGER start;
        LARGE_INTEGER stop;
        } stopWatch;

    class CStopWatch
        {
        private:
            stopWatch timer;
            LARGE_INTEGER frequency;
            char *FunctionName;
            bool did_end;

        public:
            CStopWatch(char *FName):
                FunctionName(FName),
                did_end(false)
                {
                timer.start.QuadPart=0;
                timer.stop.QuadPart=0;
                QueryPerformanceFrequency(&frequency);
                QueryPerformanceCounter(&timer.start);
                }

            ~CStopWatch()
                {
                end();
                }
            void end()
                {
                if(did_end)
                    return;
                QueryPerformanceCounter(&timer.stop);
                LARGE_INTEGER time;
                time.QuadPart = timer.stop.QuadPart - timer.start.QuadPart;
                CallTime[FunctionName] = CallTime[FunctionName] + ((double)time.QuadPart / (double)frequency.QuadPart);
                did_end = true;
                }
        };
    #define TIME_FUNC CStopWatch cbtimer(__FUNCTION__)
#else
    #define TIME_FUNC
#endif

#ifdef CBASH_CALLCOUNT
    #include <map>
    extern std::map<char *, unsigned long> CallCount;

    class CCounter
        {
        private:
            char *FunctionName;
            bool did_end;

        public:
            CCounter(char *FName):
                FunctionName(FName),
                did_end(false)
                {
                end();
                }
            void end()
                {
                if(did_end)
                    return;
                CallCount[FunctionName] = ++CallCount[FunctionName];
                did_end = true;
                }
        };

    #define COUNT_FUNC CCounter cbcounter(__FUNCTION__)
#else
    #define COUNT_FUNC
#endif

#ifdef CBASH_DEBUG_VARS
    #include <map>
    extern std::map<unsigned long, unsigned long> uint32_uint32_map1;
    extern std::map<unsigned long, unsigned long> uint32_uint32_map2;
    extern std::map<unsigned long, unsigned long> uint32_uint32_map3;
    extern std::map<char *, unsigned long> string_uint32_map;
    extern std::map<unsigned long, char *> uint32_string_map;
    extern unsigned long debug_temp1;
    extern unsigned long debug_temp2;
    extern unsigned long debug_temp3;
    extern unsigned long debug_temp4;
#endif

#ifndef FLT_MAX
    #define FLT_MAX         3.402823466e+38F        /* max value */
#endif
#ifndef FLT_MIN
    #define FLT_MIN         1.175494351e-38F        /* min positive value */
#endif

#ifndef PRINT_RECORD_IDENTIFIERS
    #define PRINT_RECORD_IDENTIFIERS printer("CollectionID: %08X, ModID: %08X, RecordID: %08X\n", CollectionID, ModID, RecordID)
#endif

#ifndef PRINT_FIELD_IDENTIFIERS
    #define PRINT_FIELD_IDENTIFIERS printer("FieldID: %i, ListIndex: %i, ListFieldID: %i, ListX2Index: %i, ListX2FieldID: %i, ListX3Index: %i, ListX3FieldID: %i \n", FieldID, ListIndex, ListFieldID, ListX2Index, ListX2FieldID, ListX3Index, ListX3FieldID)
#endif

#ifndef PRINT_EXCEPTION
    #define PRINT_EXCEPTION(ex) printer("%s: Error - %s\n", __FUNCTION__, ex.what())
#endif

#ifndef PRINT_ERROR
#define PRINT_ERROR printer("%s: Error - An unhandled exception occurred.\n", __FUNCTION__)
#endif

#ifndef NUMTHREADS
    #define NUMTHREADS    boost::thread::hardware_concurrency()
#endif

//Using 64KB buffers
#ifndef BUFFERSIZE
    #define BUFFERSIZE    65536
#endif

#ifndef END_HARDCODED_IDS
    #define END_HARDCODED_IDS    0x00000800
#endif

#ifndef VATSFUNCTIONSIZE
    #define VATSFUNCTIONSIZE 18
#endif

typedef cb_formid_t FORMID;
typedef uint32_t MGEFCODE;
typedef uint32_t ACTORVALUE;
typedef uint32_t FORMID_OR_UINT32;
typedef uint32_t FORMID_OR_FLOAT32;
typedef uint32_t MGEFCODE_OR_UINT32;
typedef uint32_t FORMID_OR_MGEFCODE_OR_ACTORVALUE_OR_UINT32;
typedef uint32_t FORMID_OR_ACTORVALUE_OR_UINT32;

typedef uint8_t * UINT8ARRAY;
typedef int16_t * SINT16ARRAY;
typedef uint32_t * UINT32ARRAY;
typedef int32_t * SINT32ARRAY;
typedef FORMID * FORMIDARRAY;
typedef char ** STRINGARRAY;
typedef MGEFCODE * MGEFCODEARRAY;
typedef ModFile ** MODIDARRAY;
typedef Record ** RECORDIDARRAY;

#ifndef DEFAULTED_FIELD_IDENTIFIERS
    #define DEFAULTED_FIELD_IDENTIFIERS const uint32_t FieldID=0, const uint32_t ListIndex=0, const uint32_t ListFieldID=0, const uint32_t ListX2Index=0, const uint32_t ListX2FieldID=0, const uint32_t ListX3Index=0, const uint32_t ListX3FieldID=0
#endif

#define WHERESTR            "[%s, line %d]: "
#define WHEREARG            __FUNCTION__, __LINE__
#define DEBUGPRINT2(...)    printer(__VA_ARGS__)
#define DPRINT(_fmt, ...)   DEBUGPRINT2(WHERESTR _fmt "\n", WHEREARG, __VA_ARGS__)
#define DPRINT1(_fmt)       DEBUGPRINT2(WHERESTR _fmt "\n", WHEREARG)

#define QDPRINT             DEBUGPRINT2(WHERESTR "\n", WHEREARG)

#define VHDPRINT(_var)       DPRINT(#_var " = %08X",_var)
#define VSDPRINT(_var)       DPRINT(#_var " = %s",_var)
#define VDDPRINT(_var)       DPRINT(#_var " = %d",_var)


#define REV32(x)            ((#@x & 0x000000FFU) << 24 | (#@x & 0x0000FF00U) << 8 | (#@x & 0x00FF0000U) >> 8 | (#@x & 0xFF000000U) >> 24)
#define WRITE(x)            x.Write(REV32(x), writer)
#define WRITEREQ(x)         x.ReqWrite(REV32(x), writer)
#define WRITEAS(x,y)        x.Write(REV32(y), writer)
#define WRITEEMPTY(x)       writer.record_write_subheader(REV32(x), 0);

// 3 methods to flip bits conditionally
#ifdef BITSET_BRANCHING // slowest method
    #define SETBIT(var,mask,set) var = set ? (var | mask) : (var & ~mask)
#elif defined BITSET_NO_SUPERSCALAR
    // Uses more operations, but avoids branching
    // Usually about 5-10% faster than branching
    #define SETBIT(var,mask,set) \
        __pragma(warning(push)) \
        __pragma(warning(disable:4804)) \
        var ^= (-set ^ var) & mask \
        __pramga(warning(pop))
#else // Superscalar CPU method
      // Pretty much all modern CPU's are superscalar
      // About 16% faster than the non-branching method
    #define SETBIT(var,mask,set) \
        __pragma(warning(push)) \
        __pragma(warning(disable:4804)) \
        var = (var & ~mask) | (-set & mask) \
        __pragma(warning(pop))
#endif

// Quick macro to debug struct sizes at compile time
#define SIZE_CHECK_MSG(type, size, msg) \
    BOOST_STATIC_ASSERT_MSG(sizeof(type) == size, msg)

// Macro to ensure a structure has a specific size when compiled.
// This ensured that doing a memcpy from a file on disk will correctly
// fill in the fields.
#define SIZE_CHECK(type, size) \
    SIZE_CHECK_MSG(type, size, #type " must be " #size " bytes")
