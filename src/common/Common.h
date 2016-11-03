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

// Common.h
#include <time.h>
#include <io.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <share.h>
#include <errno.h>
#include <exception>
#include <boost/unordered_set.hpp>
#include <set>
#include <map>
//#include <boost/interprocess/file_mapping.hpp>
//#include <boost/interprocess/mapped_region.hpp>
#include <boost/iostreams/device/mapped_file.hpp>
#include <vector>
#include "MacroDefinitions.h"
#include "Types.h"

extern int (*printer)(const char * _Format, ...);
extern int32_t (*LoggingCallback)(const char *);
extern void (*RaiseCallback)(const char *);

enum TopTypes {
    eTop,
    eWorld,
    eInteriorBlock,
    eInteriorSubBlock,
    eExteriorBlock,
    eExteriorSubBlock,
    eCellChildren,
    eTopicChildren,
    eCellPersistent,
    eCellTemporary,
    eCellVWD
    };

enum varType {
    eNONE,
    eUINT32,
    eFORMID,
    eVATSPARAM,
    eEVENTDATA,
    };

class Ex_NULL : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const;
    };

class Ex_INVALIDINDEX : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const;
    };

class Ex_INVALIDCOLLECTIONINDEX : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const;
    };

class Ex_INVALIDMODINDEX : public std::exception
    {
    public:
        const char * __CLR_OR_THIS_CALL what() const;
    };

//wrappers for _stricmp and strcmp that handle NULL args
int icmps(const char * lhs, const char * rhs);
int cmps(const char * lhs, const char * rhs);

struct ModFile;
struct Record;
class StringRecord;

struct sameStr
    {
    bool operator()( const char * s1, const char * s2 ) const;
    };

bool ReadChunk(unsigned char *&buffer, const uint32_t &buffer_size, void *dest_buffer, const uint32_t &dest_buffer_size, const bool &skip_load);

typedef std::multimap<uint32_t, Record *> FormID_Map;
typedef std::multimap<char *, Record *, sameStr> EditorID_Map;

typedef FormID_Map::iterator FormID_Iterator;
typedef EditorID_Map::iterator EditorID_Iterator;

typedef std::pair<FormID_Iterator, FormID_Iterator> FormID_Range;
typedef std::pair<EditorID_Iterator, EditorID_Iterator> EditorID_Range;

typedef std::pair<varType, varType> FunctionArguments;

typedef std::map<uint32_t, FunctionArguments>::value_type Function_ArgumentsType;
typedef std::map<uint32_t, char *>::value_type Function_NameType;
typedef std::map<uint32_t, std::vector<uint32_t> >::value_type RecordType_PossibleGroupsType;

typedef std::map<uint32_t, std::vector<uint32_t> >::const_iterator RecordType_PossibleGroups_Iterator;
typedef std::map<uint32_t, FunctionArguments>::const_iterator Function_Arguments_Iterator;
typedef std::map<uint32_t, char *>::const_iterator ID_Name_Iterator;

extern const std::map<uint32_t, FunctionArguments> Function_Arguments;
extern const std::map<uint32_t, char *> Function_Name;
extern const std::map<uint32_t, char *> Comparison_Name;
extern const std::map<uint32_t, char *> IDLEGroup_Name;
extern const std::map<uint32_t, char *> PACKAIType_Name;
extern const std::map<uint32_t, char *> PACKLocType_Name;
extern const std::map<uint32_t, char *> PACKTargetType_Name;
extern const std::map<uint32_t, char *> HardCodedFormID_EditorID;

extern const std::map<uint32_t, FunctionArguments> FNVFunction_Arguments;
extern const uint32_t VATSFunction_Argument[];

extern const std::map<uint32_t, FunctionArguments> SKFunction_Arguments;

extern const float flt_max;
extern const float flt_min;
extern const float flt_0;
extern const float flt_1;
extern const float flt_3;
extern const float flt_n2147483648;

#ifdef CBASH_CALLTIMING
    extern std::map<char *, double> CallTime;
#endif
#ifdef CBASH_CALLCOUNT
    extern std::map<char *, unsigned long> CallCount;
#endif

#ifdef CBASH_DEBUG_CHUNK
    void peek_around(unsigned char *position, uint32_t length);
#endif

class GenericOp
    {
    public:
        GenericOp();
        ~GenericOp();

        virtual bool perform() abstract {};
    };

class RenameOp : public GenericOp
    {
    private:
        char * original_name;
        char * destination_name;

    public:
        RenameOp(char * _original_name, char * _destination_name);
        ~RenameOp();

        bool perform();
    };

char * DeGhostModName(char * const ModName);
bool FileExists(char * const FileName);
char * GetTemporaryFileName(char * FileName, bool IsBackup=false);
bool AlmostEqual(float A, float B, int32_t maxUlps);
void UnrecognizedSubRecord(cb_formid_t formID, uint32_t subType, uint32_t subSize, unsigned char *&buffer, unsigned char *end_buffer);

class FileWriter
    {
    private:
        unsigned char *file_buffer, *record_buffer, *compressed_buffer;
        uint32_t file_buffer_used, record_buffer_used, compressed_buffer_used;
        uint32_t file_buffer_size, record_buffer_size, compressed_buffer_size;
        int fh;
        char * FileName;

    public:
        FileWriter(char * filename, uint32_t size);
        ~FileWriter();

        int32_t open();
        int32_t close();

        void   record_write(const void *source, uint32_t length);
        void   record_write_subheader(uint32_t signature, uint32_t length);
        void   record_write_subrecord(uint32_t signature, const void *source, uint32_t length);
        uint32_t record_compress();
        uint32_t record_size();
        void   record_flush();

        uint32_t file_tell();
        void   file_write(const void *source_buffer, uint32_t source_buffer_used);
        void   file_write(uint32_t position, const void *source_buffer, uint32_t source_buffer_used);
    };

