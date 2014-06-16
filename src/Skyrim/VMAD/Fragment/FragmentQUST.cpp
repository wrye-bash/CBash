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
// FragmentQUST.cpp

#include "FragmentQUST.h"
#include "../Alias.h"

FragmentQUST::Fragment & FragmentQUST::Fragment::operator = (const Fragment &other)
{
    stage = other.stage;
    unk1 = other.unk1;
    stageIndex = other.stageIndex;
    unk2 = other.unk2;
    scriptName = other.scriptName;
    fragmentName = other.fragmentName;

    return *this;
}

bool FragmentQUST::Fragment::operator == (const Fragment &other) const
{
    return (stage == other.stage &&
            unk1 == other.unk1 &&
            stageIndex == other.stageIndex &&
            unk2 == other.unk2 &&
            scriptName.equalsi(other.scriptName) &&
            fragmentName.equalsi(other.fragmentName)
            );
}

bool FragmentQUST::Fragment::operator != (const Fragment &other) const
{
    return !(*this == other);
}

FragmentQUST::FragmentQUST()
{
    //
}

FragmentQUST::~FragmentQUST()
{
    for (UINT16 i = 0; i < fragments.size(); ++i)
        delete fragments[i];
    for (UINT16 i = 0; i < aliases.size(); ++i)
        delete aliases[i];
}

void FragmentQUST::Read(unsigned char *&buffer, const SINT16 &version, const SINT16 &objFormat, const bool &CompressedOnDisk)
{
    // unk1
    unk1 = *(UINT8 *)buffer;
    buffer += 1;
    // fragmentCount
    UINT16 count = *(UINT16 *)buffer;
    buffer += 2;
    // fileName
    UINT16 nameSize = *(UINT16 *)buffer;
    buffer += 2;
    fileName.Read(buffer, nameSize, CompressedOnDisk);
    // fragments
    for (UINT16 i = 0; i < count; ++i)
    {
        Fragment *f = new Fragment;
        f->stage = *(UINT16 *)buffer;
        buffer += 2;
        f->unk1 = *(UINT16 *)buffer;
        buffer += 2;
        f->stageIndex = *(SINT32 *)buffer;
        buffer += 4;
        f->unk2 = *(UINT8 *)buffer;
        buffer += 1;
        nameSize = *(UINT16 *)buffer;
        buffer += 2;
        f->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(UINT16 *)buffer;
        buffer += 2;
        f->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
        fragments.push_back(f);
    }
    // aliasCount
    count = *(UINT16 *)buffer;
    buffer += 2;
    for (UINT16 i = 0; i < count; ++i)
    {
        aliases.push_back(new Alias);
        aliases.back()->Read(buffer, version, objFormat, CompressedOnDisk);
    }
}

void FragmentQUST::VisitFormIDs(FormIDOp &op)
{
    for (UINT16 i = 0; i < aliases.size(); ++i)
        aliases[i]->VisitFormIDs(op);
}

UINT32 FragmentQUST::GetSize() const
{
    // unk1 + fragmentCount + fileNameSize + aliasCount
    UINT32 total = sizeof(UINT8) + sizeof(UINT16) + sizeof(UINT16) + sizeof(UINT16);
    total += fileName.GetSize();
    for (UINT16 i = 0; i < fragments.size(); ++i)
    {
        // stage + unk1 + stageIndex + unk2 + scriptNameSize + fragmentNameSize
        total += (4 * sizeof(UINT16)) + sizeof(UINT8) + sizeof(SINT32);
        total += fragments[i]->scriptName.GetSize();
        total += fragments[i]->fragmentName.GetSize();
    }
    for (UINT16 i = 0; i < aliases.size(); ++i)
        total += aliases[i]->GetSize();
    return total;
}

void FragmentQUST::Write(FileWriter &writer) const
{
    writer.record_write(&unk1, sizeof(unk1));
    UINT16 count = fragments.size();
    writer.record_write(&count, sizeof(count));
    fileName.Write16(writer);
    for (UINT16 i = 0; i < count; ++i)
    {
        writer.record_write(&(fragments[i]->stage), sizeof(UINT16));
        writer.record_write(&(fragments[i]->unk1), sizeof(UINT16));
        writer.record_write(&(fragments[i]->stageIndex), sizeof(SINT32));
        writer.record_write(&(fragments[i]->unk2), sizeof(UINT8));
        fragments[i]->scriptName.Write16(writer);
        fragments[i]->fragmentName.Write16(writer);
    }
    count = aliases.size();
    writer.record_write(&count, sizeof(count));
    for (UINT16 i = 0; i < count; ++i)
        aliases[i]->Write(writer);
}

bool FragmentQUST::equals(const Fragments *other) const
{
    try
    {
        const FragmentQUST *o = reinterpret_cast<const FragmentQUST *>(other);
        if (fragments.size() != o->fragments.size())
            return false;
        for (UINT16 i = 0; i < fragments.size(); ++i)
            if (*(fragments[i]) != *(o->fragments[i]))
                return false;
        if (aliases.size() != o->aliases.size())
            return false;
        for (UINT16 i = 0; i < aliases.size(); ++i)
            if (*(aliases[i]) != *(o->aliases[i]))
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Fragments * FragmentQUST::Copy() const
{
    FragmentQUST *f = new FragmentQUST;
    *f = *this;
    return (Fragments *)f;
}

FragmentQUST & FragmentQUST::operator = (const FragmentQUST &other)
{
    unk1 = other.unk1;
    fileName = other.fileName;

    for (UINT16 i = 0; i < fragments.size(); ++i)
        delete fragments[i];
    fragments.clear();

    for (UINT16 i = 0; i < other.fragments.size(); ++i)
    {
        fragments.push_back(new Fragment);
        *(fragments.back()) = *(other.fragments[i]);
    }

    for (UINT16 i = 0; i < aliases.size(); ++i)
        delete aliases[i];

    for (UINT16 i = 0; i < other.aliases.size(); ++i)
    {
        aliases.push_back(new Alias);
        *(aliases.back()) = *(other.aliases[i]);
    }

    return *this;
}
