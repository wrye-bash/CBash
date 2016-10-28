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
#include "zlib.h"
#include <sys/utime.h>

int (*printer)(const char * _Format, ...) = &printf;
int32_t (*LoggingCallback)(const char *) = NULL;
void (*RaiseCallback)(const char *) = NULL;

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

const char * Ex_NULL::__CLR_OR_THIS_CALL what() const
    {
    return "NULL Pointer";
    }

const char * Ex_INVALIDINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Index";
    }

const char * Ex_INVALIDCOLLECTIONINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Collection Index";
    }

const char * Ex_INVALIDMODINDEX::__CLR_OR_THIS_CALL what() const
    {
    return "Invalid Mod Index";
    }

int icmps(const char * lhs, const char * rhs)
    {
    if(lhs == rhs)
        return 0;
    if(lhs == NULL)
        return -1;
    if(rhs == NULL)
        return 1;
    return _stricmp(lhs, rhs);
    }

int cmps(const char * lhs, const char * rhs)
    {
    if(lhs == rhs)
        return 0;
    if(lhs == NULL)
        return -1;
    if(rhs == NULL)
        return 1;
    return strcmp(lhs, rhs);
    }

bool sameStr::operator()( const char * s1, const char * s2 ) const
    {
    return icmps(s1, s2) < 0;
    }

