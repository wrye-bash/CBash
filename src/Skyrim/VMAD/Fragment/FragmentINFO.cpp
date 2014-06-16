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
// FragmentINFO.cpp

#include "FragmentINFO.h"

FragmentINFO::FragmentINFO()
{
    //
}

FragmentINFO::~FragmentINFO()
{
    for (UINT8 i = 0; i < fragments.size(); ++i)
        delete fragments[i];
}

void FragmentINFO::Read(unsigned char *&buffer, const bool &CompressedOnDisk)
{
    // unk1
    unk1 = *(UINT8 *)buffer;
    buffer += 1;
    // fragmentCount
    UINT8 count = *(UINT8 *)buffer;
    buffer += 1;
    // fileName
    UINT16 nameSize = *(UINT16 *)buffer;
    buffer += 2;
    fileName.Read(buffer, nameSize, CompressedOnDisk);
    // fragments
    for (UINT8 i = 0; i < count; ++i)
    {
        GenFragment *f = new GenFragment;
        f->unk1 = *(UINT8 *)buffer;
        buffer += 1;
        UINT16 nameSize = *(UINT16 *)buffer;
        buffer += 2;
        f->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(UINT16 *)buffer;
        buffer += 2;
        f->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
}

UINT32 FragmentINFO::GetSize() const
{
    // unk1 + fragmentCount + fileNameSize
    UINT32 total = sizeof(UINT8) + sizeof(UINT8) + sizeof(UINT16);
    total += fileName.GetSize();
    for (UINT8 i = 0; i < fragments.size(); ++i)
    {
        // unk1 + scriptNameSize + fragmentNameSize
        total += sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT16);
        total += fragments[i]->scriptName.GetSize();
        total += fragments[i]->fragmentName.GetSize();
    }
    return total;
}

void FragmentINFO::Write(FileWriter &writer) const
{
    writer.record_write(&unk1, sizeof(unk1));
    UINT16 count = fragments.size();
    writer.record_write(&count, sizeof(count));
    fileName.Write16(writer);
    for (UINT16 i = 0; i < count; ++i)
    {
        writer.record_write(&(fragments[i]->unk1), sizeof(UINT8));
        fragments[i]->scriptName.Write16(writer);
        fragments[i]->fragmentName.Write16(writer);
    }
}

bool FragmentINFO::equals(const Fragments *other) const
{
    try
    {
        const FragmentINFO *o = reinterpret_cast<const FragmentINFO *>(other);
        if (fragments.size() != o->fragments.size())
            return false;
        for (UINT16 i = 0; i < fragments.size(); ++i)
            if (*(fragments[i]) != *(o->fragments[i]))
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Fragments * FragmentINFO::Copy() const
{
    FragmentINFO *f = new FragmentINFO;
    *f = *this;
    return (Fragments *)f;
}

FragmentINFO & FragmentINFO::operator = (const FragmentINFO &other)
{
    unk1 = other.unk1;
    fileName = other.fileName;

    for (UINT16 i = 0; i < fragments.size(); ++i)
        delete fragments[i];
    fragments.clear();

    for (UINT16 i = 0; i < other.fragments.size(); ++i)
    {
        fragments.push_back(new GenFragment);
        *(fragments.back()) = *(other.fragments[i]);
    }

    return *this;
}
