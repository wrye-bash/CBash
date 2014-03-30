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
// Common.cpp
#include "Common.h"
#include "zlib/zlib.h"
#include <sys/utime.h>

int (*printer)(const char * _Format, ...) = &printf;
SINT32 (*LoggingCallback)(const STRING) = NULL;
void (*RaiseCallback)(const STRING) = NULL;

#ifdef CBASH_DEBUG_VARS
    std::map<unsigned long, unsigned long> uint32_uint32_map1;
    std::map<unsigned long, unsigned long> uint32_uint32_map2;
    std::map<unsigned long, unsigned long> uint32_uint32_map3;
    std::map<char *, unsigned long> string_uint32_map;
    std::map<unsigned long, char *> uint32_string_map;
    unsigned long debug_temp1 = 0;
    unsigned long debug_temp2 = 0;
    unsigned long debug_temp3 = 0;
    unsigned long debug_temp4 = 0;
#endif

#ifdef CBASH_CALLTIMING
    std::map<char *, double> CallTime;
#endif

#ifdef CBASH_CALLCOUNT
    std::map<char *, unsigned long> CallCount;
#endif

const STRING Ex_NULL::__CLR_OR_THIS_CALL what() const
    {
    return "NULL Pointer";
    }

const STRING Ex_INVALIDINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Index";
    }

const STRING Ex_INVALIDCOLLECTIONINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Collection Index";
    }

const STRING Ex_INVALIDMODINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Mod Index";
    }

int icmps(const STRING lhs, const STRING rhs)
    {
    if(lhs == rhs)
        return 0;
    if(lhs == NULL)
        return -1;
    if(rhs == NULL)
        return 1;
    return _stricmp(lhs, rhs);
    }

int cmps(const STRING lhs, const STRING rhs)
    {
    if(lhs == rhs)
        return 0;
    if(lhs == NULL)
        return -1;
    if(rhs == NULL)
        return 1;
    return strcmp(lhs, rhs);
    }

bool sameStr::operator()( const STRING s1, const STRING s2 ) const
    {
    return icmps(s1, s2) < 0;
    }

#ifdef CBASH_DEBUG_CHUNK
    void peek_around(unsigned char *position, UINT32 length)
        {
        for(SINT32 x = length; x > 0; x--)
            printf("%02X ", (position)[-x]);
        for(UINT32 x = 0; x < length; x++)
            printf("%02X ", (position)[x]);
        printf("\n\n");
        for(SINT32 x = length; x > 0; x--)
            printf("%c", (position)[-x]);
        for(UINT32 x = 0; x < length; x++)
            printf("%c", (position)[x]);
        printf("\n");
        }
#endif

GenericOp::GenericOp()
    {
    //
    }

GenericOp::~GenericOp()
    {
    //
    }

STRING DeGhostModName(STRING const ModName)
    {
    STRING NonGhostName = NULL;
    UINT32 NameLength = (UINT32)strlen(ModName) + 1;
    if(NameLength > 7)
        {
        if(icmps(".ghost",ModName + NameLength - 7) == 0)
            {
            NonGhostName = new char[NameLength];
            strcpy_s(NonGhostName, NameLength, ModName);
            NonGhostName[NameLength - 7] = 0x00;
            //printer("DeGhostModName: De-ghosted (%s)(%d) to (%s)(%d)\n", ModName, strlen(ModName), NonGhostName, strlen(NonGhostName));
            return NonGhostName;
            }
        }
    return NULL;
    }

bool FileExists(STRING const FileName)
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

STRING GetTemporaryFileName(STRING FileName, bool IsBackup)
    {
    STRING NonGhostName = DeGhostModName(FileName);
    STRING const &UsedName = NonGhostName ? NonGhostName : FileName;
    static time_t last_save = time(NULL);

    time_t ltime;
    struct tm current_time;

    //Keep at least 1 minute between each datestamp
    time(&ltime);
    if(ltime - last_save < 60)
        ltime = last_save + 60;
    last_save = ltime;

    switch(_localtime64_s(&current_time, &ltime))
        {
        case 0:
            break;
        case EINVAL:
            //Fallthrough intentional. EINVAL should never be returned.
        default:
            printer("GetTemporaryFileName: Error - Unable to make a temporary filename for \"%s\". _localtime64_s failed due to invalid arguments.\n", UsedName);
            return NULL;
        }

    STRING temp_extension = IsBackup ? ".bak.%Y_%m_%d_%H_%M_%S" : ".new.%Y_%m_%d_%H_%M_%S";
    UINT32 name_size = (UINT32)strlen(UsedName);
    UINT32 temp_size = name_size + (UINT32)strlen(".XXX.XXXX_XX_XX_XX_XX_XX") + 1;
    STRING temp_name = new char[temp_size];

    strcpy_s(temp_name, temp_size, UsedName);
    delete []NonGhostName;
    strftime(temp_name + name_size, temp_size, temp_extension, &current_time);

    //If the new name already exists, add another minute until a free name is available
    //If 10 tries pass, then give up.
    UINT32 attempts = 0;
    while(FileExists(temp_name))
        {
        if(attempts > 10)
            break;
        attempts++;
        current_time.tm_min++;
        mktime(&current_time);
        strftime(temp_name + name_size, temp_size, temp_extension, &current_time);
        };

    return temp_name;
    }

RenameOp::RenameOp(STRING _original_name, STRING _destination_name):
    original_name(_original_name),
    destination_name(_destination_name),
    GenericOp()
    {
    //
    }

RenameOp::~RenameOp()
    {
    delete []original_name;
    }

bool RenameOp::perform()
    {
    static time_t last_save = time(NULL);
    time_t ltime;
    time(&ltime);

    //Keep at least 1 minute between each datestamp
    time(&ltime);
    if(ltime - last_save < 60)
        ltime = last_save + 60;
    last_save = ltime;

    struct stat o_time;
    struct _utimbuf original_times;

    original_times.actime = ltime;
    original_times.modtime = ltime;

    //Backup any existing file
    if(FileExists(destination_name))
        {
        stat(destination_name, &o_time);
        original_times.actime = o_time.st_atime;
        original_times.modtime = o_time.st_mtime;
        STRING backup_name = GetTemporaryFileName(destination_name, true);

        switch(rename(destination_name, backup_name))
            {
            case 0:
                _utime(backup_name, &original_times);
                break;
            case EACCES:
                printer("RenameOp: Error - Unable to rename existing file from \"%s\" to \"%s\". File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path.\n", destination_name, backup_name);
                break;
            case ENOENT:
                printer("RenameOp: Error - Unable to rename existing file from \"%s\" to \"%s\". File or path specified by oldname not found.\n", destination_name, backup_name);
                break;
            case EINVAL:
                printer("RenameOp: Error - Unable to rename existing file from \"%s\" to \"%s\". Name contains invalid characters.\n", destination_name, backup_name);
                break;
            case EEXIST:
                printer("RenameOp: Error - Unable to rename existing file from \"%s\" to \"%s\". The new file name already exists.\n", destination_name, backup_name);
                break;
            default:
                perror("Unknown");
                printer("RenameOp: Error - Unable to rename existing file from \"%s\" to \"%s\". Unknown details.\n", destination_name, backup_name);
                break;
            }
        delete []backup_name;
        }

    //Replace any existing file with the new file
    switch(rename(original_name, destination_name))
        {
        case 0:
            _utime(destination_name, &original_times);
            return true;
        case EACCES:
            printer("RenameOp: Warning - Unable to rename temporary file from \"%s\" to \"%s\". File or directory specified by newname already exists or could not be created (invalid path); or oldname is a directory and newname specifies a different path.\n", original_name, destination_name);
            break;
        case ENOENT:
            printer("RenameOp: Warning - Unable to rename temporary file from \"%s\" to \"%s\". File or path specified by oldname not found.\n", original_name, destination_name);
            break;
        case EINVAL:
            printer("RenameOp: Warning - Unable to rename temporary file from \"%s\" to \"%s\". Name contains invalid characters.\n", original_name, destination_name);
            break;
        case EEXIST:
            printer("RenameOp: Warning - Unable to rename temporary file from \"%s\" to \"%s\". The new file name already exists.\n", original_name, destination_name);
            break;
        default:
            perror("Unknown");
            printer("RenameOp: Warning - Unable to rename temporary file from \"%s\" to \"%s\". Unknown details.\n", original_name, destination_name);
            break;
        }
    return false;
    }

