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
// FragmentPACK.cpp

#include "FragmentPACK.h"

FragmentPACK::FragmentPACK() :
onBegin(NULL), onEnd(NULL), onChange(NULL)
{
    //
}

FragmentPACK::~FragmentPACK()
{
    delete onBegin;
    delete onEnd;
    delete onChange;
}

void FragmentPACK::Read(unsigned char *&buffer, const bool &CompressedOnDisk)
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
    // fragments
    if (flags & fHasOnBegin)
    {
        onBegin = new GenFragment;
        onBegin->unk1 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onBegin->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onBegin->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
    else
        onBegin = NULL;
    if (flags & fHasOnEnd)
    {
        onEnd = new GenFragment;
        onEnd->unk1 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onEnd->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onEnd->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
    else
        onEnd = NULL;
    if (flags  & fHasOnChange)
    {
        onChange = new GenFragment;
        onChange->unk1 = *(uint8_t *)buffer;
        buffer += 1;
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onChange->scriptName.Read(buffer, nameSize, CompressedOnDisk);
        nameSize = *(uint16_t *)buffer;
        buffer += 2;
        onChange->fragmentName.Read(buffer, nameSize, CompressedOnDisk);
    }
    else
        onChange = NULL;
}

uint32_t FragmentPACK::GetSize() const
{
    // unk1 + flags + fileNameSize
    uint32_t total = sizeof(uint8_t) + sizeof(uint8_t) + sizeof(uint16_t);
    total += fileName.GetSize();
    if (onBegin != NULL)
    {
        // unk1 + scriptNameSize + fragmentNameSize
        total += sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
        total += onBegin->scriptName.GetSize();
        total += onBegin->fragmentName.GetSize();
    }
    if (onEnd != NULL)
    {
        total += sizeof(uint8_t) + sizeof(uint16_t) + sizeof(uint16_t);
        total += onEnd->scriptName.GetSize();
        total += onEnd->fragmentName.GetSize();
    }
    if (onChange != NULL)
    {
        total += sizeof(uint8_t)+sizeof(uint16_t)+sizeof(uint16_t);
        total += onChange->scriptName.GetSize();
        total += onChange->fragmentName.GetSize();
    }
    return total;
}

void FragmentPACK::Write(FileWriter &writer) const
{
    writer.record_write(&unk1, sizeof(unk1));
    uint8_t flags = ((onBegin != NULL ? fHasOnBegin : 0) |
                   (onEnd != NULL ? fHasOnEnd : 0) |
                   (onChange != NULL ? fHasOnChange : 0)
                   );
    writer.record_write(&flags, sizeof(flags));
    fileName.Write16(writer);
    if (onBegin != NULL)
    {
        writer.record_write(&(onBegin->unk1), sizeof(uint8_t));
        onBegin->scriptName.Write16(writer);
        onBegin->fragmentName.Write16(writer);
    }
    if (onEnd != NULL)
    {
        writer.record_write(&(onEnd->unk1), sizeof(uint8_t));
        onEnd->scriptName.Write16(writer);
        onEnd->fragmentName.Write16(writer);
    }
    if (onChange != NULL)
    {
        writer.record_write(&(onChange->unk1), sizeof(uint8_t));
        onChange->scriptName.Write16(writer);
        onChange->fragmentName.Write16(writer);
    }
}

bool FragmentPACK::equals(const Fragments *other) const
{
    try
    {
        const FragmentPACK *o = reinterpret_cast<const FragmentPACK *>(other);
        // begin fragment
        if (onBegin != NULL && o->onBegin == NULL)
            return false;
        if (onBegin == NULL && o->onBegin != NULL)
            return false;
        if (onBegin != NULL && o->onBegin != NULL)
            if (*onBegin != *(o->onBegin))
                return false;
        // end fragment
        if (onEnd != NULL && o->onEnd == NULL)
            return false;
        if (onEnd == NULL && o->onEnd != NULL)
            return false;
        if (onEnd != NULL && o->onBegin != NULL)
            if (*onEnd != *(o->onEnd))
                return false;
        // change fragment
        if (onChange != NULL && o->onChange == NULL)
            return false;
        if (onChange == NULL && o->onChange != NULL)
            return false;
        if (onChange != NULL && o->onChange != NULL)
            if (*onChange != *(o->onChange))
                return false;
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Fragments * FragmentPACK::Copy() const
{
    FragmentPACK *f = new FragmentPACK;
    *f = *this;
    return (Fragments *)f;
}

FragmentPACK & FragmentPACK::operator = (const FragmentPACK &other)
{
    unk1 = other.unk1;
    fileName = other.fileName;

    if (onBegin)
        delete onBegin;
    if (other.onBegin)
    {
        onBegin = new GenFragment;
        *onBegin = *(other.onBegin);
    }
    else
        onBegin = NULL;

    if (onEnd)
        delete onEnd;
    if (other.onEnd)
    {
        onEnd = new GenFragment;
        *onEnd = *(other.onEnd);
    }
    else
        onEnd = NULL;

    if (onChange)
        delete onChange;
    if (other.onChange)
    {
        onChange = new GenFragment;
        *onChange = *(other.onChange);
    }
    else
        onChange = NULL;

    return *this;
}
