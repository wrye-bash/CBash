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
 *  Jacob "Lojack" Lojewski
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
// SkyrimCommon.cpp
#include "SkyrimCommon.h"

StringLookups::StringLookups()
{
    //
}

STRING StringLookups::GetFileName(STRING ModName, STRING Language, typeTypes Type) const
{
    // Assume that cwd is set to the 'Data' directory still,
    // it should have been set by Collection.AddMod
    size_t ModNameSize = strlen(ModName) - 4; // strlen(".esp")
    size_t LanguageSize = strlen(Language);
    size_t DirectorySize = 10; // strlen("./Strings/")
    size_t NameSize = ModNameSize + LanguageSize + DirectorySize + 2; // +2 = NULL and "_"
    NameSize += (Type == eStrings ? 8 : 10); // strlen(".STRINGS") : strlen(".DLSTRINGS") or strlen(".ILSTRINGS")
    
    // Allocate
    STRING FileName = new char[NameSize];
    strcpy(FileName, "./Strings/");
    strncat(FileName, ModName, ModNameSize);
    strcat(FileName, "_");
    strcat(FileName, Language);
    switch(Type)
    {
    case eStrings:
        strcat(FileName, ".STRINGS");
        break;
    case eDLStrings:
        strcat(FileName, ".DLSTRINGS");
        break;
    case eILStrings:
        strcat(FileName, ".ILSTRINGS");
        break;
    }
    return FileName;
}

bool StringLookups::Open(STRING ModName)
{
    if (ModName == NULL || file_map_strings.is_open())
        return false;

    /* TODO: Actually generate the applicible file names */
    // .STRINGS file.  For now, we'll assume ENGLISH is the language to use
    STRING StringsFileName = GetFileName(ModName, "English", eStrings);
    STRING DLStringsFileName = GetFileName(ModName, "English", eDLStrings);
    STRING ILStringsFileName = GetFileName(ModName, "English", eILStrings);

    try
    {
        Open(StringsFileName, file_map_strings);
        Open(DLStringsFileName, file_map_dlstrings);
        Open(ILStringsFileName, file_map_ilstrings);
    }
    catch(...)
    {
        Close();
        delete [] StringsFileName;
        delete [] DLStringsFileName;
        delete [] ILStringsFileName;
        throw;
    }

    delete [] StringsFileName;
    delete [] DLStringsFileName;
    delete [] ILStringsFileName;

    return true;
}

void StringLookups::Open(STRING FileName, boost::iostreams::mapped_file_source &file_map)
{
    try
    {
        file_map.open(FileName);
    }
    catch(std::ios::failure const &ex)
    {
        printer("StringLookups: Error - Unable to open \"%s\" as read only via memory mapping. The file is probably open in another application.\n", FileName);
        throw ex;
    }
    catch(std::exception &ex)
    {
        printer("StringLookups: Error - Unable to open \"%s\" as read only via memory mapping.\n", FileName);
        throw ex;
    }
    catch(...)
    {
        printer("StringLookups: Error - Unable to open \"%s\" as read only via memory mapping.  An unhandled exception occurred.\n", FileName);
        throw;
    }
}

bool StringLookups::Close()
    {
        // Cases where we care about the return value,
        // all files we either be open or closed.
        bool ret = file_map_strings.is_open();

        // Documentation isn't really clear if calling
        // close() on a closed file is bad, so check
        // anyway.
        if (ret)
            file_map_strings.close();
        if (file_map_dlstrings.is_open())
            file_map_dlstrings.close();
        if (file_map_ilstrings.is_open())
            file_map_ilstrings.close();

        return ret;
    }

void StringLookups::Load()
{
    Strings.clear();
    Load(file_map_strings, eStrings);
    Load(file_map_dlstrings, eDLStrings);
    Load(file_map_ilstrings, eILStrings);
}

void StringLookups::Load(boost::iostreams::mapped_file_source &file_map, typeTypes Type)
{
    UINT8 *buffer, *dataBegin;
    buffer = const_cast<UINT8 *>(reinterpret_cast<const UINT8 *>(file_map.data()));

    UINT32 stringCount = *reinterpret_cast<UINT32 *>(buffer);
    buffer += 8; // 4 for stringCount, 4 for dataSize (skipped)

    dataBegin = buffer + (stringCount * 8) + (Type == 0 ? 0 : 4);    

    for(UINT32 i = 0; i < stringCount; ++i)
    {
        UINT32 id = *reinterpret_cast<UINT32 *>(buffer);
        UINT32 offset = *reinterpret_cast<UINT32 *>(buffer);

        STRING value = reinterpret_cast<STRING>(dataBegin + offset);
        Strings[id] = value;
    }
}