class FormIDHandlerClass
    {
    //In order to identify a record across mods, two pieces of info are needed:
    // 1) The originating mod.
    // 2) A unique identifier within the mod.

    //As long as those two requirements are met, the implementation details don't matter.
    //In practice, there are two different implementations in use:
    // 1) FormIDs (used by the game engine, TES4Edit, etc)
    // 2) Long formIDs (used by Wrye Bash and therefore used in cint)

    //A formID is composed of two parts, the modIndex and the objectID.
    // The modIndex identifies the originating mod and the objectID identifies the record within that mod.
    // The modIndex is a uint8_t index, and the objectID is a UINT24.
    // They are combined into a single uint32_t where 0xFF000000 is the modIndex and the objectID is 0x00FFFFFF.
    // I.E. a modIndex of 0x01 and an objectID of 0x00084F would result in the formID 0x0100084F.
    // Considering that Oblivion.esm alone has over a million records,
    //  and that each record may reference multiple other records, this is both a fast and low memory method.
    //
    // There are a couple problems though:
    //  1) A modIndex can only use 0-255, but there are several orders of magnitudes more mods.
    //     Inevitably, mods will end up using the same modIndex value.
    //  2) A modIndex can't directly identify a mod; mods are named, not numbered.
    //
    // Bethesda solves these issues by:
    //  1) Limiting mods to 254 (255 is reserved)
    //  2) Translating a mod name to a unique modIndex value.
    // The implementation details of these fixes differs depending on whether the record is on disk or in memory.
    //
    // If the record is on disk (being read/written):
    //  1) There is an array of mod names in the TES4 record termed the masters. It is signed with "MAST".
    //     Whenever a record from another mod is added to a mod,
    //      its originating mod name is added to this array if not already present.
    //     This array is limited to 254 entries. Therefore a mod is unable to have more than 254 masters.
    //  2) The modIndex identifies the array index of the originating mod's name.
    //     If the modIndex is greater than the array size (up to 255), it identifies that mod as the source.
    //
    //  For example, if an esp named "Test.esp" uses records from "Oblivion.esm", "OOO.esm", and "COBL.esm",
    //   it will have these names in the MAST chunk of its TES4 record. A record with the formID 0x0100084F
    //   has a modIndex of 1, and an objectID of 0x84F. The modIndex is used to access the master array
    //   resulting in "OOO.esm". The record is thus identified as originating from "OOO.esm" with the unique
    //   identifier of 0x84F. Similarly, 0x0000084F is a completely different record that originates from
    //   "Oblivion.esm". On the other hand, 0x0300084F, 0x0400084F, and 0xFF00084F all refer to the same
    //   record that originates from "Test.esp". Although they have different modIndex values, they are all
    //   greater than the master array length. For the majority of formIDs originating within a mod, the
    //   modIndex will be equal to the size of the master array, but not always.
    //
    // If the record is in memory:
    //  1) The number of active mods is limited to 254 (255 is used for the save file).
    //     These mods are arranged into a load order based primarily on the modified time of each mod, with
    //      esm mods sorting before esp mods.
    //  2) The modIndex identifies the load order index of the mod. If the load order changes, the modIndex of a given
    //      record will change to reflect this.
    //
    //  For example, if the mods "Test.esp", "Oblivion.esm", "OOO.esm", and "COBL.esm" are active, they may
    //   be sorted into a load order "Oblivion.esm", "COBL.esm", "OOO.esm", and "Test.esp". A record with the
    //   formID 0x0100084F has a modIndex of 1, and an objectID of 0x84F. The modIndex is used to access the
    //   load order array resulting in "COBL.esm". The record is thus identified as originating from "COBL.esm"
    //   with the unique identifier of 0x84F. Similarly, 0x0000084F is a completely different record that
    //   originates from "Oblivion.esm", 0x0200084F comes from "OOO.esm", 0x0300084F comes from "Test.esp", and
    //   0xFF00084F comes from the savegame.
    //
    // Notice that the formID 0x0100084F in the above examples identifies two completely different records based on
    //  whether the record is on disk or in memory. The game engine has to be able to convert between the disk
    //  representation and the in memory representation. This is known as resolving the formID. It occurs every time
    //  the game engine is started, the Construction Set (CS) opens a mod, and when the CS saves a mod. Almost every
    //  record has to have its formID resolved as well as every formID that record happens to reference.
    //  (To complicate matters, some records are identified by their editorID instead of their formID, and any formID
    //  with an objectID <= 0x800 doesn't use the modIndex at all. Instead, they're considered to belong to the
    //  engine itself.)
    //
    //  The key to doing this lays in the fact that in both cases, the modIndex can be used to get a mod's name.
    //   On disk, the modIndex directly references a name in the master array, and in memory, it references a mod at
    //   a given load order, and the engine knows the name of that mod.
    //
    //  So, the on disk modIndex maps to a mod name which maps to the in memory modIndex.
    //
    //  Combining the two previous examples, the on disk formID 0x0100084F in mod "Test.esp" refers to
    //   ("OOO.esm", 0x84F). The load order is "Oblivion.esm", "COBL.esm", "OOO.esm", and "Test.esp". The engine
    //   finds a match between "OOO.esm" and the mod name at load order position 0x02, so the in memory modIndex
    //   becomes 0x02, and the formID is 0x0200084F. "Oblivion.esm" has no masters, so the on disk formID 0x0100084F
    //   in mod "Oblivion.esm" refers to ("Oblivion.esm", 0x84F). The engine finds a match between
    //   "Oblivion.esm" and the mod name at load order position 0x00, so the modIndex becomes 0x00,
    //   and the in memory formID is 0x0000084F.
    //
    //  When the CS saves a mod to disk, this process is essentially reversed. Given a new mod being saved
    //   to "SaveTest.esp" with the same load order as above, the in memory formID 0x0200084F refers to the mod at
    //   load order position 0x02 which has the name "OOO.esm". If "OOO.esm" is found at position 0x00 in
    //   the mod's masters, so the on disk formID becomes 0x0000084F.
    //
    // Instead of directly working with formIDs, Wrye Bash uses a concept it calls long formIDs.
    //  Rather than going from on disk modIndex to mod name to in memory modIndex, long formIDs stop at the mod name.
    //  So the long formID is always just one step away from becoming either an on disk formID or in memory formID.
    //
    //  For example, using the same example setup as before, the on disk formID 0x0100084F in mod
    //   "Test.esp" refers to ("OOO.esm", 0x84F), so the long formID is just that, ("OOO.esm", 0x84F).
    //   When converting ("OOO.esm", 0x84F) back to the on disk formID, if "OOO.esm" is found at position 0x00
    //   in the mod's masters, the on disk formID becomes 0x0000084F.
    //
    // Each approach satisfies the conditions to uniquely identify a record, but they have their own pros and cons.
    //  FormID Pros:
    //   1) A uint32_t uses much less memory than a string and uint32_t.
    //   2) It is much faster to load a uint32_t than a string and uint32_t.
    //   3) Comparing uint32_t's is much faster than case insensitive comparing a string and a uint32_t.
    //  FormID Cons:
    //   1) The resolution process is a bit involved.
    //   2) Depending on implementation, resolving a formID can be very slow.
    //      The naive approach is to case insensitively search through the load order and/or masters every time a
    //       formID is resolved.
    //   3) Neither the on disk formID nor the in memory formID is stable. On disk formID 0x0100084F may refer to
    //       ("OOO.esm", 0x84F) at one point in time, and ("COBL.esm", 0x84F) at some other time. It all depends on
    //       whether the masters were changed. In memory formID 0x0100084F may refer to ("COBL.esm", 0x84F)
    //       at one point in time, and ("Test.esp", 0x84F) at some other time. It all depends on whether the load order
    //       was changed. It isn't trivial to match records across two different load orders.
    //   4) A human can't simply look at the formID and know where the record originates.
    //
    //  Long formID Pros:
    //   1) A long formID is stable. It doesn't matter what the load order is, nor what the mod masters are.
    //      ("OOO.esm", 0x84F) always refers to the record in "OOO.esm" with the objectID 0x84F. This makes it
    //      extremely trivial to match records despite differing load orders. This allows actions such as
    //      importing data from a text file or from a mod file not in the load order.
    //   2) The resolution process is simpler.
    //   3) The originating mod of a record becomes extremely obvious.
    //  Long formID Cons:
    //   1) Uses much more memory than a formID.
    //   2) Takes much more time to process than a formID.
    //   3) Have to work with a "non-standard" format, and deal with conversions when needed.
    //
    //CBash uses the formID internally, but defaults to the long formID in its Python interface.
    // This involves extra work, but allows Python to work with a stable record identifier while
    //  preserving the speed and memory savings internally by using formIDs.
    //
    //CBash is heavily optimized for speedy formID resolution. Since there is a maximum of 255
    // possible masters per mod, and a similar limit on the number of mods in a given load order,
    // CBash can precompute all possible on disk modIndex to in memory modIndex matches. These
    // are stored in a fixed size array, so that resolving a formID is a simple matter of
    // selecting the appropriate resolution table, and using the given modIndex as the index.
    // CBash uses the terminology "expand" when resolving an on disk formID to an in memory formID,
    // and "collapse" when resolving an in memory formID to an on disk formID.
    public:
        std::vector<char *> &MAST;        //The list of masters
        std::vector<char *> LoadOrder255;       //The current load order of active mods
        boost::unordered_set<uint32_t> NewTypes;  //Tracks the type of any new records for reporting
        uint32_t &nextObject;                     //The object counter for quickly providing new objectIDs
        uint8_t  ExpandTable[256];                //Maps the on disk modIndex to the in memory modIndex
        uint8_t  CollapseTable[256];              //Maps the in memory modIndex to the on disk modIndex (not always a direct inverse of ExpandTable)
        unsigned char * FileStart;
        unsigned char * FileEnd;
        uint8_t  ExpandedIndex;                   //The load order index
        uint8_t  CollapsedIndex;                  //The size of MAST
        bool   IsEmpty;
        bool   bMastersChanged;
        int32_t EmptyGRUPs;
        std::vector<FORMID> OrphanedRecords;

        FormIDHandlerClass(std::vector<char *> &_MAST, uint32_t &_NextObject);
        ~FormIDHandlerClass();

        void   SetLoadOrder(std::vector<char *> &cLoadOrder);
        uint32_t NextExpandedFormID();
        void   CreateFormIDLookup(const uint8_t expandedIndex);
        void   UpdateFormIDLookup();
        void   AddMaster(char * const curMaster);
        bool   MastersChanged();
        bool   IsValid(const unsigned char *_SrcBuf);
    };

