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
// FragmentPERK.cpp

#include "FragmentPERK.h"

FragmentPERK::Fragment & FragmentPERK::Fragment::operator = (const Fragment &other)
{
    index = other.index;
    unk1 = other.unk1;
    unk2 = other.unk2;
    scriptName = other.scriptName;
    fragmentName = other.fragmentName;
    
    return *this;
}

bool FragmentPERK::Fragment::operator == (const Fragment &other) const
{
    return (index == other.index &&
            unk1 == other.unk1 &&
            unk2 == other.unk2 &&
            scriptName.equalsi(other.scriptName) &&
            fragmentName.equalsi(other.fragmentName)
            );
}

bool FragmentPERK::Fragment::operator != (const Fragment &other) const
{
    return !(*this == other);
}

FragmentPERK::FragmentPERK()
{
    //
}

FragmentPERK::~FragmentPERK()
{
    for (uint16_t i = 0; i < fragments.size(); ++i)
        delete fragments[i];
}

void FragmentPERK::Read(unsigned char *&buffer, const bool &CompressedOnDisk)
{
    // unk1
    unk1 = *(uint8_t *)buffer;
    buffer += 1;
    // fileName
    uint16_t nameSize = *(uint16_t *)buffer;
    buffer += 2;
    fileName.Read(buffer, nameSize, CompressedOnDisk);
    // fragmentCount
    uint16_t count = *(uint16_t *)buffer;
    buffer += 2;
    // fragments
    for (uint16_t i = 0; i < count; ++i)
    {
        Fragment *f = new Fragment;
        f->index = *(uint16_t *)buffer;
        buffer += 2;
        f->unk1 = *(uint16_t *)buffer;
        buffer += 2;
        f->unk2 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        f->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        f->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
        fragments.push_back(f);
    }
}

uint32_t FragmentPERK::GetSize() const
{
    // unk1 + fragmentCount + fileNameSize
    uint32_t total = sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
    total += fileName.GetSize();
    for (uint16_t i = 0; i < fragments.size(); ++i)
    {
        // unk1 + unk2 + index + scriptNameSize + fragmentNameSize
        total += (4 * sizeof(uint16_t)) + sizeof(uint8_t);
        total += fragments[i]->scriptName.GetSize();
        total += fragments[i]->fragmentName.GetSize();
    }
    return total;
}

void FragmentPERK::Write(FileWriter &writer) const
{
    writer.record_write(&unk1, sizeof(unk1));
    fileName.Write16(writer);
    uint16_t count = static_cast<uint16_t>(fragments.size());
    writer.record_write(&count, sizeof(count));
    for (uint16_t i = 0; i < count; ++i)
    {
        writer.record_write(&(fragments[i]->index), sizeof(uint16_t));
        writer.record_write(&(fragments[i]->unk1), sizeof(uint16_t));
        writer.record_write(&(fragments[i]->unk2), sizeof(uint8_t));
        fragments[i]->scriptName.Write16(writer);
        fragments[i]->fragmentName.Write16(writer);
    }
}

bool FragmentPERK::equals(const Fragments *other) const
{
    try
    {
        const FragmentPERK *o = reinterpret_cast<const FragmentPERK *>(other);
        if (fragments.size() != o->fragments.size())
            return false;
        for (uint16_t i = 0; i < fragments.size(); ++i)
            if (*(fragments[i]) != *(o->fragments[i]))
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Fragments * FragmentPERK::Copy() const
{
    FragmentPERK *f = new FragmentPERK;
    *f = *this;
    return (Fragments *)f;
}

FragmentPERK & FragmentPERK::operator = (const FragmentPERK &other)
{
    unk1 = other.unk1;
    fileName = other.fileName;

    for (uint16_t i = 0; i < fragments.size(); ++i)
        delete fragments[i];
    fragments.clear();

    for (uint16_t i = 0; i < other.fragments.size(); ++i)
    {
        fragments.push_back(new Fragment);
        *(fragments.back()) = *(other.fragments[i]);
    }

    return *this;
}
