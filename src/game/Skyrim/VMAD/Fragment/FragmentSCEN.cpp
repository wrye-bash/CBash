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
// FragmentSCEN.cpp

#include "FragmentSCEN.h"

FragmentSCEN::FragmentPhase & FragmentSCEN::FragmentPhase::operator = (const FragmentPhase &other)
{
    flags = other.flags;
    index = other.index;
    unk1 = other.unk1;
    scriptName = other.scriptName;
    fragmentName = other.fragmentName;

    return *this;
}

bool FragmentSCEN::FragmentPhase::operator == (const FragmentPhase &other) const
{
    return (flags == other.flags &&
            index == other.index &&
            unk1 == other.unk1 &&
            scriptName.equalsi(other.scriptName) &&
            fragmentName.equalsi(other.fragmentName)
            );
}

bool FragmentSCEN::FragmentPhase::operator != (const FragmentPhase &other) const
{
    return !(*this == other);
}

FragmentSCEN::FragmentSCEN() :
beginFragment(NULL), endFragment(NULL)
{
    //
}

FragmentSCEN::~FragmentSCEN()
{
    delete beginFragment;
    delete endFragment;
    for (uint16_t i = 0; i < phases.size(); ++i)
        delete phases[i];
}

void FragmentSCEN::Read(unsigned char *&buffer, const bool &CompressedOnDisk)
{
    // unk1
    unk1 = *(uint8_t *)buffer;
    buffer += 1;
    // flags
    uint8_t flags = *(uint8_t *)buffer;
    buffer += 1;
    // fileName
    uint16_t nameSize = *(uint16_t *)buffer;
    buffer += 2;
    fileName.Read(buffer, nameSize, CompressedOnDisk);
    // beginFragment
    if (flags & fHasBegin)
    {
        beginFragment = new GenFragment;
        beginFragment->unk1 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        beginFragment->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        beginFragment->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
    else
        beginFragment = NULL;
    // endFragment
    if (flags & fHasEnd)
    {
        endFragment = new GenFragment;
        endFragment->unk1 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        endFragment->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        endFragment->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
    else
        endFragment = NULL;
    // phaseCount
    uint16_t count = *(uint16_t *)buffer;
    buffer += 2;
    // phases
    for (uint16_t i = 0; i < count; ++i)
    {
        FragmentPhase *f = new FragmentPhase;
        f->flags = *(uint8_t *)buffer;
        buffer += 1;
        f->index = *(uint8_t *)buffer;
        buffer += 1;
        f->unk1 = *(uint32_t *)buffer;
        buffer += 4;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        f->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        f->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
        phases.push_back(f);
    }
}

uint32_t FragmentSCEN::GetSize() const
{
    // unk1 + flags + fileNameSize + phaseCount
    uint32_t total = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
    total += fileName.GetSize();
    if (beginFragment != NULL)
    {
        // unk1 + scriptNameSize + fragmentNameSize
        total += sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
        total += beginFragment->scriptName.GetSize();
        total += beginFragment->fragmentName.GetSize();
    }
    if (endFragment != NULL)
    {
        total += sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
        total += endFragment->scriptName.GetSize();
        total += endFragment->fragmentName.GetSize();
    }
    for (uint16_t i = 0; i < phases.size(); ++i)
    {
        // flags + index + unk1 + scriptNameSize + fragmentNameSize
        total += sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint32_t) + sizeof(uint16_t) + sizeof(uint16_t);
        total += phases[i]->scriptName.GetSize();
        total += phases[i]->fragmentName.GetSize();
    }
    return total;
}

void FragmentSCEN::Write(FileWriter &writer) const
{
    writer.record_write(&unk1, sizeof(unk1));
    uint8_t flags = ((beginFragment != NULL ? fHasBegin : 0) |
                   (endFragment != NULL ? fHasEnd : 0));
    writer.record_write(&flags, sizeof(flags));
    fileName.Write16(writer);
    if (beginFragment != NULL)
    {
        writer.record_write(&(beginFragment->unk1), sizeof(uint8_t));
        beginFragment->scriptName.Write16(writer);
        beginFragment->fragmentName.Write16(writer);
    }
    uint16_t count = static_cast<uint16_t>(phases.size());
    writer.record_write(&count, sizeof(count));
    for (uint16_t i = 0; i < count; ++i)
    {
        writer.record_write(&(phases[i]->flags), sizeof(uint8_t));
        writer.record_write(&(phases[i]->index), sizeof(uint8_t));
        writer.record_write(&(phases[i]->unk1), sizeof(uint32_t));
        phases[i]->scriptName.Write16(writer);
        phases[i]->fragmentName.Write16(writer);
    }
}

bool FragmentSCEN::equals(const Fragments *other) const
{
    try
    {
        const FragmentSCEN *o = reinterpret_cast<const FragmentSCEN *>(other);
        // beginFragment
        if (beginFragment != NULL && o->beginFragment == NULL)
            return false;
        if (beginFragment == NULL && o->beginFragment != NULL)
            return false;
        if (beginFragment != NULL && o->beginFragment != NULL)
            if (*beginFragment != *(o->beginFragment))
                return false;
        // endFragment
        if (endFragment != NULL && o->endFragment == NULL)
            return false;
        if (endFragment == NULL && o->endFragment != NULL)
            return false;
        if (endFragment != NULL && o->endFragment != NULL)
            if (*endFragment != *(o->endFragment))
                return false;
        // phases
        if (phases.size() != o->phases.size())
            return false;
        for (uint16_t i = 0; i < phases.size(); ++i)
            if (*(phases[i]) != *(o->phases[i]))
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Fragments * FragmentSCEN::Copy() const
{
    FragmentSCEN *f = new FragmentSCEN;
    *f = *this;
    return (Fragments *)f;
}

FragmentSCEN & FragmentSCEN::operator = (const FragmentSCEN &other)
{
    unk1 = other.unk1;
    fileName = other.fileName;

    if (beginFragment)
        delete beginFragment;
    if (other.beginFragment)
    {
        beginFragment = new GenFragment;
        *(beginFragment) = *(other.beginFragment);
    }
    else
        beginFragment = NULL;

    if (endFragment)
        delete endFragment;
    if (other.endFragment)
    {
        endFragment = new GenFragment;
        *(endFragment) = *(other.endFragment);
    }
    else
        endFragment = NULL;

    for (uint16_t i = 0; i < phases.size(); ++i)
        delete phases[i];
    phases.clear();

    for (uint16_t i = 0; i < other.phases.size(); ++i)
    {
        phases.push_back(new FragmentPhase);
        *(phases.back()) = *(other.phases[i]);
    }

    return *this;
}