class CreationFlags
    {
    public:
        CreationFlags();
        CreationFlags(uint32_t nFlags);
        ~CreationFlags();

        bool SetAsOverride;
        bool CopyWinningParent;

        //Internal use
        bool ExistingReturned;

        uint32_t GetFlags();
    };

class ModFlags
    {
    public:
        ModFlags();
        ModFlags(uint32_t _Flags);
        ~ModFlags();

        bool IsMinLoad;
        bool IsFullLoad;
        bool IsNoLoad;
        bool IsSkipNewRecords;
        bool IsSkipAllRecords;
        bool IsInLoadOrder;
        bool IsSaveable;
        bool IsAddMasters;
        bool IsLoadMasters;
        bool IsExtendedConflicts;
        bool IsTrackNewTypes;
        bool IsIndexLANDs;
        bool IsFixupPlaceables;
        bool IsCreateNew;
        bool IsIgnoreInactiveMasters;

        //For internal use, may not be set by constructor
        bool LoadedGRUPs;

        uint32_t GetFlags();
    };

class SaveFlags
    {
    public:
        SaveFlags();
        SaveFlags(uint32_t _Flags);
        ~SaveFlags();

        bool IsCleanMasters;
        bool IsCloseCollection;
    };

class StringRecord
    {
    private:
        #ifdef CBASH_X64_COMPATIBILITY
            bool IsOnDisk;
            #define O_IS_ON_DISK(x) (x.IsOnDisk)
            #define S_IS_ON_DISK (IsOnDisk)
            #define O_SET_ON_DISK(x, y) (x.IsOnDisk = y)
            #define S_SET_ON_DISK(x) (IsOnDisk = x)
            #define S_GET_VALUE (value)
            #define O_GET_VALUE(x) (x.value)
            #define VAL_NAME value
        #else
            //Save memory on x86 builds by using the unused high bit of the char * pointer
            enum flagsFlags
                {
                fIsOnDisk = 0x80000000
                };
            #define O_IS_ON_DISK(x) (((uint32_t)x._value & 0x80000000) != 0)
            #define S_IS_ON_DISK (((uint32_t)_value & 0x80000000) != 0)
            #define O_SET_ON_DISK(x, y) (x._value = y ? (char *)((uint32_t)x._value | 0x80000000) : (char *)((uint32_t)x._value & ~0x80000000))
            #define S_SET_ON_DISK(x) (_value = x ? (char *)((uint32_t)_value | 0x80000000) : (char *)((uint32_t)_value & ~0x80000000))
            #define S_GET_VALUE ((char *)((uint32_t)_value & ~0x80000000))
            #define O_GET_VALUE(x) ((char *)((uint32_t)x._value & ~0x80000000))
            #define VAL_NAME _value
            char * _value;
        #endif

    public:
        #ifdef CBASH_X64_COMPATIBILITY
            char * value;
        #else
            __declspec(property(get=GetString)) char * value;
        #endif

        StringRecord();
        StringRecord(const StringRecord &p);
        ~StringRecord();

        uint32_t GetSize() const;
        #ifndef CBASH_X64_COMPATIBILITY
            char * GetString();
        #endif

        bool IsLoaded() const;
        void Load();
        void Unload();

        bool Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk);
        void Write(uint32_t _Type, FileWriter &writer);
        void ReqWrite(uint32_t _Type, FileWriter &writer);

        void Copy(char * FieldValue);
        void TruncateCopy(char * FieldValue, uint32_t MaxSize);

        bool equals(const StringRecord &other) const;
        bool equalsi(const StringRecord &other) const;
        StringRecord& operator = (const StringRecord &rhs);
    };

class NonNullStringRecord
    {
    private:
        uint32_t DiskSize;
        char * _value;

    public:
        __declspec(property(get=GetString)) char * value;

        NonNullStringRecord();
        NonNullStringRecord(const NonNullStringRecord &p);
        ~NonNullStringRecord();

        uint32_t GetSize() const;
        char * GetString();

        bool IsLoaded() const;
        void Load();
        void Unload();

        bool Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk);
        void Write(uint32_t _Type, FileWriter &writer);
        void Write16(FileWriter &writer) const;
        void ReqWrite(uint32_t _Type, FileWriter &writer);

        void Copy(char * FieldValue);

        bool equals(const NonNullStringRecord &other) const;
        bool equalsi(const NonNullStringRecord &other) const;
        NonNullStringRecord& operator = (const NonNullStringRecord &rhs);
    };

class UnorderedPackedStrings
    {
    public:
        std::vector<char *> value;

        UnorderedPackedStrings();
        ~UnorderedPackedStrings();

        uint32_t GetSize() const;

        bool IsLoaded() const;
        void Load();
        void Unload();

        void resize(uint32_t newSize);

        bool Read(unsigned char *&buffer, const uint32_t &subSize);
        void Write(uint32_t _Type, FileWriter &writer);

        void Copy(STRINGARRAY FieldValue, uint32_t ArraySize);

        UnorderedPackedStrings& operator = (const UnorderedPackedStrings &rhs);
        bool equals(const UnorderedPackedStrings &other) const;
        bool equalsi(const UnorderedPackedStrings &other) const;
    };

class RawRecord
    {
    private:
        //Using the upper bit of size to store a flag
        //This restricts the max size to a paltry 2GB, so not an issue
        enum flagsFlags
            {
            fIsOnDisk = 0x80000000
            };

    public:
        uint32_t size;
        unsigned char *value;

        RawRecord();
        RawRecord(const RawRecord &p);
        ~RawRecord();

        uint32_t GetSize() const;

        bool IsLoaded() const;
        void Load();
        void Unload();

        bool Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk);
        void Write(uint32_t _Type, FileWriter &writer);
        void ReqWrite(uint32_t _Type, FileWriter &writer);

        void Copy(unsigned char *FieldValue, uint32_t nSize);

        RawRecord& operator = (const RawRecord &rhs);
        bool operator ==(const RawRecord &other) const;
        bool operator !=(const RawRecord &other) const;
    };