#ifdef CBASH_DEBUG_CHUNK
    void peek_around(unsigned char *position, uint32_t length)
        {
        for(int32_t x = length; x > 0; x--)
            printf("%02X ", (position)[-x]);
        for(uint32_t x = 0; x < length; x++)
            printf("%02X ", (position)[x]);
        printf("\n\n");
        for(int32_t x = length; x > 0; x--)
            printf("%c", (position)[-x]);
        for(uint32_t x = 0; x < length; x++)
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

char * DeGhostModName(char * const ModName)
    {
    char * NonGhostName = NULL;
    uint32_t NameLength = (uint32_t)strlen(ModName) + 1;
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

bool FileExists(char * const FileName)
    {
    struct stat statBuffer;
    return (stat(FileName, &statBuffer) >= 0 && statBuffer.st_mode & S_IFREG);
    }

char * GetTemporaryFileName(char * FileName, bool IsBackup)
    {
    char * NonGhostName = DeGhostModName(FileName);
    char * const &UsedName = NonGhostName ? NonGhostName : FileName;
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

    char * temp_extension = IsBackup ? ".bak.%Y_%m_%d_%H_%M_%S" : ".new.%Y_%m_%d_%H_%M_%S";
    uint32_t name_size = (uint32_t)strlen(UsedName);
    uint32_t temp_size = name_size + (uint32_t)strlen(".XXX.XXXX_XX_XX_XX_XX_XX") + 1;
    char * temp_name = new char[temp_size];

    strcpy_s(temp_name, temp_size, UsedName);
    delete []NonGhostName;
    strftime(temp_name + name_size, temp_size, temp_extension, &current_time);

    //If the new name already exists, add another minute until a free name is available
    //If 10 tries pass, then give up.
    uint32_t attempts = 0;
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

RenameOp::RenameOp(char * _original_name, char * _destination_name):
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
        char * backup_name = GetTemporaryFileName(destination_name, true);

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

bool AlmostEqual(float A, float B, int32_t maxUlps)
    {
    int32_t aInt = *(int32_t*)&A;
    // Make aInt lexicographically ordered as a twos-complement int
    if (aInt < 0)
        aInt = 0x80000000 - aInt;
    // Make bInt lexicographically ordered as a twos-complement int
    int32_t bInt = *(int32_t*)&B;
    if (bInt < 0)
        bInt = 0x80000000 - bInt;

    // Now we can compare aInt and bInt to find out how far apart A and B
    // are.
    if (abs(aInt - bInt) <= maxUlps)
        return true;
    return false;
    }

void UnrecognizedSubRecord(cb_formid_t formID, uint32_t subType, uint32_t subSize, unsigned char *&buffer, unsigned char *end_buffer)
{
    //printf("FileName = %s\n", FileName);
    printf("  BPTD: %08X - Unknown subType = %04x\n", formID, subType);
    printf("  Size = %i\n", subSize);
    printf("  CurPos = %04x\n\n", reinterpret_cast<unsigned int>(buffer - 6));
    buffer = end_buffer;
}

FileWriter::FileWriter(char * filename, uint32_t size):
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

int32_t FileWriter::open()
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

int32_t FileWriter::close()
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

void FileWriter::record_write(const void *source, uint32_t length)
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

void FileWriter::record_write_subheader(uint32_t signature, uint32_t length)
    {
    if(length <= 65535)
        {
        record_write(&signature, 4);
        record_write(&length, 2);
        }
    else //Requires XXXX SubRecord
        {
        uint32_t _Temp = 4;
        record_write("XXXX", 4);
        record_write(&_Temp, 2);
        record_write(&length, 4);
        record_write(&signature, 4);
        _Temp = 0;
        record_write(&_Temp, 2);
        }
    return;
    }

void FileWriter::record_write_subrecord(uint32_t signature, const void *source, uint32_t length)
    {
    record_write_subheader(signature, length);
    record_write(source, length);
    return;
    }

uint32_t FileWriter::record_compress()
    {
    uLong compSize = compressBound(record_buffer_used);
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

uint32_t FileWriter::record_size()
    {
    return record_buffer_used;
    }

void FileWriter::record_flush()
    {
    file_write(record_buffer, record_buffer_used);
    record_buffer_used = 0;
    return;
    }

uint32_t FileWriter::file_tell()
    {
    return file_buffer_used + _tell(fh);
    }

void FileWriter::file_write(const void *source_buffer, uint32_t source_buffer_used)
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

void FileWriter::file_write(uint32_t position, const void *source_buffer, uint32_t source_buffer_used)
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
    int32_t curPos = _tell(fh);

    if(position < (uint32_t)curPos)
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

FormIDHandlerClass::FormIDHandlerClass(std::vector<char *> &_MAST, uint32_t &_NextObject):
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

void FormIDHandlerClass::SetLoadOrder(std::vector<char *> &cLoadOrder)
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

uint32_t FormIDHandlerClass::NextExpandedFormID()
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
    uint32_t numMods = (uint32_t)LoadOrder255.size();
    char * curMaster = NULL;
    CollapsedIndex = (uint8_t)MAST.size();
    //By default, every in memory modIndex maps to the on disk modIndex of the mod
    for(uint16_t p = 0; p <= 0xFF; ++p)
        CollapseTable[(uint8_t)p] = CollapsedIndex;

    //Go ahead and sort the masters now since it can't otherwise be done without
    // screwing up the CollapseTable
    std::vector<char *> sortedMAST;
    sortedMAST.reserve(CollapsedIndex);
    for(uint32_t x = 0; x < LoadOrder255.size(); ++x)
        {
        curMaster = LoadOrder255[(uint8_t)x];
        for(uint16_t y = 0; y < CollapsedIndex; ++y)
            {
            if(icmps(curMaster, MAST[(uint8_t)y]) == 0)
                {
                sortedMAST.push_back(MAST[(uint8_t)y]);
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
    for(uint16_t p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[(uint8_t)p] = sortedMAST[(uint8_t)p];
        //printer("master %s\n", curMaster);
        for(uint32_t y = 0; y < numMods; ++y)
            if(icmps(LoadOrder255[(uint8_t)y], curMaster) == 0)
                {
                CollapseTable[(uint8_t)y] = (uint8_t)p;
                //printer("%02X == %02X\n", (uint8_t)y, (uint8_t)p);
                break;
                }
        }
    //printer("Collapse table updated.\n");
    //printer("Existing expand table: %02X\n", ExpandedIndex);
    //for(uint32_t y = 0; y <= 0xFF; ++y)
    //    printer("%02X == %02X\n", (uint8_t)y, ExpandTable[(uint8_t)y]);
    //printer("End expand table.\n");
    sortedMAST.clear();
    return;
    }

void FormIDHandlerClass::CreateFormIDLookup(const uint8_t expandedIndex)
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

    uint32_t numMods = (uint32_t)LoadOrder255.size();
    char * curMaster = NULL;

    CollapsedIndex = (uint8_t)MAST.size();
    ExpandedIndex = expandedIndex;

    //By default, every in memory modIndex maps to the on disk modIndex of the mod
    //By default, every on disk modIndex maps to the in memory modIndex of the mod
    for(uint16_t p = 0; p <= 0xFF; ++p)
        {
        CollapseTable[(uint8_t)p] = CollapsedIndex;
        ExpandTable[(uint8_t)p] = ExpandedIndex;
        }

    //Map every on disk modIndex to its in memory modIndex and vice versa
    for(uint16_t p = 0; p < CollapsedIndex; ++p)
        {
        curMaster = MAST[(uint8_t)p];
        for(uint32_t y = 0; y < numMods; ++y)
            if(icmps(LoadOrder255[(uint8_t)y], curMaster) == 0)
                {
                ExpandTable[(uint8_t)p] = (uint8_t)y;
                CollapseTable[(uint8_t)y] = (uint8_t)p;
                break;
                }
        }
    return;
    }

void FormIDHandlerClass::AddMaster(char * const curMaster)
    {
    uint32_t size = (uint32_t)strlen(curMaster) + 1;
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

CreationFlags::CreationFlags(uint32_t nFlags):
    SetAsOverride((nFlags & CB_SET_AS_OVERRIDE) != 0),
    CopyWinningParent((nFlags & CB_COPY_WINNING_PARENT) != 0),
    ExistingReturned(false)
    {
    //
    }

CreationFlags::~CreationFlags()
    {
    //
    }

uint32_t CreationFlags::GetFlags()
    {
    uint32_t flags = 0;
    if(SetAsOverride)
        flags |= CB_SET_AS_OVERRIDE;
    if(CopyWinningParent)
        flags |= CB_COPY_WINNING_PARENT;
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

ModFlags::ModFlags(uint32_t _Flags):
    IsMinLoad((_Flags & CB_MIN_LOAD) != 0 && (_Flags & CB_FULL_LOAD) == 0),
    IsFullLoad((_Flags & CB_FULL_LOAD) != 0),
    IsNoLoad(!(IsMinLoad || IsFullLoad)),
    IsSkipNewRecords((_Flags & CB_SKIP_NEW_RECORDS) != 0),
    IsSkipAllRecords((_Flags & CB_SKIP_ALL_RECORDS) != 0),
    IsInLoadOrder((_Flags & CB_IN_LOAD_ORDER) != 0),
    IsSaveable(((_Flags & CB_IN_LOAD_ORDER) != 0) ? ((_Flags & CB_SAVEABLE) != 0) : false),
    IsAddMasters(((_Flags & CB_IGNORE_INACTIVE_MASTERS) != 0) ? false : ((_Flags & CB_ADD_MASTERS) != 0)),
    IsLoadMasters((_Flags & CB_LOAD_MASTERS) != 0),
    IsExtendedConflicts((_Flags & CB_EXTENDED_CONFLICTS) != 0),
    IsTrackNewTypes((_Flags & CB_TRACK_NEW_TYPES) != 0),
    IsIndexLANDs((_Flags & CB_INDEX_LANDS) != 0),
    IsFixupPlaceables((_Flags & CB_FIXUP_PLACEABLES) != 0),
    IsCreateNew((_Flags & CB_CREATE_NEW) != 0),
    IsIgnoreInactiveMasters((_Flags & CB_IGNORE_INACTIVE_MASTERS) != 0),
    LoadedGRUPs(false)
    {
    //
    }

ModFlags::~ModFlags()
    {
    //
    }

uint32_t ModFlags::GetFlags()
    {
    uint32_t flags = 0;
    if(IsMinLoad)
        flags |= CB_MIN_LOAD;
    if(IsFullLoad)
        {
        flags |= CB_FULL_LOAD;
        flags &= ~CB_MIN_LOAD;
        }
    if(IsNoLoad)
        {
        flags &= ~CB_FULL_LOAD;
        flags &= ~CB_MIN_LOAD;
        }
    if(IsSkipNewRecords)
        flags |= CB_SKIP_NEW_RECORDS;
    if(IsSkipAllRecords)
        flags |= CB_SKIP_ALL_RECORDS;
    if(IsInLoadOrder)
        flags |= CB_IN_LOAD_ORDER;
    if(IsSaveable)
        flags |= CB_SAVEABLE;
    if(IsAddMasters)
        flags |= CB_ADD_MASTERS;
    if(IsLoadMasters)
        flags |= CB_LOAD_MASTERS;
    if(IsExtendedConflicts)
        flags |= CB_EXTENDED_CONFLICTS;
    if(IsTrackNewTypes)
        flags |= CB_TRACK_NEW_TYPES;
    if(IsIndexLANDs)
        flags |= CB_INDEX_LANDS;
    if(IsFixupPlaceables)
        flags |= CB_FIXUP_PLACEABLES;
    if(IsCreateNew)
        flags |= CB_CREATE_NEW;
    if(IsIgnoreInactiveMasters)
        {
        flags &= ~CB_ADD_MASTERS;
        flags |= CB_IGNORE_INACTIVE_MASTERS;
        }
    return flags;
    }

SaveFlags::SaveFlags():
    IsCleanMasters(true),
    IsCloseCollection(false)
    {
    //
    }

SaveFlags::SaveFlags(uint32_t _Flags):
    IsCleanMasters((_Flags & CB_CLEAN_MASTERS) != 0),
    IsCloseCollection((_Flags & CB_CLOSE_COLLECTION) != 0)
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
        uint32_t size = p.GetSize();
        VAL_NAME = new char[size];
        memcpy(VAL_NAME, p.VAL_NAME, size);
        }
    }

StringRecord::~StringRecord()
    {
    if(!S_IS_ON_DISK)
        delete []VAL_NAME;
    }

uint32_t StringRecord::GetSize() const
    {
    return VAL_NAME != NULL ? (uint32_t)strlen((S_GET_VALUE)) + 1 : 0;
    }

#ifndef CBASH_X64_COMPATIBILITY
    char * StringRecord::GetString()
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

bool StringRecord::Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk)
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

void StringRecord::Write(uint32_t _Type, FileWriter &writer)
    {
    if((S_GET_VALUE) != NULL)
        writer.record_write_subrecord(_Type, (S_GET_VALUE), (uint32_t)strlen((S_GET_VALUE)) + 1);
    }

void StringRecord::ReqWrite(uint32_t _Type, FileWriter &writer)
    {
    if((S_GET_VALUE) != NULL)
        writer.record_write_subrecord(_Type, (S_GET_VALUE), (uint32_t)strlen((S_GET_VALUE)) + 1);
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void StringRecord::Copy(char * FieldValue)
    {
    Unload();
    if(FieldValue != NULL)
        {
        S_SET_ON_DISK(false);
        uint32_t size = (uint32_t)strlen(FieldValue) + 1;
        VAL_NAME = new char[size];
        memcpy(VAL_NAME, FieldValue, size);
        }
    }

void StringRecord::TruncateCopy(char * FieldValue, uint32_t MaxSize)
    {
    Unload();
    if(FieldValue != NULL)
        {
        S_SET_ON_DISK(false);
        uint32_t size = (uint32_t)strlen(FieldValue) + 1;
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
            uint32_t size = (uint32_t)strlen(rhs.VAL_NAME) + 1;
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
        uint32_t size = p.GetSize();
        _value = new char[size];
        memcpy(_value, p._value, size);
        }
    }

NonNullStringRecord::~NonNullStringRecord()
    {
    if(DiskSize == 0)
        delete []_value;
    }

uint32_t NonNullStringRecord::GetSize() const
    {
    return _value != NULL ? (DiskSize ? DiskSize : (uint32_t)strlen(_value)) : 0;
    }

char * NonNullStringRecord::GetString()
    {
    if(DiskSize != 0)
        {
        //Have to sanitize the string before letting it be used
        //The string needs a null terminator added, so load it from disk
        char * nvalue = new char[DiskSize + 1];
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

bool NonNullStringRecord::Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk)
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
        _value = subSize > 0 ? reinterpret_cast<char *>(buffer) : nullptr;
        }
    buffer += subSize;
    return true;
    }

void NonNullStringRecord::Write(uint32_t _Type, FileWriter &writer)
    {
    if(_value != NULL)
        writer.record_write_subrecord(_Type, _value, DiskSize ? DiskSize : (uint32_t)strlen(_value));
    }

void NonNullStringRecord::Write16(FileWriter &writer) const
    {
    if (_value != NULL)
    {
        uint16_t size = DiskSize ? (uint16_t)DiskSize : (uint16_t)strlen(_value);
        writer.record_write(&size, sizeof(size));
        writer.record_write(_value, size);
    }
    }

void NonNullStringRecord::ReqWrite(uint32_t _Type, FileWriter &writer)
    {
    if(_value != NULL)
        writer.record_write_subrecord(_Type, _value, DiskSize ? DiskSize : (uint32_t)strlen(_value));
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void NonNullStringRecord::Copy(char * FieldValue)
    {
    Unload();
    if(FieldValue != NULL)
        {
        DiskSize = 0;
        uint32_t size = (uint32_t)strlen(FieldValue) + 1;
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
            uint32_t size = (uint32_t)strlen(rhs._value) + 1;
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

uint32_t UnorderedPackedStrings::GetSize() const
    {
    if(value.size())
        {
        uint32_t cSize = 1; //final null terminator
        for(uint32_t p = 0; p < value.size(); p++)
            if(value[p] != NULL)
                cSize += (uint32_t)strlen(value[p]) + 1;
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
    for(uint32_t x = 0; x < value.size(); ++x)
        delete value[x];
    value.clear();
    }

void UnorderedPackedStrings::resize(uint32_t newSize)
    {
    //Shrink
    uint32_t size = (uint32_t)value.size();
    for(; size > newSize;)
        delete value[--size];
    value.resize(newSize);
    //Grow
    for(; size < newSize;)
        value[size++] = NULL;
    }

bool UnorderedPackedStrings::Read(unsigned char *&buffer, const uint32_t &subSize)
    {
    if(value.size() != 0)
        {
        buffer += subSize;
        return false;
        }
    char * curString = NULL;

    for(unsigned char *end_buffer = buffer + subSize;buffer < (end_buffer - 1);)
        {
        if(((char *)buffer)[0] == 0x00)
            {
            buffer++;
            continue;
            }
        uint32_t size = (uint32_t)strlen((char *)buffer) + 1;
        curString = new char[size];
        strcpy_s(curString, size, (char *)buffer);
        value.push_back(curString);
        buffer += size;
        }
    buffer++; //Skip the final null terminator
    return true;
    }

void UnorderedPackedStrings::Write(uint32_t _Type, FileWriter &writer)
    {
    if(value.size())
        {
        writer.record_write_subheader(_Type, GetSize());
        for(uint32_t p = 0; p < value.size(); p++)
            if(value[p] != NULL)
                writer.record_write(value[p], (uint32_t)strlen(value[p]) + 1);
        uint8_t cSize = 0x00;
        //write final null terminator
        writer.record_write(&cSize, 1);
        }
    }

void UnorderedPackedStrings::Copy(STRINGARRAY FieldValue, uint32_t ArraySize)
    {
    resize(ArraySize);
    for(uint32_t x = 0; x < ArraySize; x++)
        {
        if(((STRINGARRAY)FieldValue)[x] != NULL)
            {
            uint32_t size = (uint32_t)strlen(((STRINGARRAY)FieldValue)[x]) + 1;
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
            uint32_t size = 0;
            for(uint32_t p = 0; p < rhs.value.size(); p++)
                {
                if(rhs.value[p] != NULL)
                    {
                    size = (uint32_t)strlen(rhs.value[p]) + 1;
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
        for(uint32_t x = 0; x < value.size(); ++x)
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
        for(uint32_t x = 0; x < value.size(); ++x)
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

uint32_t RawRecord::GetSize() const
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

bool RawRecord::Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk)
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

void RawRecord::Write(uint32_t _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, size & ~fIsOnDisk);
    }

void RawRecord::ReqWrite(uint32_t _Type, FileWriter &writer)
    {
    if(value != NULL)
        writer.record_write_subrecord(_Type, value, size & ~fIsOnDisk);
    else
        {
        char null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
        }
    }

void RawRecord::Copy(unsigned char *FieldValue, uint32_t nSize)
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

bool ReadChunk(unsigned char *&buffer, const uint32_t &buffer_size, void *dest_buffer, const uint32_t &dest_buffer_size, const bool &skip_load)
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

const uint32_t VATSFunction_Argument[] =
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

Function_ArgumentsType SKFunction_ArgumentsInit[] =
{
    Function_ArgumentsType(0, std::make_pair(eNONE, eNONE)),         //GetWantBlocking
    Function_ArgumentsType(1, std::make_pair(eFORMID, eNONE)),       //GetDistance
    Function_ArgumentsType(5, std::make_pair(eNONE, eNONE)),         //GetLocked
    Function_ArgumentsType(6, std::make_pair(eUINT32, eNONE)),       //GetPos
    Function_ArgumentsType(8, std::make_pair(eUINT32, eNONE)),       //GetAngle
    Function_ArgumentsType(10, std::make_pair(eUINT32, eNONE)),      //GetStartingPos
    Function_ArgumentsType(11, std::make_pair(eUINT32, eNONE)),      //GetStartingAngle
    Function_ArgumentsType(12, std::make_pair(eNONE, eNONE)),        //GetSecondsPassed
    Function_ArgumentsType(14, std::make_pair(eUINT32, eNONE)),      //GetActorValue
    Function_ArgumentsType(18, std::make_pair(eNONE, eNONE)),        //GetCurrentTime
    Function_ArgumentsType(24, std::make_pair(eNONE, eNONE)),        //GetScale
    Function_ArgumentsType(25, std::make_pair(eNONE, eNONE)),        //IsMoving
    Function_ArgumentsType(26, std::make_pair(eNONE, eNONE)),        //IsTurning
    Function_ArgumentsType(27, std::make_pair(eFORMID, eNONE)),      //GetLineOfSight
    Function_ArgumentsType(32, std::make_pair(eFORMID, eNONE)),      //GetInSameCell
    Function_ArgumentsType(35, std::make_pair(eNONE, eNONE)),        //GetDisabled
    Function_ArgumentsType(36, std::make_pair(eUINT32, eNONE)),      //MenuMode
    Function_ArgumentsType(39, std::make_pair(eNONE, eNONE)),        //GetDisease
    Function_ArgumentsType(41, std::make_pair(eNONE, eNONE)),        //GetClothingValue
    Function_ArgumentsType(42, std::make_pair(eFORMID, eNONE)),      //SameFction
    Function_ArgumentsType(43, std::make_pair(eFORMID, eNONE)),      //SameRace
    Function_ArgumentsType(44, std::make_pair(eFORMID, eNONE)),      //SameSex
    Function_ArgumentsType(45, std::make_pair(eFORMID, eNONE)),      //GetDetected
    Function_ArgumentsType(46, std::make_pair(eNONE, eNONE)),        //GetDead
    Function_ArgumentsType(47, std::make_pair(eFORMID, eNONE)),      //GetItemCount
    Function_ArgumentsType(48, std::make_pair(eNONE, eNONE)),        //GetGold
    Function_ArgumentsType(49, std::make_pair(eNONE, eNONE)),        //GetSleeping
    Function_ArgumentsType(50, std::make_pair(eNONE, eNONE)),        //GetTalkedToPC
    Function_ArgumentsType(53, std::make_pair(eFORMID, eUINT32)),    //GetScriptVariable
    Function_ArgumentsType(56, std::make_pair(eFORMID, eNONE)),      //GetQuestRunning
    Function_ArgumentsType(58, std::make_pair(eFORMID, eNONE)),      //GetStage
    Function_ArgumentsType(59, std::make_pair(eFORMID, eUINT32)),    //GetStageDone
    Function_ArgumentsType(60, std::make_pair(eFORMID, eFORMID)),    //GetFactionRankDifference
    Function_ArgumentsType(61, std::make_pair(eNONE, eNONE)),        //GetAlarmed
    Function_ArgumentsType(62, std::make_pair(eNONE, eNONE)),        //IsRaining
    Function_ArgumentsType(63, std::make_pair(eNONE, eNONE)),        //GetAttacked
    Function_ArgumentsType(64, std::make_pair(eNONE, eNONE)),        //GetIsCreature
    Function_ArgumentsType(65, std::make_pair(eNONE, eNONE)),        //GetLockLevel
    Function_ArgumentsType(66, std::make_pair(eFORMID, eNONE)),      //GetShouldAttack
    Function_ArgumentsType(67, std::make_pair(eFORMID, eNONE)),      //GetInCell
    Function_ArgumentsType(68, std::make_pair(eFORMID, eNONE)),      //GetIsClass
    Function_ArgumentsType(69, std::make_pair(eFORMID, eNONE)),      //GetIsRace
    Function_ArgumentsType(70, std::make_pair(eFORMID, eNONE)),      //GetIsSex
    Function_ArgumentsType(71, std::make_pair(eFORMID, eNONE)),      //GetInFaction
    Function_ArgumentsType(72, std::make_pair(eFORMID, eNONE)),      //GetIsID
    Function_ArgumentsType(73, std::make_pair(eFORMID, eNONE)),      //GetFactionRank
    Function_ArgumentsType(74, std::make_pair(eFORMID, eNONE)),      //GetGlobalValue
    Function_ArgumentsType(75, std::make_pair(eNONE, eNONE)),        //IsSnowing
    Function_ArgumentsType(77, std::make_pair(eNONE, eNONE)),        //GetRandomPercent
    Function_ArgumentsType(79, std::make_pair(eFORMID, eUINT32)),    //GetQuestVvariable
    Function_ArgumentsType(80, std::make_pair(eNONE, eNONE)),        //GetLevel
    Function_ArgumentsType(81, std::make_pair(eNONE, eNONE)),        //IsRotating
    Function_ArgumentsType(84, std::make_pair(eFORMID, eNONE)),      //GetDeadCount
    Function_ArgumentsType(91, std::make_pair(eNONE, eNONE)),        //GetIsAlerted
    Function_ArgumentsType(98, std::make_pair(eNONE, eNONE)),        //GetPlayerControlsDisabled
    Function_ArgumentsType(99, std::make_pair(eFORMID, eNONE)),      //GetHeadingAngle
    Function_ArgumentsType(101, std::make_pair(eNONE, eNONE)),       //IsWeaponMagicOut
    Function_ArgumentsType(102, std::make_pair(eNONE, eNONE)),       //IsTorchOut
    Function_ArgumentsType(103, std::make_pair(eNONE, eNONE)),       //IsShieldOut
    Function_ArgumentsType(106, std::make_pair(eNONE, eNONE)),       //IsFacingUp
    Function_ArgumentsType(107, std::make_pair(eNONE, eNONE)),       //GetKnockedState
    Function_ArgumentsType(108, std::make_pair(eNONE, eNONE)),       //GetWeaponAnimType
    Function_ArgumentsType(109, std::make_pair(eUINT32, eNONE)),     //IsWeaponSkillType
    Function_ArgumentsType(110, std::make_pair(eNONE, eNONE)),       //GetCurrentAIPackage
    Function_ArgumentsType(111, std::make_pair(eNONE, eNONE)),       //IsWaiting
    Function_ArgumentsType(112, std::make_pair(eNONE, eNONE)),       //IsIdlePlaying
    Function_ArgumentsType(116, std::make_pair(eNONE, eNONE)),       //IsIntimidatedbyPlayer
    Function_ArgumentsType(117, std::make_pair(eFORMID, eNONE)),     //IsPlayerInRegion
    Function_ArgumentsType(118, std::make_pair(eNONE, eNONE)),       //GetActorAggroRadiusViolated
    Function_ArgumentsType(122, std::make_pair(eFORMID, eUINT32)),   //GetCrime
    Function_ArgumentsType(123, std::make_pair(eNONE, eNONE)),       //IsGreetingPlayer
    Function_ArgumentsType(125, std::make_pair(eNONE, eNONE)),       //IsGuard
    Function_ArgumentsType(127, std::make_pair(eNONE, eNONE)),       //HasBeenEaten
    Function_ArgumentsType(128, std::make_pair(eNONE, eNONE)),       //GetStaminaPercentage
    Function_ArgumentsType(129, std::make_pair(eFORMID, eNONE)),     //GetPCIsClass
    Function_ArgumentsType(130, std::make_pair(eFORMID, eNONE)),     //GetPCIsRace
    Function_ArgumentsType(131, std::make_pair(eFORMID, eNONE)),     //GetPCIsSex
    Function_ArgumentsType(132, std::make_pair(eFORMID, eNONE)),     //GetPCInFaction
    Function_ArgumentsType(133, std::make_pair(eNONE, eNONE)),       //SameFactionAsPC
    Function_ArgumentsType(134, std::make_pair(eNONE, eNONE)),       //SameRaceAsPC
    Function_ArgumentsType(135, std::make_pair(eNONE, eNONE)),       //SameSexAsPC
    Function_ArgumentsType(136, std::make_pair(eFORMID, eNONE)),     //GetIsReference
    Function_ArgumentsType(141, std::make_pair(eNONE, eNONE)),       //IsTalking
    Function_ArgumentsType(142, std::make_pair(eNONE, eNONE)),       //GetWalkSpeed
    Function_ArgumentsType(143, std::make_pair(eNONE, eNONE)),       //GetCurrentAIProcedure
    Function_ArgumentsType(144, std::make_pair(eNONE, eNONE)),       //GetTrespassWarningLevel
    Function_ArgumentsType(145, std::make_pair(eNONE, eNONE)),       //IsTresPassing
    Function_ArgumentsType(146, std::make_pair(eNONE, eNONE)),       //IsInMyOwnedCell
    Function_ArgumentsType(147, std::make_pair(eNONE, eNONE)),       //GetWindSpeed
    Function_ArgumentsType(148, std::make_pair(eNONE, eNONE)),       //GetCurrentWeatherPercent
    Function_ArgumentsType(149, std::make_pair(eFORMID, eNONE)),     //GetIsCurrentWeather
    Function_ArgumentsType(150, std::make_pair(eNONE, eNONE)),       //IsContinuingPackagePCNear
    Function_ArgumentsType(152, std::make_pair(eFORMID, eNONE)),     //GetIsCrimeFaction
    Function_ArgumentsType(153, std::make_pair(eNONE, eNONE)),       //CanHaveFlames
    Function_ArgumentsType(154, std::make_pair(eNONE, eNONE)),       //HasFlames
    Function_ArgumentsType(157, std::make_pair(eNONE, eNONE)),       //GetOpenState
    Function_ArgumentsType(159, std::make_pair(eNONE, eNONE)),       //GetSitting
    Function_ArgumentsType(161, std::make_pair(eFORMID, eNONE)),     //GetIsCurrentPackage
    Function_ArgumentsType(162, std::make_pair(eFORMID, eNONE)),     //IsCurrentFurnitureRef
    Function_ArgumentsType(163, std::make_pair(eFORMID, eNONE)),     //IsCurrentFurnitureObj
    Function_ArgumentsType(170, std::make_pair(eNONE, eNONE)),       //GetDayOfWeek
    Function_ArgumentsType(172, std::make_pair(eFORMID, eNONE)),     //GetTalkedToPCParam
    Function_ArgumentsType(175, std::make_pair(eNONE, eNONE)),       //IsPCSleeping
    Function_ArgumentsType(176, std::make_pair(eNONE, eNONE)),       //IsPCAMurderer
    Function_ArgumentsType(180, std::make_pair(eFORMID, eFORMID)),   //HasSameEditorLocAsRef
    Function_ArgumentsType(181, std::make_pair(eFORMID, eFORMID)),   //HasSameEditorLocAsRefAlias
    Function_ArgumentsType(182, std::make_pair(eFORMID, eNONE)),     //GetEquiped
    Function_ArgumentsType(185, std::make_pair(eNONE, eNONE)),       //IsSwimming
    Function_ArgumentsType(190, std::make_pair(eNONE, eNONE)),       //GetAmountSoldStolen
    Function_ArgumentsType(192, std::make_pair(eNONE, eNONE)),       //GetIgnoreCrime
    Function_ArgumentsType(193, std::make_pair(eFORMID, eNONE)),     //GetPCExpelled
    Function_ArgumentsType(195, std::make_pair(eFORMID, eNONE)),     //GetPCFactionMurder
    Function_ArgumentsType(197, std::make_pair(eFORMID, eNONE)),     //GetPCEnemyofFaction
    Function_ArgumentsType(199, std::make_pair(eFORMID, eNONE)),     //GetPCFactionAttack
    Function_ArgumentsType(203, std::make_pair(eNONE, eNONE)),       //GetDestroyed
    Function_ArgumentsType(214, std::make_pair(eFORMID, eNONE)),     //HasMagicEffect
    Function_ArgumentsType(215, std::make_pair(eNONE, eNONE)),       //GetDefaultOpen
    Function_ArgumentsType(219, std::make_pair(eNONE, eNONE)),       //GetAnimAction
    Function_ArgumentsType(223, std::make_pair(eFORMID, eNONE)),     //IsSpellTarget
    Function_ArgumentsType(224, std::make_pair(eNONE, eNONE)),       //GetVATSMode
    Function_ArgumentsType(225, std::make_pair(eNONE, eNONE)),       //GetPersuationNumber
    Function_ArgumentsType(226, std::make_pair(eNONE, eNONE)),       //GetVampireFeed
    Function_ArgumentsType(227, std::make_pair(eNONE, eNONE)),       //GetCannibal
    Function_ArgumentsType(228, std::make_pair(eFORMID, eNONE)),     //GetIsClassDefault
    Function_ArgumentsType(229, std::make_pair(eNONE, eNONE)),       //GetClassDefaultMatch
    Function_ArgumentsType(230, std::make_pair(eFORMID, eFORMID)),   //GetInCellParam
    Function_ArgumentsType(235, std::make_pair(eNONE, eNONE)),       //GetVatsTargetHeight
    Function_ArgumentsType(237, std::make_pair(eNONE, eNONE)),       //GetIsGhost
    Function_ArgumentsType(242, std::make_pair(eNONE, eNONE)),       //GetUnconscious
    Function_ArgumentsType(244, std::make_pair(eNONE, eNONE)),       //GetRestrained
    Function_ArgumentsType(246, std::make_pair(eFORMID, eNONE)),     //GetIsUsedItem
    Function_ArgumentsType(247, std::make_pair(eFORMID, eNONE)),     //GetIsUsedItemType
    Function_ArgumentsType(248, std::make_pair(eFORMID, eNONE)),     //IsScenePlaying
    Function_ArgumentsType(249, std::make_pair(eNONE, eNONE)),       //IsInDialogWithPlayer
    Function_ArgumentsType(250, std::make_pair(eFORMID, eNONE)),     //GetLocationCleared
    Function_ArgumentsType(254, std::make_pair(eNONE, eNONE)),       //GetIsPlayableRace
    Function_ArgumentsType(255, std::make_pair(eNONE, eNONE)),       //GetOffersServicesNow
    Function_ArgumentsType(258, std::make_pair(eFORMID, eFORMID)),   //HasAssociationType
    Function_ArgumentsType(259, std::make_pair(eFORMID, eNONE)),     //HasFamilyRelationship
    Function_ArgumentsType(261, std::make_pair(eFORMID, eNONE)),     //HasParentRelationship
    Function_ArgumentsType(262, std::make_pair(eFORMID, eNONE)),     //IsWarningAbout
    Function_ArgumentsType(263, std::make_pair(eNONE, eNONE)),       //IsWeaponOut
    Function_ArgumentsType(264, std::make_pair(eFORMID, eNONE)),     //HasSpell
    Function_ArgumentsType(265, std::make_pair(eNONE, eNONE)),       //IsTimePassing
    Function_ArgumentsType(266, std::make_pair(eNONE, eNONE)),       //IsPleasant
    Function_ArgumentsType(267, std::make_pair(eNONE, eNONE)),       //IsCloudy
    Function_ArgumentsType(274, std::make_pair(eNONE, eNONE)),       //IsSmallBump
    Function_ArgumentsType(277, std::make_pair(eUINT32, eNONE)),     //GetBaseActorValue
    Function_ArgumentsType(278, std::make_pair(eFORMID, eNONE)),     //IsOwner
    Function_ArgumentsType(280, std::make_pair(eFORMID, eFORMID)),   //IsCellOwner
    Function_ArgumentsType(282, std::make_pair(eNONE, eNONE)),       //IsHorseStolen
    Function_ArgumentsType(285, std::make_pair(eNONE, eNONE)),       //IsLeftUp
    Function_ArgumentsType(286, std::make_pair(eNONE, eNONE)),       //IsSneaking
    Function_ArgumentsType(287, std::make_pair(eNONE, eNONE)),       //IsRunning
    Function_ArgumentsType(288, std::make_pair(eNONE, eNONE)),       //GetFriendHit
    Function_ArgumentsType(289, std::make_pair(eUINT32, eNONE)),     //IsInCombat
    Function_ArgumentsType(300, std::make_pair(eNONE, eNONE)),       //IsInInterior
    Function_ArgumentsType(304, std::make_pair(eNONE, eNONE)),       //IsWaterObject
    Function_ArgumentsType(305, std::make_pair(eNONE, eNONE)),       //GetPlayerAction
    Function_ArgumentsType(306, std::make_pair(eNONE, eNONE)),       //IsActorUsingATorch
    Function_ArgumentsType(309, std::make_pair(eNONE, eNONE)),       //IsXBox
    Function_ArgumentsType(310, std::make_pair(eFORMID, eNONE)),     //GetInWorldspace
    Function_ArgumentsType(312, std::make_pair(eUINT32, eNONE)),     //GetPCMiscStat
    Function_ArgumentsType(313, std::make_pair(eNONE, eNONE)),       //GetPairedAnimation
    Function_ArgumentsType(314, std::make_pair(eNONE, eNONE)),       //IsActorAVictim
    Function_ArgumentsType(315, std::make_pair(eNONE, eNONE)),       //GetTotalPersuationNumber
    Function_ArgumentsType(318, std::make_pair(eNONE, eNONE)),       //GetIdleDoneOnce
    Function_ArgumentsType(320, std::make_pair(eNONE, eNONE)),       //GetNoRumors
    Function_ArgumentsType(323, std::make_pair(eNONE, eNONE)),       //GetCombatState
    Function_ArgumentsType(325, std::make_pair(eFORMID, eNONE)),     //GetWithinPackageLocation
    Function_ArgumentsType(327, std::make_pair(eNONE, eNONE)),       //IsRidingHorse
    Function_ArgumentsType(329, std::make_pair(eNONE, eNONE)),       //IsFleeing
    Function_ArgumentsType(332, std::make_pair(eNONE, eNONE)),       //IsInDangerousWater
    Function_ArgumentsType(338, std::make_pair(eNONE, eNONE)),       //GetIgnoreFriendlyHits
    Function_ArgumentsType(339, std::make_pair(eNONE, eNONE)),       //IsPlayersLastRiddenHorse
    Function_ArgumentsType(353, std::make_pair(eNONE, eNONE)),       //IsActor
    Function_ArgumentsType(354, std::make_pair(eNONE, eNONE)),       //IsEssential
    Function_ArgumentsType(358, std::make_pair(eNONE, eNONE)),       //IsPlayerMovingIntoNewSpace
    Function_ArgumentsType(359, std::make_pair(eFORMID, eNONE)),     //GetInCurrentLoc
    Function_ArgumentsType(360, std::make_pair(eFORMID, eNONE)),     //GetInCurrentLocAlias
    Function_ArgumentsType(361, std::make_pair(eNONE, eNONE)),       //GetTimeDead
    Function_ArgumentsType(362, std::make_pair(eFORMID, eNONE)),     //HasLinkedRef
    Function_ArgumentsType(365, std::make_pair(eNONE, eNONE)),       //IsChild
    Function_ArgumentsType(366, std::make_pair(eFORMID, eNONE)),     //GetStolenItemValueNoCrime
    Function_ArgumentsType(367, std::make_pair(eNONE, eNONE)),       //GetLastPlayerAction
    Function_ArgumentsType(368, std::make_pair(eUINT32, eNONE)),     //IsPlayerActionActive
    Function_ArgumentsType(370, std::make_pair(eFORMID, eNONE)),     //IsTalkingActivatorActor
    Function_ArgumentsType(372, std::make_pair(eFORMID, eNONE)),     //IsInList
    Function_ArgumentsType(373, std::make_pair(eFORMID, eNONE)),     //GetStolenItemValue
    Function_ArgumentsType(375, std::make_pair(eFORMID, eNONE)),     //GetCrimeGoldViolent
    Function_ArgumentsType(376, std::make_pair(eFORMID, eNONE)),     //GetCrimeGoldNonviolent
    Function_ArgumentsType(378, std::make_pair(eFORMID, eNONE)),     //HasShout
    Function_ArgumentsType(381, std::make_pair(eFORMID, eNONE)),     //GetHasNote
    Function_ArgumentsType(390, std::make_pair(eNONE, eNONE)),       //GetHitLocation
    Function_ArgumentsType(391, std::make_pair(eNONE, eNONE)),       //IsPC1stPerson
    Function_ArgumentsType(396, std::make_pair(eNONE, eNONE)),       //GetCauseofDeath
    Function_ArgumentsType(397, std::make_pair(eUINT32, eNONE)),     //IsLimbGone
    Function_ArgumentsType(398, std::make_pair(eFORMID, eNONE)),     //IsWeaponInList
    Function_ArgumentsType(402, std::make_pair(eNONE, eNONE)),       //IsBribedbyPlayer
    Function_ArgumentsType(403, std::make_pair(eFORMID, eNONE)),     //GetRelationshipRank
    Function_ArgumentsType(407, std::make_pair(eUINT32, eUINT32)),   //GetVATSValue
    Function_ArgumentsType(408, std::make_pair(eFORMID, eNONE)),     //IsKiller
    Function_ArgumentsType(409, std::make_pair(eFORMID, eNONE)),     //IsKillerObject
    Function_ArgumentsType(410, std::make_pair(eFORMID, eFORMID)),   //GetFactionCombatReaction
    Function_ArgumentsType(414, std::make_pair(eFORMID, eNONE)),     //Exists
    Function_ArgumentsType(415, std::make_pair(eNONE, eNONE)),       //GetGroupMemberCount
    Function_ArgumentsType(416, std::make_pair(eNONE, eNONE)),       //GetGroupTargetCount
    Function_ArgumentsType(426, std::make_pair(eFORMID, eNONE)),     //GetIsVoiceType
    Function_ArgumentsType(427, std::make_pair(eNONE, eNONE)),       //GetPlantedExplosive
    Function_ArgumentsType(429, std::make_pair(eNONE, eNONE)),       //IsScenePackageRunning
    Function_ArgumentsType(430, std::make_pair(eNONE, eNONE)),       //GetHealthPercentage
    Function_ArgumentsType(432, std::make_pair(eFORMID, eNONE)),     //GetIsObjectType
    Function_ArgumentsType(434, std::make_pair(eNONE, eNONE)),       //GetDialogEmotion
    Function_ArgumentsType(435, std::make_pair(eNONE, eNONE)),       //GetDialogEmotionValue
    Function_ArgumentsType(437, std::make_pair(eUINT32, eNONE)),     //GetIsCreatureType
    Function_ArgumentsType(444, std::make_pair(eFORMID, eNONE)),     //GetInCurrentLocFormList
    Function_ArgumentsType(445, std::make_pair(eFORMID, eNONE)),     //GetInZone
    Function_ArgumentsType(446, std::make_pair(eUINT32, eNONE)),     //GetVelocity
    Function_ArgumentsType(447, std::make_pair(eUINT32, eNONE)),     //GetGraphVariableFloat
    Function_ArgumentsType(448, std::make_pair(eFORMID, eNONE)),     //HasPerk
    Function_ArgumentsType(449, std::make_pair(eFORMID, eNONE)),     //GetFactionRelation
    Function_ArgumentsType(450, std::make_pair(eFORMID, eNONE)),     //IsLastIdlePlayed
    Function_ArgumentsType(453, std::make_pair(eNONE, eNONE)),       //GetPlayerTeammate
    Function_ArgumentsType(458, std::make_pair(eNONE, eNONE)),       //GetActorCrimePlayerEnemy
    Function_ArgumentsType(459, std::make_pair(eFORMID, eNONE)),     //GetCrimeGold
    Function_ArgumentsType(462, std::make_pair(eNONE, eNONE)),       //GetPlayerGrabbedRef
    Function_ArgumentsType(463, std::make_pair(eFORMID, eNONE)),     //IsPlayerGrabbedRef
    Function_ArgumentsType(465, std::make_pair(eFORMID, eNONE)),     //GetKeywordItemCount
    Function_ArgumentsType(470, std::make_pair(eNONE, eNONE)),       //GetDestructionStage
    Function_ArgumentsType(473, std::make_pair(eFORMID, eNONE)),     //GetIsAlignment
    Function_ArgumentsType(476, std::make_pair(eNONE, eNONE)),       //IsProtected
    Function_ArgumentsType(477, std::make_pair(eFORMID, eNONE)),     //GetThreatRatio
    Function_ArgumentsType(479, std::make_pair(eFORMID, eNONE)),     //GetIsUsedItemEquipType
    Function_ArgumentsType(480, std::make_pair(eNONE, eNONE)),       //GetPlayerName
    Function_ArgumentsType(487, std::make_pair(eNONE, eNONE)),       //IsCarryable
    Function_ArgumentsType(488, std::make_pair(eNONE, eNONE)),       //GetConcussed
    Function_ArgumentsType(491, std::make_pair(eNONE, eNONE)),       //GetMapMarkerVisible
    Function_ArgumentsType(494, std::make_pair(eUINT32, eNONE)),     //GetPermanentActorValue
    Function_ArgumentsType(495, std::make_pair(eNONE, eNONE)),       //GetKillingBlowLimb
    Function_ArgumentsType(497, std::make_pair(eFORMID, eNONE)),     //CanPayCrimeGold
    Function_ArgumentsType(499, std::make_pair(eNONE, eNONE)),       //GetDaysInJail
    Function_ArgumentsType(500, std::make_pair(eNONE, eNONE)),       //EPAlchemyGetMakingPoison
    Function_ArgumentsType(501, std::make_pair(eFORMID, eNONE)),     //EPAlchemyEffectHasKeyword
    Function_ArgumentsType(503, std::make_pair(eNONE, eNONE)),       //GetAllowWorldInteractions
    Function_ArgumentsType(508, std::make_pair(eNONE, eNONE)),       //GetLastHitCritical
    Function_ArgumentsType(513, std::make_pair(eFORMID, eNONE)),     //IsCombatTarget
    Function_ArgumentsType(515, std::make_pair(eFORMID, eNONE)),     //GetVATSRightAreaFree
    Function_ArgumentsType(516, std::make_pair(eFORMID, eNONE)),     //GetVATSLeftAreaFree
    Function_ArgumentsType(517, std::make_pair(eFORMID, eNONE)),     //GetVATSBackAreaFree
    Function_ArgumentsType(518, std::make_pair(eFORMID, eNONE)),     //GetVATSFrontAreaFree
    Function_ArgumentsType(519, std::make_pair(eNONE, eNONE)),       //GetIsLockBroken
    Function_ArgumentsType(520, std::make_pair(eNONE, eNONE)),       //IsPS3
    Function_ArgumentsType(521, std::make_pair(eNONE, eNONE)),       //IsWin32
    Function_ArgumentsType(522, std::make_pair(eFORMID, eNONE)),     //GetVATSRightTargetVisible
    Function_ArgumentsType(523, std::make_pair(eFORMID, eNONE)),     //GetVATSLeftTargetVisible
    Function_ArgumentsType(524, std::make_pair(eFORMID, eNONE)),     //GetVATSBackTargetVisible
    Function_ArgumentsType(525, std::make_pair(eFORMID, eNONE)),     //GetVATSFrontTargetVisible
    Function_ArgumentsType(528, std::make_pair(eFORMID, eNONE)),     //IsInCriticalStage
    Function_ArgumentsType(530, std::make_pair(eNONE, eNONE)),       //GetXPForNextLevel
    Function_ArgumentsType(533, std::make_pair(eFORMID, eNONE)),     //GetInfamy
    Function_ArgumentsType(534, std::make_pair(eFORMID, eNONE)),     //GetInfamyViolent
    Function_ArgumentsType(535, std::make_pair(eFORMID, eNONE)),     //GetInfamyNonViolent
    Function_ArgumentsType(543, std::make_pair(eFORMID, eNONE)),     //GetQuestCompleted
    Function_ArgumentsType(547, std::make_pair(eNONE, eNONE)),       //IsGoreDisabled
    Function_ArgumentsType(550, std::make_pair(eFORMID, eUINT32)),   //IsSceneActionComplete
    Function_ArgumentsType(552, std::make_pair(eFORMID, eNONE)),     //GetSpellUsageNum
    Function_ArgumentsType(554, std::make_pair(eNONE, eNONE)),       //GetActorsInHigh
    Function_ArgumentsType(555, std::make_pair(eNONE, eNONE)),       //HasLoaded3D
    Function_ArgumentsType(560, std::make_pair(eFORMID, eNONE)),     //HasKeyword
    Function_ArgumentsType(561, std::make_pair(eFORMID, eNONE)),     //HasRefType
    Function_ArgumentsType(562, std::make_pair(eFORMID, eNONE)),     //LocationHasKeyword
    Function_ArgumentsType(563, std::make_pair(eFORMID, eNONE)),     //LocationHasRefType
    Function_ArgumentsType(565, std::make_pair(eFORMID, eNONE)),     //GetIsEditorLocation
    Function_ArgumentsType(566, std::make_pair(eFORMID, eNONE)),     //GetIsAliasRef
    Function_ArgumentsType(567, std::make_pair(eFORMID, eNONE)),     //GetIsEditorLocAlias
    Function_ArgumentsType(568, std::make_pair(eNONE, eNONE)),       //IsSprinting
    Function_ArgumentsType(569, std::make_pair(eNONE, eNONE)),       //IsBlocking
    Function_ArgumentsType(570, std::make_pair(eFORMID, eNONE)),     //HasEquippedSpell
    Function_ArgumentsType(571, std::make_pair(eFORMID, eNONE)),     //GetCurrentCastingType
    Function_ArgumentsType(572, std::make_pair(eFORMID, eNONE)),     //GetCurrentDeliveryType
    Function_ArgumentsType(574, std::make_pair(eNONE, eNONE)),       //GetAttackState
    Function_ArgumentsType(576, std::make_pair(eEVENTDATA, eFORMID)),//GetEventData
    Function_ArgumentsType(577, std::make_pair(eFORMID, eFORMID)),   //IsCloserToAThanB
    Function_ArgumentsType(579, std::make_pair(eFORMID, eNONE)),     //GetEquippedShout
    Function_ArgumentsType(580, std::make_pair(eNONE, eNONE)),       //IsBleedingOut
    Function_ArgumentsType(584, std::make_pair(eFORMID, eUINT32)),   //GetRelativeAngle
    Function_ArgumentsType(589, std::make_pair(eNONE, eNONE)),       //GetMovementDirection
    Function_ArgumentsType(590, std::make_pair(eNONE, eNONE)),       //IsInScene
    Function_ArgumentsType(591, std::make_pair(eFORMID, eFORMID)),   //GetRefTypeDeadCount
    Function_ArgumentsType(592, std::make_pair(eFORMID, eFORMID)),   //GetRefTypeAliveCount
    Function_ArgumentsType(594, std::make_pair(eNONE, eNONE)),       //GetIsFlying
    Function_ArgumentsType(595, std::make_pair(eFORMID, eFORMID)),   //IsCurrentSpell
    Function_ArgumentsType(596, std::make_pair(eFORMID, eFORMID)),   //SpellHasKeyword
    Function_ArgumentsType(597, std::make_pair(eFORMID, eNONE)),     //GetEquippedItemType
    Function_ArgumentsType(598, std::make_pair(eFORMID, eNONE)),     //GetLocationAliasCleared
    Function_ArgumentsType(600, std::make_pair(eFORMID, eFORMID)),   //GetLocAliasRefTypeDeadCount
    Function_ArgumentsType(601, std::make_pair(eFORMID, eFORMID)),   //GetLocAliasRefTypeAliveCount
    Function_ArgumentsType(602, std::make_pair(eFORMID, eNONE)),     //IsWardState
    Function_ArgumentsType(603, std::make_pair(eFORMID, eFORMID)),   //IsInSameCurrentLocAsRef
    Function_ArgumentsType(604, std::make_pair(eFORMID, eFORMID)),   //IsInSameCurrentLocAsRefAlias
    Function_ArgumentsType(605, std::make_pair(eFORMID, eFORMID)),   //LocAliasIsLocation
    Function_ArgumentsType(606, std::make_pair(eFORMID, eFORMID)),   //GetKeywordDataForLocation
    Function_ArgumentsType(608, std::make_pair(eFORMID, eFORMID)),   //GetKeywordDataForAlias
    Function_ArgumentsType(610, std::make_pair(eFORMID, eFORMID)),   //LocAliasHasKeyword
    Function_ArgumentsType(611, std::make_pair(eUINT32, eNONE)),     //IsNullPackageData
    Function_ArgumentsType(612, std::make_pair(eUINT32, eNONE)),     //GetNumericPackageData
    Function_ArgumentsType(613, std::make_pair(eFORMID, eNONE)),     //IsFurnitureAnimType
    Function_ArgumentsType(614, std::make_pair(eFORMID, eNONE)),     //IsFurnitureEntryType
    Function_ArgumentsType(615, std::make_pair(eNONE, eNONE)),       //GetHighestRelationshipRank
    Function_ArgumentsType(616, std::make_pair(eNONE, eNONE)),       //GetLowestRelationshipRank
    Function_ArgumentsType(617, std::make_pair(eFORMID, eNONE)),     //HasAssociationTypeAny
    Function_ArgumentsType(618, std::make_pair(eNONE, eNONE)),       //HasFamilyRelationshipAny
    Function_ArgumentsType(619, std::make_pair(eUINT32, eNONE)),     //GetPathingTargetOffset
    Function_ArgumentsType(620, std::make_pair(eUINT32, eNONE)),     //GetPathingTargetAngleOffset
    Function_ArgumentsType(621, std::make_pair(eNONE, eNONE)),       //GetPathingTargetSpeed
    Function_ArgumentsType(622, std::make_pair(eUINT32, eNONE)),     //GetPathingTargetSpeedAngle
    Function_ArgumentsType(623, std::make_pair(eNONE, eNONE)),       //GetMovementSpeed
    Function_ArgumentsType(624, std::make_pair(eFORMID, eNONE)),     //GetInContainer
    Function_ArgumentsType(625, std::make_pair(eFORMID, eNONE)),     //IsLocationLoaded
    Function_ArgumentsType(626, std::make_pair(eFORMID, eNONE)),     //IsLocAliasLoaded
    Function_ArgumentsType(627, std::make_pair(eNONE, eNONE)),       //IsDualCasting
    Function_ArgumentsType(629, std::make_pair(eFORMID, eUINT32)),   //GetVMQuestVariable
    Function_ArgumentsType(630, std::make_pair(eFORMID, eUINT32)),   //GetVMScriptVariable
    Function_ArgumentsType(631, std::make_pair(eNONE, eNONE)),       //IsEnteringInteractionQuick
    Function_ArgumentsType(632, std::make_pair(eNONE, eNONE)),       //IsCasting
    Function_ArgumentsType(633, std::make_pair(eNONE, eNONE)),       //GetFlyingState
    Function_ArgumentsType(635, std::make_pair(eNONE, eNONE)),       //IsInFavorState
    Function_ArgumentsType(636, std::make_pair(eNONE, eNONE)),       //HasTwoHandedWeaponEquipped
    Function_ArgumentsType(637, std::make_pair(eNONE, eNONE)),       //IsExitingInstant
    Function_ArgumentsType(638, std::make_pair(eNONE, eNONE)),       //IsInFriendStatewithPlayer
    Function_ArgumentsType(639, std::make_pair(eFORMID, eUINT32)),   //GetWithinDistance
    Function_ArgumentsType(640, std::make_pair(eUINT32, eNONE)),     //GetActorValuePercent
    Function_ArgumentsType(641, std::make_pair(eNONE, eNONE)),       //IsUnique
    Function_ArgumentsType(642, std::make_pair(eNONE, eNONE)),       //GetLastBumpDirection
    Function_ArgumentsType(644, std::make_pair(eFORMID, eNONE)),     //IsInFurnitureState
    Function_ArgumentsType(645, std::make_pair(eNONE, eNONE)),       //GetIsInjured
    Function_ArgumentsType(646, std::make_pair(eNONE, eNONE)),       //GetIsCrashLandRequest
    Function_ArgumentsType(647, std::make_pair(eNONE, eNONE)),       //GetIsHastyLandRequest
    Function_ArgumentsType(650, std::make_pair(eFORMID, eFORMID)),   //IsLinkedTo
    Function_ArgumentsType(651, std::make_pair(eFORMID, eNONE)),     //GetKeywordDataForCurrentLocation
    Function_ArgumentsType(652, std::make_pair(eFORMID, eNONE)),     //GetInSharedCrimeFaction
    Function_ArgumentsType(654, std::make_pair(eNONE, eNONE)),       //GetBribeSuccess
    Function_ArgumentsType(655, std::make_pair(eNONE, eNONE)),       //GetIntimidateSuccess
    Function_ArgumentsType(656, std::make_pair(eNONE, eNONE)),       //GetArrestedState
    Function_ArgumentsType(657, std::make_pair(eNONE, eNONE)),       //GetArrestingActor
    Function_ArgumentsType(659, std::make_pair(eNONE, eNONE)),       //EPTemperingItemIsEnchanted
    Function_ArgumentsType(660, std::make_pair(eFORMID, eNONE)),     //EPTemperingItemHasKeyword
    Function_ArgumentsType(664, std::make_pair(eFORMID, eNONE)),     //GetReplacedItemType
    Function_ArgumentsType(672, std::make_pair(eNONE, eNONE)),       //IsAttacking
    Function_ArgumentsType(673, std::make_pair(eNONE, eNONE)),       //IsPowerAttacking
    Function_ArgumentsType(674, std::make_pair(eNONE, eNONE)),       //IsLastHostileActor
    Function_ArgumentsType(675, std::make_pair(eUINT32, eNONE)),     //GetGraphVariableInt
    Function_ArgumentsType(676, std::make_pair(eNONE, eNONE)),       //GetCurrentShoutVariation
    Function_ArgumentsType(678, std::make_pair(eFORMID, eNONE)),     //ShouldAttackKill
    Function_ArgumentsType(680, std::make_pair(eNONE, eNONE)),       //GetActivationHeight
    Function_ArgumentsType(681, std::make_pair(eUINT32, eNONE)),     //EPModSkillUsage_IsAdvancedSkill
    Function_ArgumentsType(682, std::make_pair(eFORMID, eNONE)),     //WornHasKeyword
    Function_ArgumentsType(683, std::make_pair(eNONE, eNONE)),       //GetPathingCurrentSpeed
    Function_ArgumentsType(684, std::make_pair(eUINT32, eNONE)),     //GetPathingCurrentSpeedAngle
    Function_ArgumentsType(691, std::make_pair(eFORMID, eNONE)),     //EPModSkillUsage_AdvancedObjectHasKeyword
    Function_ArgumentsType(692, std::make_pair(eFORMID, eNONE)),     //EPModSkillUsage_IsAdvancedAction
    Function_ArgumentsType(693, std::make_pair(eFORMID, eNONE)),     //EPMagic_SpellHasKeyword
    Function_ArgumentsType(694, std::make_pair(eNONE, eNONE)),       //GetNoBleedoutRecovery
    Function_ArgumentsType(696, std::make_pair(eUINT32, eNONE)),     //EPMagic_SpellHasSkill
    Function_ArgumentsType(697, std::make_pair(eFORMID, eNONE)),     //IsAttackType
    Function_ArgumentsType(698, std::make_pair(eNONE, eNONE)),       //IsAllowedToFly
    Function_ArgumentsType(699, std::make_pair(eFORMID, eNONE)),     //HasMagicEffectKeyword
    Function_ArgumentsType(700, std::make_pair(eNONE, eNONE)),       //IsCommandedActor
    Function_ArgumentsType(701, std::make_pair(eNONE, eNONE)),       //IsStaggered
    Function_ArgumentsType(702, std::make_pair(eNONE, eNONE)),       //IsRecoiling
    Function_ArgumentsType(703, std::make_pair(eNONE, eNONE)),       //IsExitingInteractionQuick
    Function_ArgumentsType(704, std::make_pair(eNONE, eNONE)),       //IsPathing
    Function_ArgumentsType(705, std::make_pair(eFORMID, eNONE)),     //GetShouldHelp
    Function_ArgumentsType(706, std::make_pair(eFORMID, eNONE)),     //HasBoundWeaponEquipped
    Function_ArgumentsType(707, std::make_pair(eFORMID, eNONE)),     //GetCombatTargetHasKeyword
    Function_ArgumentsType(709, std::make_pair(eNONE, eNONE)),       //GetCombatGroupMemberCount
    Function_ArgumentsType(710, std::make_pair(eNONE, eNONE)),       //IsIgnoringCombat
    Function_ArgumentsType(711, std::make_pair(eNONE, eNONE)),       //GetLightLevel
    Function_ArgumentsType(713, std::make_pair(eFORMID, eNONE)),     //SpellHasCastingPerk
    Function_ArgumentsType(714, std::make_pair(eNONE, eNONE)),       //IsBeingRidden
    Function_ArgumentsType(715, std::make_pair(eNONE, eNONE)),       //IsUndead
    Function_ArgumentsType(716, std::make_pair(eNONE, eNONE)),       //GetRealHoursPassed
    Function_ArgumentsType(718, std::make_pair(eNONE, eNONE)),       //IsUnlockedDoor
    Function_ArgumentsType(719, std::make_pair(eFORMID, eNONE)),     //IsHostileToActor
    Function_ArgumentsType(720, std::make_pair(eNONE, eNONE)),       //GetTargetHeight
    Function_ArgumentsType(721, std::make_pair(eNONE, eNONE)),       //IsPoison
    Function_ArgumentsType(722, std::make_pair(eFORMID, eNONE)),     //WornApparelHasKeywordCount
    Function_ArgumentsType(723, std::make_pair(eNONE, eNONE)),       //GetItemHealthPercent
    Function_ArgumentsType(724, std::make_pair(eNONE, eNONE)),       //EffectWasDualCast
    Function_ArgumentsType(725, std::make_pair(eNONE, eNONE)),       //GetKnockStateEnum
    Function_ArgumentsType(726, std::make_pair(eNONE, eNONE)),       //DoesNotExist
    Function_ArgumentsType(730, std::make_pair(eNONE, eNONE)),       //IsOnFlyingMount
    Function_ArgumentsType(731, std::make_pair(eNONE, eNONE)),       //CanFlyHere
    Function_ArgumentsType(732, std::make_pair(eNONE, eNONE)),       //IsFlyingMountPatrolQueued
    Function_ArgumentsType(733, std::make_pair(eNONE, eNONE)),       //IsFlyingMountFastTravelling
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
    Function_NameType(731, (char *)"CanFlyHere"),
    Function_NameType(153, (char *)"CanHaveFlames"),
    Function_NameType(127, (char *)"CanPayCrimeGold"),
    Function_NameType(497, (char *)"CanPayCrimeGold"),
    Function_NameType(607, (char *)"ChallengeLocked"),
    Function_NameType(726, (char *)"DoesNotExist"),
    Function_NameType(501, (char *)"EPAlchemyEffectHasKeyword"),
    Function_NameType(500, (char *)"EPAlchemyGetMakingPoison"),
    Function_NameType(693, (char *)"EPMagic_SpellHasKeyword"),
    Function_NameType(696, (char *)"EPMagic_SpellHasSkill"),
    Function_NameType(691, (char *)"EPModSkillUsage_AdvancedObjectHasKeyword"),
    Function_NameType(692, (char *)"EPModSkillUsage_IsAdvancedAction"),
    Function_NameType(681, (char *)"EPModSkillUsage_IsAdvancedSkill"),
    Function_NameType(660, (char *)"EPTemperingItemHasKeyword"),
    Function_NameType(659, (char *)"EPTemperingItemIsEnchanted"),
    Function_NameType(724, (char *)"EffectWasDualCast"),
    Function_NameType(414, (char *)"Exists"),
    Function_NameType(680, (char *)"GetActivationHeight"),
    Function_NameType(118, (char *)"GetActorAggroRadiusViolated"),
    Function_NameType(458, (char *)"GetActorCrimePlayerEnemy"),
    Function_NameType(460, (char *)"GetActorFactionPlayerEnemy"),
    Function_NameType(14, (char *)"GetActorValue"),
    Function_NameType(640, (char *)"GetActorValuePercent"),
    Function_NameType(554, (char *)"GetActorsInHigh"),
    Function_NameType(557, (char *)"GetActorsInHigh"),
    Function_NameType(61, (char *)"GetAlarmed"),
    Function_NameType(503, (char *)"GetAllowWorldInteractions"),
    Function_NameType(190, (char *)"GetAmountSoldStolen"),
    Function_NameType(8, (char *)"GetAngle"),
    Function_NameType(219, (char *)"GetAnimAction"),
    Function_NameType(81, (char *)"GetArmorRating"),
    Function_NameType(274, (char *)"GetArmorRatingUpperBody"),
    Function_NameType(656, (char *)"GetArrestedState"),
    Function_NameType(657, (char *)"GetArrestingActor"),
    Function_NameType(574, (char *)"GetAttackState"),
    Function_NameType(63, (char *)"GetAttacked"),
    Function_NameType(264, (char *)"GetBarterGold"),
    Function_NameType(277, (char *)"GetBaseActorValue"),
    Function_NameType(654, (char *)"GetBribeSuccess"),
    Function_NameType(396, (char *)"GetCauseofDeath"),
    Function_NameType(229, (char *)"GetClassDefaultMatch"),
    Function_NameType(41, (char *)"GetClothingValue"),
    Function_NameType(709, (char *)"GetCombatGroupMemberCount"),
    Function_NameType(707, (char *)"GetCombatTargetHasKeyword"),
    Function_NameType(488, (char *)"GetConcussed"),
    Function_NameType(489, (char *)"GetConcussed"),
    Function_NameType(122, (char *)"GetCrime"),
    Function_NameType(116, (char *)"GetCrimeGold"),
    Function_NameType(459, (char *)"GetCrimeGold"),
    Function_NameType(376, (char *)"GetCrimeGoldNonviolent"),
    Function_NameType(375, (char *)"GetCrimeGoldViolent"),
    Function_NameType(110, (char *)"GetCurrentAIPackage"),
    Function_NameType(143, (char *)"GetCurrentAIProcedure"),
    Function_NameType(571, (char *)"GetCurrentCastingType"),
    Function_NameType(572, (char *)"GetCurrentDeliveryType"),
    Function_NameType(676, (char *)"GetCurrentShoutVariation"),
    Function_NameType(18, (char *)"GetCurrentTime"),
    Function_NameType(148, (char *)"GetCurrentWeatherPercent"),
    Function_NameType(170, (char *)"GetDayOfWeek"),
    Function_NameType(499, (char *)"GetDaysInJail"),
    Function_NameType(46, (char *)"GetDead"),
    Function_NameType(84, (char *)"GetDeadCount"),
    Function_NameType(203, (char *)"GetDestroyed"),
    Function_NameType(470, (char *)"GetDestructionStage"),
    Function_NameType(471, (char *)"GetDestructionStage"),
    Function_NameType(45, (char *)"GetDetected"),
    Function_NameType(180, (char *)"GetDetectionLevel"),
    Function_NameType(434, (char *)"GetDialogEmotion"),
    Function_NameType(435, (char *)"GetDialogEmotionValue"),
    Function_NameType(436, (char *)"GetDialogueEmotionValue"),
    Function_NameType(35, (char *)"GetDisabled"),
    Function_NameType(39, (char *)"GetDisease"),
    Function_NameType(76, (char *)"GetDisposition"),
    Function_NameType(1, (char *)"GetDistance"),
    Function_NameType(215, (char *)"GetDoorDefaultOpen"),
    Function_NameType(182, (char *)"GetEquipped"),
    Function_NameType(597, (char *)"GetEquippedItemType"),
    Function_NameType(579, (char *)"GetEquippedShout"),
    Function_NameType(576, (char *)"GetEventData"),
    Function_NameType(410, (char *)"GetFactionCombatReaction"),
    Function_NameType(411, (char *)"GetFactionCombatReaction"),
    Function_NameType(73, (char *)"GetFactionRank"),
    Function_NameType(60, (char *)"GetFactionRankDifference"),
    Function_NameType(449, (char *)"GetFactionRelation"),
    Function_NameType(128, (char *)"GetFatiguePercentage"),
    Function_NameType(633, (char *)"GetFlyingState"),
    Function_NameType(288, (char *)"GetFriendHit"),
    Function_NameType(160, (char *)"GetFurnitureMarkerID"),
    Function_NameType(74, (char *)"GetGlobalValue"),
    Function_NameType(48, (char *)"GetGold"),
    Function_NameType(447, (char *)"GetGraphVariableFloat"),
    Function_NameType(675, (char *)"GetGraphVariableInt"),
    Function_NameType(415, (char *)"GetGroupMemberCount"),
    Function_NameType(416, (char *)"GetGroupTargetCount"),
    Function_NameType(417, (char *)"GetGroupTargetCount"),
    Function_NameType(381, (char *)"GetHasNote"),
    Function_NameType(382, (char *)"GetHasNote"),
    Function_NameType(99, (char *)"GetHeadingAngle"),
    Function_NameType(430, (char *)"GetHealthPercentage"),
    Function_NameType(431, (char *)"GetHealthPercentage"),
    Function_NameType(615, (char *)"GetHighestRelationshipRank"),
    Function_NameType(390, (char *)"GetHitLocation"),
    Function_NameType(318, (char *)"GetIdleDoneOnce"),
    Function_NameType(192, (char *)"GetIgnoreCrime"),
    Function_NameType(338, (char *)"GetIgnoreFriendlyHits"),
    Function_NameType(67, (char *)"GetInCell"),
    Function_NameType(230, (char *)"GetInCellParam"),
    Function_NameType(624, (char *)"GetInContainer"),
    Function_NameType(359, (char *)"GetInCurrentLoc"),
    Function_NameType(360, (char *)"GetInCurrentLocAlias"),
    Function_NameType(444, (char *)"GetInCurrentLocFormList"),
    Function_NameType(71, (char *)"GetInFaction"),
    Function_NameType(32, (char *)"GetInSameCell"),
    Function_NameType(652, (char *)"GetInSharedCrimeFaction"),
    Function_NameType(310, (char *)"GetInWorldspace"),
    Function_NameType(445, (char *)"GetInZone"),
    Function_NameType(533, (char *)"GetInfamy"),
    Function_NameType(535, (char *)"GetInfamyNonViolent"),
    Function_NameType(534, (char *)"GetInfamyViolent"),
    Function_NameType(655, (char *)"GetIntimidateSuccess"),
    Function_NameType(305, (char *)"GetInvestmentGold"),
    Function_NameType(91, (char *)"GetIsAlerted"),
    Function_NameType(566, (char *)"GetIsAliasRef"),
    Function_NameType(473, (char *)"GetIsAlignment"),
    Function_NameType(474, (char *)"GetIsAlignment"),
    Function_NameType(68, (char *)"GetIsClass"),
    Function_NameType(228, (char *)"GetIsClassDefault"),
    Function_NameType(646, (char *)"GetIsCrashLandRequest"),
    Function_NameType(64, (char *)"GetIsCreature"),
    Function_NameType(437, (char *)"GetIsCreatureType"),
    Function_NameType(438, (char *)"GetIsCreatureType"),
    Function_NameType(152, (char *)"GetIsCrimeFaction"),
    Function_NameType(161, (char *)"GetIsCurrentPackage"),
    Function_NameType(149, (char *)"GetIsCurrentWeather"),
    Function_NameType(567, (char *)"GetIsEditorLocAlias"),
    Function_NameType(565, (char *)"GetIsEditorLocation"),
    Function_NameType(594, (char *)"GetIsFlying"),
    Function_NameType(237, (char *)"GetIsGhost"),
    Function_NameType(647, (char *)"GetIsHastyLandRequest"),
    Function_NameType(72, (char *)"GetIsID"),
    Function_NameType(645, (char *)"GetIsInjured"),
    Function_NameType(519, (char *)"GetIsLockBroken"),
    Function_NameType(432, (char *)"GetIsObjectType"),
    Function_NameType(433, (char *)"GetIsObjectType"),
    Function_NameType(254, (char *)"GetIsPlayableRace"),
    Function_NameType(224, (char *)"GetIsPlayerBirthsign"),
    Function_NameType(69, (char *)"GetIsRace"),
    Function_NameType(136, (char *)"GetIsReference"),
    Function_NameType(70, (char *)"GetIsSex"),
    Function_NameType(246, (char *)"GetIsUsedItem"),
    Function_NameType(479, (char *)"GetIsUsedItemEquipType"),
    Function_NameType(247, (char *)"GetIsUsedItemType"),
    Function_NameType(426, (char *)"GetIsVoiceType"),
    Function_NameType(47, (char *)"GetItemCount"),
    Function_NameType(723, (char *)"GetItemHealthPercent"),
    Function_NameType(608, (char *)"GetKeywordDataForAlias"),
    Function_NameType(651, (char *)"GetKeywordDataForCurrentLocation"),
    Function_NameType(606, (char *)"GetKeywordDataForLocation"),
    Function_NameType(465, (char *)"GetKeywordItemCount"),
    Function_NameType(495, (char *)"GetKillingBlowLimb"),
    Function_NameType(496, (char *)"GetKillingBlowLimb"),
    Function_NameType(725, (char *)"GetKnockStateEnum"),
    Function_NameType(107, (char *)"GetKnockedState"),
    Function_NameType(642, (char *)"GetLastBumpDirection"),
    Function_NameType(508, (char *)"GetLastHitCritical"),
    Function_NameType(510, (char *)"GetLastHitCritical"),
    Function_NameType(367, (char *)"GetLastPlayerAction"),
    Function_NameType(80, (char *)"GetLevel"),
    Function_NameType(711, (char *)"GetLightLevel"),
    Function_NameType(27, (char *)"GetLineOfSight"),
    Function_NameType(601, (char *)"GetLocAliasRefTypeAliveCount"),
    Function_NameType(600, (char *)"GetLocAliasRefTypeDeadCount"),
    Function_NameType(598, (char *)"GetLocationAliasCleared"),
    Function_NameType(250, (char *)"GetLocationCleared"),
    Function_NameType(65, (char *)"GetLockLevel"),
    Function_NameType(5, (char *)"GetLocked"),
    Function_NameType(616, (char *)"GetLowestRelationshipRank"),
    Function_NameType(491, (char *)"GetMapMarkerVisible"),
    Function_NameType(492, (char *)"GetMapMarkerVisible"),
    Function_NameType(589, (char *)"GetMovementDirection"),
    Function_NameType(623, (char *)"GetMovementSpeed"),
    Function_NameType(694, (char *)"GetNoBleedoutRecovery"),
    Function_NameType(320, (char *)"GetNoRumors"),
    Function_NameType(612, (char *)"GetNumericPackageData"),
    Function_NameType(420, (char *)"GetObjectiveCompleted"),
    Function_NameType(421, (char *)"GetObjectiveDisplayed"),
    Function_NameType(255, (char *)"GetOffersServicesNow"),
    Function_NameType(157, (char *)"GetOpenState"),
    Function_NameType(193, (char *)"GetPCExpelled"),
    Function_NameType(199, (char *)"GetPCFactionAttack"),
    Function_NameType(195, (char *)"GetPCFactionMurder"),
    Function_NameType(197, (char *)"GetPCFactionSteal"),
    Function_NameType(201, (char *)"GetPCFactionSubmitAuthority"),
    Function_NameType(249, (char *)"GetPCFame"),
    Function_NameType(132, (char *)"GetPCInFaction"),
    Function_NameType(251, (char *)"GetPCInfamy"),
    Function_NameType(129, (char *)"GetPCIsClass"),
    Function_NameType(130, (char *)"GetPCIsRace"),
    Function_NameType(131, (char *)"GetPCIsSex"),
    Function_NameType(312, (char *)"GetPCMiscStat"),
    Function_NameType(683, (char *)"GetPathingCurrentSpeed"),
    Function_NameType(684, (char *)"GetPathingCurrentSpeedAngle"),
    Function_NameType(620, (char *)"GetPathingTargetAngleOffset"),
    Function_NameType(619, (char *)"GetPathingTargetOffset"),
    Function_NameType(621, (char *)"GetPathingTargetSpeed"),
    Function_NameType(622, (char *)"GetPathingTargetSpeedAngle"),
    Function_NameType(494, (char *)"GetPermanentActorValue"),
    Function_NameType(225, (char *)"GetPersuasionNumber"),
    Function_NameType(427, (char *)"GetPlantedExplosive"),
    Function_NameType(428, (char *)"GetPlantedExplosive"),
    Function_NameType(98, (char *)"GetPlayerControlsDisabled"),
    Function_NameType(462, (char *)"GetPlayerGrabbedRef"),
    Function_NameType(362, (char *)"GetPlayerHasLastRiddenHorse"),
    Function_NameType(365, (char *)"GetPlayerInSEWorld"),
    Function_NameType(480, (char *)"GetPlayerName"),
    Function_NameType(453, (char *)"GetPlayerTeammate"),
    Function_NameType(454, (char *)"GetPlayerTeammate"),
    Function_NameType(455, (char *)"GetPlayerTeammateCount"),
    Function_NameType(6, (char *)"GetPos"),
    Function_NameType(543, (char *)"GetQuestCompleted"),
    Function_NameType(546, (char *)"GetQuestCompleted"),
    Function_NameType(56, (char *)"GetQuestRunning"),
    Function_NameType(79, (char *)"GetQuestVariable"),
    Function_NameType(77, (char *)"GetRandomPercent"),
    Function_NameType(716, (char *)"GetRealHoursPassed"),
    Function_NameType(592, (char *)"GetRefTypeAliveCount"),
    Function_NameType(591, (char *)"GetRefTypeDeadCount"),
    Function_NameType(403, (char *)"GetRelationshipRank"),
    Function_NameType(584, (char *)"GetRelativeAngle"),
    Function_NameType(664, (char *)"GetReplacedItemType"),
    Function_NameType(573, (char *)"GetReputation"),
    Function_NameType(575, (char *)"GetReputationThreshold"),
    Function_NameType(244, (char *)"GetRestrained"),
    Function_NameType(24, (char *)"GetScale"),
    Function_NameType(53, (char *)"GetScriptVariable"),
    Function_NameType(12, (char *)"GetSecondsPassed"),
    Function_NameType(66, (char *)"GetShouldAttack"),
    Function_NameType(705, (char *)"GetShouldHelp"),
    Function_NameType(159, (char *)"GetSitting"),
    Function_NameType(49, (char *)"GetSleeping"),
    Function_NameType(552, (char *)"GetSpellUsageNum"),
    Function_NameType(58, (char *)"GetStage"),
    Function_NameType(59, (char *)"GetStageDone"),
    Function_NameType(11, (char *)"GetStartingAngle"),
    Function_NameType(10, (char *)"GetStartingPos"),
    Function_NameType(373, (char *)"GetStolenItemValue"),
    Function_NameType(366, (char *)"GetStolenItemValueNoCrime"),
    Function_NameType(50, (char *)"GetTalkedToPC"),
    Function_NameType(172, (char *)"GetTalkedToPCParam"),
    Function_NameType(720, (char *)"GetTargetHeight"),
    Function_NameType(477, (char *)"GetThreatRatio"),
    Function_NameType(478, (char *)"GetThreatRatio"),
    Function_NameType(361, (char *)"GetTimeDead"),
    Function_NameType(315, (char *)"GetTotalPersuasionNumber"),
    Function_NameType(144, (char *)"GetTrespassWarningLevel"),
    Function_NameType(242, (char *)"GetUnconscious"),
    Function_NameType(259, (char *)"GetUsedItemActivate"),
    Function_NameType(258, (char *)"GetUsedItemLevel"),
    Function_NameType(517, (char *)"GetVATSBackAreaFree"),
    Function_NameType(524, (char *)"GetVATSBackTargetVisible"),
    Function_NameType(527, (char *)"GetVATSBackTargetVisible"),
    Function_NameType(518, (char *)"GetVATSFrontAreaFree"),
    Function_NameType(525, (char *)"GetVATSFrontTargetVisible"),
    Function_NameType(516, (char *)"GetVATSLeftAreaFree"),
    Function_NameType(523, (char *)"GetVATSLeftTargetVisible"),
    Function_NameType(526, (char *)"GetVATSLeftTargetVisible"),
    Function_NameType(515, (char *)"GetVATSRightAreaFree"),
    Function_NameType(522, (char *)"GetVATSRightTargetVisible"),
    Function_NameType(407, (char *)"GetVATSValue"),
    Function_NameType(629, (char *)"GetVMQuestVariable"),
    Function_NameType(630, (char *)"GetVMScriptVariable"),
    Function_NameType(40, (char *)"GetVampire"),
    Function_NameType(226, (char *)"GetVampireFeed"),
    Function_NameType(235, (char *)"GetVatsTargetHeight"),
    Function_NameType(446, (char *)"GetVelocity"),
    Function_NameType(142, (char *)"GetWalkSpeed"),
    Function_NameType(0, (char *)"GetWantBlocking"),
    Function_NameType(108, (char *)"GetWeaponAnimType"),
    Function_NameType(109, (char *)"GetWeaponSkillType"),
    Function_NameType(147, (char *)"GetWindSpeed"),
    Function_NameType(639, (char *)"GetWithinDistance"),
    Function_NameType(325, (char *)"GetWithinPackageLocation"),
    Function_NameType(530, (char *)"GetXPForNextLevel"),
    Function_NameType(617, (char *)"HasAssociationTypeAny"),
    Function_NameType(706, (char *)"HasBoundWeaponEquipped"),
    Function_NameType(570, (char *)"HasEquippedSpell"),
    Function_NameType(618, (char *)"HasFamilyRelationshipAny"),
    Function_NameType(154, (char *)"HasFlames"),
    Function_NameType(560, (char *)"HasKeyword"),
    Function_NameType(555, (char *)"HasLoaded3D"),
    Function_NameType(558, (char *)"HasLoaded3D"),
    Function_NameType(214, (char *)"HasMagicEffect"),
    Function_NameType(699, (char *)"HasMagicEffectKeyword"),
    Function_NameType(261, (char *)"HasParentRelationship"),
    Function_NameType(448, (char *)"HasPerk"),
    Function_NameType(561, (char *)"HasRefType"),
    Function_NameType(181, (char *)"HasSameEditorLocAsRefAlias"),
    Function_NameType(378, (char *)"HasShout"),
    Function_NameType(636, (char *)"HasTwoHandedWeaponEquipped"),
    Function_NameType(227, (char *)"HasVampireFed"),
    Function_NameType(353, (char *)"IsActor"),
    Function_NameType(314, (char *)"IsActorAVictim"),
    Function_NameType(313, (char *)"IsActorEvil"),
    Function_NameType(306, (char *)"IsActorUsingATorch"),
    Function_NameType(698, (char *)"IsAllowedToFly"),
    Function_NameType(697, (char *)"IsAttackType"),
    Function_NameType(672, (char *)"IsAttacking"),
    Function_NameType(714, (char *)"IsBeingRidden"),
    Function_NameType(580, (char *)"IsBleedingOut"),
    Function_NameType(569, (char *)"IsBlocking"),
    Function_NameType(402, (char *)"IsBribedbyPlayer"),
    Function_NameType(487, (char *)"IsCarryable"),
    Function_NameType(632, (char *)"IsCasting"),
    Function_NameType(280, (char *)"IsCellOwner"),
    Function_NameType(577, (char *)"IsCloserToAThanB"),
    Function_NameType(267, (char *)"IsCloudy"),
    Function_NameType(513, (char *)"IsCombatTarget"),
    Function_NameType(700, (char *)"IsCommandedActor"),
    Function_NameType(150, (char *)"IsContinuingPackagePCNear"),
    Function_NameType(163, (char *)"IsCurrentFurnitureObj"),
    Function_NameType(162, (char *)"IsCurrentFurnitureRef"),
    Function_NameType(595, (char *)"IsCurrentSpell"),
    Function_NameType(627, (char *)"IsDualCasting"),
    Function_NameType(631, (char *)"IsEnteringInteractionQuick"),
    Function_NameType(354, (char *)"IsEssential"),
    Function_NameType(637, (char *)"IsExitingInstant"),
    Function_NameType(703, (char *)"IsExitingInteractionQuick"),
    Function_NameType(106, (char *)"IsFacingUp"),
    Function_NameType(733, (char *)"IsFlyingMountFastTravelling"),
    Function_NameType(732, (char *)"IsFlyingMountPatrolQueued"),
    Function_NameType(613, (char *)"IsFurnitureAnimType"),
    Function_NameType(614, (char *)"IsFurnitureEntryType"),
    Function_NameType(547, (char *)"IsGoreDisabled"),
    Function_NameType(123, (char *)"IsGreetingPlayer"),
    Function_NameType(125, (char *)"IsGuard"),
    Function_NameType(586, (char *)"IsHardcore"),
    Function_NameType(282, (char *)"IsHorseStolen"),
    Function_NameType(719, (char *)"IsHostileToActor"),
    Function_NameType(112, (char *)"IsIdlePlaying"),
    Function_NameType(710, (char *)"IsIgnoringCombat"),
    Function_NameType(289, (char *)"IsInCombat"),
    Function_NameType(528, (char *)"IsInCriticalStage"),
    Function_NameType(531, (char *)"IsInCriticalStage"),
    Function_NameType(332, (char *)"IsInDangerousWater"),
    Function_NameType(635, (char *)"IsInFavorState"),
    Function_NameType(638, (char *)"IsInFriendStatewithPlayer"),
    Function_NameType(644, (char *)"IsInFurnitureState"),
    Function_NameType(300, (char *)"IsInInterior"),
    Function_NameType(372, (char *)"IsInList"),
    Function_NameType(146, (char *)"IsInMyOwnedCell"),
    Function_NameType(603, (char *)"IsInSameCurrentLocAsRef"),
    Function_NameType(604, (char *)"IsInSameCurrentLocAsRefAlias"),
    Function_NameType(590, (char *)"IsInScene"),
    Function_NameType(408, (char *)"IsKiller"),
    Function_NameType(409, (char *)"IsKillerObject"),
    Function_NameType(674, (char *)"IsLastHostileActor"),
    Function_NameType(450, (char *)"IsLastIdlePlayed"),
    Function_NameType(451, (char *)"IsLastIdlePlayed"),
    Function_NameType(285, (char *)"IsLeftUp"),
    Function_NameType(397, (char *)"IsLimbGone"),
    Function_NameType(650, (char *)"IsLinkedTo"),
    Function_NameType(626, (char *)"IsLocAliasLoaded"),
    Function_NameType(625, (char *)"IsLocationLoaded"),
    Function_NameType(25, (char *)"IsMoving"),
    Function_NameType(611, (char *)"IsNullPackageData"),
    Function_NameType(730, (char *)"IsOnFlyingMount"),
    Function_NameType(278, (char *)"IsOwner"),
    Function_NameType(391, (char *)"IsPC1stPerson"),
    Function_NameType(392, (char *)"IsPC1stPerson"),
    Function_NameType(176, (char *)"IsPCAMurderer"),
    Function_NameType(175, (char *)"IsPCSleeping"),
    Function_NameType(520, (char *)"IsPS3"),
    Function_NameType(704, (char *)"IsPathing"),
    Function_NameType(368, (char *)"IsPlayerActionActive"),
    Function_NameType(463, (char *)"IsPlayerGrabbedRef"),
    Function_NameType(464, (char *)"IsPlayerGrabbedRef"),
    Function_NameType(171, (char *)"IsPlayerInJail"),
    Function_NameType(117, (char *)"IsPlayerInRegion"),
    Function_NameType(358, (char *)"IsPlayerMovingIntoNewSpace"),
    Function_NameType(339, (char *)"IsPlayersLastRiddenHorse"),
    Function_NameType(266, (char *)"IsPleasant"),
    Function_NameType(721, (char *)"IsPoison"),
    Function_NameType(673, (char *)"IsPowerAttacking"),
    Function_NameType(476, (char *)"IsProtected"),
    Function_NameType(62, (char *)"IsRaining"),
    Function_NameType(702, (char *)"IsRecoiling"),
    Function_NameType(327, (char *)"IsRidingHorse"),
    Function_NameType(287, (char *)"IsRunning"),
    Function_NameType(550, (char *)"IsSceneActionComplete"),
    Function_NameType(429, (char *)"IsScenePackageRunning"),
    Function_NameType(248, (char *)"IsScenePlaying"),
    Function_NameType(103, (char *)"IsShieldOut"),
    Function_NameType(286, (char *)"IsSneaking"),
    Function_NameType(75, (char *)"IsSnowing"),
    Function_NameType(223, (char *)"IsSpellTarget"),
    Function_NameType(568, (char *)"IsSprinting"),
    Function_NameType(701, (char *)"IsStaggered"),
    Function_NameType(185, (char *)"IsSwimming"),
    Function_NameType(141, (char *)"IsTalking"),
    Function_NameType(370, (char *)"IsTalkingActivatorActor"),
    Function_NameType(265, (char *)"IsTimePassing"),
    Function_NameType(102, (char *)"IsTorchOut"),
    Function_NameType(145, (char *)"IsTrespassing"),
    Function_NameType(329, (char *)"IsTurnArrest"),
    Function_NameType(26, (char *)"IsTurning"),
    Function_NameType(715, (char *)"IsUndead"),
    Function_NameType(641, (char *)"IsUnique"),
    Function_NameType(718, (char *)"IsUnlockedDoor"),
    Function_NameType(111, (char *)"IsWaiting"),
    Function_NameType(602, (char *)"IsWardState"),
    Function_NameType(262, (char *)"IsWarningAbout"),
    Function_NameType(304, (char *)"IsWaterObject"),
    Function_NameType(398, (char *)"IsWeaponInList"),
    Function_NameType(399, (char *)"IsWeaponInList"),
    Function_NameType(101, (char *)"IsWeaponOut"),
    Function_NameType(263, (char *)"IsWeaponOut"),
    Function_NameType(521, (char *)"IsWin32"),
    Function_NameType(309, (char *)"IsXBox"),
    Function_NameType(104, (char *)"IsYielding"),
    Function_NameType(610, (char *)"LocAliasHasKeyword"),
    Function_NameType(605, (char *)"LocAliasIsLocation"),
    Function_NameType(562, (char *)"LocationHasKeyword"),
    Function_NameType(563, (char *)"LocationHasRefType"),
    Function_NameType(36, (char *)"MenuMode"),
    Function_NameType(42, (char *)"SameFaction"),
    Function_NameType(133, (char *)"SameFactionAsPC"),
    Function_NameType(43, (char *)"SameRace"),
    Function_NameType(134, (char *)"SameRaceAsPC"),
    Function_NameType(44, (char *)"SameSex"),
    Function_NameType(135, (char *)"SameSexAsPC"),
    Function_NameType(678, (char *)"ShouldAttackKill"),
    Function_NameType(713, (char *)"SpellHasCastingPerk"),
    Function_NameType(596, (char *)"SpellHasKeyword"),
    Function_NameType(323, (char *)"WhichServiceMenu"),
    Function_NameType(722, (char *)"WornApparelHasKeywordCount"),
    Function_NameType(682, (char *)"WornHasKeyword"),
    };

Function_NameType Comparison_NameInit[] =
    {
    Function_NameType(0x00,(char *)"Equal to"),
    Function_NameType(0x01,(char *)"Equal to / Or"),
    Function_NameType(0x02,(char *)"Equal to / Run on target"),
    Function_NameType(0x03,(char *)"Equal to / Or, Run on target"),
    Function_NameType(0x04,(char *)"Equal to / Use global"),
    Function_NameType(0x05,(char *)"Equal to / Or, Use global"),
    Function_NameType(0x06,(char *)"Equal to / Run on target, Use global"),
    Function_NameType(0x07,(char *)"Equal to / Or, Run on target, Use global"),
    Function_NameType(0x20,(char *)"Not equal to"),
    Function_NameType(0x21,(char *)"Not equal to / Or"),
    Function_NameType(0x22,(char *)"Not equal to / Run on target"),
    Function_NameType(0x23,(char *)"Not equal to / Or, Run on target"),
    Function_NameType(0x24,(char *)"Not equal to / Use global"),
    Function_NameType(0x25,(char *)"Not equal to / Or, Use global"),
    Function_NameType(0x26,(char *)"Not equal to / Run on target, Use global"),
    Function_NameType(0x27,(char *)"Not equal to / Or, Run on target, Use global"),
    Function_NameType(0x40,(char *)"Greater than"),
    Function_NameType(0x41,(char *)"Greater than / Or"),
    Function_NameType(0x42,(char *)"Greater than / Run on target"),
    Function_NameType(0x43,(char *)"Greater than / Or, Run on target"),
    Function_NameType(0x44,(char *)"Greater than / Use global"),
    Function_NameType(0x45,(char *)"Greater than / Or, Use global"),
    Function_NameType(0x46,(char *)"Greater than / Run on target, Use global"),
    Function_NameType(0x47,(char *)"Greater than / Or, Run on target, Use global"),
    Function_NameType(0x60,(char *)"Greater than or equal to"),
    Function_NameType(0x61,(char *)"Greater than or equal to / Or"),
    Function_NameType(0x62,(char *)"Greater than or equal to / Run on target"),
    Function_NameType(0x63,(char *)"Greater than or equal to / Or, Run on target"),
    Function_NameType(0x64,(char *)"Greater than or equal to / Use global"),
    Function_NameType(0x65,(char *)"Greater than or equal to / Or, Use global"),
    Function_NameType(0x66,(char *)"Greater than or equal to / Run on target, Use global"),
    Function_NameType(0x67,(char *)"Greater than or equal to / Or, Run on target, Use global"),
    Function_NameType(0x80,(char *)"Less than"),
    Function_NameType(0x81,(char *)"Less than / Or"),
    Function_NameType(0x82,(char *)"Less than / Run on target"),
    Function_NameType(0x83,(char *)"Less than / Or, Run on target"),
    Function_NameType(0x84,(char *)"Less than / Use global"),
    Function_NameType(0x85,(char *)"Less than / Or, Use global"),
    Function_NameType(0x86,(char *)"Less than / Run on target, Use global"),
    Function_NameType(0x87,(char *)"Less than / Or, Run on target, Use global"),
    Function_NameType(0xA0,(char *)"Less than or equal to"),
    Function_NameType(0xA1,(char *)"Less than or equal to / Or"),
    Function_NameType(0xA2,(char *)"Less than or equal to / Run on target"),
    Function_NameType(0xA3,(char *)"Less than or equal to / Or, Run on target"),
    Function_NameType(0xA4,(char *)"Less than or equal to / Use global"),
    Function_NameType(0xA5,(char *)"Less than or equal to / Or, Use global"),
    Function_NameType(0xA6,(char *)"Less than or equal to / Run on target, Use global"),
    Function_NameType(0xA7,(char *)"Less than or equal to / Or, Run on target, Use global")
    };

Function_NameType IDLEGroup_NameInit[] =
    {
    Function_NameType(0x80,(char *)"Lower Body"),
    Function_NameType(0x00,(char *)"Lower Body, Must return a file"),
    Function_NameType(0x81,(char *)"Left Arm"),
    Function_NameType(0x01,(char *)"Left Arm, Must return a file"),
    Function_NameType(0x82,(char *)"Left Hand"),
    Function_NameType(0x02,(char *)"Left Hand, Must return a file"),
    Function_NameType(0x83,(char *)"Right Arm"),
    Function_NameType(0x03,(char *)"Right Arm, Must return a file"),
    Function_NameType(0x84,(char *)"Special Idle"),
    Function_NameType(0x04,(char *)"Special Idle, Must return a file"),
    Function_NameType(0x85,(char *)"Whole Body"),
    Function_NameType(0x05,(char *)"Whole Body, Must return a file"),
    Function_NameType(0x86,(char *)"Upper Body"),
    Function_NameType(0x06,(char *)"Upper Body, Must return a file"),
    };

Function_NameType PACKAIType_NameInit[] =
    {
    Function_NameType(0,(char *)"Find"),
    Function_NameType(1,(char *)"Follow"),
    Function_NameType(2,(char *)"Escort"),
    Function_NameType(3,(char *)"Eat"),
    Function_NameType(4,(char *)"Sleep"),
    Function_NameType(5,(char *)"Wander"),
    Function_NameType(6,(char *)"Travel"),
    Function_NameType(7,(char *)"Accompany"),
    Function_NameType(8,(char *)"Use item at"),
    Function_NameType(9,(char *)"Ambush"),
    Function_NameType(10,(char *)"Flee not combat"),
    Function_NameType(11,(char *)"Cast magic")
    };

Function_NameType PACKLocType_NameInit[] =
    {
    Function_NameType(0,(char *)"Near reference"),
    Function_NameType(1,(char *)"In cell"),
    Function_NameType(2,(char *)"Near current location"),
    Function_NameType(3,(char *)"Near editor location"),
    Function_NameType(4,(char *)"Object ID"),
    Function_NameType(5,(char *)"Object type")
    };

Function_NameType PACKTargetType_NameInit[] =
    {
    Function_NameType(0,(char *)"Specific reference"),
    Function_NameType(1,(char *)"Object ID"),
    Function_NameType(2,(char *)"Object type")
    };

Function_NameType HardCodedFormID_EditorIDInit[] =
    {
    Function_NameType(0x0001,(char *)"DoorMarker"),
    Function_NameType(0x0002,(char *)"TravelMarker"),
    Function_NameType(0x0003,(char *)"NorthMarker"),
    Function_NameType(0x0004,(char *)"PrisonMarker"),
    Function_NameType(0x0005,(char *)"DivineMarker"),
    Function_NameType(0x0006,(char *)"TempleMarker"),
    Function_NameType(0x0007,(char *)"Player"),
    Function_NameType(0x000A,(char *)"Lockpick"),
    Function_NameType(0x000B,(char *)"SkeletonKey"),
    Function_NameType(0x000C,(char *)"RepairHammer"),
    Function_NameType(0x000E,(char *)"LootBag"),
    Function_NameType(0x000F,(char *)"Gold001"),
    Function_NameType(0x0010,(char *)"MapMarker"),
    Function_NameType(0x0011,(char *)"StolenGoods"),
    Function_NameType(0x0012,(char *)"HorseMarker"),
    Function_NameType(0x0013,(char *)"CreatureFaction"),
    Function_NameType(0x0014,(char *)"PlayerRef"),
    Function_NameType(0x0015,(char *)"JailPants"),
    Function_NameType(0x0016,(char *)"JailShoes"),
    Function_NameType(0x0017,(char *)"JailShirt"),
    Function_NameType(0x0018,(char *)"DefaultWater"),
    Function_NameType(0x0019,(char *)"VampireRace"),
    Function_NameType(0x001A,(char *)"eyeReanimate"),
    Function_NameType(0x001E,(char *)"FlameNode0"),
    Function_NameType(0x001F,(char *)"FlameNode1"),
    Function_NameType(0x0020,(char *)"FlameNode2"),
    Function_NameType(0x0021,(char *)"FlameNode3"),
    Function_NameType(0x0022,(char *)"FlameNode4"),
    Function_NameType(0x0023,(char *)"FlameNode5"),
    Function_NameType(0x0024,(char *)"FlameNode6"),
    Function_NameType(0x0025,(char *)"FlameNode7"),
    Function_NameType(0x0026,(char *)"FlameNode8"),
    Function_NameType(0x0027,(char *)"FlameNode9"),
    Function_NameType(0x0028,(char *)"FlameNode10"),
    Function_NameType(0x0029,(char *)"FlameNode11"),
    Function_NameType(0x002A,(char *)"FlameNode12"),
    Function_NameType(0x002B,(char *)"FlameNode13"),
    Function_NameType(0x002C,(char *)"FlameNode14"),
    Function_NameType(0x002D,(char *)"FlameNode15"),
    Function_NameType(0x002E,(char *)"FlameNode16"),
    Function_NameType(0x002F,(char *)"FlameNode17"),
    Function_NameType(0x0030,(char *)"FlameNode18"),
    Function_NameType(0x0031,(char *)"FlameNode19"),
    Function_NameType(0x0032,(char *)"FlameNode20"),
    Function_NameType(0x0034,(char *)"XMarkerHeading"),
    Function_NameType(0x0035,(char *)"GameYear"),
    Function_NameType(0x0036,(char *)"GameMonth"),
    Function_NameType(0x0037,(char *)"GameDay"),
    Function_NameType(0x0038,(char *)"GameHour"),
    Function_NameType(0x0039,(char *)"GameDaysPassed"),
    Function_NameType(0x003A,(char *)"TimeScale"),
    Function_NameType(0x003B,(char *)"XMarker"),
    Function_NameType(0x003C,(char *)"Tamriel"),
    Function_NameType(0x003D,(char *)"SkillArmorer"),
    Function_NameType(0x003E,(char *)"SkillAthletics"),
    Function_NameType(0x003F,(char *)"SkillBlade"),
    Function_NameType(0x0040,(char *)"SkillBlock"),
    Function_NameType(0x0041,(char *)"SkillBlunt"),
    Function_NameType(0x0042,(char *)"SkillHandToHand"),
    Function_NameType(0x0043,(char *)"SkillHeavyArmor"),
    Function_NameType(0x0044,(char *)"SkillAlchemy"),
    Function_NameType(0x0045,(char *)"SkillAlteration"),
    Function_NameType(0x0046,(char *)"SkillConjuration"),
    Function_NameType(0x0047,(char *)"SkillDestruction"),
    Function_NameType(0x0048,(char *)"SkillIllusion"),
    Function_NameType(0x0049,(char *)"SkillMysticism"),
    Function_NameType(0x004A,(char *)"SkillRestoration"),
    Function_NameType(0x004B,(char *)"SkillAcrobatics"),
    Function_NameType(0x004C,(char *)"SkillLightArmor"),
    Function_NameType(0x004D,(char *)"SkillMarksman"),
    Function_NameType(0x004E,(char *)"SkillMercantile"),
    Function_NameType(0x004F,(char *)"SkillSecurity"),
    Function_NameType(0x0050,(char *)"SkillSneak"),
    Function_NameType(0x0051,(char *)"SkillSpeechcraft"),
    Function_NameType(0x0064,(char *)"FurnitureMarker01"),
    Function_NameType(0x0065,(char *)"FurnitureMarker02"),
    Function_NameType(0x0066,(char *)"FurnitureMarker03"),
    Function_NameType(0x0067,(char *)"FurnitureMarker04"),
    Function_NameType(0x0068,(char *)"FurnitureMarker05"),
    Function_NameType(0x0069,(char *)"FurnitureMarker06"),
    Function_NameType(0x006A,(char *)"FurnitureMarker07"),
    Function_NameType(0x006B,(char *)"FurnitureMarker08"),
    Function_NameType(0x006C,(char *)"FurnitureMarker09"),
    Function_NameType(0x006D,(char *)"FurnitureMarker10"),
    Function_NameType(0x006E,(char *)"FurnitureMarker11"),
    Function_NameType(0x006F,(char *)"FurnitureMarker12"),
    Function_NameType(0x0070,(char *)"FurnitureMarker13"),
    Function_NameType(0x0071,(char *)"FurnitureMarker14"),
    Function_NameType(0x0072,(char *)"FurnitureMarker15"),
    Function_NameType(0x0073,(char *)"FurnitureMarker16"),
    Function_NameType(0x0074,(char *)"FurnitureMarker17"),
    Function_NameType(0x0075,(char *)"FurnitureMarker18"),
    Function_NameType(0x0076,(char *)"FurnitureMarker19"),
    Function_NameType(0x0077,(char *)"FurnitureMarker20"),
    Function_NameType(0x00AA,(char *)"ADMIREHATE"),
    Function_NameType(0x00AB,(char *)"ADMIRELOVE"),
    Function_NameType(0x00AC,(char *)"ADMIRELIKE"),
    Function_NameType(0x00AD,(char *)"ADMIREDISLIKE"),
    Function_NameType(0x00AE,(char *)"COERCEHATE"),
    Function_NameType(0x00AF,(char *)"COERCELOVE"),
    Function_NameType(0x00B0,(char *)"COERCELIKE"),
    Function_NameType(0x00B1,(char *)"COERCEDISLIKE"),
    Function_NameType(0x00B2,(char *)"BOASTHATE"),
    Function_NameType(0x00B3,(char *)"BOASTLOVE"),
    Function_NameType(0x00B4,(char *)"BOASTLIKE"),
    Function_NameType(0x00B5,(char *)"BOASTDISLIKE"),
    Function_NameType(0x00B6,(char *)"JOKEHATE"),
    Function_NameType(0x00B7,(char *)"JOKELOVE"),
    Function_NameType(0x00B8,(char *)"JOKELIKE"),
    Function_NameType(0x00B9,(char *)"JOKEDISLIKE"),
    Function_NameType(0x00BA,(char *)"BRIBE"),
    Function_NameType(0x00BB,(char *)"PERSUASIONENTER"),
    Function_NameType(0x00BC,(char *)"PERSUASIONEXIT"),
    Function_NameType(0x00C8,(char *)"GREETING"),
    Function_NameType(0x00D2,(char *)"HELLO"),
    Function_NameType(0x00D3,(char *)"ANY"),
    Function_NameType(0x00D4,(char *)"GOODBYE"),
    Function_NameType(0x00D5,(char *)"IdleChatter"),
    Function_NameType(0x00D6,(char *)"SPELLHELP"),
    Function_NameType(0x00D7,(char *)"INFOGENERAL"),
    Function_NameType(0x00DC,(char *)"Attack"),
    Function_NameType(0x00DD,(char *)"Hit"),
    Function_NameType(0x00DE,(char *)"Flee"),
    Function_NameType(0x00DF,(char *)"Steal"),
    Function_NameType(0x00E0,(char *)"Trespass"),
    Function_NameType(0x00E1,(char *)"Yield"),
    Function_NameType(0x00E2,(char *)"AcceptYield"),
    Function_NameType(0x00E3,(char *)"Pickpocket"),
    Function_NameType(0x00E4,(char *)"Assault"),
    Function_NameType(0x00E5,(char *)"Murder"),
    Function_NameType(0x00E6,(char *)"PowerAttack"),
    Function_NameType(0x00E7,(char *)"AssaultNoCrime"),
    Function_NameType(0x00E8,(char *)"MurderNoCrime"),
    Function_NameType(0x00E9,(char *)"PickpocketNoCrime"),
    Function_NameType(0x00EA,(char *)"StealNoCrime"),
    Function_NameType(0x00EB,(char *)"TrespassNoCrime"),
    Function_NameType(0x00F0,(char *)"AdmireSuccess"),
    Function_NameType(0x00F1,(char *)"AdmireFail"),
    Function_NameType(0x00F2,(char *)"AdmireNeutral"),
    Function_NameType(0x00F3,(char *)"TauntSuccess"),
    Function_NameType(0x00F4,(char *)"TauntFail"),
    Function_NameType(0x00F5,(char *)"TauntNeutral"),
    Function_NameType(0x00F6,(char *)"BoastSuccess"),
    Function_NameType(0x00F7,(char *)"BoastFail"),
    Function_NameType(0x00F8,(char *)"BoastNeutral"),
    Function_NameType(0x00F9,(char *)"JokeSuccess"),
    Function_NameType(0x00FA,(char *)"JokeFail"),
    Function_NameType(0x00FB,(char *)"JokeNeutral"),
    Function_NameType(0x00FC,(char *)"BribeSuccess"),
    Function_NameType(0x00FD,(char *)"BribeFail"),
    Function_NameType(0x00FE,(char *)"DemandSuccess"),
    Function_NameType(0x00FF,(char *)"DemandFail"),
    Function_NameType(0x0100,(char *)"DemandNoMoney"),
    Function_NameType(0x0101,(char *)"DemandNoMoreCircle"),
    Function_NameType(0x0102,(char *)"BribeNoMoreCircle"),
    Function_NameType(0x0103,(char *)"BribeNoMoney"),
    Function_NameType(0x0104,(char *)"Noticed"),
    Function_NameType(0x0105,(char *)"Seen"),
    Function_NameType(0x0106,(char *)"Unseen"),
    Function_NameType(0x0107,(char *)"Lost"),
    Function_NameType(0x010E,(char *)"ServiceRefusal"),
    Function_NameType(0x010F,(char *)"BarterStart"),
    Function_NameType(0x0110,(char *)"BarterFail"),
    Function_NameType(0x0111,(char *)"Repair"),
    Function_NameType(0x0112,(char *)"Travel"),
    Function_NameType(0x0113,(char *)"Training"),
    Function_NameType(0x0114,(char *)"BarterBuyItem"),
    Function_NameType(0x0115,(char *)"BarterSellItem"),
    Function_NameType(0x0116,(char *)"BarterExit"),
    Function_NameType(0x0117,(char *)"BarterStolen"),
    Function_NameType(0x0118,(char *)"InfoRefusal"),
    Function_NameType(0x0119,(char *)"Idle"),
    Function_NameType(0x011A,(char *)"ObserveCombat"),
    Function_NameType(0x011B,(char *)"Corpse"),
    Function_NameType(0x011C,(char *)"TimeToGo"),
    Function_NameType(0x011D,(char *)"RepairExit"),
    Function_NameType(0x0120,(char *)"Recharge"),
    Function_NameType(0x0121,(char *)"RechargeExit"),
    Function_NameType(0x0124,(char *)"TrainingExit"),
    Function_NameType(0x012C,(char *)"MagicFailureSoundAlteration"),
    Function_NameType(0x012D,(char *)"MagicFailureSoundConjuration"),
    Function_NameType(0x012E,(char *)"MagicFailureSoundDestruction"),
    Function_NameType(0x012F,(char *)"MagicFailureSoundIllusion"),
    Function_NameType(0x0130,(char *)"MagicFailureSoundMysticism"),
    Function_NameType(0x0131,(char *)"MagicFailureSoundRestoration"),
    Function_NameType(0x0136,(char *)"DefaultPlayerSpell"),
    Function_NameType(0x0137,(char *)"DefaultMarksmanParalyzeSpell"),
    Function_NameType(0x0138,(char *)"MagicEnchantDrawSoundAlteration"),
    Function_NameType(0x0139,(char *)"MagicEnchantDrawSoundConjuration"),
    Function_NameType(0x013A,(char *)"MagicEnchantDrawSoundDestruction"),
    Function_NameType(0x013B,(char *)"MagicEnchantDrawSoundIllusion"),
    Function_NameType(0x013C,(char *)"MagicEnchantDrawSoundMysticism"),
    Function_NameType(0x013D,(char *)"MagicEnchantDrawSoundRestoration"),
    Function_NameType(0x013E,(char *)"MagicEnchantHitSoundAlteration"),
    Function_NameType(0x013F,(char *)"MagicEnchantHitSoundConjuration"),
    Function_NameType(0x0140,(char *)"MagicEnchantHitSoundDestruction"),
    Function_NameType(0x0141,(char *)"MagicEnchantHitSoundIllusion"),
    Function_NameType(0x0142,(char *)"MagicEnchantHitSoundMysticism"),
    Function_NameType(0x0143,(char *)"MagicEnchantHitSoundRestoration"),
    Function_NameType(0x0144,(char *)"effectAbsorb"),
    Function_NameType(0x0145,(char *)"effectReflect"),
    Function_NameType(0x0146,(char *)"LifeDetected"),
    Function_NameType(0x015E,(char *)"DefaultWeather"),
    Function_NameType(0x015F,(char *)"DefaultClimate"),
    Function_NameType(0x0191,(char *)"WelkyndStone"),
    Function_NameType(0x0192,(char *)"BlackSoulGem"),
    Function_NameType(0x0193,(char *)"AzuraStone"),
    Function_NameType(0x0194,(char *)"VarlaStone"),
    Function_NameType(0x0212,(char *)"FootSoundDirt"),
    Function_NameType(0x0213,(char *)"FootSoundGrass"),
    Function_NameType(0x0214,(char *)"FootSoundStone"),
    Function_NameType(0x0215,(char *)"FootSoundWater"),
    Function_NameType(0x0216,(char *)"FootSoundWood"),
    Function_NameType(0x0217,(char *)"FootSoundHeavyArmor"),
    Function_NameType(0x0218,(char *)"FootSoundLightArmor"),
    Function_NameType(0x0219,(char *)"FootSoundEarthLand"),
    Function_NameType(0x021A,(char *)"FootSoundGrassLand"),
    Function_NameType(0x021B,(char *)"FootSoundMetalLand"),
    Function_NameType(0x021C,(char *)"FootSoundStoneLand"),
    Function_NameType(0x021D,(char *)"FootSoundWaterLand"),
    Function_NameType(0x021E,(char *)"FootSoundWoodLand"),
    Function_NameType(0x021F,(char *)"FSTSnow"),
    Function_NameType(0x0220,(char *)"FSTSnowLand"),
    Function_NameType(0x0221,(char *)"FSTEarthSneak"),
    Function_NameType(0x0222,(char *)"FSTGrassSneak"),
    Function_NameType(0x0223,(char *)"FSTMetalSneak"),
    Function_NameType(0x0224,(char *)"FSTSnowSneak"),
    Function_NameType(0x0225,(char *)"FSTStoneSneak"),
    Function_NameType(0x0226,(char *)"FSTWaterSneak"),
    Function_NameType(0x0227,(char *)"FSTWoodSneak"),
    Function_NameType(0x0228,(char *)"FSTArmorLightSneak"),
    Function_NameType(0x0229,(char *)"FSTArmorHeavySneak"),
    Function_NameType(0x022B,(char *)"FSTMetal")
    };

Function_NameType EntryPoint_NameInit[] =
    {
    Function_NameType(0,(char *)"Calculate Weapon Damage"),
    Function_NameType(1,(char *)"Calculate My Critical Hit Chance"),
    Function_NameType(2,(char *)"Calculate My Critical Hit Damage"),
    Function_NameType(3,(char *)"Calculate Weapon Attack AP Cost"),
    Function_NameType(4,(char *)"Calculate Mine Explode Chance"),
    Function_NameType(5,(char *)"Adjust Range Penalty"),
    Function_NameType(6,(char *)"Adjust Limb Damage"),
    Function_NameType(7,(char *)"Calculate Weapon Range"),
    Function_NameType(8,(char *)"Calculate To Hit Chance"),
    Function_NameType(9,(char *)"Adjust Experience Points"),
    Function_NameType(10,(char *)"Adjust Gained Skill Points"),
    Function_NameType(11,(char *)"Adjust Book Skill Points"),
    Function_NameType(12,(char *)"Modify Recovered Health"),
    Function_NameType(13,(char *)"Calculate Inventory AP Cost"),
    Function_NameType(14,(char *)"Get Disposition"),
    Function_NameType(15,(char *)"Get Should Attack"),
    Function_NameType(16,(char *)"Get Should Assist"),
    Function_NameType(17,(char *)"Calculate Buy Price"),
    Function_NameType(18,(char *)"Get Bad Karma"),
    Function_NameType(19,(char *)"Get Good Karma"),
    Function_NameType(20,(char *)"Ignore Locked Terminal"),
    Function_NameType(21,(char *)"Add Leveled List On Death"),
    Function_NameType(22,(char *)"Get Max Carry Weight"),
    Function_NameType(23,(char *)"Modify Addiction Chance"),
    Function_NameType(24,(char *)"Modify Addiction Duration"),
    Function_NameType(25,(char *)"Modify Positive Chem Duration"),
    Function_NameType(26,(char *)"Adjust Drinking Radiation"),
    Function_NameType(27,(char *)"Activate"),
    Function_NameType(28,(char *)"Mysterious Stranger"),
    Function_NameType(29,(char *)"Has Paralyzing Palm"),
    Function_NameType(30,(char *)"Hacking Science Bonus"),
    Function_NameType(31,(char *)"Ignore Running During Detection"),
    Function_NameType(32,(char *)"Ignore Broken Lock"),
    Function_NameType(33,(char *)"Has Concentrated Fire"),
    Function_NameType(34,(char *)"Calculate Gun Spread"),
    Function_NameType(35,(char *)"Player Kill AP Reward"),
    Function_NameType(36,(char *)"Modify Enemy Critical Hit Chance"),
    Function_NameType(37,(char *)"Reload Speed"),
    Function_NameType(38,(char *)"Equip Speed"),
    Function_NameType(39,(char *)"Action Point Regen"),
    Function_NameType(40,(char *)"Action Point Cost"),
    Function_NameType(41,(char *)"Miss Fortune"),
    Function_NameType(42,(char *)"Modify Run Speed"),
    Function_NameType(43,(char *)"Modify Attack Speed"),
    Function_NameType(44,(char *)"Modify Radiation Consumed"),
    Function_NameType(45,(char *)"Has Pip Hacker"),
    Function_NameType(46,(char *)"Has Meltdown"),
    Function_NameType(47,(char *)"See Enemy Health"),
    Function_NameType(48,(char *)"Has Jury Rigging"),
    Function_NameType(49,(char *)"Modify Threat Range"),
    Function_NameType(50,(char *)"Modify Thread"),
    Function_NameType(51,(char *)"Has Fast Travel Always"),
    Function_NameType(52,(char *)"Knockdown Chance"),
    Function_NameType(53,(char *)"Modify Weapon Strength Req"),
    Function_NameType(54,(char *)"Modify Aiming Move Speed"),
    Function_NameType(55,(char *)"Modify Light Items"),
    Function_NameType(56,(char *)"Modify Damage Threshold (defender)"),
    Function_NameType(57,(char *)"Modify Chance for Ammo Item"),
    Function_NameType(58,(char *)"Modify Damage Threshold (attacker)"),
    Function_NameType(59,(char *)"Modify Throwing Velocity"),
    Function_NameType(60,(char *)"Chance for Item on Fire"),
    Function_NameType(61,(char *)"Has Unarmed Forward Power Attack"),
    Function_NameType(62,(char *)"Has Unarmed Back Power Attack"),
    Function_NameType(63,(char *)"Has Unarmed Crouched Power Attack"),
    Function_NameType(64,(char *)"Has Unarmed Counter Attack"),
    Function_NameType(65,(char *)"Has Unarmed Left Power Attack"),
    Function_NameType(66,(char *)"Has Unarmed Right Power Attack"),
    Function_NameType(67,(char *)"VATS HelperChance"),
    Function_NameType(68,(char *)"Modify Item Damage"),
    Function_NameType(69,(char *)"Has Improved Detection"),
    Function_NameType(70,(char *)"Has Improved Spotting"),
    Function_NameType(71,(char *)"Has Improved Item Detection"),
    Function_NameType(72,(char *)"Adjust Explosion Radius"),
    Function_NameType(73,(char *)"Reserved")
    };

const std::map<uint32_t, FunctionArguments> Function_Arguments(Function_ArgumentsInit, Function_ArgumentsInit + sizeof(Function_ArgumentsInit) / sizeof(Function_ArgumentsInit[0]));

const std::map<uint32_t, char *> Function_Name(Function_NameInit, Function_NameInit + sizeof(Function_NameInit) / sizeof(Function_NameInit[0]));
const std::map<uint32_t, char *> Comparison_Name(Comparison_NameInit, Comparison_NameInit + sizeof(Comparison_NameInit) / sizeof(Comparison_NameInit[0]));
const std::map<uint32_t, char *> IDLEGroup_Name(IDLEGroup_NameInit, IDLEGroup_NameInit + sizeof(IDLEGroup_NameInit) / sizeof(IDLEGroup_NameInit[0]));
const std::map<uint32_t, char *> PACKAIType_Name(PACKAIType_NameInit, PACKAIType_NameInit + sizeof(PACKAIType_NameInit) / sizeof(PACKAIType_NameInit[0]));
const std::map<uint32_t, char *> PACKLocType_Name(PACKLocType_NameInit, PACKLocType_NameInit + sizeof(PACKLocType_NameInit) / sizeof(PACKLocType_NameInit[0]));
const std::map<uint32_t, char *> PACKTargetType_Name(PACKTargetType_NameInit, PACKTargetType_NameInit + sizeof(PACKTargetType_NameInit) / sizeof(PACKTargetType_NameInit[0]));
const std::map<uint32_t, char *> HardCodedFormID_EditorID(HardCodedFormID_EditorIDInit, HardCodedFormID_EditorIDInit + sizeof(HardCodedFormID_EditorIDInit) / sizeof(HardCodedFormID_EditorIDInit[0]));

const std::map<uint32_t, char *> EntryPoint_Name(EntryPoint_NameInit, EntryPoint_NameInit + sizeof(EntryPoint_NameInit) / sizeof(EntryPoint_NameInit[0]));
const std::map<uint32_t, FunctionArguments> FNVFunction_Arguments(FNVFunction_ArgumentsInit, FNVFunction_ArgumentsInit + sizeof(FNVFunction_ArgumentsInit) / sizeof(FNVFunction_ArgumentsInit[0]));
const std::map<uint32_t, FunctionArguments> SKFunction_Arguments(SKFunction_ArgumentsInit, SKFunction_ArgumentsInit + sizeof(SKFunction_ArgumentsInit) / sizeof(SKFunction_ArgumentsInit[0]));

const float flt_max = FLT_MAX;
const float flt_min = FLT_MIN;
const float flt_3 = 3.0f;
const float flt_1 = 1.0f;
const float flt_0 = 0.0f;
const float flt_n2147483648 = -2147483648.0f;