bool AlmostEqual(FLOAT32 A, FLOAT32 B, SINT32 maxUlps)
    {
    SINT32 aInt = *(SINT32*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    SINT32 bInt = *(SINT32*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    if (abs(aInt - bInt) <= maxUlps)
        return true;
    return false;
    }

FileWriter::FileWriter(STRING filename, UINT32 size):
    file_buffer(NULL),
    record_buffer(NULL),
    compressed_buffer(NULL),
    file_buffer_used(0),
    record_buffer_used(0),
    compressed_buffer_used(0),
    file_buffer_size(size),
    record_buffer_size(size),
    compressed_buffer_size(size),
    fh(-1),
    FileName(filename)
    {
    if(size == 0)
        return;
    file_buffer = new unsigned char[file_buffer_size];
    record_buffer = new unsigned char[record_buffer_size];
    compressed_buffer = new unsigned char[compressed_buffer_size];
    }

FileWriter::~FileWriter()
    {
    close();
    delete []file_buffer;
    delete []record_buffer;
    delete []compressed_buffer;
    }

SINT32 FileWriter::open()
    {
    if(fh != -1 || FileName == NULL)
        return -1;
    errno_t err = _sopen_s(&fh, FileName, _O_CREAT | _O_RDWR | _O_BINARY, _SH_DENYWR, _S_IREAD | _S_IWRITE );
    if( err != 0 )
        {
        switch(err)
            {
            case EACCES:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. Given path is a directory, or file is read-only, but an open-for-writing operation was attempted.\n", FileName);
                return -1;
            case EEXIST:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. _O_CREAT and _O_EXCL flags were specified, but filename already exists.\n", FileName);
                return -1;
            case EINVAL:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. Invalid oflag, shflag, or pmode  argument, or pfh or filename was a null pointer.\n", FileName);
                return -1;
            case EMFILE:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. No more file descriptors available.\n", FileName);
                return -1;
            case ENOENT:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. File or path not found.\n", FileName);
                return -1;
            default:
                printer("FileWriter: Error - Unable to open \"%s\" as read,write via file handle. An unknown error occurred.\n", FileName);
                return -1;
            }
        _close(fh);
        return -1;
        }
    return 0;
    }

SINT32 FileWriter::close()
    {
    if(fh != -1)
        {
        if(file_buffer_used)
            {
            _write(fh, file_buffer, file_buffer_used);
            file_buffer_used = 0;
            }
        _close(fh);
        }
    fh = -1;
    return 0;
    }

void FileWriter::record_write(const void *source, UINT32 length)
    {
    if(length == 0)
        return;
    if(source == NULL)
        {
        printer("FileWriter:write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }

    if((length + record_buffer_used) > record_buffer_size)
        {
        //Should be rare or never occur with a sufficiently large initial buffer size
        record_buffer_size = (length + record_buffer_used) * 2;
        unsigned char *resized_buffer = new unsigned char[record_buffer_size];
        memcpy(resized_buffer, record_buffer, record_buffer_used);
        delete []record_buffer;
        record_buffer = resized_buffer;
        }

    memcpy(record_buffer + record_buffer_used, source, length);
    record_buffer_used += length;
    return;
    }

void FileWriter::record_write_subheader(UINT32 signature, UINT32 length)
    {
    if(length <= 65535)
        {
        record_write(&signature, 4);
        record_write(&length, 2);
        }
    else //Requires XXXX SubRecord
        {
        UINT32 _Temp = 4;
        record_write("XXXX", 4);
        record_write(&_Temp, 2);
        record_write(&length, 4);
        record_write(&signature, 4);
        _Temp = 0;
        record_write(&_Temp, 2);
        }
    return;
    }

void FileWriter::record_write_subrecord(UINT32 signature, const void *source, UINT32 length)
    {
    record_write_subheader(signature, length);
    record_write(source, length);
    return;
    }

UINT32 FileWriter::record_compress()
    {
    UINT32 compSize = compressBound(record_buffer_used);
    if(compSize + 4 > compressed_buffer_size)
        {
        delete []compressed_buffer;
        compressed_buffer_size = compSize + 4;
        compressed_buffer = new unsigned char[compressed_buffer_size];
        }
    else
        compSize = compressed_buffer_size;
    compress2(compressed_buffer + 4, &compSize, record_buffer, record_buffer_used, 6);
    memcpy(compressed_buffer, &record_buffer_used, 4);
    std::swap(record_buffer, compressed_buffer);
    std::swap(record_buffer_size, compressed_buffer_size);
    record_buffer_used = compSize + 4;
    return record_buffer_used;
    }

UINT32 FileWriter::record_size()
    {
    return record_buffer_used;
    }

void FileWriter::record_flush()
    {
    file_write(record_buffer, record_buffer_used);
    record_buffer_used = 0;
    return;
    }

UINT32 FileWriter::file_tell()
    {
    return file_buffer_used + _tell(fh);
    }

void FileWriter::file_write(const void *source_buffer, UINT32 source_buffer_used)
    {
    if(source_buffer_used == 0)
        return;

    if(fh == -1 || file_buffer == NULL)
        {
        printer("FileWriter::file_write: Error - Unable to write. File buffer or File Handle is invalid.\n");
        return;
        }
    else if(source_buffer == NULL)
        {
        printer("FileWriter::file_write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }

    //Flush the file buffer if it is getting full
    if((file_buffer_used + source_buffer_used) >= file_buffer_size)
        {
        //file_flush();
        _write(fh, file_buffer, file_buffer_used);
        file_buffer_used = 0;
        }
    //Use the file buffer if there's room
    if(source_buffer_used < file_buffer_size)
        {
        memcpy(file_buffer + file_buffer_used, source_buffer, source_buffer_used);
        file_buffer_used += source_buffer_used;
        }
    else
        {
        //Otherwise, write directly to disk.
        _write(fh, source_buffer, source_buffer_used);
        }
    return;
    }

void FileWriter::file_write(UINT32 position, const void *source_buffer, UINT32 source_buffer_used)
    {
    //Back written data must not advance past the current tell / file_buffer_used
    if(source_buffer_used == 0)
        return;

    if(fh == -1 || file_buffer == NULL)
        {
        printer("FileWriter::file_write: Error - Unable to write. File buffer or File Handle is invalid.\n");
        return;
        }
    else if(source_buffer == NULL)
        {
        printer("FileWriter::file_write: Error - Unable to write. Source buffer is NULL.\n");
        return;
        }
    SINT32 curPos = _tell(fh);

    if(position < (UINT32)curPos)
        {
        //It has already been written to disk.
        _lseek(fh, position, SEEK_SET);
        _write(fh, source_buffer, source_buffer_used);
        _lseek(fh, curPos, SEEK_SET);
        }
    else if(position < (file_buffer_used + curPos))
        {
        //Address is still in buffer
        memcpy(file_buffer + (position - curPos), source_buffer, source_buffer_used);
        }
    else
        {
        printer("FileWriter::file_write: Error - Unable to write at offset. Provided offset is greater than the current position.\n");
        return;
        }
    return;
    }

FormIDHandlerClass::FormIDHandlerClass(std::vector<STRING> &_MAST, UINT32 &_NextObject):
    MAST(_MAST),
    nextObject(_NextObject),
    ExpandedIndex(0),
    CollapsedIndex(0),
    IsEmpty(true),
    bMastersChanged(false),
    FileStart(0),
    FileEnd(0),
    EmptyGRUPs(0)
    {
    //
    }

FormIDHandlerClass::~FormIDHandlerClass()
    {
    //
    }

void FormIDHandlerClass::SetLoadOrder(std::vector<STRING> &cLoadOrder)
    {
    if(cLoadOrder.size() > 0xFF)
        {
        printer("FormIDHandler: Error - Unable to set load order. Tried to set load order > 0xFF. Load order size = %i.\n", cLoadOrder.size());
        throw 1;
        return;
        }
    LoadOrder255 = cLoadOrder;
    return;
    }

UINT32 FormIDHandlerClass::NextExpandedFormID()
    {
    //0x00FFFFFF is the highest formID that can be used.
    if(++nextObject >= 0x01000000)
        nextObject = END_HARDCODED_IDS + 1;
    //printer("Assigning new: %08X\n", (ExpandedIndex << 24) | (nextObject + 1));
    return (ExpandedIndex << 24) | nextObject;
    }

void FormIDHandlerClass::UpdateFormIDLookup()
    {
    //Each ModFile maintains a formID resolution lookup table of valid modIndexs
    //both when expanded into a load order corrected format
    //and for when collapsed back into a writable format
    //This function populates that table, and allows much, much faster formID resolution
    //which occurs on every formID that is read, set, and written...

    //The Collapsed lookup table has to be updated anytime the mod's masters change.
    //It also sorts the masters based on the load order
    UINT32 numMods = (UINT32)LoadOrder255.size();
    STRING curMaster = NULL;
    CollapsedIndex = (UINT8)MAST.size();
    //By default, every in memory modIndex maps to the on disk modIndex of the mod
    for(UINT16 p = 0; p <= 0xFF; ++p)
        CollapseTable[(UINT8)p] = CollapsedIndex;

    //Go ahead and sort the masters now since it can't otherwise be done without
    // screwing up the CollapseTable
    std::vector<STRING> sortedMAST;
    sortedMAST.reserve(CollapsedIndex);
    for(UINT32 x = 0; x < LoadOrder255.size(); ++x)
        {
        curMaster = LoadOrder255[(UINT8)x];
        for(UINT16 y = 0; y < CollapsedIndex; ++y)
            {
            if(icmps(curMaster, MAST[(UINT8)y]) == 0)
                {
                sortedMAST.push_back(MAST[(UINT8)y]);
                break;
                }
            }
        }
    //MAST = sortedMAST;
    MAST.clear();
    MAST.resize(sortedMAST.size());
    //printer("Base collapse table: %02X\n", CollapsedIndex);
    //printer("Updating collapse table\n");
    //Replace the masters with the sorted masters, and then map the in memory modIndex
    // to the on disk modIndex
    //The CollapseTable is essentially the same for every mod, except for the defaulted
    // fields.
    for(UINT16 p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[(UINT8)p] = sortedMAST[(UINT8)p];
        //printer("master %s\n", curMaster);
        for(UINT32 y = 0; y < numMods; ++y)
            if(icmps(LoadOrder255[(UINT8)y], curMaster) == 0)
                {
                CollapseTable[(UINT8)y] = (UINT8)p;
                //printer("%02X == %02X\n", (UINT8)y, (UINT8)p);
                break;
                }
        }
    //printer("Collapse table updated.\n");
    //printer("Existing expand table: %02X\n", ExpandedIndex);
    //for(UINT32 y = 0; y <= 0xFF; ++y)
    //    printer("%02X == %02X\n", (UINT8)y, ExpandTable[(UINT8)y]);
    //printer("End expand table.\n");
    sortedMAST.clear();
    return;
    }

void FormIDHandlerClass::CreateFormIDLookup(const UINT8 expandedIndex)
    {
    //Each ModFile maintains a formID resolution lookup table of valid modIndexs
    //both when expanded into a load order corrected format
    //and for when collapsed back into a writable format
    //This function populates that table, and allows much, much faster formID resolution
    //which occurs on every formID that is read, set, and written...

    //The Expanded lookup table is only created once when the mod is first loaded.
    //This allows records to be read even after a master has been added, and have the formID
    //be set to the proper load order corrected value.
    //This can only be done because the load order is finalized once the mods are loaded.

    UINT32 numMods = (UINT32)LoadOrder255.size();
    STRING curMaster = NULL;

    CollapsedIndex = (UINT8)MAST.size();
    ExpandedIndex = expandedIndex;

    //By default, every in memory modIndex maps to the on disk modIndex of the mod
    //By default, every on disk modIndex maps to the in memory modIndex of the mod
    for(UINT16 p = 0; p <= 0xFF; ++p)
        {
        CollapseTable[(UINT8)p] = CollapsedIndex;
        ExpandTable[(UINT8)p] = ExpandedIndex;
        }

    //Map every on disk modIndex to its in memory modIndex and vice versa
    for(UINT16 p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[(UINT8)p];
        for(UINT32 y = 0; y < numMods; ++y)
            if(icmps(LoadOrder255[(UINT8)y], curMaster) == 0)
                {
                ExpandTable[(UINT8)p] = (UINT8)y;
                CollapseTable[(UINT8)y] = (UINT8)p;
                break;
                }
        }
    return;
    }

void FormIDHandlerClass::AddMaster(STRING const curMaster)
    {
    UINT32 size = (UINT32)strlen(curMaster) + 1;
    MAST.push_back(new char[size]);
    memcpy(MAST.back(), curMaster, size);

    bMastersChanged = true;
    //Update the formID resolution lookup table
    UpdateFormIDLookup();
    return;
    }

bool FormIDHandlerClass::MastersChanged()
    {
    return bMastersChanged;
    }

bool FormIDHandlerClass::IsValid(const unsigned char *_SrcBuf)
    {
    return (_SrcBuf >= FileStart && _SrcBuf <= FileEnd);
    }

CreationFlags::CreationFlags():
    SetAsOverride(false),
    CopyWinningParent(false),
    ExistingReturned(false)
    {
    //
    }

CreationFlags::CreationFlags(UINT32 nFlags):
    SetAsOverride((nFlags & fSetAsOverride) != 0),
    CopyWinningParent((nFlags & fCopyWinningParent) != 0),
    ExistingReturned(false)
    {
    //
    }

CreationFlags::~CreationFlags()
    {
    //
    }

UINT32 CreationFlags::GetFlags()
    {
    UINT32 flags = 0;
    if(SetAsOverride)
        flags |= fSetAsOverride;
    if(CopyWinningParent)
        flags |= fCopyWinningParent;
    return flags;
    }

ModFlags::ModFlags():
    IsMinLoad(true),
    IsFullLoad(false),
    IsNoLoad(false),
    IsSkipNewRecords(false),
    IsInLoadOrder(true),
    IsSaveable(true),
    IsAddMasters(true),
    IsLoadMasters(true),
    IsExtendedConflicts(true),
    IsTrackNewTypes(false),
    IsIndexLANDs(false),
    IsFixupPlaceables(false),
    IsCreateNew(false),
    IsIgnoreInactiveMasters(false),
    LoadedGRUPs(false)
    {
    //
    }

ModFlags::ModFlags(UINT32 _Flags):
    IsMinLoad((_Flags & fIsMinLoad) != 0 && (_Flags & fIsFullLoad) == 0),
    IsFullLoad((_Flags & fIsFullLoad) != 0),
    IsNoLoad(!(IsMinLoad || IsFullLoad)),
    IsSkipNewRecords((_Flags & fIsSkipNewRecords) != 0),
    IsSkipAllRecords((_Flags & fIsSkipAllRecords) != 0),
    IsInLoadOrder((_Flags & fIsInLoadOrder) != 0),
    IsSaveable(((_Flags & fIsInLoadOrder) != 0) ? ((_Flags & fIsSaveable) != 0) : false),
    IsAddMasters(((_Flags & fIsIgnoreInactiveMasters) != 0) ? false : ((_Flags & fIsAddMasters) != 0)),
    IsLoadMasters((_Flags & fIsLoadMasters) != 0),
    IsExtendedConflicts((_Flags & fIsExtendedConflicts) != 0),
    IsTrackNewTypes((_Flags & fIsTrackNewTypes) != 0),
    IsIndexLANDs((_Flags & fIsIndexLANDs) != 0),
    IsFixupPlaceables((_Flags & fIsFixupPlaceables) != 0),
    IsCreateNew((_Flags & fIsCreateNew) != 0),
    IsIgnoreInactiveMasters((_Flags & fIsIgnoreInactiveMasters) != 0),
    LoadedGRUPs(false)
    {
    //
    }

ModFlags::~ModFlags()
    {
    //
    }

UINT32 ModFlags::GetFlags()
    {
    UINT32 flags = 0;
    if(IsMinLoad)
        flags |= fIsMinLoad;
    if(IsFullLoad)
        {
        flags |= fIsFullLoad;
        flags &= ~fIsMinLoad;
        }
    if(IsNoLoad)
        {
        flags &= ~fIsFullLoad;
        flags &= ~fIsMinLoad;
        }
    if(IsSkipNewRecords)
        flags |= fIsSkipNewRecords;
    if(IsSkipAllRecords)
        flags |= fIsSkipAllRecords;
    if(IsInLoadOrder)
        flags |= fIsInLoadOrder;
    if(IsSaveable)
        flags |= fIsSaveable;
    if(IsAddMasters)
        flags |= fIsAddMasters;
    if(IsLoadMasters)
        flags |= fIsLoadMasters;
    if(IsExtendedConflicts)
        flags |= fIsExtendedConflicts;
    if(IsTrackNewTypes)
        flags |= fIsTrackNewTypes;
    if(IsIndexLANDs)
        flags |= fIsIndexLANDs;
    if(IsFixupPlaceables)
        flags |= fIsFixupPlaceables;
    if(IsCreateNew)
        flags |= fIsCreateNew;
    if(IsIgnoreInactiveMasters)
        {
        flags &= ~fIsAddMasters;
        flags |= fIsIgnoreInactiveMasters;
        }
    return flags;
    }

SaveFlags::SaveFlags():
    IsCleanMasters(true),
    IsCloseCollection(false)
    {
    //
    }

SaveFlags::SaveFlags(UINT32 _Flags):
    IsCleanMasters((_Flags & fIsCleanMasters) != 0),
    IsCloseCollection((_Flags & fIsCloseCollection) != 0)
    {
    //
    }

SaveFlags::~SaveFlags()
    {
    //
    }

StringRecord::StringRecord():
#ifdef CBASH_X64_COMPATIBILITY
    value(NULL),
    IsOnDisk(false)
#else
    _value(NULL)
#endif
    {
    //
    }

StringRecord::StringRecord(const StringRecord &p):
#ifdef CBASH_X64_COMPATIBILITY
    value(NULL),
    IsOnDisk(false)
#else
    _value(NULL)
#endif
    {
    if(!p.IsLoaded())
        return;

    if(O_IS_ON_DISK(p))
        {
        VAL_NAME = p.VAL_NAME;
        S_SET_ON_DISK(true);
        }
    else
        {
        UINT32 size = p.GetSize();
        VAL_NAME = new char[size];
        memcpy(VAL_NAME, p.VAL_NAME, size);
        }
    }

StringRecord::~StringRecord()
    {
    if(!S_IS_ON_DISK)
        delete []VAL_NAME;
    }

UINT32 StringRecord::GetSize() const
    {
    return VAL_NAME != NULL ? (UINT32)strlen((S_GET_VALUE)) + 1 : 0;
    }

#ifndef CBASH_X64_COMPATIBILITY
    STRING StringRecord::GetString()
        {
        return S_GET_VALUE;
        }
#endif

bool StringRecord::IsLoaded() const
    {
    return VAL_NAME != NULL;
    }

void StringRecord::Load()
    {
    //
    }

void StringRecord::Unload()
    {
    if(!S_IS_ON_DISK)
        {
        delete []VAL_NAME;
        VAL_NAME = NULL;
        }
    }

bool StringRecord::Read(unsigned char *&buffer, const UINT32 &subSize, const bool &CompressedOnDisk)
    {
    if(IsLoaded())
        {
        buffer += subSize;
        return false;
        }
    if(CompressedOnDisk)
        {
        VAL_NAME = new char[subSize];
        memcpy(VAL_NAME, buffer, subSize);
        }
    else
        {
        VAL_NAME = (char *)buffer;
        S_SET_ON_DISK(true);
        }

    buffer += subSize;
    return true;
    }

void StringRecord::Write(UINT32 _Type, FileWriter &writer)
    {
    if((S_GET_VALUE) != NULL)
        writer.record_write_subrecord(_Type, (S_GET_VALUE), (UINT32)strlen((S_GET_VALUE)) + 1);
    }

void StringRecord::ReqWrite(UINT32 _Type, FileWriter &writer)
    {
    if((S_GET_VALUE) != NULL)
        writer.record_write_subrecord(_Type, (S_GET_VALUE), (UINT32)strlen((S_GET_VALUE)) + 1);
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void StringRecord::Copy(STRING FieldValue)
    {
    Unload();
    if(FieldValue != NULL)
        {
        S_SET_ON_DISK(false);
        UINT32 size = (UINT32)strlen(FieldValue) + 1;
        VAL_NAME = new char[size];
        memcpy(VAL_NAME, FieldValue, size);
        }
    }

void StringRecord::TruncateCopy(STRING FieldValue, UINT32 MaxSize)
    {
    Unload();
    if(FieldValue != NULL)
        {
        S_SET_ON_DISK(false);
        UINT32 size = (UINT32)strlen(FieldValue) + 1;
        if(MaxSize > size)
            size = MaxSize;
        VAL_NAME = new char[size];
        memcpy(VAL_NAME, FieldValue, size);
        VAL_NAME[size - 1] = 0x00; //Ensure null termination in case of truncation
        }
    }

bool StringRecord::equals(const StringRecord &other) const
    {
    return cmps((S_GET_VALUE), (O_GET_VALUE(other))) == 0;
    }

bool StringRecord::equalsi(const StringRecord &other) const
    {
    return icmps((S_GET_VALUE), (O_GET_VALUE(other))) == 0;
    }

StringRecord& StringRecord::operator = (const StringRecord &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if(O_IS_ON_DISK(rhs))
            {
            VAL_NAME = rhs.VAL_NAME;
            S_SET_ON_DISK(true);
            }
        else if(rhs.VAL_NAME != NULL)
            {
            S_SET_ON_DISK(false);
            UINT32 size = (UINT32)strlen(rhs.VAL_NAME) + 1;
            VAL_NAME = new char[size];
            memcpy(VAL_NAME, rhs.VAL_NAME, size);
            }
        }
    return *this;
    }

NonNullStringRecord::NonNullStringRecord():
    _value(NULL),
    DiskSize(0)
    {
    //
    }

NonNullStringRecord::NonNullStringRecord(const NonNullStringRecord &p):
    _value(NULL),
    DiskSize(0)
    {
    if(!p.IsLoaded())
        return;

    if(p.DiskSize)
        {
        _value = p._value;
        DiskSize = p.DiskSize;
        }
    else
        {
        UINT32 size = p.GetSize();
        _value = new char[size];
        memcpy(_value, p._value, size);
        }
    }

NonNullStringRecord::~NonNullStringRecord()
    {
    if(DiskSize == 0)
        delete []_value;
    }

UINT32 NonNullStringRecord::GetSize() const
    {
    return _value != NULL ? (DiskSize ? DiskSize : (UINT32)strlen(_value)) : 0;
    }

STRING NonNullStringRecord::GetString()
    {
    if(DiskSize != 0)
        {
        //Have to sanitize the string before letting it be used
        //The string needs a null terminator added, so load it from disk
        STRING nvalue = new char[DiskSize + 1];
        nvalue[DiskSize] = 0x00;
        memcpy(nvalue, _value, DiskSize);
        _value = nvalue;
        DiskSize = 0;
        }
    return _value;
    }

bool NonNullStringRecord::IsLoaded() const
    {
    return _value != NULL;
    }

void NonNullStringRecord::Load()
    {
    //
    }

void NonNullStringRecord::Unload()
    {
    if(DiskSize == 0)
        {
        delete []_value;
        _value = NULL;
        }
    }

bool NonNullStringRecord::Read(unsigned char *&buffer, const UINT32 &subSize, const bool &CompressedOnDisk)
    {
    if(IsLoaded())
        {
        buffer += subSize;
        return false;
        }
    if(CompressedOnDisk)
        {
        _value = new char[subSize + 1];
        _value[subSize] = 0x00;
        memcpy(_value, buffer, subSize);
        }
    else
        {
        DiskSize = subSize;
        _value = (char *)buffer;
        }
    buffer += subSize;
    return true;
    }

void NonNullStringRecord::Write(UINT32 _Type, FileWriter &writer)
    {
    if(_value != NULL)
        writer.record_write_subrecord(_Type, _value, DiskSize ? DiskSize : (UINT32)strlen(_value));
    }

void NonNullStringRecord::Write16(FileWriter &writer) const
    {
    if (_value != NULL)
    {
        UINT16 size = DiskSize ? (UINT16)DiskSize : (UINT16)strlen(_value);
        writer.record_write(&size, sizeof(size));
        writer.record_write(_value, size);
    }
    }

void NonNullStringRecord::ReqWrite(UINT32 _Type, FileWriter &writer)
    {
    if(_value != NULL)
        writer.record_write_subrecord(_Type, _value, DiskSize ? DiskSize : (UINT32)strlen(_value));
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void NonNullStringRecord::Copy(STRING FieldValue)
    {
    Unload();
    if(FieldValue != NULL)
        {
        DiskSize = 0;
        UINT32 size = (UINT32)strlen(FieldValue) + 1;
        _value = new char[size];
        memcpy(_value, FieldValue, size);
        }
    }

bool NonNullStringRecord::equals(const NonNullStringRecord &other) const
    {
    return cmps(_value, other._value) == 0;
    }

bool NonNullStringRecord::equalsi(const NonNullStringRecord &other) const
    {
    return icmps(_value, other._value) == 0;
    }

NonNullStringRecord& NonNullStringRecord::operator = (const NonNullStringRecord &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if(rhs.DiskSize)
            {
            _value = rhs._value;
            DiskSize = rhs.DiskSize;
            }
        else if(rhs._value != NULL)
            {
            DiskSize = 0;
            UINT32 size = (UINT32)strlen(rhs._value) + 1;
            _value = new char[size];
            memcpy(_value, rhs._value, size);
            }
        }
    return *this;
    }

UnorderedPackedStrings::UnorderedPackedStrings()
    {
    //
    }

UnorderedPackedStrings::~UnorderedPackedStrings()
    {
    Unload();
    }

UINT32 UnorderedPackedStrings::GetSize() const
    {
    if(value.size())
        {
        UINT32 cSize = 1; //final null terminator
        for(UINT32 p = 0; p < value.size(); p++)
            if(value[p] != NULL)
                cSize += (UINT32)strlen(value[p]) + 1;
        return cSize == 1 ? 0 : cSize;
        }
    return 0;
    }

bool UnorderedPackedStrings::IsLoaded() const
    {
    return (value.size() != 0);
    }

void UnorderedPackedStrings::Load()
    {
    //
    }

void UnorderedPackedStrings::Unload()
    {
    for(UINT32 x = 0; x < value.size(); ++x)
        delete value[x];
    value.clear();
    }

void UnorderedPackedStrings::resize(UINT32 newSize)
    {
    //Shrink
    UINT32 size = (UINT32)value.size();
    for(; size > newSize;)
        delete value[--size];
    value.resize(newSize);
    //Grow
    for(; size < newSize;)
        value[size++] = NULL;
    }

bool UnorderedPackedStrings::Read(unsigned char *&buffer, const UINT32 &subSize)
    {
    if(value.size() != 0)
        {
        buffer += subSize;
        return false;
        }
    STRING curString = NULL;

    for(unsigned char *end_buffer = buffer + subSize;buffer < (end_buffer - 1);)
        {
        if(((STRING)buffer)[0] == 0x00)
            {
            buffer++;
            continue;
            }
        UINT32 size = (UINT32)strlen((STRING)buffer) + 1;
        curString = new char[size];
        strcpy_s(curString, size, (STRING)buffer);
        value.push_back(curString);
        buffer += size;
        }
    buffer++; //Skip the final null terminator
    return true;
    }

void UnorderedPackedStrings::Write(UINT32 _Type, FileWriter &writer)
    {
    if(value.size())
        {
        writer.record_write_subheader(_Type, GetSize());
        for(UINT32 p = 0; p < value.size(); p++)
            if(value[p] != NULL)
                writer.record_write(value[p], (UINT32)strlen(value[p]) + 1);
        UINT8 cSize = 0x00;
        //write final null terminator
        writer.record_write(&cSize, 1);
        }
    }

void UnorderedPackedStrings::Copy(STRINGARRAY FieldValue, UINT32 ArraySize)
    {
    resize(ArraySize);
    for(UINT32 x = 0; x < ArraySize; x++)
        {
        if(((STRINGARRAY)FieldValue)[x] != NULL)
            {
            UINT32 size = (UINT32)strlen(((STRINGARRAY)FieldValue)[x]) + 1;
            value[x] = new char[size];
            memcpy(value[x], ((STRINGARRAY)FieldValue)[x], size);
            }
        }
    }

UnorderedPackedStrings& UnorderedPackedStrings::operator = (const UnorderedPackedStrings &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if(rhs.value.size() != 0)
            {
            value.resize(rhs.value.size());
            UINT32 size = 0;
            for(UINT32 p = 0; p < rhs.value.size(); p++)
                {
                if(rhs.value[p] != NULL)
                    {
                    size = (UINT32)strlen(rhs.value[p]) + 1;
                    value[p] = new char[size];
                    strcpy_s(value[p], size, rhs.value[p]);
                    }
                }
            }
        }
    return *this;
    }

bool UnorderedPackedStrings::equals(const UnorderedPackedStrings &other) const
    {
    //Hack
    //Equality testing should use a set or somesuch
    if(value.size() == other.value.size())
        {
        for(UINT32 x = 0; x < value.size(); ++x)
            if(cmps(value[x], other.value[x]) != 0)
                return false;
        return true;
        }
    return false;
    }

bool UnorderedPackedStrings::equalsi(const UnorderedPackedStrings &other) const
    {
    //Hack
    //Equality testing should use a set or somesuch
    if(value.size() == other.value.size())
        {
        for(UINT32 x = 0; x < value.size(); ++x)
            if(icmps(value[x], other.value[x]) != 0)
                return false;
        return true;
        }
    return false;
    }

RawRecord::RawRecord():
    size(0),
    value(NULL)
    {
    //
    }

RawRecord::RawRecord(const RawRecord &p):
    value(NULL)
    {
    if(!p.IsLoaded())
        return;
    size = p.size;
    if((fIsOnDisk & p.size) != 0)
        value = p.value;
    else
        {
        value = new unsigned char[size];
        memcpy(value,p.value,size);
        }
    }

RawRecord::~RawRecord()
    {
    if((fIsOnDisk & size) == 0)
        delete []value;
    }

UINT32 RawRecord::GetSize() const
    {
    return size & ~fIsOnDisk;
    }

bool RawRecord::IsLoaded() const
    {
    return value != NULL;
    }

void RawRecord::Load()
    {
    //
    }

void RawRecord::Unload()
    {
    if((fIsOnDisk & size) == 0)
        {
        size = 0;
        delete []value;
        value = NULL;
        }
    }

bool RawRecord::Read(unsigned char *&buffer, const UINT32 &subSize, const bool &CompressedOnDisk)
    {
    if(IsLoaded())
        {
        buffer += subSize;
        return false;
        }
    size = subSize;
    if(CompressedOnDisk)
        {
        value = new unsigned char[size];
        memcpy(value, buffer, size);
        }
    else
        {
        size |= fIsOnDisk;
        value = buffer;
        }
    buffer += subSize;
    return true;
    }

void RawRecord::Write(UINT32 _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, size & ~fIsOnDisk);
    }

void RawRecord::ReqWrite(UINT32 _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, size & ~fIsOnDisk);
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void RawRecord::Copy(unsigned char *FieldValue, UINT32 nSize)
    {
    Unload();
    if(FieldValue != NULL)
        {
        size = nSize;
        value = new unsigned char[size];
        memcpy(value, FieldValue, size);
        }
    }

RawRecord& RawRecord::operator = (const RawRecord &rhs)
    {
    if(this != &rhs)
        {
        Unload();
        if((rhs.size & fIsOnDisk) != 0)
            {
            value = rhs.value;
            size = rhs.size;
            }
        else if(rhs.value != NULL)
            {
            size = rhs.size;
            value = new unsigned char[size];
            memcpy(value, rhs.value, size);
            }
        }
    return *this;
    }

bool RawRecord::operator ==(const RawRecord &other) const
    {
    if(!IsLoaded())
        {
        if(!other.IsLoaded())
            return true;
        }
    else if(other.IsLoaded() && ((size & ~fIsOnDisk) == (other.size & ~fIsOnDisk)) && (memcmp(value, other.value, size & ~fIsOnDisk) == 0))
        return true;
    return false;
    }

bool RawRecord::operator !=(const RawRecord &other) const
    {
    return !(*this == other);
    }

bool ReadChunk(unsigned char *&buffer, const UINT32 &buffer_size, void *dest_buffer, const UINT32 &dest_buffer_size, const bool &skip_load)
    {
    if(skip_load)
        {
        buffer += buffer_size;
        return false;
        }
    #ifdef CBASH_CHUNK_WARN
        if(buffer_size > dest_buffer_size)
            {
            printer("ReadChunk: Warning - Unable to fully parse chunk (%c%c%c%c). "
                   "Size of chunk (%u) is larger than the size of the subrecord (%u) "
                   "and will be truncated.\n",
                   buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                   buffer_size, dest_buffer_size);
            CBASH_CHUNK_DEBUG
            }
        #ifdef CBASH_CHUNK_LCHECK
            else if(buffer_size < dest_buffer_size)
            {
            printer("ReadChunk: Info - Unable to fully parse chunk (%c%c%c%c). Size "
                   "of chunk (%u) is less than the size of the subrecord (%u) and any "
                   "remaining fields have their default value.\n",
                   buffer[-6], buffer[-5], buffer[-4], buffer[-3],
                   buffer_size, dest_buffer_size);
            CBASH_CHUNK_DEBUG
            }
        #endif
    #endif
    memcpy(dest_buffer, buffer, buffer_size > dest_buffer_size ? dest_buffer_size : buffer_size);
    buffer += buffer_size;
    return true;
    }

const UINT32 VATSFunction_Argument[] =
    {
    eFORMID,
    eFORMID,
    eFORMID,
    eFORMID,
    eNONE,
    eUINT32,
    eUINT32,
    eNONE,
    eNONE,
    eFORMID,
    eFORMID,
    eNONE,
    eNONE,
    eNONE,
    eNONE,
    eUINT32,
    eNONE,
    eNONE
    };

Function_ArgumentsType FNVFunction_ArgumentsInit[] =
    {
    Function_ArgumentsType(1,std::make_pair(eFORMID,eNONE)),      //GetDistance
    Function_ArgumentsType(5,std::make_pair(eNONE,eNONE)),        //GetLocked
    Function_ArgumentsType(6,std::make_pair(eUINT32,eNONE)),      //GetPos
    Function_ArgumentsType(8,std::make_pair(eUINT32,eNONE)),      //GetAngle
    Function_ArgumentsType(10,std::make_pair(eUINT32,eNONE)),     //GetStartingPos
    Function_ArgumentsType(11,std::make_pair(eUINT32,eNONE)),     //GetStartingAngle
    Function_ArgumentsType(12,std::make_pair(eNONE,eNONE)),       //GetSecondsPassed
    Function_ArgumentsType(14,std::make_pair(eUINT32,eNONE)),     //GetActorValue
    Function_ArgumentsType(18,std::make_pair(eNONE,eNONE)),       //GetCurrentTime
    Function_ArgumentsType(24,std::make_pair(eNONE,eNONE)),       //GetScale
    Function_ArgumentsType(25,std::make_pair(eNONE,eNONE)),       //IsMoving
    Function_ArgumentsType(26,std::make_pair(eNONE,eNONE)),       //IsTurning
    Function_ArgumentsType(27,std::make_pair(eFORMID,eNONE)),     //GetLineOfSight
    Function_ArgumentsType(32,std::make_pair(eFORMID,eNONE)),     //GetInSameCell
    Function_ArgumentsType(35,std::make_pair(eNONE,eNONE)),       //GetDisabled
    Function_ArgumentsType(36,std::make_pair(eUINT32,eNONE)),     //MenuMode
    Function_ArgumentsType(39,std::make_pair(eNONE,eNONE)),       //GetDisease
    Function_ArgumentsType(40,std::make_pair(eNONE,eNONE)),       //GetVampire
    Function_ArgumentsType(41,std::make_pair(eNONE,eNONE)),       //GetClothingValue
    Function_ArgumentsType(42,std::make_pair(eFORMID,eNONE)),     //SameFaction
    Function_ArgumentsType(43,std::make_pair(eFORMID,eNONE)),     //SameRace
    Function_ArgumentsType(44,std::make_pair(eFORMID,eNONE)),     //SameSex
    Function_ArgumentsType(45,std::make_pair(eFORMID,eNONE)),     //GetDetected
    Function_ArgumentsType(46,std::make_pair(eNONE,eNONE)),       //GetDead
    Function_ArgumentsType(47,std::make_pair(eFORMID,eNONE)),     //GetItemCount
    Function_ArgumentsType(48,std::make_pair(eNONE,eNONE)),       //GetGold
    Function_ArgumentsType(49,std::make_pair(eNONE,eNONE)),       //GetSleeping
    Function_ArgumentsType(50,std::make_pair(eNONE,eNONE)),       //GetTalkedToPC
    Function_ArgumentsType(53,std::make_pair(eFORMID,eUINT32)),   //GetScriptVariable
    Function_ArgumentsType(56,std::make_pair(eFORMID,eNONE)),     //GetQuestRunning
    Function_ArgumentsType(58,std::make_pair(eFORMID,eNONE)),     //GetStage
    Function_ArgumentsType(59,std::make_pair(eFORMID,eUINT32)),   //GetStageDone
    Function_ArgumentsType(60,std::make_pair(eFORMID,eFORMID)),   //GetFactionRankDifference
    Function_ArgumentsType(61,std::make_pair(eNONE,eNONE)),       //GetAlarmed
    Function_ArgumentsType(62,std::make_pair(eNONE,eNONE)),       //IsRaining
    Function_ArgumentsType(63,std::make_pair(eNONE,eNONE)),       //GetAttacked
    Function_ArgumentsType(64,std::make_pair(eNONE,eNONE)),       //GetIsCreature
    Function_ArgumentsType(65,std::make_pair(eNONE,eNONE)),       //GetLockLevel
    Function_ArgumentsType(66,std::make_pair(eFORMID,eNONE)),     //GetShouldAttack
    Function_ArgumentsType(67,std::make_pair(eFORMID,eNONE)),     //GetInCell
    Function_ArgumentsType(68,std::make_pair(eFORMID,eNONE)),     //GetIsClass
    Function_ArgumentsType(69,std::make_pair(eFORMID,eNONE)),     //GetIsRace
    Function_ArgumentsType(70,std::make_pair(eUINT32,eNONE)),     //GetIsSex
    Function_ArgumentsType(71,std::make_pair(eFORMID,eNONE)),     //GetInFaction
    Function_ArgumentsType(72,std::make_pair(eFORMID,eNONE)),     //GetIsID
    Function_ArgumentsType(73,std::make_pair(eFORMID,eNONE)),     //GetFactionRank
    Function_ArgumentsType(74,std::make_pair(eFORMID,eNONE)),     //GetGlobalValue
    Function_ArgumentsType(75,std::make_pair(eNONE,eNONE)),       //IsSnowing
    Function_ArgumentsType(76,std::make_pair(eFORMID,eNONE)),     //GetDisposition
    Function_ArgumentsType(77,std::make_pair(eNONE,eNONE)),       //GetRandomPercent
    Function_ArgumentsType(79,std::make_pair(eFORMID,eUINT32)),   //GetQuestVariable
    Function_ArgumentsType(80,std::make_pair(eNONE,eNONE)),       //GetLevel
    Function_ArgumentsType(81,std::make_pair(eNONE,eNONE)),       //GetArmorRating
    Function_ArgumentsType(84,std::make_pair(eFORMID,eNONE)),     //GetDeadCount
    Function_ArgumentsType(91,std::make_pair(eNONE,eNONE)),       //GetIsAlerted
    Function_ArgumentsType(98,std::make_pair(eUINT32,eUINT32)),   //GetPlayerControlsDisabled
    Function_ArgumentsType(99,std::make_pair(eFORMID,eNONE)),     //GetHeadingAngle
    Function_ArgumentsType(101,std::make_pair(eNONE,eNONE)),      //IsWeaponOut
    Function_ArgumentsType(102,std::make_pair(eNONE,eNONE)),      //IsTorchOut
    Function_ArgumentsType(103,std::make_pair(eNONE,eNONE)),      //IsShieldOut
    Function_ArgumentsType(106,std::make_pair(eNONE,eNONE)),      //IsFacingUp
    Function_ArgumentsType(107,std::make_pair(eNONE,eNONE)),      //GetKnockedState
    Function_ArgumentsType(108,std::make_pair(eNONE,eNONE)),      //GetWeaponAnimType
    Function_ArgumentsType(109,std::make_pair(eUINT32,eNONE)),    //IsWeaponSkillType
    Function_ArgumentsType(110,std::make_pair(eNONE,eNONE)),      //GetCurrentAIPackage
    Function_ArgumentsType(111,std::make_pair(eNONE,eNONE)),      //IsWaiting
    Function_ArgumentsType(112,std::make_pair(eNONE,eNONE)),      //IsIdlePlaying
    Function_ArgumentsType(116,std::make_pair(eNONE,eNONE)),      //GetMinorCrimeCount
    Function_ArgumentsType(117,std::make_pair(eNONE,eNONE)),      //GetMajorCrimeCount
    Function_ArgumentsType(118,std::make_pair(eNONE,eNONE)),      //GetActorAggroRadiusViolated
    Function_ArgumentsType(122,std::make_pair(eFORMID,eUINT32)),  //GetCrime
    Function_ArgumentsType(123,std::make_pair(eNONE,eNONE)),      //IsGreetingPlayer
    Function_ArgumentsType(125,std::make_pair(eNONE,eNONE)),      //IsGuard
    Function_ArgumentsType(127,std::make_pair(eNONE,eNONE)),      //HasBeenEaten
    Function_ArgumentsType(128,std::make_pair(eNONE,eNONE)),      //GetFatiguePercentage
    Function_ArgumentsType(129,std::make_pair(eFORMID,eNONE)),    //GetPCIsClass
    Function_ArgumentsType(130,std::make_pair(eFORMID,eNONE)),    //GetPCIsRace
    Function_ArgumentsType(131,std::make_pair(eUINT32,eNONE)),    //GetPCIsSex
    Function_ArgumentsType(132,std::make_pair(eFORMID,eNONE)),    //GetPCInFaction
    Function_ArgumentsType(133,std::make_pair(eNONE,eNONE)),      //SameFactionAsPC
    Function_ArgumentsType(134,std::make_pair(eNONE,eNONE)),      //SameRaceAsPC
    Function_ArgumentsType(135,std::make_pair(eNONE,eNONE)),      //SameSexAsPC
    Function_ArgumentsType(136,std::make_pair(eFORMID,eNONE)),    //GetIsReference
    Function_ArgumentsType(141,std::make_pair(eNONE,eNONE)),      //IsTalking
    Function_ArgumentsType(142,std::make_pair(eNONE,eNONE)),      //GetWalkSpeed
    Function_ArgumentsType(143,std::make_pair(eNONE,eNONE)),      //GetCurrentAIProcedure
    Function_ArgumentsType(144,std::make_pair(eNONE,eNONE)),      //GetTrespassWarningLevel
    Function_ArgumentsType(145,std::make_pair(eNONE,eNONE)),      //IsTrespassing
    Function_ArgumentsType(146,std::make_pair(eNONE,eNONE)),      //IsInMyOwnedCell
    Function_ArgumentsType(147,std::make_pair(eNONE,eNONE)),      //GetWindSpeed
    Function_ArgumentsType(148,std::make_pair(eNONE,eNONE)),      //GetCurrentWeatherPercent
    Function_ArgumentsType(149,std::make_pair(eFORMID,eNONE)),    //GetIsCurrentWeather
    Function_ArgumentsType(150,std::make_pair(eNONE,eNONE)),      //IsContinuingPackagePCNear
    Function_ArgumentsType(153,std::make_pair(eNONE,eNONE)),      //CanHaveFlames
    Function_ArgumentsType(154,std::make_pair(eNONE,eNONE)),      //HasFlames
    Function_ArgumentsType(157,std::make_pair(eNONE,eNONE)),      //GetOpenState
    Function_ArgumentsType(159,std::make_pair(eNONE,eNONE)),      //GetSitting
    Function_ArgumentsType(160,std::make_pair(eNONE,eNONE)),      //GetFurnitureMarkerID
    Function_ArgumentsType(161,std::make_pair(eFORMID,eNONE)),    //GetIsCurrentPackage
    Function_ArgumentsType(162,std::make_pair(eFORMID,eNONE)),    //IsCurrentFurnitureRef
    Function_ArgumentsType(163,std::make_pair(eFORMID,eNONE)),    //IsCurrentFurnitureObj
    Function_ArgumentsType(170,std::make_pair(eNONE,eNONE)),      //GetDayOfWeek
    Function_ArgumentsType(172,std::make_pair(eFORMID,eNONE)),    //GetTalkedToPCParam
    Function_ArgumentsType(175,std::make_pair(eNONE,eNONE)),      //IsPCSleeping
    Function_ArgumentsType(176,std::make_pair(eNONE,eNONE)),      //IsPCAMurderer
    Function_ArgumentsType(180,std::make_pair(eFORMID,eNONE)),    //GetDetectionLevel
    Function_ArgumentsType(182,std::make_pair(eFORMID,eNONE)),    //GetEquipped
    Function_ArgumentsType(185,std::make_pair(eNONE,eNONE)),      //IsSwimming
    Function_ArgumentsType(190,std::make_pair(eNONE,eNONE)),      //GetAmountSoldStolen
    Function_ArgumentsType(192,std::make_pair(eNONE,eNONE)),      //GetIgnoreCrime
    Function_ArgumentsType(193,std::make_pair(eFORMID,eNONE)),    //GetPCExpelled
    Function_ArgumentsType(195,std::make_pair(eFORMID,eNONE)),    //GetPCFactionMurder
    Function_ArgumentsType(197,std::make_pair(eFORMID,eNONE)),    //GetPCEnemyofFaction
    Function_ArgumentsType(199,std::make_pair(eFORMID,eNONE)),    //GetPCFactionAttack
    Function_ArgumentsType(203,std::make_pair(eNONE,eNONE)),      //GetDestroyed
    Function_ArgumentsType(214,std::make_pair(eFORMID,eNONE)),    //HasMagicEffect
    Function_ArgumentsType(215,std::make_pair(eNONE,eNONE)),      //GetDefaultOpen
    Function_ArgumentsType(219,std::make_pair(eNONE,eNONE)),      //GetAnimAction
    Function_ArgumentsType(223,std::make_pair(eFORMID,eNONE)),    //IsSpellTarget
    Function_ArgumentsType(224,std::make_pair(eNONE,eNONE)),      //GetVATSMode
    Function_ArgumentsType(225,std::make_pair(eNONE,eNONE)),      //GetPersuasionNumber
    Function_ArgumentsType(226,std::make_pair(eNONE,eNONE)),      //GetSandman
    Function_ArgumentsType(227,std::make_pair(eNONE,eNONE)),      //GetCannibal
    Function_ArgumentsType(228,std::make_pair(eFORMID,eNONE)),    //GetIsClassDefault
    Function_ArgumentsType(229,std::make_pair(eNONE,eNONE)),      //GetClassDefaultMatch
    Function_ArgumentsType(230,std::make_pair(eFORMID,eFORMID)),  //GetInCellParam
    Function_ArgumentsType(235,std::make_pair(eNONE,eNONE)),      //GetVatsTargetHeight
    Function_ArgumentsType(237,std::make_pair(eNONE,eNONE)),      //GetIsGhost
    Function_ArgumentsType(242,std::make_pair(eNONE,eNONE)),      //GetUnconscious
    Function_ArgumentsType(244,std::make_pair(eNONE,eNONE)),      //GetRestrained
    Function_ArgumentsType(246,std::make_pair(eFORMID,eNONE)),    //GetIsUsedItem
    Function_ArgumentsType(247,std::make_pair(eUINT32,eNONE)),    //GetIsUsedItemType
    Function_ArgumentsType(254,std::make_pair(eNONE,eNONE)),      //GetIsPlayableRace
    Function_ArgumentsType(255,std::make_pair(eNONE,eNONE)),      //GetOffersServicesNow
    Function_ArgumentsType(258,std::make_pair(eNONE,eNONE)),      //GetUsedItemLevel
    Function_ArgumentsType(259,std::make_pair(eNONE,eNONE)),      //GetUsedItemActivate
    Function_ArgumentsType(264,std::make_pair(eNONE,eNONE)),      //GetBarterGold
    Function_ArgumentsType(265,std::make_pair(eNONE,eNONE)),      //IsTimePassing
    Function_ArgumentsType(266,std::make_pair(eNONE,eNONE)),      //IsPleasant
    Function_ArgumentsType(267,std::make_pair(eNONE,eNONE)),      //IsCloudy
    Function_ArgumentsType(274,std::make_pair(eNONE,eNONE)),      //GetArmorRatingUpperBody
    Function_ArgumentsType(277,std::make_pair(eUINT32,eNONE)),    //GetBaseActorValue
    Function_ArgumentsType(278,std::make_pair(eFORMID,eNONE)),    //IsOwner
    Function_ArgumentsType(280,std::make_pair(eFORMID,eFORMID)),  //IsCellOwner
    Function_ArgumentsType(282,std::make_pair(eNONE,eNONE)),      //IsHorseStolen
    Function_ArgumentsType(285,std::make_pair(eNONE,eNONE)),      //IsLeftUp
    Function_ArgumentsType(286,std::make_pair(eNONE,eNONE)),      //IsSneaking
    Function_ArgumentsType(287,std::make_pair(eNONE,eNONE)),      //IsRunning
    Function_ArgumentsType(288,std::make_pair(eNONE,eNONE)),      //GetFriendHit
    Function_ArgumentsType(289,std::make_pair(eNONE,eNONE)),      //IsInCombat
    Function_ArgumentsType(300,std::make_pair(eNONE,eNONE)),      //IsInInterior
    Function_ArgumentsType(304,std::make_pair(eNONE,eNONE)),      //IsWaterObject
    Function_ArgumentsType(306,std::make_pair(eNONE,eNONE)),      //IsActorUsingATorch
    Function_ArgumentsType(309,std::make_pair(eNONE,eNONE)),      //IsXBox
    Function_ArgumentsType(310,std::make_pair(eFORMID,eNONE)),    //GetInWorldspace
    Function_ArgumentsType(312,std::make_pair(eUINT32,eNONE)),    //GetPCMiscStat
    Function_ArgumentsType(313,std::make_pair(eNONE,eNONE)),      //IsActorEvil
    Function_ArgumentsType(314,std::make_pair(eNONE,eNONE)),      //IsActorAVictim
    Function_ArgumentsType(315,std::make_pair(eNONE,eNONE)),      //GetTotalPersuasionNumber
    Function_ArgumentsType(318,std::make_pair(eNONE,eNONE)),      //GetIdleDoneOnce
    Function_ArgumentsType(320,std::make_pair(eNONE,eNONE)),      //GetNoRumors
    Function_ArgumentsType(323,std::make_pair(eNONE,eNONE)),      //WhichServiceMenu
    Function_ArgumentsType(327,std::make_pair(eNONE,eNONE)),      //IsRidingHorse
    Function_ArgumentsType(332,std::make_pair(eNONE,eNONE)),      //IsInDangerousWater
    Function_ArgumentsType(338,std::make_pair(eNONE,eNONE)),      //GetIgnoreFriendlyHits
    Function_ArgumentsType(339,std::make_pair(eNONE,eNONE)),      //IsPlayersLastRiddenHorse
    Function_ArgumentsType(353,std::make_pair(eNONE,eNONE)),      //IsActor
    Function_ArgumentsType(354,std::make_pair(eNONE,eNONE)),      //IsEssential
    Function_ArgumentsType(358,std::make_pair(eNONE,eNONE)),      //IsPlayerMovingIntoNewSpace
    Function_ArgumentsType(361,std::make_pair(eNONE,eNONE)),      //GetTimeDead
    Function_ArgumentsType(362,std::make_pair(eNONE,eNONE)),      //GetPlayerHasLastRiddenHorse
    Function_ArgumentsType(365,std::make_pair(eNONE,eNONE)),      //IsChild
    Function_ArgumentsType(367,std::make_pair(eNONE,eNONE)),      //GetLastPlayerAction
    Function_ArgumentsType(368,std::make_pair(eUINT32,eNONE)),    //IsPlayerActionActive
    Function_ArgumentsType(370,std::make_pair(eFORMID,eNONE)),    //IsTalkingActivatorActor
    Function_ArgumentsType(372,std::make_pair(eFORMID,eNONE)),    //IsInList
    Function_ArgumentsType(382,std::make_pair(eFORMID,eNONE)),    //GetHasNote
    Function_ArgumentsType(391,std::make_pair(eNONE,eNONE)),      //GetHitLocation
    Function_ArgumentsType(392,std::make_pair(eNONE,eNONE)),      //IsPC1stPerson
    Function_ArgumentsType(397,std::make_pair(eNONE,eNONE)),      //GetCauseofDeath
    Function_ArgumentsType(398,std::make_pair(eUINT32,eNONE)),    //IsLimbGone
    Function_ArgumentsType(399,std::make_pair(eFORMID,eNONE)),    //IsWeaponInList
    Function_ArgumentsType(403,std::make_pair(eNONE,eNONE)),      //HasFriendDisposition
    Function_ArgumentsType(408,std::make_pair(eUINT32,eVATSPARAM)),//GetVATSValue
    Function_ArgumentsType(409,std::make_pair(eFORMID,eNONE)),    //IsKiller
    Function_ArgumentsType(410,std::make_pair(eFORMID,eNONE)),    //IsKillerObject
    Function_ArgumentsType(411,std::make_pair(eFORMID,eFORMID)),  //GetFactionCombatReaction
    Function_ArgumentsType(415,std::make_pair(eFORMID,eNONE)),    //Exists
    Function_ArgumentsType(416,std::make_pair(eNONE,eNONE)),      //GetGroupMemberCount
    Function_ArgumentsType(417,std::make_pair(eNONE,eNONE)),      //GetGroupTargetCount
    Function_ArgumentsType(420,std::make_pair(eFORMID,eFORMID)),  //GetObjectiveCompleted
    Function_ArgumentsType(421,std::make_pair(eFORMID,eFORMID)),  //GetObjectiveDisplayed
    Function_ArgumentsType(427,std::make_pair(eFORMID,eNONE)),    //GetIsVoiceType
    Function_ArgumentsType(428,std::make_pair(eNONE,eNONE)),      //GetPlantedExplosive
    Function_ArgumentsType(430,std::make_pair(eNONE,eNONE)),      //IsActorTalkingThroughActivator
    Function_ArgumentsType(431,std::make_pair(eNONE,eNONE)),      //GetHealthPercentage
    Function_ArgumentsType(433,std::make_pair(eUINT32,eNONE)),    //GetIsObjectType
    Function_ArgumentsType(435,std::make_pair(eNONE,eNONE)),      //GetDialogueEmotion
    Function_ArgumentsType(436,std::make_pair(eNONE,eNONE)),      //GetDialogueEmotionValue
    Function_ArgumentsType(438,std::make_pair(eUINT32,eNONE)),    //GetIsCreatureType
    Function_ArgumentsType(446,std::make_pair(eFORMID,eNONE)),    //GetInZone
    Function_ArgumentsType(449,std::make_pair(eFORMID,eUINT32)),  //HasPerk
    Function_ArgumentsType(450,std::make_pair(eFORMID,eNONE)),    //GetFactionRelation
    Function_ArgumentsType(451,std::make_pair(eFORMID,eNONE)),    //IsLastIdlePlayed
    Function_ArgumentsType(454,std::make_pair(eNONE,eNONE)),      //GetPlayerTeammate
    Function_ArgumentsType(455,std::make_pair(eNONE,eNONE)),      //GetPlayerTeammateCount
    Function_ArgumentsType(459,std::make_pair(eNONE,eNONE)),      //GetActorCrimePlayerEnemy
    Function_ArgumentsType(460,std::make_pair(eNONE,eNONE)),      //GetActorFactionPlayerEnemy
    Function_ArgumentsType(462,std::make_pair(eUINT32,eNONE)),    //IsPlayerTagSkill
    Function_ArgumentsType(464,std::make_pair(eFORMID,eNONE)),    //IsPlayerGrabbedRef
    Function_ArgumentsType(471,std::make_pair(eNONE,eNONE)),      //GetDestructionStage
    Function_ArgumentsType(474,std::make_pair(eUINT32,eNONE)),    //GetIsAlignment
    Function_ArgumentsType(478,std::make_pair(eFORMID,eNONE)),    //GetThreatRatio
    Function_ArgumentsType(480,std::make_pair(eUINT32,eNONE)),    //GetIsUsedItemEquipType
    Function_ArgumentsType(489,std::make_pair(eNONE,eNONE)),      //GetConcussed
    Function_ArgumentsType(492,std::make_pair(eNONE,eNONE)),      //GetMapMarkerVisible
    Function_ArgumentsType(495,std::make_pair(eUINT32,eNONE)),    //GetPermanentActorValue
    Function_ArgumentsType(496,std::make_pair(eNONE,eNONE)),      //GetKillingBlowLimb
    Function_ArgumentsType(500,std::make_pair(eNONE,eNONE)),      //GetWeaponHealthPerc
    Function_ArgumentsType(503,std::make_pair(eNONE,eNONE)),      //GetRadiationLevel
    Function_ArgumentsType(510,std::make_pair(eNONE,eNONE)),      //GetLastHitCritical
    Function_ArgumentsType(515,std::make_pair(eFORMID,eNONE)),    //IsCombatTarget
    Function_ArgumentsType(518,std::make_pair(eFORMID,eNONE)),    //GetVATSRightAreaFree
    Function_ArgumentsType(519,std::make_pair(eFORMID,eNONE)),    //GetVATSLeftAreaFree
    Function_ArgumentsType(520,std::make_pair(eFORMID,eNONE)),    //GetVATSBackAreaFree
    Function_ArgumentsType(521,std::make_pair(eFORMID,eNONE)),    //GetVATSFrontAreaFree
    Function_ArgumentsType(522,std::make_pair(eNONE,eNONE)),      //GetIsLockBroken
    Function_ArgumentsType(523,std::make_pair(eNONE,eNONE)),      //IsPS3
    Function_ArgumentsType(524,std::make_pair(eNONE,eNONE)),      //IsWin32
    Function_ArgumentsType(525,std::make_pair(eFORMID,eNONE)),    //GetVATSRightTargetVisible
    Function_ArgumentsType(526,std::make_pair(eFORMID,eNONE)),    //GetVATSLeftTargetVisible
    Function_ArgumentsType(527,std::make_pair(eFORMID,eNONE)),    //GetVATSBackTargetVisible
    Function_ArgumentsType(528,std::make_pair(eFORMID,eNONE)),    //GetVATSFrontTargetVisible
    Function_ArgumentsType(531,std::make_pair(eUINT32,eNONE)),    //IsInCriticalStage
    Function_ArgumentsType(533,std::make_pair(eNONE,eNONE)),      //GetXPForNextLevel
    Function_ArgumentsType(546,std::make_pair(eFORMID,eNONE)),    //GetQuestCompleted
    Function_ArgumentsType(550,std::make_pair(eNONE,eNONE)),      //IsGoreDisabled
    Function_ArgumentsType(555,std::make_pair(eFORMID,eNONE)),    //GetSpellUsageNum
    Function_ArgumentsType(557,std::make_pair(eNONE,eNONE)),      //GetActorsInHigh
    Function_ArgumentsType(558,std::make_pair(eNONE,eNONE)),      //HasLoaded3D
    Function_ArgumentsType(573,std::make_pair(eFORMID,eUINT32)),  //GetReputation
    Function_ArgumentsType(574,std::make_pair(eFORMID,eUINT32)),  //GetReputationPct
    Function_ArgumentsType(575,std::make_pair(eFORMID,eUINT32)),  //GetReputationThreshold
    Function_ArgumentsType(586,std::make_pair(eNONE,eNONE)),      //IsHardcore
    Function_ArgumentsType(601,std::make_pair(eNONE,eNONE)),      //GetForceHitReaction
    Function_ArgumentsType(607,std::make_pair(eFORMID,eNONE)),    //ChallengeLocked
    Function_ArgumentsType(610,std::make_pair(eFORMID,eNONE)),    //GetCasinoWinningStage
    Function_ArgumentsType(612,std::make_pair(eFORMID,eNONE)),    //PlayerInRegion
    Function_ArgumentsType(614,std::make_pair(eFORMID,eNONE)),    //GetChallengeCompleted
    Function_ArgumentsType(619,std::make_pair(eNONE,eNONE))       //IsAlwaysHardcore
    };

Function_ArgumentsType Function_ArgumentsInit[] =
    {
    Function_ArgumentsType(1,std::make_pair(eFORMID,eNONE)),     //GetDistance
    Function_ArgumentsType(5,std::make_pair(eNONE,eNONE)),       //GetLocked
    Function_ArgumentsType(6,std::make_pair(eUINT32,eNONE)),     //GetPos
    Function_ArgumentsType(8,std::make_pair(eUINT32,eNONE)),     //GetAngle
    Function_ArgumentsType(10,std::make_pair(eUINT32,eNONE)),    //GetStartingPos
    Function_ArgumentsType(11,std::make_pair(eUINT32,eNONE)),    //GetStartingAngle
    Function_ArgumentsType(12,std::make_pair(eNONE,eNONE)),      //GetSecondsPassed
    Function_ArgumentsType(14,std::make_pair(eUINT32,eNONE)),    //GetActorValue
    Function_ArgumentsType(18,std::make_pair(eNONE,eNONE)),      //GetCurrentTime
    Function_ArgumentsType(24,std::make_pair(eNONE,eNONE)),      //GetScale
    Function_ArgumentsType(27,std::make_pair(eFORMID,eNONE)),    //GetLineOfSight
    Function_ArgumentsType(32,std::make_pair(eFORMID,eNONE)),    //GetInSameCell
    Function_ArgumentsType(35,std::make_pair(eNONE,eNONE)),      //GetDisabled
    Function_ArgumentsType(36,std::make_pair(eUINT32,eNONE)),    //MenuMode
    Function_ArgumentsType(39,std::make_pair(eNONE,eNONE)),      //GetDisease
    Function_ArgumentsType(40,std::make_pair(eNONE,eNONE)),      //GetVampire
    Function_ArgumentsType(41,std::make_pair(eNONE,eNONE)),      //GetClothingValue
    Function_ArgumentsType(42,std::make_pair(eFORMID,eNONE)),    //SameFaction
    Function_ArgumentsType(43,std::make_pair(eFORMID,eNONE)),    //SameRace
    Function_ArgumentsType(44,std::make_pair(eFORMID,eNONE)),    //SameSex
    Function_ArgumentsType(45,std::make_pair(eFORMID,eNONE)),    //GetDetected
    Function_ArgumentsType(46,std::make_pair(eNONE,eNONE)),      //GetDead
    Function_ArgumentsType(47,std::make_pair(eFORMID,eNONE)),    //GetItemCount
    Function_ArgumentsType(48,std::make_pair(eNONE,eNONE)),      //GetGold
    Function_ArgumentsType(49,std::make_pair(eNONE,eNONE)),      //GetSleeping
    Function_ArgumentsType(50,std::make_pair(eNONE,eNONE)),      //GetTalkedToPC
    Function_ArgumentsType(53,std::make_pair(eFORMID,eUINT32)),  //GetScriptVariable
    Function_ArgumentsType(56,std::make_pair(eFORMID,eNONE)),    //GetQuestRunning
    Function_ArgumentsType(58,std::make_pair(eFORMID,eNONE)),    //GetStage
    Function_ArgumentsType(59,std::make_pair(eFORMID,eUINT32)),  //GetStageDone
    Function_ArgumentsType(60,std::make_pair(eFORMID,eFORMID)),  //GetFactionRankDifference
    Function_ArgumentsType(61,std::make_pair(eNONE,eNONE)),      //GetAlarmed
    Function_ArgumentsType(62,std::make_pair(eNONE,eNONE)),      //IsRaining
    Function_ArgumentsType(63,std::make_pair(eNONE,eNONE)),      //GetAttacked
    Function_ArgumentsType(64,std::make_pair(eNONE,eNONE)),      //GetIsCreature
    Function_ArgumentsType(65,std::make_pair(eNONE,eNONE)),      //GetLockLevel
    Function_ArgumentsType(66,std::make_pair(eFORMID,eNONE)),    //GetShouldAttack
    Function_ArgumentsType(67,std::make_pair(eFORMID,eNONE)),    //GetInCell
    Function_ArgumentsType(68,std::make_pair(eFORMID,eNONE)),    //GetIsClass
    Function_ArgumentsType(69,std::make_pair(eFORMID,eNONE)),    //GetIsRace
    Function_ArgumentsType(70,std::make_pair(eUINT32,eNONE)),    //GetIsSex
    Function_ArgumentsType(71,std::make_pair(eFORMID,eNONE)),    //GetInFaction
    Function_ArgumentsType(72,std::make_pair(eFORMID,eNONE)),    //GetIsID
    Function_ArgumentsType(73,std::make_pair(eFORMID,eNONE)),    //GetFactionRank
    Function_ArgumentsType(74,std::make_pair(eFORMID,eNONE)),    //GetGlobalValue
    Function_ArgumentsType(75,std::make_pair(eNONE,eNONE)),      //IsSnowing
    Function_ArgumentsType(76,std::make_pair(eFORMID,eNONE)),    //GetDisposition
    Function_ArgumentsType(77,std::make_pair(eNONE,eNONE)),      //GetRandomPercent
    Function_ArgumentsType(79,std::make_pair(eFORMID,eUINT32)),  //GetQuestVariable
    Function_ArgumentsType(80,std::make_pair(eNONE,eNONE)),      //GetLevel
    Function_ArgumentsType(81,std::make_pair(eNONE,eNONE)),      //GetArmorRating
    Function_ArgumentsType(84,std::make_pair(eFORMID,eNONE)),    //GetDeadCount
    Function_ArgumentsType(91,std::make_pair(eNONE,eNONE)),      //GetIsAlerted
    Function_ArgumentsType(98,std::make_pair(eNONE,eNONE)),      //GetPlayerControlsDisabled
    Function_ArgumentsType(99,std::make_pair(eFORMID,eNONE)),    //GetHeadingAngle
    Function_ArgumentsType(101,std::make_pair(eNONE,eNONE)),     //IsWeaponOut
    Function_ArgumentsType(102,std::make_pair(eNONE,eNONE)),     //IsTorchOut
    Function_ArgumentsType(103,std::make_pair(eNONE,eNONE)),     //IsShieldOut
    Function_ArgumentsType(104,std::make_pair(eNONE,eNONE)),     //IsYielding
    Function_ArgumentsType(106,std::make_pair(eNONE,eNONE)),     //IsFacingUp
    Function_ArgumentsType(107,std::make_pair(eNONE,eNONE)),     //GetKnockedState
    Function_ArgumentsType(108,std::make_pair(eNONE,eNONE)),     //GetWeaponAnimType
    Function_ArgumentsType(109,std::make_pair(eNONE,eNONE)),     //GetWeaponSkillType
    Function_ArgumentsType(110,std::make_pair(eNONE,eNONE)),     //GetCurrentAIPackage
    Function_ArgumentsType(111,std::make_pair(eNONE,eNONE)),     //IsWaiting
    Function_ArgumentsType(112,std::make_pair(eNONE,eNONE)),     //IsIdlePlaying
    Function_ArgumentsType(116,std::make_pair(eNONE,eNONE)),     //GetCrimeGold
    Function_ArgumentsType(122,std::make_pair(eFORMID,eUINT32)), //GetCrime
    Function_ArgumentsType(125,std::make_pair(eNONE,eNONE)),     //IsGuard
    Function_ArgumentsType(127,std::make_pair(eNONE,eNONE)),     //CanPayCrimeGold
    Function_ArgumentsType(128,std::make_pair(eNONE,eNONE)),     //GetFatiguePercentage
    Function_ArgumentsType(129,std::make_pair(eFORMID,eNONE)),   //GetPCIsClass
    Function_ArgumentsType(130,std::make_pair(eFORMID,eNONE)),   //GetPCIsRace
    Function_ArgumentsType(131,std::make_pair(eUINT32,eNONE)),   //GetPCIsSex
    Function_ArgumentsType(132,std::make_pair(eFORMID,eNONE)),   //GetPCInFaction
    Function_ArgumentsType(133,std::make_pair(eNONE,eNONE)),     //SameFactionAsPC
    Function_ArgumentsType(134,std::make_pair(eNONE,eNONE)),     //SameRaceAsPC
    Function_ArgumentsType(135,std::make_pair(eNONE,eNONE)),     //SameSexAsPC
    Function_ArgumentsType(136,std::make_pair(eFORMID,eNONE)),   //GetIsReference
    Function_ArgumentsType(141,std::make_pair(eNONE,eNONE)),     //IsTalking
    Function_ArgumentsType(142,std::make_pair(eNONE,eNONE)),     //GetWalkSpeed
    Function_ArgumentsType(143,std::make_pair(eNONE,eNONE)),     //GetCurrentAIProcedure
    Function_ArgumentsType(144,std::make_pair(eNONE,eNONE)),     //GetTrespassWarningLevel
    Function_ArgumentsType(145,std::make_pair(eNONE,eNONE)),     //IsTrespassing
    Function_ArgumentsType(146,std::make_pair(eNONE,eNONE)),     //IsInMyOwnedCell
    Function_ArgumentsType(147,std::make_pair(eNONE,eNONE)),     //GetWindSpeed
    Function_ArgumentsType(148,std::make_pair(eNONE,eNONE)),     //GetCurrentWeatherPercent
    Function_ArgumentsType(149,std::make_pair(eFORMID,eNONE)),   //GetIsCurrentWeather
    Function_ArgumentsType(150,std::make_pair(eNONE,eNONE)),     //IsContinuingPackagePCNear
    Function_ArgumentsType(153,std::make_pair(eNONE,eNONE)),     //CanHaveFlames
    Function_ArgumentsType(154,std::make_pair(eNONE,eNONE)),     //HasFlames
    Function_ArgumentsType(157,std::make_pair(eNONE,eNONE)),     //GetOpenState
    Function_ArgumentsType(159,std::make_pair(eNONE,eNONE)),     //GetSitting
    Function_ArgumentsType(160,std::make_pair(eNONE,eNONE)),     //GetFurnitureMarkerID
    Function_ArgumentsType(161,std::make_pair(eFORMID,eNONE)),   //GetIsCurrentPackage
    Function_ArgumentsType(162,std::make_pair(eFORMID,eNONE)),   //IsCurrentFurnitureRef
    Function_ArgumentsType(163,std::make_pair(eFORMID,eNONE)),   //IsCurrentFurnitureObj
    Function_ArgumentsType(170,std::make_pair(eNONE,eNONE)),     //GetDayOfWeek
    Function_ArgumentsType(171,std::make_pair(eNONE,eNONE)),     //IsPlayerInJail
    Function_ArgumentsType(172,std::make_pair(eFORMID,eNONE)),   //GetTalkedToPCParam
    Function_ArgumentsType(175,std::make_pair(eNONE,eNONE)),     //IsPCSleeping
    Function_ArgumentsType(176,std::make_pair(eNONE,eNONE)),     //IsPCAMurderer
    Function_ArgumentsType(180,std::make_pair(eFORMID,eNONE)),   //GetDetectionLevel
    Function_ArgumentsType(182,std::make_pair(eFORMID,eNONE)),   //GetEquipped
    Function_ArgumentsType(185,std::make_pair(eNONE,eNONE)),     //IsSwimming
    Function_ArgumentsType(190,std::make_pair(eNONE,eNONE)),     //GetAmountSoldStolen
    Function_ArgumentsType(193,std::make_pair(eFORMID,eNONE)),   //GetPCExpelled
    Function_ArgumentsType(195,std::make_pair(eFORMID,eNONE)),   //GetPCFactionMurder
    Function_ArgumentsType(197,std::make_pair(eFORMID,eNONE)),   //GetPCFactionSteal
    Function_ArgumentsType(199,std::make_pair(eFORMID,eNONE)),   //GetPCFactionAttack
    Function_ArgumentsType(201,std::make_pair(eFORMID,eNONE)),   //GetPCFactionSubmitAuthority
    Function_ArgumentsType(203,std::make_pair(eNONE,eNONE)),     //GetDestroyed
    Function_ArgumentsType(214,std::make_pair(eFORMID,eNONE)),   //HasMagicEffect
    Function_ArgumentsType(215,std::make_pair(eNONE,eNONE)),     //GetDoorDefaultOpen
    Function_ArgumentsType(223,std::make_pair(eFORMID,eNONE)),   //IsSpellTarget
    Function_ArgumentsType(224,std::make_pair(eFORMID,eNONE)),   //GetIsPlayerBirthsign
    Function_ArgumentsType(225,std::make_pair(eNONE,eNONE)),     //GetPersuasionNumber
    Function_ArgumentsType(227,std::make_pair(eNONE,eNONE)),     //HasVampireFed
    Function_ArgumentsType(228,std::make_pair(eFORMID,eNONE)),   //GetIsClassDefault
    Function_ArgumentsType(229,std::make_pair(eNONE,eNONE)),     //GetClassDefaultMatch
    Function_ArgumentsType(230,std::make_pair(eFORMID,eFORMID)), //GetInCellParam
    Function_ArgumentsType(237,std::make_pair(eNONE,eNONE)),     //GetIsGhost
    Function_ArgumentsType(242,std::make_pair(eNONE,eNONE)),     //GetUnconscious
    Function_ArgumentsType(244,std::make_pair(eNONE,eNONE)),     //GetRestrained
    Function_ArgumentsType(246,std::make_pair(eFORMID,eNONE)),   //GetIsUsedItem
    Function_ArgumentsType(247,std::make_pair(eUINT32,eNONE)),   //GetIsUsedItemType
    Function_ArgumentsType(249,std::make_pair(eNONE,eNONE)),     //GetPCFame
    Function_ArgumentsType(251,std::make_pair(eNONE,eNONE)),     //GetPCInfamy
    Function_ArgumentsType(254,std::make_pair(eNONE,eNONE)),     //GetIsPlayableRace
    Function_ArgumentsType(255,std::make_pair(eNONE,eNONE)),     //GetOffersServicesNow
    Function_ArgumentsType(258,std::make_pair(eNONE,eNONE)),     //GetUsedItemLevel
    Function_ArgumentsType(259,std::make_pair(eNONE,eNONE)),     //GetUsedItemActivate
    Function_ArgumentsType(264,std::make_pair(eNONE,eNONE)),     //GetBarterGold
    Function_ArgumentsType(265,std::make_pair(eNONE,eNONE)),     //IsTimePassing
    Function_ArgumentsType(266,std::make_pair(eNONE,eNONE)),     //IsPleasant
    Function_ArgumentsType(267,std::make_pair(eNONE,eNONE)),     //IsCloudy
    Function_ArgumentsType(274,std::make_pair(eNONE,eNONE)),     //GetArmorRatingUpperBody
    Function_ArgumentsType(277,std::make_pair(eUINT32,eNONE)),   //GetBaseActorValue
    Function_ArgumentsType(278,std::make_pair(eFORMID,eNONE)),   //IsOwner
    Function_ArgumentsType(280,std::make_pair(eFORMID,eFORMID)), //IsCellOwner
    Function_ArgumentsType(282,std::make_pair(eNONE,eNONE)),     //IsHorseStolen
    Function_ArgumentsType(285,std::make_pair(eNONE,eNONE)),     //IsLeftUp
    Function_ArgumentsType(286,std::make_pair(eNONE,eNONE)),     //IsSneaking
    Function_ArgumentsType(287,std::make_pair(eNONE,eNONE)),     //IsRunning
    Function_ArgumentsType(288,std::make_pair(eFORMID,eNONE)),   //GetFriendHit
    Function_ArgumentsType(289,std::make_pair(eNONE,eNONE)),     //IsInCombat
    Function_ArgumentsType(300,std::make_pair(eNONE,eNONE)),     //IsInInterior
    Function_ArgumentsType(305,std::make_pair(eNONE,eNONE)),     //GetInvestmentGold
    Function_ArgumentsType(306,std::make_pair(eNONE,eNONE)),     //IsActorUsingATorch
    Function_ArgumentsType(309,std::make_pair(eNONE,eNONE)),     //IsXBox
    Function_ArgumentsType(310,std::make_pair(eFORMID,eNONE)),   //GetInWorldspace
    Function_ArgumentsType(312,std::make_pair(eUINT32,eNONE)),   //GetPCMiscStat
    Function_ArgumentsType(313,std::make_pair(eNONE,eNONE)),     //IsActorEvil
    Function_ArgumentsType(314,std::make_pair(eNONE,eNONE)),     //IsActorAVictim
    Function_ArgumentsType(315,std::make_pair(eNONE,eNONE)),     //GetTotalPersuasionNumber
    Function_ArgumentsType(318,std::make_pair(eNONE,eNONE)),     //GetIdleDoneOnce
    Function_ArgumentsType(320,std::make_pair(eNONE,eNONE)),     //GetNoRumors
    Function_ArgumentsType(323,std::make_pair(eNONE,eNONE)),     //WhichServiceMenu
    Function_ArgumentsType(327,std::make_pair(eNONE,eNONE)),     //IsRidingHorse
    Function_ArgumentsType(329,std::make_pair(eNONE,eNONE)),     //IsTurnArrest
    Function_ArgumentsType(332,std::make_pair(eNONE,eNONE)),     //IsInDangerousWater
    Function_ArgumentsType(338,std::make_pair(eNONE,eNONE)),     //GetIgnoreFriendlyHits
    Function_ArgumentsType(339,std::make_pair(eNONE,eNONE)),     //IsPlayersLastRiddenHorse
    Function_ArgumentsType(353,std::make_pair(eNONE,eNONE)),     //IsActor
    Function_ArgumentsType(354,std::make_pair(eNONE,eNONE)),     //IsEssential
    Function_ArgumentsType(358,std::make_pair(eNONE,eNONE)),     //IsPlayerMovingIntoNewSpace
    Function_ArgumentsType(361,std::make_pair(eNONE,eNONE)),     //GetTimeDead
    Function_ArgumentsType(362,std::make_pair(eNONE,eNONE)),     //GetPlayerHasLastRiddenHorse
    Function_ArgumentsType(365,std::make_pair(eNONE,eNONE))      //GetPlayerInSEWorld
    };

Function_NameType Function_NameInit[] =
    {
    Function_NameType(153,(STRING)"CanHaveFlames"),
    Function_NameType(127,(STRING)"CanPayCrimeGold"),
    Function_NameType(14,(STRING)"GetActorValue"),
    Function_NameType(61,(STRING)"GetAlarmed"),
    Function_NameType(190,(STRING)"GetAmountSoldStolen"),
    Function_NameType(8,(STRING)"GetAngle"),
    Function_NameType(81,(STRING)"GetArmorRating"),
    Function_NameType(274,(STRING)"GetArmorRatingUpperBody"),
    Function_NameType(63,(STRING)"GetAttacked"),
    Function_NameType(264,(STRING)"GetBarterGold"),
    Function_NameType(277,(STRING)"GetBaseActorValue"),
    Function_NameType(229,(STRING)"GetClassDefaultMatch"),
    Function_NameType(41,(STRING)"GetClothingValue"),
    Function_NameType(122,(STRING)"GetCrime"),
    Function_NameType(116,(STRING)"GetCrimeGold"),
    Function_NameType(110,(STRING)"GetCurrentAIPackage"),
    Function_NameType(143,(STRING)"GetCurrentAIProcedure"),
    Function_NameType(18,(STRING)"GetCurrentTime"),
    Function_NameType(148,(STRING)"GetCurrentWeatherPercent"),
    Function_NameType(170,(STRING)"GetDayOfWeek"),
    Function_NameType(46,(STRING)"GetDead"),
    Function_NameType(84,(STRING)"GetDeadCount"),
    Function_NameType(203,(STRING)"GetDestroyed"),
    Function_NameType(45,(STRING)"GetDetected"),
    Function_NameType(180,(STRING)"GetDetectionLevel"),
    Function_NameType(35,(STRING)"GetDisabled"),
    Function_NameType(39,(STRING)"GetDisease"),
    Function_NameType(76,(STRING)"GetDisposition"),
    Function_NameType(1,(STRING)"GetDistance"),
    Function_NameType(215,(STRING)"GetDoorDefaultOpen"),
    Function_NameType(182,(STRING)"GetEquipped"),
    Function_NameType(73,(STRING)"GetFactionRank"),
    Function_NameType(60,(STRING)"GetFactionRankDifference"),
    Function_NameType(128,(STRING)"GetFatiguePercentage"),
    Function_NameType(288,(STRING)"GetFriendHit"),
    Function_NameType(160,(STRING)"GetFurnitureMarkerID"),
    Function_NameType(74,(STRING)"GetGlobalValue"),
    Function_NameType(48,(STRING)"GetGold"),
    Function_NameType(99,(STRING)"GetHeadingAngle"),
    Function_NameType(318,(STRING)"GetIdleDoneOnce"),
    Function_NameType(338,(STRING)"GetIgnoreFriendlyHits"),
    Function_NameType(67,(STRING)"GetInCell"),
    Function_NameType(230,(STRING)"GetInCellParam"),
    Function_NameType(71,(STRING)"GetInFaction"),
    Function_NameType(32,(STRING)"GetInSameCell"),
    Function_NameType(305,(STRING)"GetInvestmentGold"),
    Function_NameType(310,(STRING)"GetInWorldspace"),
    Function_NameType(91,(STRING)"GetIsAlerted"),
    Function_NameType(68,(STRING)"GetIsClass"),
    Function_NameType(228,(STRING)"GetIsClassDefault"),
    Function_NameType(64,(STRING)"GetIsCreature"),
    Function_NameType(161,(STRING)"GetIsCurrentPackage"),
    Function_NameType(149,(STRING)"GetIsCurrentWeather"),
    Function_NameType(237,(STRING)"GetIsGhost"),
    Function_NameType(72,(STRING)"GetIsID"),
    Function_NameType(254,(STRING)"GetIsPlayableRace"),
    Function_NameType(224,(STRING)"GetIsPlayerBirthsign"),
    Function_NameType(69,(STRING)"GetIsRace"),
    Function_NameType(136,(STRING)"GetIsReference"),
    Function_NameType(70,(STRING)"GetIsSex"),
    Function_NameType(246,(STRING)"GetIsUsedItem"),
    Function_NameType(247,(STRING)"GetIsUsedItemType"),
    Function_NameType(47,(STRING)"GetItemCount"),
    Function_NameType(107,(STRING)"GetKnockedState"),
    Function_NameType(80,(STRING)"GetLevel"),
    Function_NameType(27,(STRING)"GetLineOfSight"),
    Function_NameType(5,(STRING)"GetLocked"),
    Function_NameType(65,(STRING)"GetLockLevel"),
    Function_NameType(320,(STRING)"GetNoRumors"),
    Function_NameType(255,(STRING)"GetOffersServicesNow"),
    Function_NameType(157,(STRING)"GetOpenState"),
    Function_NameType(193,(STRING)"GetPCExpelled"),
    Function_NameType(199,(STRING)"GetPCFactionAttack"),
    Function_NameType(195,(STRING)"GetPCFactionMurder"),
    Function_NameType(197,(STRING)"GetPCFactionSteal"),
    Function_NameType(201,(STRING)"GetPCFactionSubmitAuthority"),
    Function_NameType(249,(STRING)"GetPCFame"),
    Function_NameType(132,(STRING)"GetPCInFaction"),
    Function_NameType(251,(STRING)"GetPCInfamy"),
    Function_NameType(129,(STRING)"GetPCIsClass"),
    Function_NameType(130,(STRING)"GetPCIsRace"),
    Function_NameType(131,(STRING)"GetPCIsSex"),
    Function_NameType(312,(STRING)"GetPCMiscStat"),
    Function_NameType(225,(STRING)"GetPersuasionNumber"),
    Function_NameType(98,(STRING)"GetPlayerControlsDisabled"),
    Function_NameType(365,(STRING)"GetPlayerInSEWorld"),
    Function_NameType(362,(STRING)"GetPlayerHasLastRiddenHorse"),
    Function_NameType(6,(STRING)"GetPos"),
    Function_NameType(56,(STRING)"GetQuestRunning"),
    Function_NameType(79,(STRING)"GetQuestVariable"),
    Function_NameType(77,(STRING)"GetRandomPercent"),
    Function_NameType(244,(STRING)"GetRestrained"),
    Function_NameType(24,(STRING)"GetScale"),
    Function_NameType(53,(STRING)"GetScriptVariable"),
    Function_NameType(12,(STRING)"GetSecondsPassed"),
    Function_NameType(66,(STRING)"GetShouldAttack"),
    Function_NameType(159,(STRING)"GetSitting"),
    Function_NameType(49,(STRING)"GetSleeping"),
    Function_NameType(58,(STRING)"GetStage"),
    Function_NameType(59,(STRING)"GetStageDone"),
    Function_NameType(11,(STRING)"GetStartingAngle"),
    Function_NameType(10,(STRING)"GetStartingPos"),
    Function_NameType(50,(STRING)"GetTalkedToPC"),
    Function_NameType(172,(STRING)"GetTalkedToPCParam"),
    Function_NameType(361,(STRING)"GetTimeDead"),
    Function_NameType(315,(STRING)"GetTotalPersuasionNumber"),
    Function_NameType(144,(STRING)"GetTrespassWarningLevel"),
    Function_NameType(242,(STRING)"GetUnconscious"),
    Function_NameType(259,(STRING)"GetUsedItemActivate"),
    Function_NameType(258,(STRING)"GetUsedItemLevel"),
    Function_NameType(40,(STRING)"GetVampire"),
    Function_NameType(142,(STRING)"GetWalkSpeed"),
    Function_NameType(108,(STRING)"GetWeaponAnimType"),
    Function_NameType(109,(STRING)"GetWeaponSkillType"),
    Function_NameType(147,(STRING)"GetWindSpeed"),
    Function_NameType(154,(STRING)"HasFlames"),
    Function_NameType(214,(STRING)"HasMagicEffect"),
    Function_NameType(227,(STRING)"HasVampireFed"),
    Function_NameType(353,(STRING)"IsActor"),
    Function_NameType(314,(STRING)"IsActorAVictim"),
    Function_NameType(313,(STRING)"IsActorEvil"),
    Function_NameType(306,(STRING)"IsActorUsingATorch"),
    Function_NameType(280,(STRING)"IsCellOwner"),
    Function_NameType(267,(STRING)"IsCloudy"),
    Function_NameType(150,(STRING)"IsContinuingPackagePCNear"),
    Function_NameType(163,(STRING)"IsCurrentFurnitureObj"),
    Function_NameType(162,(STRING)"IsCurrentFurnitureRef"),
    Function_NameType(354,(STRING)"IsEssential"),
    Function_NameType(106,(STRING)"IsFacingUp"),
    Function_NameType(125,(STRING)"IsGuard"),
    Function_NameType(282,(STRING)"IsHorseStolen"),
    Function_NameType(112,(STRING)"IsIdlePlaying"),
    Function_NameType(289,(STRING)"IsInCombat"),
    Function_NameType(332,(STRING)"IsInDangerousWater"),
    Function_NameType(300,(STRING)"IsInInterior"),
    Function_NameType(146,(STRING)"IsInMyOwnedCell"),
    Function_NameType(285,(STRING)"IsLeftUp"),
    Function_NameType(278,(STRING)"IsOwner"),
    Function_NameType(176,(STRING)"IsPCAMurderer"),
    Function_NameType(175,(STRING)"IsPCSleeping"),
    Function_NameType(171,(STRING)"IsPlayerInJail"),
    Function_NameType(358,(STRING)"IsPlayerMovingIntoNewSpace"),
    Function_NameType(339,(STRING)"IsPlayersLastRiddenHorse"),
    Function_NameType(266,(STRING)"IsPleasant"),
    Function_NameType(62,(STRING)"IsRaining"),
    Function_NameType(327,(STRING)"IsRidingHorse"),
    Function_NameType(287,(STRING)"IsRunning"),
    Function_NameType(103,(STRING)"IsShieldOut"),
    Function_NameType(286,(STRING)"IsSneaking"),
    Function_NameType(75,(STRING)"IsSnowing"),
    Function_NameType(223,(STRING)"IsSpellTarget"),
    Function_NameType(185,(STRING)"IsSwimming"),
    Function_NameType(141,(STRING)"IsTalking"),
    Function_NameType(265,(STRING)"IsTimePassing"),
    Function_NameType(102,(STRING)"IsTorchOut"),
    Function_NameType(145,(STRING)"IsTrespassing"),
    Function_NameType(329,(STRING)"IsTurnArrest"),
    Function_NameType(111,(STRING)"IsWaiting"),
    Function_NameType(101,(STRING)"IsWeaponOut"),
    Function_NameType(309,(STRING)"IsXBox"),
    Function_NameType(104,(STRING)"IsYielding"),
    Function_NameType(36,(STRING)"MenuMode"),
    Function_NameType(42,(STRING)"SameFaction"),
    Function_NameType(133,(STRING)"SameFactionAsPC"),
    Function_NameType(43,(STRING)"SameRace"),
    Function_NameType(134,(STRING)"SameRaceAsPC"),
    Function_NameType(44,(STRING)"SameSex"),
    Function_NameType(135,(STRING)"SameSexAsPC"),
    Function_NameType(323,(STRING)"WhichServiceMenu")
    };

Function_NameType Comparison_NameInit[] =
    {
    Function_NameType(0x00,(STRING)"Equal to"),
    Function_NameType(0x01,(STRING)"Equal to / Or"),
    Function_NameType(0x02,(STRING)"Equal to / Run on target"),
    Function_NameType(0x03,(STRING)"Equal to / Or, Run on target"),
    Function_NameType(0x04,(STRING)"Equal to / Use global"),
    Function_NameType(0x05,(STRING)"Equal to / Or, Use global"),
    Function_NameType(0x06,(STRING)"Equal to / Run on target, Use global"),
    Function_NameType(0x07,(STRING)"Equal to / Or, Run on target, Use global"),
    Function_NameType(0x20,(STRING)"Not equal to"),
    Function_NameType(0x21,(STRING)"Not equal to / Or"),
    Function_NameType(0x22,(STRING)"Not equal to / Run on target"),
    Function_NameType(0x23,(STRING)"Not equal to / Or, Run on target"),
    Function_NameType(0x24,(STRING)"Not equal to / Use global"),
    Function_NameType(0x25,(STRING)"Not equal to / Or, Use global"),
    Function_NameType(0x26,(STRING)"Not equal to / Run on target, Use global"),
    Function_NameType(0x27,(STRING)"Not equal to / Or, Run on target, Use global"),
    Function_NameType(0x40,(STRING)"Greater than"),
    Function_NameType(0x41,(STRING)"Greater than / Or"),
    Function_NameType(0x42,(STRING)"Greater than / Run on target"),
    Function_NameType(0x43,(STRING)"Greater than / Or, Run on target"),
    Function_NameType(0x44,(STRING)"Greater than / Use global"),
    Function_NameType(0x45,(STRING)"Greater than / Or, Use global"),
    Function_NameType(0x46,(STRING)"Greater than / Run on target, Use global"),
    Function_NameType(0x47,(STRING)"Greater than / Or, Run on target, Use global"),
    Function_NameType(0x60,(STRING)"Greater than or equal to"),
    Function_NameType(0x61,(STRING)"Greater than or equal to / Or"),
    Function_NameType(0x62,(STRING)"Greater than or equal to / Run on target"),
    Function_NameType(0x63,(STRING)"Greater than or equal to / Or, Run on target"),
    Function_NameType(0x64,(STRING)"Greater than or equal to / Use global"),
    Function_NameType(0x65,(STRING)"Greater than or equal to / Or, Use global"),
    Function_NameType(0x66,(STRING)"Greater than or equal to / Run on target, Use global"),
    Function_NameType(0x67,(STRING)"Greater than or equal to / Or, Run on target, Use global"),
    Function_NameType(0x80,(STRING)"Less than"),
    Function_NameType(0x81,(STRING)"Less than / Or"),
    Function_NameType(0x82,(STRING)"Less than / Run on target"),
    Function_NameType(0x83,(STRING)"Less than / Or, Run on target"),
    Function_NameType(0x84,(STRING)"Less than / Use global"),
    Function_NameType(0x85,(STRING)"Less than / Or, Use global"),
    Function_NameType(0x86,(STRING)"Less than / Run on target, Use global"),
    Function_NameType(0x87,(STRING)"Less than / Or, Run on target, Use global"),
    Function_NameType(0xA0,(STRING)"Less than or equal to"),
    Function_NameType(0xA1,(STRING)"Less than or equal to / Or"),
    Function_NameType(0xA2,(STRING)"Less than or equal to / Run on target"),
    Function_NameType(0xA3,(STRING)"Less than or equal to / Or, Run on target"),
    Function_NameType(0xA4,(STRING)"Less than or equal to / Use global"),
    Function_NameType(0xA5,(STRING)"Less than or equal to / Or, Use global"),
    Function_NameType(0xA6,(STRING)"Less than or equal to / Run on target, Use global"),
    Function_NameType(0xA7,(STRING)"Less than or equal to / Or, Run on target, Use global")
    };

Function_NameType IDLEGroup_NameInit[] =
    {
    Function_NameType(0x80,(STRING)"Lower Body"),
    Function_NameType(0x00,(STRING)"Lower Body, Must return a file"),
    Function_NameType(0x81,(STRING)"Left Arm"),
    Function_NameType(0x01,(STRING)"Left Arm, Must return a file"),
    Function_NameType(0x82,(STRING)"Left Hand"),
    Function_NameType(0x02,(STRING)"Left Hand, Must return a file"),
    Function_NameType(0x83,(STRING)"Right Arm"),
    Function_NameType(0x03,(STRING)"Right Arm, Must return a file"),
    Function_NameType(0x84,(STRING)"Special Idle"),
    Function_NameType(0x04,(STRING)"Special Idle, Must return a file"),
    Function_NameType(0x85,(STRING)"Whole Body"),
    Function_NameType(0x05,(STRING)"Whole Body, Must return a file"),
    Function_NameType(0x86,(STRING)"Upper Body"),
    Function_NameType(0x06,(STRING)"Upper Body, Must return a file"),
    };

Function_NameType PACKAIType_NameInit[] =
    {
    Function_NameType(0,(STRING)"Find"),
    Function_NameType(1,(STRING)"Follow"),
    Function_NameType(2,(STRING)"Escort"),
    Function_NameType(3,(STRING)"Eat"),
    Function_NameType(4,(STRING)"Sleep"),
    Function_NameType(5,(STRING)"Wander"),
    Function_NameType(6,(STRING)"Travel"),
    Function_NameType(7,(STRING)"Accompany"),
    Function_NameType(8,(STRING)"Use item at"),
    Function_NameType(9,(STRING)"Ambush"),
    Function_NameType(10,(STRING)"Flee not combat"),
    Function_NameType(11,(STRING)"Cast magic")
    };

Function_NameType PACKLocType_NameInit[] =
    {
    Function_NameType(0,(STRING)"Near reference"),
    Function_NameType(1,(STRING)"In cell"),
    Function_NameType(2,(STRING)"Near current location"),
    Function_NameType(3,(STRING)"Near editor location"),
    Function_NameType(4,(STRING)"Object ID"),
    Function_NameType(5,(STRING)"Object type")
    };

Function_NameType PACKTargetType_NameInit[] =
    {
    Function_NameType(0,(STRING)"Specific reference"),
    Function_NameType(1,(STRING)"Object ID"),
    Function_NameType(2,(STRING)"Object type")
    };

Function_NameType HardCodedFormID_EditorIDInit[] =
    {
    Function_NameType(0x0001,(STRING)"DoorMarker"),
    Function_NameType(0x0002,(STRING)"TravelMarker"),
    Function_NameType(0x0003,(STRING)"NorthMarker"),
    Function_NameType(0x0004,(STRING)"PrisonMarker"),
    Function_NameType(0x0005,(STRING)"DivineMarker"),
    Function_NameType(0x0006,(STRING)"TempleMarker"),
    Function_NameType(0x0007,(STRING)"Player"),
    Function_NameType(0x000A,(STRING)"Lockpick"),
    Function_NameType(0x000B,(STRING)"SkeletonKey"),
    Function_NameType(0x000C,(STRING)"RepairHammer"),
    Function_NameType(0x000E,(STRING)"LootBag"),
    Function_NameType(0x000F,(STRING)"Gold001"),
    Function_NameType(0x0010,(STRING)"MapMarker"),
    Function_NameType(0x0011,(STRING)"StolenGoods"),
    Function_NameType(0x0012,(STRING)"HorseMarker"),
    Function_NameType(0x0013,(STRING)"CreatureFaction"),
    Function_NameType(0x0014,(STRING)"PlayerRef"),
    Function_NameType(0x0015,(STRING)"JailPants"),
    Function_NameType(0x0016,(STRING)"JailShoes"),
    Function_NameType(0x0017,(STRING)"JailShirt"),
    Function_NameType(0x0018,(STRING)"DefaultWater"),
    Function_NameType(0x0019,(STRING)"VampireRace"),
    Function_NameType(0x001A,(STRING)"eyeReanimate"),
    Function_NameType(0x001E,(STRING)"FlameNode0"),
    Function_NameType(0x001F,(STRING)"FlameNode1"),
    Function_NameType(0x0020,(STRING)"FlameNode2"),
    Function_NameType(0x0021,(STRING)"FlameNode3"),
    Function_NameType(0x0022,(STRING)"FlameNode4"),
    Function_NameType(0x0023,(STRING)"FlameNode5"),
    Function_NameType(0x0024,(STRING)"FlameNode6"),
    Function_NameType(0x0025,(STRING)"FlameNode7"),
    Function_NameType(0x0026,(STRING)"FlameNode8"),
    Function_NameType(0x0027,(STRING)"FlameNode9"),
    Function_NameType(0x0028,(STRING)"FlameNode10"),
    Function_NameType(0x0029,(STRING)"FlameNode11"),
    Function_NameType(0x002A,(STRING)"FlameNode12"),
    Function_NameType(0x002B,(STRING)"FlameNode13"),
    Function_NameType(0x002C,(STRING)"FlameNode14"),
    Function_NameType(0x002D,(STRING)"FlameNode15"),
    Function_NameType(0x002E,(STRING)"FlameNode16"),
    Function_NameType(0x002F,(STRING)"FlameNode17"),
    Function_NameType(0x0030,(STRING)"FlameNode18"),
    Function_NameType(0x0031,(STRING)"FlameNode19"),
    Function_NameType(0x0032,(STRING)"FlameNode20"),
    Function_NameType(0x0034,(STRING)"XMarkerHeading"),
    Function_NameType(0x0035,(STRING)"GameYear"),
    Function_NameType(0x0036,(STRING)"GameMonth"),
    Function_NameType(0x0037,(STRING)"GameDay"),
    Function_NameType(0x0038,(STRING)"GameHour"),
    Function_NameType(0x0039,(STRING)"GameDaysPassed"),
    Function_NameType(0x003A,(STRING)"TimeScale"),
    Function_NameType(0x003B,(STRING)"XMarker"),
    Function_NameType(0x003C,(STRING)"Tamriel"),
    Function_NameType(0x003D,(STRING)"SkillArmorer"),
    Function_NameType(0x003E,(STRING)"SkillAthletics"),
    Function_NameType(0x003F,(STRING)"SkillBlade"),
    Function_NameType(0x0040,(STRING)"SkillBlock"),
    Function_NameType(0x0041,(STRING)"SkillBlunt"),
    Function_NameType(0x0042,(STRING)"SkillHandToHand"),
    Function_NameType(0x0043,(STRING)"SkillHeavyArmor"),
    Function_NameType(0x0044,(STRING)"SkillAlchemy"),
    Function_NameType(0x0045,(STRING)"SkillAlteration"),
    Function_NameType(0x0046,(STRING)"SkillConjuration"),
    Function_NameType(0x0047,(STRING)"SkillDestruction"),
    Function_NameType(0x0048,(STRING)"SkillIllusion"),
    Function_NameType(0x0049,(STRING)"SkillMysticism"),
    Function_NameType(0x004A,(STRING)"SkillRestoration"),
    Function_NameType(0x004B,(STRING)"SkillAcrobatics"),
    Function_NameType(0x004C,(STRING)"SkillLightArmor"),
    Function_NameType(0x004D,(STRING)"SkillMarksman"),
    Function_NameType(0x004E,(STRING)"SkillMercantile"),
    Function_NameType(0x004F,(STRING)"SkillSecurity"),
    Function_NameType(0x0050,(STRING)"SkillSneak"),
    Function_NameType(0x0051,(STRING)"SkillSpeechcraft"),
    Function_NameType(0x0064,(STRING)"FurnitureMarker01"),
    Function_NameType(0x0065,(STRING)"FurnitureMarker02"),
    Function_NameType(0x0066,(STRING)"FurnitureMarker03"),
    Function_NameType(0x0067,(STRING)"FurnitureMarker04"),
    Function_NameType(0x0068,(STRING)"FurnitureMarker05"),
    Function_NameType(0x0069,(STRING)"FurnitureMarker06"),
    Function_NameType(0x006A,(STRING)"FurnitureMarker07"),
    Function_NameType(0x006B,(STRING)"FurnitureMarker08"),
    Function_NameType(0x006C,(STRING)"FurnitureMarker09"),
    Function_NameType(0x006D,(STRING)"FurnitureMarker10"),
    Function_NameType(0x006E,(STRING)"FurnitureMarker11"),
    Function_NameType(0x006F,(STRING)"FurnitureMarker12"),
    Function_NameType(0x0070,(STRING)"FurnitureMarker13"),
    Function_NameType(0x0071,(STRING)"FurnitureMarker14"),
    Function_NameType(0x0072,(STRING)"FurnitureMarker15"),
    Function_NameType(0x0073,(STRING)"FurnitureMarker16"),
    Function_NameType(0x0074,(STRING)"FurnitureMarker17"),
    Function_NameType(0x0075,(STRING)"FurnitureMarker18"),
    Function_NameType(0x0076,(STRING)"FurnitureMarker19"),
    Function_NameType(0x0077,(STRING)"FurnitureMarker20"),
    Function_NameType(0x00AA,(STRING)"ADMIREHATE"),
    Function_NameType(0x00AB,(STRING)"ADMIRELOVE"),
    Function_NameType(0x00AC,(STRING)"ADMIRELIKE"),
    Function_NameType(0x00AD,(STRING)"ADMIREDISLIKE"),
    Function_NameType(0x00AE,(STRING)"COERCEHATE"),
    Function_NameType(0x00AF,(STRING)"COERCELOVE"),
    Function_NameType(0x00B0,(STRING)"COERCELIKE"),
    Function_NameType(0x00B1,(STRING)"COERCEDISLIKE"),
    Function_NameType(0x00B2,(STRING)"BOASTHATE"),
    Function_NameType(0x00B3,(STRING)"BOASTLOVE"),
    Function_NameType(0x00B4,(STRING)"BOASTLIKE"),
    Function_NameType(0x00B5,(STRING)"BOASTDISLIKE"),
    Function_NameType(0x00B6,(STRING)"JOKEHATE"),
    Function_NameType(0x00B7,(STRING)"JOKELOVE"),
    Function_NameType(0x00B8,(STRING)"JOKELIKE"),
    Function_NameType(0x00B9,(STRING)"JOKEDISLIKE"),
    Function_NameType(0x00BA,(STRING)"BRIBE"),
    Function_NameType(0x00BB,(STRING)"PERSUASIONENTER"),
    Function_NameType(0x00BC,(STRING)"PERSUASIONEXIT"),
    Function_NameType(0x00C8,(STRING)"GREETING"),
    Function_NameType(0x00D2,(STRING)"HELLO"),
    Function_NameType(0x00D3,(STRING)"ANY"),
    Function_NameType(0x00D4,(STRING)"GOODBYE"),
    Function_NameType(0x00D5,(STRING)"IdleChatter"),
    Function_NameType(0x00D6,(STRING)"SPELLHELP"),
    Function_NameType(0x00D7,(STRING)"INFOGENERAL"),
    Function_NameType(0x00DC,(STRING)"Attack"),
    Function_NameType(0x00DD,(STRING)"Hit"),
    Function_NameType(0x00DE,(STRING)"Flee"),
    Function_NameType(0x00DF,(STRING)"Steal"),
    Function_NameType(0x00E0,(STRING)"Trespass"),
    Function_NameType(0x00E1,(STRING)"Yield"),
    Function_NameType(0x00E2,(STRING)"AcceptYield"),
    Function_NameType(0x00E3,(STRING)"Pickpocket"),
    Function_NameType(0x00E4,(STRING)"Assault"),
    Function_NameType(0x00E5,(STRING)"Murder"),
    Function_NameType(0x00E6,(STRING)"PowerAttack"),
    Function_NameType(0x00E7,(STRING)"AssaultNoCrime"),
    Function_NameType(0x00E8,(STRING)"MurderNoCrime"),
    Function_NameType(0x00E9,(STRING)"PickpocketNoCrime"),
    Function_NameType(0x00EA,(STRING)"StealNoCrime"),
    Function_NameType(0x00EB,(STRING)"TrespassNoCrime"),
    Function_NameType(0x00F0,(STRING)"AdmireSuccess"),
    Function_NameType(0x00F1,(STRING)"AdmireFail"),
    Function_NameType(0x00F2,(STRING)"AdmireNeutral"),
    Function_NameType(0x00F3,(STRING)"TauntSuccess"),
    Function_NameType(0x00F4,(STRING)"TauntFail"),
    Function_NameType(0x00F5,(STRING)"TauntNeutral"),
    Function_NameType(0x00F6,(STRING)"BoastSuccess"),
    Function_NameType(0x00F7,(STRING)"BoastFail"),
    Function_NameType(0x00F8,(STRING)"BoastNeutral"),
    Function_NameType(0x00F9,(STRING)"JokeSuccess"),
    Function_NameType(0x00FA,(STRING)"JokeFail"),
    Function_NameType(0x00FB,(STRING)"JokeNeutral"),
    Function_NameType(0x00FC,(STRING)"BribeSuccess"),
    Function_NameType(0x00FD,(STRING)"BribeFail"),
    Function_NameType(0x00FE,(STRING)"DemandSuccess"),
    Function_NameType(0x00FF,(STRING)"DemandFail"),
    Function_NameType(0x0100,(STRING)"DemandNoMoney"),
    Function_NameType(0x0101,(STRING)"DemandNoMoreCircle"),
    Function_NameType(0x0102,(STRING)"BribeNoMoreCircle"),
    Function_NameType(0x0103,(STRING)"BribeNoMoney"),
    Function_NameType(0x0104,(STRING)"Noticed"),
    Function_NameType(0x0105,(STRING)"Seen"),
    Function_NameType(0x0106,(STRING)"Unseen"),
    Function_NameType(0x0107,(STRING)"Lost"),
    Function_NameType(0x010E,(STRING)"ServiceRefusal"),
    Function_NameType(0x010F,(STRING)"BarterStart"),
    Function_NameType(0x0110,(STRING)"BarterFail"),
    Function_NameType(0x0111,(STRING)"Repair"),
    Function_NameType(0x0112,(STRING)"Travel"),
    Function_NameType(0x0113,(STRING)"Training"),
    Function_NameType(0x0114,(STRING)"BarterBuyItem"),
    Function_NameType(0x0115,(STRING)"BarterSellItem"),
    Function_NameType(0x0116,(STRING)"BarterExit"),
    Function_NameType(0x0117,(STRING)"BarterStolen"),
    Function_NameType(0x0118,(STRING)"InfoRefusal"),
    Function_NameType(0x0119,(STRING)"Idle"),
    Function_NameType(0x011A,(STRING)"ObserveCombat"),
    Function_NameType(0x011B,(STRING)"Corpse"),
    Function_NameType(0x011C,(STRING)"TimeToGo"),
    Function_NameType(0x011D,(STRING)"RepairExit"),
    Function_NameType(0x0120,(STRING)"Recharge"),
    Function_NameType(0x0121,(STRING)"RechargeExit"),
    Function_NameType(0x0124,(STRING)"TrainingExit"),
    Function_NameType(0x012C,(STRING)"MagicFailureSoundAlteration"),
    Function_NameType(0x012D,(STRING)"MagicFailureSoundConjuration"),
    Function_NameType(0x012E,(STRING)"MagicFailureSoundDestruction"),
    Function_NameType(0x012F,(STRING)"MagicFailureSoundIllusion"),
    Function_NameType(0x0130,(STRING)"MagicFailureSoundMysticism"),
    Function_NameType(0x0131,(STRING)"MagicFailureSoundRestoration"),
    Function_NameType(0x0136,(STRING)"DefaultPlayerSpell"),
    Function_NameType(0x0137,(STRING)"DefaultMarksmanParalyzeSpell"),
    Function_NameType(0x0138,(STRING)"MagicEnchantDrawSoundAlteration"),
    Function_NameType(0x0139,(STRING)"MagicEnchantDrawSoundConjuration"),
    Function_NameType(0x013A,(STRING)"MagicEnchantDrawSoundDestruction"),
    Function_NameType(0x013B,(STRING)"MagicEnchantDrawSoundIllusion"),
    Function_NameType(0x013C,(STRING)"MagicEnchantDrawSoundMysticism"),
    Function_NameType(0x013D,(STRING)"MagicEnchantDrawSoundRestoration"),
    Function_NameType(0x013E,(STRING)"MagicEnchantHitSoundAlteration"),
    Function_NameType(0x013F,(STRING)"MagicEnchantHitSoundConjuration"),
    Function_NameType(0x0140,(STRING)"MagicEnchantHitSoundDestruction"),
    Function_NameType(0x0141,(STRING)"MagicEnchantHitSoundIllusion"),
    Function_NameType(0x0142,(STRING)"MagicEnchantHitSoundMysticism"),
    Function_NameType(0x0143,(STRING)"MagicEnchantHitSoundRestoration"),
    Function_NameType(0x0144,(STRING)"effectAbsorb"),
    Function_NameType(0x0145,(STRING)"effectReflect"),
    Function_NameType(0x0146,(STRING)"LifeDetected"),
    Function_NameType(0x015E,(STRING)"DefaultWeather"),
    Function_NameType(0x015F,(STRING)"DefaultClimate"),
    Function_NameType(0x0191,(STRING)"WelkyndStone"),
    Function_NameType(0x0192,(STRING)"BlackSoulGem"),
    Function_NameType(0x0193,(STRING)"AzuraStone"),
    Function_NameType(0x0194,(STRING)"VarlaStone"),
    Function_NameType(0x0212,(STRING)"FootSoundDirt"),
    Function_NameType(0x0213,(STRING)"FootSoundGrass"),
    Function_NameType(0x0214,(STRING)"FootSoundStone"),
    Function_NameType(0x0215,(STRING)"FootSoundWater"),
    Function_NameType(0x0216,(STRING)"FootSoundWood"),
    Function_NameType(0x0217,(STRING)"FootSoundHeavyArmor"),
    Function_NameType(0x0218,(STRING)"FootSoundLightArmor"),
    Function_NameType(0x0219,(STRING)"FootSoundEarthLand"),
    Function_NameType(0x021A,(STRING)"FootSoundGrassLand"),
    Function_NameType(0x021B,(STRING)"FootSoundMetalLand"),
    Function_NameType(0x021C,(STRING)"FootSoundStoneLand"),
    Function_NameType(0x021D,(STRING)"FootSoundWaterLand"),
    Function_NameType(0x021E,(STRING)"FootSoundWoodLand"),
    Function_NameType(0x021F,(STRING)"FSTSnow"),
    Function_NameType(0x0220,(STRING)"FSTSnowLand"),
    Function_NameType(0x0221,(STRING)"FSTEarthSneak"),
    Function_NameType(0x0222,(STRING)"FSTGrassSneak"),
    Function_NameType(0x0223,(STRING)"FSTMetalSneak"),
    Function_NameType(0x0224,(STRING)"FSTSnowSneak"),
    Function_NameType(0x0225,(STRING)"FSTStoneSneak"),
    Function_NameType(0x0226,(STRING)"FSTWaterSneak"),
    Function_NameType(0x0227,(STRING)"FSTWoodSneak"),
    Function_NameType(0x0228,(STRING)"FSTArmorLightSneak"),
    Function_NameType(0x0229,(STRING)"FSTArmorHeavySneak"),
    Function_NameType(0x022B,(STRING)"FSTMetal")
    };

Function_NameType EntryPoint_NameInit[] =
    {
    Function_NameType(0,(STRING)"Calculate Weapon Damage"),
    Function_NameType(1,(STRING)"Calculate My Critical Hit Chance"),
    Function_NameType(2,(STRING)"Calculate My Critical Hit Damage"),
    Function_NameType(3,(STRING)"Calculate Weapon Attack AP Cost"),
    Function_NameType(4,(STRING)"Calculate Mine Explode Chance"),
    Function_NameType(5,(STRING)"Adjust Range Penalty"),
    Function_NameType(6,(STRING)"Adjust Limb Damage"),
    Function_NameType(7,(STRING)"Calculate Weapon Range"),
    Function_NameType(8,(STRING)"Calculate To Hit Chance"),
    Function_NameType(9,(STRING)"Adjust Experience Points"),
    Function_NameType(10,(STRING)"Adjust Gained Skill Points"),
    Function_NameType(11,(STRING)"Adjust Book Skill Points"),
    Function_NameType(12,(STRING)"Modify Recovered Health"),
    Function_NameType(13,(STRING)"Calculate Inventory AP Cost"),
    Function_NameType(14,(STRING)"Get Disposition"),
    Function_NameType(15,(STRING)"Get Should Attack"),
    Function_NameType(16,(STRING)"Get Should Assist"),
    Function_NameType(17,(STRING)"Calculate Buy Price"),
    Function_NameType(18,(STRING)"Get Bad Karma"),
    Function_NameType(19,(STRING)"Get Good Karma"),
    Function_NameType(20,(STRING)"Ignore Locked Terminal"),
    Function_NameType(21,(STRING)"Add Leveled List On Death"),
    Function_NameType(22,(STRING)"Get Max Carry Weight"),
    Function_NameType(23,(STRING)"Modify Addiction Chance"),
    Function_NameType(24,(STRING)"Modify Addiction Duration"),
    Function_NameType(25,(STRING)"Modify Positive Chem Duration"),
    Function_NameType(26,(STRING)"Adjust Drinking Radiation"),
    Function_NameType(27,(STRING)"Activate"),
    Function_NameType(28,(STRING)"Mysterious Stranger"),
    Function_NameType(29,(STRING)"Has Paralyzing Palm"),
    Function_NameType(30,(STRING)"Hacking Science Bonus"),
    Function_NameType(31,(STRING)"Ignore Running During Detection"),
    Function_NameType(32,(STRING)"Ignore Broken Lock"),
    Function_NameType(33,(STRING)"Has Concentrated Fire"),
    Function_NameType(34,(STRING)"Calculate Gun Spread"),
    Function_NameType(35,(STRING)"Player Kill AP Reward"),
    Function_NameType(36,(STRING)"Modify Enemy Critical Hit Chance"),
    Function_NameType(37,(STRING)"Reload Speed"),
    Function_NameType(38,(STRING)"Equip Speed"),
    Function_NameType(39,(STRING)"Action Point Regen"),
    Function_NameType(40,(STRING)"Action Point Cost"),
    Function_NameType(41,(STRING)"Miss Fortune"),
    Function_NameType(42,(STRING)"Modify Run Speed"),
    Function_NameType(43,(STRING)"Modify Attack Speed"),
    Function_NameType(44,(STRING)"Modify Radiation Consumed"),
    Function_NameType(45,(STRING)"Has Pip Hacker"),
    Function_NameType(46,(STRING)"Has Meltdown"),
    Function_NameType(47,(STRING)"See Enemy Health"),
    Function_NameType(48,(STRING)"Has Jury Rigging"),
    Function_NameType(49,(STRING)"Modify Threat Range"),
    Function_NameType(50,(STRING)"Modify Thread"),
    Function_NameType(51,(STRING)"Has Fast Travel Always"),
    Function_NameType(52,(STRING)"Knockdown Chance"),
    Function_NameType(53,(STRING)"Modify Weapon Strength Req"),
    Function_NameType(54,(STRING)"Modify Aiming Move Speed"),
    Function_NameType(55,(STRING)"Modify Light Items"),
    Function_NameType(56,(STRING)"Modify Damage Threshold (defender)"),
    Function_NameType(57,(STRING)"Modify Chance for Ammo Item"),
    Function_NameType(58,(STRING)"Modify Damage Threshold (attacker)"),
    Function_NameType(59,(STRING)"Modify Throwing Velocity"),
    Function_NameType(60,(STRING)"Chance for Item on Fire"),
    Function_NameType(61,(STRING)"Has Unarmed Forward Power Attack"),
    Function_NameType(62,(STRING)"Has Unarmed Back Power Attack"),
    Function_NameType(63,(STRING)"Has Unarmed Crouched Power Attack"),
    Function_NameType(64,(STRING)"Has Unarmed Counter Attack"),
    Function_NameType(65,(STRING)"Has Unarmed Left Power Attack"),
    Function_NameType(66,(STRING)"Has Unarmed Right Power Attack"),
    Function_NameType(67,(STRING)"VATS HelperChance"),
    Function_NameType(68,(STRING)"Modify Item Damage"),
    Function_NameType(69,(STRING)"Has Improved Detection"),
    Function_NameType(70,(STRING)"Has Improved Spotting"),
    Function_NameType(71,(STRING)"Has Improved Item Detection"),
    Function_NameType(72,(STRING)"Adjust Explosion Radius"),
    Function_NameType(73,(STRING)"Reserved")
    };

const std::map<UINT32, FunctionArguments> Function_Arguments(Function_ArgumentsInit, Function_ArgumentsInit + sizeof(Function_ArgumentsInit) / sizeof(Function_ArgumentsInit[0]));

const std::map<UINT32, STRING> Function_Name(Function_NameInit, Function_NameInit + sizeof(Function_NameInit) / sizeof(Function_NameInit[0]));
const std::map<UINT32, STRING> Comparison_Name(Comparison_NameInit, Comparison_NameInit + sizeof(Comparison_NameInit) / sizeof(Comparison_NameInit[0]));
const std::map<UINT32, STRING> IDLEGroup_Name(IDLEGroup_NameInit, IDLEGroup_NameInit + sizeof(IDLEGroup_NameInit) / sizeof(IDLEGroup_NameInit[0]));
const std::map<UINT32, STRING> PACKAIType_Name(PACKAIType_NameInit, PACKAIType_NameInit + sizeof(PACKAIType_NameInit) / sizeof(PACKAIType_NameInit[0]));
const std::map<UINT32, STRING> PACKLocType_Name(PACKLocType_NameInit, PACKLocType_NameInit + sizeof(PACKLocType_NameInit) / sizeof(PACKLocType_NameInit[0]));
const std::map<UINT32, STRING> PACKTargetType_Name(PACKTargetType_NameInit, PACKTargetType_NameInit + sizeof(PACKTargetType_NameInit) / sizeof(PACKTargetType_NameInit[0]));
const std::map<UINT32, STRING> HardCodedFormID_EditorID(HardCodedFormID_EditorIDInit, HardCodedFormID_EditorIDInit + sizeof(HardCodedFormID_EditorIDInit) / sizeof(HardCodedFormID_EditorIDInit[0]));

const std::map<UINT32, STRING> EntryPoint_Name(EntryPoint_NameInit, EntryPoint_NameInit + sizeof(EntryPoint_NameInit) / sizeof(EntryPoint_NameInit[0]));
const std::map<UINT32, FunctionArguments> FNVFunction_Arguments(FNVFunction_ArgumentsInit, FNVFunction_ArgumentsInit + sizeof(FNVFunction_ArgumentsInit) / sizeof(FNVFunction_ArgumentsInit[0]));

const float flt_max = FLT_MAX;
const float flt_min = FLT_MIN;
const float flt_3 = 3.0f;
const float flt_1 = 1.0f;
const float flt_0 = 0.0f;
const float flt_n2147483648 = -2147483648.0f;