//Base record field. Vestigial.
//Used when it isn't known if the record is required or optional.
//Should only be used with simple data types that should be initialized to 0 (int, float, etc) and not structs
//exponent parameter is only used on the float specialization
template<class T, T defaultValue=0>
struct SimpleSubRecord
    {
    T value;
    bool isLoaded;

    SimpleSubRecord():
        isLoaded(false),
        value(defaultValue)
        {
        //
        }
    ~SimpleSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (isLoaded && value != defaultValue);
        }
    void Load()
        {
        isLoaded = true;
        }
    void Unload()
        {
        value = defaultValue;
        isLoaded = false;
        }
    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool was_loaded = ReadChunk(buffer, subSize, &value, sizeof(T), isLoaded);
        isLoaded = true;
        return was_loaded;
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(isLoaded && value != defaultValue)
            writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    SimpleSubRecord<T, defaultValue>& operator = (const SimpleSubRecord<T, defaultValue> &rhs)
        {
        if(this != &rhs)
            {
            isLoaded = rhs.isLoaded;
            value = rhs.value;
            }
        return *this;
        }
    bool operator ==(const SimpleSubRecord<T, defaultValue> &other) const
        {
        return (isLoaded == other.isLoaded &&
                value == other.value);
        }
    bool operator !=(const SimpleSubRecord<T, defaultValue> &other) const
        {
        return !(*this == other);
        }
    };

template<const float &defaultValue=flt_0>
struct SimpleFloatSubRecord
    {
    float value;
    bool isLoaded;

    SimpleFloatSubRecord():
        isLoaded(false),
        value(defaultValue)
        {
        //
        }
    ~SimpleFloatSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(float);
        }

    bool IsLoaded() const
        {
        return (isLoaded && !AlmostEqual(value, defaultValue, 2));
        }

    void Load()
        {
        isLoaded = true;
        }

    void Unload()
        {
        value = defaultValue;
        isLoaded = false;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool was_loaded = ReadChunk(buffer, subSize, &value, sizeof(float), isLoaded);
        isLoaded = true;
        return was_loaded;
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(isLoaded && value != defaultValue)
            writer.record_write_subrecord(_Type, &value, sizeof(float));
        }

    void ReqWrite(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(float));
        }

    SimpleFloatSubRecord<defaultValue>& operator = (const SimpleFloatSubRecord<defaultValue> &rhs)
        {
        if(this != &rhs)
            {
            isLoaded = rhs.isLoaded;
            value = rhs.value;
            }
        return *this;
        }

    bool operator ==(const SimpleFloatSubRecord<defaultValue> &other) const
        {
        return (isLoaded == other.isLoaded &&
                AlmostEqual(value, other.value, 2));
        }

    bool operator !=(const SimpleFloatSubRecord<defaultValue> &other) const
        {
        return !(*this == other);
        }
    };

//Used for subrecords that are required
//Even if not actually loaded from disk, they are always considered loaded even if they're explicitly unloaded.
//Unloading them simply resets the values to default.
//Should only be used with simple data types that should be initialized to 0 (int, float, etc) and not structs
//exponent parameter is only used on the float specialization
template<class T, T defaultValue=0>
struct ReqSimpleSubRecord
    {
    T value;

    ReqSimpleSubRecord():
        value(defaultValue)
        {
        //
        }

    ~ReqSimpleSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return true;
        }

    void Load()
        {
        //
        }

    void Unload()
        {
        value = defaultValue;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        return ReadChunk(buffer, subSize, &value, sizeof(T), false);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    ReqSimpleSubRecord<T, defaultValue>& operator = (const ReqSimpleSubRecord<T, defaultValue> &rhs)
        {
        if(this != &rhs)
            value = rhs.value;
        return *this;
        }

    bool operator ==(const ReqSimpleSubRecord<T, defaultValue> &other) const
        {
        return (value == other.value);
        }

    bool operator !=(const ReqSimpleSubRecord<T, defaultValue> &other) const
        {
        return !(*this == other);
        }
    };

template<const float &defaultValue=flt_0>
struct ReqSimpleFloatSubRecord
    {
    float value;

    ReqSimpleFloatSubRecord():
        value(defaultValue)
        {
        //
        }

    ~ReqSimpleFloatSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(float);
        }

    bool IsLoaded() const
        {
        return true;
        }

    void Load()
        {
        //
        }

    void Unload()
        {
        value = defaultValue;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        return ReadChunk(buffer, subSize, &value, sizeof(float), false);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(float));
        }

    ReqSimpleFloatSubRecord<defaultValue>& operator = (const ReqSimpleFloatSubRecord<defaultValue> &rhs)
        {
        if(this != &rhs)
            value = rhs.value;
        return *this;
        }

    bool operator ==(const ReqSimpleFloatSubRecord<defaultValue> &other) const
        {
        return (AlmostEqual(value, other.value, 2));
        }

    bool operator !=(const ReqSimpleFloatSubRecord<defaultValue> &other) const
        {
        return !(*this == other);
        }
    };
//Used for subrecords that are optional
//Even if loaded, they are considered unloaded if they're equal to their defaults
//Should only be used with simple data types (int, float, etc) and not structs
template<class T, T defaultValue=0>
struct OptSimpleSubRecord
    {
    T value;

    OptSimpleSubRecord():
        value(defaultValue)
        {
        //
        }

    ~OptSimpleSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (value != defaultValue);
        }

    void Load()
        {
        //
        }

    void Unload()
        {
        value = defaultValue;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        return ReadChunk(buffer, subSize, &value, sizeof(T), false);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value != defaultValue)
            writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    void ReqWrite(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    OptSimpleSubRecord<T, defaultValue>& operator = (const OptSimpleSubRecord<T, defaultValue> &rhs)
        {
        if(this != &rhs)
            value = rhs.value;
        return *this;
        }

    bool operator ==(const OptSimpleSubRecord<T, defaultValue> &other) const
        {
        return value == other.value;
        }

    bool operator !=(const OptSimpleSubRecord<T, defaultValue> &other) const
        {
        return value != other.value;
        }
    };
//Used for subrecords that are optional
//Even if loaded, they are considered unloaded if they're equal to their defaults
//Should only be used with simple data types (int, float, etc) and not structs
template<class T>
struct OptZeroSubRecord
{
  T value;

  OptZeroSubRecord()
  {
    //
    Unload();
  }

  ~OptZeroSubRecord()
  {
    //
  }

  uint32_t GetSize() const
  {
    return sizeof(T);
  }

  bool IsLoaded() const
  {
    struct OptZeroSubRecord zero; return (this == zero);
  }

  void Load()
  {
    //
  }

  void Unload()
  {
    memset(&value, 0, GetSize());
  }

  bool Read(unsigned char *&buffer, const uint32_t &subSize)
  {
    return ReadChunk(buffer, subSize, &value, sizeof(T), false);
  }

  void Write(uint32_t _Type, FileWriter &writer)
  {
    if(value != defaultValue)
      writer.record_write_subrecord(_Type, &value, sizeof(T));
  }

  void ReqWrite(uint32_t _Type, FileWriter &writer)
  {
    writer.record_write_subrecord(_Type, &value, sizeof(T));
  }

  OptZeroSubRecord<T>& operator = (const OptZeroSubRecord<T> &rhs)
  {
    if(this != &rhs)
      memcpy(value, rhs.value, GetSize());
    return *this;
  }

  bool operator ==(const OptZeroSubRecord<T> &other) const
  {
    return  !memcmp(&value, &zero.value, GetSize());
  }

  bool operator !=(const OptZeroSubRecord<T> &other) const
  {
    return !!memcmp(&value, &zero.value, GetSize());
  }
};