LStringRecord::LStringRecord()
    : value(NULL),
      IsOnDisk(false)
{
    //
}

LStringRecord::LStringRecord(const LStringRecord &p)
    : value(NULL),
      IsOnDisk(false)
{
    if (!p.IsLoaded())
        return;

    if (p.IsOnDisk)
    {
        value = p.value;
        IsOnDisk = true;
    }
    else
    {
        UINT32 size = p.GetSize();
        value = new char[size];
        memcpy(value, p.value, size);
    }
}

LStringRecord::~LStringRecord()
{
    if(!IsOnDisk)
        delete [] value;
}

UINT32 LStringRecord::GetSize() const
{
    return value != NULL ? static_cast<UINT32>(strlen(value)) + 1 : 0;
}

bool LStringRecord::IsLoaded() const
{
    return value != NULL;
}

void LStringRecord::Load()
{
    //
}

void LStringRecord::Unload()
{
    if (!IsOnDisk)
    {
        delete [] value;
        value = NULL;
    }
}

bool LStringRecord::Read(unsigned char *&buffer, const UINT32 &subSize, const bool &CompressedOnDisk, StringLookups *LookupStrings)
{
    if (IsLoaded())
    {
        buffer += subSize;
        return false;
    }
    if (LookupStrings != NULL)
    {
        UINT32 Id = *reinterpret_cast<UINT32 *>(buffer);
        value = LookupStrings->Strings[Id];
        IsOnDisk = true;
    }
    else
    {
        if (CompressedOnDisk)
        {
            value = new char[subSize];
            memcpy(value, buffer, subSize);
        }
        else
        {
            value = const_cast<STRING>(reinterpret_cast<const STRING>(buffer));
            IsOnDisk = true;
        }
    }
    buffer += subSize;
    return true;
}

void LStringRecord::Write(UINT32 _Type, FileWriter &writer)
{
    if (value != NULL)
        writer.record_write_subrecord(_Type, value, static_cast<UINT32>(strlen(value)) + 1);
}

void LStringRecord::ReqWrite(UINT32 _Type, FileWriter &writer)
{
    if (value != NULL)
        writer.record_write_subrecord(_Type, value, static_cast<UINT32>(strlen(value)) + 1);
    else
    {
        UINT8 null = 0x00;
        writer.record_write_subrecord(_Type, &null, 1);
    }
}

void LStringRecord::Copy(STRING FieldValue)
{
    Unload();
    if (FieldValue != NULL)
    {
        IsOnDisk = false;
        UINT32 size = static_cast<UINT32>(strlen(FieldValue)) + 1;
        value = new char[size];
        memcpy(value, FieldValue, size);
    }
}

void LStringRecord::TruncateCopy(STRING FieldValue, UINT32 MaxSize)
{
    Unload();
    if (FieldValue != NULL)
    {
        IsOnDisk = false;
        UINT32 size = static_cast<UINT32>(strlen(FieldValue)) + 1;
        if (MaxSize > size)
            size = MaxSize;
        value = new char[size];
        memcpy(value, FieldValue, size);
        value[size - 1] = 0x00; //Ensure null termination in case of truncation
    }
}

bool LStringRecord::equals(const LStringRecord &other) const
{
    return cmps(value, other.value) == 0;
}

bool LStringRecord::equalsi(const LStringRecord &other) const
{
    return icmps(value, other.value) == 0;
}

LStringRecord& LStringRecord::operator = (const LStringRecord &rhs)
{
    if (this != &rhs)
    {
        Unload();
        if(rhs.IsOnDisk)
        {
            value = rhs.value;
            IsOnDisk = true;
        }
        else if (rhs.value != NULL)
        {
            IsOnDisk = false;
            UINT32 size = static_cast<UINT32>(strlen(rhs.VAL_NAME)) + 1;
            value = new char[size];
            memcpy(value, rhs.value, size);
        }
    }
    return *this;
}