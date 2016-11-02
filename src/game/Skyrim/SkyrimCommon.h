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
#pragma once
// SkyrimCommon.h

#include "common/Common.h"
#include "VMAD/VMAD.h"
#include <map>


class StringLookups
    {
    public:
        enum typeTypes
        {
            eStrings =   0,     // .STRINGS file
            eDLStrings = 1,     // .DLSTRINGS file
            eILStrings = 2,     // .ILSTRINGS file
        };

        typedef std::map<uint32_t,char *> MapType;

    private:
        boost::iostreams::mapped_file_source file_map_strings;
        boost::iostreams::mapped_file_source file_map_dlstrings;
        boost::iostreams::mapped_file_source file_map_ilstrings;

        void Open(char * FileName, boost::iostreams::mapped_file_source &file_map);
        void Load(boost::iostreams::mapped_file_source &file_map, typeTypes Type);

        char * GetFileName(char * ModName, char * Language, typeTypes Type) const;

    public:
        /* For now we'll merge everything into one map, for speed an memory
           saving.  When writing these files becomes necessary, we'll need to
           provide a way to distinguish their source files. */
        MapType Strings;

        StringLookups();

        bool Open(char * ModName);
        bool Close();

        void Load();
    };

class LStringRecord
    {
    private:
        bool IsOnDisk;

    public:
        char * value;

        LStringRecord();
        LStringRecord(const LStringRecord &p);
        ~LStringRecord();

        uint32_t GetSize() const;

        bool IsLoaded() const;
        void Load();
        void Unload();

        bool Read(unsigned char *&buffer, const uint32_t &subSize, const bool &CompressedOnDisk, StringLookups *LookupStrings);
        void Write(uint32_t _Type, FileWriter &writer);
        void ReqWrite(uint32_t _Type, FileWriter &writer);

        void Copy(char * FieldValue);
        void TruncateCopy(char * FieldValue, uint32_t MaxSize);

        bool equals(const LStringRecord &other) const;
        bool equalsi(const LStringRecord &other) const;
        LStringRecord& operator = (const LStringRecord &rhs);
    };