template<const float &defaultValue=flt_0>
struct OptSimpleFloatSubRecord
    {
    float value;

    OptSimpleFloatSubRecord():
        value(defaultValue)
        {
        //
        }
    ~OptSimpleFloatSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(float);
        }

    bool IsLoaded() const
        {
        return !(AlmostEqual(value, defaultValue, 2));
        }

    void Load()
        {
        //
        }

    void Unload()
        {
        value = defaultValue;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        return ReadChunk(buffer, subSize, &value, sizeof(float), false);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(IsLoaded())
            writer.record_write_subrecord(_Type, &value, sizeof(float));
        }

    void ReqWrite(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(float));
        }

    OptSimpleFloatSubRecord<defaultValue>& operator = (const OptSimpleFloatSubRecord<defaultValue> &rhs)
        {
        if(this != &rhs)
            value = rhs.value;
        return *this;
        }

    bool operator ==(const OptSimpleFloatSubRecord<defaultValue> &other) const
        {
        return AlmostEqual(value, other.value, 2);
        }

    bool operator !=(const OptSimpleFloatSubRecord<defaultValue> &other) const
        {
        return !(AlmostEqual(value, other.value, 2));
        }
    };
//Identical to OptSimpleSubRecord except for IsLoaded
//Once loaded, they are always considered loaded unless they're explicitly unloaded.
//They don't compare to the default value to see if they're still considered loaded.
//Should only be used with simple data types that should be initialized to 0 (int, float, etc) and not structs
template<class T, T defaultValue=0>
struct SemiOptSimpleSubRecord
    {
    T *value;

    SemiOptSimpleSubRecord():
        value(NULL)
        {
        //
        }

    ~SemiOptSimpleSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (value != NULL);
        }

    void Load()
        {
        if(value == NULL)
            value = new T(defaultValue);
        }

    void Unload()
        {
        delete value;
        value = NULL;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool is_loaded = (value != NULL);
        if(!is_loaded)
            value = new T(defaultValue);
        return ReadChunk(buffer, subSize, value, sizeof(T), is_loaded);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value != NULL)
            writer.record_write_subrecord(_Type, value, sizeof(T));
        }

    SemiOptSimpleSubRecord<T, defaultValue>& operator = (const SemiOptSimpleSubRecord<T, defaultValue> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    value = new T(defaultValue);
                else
                    value->~T();
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }

    bool operator ==(const SemiOptSimpleSubRecord<T, defaultValue> &other) const
        {
        if(!IsLoaded())
            {
            if(!other.IsLoaded())
                return true;
            }
        else if(other.IsLoaded() && *value == *other.value)
            return true;
        return false;
        }

    bool operator !=(const SemiOptSimpleSubRecord<T, defaultValue> &other) const
        {
        return !(*this == other);
        }
    };

template<const float &defaultValue=flt_0>
struct SemiOptSimpleFloatSubRecord
    {
    float *value;

    SemiOptSimpleFloatSubRecord():
        value(NULL)
        {
        //
        }
    ~SemiOptSimpleFloatSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(float);
        }

    bool IsLoaded() const
        {
        return (value != NULL);
        }

    void Load()
        {
        if(value == NULL)
            value = new float(defaultValue);
        }

    void Unload()
        {
        delete value;
        value = NULL;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool is_loaded = (value != NULL);
        if(!is_loaded)
            value = new float(defaultValue);
        return ReadChunk(buffer, subSize, value, sizeof(float), is_loaded);
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value != NULL)
            writer.record_write_subrecord(_Type, value, sizeof(float));
        }

    SemiOptSimpleFloatSubRecord<defaultValue>& operator = (const SemiOptSimpleFloatSubRecord<defaultValue> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    value = new float(defaultValue);
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }

    bool operator ==(const SemiOptSimpleFloatSubRecord<defaultValue> &other) const
        {
        if(!IsLoaded())
            {
            if(!other.IsLoaded())
                return true;
            }
        else if(other.IsLoaded() && AlmostEqual(*value, *other.value, 2))
            return true;
        return false;
        }

    bool operator !=(const SemiOptSimpleFloatSubRecord<defaultValue> &other) const
        {
        return !(*this == other);
        }
    };

//Base record field. Vestigial.
//Used when it isn't known if the record is required or optional.
template<class T>
struct SubRecord
    {
    T value;
    bool isLoaded;

    SubRecord():
        isLoaded(false),
        value()
        {
        //
        }

    ~SubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (isLoaded && value != DefaultSingleton<T>::value());
        }

    void Load()
        {
        isLoaded = true;
        }

    void Unload()
        {
        T newValue;
        value.~T();
        value = newValue;
        isLoaded = false;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool was_loaded = ReadChunk(buffer, subSize, &value, sizeof(T), isLoaded);
        isLoaded = true;
        return was_loaded;
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(isLoaded)
            writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    T *operator->() const
        {
        return &value;
        }
    bool operator ==(const SubRecord<T> &other) const
        {
        return (value == other.value &&
                isLoaded == other.isLoaded);
        }
    bool operator !=(const SubRecord<T> &other) const
        {
        return !(*this == other);
        }
    };

//Used for subrecords that are required
//Even if not actually loaded from disk, they are always considered loaded even if they're explicitly unloaded.
//Unloading them simply resets the values to default.
template<class T>
struct ReqSubRecord
    {
    T value;

    ReqSubRecord():
        value()
        {
        //
        }
    ~ReqSubRecord()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return true;
        }
    void Load()
        {
        //
        }
    void Unload()
        {
        T newValue;
        value.~T();
        value = newValue;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        return ReadChunk(buffer, subSize, &value, sizeof(T), false);
    //#ifdef CBASH_CHUNK_LCHECK
    //    else if(subSize < sizeof(T))
    //        {
    //    #ifdef CBASH_CHUNK_WARN
    //        uint32_t test = *((uint32_t *)(buffer - 6));
    //        uint32_t test2 = *((uint32_t *)(buffer + subSize));
    //        if (!(test == REV32(DATA) && (test2 == REV32(DIAL) || test2 == REV32(GRUP)) && subSize == 1 && sizeof(T) == 2) &&
    //            !(test == REV32(DATA) && (test2 == REV32(CNAM) || test2 == REV32(RNAM) || test2 == REV32(WMI1)) && sizeof(T) == 4 && subSize == 1) &&
    //            !(test == REV32(SNDX) && subSize == 12) &&
    //            !(test == REV32(DNAM) && test2 == REV32(ITXT) && subSize == 3) &&
    //            !(test == REV32(DNAM) && (test2 == REV32(ARMO) || test2 == REV32(BNAM)) && subSize == 4 && sizeof(T) == 12) &&
    //            !(test == REV32(DNAM) && (test2 == REV32(CRDT) || test2 == REV32(VATS)) && sizeof(T) == 204) && //multiple possible subSizes
    //            !(test == REV32(VATS) && (test2 == REV32(VNAM) || test2 == REV32(WEAP)) && subSize == 16 && sizeof(T) == 20) &&
    //            !(test == REV32(DATA) && (test2 == REV32(NAM1) || test2 == REV32(NAM2) || test2 == REV32(VNAM) || test2 == REV32(PROJ)) && subSize == 68 && sizeof(T) == 84) &&
    //            !(test == REV32(DATA) && (test2 == REV32(CTDA) || test2 == REV32(INDX) || test2 == REV32(QOBJ)) && subSize == 2 && sizeof(T) == 8) &&
    //            !(test == REV32(DATA) && (test2 == REV32(IDLE) || test2 == REV32(GRUP)) && subSize == 6 && sizeof(T) == 8) &&
    //            !(test == REV32(PKDT) && subSize == 8 && sizeof(T) == 12) &&
    //            !(test == REV32(DATA) && subSize == 184 && sizeof(T) == 196) &&
    //            !(test == REV32(DNAM) && subSize == 184 && sizeof(T) == 196) &&
    //            !(test == REV32(DATA) && (test2 == REV32(EFSH) || test2 == REV32(GRUP)) && sizeof(T) == 308) //multiple possible subSizes
    //            )
    //            {
    //            printer("ReqSubRecord: Info - Unable to fully parse chunk (%c%c%c%c). Size "
    //                   "of chunk (%u) is less than the size of the subrecord (%u) and any "
    //                   "remaining fields have their default value.\n",
    //                   buffer[-6], buffer[-5], buffer[-4], buffer[-3],
    //                   subSize, sizeof(T));
    //            CBASH_CHUNK_DEBUG
    //            }
    //    #endif
    //        memcpy(&value, buffer, subSize);
    //        }
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        writer.record_write_subrecord(_Type, &value, sizeof(T));
        }

    const T *operator->() const
        {
        return &value;
        }
    T *operator->()
        {
        return &value;
        }
    bool operator ==(const ReqSubRecord<T> &other) const
        {
        return (value == other.value);
        }
    bool operator !=(const ReqSubRecord<T> &other) const
        {
        return !(*this == other);
        }
    };

