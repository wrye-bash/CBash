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
// PropertyString.cpp

#include "PropertyString.h"

uint32_t PropertyString::GetSize() const
{
    // common + valueSize + value
    return Property::GetSize() + sizeof(uint16_t) + value.GetSize();
}

void PropertyString::Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk)
{
    Property::Read(buffer, version, objFormat, CompressedOnDisk);
    uint16_t strSize = *(uint16_t *)buffer;
    buffer += 2;
    value.Read(buffer, strSize, CompressedOnDisk);
}

void PropertyString::Write(FileWriter &writer)
{
    Property::Write(writer);
    value.Write16(writer);
}

bool PropertyString::equals(const Property *other) const
{
    try
    {
        const PropertyString *o = reinterpret_cast<const PropertyString *>(other);
        return value.equals(o->value);
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyString::Copy() const
{
    PropertyString *p = new PropertyString;
    *p = *this;
    return (Property *)p;
}

PropertyString & PropertyString::operator = (const PropertyString  &other)
{
    name = other.name;
    // type - same already
    status = other.status;
    value = other.value;
    return *this;
}

uint32_t PropertyStringArray::GetSize() const
{
    // common + itemCount
    uint32_t total = Property::GetSize() + sizeof(uint32_t);
    for (uint32_t i = 0; i < size(); ++i)
        total += sizeof(uint16_t)+(*this)[i].GetSize();
    return total;
}

void PropertyStringArray::Read(unsigned char *&buffer, const int16_t &version, const int16_t &objFormat, const bool &CompressedOnDisk)
{
    uint32_t count = *(uint32_t *)buffer;
    buffer += 4;

    resize(count);
    for (uint32_t i = 0; i < count; ++i)
    {
        uint16_t strSize = *(uint16_t *)buffer;
        buffer += 2;
        (*this)[i].Read(buffer, strSize, CompressedOnDisk);
    }
}

void PropertyStringArray::Write(FileWriter &writer)
{
    Property::Write(writer);
    uint32_t count = size();
    writer.record_write(&count, sizeof(count));
    for (uint32_t i = 0; i < count; ++i)
        (*this)[i].Write16(writer);
}

bool PropertyStringArray::equals(const Property *other) const
{
    try
    {
        const PropertyStringArray *o = reinterpret_cast<const PropertyStringArray *>(other);
        if (size() != o->size())
            return false;
        for (uint32_t i = 0; i < size(); ++i)
        {
            if (!(*this)[i].equals((*o)[i]))
                return false;
        }
        return true;
    }
    catch (...)
    {
        return false;
    }
}

Property * PropertyStringArray::Copy() const
{
    PropertyStringArray *p = new PropertyStringArray;
    *p = *this;
    return (Property *)p;
}

PropertyStringArray & PropertyStringArray::operator = (const PropertyStringArray &other)
{
    name = other.name;
    status = other.status;
    assign(other.begin(), other.end());
    return *this;
}