template<class T>
class DefaultSingleton
    {
    private:
        DefaultSingleton() {};                                     // Private constructor
        DefaultSingleton(const DefaultSingleton&);                 // Prevent copy-construction
        DefaultSingleton& operator=(const DefaultSingleton&);      // Prevent assignment

    public:
        static T& value()
            {
            static T defaultValue;
            return defaultValue;
            }
    };

//Used for subrecords that are optional
//Even if loaded, they are considered unloaded if they're equal to their defaults
template<class T>
struct OptSubRecord
    {
    T *value;

    OptSubRecord():
        value(NULL)
        {
        //
        }

    ~OptSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (value != NULL && *value != DefaultSingleton<T>::value());
        }

    void Load()
        {
        if(value == NULL)
            value = new T();
        }
    void Unload()
        {
        delete value;
        value = NULL;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool is_loaded = (value != NULL);
        if(!is_loaded)
            value = new T();
        return ReadChunk(buffer, subSize, value, sizeof(T), is_loaded);
        //#ifdef CBASH_CHUNK_LCHECK
        //    else if(subSize < sizeof(T))
        //    {
        //#ifdef CBASH_CHUNK_WARN
        //    uint32_t test = *((uint32_t *)(buffer - 6));
        //    uint32_t test2 = *((uint32_t *)(buffer + subSize));
        //    if (!(test == REV32(XCLC) && subSize == 8) &&
        //        !(test == REV32(DAT2) && (test2 == REV32(ONAM) || test2 == REV32(QNAM) || test2 == REV32(RCIL) || test2 == REV32(AMMO)) && subSize == 12 && sizeof(T) == 20)
        //        )
        //        {
        //        printer("OptSubRecord: Info - Unable to fully parse chunk (%c%c%c%c). Size "
        //               "of chunk (%u) is less than the size of the subrecord (%u) and any "
        //               "remaining fields have their default value.\n",
        //               buffer[-6], buffer[-5], buffer[-4], buffer[-3],
        //               subSize, sizeof(T));
        //        CBASH_CHUNK_DEBUG
        //        }
        //#endif
        //    memcpy(value, buffer, subSize);
        //    }
        //#endif
        }

    void Write(FileWriter &writer)
        {
        if(value != NULL)
            value->Write(writer);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value != NULL)
            writer.record_write_subrecord(_Type, value, sizeof(T));
        }

    T *operator->() const
        {
        return value;
        }

    OptSubRecord<T>& operator = (const OptSubRecord<T> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    value = new T();
                else
                    value->~T();
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }

    bool operator ==(const OptSubRecord<T> &other) const
        {
        if(!IsLoaded())
            {
            if(!other.IsLoaded())
                return true;
            }
        else if(other.IsLoaded() && *value == *other.value)
            return true;
        return false;
        }

    bool operator !=(const OptSubRecord<T> &other) const
        {
        return !(*this == other);
        }
    };

//Identical to OptSubRecord except for IsLoaded
//Once loaded, they are always considered loaded unless they're explicitly unloaded.
//They don't compare to the default value to see if they're still considered loaded.
template<class T>
struct SemiOptSubRecord
    {
    T *value;

    SemiOptSubRecord():
        value(NULL)
        {
        //
        }
    ~SemiOptSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded() const
        {
        return (value != NULL);
        }

    void Load()
        {
        if(value == NULL)
            value = new T();
        }

    void Unload()
        {
        delete value;
        value = NULL;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool is_loaded = (value != NULL);
        if(!is_loaded)
            value = new T();
        return ReadChunk(buffer, subSize, value, sizeof(T), is_loaded);
    //#ifdef CBASH_CHUNK_LCHECK
    //    else if(subSize < sizeof(T))
    //        {
    //    #ifdef CBASH_CHUNK_WARN
    //        uint32_t test = *((uint32_t *)(buffer - 6));
    //        if(!(test == REV32(XLOC) && subSize == 12 && sizeof(T) == 20))
    //            {
    //            printer("SemiOptSubRecord: Info - Unable to fully parse chunk (%c%c%c%c). Size "
    //                   "of chunk (%u) is less than the size of the subrecord (%u) and any "
    //                   "remaining fields have their default value.\n",
    //                   buffer[-6], buffer[-5], buffer[-4], buffer[-3],
    //                   subSize, sizeof(T));
    //            CBASH_CHUNK_DEBUG
    //            }
    //    #endif
    //        memcpy(value, buffer, subSize);
    //        }
    //#endif
        }

    void Write(FileWriter &writer)
        {
        if(value != NULL)
            value->Write(writer);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value != NULL)
            writer.record_write_subrecord(_Type, value, sizeof(T));
        }

    T *operator->() const
        {
        return value;
        }

    SemiOptSubRecord<T>& operator = (const SemiOptSubRecord<T> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    value = new T();
                else
                    value->~T();
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }

    bool operator ==(const SemiOptSubRecord<T> &other) const
        {
        if(!IsLoaded())
            {
            if(!other.IsLoaded())
                return true;
            }
        else if(other.IsLoaded() && *value == *other.value)
            return true;
        return false;
        }

    bool operator !=(const SemiOptSubRecord<T> &other) const
        {
        return !(*this == other);
        }
    };

//Hack to support OBMEEFIX
//Identical to OptSubRecord except for IsLoaded
//If value->efixOverrides is equal to 0, it unloads itself
template<class T>
struct OBMEEFIXSubRecord
    {
    T *value;

    OBMEEFIXSubRecord():
        value(NULL)
        {
        //
        }

    ~OBMEEFIXSubRecord()
        {
        Unload();
        }

    uint32_t GetSize() const
        {
        return sizeof(T);
        }

    bool IsLoaded()
        {
        if(value == NULL)
            return false;
        if(value->efixOverrides == 0)
            {
            Unload();
            return false;
            }

        return (*value != DefaultSingleton<T>::value());
        }

    bool Internal_IsLoaded() const
        {
        return (value != NULL && *value != DefaultSingleton<T>::value());
        }

    void Load()
        {
        if(value == NULL)
            value = new T();
        }

    void Unload()
        {
        delete value;
        value = NULL;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        bool is_loaded = (value != NULL);
        if(!is_loaded)
            value = new T();
        return ReadChunk(buffer, subSize, value, sizeof(T), is_loaded);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(IsLoaded())
            writer.record_write_subrecord(_Type, value, sizeof(T));
        }

    T *operator->() const
        {
        return value;
        }

    OBMEEFIXSubRecord<T>& operator = (const OBMEEFIXSubRecord<T> &rhs)
        {
        if(this != &rhs)
            if(rhs.value != NULL)
                {
                if(value == NULL)
                    value = new T();
                else
                    value->~T();
                *value = *rhs.value;
                }
            else
                {
                delete value;
                value = NULL;
                }
        return *this;
        }

    bool operator ==(const OBMEEFIXSubRecord<T> &other) const
        {
        if(!Internal_IsLoaded())
            {
            if(!other.Internal_IsLoaded())
                return true;
            }
        else if(other.Internal_IsLoaded() && *value == *other.value)
            return true;
        return false;
        }

    bool operator !=(const OBMEEFIXSubRecord<T> &other) const
        {
        return !(*this == other);
        }
    };

template<class T, class _Pr = std::less<T> >
struct OrderedPackedArray
    {
    std::vector<T> value;

    OrderedPackedArray()
        {
        //
        }

    ~OrderedPackedArray()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T) * (uint32_t)value.size();
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }

    void Unload()
        {
        value.clear();
        }

    void resize(uint32_t &newSize)
        {
        value.resize(newSize);
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        if(subSize % sizeof(T) == 0)
            {
            if(subSize == 0)
                {
                buffer += subSize;
                return false;
                }
            value.resize(subSize / sizeof(T));
            memcpy(&value[0], buffer, subSize);
            }
        #ifdef CBASH_CHUNK_WARN
            else
                {
                printer("PackedArray: Error - Unable to parse chunk. "
                       "Size of chunk (%u) is not a multiple of the "
                       "size of the subrecord (%u)\n", subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
                }
        #endif
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        std::sort(value.begin(), value.end(), _Pr());
        if(value.size())
            writer.record_write_subrecord(_Type, &value[0], (uint32_t)value.size() * sizeof(T));
        }

    OrderedPackedArray<T, _Pr>& operator = (const OrderedPackedArray<T, _Pr> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                value[x] = rhs.value[x];
            }
        return *this;
        }

    bool operator ==(const OrderedPackedArray<T, _Pr> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < (uint32_t)value.size(); ++x)
                if(value[x] != other.value[x])
                    return false;
            return true;
            }
        return false;
        }

    bool operator !=(const OrderedPackedArray<T, _Pr> &other) const
        {
        return !(*this == other);
        }
    };

template<class T>
struct UnorderedPackedArray
    {
    std::vector<T> value;

    UnorderedPackedArray()
        {
        //
        }

    ~UnorderedPackedArray()
        {
        //
        }

    uint32_t GetSize() const
        {
        return sizeof(T) * (uint32_t)value.size();
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }

    void Unload()
        {
        value.clear();
        }

    void resize(uint32_t newSize)
        {
        value.resize(newSize);
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        if(subSize % sizeof(T) == 0)
            {
            if(subSize == 0)
                {
                buffer += subSize;
                return false;
                }
            value.resize(subSize / sizeof(T));
            memcpy(&value[0], buffer, subSize);
            }
        #ifdef CBASH_CHUNK_WARN
            else
                {
                printer("UnorderedPackedArray: Error - Unable to parse chunk. "
                       "Size of chunk (%u) is not a multiple of the "
                       "size of the subrecord (%u)\n", subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
                }
        #endif
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        if(value.size())
            writer.record_write_subrecord(_Type, &value[0], (uint32_t)value.size() * sizeof(T));
        }

    void ReqWrite(uint32_t _Type, FileWriter &writer)
        {
        if(value.size())
            writer.record_write_subrecord(_Type, &value[0], (uint32_t)value.size() * sizeof(T));
        else
            writer.record_write_subheader(_Type, 0);
        }

    UnorderedPackedArray<T>& operator = (const UnorderedPackedArray<T> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                value[x] = rhs.value[x];
            }
        return *this;
        }

    bool operator ==(const UnorderedPackedArray<T> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < value.size(); ++x)
                {
                bool good = false;
                for(uint32_t y = 0; y < value.size(); ++y)
                    if(value[x] == other.value[y])
                        {
                        //Found its match
                        good = true;
                        break;
                        }
                if(!good) return false;
                }
            return true;
            }
        return false;
        }

    bool operator !=(const UnorderedPackedArray<T> &other) const
        {
        return !(*this == other);
        }
    };

template<class T, class _Pr = std::less<T> >
struct OrderedSparseArray
    {
    std::vector<T> value;

    OrderedSparseArray()
        {
        //
        }
    ~OrderedSparseArray()
        {
        //
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }

    void Unload()
        {
        value.clear();
        }

    void resize(uint32_t &newSize)
        {
        value.resize(newSize);
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        T curValue;
        if(subSize > sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("OrderedSparseArray: Warning - Unable to fully parse chunk (%c%c%c%c). "
                       "Size of chunk (%u) is larger than the size of the subrecord (%u) "
                       "and will be truncated.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&curValue, buffer, sizeof(T));
            }
        #ifdef CBASH_CHUNK_LCHECK
            else if(subSize < sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("OrderedSparseArray: Info - Unable to fully parse chunk (%c%c%c%c). Size "
                       "of chunk (%u) is less than the size of the subrecord (%u) and any "
                       "remaining fields have their default value.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&curValue, buffer, subSize);
            }
        #endif
        else
            memcpy(&curValue, buffer, subSize);
        value.push_back(curValue);
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(FileWriter &writer)
        {
        std::sort(value.begin(), value.end(), _Pr());
        for(uint32_t p = 0; p < value.size(); p++)
            value[p].Write(writer);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        std::sort(value.begin(), value.end(), _Pr());
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, &value[p], sizeof(T));
        }

    void Write(FileWriter &writer, bool)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            value[p].Write(writer);
        }

    void Write(uint32_t _Type, FileWriter &writer, bool)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, &value[p], sizeof(T));
        }

    OrderedSparseArray<T, _Pr>& operator = (const OrderedSparseArray<T, _Pr> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                value[x] = rhs.value[x];
            }
        return *this;
        }

    bool operator ==(const OrderedSparseArray<T, _Pr> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < (uint32_t)value.size(); ++x)
                if(value[x] != other.value[x])
                    return false;
            return true;
            }
        return false;
        }
    bool operator !=(const OrderedSparseArray<T, _Pr> &other) const
        {
        return !(*this == other);
        }
    };

template<class T, class _Pr>
struct OrderedSparseArray<T *, _Pr>
    {
    std::vector<T *> value;

    OrderedSparseArray()
        {
        //
        }
    ~OrderedSparseArray()
        {
        Unload();
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }
    void Unload()
        {
        for(uint32_t x = 0; x < value.size(); ++x)
            delete value[x];
        value.clear();
        }

    void resize(uint32_t &newSize)
        {
        //Shrink
        uint32_t size = (uint32_t)value.size();
        for(; size > newSize;)
            delete value[--size];
        value.resize(newSize);
        //Grow
        for(; size < newSize;)
            value[size++] = new T;
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        value.push_back(new T);
        if(subSize > sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("OrderedSparseArray: Warning - Unable to fully parse chunk (%c%c%c%c). "
                       "Size of chunk (%u) is larger than the size of the subrecord (%u) "
                       "and will be truncated.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&(*value.back()), buffer, sizeof(T));
            }
        #ifdef CBASH_CHUNK_LCHECK
            else if(subSize < sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                uint32_t test = *((uint32_t *)(buffer - 6));
                if (!((test == REV32(SCRO) || test == REV32(SCRV)) && subSize == 4) &&
                    !(test == REV32(CTDA) && (subSize == 20 || subSize == 24)&& sizeof(T) == 28)
                    )
                    {
                    printer("OrderedSparseArray: Info - Unable to fully parse chunk (%c%c%c%c). Size "
                           "of chunk (%u) is less than the size of the subrecord (%u) and any "
                           "remaining fields have their default value.\n",
                           buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                           subSize, sizeof(T));
                    CBASH_CHUNK_DEBUG
                    }
            #endif
            memcpy(&(*value.back()), buffer, subSize);
            }
        #endif
        else
            memcpy(&(*value.back()), buffer, subSize);
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(FileWriter &writer)
        {
        std::sort(value.begin(), value.end(), _Pr());
        for(uint32_t p = 0; p < value.size(); p++)
            value[p]->Write(writer);
        }

    void Write(FileWriter &writer, bool)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            value[p]->Write(writer);
        }

    void Write(uint32_t _Type, FileWriter &writer)
        {
        std::sort(value.begin(), value.end(), _Pr());
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, value[p], sizeof(T));
        }

    void Write(uint32_t _Type, FileWriter &writer, bool)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, value[p], sizeof(T));
        }

    OrderedSparseArray<T *, _Pr>& operator = (const OrderedSparseArray<T *, _Pr> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                {
                value[x] = new T;
                *value[x] = *rhs.value[x];
                }
            }
        return *this;
        }
    bool operator ==(const OrderedSparseArray<T *, _Pr> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < (uint32_t)value.size(); ++x)
                if(*value[x] != *other.value[x])
                    return false;
            return true;
            }
        return false;
        }
    bool operator !=(const OrderedSparseArray<T *, _Pr> &other) const
        {
        return !(*this == other);
        }
    };

template<class T>
struct UnorderedSparseArray
    {
    std::vector<T> value;

    UnorderedSparseArray()
        {
        //
        }
    ~UnorderedSparseArray()
        {
        //
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }

    void Unload()
        {
        value.clear();
        }

    void resize(uint32_t &newSize)
        {
        value.resize(newSize);
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        T curValue;
        if(subSize > sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("UnorderedSparseArray: Warning - Unable to fully parse chunk (%c%c%c%c). "
                       "Size of chunk (%u) is larger than the size of the subrecord (%u) "
                       "and will be truncated.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&curValue, buffer, sizeof(T));
            }
        #ifdef CBASH_CHUNK_LCHECK
            else if(subSize < sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("UnorderedSparseArray: Info - Unable to fully parse chunk (%c%c%c%c). Size "
                       "of chunk (%u) is less than the size of the subrecord (%u) and any "
                       "remaining fields have their default value.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&curValue, buffer, subSize);
            }
        #endif
        else
            memcpy(&curValue, buffer, subSize);
        value.push_back(curValue);
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(FileWriter &writer)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            value[p].Write(writer);
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, &value[p], sizeof(T));
        }

    UnorderedSparseArray<T>& operator = (const UnorderedSparseArray<T> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                value[x] = rhs.value[x];
            }
        return *this;
        }

    bool operator ==(const UnorderedSparseArray<T> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < value.size(); ++x)
                {
                bool good = false;
                for(uint32_t y = 0; y < value.size(); ++y)
                    if(value[x] == other.value[y])
                        {
                        //Found its match
                        good = true;
                        break;
                        }
                if(!good) return false;
                }
            return true;
            }
        return false;
        }
    bool operator !=(const UnorderedSparseArray<T> &other) const
        {
        return !(*this == other);
        }
    };

template<class T>
struct UnorderedSparseArray<T *>
    {
    std::vector<T *> value;

    UnorderedSparseArray()
        {
        //
        }
    ~UnorderedSparseArray()
        {
        Unload();
        }

    bool IsLoaded() const
        {
        return value.size() != 0;
        }

    void Unload()
        {
        for(uint32_t x = 0; x < value.size(); ++x)
            delete value[x];
        value.clear();
        }

    void resize(uint32_t &newSize)
        {
        //Shrink
        uint32_t size = (uint32_t)value.size();
        for(; size > newSize;)
            delete value[--size];
        value.resize(newSize);
        //Grow
        for(; size < newSize;)
            value[size++] = new T;
        return;
        }

    bool Read(unsigned char *&buffer, const uint32_t &subSize)
        {
        value.push_back(new T);
        if(subSize > sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("UnorderedSparseArray: Warning - Unable to fully parse chunk (%c%c%c%c). "
                       "Size of chunk (%u) is larger than the size of the subrecord (%u) "
                       "and will be truncated.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&(*value.back()), buffer, sizeof(T));
            }
        #ifdef CBASH_CHUNK_LCHECK
            else if(subSize < sizeof(T))
            {
            #ifdef CBASH_CHUNK_WARN
                printer("UnorderedSparseArray: Info - Unable to fully parse chunk (%c%c%c%c). Size "
                       "of chunk (%u) is less than the size of the subrecord (%u) and any "
                       "remaining fields have their default value.\n",
                       buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                       subSize, sizeof(T));
                CBASH_CHUNK_DEBUG
            #endif
            memcpy(&(*value.back()), buffer, subSize);
            }
        #endif
        else
            memcpy(&(*value.back()), buffer, subSize);
        //size = subSize;
        buffer += subSize;
        return true;
        }

    void Write(FileWriter &writer)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            value[p]->Write(writer);
        }
    void Write(uint32_t _Type, FileWriter &writer)
        {
        for(uint32_t p = 0; p < value.size(); p++)
            writer.record_write_subrecord(_Type, value[p], sizeof(T));
        }

    UnorderedSparseArray<T *>& operator = (const UnorderedSparseArray<T *> &rhs)
        {
        if(this != &rhs)
            {
            value.resize(rhs.value.size());
            for(uint32_t x = 0; x < value.size(); x++)
                {
                value[x] = new T;
                *value[x] = *rhs.value[x];
                }
            }
        return *this;
        }

    bool operator ==(const UnorderedSparseArray<T *> &other) const
        {
        if(value.size() == other.value.size())
            {
            for(uint32_t x = 0; x < value.size(); ++x)
                {
                bool good = false;
                for(uint32_t y = 0; y < value.size(); ++y)
                    if(*value[x] == *other.value[y])
                        {
                        //Found its match
                        good = true;
                        break;
                        }
                if(!good) return false;
                }
            return true;
            }
        return false;
        }
    bool operator !=(const UnorderedSparseArray<T *> &other) const
        {
        return !(*this == other);
        }
    };

template <typename T, typename countType, int countRecord>
class ReqCounted : public T
{
public:
    void Write(FileWriter &writer)
    {
        countType count = static_cast<countType>(value.size());
        writer.record_write_subrecord(countRecord, &count, sizeof(count));
        for (uint32_t p = 0; p < value.size(); p++)
            value[p]->Write(writer);
    }

    void Write(uint32_t _Type, FileWriter &writer)
    {
        countType count = static_cast<countType>(value.size());
        writer.record_write_subrecord(countRecord, &count, sizeof(count));
        T::Write(_Type, writer);
    }
};

template <typename T, typename countType, int countRecord>
class OptCounted : public T
{
public:
    void Write(FileWriter &writer)
    {
        countType count = value.size();
        if (count)
        {
            writer.record_write_subrecord(countRecord, &count, sizeof(count));
            for (uint32_t p = 0; p < value.size(); p++)
                value[p]->Write(writer);
        }
    }

    void Write(uint32_t _Type, FileWriter &writer)
    {
        countType count = value.size();
        if (count)
        {
            writer.record_write_subrecord(countRecord, &count, sizeof(count));
            T::Write(_Type, writer);
        }
    }
};
